#ifndef DFINTERFACE_H
#define DFINTERFACE_H

#include <vector>
#include <map>
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

enum TrackedBlocks
{
	HAPPINESS_CHANGED,
	FLAGS_CHANGED,
	ATTRIBUTES_CHANGED,
	SKILLS_CHANGED,
	SEX_CHANGED
};

struct statusTracker
{
	statusTracker() : id(0), skillsChanged(false), attributesChanged(false),
		flagsChanged(false), happinessChanged(false), sexChanged(false){}
	uint32_t id;
	bool skillsChanged;
	bool attributesChanged;
	bool flagsChanged;
	bool happinessChanged;
	bool sexChanged;
};

class DFInterface
{
public:
	DFInterface(void);
	~DFInterface(void);

	bool writeAllChanges();
	bool changesPending();
	bool isAttached();
	bool attach();
	void detatch();
	void forceResume();
	void update();
	void setProcessDead(bool state);
	void setChanged(uint32_t id, TrackedBlocks changedBlock);
	
	std::vector<DFHack::t_creature *>& getDwarves();
	std::vector<DFHack::t_creature *>& getCreatures();
	DFHack::t_creature* getDwarf(uint32_t dwarf);
	DFHack::t_creature* getCreature(uint32_t creature);
	DFHack::t_level getLevelInfo(uint32_t level);

	QString getVersion();
	QString translateName(const DFHack::t_name &name, bool english = false);
	QString translateSkill(const uint32_t skill);
	QString translateProfession(const uint32_t prof);
	QString translateRace(const uint32_t race);
	QString translateLabour(const uint8_t labour);
	QString translateTrait(uint32_t index, uint32_t value);
	uint32_t getRacialAverage(uint32_t race, uint32_t caste, RacialStat stat);
	uint32_t getCurrentYear();	

private:
	bool isContextValid();
	void resume();
	void suspend();
	void process();
	void cleanup();
	bool internalWriteChanges();
	bool writeLoop(std::vector<DFHack::t_creature *> &data);

private:
	std::vector<DFHack::t_creature *> creatures;
	std::vector<DFHack::t_creature *> dwarves;
	std::vector<DFHack::t_creature *> allCreatures;
	std::vector<DFHack::t_creature *> allDwarves;

	std::map<uint32_t, statusTracker> changeTracker;
	uint32_t numCreatures;
	uint32_t currentYear;
	bool processDead;
	bool dataChanged;

	DFHack::ContextManager *DFMgr;
    DFHack::Context *DF;
	DFHack::Materials *Materials;
	DFHack::Translation *Tran;
	DFHack::Creatures *Creatures;
	DFHack::memory_info *mem;
	DFHack::World * world;
};

#endif
