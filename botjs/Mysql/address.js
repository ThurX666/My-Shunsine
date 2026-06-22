const { getConfig } = require('../config');

function getServerInfo() {
    const config = getConfig();

    return {
        host: config.samp.host,
        port: config.samp.port,
    };
}

module.exports = {
    getServerInfo,
    get serverInfo() {
        return getServerInfo();
    },
};
