#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <string>
#include <fstream>

// XML parser with functions of
// - finding tag node elements in document and tag nodes
// - get innerText of tag nodes
class XmlParser
{
	std::ifstream inFile;
public:
	virtual ~XmlParser() { if (inFile.is_open()) inFile.close(); }

	// Tag node of definite XmlParser object
	class node
	{
		// File of tag node
		// Node have to keep ifstream file on xmlParser object
		std::ifstream *inFile = nullptr;

		// Position of innerText within tag node
		std::streamoff startPosOfInnerText;

		std::string tagName;

	public:
		node(std::streamoff startPosOfInnerTextArg, std::string tagNameArg, std::ifstream *inFileArg) :
			startPosOfInnerText(startPosOfInnerTextArg), tagName(tagNameArg), inFile(inFileArg) { }

		// Find first child element-tag with name - tagNameArg
		// within this->tagName tag
		node* firstChildElement(std::string tagNameArg);

		// Get innerText of tag node
		std::string getText();

		// Return next element in file with the same tag - this->tagName
		node *nextSlibingElement();
	};

	// Find first child element tag with name - strTagName
	node* firstChildElement(std::string strTagName);

	// Open file of xmlParser object
	bool openFile(std::string fileName) { inFile.open(fileName); return inFile.is_open() == true; }
};

#endif // XML_PARSER_H