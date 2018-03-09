/**
 * Implementation of Vehicle, Sedan, SUV classes
 */

#include "vehicle.h"

using namespace std;

namespace {
    const int DefaultFourWheelerSeatingCapacity = 5;
    const int DefaultThirdRowCapacity = 3;
}

namespace CarRentalAgency {

Vehicle::Vehicle(const string& licensePlate, const string& brand, int seatingCapacity)
    : m_licensePlate(licensePlate),
      m_brand(brand),
      m_seatingCapacity(seatingCapacity)
{
}

Vehicle::~Vehicle() 
{
}

string Vehicle::getLicensePlate() const
{
    return m_licensePlate;
}
    
string Vehicle::getBrand() const
{
    return m_brand;
}
    
int Vehicle::getSeatingCapacity() const
{
    return m_seatingCapacity;
}

Sedan::Sedan(const string& licensePlate, const string& brand, bool hasSportsPackage)
    : Vehicle(licensePlate, brand, DefaultFourWheelerSeatingCapacity)
{        
}

SUV::SUV(const string& licensePlate, const string& brand, bool hasThirdRowSeats)
    : Vehicle(
        licensePlate,
        brand,
        (hasThirdRowSeats ? DefaultFourWheelerSeatingCapacity + DefaultThirdRowCapacity :
         DefaultFourWheelerSeatingCapacity))
{
}

} // CarRentalAgency
