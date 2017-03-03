// Optimization script

stock SetPVarInt_OP(playerid,name[], value)
	return (value == 0) ? DeletePVar(playerid, name) : SetPVarInt(playerid, name, value);

#define SetPVarInt SetPVarInt_OP

stock SECURE_INI_WriteString(INI:Handle, line[], val[])
{
	for(new i, len = strlen(val); i < len; i++)
	{
		if(val[i] == '=')
			val[i] = '_';
	}
	INI_WriteString(Handle, line, val);
	return 1;
}

#define INI_WriteString SECURE_INI_WriteString
