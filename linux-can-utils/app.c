#include <stdio.h>
#include "dem.h"
#include "dcm.h"
#include "app.h"

// Function to display menu options
static void display_menu() {
    printf("\nSimulation App Menu:\n");
    printf("1. Trigger Diagnostic Event\n");
    printf("2. View Stored Events\n");
    printf("3. Send Diagnostic Request\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

// Main logic of the simulation app
void run_simulation_app() {

    int choice;
    uint32_t event_id;
    uint8_t severity, status;

    // Main loop for the simulation app
    do {
        // Display menu
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Trigger Diagnostic Event
                printf("\nEnter Event ID: ");
                scanf("%u", &event_id);
                printf("Enter Severity: ");
                scanf("%hhu", &severity);
                printf("Enter Status: ");
                scanf("%hhu", &status);

                // Add event to DEM
                add_event(event_id, severity, status);

                // Inform DCM about the event
               // inform_dcm(event_id);

                printf("\nDiagnostic Event Triggered.\n");
                break;
            case 2:
                // View Stored Events
                print_events();
                break;
            case 3:
            // send can message
                send_diagnostic_request();
                break;
            case 4 :
                // Exit
                printf("\nExiting Simulation App.\n");
                break;
            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 4);
}