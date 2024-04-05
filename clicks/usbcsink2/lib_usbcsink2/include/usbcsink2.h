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
 * @file usbcsink2.h
 * @brief This file contains API for USB-C Sink 2 Click Driver.
 */

#ifndef USBCSINK2_H
#define USBCSINK2_H

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
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup usbcsink2 USB-C Sink 2 Click Driver
 * @brief API for configuring and manipulating USB-C Sink 2 Click driver.
 * @{
 */

/**
 * @defgroup usbcsink2_reg USB-C Sink 2 Registers List
 * @brief List of registers of USB-C Sink 2 Click driver.
 */

/**
 * @addtogroup usbcsink2_reg
 * @{
 */

/**
 * @brief USB-C Sink 2 description register.
 * @details Specified register for description of USB-C Sink 2 Click driver.
 */
#define USBCSINK2_CMD_SRCPDO             0x00
#define USBCSINK2_CMD_PDONUM             0x1C
#define USBCSINK2_CMD_STATUS             0x1D
#define USBCSINK2_CMD_MASK               0x1E
#define USBCSINK2_CMD_VOLTAGE            0x20
#define USBCSINK2_CMD_CURRENT            0x21
#define USBCSINK2_CMD_TEMP               0x22
#define USBCSINK2_CMD_OCPTHR             0x23
#define USBCSINK2_CMD_OTPTHR             0x24
#define USBCSINK2_CMD_DRTHR              0x25
#define USBCSINK2_CMD_TR25               0x28
#define USBCSINK2_CMD_TR50               0x2A
#define USBCSINK2_CMD_TR75               0x2C
#define USBCSINK2_CMD_TR100              0x2E
#define USBCSINK2_CMD_RDO                0x30

/*! @} */ // usbcsink2_reg

/**
 * @defgroup usbcsink2_set USB-C Sink 2 Registers Settings
 * @brief Settings for registers of USB-C Sink 2 Click driver.
 */

/**
 * @addtogroup usbcsink2_set
 * @{
 */

/**
 * @brief USB-C Sink 2 PDO and RDO length data values.
 * @details Specified PDO and RDO length data values of USB-C Sink 2 Click driver.
 */
#define USBCSINK2_SRCPDO_LENGTH          28
#define USBCSINK2_RDO_LENGTH             4

/**
 * @brief USB-C Sink 2 status successful RDO request data value.
 * @details Specified status successful RDO request data value of USB-C Sink 2 Click driver.
 */
#define USBCSINK2_RDO_REQ_SUCCESS        0x03

/**
 * @brief USB-C Sink 2 voltage and current measured calculation data values.
 * @details Specified PDO and RDO length data values of USB-C Sink 2 Click driver.
 */
#define USBCSINK2_SENS_VTG_MV            80.0f
#define USBCSINK2_SENS_CURRENT_MA        24.0f

/**
 * @brief USB-C Sink 2 ADC setting.
 * @details Specified settings for ADC of USB-C Sink 2 Click driver.
 */
#define USBCSINK2_ADC_RESOLUTION         0x0FFF
#define USBCSINK2_VREF_3V3               3.3
#define USBCSINK2_VREF_5V                5.0

/**
 * @brief USB-C Sink 2 device address setting.
 * @details Specified setting for device slave address selection of
 * USB-C Sink 2 Click driver.
 */
#define USBCSINK2_SET_DEV_ADDR           0x51

/*! @} */ // usbcsink2_set

/**
 * @defgroup usbcsink2_map USB-C Sink 2 MikroBUS Map
 * @brief MikroBUS pin mapping of USB-C Sink 2 Click driver.
 */

/**
 * @addtogroup usbcsink2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB-C Sink 2 Click to the selected MikroBUS.
 */
#define USBCSINK2_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // usbcsink2_map
/*! @} */ // usbcsink2

/**
 * @brief USB-C Sink 2 Click context object.
 * @details Context object definition of USB-C Sink 2 Click driver.
 */
typedef struct
{
    digital_in_t int_pin;           /**< Interrupt pin. */

    analog_in_t  adc;               /**< ADC module object. */
    i2c_master_t i2c;               /**< I2C driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    float        vref;              /**< ADC reference voltage. */
    
    uint8_t number_of_valid_pdo;    /**< Total number of valid PDOs. */
    uint8_t pdo_data[ 28 ];         /**< Power Data Object data. */

} usbcsink2_t;

/**
 * @brief USB-C Sink 2 Click configuration object.
 * @details Configuration object definition of USB-C Sink 2 Click driver.
 */
typedef struct
{
    pin_name_t an;     /**< Analog pin descriptor. */
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;    /**< Interrupt pin. */

    analog_in_resolution_t resolution;    /**< ADC resolution. */
    float                  vref;          /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;      /**< I2C serial speed. */
    uint8_t                i2c_address;    /**< I2C slave address. */

} usbcsink2_cfg_t;

/**
 * @brief USB-C Sink 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBCSINK2_OK = 0,
    USBCSINK2_ERROR = -1

} usbcsink2_return_value_t;

/*!
 * @addtogroup usbcsink2 USB-C Sink 2 Click Driver
 * @brief API for configuring and manipulating USB-C Sink 2 Click driver.
 * @{
 */

/**
 * @brief USB-C Sink 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbcsink2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbcsink2_cfg_setup ( usbcsink2_cfg_t *cfg );

/**
 * @brief USB-C Sink 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbcsink2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink2_init ( usbcsink2_t *ctx, usbcsink2_cfg_t *cfg );

/**
 * @brief USB-C Sink 2 default configuration function.
 * @details This function executes a default configuration of USB-C Sink 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t usbcsink2_default_cfg ( usbcsink2_t *ctx );

/**
 * @brief USB-C Sink 2 data writing function.
 * @details This function writes a desired number of data bytes starting using desired command
 * of the AP33772, High-Performance USB PD Sink Controller
 * on the USB-C Sink 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink2_generic_write ( usbcsink2_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief USB-C Sink 2 data reading function.
 * @details This function reads a desired number of data bytes using desired command
 * of the AP33772, High-Performance USB PD Sink Controller
 * on the USB-C Sink 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink2_generic_read ( usbcsink2_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief USB-C Sink 2 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink2_read_raw_adc ( usbcsink2_t *ctx, uint16_t *raw_adc );

/**
 * @brief USB-C Sink 2 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t usbcsink2_read_voltage ( usbcsink2_t *ctx, float *voltage );

/**
 * @brief USB-C Sink 2 set vref function.
 * @details This function sets the voltage reference for USB-C Sink 2 click driver.
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b usbcsink2_init is 3.3V.
 */
err_t usbcsink2_set_vref ( usbcsink2_t *ctx, float vref );

/**
 * @brief USB-C Sink 2 PDO data reading function.
 * @details This function reads a source power delivery data of 28 bytes
 * and used to expose PD Source (SRC) power capabilities
 * of the AP33772, High-Performance USB PD Sink Controller
 * on the USB-C Sink 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[out] pdo :  Source Power Data Object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink2_read_pdo ( usbcsink2_t *ctx, uint8_t *pdo );

/**
 * @brief USB-C Sink 2 PDO number reading function.
 * @details This function reads the total number of valid PDOs
 * of the AP33772, High-Performance USB PD Sink Controller
 * on the USB-C Sink 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[out] pdo_num : Total number of valid PDOs.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink2_get_pdo_num ( usbcsink2_t *ctx, uint8_t *pdo_num );

/**
 * @brief USB-C Sink 2 status reading function.
 * @details This function reads the status data to reports the Sink Controller’s
 * of the AP33772, High-Performance USB PD Sink Controller
 * on the USB-C Sink 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink2_read_status ( usbcsink2_t *ctx, uint8_t *status );

/**
 * @brief USB-C Sink 2 wait RDO request function.
 * @details This function waith a successful RDO request
 * of the AP33772, High-Performance USB PD Sink Controller
 * on the USB-C Sink 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink2_wait_rdo_req_success ( usbcsink2_t *ctx );

/**
 * @brief USB-C Sink 2 get the voltage function.
 * @details This function reads the PDO voltage measured
 * of the AP33772, High-Performance USB PD Sink Controller
 * on the USB-C Sink 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[out] voltage_mv : Voltage [mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink2_get_pdo_voltage ( usbcsink2_t *ctx, float *voltage_mv );

/**
 * @brief USB-C Sink 2 get the current function.
 * @details This function reads the PDO current measured
 * of the AP33772, High-Performance USB PD Sink Controller
 * on the USB-C Sink 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[out] voltage_mv : Current [mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink2_get_pdo_current ( usbcsink2_t *ctx, float *current_ma );

/**
 * @brief USB-C Sink 2 get the temperature function.
 * @details This function reads the temperature
 * of the AP33772, High-Performance USB PD Sink Controller
 * on the USB-C Sink 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[out] temperature : Temperature [degree Celsius].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink2_get_temperature ( usbcsink2_t *ctx, uint8_t *temperature );

/**
 * @brief USB-C Sink 2 write the RDO function.
 * @details This function PDO request negotiation procedure, 
 * 4-byte data is written to RDO (Request Data Object)
 * of the AP33772, High-Performance USB PD Sink Controller
 * on the USB-C Sink 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[out] rdo : Request Data Object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink2_write_rdo ( usbcsink2_t *ctx, uint8_t *rdo );

/**
 * @brief USB-C Sink 2 hard reset the RDO function.
 * @details This function is used to reset by writing RDO register with all-zero data
 * of the AP33772, High-Performance USB PD Sink Controller
 * on the USB-C Sink 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @param[out] rdo : Request Data Object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The USB-C Sink 2 will be reset to its initial state and output will be turned off.
 */
err_t usbcsink2_reset ( usbcsink2_t *ctx );

/**
 * @brief USB-C Sink 2 get interrupt function.
 * @details This function get states of the Interrupt ( INT ) pin
 * of the AP33772, High-Performance USB PD Sink Controller
 * on the USB-C Sink 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #usbcsink2_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t usbcsink2_get_interrupt ( usbcsink2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // USBCSINK2_H

/*! @} */ // usbcsink2

// ------------------------------------------------------------------------ END
