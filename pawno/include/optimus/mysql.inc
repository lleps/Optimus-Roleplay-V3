new opHandle = -1;

enum e_mysql_data {
	myhost,
	myuser,
	mydatabase,
	mypassword
}

static MySQL[e_mysql_data][45];

public OnGameModeInit() {
	
	opmysql_init();
	
	opmysql_runFile("MySQL/Vehiculos.sql");
	opmysql_runFile("MySQL/Subsidios.sql");
	opmysql_runFile("MySQL/Logs.sql");
	
	#if defined opmysql_OnGameModeInit
		return opmysql_OnGameModeInit();
	#else
		return 1;
	#endif
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit opmysql_OnGameModeInit

forward opmysql_OnGameModeInit();

stock opmysql_init() {

	static const filename[] = "database.ini";
	
	if (!fexist (filename)) {
	    printf ("NO EXISTE EL ARCHIVO DATABASE.ini ...");
	    
		static bool: running = true;
		
		while (running) {}
	
	}
	
	new
	    stringRead[100],
	    File: config = fopen (filename, io_read);

	while (fread(config, stringRead)) {
	
	    if (stringRead[0] == '#' || stringRead[1] == '#')
	        continue;
	        
		printf ("Informacion de MySQL:");
		
	    sscanf (stringRead, "p<|>s[30]s[30]s[30]s[30]", MySQL[myhost], MySQL[myuser], MySQL[mydatabase], MySQL[mypassword]);
	    
	    printf ("\t- Host: \"%s\"", MySQL[myhost]);
	    printf ("\t- User: \"%s\"", MySQL[myuser]);
	    printf ("\t- Database: \"%s\"", MySQL[mydatabase]);
	    printf ("\t- Password: \"%s\"", MySQL[mypassword]);

	}
	
	mysql_log(LOG_WARNING | LOG_ERROR);
	
	printf ("Intentando conectar ..");
	
	opHandle = mysql_connect (MySQL[myhost], MySQL[myuser], MySQL[mydatabase], MySQL[mypassword]);
	mysql_log(LOG_ERROR | LOG_WARNING);
	
}
stock opmysql_runFile(const filename[]) {
	
	if (!fexist(filename)) {
		printf ("[src/include/optimus/mysql.inc]: Error, opmysql_runFile (Archivo '%s' no existe)", filename);
		return 0;
	}
	
	new
		File:arch = fopen(filename, io_read),
		stringRead[1024];
		
	while (fread(arch, stringRead)) {
		if (strfind(stringRead, "#") != -1 || strlen(stringRead) < 5) continue;

		mysql_tquery(opHandle, stringRead, "", "");
		//printf(stringRead);
	}
	
	return 1;
}

// All definitions
#define opmysql_tquery(		mysql_tquery(opHandle,
#define opmysql_pquery(		mysql_pquery(opHandle,
#define opmysql_format(		mysql_format(opHandle,