// Optimus RolePlay Vehicle functions
// 						* By spell

#if defined _opvehicle_included_
	#endinput
#endif

#define _opvehicle_included_

#if !defined IsValidVehicle
	native IsValidVehicle(vehicleid);
#endif

// * Definitions
#define ownVeh_loop(%0) 					for (new %0 = ownVeh:0; _:%0 < MAX_VEHICLES; %0++) if(ownVeh_isValid(%0))
//#define ownVeh_displayVehicles(%0,%1,%2)	for (new %1 = 0, %2 = InfoJugador[%0][jVehiculo][%1]; %1 < E_VEH_MAX; %1++) if((%2 = InfoJugador[%0][jVehiculo][%1]) != INVALID_OWNVEH_ID)
#define ownVeh_displayVehicles(%0,%1) 		foreach(ownVeh, %1) if (InfoJugador[%0][jNameCode] == veh_getOwnerCode(ownVeh_ID(ownVeh:%1)))
#define veh_loop(%0)						for (new %0 = 0; %0 < MAX_VEHICLES; %0++) if(IsValidVehicle(%0))

#define veh_setFamily veh_setExtra1
#define veh_getFamily veh_getExtra1

#define veh_setFaction veh_setExtra1
#define veh_getFaction(%0) ((veh_getType(%0) == VEH_TYPE_FACVEH) ? veh_getExtra1(%0) : 0)

#define veh_setJob veh_setExtra1
#define veh_getJob(%0) ((veh_getType(%0) == VEH_TYPE_JOBVEH) ? veh_getExtra1(%0) : 0)

#define sellVeh_path "Vehiculos/venta.dat"

#define INVALID_OWNVEH_ID ownVeh:-0xFF

// * Enums
enum {
	E_VEH_RESPAWNTIME = -1,
	E_VEH_MAX = 10, // Max vehicles per-player
	E_MAX_COMPONENTS = 14,
	E_VEH_WAITTIME = 60 * 60 * 3, // 3 hs
	E_VEH_WAITTIME_ADD = 10 * 60, // 10 min
	E_VEH_DESTROYED_VW = 0b01,
	E_VEH_DESTROYED_TIME = 60 * 50, // 50 min
	
	// Vehicle type
	VEH_TYPE_OWNVEH = 1,
	VEH_TYPE_SELLVEH = 2,
	VEH_TYPE_JOBVEH = 3,
	VEH_TYPE_FACVEH = 4,
	
	// Model
	E_MAX_MODEL = 611
}

enum (<<= 1) {
	OPTION_CLOSE_ON_SPAWN = 0b01
}
enum E_VEH_DATA {

	vehdomain[MAX_PLAYER_NAME],
	vehdomaincode,
	
	vehtype,
	vehmodelid,
	
	Float:vehsx,
	Float:vehsy,
	Float:vehsz,
	Float:vehsangle,

	vehsintid,
	vehsvwid,
	vehintid,
	vehvwid,
	vehplate,
	vehextra1,
	vehcolor1,
	vehcolor2,
	vehbools,
	Float:vehfuel,
	vehlastspawn,
	
	// Custom
	vehpaintjob,
	vehmods[E_MAX_COMPONENTS]
}

#define veh_debug printf

// * OwnVeh enums
enum E_OWNVEH_DATA {

	ownUID, // Unique-ID
	ownSID, // Server-ID
	
	ownwaittime,
	ownspawntime
}

static
	// Vars
	ownVeh:ownVehData[MAX_VEHICLES][E_OWNVEH_DATA],
	vehData[MAX_VEHICLES][E_VEH_DATA]
;

new
	// Iterators
	Iterator:veh<MAX_VEHICLES>,
	Iterator:ownVeh<MAX_VEHICLES>
;

// * model enum
enum E_MODEL_DATA
{
	modelname [32 char],
	modelmaxspeed,
	modelmaxfuel,
	modelmalslots
}

static const modelData[][E_MODEL_DATA] =
{
	{!"Landstalker", 140, 120, 10},
	{!"Bravura", 131, 60, 6},
	{!"Buffalo", 166, 65, 6},
	{!"Linerunner", 98, 150, 0},
	{!"Pereniel", 118, 60, 8},
	{!"Sentinel", 146, 60, 6},
	{!"Dumper", 98, 120, 0},
	{!"Firetruck", 132, 110, 0},
	{!"Trashmaster", 89, 120, 0},
	{!"Stretch", 140, 85, 6},
	{!"Manana", 115, 60, 4},
	{!"Infernus", 197, 80, 0},
	{!"Voodoo", 150, 75, 6},
	{!"Pony", 98, 90, 3},
	{!"Mule", 94, 90, 12},
	{!"Cheetah", 171, 70, 4},
	{!"Ambulancia", 137, 120, 10},
	{!"Leviathan", 399, 300, 12},
	{!"Moonbeam", 103, 95, 6},
	{!"Esperanto", 133, 70, 4},
	{!"Taxi", 129, 65, 6},
	{!"Washington", 137, 70, 6},
	{!"Bobcat", 124, 90, 10},
	{!"Mr Whoopee", 88, 90, 6},
	{!"BF Injection", 120, 50, 0},
	{!"Hunter", 399, 450, 0},
	{!"Premier", 154, 65, 6},
	{!"Enforcer", 147, 100, 10},
	{!"Securicar", 139, 100, 12},
	{!"Banshee", 179, 70, 0},
	{!"Predator", 399, 300, 0},
	{!"Bus", 116, 200, 0},
	{!"Rhino", 84, 500, 0},
	{!"Barracks", 98, 250, 20},
	{!"Hotknife", 148, 50, 4},
	{!"Trailer", 0, 9999, 0},
	{!"Previon", 133, 60, 4},
	{!"Coach", 140, 200, 0},
	{!"Cabbie", 127, 75, 6},
	{!"Stallion", 150, 60, 4},
	{!"Rumpo", 121, 90, 12},
	{!"RC Bandit", 67, 40, 0},
	{!"Romero", 124, 70, 10},
	{!"Packer", 112, 200, 0},
	{!"Monster Truck A", 98, 100, 0},
	{!"Admiral", 146, 65, 6},
	{!"Squalo", 399, 300, 0},
	{!"Seasparrow", 399, 200, 0},
	{!"Pizzaboy", 162, 50, 1},
	{!"Tram", 399, 100, 0},
	{!"Trailer", 399, 9999, 0},
	{!"Turismo", 172, 75, 0},
	{!"Speeder", 399, 300, 0},
	{!"Reefer", 399, 500, 0},
	{!"Tropic", 399, 500, 0},
	{!"Flatbed", 140, 200, 20},
	{!"Yankee", 94, 150, 17},
	{!"Caddy", 84, 40, 3},
	{!"Solair", 140, 70, 6},
	{!"Berkley's RC Van", 121, 85, 10},
	{!"Skimmer", 399, 100, 0},
	{!"PCJ-600", 180, 70, 0},
	{!"Faggio", 155, 50, 0},
	{!"Freeway", 180, 60, 0},
	{!"RC Baron", 399, 100, 0},
	{!"RC Raider", 399, 100, 0},
	{!"Glendale", 131, 70, 6},
	{!"Oceanic", 125, 70, 6},
	{!"Sanchez", 164, 50, 3},
	{!"Sparrow", 399, 150, 0},
	{!"Patriot", 139, 100, 8},
	{!"Quad", 98, 70, 0},
	{!"Coastguard", 399, 300, 17},
	{!"Dinghy", 399, 100, 0},
	{!"Hermes", 133, 70, 4},
	{!"Sabre", 154, 70, 8},
	{!"Rustler", 399, 120, 0},
	{!"ZR-350", 166, 60, 4},
	{!"Walton", 105, 80, 10},
	{!"Regina", 124, 70, 4},
	{!"Comet", 164, 60, 4},
	{!"BMX", 86, 9999, 0},
	{!"Burrito", 139, 85, 12},
	{!"Camper", 109, 85, 12},
	{!"Marquis", 399, 350, 7},
	{!"Baggage", 88, 60, 0},
	{!"Dozer", 56, 150, 0},
	{!"Maverick", 399, 200, 6},
	{!"Maverick (LSTV)", 399, 100, 0},
	{!"Rancher", 124, 80, 6},
	{!"FBI Rancher", 139, 90, 7},
	{!"Virgo", 132, 70, 4},
	{!"Greenwood", 125, 70, 6},
	{!"Jetmax", 399, 300, 0},
	{!"Hotring", 191, 90, 4},
	{!"Sandking", 157, 80, 8},
	{!"Blista Compact", 145, 60, 6},
	{!"Maverick (SAPD)", 399, 200, 6},
	{!"Boxville", 96, 120, 17},
	{!"Benson", 109, 150, 17},
	{!"Mesa", 125, 60, 5},
	{!"RC Goblin", 399, 100, 0},
	{!"Hotring Racer", 191, 90, 0},
	{!"Hotring Racer", 191, 90, 0},
	{!"Bloodring Banger", 154, 90, 6},
	{!"Rancher", 124, 80, 7},
	{!"Super GT", 159, 75, 6},
	{!"Elegant", 148, 75, 6},
	{!"Journey", 96, 90, 12},
	{!"Bicicleta", 93, 9999, 0},
	{!"Mountain Bike", 117, 9999, 0},
	{!"Beagle", 399, 150, 0},
	{!"Cropdust", 399, 150, 0},
	{!"Stunt", 399, 150, 0},
	{!"Tanker", 107, 200, 0},
	{!"RoadTrain", 126, 200, 0},
	{!"Nebula", 140, 70, 6},
	{!"Majestic", 140, 60, 4},
	{!"Buccaneer", 146, 70, 4},
	{!"Shamal", 399, 500, 0},
	{!"Hydra", 399, 750, 0},
	{!"FCR-900", 190, 70, 0},
	{!"NRG-500", 200, 90, 0},
	{!"HPV1000", 172, 80, 4},
	{!"Cement Truck", 116, 0, 0},
	{!"Tow Truck", 143, 100, 0},
	{!"Fortune", 140, 60, 4},
	{!"Cadrona", 133, 60, 4},
	{!"FBI Truck", 157, 80, 7},
	{!"Willard", 133, 70, 6},
	{!"Forklift", 54, 70, 0},
	{!"Tractor", 62, 80, 0},
	{!"Combine", 98, 100, 0},
	{!"Feltzer", 148, 70, 6},
	{!"Remington", 150, 70, 4},
	{!"Slamvan", 140, 75, 8},
	{!"Blade", 154, 70, 6},
	{!"Freight", 399, 1000, 0},
	{!"Streak", 399, 700, 0},
	{!"Vortex", 89, 100, 0},
	{!"Vincent", 136, 70, 6},
	{!"Bullet", 180, 75, 4},
	{!"Clover", 146, 65, 6},
	{!"Sadler", 134, 80, 10},
	{!"Firetruck", 132, 100, 0},
	{!"Hustler", 131, 70, 0},
	{!"Intruder", 133, 70, 6},
	{!"Primo", 127, 65, 6},
	{!"Cargobob", 399, 450, 17},
	{!"Tampa", 136, 65, 6},
	{!"Sunrise", 128, 70, 5},
	{!"Merit", 140, 70, 9},
	{!"Utility", 108, 90, 0},
	{!"Nevada", 399, 100, 0},
	{!"Yosemite", 128, 90, 12},
	{!"Windsor", 141, 60, 4},
	{!"Monster Truck B", 98, 90, 0},
	{!"Monster Truck C", 98, 90, 0},
	{!"Uranus", 139, 70, 4},
	{!"Jester", 158, 70, 6},
	{!"Sultan", 150, 85, 8},
	{!"Stratum", 137, 70, 6},
	{!"Elegy", 158, 70, 6},
	{!"Raindance", 399, 300, 17},
	{!"RC Tiger", 79, 300, 0},
	{!"Flash", 146, 70, 6},
	{!"Tahoma", 142, 70, 6},
	{!"Savanna", 154, 65, 4},
	{!"Bandito", 130, 60, 0},
	{!"Freight", 399, 100, 0},
	{!"Trailer", 399, 9999, 0},
	{!"Kart", 83, 40, 0},
	{!"Mower", 54, 90, 0},
	{!"Duneride", 98, 120, 20},
	{!"Sweeper", 53, 60, 0},
	{!"Broadway", 140, 70, 6},
	{!"Tornado", 140, 70, 8},
	{!"AT-400", 399, 1000, 0},
	{!"DFT-30", 116, 150, 20},
	{!"Huntley", 140, 90, 10},
	{!"Stafford", 136, 80, 6},
	{!"BF-400", 170, 70, 3},
	{!"Newsvan", 121, 100, 0},
	{!"Tug", 76, 100, 0},
	{!"Trailer", 399, 9999, 0},
	{!"Emperor", 136, 70, 6},
	{!"Wayfarer", 175, 75, 0},
	{!"Euros", 147, 70, 5},
	{!"Hotdog", 96, 80, 0},
	{!"Club", 145, 75, 6},
	{!"Trailer", 399, 9999, 0},
	{!"Trailer", 399, 9999, 0},
	{!"Andromada", 399, 2000, 0},
	{!"Dodo", 399, 500, 0},
	{!"RC Cam", 54, 10, 0},
	{!"Launch", 399, 90, 14},
	{!"Patrulla (LSPD)", 210, 90, 8},
	{!"Patrulla (SFPD)", 156, 90, 8},
	{!"Patrulla (LVPD)", 156, 90, 8},
	{!"Police Ranger", 140, 120, 8},
	{!"Picador", 134, 70, 10},
	{!"S.W.A.T. Van", 98, 200, 0},
	{!"Alpha", 150, 70, 4},
	{!"Phoenix", 152, 75, 4},
	{!"Glendale (Chocado)", 131, 40, 6},
	{!"Sadler (Chocada)", 134, 40, 10},
	{!"Luggage Trailer", 399, 50, 0},
	{!"Luggage Trailer", 399, 50, 0},
	{!"Stair Trailer", 399, 50, 0},
	{!"Boxville", 96, 120, 12},
	{!"Farm Plow", 399, 200, 0},
	{!"Utility Trailer", 399, 50, 0}
};

public OnGameModeInit() {

	sellVeh_loadFile();
	
	#if defined opvehicle_OnGameModeInit
	return opvehicle_OnGameModeInit();
	#else
	return 1;
	#endif
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit opvehicle_OnGameModeInit

forward opvehicle_OnGameModeInit();

public OnVehicleSpawn(vehicleid) {

	#if defined opvehicle_OnVehicleSpawn
	opvehicle_OnVehicleSpawn(vehicleid);
	#endif
	
	veh_refuel(vehicleid);
	
	if (veh_getType(vehicleid) == VEH_TYPE_OWNVEH || veh_getType(vehicleid) == VEH_TYPE_SELLVEH) {
		veh_applySpawnInfo(vehicleid);
	}
	return 1;
}

#if defined _ALS_OnVehicleSpawn
	#undef OnVehicleSpawn
#else
	#define _ALS_OnVehicleSpawn
#endif
#define OnVehicleSpawn opvehicle_OnVehicleSpawn

forward opvehicle_OnVehicleSpawn(vehicleid);

stock veh_create(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawntime=-1, intid=0, vwid=0, type = 0, bools = 0) {
	new vehID = CreateVehicle(modelid, x, y, z, angle, color1, color2, respawntime);
	
	if (vehID != INVALID_VEHICLE_ID) {

		if (color1 == -1) color1 = random(0xFF / 2);
		if (color2 == -1) color2 = random(0xFF / 2);
		
		//Spawn data
		vehData[vehID][vehtype] = type;
		vehData[vehID][vehmodelid] = modelid;
		vehData[vehID][vehsx] = x;
		vehData[vehID][vehsy] = y;
		vehData[vehID][vehsz] = z;
		vehData[vehID][vehsangle] = angle;
		vehData[vehID][vehsintid] = intid;
		vehData[vehID][vehsvwid] = vwid;
		vehData[vehID][vehbools] = bools;
		
		//Other
		vehData[vehID][vehintid] = intid;
		vehData[vehID][vehvwid] = vwid;
		vehData[vehID][vehcolor1] = color1;
		vehData[vehID][vehcolor2] = color2;
		vehData[vehID][vehlastspawn] = gettime();
		
		if (intid != 0) veh_setInterior(vehID, intid);
		if (vwid != 0) veh_setVirtualWorld(vehID, vwid);
	
		if (bools & OPTION_CLOSE_ON_SPAWN) {
			veh_setDoors(vehID, true);
		}
		
		veh_refuel(vehID);
		
		Iter_Add(veh, vehID);
	}
	return vehID;
}
stock veh_destroy(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return;
	
	// Clear
	for (new i = 0; E_VEH_DATA:i < E_VEH_DATA; i++) {
		vehData[vehicleid][E_VEH_DATA:i] = 0;
	}
	
	new next;
	Iter_SafeRemove(veh, vehicleid, next);
	DestroyVehicle(vehicleid);
}
stock veh_setOwner(vehicleid, owner[]) {
	if (!IsValidVehicle(vehicleid)) return;
	
	store(vehData[vehicleid][vehdomain], owner, MAX_PLAYER_NAME);
	vehData[vehicleid][vehdomaincode] = udb_hash(owner);
}
stock veh_getOwner(vehicleid, owner[], size = sizeof(owner)) {
	if (!IsValidVehicle(vehicleid)) return 0;
	
	store(owner, vehData[vehicleid][vehdomain], size);
	return 1;
}
stock veh_getOwnerCode(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return 0;
	
	return vehData[vehicleid][vehdomaincode];
}
stock veh_getOwnerAsString(vehicleid) {
	new
		owner[MAX_PLAYER_NAME] = "Nadie";
		
	veh_getOwner(vehicleid, owner, sizeof(owner));
	return owner;
}
stock veh_setType(vehicleid, type) {
	if (!IsValidVehicle(vehicleid)) return;
	
	vehData[vehicleid][vehtype] = type;
}
stock veh_getType(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return -1;
	
	return vehData[vehicleid][vehtype];
}
stock veh_toggleOption(vehicleid, option, toggle) {
	if (!IsValidVehicle(vehicleid)) return;
	
	if (toggle)
		vehData[vehicleid][vehbools] |= option;
		
	else
		vehData[vehicleid][vehbools] &= ~option;
		
}
stock veh_getOption(vehicleid, option) {
	if (!IsValidVehicle(vehicleid)) return 0;
	
	return (vehData[vehicleid][vehbools] & option);
}
stock veh_getOptions(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return 0;
	
	return vehData[vehicleid][vehbools];
}
stock veh_setOptions(vehicleid, value) {
	if (!IsValidVehicle(vehicleid)) return;
	
	vehData[vehicleid][vehbools] = value;
}
stock veh_setInterior(vehicleid, intid) {
	if (!IsValidVehicle(vehicleid))	return;
	
	foreach(Player, i) {
		if (GetPlayerVehicleID(i) == vehicleid) {
			SetPlayerInterior(i, intid);
		}
	}
	
	vehData[vehicleid][vehintid] = intid;
	LinkVehicleToInterior(vehicleid, intid);
}
stock veh_getInterior(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return -1;
	
	return vehData[vehicleid][vehintid];
}
stock veh_setVirtualWorld(vehicleid, vwid) {
	if (!IsValidVehicle(vehicleid)) return;
	
	foreach(Player, i) {
		if (GetPlayerVehicleID(i) == vehicleid) {
			SetPlayerVirtualWorld(i, vwid);
		}
	}
	
	vehData[vehicleid][vehvwid] = vwid;
	SetVehicleVirtualWorld(vehicleid, vwid);
}
stock veh_getVirtualWorld(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return -1;
	
	return vehData[vehicleid][vehvwid];
}
stock veh_getModelID(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return 0;
	
	return vehData[vehicleid][vehmodelid];
}
stock veh_getColor(vehicleid, &color1, &color2) {
	if (!IsValidVehicle(vehicleid)) return;
	
	color1 = vehData[vehicleid][vehcolor1];
	color2 = vehData[vehicleid][vehcolor2];
}
stock veh_setColor(vehicleid, color1, color2) {
	if (!IsValidVehicle(vehicleid)) return;
	
	vehData[vehicleid][vehcolor1] = color1;
	vehData[vehicleid][vehcolor2] = color2;
	
	ChangeVehicleColor(vehicleid, color1, color2);
}
stock veh_applySpawnInfo(vehicleid) {

	if (!IsValidVehicle(vehicleid)) return;
	
	// Blank memory data of the specified id.
	if (vehData[vehicleid][vehmodelid] == 0) return;
	
	// Set int and vw to 0
	vehData[vehicleid][vehintid] = 0;
	vehData[vehicleid][vehvwid] = 0;	
	
	// Copy vehicle data to new variable
	new copyData[E_VEH_DATA];
		
	for (new i; E_VEH_DATA:i < E_VEH_DATA; i++) {
		copyData[E_VEH_DATA:i] = vehData[vehicleid][E_VEH_DATA:i];
	}
		
	veh_destroy(vehicleid);
		
	new newVehID = veh_create(copyData[vehmodelid], copyData[vehsx], copyData[vehsy], copyData[vehsz], copyData[vehsangle], copyData[vehcolor1], copyData[vehcolor2], -1, copyData[vehsintid], copyData[vehsvwid], VEH_TYPE_OWNVEH);

	// Pass spawn data to current data.
	copyData[vehintid] = copyData[vehsintid];
	copyData[vehvwid] = copyData[vehsvwid];
	
	if (newVehID == INVALID_VEHICLE_ID)
		return;
		
	for (new i; E_VEH_DATA:i < E_VEH_DATA; i++) {
		vehData[newVehID][E_VEH_DATA:i] = copyData[E_VEH_DATA:i];
	}
	
	if (copyData[vehpaintjob]) {
		ChangeVehiclePaintjob(newVehID, copyData[vehpaintjob] - 1);
	}
	
	for (new j; j < E_MAX_COMPONENTS; j++) {
		if (copyData[vehmods][j] >= 1000) {
			AddVehicleComponent(newVehID, copyData[vehmods][j]);
		}
	}
	
	if (vehicleid != newVehID) {
		if (copyData[vehtype] == VEH_TYPE_OWNVEH) {
			foreach(ownVeh, i) {
				if (ownVehData[i][ownSID] == vehicleid) {
					//veh_debug("change_id(%d | %d)", ownVehData[i][ownSID], newVehID);
					ownVehData[i][ownSID] = newVehID;
				}
			}
		}
		vehicleid = newVehID;
	}

	if (copyData[vehbools] & OPTION_CLOSE_ON_SPAWN) {
		veh_setDoors(newVehID, true);
	}
		
	CallLocalFunction("veh_onRespawn", "i", newVehID);
	
	vehData[newVehID][vehlastspawn] = gettime();
	
	//veh_debug("veh_appySpawnInfo(vehicleid: %d | newVehID: %d | time: %dms)", vehicleid, newVehID, resultTime);
}
stock veh_setPlate(vehicleid, plate) {
	if (!IsValidVehicle(vehicleid)) return;
	
	vehData[vehicleid][vehplate] = plate;
}
stock veh_getPlate(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return 0;
	
	return vehData[vehicleid][vehplate];
}
stock veh_getPlateAsString(vehicleid) {
	new
		string[11];
	if (!IsValidVehicle(vehicleid)) {
		string = "00 000-000";
	}
	else {
		format(string, sizeof(string), "%08x", veh_getPlate(vehicleid));

		strins(string, "-", 5, sizeof(string));
		strins(string, " ", 2, sizeof(string));
		
	}
	return string;
}
stock ownVeh:veh_ownVehID(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return INVALID_OWNVEH_ID;
	
	foreach(ownVeh, i) {
		if (ownVeh_ID(ownVeh:i) == vehicleid) {
			return ownVeh:i;
		}
	}
	return INVALID_OWNVEH_ID;
}
stock veh_setFuel(vehicleid, Float:fuel) {
	if (!IsValidVehicle(vehicleid)) return;
	
	vehData[vehicleid][vehfuel] = fuel;
}
stock Float:veh_getFuel(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return 0.0;
	
	return vehData[vehicleid][vehfuel];
}
stock veh_getMaxFuel(vehicleid) {
	return model_getMaxFuel(GetVehicleModel(vehicleid));
}
stock veh_refuel(vehicleid) {
	veh_setFuel(vehicleid, veh_getMaxFuel(vehicleid));
}
stock veh_putPlayerIn(vehicleid, playerid, seat) {
	//if (!IsValidVehicle(vehicleid)) return;
	
	SetPlayerInterior(playerid, veh_getInterior(vehicleid));
	SetPlayerVirtualWorld(playerid, veh_getVirtualWorld(vehicleid));
	
	PutPlayerInVehicle(playerid, vehicleid, seat);
}
stock veh_getName(vehicleid, dest[], size = sizeof(dest)) {
	return model_getName(GetVehicleModel(vehicleid), dest, size);
}
stock veh_getNameAsString(vehicleid) {
	new
		name[32];
		
	veh_getName(vehicleid, name, sizeof(name));
	return name;
}
stock veh_getMalSlots(vehicleid) {
	return model_getMalSlots(GetVehicleModel(vehicleid));
}
stock veh_getMaxSpeed(vehicleid) {
	return model_getMaxSpeed(GetVehicleModel(vehicleid));
}
stock veh_setPaintjob(vehicleid, paintjobid) {
	if (!IsValidVehicle(vehicleid)) return;
	
	ChangeVehiclePaintjob(vehicleid, paintjobid - 1);
	vehData[vehicleid][vehpaintjob] = paintjobid;
}
stock veh_getPaintjob(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return -1;
	
	return vehData[vehicleid][vehpaintjob];
}
stock veh_addComponent(vehicleid, componentid, bool:remove = false) {
	if (!IsValidVehicle(vehicleid)) return;
	
	if (remove) {
		RemoveVehicleComponent(vehicleid, componentid);
	}
	else {
		AddVehicleComponent(vehicleid, componentid);
	}
	
	vehData[vehicleid][vehmods][GetVehicleComponentType(componentid)] = !remove ? componentid : 0;
}

//Spawn functions
stock veh_getSpawnInfo(vehicleid, &Float:x=0.0, &Float:y=0.0, &Float:z=0.0, &Float:angle=0.0, &intid=0, &vwid=0) {
	if (!IsValidVehicle(vehicleid)) return;

	x = vehData[vehicleid][vehsx];
	y = vehData[vehicleid][vehsy];
	z = vehData[vehicleid][vehsz];
	angle = vehData[vehicleid][vehsangle];
	intid = vehData[vehicleid][vehsintid];
	vwid = vehData[vehicleid][vehsvwid];
}
stock veh_setSpawnInfo(vehicleid, Float:x, Float:y, Float:z, Float:angle, intid, vwid) {
	if (!IsValidVehicle(vehicleid)) return;
	
	vehData[vehicleid][vehsx] = x;
	vehData[vehicleid][vehsy] = y;
	vehData[vehicleid][vehsz] = z;
	vehData[vehicleid][vehsangle] = angle;
	vehData[vehicleid][vehsintid] = intid;
	vehData[vehicleid][vehsvwid] = vwid;
}
stock veh_setSpawnInterior(vehicleid, intid) {
	if (!IsValidVehicle(vehicleid)) return;
	
	vehData[vehicleid][vehsintid] = intid;
}
stock veh_getSpawnInterior(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return -1;
	
	return vehData[vehicleid][vehsintid];
}
stock veh_setSpawnVirtualWorld(vehicleid, vwid) {
	if (!IsValidVehicle(vehicleid)) return;
	
	vehData[vehicleid][vehsvwid] = vwid;
}
stock veh_getSpawnVirtualWorld(vehicleid) {

	if (!IsValidVehicle(vehicleid)) return -1;
	
	return vehData[vehicleid][vehsvwid];
}
stock veh_setExtra1(vehicleid, value) {
	if (!IsValidVehicle(vehicleid)) return;
	
	vehData[vehicleid][vehextra1] = value;
}
stock veh_getExtra1(vehicleid) {

	if (!IsValidVehicle(vehicleid)) return -1;
	
	return vehData[vehicleid][vehextra1];
}
stock veh_isOwnVeh(vehicleid) {
	return veh_getType(vehicleid) == VEH_TYPE_OWNVEH;
}
stock veh_isSellVeh(vehicleid) {
	return veh_getType(vehicleid) == VEH_TYPE_SELLVEH;
}
stock veh_getBoot(vehicleid) {
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return boot == 1;
}
stock veh_setBoot(vehicleid, boot) {
	new engine, lights, alarm, doors, bonnet, E_NaN, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, E_NaN, objective);
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
}
stock veh_getEngine(vehicleid) {
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return engine == 1;
}
stock veh_setEngine(vehicleid, engine) {
	new E_NaN, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, E_NaN, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
}
stock veh_getBonnet(vehicleid) {
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return bonnet == 1;
}
stock veh_setBonnet(vehicleid, bonnet) {
	new engine, lights, alarm, doors, E_NaN, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, E_NaN, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
}
stock veh_getLights(vehicleid) {
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return lights == 1;
}
stock veh_setLights(vehicleid, lights) {
	new engine, E_NaN, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, E_NaN, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
}
stock veh_getDoors(vehicleid) {
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return doors == 1;
}
stock veh_setDoors(vehicleid, doors) {
	new engine, lights, alarm, E_NaN, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, E_NaN, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	
	if (veh_isOwnVeh(vehicleid)) {
		
		veh_toggleOption(vehicleid, OPTION_CLOSE_ON_SPAWN, doors);
		
	}
}
stock veh_respawn(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return 0;
	
	vehData[vehicleid][vehlastspawn] = gettime();
	SetVehicleToRespawn(vehicleid);
	return 1;
}
stock veh_getLastSpawn(vehicleid) {
	if (!IsValidVehicle(vehicleid)) return 0;
	
	return vehData[vehicleid][vehlastspawn];
}
stock veh_isDestroyed(vehicleid) {
	return veh_getVirtualWorld(vehicleid) == E_VEH_DESTROYED_VW;
}
stock veh_plateToStr(plate) {
	new
		string[11] = "00 000-000";

	format(string, sizeof(string), "%08x", plate);

	strins(string, "-", 5, sizeof(string));
	strins(string, " ", 2, sizeof(string));
	return string;
}

stock veh_strToPlate(plate[]) {
	
	// FORMATO: XX XXX-XXX
	
	new 
		len = strlen(plate);
		
	if (len != 10) return -1;
	
	new
		dest[11];
		
	store(dest, plate, sizeof(dest));

	for (new i; i < len; i++) {
		if ((dest[i] == ' ' && i == 2) || (dest[i] == '-' && i == 5)) {
			for (new a = i; a < len; a++) {
				dest[a] = dest[a+1];
			}
			len--;
			continue;
		}
		switch (dest[i]) {
			case '0' .. '9', 'A' .. 'F', 'a' .. 'f': continue;
			default: return -1;
		}
	}
	return strhex(dest);
}

//@ownVeh
forward ownVeh:ownVeh_create(UID, owner[], modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, intid, vwid, bools);
public ownVeh:ownVeh_create(UID, owner[], modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, intid, vwid, bools) {

	new ret = Iter_Free(ownVeh);
	
	if (ret == -1)	{
		return INVALID_OWNVEH_ID;
	}
	
	new vehID = veh_create(modelid, x, y, z, angle, color1, color2, -1, intid, vwid, VEH_TYPE_OWNVEH, bools);
	
	if (vehID != INVALID_VEHICLE_ID) {
	
		ownVehData[ret][ownSID] = vehID;
		ownVehData[ret][ownUID] = UID;
		
		veh_setOwner(vehID, owner);
		
		veh_setPlate(vehID, UID);
		
		Iter_Add(ownVeh, ret);
		
		//veh_debug ("ownVeh_create(UID:%d, model:%d, sid:%d)", UID, modelid, ownVehData[ret][ownSID]);

		return ownVeh:ret;
	}
	return INVALID_OWNVEH_ID;
}
stock ownVeh_remove(ownVeh: ID) {

	if (ownVeh_isValid(ID)) {
	
		// Veh clear
		veh_destroy(ownVeh_ID(ID));
		
		// mem clear
		for (new i = 0; E_OWNVEH_DATA:i < E_OWNVEH_DATA; i++) {
			ownVehData[ID][E_OWNVEH_DATA:i] = ownVeh: 0;
		}
		Iter_Remove(ownVeh, _:ID);
		
		return true;
	}
	return false;
}
stock ownVeh_isValid(ownVeh: ID) {
	return Iter_Contains(ownVeh, _:ID);
}
stock ownVeh_genUID() {
	return 1 + random(0xFFFFFFFF-1);
}
stock ownVeh_getUID(ownVeh: ID) {
	if (!ownVeh_isValid(ID)) return 0;
	
	return ownVehData[ID][ownUID];
}
stock ownVeh_ID(ownVeh: ID) {
	if (!ownVeh_isValid(ID)) return INVALID_VEHICLE_ID;
	
	return ownVehData[ID][ownSID];
}
stock ownVeh_setWaitTime(ownVeh: ID, value) {
	if (!ownVeh_isValid(ID)) return;
	
	ownVehData[ID][ownwaittime] = value;
	//veh_debug("setWaitTime(%d)", value);
}
stock ownVeh_getWaitTime(ownVeh: ID) {
	if (!ownVeh_isValid(ID)) return 0;
	
	return ownVehData[ID][ownwaittime];
}
stock ownVeh_setSpawnTime(ownVeh: ID, value) {
	if (!ownVeh_isValid(ID)) return;
	
	ownVehData[ID][ownspawntime] = value;
	//veh_debug("setWaitTime(%d)", value);
}
stock ownVeh_getSpawnTime(ownVeh: ID) {
	if (!ownVeh_isValid(ID)) return 0;
	
	return ownVehData[ID][ownspawntime];
}

stock ownVeh_processSecond() {
	ownVeh_loop(ownVeh: i) {
		if (ownVeh_getSpawnTime(i)) {
			ownVeh_setSpawnTime(i, ownVeh_getSpawnTime(i) + 1);
			
			if (ownVeh_getSpawnTime(i) > E_VEH_DESTROYED_TIME && veh_getVirtualWorld(ownVeh_ID(i)) == E_VEH_DESTROYED_VW) {
				
				veh_setVirtualWorld(ownVeh_ID(i), veh_getSpawnVirtualWorld(ownVeh_ID(i)));
			}	
		}
		if (ownVeh_getWaitTime(i)) {
			ownVeh_setWaitTime(i, ownVeh_getWaitTime(i) + 1);
			
			if (ownVeh_getWaitTime(i) > E_VEH_WAITTIME) {
			
				new 
					bool: playersIn,
					vehicleID = ownVeh_ID(i);
				
				foreach(Player, p) {
					if (GetPlayerVehicleID(p) == vehicleID) {
						playersIn = true;
						break;
					}
				}
				if (!playersIn) {
					ownVeh_remove(i);
				}
				else {
					ownVeh_setWaitTime(i, ownVeh_getWaitTime(i) - E_VEH_WAITTIME_ADD);
				}
			}
		}
	}
}
stock ownVeh_getOwner(ownVeh: ID, owner[], size = sizeof(owner)) {
	if (ownVeh_isValid(ID)) {

		store(owner, veh_getOwnerAsString(ownVeh_ID(ID)), size);
		return 1;
	}
	return 0;
}
stock ownVeh_getOwnerAsString(ownVeh: ID) {
	new
		owner[MAX_PLAYER_NAME] = "Nadie";

	ownVeh_getOwner(ID, owner, sizeof(owner));
	return owner;
}
stock ownVeh_addComponent(ownVeh: ID, componentid, bool:remove = false) {
	new
		varName[12];
		
	format(varName, sizeof(varName), "mod_%d", GetVehicleComponentType(componentid));
	ownVeh_MySQL_updateInt(ID, varName, !remove ? componentid : 0);
}

//MySQL
stock ownVeh_MySQL_insert(ownVeh: ID, callback[]="", extraID=0) {
	if (!ownVeh_isValid(ID)) return;

	new
		querystr[512];
		
	new
		vehID = ownVeh_ID(ID),
		modelid = veh_getModelID(vehID),
		Float:x,
		Float:y,
		Float:z,
		Float:angle,
		intid,
		vwid,
		color1,
		color2;
		
	veh_getSpawnInfo(vehID, x, y, z, angle, intid, vwid);
	veh_getColor(vehID, color1, color2);
	
	format(querystr, sizeof(querystr), "INSERT INTO Vehiculos (`UID`,`Owner`,`modelid`,`x`,`y`,`z`,`angle`,`intid`,`vwid`,`color1`,`color2`) VALUES \
															  (%d,'%s',%d,%f,%f,%f,%f,%d,%d,%d,%d)",
															  ownVehData[ID][ownUID],
															  veh_getOwnerAsString(vehID),
															  modelid,
															  x,
															  y,
															  z,
															  angle,
															  intid,
															  vwid,
															  color1,
															  color2);
															  
	opmysql_pquery(querystr, callback, "i", extraID);
	//veh_debug(querystr);
}
stock ownVeh_MySQL_update(ownVeh: ID, callback[]="", extraID=0) {

	if (!ownVeh_isValid(ID)) return;

	new
		querystr[512];
		
	new
		vehID = ownVeh_ID(ID),
		Float:x,
		Float:y,
		Float:z,
		Float:angle,
		intid,
		vwid,
		color1,
		color2;
		
	veh_getSpawnInfo(vehID, x, y, z, angle, intid, vwid);
	veh_getColor(vehID, color1, color2);

	
	format(querystr, sizeof(querystr), "UPDATE Vehiculos SET `x`=%f,`y`=%f,`z`=%f,`angle`=%f,`intid`=%d,`vwid`=%d,`color1`=%d,`color2`=%d WHERE `UID`=%d",
															  x,
															  y,
															  z,
															  angle,
															  intid,
															  vwid,
															  color1,
															  color2,															  
															  ownVehData[ID][ownUID]);
															  
	opmysql_pquery(querystr, callback, "i", extraID);
	//veh_debug(querystr);
}
stock ownVeh_MySQL_updateString(ownVeh: ID, variable[], value[], callback[]="", extraID=0) {

	if (!ownVeh_isValid(ID)) return;

	new
		querystr[155];
		

	opmysql_format(querystr, sizeof(querystr), "UPDATE Vehiculos SET `%s`='%e' WHERE UID=%d", variable, value, ownVehData[ID][ownUID]);
	opmysql_pquery(querystr, callback, "i", extraID);
	//veh_debug(querystr);
}
stock ownVeh_MySQL_updateInt(ownVeh: ID, variable[], value, callback[]="", extraID=0) {

	if (!ownVeh_isValid(ID)) return;

	new
		querystr[138];
		
	opmysql_format(querystr, sizeof(querystr), "UPDATE Vehiculos SET `%s`=%d WHERE UID=%d", variable, value, ownVehData[ID][ownUID]);
	opmysql_pquery(querystr, callback, "i", extraID);
	//veh_debug(querystr);
}
stock ownVeh_MySQL_updateFloat(ownVeh: ID, variable[], Float:value, callback[]="", extraID=0) {

	if (!ownVeh_isValid(ID)) return;

	new
		querystr[138];
		

	opmysql_format(querystr, sizeof(querystr), "UPDATE Vehiculos SET `%s`=%f WHERE UID=%d", variable, value, ownVehData[ID][ownUID]);
	opmysql_pquery(querystr, callback, "i", extraID);
	//veh_debug(querystr);
}
stock ownVeh_MySQL_load_owner(owner[], callback[]="", extraID=0) {
	
	new
		querystr[128];
		
	format(querystr, sizeof(querystr), "SELECT * FROM Vehiculos WHERE Owner = '%s'", owner); 
	opmysql_pquery(querystr, callback, "i", extraID);
}
stock ownVeh_MySQL_load_UID(UID, callback[]="", extraID=0) {
	
	new
		querystr[100];
		
	format(querystr, sizeof(querystr), "SELECT * FROM Vehiculos WHERE UID = %d", UID); 
	opmysql_pquery(querystr, callback, "i", extraID);
}
stock ownVeh_MySQL_remove(ownVeh: ID, callback[]="", extraID=0) {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
	if (!ownVeh_isValid(ID)) return;

	new
		querystr[128];
		
	format(querystr, sizeof(querystr), "DELETE FROM Vehiculos WHERE `UID`=%d", ownVehData[ID][ownUID]);	
	opmysql_pquery(querystr, callback, "i", extraID);	
	//veh_debug(querystr);
}

//model
stock model_isValid(modelid) {
	return (400 <= modelid < E_MAX_MODEL);
}
stock model_getName(modelid, dest[], size = sizeof(dest)) {
	if (!model_isValid(modelid)) return 0;

	strunpack(dest, modelData[modelid-400][modelname], size);
	return 1;
}
stock model_getNameAsString(modelid) {
	new
		name[32];
		
	model_getName(modelid, name, sizeof(name));
	return name;
}
stock model_getMaxFuel(modelid) {
	if (!model_isValid(modelid)) return 0;
	
	return modelData[modelid-400][modelmaxfuel];
}
stock model_getMalSlots(modelid) {

	if (!model_isValid(modelid)) return 0;
	
	return modelData[modelid-400][modelmalslots];
}
stock model_getMaxSpeed(modelid) {
	if (!model_isValid(modelid)) return 0;
	
	return modelData[modelid-400][modelmaxspeed];
}
stock model_size() {
	return sizeof(modelData);
}

//sellveh
stock sellVeh_create(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, intid, vwid) {

	new vehID = veh_create(modelid, x, y, z, angle, color1, color2, -1, intid, vwid, VEH_TYPE_SELLVEH);
	return vehID;
}
stock sellVeh_destroy(vehicleid) {
	if (veh_getType(vehicleid) == VEH_TYPE_SELLVEH) {
		veh_destroy(vehicleid);
		return true;
	}
	return false;
}
stock sellVeh_updateFile() {
	new
		File:Arch = fopen(sellVeh_path, io_write),
		string[90];
		
	foreach(veh, i) {
		if (veh_getType(i) == VEH_TYPE_SELLVEH) {
			new
				modelid = veh_getModelID(i),
				Float:x,
				Float:y,
				Float:z,
				Float:angle,
				color1,
				color2,
				intid,
				vwid;
				
			veh_getSpawnInfo(i, x, y, z, angle, intid, vwid);
			veh_getColor(i, color1, color2);
			
			format(string, sizeof(string), "%d|%f|%f|%f|%f|%d|%d|%d|%d\n", modelid, x, y, z, angle, color1, color2, intid, vwid);
			fwrite(Arch, string);
		}
	}
	fclose(Arch);
}
stock sellVeh_loadFile() {

	if (!fexist(sellVeh_path)) return;
	
	new
		File:Arch = fopen(sellVeh_path, io_read),
		string[90];
		
	while (fread(Arch, string)) {
		new
			modelid,
			Float:x,
			Float:y,
			Float:z,
			Float:angle,
			color1,
			color2,
			intid,
			vwid;
			
		sscanf(string, "p<|>dffffiiii", modelid, x, y, z, angle, color1, color2, intid, vwid);
		sellVeh_create(modelid, x, y, z, angle, color1, color2, intid, vwid);
	}
	fclose(Arch);
}


