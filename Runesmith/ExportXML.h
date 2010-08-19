#ifndef EXPORTXML_H
#define EXPORTXML_H

#include <QString>
#include <QXmlStreamWriter>
#include "GenericExporter.h"

class ExportXML : public GenericExporter
{
public:
	ExportXML(QString filename, unsigned int stats);
	virtual ~ExportXML(void);
	void exportCreature(RSCreature *creature);

private:
	QXmlStreamWriter outStream;
};

#endif