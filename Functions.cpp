#define _CRT_SECURE_NO_WARNINGS

#include "Functions.h"
#include "Utils.h"

vector<pair<int, long int>> indices;
vector <long int> garbage;
vector <long int> garbageD;
FILE* brandsF;
FILE* devicesF;
char* garbageAddresses;
char* garbageAddressesD;
char* indexAddresses;

int findBrandInIndex(int id)
{
	int l = 0, r = (int)indices.size() - 1, mid;
	while (r >= l)
	{
		mid = (l + r) / 2;
		if (indices[mid].first == id)
		{
			return mid;
		}
		if (indices[mid].first > id)
		{
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	return ABSENT_MARK;
}

void writeAllBrands()
{
	int i = 0;
	int size = sizeof(int) * 2 + sizeof(char) * 2 * STRING_SIZE + sizeof(long int);

	while (!feof(brandsF))
	{
		fseek(brandsF, size * i, SEEK_SET);
		Brands brand = readBrand(brandsF);
		if(brand.getId() != -858993460) cout << brand.toStringU() << endl;
		i++;
	}
}

void writeAllDevices()
{
	int i = 0, error = 0;
	int size = sizeof(int) * 4 + sizeof(char) * STRING_SIZE + sizeof(long int) * 2;

	while (!feof(devicesF))
	{
		fseek(devicesF, size * i, SEEK_SET);
		Devices device = readDevice(devicesF);
		if (device.getId() != -858993460) cout << device.toStringU() << endl;
		i++;
	}
}

long int findBrandAddress(int id)
{
	int index = findBrandInIndex(id);
	return index == ABSENT_MARK ? ABSENT_MARK : indices[index].second;
}

void loadIndices(int& error)
{
	FILE* file = fopen(indexAddresses, "rb+");

	if (!file)
	{
		error = CAN_NOT_LOAD_INDEX_FILE_ERROR_CODE;
		return;
	}
	if (!fileEmpty(file))
	{
		int id;
		long int position;

		fread(&id, sizeof(int), 1, file);
		fread(&position, sizeof(long int), 1, file);
		while (!feof(file))
		{
			indices.emplace_back(id, position);
			fread(&id, sizeof(int), 1, file);
			fread(&position, sizeof(long int), 1, file);
		}
	}
	fclose(file);
}

void writeIndices(int& error)
{
	FILE* file = fopen(indexAddresses, "wb+");

	if (!file)
	{
		error = CAN_NOT_LOAD_INDEX_FILE_ERROR_CODE;
		return;
	}
	for (pair<int, long int>& item : indices)
	{
		fwrite(&item.first, sizeof(int), 1, file);
		fwrite(&item.second, sizeof(long int), 1, file);
	}
	fclose(file);
}

void loadFreeSpaceAddresses(int& error)
{
	if (fileEmpty(garbageAddresses) || fileEmpty(garbageAddressesD))
	{
		return;
	}

	FILE* file = fopen(garbageAddresses, "rb+");
	FILE* fileD = fopen(garbageAddressesD, "rb+");

	if (!file || !fileD)
	{
		error = CAN_NOT_LOAD_FREE_SPACES_FILE_ERROR_CODE;
		return;
	}

	int freeSpace, freeSpaceD;
	do
	{
		fread(&freeSpace, sizeof(long int), 1, file);
		garbage.push_back(freeSpace);
	} while (!feof(file));

	do
	{
		fread(&freeSpaceD, sizeof(long int), 1, fileD);
		garbageD.push_back(freeSpaceD);
	} while (!feof(fileD));

	fclose(file);
	fclose(fileD);
}

void writeFreeSpaceAddresses(int& error)
{
	FILE* file = fopen(garbageAddresses, "wb+");
	FILE* fileD = fopen(garbageAddressesD, "wb+");

	if (!file || !fileD)
	{
		error = CAN_NOT_LOAD_FREE_SPACES_FILE_ERROR_CODE;
		return;
	}

	for (long int freeSpace : garbage)
	{
		fwrite(&freeSpace, sizeof(int), 1, file);
	}

	for (long int freeSpaceD : garbageD)
	{
		fwrite(&freeSpaceD, sizeof(int), 1, fileD);
	}

	fclose(file);
	fclose(fileD);
}

long int findDeviceAddress(int brandId, int deviceId, int& error)
{
	long int address = getBrand(brandId, error).getFirstDevice();
	if (error)
	{
		return ABSENT_MARK;
	}
	while (address != END_MARK)
	{
		Devices device = readDevice(devicesF, address);
		if (device.getId() == deviceId)
		{
			break;
		}
		address = device.getNextDevice();
	}
	return address;
}

void prepare(char* brandsFilePath,
	char* freeSpacesAddressesFilePath,
	char* freeSpacesAddressesFilePathD,
	char* indexFilePath,
	char* devicesFilePath,
	int& error)
{
	brandsF = fopen(brandsFilePath, "rb+");
	if (!brandsF)
	{
		error = CAN_NOT_LOAD_BRANDS_FILE_ERROR_CODE;
		return;
	}

	garbageAddresses = freeSpacesAddressesFilePath;
	garbageAddressesD = freeSpacesAddressesFilePathD;

	loadFreeSpaceAddresses(error);
	if (error)
	{
		return;
	}

	indexAddresses = indexFilePath;
	loadIndices(error);
	if (error)
	{
		return;
	}

	devicesF = fopen(devicesFilePath, "rb+");
	if (!devicesF)
	{
		error = CAN_NOT_LOAD_DEVICES_FILE_ERROR_CODE;
		return;
	}
}

void close(int& error)
{
	fclose(brandsF);

	writeFreeSpaceAddresses(error);
	if (error)
	{
		return;
	}

	writeIndices(error);
	if (error)
	{
		return;
	}

	fclose(devicesF);
}

bool existsBrand(int id)
{
	return findBrandAddress(id) != END_MARK;
}

void insertBrand(Brands brand, int& error)
{
	if (garbage.empty())
	{
		fseek(brandsF, 0, SEEK_END);
	}
	else
	{
		fseek(brandsF, garbage.back(), SEEK_SET);
		garbage.pop_back();
	}
	indices.emplace_back(brand.getId(), ftell(brandsF));
	sort(begin(indices), end(indices));
	writeBrand(brand, brandsF);
}

bool existsDevice(int id)
{
	int i = 0, error = 0;
	int size = sizeof(int) * 4 + sizeof(char) * STRING_SIZE + sizeof(long int) * 2;
	fopen("Devices.bin", "rb+");

	while (!feof(devicesF))
	{
		fseek(devicesF, size * i, SEEK_SET);
		Devices device = readDevice(devicesF);
		if (id == device.getId()) return true;
		i++;
	}

	return false;
}

void insertDevice(Devices device, int& error)
{
	Brands brand = getBrand(device.getBrandId(), error);
	if (error)
	{
		return;
	}

	long int newDeviceAddress;

	if (garbageD.empty())
	{
		fseek(devicesF, 0, SEEK_END);
		newDeviceAddress = ftell(devicesF);
	}
	else
	{
		fseek(devicesF, garbageD.back(), SEEK_SET);
		newDeviceAddress = ftell(devicesF);
		garbageD.pop_back();
	}

	device.setNextDevice(brand.getFirstDevice());
	writeDevice(device, devicesF);

	Devices nextDevice = readDevice(devicesF, brand.getFirstDevice());
	nextDevice.setPreviousDevice(newDeviceAddress);
	writeDevice(nextDevice, brand.getFirstDevice(), devicesF);

	brand.setFirstDevice(newDeviceAddress);
	updateBrand(brand, brand.getId(), error);
}

void removeBrand(int id, int& error)
{
	int index = findBrandInIndex(id);
	if (index == ABSENT_MARK)
	{
		error = CAN_NOT_FIND_BRAND_ERROR_CODE;
		return;
	}

	long int address = indices[index].second;
	Brands brand = readBrand(brandsF, address);
	brand.setState(DEVICE_REMOVED_STATE);
	writeBrand(brand, address, brandsF);

	long addressD = brand.getFirstDevice(), result = 0;

	while (!error && addressD != END_MARK) {
		Devices device = readDevice(devicesF, addressD);
		device.setState(DEVICE_REMOVED_STATE);
		writeDevice(device, addressD, devicesF);
		garbageD.push_back(addressD);
		addressD = device.getNextDevice();
	}

	garbage.push_back(address);
	indices.erase(begin(indices) + index);
}

void removeDevice(int brandId, int deviceId, int& error)
{
	long int deviceAddress = findDeviceAddress(brandId, deviceId, error);
	if (error)
	{
		return;
	}
	if (deviceAddress == ABSENT_MARK)
	{
		error = CAN_NOT_FIND_DEVICE_ERROR_CODE;
		return;
	}

	Devices device = readDevice(devicesF, deviceAddress);

	if (device.getPreviousDevice() == ABSENT_MARK)
	{
		Brands brand = getBrand(brandId, error);
		brand.setFirstDevice(device.getNextDevice());
		updateBrand(brand, brand.getId(), error);
	}
	else
	{
		Devices previousDevice = readDevice(devicesF, device.getPreviousDevice());
		previousDevice.setNextDevice(device.getNextDevice());
		updateDevice(previousDevice, brandId, previousDevice.getId(), error);
	}

	device.setState(DEVICE_REMOVED_STATE);
	writeDevice(device, deviceAddress, devicesF);

	garbageD.push_back(deviceAddress);
}

void updateBrand(Brands brand, int id, int& error)
{
	long int address = findBrandAddress(id);
	if (address == ABSENT_MARK)
	{
		error = CAN_NOT_FIND_BRAND_ERROR_CODE;
		return;
	}
	writeBrand(brand, address, brandsF);
}

void updateDevice(Devices device, int brandId, int id, int& error)
{
	long address = findDeviceAddress(brandId, id, error);
	if (error)
	{
		return;
	}
	if (address == ABSENT_MARK)
	{
		error = CAN_NOT_FIND_DEVICE_ERROR_CODE;
		return;
	}
	writeDevice(device, address, devicesF);
}

Brands getBrand(int id, int& error)
{
	long address = findBrandAddress(id);
	if (address == ABSENT_MARK)
	{
		error = CAN_NOT_FIND_BRAND_ERROR_CODE;
		return {};
	}
	return readBrand(brandsF, address);
}

Devices getDevice(int brandId, int id, int& error)
{
	long int address = findDeviceAddress(brandId, id, error);
	if (error)
	{
		return {};
	}
	if (address == ABSENT_MARK)
	{
		error = CAN_NOT_FIND_DEVICE_ERROR_CODE;
		return {};
	}
	return readDevice(devicesF, address);
}

long countAllBrands()
{
	return (long)indices.size();
}

long countDevicesForBrand(int brandId, int& error)
{
	long address = getBrand(brandId, error).getFirstDevice(), result = 0;
	if (error)
	{
		return 0;
	}
	while (address != END_MARK) {
		Devices device = readDevice(devicesF, address);
		address = device.getNextDevice();
		result += device.getState() == DEVICE_ACTIVE_STATE;
	}
	return result;
}

long countAllDevices()
{
	int error = 0;
	long result = 0;
	for (auto& g : indices)
	{
		result += countDevicesForBrand(g.first, error);
	}
	return result;
}