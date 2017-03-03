#include <a_samp>
public OnPlayerCommandText(playerid, cmdtext[]) {
	if(strfind(cmdtext,"/OnPlayerUpdate",true)==0) {
	    new cmdLen = strlen("/OnPlayerUpdate");
	    if (strlen(cmdtext) < (cmdLen+1)) return SendClientMessage(playerid, -1, "/OnPlayerUpdate <times>");

	    new timesToCall = strval(cmdtext[cmdLen + 1]);
	    new initialTime = GetTickCount();

		for (new i = 0; i < timesToCall; i++) {
			CallRemoteFunction("OnPlayerUpdate", "i", playerid);
		}

		new totalTime = GetTickCount() - initialTime;
		new Float:averageTime = floatdiv(float(totalTime), float(timesToCall));
		new string[150];
		
		new Float:operationsPerMS = floatdiv(float(timesToCall), float(totalTime));
		new operationsPerSec = floatround(operationsPerMS * 1000);
		format(string, 150, "total ms spent: %d - ms per call: %f - %f op/ms - %d op/s", totalTime, averageTime, operationsPerMS, operationsPerSec);
		SendClientMessage(playerid,0xAFAFAFAA,string);
		return 1;
	}
	return 0;
}
