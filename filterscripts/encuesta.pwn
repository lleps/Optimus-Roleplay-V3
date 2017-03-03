/* Sistema de encuestas
 * /encuestafs pregunta|opcion1|opcion2|opcion3
 * /votar 1-3
 */

#include <a_samp>
#include <zcmd>
#include <sscanf2>

new optionVote[3];

public OnFilterScriptInit()
{
	print("\n--------------------------------------");
	print(" FS de encuestas");
	print("--------------------------------------\n");
	return 1;
}

public OnFilterScriptExit(){
	return 1;
}

CMD:encuestafs(playerid,params[]) {
	new question[200],option1[90],option2[90],option3[90];
	if (sscanf(params, "p<|>s[200]s[90]s[90]s[90]", question, option1, option2, option3)) {
		return SendClientMessage(playerid, -1, "/encuestafs pregunta|opcion1|opcion2|opcion3");
	}
	
	optionVote[0] = 0;
	optionVote[1] = 0;
	optionVote[2] = 0;
	
	for (new i = 0; i < MAX_PLAYERS; i++) if (IsPlayerConnected(i)) {
		for (new j = 0; j < 10; j++) SendClientMessage(i, -1, "");
		
		new string[200];
		
		format(string, 200, "Encuesta: %s", question);
		SendClientMessage(i, -1, string);

		format(string, 200, "(/votar 1): %s", option1);
		SendClientMessage(i, -1, string);

		format(string, 200, "(/votar 2) %s", option2);
		SendClientMessage(i, -1, string);

		format(string, 200, "(/votar 3): %s", option3);
		SendClientMessage(i, -1, string);

		SetPVarInt(i, "CanVote", 1);
	}
	return 1;
}

CMD:resultadosfs(playerid,params[]) {
	new str[100];
	format(str, 100, "Opcion 1: %d", optionVote[0]);
	SendClientMessage(playerid, -1, str);

	format(str, 100, "Opcion 2: %d", optionVote[1]);
	SendClientMessage(playerid, -1, str);

	format(str, 100, "Opcion 3: %d", optionVote[2]);
	SendClientMessage(playerid, -1, str);
	return 1;
}

CMD:votar(playerid,params[]) {
	new option = strval(params);
	if (option < 1 && option > 3) return SendClientMessage(playerid, -1, "Usa /votar 1-3");
	if (!GetPVarInt(playerid, "CanVote")) return SendClientMessage(playerid, -1, "No puedes votar ahora.");
	DeletePVar(playerid, "CanVote");
	optionVote[option - 1]++;
	SendClientMessage(playerid, -1, "Enviaste tu voto. Gracias por participar.");
	return 1;
}
