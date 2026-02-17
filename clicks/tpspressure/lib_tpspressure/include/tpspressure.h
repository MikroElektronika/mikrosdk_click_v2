/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file tpspressure.h
 * @brief This file contains API for TPS Pressure Click Driver.
 */

#ifndef TPSPRESSURE_H
#define TPSPRESSURE_H

#ifdef __cplusplus
extern "C"{
#endif

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
#include "drv_i2c_master.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup tpspressure TPS Pressure Click Driver
 * @brief API for configuring and manipulating TPS Pressure Click driver.
 * @{
 */

/**
 * @defgroup tpspressure_reg TPS Pressure Registers List
 * @brief List of registers of TPS Pressure Click driver.
 */

/**
 * @addtogroup tpspressure_reg
 * @{
 */

/**
 * @brief TPS Pressure commands list.
 * @details Specified commands list of TPS Pressure Click driver.
 */
#define TPSPRESSURE_CMD_READ_SENSOR_ID          0x08
#define TPSPRESSURE_CMD_RESET                   0x10
#define TPSPRESSURE_CMD_REFRESH                 0x12
#define TPSPRESSURE_CMD_WRITE_OPERATING_MODE    0x14
#define TPSPRESSURE_CMD_READ_OPERATING_MODE     0x16
#define TPSPRESSURE_CMD_START_AUTOMATIC_MODE    0x18
#define TPSPRESSURE_CMD_STOP_AUTOMATIC_MODE     0x1A
#define TPSPRESSURE_CMD_WRITE_CONFIG_PRES_4     0x20
#define TPSPRESSURE_CMD_WRITE_CONFIG_TEMP1_4    0x22
#define TPSPRESSURE_CMD_READ_CONFIG_PRES_4      0x28
#define TPSPRESSURE_CMD_READ_CONFIG_TEMP1_4     0x2A
#define TPSPRESSURE_CMD_CONVERSION              0x4E
#define TPSPRESSURE_CMD_READ_ADC_P              0x52
#define TPSPRESSURE_CMD_READ_ADC_T1             0x54
#define TPSPRESSURE_CMD_READ_ADC_T1_P           0x56
#define TPSPRESSURE_CMD_WRITE_INTERRUPT_MASK    0x60
#define TPSPRESSURE_CMD_READ_INTERRUPT_MASK     0x68
#define TPSPRESSURE_CMD_WRITE_INTERRUPT_REG     0x70
#define TPSPRESSURE_CMD_READ_INTERRUPT_REG      0x78
#define TPSPRESSURE_CMD_WRITE_NVM               0x86
#define TPSPRESSURE_CMD_ERASE_NVM               0x96
#define TPSPRESSURE_CMD_READ_NVM                0xA6
#define TPSPRESSURE_CMD_WRITE_LIMITS            0xC0
#define TPSPRESSURE_CMD_READ_LIMITS             0xD0
#define TPSPRESSURE_CMD_WRITE_REG               0xE0
#define TPSPRESSURE_CMD_READ_REG                0xE2

/**
 * @brief TPS Pressure register list.
 * @details Specified register list of TPS Pressure Click driver.
 */
#define TPSPRESSURE_REG_NVM_START               0x00
#define TPSPRESSURE_REG_NVM_END                 0x1F
#define TPSPRESSURE_REG_PRES_4                  0x61
#define TPSPRESSURE_REG_TEMP1_4                 0x62
#define TPSPRESSURE_REG_OPER                    0x64
#define TPSPRESSURE_REG_DAC_2                   0x65
#define TPSPRESSURE_REG_POST_GAIN_P             0x66
#define TPSPRESSURE_REG_POST_GAIN_T1            0x67
#define TPSPRESSURE_REG_POST_OFF_P              0x69
#define TPSPRESSURE_REG_POST_OFF_T1             0x6A
#define TPSPRESSURE_REG_COM                     0x6C
#define TPSPRESSURE_REG_LIMIT_1                 0x6D
#define TPSPRESSURE_REG_LIMIT_2                 0x6E
#define TPSPRESSURE_REG_LIMIT_3                 0x6F
#define TPSPRESSURE_REG_LIMIT_4                 0x70
#define TPSPRESSURE_REG_INT_EN_0                0x73
#define TPSPRESSURE_REG_INT_EN_1                0x74
#define TPSPRESSURE_REG_INT_EN_2                0x75
#define TPSPRESSURE_REG_CUST                    0x76
#define TPSPRESSURE_REG_EN_CRC_U_MEM            0x7E
#define TPSPRESSURE_REG_CRC_USER_MEM            0x7F

/*! @} */ // tpspressure_reg

/**
 * @defgroup tpspressure_set TPS Pressure Registers Settings
 * @brief Settings for registers of TPS Pressure Click driver.
 */

/**
 * @addtogroup tpspressure_set
 * @{
 */

/**
 * @brief TPS Pressure measurement calculation setting.
 * @details Specified setting for measurement calculation of TPS Pressure Click driver.
 */
#define TPSPRESSURE_PRESSURE_MIN                ( -5.0 )
#define TPSPRESSURE_PRESSURE_MAX                ( 40.0 )
#define TPSPRESSURE_TEMPERATURE_MIN             ( -20.0 )
#define TPSPRESSURE_TEMPERATURE_MAX             ( 85.0 )
#define TPSPRESSURE_DATA_RESOLUTION             ( 0xFFFFFFul )
#define TPSPRESSURE_DATA_MIN                    ( TPSPRESSURE_DATA_RESOLUTION * 0.1 )
#define TPSPRESSURE_DATA_MAX                    ( TPSPRESSURE_DATA_RESOLUTION * 0.9 )

/**
 * @brief TPS Pressure sensor ID setting.
 * @details Specified setting for sensor ID of TPS Pressure Click driver.
 */
#define TPSPRESSURE_PART_NUMBER                 0x7765D96Cul

/**
 * @brief TPS Pressure timeout setting.
 * @details Specified setting for timeout of TPS Pressure Click driver.
 */
#define TPSPRESSURE_TIMEOUT_MS                  2000

/**
 * @brief TPS Pressure ADC setting.
 * @details Specified settings for ADC of TPS Pressure Click driver.
 */
#define TPSPRESSURE_VREF_3V3                    3.3
#define TPSPRESSURE_VREF_5V                     5.0

/**
 * @brief TPS Pressure device address setting.
 * @details Specified setting for device slave address selection of
 * TPS Pressure Click driver.
 */
#define TPSPRESSURE_DEVICE_ADDRESS              0x74

/*! @} */ // tpspressure_set

/**
 * @defgroup tpspressure_map TPS Pressure MikroBUS Map
 * @brief MikroBUS pin mapping of TPS Pressure Click driver.
 */

/**
 * @addtogroup tpspressure_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TPS Pressure Click to the selected MikroBUS.
 */
#define TPSPRESSURE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sdo = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // tpspressure_map
/*! @} */ // tpspressure

/**
 * @brief TPS Pressure Click context object.
 * @details Context object definition of TPS Pressure Click driver.
 */
typedef struct
{
    digital_out_t en;           /**< Device enable pin (active high). */

    digital_in_t sdo;           /**< Serial data output / device ready pin (active high). */

    i2c_master_t i2c;           /**< I2C driver object. */
    analog_in_t adc;            /**< ADC module object. */

    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} tpspressure_t;

/**
 * @brief TPS Pressure Click configuration object.
 * @details Configuration object definition of TPS Pressure Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t an;              /**< Analog pin descriptor. */

    pin_name_t en;              /**< Device enable pin (active high). */
    pin_name_t sdo;             /**< Serial data output / device ready pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} tpspressure_cfg_t;

/**
 * @brief TPS Pressure Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TPSPRESSURE_OK = 0,
    TPSPRESSURE_ERROR = -1

} tpspressure_return_value_t;

/*!
 * @addtogroup tpspressure TPS Pressure Click Driver
 * @brief API for configuring and manipulating TPS Pressure Click driver.
 * @{
 */

/**
 * @brief TPS Pressure configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tpspressure_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tpspressure_cfg_setup ( tpspressure_cfg_t *cfg );

/**
 * @brief TPS Pressure initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tpspressure_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure_init ( tpspressure_t *ctx, tpspressure_cfg_t *cfg );

/**
 * @brief TPS Pressure default configuration function.
 * @details This function executes a default configuration of TPS Pressure
 * Click board.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t tpspressure_default_cfg ( tpspressure_t *ctx );

/**
 * @brief TPS Pressure write command function.
 * @details This function writes a single command byte to the device
 * after waiting for the device-ready signal.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[in] cmd : Command opcode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid command, not ready, or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure_write_cmd ( tpspressure_t *ctx, uint8_t cmd );

/**
 * @brief TPS Pressure write command with data function.
 * @details This function writes a command followed by a 16-bit data word
 * to the device after waiting for the device-ready signal.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[in] cmd : Command opcode.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid command, not ready, or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure_write_cmd_data ( tpspressure_t *ctx, uint8_t cmd, uint16_t data_in );

/**
 * @brief TPS Pressure read command data function.
 * @details This function issues a command and reads one to four
 * 16-bit words from the device after waiting for the device-ready signal.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[in] cmd : Command opcode.
 * @param[out] data_out : Output buffer for 16-bit data words.
 * @param[in] len : Number of 16-bit words to read (1..4).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid args/command, not ready, or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure_read_cmd_data ( tpspressure_t *ctx, uint8_t cmd, uint16_t *data_out, uint8_t len );

/**
 * @brief TPS Pressure write command with address function.
 * @details This function writes a command and an 8-bit address
 * (e.g., for NVM erase) after waiting for the device-ready signal.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[in] cmd : Command opcode.
 * @param[in] addr : Register address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid args/command, not ready, or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure_write_cmd_addr ( tpspressure_t *ctx, uint8_t cmd, uint8_t addr );

/**
 * @brief TPS Pressure write command, address and data function.
 * @details This function writes a command, an 8-bit address, and a
 * 16-bit data word (e.g., for NVM/REG write) after waiting for ready.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[in] cmd : Command opcode.
 * @param[in] addr : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid args/command, not ready, or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure_write_cmd_addr_data ( tpspressure_t *ctx, uint8_t cmd, uint8_t addr, uint16_t data_in );

/**
 * @brief TPS Pressure read command, address and data function.
 * @details This function writes a command and an 8-bit address and
 * then reads one 16-bit word from the device after waiting for ready.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[in] cmd : Command opcode.
 * @param[in] addr : Register address.
 * @param[out] data_out : Output read 16-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid args/command, not ready, or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure_read_cmd_addr_data ( tpspressure_t *ctx, uint8_t cmd, uint8_t addr, uint16_t *data_out );

/**
 * @brief TPS Pressure read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure_read_raw_adc ( tpspressure_t *ctx, uint16_t *raw_adc );

/**
 * @brief TPS Pressure read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t tpspressure_read_voltage ( tpspressure_t *ctx, float *voltage );

/**
 * @brief TPS Pressure set vref function.
 * @details This function sets the voltage reference for TPS Pressure Click driver.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b tpspressure_init is 3.3V.
 */
err_t tpspressure_set_vref ( tpspressure_t *ctx, float vref );

/**
 * @brief TPS Pressure enable device function.
 * @details This function sets the enable control pin to a high logic level
 * to power-up or enable the device operation.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void tpspressure_enable_device ( tpspressure_t *ctx );

/**
 * @brief TPS Pressure disable device function.
 * @details This function sets the enable control pin to a low logic level
 * to power-down or disable the device operation.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void tpspressure_disable_device ( tpspressure_t *ctx );

/**
 * @brief TPS Pressure get SDO pin function.
 * @details This function reads the logic state of the SDO/DONE pin which
 * indicates device data-ready status (logic 1 = ready).
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @return Pin logic state: @li @c 0 - LOW,
 *                          @li @c 1 - HIGH.
 * @note None.
 */
uint8_t tpspressure_get_sdo_pin ( tpspressure_t *ctx );

/**
 * @brief TPS Pressure wait-ready function.
 * @details This function waits until the SDO/DONE pin goes HIGH,
 * indicating the device is ready for the next operation, with timeout protection.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @return @li @c  0 - Success (ready),
 *         @li @c -1 - Error (timeout).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure_wait_ready ( tpspressure_t *ctx );

/**
 * @brief TPS Pressure read sensor ID function.
 * @details This function reads the device identification fields and parses them
 * into part number, serial number, and wafer number values.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[out] part_num : Output part number (nullable).
 * @param[out] serial_num : Output serial number (nullable).
 * @param[out] wafer_num : Output wafer number (nullable).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (communication failure).
 * See #err_t definition for detailed explanation.
 * @note Any of the output pointers can be @c NULL if the value is not required.
 */
err_t tpspressure_read_sensor_id ( tpspressure_t *ctx, uint32_t *part_num, uint16_t *serial_num, uint16_t *wafer_num );

/**
 * @brief TPS Pressure communication check function.
 * @details This function verifies communication by reading the sensor ID
 * and validating the part number against the expected value.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @return @li @c  0 - Success (device recognized),
 *         @li @c -1 - Error (device not recognized or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure_check_communication ( tpspressure_t *ctx );

/**
 * @brief TPS Pressure read raw data function.
 * @details This function triggers a conversion and reads raw pressure and
 * temperature codes from the device.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[out] press : Output raw pressure code (nullable).
 * @param[out] temp : Output raw temperature code (nullable).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (conversion/communication failure).
 * See #err_t definition for detailed explanation.
 * @note Either output pointer may be @c NULL if the value is not needed.
 */
err_t tpspressure_read_raw_data ( tpspressure_t *ctx, uint32_t *press, uint32_t *temp );

/**
 * @brief TPS Pressure read converted data function.
 * @details This function reads pressure (mBar) and temperature (degC) values.
 * @param[in] ctx : Click context object.
 * See #tpspressure_t object definition for detailed explanation.
 * @param[out] press : Output pressure value in device units (nullable).
 * @param[out] temp : Output temperature value in device units (nullable).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (conversion/communication failure).
 * See #err_t definition for detailed explanation.
 * @note Either output pointer may be @c NULL if the value is not needed.
 */
err_t tpspressure_read_data ( tpspressure_t *ctx, float *press, float *temp );

#ifdef __cplusplus
}
#endif
#endif // TPSPRESSURE_H

/*! @} */ // tpspressure

// ------------------------------------------------------------------------ END
