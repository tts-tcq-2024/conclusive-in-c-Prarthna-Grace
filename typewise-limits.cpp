#include "typewise-alert.h"

void getTemperatureLimits(CoolingType coolingType, int& lowerLimit, int& upperLimit) {
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
    }
}

