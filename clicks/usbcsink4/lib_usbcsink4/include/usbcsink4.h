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
 * @file usbcsink4.h
 * @brief This file contains API for USB-C Sink 4 Click Driver.
 */

#ifndef USBCSINK4_H
#define USBCSINK4_H

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

/*!
 * @addtogroup usbcsink4 USB-C Sink 4 Click Driver
 * @brief API for configuring and manipulating USB-C Sink 4 Click driver.
 * @{
 */

/**
 * @defgroup usbcsink4_reg USB-C Sink 4 Registers List
 * @brief List of registers of USB-C Sink 4 Click driver.
 */

/**
 * @addtogroup usbcsink4_reg
 * @{
 */

/**
 * @brief USB-C Sink 4 description register.
 * @details Specified register for description of USB-C Sink 4 Click driver.
 */
#define USBCSINK4_REG_DEVICE_MODE                0x0000u
#define USBCSINK4_REG_SILICON_ID                 0x0002u
#define USBCSINK4_REG_INTERRUPT                  0x0006u
#define USBCSINK4_REG_TYPE_C_STATUS              0x100Cu
#define USBCSINK4_REG_BUS_VOLTAGE                0x100Du
#define USBCSINK4_REG_BUS_CURRENT                0x1058u
#define USBCSINK4_REG_EVENT_STATUS               0x1034u
#define USBCSINK4_REG_CHARGING_MODE_STATUS       0x1095u
#define USBCSINK4_REG_RESET                      0x0008u
#define USBCSINK4_REG_EVENT_MASK                 0x1024u
#define USBCSINK4_REG_FAULT_PIN_MASK             0x1080u
#define USBCSINK4_REG_OVP_CONFIG                 0x1088u
#define USBCSINK4_REG_SNK_FET_DISABLE            0x1084u
#define USBCSINK4_REG_SNK_FET_CONTROL            0x1085u
#define USBCSINK4_REG_SAFE_PWR_CONTROL           0x1086u
#define USBCSINK4_REG_CHARGING_MODE_DISABLE      0x1094u
#define USBCSINK4_REG_DEV_RESPONSE               0x007Eu
#define USBCSINK4_REG_PD_RESPONSE                0x1400u
#define USBCSINK4_REG_READ_DATA_MEMORY_START     0x1404u
#define USBCSINK4_REG_READ_DATA_MEMORY_STOP      0x150Bu
#define USBCSINK4_REG_WRITE_DATA_MEMORY_START    0x1800u
#define USBCSINK4_REG_WRITE_DATA_MEMORY_STOP     0x19FFu

/*! @} */ // usbcsink4_reg

/**
 * @defgroup usbcsink4_set USB-C Sink 4 Registers Settings
 * @brief Settings for registers of USB-C Sink 4 Click driver.
 */

/**
 * @addtogroup usbcsink4_set
 * @{
 */

/**
 * @brief USB-C Sink 4 description setting.
 * @details Specified setting for description of USB-C Sink 4 Click driver.
 */
#define USBCSINK4_TYPE_C_ST_PORT_DISCONN         0x00
#define USBCSINK4_TYPE_C_ST_PORT_CONN            0x01
#define USBCSINK4_TYPE_C_ST_PORT_BITMAKS         0x01
#define USBCSINK4_TYPE_C_ST_CC_1                 0x00
#define USBCSINK4_TYPE_C_ST_CC_2                 0x01
#define USBCSINK4_TYPE_C_ST_CC_BITMAKS           0x01
#define USBCSINK4_TYPE_C_ST_ATT_NTH              0x00
#define USBCSINK4_TYPE_C_ST_ATT_SRC              0x02
#define USBCSINK4_TYPE_C_ST_ATT_DEBUG            0x03
#define USBCSINK4_TYPE_C_ST_ATT_BITMAKS          0x07
#define USBCSINK4_TYPE_C_ST_CURR_0_9A            0x00
#define USBCSINK4_TYPE_C_ST_CURR_1A              0x01
#define USBCSINK4_TYPE_C_ST_CURR_3A              0x02
#define USBCSINK4_TYPE_C_ST_CURR_BITMAKS         0x03

/**
 * @brief USB-C Sink 4 legacy charging mode support and status setting.
 * @details Specified setting for legacy charging mode support and status of USB-C Sink 4 Click driver.
 */
#define USBCSINK4_CHARGING_MODE_ENABLE           0x00
#define USBCSINK4_CHARGING_MODE_DISABLE          0x01
#define USBCSINK4_CHG_MODE_STATUS_CLEAR          0xFF

/**
 * @brief USB-C Sink 4 active Legacy charging mode.
 * @details active Legacy charging mode of USB-C Sink 4 Click driver.
 */
#define USBCSINK4_CHG_MODE_STATUS_NO_LGC         0x00
#define USBCSINK4_CHG_MODE_STATUS_BC1_2DCP_CDC   0x01
#define USBCSINK4_CHG_MODE_STATUS_QC2_1          0x02
#define USBCSINK4_CHG_MODE_STATUS_AFC            0x04
#define USBCSINK4_CHG_MODE_STATUS_APPLE          0x05

/**
 * @brief USB-C Sink 4 active Legacy charging mode.
 * @details active Legacy charging mode of USB-C Sink 4 Click driver.
 */
#define USBCSINK4_INTERRUPT_RESPONSE_NO          0x00
#define USBCSINK4_INTERRUPT_RESPONSE_DEV         0x01
#define USBCSINK4_INTERRUPT_RESPONSE_PD          0x02

/**
 * @brief USB-C Sink 4 voltage and current sensitivity setting.
 * @details Specified setting for description of USB-C Sink 4 Click driver.
 */
#define USBCSINK4_VOLTAGE_SENS                   0.1f
#define USBCSINK4_CURRENT_SENS                   0.05f

/**
 * @brief USB-C Sink 4 OVP configuration data values.
 * @details OVP configuration data values of USB-C Sink 4 Click driver.
 */
#define USBCSINK4_OVP_CONFIG_SIG_DISABLE        'D'
#define USBCSINK4_OVP_CONFIG_SIG_RE_ENABLE      'C'
#define USBCSINK4_OVP_CONFIG_THOLD_DEFAULT       0x28
#define USBCSINK4_OVP_CONFIG_DBNC_DEFAULT        0x0A

/**
 * @brief USB-C Sink 4 reset the device or the I2C block.
 * @details reset the device or the I2C block of USB-C Sink 4 Click driver.
 */
#define USBCSINK4_SIG_RESET                      'R'
#define USBCSINK4_RESET_I2C                      0x00
#define USBCSINK4_RESET_DEVICE                   0x01

/**
 * @brief USB-C Sink 4 device response data values.
 * @details Device response data values of USB-C Sink 4 Click driver.
 */
#define USBCSINK4_DEV_RSP_CMD_REG_WRITE          0x00
#define USBCSINK4_DEV_RSP_ASYNC_EVENT            0x80
#define USBCSINK4_DEV_RSP_CODE_NO_RSP            0x00
#define USBCSINK4_DEV_RSP_CODE_SUCCESS           0x02
#define USBCSINK4_DEV_RSP_CODE_INVALID           0x05
#define USBCSINK4_DEV_RSP_CODE_UNEXPECTED        0x09
#define USBCSINK4_DEV_RSP_CODE_NOT_SUPPORTED     0x0A
#define USBCSINK4_DEV_RSP_CODE_TXN_FAILED        0x0C
#define USBCSINK4_DEV_RSP_CODE_PD_CMD_FAILED     0x0D
#define USBCSINK4_DEV_RSP_CODE_PORT_BUSY         0x12
#define USBCSINK4_DEV_RSP_CODE_RST_CPLT          0x80
#define USBCSINK4_DEV_RSP_CODE_MSG_QUEUE_OVF     0x81
#define USBCSINK4_DEV_RSP_CODE_OVC               0x82
#define USBCSINK4_DEV_RSP_CODE_OVV               0x83
#define USBCSINK4_DEV_RSP_CODE_PORT_CONN         0x84
#define USBCSINK4_DEV_RSP_CODE_PORT_DISCONN      0x85
#define USBCSINK4_DEV_RSP_CODE_PD_NEG_CPLT       0x86
#define USBCSINK4_DEV_RSP_CODE_SWAP_CPLT         0x87
#define USBCSINK4_DEV_RSP_CODE_PS_RDY            0x8A
#define USBCSINK4_DEV_RSP_CODE_GOTOMIN           0x8B
#define USBCSINK4_DEV_RSP_CODE_ACCEPT            0x8C
#define USBCSINK4_DEV_RSP_CODE_REJECT            0x8D
#define USBCSINK4_DEV_RSP_CODE_WAIT              0x8E
#define USBCSINK4_DEV_RSP_CODE_HARD_RST          0x8F
#define USBCSINK4_DEV_RSP_CODE_VDM_REC           0x90
#define USBCSINK4_DEV_RSP_CODE_SRC_CAPB          0x91
#define USBCSINK4_DEV_RSP_CODE_SINK_CAPB         0x92
#define USBCSINK4_DEV_RSP_CODE_HARD_RST_SENT     0x9A
#define USBCSINK4_DEV_RSP_CODE_SOFT_RST_SENT     0x9B
#define USBCSINK4_DEV_RSP_CODE_SRC_DIS           0x9D
#define USBCSINK4_DEV_RSP_CODE_NO_VDM_RES_REC    0x9F

/**
 * @brief USB-C Sink 4 silicon ID value.
 * @details Silicon ID value of USB-C Sink 4 Click driver.
 */
#define USBCSINK4_SILICON_ID_BCR_LITE            0x20A2u

/**
 * @brief USB-C Sink 4 device address setting.
 * @details Specified setting for device slave address selection of
 * USB-C Sink 4 Click driver.
 */
#define USBCSINK4_DEVICE_ADDRESS                 0x08

/*! @} */ // usbcsink4_set

/**
 * @defgroup usbcsink4_map USB-C Sink 4 MikroBUS Map
 * @brief MikroBUS pin mapping of USB-C Sink 4 Click driver.
 */

/**
 * @addtogroup usbcsink4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB-C Sink 4 Click to the selected MikroBUS.
 */
#define USBCSINK4_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // usbcsink4_map
/*! @} */ // usbcsink4

/**
 * @brief USB-C Sink 4 Click context object.
 * @details Context object definition of USB-C Sink 4 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t flt;         /**< Fault conditions pin. */
    digital_in_t int_pin;     /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} usbcsink4_t;

/**
 * @brief USB-C Sink 4 Click configuration object.
 * @details Configuration object definition of USB-C Sink 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */
    
    pin_name_t flt;            /**< Fault conditions pin. */
    pin_name_t int_pin;        /**< Interrupt pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} usbcsink4_cfg_t;

/**
 * @brief USB-C Sink 4 Click status of the Type-C port.
 * @details Status of the Type-C port object definition of USB-C Sink 4 Click driver.
 */
typedef struct
{
    uint8_t port_par_cxn;     /**< Port Partner Connection Status. */
    uint8_t cc_pol;           /**< CC Polarity Status. */
    uint8_t att_dev_type;     /**< Attached Device Type Status. */
    uint8_t curr_lvl;         /**< Current Level Status. */

} usbcsink4_type_c_status_t;

/**
 * @brief USB-C Sink 4 Click status of the event.
 * @details Status of the event of USB-C Sink 4 Click driver.
 */
typedef struct
{
    uint8_t dev_att;           /**< Type-C Device Attached . */
    uint8_t dev_disc;          /**< Type-C Device Disconnected. */
    uint8_t pd_cn_comp;        /**< PD Contract Negotiation Completed. */
    uint8_t pwr_role;          /**< Power Role Swap Completed. */
    uint8_t data_role;         /**< Data Role Swap Completed. */
    uint8_t vconn;             /**< VCONN Swap Completed. */
    uint8_t hw_rst_rec;        /**< Hard Reset received. */
    uint8_t hw_rst_sent;       /**< Hard Reset sent. */
    uint8_t soft_rst_sent;     /**< Soft Reset sent. */
    uint8_t cable_rst_sent;    /**< Cable Reset sent. */
    uint8_t err_rcvy;          /**< Type-C Error Recovery initiated. */
    uint8_t vbus_err;          /**< Unexpected voltage on VBUS. */
    uint8_t vbus_vtg_ovr;      /**< VBUS voltage is over expected voltage range. */
    uint8_t vbus_curr_ovr;     /**< VBUS current is over the limit value. */

} usbcsink4_event_status_t;


/**
 * @brief USB-C Sink 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBCSINK4_OK = 0,
    USBCSINK4_ERROR = -1

} usbcsink4_return_value_t;

/*!
 * @addtogroup usbcsink4 USB-C Sink 4 Click Driver
 * @brief API for configuring and manipulating USB-C Sink 4 Click driver.
 * @{
 */

/**
 * @brief USB-C Sink 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbcsink4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbcsink4_cfg_setup ( usbcsink4_cfg_t *cfg );

/**
 * @brief USB-C Sink 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbcsink4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink4_init ( usbcsink4_t *ctx, usbcsink4_cfg_t *cfg );

/**
 * @brief USB-C Sink 4 default configuration function.
 * @details This function executes a default configuration of USB-C Sink 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t usbcsink4_default_cfg ( usbcsink4_t *ctx );

/**
 * @brief USB-C Sink 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink4_generic_write ( usbcsink4_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief USB-C Sink 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink4_generic_read ( usbcsink4_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief USB-C Sink 4 get Silicon ID function.
 * @details This function reads the Silicon ID of the device 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @param[out] silicon_id : Silicon ID of the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink4_get_silicon_id ( usbcsink4_t *ctx, uint16_t *silicon_id );

/**
 * @brief USB-C Sink 4 get Type-C status function.
 * @details This function reads the reports of the status of the Type-C port
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @param[out] type_c_status : Status of the Type-C port object.
 * See #usbcsink4_type_c_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink4_get_type_c_status ( usbcsink4_t *ctx, usbcsink4_type_c_status_t *type_c_status );

/**
 * @brief USB-C Sink 4 get VBUS function.
 * @details This function reads the live voltage on the VBUS supply for the specified port
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @param[out] vbus_v : Voltage [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink4_get_bus_voltage ( usbcsink4_t *ctx, float *vbus_v );

/**
 * @brief USB-C Sink 4 get VBUS current function.
 * @details This function reads the live current draw on the VBUS supply for the specified port
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @param[out] vbus_c : Current [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink4_get_bus_current ( usbcsink4_t *ctx, float *vbus_c );

/**
 * @brief USB-C Sink 4 get event status function.
 * @details This function reads the reports of the event status 
 * to know what has happened on the Type-C/PD port
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @param[out] event_status : Event status object.
 * See #usbcsink4_event_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink4_get_event_status ( usbcsink4_t *ctx, usbcsink4_event_status_t *event_status );

/**
 * @brief USB-C Sink 4 get charging mode function.
 * @details This function reads the status reports of the active legacy charging mode
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @param[out] chrg_mode : Legacy charging mode status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink4_get_chrg_mode ( usbcsink4_t *ctx, uint8_t *chrg_mode );

/**
 * @brief USB-C Sink 4 reset the device function.
 * @details This function performs the software reset of the device
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink4_reset_device ( usbcsink4_t *ctx );

/**
 * @brief USB-C Sink 4 reset the I2C block function.
 * @details This function performs the software reset of the I2C block
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink4_reset_i2c ( usbcsink4_t *ctx );

/**
 * @brief USB-C Sink 4 get response function.
 * @details This function is used to store responses to commands sent on certain command registers
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @param[in] rsp_code : Response Code.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink4_get_response ( usbcsink4_t *ctx, uint8_t *rsp_code );

/**
 * @brief USB-C Sink 4 get interrupt function.
 * @details This function get states of the interrupt pin.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t usbcsink4_get_interrupt ( usbcsink4_t *ctx );

/**
 * @brief USB-C Sink 4 get fault indicator function.
 * @details This function get states of the fault indicator pin.
 * @param[in] ctx : Click context object.
 * See #usbcsink4_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t usbcsink4_get_fault_condition ( usbcsink4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // USBCSINK4_H

/*! @} */ // usbcsink4


// ------------------------------------------------------------------------ END
