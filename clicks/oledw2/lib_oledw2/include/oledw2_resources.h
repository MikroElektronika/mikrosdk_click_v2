#ifndef _OLEDW2_RESOURCES_H_
#define _OLEDW2_RESOURCES_H_
#include "stdint.h"

// Comment out any of below macros to exclude it from compiling for low-memory systems.
#define OLEDW2_INCLUDE_IMG

// Font types definition
#define OLEDW2_FONT_5X7     0
#define OLEDW2_FONT_6X8     1
#define OLEDW2_FONT_8X16    2

/**
 * @brief Memory buffers for 128x32 display.
 */

#ifdef OLEDW2_INCLUDE_IMG
// 'MIKROE' image, 128x32px
extern const uint8_t oledw2_img_mikroe[ ];
#endif

#ifdef OLEDW2_FONT_5X7
// 5x7 font
extern const uint8_t oledw2_font_5x7[ ];
#endif

#ifdef OLEDW2_FONT_6X8
// 6x8 font
extern const uint8_t oledw2_font_6x8[ ];
#endif

#ifdef OLEDW2_FONT_8X16
// 8x16 font
extern const uint8_t oledw2_font_8x16[ ];
#endif

#endif // _OLEDW2_RESOURCES_H_