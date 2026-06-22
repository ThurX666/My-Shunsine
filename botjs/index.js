require('dotenv').config();

const {
    ActionRowBuilder,
    ButtonBuilder,
    ButtonStyle,
    Client,
    EmbedBuilder,
    GatewayIntentBits,
    MessageFlags,
    REST,
    Routes,
    SlashCommandBuilder,
} = require('discord.js');
const mysql = require('mysql2/promise');

const { getConfig, validateConfig, canAccessPanel } = require('./config');
const { getServerInfo } = require('./Mysql/address');
const { checkMySQLConnection } = require('./Mysql/utils');
const {
    ButtonBindAccount,
    ButtonChangePassword,
    ButtonCreateAccount,
    factionModal,
} = require('./modal/modals');
const { HandleAdminLevel } = require('./interactions/admin');
const { handleBindAccount } = require('./interactions/bind');
const { handleChangePassword } = require('./interactions/changePassword');
const { generateRedeem } = require('./interactions/redeem');
const { handleCreateAccount } = require('./interactions/register');
const { handleReverify } = require('./interactions/reverif');

const config = getConfig();
const serverInfo = getServerInfo();

const commands = [
    new SlashCommandBuilder()
        .setName('showpanel')
        .setDescription('User Control Panel'),
    new SlashCommandBuilder()
        .setName('setadmin')
        .setDescription('Set a user as admin.')
        .addStringOption(option =>
            option.setName('username')
                .setDescription('The username of the player to set as admin.')
                .setRequired(true))
        .addIntegerOption(option =>
            option.setName('level')
                .setDescription('Admin level to assign.')
                .setRequired(true)),
    new SlashCommandBuilder()
        .setName('players')
        .setDescription('To see the number of players on IC'),
    new SlashCommandBuilder()
        .setName('changelog')
        .setDescription('Send new server changelog.')
        .addStringOption(option =>
            option.setName('version')
                .setDescription('Versi changelog')
                .setRequired(true))
        .addStringOption(option =>
            option.setName('changed')
                .setDescription('Detail perubahan')
                .setRequired(true))
        .addStringOption(option =>
            option.setName('fixes_improvement')
                .setDescription('Detail perbaikan dan peningkatan')
                .setRequired(true)),
    new SlashCommandBuilder()
        .setName('faction')
        .setDescription('Create buttons for faction Discord links'),
    new SlashCommandBuilder()
        .setName('createrdm')
        .setDescription('Create a new redeem code')
        .addStringOption(option =>
            option.setName('code')
                .setDescription('The redeem code')
                .setRequired(true))
        .addStringOption(option =>
            option.setName('type')
                .setDescription('Type of reward')
                .setRequired(true)
                .addChoices(
                    { name: 'Money', value: 'money' },
                    { name: 'Gold', value: 'gold' },
                    { name: 'VIP', value: 'vip' }
                ))
        .addIntegerOption(option =>
            option.setName('amount')
                .setDescription('Amount of the reward')
                .setRequired(true))
        .addIntegerOption(option =>
            option.setName('limit')
                .setDescription('Usage limit for the code')
                .setRequired(true)),
    new SlashCommandBuilder()
        .setName('serveronline')
        .setDescription('Kirim pesan bahwa server online'),
    new SlashCommandBuilder()
        .setName('serveroffline')
        .setDescription('Kirim pesan bahwa server offline tanpa pengecekan'),
    new SlashCommandBuilder()
        .setName('serverrestart')
        .setDescription('Kirim pesan bahwa server sedang restart')
].map(command => command.toJSON());

const bannedWordsList = [
    'anjeng', 'allah', 'anjg', 'anjing', 'ass', 'asu', 'bab1', 'babi', 'bajingan', 'bangsat', 'bego', 'bego.jing', 'begok',
    'bencong', 'bgst', 'bitch', 'bjir', 'blok', 'brengsek', 'buajingan', 'cok', 'dancok', 'dongo',
    'dungu', 'entod', 'entot', 'fuck', 'goblok', 'haram', 'idiot', 'jablay', 'jancok', 'jembut', 'jeng',
    'jiancok', 'jir', 'jmbt', 'juancok', 'k0nt0l', 'konto', 'k0ntol', 'ktl', 'kampang', 'kampret', 'kanjut', 'khontol',
    'kimak', 'kintil', 'kintil.kontol', 'kirik', 'kntl', 'konol', 'kntol', 'kontl', 'kontol', 'Kontol', 'kontols', 'kuntul',
    'kunyuk', 'lol', 'lonte', 'meki', 'memek', 'memeks', 'Memeks', 'memeq', 'memk', 'mmek',
    'mmk', 'ng3n', 'Ng3nt0d', 'ng3nt0t', 'ngen', 'ngento', 'ngengod', 'ngent', 'ngentd', 'ngentod', 'Ngentod²',
    'ngentot', 'ngentt', 'ngew', 'ngewe', 'ngntd', 'ngntot', 'nhentod', 'nhentot', 'njing',
    'nyeong', 'p0rn', 'pantek', 'peler', 'poorn', 'porn', 'pornn', 'pornrn', 'puki', 'pukimak', 'sange',
    'sepong', 'sepongin', 'spong', 't0d', 't0l0l', 't0t', 'tai', 'taik', 'talal', 'telaso', 'tempik', 'tilil', 'tll',
    'tlol', 'tod', 'tolol', 'tot', 'tulul', 'yatim', 'y4tim', 'yat1m', 'y4t1m', 'yteam', 'yesus',
];
const bannedWordsRegex = new RegExp(`\\b(${bannedWordsList.join('|')})\\b`, 'i');
const userWarnings = new Map();

let pool;
let client;

function createPool() {
    console.log(`Creating MySQL pool for ${config.db.host}:${config.db.port}/${config.db.database}`);
    return mysql.createPool({
        host: config.db.host,
        port: config.db.port,
        user: config.db.user,
        password: config.db.password,
        database: config.db.database,
        waitForConnections: true,
        connectionLimit: 10,
        queueLimit: 0,
        connectTimeout: config.db.connectTimeout,
    });
}

function createClient() {
    return new Client({
        intents: [
            GatewayIntentBits.Guilds,
            GatewayIntentBits.GuildMessages,
            GatewayIntentBits.MessageContent,
        ],
    });
}

async function registerCommandsForClient(activeClient) {
    if (!config.registerCommands) {
        console.log('Slash command registration skipped because REGISTER_COMMANDS=false.');
        return;
    }

    const rest = new REST({ version: '10' }).setToken(config.discordToken);

    console.log('Started refreshing application (/) commands.');
    await rest.put(Routes.applicationCommands(activeClient.user.id), { body: commands });
    console.log('Successfully reloaded application (/) commands.');
}

function buildPanelEmbed() {
    return {
        color: 0x111211,
        title: 'UCP Registration My Sunshine Roleplay',
        description: 'We have provided an option below to help you:',
        fields: [
            { name: '__Register Account Button__', value: `> If you don't have a UCP account or it's your first time joining our server, you can use the button to create an account.` },
            { name: '__Change Password Account Button__', value: '> If you have problems forgetting your password, you can use the button to create a new password.' },
            { name: '__Reverify Account Button__', value: "> To send a re-verification code if you don't get the bot verification code in your DM." },
            { name: '__Bind Account Button__', value: "> To bind your discord account with a UCP account, make sure you still remember the PIN code when creating the first UCP account." },
        ],
        image: { url: config.images.register },
        footer: { text: 'Copyright (c) 2025 My Sunshine Roleplay (All rights reversed)' },
        timestamp: new Date(),
    };
}

function buildPanelButtons() {
    const buttonCreate = new ButtonBuilder()
        .setCustomId('create_account')
        .setLabel('Register!')
        .setStyle(ButtonStyle.Primary);

    const buttonChange = new ButtonBuilder()
        .setCustomId('change_password')
        .setLabel('Change Password!')
        .setStyle(ButtonStyle.Secondary);

    const buttonReverify = new ButtonBuilder()
        .setCustomId('reverify')
        .setLabel('Reverif!')
        .setStyle(ButtonStyle.Success);

    const buttonBind = new ButtonBuilder()
        .setCustomId('bind_account')
        .setLabel('Bind!')
        .setStyle(ButtonStyle.Danger);

    return new ActionRowBuilder().addComponents(buttonCreate, buttonChange, buttonReverify, buttonBind);
}

function logInteraction(interaction, detail) {
    const guildName = interaction.guild?.name ?? 'DM';
    const channelName = interaction.channel?.name ?? interaction.channelId ?? 'unknown-channel';
    console.log(
        `[interaction] type=${interaction.type} user=${interaction.user?.tag ?? interaction.user?.id} guild=${guildName} channel=${channelName} detail=${detail}`
    );
}

async function handleSlashCommand(interaction) {
    const { commandName } = interaction;
    logInteraction(interaction, `slash:${commandName}`);

    if (commandName === 'showpanel') {
        if (!canAccessPanel(interaction, config)) {
            await interaction.reply({ content: 'You do not have permission to use this command.', flags: MessageFlags.Ephemeral });
            return;
        }

        await interaction.reply({ embeds: [buildPanelEmbed()], components: [buildPanelButtons()] });
        return;
    }

    if (commandName === 'setadmin') {
        if (!canAccessPanel(interaction, config)) {
            await interaction.reply({ content: 'You do not have permission to use this command.', flags: MessageFlags.Ephemeral });
            return;
        }

        await HandleAdminLevel(interaction, pool);
        return;
    }

    if (commandName === 'createrdm') {
        if (!canAccessPanel(interaction, config)) {
            await interaction.reply({ content: 'You do not have permission to use this command.', flags: MessageFlags.Ephemeral });
            return;
        }

        await generateRedeem(interaction, pool, config);
        return;
    }

    if (commandName === 'players') {
        await interaction.reply({ content: 'Sistem pengecekan pemain sedang dinonaktifkan sementara.', flags: MessageFlags.Ephemeral });
        return;
    }

    if (commandName === 'changelog') {
        if (!canAccessPanel(interaction, config)) {
            await interaction.reply({ content: 'You do not have permission to use this command.', flags: MessageFlags.Ephemeral });
            return;
        }

        if (!config.discord.updateChannelId) {
            await interaction.reply({ content: 'UPDATE_CHANNEL_ID is not configured.', flags: MessageFlags.Ephemeral });
            return;
        }

        const version = interaction.options.getString('version');
        const changedFormatted = interaction.options.getString('changed').replace(/,/g, '\n');
        const fixesFormatted = interaction.options.getString('fixes_improvement').replace(/,/g, '\n');
        const channelUpdate = await client.channels.fetch(config.discord.updateChannelId);
        const currentDate = new Date();
        const formattedDate = currentDate.toLocaleDateString('id-ID', {
            year: 'numeric',
            month: 'long',
            day: 'numeric',
            hour: 'numeric',
            minute: 'numeric',
            timeZone: 'Asia/Jakarta',
            hour12: false,
        });

        const changelogEmbed = new EmbedBuilder()
            .setColor(0x111211)
            .setTitle(`Changelogs v${version}`)
            .addFields(
                { name: '__Changes__', value: changedFormatted },
                { name: '__Fixes & Improvement__', value: fixesFormatted },
            )
            .setFooter({ text: `Update pada ${formattedDate} WIB`, iconURL: interaction.user.displayAvatarURL({ dynamic: true, size: 32 }) });

        await channelUpdate.send({ embeds: [changelogEmbed] });
        await interaction.reply({ content: 'Changelog sent successfully.', flags: MessageFlags.Ephemeral });
        return;
    }

    if (commandName === 'faction') {
        await factionModal(interaction, config);
        return;
    }

    if (['serveronline', 'serveroffline', 'serverrestart'].includes(commandName)) {
        const imageMap = {
            serveronline: config.images.online,
            serveroffline: config.images.offline,
            serverrestart: config.images.restart,
        };
        const statusMap = {
            serveronline: 'Online',
            serveroffline: 'Offline',
            serverrestart: 'Restarting',
        };

        const embed = new EmbedBuilder()
            .setTitle('My Sunshine Roleplay')
            .setDescription(`Server is now **${statusMap[commandName]}!**`)
            .setColor(0x111211)
            .addFields(
                { name: 'Host:', value: `${serverInfo.host}:${serverInfo.port}`, inline: true },
                { name: 'Version:', value: '0.1.20n/0.3DL', inline: true }
            )
            .setImage(imageMap[commandName]);

        await interaction.reply({ content: '@everyone', embeds: [embed] });
    }
}

async function handleInteraction(interaction) {
    if (interaction.isChatInputCommand()) {
        await handleSlashCommand(interaction);
        return;
    }

    if (interaction.isButton()) {
        logInteraction(interaction, `button:${interaction.customId}`);
        if (interaction.customId === 'create_account') {
            await ButtonCreateAccount(interaction, pool);
            return;
        }

        if (interaction.customId === 'change_password') {
            await ButtonChangePassword(interaction, pool);
            return;
        }

        if (interaction.customId === 'reverify') {
            await handleReverify(interaction, pool, config);
            return;
        }

        if (interaction.customId === 'bind_account') {
            await ButtonBindAccount(interaction, pool);
        }

        return;
    }

    if (interaction.isModalSubmit()) {
        logInteraction(interaction, `modal:${interaction.customId}`);
        if (interaction.customId === 'create_account_modal') {
            await handleCreateAccount(interaction, pool, config);
            return;
        }

        if (interaction.customId === 'change_password_modal') {
            await handleChangePassword(interaction, pool);
            return;
        }

        if (interaction.customId === 'bind_account_modal') {
            await handleBindAccount(interaction, pool);
        }

        return;
    }

    if (interaction.isStringSelectMenu() && interaction.customId === 'list-faction') {
        logInteraction(interaction, `select:${interaction.customId}:${interaction.values.join(',')}`);
        await interaction.deferUpdate();

        const factionMessages = {
            'police-menu': '**__POLICE DEPARTMENT DISCORD__**\n\nhttps://discord.gg/DJmBPctTZJ',
            'fire-menu': '_FIRE DEPARTMENT DISCORD_\n\nhttps://discord.gg/dDQdszE4GW',
            'news-menu': '_NEWS AGENCY DISCORD_\n\nhttps://discord.gg/9HVjJ8fR8e',
            'sags-menu': '_GOVERMENT SERVICE DISCORD_\n\nhttps://discord.gg/hS4nKZRpj7',
            'family-menu': '**__FAMILIES AND GANG__**\n\nhttps://discord.gg/npDwAp8MEt',
        };

        const message = factionMessages[interaction.values[0]] ?? 'Invalid selection.';
        await interaction.followUp({ content: message, flags: MessageFlags.Ephemeral });
    }
}

async function handleInfoMessage(message) {
    if (message.author.bot) {
        return;
    }

    console.log(
        `[message] user=${message.author.tag} guild=${message.guild?.name ?? 'DM'} channel=${message.channel?.name ?? message.channelId} content=${message.content}`
    );

    if (config.discord.excludedChannelId && message.channel.id === config.discord.excludedChannelId) {
        return;
    }

    if (message.content.toLowerCase().includes('ip')) {
        await message.reply(`The server's IP address is: \`${serverInfo.host}:${serverInfo.port}\``);
    }

    if (message.content.toLowerCase().includes('ucp')) {
        await message.reply(`Go to ${config.discord.ucpHelpUrl} to create your account`);
    }
}

async function handleModerationMessage(message) {
    if (message.author.bot || !bannedWordsRegex.test(message.content.toLowerCase())) {
        return;
    }

    try {
        await message.delete();

        const warnings = (userWarnings.get(message.author.id) || 0) + 1;
        userWarnings.set(message.author.id, warnings);

        const warningMessage = await message.channel.send(`${message.author}, pesan kamu mengandung konten yang tidak pantas dan telah dihapus. Ini adalah peringatan ke-${warnings}/3.`);
        setTimeout(() => {
            warningMessage.delete().catch(err => console.error('Gagal menghapus pesan peringatan:', err));
        }, 3000);

        if (warnings >= 3 && message.member) {
            await message.member.timeout(10 * 60 * 1000, 'Penggunaan bahasa tidak pantas berulang kali');
            await message.channel.send(`${message.author} telah diberi timeout selama 10 menit karena berulang kali menggunakan bahasa yang tidak pantas.`);
            userWarnings.set(message.author.id, 0);
        }
    } catch (error) {
        console.error('Gagal menghapus pesan atau memberikan timeout:', error);
    }
}

function attachClientEvents(activeClient) {
    activeClient.once('clientReady', async () => {
        console.log(`Discord client ready as ${activeClient.user.tag}`);
        await registerCommandsForClient(activeClient);
    });

    activeClient.on('interactionCreate', async interaction => {
        try {
            await handleInteraction(interaction);
        } catch (error) {
            console.error('Interaction handling failed:', error);

            if (interaction.isRepliable() && !interaction.replied && !interaction.deferred) {
                await interaction.reply({ content: ':x: An error occurred while processing your request.', flags: MessageFlags.Ephemeral });
            }
        }
    });

    activeClient.on('messageCreate', async message => {
        try {
            await handleInfoMessage(message);
            await handleModerationMessage(message);
        } catch (error) {
            console.error('Message handling failed:', error);
        }
    });
}

async function start() {
    console.log('Bot startup initiated.');
    const missing = validateConfig(config);

    if (missing.length > 0) {
        throw new Error(`Missing required environment variables: ${missing.join(', ')}`);
    }

    console.log('Configuration validation passed.');

    pool = createPool();
    console.log('Checking MySQL connectivity...');

    const mysqlReady = await checkMySQLConnection(pool);
    if (!mysqlReady) {
        throw new Error('MySQL connectivity check failed.');
    }

    if (!config.enableBotLogin) {
        console.log('ENABLE_BOT_LOGIN=false, Discord login skipped after successful config and DB validation.');
        await pool.end();
        pool = null;
        return;
    }

    client = createClient();
    attachClientEvents(client);
    console.log('Discord client created.');

    if (config.dryRun) {
        console.log('DRY_RUN=true, Discord login skipped.');
        await pool.end();
        pool = null;
        return;
    }

    console.log('Attempting Discord login...');
    await client.login(config.discordToken);
    console.log('Discord login promise resolved.');
}

if (require.main === module) {
    start().catch(error => {
        console.error('Bot startup failed:', error);
        process.exitCode = 1;
    });
}

module.exports = {
    config,
    commands,
    createClient,
    createPool,
    getClient: () => client,
    getPool: () => pool,
    start,
};
