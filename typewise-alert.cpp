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

void getTemperatureLimits(CoolingType coolingType, int &lowerLimit, int &upperLimit) {
    switch (coolingType) {
        case PASSIVE_COOLING:
            lowerLimit = 0;
            upperLimit = 35;
            break;
        case HI_ACTIVE_COOLING:
            lowerLimit = 0;
            upperLimit = 45;
            break;
        case MED_ACTIVE_COOLING:
            lowerLimit = 0;
            upperLimit = 40;
            break;
        default:
            // Set defaults or handle unknown cooling type if needed
            lowerLimit = 0;
            upperLimit = 0;
            break;
    }
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    int lowerLimit = 0;
    int upperLimit = 0;

    // Pass addresses of lowerLimit and upperLimit
    getTemperatureLimits(coolingType, &lowerLimit, &upperLimit);

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

