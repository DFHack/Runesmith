#include "ExportXML.h"

ExportXML::ExportXML(QString filename, unsigned int stats) 
: GenericExporter(filename, stats), outStream(fp)
{
	outStream.setAutoFormatting(true);
	outStream.writeStartDocument();
	outStream.writeStartElement("Creatures");
}

ExportXML::~ExportXML(void)
{
	outStream.writeEndElement();
	outStream.writeEndDocument();
}

void ExportXML::exportCreature(RSCreature *creature)
{
	outStream.writeStartElement("Creature");

	if(toWrite & RACE)
	{
		outStream.writeTextElement("Race", creature->getRace());
	}

	if(toWrite & NAME)
	{
		outStream.writeTextElement("Name", creature->getDwarvishName());
	}

	if(toWrite & ENGLISH_NAME)
	{
		outStream.writeTextElement("EnglishName", creature->getEnglishName());
	}

	if(toWrite & NICKNAME)
	{
		outStream.writeTextElement("Nickname", creature->getNickname());
	}

	if(toWrite & HAPPINESS)
	{
		outStream.writeTextElement("Happiness", creature->getFormattedHappiness());
	}

	if(toWrite & PROFESSION)
	{
		outStream.writeTextElement("Profession", creature->getProfession());
	}

	if(toWrite & SEX)
	{
		outStream.writeTextElement("Sex", creature->getSex());
	}

	if(toWrite & DOB)
	{
		outStream.writeTextElement("DOB", creature->getDOB());
	}

	if(toWrite & AGE)
	{
		outStream.writeTextElement("Age", creature->getAge());
	}

	if(toWrite & CUSTOM_PROF)
	{
		outStream.writeTextElement("CustomProfession", 
			creature->getRawCreature().custom_profession);
	}

	if(toWrite & SKILLS)
	{
		outStream.writeStartElement("Skills");		
		std::vector<formattedSkill> skills = creature->getFormattedSkills();

		for(int i=0; i<skills.size(); i++)
		{
			outStream.writeStartElement("Skill");
			outStream.writeTextElement("Name", skills[i].skill);
			outStream.writeTextElement("Level", skills[i].level);
			outStream.writeTextElement("Experience", QString::number(skills[i].xp));
			outStream.writeEndElement();
		}

		outStream.writeEndElement();
	}

	if(toWrite & ATTRIBUTES)
	{
		outStream.writeStartElement("Attributes");

		outStream.writeTextElement("Strength", creature->getStrength());
		outStream.writeTextElement("Agility", creature->getAgility());
		outStream.writeTextElement("Toughness", creature->getToughness());
		outStream.writeTextElement("Endurance", creature->getEndurance());
		outStream.writeTextElement("Recuperation", creature->getRecuperation());
		outStream.writeTextElement("DiseaseResistance", creature->getDiseaseRes());
		outStream.writeTextElement("Willpower", creature->getWillpower());
		outStream.writeTextElement("Memory", creature->getMemory());
		outStream.writeTextElement("Focus", creature->getFocus());
		outStream.writeTextElement("Intuition", creature->getIntuition());
		outStream.writeTextElement("Patience", creature->getPatience());
		outStream.writeTextElement("Empathy", creature->getEmpathy());
		outStream.writeTextElement("SocialAwareness", creature->getSocialAwareness());
		outStream.writeTextElement("Creatvity", creature->getCreativity());
		outStream.writeTextElement("Musicality", creature->getMusicality());
		outStream.writeTextElement("AnalyticalAbility", creature->getAnalyticalAbility());
		outStream.writeTextElement("LinguisticAbility", creature->getLinguisticAbility());
		outStream.writeTextElement("SpatialSense", creature->getSpatialSense());
		outStream.writeTextElement("KinaestheticSense", creature->getKinestheticSense());

		outStream.writeEndElement();		
	}

	if(toWrite & TRAITS)
	{
		outStream.writeStartElement("Traits");
		std::vector<cacheItem> const& traits = creature->getTraitCache();

		for(int i=0; i<traits.size(); i++)
		{
			outStream.writeTextElement("Trait", traits[i].text);
		}

		outStream.writeEndElement();
	}

	if(toWrite & LABOURS)
	{
		outStream.writeStartElement("Labours");
		std::vector<cacheItem> const& labours = creature->getLabourCache();

		for(int i=0; i<labours.size(); i++)
		{
			outStream.writeTextElement("Labour", labours[i].text);
		}

		outStream.writeEndElement();
	}

	if(toWrite & MOOD)
	{
		outStream.writeStartElement("Mood");
		outStream.writeTextElement("Type", creature->getMood());
		outStream.writeTextElement("Skill", creature->getMoodSkill());
		outStream.writeEndElement();
	}

	outStream.writeEndElement();
}
