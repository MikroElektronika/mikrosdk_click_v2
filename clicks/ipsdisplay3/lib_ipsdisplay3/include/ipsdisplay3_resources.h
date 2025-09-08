#ifndef _IPSDISPLAY3_RESOURCES_H_
#define _IPSDISPLAY3_RESOURCES_H_
#include "stdint.h"

// Change the value of the following macro to 1 to include image resources.
// It's excluded by default to save space for low-memory systems.
#define IPSDISPLAY3_RESOURCES_INCLUDE_IMG   0

// Font types definition
#define IPSDISPLAY3_FONT_6X12               0
#define IPSDISPLAY3_FONT_8X16               1
#define IPSDISPLAY3_FONT_12X24              2

/**
 * @brief Memory buffers for 128x115 IPS display.
 */

#if IPSDISPLAY3_RESOURCES_INCLUDE_IMG
// 'MIKROE' image, 128x115px
extern const uint16_t ipsdisplay3_img_mikroe[ ];
#endif

#ifdef IPSDISPLAY3_FONT_6X12
// 6x12 font
extern const uint8_t ipsdisplay3_font_6x12[ ];
#endif

#ifdef IPSDISPLAY3_FONT_8X16
// 8x16 font
extern const uint8_t ipsdisplay3_font_8x16[ ];
#endif

#ifdef IPSDISPLAY3_FONT_12X24
// 12x24 font
extern const uint8_t ipsdisplay3_font_12x24[ ];
#endif

#endif // _IPSDISPLAY3_RESOURCES_H_