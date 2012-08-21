#ifndef STATEXPORTMANAGER_H
#define STATEXPORTMANAGER_H

#include <QString>
#include "GenericExporter.h"

class StatExportManager
{
public:
	StatExportManager(void);
	virtual ~StatExportManager(void);
	GenericExporter* open(QString filename, unsigned int stats);
};

#endif