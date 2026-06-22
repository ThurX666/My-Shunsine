# BotJS Deployment

## Pterodactyl

- Runtime: Node.js 20 LTS
- Startup command: gunakan bawaan panel
- `MAIN_FILE`: `index.ts` jika panel memaksa jalur `ts-node --esm`
- `MAIN_FILE`: `index.js` jika panel benar-benar menjalankan `node` untuk file `.js`
- Working directory: folder root yang berisi `package.json` dan `index.js`
- Install command: `npm install --omit=dev`

## Required Environment Variables

- `DISCORD_TOKEN`
- `DB_HOST`
- `DB_PORT` default `3306`
- `DB_USER`
- `DB_PASSWORD`
- `DB_NAME`
- `ENABLE_BOT_LOGIN`
- `REGISTER_COMMANDS`
- `MEMBER_ROLE_ID`
- `UPDATE_CHANNEL_ID`
- `PANEL_ACCESS_ROLE_ID`
- `SAMP_HOST`
- `SAMP_PORT`

## Local Debug

- Set `ENABLE_BOT_LOGIN=false`
- Set `REGISTER_COMMANDS=false`
- Run `node index.js`

Mode ini hanya memvalidasi konfigurasi dan koneksi database tanpa login Discord.
