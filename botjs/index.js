require('dotenv').config();
const { Client, GatewayIntentBits, REST, Routes, SlashCommandBuilder, ButtonBuilder, ButtonStyle, ActionRowBuilder, EmbedBuilder, MessageFlags } = require('discord.js');
const mysql = require('mysql2/promise');
//const cron = require('node-cron');
// const samp = require('samp-query');
const { serverInfo } = require('./Mysql/address');
const { ButtonBindAccount, ButtonCreateAccount, ButtonChangePassword } = require('./modal/modals');
const { handleCreateAccount } = require('./interactions/register');
const { handleChangePassword } = require('./interactions/changePassword');
const { handleReverify } = require('./interactions/reverif');
const { handleBindAccount } = require('./interactions/bind');
const { HandleAdminLevel } = require('./interactions/admin');
const { checkMySQLConnection } = require('./Mysql/utils');
// const { startActivityUpdater } = require('./interactions/activity');
const { generateRedeem } = require('./interactions/redeem');
// Adjust the path as necessary based on your file structure
const {
    factionModal // Import it here
} = require('./modal/modals'); // Change this to the correct path





// Token dan konfigurasi lainnya
const CHANNEL_ID = '1227299320836132864'; // Ganti dengan channel ID kamu
const IMAGE_ON = 'https://cdn.discordapp.com/attachments/1500909054153854986/1500909274803736727/standard.gif?ex=69facef0&is=69f97d70&hm=494642bea7ebb781a57d3353ec48eca02f8246c544910650553eec3b0a910ed0&'; // URL gambar
const IMAGE_OFF = 'https://cdn.discordapp.com/attachments/1500909054153854986/1500909274459672677/standard.gif?ex=69facef0&is=69f97d70&hm=8182d16f55e30aa344e72a383484d14b9b128ab6ba86804af977ac7a42bc714b&';
const IMAGE_RESTART = 'https://cdn.discordapp.com/attachments/1500909054153854986/1500910588476260582/standard.gif?ex=69fad029&is=69f97ea9&hm=b5316d2f4c379ae6b27d1cdec621a12258443142fcdbddfe30d57d6d4c747da3';

// Inisialisasi client Discord
const client = new Client({
    intents: [
        GatewayIntentBits.Guilds,
        GatewayIntentBits.GuildMessages,
        GatewayIntentBits.MessageContent
    ]
});



// Setup MySQL connection
const pool = mysql.createPool({
    host: process.env.DB_HOST,
    user: process.env.DB_USER,
    password: process.env.DB_PASSWORD,
    database: process.env.DB_NAME,
    waitForConnections: true,
    connectionLimit: 10,
    queueLimit: 0,
    connectTimeout: 10000  // 10 seconds
});

client.once('clientReady', async () => {
    console.log(`Logged in as ${client.user.tag}!`);
    registerCommands();
    checkMySQLConnection(pool);
    // startActivityUpdater(client); // Sistem update status otomatis dimatikan
    
});

const commands = [
    new SlashCommandBuilder()
        .setName('showpanel')
        .setDescription('User Control Panel (Owner Only)'),
    new SlashCommandBuilder()
    .setName('setadmin')
    .setDescription('Set a user as admin.')
    .addStringOption(option => 
      option.setName('username')
        .setDescription('The username of the player to set as admin. (Owner Only)')
        .setRequired(true))
    .addIntegerOption(option => 
      option.setName('level')
        .setDescription('Admin level to assign (1 for limited, 6 for full access).')
        .setRequired(true)),
    new SlashCommandBuilder()
	    .setName('players')
	    .setDescription('To see the number of players on IC'),
	new SlashCommandBuilder()
        .setName('changelog')
        .setDescription('Send Info changelog server new. (Owner Only)')
        .addStringOption(option =>
            option.setName('version')
                .setDescription('Versi changelog ( syntx : 0.2.1 Beginning )')
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
                .setName("faction")
                .setDescription("Create Buttons Create Faction"),
    new SlashCommandBuilder()
        .setName('createrdm')
        .setDescription('Create a new redeem code')
        .addStringOption(option => 
            option.setName('code')
                .setDescription('The redeem code')
                .setRequired(true))
        .addStringOption(option => 
            option.setName('type')
                .setDescription('Type of reward (money, gold, vip)')
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
                .setRequired(true))
                .addStringOption(option =>
                    option.setName('judul')
                        .setDescription('Judul pembaruan')
                        .setRequired(true))
        .addStringOption(option =>
                    option.setName('deskripsi')
                        .setDescription('Deskripsi pembaruan')
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
    "anjeng", "allah", "anjg", "anjing", "ass", "asu", "bab1", "babi", "bajingan", "bangsat", "bego", "bego.jing", "begok", 
    "bencong", "bgst", "bitch", "bjir", "blok", "brengsek", "buajingan", "cok", "dancok", "dongo", 
    "dungu", "entod", "entot", "fuck", "goblok", "haram", "idiot", "jablay", "jancok", "jembut", "jeng", 
    "jiancok", "jir", "jmbt", "juancok", "k0nt0l", "konto", "k0ntol", "ktl", "kampang", "kampret", "kanjut", "khontol", 
    "kimak", "kintil", "kintil.kontol", "kirik", "kntl", "konol", "kntol", "kontl", "kontol", "Kontol", "kontols", "kuntul", 
    "kunyuk", "lol", "lonte", "meki", "memek", "memeks", "Memeks", "memeq", "memk", "mmek", 
    "mmk", "ng3n", "Ng3nt0d", "ng3nt0t", "ngen", "ngento", "ngengod","ngent", "ngentd", "ngentod", "Ngentod²", 
    "ngentot", "ngentt", "ngew", "ngewe", "ngewe", "ngntd", "ngntot", "nhentod", "nhentot", "njing", 
    "nyeong", "p0rn", "pantek", "peler", "poorn", "porn", "pornn", "pornrn", "puki", "pukimak", "sange", 
    "sepong", "sepongin", "spong", "t0d", "t0l0l", "t0t", "tai", "taik", "talal", "telaso", "tempik", "tilil", "tll", 
    "tlol", "tod", "tolol", "tot", "tulul", "yatim", "y4tim", "yat1m", "y4t1m", "yteam", "yesus",
];
const bannedWordsRegex = new RegExp(`\\b(${bannedWordsList.join('|')})\\b`, 'i');

const userWarnings = new Map();



async function registerCommands() {
    const rest = new REST({ version: '10' }).setToken(process.env.DISCORD_TOKEN);

    try {
        console.log('Started refreshing application (/) commands.');

        await rest.put(
            Routes.applicationCommands(client.user.id),
            { body: commands },
        );

        console.log('Successfully reloaded application (/) commands.');
    } catch (error) {
        console.error(error);
    }
}

client.on('interactionCreate', async interaction => {
    if (interaction.isCommand()) {
        const { commandName } = interaction;
        if (commandName === 'showpanel') {
            if (!interaction.member.permissions.has('Administrator')) {
            await interaction.reply({
                content: 'You do not have permission to use this command.',
                flags: MessageFlags.Ephemeral
            });
            return;
        }
        
	    const embed = {
	            color: 0x111211,
	            title: "UCP Registration My Sunshine Roleplay",
	            description: 'We have provided an option below to help you:',
	            fields: [
	                { name: '__Register Account Button__', value: `> If you don't have a UCP account or it's your first time joining our server, you can use the button to create an account.` },
					{ name: '__Change Password Account Button__', value: `> If you have problems forgetting your password, you can use the button to create a new password.` },
					{ name: '__Reverify Account Button__', value: `> To send a re-verification code if you don't get the bot verification code in your DM.` },
					{ name: '__Bind Account Button__', value: `> To bind your discord account with a UCP account, it can be used if your discord account is not linked to the UCP account you have, make sure you still remember the PIN code when creating the first UCP account` },
	            ],
	            image: { url: 'https://cdn.discordapp.com/attachments/1500909054153854986/1500914155048144906/Urban-removebg-preview.png?ex=69fad37c&is=69f981fc&hm=76a6bf6fcdc462efa5d33e1d31eef081de4f3fe5dff3ef14d6426d860328ccf8&' },
	            footer: { text: `Copyright (c) 2025 My Sunshine Roleplay (All rights reversed)` },
	            timestamp: new Date(),
	    };

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

        const row = new ActionRowBuilder().addComponents(buttonCreate, buttonChange, buttonReverify, buttonBind);

        await interaction.reply({ embeds: [embed], components: [row] });
        } else if (commandName === 'setadmin') {
            HandleAdminLevel(interaction, pool);
        } else if (commandName === 'createrdm') {
            generateRedeem(interaction, pool);
        } else if (commandName === 'players') {
            // Sistem query dimatikan sementara
            interaction.reply({ content: 'Sistem pengecekan pemain sedang dinonaktifkan sementara.', flags: MessageFlags.Ephemeral });
		// samp(serverInfo, (error, response) => {
        //     if (error) {
        //         console.error('SAMP Query Error:', error);
        //         interaction.reply(`Failed to retrieve player count. Error: \`${error}\``);
        //         return;
        //     }

        //     const playerCount = response.online;
        //     const maxPlayers = response.maxplayers;
        //     const players = response.players;

        //     const serverAddress = `${serverInfo.host}:${serverInfo.port}`;

        //     if (playerCount > 0) {
        //         let playerList = players.map(player => `ID: ${player.id} | ${player.name} (Ping: ${player.ping})`).join('\n');
                
        //         const embed = {
		// 			color: 0x111211,
		// 			title: 'Players on the Current Server',
		// 			description: `**Server:** \`${serverAddress}\` \n\nThere are currently ${playerCount} players online out of a maximum of ${maxPlayers}:\n\n${playerList}`,
		// 			footer: { text: `Copyright (c) 2025 My Sunshine Roleplay (All rights reversed)` },
		//             timestamp: new Date(),
		// 		}
        //         interaction.reply({ embeds: [embed] });
        //     } else {
        //         interaction.reply(`There are currently no players online.`);
        //     } 
        // });
        } else if (commandName === 'changelog') {		
        const version = interaction.options.getString('version');
        const changed = interaction.options.getString('changed').replace(/,/g, '\n'); // Replace commas with newlines
        const fixesImprovement = interaction.options.getString('fixes_improvement').replace(/,/g, '\n'); // Replace commas with newlines
        
        console.log('Original Changed:', changed);
        console.log('Original Fixes:', fixesImprovement);
    
        const changedFormatted = changed.replace(/,/g, '\n');
        const fixesFormatted = fixesImprovement.replace(/,/g, '\n');
    
        console.log('Formatted Changed:', changedFormatted);
        console.log('Formatted Fixes:', fixesFormatted);
	
			const channelUpdate = await client.channels.fetch(process.env.UPDATE_CHANNEL_ID);
			
			const currentDate = new Date();
			const options = { 
			    year: 'numeric', 
			    month: 'long', 
			    day: 'numeric', 
			    hour: 'numeric', 
			    minute: 'numeric', 
			    timeZone: 'Asia/Jakarta',
			    hour12: false
			};
			const formattedDate = currentDate.toLocaleDateString('id-ID', options);
			const finalDate = `${formattedDate} WIB`;
	
			const userAvatar = interaction.user.displayAvatarURL({ dynamic: true, size: 32 });
			
			try {
			   const ownerRole = interaction.guild.roles.cache.find(role => role.name === 'scripter');
			   if (!interaction.member.roles.cache.has(ownerRole.id)) {
			       await interaction.reply({ content: 'You do not have permission to use this command.', flags: MessageFlags.Ephemeral });
			       return;
		     }
	         const changelogEmbed = new EmbedBuilder()
	            .setColor(0x111211)
	            .setTitle(`Changelogs v${version}`)
	            .addFields(
	                { name: '__Changes__', value: changedFormatted },
	                { name: '__Fixes & Improvement__', value: fixesFormatted },
	            )
	            .setFooter({ text: `Update pada ${finalDate}` , iconURL: userAvatar });
	
		    await channelUpdate.send({ embeds: [changelogEmbed] });
	      } catch (error) {
	      console.error(error);
	    }
        } else if (commandName === 'faction') {
            factionModal(interaction); // Show the faction modal
        } else if (commandName === 'serveronline') {
            // Buat embed untuk server online
            const serverAddress = `${serverInfo.host}:${serverInfo.port}`;
            
            const embed = new EmbedBuilder()
                .setTitle('My Sunshine Roleplay')
                .setDescription('Server is now **Online!**')
                .setColor(0x111211)
                .addFields(
                    { name: 'Host:', value: serverAddress, inline: true }, 
                    { name: 'Version:', value: '0.1.20n/0.3DL', inline: true }
                )
                .setImage(IMAGE_ON);
    
            // Kirim embed ke channel tempat command dipanggil
            await interaction.reply({ content: '@everyone', embeds: [embed] });
            console.log('Pesan server online telah dikirim.');
        } else if (commandName === 'serveroffline') {
            // Buat embed untuk server offline
            const serverAddress = `${serverInfo.host}:${serverInfo.port}`;
    
            const embed = new EmbedBuilder()
                .setTitle('My Sunshine Roleplay')
                .setDescription('Server is now **Offline!**')
                .setColor(0x111211)
                .addFields(
                    { name: 'Host:', value: serverAddress, inline: true }, 
                    { name: 'Version:', value: '0.1.20n/0.3DL', inline: true }
                )
                .setImage(IMAGE_OFF);
    
            // Kirim embed ke channel tempat command dipanggil
            await interaction.reply({ content: '@everyone', embeds: [embed] });
            console.log('Pesan server offline telah dikirim.');
        } else if (commandName === 'serverrestart') {
            // Buat embed untuk server restart
            const serverAddress = `${serverInfo.host}:${serverInfo.port}`;
    
            const embed = new EmbedBuilder()
                .setTitle('My Sunshine Roleplay')
                .setDescription('Server is now **Restarting!**')
                .setColor(0x111211)
                .addFields(
                    { name: 'Host:', value: serverAddress, inline: true }, 
                    { name: 'Version:', value: '0.1.20n/0.3DL', inline: true }
                )
                .setImage(IMAGE_RESTART);
    
            // Kirim embed ke channel tempat command dipanggil
            await interaction.reply({ content: '@everyone', embeds: [embed] });
            console.log('Pesan server restart telah dikirim.');
        }
    } else if (interaction.isButton()) { // Handle button interactions
        if (interaction.customId === 'create_account') { // This is a duplicate button handler
            ButtonCreateAccount(interaction, pool);
        } else if (interaction.customId === 'change_password') {
            ButtonChangePassword(interaction, pool);
        } else if (interaction.customId === 'reverify') {
            handleReverify(interaction, pool);
        } else if (interaction.customId === 'bind_account') {
            ButtonBindAccount(interaction, pool);
        }
    } else if (interaction.isModalSubmit()) {
        if (interaction.customId === 'create_account_modal') {
            handleCreateAccount(interaction, pool);
        } else if (interaction.customId === 'change_password_modal') {
            handleChangePassword(interaction, pool);
        } else if (interaction.customId === 'bind_account_modal') {
            handleBindAccount(interaction, pool);
        } else if (interaction.customId === 'reverify') {
            await handleReverify(interaction, pool);
        } else if (interaction.customId === 'bind_account') {
            await ButtonBindAccount(interaction, pool);
        }
        // Handle additional button actions as necessary
    } else if (interaction.isStringSelectMenu()) {
        try {
            await interaction.deferUpdate(); // Acknowledge the interaction to avoid timeout

            if (interaction.customId === 'list-faction') {
                let message;
                switch (interaction.values[0]) {
                    case 'police-menu':
                        message = "**__POLICE DEPARTMENT DISCORD__**\n\nhttps://discord.gg/DJmBPctTZJ";
                        break;
                    case 'fire-menu':
                        message = "_FIRE DEPARTMENT DISCORD_\n\nhttps://discord.gg/dDQdszE4GW";
                        break;
                    case 'news-menu':
                        message = "_NEWS AGENCY DISCORD_\n\nhttps://discord.gg/9HVjJ8fR8e";
                        break;
                    case 'sags-menu':
                        message = "_GOVERMENT SERVICE DISCORD_\n\nhttps://discord.gg/hS4nKZRpj7";
                        break;
                    case 'family-menu':
                        message = "**__FAMILIES AND GANG__**\n\nhttps://discord.gg/npDwAp8MEt";
                        break;
                    default:
                        message = "Invalid selection."; // Fallback message
                }

                await interaction.followUp({ content: message, flags: MessageFlags.Ephemeral }); // Send the message as a follow-up
            }
        } catch (error) {
            console.error("Error handling interaction:", error);
            await interaction.reply({ content: ':x: An error occurred while processing your request.', flags: MessageFlags.Ephemeral });
        }
    }
});



client.on('messageCreate', async (message) => {
    try {
        // Ignore messages from the bot itself
        if (message.author.bot) return;

        // Pengecualian untuk channel tertentu
        const excludedChannelId = '1227244555447963669'; // Ganti dengan ID channel yang dikecualikan
        if (message.channel.id === excludedChannelId) return;

        // Log server and channel information
        console.log(`Received message in server ID: ${message.guild.id}, channel ID: ${message.channel.id}`);
        console.log(`Received message: ${message.content}`); // Log received message

        // Check if the message contains the word "ip" (case insensitive)
        if (message.content.toLowerCase().includes('ip')) {
            const replyMessage = `The server's IP address is: \`${serverInfo.host}:${serverInfo.port}\``;
            
            console.log(`Replying with: ${replyMessage}`); // Log reply message
            await message.reply(replyMessage);
        }
        if (message.content.toLowerCase().includes('ucp')) {
            const replyMessage = `Go to https://discordapp.com/channels/1487812118207135854/1487812119234871418 to create your account`;
            
            console.log(`Replying with: ${replyMessage}`); // Log reply message
            await message.reply(replyMessage);
        }
    } catch (error) {
        console.error('Error handling message:', error);
    }
});




client.on('messageCreate', async (message) => {
  if (message.author.bot) return;

if (bannedWordsRegex.test(message.content.toLowerCase())) {
    try {
        await message.delete(); // Delete the inappropriate message

        let warnings = userWarnings.get(message.author.id) || 0;
        warnings++;

        userWarnings.set(message.author.id, warnings);

        // Send a warning message in the channel, but only to the author
        const warningMessage = await message.channel.send(`${message.author}, pesan kamu mengandung konten yang tidak pantas dan telah dihapus. Ini adalah peringatan ke-${warnings}/3.`);

        // Delete the warning message after 3 seconds
        setTimeout(() => {
            warningMessage.delete().catch(err => console.error('Gagal menghapus pesan peringatan:', err));
        }, 3000);

        if (warnings >= 3) {
            await message.member.timeout(10 * 60 * 1000, 'Penggunaan bahasa tidak pantas berulang kali'); // Timeout 10 menit
            await message.channel.send(`${message.author} telah diberi timeout selama 10 menit karena berulang kali menggunakan bahasa yang tidak pantas.`);
            userWarnings.set(message.author.id, 0);
        }

    } catch (err) {
        console.error('Gagal menghapus pesan atau memberikan timeout:', err);
    }
}
});

client.login(process.env.DISCORD_TOKEN);
