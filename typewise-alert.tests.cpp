#include <gtest/gtest.h>
#include "typewise-alert.h"

// Define mock variables
BreachType MockControllerBreachType;
BreachType MockEmailBreachType;
bool isControllerAlertCalled = false;
bool isEmailAlertCalled = false;

// Define mock functions
void mockSendToController(BreachType breachType) {
    MockControllerBreachType = breachType;
    isControllerAlertCalled = true;
}

void mockSendToEmail(BreachType breachType) {
    MockEmailBreachType = breachType;
    isEmailAlertCalled = true;
}

// Assign mock functions to function pointers
void (*sendToControllerPtr)(BreachType) = mockSendToController;
void (*sendToEmailPtr)(BreachType) = mockSendToEmail;

// Reset function for mock variables
void resetMocks() {
    isControllerAlertCalled = false;
    isEmailAlertCalled = false;
    MockControllerBreachType = NORMAL;
    MockEmailBreachType = NORMAL;
}

// Test fixture class
class TypewiseAlertTest : public ::testing::Test {
protected:
    void SetUp() override {
        resetMocks();
    }

    void testAlertForCoolingType(AlertTarget alertTarget, CoolingType coolingType, double temperatureInC, BreachType expectedBreach) {
        BatteryCharacter batteryChar = {coolingType, "BrandX"};
        testing::internal::CaptureStdout();
        checkAndAlert(alertTarget, batteryChar, temperatureInC);
        std::string output = testing::internal::GetCapturedStdout();
        ASSERT_EQ(expectedBreach, classifyTemperatureBreach(coolingType, temperatureInC));
        if (alertTarget == TO_CONTROLLER) {
            validateControllerOutput(expectedBreach, output);
        } else if (alertTarget == TO_EMAIL) {
            validateEmailOutput(expectedBreach, output);
        }
    }

    void validateControllerOutput(BreachType expectedBreach, const std::string& output) {
        std::string expectedOutput = (expectedBreach == TOO_LOW) ? "feed : 1\n" :
                                     (expectedBreach == TOO_HIGH) ? "feed : 2\n" :
                                     "feed : 0\n";
        ASSERT_EQ(output, expectedOutput);
    }

    void validateEmailOutput(BreachType expectedBreach, const std::string& output) {
        std::string expectedOutput = (expectedBreach == TOO_LOW) ? "To: a.b@c.com\nHi, the temperature is too low\n" :
                                     (expectedBreach == TOO_HIGH) ? "To: a.b@c.com\nHi, the temperature is too high\n" :
                                     "";
        ASSERT_EQ(output, expectedOutput);
    }
};

// Test Cases for Passive Cooling
TEST_F(TypewiseAlertTest, PassiveCooling_ToController_NormalTemperature) {
    testAlertForCoolingType(TO_CONTROLLER, PASSIVE_COOLING, 20, NORMAL);
}

TEST_F(TypewiseAlertTest, PassiveCooling_ToController_TooLowTemperature) {
    testAlertForCoolingType(TO_CONTROLLER, PASSIVE_COOLING, -1, TOO_LOW);
}

TEST_F(TypewiseAlertTest, PassiveCooling_ToController_TooHighTemperature) {
    testAlertForCoolingType(TO_CONTROLLER, PASSIVE_COOLING, 36, TOO_HIGH);
}

TEST_F(TypewiseAlertTest, PassiveCooling_ToEmail_NormalTemperature) {
    testAlertForCoolingType(TO_EMAIL, PASSIVE_COOLING, 20, NORMAL);
}

TEST_F(TypewiseAlertTest, PassiveCooling_ToEmail_TooLowTemperature) {
    testAlertForCoolingType(TO_EMAIL, PASSIVE_COOLING, -1, TOO_LOW);
}

TEST_F(TypewiseAlertTest, PassiveCooling_ToEmail_TooHighTemperature) {
    testAlertForCoolingType(TO_EMAIL, PASSIVE_COOLING, 36, TOO_HIGH);
}

// Test Cases for High Active Cooling
TEST_F(TypewiseAlertTest, HiActiveCooling_ToController_NormalTemperature) {
    testAlertForCoolingType(TO_CONTROLLER, HI_ACTIVE_COOLING, 30, NORMAL);
}

TEST_F(TypewiseAlertTest, HiActiveCooling_ToController_TooLowTemperature) {
    testAlertForCoolingType(TO_CONTROLLER, HI_ACTIVE_COOLING, -1, TOO_LOW);
}

TEST_F(TypewiseAlertTest, HiActiveCooling_ToController_TooHighTemperature) {
    testAlertForCoolingType(TO_CONTROLLER, HI_ACTIVE_COOLING, 46, TOO_HIGH);
}

TEST_F(TypewiseAlertTest, HiActiveCooling_ToEmail_NormalTemperature) {
    testAlertForCoolingType(TO_EMAIL, HI_ACTIVE_COOLING, 30, NORMAL);
}

TEST_F(TypewiseAlertTest, HiActiveCooling_ToEmail_TooLowTemperature) {
    testAlertForCoolingType(TO_EMAIL, HI_ACTIVE_COOLING, -1, TOO_LOW);
}

TEST_F(TypewiseAlertTest, HiActiveCooling_ToEmail_TooHighTemperature) {
    testAlertForCoolingType(TO_EMAIL, HI_ACTIVE_COOLING, 46, TOO_HIGH);
}

// Test Cases for Medium Active Cooling
TEST_F(TypewiseAlertTest, MedActiveCooling_ToController_NormalTemperature) {
    testAlertForCoolingType(TO_CONTROLLER, MED_ACTIVE_COOLING, 30, NORMAL);
}

TEST_F(TypewiseAlertTest, MedActiveCooling_ToController_TooLowTemperature) {
    testAlertForCoolingType(TO_CONTROLLER, MED_ACTIVE_COOLING, -1, TOO_LOW);
}

TEST_F(TypewiseAlertTest, MedActiveCooling_ToController_TooHighTemperature) {
    testAlertForCoolingType(TO_CONTROLLER, MED_ACTIVE_COOLING, 41, TOO_HIGH);
}

TEST_F(TypewiseAlertTest, MedActiveCooling_ToEmail_NormalTemperature) {
    testAlertForCoolingType(TO_EMAIL, MED_ACTIVE_COOLING, 30, NORMAL);
}

TEST_F(TypewiseAlertTest, MedActiveCooling_ToEmail_TooLowTemperature) {
    testAlertForCoolingType(TO_EMAIL, MED_ACTIVE_COOLING, -1, TOO_LOW);
}

TEST_F(TypewiseAlertTest, MedActiveCooling_ToEmail_TooHighTemperature) {
    testAlertForCoolingType(TO_EMAIL, MED_ACTIVE_COOLING, 41, TOO_HIGH);
}

