/**
 * Implementation of CarRental class
 */

#include <algorithm>

#include "car_rental.h"

using namespace std;

namespace {
class LicensePlatePredicate : public unary_function<shared_ptr<CarRentalAgency::Vehicle>, bool>
{
public:
    LicensePlatePredicate(const string& licensePlate) : m_licensePlate(licensePlate) {}
    bool operator()(const shared_ptr<CarRentalAgency::Vehicle>& vehiclePtr) {
        return vehiclePtr->getLicensePlate() == m_licensePlate;
    }
private:
    const string m_licensePlate;
};

class SeatingCapacityPredicate : public unary_function<shared_ptr<CarRentalAgency::Vehicle>, bool>
{
public:
    SeatingCapacityPredicate(int seatingCapacity) : m_seatingCapacity(seatingCapacity) {}
    bool operator()(const shared_ptr<CarRentalAgency::Vehicle>& vehiclePtr) {
        return vehiclePtr->getSeatingCapacity() >= m_seatingCapacity;
    }
private:
    int m_seatingCapacity;
};

}

namespace CarRentalAgency {

CarRental::CarRental() 
{
}

int CarRental::init() 
{
    unrentedVehicleList.clear();
    rentedVehicleList.clear();
    /*
     * TODO
     * load vehicle inventory from persistent data store
     */
    return 0;
}

shared_ptr<Vehicle> CarRental::getVehicle(int minimumSeatingCapacity) const
{
    auto itr = find_if(unrentedVehicleList.begin(), unrentedVehicleList.end(),
                       SeatingCapacityPredicate(minimumSeatingCapacity));
    return (itr == unrentedVehicleList.end() ? shared_ptr<Vehicle>() : *itr);
}

shared_ptr<Vehicle> CarRental::getVehicle(const string& licensePlate) const
{
    auto itr = find_if(unrentedVehicleList.begin(), unrentedVehicleList.end(),
                       LicensePlatePredicate(licensePlate));
    return (itr == unrentedVehicleList.end() ? shared_ptr<Vehicle>() : *itr);
}

int CarRental::move(VehicleList& dst, VehicleList& src, const string& licensePlate) 
{
    auto itr = find_if(src.begin(), src.end(), LicensePlatePredicate(licensePlate));
    if (itr != src.end()) {
        shared_ptr<Vehicle> vehicle = *itr;
        src.erase(itr);
        dst.push_back(vehicle);
        return 0;
    }
    return 1;
}

int CarRental::rentVehicle(const string& licensePlate) 
{
    return move(rentedVehicleList, unrentedVehicleList, licensePlate);
}

int CarRental::returnVehicle(const string& licensePlate) 
{
    return move(unrentedVehicleList, rentedVehicleList, licensePlate);
}

int CarRental::addVehicle(const shared_ptr<Vehicle>& vehicle) 
{
    auto itr = find_if(unrentedVehicleList.begin(), unrentedVehicleList.end(),
                       LicensePlatePredicate(vehicle->getLicensePlate()));
    if (itr != unrentedVehicleList.end()) {
        return 1;
    }

    itr = find_if(rentedVehicleList.begin(), rentedVehicleList.end(),
                  LicensePlatePredicate(vehicle->getLicensePlate()));
    if (itr != rentedVehicleList.end()) {
        return 1;
    }
    
    unrentedVehicleList.push_back(vehicle);
    return 0;
}

int CarRental::removeVehicle(const string& licensePlate) 
{
    auto itr = find_if(unrentedVehicleList.begin(), unrentedVehicleList.end(),
                       LicensePlatePredicate(licensePlate));
    if (itr != unrentedVehicleList.end()) {
        unrentedVehicleList.erase(itr);
        return 0;
    }
    return 1;
}

} // CarRentalAgency
