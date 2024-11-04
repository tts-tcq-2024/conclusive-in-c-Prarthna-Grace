#include "typewise-alert.h"
#include <stdio.h>

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
    const char* recipient = "a.b@c.com";

    if (breachType == NORMAL) {
        return;  // Exit early if there is no breach
    }

    printf("To: %s\n", recipient);
    
    // Print the corresponding message based on the breach type
    switch (breachType) {
        case TOO_LOW:
            printf("Hi, the temperature is too low\n");
            break;
        case TOO_HIGH:
            printf("Hi, the temperature is too high\n");
            break;
        default:
            // Handle unexpected values gracefully (if needed)
            break;
    }
}

