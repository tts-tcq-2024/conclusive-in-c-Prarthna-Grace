#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

#include "typewise-alert.h"

// Functions to get temperature limits for each cooling type
void setPassiveCoolingLimits(int &lowerLimit, int &upperLimit) {
    lowerLimit = 0;
    upperLimit = 35;
}

void setHiActiveCoolingLimits(int &lowerLimit, int &upperLimit) {
    lowerLimit = 0;
    upperLimit = 45;
}

void setMedActiveCoolingLimits(int &lowerLimit, int &upperLimit) {
    lowerLimit = 0;
    upperLimit = 40;
}

// Function pointer type for setting limits
typedef void (*SetLimitsFunc)(int &, int &);

// Array of function pointers for each cooling type
SetLimitsFunc limitSetters[] = {
    setPassiveCoolingLimits,    // 0: PASSIVE_COOLING
    setHiActiveCoolingLimits,   // 1: HI_ACTIVE_COOLING
    setMedActiveCoolingLimits    // 2: MED_ACTIVE_COOLING
};

// Main function to determine temperature limits
void getTemperatureLimits(CoolingType coolingType, int &lowerLimit, int &upperLimit) {
    if (coolingType >= PASSIVE_COOLING && coolingType <= MED_ACTIVE_COOLING) {
        limitSetters[coolingType](lowerLimit, upperLimit);
    } else {
        // Set defaults or handle unknown cooling type if needed
        lowerLimit = 0;
        upperLimit = 0;
    }
}


BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    int lowerLimit = 0;
    int upperLimit = 0;

    // Pass by reference correctly
    getTemperatureLimits(coolingType, lowerLimit, upperLimit);

    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

