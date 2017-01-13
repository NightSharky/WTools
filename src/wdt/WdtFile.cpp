#include "WdtFile.h"

WdtFile::WdtFile(std::string _path)
{
	path = _path;

	LoadFromFile();


}

uint32 WdtFile::LoadFromFile()
{
	file.open(path.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
	file.seekg(0, file.end);
	filesize = file.tellg();
	file.seekg(0, file.beg);
	buffer.resize(filesize);
	file.read(&buffer[0], filesize);
	file.close();

	std::memcpy(&mver, &buffer[0], sizeof(mver));

	std::memcpy(&mphd, &buffer[sizeof(mver)], sizeof(mphd));

	std::memcpy(&main, &buffer[sizeof(mver)+sizeof(mphd)], sizeof(main));

	if(Mask(mphd.flags, MPHD_GLOBAL_OBJECT_IN_USE))
	{
		std::memcpy(&mwmo, &buffer[sizeof(mver)+sizeof(mphd)+sizeof(main)], sizeof(mwmo));
		mwmo_object = &buffer[sizeof(mver)+sizeof(mphd)+sizeof(main)+sizeof(mwmo)];

		std::memcpy(&modf, &buffer[sizeof(mver)+sizeof(mphd)+sizeof(main)+sizeof(mwmo)+mwmo.size], sizeof(modf));
	}


	return filesize;
}

void WdtFile::PrintScheme()
{
	std::cout << "Map version: " << mver.version << std::endl;
	std::cout << "Flags: " << mphd.flags;
	if(Mask(mphd.flags, MPHD_GLOBAL_OBJECT_IN_USE))
		std::cout << "\n\tMPHD_GLOBAL_OBJECT_IN_USE";
	if(Mask(mphd.flags, MPHD_VERTEX_SHADING))
		std::cout << "\n\tMPHD_VERTEX_SHADING";
	if(Mask(mphd.flags, MPHD_TERRAIN_SHADER))
		std::cout << "\n\tMPHD_TERRAIN_SHADER";
	if(Mask(mphd.flags, MPHD_DISABLES_SOMETHING))
		std::cout << "\n\tMPHD_DISABLES_SOMETHING";
	if(Mask(mphd.flags, MPHD_TERRAIN_SHADER_EXT))
		std::cout << "\n\tMPHD_TERRAIN_SHADER_EXT";
	std::cout << std::endl;

	if(!Mask(mphd.flags, MPHD_GLOBAL_OBJECT_IN_USE))
	{
		std::string occu = "█";
		std::string free = "░";
		
		for (int r = 0; r < 64; ++r)
		{
			for (int c = 0; c < 64; ++c)
			{
				if(Mask(main.chunk[r*64+c].flags, CHUNK_HAS_ADT))
					std::cout << occu;
				else
					std::cout << free;
			}
			std::cout << std::endl;
		}
	}
	else
	{
		std::cout << "There is no ADT file. Using GLOBAL_OBJECT instead." << std::endl;
		std::cout << "Used global object: \n\t" << mwmo_object << std::endl;

		std::cout << "\n\tID: " << modf.ID;
		std::cout << ",\tUID for instace: " << modf.unique_identifier_for_this_instance << std::endl;
		std::cout << "\tPosition X: " << modf.Position[0] 
			<< ", Y: " << modf.Position[1] 
			<< ", Z: " << modf.Position[2] << std::endl;
		std::cout << "\tOrientation X: " << modf.Orientation[0] 
			<< ", Y: " << modf.Orientation[1] 
			<< ", Z: " << modf.Orientation[2] << std::endl;
		std::cout << "\tBounding Box A: " << modf.Bounding_Box[0] 
			<< ", B: " << modf.Bounding_Box[1] 
			<< ", C: " << modf.Bounding_Box[2] 
			<< ", D: " << modf.Bounding_Box[3] 
			<< ", E: " << modf.Bounding_Box[4] 
			<< ", F: " << modf.Bounding_Box[5] << std::endl;
		std::cout << "\tFlags: " << modf.Flags << std::endl;
		std::cout << "\tDoodad set index: " << modf.Doodad_set_index << std::endl;
		std::cout << "\tName_set: " << modf.Name_set << std::endl;
		std::cout << "\tPadding: " << modf.Padding << std::endl;
	}
}
