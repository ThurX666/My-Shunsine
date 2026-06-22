const { exec } = require('child_process');
const fs = require('fs');
const path = require('path');
const { EmbedBuilder } = require('discord.js');

async function backupDatabase(pool, client, channelId) {
  const backupFile = path.join(__dirname, `../../backup-${Date.now()}.sql`);
  const command = `mysqldump -u ${process.env.DB_USER} -p${process.env.DB_PASSWORD} ${process.env.DB_NAME} > ${backupFile}`;
  
  exec(command, (error, stdout, stderr) => {
    if (error) {
      console.error(`Error during database backup: ${error.message}`);
      return;
    }

    if (stderr) {
      console.error(`Stderr during database backup: ${stderr}`);
      return;
    }

    console.log(`Database backup created successfully: ${backupFile}`);
    const channel = client?.channels?.cache?.get(channelId);

    if (channel) {
      const embed = new EmbedBuilder()
        .setTitle('Database Backup')
        .setDescription('The database backup was created successfully.')
        .setColor('#111211')
        .setTimestamp();

      channel.send({ embeds: [embed], files: [backupFile] })
        .then(() => {
          // hapus file cadangan setelah dikirim
          fs.unlinkSync(backupFile);
          console.log(`Backup file deleted: ${backupFile}`);
        })
        .catch(error => {
          console.error(`Failed to send backup file: ${error.message}`);
        });
    } else {
      console.error('Channel not found');
    }
  });
}

module.exports = { backupDatabase };
