#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H

#include <cstring> // Include for string manipulation if needed

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48]; // Consider std::string in C++
} BatteryCharacter;

// Updated function signatures
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
BreachType inferBreach(double value, double lowerLimit, double upperLimit);
void getTemperatureLimits(CoolingType coolingType, int &lowerLimit, int &upperLimit); // Use references
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

#endif // TYPEWISE_ALERT_H
