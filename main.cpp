#include <iostream>

#include "Screen.h"

int main(int argc, char** argv)
{
	auto screen = new Screen("Tiling with Geometry", 1024, 768);
	screen->Init();

	return 0;
}
