#include "creatureCmps.h"
#include <string>

bool creatureAscNameCmp(DFHack::t_creature *left, DFHack::t_creature *right)
{
	if(left->name.has_name && right->name.has_name)
	{
		int i = strcmp(left->name.first_name, right->name.first_name);

		if(i < 0)
			return true;
		else
			return false;
	}
	else
	{
		if(left->name.has_name)
			return true;
		else
			return false;
	}

}

bool creatureDecNameCmp(DFHack::t_creature *left, DFHack::t_creature *right)
{
	if(left->name.has_name && right->name.has_name)
	{
		int i = strcmp(left->name.first_name, right->name.first_name);

		if(i > 0)
			return true;
		else
			return false;
	}
	else
	{
		if(left->name.has_name)
			return true;
		else
			return false;
	}

}

bool creatureAscProfCmp(DFHack::t_creature *left, DFHack::t_creature *right)
{
	if(left->profession > right->profession)
		return true;
	else
		return false;
}
