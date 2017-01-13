#include <iostream>
#include <string>

#include "WmoFile.h"

int main(int argc, char ** argv)
{
	WmoFile* wmo = new WmoFile("test.wmo");
	wmo->LoadFromFile();
	wmo->DetectBlocks();
	return 0;
}