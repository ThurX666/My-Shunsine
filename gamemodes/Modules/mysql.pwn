// MySQL configuration
#if defined Production
    #define		MYSQL_HOST 			"solid.evolution-host.com"
    #define		MYSQL_USER 			"u404_R2YBSWsKaZ"
    #define		MYSQL_PASSWORD 		"oU4TPyy.tkyec@QqJaoabby1"
    #define		MYSQL_DATABASE 		"s404_sunshine"
#endif

#if defined Local
    #define		MYSQL_HOST 			"localhost"
    #define		MYSQL_USER 			"root"
    #define		MYSQL_PASSWORD 		""
    #define		MYSQL_DATABASE 		"s404_sunshine"
#endif

// vrp

// MySQL connection handle
new MySQL: g_SQL;
