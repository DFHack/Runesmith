#include "GenericExporter.h"
#include "rsException.h"

GenericExporter::GenericExporter(QString filename, unsigned int stats)
: toWrite(stats)
{
	fp = new QFile(filename);

	if(!fp->open(QIODevice::WriteOnly | QIODevice::Text))
		throw RSException();

	outStream = new QTextStream(fp);

}

GenericExporter::~GenericExporter(void)
{
	if(outStream)
		delete outStream;

	if(fp)
	{
		fp->close();
		delete fp;
	}
}