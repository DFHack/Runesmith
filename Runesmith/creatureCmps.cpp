#include "creatureCmps.h"
#include <string>

//TODO test to see if these are the correct way round
bool creatureAscNameCmp(RSCreature* left, RSCreature* right)
{
	if(left->getDwarvishName() < right->getDwarvishName())
		return true;
	else
		return false;
}

bool creatureDecNameCmp(RSCreature* left, RSCreature* right)
{
	if(left->getDwarvishName() > right->getDwarvishName())
		return true;
	else
		return false;
}

bool creatureAscProfCmp(RSCreature* left, RSCreature* right)
{
	if(left->getProfession() < right->getProfession())
		return true;
	else
		return false;
}

bool creatureDecProfCmp(RSCreature* left, RSCreature* right)
{
	if(left->getProfession() > right->getProfession())
		return true;
	else
		return false;
}