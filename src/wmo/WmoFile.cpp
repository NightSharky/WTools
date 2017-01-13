#include "WmoFile.h"

WmoFile::WmoFile(std::string _path)
{
	path = _path;
}

WmoFile::~WmoFile()
{

}

uint32 WmoFile::LoadFromFile()
{
	file.open(path.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
	file.seekg(0, file.end);
	filesize = file.tellg();
	file.seekg(0, file.beg);
	buffer.resize(filesize);
	file.read(&buffer[0], filesize);
	file.close();

	return filesize;
}

void WmoFile::DetectBlocks()
{
	int pos = 0;

	int count = 1000;

	for (int itr = 0; itr < count; ++itr)
	{
		if (pos > filesize)
			break;
		std::memcpy(&block[itr], &buffer[pos], sizeof(block[itr]));
		std::cout << "BlockId: " << itr+1 << ", Offset: " << pos << ", Block: " 
			<< block[itr].marker[3]
			<< block[itr].marker[2]
			<< block[itr].marker[1]
			<< block[itr].marker[0]
			<< ", Size: " << block[itr].size << std::endl;


		pos = pos + sizeof(block[itr]) + block[itr].size;
	}
	
}