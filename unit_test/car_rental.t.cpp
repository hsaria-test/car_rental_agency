
#include "gtest/gtest.h"

#include "car_rental.h"

using namespace CarRentalAgency;

namespace {
class TestCarRental : public testing::Test 
{
protected:
    virtual void SetUp() {
        carRental.init();
        
        m_sedanLicensePlate = "lic1";
        m_suvLicensePlate = "lic2";
        m_largeSuvLicensePlate = "lic3";
        m_sedanBrand = "brand1";
        m_suvBrand = "brand2";
        m_largeSuvBrand = "brand3";
        

        std::shared_ptr<Vehicle> sedan(new Sedan(m_sedanLicensePlate, m_sedanBrand, false));
        carRental.addVehicle(sedan);
        std::shared_ptr<Vehicle> suv(new SUV(m_suvLicensePlate, m_suvBrand, false));
        carRental.addVehicle(suv);
        std::shared_ptr<Vehicle> largeSuv(new SUV(m_largeSuvLicensePlate, m_largeSuvBrand, true));
        carRental.addVehicle(largeSuv);
    } 

    CarRental carRental;
    std::string m_sedanLicensePlate, m_suvLicensePlate, m_largeSuvLicensePlate;
    std::string m_sedanBrand, m_suvBrand, m_largeSuvBrand;
};

TEST_F(TestCarRental, GetSedan) 
{
    EXPECT_EQ(carRental.getVehicle(0)->getLicensePlate(), m_sedanLicensePlate);
}

TEST_F(TestCarRental, GetSUV) 
{
    EXPECT_EQ(carRental.getVehicle(m_suvLicensePlate)->getLicensePlate(), m_suvLicensePlate);
}

TEST_F(TestCarRental, GetLargeSUV) 
{
    EXPECT_EQ(carRental.getVehicle(8)->getLicensePlate(), m_largeSuvLicensePlate);
    EXPECT_FALSE(carRental.getVehicle(10));
}

TEST_F(TestCarRental, RentVehicle) 
{
    EXPECT_EQ(carRental.rentVehicle(m_suvLicensePlate), 0);
    EXPECT_FALSE(carRental.getVehicle(m_suvLicensePlate));
    EXPECT_EQ(carRental.returnVehicle(m_suvLicensePlate), 0);
    EXPECT_EQ(carRental.getVehicle(m_suvLicensePlate)->getLicensePlate(), m_suvLicensePlate);
}

TEST_F(TestCarRental, RemoveVehicel) 
{
    EXPECT_EQ(carRental.removeVehicle(m_largeSuvLicensePlate), 0);
    EXPECT_FALSE(carRental.getVehicle(8));
}

TEST_F(TestCarRental, ErrorTest) 
{
    std::shared_ptr<Vehicle> suv(new SUV(m_suvLicensePlate, m_suvBrand, false));
    EXPECT_NE(carRental.addVehicle(suv), 0);
    EXPECT_EQ(carRental.removeVehicle(m_sedanLicensePlate), 0);
    EXPECT_EQ(carRental.removeVehicle(m_suvLicensePlate), 0);
    EXPECT_EQ(carRental.removeVehicle(m_largeSuvLicensePlate), 0);

    EXPECT_FALSE(carRental.getVehicle(0));
    EXPECT_FALSE(carRental.getVehicle(m_sedanLicensePlate));
    EXPECT_NE(carRental.rentVehicle(m_sedanLicensePlate), 0);
    EXPECT_NE(carRental.returnVehicle(m_sedanLicensePlate), 0);
    EXPECT_NE(carRental.removeVehicle(m_sedanLicensePlate), 0);
}
    
}
