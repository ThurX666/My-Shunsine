const { Client, GatewayIntentBits, PermissionsBitField } = require('discord.js');
const client = new Client({
  intents: [GatewayIntentBits.Guilds, GatewayIntentBits.GuildMessages, GatewayIntentBits.MessageContent],
});

const bannedWords = [
    "anjeng", "anjg", "anjing", "ass", "asu", "bab1", "babi", "bajingan", "bangsat", "bego", "bego.jing", "begok", 
    "bencong", "bgst", "bitch", "bjir", "blok", "brengsek", "buajingan", "cok", "dancok", "dongo", 
    "dungu", "entod", "entot", "fuck", "goblok", "haram", "idiot", "jablay", "jancok", "jembut", "jeng", 
    "jiancok", "jir", "jmbt", "juancok", "k0nt0l", "k0ntol", "kampang", "kampret", "kanjut", "khontol", 
    "kimak", "kintil", "kintil.kontol", "kirik", "kntl", "kntol", "kontl", "kontol", "Kontol", "kontols", "kuntul", 
    "kunyuk", "lol", "lonte", "meki", "memek", "memeks", "Memeks", "memeq", "memk", "mmek", 
    "mmk", "ng3n", "Ng3nt0d", "ng3nt0t", "ngen", "ngent", "ngentd", "ngentod", "Ngentod²", 
    "ngentot", "ngentt", "ngew", "ngewe", "ngewe", "ngntd", "ngntot", "nhentod", "nhentot", "njing", 
    "nyeong", "p0rn", "pantek", "peler", "poorn", "porn", "pornn", "pornrn", "puki", "pukimak", "sange", 
    "sepong", "sepongin", "spong", "t0d", "t0l0l", "t0t", "tai", "taik", "talal", "telaso", "tempik", "tilil", "tll", 
    "tlol", "tod", "tolol", "tot", "tulul", "yatim"
];

const userWarnings = new Map();

client.on('messageCreate', async (message) => {
  if (message.author.bot) return;

  // Split the message into individual words and check for exact banned words
  const words = message.content.toLowerCase().split(/\s+/); // Split by spaces and other white spaces
  
  const found = words.some(word => bannedWords.includes(word)); // Check for exact word match
  
  if (found) {
    try {
      await message.delete();

      let warnings = userWarnings.get(message.author.id) || 0;
      warnings++;

      userWarnings.set(message.author.id, warnings);
      await message.channel.reply(`${message.author}, pesan kamu mengandung konten yang tidak pantas dan telah dihapus. Ini adalah peringatan ke-${warnings}/3.`);

      if (warnings >= 3) {
        await message.member.timeout(10 * 60 * 1000, 'Penggunaan bahasa tidak pantas berulang kali'); // Timeout 10 menit
        await message.channel.send(`${message.author} telah diberi timeout selama 10 menit karena berulang kali menggunakan bahasa yang tidak pantas.`);
        userWarnings.set(message.author.id, 0);
      }

    } catch (err) {
      console.error('Gagal menghapus pesan atau memberikan timeout:', err);
    }
  }
});
