#include "ExportXML.h"

ExportXML::ExportXML(QString filename, unsigned int stats) 
: GenericExporter(filename, stats), outStream(fp)
{
	outStream.setAutoFormatting(true);
	outStream.writeStartDocument();
}

ExportXML::~ExportXML(void)
{
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

	if(toWrite & PROFESSION)
	{
		outStream.writeTextElement("Profession", creature->getProfession());
	}

	if(toWrite & HAPPINESS)
	{
		outStream.writeTextElement("Happiness", creature->getFormattedHappiness());
	}

	if(toWrite & SKILLS)
	{
	}

	if(toWrite & ATTRIBUTES)
	{
	}

	if(toWrite & TRAITS)
	{
	}

	if(toWrite & LABOURS)
	{
	}

	if(toWrite & MOOD)
	{
	}

	if(toWrite & NICKNAME)
	{
		outStream.writeTextElement("Nickname", creature->getNickname());
	}

	if(toWrite & ENGLISH_NAME)
	{
		outStream.writeTextElement("EnglishName", creature->getEnglishName());
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

	if(toWrite & FLAGS)
	{
	}

	outStream.writeEndElement();
}
