#include "Devices.h"

void Devices::setId(int newId)
{
    id = newId;
}

int Devices::getId() const
{
    return id;
}

void Devices::setBrandId(int newBrandId)
{
    brandId = newBrandId;
}

int Devices::getBrandId() const
{
    return brandId;
}

void Devices::setName(char* newName)
{
    memcpy(name, newName, STRING_SIZE);
}

char* Devices::getName()
{
    return name;
}

void Devices::setPrice(int newPrice)
{
    price = newPrice;
}

int Devices::getPrice() const
{
    return price;
}

void Devices::setNextDevice(long int newNextDevice)
{
    nextDevice = newNextDevice;
}

long int Devices::getNextDevice() const
{
    return nextDevice;
}

void Devices::setPreviousDevice(long int newPreviousDevice)
{
    previousDevice = newPreviousDevice;
}

long int Devices::getPreviousDevice() const
{
    return previousDevice;
}

void Devices::setState(int newState)
{
    state = newState;
}

int Devices::getState() const
{
    return state;
}

std::string Devices::toString()
{
    return "ID: " + std::to_string(id) + " | " + "Brand ID: " + std::to_string(brandId) + " Name: " + name + " Price: " + std::to_string(price) + " UAH";
}

std::string Devices::toStringU()
{
    return "State: " + std::to_string(state) + " ID: " + std::to_string(id) + " | " + "Brand ID: " + std::to_string(brandId) + " Name: " + name + " Price: " + std::to_string(price) + " UAH" + " Previous: " + std::to_string(previousDevice) + " Next: " + std::to_string(price);
}

Devices::Devices(int id,
    int brandId,
    const char* name,
    int price,
    long previousDevice,
    long nextDevice,
    int state)
{
    this->id = id;
    this->brandId = brandId;
    memcpy(this->name, name, STRING_SIZE);
    this->price = price;
    this->nextDevice = nextDevice;
    this->state = state;
    this->previousDevice = previousDevice;
}