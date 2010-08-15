#ifndef EXPORTABLESTATS_H
#define EXPORTABLESTATS_H

enum ExportableStats
{
	NONE = 0x0,
	RACE = 0x1,
	NAME = 0x2,
	PROFESSION = 0x4,
	HAPPINESS = 0x8,
	SKILLS = 0x10,
	ATTRIBUTES = 0x20,
	TRAITS = 0x40,
	LABOURS = 0x80,
	MOOD = 0x100,
	NICKNAME = 0x200,
	ENGLISH_NAME = 0x400,
	SEX = 0x800,
	DOB = 0x1000,
	AGE = 0x2000,
	CUSTOM_PROF = 0x4000,
	FLAGS = 0x8000
};

#endif