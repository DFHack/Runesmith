#ifndef DFINTERFACE_H
#define DFINTERFACE_H

#include <vector>
#include <map>
#include <QString>
#include <DFHack.h>
class RSCreature;

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
	EMPATHY_STAT,
	SOCIAL_AWARENESS_STAT,
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
	void forceResume();
	void update();
	void setProcessDead(bool state);
	void setMainRace(QString nMainRace);
	void setAllRaceSkills(uint8_t val);
	void setAllRaceAttrs(uint16_t val);

	bool writeAllChanges();
	bool changesPending();
	bool readMats(const DFHack::t_creature *creature, 
					std::vector<DFHack::t_material> &mats);
	
	std::vector<DFHack::t_matgloss> const& getOrganicMats();
	std::vector<DFHack::t_matgloss> const& getInorgaincMats();
	std::vector< std::vector<std::string> > const& getAllTraits();
	std::vector<RSCreature*>& getDwarves();
	std::vector<RSCreature*>& getCreatures();
	
	RSCreature* getDwarf(uint32_t dwarf);
	RSCreature* getCreature(uint32_t creature);
	DFHack::t_level getLevelInfo(uint32_t level);

	QString getVersion();
	QString translateName(DFHack::t_name const& name, bool english);
	QString translateSkill(const uint32_t skill);
	QString translateProfession(const uint32_t prof);
	QString translateRace(const uint32_t race);
	QString translateLabour(const uint8_t labour);
	QString translateTrait(uint32_t index, uint32_t value);
	QString getMatDescription(DFHack::t_material &mat);
	QString getMaterialType(DFHack::t_material &mat);
	QString getMood(uint32_t mood);
	
	uint32_t getRacialAverage(uint32_t race, uint32_t caste, RacialStat stat);
	uint32_t getCurrentYear();
	int32_t getDwarfCiv();

	/* Sorting (Dwarves)*/
	void sortDwarvesByName(bool decending);
	void sortDwarvesByProf(bool decending);
	void sortDwarvesByHap(bool decending);

private:
	bool isContextValid();
	void resume();
	void suspend();
	void process();
	void cleanup();
	bool internalWriteChanges();
	bool writeLoop(std::vector<RSCreature*> &data);

private:
	std::vector<RSCreature*> creatures;
	std::vector<RSCreature*> dwarves;
	std::vector<RSCreature*> allCreatures;
	std::vector<RSCreature*> allDwarves;
	std::vector<DFHack::t_creaturetype> raceExCache;
	std::vector<DFHack::t_matgloss> organicMatCache;
	std::vector<DFHack::t_matgloss> inorganicMatCache;

	uint32_t numCreatures;
	uint32_t currentYear;
	int32_t dwarfCivID;
	bool processDead;
	QString mainRace;

	DFHack::ContextManager *DFMgr;
    DFHack::Context *DF;
	DFHack::Materials *Materials;
	DFHack::Translation *Tran;
	DFHack::Creatures *Creatures;
	DFHack::memory_info *mem;
	DFHack::World * world;
};

#endif
