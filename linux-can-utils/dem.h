/* dem.h */

#ifndef DEM_H
#define DEM_H

#include <stdint.h>

// mac num of events
#define MAX_EVENTS 100

// Event structure
typedef struct {
    uint32_t event_id;
    uint8_t status;
    
} DemEvent;

extern const struct {
    uint32_t event_id;
    uint8_t positive_response[4]; // Positive response format: [62, 00, DID, value]
} hardcoded_dids[];

// Function prototypes
void initialize_dem();
void add_event(uint32_t event_id, uint8_t status);
DemEvent* get_event(uint32_t event_id);
void clear_events();
void print_events();
void update_soc_value(uint32_t event_id, uint8_t new_status);

#endif /* DEM_H */
