/**
 * Class to represent a vehicle
 */

#ifndef H_VEHICLE
#define H_VEHICLE

#include <string>

namespace CarRentalAgency {

class Vehicle {
public:
    Vehicle(const std::string& licensePlate, const std::string& brand, int seatingCapacity);
    virtual ~Vehicle() = 0;

    std::string getLicensePlate() const;
    std::string getBrand() const;
    int getSeatingCapacity() const;

private:
    std::string m_licensePlate;
    std::string m_brand;
    int m_seatingCapacity;
};

class Sedan : public Vehicle {
public:
    Sedan(const std::string& license, const std::string& brand, bool hasSportsPackage);
};

class SUV : public Vehicle {
public:
    SUV(const std::string& license, const std::string& brand, bool hasThirdRowSeats);
};

#endif // H_VEHICLE

} // CarRentalAgency
