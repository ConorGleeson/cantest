/* dem.h */

#ifndef DEM_H
#define DEM_H

#include <stdint.h>

// mac num of events
#define MAX_EVENTS 100

// Event structure
typedef struct {
    uint32_t event_id;
    uint8_t severity;
    uint8_t status;
    
} DemEvent;

// Function prototypes
void initialize_dem();
void add_event(uint32_t event_id, uint8_t severity, uint8_t status);
DemEvent* get_event(uint32_t event_id);
void clear_events();
void print_events();

#endif /* DEM_H */
