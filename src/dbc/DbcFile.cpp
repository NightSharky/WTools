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

uint32 DbcFile::GetUInt32(int offs)
{
	uint32 tmp;
	std::memcpy(&tmp, &buffer[offs], sizeof(tmp));
	return tmp;
}

int32 DbcFile::GetInt32(int offs)
{
	int32 tmp;
	std::memcpy(&tmp, &buffer[offs], sizeof(tmp));
	return tmp;
}

float DbcFile::GetFloat(int offs)
{
	float tmp;
	std::memcpy(&tmp, &buffer[offs], sizeof(tmp));
	return tmp;
}

std::string DbcFile::GetString(int offs)
{
	uint32 stroffset = GetUInt32(offs);
	
	int rpos = filesize - info.String_Block_Size + stroffset;

	char* flemch = &buffer[rpos];

	std::string str = flemch;

	return str;
}

void DbcFile::PrintTable()
{
	std::cout << info.Signature[0] 
		<< info.Signature[1] 
		<< info.Signature[2] 
		<< info.Signature[3] 
		<< ", Rows: " << info.Records 
		<< ", Fields: " << info.Fields 
		<< ", RSize: " << info.Record_Size 
		<< ", SBSize: " << info.String_Block_Size 
		<< std::endl; 

	for (int i = 0; i < info.Records; ++i) //řádky
	{
		for (int o = 0; o < info.Fields; ++o) //sloupce
		{
			int pos = sizeof(info) + (i * info.Record_Size) + (o * (info.Record_Size / info.Fields));
			if (structures[path][o] == 'u')
			{
				std::cout << GetUInt32(pos);
			}
			else if(structures[path][o] == 'i')
			{
				std::cout << GetInt32(pos);
			}
			else if(structures[path][o] == 'f')
			{
				std::cout << GetFloat(pos);
			}
			else if(structures[path][o] == 's')
			{
				std::cout << GetString(pos);
			}
			else
			{
				std::cout << "<unk>";
			}
			if(o!=info.Fields-1)
				std::cout << ", ";

		}
		std::cout << std::endl;
	}

}