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
 * \brief This file contains API for GMR Angle Click driver.
 *
 * \addtogroup gmrangle GMR Angle Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GMRANGLE_H
#define GMRANGLE_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define GMRANGLE_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.ifa = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.css = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.ifc = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.ifb = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GMRANGLE_OK                                 0
#define GMRANGLE_ERROR                             -1
/** \} */

/**
 * \defgroup reg Sensor registers address
 * \{
 */
#define GMRANGLE_REG_STAT                           0x00
#define GMRANGLE_REG_ACSTAT                         0x01
#define GMRANGLE_REG_AVAL                           0x02
#define GMRANGLE_REG_ASPD                           0x03
#define GMRANGLE_REG_AREV                           0x04
#define GMRANGLE_REG_FSYNC                          0x05
#define GMRANGLE_REG_MOD_1                          0x06
#define GMRANGLE_REG_SIL                            0x07
#define GMRANGLE_REG_MOD_2                          0x08
#define GMRANGLE_REG_MOD_3                          0x09
#define GMRANGLE_REG_OFFX                           0x0A
#define GMRANGLE_REG_OFFY                           0x0B
#define GMRANGLE_REG_SYNCH                          0x0C
#define GMRANGLE_REG_IFAB                           0x0D
#define GMRANGLE_REG_MOD_4                          0x0E
#define GMRANGLE_REG_TCO_Y                          0x0F
#define GMRANGLE_REG_ADC_X                          0x10
#define GMRANGLE_REG_ADC_Y                          0x11
/** \} */

/**
 * \defgroup wr_cmd SPI write/read cmd
 * \{
 */
#define GMRANGLE_READ_SENSOR                        0x80
#define GMRANGLE_GET_BIT_5_4                        0x30
#define GMRANGLE_GET_BIT_3_0                        0x0F
/** \} */

/**
 * \defgroup bit_mask Bit mask
 * \{
 */
#define GMRANGLE_SYSTEM_ERROR_MASK                  0x4000
#define GMRANGLE_INTERFACE_ERROR_MASK               0x2000
#define GMRANGLE_INV_ANGLE_ERROR_MASK               0x1000
#define GMRANGLE_CRC_POLYNOMIAL                     0x1D00
#define GMRANGLE_CRC_SEED                           0xFF00
#define GMRANGLE_CRC_NUM_REGISTERS                  0x0008
#define GMRANGLE_MAX_REGISTER_MEM                   0x0030
#define GMRANGLE_DELETE_BIT_15                      0x7FFF
#define GMRANGLE_CHANGE_UINT_TO_INT_16              0xFFFF
#define GMRANGLE_CHANGE_UINT_TO_INT_15              0x8000
#define GMRANGLE_MAX_BIT_14                         0x3FFF
#define GMRANGLE_CHECK_BIT_14                       0x4000
#define GMRANGLE_GET_BIT_14_4                       0x7FF0
#define GMRANGLE_DELETE_7BITS                       0x01FF
#define GMRANGLE_CHANGE_UNIT_TO_INT_9               0x0200
#define GMRANGLE_CHECK_BIT_9                        0x0100
#define GMRANGLE_CHECK_BIT_15                       0x8000
/** \} */

/**
 * \defgroup calc_val Calculate value
 * \{
 */
#define GMRANGLE_POW_2_15                           32768.0f
#define GMRANGLE_POW_2_7                            128.0f
#define GMRANGLE_ANGLE_360_VAL                      360.0f
#define GMRANGLE_TEMP_OFFSET                        152.0f
#define GMRANGLE_TEMP_DIV                           2.776f
#define GMRANGLE_DATA_RESOLUTION                    0x7FFF
/** \} */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b gmrangle_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define GMRANGLE_SET_DATA_SAMPLE_EDGE               SET_SPI_DATA_SAMPLE_EDGE
#define GMRANGLE_SET_DATA_SAMPLE_MIDDLE             SET_SPI_DATA_SAMPLE_MIDDLE

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
    digital_out_t cs;
    digital_out_t css;

    // Input pins 
    digital_in_t ifa;
    digital_in_t ifb;
    digital_in_t ifc;
    
    // Modules 
    spi_master_t spi;
    pin_name_t chip_select;

} gmrangle_t;

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
    pin_name_t ifa;
    pin_name_t css;
    pin_name_t ifc;
    pin_name_t ifb;

    // static variable 
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} gmrangle_cfg_t;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void gmrangle_cfg_setup ( gmrangle_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t gmrangle_init ( gmrangle_t *ctx, gmrangle_cfg_t *cfg );

/**
 * @brief Generic read 16-bit data function.
 *
 * @param ctx          Click object.
 * @param reg          6-bit register address.
 * 
 * @return             16-bit read data.
 *
 * @details This function read 16-bit data 
 * from the targeted 6-bit register address of the
 * TLE5012 GMR-Based Angular Sensor on the GMR Angle Click board.
 */
uint16_t gmrangle_read_data ( gmrangle_t *ctx, uint8_t reg );

/**
 * @brief Generic write 16-bit data function.
 *
 * @param ctx          Click object.
 * @param reg          6-bit register address.
 * @param tx_data      16-bit data to write.
 *
 * @details This function write the 16-bit data 
 * to the targeted 6-bit register address of the
 * TLE5012 GMR-Based Angular Sensor on the GMR Angle Click board.
 */
void gmrangle_write_data ( gmrangle_t *ctx, uint8_t reg, uint16_t tx_data );

/**
 * @brief Get the status data function.
 *
 * @param ctx          Click object.
 * 
 * @return             16-bit status data:
 * - [ bit 15 ]      : Read Status:
 *                   - 0 : after readout;
 *                   - 1 : status values changed ( Reset value );
 * - [ bit 14 : 13 ] : Slave Number:
 *                   - 0 : ( Reset value );
 * - [ bit 12 ]      : No GMR Angle Value:
 *                   - 0 : valid GMR angle value on the interface ( Reset value );
 *                   - 1 : no valid GMR angle value on the interface;
 * - [ bit 11 ]      : No GMR XY Values:
 *                   - 0 : valid GMR_XY values on the interface ( Reset value );
 *                   - 1 : no valid GMR_XY values on the interface;
 * - [ bit 10 ]      : Status ROM:
 *                   - 0 : after readout, CRC ok ( Reset value );
 *                   - 1 : CRC fail or running;
 * - [ bit 9 ]       : Status ADC-Test:
 *                   - 0 : after readout ( Reset value );
 *                   - 1 : Test vectors out of limit;
 * - [ bit 8 ]       : Reserved;
 * - [ bit 7 ]       : Status Magnitude Out of Limit:
 *                   - 0 : after readout ( Reset value );
 *                   - 1 : TGMR-magnitude out of limit ( >23230 digits );
 * - [ bit 6 ]       : Status X,Y Data Out of Limit:
 *                   - 0 : after readout ( Reset value );
 *                   - 1 : X,Y data out of limit ( >23230 digits );
 * - [ bit 5 ]       : Status Overflow:
 *                   - 0 : after readout ( Reset value );
 *                   - 1 : DSPU overflow occurred;
 * - [ bit 4 ]       : Status Digital Signal Processing Unit:
 *                   - 0 : after readout ( Reset value );
 *                   - 1 : DSPU self test not ok, or selftest is running;
 * - [ bit 3 ]       : Status Fuse CRC:
 *                   - 0 : after readout, Fuse CRC ok ( Reset value );
 *                   - 1 : Fuse CRC fail;
 * - [ bit 2 ]       : Status Voltage Regulator:
 *                   - 0 : after readout ( Reset value );
 *                   - 1 : VDD overvoltage, VDD undervoltage, VDD-off ,GNDoff or VOVG, VOVA, VOVD to high;
 * - [ bit 1 ]       : Status Watchdog:
 *                   - 0 : after chip reset ( Reset value );
 *                   - 1 : watchdog counter expired;
 * - [ bit 0 ]       : Status Reset:
 *                   - 0 : after readout ( Reset value );
 *                   - 1 :  indication of power-up, short power-break or active reset;
 *
 * @details This function read 16-bit status data 
 * from the 6-bit register address ( GMRANGLE_REG_STAT )
 * of the TLE5012 GMR-Based Angular Sensor on the GMR Angle Click board.
 */
uint16_t gmrangle_get_status ( gmrangle_t *ctx );

/**
 * @brief Set activation status register function.
 *
 * @param ctx          Click object.
 * 
 * @return             16-bit activation status data:
 * - [ bit 15 : 10 ] : Reserved;
 * - [ bit 9 ]       : Enable GMR Vector check:
 *                   - 0 : ( Reset value );
 * - [ bit 8 ]       : Reserved;
 * - [ bit 7 ]       : Activation of ADC-Redundancy-BIST:
 *                   - 0 : after execution;
 *                   - 1 : activation of redundancy BIST ( Reset value );
 * - [ bit 6 ]       : Activation of ADC-BIST:
 *                   - 0 : after execution;
 *                   - 1 : activation of redundancy BIST ( Reset value );
 * - [ bit 5 ]       : Enable of DSPU Overflow Check:
 *                   - 1 : ( Reset value );
 * - [ bit 4 ]       : Activation DSPU BIST:
 *                   - 0 : after execution;
 *                   - 1 : activation of DSPU BIST ( Reset value );
 * - [ bit 3 ]       : Activation Fuse CRC:
 *                   - 0 : after execution;
 *                   - 1 : activation of Fuse CRC ( Reset value );
 * - [ bit 2 ]       : Enable Voltage Regulator Check:
 *                   - 1 : ( Reset value );
 * - [ bit 1 ]       : Enable DSPU Watchdog-HW-Reset:
 *                   - 1 : ( Reset value );
 * - [ bit 0 ]       : Activation of Hardware Reset:
 *                   - 0 : after execution ( Reset value );
 *                   - 1 : activation of HW Reset;
 *
 * @details This function write 16-bit a_data data
 * to the 6-bit register address ( GMRANGLE_REG_ACSTAT )
 * of the TLE5012 GMR-Based Angular Sensor on the GMR Angle Click board.
 */
void gmrangle_set_act_status ( gmrangle_t *ctx, uint16_t a_data );

/**
 * @brief Get the angle speed value function.
 *
 * @param ctx          Click object.
 * 
 * @return             16-bit signed angle speed value
 *
 * @details This function read 16-bit signed angle speed value 
 * from the 6-bit register address ( GMRANGLE_REG_ASPD )
 * of the TLE5012 GMR-Based Angular Sensor on the GMR Angle Click board.
 */
int16_t gmrangle_get_angle_speed_value ( gmrangle_t *ctx );

/**
 * @brief Get the angle speed function.
 *
 * @param ctx                   Click object.
 * @param final_angle_speed     Pointer to the memory location where float be stored
 * @param angle_speed_val       Pointer to the memory location where 16-bit signed be stored
 *
 * @details This function get the angle speed 
 * by read from the from the 6-bit register address ( GMRANGLE_REG_ASPD )
 * of the TLE5012 GMR-Based Angular Sensor on the GMR Angle Click board.
 */
void gmrangle_get_angle_speed ( gmrangle_t *ctx, float *final_angle_speed, int16_t *angle_speed_val );

/**
 * @brief Get the angle range function.
 *
 * @param ctx          Click object.
 * 
 * @return             float value of the angle range
 *
 * @details This function read value of the angle range 
 * from the 6-bit register address ( GMRANGLE_REG_MOD_2 )
 * of the TLE5012 GMR-Based Angular Sensor on the GMR Angle Click board.
 */
float gmrangle_get_angle_range ( gmrangle_t *ctx );

/**
 * @brief Get the number of revolutions function.
 *
 * @param ctx          Click object.
 * 
 * @return             16-bit signed value of the number of the revolutions.
 *
 * @details This function read the number of the revolutions 
 * from the 6-bit register address ( GMRANGLE_REG_AREV )
 * of the TLE5012 GMR-Based Angular Sensor on the GMR Angle Click board.
 */
int16_t gmrangle_get_num_revolutions ( gmrangle_t *ctx );

/**
 * @brief Get the angle value function.
 *
 * @param ctx          Click object.
 * 
 * @return             16-bit signed value of the angle.
 *
 * @details This function read the 16-bit signed value of the angle 
 * from the 6-bit register address ( GMRANGLE_REG_AVAL )
 * of the TLE5012 GMR-Based Angular Sensor on the GMR Angle Click board.
 */
uint16_t gmrangle_get_angle_value ( gmrangle_t *ctx );

/**
 * @brief Calculate angle function.
 *
 * @param ctx          Click object.
 * 
 * @return             float value of the angle in degree.
 *
 * @details This function calculate the float value 
 * of the angle in degree
 * of the TLE5012 GMR-Based Angular Sensor on the GMR Angle Click board.
 */
float gmrangle_calculate_angle ( gmrangle_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _GMRANGLE_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
