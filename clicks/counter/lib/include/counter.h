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
 * \brief This file contains API for Counter Click driver.
 *
 * \addtogroup counter Counter Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COUNTER_H
#define COUNTER_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define COUNTER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.en      = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COUNTER_RETVAL  uint8_t

#define COUNTER_OK           0x00
#define COUNTER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register_commands Register commands
 * \{
 */
#define COUNTER_CMD_CLR               0x00    
#define COUNTER_CMD_WR                0x80    
#define COUNTER_CMD_LOAD              0xC0    
#define COUNTER_CMD_RD                0X40    
/** \} */

/**
 * \defgroup counter_click_registers Counter click registers
 * \{
 */
#define COUNTER_MDR0                  0x08    
#define COUNTER_MDR1                  0x10    
#define COUNTER_DTR                   0x18    
#define COUNTER_CNTR                  0x20    
#define COUNTER_OTR                   0x28    
#define COUNTER_STR                   0x30    
/** \} */

/**
 * \defgroup mdr0_count_mode_setting MDR0 count mode setting
 * \{
 */
#define COUNTER_NON_QUAD              0x00    
#define COUNTER_1X_QUAD               0x01    
#define COUNTER_2X_QUAD               0x02    
#define COUNTER_4X_QUAD               0x03    
/** \} */

/**
 * \defgroup  mdr0_count_type_setting MDR0 count type setting
 * \{
 */
#define COUNTER_FREE_RUN              0x00    
#define COUNTER_SINGLE_COUNT          0x04    
#define COUNTER_RANGE_LIMIT           0x08    
#define COUNTER_N_MODULE              0x0C    
/** \} */

/**
 * \defgroup mdr0_index_setting MDR0 index setting
 * \{
 */
#define COUNTER_INDEX_DISABLED        0x00    
#define COUNTER_INDEX_LOAD_CNTR       0x10     
#define COUNTER_INDEX_RESET_CNTR      0x20     
#define COUNTER_INDEX_LOAD_OTR        0x30     
/** \} */

/**
 * \defgroup mdr0_index_sign_setting MDR0 index sign setting
 * \{
 */
#define COUNTER_INDEX_NEG             0x00    
#define COUNTER_INDEX_POS             0x40    
/** \} */

/**
 * \defgroup mdr0_clock_filter_division_factor MDR0 clock filter division factor
 */
#define COUNTER_FILTER_CLOCK_DIV1     0x00    
#define COUNTER_FILTER_CLOCK_DIV2     0x80    
/** \} */

/**
 * \defgroup mdr1_buffer_size_setting MDR1 buffer size setting
 * \{
 */
#define COUNTER_MODE_32               0x00    
#define COUNTER_MODE_24               0x01    
#define COUNTER_MODE_16               0x02    
#define COUNTER_MODE_8                0x03    
/** \} */

/**
 * \defgroup mdr1_enable_disable_counting_setting MDR1 enable/disable counting setting
 * \{
 */
#define COUNTER_ENABLE                0x00    
#define COUNTER_DISABLE               0x04    

/** \} */

/**
 * \defgroup mdr1_flags_settings MDR1 flags settings
 * \{
 */
#define COUNTER_FLAG_DISABLE          0x00    
#define COUNTER_FLAG_IDX              0x10    
#define COUNTER_FLAG_CMP              0x20    
#define COUNTER_FLAG_BW               0x40    
#define COUNTER_FLAG_FY               0x80    
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

    digital_out_t en;
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    // Variables 

    uint8_t buffer_size;

} counter_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t en;
    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} counter_cfg_t;

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
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void counter_cfg_setup ( counter_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param counter Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
COUNTER_RETVAL counter_init ( counter_t *ctx, counter_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Counter click.
 */
void counter_default_cfg ( counter_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void counter_generic_transfer 
( 
    counter_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Writes data into MDR0
 *
 * @param ctx          Click object.
 * @param settings     MDR0 settings.
 * 
 * @note The MDR0 (Mode Register 0) is an 8-bit read/write register that sets up the
 * operating mode for the LS7366. Upon power up MDR0 is cleared to zero.
 *
 * @description This function writes data into MDR0, using click object.
 */
void counter_write_mdr0 ( counter_t *ctx, uint8_t settings );

/**
 * @brief Writes data into MDR1
 *
 * @param ctx          Click object.
 * @param settings     MDR1 settings.
 * 
 * @note The MDR1 (Mode Register 1) is an 8-bit read/write register which is appended
 * to MDR0 for additional modes. Upon power-up MDR1 is cleared to zero.
 *
 * @description This function writes data into MDR1, using click object.
 */
void counter_write_mdr1 ( counter_t *ctx, uint8_t settings );

/**
 * @brief Writes data into DTR
 * 
 * @param ctx          Click object.
 * @param buffer       Data to be written into DTR.
 *
 * @note The DTR is a software configurable 8, 16, 24 or 32-bit input data register
 * which can be written into directly from MOSI, the serial input. The DTR data
 * can be transferred into the 32-bit counter (CNTR) under program control or
 * by hardware index signal.
 *
 * @description This function writes data into DTR, using click object.
 */
void counter_write_dtr ( counter_t *ctx, uint8_t buffer );

/**
 * @brief Loads CNTR from DTR
 * 
 * @param ctx          Click object.
 *
 * @note The CNTR is a software configurable 8, 16, 24 or 32-bit up/down counter which
 * counts the up/down pulses resulting from the quadrature clocks applied at the
 * A and B inputs, or alternatively, in non-quadrature mode, pulses applied at
 * the A input.
 *
 * @description This function loads CNTR from DTR, using click object.
 */
void counter_load_cntr ( counter_t *ctx );

/**
 * @brief Loads OTR from CNTR
 *
 * @param ctx          Click object.
 * 
 * @note The OTR is a software configuration 8, 16, 24 or 32-bit register which can be
 * read back on the MISO output. Since instantaneous CNTR value is often needed
 * to be read while the CNTR continues to count, the OTR serves as a convenient
 * dump site for instantaneous CNTR data which can then be read without
 * interfering with the counting process.
 * 
 * @description This function loads OTR from CNTR, using click object.
 */
void counter_load_otr ( counter_t *ctx );

/**
 * @brief Reads MDR0
 * 
 * @param ctx          Click object.
 * @returns            Data from MDR0.
 * 
 * @description This function reads MDR0, using click object.
 */
uint8_t counter_read_mdr0 ( counter_t *ctx );

/**
 * @brief Reads MDR1
 * 
 * @param ctx          Click object.
 * @returns            Data from MDR1.
 * 
 * @description This function reads MDR1, using click object.
 */
uint8_t counter_read_mdr1 ( counter_t *ctx );

/**
 * @brief Reads OTR
 * 
 * @param ctx          Click object.
 * @returns            OTR register data.
 * 
 * @description This function reads OTR, using click object.
 */
uint8_t counter_read_otr ( counter_t *ctx );

/**
 * @brief Reads CNTR
 *
 * @param ctx          Click object.
 * @returns            CNTR register data.
 * 
 * @description This function reads CNTR, using click object.
 */
uint8_t counter_read_cntr ( counter_t *ctx );

/**
 * @brief Reads STR
 *
 * @param ctx          Click object.
 * @returns            Status register data.
 * 
 * @note
 * <pre>
 * The STR is an 8-bit status register which stores count related status
 * information.
 *
 * B0 - Sign bit. 1: negative, 0: positive
 * B1 - Count direction indicator: 0: count down, 1: count up
 * B2 - Power loss indicator latch; set upon power up
 * B3 - Count enable status: 0: counting disabled, 1: counting enabled
 * B4 - Index latch
 * B5 - Compare (CNTR = DTR) latch
 * B6 - Borrow (CNTR underflow) latch
 * B7 - Carry (CNTR overflow) latch
 * </pre>
 * 
 * @description This function reads STR, using click object.
 */
uint8_t counter_read_str ( counter_t *ctx );

/**
 * @brief Clears MDR0
 * 
 * @param ctx          Click object.
 * 
 * @description This function clears MDR0.
 */
void counter_clear_mrd0 ( counter_t *ctx );

/**
 * @brief Clears MDR1
 * 
 * @param ctx          Click object.
 * 
 * @description This function clears MDR1.
 */
void counter_clead_mrd1 ( counter_t *ctx );

/**
 * @brief Clears CNTR
 * 
 * @param ctx          Click object.
 * 
 * @description This function clears CNTR.
 */
void counter_clear_cntr ( counter_t *ctx );

/**
 * @brief Clears STR
 *
 * @param ctx          Click object.
 * 
 * @note
 * <pre>
 * Resets all status bits except CEN and U/D. In quadrature mode, if the
 * quadrature clocks have been halted, the status bits CY, BW and CMP are not
 * affected by a “CLR STR” command under the following conditions:
 *      CY: If CNTR = FFFFFFFF with status bit U/D = 1
 *      BW: If CNTR = 0 with status bit U/D = 0
 *      CMP: If CNTR = DTR
 * In non-quadrature mode the same rules apply if input A is held at
 * logic low.
 * </pre>
 * 
 * @description This function clears STR
 */
void counter_clear_str ( counter_t *ctx );

/**
 * @brief Initialisation of click board with default settings.
 *
 * @param ctx          Click object.
 * 
 * @note
 * <pre>
 * MDR0 settings :
 *      4X quad
 *      Free run
 *      Counter index disabled
 *      Filter clock division 1
 *
 * MDR1 settings :
 *      Counter mode 32
 *      Counter disabled
 *      Flags disabled
 * </pre>
 * 
 * @description This function initialize of click board with default settings.
 */
void counter_initialisation ( counter_t *ctx );

/**
 * @brief Initialisation of click board with specific settings.
 *
 * @param ctx          Click object.
 * @param mdr0_set     Settings for mdr0.
 * @param mdr1_set     Settings for mdr1.
 * 
 * @description This function initialize of click board with specific settings.
 */
void counter_init_advanced ( counter_t *ctx, uint8_t mdr0_set, uint8_t mdr1_set );

/**
 * @brief Enables counting ( Software mode )
 * 
 * @param ctx          Click object.
 * 
 * @description This function enables counting in software mode.
 */
void counter_enable ( counter_t *ctx );

/**
 * @brief Disables counting ( Software mode )
 * 
 * @param ctx          Click object.
 * 
 * @description This function disables counting in software mode.
 */
void counter_disable ( counter_t *ctx );

/**
 * @brief Enables counting ( Hardware mode )
 * 
 * @param ctx          Click object.
 * 
 * @description This function enables counting in hardware mode.
 */
void counter_chip_enable ( counter_t *ctx );

/**
 * @brief Disables counting ( Hardware mode )
 * 
 * @param ctx          Click object.
 * 
 * @description This function disables counting in hardware mode.
 */
void counter_chip_disable ( counter_t *ctx );

/**
 * @brief Function for get int-pin state
 * 
 * @param ctx          Click object.
 * @returns            Int pin state.
 * 
 * @description This function gets int-pin state.
 */
uint8_t get_int_state ( counter_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _COUNTER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
