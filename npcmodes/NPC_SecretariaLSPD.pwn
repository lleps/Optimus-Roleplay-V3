#include <a_npc>

#define F_NAME "Asistente_LSPD" 
#define R_TYPE 2

main()
{
	printf("\nAsistente_LSPD.rec -> Cargado...\n");
}

public OnRecordingPlaybackEnd()
{
	return StartRecordingPlayback(R_TYPE, F_NAME);
}

public OnNPCSpawn()
{
	return StartRecordingPlayback(R_TYPE, F_NAME);
}
// EOF
