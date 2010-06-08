#ifndef DFINTERFACE_H
#define DFINTERFACE_H

#include <DFHack.h>

class DFInterface
{
public:
	DFInterface(void);
	~DFInterface(void);
	bool isContextValid();
	bool attach();
	void detatch();
	void update();
	std::vector<DFHack::t_creature>& getDwarves();
	std::vector<DFHack::t_creature>& getCreatures();
	DFHack::t_creature& getDwarf(int dwarf);
	DFHack::t_creature& getCreature(int creature);

private:
	void resume();
	void suspend();
	void process();

private:
	std::vector<DFHack::t_creature> creatures;
	std::vector<DFHack::t_creature> dwarves;
	uint32_t numCreatures;

	DFHack::ContextManager *DFMgr;
    DFHack::Context *DF;
	DFHack::Materials *Materials;
	DFHack::Translation *Tran;
	DFHack::Creatures *Creatures;	
};

#endif
