#include "Menu.h"

const string MAIN_MENU_OPTIONS_TEXT = "----------------  MENU  -----------------\n"
"| \033[31m[0] - Exit\033[0m                            |\n| [1]"
" - New brand			| insert-m\n| [2] - Find brand      		| get-m\n| [3]"
" - Delete brand			| del-m\n| [4] - Edit brand                      | update-m\n| [5]"
" - New device                      | insert-s\n| [6] - Find device                     | get-s\n| [7]"
" - Delete device                   | del-s\n| [8] - Edit device                     | update-s\n| [9]"
" - How many brands?		| calc-m\n| [10] - How many devices?              | calc-s\n| [11]"
" - Count devices for the brand	| calc-s1\n| [12]"
" - Write all brands		| ut-m\n| [13]"
" - Write all devices		| ut-s\n"
"-----------------------------------------\n\n"
"Type option: ";

const string MAIN_MENU_WRONG_INPUT = "\nPlease type value between 0 and 13";

const string BRAND_ID_REQUEST_TEXT = "\nType id of a brand";
const string BRAND_NEW_ID_REQUEST_TEXT = "\nType new id of a brand";

const string NEW_BRAND_NAME_REQUEST_TEXT = "Type name of a new brand";
const string BRAND_NEW_NAME_REQUEST_TEXT = "\nType a new name for the brand";

const string NEW_BRAND_COUNTRY_REQUEST_TEXT = "Type country of a new brand";
const string BRAND_NEW_COUNTRY_REQUEST_TEXT = "\nType new country for the brand";

const string ID_IS_ALREADY_USED_TEXT = "\nSorry this id is already occupied";

const string BRAND_SUCCESSFULLY_ADDED_TEXT = "\nSuccessfully added brand";
const string BRAND_SUCCESSFULLY_DELETED_TEXT = "\nSuccessfully deleted brand";

const string BRAND_SELECT_FIELD_TO_UPDATE = "\n(0) stop updating\n(1) name\n(2) country\n(3) id";

const string BRAND_SUCCESSFULLY_UPDATED_TEXT = "\nBrand was successfully updated";

const string DEVICE_ID_REQUEST_TEXT = "Type id of a device";

const string NEW_DEVICE_ID_REQUEST_TEXT = "Type an id of a new device";
const string NEW_DEVICE_BRAND_ID_REQUEST_TEXT = "Type an id of a brand of new device";
const string NEW_DEVICE_NAME_REQUEST_TEXT = "Type a name of this device";
const string NEW_DEVICE_PRICE_REQUEST_TEXT = "Type a price in this device";
const string DEVICE_SUCCESSFULLY_ADDED_TEXT = "\nDevice was successfully added";

const string DEVICE_SUCCESSFULLY_DELETED_TEXT = "\nDevice was successfully deleted";

const string DEVICE_SELECT_FIELDS_TO_UPDATE_TEXT = "\n(0) stop updating\n(1) name\n(2) price\n(3) id\n(4) brand id";
const string DEVICE_NEW_BRAND_ID_REQUEST_TEXT = "\nType a new brand id of a device";
const string DEVICE_NEW_ID_REQUEST_TEXT = "\nType a new id of a device";
const string DEVICE_NEW_PRICE_REQUEST_TEXT = "\nType new price of a device";
const string DEVICE_NEW_NAME_REQUEST_TEXT = "\nType a new name of a device";

const string ALL_BRANDS_COUNT_RESULT_TEXT = "\nBrands count: ";
const string ALL_DEVICES_COUNT_RESULT_TEXT = "\nDevices count: ";
const string DIRECTORS_DEVICES_COUNT_RESULT_TEXT = "\nSpecified brand's devices count: ";

int readInt(const string& text)
{
	int value;
	cout << text << endl;
	cin >> value;

	if (!cin) cin.clear();

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return value;
}

char* readString(const string& text)
{
	char* string = new char[STRING_SIZE];
	cout << text << endl;
	cin.getline(string, STRING_SIZE);
	return string;
}

void addBrandMenu()
{
	int id;
	while (true)
	{
		id = readInt(BRAND_ID_REQUEST_TEXT);

		if (existsBrand(id))
		{
			cout << ID_IS_ALREADY_USED_TEXT << endl;
			continue;
		}

		break;
	}

	char* name = readString(NEW_BRAND_NAME_REQUEST_TEXT);
	char* country = readString(NEW_BRAND_COUNTRY_REQUEST_TEXT);

	int error = 0;
	insertBrand(Brands(id, name, country), error);

	if (error)
	{
		printError(error);
		error = 0;
		return;
	}
	cout << BRAND_SUCCESSFULLY_ADDED_TEXT << endl;
}

void getBrandMenu()
{
	int id = readInt(BRAND_ID_REQUEST_TEXT);

	int error = 0;
	Brands brand = getBrand(id, error);

	if (error)
	{
		printError(error);
		error = 0;
		return;
	}
	cout << brand.toString() << endl;
}

void removeBrandMenu()
{
	int id = readInt(BRAND_ID_REQUEST_TEXT), error = 0;
	removeBrand(id, error);
	if (error)
	{
		printError(error);
		error = 0;
		return;
	}
	cout << BRAND_SUCCESSFULLY_DELETED_TEXT << endl;
}

void updateBrandName(Brands& brand)
{
	char* name = readString(BRAND_NEW_NAME_REQUEST_TEXT);
	brand.setName(name);
}

void updateBrandCountry(Brands& brand)
{
	char* country = readString(BRAND_NEW_COUNTRY_REQUEST_TEXT);
	brand.setCountry(country);
}

void updateBrandId(Brands& brand)
{
	int id = readInt(BRAND_NEW_ID_REQUEST_TEXT);
	brand.setId(id);
}

void updateBrandFields(Brands& brand)
{
	int option;
	do
	{
		option = readInt(BRAND_SELECT_FIELD_TO_UPDATE);
		switch (option)
		{
		case 0:
			break;
		case 1:
			updateBrandName(brand);
			break;
		case 2:
			updateBrandCountry(brand);
			break;
		case 3:
			updateBrandId(brand);
			break;
		default:
			break;
		}
	} while (option != 0);
}

void updateBrandMenu()
{
	int id = readInt(BRAND_ID_REQUEST_TEXT), error = 0;
	Brands brand = getBrand(id, error);

	if (error)
	{
		printError(error);
		error = 0;
		return;
	}

	updateBrandFields(brand);

	updateBrand(brand, id, error);

	if (error)
	{
		printError(error);
		error = 0;
		return;
	}

	cout << BRAND_SUCCESSFULLY_UPDATED_TEXT << endl;
}

void addDeviceMenu()
{
	int deviceId;
	int brandId;

	while (true)
	{
		deviceId = readInt(DEVICE_ID_REQUEST_TEXT);
		brandId = readInt(BRAND_ID_REQUEST_TEXT);

		if (existsDevice(deviceId))
		{
			cout << ID_IS_ALREADY_USED_TEXT << endl;
			continue;
		}

		break;
	}

	char* name = readString(NEW_DEVICE_NAME_REQUEST_TEXT);
	int pagesNumber = readInt(NEW_DEVICE_PRICE_REQUEST_TEXT);

	int error = 0;
	insertDevice(Devices(deviceId, brandId, name, pagesNumber), error);

	if (error)
	{
		printError(error);
		error = 0;
		return;
	}

	cout << DEVICE_SUCCESSFULLY_ADDED_TEXT << endl;
}

void getDeviceMenu()
{
	int brandId = readInt(BRAND_ID_REQUEST_TEXT);
	int deviceId = readInt(DEVICE_ID_REQUEST_TEXT);

	int error = 0;
	Devices device = getDevice(brandId, deviceId, error);
	if (error)
	{
		printError(error);
		error = 0;
		return;
	}

	Brands brand = getBrand(brandId, error);
	if (error)
	{
		printError(error);
		error = 0;
		return;
	}

	cout << device.toString() << endl;
}

void removeDeviceMenu()
{
	int brandId = readInt(BRAND_ID_REQUEST_TEXT);
	int deviceId = readInt(DEVICE_ID_REQUEST_TEXT);

	int error = 0;
	removeDevice(brandId, deviceId, error);
	if (error)
	{
		printError(error);
		error = 0;
		return;
	}
	cout << DEVICE_SUCCESSFULLY_DELETED_TEXT << endl;
}

void updateDeviceName(Devices& device)
{
	char* name = readString(DEVICE_NEW_NAME_REQUEST_TEXT);
	device.setName(name);
}

void updateDevicePrice(Devices& device)
{
	int price = readInt(DEVICE_NEW_PRICE_REQUEST_TEXT);
	device.setPrice(price);
}

void updateDeviceId(Devices& device)
{
	int id = readInt(DEVICE_NEW_ID_REQUEST_TEXT);
	device.setId(id);
}

void updateDeviceBrandId(Devices& device)
{
	int brandId = readInt(DEVICE_NEW_BRAND_ID_REQUEST_TEXT);
	device.setBrandId(brandId);
}

void updateDeviceFields(Devices& device)
{
	int options;
	do
	{
		options = readInt(DEVICE_SELECT_FIELDS_TO_UPDATE_TEXT);
		switch (options)
		{
		case 1:
			updateDeviceName(device);
			break;
		case 2:
			updateDevicePrice(device);
			break;
		case 3:
			updateDeviceId(device);
			break;
		case 4:
			updateDeviceBrandId(device);
			break;
		default:
			break;
		}
	} while (options != 0);
}

void updateDeviceMenu()
{
	int brandId = readInt(BRAND_ID_REQUEST_TEXT);
	int deviceId = readInt(DEVICE_ID_REQUEST_TEXT);

	int error = 0;
	Devices device = getDevice(brandId, deviceId, error);
	if (error)
	{
		printError(error);
		error = 0;
		return;
	}
	updateDeviceFields(device);
	updateDevice(device, brandId, deviceId, error);
}

void countAllBrandsMenu()
{
	cout << ALL_BRANDS_COUNT_RESULT_TEXT << countAllBrands() << endl;
}

void coutAllDevicesMenu()
{
	cout << ALL_DEVICES_COUNT_RESULT_TEXT << countAllDevices() << endl;
}

void countAllDevicesForBrandMenu()
{
	int brandId = readInt(BRAND_ID_REQUEST_TEXT), error = 0;
	long count = countDevicesForBrand(brandId, error);
	if (error)
	{
		printError(error);
		return;
	}
	cout << DIRECTORS_DEVICES_COUNT_RESULT_TEXT << count << endl;
}

void start()
{
	int option;
	do
	{
		cout << "\n";
		option = readInt(MAIN_MENU_OPTIONS_TEXT);
		switch (option)
		{
		case 0:
			break;
		case 1:
			addBrandMenu();
			break;
		case 2:
			getBrandMenu();
			break;
		case 3:
			removeBrandMenu();
			break;
		case 4:
			updateBrandMenu();
			break;
		case 5:
			addDeviceMenu();
			break;
		case 6:
			getDeviceMenu();
			break;
		case 7:
			removeDeviceMenu();
			break;
		case 8:
			updateDeviceMenu();
			break;
		case 9:
			countAllBrandsMenu();
			break;
		case 10:
			coutAllDevicesMenu();
			break;
		case 11:
			countAllDevicesForBrandMenu();
			break;
		case 12:
			writeAllBrands();
			break;
		case 13:
			writeAllDevices();
			break;
		default:
			cout << MAIN_MENU_WRONG_INPUT << endl;
			break;
		}
	} while (option != 0);
}