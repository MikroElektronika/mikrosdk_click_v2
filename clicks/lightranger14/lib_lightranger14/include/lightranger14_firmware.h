#ifndef _LIGHTRANGER14_FIRMWARE_H_
#define _LIGHTRANGER14_FIRMWARE_H_
#include "stdint.h"

/**
 * @brief Firmware image for LightRanger 14 Click.
 */
#define LIGHTRANGER14_IMAGE_START   0x00010000ul
#define LIGHTRANGER14_IMAGE_FINISH  0x00012618ul

extern const uint8_t lightranger14_image[ ];

#endif // _LIGHTRANGER14_FIRMWARE_H_