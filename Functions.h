#ifndef INCLUDED_Functions_H
#define INCLUDED_Functions_H

#include "Brands.h"
#include "Utils.h"
#include "Devices.h"
#include <iostream>
#include <cstdio>
#include <algorithm> 

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::sort;

void prepare(char* brandsFilePath,
    char* freeSpacesAddressesFilePath,
    char* freeSpacesAddressesFilePathD,
    char* indexFilePath,
    char* devicesFilePath,
    int& error);

void writeAllBrands();

void writeAllDevices();

void close(int& error);

bool existsBrand(int id);

void insertBrand(Brands brand, int& error);

bool existsDevice(int id);

void insertDevice(Devices device, int& error);

void removeBrand(int id, int& error);

void removeDevice(int deviceId, int brandId, int& error);

void updateBrand(Brands brand, int id, int& error);

void updateDevice(Devices device, int brandId, int deviceId, int& error);

Brands getBrand(int id, int& error);

long findBrandAddress(int id);

Devices getDevice(int deviceId, int id, int& error);

long countAllBrands();

long countAllDevices();

long countDevicesForBrand(int brandId, int& error);

#endif // INCLUDED_Functions_H