#include "levelParse.h"

levelParse::levelParse(void)
{
}

levelParse::~levelParse(void)
{
}

bool levelParse::startDocument()
{
	return true;
}

bool levelParse::startElement(const QString & namespaceURI,
				  const QString & localName,
				  const QString & qName,
				  const QXmlAttributes & atts)
{
	return true;
}

bool levelParse::characters(const QString& text)
{
	return true;
}

bool levelParse::endElement(const QString & namespaceURI,
				const QString & localName,
				const QString & qName )
{
	return true;
}

bool levelParse::endDocument()
{
	return true;
}

