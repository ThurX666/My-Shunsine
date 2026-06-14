const crypto= require("crypto");
const { MessageFlags } = require('discord.js');

async function handleChangePassword(interaction, pool) {
    const password = interaction.fields.getTextInputValue('password_input');
    const confirmPassword = interaction.fields.getTextInputValue('confirm_password_input');

    if (password !== confirmPassword) {
        await interaction.reply({ content: ':x: Passwords do not match. Please try again.', flags: MessageFlags.Ephemeral });
        return;
    }

    try {
        const salt = Array.from({length: 16}, () => String.fromCharCode(Math.floor(Math.random() * 94) + 33)).join('');
        const hashedNewPassword = crypto.createHash('sha256').update(password + salt).digest('hex').toUpperCase();
        await pool.query(`UPDATE ucp SET password = ?, salt = ? WHERE DiscordID = ?`, [hashedNewPassword, salt, interaction.user.id]);

        await interaction.reply({ content: ':white_check_mark: Password changed successfully!', flags: MessageFlags.Ephemeral });
    } catch (error) {
        console.error(error);
        await interaction.reply({ content: ':x: Failed to change password. Please try again later.', flags: MessageFlags.Ephemeral });
    }
}

module.exports = { handleChangePassword };
