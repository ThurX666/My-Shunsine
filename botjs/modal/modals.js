const { ModalBuilder, TextInputBuilder, TextInputStyle, ActionRowBuilder, EmbedBuilder, StringSelectMenuBuilder, StringSelectMenuOptionBuilder, MessageFlags } = require('discord.js');

// Show Create Account Modal
function showCreateAccountModal(interaction) {
    const modal = new ModalBuilder()
        .setCustomId('create_account_modal')
        .setTitle('My Sunshine UCP Registration');

    const ucpInput = new TextInputBuilder()
        .setCustomId('username_input')
        .setLabel('UCP Name')
        .setPlaceholder('Input Valid UCP Name')
        .setMaxLength(15)
        .setStyle(TextInputStyle.Short)
        .setRequired(true);

    const passwordInput = new TextInputBuilder()
        .setCustomId('password_input')
        .setLabel('Password')
        .setPlaceholder('Input Valid UCP Password')
        .setStyle(TextInputStyle.Short)
        .setMaxLength(24)
        .setMinLength(8)
        .setRequired(true);

    const confirmPasswordInput = new TextInputBuilder()
        .setCustomId('confirm_password_input')
        .setLabel('Confirm Password')
        .setPlaceholder('Re-Input Valid UCP Password')
        .setStyle(TextInputStyle.Short)
        .setMaxLength(24)
        .setMinLength(8)
        .setRequired(true);

    modal.addComponents(
        new ActionRowBuilder().addComponents(ucpInput),
        new ActionRowBuilder().addComponents(passwordInput),
        new ActionRowBuilder().addComponents(confirmPasswordInput)
    );

    interaction.showModal(modal);  // Show the modal
}

// Show Change Password Modal
async function showChangePasswordModal(interaction, pool) {
    const [rows] = await pool.query('SELECT * FROM ucp WHERE DiscordID = ?', [interaction.user.id]);
    
    const modal = new ModalBuilder()
        .setCustomId('change_password_modal')
        .setTitle(`Change Password! UCP: ${rows[0].username}`);

    const passwordInput = new TextInputBuilder()
        .setCustomId('password_input')
        .setLabel('New Password')
        .setPlaceholder('Input Valid UCP Password')
        .setStyle(TextInputStyle.Short)
        .setMaxLength(24)
        .setMinLength(8)
        .setRequired(true);

    const confirmPasswordInput = new TextInputBuilder()
        .setCustomId('confirm_password_input')
        .setLabel('New Password Confirmation')
        .setPlaceholder('Re-Input Valid UCP Password')
        .setStyle(TextInputStyle.Short)
        .setMaxLength(24)
        .setMinLength(8)
        .setRequired(true);

    modal.addComponents(
        new ActionRowBuilder().addComponents(passwordInput),
        new ActionRowBuilder().addComponents(confirmPasswordInput)
    );

    interaction.showModal(modal);  // Show the modal
}

// Show Faction Modal
function factionModal(interaction) {
    const embed = new EmbedBuilder()
        .setTitle("Families & Gang Discord")
        .setDescription("\n_\nini adalah official discord faction My Sunshine Roleplay, Silahkan join ke discord server faction untuk mengetahui informasi terbaru tentang faction.\n_\n")
        .setImage("https://cdn.discordapp.com/attachments/1500909054153854986/1500914155828281575/standard_1.gif?ex=69fad37c&is=69f981fc&hm=87762101203843b61b3c581110cf62a126107fb9d4efff05d03f3e9b383f9270&")
        .setFooter({ text: "My Sunshine Assistent" })
        .setTimestamp();

    const select = new StringSelectMenuBuilder()
        .setCustomId('list-faction')
        .setPlaceholder('📌 Select Menu!')
        .addOptions(
            new StringSelectMenuOptionBuilder()
                .setLabel('Police Departement')
                .setDescription('Pilih menu ini untuk join discord SAPD')
                .setEmoji('1247325523479363685')
                .setValue('police-menu'),
            
            new StringSelectMenuOptionBuilder()
                .setLabel('Medic Departement')
                .setDescription('Pilih menu ini untuk melihat SAMD')
                .setEmoji('1247325653406060705')
                .setValue('Medic-menu'),

            new StringSelectMenuOptionBuilder()
                .setLabel('News Agency')
                .setDescription('Pilih menu ini untuk melihat SANA')
                .setEmoji('1247325682271522918')
                .setValue('news-menu'),

            new StringSelectMenuOptionBuilder()
                .setLabel('Goverment Service')
                .setDescription('Pilih menu ini untuk melihat SAGS')
                .setEmoji('1180862345266868295')
                .setValue('sags-menu'),

            new StringSelectMenuOptionBuilder()
                .setLabel('Family And Gang')
                .setDescription('Pilih menu ini untuk melihat FnG')
                .setEmoji('1247325708024418334')
                .setValue('family-menu')
        );

    const row = new ActionRowBuilder().addComponents(select);
    
    interaction.reply({ embeds: [embed], components: [row] }); // Reply with embed and select menu
}


// Show Bind Account Modal
function showBindAccountModal(interaction) {
    const modal = new ModalBuilder()
        .setCustomId('bind_account_modal')
        .setTitle('Bind UCP Account');

    const ucpNameInput = new TextInputBuilder()
        .setCustomId('ucp_name_input')
        .setLabel('UCP Name')
        .setPlaceholder('Input Valid UCP Name')
        .setStyle(TextInputStyle.Short)
        .setRequired(true);

    const otpInput = new TextInputBuilder()
        .setCustomId('otp_input')
        .setLabel('OTP/PIN')
        .setPlaceholder('Input Valid OTP/PIN UCP')
        .setStyle(TextInputStyle.Short)
        .setRequired(true);

    modal.addComponents(
        new ActionRowBuilder().addComponents(ucpNameInput),
        new ActionRowBuilder().addComponents(otpInput)
    );

    interaction.showModal(modal);  // Show the modal
}

// Button Handlers
async function ButtonBindAccount(interaction, pool) {
    try {
        const [rows] = await pool.query('SELECT * FROM ucp WHERE DiscordID = ?', [interaction.user.id]);
        if (rows.length > 0) {
            return interaction.reply({ content: ':x: This UCP account is already bound to another Discord account! Please press the button below to reverify your account.', flags: MessageFlags.Ephemeral });
        } else {
            showBindAccountModal(interaction);
        }
    } catch (error) {
        console.error(error);
        interaction.reply({ content: ':x: There was an error binding your UCP account.', flags: MessageFlags.Ephemeral });
    }
}

async function ButtonCreateAccount(interaction, pool) {
    try {
        const [existingAccount] = await pool.query('SELECT * FROM ucp WHERE DiscordID = ?', [interaction.user.id]);
        if (existingAccount.length > 0) {
            const username = existingAccount[0].username || 'Unknown';
            return interaction.reply({ content: `:x: You have already created an account with the username: ${username}`, flags: MessageFlags.Ephemeral });
        } else {
            showCreateAccountModal(interaction);
        }
    } catch (error) {
        console.error(error);
        await interaction.reply({ content: ':x: An error occurred while creating the account. Please try again later.', flags: MessageFlags.Ephemeral });
    }
}

async function ButtonChangePassword(interaction, pool) {
    try {
        const [rows] = await pool.query('SELECT username FROM ucp WHERE DiscordID = ?', [interaction.user.id]);
        if (rows.length === 0) {
            await interaction.reply({ content: ':x: No UCP account found for your Discord ID.', flags: MessageFlags.Ephemeral });
        } else {
            showChangePasswordModal(interaction, pool);
        }
    } catch (error) {
        console.error(error);
        await interaction.reply({ content: ':x: Failed to change password. Please try again later.', flags: MessageFlags.Ephemeral });
    }
}

// Exporting Functions
module.exports = { 
    showCreateAccountModal, 
    showChangePasswordModal, 
    showBindAccountModal, 
    ButtonBindAccount, 
    ButtonCreateAccount, 
    ButtonChangePassword, 
    factionModal 
};
