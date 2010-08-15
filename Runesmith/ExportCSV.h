#ifndef EXPORTCSV_H
#define EXPORTCSV_H

#include <QString>
#include "GenericExporter.h"

class ExportCSV : public GenericExporter
{
public:
	ExportCSV(QString filename, unsigned int stats);
	virtual ~ExportCSV(void);
	void exportCreature(RSCreature *creature);
};

#endif