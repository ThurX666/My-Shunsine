const ignoredWarningCodes = new Set([
    'DEP0180',
    'MODULE_TYPELESS_PACKAGE_JSON',
]);

const originalEmitWarning = process.emitWarning.bind(process);
process.emitWarning = (warning, ...args) => {
    let warningCode;

    if (warning && typeof warning === 'object' && 'code' in warning) {
        warningCode = warning.code;
    } else if (args.length > 0 && typeof args[0] === 'object' && args[0] && 'code' in args[0]) {
        warningCode = args[0].code;
    } else if (args.length > 1 && typeof args[1] === 'string') {
        warningCode = args[1];
    }

    if (warningCode && ignoredWarningCodes.has(String(warningCode))) {
        return;
    }

    return originalEmitWarning(warning, ...args);
};

const { createRequire } = await import('node:module');
const require = createRequire(import.meta.url);
const bot = require('./index.js');

Promise.resolve(bot.start()).catch((error) => {
    console.error('Bot startup failed:', error);
    process.exitCode = 1;
});
