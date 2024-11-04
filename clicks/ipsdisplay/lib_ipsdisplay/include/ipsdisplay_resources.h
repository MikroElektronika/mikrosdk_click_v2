#ifndef _IPSDISPLAY_RESOURCES_H_
#define _IPSDISPLAY_RESOURCES_H_
#include "stdint.h"

// Change the value of the following macro to 1 to include image resources.
// It's excluded by default to save space for low-memory systems.
#define IPSDISPLAY_RESOURCES_INCLUDE_IMG    0

/**
 * @brief Memory buffers for 135x240 IPS display.
 */
 
#if IPSDISPLAY_RESOURCES_INCLUDE_IMG
// 'MIKROE' image, 240x135px
extern const uint16_t ipsdisplay_img_mikroe[ ];
#endif

// 6x12 font
extern const uint8_t ipsdisplay_font_6x12[ ];

#endif // _IPSDISPLAY_RESOURCES_H_