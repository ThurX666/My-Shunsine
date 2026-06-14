const { Client, GatewayIntentBits, EmbedBuilder } = require('discord.js');
const client = new Client({ intents: [GatewayIntentBits.Guilds, GatewayIntentBits.GuildMessages, GatewayIntentBits.MessageContent, GatewayIntentBits.DirectMessages] });

async function HandlerPatchUpdateNotes(interaction) {
	
    const version = interaction.options.getString('version');
    const changed = interaction.options.getString('changed').replace(/,/g, '\n'); // Replace commas with newlines
    const fixesImprovement = interaction.options.getString('fixes_improvement').replace(/,/g, '\n'); // Replace commas with newlines
	
	console.log('Original Changed:', changed);
	console.log('Original Fixes:', fixesImprovement);

	const changedFormatted = changed.replace(/,/g, '\n');
	const fixesFormatted = fixesImprovement.replace(/,/g, '\n');

	console.log('Formatted Changed:', changedFormatted);
	console.log('Formatted Fixes:', fixesFormatted);



	//const channelUpdate = await client.channels.fetch(process.env.UPDATE_CHANNEL_ID);
	const updateChannelId = '1227299980511809719';
	
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
	       await interaction.reply({ content: 'You do not have permission to use this command.', ephemeral: true });
	       return;
	    }
       const changelogEmbed = new EmbedBuilder()
          .setColor(0x111211)
          .setTitle(`Changelogs v${version}`)
          .addFields(
              { name: '__Changes__', value: changedFormatted },
              { name: '__Fixes & Improvement__', value: fixesFormatted },
          )
          .setFooter({ text: `__*Update pada ${finalDate}*__` , iconURL: `https://media.discordapp.net/attachments/1424686652156018720/1424687138225782806/78ea7d2e-dc35-4b95-89cb-2d1bf716212f.png?ex=68fde74b&is=68fc95cb&hm=ccc1350a14b52fe294cf2c853c0785cad0df88bdf7edb88a89d6121c0893d720&=&format=webp&quality=lossless?ex=67093360&is=6707e1e0&hm=b636a5adaad6b2de606abb199d2f40245035e1fa4a28caae10fff7f074efd236&` });

	const channelPatchUpdate = client.channels.cache.get(updateChannelId);
	
	if (channelPatchUpdate) {
	    await channelPatchUpdate.send({ embeds: [changelogEmbed] });
	    await interaction.reply({ content: 'The update has been successfully sent to <#1344143971135262823>' });
    } else {
	    console.error('Channel id tidak di temukan');
    }
  } catch (error) {
    console.error(error);
    return interaction.reply({ content: 'An error occurred while interacting.', ephemeral: true });
  }
}

module.exports = { HandlerPatchUpdateNotes };
