@echo off
echo Windows local debug helper
echo ENABLE_BOT_LOGIN=false lets you validate config and DB without logging into Discord.
set ENABLE_BOT_LOGIN=false
set REGISTER_COMMANDS=false

echo Installing dependencies...
npm install

echo Starting the bot...
node index.js

pause
