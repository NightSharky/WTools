#ifndef WMOFILE_H
#define WMOFILE_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <map>

typedef unsigned int uint32;
typedef int int32;
typedef unsigned short uint16;
typedef short int16;

typedef struct 
{
	char marker[4];
	int size;
} ChunkBlock;

class WmoFile
{
	public:
		WmoFile(std::string _path);
		~WmoFile();
		uint32 LoadFromFile();
		void DetectBlocks();
	private:
		std::string path;
		uint32 filesize;
		std::fstream file;
		std::vector<char> buffer;
		std::vector<char>::iterator position;

		ChunkBlock block[1000];
		ChunkBlock tmp;
};

#endif