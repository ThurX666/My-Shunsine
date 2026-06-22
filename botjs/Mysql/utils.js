async function checkMySQLConnection(pool) {
    let connection;

    try {
        connection = await pool.getConnection();
        console.log('Connected to MySQL database.');
        return true;
    } catch (error) {
        console.error('Failed to connect to MySQL database:', error);
        return false;
    } finally {
        if (connection) {
            connection.release();
        }
    }
}

module.exports = { checkMySQLConnection };
