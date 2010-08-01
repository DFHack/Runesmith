#include "creatureCmps.h"
#include <string>

//TODO test to see if these are the correct way round
bool creatureAscNameCmp(RSCreature* left, RSCreature* right)
{
	if(left->dwarvishName > right->dwarvishName)
		return true;
	else
		return false;
}

bool creatureDecNameCmp(RSCreature* left, RSCreature* right)
{
	if(left->dwarvishName < right->dwarvishName)
		return true;
	else
		return false;
}

bool creatureAscProfCmp(RSCreature* left, RSCreature* right)
{
	if(left->profession > right->profession)
		return true;
	else
		return false;
}
