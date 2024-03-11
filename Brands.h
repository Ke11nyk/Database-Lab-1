#ifndef INCLUDED_Brands_H
#define INCLUDED_Brands_H

#include "Constants.h"
#include <string>
#include <vector>
#include <cstdlib>

struct Brands
{
private:
	int id = -1;
	char* name = new char[STRING_SIZE];
	char* country = new char[STRING_SIZE];
	int state = BRAND_ACTIVE_STATE;
	long int firstDevice{};

public:
	char* getName();

	char* getCountry();

	int getId() const;

	void setName(char* newName);

	void setCountry(char* newCountry);

	void setId(int newId);

	void setState(int newState);

	int getState() const;

	void setFirstDevice(long int newFirstDevice);

	long int getFirstDevice() const;

	Brands(int id,
		const char* name,
		const char* country,
		int state = BRAND_ACTIVE_STATE,
		long int firstDevice = END_MARK);

	std::string toString();

	std::string toStringU();

	Brands() = default;
};

#endif // INCLUDED_Brands_H