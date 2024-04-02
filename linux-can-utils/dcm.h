/* dcm.h */

#ifndef DCM_H
#define DCM_H


#include <stdint.h>

// Function prototypes
void initialize_dcm();
void inform_dcm(uint32_t event_id);
void cleanup_dcm();

#endif /* DCM_H */
