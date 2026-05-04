/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file tpspressure150pd.h
 * @brief This file contains API for TPS Pressure 150PD Click Driver.
 */

#ifndef TPSPRESSURE150PD_H
#define TPSPRESSURE150PD_H

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
 * @addtogroup tpspressure150pd TPS Pressure 150PD Click Driver
 * @brief API for configuring and manipulating TPS Pressure 150PD Click driver.
 * @{
 */

/**
 * @defgroup tpspressure150pd_reg TPS Pressure 150PD Registers List
 * @brief List of registers of TPS Pressure 150PD Click driver.
 */

/**
 * @addtogroup tpspressure150pd_reg
 * @{
 */

/**
 * @brief TPS Pressure 150PD commands list.
 * @details Specified commands list of TPS Pressure 150PD Click driver.
 */
#define TPSPRESSURE150PD_CMD_READ_SENSOR_ID          0x08
#define TPSPRESSURE150PD_CMD_RESET                   0x10
#define TPSPRESSURE150PD_CMD_REFRESH                 0x12
#define TPSPRESSURE150PD_CMD_WRITE_OPERATING_MODE    0x14
#define TPSPRESSURE150PD_CMD_READ_OPERATING_MODE     0x16
#define TPSPRESSURE150PD_CMD_START_AUTOMATIC_MODE    0x18
#define TPSPRESSURE150PD_CMD_STOP_AUTOMATIC_MODE     0x1A
#define TPSPRESSURE150PD_CMD_WRITE_CONFIG_PRES_4     0x20
#define TPSPRESSURE150PD_CMD_WRITE_CONFIG_TEMP1_4    0x22
#define TPSPRESSURE150PD_CMD_READ_CONFIG_PRES_4      0x28
#define TPSPRESSURE150PD_CMD_READ_CONFIG_TEMP1_4     0x2A
#define TPSPRESSURE150PD_CMD_CONVERSION              0x4E
#define TPSPRESSURE150PD_CMD_READ_ADC_P              0x52
#define TPSPRESSURE150PD_CMD_READ_ADC_T1             0x54
#define TPSPRESSURE150PD_CMD_READ_ADC_T1_P           0x56
#define TPSPRESSURE150PD_CMD_WRITE_INTERRUPT_MASK    0x60
#define TPSPRESSURE150PD_CMD_READ_INTERRUPT_MASK     0x68
#define TPSPRESSURE150PD_CMD_WRITE_INTERRUPT_REG     0x70
#define TPSPRESSURE150PD_CMD_READ_INTERRUPT_REG      0x78
#define TPSPRESSURE150PD_CMD_WRITE_NVM               0x86
#define TPSPRESSURE150PD_CMD_ERASE_NVM               0x96
#define TPSPRESSURE150PD_CMD_READ_NVM                0xA6
#define TPSPRESSURE150PD_CMD_WRITE_LIMITS            0xC0
#define TPSPRESSURE150PD_CMD_READ_LIMITS             0xD0
#define TPSPRESSURE150PD_CMD_WRITE_REG               0xE0
#define TPSPRESSURE150PD_CMD_READ_REG                0xE2

/**
 * @brief TPS Pressure 150PD register list.
 * @details Specified register list of TPS Pressure 150PD Click driver.
 */
#define TPSPRESSURE150PD_REG_NVM_START               0x00
#define TPSPRESSURE150PD_REG_NVM_END                 0x1F
#define TPSPRESSURE150PD_REG_PRES_4                  0x61
#define TPSPRESSURE150PD_REG_TEMP1_4                 0x62
#define TPSPRESSURE150PD_REG_OPER                    0x64
#define TPSPRESSURE150PD_REG_DAC_2                   0x65
#define TPSPRESSURE150PD_REG_POST_GAIN_P             0x66
#define TPSPRESSURE150PD_REG_POST_GAIN_T1            0x67
#define TPSPRESSURE150PD_REG_POST_OFF_P              0x69
#define TPSPRESSURE150PD_REG_POST_OFF_T1             0x6A
#define TPSPRESSURE150PD_REG_COM                     0x6C
#define TPSPRESSURE150PD_REG_LIMIT_1                 0x6D
#define TPSPRESSURE150PD_REG_LIMIT_2                 0x6E
#define TPSPRESSURE150PD_REG_LIMIT_3                 0x6F
#define TPSPRESSURE150PD_REG_LIMIT_4                 0x70
#define TPSPRESSURE150PD_REG_INT_EN_0                0x73
#define TPSPRESSURE150PD_REG_INT_EN_1                0x74
#define TPSPRESSURE150PD_REG_INT_EN_2                0x75
#define TPSPRESSURE150PD_REG_CUST                    0x76
#define TPSPRESSURE150PD_REG_EN_CRC_U_MEM            0x7E
#define TPSPRESSURE150PD_REG_CRC_USER_MEM            0x7F

/*! @} */ // tpspressure150pd_reg

/**
 * @defgroup tpspressure150pd_set TPS Pressure 150PD Registers Settings
 * @brief Settings for registers of TPS Pressure 150PD Click driver.
 */

/**
 * @addtogroup tpspressure150pd_set
 * @{
 */

/**
 * @brief TPS Pressure 150PD measurement calculation setting.
 * @details Specified setting for measurement calculation of TPS Pressure 150PD Click driver.
 */
#define TPSPRESSURE150PD_PRESSURE_MIN                ( -150.0 )
#define TPSPRESSURE150PD_PRESSURE_MAX                ( 150.0 )
#define TPSPRESSURE150PD_TEMPERATURE_MIN             ( -20.0 )
#define TPSPRESSURE150PD_TEMPERATURE_MAX             ( 85.0 )
#define TPSPRESSURE150PD_DATA_RESOLUTION             ( 0xFFFFFFul )
#define TPSPRESSURE150PD_DATA_MIN                    ( TPSPRESSURE150PD_DATA_RESOLUTION * 0.1 )
#define TPSPRESSURE150PD_DATA_MAX                    ( TPSPRESSURE150PD_DATA_RESOLUTION * 0.9 )

/**
 * @brief TPS Pressure 150PD sensor ID setting.
 * @details Specified setting for sensor ID of TPS Pressure 150PD Click driver.
 */
#define TPSPRESSURE150PD_PART_NUMBER                 0x77666864ul

/**
 * @brief TPS Pressure 150PD timeout setting.
 * @details Specified setting for timeout of TPS Pressure 150PD Click driver.
 */
#define TPSPRESSURE150PD_TIMEOUT_MS                  2000

/**
 * @brief TPS Pressure 150PD ADC setting.
 * @details Specified settings for ADC of TPS Pressure 150PD Click driver.
 */
#define TPSPRESSURE150PD_VREF_3V3                    3.3
#define TPSPRESSURE150PD_VREF_5V                     5.0

/**
 * @brief TPS Pressure 150PD device address setting.
 * @details Specified setting for device slave address selection of
 * TPS Pressure 150PD Click driver.
 */
#define TPSPRESSURE150PD_DEVICE_ADDRESS              0x74

/*! @} */ // tpspressure150pd_set

/**
 * @defgroup tpspressure150pd_map TPS Pressure 150PD MikroBUS Map
 * @brief MikroBUS pin mapping of TPS Pressure 150PD Click driver.
 */

/**
 * @addtogroup tpspressure150pd_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TPS Pressure 150PD Click to the selected MikroBUS.
 */
#define TPSPRESSURE150PD_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sdo = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // tpspressure150pd_map
/*! @} */ // tpspressure150pd

/**
 * @brief TPS Pressure 150PD Click context object.
 * @details Context object definition of TPS Pressure 150PD Click driver.
 */
typedef struct
{
    digital_out_t en;           /**< Device enable pin (active high). */

    digital_in_t sdo;           /**< Serial data output / device ready pin (active high). */

    i2c_master_t i2c;           /**< I2C driver object. */
    analog_in_t adc;            /**< ADC module object. */

    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} tpspressure150pd_t;

/**
 * @brief TPS Pressure 150PD Click configuration object.
 * @details Configuration object definition of TPS Pressure 150PD Click driver.
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

} tpspressure150pd_cfg_t;

/**
 * @brief TPS Pressure 150PD Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TPSPRESSURE150PD_OK = 0,
    TPSPRESSURE150PD_ERROR = -1

} tpspressure150pd_return_value_t;

/*!
 * @addtogroup tpspressure150pd TPS Pressure 150PD Click Driver
 * @brief API for configuring and manipulating TPS Pressure 150PD Click driver.
 * @{
 */

/**
 * @brief TPS Pressure 150PD configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tpspressure150pd_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tpspressure150pd_cfg_setup ( tpspressure150pd_cfg_t *cfg );

/**
 * @brief TPS Pressure 150PD initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tpspressure150pd_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure150pd_init ( tpspressure150pd_t *ctx, tpspressure150pd_cfg_t *cfg );

/**
 * @brief TPS Pressure 150PD default configuration function.
 * @details This function executes a default configuration of TPS Pressure 150PD
 * Click board.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t tpspressure150pd_default_cfg ( tpspressure150pd_t *ctx );

/**
 * @brief TPS Pressure 150PD write command function.
 * @details This function writes a single command byte to the device
 * after waiting for the device-ready signal.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[in] cmd : Command opcode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid command, not ready, or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure150pd_wr_cmd ( tpspressure150pd_t *ctx, uint8_t cmd );

/**
 * @brief TPS Pressure 150PD write command with data function.
 * @details This function writes a command followed by a 16-bit data word
 * to the device after waiting for the device-ready signal.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[in] cmd : Command opcode.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid command, not ready, or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure150pd_wr_cmd_data ( tpspressure150pd_t *ctx, uint8_t cmd, uint16_t data_in );

/**
 * @brief TPS Pressure 150PD read command data function.
 * @details This function issues a command and reads one to four
 * 16-bit words from the device after waiting for the device-ready signal.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[in] cmd : Command opcode.
 * @param[out] data_out : Output buffer for 16-bit data words.
 * @param[in] len : Number of 16-bit words to read (1..4).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid args/command, not ready, or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure150pd_rd_cmd_data ( tpspressure150pd_t *ctx, uint8_t cmd, uint16_t *data_out, uint8_t len );

/**
 * @brief TPS Pressure 150PD write command with address function.
 * @details This function writes a command and an 8-bit address
 * (e.g., for NVM erase) after waiting for the device-ready signal.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[in] cmd : Command opcode.
 * @param[in] addr : Register address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid args/command, not ready, or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure150pd_wr_cmd_a ( tpspressure150pd_t *ctx, uint8_t cmd, uint8_t addr );

/**
 * @brief TPS Pressure 150PD write command, address and data function.
 * @details This function writes a command, an 8-bit address, and a
 * 16-bit data word (e.g., for NVM/REG write) after waiting for ready.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[in] cmd : Command opcode.
 * @param[in] addr : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid args/command, not ready, or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure150pd_wr_cmd_a_data ( tpspressure150pd_t *ctx, uint8_t cmd, uint8_t addr, uint16_t data_in );

/**
 * @brief TPS Pressure 150PD read command, address and data function.
 * @details This function writes a command and an 8-bit address and
 * then reads one 16-bit word from the device after waiting for ready.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[in] cmd : Command opcode.
 * @param[in] addr : Register address.
 * @param[out] data_out : Output read 16-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid args/command, not ready, or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure150pd_rd_cmd_a_data ( tpspressure150pd_t *ctx, uint8_t cmd, uint8_t addr, uint16_t *data_out );

/**
 * @brief TPS Pressure 150PD read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure150pd_read_raw_adc ( tpspressure150pd_t *ctx, uint16_t *raw_adc );

/**
 * @brief TPS Pressure 150PD read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t tpspressure150pd_read_voltage ( tpspressure150pd_t *ctx, float *voltage );

/**
 * @brief TPS Pressure 150PD set vref function.
 * @details This function sets the voltage reference for TPS Pressure 150PD Click driver.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b tpspressure150pd_init is 3.3V.
 */
err_t tpspressure150pd_set_vref ( tpspressure150pd_t *ctx, float vref );

/**
 * @brief TPS Pressure 150PD enable device function.
 * @details This function sets the enable control pin to a high logic level
 * to power-up or enable the device operation.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void tpspressure150pd_enable_device ( tpspressure150pd_t *ctx );

/**
 * @brief TPS Pressure 150PD disable device function.
 * @details This function sets the enable control pin to a low logic level
 * to power-down or disable the device operation.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void tpspressure150pd_disable_device ( tpspressure150pd_t *ctx );

/**
 * @brief TPS Pressure 150PD get SDO pin function.
 * @details This function reads the logic state of the SDO/DONE pin which
 * indicates device data-ready status (logic 1 = ready).
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @return Pin logic state: @li @c 0 - LOW,
 *                          @li @c 1 - HIGH.
 * @note None.
 */
uint8_t tpspressure150pd_get_sdo_pin ( tpspressure150pd_t *ctx );

/**
 * @brief TPS Pressure 150PD wait-ready function.
 * @details This function waits until the SDO/DONE pin goes HIGH,
 * indicating the device is ready for the next operation, with timeout protection.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @return @li @c  0 - Success (ready),
 *         @li @c -1 - Error (timeout).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure150pd_wait_ready ( tpspressure150pd_t *ctx );

/**
 * @brief TPS Pressure 150PD read sensor ID function.
 * @details This function reads the device identification fields and parses them
 * into part number, serial number, and wafer number values.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[out] part_num : Output part number (nullable).
 * @param[out] serial_num : Output serial number (nullable).
 * @param[out] wafer_num : Output wafer number (nullable).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (communication failure).
 * See #err_t definition for detailed explanation.
 * @note Any of the output pointers can be @c NULL if the value is not required.
 */
err_t tpspressure150pd_read_sensor_id ( tpspressure150pd_t *ctx, uint32_t *part_num, uint16_t *serial_num, uint16_t *wafer_num );

/**
 * @brief TPS Pressure 150PD communication check function.
 * @details This function verifies communication by reading the sensor ID
 * and validating the part number against the expected value.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @return @li @c  0 - Success (device recognized),
 *         @li @c -1 - Error (device not recognized or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tpspressure150pd_check_com ( tpspressure150pd_t *ctx );

/**
 * @brief TPS Pressure 150PD read raw data function.
 * @details This function triggers a conversion and reads raw pressure and
 * temperature codes from the device.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[out] press : Output raw pressure code (nullable).
 * @param[out] temp : Output raw temperature code (nullable).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (conversion/communication failure).
 * See #err_t definition for detailed explanation.
 * @note Either output pointer may be @c NULL if the value is not needed.
 */
err_t tpspressure150pd_read_raw_data ( tpspressure150pd_t *ctx, uint32_t *press, uint32_t *temp );

/**
 * @brief TPS Pressure 150PD read converted data function.
 * @details This function reads pressure (Pa) and temperature (degC) values.
 * @param[in] ctx : Click context object.
 * See #tpspressure150pd_t object definition for detailed explanation.
 * @param[out] press : Output pressure value in device units (nullable).
 * @param[out] temp : Output temperature value in device units (nullable).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (conversion/communication failure).
 * See #err_t definition for detailed explanation.
 * @note Either output pointer may be @c NULL if the value is not needed.
 */
err_t tpspressure150pd_read_data ( tpspressure150pd_t *ctx, float *press, float *temp );

#ifdef __cplusplus
}
#endif
#endif // TPSPRESSURE150PD_H

/*! @} */ // tpspressure150pd

// ------------------------------------------------------------------------ END
