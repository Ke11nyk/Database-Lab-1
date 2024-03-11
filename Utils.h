#ifndef INCLUDED_Utils_H
#define INCLUDED_Utils_H

#include <iostream>
#include "Brands.h"
#include "Devices.h"
#include <vector>

long int getLastAddressInFile(FILE* file);

void writeBrand(Brands& brand, FILE* file);

void writeBrand(Brands& brand, long int address, FILE* file);

void writeDevice(Devices& device, FILE* file);

void writeDevice(Devices& device, long int address, FILE* file);

Brands readBrand(FILE* file);

Brands readBrand(FILE* file, long int address);

Devices readDevice(FILE* file);

Devices readDevice(FILE* file, long int address);

bool fileEmpty(char* path);

bool fileEmpty(FILE* file);

#endif // !INCLUDED_Utils_H