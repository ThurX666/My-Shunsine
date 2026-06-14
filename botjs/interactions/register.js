const crypto= require("crypto");
const { EmbedBuilder, MessageFlags } = require('discord.js');

async function handleCreateAccount(interaction, pool) {
    const username = interaction.fields.getTextInputValue('username_input');
    const password = interaction.fields.getTextInputValue('password_input');
    const confirmPassword = interaction.fields.getTextInputValue('confirm_password_input');

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

        const [existingUser] = await pool.query('SELECT * FROM ucp WHERE username = ?', [username]);
        if (existingUser.length > 0) {
            return interaction.editReply({ content: ':x: username name is already in use!' });
        }

        // Debug: Log the DiscordID being queried
        const discordId = String(interaction.user.id);
        console.log(`Checking for existing account with DiscordID: ${discordId}`);
        
        const [existingAccount] = await pool.query('SELECT * FROM ucp WHERE DiscordID = ?', [discordId]);
        console.log(`Query result: Found ${existingAccount.length} account(s)`);
        if (existingAccount.length > 0) {
            console.log(`Existing account data: ${JSON.stringify(existingAccount[0])}`);
            const username = existingAccount[0].username || 'Unknown';
            return interaction.editReply({ content: `:x: You have already created an account with the username: ${username}` });
        }

        const salt = Array.from({length: 16}, () => String.fromCharCode(Math.floor(Math.random() * 94) + 33)).join('');
        const hashedPassword = crypto.createHash('sha256').update(password + salt).digest('hex').toUpperCase();
        const verifycode = Math.floor(Math.random() * 1000000);

        await pool.query('INSERT INTO ucp (username, password, salt, pin, DiscordID) VALUES (?, ?, ?, ?, ?)', [username, hashedPassword, salt, verifycode, interaction.user.id]);

		const embed = new EmbedBuilder()
			.setTitle('Your registration is successful!')
			.setDescription(`Your username name is: ${username}\nYour verification code is: ${verifycode}`)
			.setColor('#111211')
			.setImage('https://cdn.discordapp.com/attachments/1500909054153854986/1500914155048144906/Urban-removebg-preview.png?ex=69fad37c&is=69f981fc&hm=76a6bf6fcdc462efa5d33e1d31eef081de4f3fe5dff3ef14d6426d860328ccf8')
			.setFooter({ text: 'Copyright (c) 2025 My Sunshine Roleplay (All rights reversed)'})
			.setTimestamp();
			
        const member = interaction.member;
        if (member) {
            await member.roles.add('1487812118207135859').catch(err => console.error("Gagal menambah role:", err));
            await member.setNickname(username).catch(err => console.error("Gagal mengganti nickname:", err));
        }

        await interaction.user.send({
	         content: `Hello <@${interaction.user.id}>`, embeds: [embed] 
		});

        await interaction.editReply({ content: ':white_check_mark: Account created successfully! Please check your DM for the verification code.' });
    } catch (error) {
        console.error(error);
        await interaction.editReply({ content: ':x: An error occurred while creating the account. Please try again later.' });
    }
}

module.exports = { handleCreateAccount };
