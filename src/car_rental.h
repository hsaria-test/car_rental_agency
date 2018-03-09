/**
 * Class to represent a car rental company
 */

#ifndef H_CARRENTAL
#define H_CARRENTAL

#include <memory>
#include <vector>

#include "vehicle.h"

namespace CarRentalAgency {

class CarRental {
public:
    CarRental();

    /**
     * Load current inventory from persistent store on startup
     * @return 0 on success and a non-zero on failure
     */
    int init();

    /**
     * Find a Vehicle to rent that matches the given minimum seating requirement
     * @return the Vehicle or Null if Vehicle is not found
     */
    std::shared_ptr<Vehicle> getVehicle(int minimumSeatingCapacity) const;

    /**
     * Find the Vehicle to rent with given license plate
     * @return the Vehicle or Null if Vehicle is not found
     */
    std::shared_ptr<Vehicle> getVehicle(const std::string& licensePlate) const;

    /**
     * Mark the given Vehicle as rented
     * @return zero on success and non-zero if vehicle is not found
     */
    int rentVehicle(const std::string& licensePlate);

    /**
     * Add returned Vehicle back to inventory
     * @return zero on success and non-zero if vehicle is not found
     */
    int returnVehicle(const std::string& licensePlate);

    /**
     * Add given Vehicle to inventory
     * @return zero on success non-zero if vehicle already exists
     */
    int addVehicle(const std::shared_ptr<Vehicle>& vehicle);

    /**
     * Remove given vehicle from inventory
     * @return zero on success and non-zero on error
     */
    int removeVehicle(const std::string& licensePlate);
    
private:
    typedef std::vector<std::shared_ptr<Vehicle> > VehicleList;
    VehicleList unrentedVehicleList;
    VehicleList rentedVehicleList;
    
    int move(VehicleList& dst, VehicleList& src, const std::string& licensePlate);
};

} // CarRentalAgency

#endif // H_CARRENTAL
