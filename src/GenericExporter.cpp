#include "GenericExporter.h"
#include "rsException.h"

GenericExporter::GenericExporter(QString filename, unsigned int stats)
: toWrite(stats)
{
	fp = new QFile(filename);

	if(!fp->open(QIODevice::WriteOnly | QIODevice::Text))
		throw RSException();
}

GenericExporter::~GenericExporter(void)
{
	if(fp)
	{
		fp->close();
		delete fp;
	}
}