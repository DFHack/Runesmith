#include "ExportCSV.h"

ExportCSV::ExportCSV(QString filename, unsigned int stats) 
: GenericExporter(filename, stats), outStream(fp)
{
	if(toWrite & RACE)
	{
		outStream << "Race,";
	}

	if(toWrite & NAME)
	{
		outStream << "Name,";
	}

	if(toWrite & ENGLISH_NAME)
	{
		outStream << "English_Name,";
	}

	if(toWrite & NICKNAME)
	{
		outStream << "Nickname,";
	}

	if(toWrite & HAPPINESS)
	{
		outStream << "Happiness,";
	}

	if(toWrite & PROFESSION)
	{
		outStream << "Profession,";
	}

	if(toWrite & SEX)
	{
		outStream << "Sex,";
	}

	if(toWrite & DOB)
	{
		outStream << "DOB,";
	}

	if(toWrite & AGE)
	{
		outStream << "Age,";
	}

	if(toWrite & CUSTOM_PROF)
	{
		outStream << "Custom_Profession,";
	}

	if(toWrite & SKILLS)
	{
			outStream << "Skills,";
	}

	if(toWrite & ATTRIBUTES)
	{
		outStream << "Attributes,";
	}

	if(toWrite & TRAITS)
	{
			outStream << "Traits,";
	}

	if(toWrite & LABOURS)
	{
			outStream << "Labours,";
	}

	if(toWrite & MOOD)
	{
		outStream << "Mood,";
	}

	outStream << "\n";
}

ExportCSV::~ExportCSV(void)
{
}

void ExportCSV::exportCreature(RSCreature *creature)
{
	if(toWrite & RACE)
	{
		outStream << creature->getRace() << ",";
	}

	if(toWrite & NAME)
	{
		outStream << creature->getDwarvishName() << ",";
	}

	if(toWrite & ENGLISH_NAME)
	{
		outStream << creature->getEnglishName() << ",";
	}

	if(toWrite & NICKNAME)
	{
		outStream << creature->getNickname() << ",";
	}

	if(toWrite & HAPPINESS)
	{
		outStream << creature->getHappiness() << ",";
	}

	if(toWrite & PROFESSION)
	{
		outStream << creature->getProfession() << ",";
	}

	if(toWrite & SEX)
	{
		outStream << creature->getSex() << ",";
	}

	if(toWrite & DOB)
	{
		outStream << creature->getDOB() << ",";
	}

	if(toWrite & AGE)
	{
		outStream << creature->getAge() << ",";
	}

	if(toWrite & CUSTOM_PROF)
	{
		outStream << creature->getRawCreature().custom_profession << ",";
	}

	if(toWrite & SKILLS)
	{
		std::vector<formattedSkill> skills = creature->getFormattedSkills();

		for(int i=0; i<skills.size(); i++)
		{
			outStream << skills[i].skill << ",";
			outStream << skills[i].level << ",";
			outStream << QString::number(skills[i].xp) << ",";
		}
	}

	if(toWrite & ATTRIBUTES)
	{
		outStream << creature->getStrength() << ",";
		outStream << creature->getAgility() << ",";
		outStream << creature->getToughness() << ",";
		outStream << creature->getEndurance() << ",";
		outStream << creature->getRecuperation() << ",";
		outStream << creature->getDiseaseRes() << ",";
		outStream << creature->getWillpower() << ",";
		outStream << creature->getMemory() << ",";
		outStream << creature->getFocus() << ",";
		outStream << creature->getIntuition() << ",";
		outStream << creature->getPatience() << ",";
		outStream << creature->getEmpathy() << ",";
		outStream << creature->getSocialAwareness() << ",";
		outStream << creature->getCreativity() << ",";
		outStream << creature->getMusicality() << ",";
		outStream << creature->getAnalyticalAbility() << ",";
		outStream << creature->getLinguisticAbility() << ",";
		outStream << creature->getSpatialSense() << ",";
		outStream << creature->getKinestheticSense() << ",";
	}

	if(toWrite & TRAITS)
	{
		std::vector<cacheItem> const& traits = creature->getTraitCache();

		for(int i=0; i<traits.size(); i++)
		{
			outStream << traits[i].text << ",";
		}
	}

	if(toWrite & LABOURS)
	{
		std::vector<cacheItem> const& labours = creature->getLabourCache();

		for(int i=0; i<labours.size(); i++)
		{
			outStream << labours[i].text << ",";
		}
	}

	if(toWrite & MOOD)
	{
		outStream << creature->getMood() << ",";
		outStream << creature->getMoodSkill() << ",";
	}

	outStream << "\n";
}
