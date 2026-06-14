const { MessageFlags } = require('discord.js');

async function HandleAdminLevel(interaction, pool) {
	
    const username = interaction.options.getString('username');
    const level = interaction.options.getInteger('level');
    
    try {
	   const ownerRole = interaction.guild.roles.cache.find(role => role.name === 'scripter');
	   if (!interaction.member.roles.cache.has(ownerRole.id)) {
	       await interaction.reply({ content: 'You do not have permission to use this command.', flags: MessageFlags.Ephemeral });
	       return;
	   }
      const [rows] = await pool.execute('SELECT * FROM ucp WHERE username = ?', [username]);

      if (rows.length === 0) {
        return interaction.reply({ content: `Invalid: Username "${username}" not found in the database.`, flags: MessageFlags.Ephemeral });
      }
      await pool.execute('UPDATE ucp SET admin = ? WHERE username = ?', [level, username]);
      return interaction.reply({ content: `:white_check_mark: Username IC ${username} has been granted admin level ${level}.` });
    } catch (error) {
      console.error(error);
      return interaction.reply({ content: 'There was an error setting the admin level. Please try again later.', flags: MessageFlags.Ephemeral });
    }
}

module.exports = { HandleAdminLevel };