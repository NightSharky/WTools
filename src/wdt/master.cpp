#include <iostream>
#include <string>

#include "WdtFile.h"

int main(int argc, char ** argv)
{
	WdtFile* wdt = new WdtFile("test.wdt");
	wdt->PrintScheme();
	return 0;
}