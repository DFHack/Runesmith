#include "ExportCSV.h"

ExportCSV::ExportCSV(QString filename, unsigned int stats) 
: GenericExporter(filename, stats)
{
}

ExportCSV::~ExportCSV(void)
{
}

void ExportCSV::exportCreature(RSCreature *creature)
{
	if(toWrite & RACE)
	{
		*outStream << creature->getRace() << ",";
	}

	if(toWrite & NAME)
	{
		*outStream << creature->getDwarvishName() << ",";
	}

	if(toWrite & PROFESSION)
	{
		*outStream << creature->getProfession() << ",";
	}

	if(toWrite & HAPPINESS)
	{
		*outStream << creature->getHappiness() << ",";
	}

	if(toWrite & SKILLS)
	{
		*outStream << creature-
	}

	if(toWrite & ATTRIBUTES)
	{
		*outStream << creature-
	}

	if(toWrite & TRAITS)
	{
		*outStream << creature-
	}

	if(toWrite & LABOURS)
	{
		*outStream << creature-
	}

	if(toWrite & MOOD)
	{
		*outStream << creature-
	}

	if(toWrite & NICKNAME)
	{
		*outStream << creature->getNickname() << ",";
	}

	if(toWrite & ENGLISH_NAME)
	{
		*outStream << creature->getEnglishName() << ",";
	}

	if(toWrite & SEX)
	{
		*outStream << creature->getSex() << ",";
	}

	if(toWrite & DOB)
	{
		*outStream << creature->getDOB() << ",";
	}

	if(toWrite & AGE)
	{
		*outStream << creature->getAge() << ",";
	}

	if(toWrite & CUSTOM_PROF)
	{
		*outStream << creature-
	}

	if(toWrite & FLAGS)
	{
		*outStream << creature-
	}
}
