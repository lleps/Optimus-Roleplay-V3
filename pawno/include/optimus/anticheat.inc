/*
*
*
*             OP_Anticheat.inc - Optimus RolePlay anticheat
*
*                                     			Created by Spell.
*/

//  *Version
#define ANTIC_VERSION                       (12)

//  *Macros
#define ANTIC::%0(%1)						forward antic_%0(%1); public antic_%0(%1)
#define A_Format(%1,						format(%1,sizeof(%1),
#define VarAntic(%0)<%1>   					antic_pInfo[%0][antic_%1]

//  *Warn
#define ResetWarns(%0,%1)                	antic_pInfo[%0][antic_Warn][antic_%1] = 0
#define AddWarn(%0,%1)                		antic_pInfo[%0][antic_Warn][antic_%1] ++
#define GetWarns(%0,%1)                		(antic_pInfo[%0][antic_Warn][antic_%1])

//  *Sync
#define Sync(%0,%1)							antic_pInfo[%0][antic_Sync] |= sync_%1
#define Unsync(%0,%1)						antic_pInfo[%0][antic_Sync] &= ~sync_%1
#define IsSynced(%0,%1)						(antic_pInfo[%0][antic_Sync] & sync_%1)

#define SYNC_RESYNC                         (8)
#define SYNC_TOO                            (18)

#define ResetSyncTime(%0,%1)                antic_pInfo[%0][antic_Time][antic_%1] = 0
#define AddSyncTime(%0,%1)                	antic_pInfo[%0][antic_Time][antic_%1] ++
#define GetSyncTime(%0,%1)                	(antic_pInfo[%0][antic_Time][antic_%1])

//  *Config
#define MAX_PING                            700
#define MAX_WARNS_INFINITEAMMO              3

#define TOO_DISTANCE_ONFOOT_WARN            30.0
#define TOO_DISTANCE_ONFOOT_KICK            250.0
#define TOO_DISTANCE_ONFOOT_BAN            	800.0

#define TOO_DISTANCE_DRIVER_WARN            60.0
#define TOO_DISTANCE_DRIVER_KICK            250.0
#define TOO_DISTANCE_DRIVER_BAN            	800.0

#define HORAS_RVEH 							(3600*6)
#define INMUNE_ADMIN                        (59)

//  *Data
static const Float: CheatPositions [][3] =
{
	{-1935.77, 228.79, 34.16}, //Transfender near Wang Cars in Doherty
	{-2707.48, 218.65, 4.93}, //Wheel Archangels in Ocean Flats
	{2645.61, -2029.15, 14.28}, //LowRider Tuning Garage in Willowfield
	{1041.26, -1036.77, 32.48}, //Transfender in Temple
	{2387.55, 1035.70, 11.56}, //Transfender in come-a-lot
	{1836.93, -1856.28, 14.13}, //Eight Ball Autos near El Corona
	{2006.11, 2292.87, 11.57}, //Welding Wedding Bomb-workshop in Emerald Isle
	{-1787.25, 1202.00, 25.84}, //Michelles Pay 'n' Spray in Downtown
	{720.10, -470.93, 17.07}, //Pay 'n' Spray in Dillimore
	{-1420.21, 2599.45, 56.43}, //Pay 'n' Spray in El Quebrados
	{-100.16, 1100.79, 20.34}, //Pay 'n' Spray in Fort Carson
	{2078.44, -1831.44, 14.13}, //Pay 'n' Spray in Idlewood
	{-2426.89, 1036.61, 51.14}, //Pay 'n' Spray in Juniper Hollow
	{1957.96, 2161.96, 11.56}, //Pay 'n' Spray in Redsands East
	{488.29, -1724.85, 12.01}, //Pay 'n' Spray in Santa Maria Beach
	{1025.08, -1037.28, 32.28}, //Pay 'n' Spray in Temple
	{2393.70, 1472.80, 11.42}, //Pay 'n' Spray near Royal Casino
	{-1904.97, 268.51, 41.04}, //Pay 'n' Spray near Wang Cars in Doherty
	{403.58, 2486.33, 17.23}, //Player Garage: Verdant Meadows
	{1578.24, 1245.20, 11.57}, //Player Garage: Las Venturas Airport
	{-2105.79, 905.11, 77.07}, //Player Garage: Calton Heights
	{423.69, 2545.99, 17.07}, //Player Garage: Derdant Meadows
	{785.79, -513.12, 17.44}, //Player Garage: Dillimore
	{-2027.34, 141.02, 29.57}, //Player Garage: Doherty
	{1698.10, -2095.88, 14.29}, //Player Garage: El Corona
	{-361.10, 1185.23, 20.49}, //Player Garage: Fort Carson
	{-2463.27, -124.86, 26.41}, //Player Garage: Hashbury
	{2505.64, -1683.72, 14.25}, //Player Garage: Johnson House
	{1350.76, -615.56, 109.88}, //Player Garage: Mulholland
	{2231.64, 156.93, 27.63}, //Player Garage: Palomino Creek
	{-2695.51, 810.70, 50.57}, //Player Garage: Paradiso
	{1293.61, 2529.54, 11.42}, //Player Garage: Prickle Pine
	{1401.34, 1903.08, 11.99}, //Player Garage: Redland West
	{2436.50, 698.43, 11.60}, //Player Garage: Rockshore West
	{322.65, -1780.30, 5.55}, //Player Garage: Santa Maria Beach
	{917.46, 2012.14, 11.65}, //Player Garage: Whitewood Estates
	{1641.14, -1526.87, 14.30}, //Commerce Region Loading Bay
	{-1617.58, 688.69, -4.50}, //San Fierro Police Garage
	{837.05, -1101.93, 23.98}, //Los Santos Cemetery
	{2338.32, -1180.61, 1027.98}, //Interior: Burning Desire House
	{-975.5766, 1061.1312, 1345.6719}, //Interior: RC Zero's Battlefield
	{-750.80, 491.00, 1371.70}, //Interior: Liberty City
	{-1400.2138, 106.8926, 1032.2779}, //Interior: Unknown Stadium
	{-2015.6638, 147.2069, 29.3127}, //Interior: Secret San Fierro Chunk
	{2220.26, -1148.01, 1025.80}, //Interior: Jefferson Motel
	{-2660.6185, 1426.8320, 907.3626}, //Interior: Jizzy's Pleasure Dome
	{-1394.20, 987.62, 1023.96}, //Stadium: Bloodbowl
	{-1410.72, 1591.16, 1052.53}, //Stadium: Kickstart
	{-1417.8720, -276.4260, 1051.1910}, //Stadium: 8-Track Stadium
	{-25.8844, -185.8689, 1003.5499}, //24/7 Store: Big-L-Shaped
	{6.0911, -29.2718, 1003.5499}, //24/7 Store: Big-Oblong
	{-30.9469, -89.6095, 1003.5499}, //24/7 Store: Med-Square
	{-25.1329, -139.0669, 1003.5499}, //24/7 Store: Med-Square
	{-27.3123, -29.2775, 1003.5499}, //24/7 Store: Sml-Long
	{-26.6915, -55.7148, 1003.5499}, //24/7 Store: Sml-Square
	{-1827.1473, 7.2074, 1061.1435}, //Airport: Ticket Sales
	{-1855.5687, 41.2631, 1061.1435}, //Airport: Baggage Claim
	{2.3848, 33.1033, 1199.8499}, //Airplane: Shamal Cabin
	{315.8561, 1024.4964, 1949.7973}, //Airplane: Andromada Cargo hold
	{2536.08, -1632.98, 13.79}, // Grove Street
	{1992.93, 1047.31, 10.82}, //Four Dragons Casino
	{2033.00, -1416.02, 16.99}, // LS Hospital
	{-2653.11, 634.78, 14.45}, // SF Hospital
	{1580.22, 1768.93, 10.82}, //LV Hospital
	{-1550.73, 99.29, 17.33}, //SF Export
 	{-2057.8000, 229.9000, 35.6204}, // San Fierro
 	{-2366.0000, -1667.4000, 484.1011}, // Mount Chiliad
 	{2503.7000, -1705.8000, 13.5480}, // Grove Street
 	{1997.9000, 1056.3000, 10.8203}, // Las Venturas
 	{-2872.7000, 2712.6001, 275.2690}, // BaySide
 	{904.1000, 608.0000, -32.3281}, // Unterwasser
 	{-236.9000, 2663.8000, 73.6513} // The big Cock
};

// Sync
enum (<<= 1)
{
	sync_Pos = 1,
	sync_Health = 2,
	sync_Armour = 4,
	sync_VehicleHP,
	sync_VehicleID,
	sync_ResetedWeapons,
	sync_WeaponID,
	sync_NoWeapon
};

enum antic_timeData
{
	antic_Pos,
	antic_Health,
	antic_Armour,
	antic_VehicleID
};

// Warn
enum antic_warnData
{
	antic_Ping,
	antic_InfiniteAmmo
};

// Bools
enum (<<= 1)
{
	antic_JetPack = 1,
	antic_Spawned = 2,
	antic_Parachute
}

enum antic_playerData
{
	//Syncing
	antic_Sync,
	
	//Warn
	antic_Warn[antic_warnData],
	
	//Time
	antic_Time[antic_timeData],

	//Bools
	antic_Bools,

	//Money
	antic_Money,
	
	//Health & Armour
	Float: antic_Health,
	Float: antic_Armour,
	
	//Pos
	Float: antic_Pos_x,
	Float: antic_Pos_y,
	Float: antic_Pos_z,
	
	//Vehicle
	antic_VehicleID,
	Float: antic_VehicleHP,
	
	//Tick
	antic_FallingTick,
	antic_PutTick
};

new
	antic_pInfo [MAX_PLAYERS]  [antic_playerData],
	WeaponTime [MAX_PLAYERS],
	bool: DisabledACWarn[MAX_PLAYERS];

new BanWeaps[] =
{
	4, 9, 35, 36, 37, 38, 39
};

timer antic_Timer1000ms[1000]()
{
	foreach (Player, i)
	{
	    antic_Check_1000ms(i);
	}
	return 1;
}

timer antic_Timer500ms[490]()
{
	new
		gtc = GetTickCount();

	foreach (Player, i)
	{
	    antic_Check_500ms(i, gtc);
	}
	return 1;
}

//  *Callback
public OnGameModeInit()
{
	repeat antic_Timer1000ms();
	repeat antic_Timer500ms();
	
	return acCB_OnGameModeInit(); // Fuck you hooks :)
}

forward acCB_OnGameModeInit();

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit acCB_OnGameModeInit

public OnIncomingConnection(playerid, ip_address[], port)
{
	// Connection flood
	#define MAX_CONNECTION_CHECK (10)
	
	static
		lastipconnection[32],
		lasttimeconnection;

 
	if (gettime() - lasttimeconnection < 4) {

		if (!strcmp(ip_address, lastipconnection)) {
		
			// Connection flood (same ip connected in 3 seconds)
			BlockIpAddress(ip_address, 60 * 1000 * 5); // 5 mins
			printf("IP %s bloqueada por connectionflood.", ip_address);
		}
	}
	
	store(lastipconnection, ip_address, sizeof(lastipconnection));
	lasttimeconnection = gettime();
	return 1;
}

public OnPlayerConnect(playerid)
{
	for(new i = 0; i < sizeof (antic_pInfo[]); i++)
	{
	    antic_pInfo[playerid][antic_playerData:i] = 0;
	}

	Sync(playerid,Pos);
	Sync(playerid,Health);
	Sync(playerid,Armour);
	Sync(playerid,VehicleHP);
	Sync(playerid,VehicleID);
	
	WeaponTime[playerid] = 6;
	DisabledACWarn[playerid] = false;
	return acCB_OnPlayerConnect(playerid);
}

forward acCB_OnPlayerConnect(playerid);

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect acCB_OnPlayerConnect

public OnPlayerSpawn(playerid)
{
	VarAntic(playerid)<Bools> |= antic_Spawned;

	GetPlayerPos (playerid, VarAntic(playerid)<Pos_x>, VarAntic(playerid)<Pos_y>, VarAntic(playerid)<Pos_z>);
	Sync(playerid,Pos);
	
	VarAntic(playerid)<Health> = 100.0;
	Sync(playerid,Health);

	VarAntic(playerid)<Armour> = 0.0;
	Sync(playerid,Armour);

	VarAntic(playerid)<VehicleID> = 0;
	Sync(playerid,VehicleID);

	VarAntic(playerid)<VehicleHP> = 0.0;
	Sync(playerid,VehicleHP);
	
	WeaponTime [playerid] = 6;
	
	VarAntic(playerid)<FallingTick> = GetTickCount();
	return acCB_OnPlayerSpawn(playerid);
}

forward acCB_OnPlayerSpawn(playerid);

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn acCB_OnPlayerSpawn

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
		new
			VehID = GetPlayerVehicleID (playerid),
			Float: health;
			
		switch (GetVehicleModel (VehID))
		{
   			case 592,577,511,512,520,593,553,476,519,460,513,548,425,417,487,488,497,563,447,469:
   			{
			   VarAntic(playerid)<Bools> |= antic_Parachute;
			}
		}
		VarAntic(playerid)<VehicleID> = VehID;
		Sync(playerid,VehicleID);
		GetVehicleHealth (VehID, health);
		if (health > 1000.0)
		{
		    antic_SetVehicleHealth (VehID, 1000.0);
		}
		else
		{
			VarAntic(playerid)<VehicleHP> = health;
			Sync(playerid,VehicleHP);
		}
	}
	else if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	{
		VarAntic(playerid)<VehicleHP> = 0.0;
		Sync(playerid,VehicleHP);
		
		VarAntic(playerid)<VehicleID> = 0;
		Sync(playerid,VehicleID);
	}
	
	if (oldstate == PLAYER_STATE_PASSENGER)
	{
		GetPlayerPos (playerid, VarAntic(playerid)<Pos_x>, VarAntic(playerid)<Pos_y>, VarAntic(playerid)<Pos_z>);
	}
	return acCB_OnPlayerStateChange(playerid, newstate, oldstate);
}

forward acCB_OnPlayerStateChange(playerid, newstate, oldstate);

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange acCB_OnPlayerStateChange

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	new
		Float:old_x,
		Float:old_y,
		Float:old_z;
	
    GetVehiclePos(vehicleid, old_x, old_y, old_z);
	
	if (VectorSize(old_x-new_x, old_y-new_y, old_z-new_z) > 2.0 || !IsPlayerInRangeOfPoint(playerid, 5.0, old_x, old_y, old_z)) {
		return 0;
	}

	return acCB_OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, new_x, new_y, new_z, vel_x, vel_y, vel_z);
}

forward acCB_OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z);

#if defined _ALS_OnUnoccupiedVehicleUpdate
	#undef OnUnoccupiedVehicleUpdate
#else
	#define _ALS_OnUnoccupiedVehicleUpdate
#endif

#define OnUnoccupiedVehicleUpdate acCB_OnUnoccupiedVehicleUpdate

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    if(hittype != BULLET_HIT_TYPE_NONE) {
        if( !( -1000.0 <= fX <= 1000.0 ) || !( -1000.0 <= fY <= 1000.0 ) || !( -1000.0 <= fZ <= 1000.0 ) ) {
            return 0; 
        }
    }
    return acCB_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, fX, fY, fZ);
}

forward acCB_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);

#if defined _ALS_OnPlayerWeaponShot
	#undef OnPlayerWeaponShot
#else
	#define _ALS_OnPlayerWeaponShot
#endif

#define OnPlayerWeaponShot acCB_OnPlayerWeaponShot

public OnPlayerUpdate(playerid)
{
	antic_SyncPlayer (playerid);
	
	if (IsSynced(playerid,VehicleID))
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
		    // Cleos y TP
		    new
		        VehID = GetPlayerVehicleID(playerid);

		    if (VarAntic(playerid)<VehicleID> != VehID)
		    {
    			antic_Kick(playerid, "Vehicle teleport");
    			return 0;
			}
			// Repair
			if (IsSynced(playerid,VehicleHP))
			{
				new
					Float: float_var;

				GetVehicleHealth(VehID, float_var);

				if(float_var == 1000.0 && (0.0 <= VarAntic(playerid)<VehicleHP> < 1000.0))
				{
				    new
				        str[40];

					A_Format(str, "Cheat de reparación (VH: %f)", VarAntic(playerid)<VehicleHP>);
					antic_Kick(playerid, str);
					SetVehicleHealth(VehID, VarAntic(playerid)<VehicleHP>);
					return 0;
				}
				else if (VarAntic(playerid)<VehicleHP> > float_var)
				{
				    CallLocalFunction ("OnPlayerCrashVehicle", "iiff", playerid, VehID, float_var, VarAntic(playerid)<VehicleHP>);
			    	VarAntic(playerid)<VehicleHP> = float_var;
				}
			}
		}
	}
	return acCB_OnPlayerUpdate(playerid);
}

forward acCB_OnPlayerUpdate(playerid);

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate acCB_OnPlayerUpdate

//  *Syncing
stock antic_SyncPlayer (playerid)
{
	// Pos
	if (!IsSynced(playerid,Pos))
	{
		if (IsPlayerInRangeOfPoint (playerid, 2.5, VarAntic(playerid)<Pos_x>, VarAntic(playerid)<Pos_y>, VarAntic(playerid)<Pos_z>))
		{
		    Sync(playerid,Pos);
		}
		else
		{
		    switch (GetSyncTime(playerid,Pos))
		    {
		        case SYNC_RESYNC: // Re-sync
		        {
		            SetPlayerPos(playerid, VarAntic(playerid)<Pos_x>, VarAntic(playerid)<Pos_y>, VarAntic(playerid)<Pos_z>);
					AddSyncTime(playerid,Pos);
				}
		        case SYNC_TOO: // Re-sync
				{
					antic_Unsynced (playerid, "SPP");
					return 1;
				}
			}
		}
	}

	// Health
	if (!IsSynced(playerid,Health))
	{
	    new
	        Float: health;

		GetPlayerHealth (playerid, health);
		if (health == VarAntic(playerid)<Health>)
		{
		    Sync(playerid,Health);
		}
		else
		{
		    switch (GetSyncTime(playerid,Health))
		    {
		        case SYNC_RESYNC: // Re-sync
		        {
		            SetPlayerHealth(playerid, VarAntic(playerid)<Health>);
		            AddSyncTime(playerid,Health);
				}
				case SYNC_TOO:
				{
					antic_Unsynced (playerid, "SPH");
					return 1;
				}
			}
		}
	}

	// Armour
	if (!IsSynced(playerid,Armour))
	{
	    new
	        Float: armour;

		GetPlayerArmour (playerid, armour);
		if (armour == VarAntic(playerid)<Armour>)
		{
		    Sync(playerid,Armour);
		}
		else
		{
		    switch (GetSyncTime(playerid,Armour))
		    {
		        case SYNC_RESYNC: // Re-sync
		        {
		            SetPlayerArmour(playerid, VarAntic(playerid)<Armour>);
		            AddSyncTime(playerid,Armour);
				}
				case SYNC_TOO:
				{
					antic_Unsynced (playerid, "SPA");
					return 1;
				}
			}
		}
	}

	// VehicleHP
	if (!IsSynced(playerid,VehicleHP))
	{
		if (GetPlayerState (playerid) == PLAYER_STATE_DRIVER)
		{
		    if (IsSynced(playerid,VehicleID) && GetPlayerVehicleID(playerid) == VarAntic(playerid)<VehicleID>)
			{
				new
		        	Float: health;

				GetVehicleHealth (GetPlayerVehicleID (playerid), health);

				if (health == VarAntic(playerid)<VehicleHP>)
				{
				    Sync(playerid,VehicleHP);
				}
			}
		}
	}
	
	//VehicleID
	if (!IsSynced(playerid,VehicleID))
	{
	    if (GetPlayerVehicleID (playerid) == VarAntic(playerid)<VehicleID>)
		{
		    Sync(playerid,VehicleID);
		}
		else
		{
		    switch (GetSyncTime(playerid,VehicleID))
		    {
		        case SYNC_RESYNC: // Re-sync
		        {
		            PutPlayerInVehicle(playerid, VarAntic(playerid)<VehicleID>, 0);
					AddSyncTime(playerid,VehicleID);
				}
				case SYNC_TOO:
				{
					antic_Unsynced (playerid, "PPIV");
					return 1;
				}
			}
		}
	}
	return 1;
}

//  *Checking
stock antic_Check_500ms(playerid, gtc)
{
	if (IsPlayerPaused (playerid))
	    return 0;

	// Airbreak, Teleport or speed hack. (Player moved too much distance in a few time)
	new
	    p_state = GetPlayerState (playerid);
	    
	if (p_state == PLAYER_STATE_ONFOOT)
	{
	    if (IsSynced(playerid,Pos))
	    {
		    new
		        Float: Distance = GetPlayerDistanceFromPoint (playerid, VarAntic(playerid)<Pos_x>, VarAntic(playerid)<Pos_y>, VarAntic(playerid)<Pos_z>);

			if (Distance > TOO_DISTANCE_ONFOOT_WARN)
			{
			    if (GetPlayerSurfingVehicleID (playerid) == INVALID_VEHICLE_ID)
			    {
					if ((gtc - VarAntic(playerid)<FallingTick>) > 7000 && GetPlayerSpecialAction (playerid) != SPECIAL_ACTION_USEJETPACK && (gtc - VarAntic(playerid)<PutTick>) > 7000)
					{
						if (Distance > TOO_DISTANCE_ONFOOT_BAN)
						{
						    if (antic_IsCheatPosition(playerid))
						    {
						        new
						            str[70],
									zone_n[40],
									Float:x, Float:y, Float:z;
									
								GetPlayerPos (playerid, x, y, z);
                                GetZoneNameAtCoord(x, y, zone_n);
								A_Format (str, "Cheat de teleport (%f:%s)", Distance, zone_n);
								antic_Ban (playerid, str);
								return 2;
							}
							else
							{
						        new
						            str[40];
								A_Format (str, "Cheat de teleport (c2:%f)", Distance);
								antic_Kick (playerid, str);
								return 2;
							}
						}
						if (Distance > TOO_DISTANCE_ONFOOT_KICK)
						{
					        new
					            str[40];
							A_Format (str, "Cheat de teleport (c1:%f)", Distance);
							antic_Kick (playerid, str);
							return 2;
						}
						new
						    str[144];
						    
						A_Format (str, "[ANTICHEAT] {ffffff}El jugador {00ff00}%s (ID: %d) {ffffff}recorrió {00ff00}%dmts{ffffff} en 0,5 segundos, posible cheat. ¡Spectear!", pName(playerid), playerid, floatround(Distance));
						antic_WarnMessage (0xFF000000, str);
					}
				}
			}
		    new
		        Float: x_s, Float: y_s, Float: z_s;

			GetPlayerVelocity (playerid, x_s, y_s, z_s);

			if (z_s < -0.2) // No está callendo
			{
				VarAntic(playerid)<FallingTick> = gtc;
			}
			GetPlayerPos (playerid, VarAntic(playerid)<Pos_x>, VarAntic(playerid)<Pos_y>, VarAntic(playerid)<Pos_z>);
		}
	}
	else if (p_state == PLAYER_STATE_DRIVER)
	{
	    if (IsSynced(playerid,Pos) && IsSynced(playerid,VehicleID))
	    {
		    new
		        Float: Distance = GetPlayerDistanceFromPoint (playerid, VarAntic(playerid)<Pos_x>, VarAntic(playerid)<Pos_y>, VarAntic(playerid)<Pos_z>);

			if (Distance > TOO_DISTANCE_DRIVER_WARN)
			{
				if ((gtc - VarAntic(playerid)<FallingTick>) > 7000 && (gtc - VarAntic(playerid)<PutTick>) > 7000)
				{
					if (Distance > TOO_DISTANCE_DRIVER_BAN)
					{
					    if (antic_IsCheatPosition(playerid))
					    {
					        new
					            str[70],
								zone_n[40],
								Float:x, Float:y, Float:z;
							GetPlayerPos (playerid, x, y, z);
                            GetZoneNameAtCoord(x, y, zone_n);
							A_Format (str, "Cheat de teleport (%f:%s)", Distance, zone_n);
							antic_Ban (playerid, str);
							return 2;
						}
						else
						{
					        new
					            str[40];
							A_Format (str, "Cheat de teleport (c2:%f)", Distance);
							antic_Kick (playerid, str);
							return 2;
						}
					}
					if (Distance > TOO_DISTANCE_DRIVER_KICK)
					{
				        new
				            str[40];
						A_Format (str, "Cheat de teleport (c1:%f)", Distance);
						antic_Kick (playerid, str);
						return 2;
					}
					new
					    str[144];
					A_Format (str, "[ANTICHEAT] {ffffff}El vehículo de {00ff00}%s (ID: %d) {ffffff}recorrió {00ff00}%dmts{ffffff} en 0,5 segundos, posible cheat. ¡Spectear!", pName(playerid), playerid, floatround(Distance));
					antic_WarnMessage (0xFF000000, str);
				}
			}
		    new
		        Float: x_s, Float: y_s, Float: z_s;

			GetVehicleVelocity (GetPlayerVehicleID (playerid), x_s, y_s, z_s);

			if (z_s < -0.2) // No está callendo
			{
				VarAntic(playerid)<FallingTick> = gtc;
			}
			GetPlayerPos (playerid, VarAntic(playerid)<Pos_x>, VarAntic(playerid)<Pos_y>, VarAntic(playerid)<Pos_z>);
		}
	}
	return 1;
}

stock antic_Check_1000ms(playerid)
{
	if (IsPlayerPaused (playerid))
	    return 0;

	new
		p_state = GetPlayerState (playerid),
		int_var;

	if (GetPlayerAdminLevelOP(playerid) >= INMUNE_ADMIN)
	    return 0;

	if (p_state == PLAYER_STATE_DRIVER || p_state == PLAYER_STATE_PASSENGER || p_state == PLAYER_STATE_ONFOOT)
	{
	    // Spawn desconocido
		if (!(VarAntic(playerid)<Bools> & antic_Spawned))
		{
		    antic_Kick (playerid, "Spawn desconocido.");
		    return 2;
		}

		// Sync time (Pos-VehicleID)
		if (!IsSynced(playerid,Pos))
		    AddSyncTime(playerid,Pos);
		    
		if (!IsSynced(playerid,VehicleID))
		    AddSyncTime(playerid,VehicleID);

		// Dinero
		if (GetPlayerMoney (playerid) != VarAntic(playerid)<Money>)
		{
		    ResetPlayerMoney (playerid);
		    GivePlayerMoney (playerid, VarAntic(playerid)<Money>);
		}
		
		// Vida y Chaleco
/*		if (IsSynced(playerid,Health))
		{
			GetPlayerHealth(playerid, float_var);

			if(float_var > VarAntic(playerid)<Health> > 0.0)
			{
				if (VarAntic(playerid)<Health> > 0.1)
				{
		    		SetPlayerHealth(playerid, VarAntic(playerid)<Health>);
				}
				else
				{
					VarAntic(playerid)<Health> = float_var;
				}
			}
		}
		else AddSyncTime(playerid,Health);
		
		if (IsSynced(playerid,Armour))
		{
			GetPlayerHealth(playerid, float_var);

			if(float_var > VarAntic(playerid)<Armour>)
			{
		    	SetPlayerHealth(playerid, VarAntic(playerid)<Armour>);
			}
		}
		else AddSyncTime(playerid,Armour);*/

		// Ping
		new
		    ping = GetPlayerPing(playerid);

		if(ping > MAX_PING && !(ping & 0xFFFF))
		{
		
		    AddWarn(playerid,Ping);
		    if(GetWarns(playerid,Ping) >= 15)
		    {
			    new
			        str[40];
				A_Format(str, "Ping excesivo (%dms/%dms)", ping, MAX_PING);
				antic_Kick(playerid, str);
				return 2;
			}
		}
		else
		{
			ResetWarns(playerid,Ping);
		}

		// Onfoot cheats
	    new
	        Float: x_s, Float: y_s, Float: z_s;

		GetPlayerVelocity (playerid, x_s, y_s, z_s);

		if (p_state == PLAYER_STATE_ONFOOT)
		{
			// GodOfCars
			int_var = GetPlayerAnimationIndex(playerid);

			if(z_s > 0.2 && int_var == 1132) // GodOfCars
			{
			    new
			        keys,
			        ud,
			        lr;
			        
				GetPlayerKeys (playerid, keys, ud, lr);
				
				if (keys & KEY_SPRINT)
				{
				    if (GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID)
				    {
					    antic_Ban(playerid, "Cleo mod (GOC)", 2);
					    return 2;
					}
				}
			}

			// Paracaidas (Flyhack)
			if(int_var == 1008 || int_var == 959)
			{
				if (x_s <= -0.8 || y_s <= -0.8 || z_s <= -0.8)
				{
			        antic_Kick(playerid, "Cheat de vuelo (p)");
			        return 2;
				}
			}

			// Jetpack
			if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK)
			{
			    if(!(VarAntic(playerid)<Bools> & antic_JetPack))
			    {
				    antic_Ban(playerid, "JetPack", 2);
				    return 2;
				}
			}
		}

		if(WeaponTime[playerid] == 0)
		{
		    int_var = GetPlayerWeapon(playerid);

		    if (int_var == 46 && !(VarAntic(playerid)<Bools> & antic_JetPack))
		    {
				antic_Ban (playerid, "Cheat (Paracaidas)", 2);
				return 2;
			}
			for(new Weap_ID; Weap_ID < sizeof(BanWeaps); Weap_ID++)
			{
	 			if(int_var == BanWeaps[Weap_ID])
	  			{
	  			    new
	  			        str[30];

					GetWeaponName(int_var, str, 30);
					format(str, 30, "Cheat de Armas [%s]", str);
					antic_Ban(playerid, str, 2);
					return 2;
				}
			}

			new
			    inv_weap = INV_GetWeapon(playerid);

			if (inv_weap)
			{
			    if (int_var > 0 && int_var != 46)
			    {
					if (int_var != inv_weap)
					{
					    new
					        str[35];

						format(str, sizeof(str), "Cheat de Armas (%d:%d)", inv_weap, int_var);
						antic_Kick(playerid, str);
						return 2;
					}
					else
					{
					    new
					        ammo = GetPlayerAmmo(playerid),
							maxa = GetWeaponAmmo(inv_weap);

						if(ammo < -1 || ammo > maxa)
						{
						    new
						        str[35];

							format(str, sizeof(str), "Cheat de munición (%d/%d)", ammo, maxa);
							antic_Ban(playerid, str, 2);
							return 2;
						}
					}
				}
			}
			else
			{
			    if (int_var > 0 && int_var != 46)
			    {
			    	new
				        str[35];

					format(str, sizeof(str), "Cheat de Armas (%d)", int_var);
					antic_Kick(playerid, str);
					return 2;
				}
			}
		}
		else
		{
		     WeaponTime[playerid] --;
		}
	}
	return 1;
}

//  *Utiles
stock antic_Kick(playerid, reason[], type = 1)
{
	return CallLocalFunction("KickPlayer", "issi", playerid, "el servidor", reason, type);
}

stock antic_Ban(playerid, reason[], type = 0)
{
	return CallLocalFunction("BanPlayer", "issi", playerid, "el servidor", reason, type);
}

stock antic_WarnMessage(color, message[])
{
	foreach (Player, i)
	{
	    if (GetPlayerAdminLevelOP(i) >= 24 && DisabledACWarn[i] == false)
	    {
	        SendClientMessage (i, color, message);
		}
	}
	return 1;
}

stock antic_Unsynced(playerid, function[])
{
	if (GetPVarInt (playerid, "antic_Unsynced."))
	    return 1;
	    
	SetPVarInt (playerid, "antic_Unsynced.", true);

	SendClientMessage (playerid, 0xFF000000, 	"Atención: {ffffff}Usted no está correctamente sincronizado con el servidor.");
	SendClientMessage (playerid, -1,     		"Esto puede deberse a mala conexión. Vuelva a ingresar y cierre todos los programas que usen internet.");
	SendClientMessage (playerid, -1,     		"Otra de las razones posibles, es que usted está utilizando mods externos o parches {ff0000}'NOP'");

	new
	    patch [100],
		Float: packetloss = antic_GetPlayerPacketLoss (playerid);

	A_Format (patch, "Porcentaje de paquetes perdidos: {ff0000}%.1f%\%", packetloss);
	SendClientMessage (playerid, -1, patch);

	format (patch, 50, "Desync (PL: %.1f\% - FUNC: %s)", packetloss, function);
	return CallLocalFunction("KickPlayer", "issi", playerid, "el servidor", patch, 0);
}

ANTIC::IsCheatPosition (playerid)//Extracted from JunkBuster
{
	for (new i = 0; i < sizeof (CheatPositions); ++i)
		if (IsPlayerInRangeOfPoint (playerid, 3.5, CheatPositions [i][0], CheatPositions [i][1], CheatPositions [i][2]))
			return true;
	return false;
}

forward Float: antic_GetPlayerPacketLoss (playerid);
public Float: antic_GetPlayerPacketLoss (playerid)
{
	new
		stats[400+1];

	GetPlayerNetworkStats(playerid, stats, sizeof(stats)); 

	new
	    pospercent = strfind (stats, "%"),
		var[10];

	strmid (var, stats, pospercent-5, pospercent-1);
	return floatstr (var);
}

stock GetWeaponSlot(weaponid)
{
	new slot;
	switch(weaponid)
	{
		case 0,1: slot = 0;
		case 2 .. 9: slot = 1;
		case 10 .. 15: slot = 10;
		case 16 .. 18, 39: slot = 8;
		case 22 .. 24: slot = 2;
		case 25 .. 27: slot = 3;
		case 28, 29, 32: slot = 4;
		case 30, 31: slot = 5;
		case 33, 34: slot = 6;
		case 35 .. 38: slot = 7;
		case 40: slot = 12;
		case 41 .. 43: slot = 9;
		case 44 .. 46: slot = 11;
	}
	return slot;
}

forward antic_CheckAMMO (playerid, ammo);
public antic_CheckAMMO (playerid, ammo)
{
	new
	    my_ammo = GetPlayerAmmo (playerid);
	    
	if (my_ammo == ammo)
	{
	    AddWarn(playerid,InfiniteAmmo);
	    
	    if (GetWarns(playerid,InfiniteAmmo) > MAX_WARNS_INFINITEAMMO)
	    {
			new
			    str[30];

			A_Format (str, "Munición infinita (W:%d, A:%d)", GetPlayerWeapon (playerid), ammo);
			antic_Ban (playerid, str);
		}
	}
	return 1;
}

//  *Hooks
ANTIC::ResetPlayerMoney(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		VarAntic(playerid)<Money> = 0;
		return 1;
	}
	return 0;
}

#if defined _ALS_ResetPlayerMoney
	#undef ResetPlayerMoney
#else
	#define _ALS_ResetPlayerMoney
#endif

#define ResetPlayerMoney antic_ResetPlayerMoney
// -========================================================================- //
ANTIC::GivePlayerMoney(playerid, money)
{
	if(IsPlayerConnected(playerid))
	{
		VarAntic(playerid)<Money> += money;
		GivePlayerMoney(playerid, money);
		return 1;
	}
	return 0;
}

#if defined _ALS_GivePlayerMoney
	#undef GivePlayerMoney
#else
	#define _ALS_GivePlayerMoney
#endif

#define GivePlayerMoney antic_GivePlayerMoney
// -========================================================================- //
ANTIC::GetPlayerMoney(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		return VarAntic(playerid)<Money>;
	}
	return 0;
}

#if defined _ALS_GetPlayerMoney
	#undef GetPlayerMoney
#else
	#define _ALS_GetPlayerMoney
#endif

#define GetPlayerMoney antic_GetPlayerMoney
// -========================================================================- //
ANTIC::SetPlayerHealth(playerid, Float:health)
{
	if(IsPlayerConnected(playerid))
	{
	    if(health > 100.0)
	        health = 100.0;

		if(health < 0.0)
		    health = 0.0;

		VarAntic(playerid)<Health> = health;
		SetPlayerHealth(playerid, health);
		Unsync(playerid,Health);
		ResetSyncTime(playerid,Health);
		return 1;
	}
	return 0;
}

#if defined _ALS_SetPlayerHealth
	#undef SetPlayerHealth
#else
	#define _ALS_SetPlayerHealth
#endif

#define SetPlayerHealth antic_SetPlayerHealth
// -========================================================================- //
ANTIC::SetPlayerArmour(playerid, Float:armour)
{
	if(IsPlayerConnected(playerid))
	{
	    if(armour > 100.0)
	        armour = 100.0;

		VarAntic(playerid)<Armour> = armour;
		SetPlayerArmour(playerid, armour);
		Unsync(playerid,Armour);
		ResetSyncTime(playerid,Armour);
		return 1;
	}
	return 0;
}

#if defined _ALS_SetPlayerArmour
	#undef SetPlayerArmour
#else
	#define _ALS_SetPlayerArmour
#endif

#define SetPlayerArmour antic_SetPlayerArmour
// -========================================================================- //
ANTIC::SetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
	if(IsPlayerConnected(playerid))
	{
		VarAntic(playerid)<Pos_x> = x;
		VarAntic(playerid)<Pos_y> = y;
		VarAntic(playerid)<Pos_z> = z;
		
		SetPlayerPos (playerid, x, y, z);
		Unsync(playerid,Pos);
		ResetSyncTime(playerid,Pos);
		return 1;
	}
	return 0;
}

#if defined _ALS_SetPlayerPos
	#undef SetPlayerPos
#else
	#define _ALS_SetPlayerPos
#endif

#define SetPlayerPos antic_SetPlayerPos
// -========================================================================- //
ANTIC::SetVehiclePos(vehicleid, Float:x, Float:y, Float:z)
{
	if (IsValidVehicle (vehicleid))
	{
		foreach (Player, i)
		{
		    if (GetPlayerVehicleID (i) == vehicleid)
		    {
				VarAntic(i)<Pos_x> = x;
				VarAntic(i)<Pos_y> = y;
				VarAntic(i)<Pos_z> = z;

				Unsync(i,Pos);
				ResetSyncTime(i,Pos);
			}
		}
		SetVehiclePos (vehicleid, x, y, z);
		return 1;
	}
	return 0;
}

#if defined _ALS_SetVehiclePos
	#undef SetVehiclePos
#else
	#define _ALS_SetVehiclePos
#endif

#define SetVehiclePos antic_SetVehiclePos
// -========================================================================- //
ANTIC::SetVehicleHealth(vehicleid, Float:health)
{
	if (IsValidVehicle (vehicleid))
	{
	    if (health > 1000.0)
	        health = 1000.0;

	    if (health < 0.0)
	        health = 0.0;

		foreach (Player, i)
		{
		    if (GetPlayerVehicleID (i) == vehicleid)
		    {
				VarAntic(i)<VehicleHP> = health;
				Unsync(i,VehicleHP);
			}
		}
		SetVehicleHealth (vehicleid, health);
		return 1;
	}
	return 0;
}

#if defined _ALS_SetVehicleHealth
	#undef SetVehicleHealth
#else
	#define _ALS_SetVehicleHealth
#endif

#define SetVehicleHealth antic_SetVehicleHealth
// -========================================================================- //
ANTIC::RepairVehicle(vehicleid)
{
	if (IsValidVehicle (vehicleid))
	{
		foreach (Player, i)
		{
		    if (GetPlayerVehicleID (i) == vehicleid)
		    {
				VarAntic(i)<VehicleHP> = 1000.0;
				Unsync(i,VehicleHP);
			}
		}
		RepairVehicle (vehicleid);
		return 1;
	}
	return 0;
}

#if defined _ALS_RepairVehicle
	#undef RepairVehicle
#else
	#define _ALS_RepairVehicle
#endif

#define RepairVehicle antic_RepairVehicle
// -========================================================================- //
ANTIC::PutPlayerInVehicle(playerid, vehicleid, seat)
{
	if (IsPlayerConnected (playerid))
	{
		if (IsValidVehicle (vehicleid))
		{
			PutPlayerInVehicle (playerid, vehicleid, seat);
			
			VarAntic(playerid)<VehicleID> = vehicleid;

			new
			    Float: health;

			GetVehicleHealth (vehicleid, health);

			if (health > 1000.0)
			{
			    antic_SetVehicleHealth (vehicleid, 1000.0);
			}
			else
			{
			    VarAntic(playerid)<VehicleHP> = health;
			}
			
			Unsync(playerid,Pos);
			Unsync(playerid,VehicleID);
			Unsync(playerid,VehicleHP);

			ResetSyncTime(playerid,Pos);
			ResetSyncTime(playerid,VehicleID);
			
			VarAntic(playerid)<PutTick> = GetTickCount();
			
			GetVehiclePos (vehicleid, VarAntic(playerid)<Pos_x>, VarAntic(playerid)<Pos_y>, VarAntic(playerid)<Pos_z>);
			return 1;
		}
	}
	return 0;
}

#if defined _ALS_PutPlayerInVehicle
	#undef PutPlayerInVehicle
#else
	#define _ALS_PutPlayerInVehicle
#endif

#define PutPlayerInVehicle antic_PutPlayerInVehicle
// -========================================================================- //
ANTIC::SetPlayerSpecialAction(playerid, actionid)
{
	if(IsPlayerConnected(playerid))
	{
	    if(actionid == SPECIAL_ACTION_USEJETPACK)
			VarAntic(playerid)<Bools> |= antic_JetPack;

   		SetPlayerSpecialAction(playerid, actionid);
		return 1;
	}
	return 0;
}

#if defined _ALS_SetPlayerSpecialAction
	#undef SetPlayerSpecialAction
#else
	#define _ALS_SetPlayerSpecialAction
#endif

#define SetPlayerSpecialAction antic_SetPlayerSpecialAction
// -========================================================================- //
ANTIC::GivePlayerWeapon(playerid, weapon, ammo)
{
	if(IsPlayerConnected(playerid))
	{
		for(new Weap; Weap < sizeof(BanWeaps); Weap++)
		{
		    if(weapon == BanWeaps[Weap])
		    {
				SendClientMessage(playerid, 0xFF000000, "[ANTICHEAT] {FFFFFF}Por cuestiones de seguridad, se bloqueo un arma que el servidor te dio");
				return 0;
			}
		}

		WeaponTime[playerid] = 6;
	    GivePlayerWeapon(playerid, weapon, ammo);
		return 1;
	}
	return 0;
}

#if defined _ALS_GivePlayerWeapon
	#undef GivePlayerWeapon
#else
	#define _ALS_GivePlayerWeapon
#endif

#define GivePlayerWeapon antic_GivePlayerWeapon
// -========================================================================- //
ANTIC::ResetPlayerWeapons(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		ResetPlayerWeapons (playerid);
		WeaponTime[playerid] = 6;

		if (IsPlayerInAnyVehicle (playerid))
		    SetPlayerArmedWeapon (playerid, 0);

		return 1;
	}
	return 0;
}

#if defined _ALS_ResetPlayerWeapons
	#undef ResetPlayerWeapons
#else
	#define _ALS_ResetPlayerWeapons
#endif

#define ResetPlayerWeapons antic_ResetPlayerWeapons
// -========================================================================- //
ANTIC::ShowPlayerDialog(playerid, dialogid, style, title[], text[], butt1[], butt2[])
{
	if(IsPlayerConnected(playerid))
	{
		SetPVarInt(playerid,"antic_DialogID", dialogid);
  		ShowPlayerDialog(playerid, dialogid, style, title, text, butt1, butt2);
  		return 1;
	}

	return 0;
}

#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif

#define ShowPlayerDialog antic_ShowPlayerDialog
// -========================================================================- //
