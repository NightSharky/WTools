#include "DbcFile.h"

DbcFile::DbcFile(std::string _path)
{
	path = _path;

	CreateStructures();

	LoadFromFile();
}

DbcFile::~DbcFile()
{
	
}

uint32 DbcFile::LoadFromFile()
{
	file.open(path.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
	file.seekg(0, file.end);
	filesize = file.tellg();
	file.seekg(0, file.beg);
	buffer.resize(filesize);
	file.read(&buffer[0], filesize);
	file.close();


	// Read file info
	std::memcpy(&info, &buffer[0], sizeof(info));

	if(info.Fields != structures[path].length())
		throw new std::string("Failed in select structure for this file.");

	PrintTable();
}

uint32 DbcFile::SaveToFile()
{
	file.open(path.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
	file.write((char*)&buffer, sizeof(std::string));
	file.close();
}

void DbcFile::CreateStructures()
{
	structures["test.dbc"] = "uuuufissssuuuuiu";
	structures["CreatureDisplayInfo.dbc"] = "uuuufissssuuuuiu";
}

void DbcFile::PrintTable()
{
	std::cout << info.Signature[0] << info.Signature[1] << info.Signature[2] << info.Signature[3] 
		<< " " << info.Records 
		<< "x" << info.Fields 
		<< "\n\t" << info.Record_Size 
		<< "/" << info.String_Block_Size 
		<< std::endl; 

	for (int i = 0; i < 3; ++i) //řádky
	{
		for (int o = 0; o < info.Fields; ++o) //sloupce
		{
			//if(structures[path][o] == 'u')
		}
	}

}