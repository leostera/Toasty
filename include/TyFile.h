#pragma once

/* Standard Libraries */
#include <typeinfo>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

/* Toasty Libraries */
#include <TyDebug.h>

/******
 * Static template functions: Outputs a string as string-stream to allow conversion between strings and primitive types
 * (int/double/float/etc...)
 */

/* Convert a primitive data type into a string */
template <typename Primitive>
static std::string PrimitiveToString(Primitive const &pValue) {
	std::ostringstream stream;
	stream << pValue;

	return stream.str();
}

/* Convert a string into a primitive data type */
template <typename Primitive>
static Primitive StringToPrimitive(std::string const &pValue) {
	std::istringstream stream(pValue);
	Primitive output;

	if(!(stream >> output)) {
		std::stringstream errormessage(std::stringstream::in | std::stringstream::out);
		errormessage << "Invalid primitive type '" << (std::string)typeid(Primitive).name() << "' in *.CDF File!";
		TyDebug::ReportError(errormessage.str(), 200);
	}

	return output;
}

//template <>
static std::string StringToPrimitive(std::string const &pValue) {
	return pValue;
}

/******
 * TyFile : Loads and parses a Toasty Data File into a 2-dimensional dynamic array of keys and their values
 */
class TyFile {
	/* Data */
	std::string m_Filename;
	std::map<std::string, std::string> m_Data;

	/* Remove all characters in a line after the defined comment token */
	void RemoveComment(std::string &pLine) const {
		if(pLine.find('#') != pLine.npos)
			pLine.erase(pLine.find('#'));
	}

	/* Returns true if the line contains space and tab characters only */
	bool OnlyWhitespace(const std::string &pLine) const {
		return (pLine.find_first_not_of(' ') == pLine.npos);
	}

	/* Returns true unless the line doesn't contain an equal symbol or if it begins with one */
	bool ValidLine(const std::string &pLine) const {
		std::string line = pLine;
		line.erase(0, line.find_first_not_of("/t "));

		if(line[0] == '=')
			return false;

		for(std::size_t i = line.find('='); i < line.length(); i++)
			if(line[i] != ' ')
				return true;

		return false;
	}

	/* Extracts the key from a line */
	void ExtractKey(std::string &pKey, size_t const &pPos, const std::string &pLine) const {
		pKey = pLine.substr(0, pPos);
		if((pKey.find('\t') != pLine.npos) || (pKey.find(' ') != pLine.npos))
			pKey.erase(pKey.find_first_of("\t "));
	}

	/* Extracts the value from a line */
	void ExtractValue(std::string &pValue, size_t const &pPos, std::string const &pLine) const {
		pValue = pLine.substr(pPos + 1);
		pValue.erase(0, pValue.find_first_not_of("\t "));
		pValue.erase(pValue.find_last_not_of("\t ") + 1);
	}

	/* Stores the key and its value onto the map */
	void ExtractContents(std::string const &pLine) {
		std::string line = pLine;

		line.erase(0, line.find_first_not_of("\t "));
		size_t pos = line.find('=');

		std::string key, value;
		this->ExtractKey(key, pos, line);
		this->ExtractValue(value, pos, line);

		if(!(KeyExists(key))) {
			m_Data.insert(std::pair<std::string, std::string>(key, value));
		}
		else {
			std::stringstream errormessage(std::stringstream::in | std::stringstream::out);
			errormessage << "Multiple definition of '" << key << "' key in '" << m_Filename << "'.";
			TyDebug::ReportError(errormessage.str(), 210);
		}

	}

	/* Evaluates a line from the file */
	void ParseLine(std::string const &pLine, size_t const &pLineNumber) {
		if(pLine.find('=') == pLine.npos) {
			std::stringstream errormessage(std::stringstream::in | std::stringstream::out);
			errormessage << "Syntax error on line '" << cConversion::PrimitiveToString(pLineNumber) << "'!";
			TyDebug::ReportError(errormessage.str(), 220);
		}

		if(!(this->ValidLine(pLine))) {
			std::stringstream errormessage(std::stringstream::in | std::stringstream::out);
			errormessage << "Syntax error on line '" << cConversion::PrimitiveToString(pLineNumber) << "'!";
			TyDebug::ReportError(errormessage.str(), 220);
		}

		this->ExtractContents(pLine);
	}

	/* Stores all contents of the file ignoring comments and whitespace onto map */
	void ParseFile() {
		std::fstream file;
		file.open(m_Filename.c_str(), std::ios::in);

		if(!(file)) {
			std::stringstream errormessage(std::stringstream::in | std::stringstream::out);
			errormessage << "Failed to load '" << m_Filename << "'.";
			TyDebug::ReportError(errormessage.str(), 230);
		}

		std::string line;
		size_t linenumber = 0;

		while(std::getline(file, line)) {
			linenumber++;
			std::string handle = line;

			if(handle.empty())
				continue;

			this->RemoveComment(handle);
			if(this->OnlyWhitespace(handle))
				continue;

			this->ParseLine(handle, linenumber);
		}

		file.close();
	}

public:
	TyFile(std::string pFilename) {
		this->m_Filename = pFilename;
		this->ParseFile();
	}

	/* Returns true of the specified key exists */
	bool KeyExists(std::string const &pKey) const {
		return m_Data.find(pKey) != m_Data.end();
	}

	/* Get the value of the specified key */
	template <typename ValueType>
	ValueType GetKeyValue(std::string const &pKey, ValueType const &pDefault = ValueType()) const {
		if(!KeyExists(pKey))
			return pDefault;

		return cConversion::StringToPrimitive<ValueType>(m_Data.find(pKey)->second);
	}
};