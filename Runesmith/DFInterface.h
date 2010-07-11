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
	EMPATHY_STAT,
	SOCIAL_AWARENESS_STAT,
	CREATVITY_STAT,
	MUSICALITY_STAT,
	ANALYTICAL_ABILITY_STAT,
	LINGUISTIC_ABILITY_STAT,
	SPATIAL_SENSE_STAT,
	KINESTHETIC_SENSE_STAT
};

struct statusTracker
{
	statusTracker() : id(0), skillsChanged(false), attributesChanged(false),
		flagsChanged(false), happinessChanged(false), sexChanged(false),
		traitsChanged(false), moodChanged(false), posChanged(false), civChanged(false){}
	uint32_t id;
	bool skillsChanged;
	bool attributesChanged;
	bool flagsChanged;
	bool happinessChanged;
	bool sexChanged;
	bool traitsChanged;
	bool moodChanged;
	bool posChanged;
	bool civChanged;
};

struct nameStore
{
	QString english;
	QString dwarvish;
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

	void setHappinessChanged(uint32_t id);
	void setFlagsChanged(uint32_t id);
	void setAttrsChanged(uint32_t id);
	void setSkillsChanged(uint32_t id);
	void setSexChanged(uint32_t id);
	void setTraitsChanged(uint32_t id);
	void setMoodChanged(uint32_t id);
	void setPosChanged(uint32_t id);
	void setCivChanged(uint32_t id);
	void setAllRaceSkills(uint8_t val);
	void setAllRaceAttrs(uint16_t val);

	bool writeAllChanges();
	bool changesPending();
	
	std::vector<DFHack::t_matgloss> const& getOrganicMats();
	std::vector<DFHack::t_matgloss> const& getInorgaincMats();
	std::vector<DFHack::t_material>& getMoodMats(uint32_t id);
	std::vector< std::vector<std::string> > const& getAllTraits();
	std::vector<DFHack::t_creature *>& getDwarves();
	std::vector<DFHack::t_creature *>& getCreatures();
	
	DFHack::t_creature* getDwarf(uint32_t dwarf);
	DFHack::t_creature* getCreature(uint32_t creature);
	DFHack::t_level getLevelInfo(uint32_t level);

	QString getVersion();
	QString translateName(const uint32_t id, bool english = false);
	QString translateSkill(const uint32_t skill);
	QString translateProfession(const uint32_t prof);
	QString translateRace(const uint32_t race);
	QString translateLabour(const uint8_t labour);
	QString translateTrait(uint32_t index, uint32_t value);
	QString getMatDescription(DFHack::t_material &mat);
	QString getMood(uint32_t mood);
	
	uint32_t getRacialAverage(uint32_t race, uint32_t caste, RacialStat stat);
	uint32_t getCurrentYear();
	int32_t getDwarfCiv();

private:
	bool isContextValid();
	void resume();
	void suspend();
	void process();
	void cleanup();
	bool internalWriteChanges();
	bool writeLoop(std::vector<DFHack::t_creature *> &data);
	bool readMats(const DFHack::t_creature *creature, std::vector<DFHack::t_material> &mats);

private:
	std::vector<DFHack::t_creature *> creatures;
	std::vector<DFHack::t_creature *> dwarves;
	std::vector<DFHack::t_creature *> allCreatures;
	std::vector<DFHack::t_creature *> allDwarves;
	std::vector<DFHack::t_creaturetype> raceExCache;

	std::map<uint32_t, nameStore> nameCache;
	std::map<uint32_t, std::vector<DFHack::t_material> > moods;
	std::map<uint32_t, statusTracker> changeTracker;

	uint32_t numCreatures;
	uint32_t currentYear;
	int32_t dwarfCivID;
	bool processDead;
	bool dataChanged;
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
