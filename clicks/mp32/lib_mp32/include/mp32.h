/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for MP3 2 Click driver.
 *
 * \addtogroup mp32 MP3 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MP32_H
#define MP32_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define MP32_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MP32_RETVAL  uint8_t

#define MP32_OK           0x00
#define MP32_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 200
#define DRV_TX_BUFFER_SIZE 50
/** \} */

/**
 * \defgroup 
 * \{
 */
#define MP32_NUM_CMD_BYTES     8
#define MP32_TIMEOUT           1000
#define MP32_MAX_VOL           0x1E
/** \} */

/**
 * \defgroup Communication Commands List
 * \{
 */
#define MP32_CMD_START_CODE    0x7E
#define MP32_CMD_END_CODE      0xEF
#define MP32_VERSION_CODE      0xFF
#define MP32_FDBK_CODE_ON      0x01
#define MP32_FDBK_CODE_OFF     0x00
/** \} */

/**
 * \defgroup Serial Commands List
 * \{
 */
#define MP32_PLAY_NEXT_SONG    0x01
#define MP32_PLAY_PREV_SONG    0x02
#define MP32_PLAY_SPEC_TRACK   0x03
#define MP32_SET_VOL_UP        0x04
#define MP32_SET_VOL_DOWN      0x05
#define MP32_SET_VOL_VALUE     0x06
#define MP32_SET_EQUALIZER     0x07
#define MP32_REP_CURR_TRACK    0x08
#define MP32_SET_DEV           0x09
#define MP32_ENTER_STDBY_MODE  0x0A
#define MP32_RESET             0x0C
#define MP32_PLAY              0x0D
#define MP32_PAUSE             0x0E
#define MP32_PLAY_SONG_SPEC    0x0F
#define MP32_SET_ALL_LOOP      0x11
#define MP32_PLAY_SONG_MP3     0x12
#define MP32_PLAY_SONG_ADV     0x13
#define MP32_SET_SONG_NAME     0x14
#define MP32_ADD_LOOP_TRACK    0x15
#define MP32_STOP              0x16
#define MP32_SET_LOOP_FOL      0x17
#define MP32_SET_SHUF_ALL      0x18
#define MP32_REP_SINGLE        0x19
#define MP32_SET_SHUF_FOL      0x28
/** \} */

/**
 * \defgroup EQUALIZER
 * \{
 */
#define MP32_EQ_NORMAL         0x00
#define MP32_EQ_POP            0x01
#define MP32_EQ_ROCK           0x02
#define MP32_EQ_JAZZ           0x03
#define MP32_EQ_CLASSIC        0x04
#define MP32_EQ_BASS           0x05
/** \} */

/**
 * \defgroup DEVICE
 * \{
 */
#define MP32_U_DISK           0x01
#define MP32_SDCARD           0x02
/** \} */

/**
 * \defgroup LOOP
 * \{
 */
#define MP32_STOP_LOOP        0x00
#define MP32_START_LOOP       0x01
/** \} */

/**
 * \defgroup Enable/Disable
 * \{
 */
#define MP32_DISABLE          0x00
#define MP32_ENABLE           0x01
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;

    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

} mp32_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t rst;


    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} mp32_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t mp32_error_t;

/** \} */ // End types group

// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void mp32_cfg_setup ( mp32_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
MP32_RETVAL mp32_init ( mp32_t *ctx, mp32_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void mp32_generic_write ( mp32_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t mp32_generic_read ( mp32_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Reset the device function.
 *
 * @param ctx Click object.
 * 
 * @description Function reset the device by set state high of the RST pin.
 */
void mp32_hw_reset ( mp32_t *ctx );

/**
 * @brief Received response data function.
 *
 * @param ctx Click object.
 * @param rd_data  Response.
 *
 * @param len      Response length.
 *
 * @description The function received response from the device.
 */
void mp32_rx_cmd ( mp32_t *ctx, uint8_t *rd_data, uint8_t len );

/**
 * @brief Write command function.
 *
 * @param ctx Click object.
 * @param cmd         Command.
 *
 * @param spec_data   16-bit specific data ( such as song name ).
 *
 * @description The function write command specific data to the device.
 */
void mp32_tx_cmd ( mp32_t *ctx, uint8_t cmd, uint16_t spec_data );

/**
 * @brief Software reset function
 *
 * @param ctx Click object.
 * 
 * @description Function set software reset of device.
 */
void mp32_sw_reset ( mp32_t *ctx );

/**
 * @brief Play specific function
 *
 * @param ctx Click object.
 * @param track_index  Track index.
 *
 * @description The function set instructions for specifying a track to play.
 */
void mp32_play_specific ( mp32_t *ctx, uint16_t track_index );

/**
 * @brief Play mode function
 *
 * @param ctx Click object.
 * 
 * @description The function set Play mode command.
 */
void mp32_play_mode ( mp32_t *ctx );

/**
 * @brief Pause mode function
 *
 * @param ctx Click object.
 * 
 * @description The function set Pause mode command.
 */
void mp32_pause_mode ( mp32_t *ctx );

/**
 * @brief Stop mode function
 *
 * @param ctx Click object.
 * 
 * @description The function set Stop mode command.
 */
void mp32_stop_mode ( mp32_t *ctx );

/**
 * @brief Set Volume function
 *
 * @param ctx Click object.
 * 
 * @param perc  Volume percentage.
 *
 * @description The function adjust the volume of the device.
 */
void mp32_set_volume ( mp32_t *ctx, uint8_t perc );

/**
 * @brief Volume up function
 *
 * @param ctx Click object.
 * 
 * @description The function increase the volume of the device.
 */
void mp32_volume_up ( mp32_t *ctx );

/**
 * @brief Play next command function
 *
 * @param ctx Click object.
 * 
 * @description The function command for Play next song.
 */
void mp32_volume_down ( mp32_t *ctx );

/**
 * @brief Play previous command function
 *
 * @param ctx Click object.
 * 
 * @description The function command for Play previous song.
 */
void mp32_play_next ( mp32_t *ctx );

/**
 * @brief Play previous command function
 *
 * @param ctx Click object.
 * 
 * @description The function command for Play previous song.
 */
void mp32_play_previous ( mp32_t *ctx );

/**
 * @brief Set equalizer mode function
 *
 * 
 * @param ctx Click object.
 * @param eq  Equalizer mode ( from 0 to 4 ).
 *
 * @description The function set equalizer mode of the device.
 */
void mp32_set_eq ( mp32_t *ctx, uint8_t eq );

/**
 * @brief Repeat current mode function
 *
 * @param ctx Click object.
 * 
 * @description The function set command for Repeat current song.
 */
void mp32_repeat_current ( mp32_t *ctx );

/**
 * @brief Set device function
 *
 * @param ctx Click object.
 * 
 * @description The function set specify a device play tracks inside.
 */
void mp32_set_device ( mp32_t *ctx, uint8_t device );

/**
 * @brief Set Low power mode function
 *
 * @param ctx Click object.
 * 
 * @description The function set Low power mode of the device.
 */
void mp32_set_low_power_mode ( mp32_t *ctx );

/**
 * @brief Specify a certain folder and play tracks inside function
 *
 * @param ctx Click object.
 * @param fol_inx    Certain folder index.
 *
 * @param track_inx  Track index.
 *
 * @description The function specify a certain folder and play tracks inside.
 */
void mp32_play_spec_in_fol ( mp32_t *ctx, uint8_t fol_inx, uint8_t track_inx );

/**
 * @brief Play specific in loop mode function
 *
 * @param ctx Click object.
 * @param loop_mode  
 * Loop mode:
 * - 0 : Looping stop.
 * - 1 : Looping start.
 *
 * @description The function play specific in loop mode.
 */
void mp32_loop_all ( mp32_t *ctx, uint8_t loop_mode );

/**
 * @brief Play folder function
 *
 * @param ctx Click object.
 * @param fol_inx    Certain folder index.
 *
 * @description The function specify a folder named MP3 and paly tracks inside.
 */
void mp32_play_fol ( mp32_t *ctx, uint8_t fol_inx );

/**
 * @brief Loop folder function
 *
 * @param ctx Click object.
 * @param fol_inx    Certain folder index.
 *
 * @description The function specify a folder for looping tracks inside.
 */
void mp32_loop_fol ( mp32_t *ctx, uint8_t fol_inx );

/**
 * @brief Random Play function
 *
 * @param ctx Click object.
 * 
 * @description The function set random play command.
 */
void mp32_random_all ( mp32_t *ctx );

// Loop  Repeat a current song
/**
 * @brief Repeat a current song function
 *
 * @param ctx Click object.
 * @param loop_mode
 * Loop mode:
 * - 0 : Start repeating a current song.
 * - 1 : Stop repeating a current song.
 *
 * @description The function set repeat a current song device mode.
 */
void mp32_loop ( mp32_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _MP32_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
