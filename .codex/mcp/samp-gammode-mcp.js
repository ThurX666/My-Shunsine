const { spawn } = require('child_process');
const fs = require('fs');
const path = require('path');
const readline = require('readline');

let serverProcess = null;
let logLines = [];
const projectRoot = 'C:/Users/guyub/Downloads/SUNSHINE';

console.log('[SAMP-MCP] Initialized!', process.cwd());

async function main() {
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
        terminal: false
    });

    rl.on('line', async (input) => {
        try {
            if (!input.trim()) return;
            
            const message = JSON.parse(input);
            console.log('[SAMP-MCP] Message:', message.method);
            
            let result = null;
            
            switch (message.method) {
                case 'initialize':
                    result = {
                        id: message.id,
                        result: {
                            protocolVersion: '2024-11-05',
                            capabilities: { tools: {} },
                            serverInfo: { name: 'samp-gammode-mcp', version: '2.0.0' }
                        }
                    };
                    break;
                    
                case 'tools/list':
                    result = { id: message.id, result: { tools: getToolList() } };
                    break;
                    
                case 'tools/call':
                    result = await handleCall(message.params);
                    break;
                    
                default:
                    result = { id: message.id, error: { code: -32601, message: 'Method not found' } };
            }
            
            console.log('[SAMP-MCP] Sending response for id:', message.id);
            console.log('[SAMP-MCP] Response:', JSON.stringify(result).substring(0, 100));
            process.stdout.write(JSON.stringify(result) + '\n');
            console.log('[SAMP-MCP] Done!');
            
        } catch (error) {
            console.error('[SAMP-MCP] ERROR:', error.message);
            console.error(error.stack);
            if (message?.id) {
                process.stdout.write(JSON.stringify({
                    id: message.id,
                    error: { code: -32603, message: error.message }
                }) + '\n');
            }
        }
    });
}

function getToolList() {
    return [
        { name: 'pawn_compile', description: 'Compile .pwn to .amx file' },
        { name: 'pawn_check_syntax', description: 'Fast syntax validation' },
        { name: 'pawn_run_server', description: 'Start SA-MP server' },
        { name: 'pawn_stop_server', description: 'Stop server gracefully' },
        { name: 'pawn_restart_server', description: 'Restart SA-MP server' },
        { name: 'pawn_get_log', description: 'Read last N lines of log' },
        { name: 'pawn_filter_log', description: 'Filter log by keyword or error level' },
        { name: 'pawn_server_status', description: 'Check if server is running' },
        { name: 'pawn_list_scripts', description: 'List all .pwn and .inc files in project' },
        { name: 'pawn_read_file', description: 'Read file content with optional line range' },
        { name: 'pawn_write_file', description: 'Write content to file' },
        { name: 'pawn_list_dir', description: 'List contents of a directory' },
        { name: 'pawn_find_files', description: 'Find files matching pattern' },
        { name: 'pawn_copy_file', description: 'Copy file to destination' },
        { name: 'pawn_count_lines', description: 'Count total lines in a file' },
        { name: 'pawn_find_include', description: 'Find #include directive usage' },
        { name: 'pawn_find_function', description: 'Find function definition or usage' },
        { name: 'pawn_extract_functions', description: 'Extract all public functions from file' },
        { name: 'pawn_find_constants', description: 'Find all constants definitions' },
        { name: 'pawn_get_dependencies', description: 'Get list of required includes' },
        { name: 'pawn_project_info', description: 'Get comprehensive project information' },
        { name: 'pawn_backup_gamemode', description: 'Create backup of current gamemode' },
        { name: 'pawn_restore_gamemode', description: 'Restore gamemode from backup' },
        { name: 'pawn_version_control', description: 'Git operations for version control' },
        { name: 'pawn_start_fivem', description: 'Alternative method via sampctl/yampc' },
        { name: 'pawn_install_dependencies', description: 'Install package dependencies' },
        { name: 'pawn_clear_cache', description: 'Clear temporary files and cache' },
        { name: 'pawn_analysis_errors', description: 'Run comprehensive error analysis' },
        { name: 'pawn_project_summary', description: 'AI-friendly summary of entire project' }
    ];
}

async function handleCall(params) {
    const { name, arguments: args } = params || {};
    console.log('[SAMP-MCP] Calling tool:', name || 'unknown');
    
    try {
        switch (name) {
            case 'pawn_compile':
                return await callCompile(args);
            case 'pawn_run_server':
                return await callRunServer(args);
            case 'pawn_stop_server':
                return callStopServer();
            case 'pawn_restart_server':
                if (serverProcess) { serverProcess.kill(); await sleep(1000); }
                return await callRunServer(args);
            case 'pawn_get_log':
                return { log: logLines.slice(-args?.lines || 50).join('\n') || 'No logs' };
            case 'pawn_list_scripts':
                return callListScripts(args?.directory);
            case 'pawn_read_file':
                return callReadFile(args?.filepath, args?.startLine, args?.endLine);
            case 'pawn_write_file':
                return callWriteFile(args);
            case 'pawn_list_dir':
                return callListDir(args?.path);
            case 'pawn_find_files':
                return callFindFiles(args);
            case 'pawn_count_lines':
                return callCountLines(args?.file);
            case 'pawn_check_syntax':
                return await callCheckSyntax(args?.file);
            case 'pawn_server_status':
                return { running: !!serverProcess, pid: serverProcess?.pid };
            default:
                return { 
                    error: `Unknown tool: ${name}`, 
                    available: ['pawn_compile', 'pawn_list_scripts', 'pawn_read_file'],
                    note: 'Use tools/list to see all available'
                };
        }
    } catch (error) {
        console.error('[SAMP-MCP] Tool error:', error.message);
        console.error(error.stack);
        return { error: error.message, stack: error.stack };
    }
}

async function callCompile(args) {
    console.log('[SAMP-MCP] Compiling...');
    return exec('pawn', ['-d', 'gamemodes/main.pwn']);
}

async function callRunServer(args) {
    if (serverProcess) return { error: 'Already running', pid: serverProcess.pid };
    console.log('[SAMP-MCP] Starting server...');
    try {
        const proc = spawn('samp-server.exe', [], { cwd: projectRoot });
        serverProcess = proc;
        proc.stdout?.on('data', d => logLines.push(d.toString()));
        proc.stderr?.on('data', d => logLines.push(d.toString()));
        return { success: true, pid: proc.pid, message: 'Server started' };
    } catch (e) {
        return { error: e.message };
    }
}

function callStopServer() {
    if (!serverProcess) return { error: 'Not running' };
    serverProcess.kill();
    serverProcess = null;
    return { success: true, message: 'Server stopped' };
}

function callListScripts(directory) {
    console.log('[SAMP-MCP] Listing scripts in:', directory || 'gamemodes');
    try {
        const dir = directory ? path.join(projectRoot, directory) : path.join(projectRoot, 'gamemodes');
        const files = fs.readdirSync(dir).filter(f => f.endsWith('.pwn') || f.endsWith('.inc'))
            .map(f => path.join(dir, f));
        return { scripts: files, count: files.length };
    } catch (e) {
        return { error: e.message, dir };
    }
}

function callReadFile(filepath, start, end) {
    console.log('[SAMP-MCP] Reading file:', filepath);
    try {
        const filePath = path.join(projectRoot, filepath);
        const content = fs.readFileSync(filePath, 'utf8');
        const lines = content.split('\n');
        const display = start && end ? lines.slice(start - 1, end).join('\n') : content.substring(0, 5000);
        return { content: display, lines: lines.length, path: filePath };
    } catch (e) {
        return { error: e.message, file: filepath };
    }
}

function callWriteFile(args) {
    try {
        const filePath = path.join(projectRoot, args?.filepath);
        fs.writeFileSync(filePath, args?.content || '', args?.append ? 'a' : 'w');
        return { success: true, bytes: (args?.content || '').length };
    } catch (e) {
        return { error: e.message };
    }
}

function callListDir(path) {
    try {
        const fullPath = path ? path.join(projectRoot, path) : projectRoot;
        const entries = fs.readdirSync(fullPath, { withFileTypes: true })
            .map(e => ({ name: e.name, isDirectory: e.isDirectory(), isFile: e.isFile() }));
        return { entries, count: entries.length };
    } catch (e) {
        return { error: e.message };
    }
}

function callFindFiles(args) {
    return { found: 0, files: [], note: 'Feature coming soon' };
}

function callCountLines(file) {
    try {
        const filePath = path.join(projectRoot, file);
        const content = fs.readFileSync(filePath, 'utf8');
        return { total: content.split('\n').length, nonEmpty: content.split('\n').filter(l => l.trim()).length };
    } catch (e) {
        return { error: e.message };
    }
}

async function callCheckSyntax(file) {
    return await exec('pawn', ['-d', file || 'gamemodes/main.pwn']);
}

async function exec(cmd, args) {
    return new Promise((resolve) => {
        const proc = spawn(cmd, args, { cwd: projectRoot, windowsHide: true });
        let stdout = '', stderr = '';
        proc.stdout.on('data', d => stdout += d);
        proc.stderr.on('data', d => stderr += d);
        proc.on('close', c => resolve({ success: c === 0, output: stdout, errors: stderr, code: c }));
        proc.on('error', e => resolve({ success: false, error: e.message }));
    });
}

function sleep(ms) { return new Promise(r => setTimeout(r, ms)); }

main().catch(console.error);
