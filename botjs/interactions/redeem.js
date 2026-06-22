const { MessageFlags } = require('discord.js');

async function generateRedeem(interaction, pool, config) {
		if (config.discord.panelAccessRoleId && !interaction.member.roles.cache.has(config.discord.panelAccessRoleId)) {
            return interaction.reply({ content: 'Anda tidak memiliki izin untuk menggunakan perintah ini.', flags: MessageFlags.Ephemeral });
        }

        if (!config.discord.panelAccessRoleId && !interaction.member.permissions.has('Administrator')) {
            return interaction.reply({ content: 'Anda tidak memiliki izin untuk menggunakan perintah ini.', flags: MessageFlags.Ephemeral });
        }
        
        const code = interaction.options.getString('code');
        const type = interaction.options.getString('type');
        const amount = interaction.options.getInteger('amount');
        const limit = interaction.options.getInteger('limit');

        try {
            if (type === 'money') {
                await interaction.reply({
                    content: 'Reward type MONEY is not supported by the current vouchers table schema yet.',
                    flags: MessageFlags.Ephemeral
                });
                return;
            }

            const [rows] = await pool.query('SELECT * FROM vouchers WHERE code = ?', [code]);

            if (rows.length > 0) {
                await interaction.reply({ content: 'Invalid: Code already exists.', flags: MessageFlags.Ephemeral });
                return;
            }
            const values = {
                gold: { vip: 0, vip_time: 0, gold: amount },
                vip: { vip: 1, vip_time: amount, gold: 0 },
            };

            if (!values[type]) {
                await interaction.reply({ content: 'Invalid reward type.', flags: MessageFlags.Ephemeral });
                return;
            }

            await pool.query(
                'INSERT INTO vouchers (code, vip, vip_time, gold, claimvip, admin, donature, claim) VALUES (?, ?, ?, ?, ?, ?, ?, ?)',
                [code, values[type].vip, values[type].vip_time, values[type].gold, `0|0|${limit}`, interaction.user.username, interaction.user.username, 0]
            );

            interaction.reply(`:white_check_mark: Kode redeem berhasil dibuat: **${code}** dengan hadiah ${type.toUpperCase()} sejumlah ${amount} dan limit penggunaan ${limit}`);
        } catch (error) {
            console.error('Error creating redeem code:', error);
            await interaction.reply({ content: 'There was an error trying to create the redeem code. Please try again later.', flags: MessageFlags.Ephemeral });
        }
	}
module.exports = { generateRedeem };
