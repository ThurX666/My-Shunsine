const crypto= require("crypto");
const { EmbedBuilder, MessageFlags } = require('discord.js');

async function handleCreateAccount(interaction, pool, config) {
    const username = interaction.fields.getTextInputValue('username_input').trim();
    const password = interaction.fields.getTextInputValue('password_input');
    const confirmPassword = interaction.fields.getTextInputValue('confirm_password_input');

    if (!/^[A-Za-z]{3,24}$/.test(username)) {
        return interaction.reply({
            content: ':x: Username must contain only letters and be 3-24 characters long.',
            flags: MessageFlags.Ephemeral
        });
    }

    if (/_/.test(username)) {
        return interaction.reply({ content: ':x: username name cannot contain underscores (_)!', flags: MessageFlags.Ephemeral });
    }
    if (/\d/.test(username)) {
        return interaction.reply({ content: ':x: username name must not contain any numbers!', flags: MessageFlags.Ephemeral });
    }

    if (password !== confirmPassword) {
        await interaction.reply({ content: ':x: Passwords do not match. Please try again.', flags: MessageFlags.Ephemeral });
        return;
    }

    try {
        await interaction.deferReply({ flags: MessageFlags.Ephemeral });

        const [existingUser] = await pool.query('SELECT username FROM ucp WHERE username = ?', [username]);
        if (existingUser.length > 0) {
            return interaction.editReply({ content: ':x: username name is already in use!' });
        }

        const discordId = String(interaction.user.id);
        const [existingAccount] = await pool.query('SELECT username FROM ucp WHERE DiscordID = ?', [discordId]);
        if (existingAccount.length > 0) {
            const username = existingAccount[0].username || 'Unknown';
            return interaction.editReply({ content: `:x: You have already created an account with the username: ${username}` });
        }

        const salt = Array.from({length: 16}, () => String.fromCharCode(Math.floor(Math.random() * 94) + 33)).join('');
        const hashedPassword = crypto.createHash('sha256').update(password + salt).digest('hex').toUpperCase();
        const verifycode = Math.floor(100000 + Math.random() * 900000);

        await pool.query('INSERT INTO ucp (username, password, salt, pin, DiscordID) VALUES (?, ?, ?, ?, ?)', [username, hashedPassword, salt, verifycode, interaction.user.id]);

		const embed = new EmbedBuilder()
			.setTitle('Your registration is successful!')
			.setDescription(`Your username name is: ${username}\nYour verification code is: ${verifycode}`)
			.setColor('#111211')
			.setImage(config.images.register)
			.setFooter({ text: 'Copyright (c) 2025 My Sunshine Roleplay (All rights reversed)'})
			.setTimestamp();
			
        const member = interaction.member;
        if (member && config.discord.memberRoleId) {
            await member.roles.add(config.discord.memberRoleId).catch(err => console.error("Gagal menambah role:", err));
        }

        if (member) {
            await member.setNickname(username).catch(err => console.error("Gagal mengganti nickname:", err));
        }

        try {
            await interaction.user.send({
	             content: `Hello <@${interaction.user.id}>`, embeds: [embed]
			});
        } catch (dmError) {
            console.error('Failed to send registration DM:', dmError);
            await interaction.editReply({ content: ':warning: Account created, but I could not send the verification code via DM. Please enable direct messages and use the Reverify button.' });
            return;
        }

        await interaction.editReply({ content: ':white_check_mark: Account created successfully! Please check your DM for the verification code.' });
    } catch (error) {
        console.error(error);
        if (interaction.deferred || interaction.replied) {
            await interaction.editReply({ content: ':x: An error occurred while creating the account. Please try again later.' });
        } else {
            await interaction.reply({ content: ':x: An error occurred while creating the account. Please try again later.', flags: MessageFlags.Ephemeral });
        }
    }
}

module.exports = { handleCreateAccount };
