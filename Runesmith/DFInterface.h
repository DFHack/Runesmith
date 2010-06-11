#ifndef DFINTERFACE_H
#define DFINTERFACE_H

#include <QString>
#include <DFHack.h>

enum RacialStat
{
	STRENGTH_STAT,
	AGILITY_STAT,
	TOUGHNESS_STAT,
	ENDURANCE_STAT,
	RECUPERATION_STAT,
	DISEASE_RESISTANCE_STAT,
	WILLPOWER_STAT,
	MEMORY_STAT,
	FOCUS_STAT,
	INTUITION_STAT,
	PATIENCE_STAT,
	CREATVITY_STAT,
	MUSICALITY_STAT,
	ANALYTICAL_ABILITY_STAT,
	LINGUISTIC_ABILITY_STAT,
	SPATIAL_SENSE_STAT,
	KINESTHETIC_SENSE_STAT
};

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
	QString translateLabour(const uint8_t labour);
	uint32_t getRacialAverage(uint32_t race, uint32_t caste, RacialStat stat);
	DFHack::t_level getLevelInfo(uint32_t level);

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
