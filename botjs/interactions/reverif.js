const { EmbedBuilder, MessageFlags } = require('discord.js');

async function handleReverify(interaction, pool) {
    try {
        const [rows] = await pool.query('SELECT username, pin FROM ucp WHERE DiscordID = ?', [interaction.user.id]);

        if (rows.length === 0) {
            await interaction.reply({ content: ':x: No UCP account found for your Discord ID.', flags: MessageFlags.Ephemeral });
            return;
        }

        const { username, pin } = rows[0];
        
        const embed = new EmbedBuilder()
	        .setTitle('Re-verification code successful!')
			.setDescription(`Your UCP name is: ${username}\nYour verification code is: ${pin}`)
			.setColor('#111211')
			.setImage('https://cdn.discordapp.com/attachments/1500909054153854986/1500914155048144906/Urban-removebg-preview.png?ex=69fad37c&is=69f981fc&hm=76a6bf6fcdc462efa5d33e1d31eef081de4f3fe5dff3ef14d6426d860328ccf8')
			.setFooter({ text: 'Copyright (c) 2025 My Sunshine Roleplay (All rights reversed)' })
			.setTimestamp();
		
        const member = interaction.member;
        const memberRole = '1487812118207135859';
        if (member && !member.roles.cache.has(memberRole)) {
            await member.roles.add(memberRole).catch(err => console.error("Gagal menambah role:", err));
        }

        if (member) await member.setNickname(username).catch(err => console.error("Gagal mengganti nickname:", err));

        await interaction.user.send({
            content: `Hello <@${interaction.user.id}>`, embeds: [embed]
        });

        await interaction.reply({ content: ':white_check_mark: Verification code resent. Please check your DM.', flags: MessageFlags.Ephemeral });
    } catch (error) {
        console.error(error);
    }
}

module.exports = { handleReverify };
