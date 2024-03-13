#include <stdio.h>
#include <stdint.h>

#define MAX_EVENTS 100 // Maximum number of events the DEM can store

//  event structure
typedef struct {
    uint32_t event_id;
    uint8_t severity;
    uint8_t status;

} DemEvent;

// DEM storage
DemEvent dem_events[MAX_EVENTS];
int dem_event_count = 0;


void add_event(uint32_t event_id, uint8_t severity, uint8_t status) {
    if (dem_event_count < MAX_EVENTS) {
        dem_events[dem_event_count].event_id = event_id;
        dem_events[dem_event_count].severity = severity;
        dem_events[dem_event_count].status = status;
        // Add more attributes 
        dem_event_count++;
    } else {
        printf("DEM storage is full\n");
    }
}

// Function to retrieve events from the DEM based on event ID
DemEvent* get_event(uint32_t event_id) {
    for (int i = 0; i < dem_event_count; i++) {
        if (dem_events[i].event_id == event_id) {
            return &dem_events[i];
        }
    }
    return NULL; // Event not found
}

// Function to clear all events from the DEM
void clear_events() {
    dem_event_count = 0;
}

// Function to print all events stored in the DEM
void print_events() {
    printf("Events stored in DEM:\n");
    for (int i = 0; i < dem_event_count; i++) {
        printf("Event ID: %u, Severity: %u, Status: %u\n", dem_events[i].event_id, dem_events[i].severity, dem_events[i].status);
        // Print more attributes as needed
    }
}

int main() {
    // prototype/test of adding events 
    add_event(1001, 2, 1); // Add an event with event ID 1001, severity 2, and status 1
    add_event(1002, 3, 0); // Add another event
    add_event(1003, 1, 1); // Add another event

    printf("Number of events stored: %d\n", dem_event_count);

    print_events(); // Print all events stored in the DEM

    // protoype retrieve event 
    uint32_t event_id_to_find = 1002;
    DemEvent* found_event = get_event(event_id_to_find);
    if (found_event != NULL) {
        printf("Found event with ID %u: Severity %u, Status %u\n", found_event->event_id, found_event->severity, found_event->status);
    } else {
        printf("Event with ID %u not found\n", event_id_to_find);
    }

    // Clear all events from the DEM
    clear_events();
    printf("Events cleared\n");

    printf("Number of events stored after clearing: %d\n", dem_event_count);

    return 0;
}