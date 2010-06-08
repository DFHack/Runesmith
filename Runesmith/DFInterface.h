#ifndef DFINTERFACE_H
#define DFINTERFACE_H

#include <QString>
#include <DFHack.h>

class DFInterface
{
public:
	DFInterface(void);
	~DFInterface(void);
	bool isAttached();
	bool attach();
	void detatch();
	void update();
	std::vector<DFHack::t_creature>& getDwarves();
	std::vector<DFHack::t_creature>& getCreatures();
	DFHack::t_creature* getDwarf(int dwarf);
	DFHack::t_creature* getCreature(int creature);
	
	QString translateName(const DFHack::t_name &name);
	QString translateSkill(const uint32_t skill);
	QString translateProfession(const uint32_t prof);
	QString translateRace(const uint32_t race);

private:
	bool isContextValid();
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
	DFHack::memory_info *mem;
};

#endif
