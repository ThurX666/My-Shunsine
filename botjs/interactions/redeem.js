const { MessageFlags } = require('discord.js');

async function generateRedeem(interaction, pool) {
	
		if (!interaction.member.permissions.has('Highest')) {
            return interaction.reply({ content: 'Anda tidak memiliki izin untuk menggunakan perintah ini.', flags: MessageFlags.Ephemeral });
        }
        
        const code = interaction.options.getString('code');
        const type = interaction.options.getString('type');
        const amount = interaction.options.getInteger('amount');
        const limit = interaction.options.getInteger('limit');

        try {
            const [rows] = await pool.query('SELECT * FROM vouchers WHERE code = ?', [code]);

            if (rows.length > 0) {
                await interaction.reply({ content: 'Invalid: Code already exists.', flags: MessageFlags.Ephemeral });
                return;
            }
            await pool.query('INSERT INTO vouchers (code, vip, vip_time, gold) VALUES (?, ?, ?, ?, 0)', [code, type, amount, limit]);

            interaction.reply(`:white_check_mark: Kode redeem berhasil dibuat: **${code}** dengan hadiah ${type.toUpperCase()} sejumlah ${amount} dan limit penggunaan ${limit}`);
        } catch (error) {
            console.error('Error creating redeem code:', error);
            await interaction.reply({ content: 'There was an error trying to create the redeem code. Please try again later.', flags: MessageFlags.Ephemeral });
        }
	}
module.exports = { generateRedeem };