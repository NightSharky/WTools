#ifndef WDTFILE_H
#define WDTFILE_H

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
	char mark[4]; 	// block marker
	int size;		// block size
	int version;	// data0
} StructMVER;

typedef struct 
{
	char mark[4];
	int size;
	int flags;
	int something;
	int unused[6];
} StructMPHD;

enum flagsMPHD
{
	MPHD_GLOBAL_OBJECT_IN_USE 	= 0x01,
	MPHD_VERTEX_SHADING			= 0x02,
	MPHD_TERRAIN_SHADER			= 0x04,
	MPHD_DISABLES_SOMETHING		= 0x08,
	MPHD_TERRAIN_SHADER_EXT		= 0x10,
};

typedef struct 
{
	int flags;		// Chunk flags
	int unk;		// set in runtime
} Chunk;

typedef struct 
{
	char mark[4];
	int size;
	Chunk chunk[64*64];

} StructMAIN;

enum flagsChunk
{
	CHUNK_HAS_ADT	= 0x01,		// indicates existence of adt file
	CHUNK_LOADED	= 0x02, 	// only for client, only in runtime
};

typedef struct 
{
	char mark[4];
	int size;
} StructBlock;

typedef struct 
{
	char mark[4];	
	int size;
	uint32 ID; 			// (index in the MWID list)
	uint32 unique_identifier_for_this_instance;
	float Position[3]; 	// (X,Y,Z)
	float Orientation[3];	// (A,B,C)
	float Bounding_Box[6];
	uint16 Flags;
	uint16 Doodad_set_index;
	uint16 Name_set;
	uint16 Padding;

} StructMODF;

class WdtFile
{
	public:
		WdtFile(std::string _path);
		~WdtFile();

		void PrintScheme();
	private:
		uint32 LoadFromFile();
		bool Mask(int mask, int flags) { if((mask & flags) == flags) return true; else return false;};


		StructMVER mver;
		StructMPHD mphd;
		StructMAIN main;
		StructBlock mwmo;
		char* mwmo_object;
		StructMODF modf;

		std::string path;
		uint32 filesize;
		std::fstream file;
		std::vector<char> buffer;
		std::vector<char>::iterator position;

};

#endif