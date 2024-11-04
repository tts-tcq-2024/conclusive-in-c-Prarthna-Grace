#include "typewise-alert.h"
#include <stdio.h>

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

#include <stdio.h>

// Function to get the email recipient
const char* getEmailRecipient() {
    return "a.b@c.com";
}

// Function to print the email content based on the breach type
void printEmailContent(BreachType breachType) {
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

void sendToEmail(BreachType breachType) {
    // Exit early if there is no breach
    if (breachType == NORMAL) {
        return;
    }

    const char* recipient = getEmailRecipient();
    printf("To: %s\n", recipient);
    
    // Print the corresponding message based on the breach type
    printEmailContent(breachType);
}


