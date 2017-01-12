#ifndef DBCFILE_H
#define DBCFILE_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <map>

typedef unsigned int uint32;
typedef int int32;

typedef struct 
{
	char Signature[4];           //always 'WDBC' 
	int32 Records;               //number of records in the file 
	int32 Fields;                //number of fields per record 
	int32 Record_Size;           //Fields*FieldSize (FieldSize is usually 4, but not always) 
	int32 String_Block_Size;     //Size of the string block
} DBCHeader;


class DbcFile
{
	public:
		DbcFile(std::string _path);
		~DbcFile();
	private:
		// functions
		uint32 LoadFromFile();
		uint32 SaveToFile();
		void PrintTable();
		void CreateStructures();
		// variables
		std::string path;
		uint32 filesize;
		std::fstream file;
		std::map<std::string,std::string> structures;
		std::vector<char> buffer;
		std::vector<char>::iterator position;

		DBCHeader info;

};

#endif