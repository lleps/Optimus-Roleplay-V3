// Map include
//						- Spell


enum 
{
	MAP_STATE_UNLOADED = 0,
	MAP_STATE_LOADED = 1,
}

static
	map_db_file[] = "maps/list.db",
	DB: map_db_id = DB:-1;

public OnGameModeInit() {

	map_db_init();
	
	#if defined opmaps_OnGameModeInit
	return opmaps_OnGameModeInit();
	#else
	return 1;
	#endif
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit opmaps_OnGameModeInit

forward opmaps_OnGameModeInit();

public OnGameModeExit() {

	map_db_close();
	
	#if defined opmaps_OnGameModeExit
	return opmaps_OnGameModeExit();
	#else
	return 1;
	#endif
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit opmaps_OnGameModeExit

forward opmaps_OnGameModeExit();

// Memory functions
stock map_load(const filename[]) {

	if (map_db_isLoaded(filename)) return 0;
	
	new
		rfilename[55],
		tmpfilename[55];
		
	format(rfilename, sizeof(rfilename), "maps/%s", filename);
	format(tmpfilename, sizeof(tmpfilename), "maps/%s.tmp", filename);
	
	if (!fexist(rfilename)) return 0;
	if (fexist(tmpfilename)) fremove(tmpfilename);
	
	// File parse
	new
		File:inputHandle = fopen(rfilename, io_read),
		File:outputHandle = fopen(tmpfilename, io_write),
		
		resultCount = map_parseFile(inputHandle, outputHandle);

	fclose(inputHandle);
	fclose(outputHandle);
	
	// Add to list db
	map_db_insert(filename, resultCount);

	return 1;
}
stock map_runFunc(const function[], function_response[], size = sizeof(function_response)) {

	new
		string[128];
		
	store(string, function);

	// Delete comments from string
	for (new i = 0; i < strlen(string); i++) {
		
		// Comment (Delete from // to end)
		if (string[i] == '/' && string[i+1] == '/') {
			strdel(string, i, strlen(string));
		}
	}
	
	// Delete Parentesis
	for (new i = 0; i < strlen(string); i++) {

		if (string[i] == '(') {
			string[i] = ':';
		}
		else if (string[i] == ')') {
			strdel(string, i, strlen(string));
		}
	}
	
	//Get functions and params
	new
		functionName[40],
		params[128];
		
	sscanf(string, "p<:>s[40]s[128]", functionName, params);
	
	if (strfind(string, "CreateDynamicObject") != -1) {

		new modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 200.0, Float:drawdistance = 0.0;

		if (!sscanf(params, "p<,>dffffffI(-1)I(-1)I(-1)F(200.0)F(0.0)", modelid, x, y, z, rx, ry, rz, worldid, interiorid, playerid, streamdistance, drawdistance)) {
			
			new ret_id = CreateDynamicObject(modelid, x, y, z, rx,ry, rz, worldid, interiorid, playerid, streamdistance, drawdistance);
				
			//printf("CreateDynamicObject(%d,%f,%f,%f,%f,%f,%f,%d,%d,%d,%f,%f);",modelid, x, y, z, rx,ry, rz, worldid, interiorid, playerid, streamdistance, drawdistance); 

			format(function_response, size, "DestroyDynamicObject(%d);", ret_id);
		}
		else {
			printf ("[src/include/optimus/maps.inc]: Parametros incorrectos (funcName: %s | params: %s)", functionName, params);
		}
	}

	
	else if (strfind(string, "DestroyDynamicObject") != -1) {

		new objectid;

		if (!sscanf(params, "i", objectid)) {
			
			DestroyDynamicObject(objectid);
			
			//printf("DestroyDynamicObject(%d);", objectid);

		}
		else {
			printf ("[src/include/optimus/maps.inc]: Parametros incorrectos (funcName: %s | params: %s)", functionName, params);
		}
	}
	
	else if (strfind(string, "CreateObject") != -1) {

		new modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:DrawDistance = 0.0;

		if (!sscanf(params, "dffffffF(0.0)", modelid, X, Y, Z, rX, rY, rZ, DrawDistance)) {
			
			new ret_id = CreateObject(modelid, X, Y, Z, rX, rY, rZ, DrawDistance);

			format(function_response, size, "DestroyObject(%d);", ret_id);
		}
		else {
			printf ("[src/include/optimus/maps.inc]: Parametros incorrectos (funcName: %s | params: %s)", functionName, params);
		}
	}
	
	else if (strfind(string, "DestroyObject") != -1) {

		new objectid;

		if (!sscanf(params, "i", objectid)) {
			
			DestroyObject(objectid);

		}
		else {
			printf ("[src/include/optimus/maps.inc]: Parametros incorrectos (funcName: %s | params: %s)", functionName, params);
		}
	}
	return 1;
}
stock map_unload(const filename[]) {
	
	if (!map_db_isLoaded(filename)) return 0;
	
	new
		tmpfilename[55];
		
	format(tmpfilename, sizeof(tmpfilename), "maps/%s.tmp", filename);
	
	if (fexist(tmpfilename)) {// run tmp file
	
		new
			File: inputHandle = fopen(tmpfilename, io_read);
		
		map_parseFile(inputHandle, File:-1); // No output data

		// Remove tmp file
		fremove(tmpfilename);
	}
	
	// Remove from list
	map_db_remove(filename);
	return 1;
}
stock map_parseFile(File:input, File:output) {

	new
		inputString[256],
		result;
		
	while (fread(input, inputString)) {
		
		new
			outputString[128],
			func_success = map_runFunc(inputString, outputString);
		
		// Unknown function
		if (func_success == -1) {
			printf("[src/include/optimus/maps.inc]: Funcion no se reconoce: %s", inputString);
			continue;
		}
		
		if (isnull(outputString)) continue;
		
		// Write in output file function response (if not null)	
		if (output != File:-1) {
			fwrite(output, outputString);
			fwrite(output, "\n");
		}
		
		// Add function return value to result.
		result += func_success;
		
	}
	return result;
}
stock map_removetmp(const filename[]) {
	new 
		strtmp[55];
		
	format(strtmp, sizeof(strtmp), "maps/%s.tmp", filename);
	
	if (fexist(strtmp)) {
		fremove(strtmp);
	}
}

// Database functions
stock map_db_init() {

	map_db_id = db_open(map_db_file);
    db_query(map_db_id, "CREATE TABLE IF NOT EXISTS list (filename VARCHAR(30), objects INTEGER DEFAULT 0 NOT NULL)");

	// Cargar lista
	map_db_loadList();

}
stock map_db_close() {
	if (map_db_id != DB:-1) {
		db_close(map_db_id);
	}
}
stock map_db_insert(const filename[], objects) {
	new
		queryStr[180];
		
	format(queryStr, sizeof(queryStr), "INSERT INTO list (filename, objects) VALUES ('%s', %d)", filename, objects);
	db_query(map_db_id, queryStr);
}
stock map_db_isLoaded(const filename[]) {
	new
		queryStr[180],
		DBResult:result,
		loaded;
		
	format(queryStr, sizeof(queryStr), "SELECT * FROM list WHERE filename = '%s'", filename);

	result = db_query(map_db_id, queryStr);
	
	loaded = db_num_rows(result);
	
	db_free_result(result);
	
	return loaded != 0;
}
stock map_db_remove(const filename[]) {
	new
		queryStr[180],
		DBResult:result;
		
	format(queryStr, sizeof(queryStr), "DELETE FROM list WHERE filename = '%s'", filename);
	result = db_query(map_db_id, queryStr);
	db_free_result(result);
}
stock DB:map_db_getDB() {
	return map_db_id;
}
stock map_db_loadList() {

	new 
		DBResult:result = db_query(map_db_id, "SELECT * FROM list");
		
	if (db_num_rows(result) != 0) {
		do
		{
			new
				filename[55],
				suc;
				
			db_get_field_assoc(result, "filename", filename, sizeof(filename));
			
			map_removetmp(filename);
			
			map_unload(filename);
			suc = map_load(filename);
			
			printf ("*- Cargando archivo de mapas '%s'..			%s.", filename, suc ? ("Cargado") : ("Fallido"));
		}
		while(db_next_row(result));
	}
	db_free_result(result);
}
