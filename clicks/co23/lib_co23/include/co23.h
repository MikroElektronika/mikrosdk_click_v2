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
 * @file co23.h
 * @brief This file contains API for CO2 3 Click Driver.
 */

#ifndef CO23_H
#define CO23_H

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
#include "drv_uart.h"

/*!
 * @addtogroup co23 CO2 3 Click Driver
 * @brief API for configuring and manipulating CO2 3 Click driver.
 * @{
 */

/**
 * @defgroup co23_reg CO2 3 Registers List
 * @brief List of registers of CO2 3 Click driver.
 */

/**
 * @addtogroup co23_reg
 * @{
 */

/**
 * @brief CO2 3 description register.
 * @details Specified register for description of CO2 3 Click driver.
 */
#define CO23_REG_PROD_ID                  0x00
#define CO23_REG_SENS_STS                 0x01
#define CO23_REG_MEAS_RATE_H              0x02
#define CO23_REG_MEAS_RATE_L              0x03
#define CO23_REG_MEAS_CFG                 0x04
#define CO23_REG_CO2PPM_H                 0x05
#define CO23_REG_CO2PPM_L                 0x06
#define CO23_REG_MEAS_STS                 0x07
#define CO23_REG_INT_CFG                  0x08
#define CO23_REG_ALARM_TH_H               0x09
#define CO23_REG_ALARM_TH_L               0x0A
#define CO23_REG_PRESS_REF_H              0x0B
#define CO23_REG_PRESS_REF_L              0x0C
#define CO23_REG_CALIB_REF_H              0x0D
#define CO23_REG_CALIB_REF_L              0x0E
#define CO23_REG_SCRATCH_PAD              0x0F
#define CO23_REG_SENS_RST                 0x10

/*! @} */ // co23_reg

/**
 * @defgroup co23_set CO2 3 Registers Settings
 * @brief Settings for registers of CO2 3 Click driver.
 */

/**
 * @addtogroup co23_set
 * @{
 */

/**
 * @brief CO2 3 description setting.
 * @details Specified setting for description of CO2 3 Click driver.
 */
#define CO23_OP_MODE_IDLE                 0x00
#define CO23_OP_MODE_SINGLE               0x01
#define CO23_OP_MODE_CONTINUOUS           0x02
#define CO23_OP_BOC_CFG_DISABLE           0x00
#define CO23_OP_BOC_CFG_AUTOMATIC         0x01
#define CO23_OP_BOC_CFG_FORCED            0x02
#define CO23_PWM_MODE_SINGLE_PULSE        0x00
#define CO23_PWM_MODE_TRAIN_PULSE         0x01 

/**
 * @brief CO2 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define CO23_TX_DRV_BUFFER_SIZE            100
#define CO23_RX_DRV_BUFFER_SIZE            300

/**
 * @brief CO2 3 device address setting.
 * @details Specified setting for device slave address selection of
 * CO2 3 Click driver.
 */
#define CO23_DEVICE_ADDRESS               0x28

/*! @} */ // co23_set

/**
 * @defgroup co23_map CO2 3 MikroBUS Map
 * @brief MikroBUS pin mapping of CO2 3 Click driver.
 */

/**
 * @addtogroup co23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of CO2 3 Click to the selected MikroBUS.
 */
#define CO23_MAP_MIKROBUS( cfg, mikrobus )           \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );    \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );    \
    cfg.pwo = MIKROBUS( mikrobus, MIKROBUS_AN );     \
    cfg.pws = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // co23_map
/*! @} */ // co23

/**
 * @brief CO2 3 Click driver selector.
 * @details Selects target driver interface of CO2 3 Click driver.
 */
typedef enum
{
    CO23_DRV_SEL_I2C,       /**< I2C driver descriptor. */
    CO23_DRV_SEL_UART       /**< UART driver descriptor. */

} co23_drv_t;

/**
 * @brief CO2 3 Click driver interface.
 * @details Definition of driver interface of CO2 3 Click driver.
 */
typedef err_t ( *co23_master_io_t )( struct co23_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief CO2 3 Click context object.
 * @details Context object definition of CO2 3 Click driver.
 */
typedef struct co23_s
{
    // Output pins
    digital_out_t pws;        /**< PWM disable pin. */

    // Input pins
    digital_in_t pwo;         /**< PWM output pin. */
    digital_in_t int_pin;     /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */
    uart_t uart;              /**< UART driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */
    
    // Buffers
    char uart_rx_buffer[ CO23_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    char uart_tx_buffer[ CO23_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    
    co23_drv_t drv_sel;          /**< Master driver interface selector. */
    co23_master_io_t write_f;    /**< Master write function. */
    co23_master_io_t read_f;     /**< Master read function. */

} co23_t;

/**
 * @brief CO2 3 Click configuration object.
 * @details Configuration object definition of CO2 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;     /**< RX pin. */
    pin_name_t tx_pin;     /**< TX pin. */
    
    pin_name_t scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t pwo;        /**< PWM output pin. */
    pin_name_t pws;        /**< PWM disable pin. */
    pin_name_t int_pin;    /**< Interrupt pin. */
    
    // Static variable
    uint32_t         baud_rate;        /**< Clock speed. */
    bool             uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;         /**< Data bits. */
    uart_parity_t    parity_bit;       /**< Parity bit. */
    uart_stop_bits_t stop_bit;         /**< Stop bits. */
    
    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */
    
    co23_drv_t drv_sel;        /**< Master driver interface selector. */

} co23_cfg_t;

/**
 * @brief CO2 3 Click sens status object.
 * @details Status object definition of CO2 3 Click driver.
 */
typedef struct
{
    uint8_t sen_rdy;
    uint8_t pwm_dis_st;
    uint8_t ortmp;
    uint8_t orvs;
    uint8_t iccer;
    uint8_t ortmp_clr;
    uint8_t orvs_clr;
    uint8_t iccer_clr;
    
} co23_sens_status_t;

/**
 * @brief CO2 3 Click measurement configuration object.
 * @details Measurement configuration object definition of CO2 3 Click driver.
 */
typedef struct
{
    uint8_t pwm_outen;
    uint8_t pwm_mode;
    uint8_t boc_cfg;
    uint8_t op_mode;
    
} co23_meas_cfg_t;

/**
 * @brief CO2 3 Click measurement status object.
 * @details Status object definition of CO2 3 Click driver.
 */
typedef struct
{
    uint8_t drdy;
    uint8_t int_sts;
    uint8_t alarm;
    uint8_t int_sts_clr;
    uint8_t alarm_clr;
    
} co23_meas_status_t;

/**
 * @brief CO2 3 Click interrupt configuration object.
 * @details Measurement configuration object definition of CO2 3 Click driver.
 */
typedef struct
{
    uint8_t int_typ;
    uint8_t int_func;
    uint8_t alarm_typ;
    
} co23_int_cfg_t;

/**
 * @brief CO2 3 Click soft reset command value data.
 * @details Predefined enum values for driver soft reset command values.
 */
typedef enum
{
    CO23_CMD_SOFT_RESET = 0xA3,
    CO23_CMD_RESET_ABOC = 0xBC,
    CO23_CMD_STEPWISE_FILTER_DIS = 0xDF,
    CO23_CMD_SAVE_FCS_CALIB_OFFSET = 0xCF,
    CO23_CMD_RESET_FCS             = 0xFC,
    CO23_CMD_STEPWISE_FILTER_EN = 0xFE

} co23_soft_reset_value_t;

/**
 * @brief CO2 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CO23_OK = 0,
    CO23_ERROR = -1

} co23_return_value_t;

/*!
 * @addtogroup co23 CO2 3 Click Driver
 * @brief API for configuring and manipulating CO2 3 Click driver.
 * @{
 */

/**
 * @brief CO2 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #co23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void co23_cfg_setup ( co23_cfg_t *cfg );

/**
 * @brief CO2 3 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #co23_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #co23_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void co23_drv_interface_selection ( co23_cfg_t *cfg, co23_drv_t drv_sel );

/**
 * @brief CO2 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #co23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_init ( co23_t *ctx, co23_cfg_t *cfg );

/**
 * @brief CO2 3 default configuration function.
 * @details This function executes a default configuration of CO2 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t co23_default_cfg ( co23_t *ctx );

/**
 * @brief CO2 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_generic_write ( co23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief CO2 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_generic_read ( co23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief CO2 3 get device ID function.
 * @details This function reads a device’s product and version ID
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[out] prod : Product ID.
 * @param[out] rev : Revision ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_get_device_id ( co23_t *ctx, uint8_t *prod, uint8_t *rev );

/**
 * @brief CO2 3 get sensor status function.
 * @details This function reads a sensor status object
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[out] sens_status : Sensor status object.
 * See co23_sens_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_get_sens_status ( co23_t *ctx, co23_sens_status_t *sens_status );

/**
 * @brief CO2 3 set measurement rate function.
 * @details This function set measurement period in continuous mode
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] meas_rate_sec : Measurement period in seconds [5 - 4095].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_set_meas_rate ( co23_t *ctx, uint16_t meas_rate_sec );

/**
 * @brief CO2 3 get measurement configuration function.
 * @details This function reads a measurement configuration object
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[out] meas_cfg : Measurement configuration object.
 * See co23_meas_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_get_meas_cfg ( co23_t *ctx, co23_meas_cfg_t *meas_cfg );

/**
 * @brief CO2 3 set measurement configuration function.
 * @details This function sets the operation settings of the device
 * by writing the measurement mode configuration object
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] meas_cfg : Measurement configuration object.
 * See co23_meas_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_set_meas_cfg ( co23_t *ctx, co23_meas_cfg_t meas_cfg );

/**
 * @brief CO2 3 get CO2 concentration function.
 * @details This function reads a CO2 concentration measurement data
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[out] co2_ppm : CO2 concentration measurement data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_get_co2_ppm ( co23_t *ctx, uint16_t *co2_ppm );

/**
 * @brief CO2 3 get measurement status function.
 * @details This function reads a measurement status object
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[out] sens_status : Measurement status object.
 * See co23_meas_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_get_meas_status ( co23_t *ctx, co23_meas_status_t *meas_status );

/**
 * @brief CO2 3 get interrupt pin configuration function.
 * @details This function reads a interrupt pin configuration object
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[out] int_cfg : Interrupt pin configuration object.
 * See co23_int_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_get_int_cfg ( co23_t *ctx, co23_int_cfg_t *int_cfg );

/**
 * @brief CO2 3 set interrupt pin configuration function.
 * @details This function sets the interrupt pin configuration
 * by writing the interrupt pin configuration object
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] int_cfg : Interrupt pin configuration object.
 * See co23_int_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_set_int_cfg ( co23_t *ctx, co23_int_cfg_t int_cfg );

/**
 * @brief CO2 3 set alarm threshold function.
 * @details This function sets the alarm threshold
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] alarm_th : Concatenated alarm threshold value [greater than 1000ppm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_set_alarm_threshold ( co23_t *ctx, uint16_t alarm_th_ppm );

/**
 * @brief CO2 3 set alarm threshold function.
 * @details This function sets the alarm threshold reference value
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] pressure_mbar : Pressure reference value [750mbar to 1150mbar].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_set_pressure_ref ( co23_t *ctx, uint16_t pressure_mbar );

/**
 * @brief CO2 3 set calibration function.
 * @details This function sets the calibration reference value
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] calib_ppm : Calibration reference value [350mbar to 900mbar].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_set_calib_ref ( co23_t *ctx, uint16_t calib_ppm );

/**
 * @brief CO2 3 soft reset trigger function.
 * @details This function is used to trigger a soft reset
 * of the XENSIV™ PAS CO2 on the CO2 3 Click board™. 
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @param[in] reset_cmd : Soft reset object.
 * See co23_soft_reset_value_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co23_soft_reset_trigger ( co23_t *ctx, co23_soft_reset_value_t reset_cmd );

/**
 * @brief CO2 3 get PWM output function.
 * @details This function get states of the PWM output ( PWO/AN ) pin
 * of XENSIV™ PAS CO2 on the CO2 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t co23_get_pwo_pin ( co23_t *ctx );

/**
 * @brief CO2 3 get interrupt function.
 * @details This function get states of the Interrupt ( INT ) pin
 * of XENSIV™ PAS CO2 on the CO2 3 Click board™.
 * @param[in] ctx : Click context object.
 * See #co23_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t co23_get_int_pin ( co23_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CO23_H

/*! @} */ // co23

// ------------------------------------------------------------------------ END
