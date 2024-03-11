#ifndef INCLUDED_Devices_H
#define INCLUDED_Devices_H

#include "Constants.h"
#include <vector>
#include <string>

struct Devices
{
private:
	int id{};
	int brandId{};
	char* name = new char[STRING_SIZE];
	int price = 0;
	long int nextDevice = -1;
	long int previousDevice = -1;
	int state{};

public:
	void setId(int newId);

	int getId() const;

	void setBrandId(int newBrandId);

	int getBrandId() const;

	void setName(char* newName);

	char* getName();

	void setPrice(int newPrice);

	int getPrice() const;

	void setNextDevice(long int newNextDevice);

	long int getNextDevice() const;

	void setPreviousDevice(long int newPreviousDevice);

	long int getPreviousDevice() const;

	void setState(int newState);

	int getState() const;

	std::string toString();

	std::string toStringU();

	Devices(int id,
		int brandId,
		const char* name,
		int price,
		long previousDevice = END_MARK,
		long nextDevice = END_MARK,
		int state = DEVICE_ACTIVE_STATE);

	Devices() = default;
};


#endif  // INCLUDED_Devices_H