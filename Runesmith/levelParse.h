#ifndef LEVEL_PARSE_H
#define LEVEL_PARSE_H

#include <QXmlDefaultHandler>

class levelParse : public QXmlDefaultHandler
{
public:
	levelParse(void);
	virtual ~levelParse(void);
	bool startDocument();
	bool endDocument();
	bool startElement(const QString & namespaceURI,
		const QString & localName,
		const QString & qName,
		const QXmlAttributes & atts);
	bool characters(const QString& text);
	bool endElement(const QString & namespaceURI,
		const QString & localName,
		const QString & qName );

};

#endif
