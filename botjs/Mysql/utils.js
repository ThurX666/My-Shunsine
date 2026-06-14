async function checkMySQLConnection(pool) {
    try {
        await pool.getConnection();
        console.log('Connected to MySQL database.');
    } catch (error) {
        console.error('Failed to connect to MySQL database:', error);
    }
}

module.exports = { checkMySQLConnection };
