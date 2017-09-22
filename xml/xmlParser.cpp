#include "xmlParser.h"

XmlParser::node * XmlParser::firstChildElement(std::string tagNameArg)
{
	if (!inFile.is_open())
		throw std::exception("XmlParser with no opening file");

	for (char c;;)
	{
		if (!inFile.get(c))
			// Return nullptr if node with tag name - strTagname hasn't found
			return nullptr;

		if (c == '<')
		{
			// nodeName - detected tag
			std::string nodeName;
			while (true)
			{
				if (!inFile.get(c))
					throw std::exception("File was ended without closed '>'");
				if (c == '>')
					break;
				nodeName += c;
			}

			if (nodeName == tagNameArg)
			{
				return new node(inFile.tellg(), tagNameArg, &inFile);
			}

		}
	}
}


XmlParser::node *XmlParser::node::firstChildElement(std::string tagNameArg)
{
	if (!inFile->is_open())
		throw std::exception("Node with no opening file");

	// Start search from startPosOfInnerText position
	inFile->seekg(startPosOfInnerText);
	for (char c;;)
	{
		if (!inFile->get(c))
			// Return nullptr if node with tag name - strTagname hasn't found
			// and file was ended
			return nullptr;
		if (c == '<')
		{
			// nodeName - detected tag
			std::string nodeName;
			while (true)
			{
				if (!inFile->get(c))
					throw std::exception("File was ended without closed '>'");
				if (c == '>')
					break;
				nodeName += c;
			}
			if (nodeName == '/' + tagName)
			{
				// Return nullptr if node with tag name - strTagName hasn't found
				// within text in parent node tag
				return nullptr;
			}
			else if (nodeName == tagNameArg)
			{
				return new node(inFile->tellg(), tagNameArg, inFile);
			}
		}
	}
}

std::string XmlParser::node::getText()
{
	if (!inFile->is_open())
		throw std::exception("Node with no opening file");

	// Start separation from startPosOfInnerText position
	inFile->seekg(startPosOfInnerText);

	std::string innerText;
	
	for (char c;;)
	{
		// Throw error if tag of node didn't close until the end of the file
		if (!inFile->get(c))
			throw std::exception("Not closed tag");

		// Check if next tag is closed tag of this node
		if (c == '<')
		{
			// nodeName - detected tag
			std::string nodeName;
			nodeName += c;
			while (true)
			{
				// Throw error if tag of node didn't close until the end of the file
				if (!inFile->get(c))
					throw std::exception("Not closed tag");
				nodeName += c;
				if (c == '>')
					break;
			}

			// if nodeName - closed tag of this node
			if (nodeName == "</" + tagName + '>')
				return innerText;
			else
				innerText += nodeName;
		}
		else
			innerText += c;
	}
}

XmlParser::node * XmlParser::node::nextSlibingElement()
{
	if (!inFile->is_open())
		throw std::exception("Node with no opening file");

	// Start search from startPosOfInnerText position
	inFile->seekg(startPosOfInnerText);

	for (char c;;)
	{
		// Return nullptr if node with "this" tag name hasn't found
		// and file was ended
		if (!inFile->get(c))
			return nullptr;

		if (c == '<')
		{
			// nodeName - detected tag
			std::string nodeName;
			while (true)
			{
				if (!inFile->get(c))
					throw std::exception("File was ended without closed '>'");
				if (c == '>')
					break;
				nodeName += c;
			}
			if (nodeName == tagName)
			{
				return new node(inFile->tellg(), tagName, inFile);
			}
		}
	}
}
