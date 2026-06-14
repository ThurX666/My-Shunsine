const { MessageFlags } = require('discord.js');

async function handleBindAccount(interaction, pool) {
    
    const ucpName = interaction.fields.getTextInputValue('ucp_name_input');
    const otp = interaction.fields.getTextInputValue('otp_input');
    const { user } = interaction;

    try {
      const [rows] = await pool.execute('SELECT * FROM ucp WHERE username = ? AND pin = ?', [ucpName, otp]);
      if (rows.length === 0) {
        return interaction.reply({ content: ':x: Invalid UCP name or OTP/PIN!', flags: MessageFlags.Ephemeral });
      }
  
      const [linkedRows] = await pool.execute('SELECT * FROM ucp WHERE DiscordID = ?', [user.id]);
      if (linkedRows.length > 0) {
        return interaction.reply({ content: ':x: Your Discord account is already linked to another UCP account. Please use the Reverif button if you need to re-verify.', flags: MessageFlags.Ephemeral });
      }
      
      await pool.execute('UPDATE ucp SET DiscordID = ? WHERE username = ?', [user.id, ucpName]);
      interaction.reply({ content: ':white_check_mark: UCP account successfully bound to your Discord account!', flags: MessageFlags.Ephemeral });
    } catch (error) {
      console.error(error);
      interaction.reply({ content: ':x: There was an error binding your UCP account.', flags: MessageFlags.Ephemeral });
    }
}

module.exports = { handleBindAccount };
