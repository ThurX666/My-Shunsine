const { EmbedBuilder } = require('discord.js');
const samp = require('samp-query');

let serverIsOnline = null;
let lastMessageId = null;
let lastUpdateTimestamp = 0;
const updateCooldown = 10 * 1000;

const { serverInfo } = require('./../Mysql/address');

function queryServer() {
    return new Promise((resolve, reject) => {
        samp(serverInfo, (error, response) => {
            if (error) return reject(error);
            resolve(response);
        });
    });
}

function showMonitoringEmbed(serverData) {
    const embed = new EmbedBuilder()
        .setColor('#111211')
        .setTitle('My Sunshine Monitor Server')
        .addFields(
	        { name: '🖥️ Hostname', value: serverData.hostname },
            { name: '🌐 Gamemode', value: serverData.gamemode },
            { name: '🗾 Map Name', value: serverData.mapname },
            { name: '👥 Players', value: `${serverData.online}/${serverData.maxplayers}` },
            { name: '📶 Ping', value: `${serverData.ping || 'N/A' } ms` }
        )
        .setImage('https://cdn.discordapp.com/attachments/1424686652156018720/1440401224376782928/CRIMSON_COAST.png?ex=691e05ad&is=691cb42d&hm=c24c3dad0a1b283a2336f409163db54b7bd573ac832c23c440c2c3ebf6bdfbb1&');

    return embed;
}

function showMonitoringOfflineEmbed() {
    const embed = new EmbedBuilder()
        .setColor('#111211')
        .setTitle('Server Offline')
        .setDescription('There is a problem with the server under maintenance, please wait a while.')
        .setFooter({ text: `Copyright (c) 2025 My Sunshine Roleplay (All rights reversed)` })
        .setTimestamp();

    return embed;
}

async function updateServerStatus(channel) {
	
	const currentTime = Date.now();

    if (currentTime - lastUpdateTimestamp < updateCooldown) {
        return;
    }
    
    try {
        const serverData = await queryServer();

        if (serverIsOnline === false) {
            console.log('Server is back online!');
            serverIsOnline = true;

			if (lastMessageId) {
		            try {
		                const lastMessage = await channel.messages.fetch(lastMessageId);
		                await lastMessage.delete();
		            } catch (error) {
		                console.error('Error deleting the last message:', error);
		            } 
	        }
            /*const messages = await channel.messages.fetch({ limit: 1 });
            if (messages.size > 0) {
                await channel.bulkDelete(messages);
            }*/

            const embed = showMonitoringEmbed(serverData);
            const sentMessage = await channel.send({ embeds: [embed] });
            lastMessageId = sentMessage.id;
            lastUpdateTimestamp = currentTime;
        } else if (serverIsOnline === null || serverIsOnline === true) {

			if (lastMessageId) {
		            try {
		                const lastMessage = await channel.messages.fetch(lastMessageId);
		                await lastMessage.delete();
		            } catch (error) {
		                console.error('Error deleting the last message:', error);
		            }
	        }
           /* const messages = await channel.messages.fetch({ limit: 1 });
            if (messages.size > 0) {
                await channel.bulkDelete(messages);
            }*/

            const embed = showMonitoringEmbed(serverData);
            const sentMessage = await channel.send({ embeds: [embed] });
            lastMessageId = sentMessage.id;
            lastUpdateTimestamp = currentTime;
            serverIsOnline = true;
        }
    } catch (error) {
        console.error('Server is offline or could not be reached:', error);

        if (serverIsOnline === true || serverIsOnline === null) {
            console.log('Server is offline.');
            serverIsOnline = false;
            
	        if (lastMessageId) {
		            try {
		                const lastMessage = await channel.messages.fetch(lastMessageId);
		                await lastMessage.delete();
		            } catch (error) {
		                console.error('Error deleting the last message:', error);
		            }
	        }
            /*const messages = await channel.messages.fetch({ limit: 1 });
            if (messages.size > 0) {
                await channel.bulkDelete(messages);
            } */
            
            const embed = showMonitoringOfflineEmbed();
            const sentMessage = await channel.send({ embeds: [embed] });
            lastMessageId = sentMessage.id;
            lastUpdateTimestamp = currentTime;
        }
    }
    setTimeout(() => updateServerStatus(channel), 4000);
}

module.exports = { showMonitoringEmbed, showMonitoringOfflineEmbed, updateServerStatus };