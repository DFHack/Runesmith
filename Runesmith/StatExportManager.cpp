#include "StatExportManager.h"
#include "ExportCSV.h"

StatExportManager::StatExportManager()
{
}

StatExportManager::~StatExportManager(void)
{
}

GenericExporter* StatExportManager::open(QString filename, unsigned int stats)
{
	QString extension = filename.right(4);

	if(!(extension.compare(".csv", Qt::CaseInsensitive)))
	{
		return new ExportCSV(filename, stats);
	}
	else if(!(extension.compare(".xml", Qt::CaseInsensitive)))
	{
	}
	
	return NULL;
}