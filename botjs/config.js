const DEFAULT_SAMP_HOST = '139.99.22.124';
const DEFAULT_SAMP_PORT = 5555;
const DEFAULT_HELP_URL = 'https://discordapp.com/channels/1495097395644727296/1495097398815490142';
const DEFAULT_ONLINE_IMAGE = 'https://cdn.discordapp.com/attachments/1500909054153854986/1500909274803736727/standard.gif?ex=69facef0&is=69f97d70&hm=494642bea7ebb781a57d3353ec48eca02f8246c544910650553eec3b0a910ed0&';
const DEFAULT_OFFLINE_IMAGE = 'https://cdn.discordapp.com/attachments/1500909054153854986/1500909274459672677/standard.gif?ex=69facef0&is=69f97d70&hm=8182d16f55e30aa344e72a383484d14b9b128ab6ba86804af977ac7a42bc714b&';
const DEFAULT_RESTART_IMAGE = 'https://cdn.discordapp.com/attachments/1500909054153854986/1500910588476260582/standard.gif?ex=69fad029&is=69f97ea9&hm=b5316d2f4c379ae6b27d1cdec621a12258443142fcdbddfe30d57d6d4c747da3';
const DEFAULT_REGISTER_IMAGE = 'https://cdn.discordapp.com/attachments/1500909054153854986/1500914155048144906/Urban-removebg-preview.png?ex=69fad37c&is=69f981fc&hm=76a6bf6fcdc462efa5d33e1d31eef081de4f3fe5dff3ef14d6426d860328ccf8';
const DEFAULT_FACTION_IMAGE = 'https://cdn.discordapp.com/attachments/1500909054153854986/1500914155828281575/standard_1.gif?ex=69fad37c&is=69f981fc&hm=87762101203843b61b3c581110cf62a126107fb9d4efff05d03f3e9b383f9270&';

function parseBoolean(value, defaultValue = false) {
    if (value === undefined || value === null || value === '') {
        return defaultValue;
    }

    return ['1', 'true', 'yes', 'on'].includes(String(value).trim().toLowerCase());
}

function parseInteger(value, defaultValue) {
    if (value === undefined || value === null || value === '') {
        return defaultValue;
    }

    const parsed = Number.parseInt(String(value), 10);
    return Number.isNaN(parsed) ? defaultValue : parsed;
}

function env(name, fallback = '') {
    return process.env[name] ?? fallback;
}

function getConfig() {
    return {
        discordToken: env('DISCORD_TOKEN'),
        enableBotLogin: parseBoolean(env('ENABLE_BOT_LOGIN'), true),
        registerCommands: parseBoolean(env('REGISTER_COMMANDS'), true),
        dryRun: parseBoolean(env('DRY_RUN'), false),
        db: {
            host: env('DB_HOST'),
            port: parseInteger(env('DB_PORT'), 3306),
            user: env('DB_USER'),
            password: env('DB_PASSWORD'),
            database: env('DB_NAME'),
            connectTimeout: parseInteger(env('DB_CONNECT_TIMEOUT'), 10000),
        },
        discord: {
            memberRoleId: env('MEMBER_ROLE_ID'),
            updateChannelId: env('UPDATE_CHANNEL_ID'),
            monitorChannelId: env('MONITOR_CHANNEL_ID'),
            panelAccessRoleId: env('PANEL_ACCESS_ROLE_ID'),
            excludedChannelId: env('EXCLUDED_CHANNEL_ID'),
            ucpHelpUrl: env('UCP_HELP_URL', DEFAULT_HELP_URL),
        },
        samp: {
            host: env('SAMP_HOST', DEFAULT_SAMP_HOST),
            port: parseInteger(env('SAMP_PORT'), DEFAULT_SAMP_PORT),
        },
        images: {
            online: env('IMAGE_ON', DEFAULT_ONLINE_IMAGE),
            offline: env('IMAGE_OFF', DEFAULT_OFFLINE_IMAGE),
            restart: env('IMAGE_RESTART', DEFAULT_RESTART_IMAGE),
            register: env('REGISTER_IMAGE', DEFAULT_REGISTER_IMAGE),
            faction: env('FACTION_IMAGE', DEFAULT_FACTION_IMAGE),
        },
    };
}

function validateConfig(config) {
    const missing = [];

    for (const key of ['host', 'user', 'password', 'database']) {
        if (!config.db[key]) {
            missing.push(`DB_${key.toUpperCase()}`);
        }
    }

    if (config.enableBotLogin && !config.discordToken) {
        missing.push('DISCORD_TOKEN');
    }

    return missing;
}

function canAccessPanel(interaction, config) {
    if (config.discord.panelAccessRoleId) {
        return Boolean(interaction.member?.roles?.cache?.has(config.discord.panelAccessRoleId));
    }

    return Boolean(interaction.member?.permissions?.has('Administrator'));
}

module.exports = {
    getConfig,
    validateConfig,
    canAccessPanel,
};
