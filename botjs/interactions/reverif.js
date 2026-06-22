const { EmbedBuilder, MessageFlags } = require('discord.js');

async function handleReverify(interaction, pool, config) {
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
			.setImage(config.images.register)
			.setFooter({ text: 'Copyright (c) 2025 My Sunshine Roleplay (All rights reversed)' })
			.setTimestamp();
		
        const member = interaction.member;
        const memberRole = config.discord.memberRoleId;
        if (member && memberRole && !member.roles.cache.has(memberRole)) {
            await member.roles.add(memberRole).catch(err => console.error("Gagal menambah role:", err));
        }

        if (member) await member.setNickname(username).catch(err => console.error("Gagal mengganti nickname:", err));

        try {
            await interaction.user.send({
                content: `Hello <@${interaction.user.id}>`, embeds: [embed]
            });
        } catch (dmError) {
            console.error('Failed to send reverify DM:', dmError);
            await interaction.reply({ content: ':warning: Account found, but I could not send the verification code via DM. Please enable direct messages and try again.', flags: MessageFlags.Ephemeral });
            return;
        }

        await interaction.reply({ content: ':white_check_mark: Verification code resent. Please check your DM.', flags: MessageFlags.Ephemeral });
    } catch (error) {
        console.error(error);
        if (!interaction.replied && !interaction.deferred) {
            await interaction.reply({ content: ':x: Failed to re-send verification code. Please try again later.', flags: MessageFlags.Ephemeral });
        }
    }
}

module.exports = { handleReverify };
