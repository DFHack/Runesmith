#ifndef RSCREATURE_H
#define RSCREATURE_H

#include <vector>
#include <QString>
#include <DFHack.h>
class DFInterface;

#define NUM_TRAITS 30

struct statusTracker
{
	statusTracker() : skillsChanged(false), attributesChanged(false),
		flagsChanged(false), happinessChanged(false), sexChanged(false),
		traitsChanged(false), moodChanged(false), posChanged(false), civChanged(false){}
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

struct formattedSkill
{
	uint8_t id;
	uint32_t xp;
	QString skill;
	QString level;
};

struct cacheItem
{
	uint32_t id;
	QString text;
};

class RSCreature
{
public:
	RSCreature(DFHack::t_creature nRawCreature, uint32_t nID, DFInterface *nDFI);
	~RSCreature(void);

	/* getters */
	const uint32_t getID();
	const uint32_t getNumSkills();
	const uint32_t getHappiness();
	const uint32_t getCiv();

	QString getDOB();
	QString getSex();
	QString getStatus();
	QString getNickname();
	QString getFormattedHappiness();
	
	QString getStrength();
	QString getAgility();
	QString getToughness();
	QString getEndurance();
	QString getRecuperation();
	QString getDiseaseRes();
	QString getWillpower();
	QString getMemory();
	QString getFocus();
	QString getIntuition();
	QString getPatience();
	QString getEmpathy();
	QString getSocialAwareness();
	QString getCreativity();
	QString getMusicality();
	QString getAnalyticalAbility();
	QString getLinguisticAbility();
	QString getSpatialSense();
	QString getKinestheticSense();

	QString const& getAge();
	QString const& getRace();
	QString const& getMood();
	QString const& getEnglishName();
	QString const& getDwarvishName();
	QString const& getMoodSkill();
	QString const& getProfession();

	std::vector<formattedSkill> const& getFormattedSkills();
	std::vector<cacheItem> const& getLabourCache();
	std::vector<cacheItem> const& getTraitCache();
	std::vector<QString> const& getJobMats();

	DFHack::t_creaturflags1 & getFlags1();
	DFHack::t_creaturflags2 & getFlags2();

	uint16_t x();
	uint16_t y();
	uint16_t z();

	bool isChanged();

	/* setters */
	//void addLabour();	
	void toggleSex();
	void setCiv(int32_t nCiv);
	void setX(uint16_t nVal);
	void setY(uint16_t nVal);
	void setZ(uint16_t nVal);
	void setMood(int nMood);
	void setMoodSkill(uint8_t skill);
	void setFlagsChanged();
	
	void setHappiness(uint32_t hapVal);
	void setAllSkillLevels(uint8_t nLevel);
	void setSkillLevel(uint8_t id, uint8_t nLevel);
	void setSkillExperiance(uint8_t id, uint16_t nExp);
	bool editTrait(uint32_t id, uint32_t level);

	void setAllAttributes(uint16_t nVal);
	void setStrength(uint32_t nVal);
	void setAgility(uint32_t nVal);
	void setToughness(uint32_t nVal);
	void setEndurance(uint32_t nVal);
	void setRecuperation(uint32_t nVal);
	void setDiseaseRes(uint32_t nVal);
	void setWillpower(uint32_t nVal);
	void setMemory(uint32_t nVal);
	void setFocus(uint32_t nVal);
	void setIntuition(uint32_t nVal);
	void setPatience(uint32_t nVal);
	void setEmpathy(uint32_t nVal);
	void setSocialAwareness(uint32_t nVal);
	void setCreativity(uint32_t nVal);
	void setMusicality(uint32_t nVal);
	void setAnalyticalAbility(uint32_t nVal);
	void setLinguisticAbility(uint32_t nVal);
	void setSpatialSense(uint32_t nVal);
	void setKinestheticSense(uint32_t nVal);

	/* maintenance */
	DFHack::t_creature const& getRawCreature();
	statusTracker const& getChanged();
	void resetFlags();

private:
	/* Helpers */
	void genSkillsCache();
	void updateSkillsCache(uint8_t id);
	void updateMoodCache();

	/* Data */
	DFInterface *DFI;
	uint32_t RSID;
	statusTracker dataChanged;

	QString englishName;
	QString dwarvishName;
	QString race;
	QString profession;
	QString moodSkill;
	QString mood;
	QString age;

	std::vector<formattedSkill> skillsCache;
	std::vector<cacheItem> labourCache;
	std::vector<cacheItem> traitCache;
	std::vector<QString> formattedMats;
	std::vector<DFHack::t_material> jobMats;

	DFHack::t_creature rawCreature;
};

#endif
