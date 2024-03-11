#define _CRT_SECURE_NO_WARNINGS

#include "Utils.h"

long int getLastAddressInFile(FILE* file)
{
	fseek(file, 0, SEEK_END);
	return ftell(file);
}

void writeBrand(Brands& brand, FILE* file)
{
	int id = brand.getId();
	int state = brand.getState();
	long int firstDevice = brand.getFirstDevice();
	fwrite(&id, sizeof(int), 1, file);
	fwrite(brand.getName(), sizeof(char), STRING_SIZE, file);
	fwrite(brand.getCountry(), sizeof(char), STRING_SIZE, file);
	fwrite(&state, sizeof(int), 1, file);
	fwrite(&firstDevice, sizeof(long int), 1, file);
}

void writeBrand(Brands& brand, long int address, FILE* file)
{
	fseek(file, address, SEEK_SET);
	writeBrand(brand, file);
}

void writeDevice(Devices& device, FILE* file)
{
	int id = device.getId();
	int brandId = device.getBrandId();
	int price = device.getPrice();
	long int previousDevice = device.getPreviousDevice();
	long int nextDevice = device.getNextDevice();
	int state = device.getState();
	fwrite(&id, sizeof(int), 1, file);
	fwrite(&brandId, sizeof(int), 1, file);
	fwrite(device.getName(), sizeof(char), STRING_SIZE, file);
	fwrite(&price, sizeof(int), 1, file);
	fwrite(&previousDevice, sizeof(long int), 1, file);
	fwrite(&nextDevice, sizeof(long int), 1, file);
	fwrite(&state, sizeof(int), 1, file);
}

void writeDevice(Devices& device, long int address, FILE* file)
{
	fseek(file, address, SEEK_SET);
	writeDevice(device, file);
}

Brands readBrand(FILE* file)
{
	char* name = new char[STRING_SIZE];
	char* country = new char[STRING_SIZE];
	int id;
	int state;
	long int firstDevice;
	fread(&id, sizeof(int), 1, file);
	fread(name, sizeof(char), STRING_SIZE, file);
	fread(country, sizeof(char), STRING_SIZE, file);
	fread(&state, sizeof(int), 1, file);
	fread(&firstDevice, sizeof(long int), 1, file);
	return { id, name, country, state, firstDevice };
}

Brands readBrand(FILE* file, long int address)
{
	fseek(file, address, SEEK_SET);
	return readBrand(file);
}

Devices readDevice(FILE* file)
{
	int id;
	int brandId;
	char* name = new char[STRING_SIZE];
	int price;
	long int previousDevice;
	long int nextDevice;
	int state;
	fread(&id, sizeof(int), 1, file);
	fread(&brandId, sizeof(int), 1, file);
	fread(name, sizeof(char), STRING_SIZE, file);
	fread(&price, sizeof(int), 1, file);
	fread(&previousDevice, sizeof(long int), 1, file);
	fread(&nextDevice, sizeof(long int), 1, file);
	fread(&state, sizeof(int), 1, file);
	return { id, brandId, name, price, previousDevice, nextDevice, state };
}

Devices readDevice(FILE* file, long int address)
{
	fseek(file, address, SEEK_SET);
	return readDevice(file);
}

bool fileEmpty(char* path)
{
	FILE* file = fopen(path, "rb");

	if (!file) return true;

	fseek(file, 0, SEEK_END);
	long int address = ftell(file);
	fclose(file);

	return address == 0;
}

bool fileEmpty(FILE* file)
{
	fseek(file, 0, SEEK_END);
	long int address = ftell(file);
	fseek(file, 0, SEEK_SET);
	return address == 0;
}