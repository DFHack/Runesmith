#ifndef CREATURECMPS_H
#define CREATURECMPS_H

#include "RSCreature.h"

bool creatureAscNameCmp(RSCreature* left, RSCreature* right);
bool creatureDecNameCmp(RSCreature* left, RSCreature* right);
bool creatureAscProfCmp(RSCreature* left, RSCreature* right);
bool creatureDecProfCmp(RSCreature* left, RSCreature* right);
bool creatureAscHapCmp(RSCreature* left, RSCreature* right);
bool creatureDecHapCmp(RSCreature* left, RSCreature* right);

#endif