#include "Errors.h"
#include "Constants.h"

const char* CAN_NOT_LOAD_INDEX_FILE_ERROR_TEXT = "CAN'T LOAD INDEX FILE";

const char* CAN_NOT_LOAD_FREE_SPACES_FILE_ERROR_TEXT = "CAN'T LOAD FREE SPACES FILE";

const char* CAN_NOT_LOAD_BRANDS_FILE_ERROR_TEXT = "CAN'T LOAD BRANDS FILE";

const char* CAN_NOT_LOAD_DEVICES_FILE_ERROR_TEXT = "CAN'T LOAD DEVICES FILE";

const char* CAN_NOT_FIND_BRAND_ERROR_TEXT = "CAN'T FIND BRANDS WITH SPECIFIED ID";

const char* CAN_NOT_FIND_DEVICE_ERROR_TEXT = "CAN'T FIND DEVICES WITH SPECIFIED ID";

map<int, const char*> ERRORS_MAP =
{
	{CAN_NOT_LOAD_INDEX_FILE_ERROR_CODE, CAN_NOT_LOAD_INDEX_FILE_ERROR_TEXT},
	{CAN_NOT_LOAD_FREE_SPACES_FILE_ERROR_CODE, CAN_NOT_LOAD_FREE_SPACES_FILE_ERROR_TEXT},
	{CAN_NOT_LOAD_BRANDS_FILE_ERROR_CODE, CAN_NOT_LOAD_BRANDS_FILE_ERROR_TEXT},
	{CAN_NOT_LOAD_DEVICES_FILE_ERROR_CODE, CAN_NOT_LOAD_DEVICES_FILE_ERROR_TEXT},
	{CAN_NOT_FIND_BRAND_ERROR_CODE, CAN_NOT_FIND_BRAND_ERROR_TEXT},
	{CAN_NOT_FIND_DEVICE_ERROR_CODE, CAN_NOT_FIND_DEVICE_ERROR_TEXT}
};

void printError(int error)
{
	cout << "\nERROR " << error << ": " << ERRORS_MAP[error] << endl;
}