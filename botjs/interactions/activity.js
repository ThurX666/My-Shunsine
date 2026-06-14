const sampQuery = require('samp-query');
const { ActivityType } = require('discord.js');
const { serverInfo } = require('./../Mysql/address');

let currentActivity = 0;
let clientInstance = null;

function queryPlayerCount() {
    return new Promise((resolve) => {
        sampQuery(serverInfo, (error, response) => {
            if (error) {
                console.error('Error querying server:', error);
                return resolve('❌ Failed to fetch'); 
            }
            const playerCount = `${response.online} players!`;
            resolve(playerCount);
        });
    });
}

async function updateActivity() {
    try {
        if (currentActivity === 0) {
            clientInstance.user.setActivity('My Sunshine Roleplay', { type: ActivityType.Playing });
        } else {
            const playerCount = await queryPlayerCount();
            clientInstance.user.setActivity(playerCount, { type: ActivityType.Listening });
        }

        currentActivity = (currentActivity + 1) % 2; // Beralih antara 0 dan 1

        setTimeout(updateActivity, 10000); // Ganti aktivitas setiap 10 detik
    } catch (error) {
        console.error('Error updating activity:', error);
    }
}

function startActivityUpdater(client) {
    clientInstance = client;
    updateActivity();
}

module.exports = {
    startActivityUpdater,
};
