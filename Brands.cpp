#include "Brands.h"

char* Brands::getName()
{
    return name;
}

char* Brands::getCountry()
{
    return country;
}

int Brands::getId() const
{
    return id;
}

void Brands::setName(char* newName)
{
    memcpy(name, newName, STRING_SIZE);
}

void Brands::setCountry(char* newCountry)
{
    memcpy(country, newCountry, STRING_SIZE);
}

void Brands::setId(int newId)
{
    id = newId;
}

void Brands::setState(int newState)
{
    state = newState;
}

int Brands::getState() const
{
    return state;
}

void Brands::setFirstDevice(long newFirstDevice)
{
    firstDevice = newFirstDevice;
}

long int Brands::getFirstDevice() const
{
    return firstDevice;
}

Brands::Brands(int id,
    const char* name,
    const char* country,
    int state,
    long firstDevice)
{
    this->id = id;
    memcpy(this->name, name, STRING_SIZE);
    memcpy(this->country, country, STRING_SIZE);
    this->state = state;
    this->firstDevice = firstDevice;
}

std::string Brands::toString()
{
    return "ID: " + std::to_string(id) + " | Name: " + name + " Country: " + country;
}

std::string Brands::toStringU()
{
    return "State: " + std::to_string(state) + " ID: " + std::to_string(id) + " | Name: " + name + " Country: " + country + " First device: " + std::to_string(firstDevice);
}