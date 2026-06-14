const {
    StringSelectMenuBuilder, 
    StringSelectMenuOptionBuilder, 
    SlashCommandBuilder,
    ActionRowBuilder,
    EmbedBuilder
} = require("discord.js");
const con = require('../mysql');

module.exports = {
    data: new SlashCommandBuilder()
    .setName("faction")
    .setDescription("Create Buttons Create Faction"),
    
    run: async (client, interaction) => {
        const embed = new EmbedBuilder()
        .setTitle("Families & Gang Discord")
        .setDescription("\n_\nini adalah official discord faction My Sunshine Roleplay, Silahkan join ke discord server faction untuk mengetahui informasi terbaru tentang faction.\n_\n")
        .setImage("https://cdn.discordapp.com/attachments/1500909054153854986/1500914155828281575/standard_1.gif?ex=69fad37c&is=69f981fc&hm=87762101203843b61b3c581110cf62a126107fb9d4efff05d03f3e9b383f9270&")
        .setFooter({
            text: "My Sunshine Assistent",
        })
        .setTimestamp();

        const select = new StringSelectMenuBuilder()
        .setCustomId('list-faction')
        .setPlaceholder('📌 Select Menu!')
        .addOptions(
            new StringSelectMenuOptionBuilder()
            .setLabel('Police Departement') // Only text in label
            .setDescription('Pilih menu ini untuk join discord SAPD')
            .setEmoji('1247325523479363685') // ID of the custom emoji
            .setValue('police-menu'),

            new StringSelectMenuOptionBuilder()
            .setLabel('Medic Departement') // Only text in label
            .setDescription('Pilih menu ini untuk melihat SAMD')
            .setEmoji('1247325653406060705') // ID of the custom emoji
            .setValue('Medic-menu'),

            new StringSelectMenuOptionBuilder()
            .setLabel('News Agency') // Only text in label
            .setDescription('Pilih menu ini untuk melihat SANA')
            .setEmoji('1247325682271522918') // ID of the custom emoji
            .setValue('news-menu'),

            new StringSelectMenuOptionBuilder()
            .setLabel('Goverment Service') // Only text in label
            .setDescription('Pilih menu ini untuk melihat SAGS')
            .setEmoji('1180862345266868295') // ID of the custom emoji
            .setValue('sags-menu'),

            new StringSelectMenuOptionBuilder()
            .setLabel('Family And Gang') // Only text in label
            .setDescription('Pilih menu ini untuk melihat FnG')
            .setEmoji('1247325708024418334') // ID of the custom emoji
            .setValue('family-menu')

        );

        let row = new ActionRowBuilder().addComponents(select);
        await interaction.reply({embeds: [embed], components: [row]});
    }
}