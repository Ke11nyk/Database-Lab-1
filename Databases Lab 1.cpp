#include "Menu.h"
#include "Functions.h"

int main()
{
	int err = 0;
	prepare((char*)"Brands.bin",
		(char*)"Garbage collector.bin",
		(char*)"Garbage collector D.bin",
		(char*)"Indices.bin",
		(char*)"Devices.bin",
		err);

	start();
	close(err);
}