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
 * @file proximity19.h
 * @brief This file contains API for Proximity 19 Click Driver.
 */

#ifndef PROXIMITY19_H
#define PROXIMITY19_H

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
 * @addtogroup proximity19 Proximity 19 Click Driver
 * @brief API for configuring and manipulating Proximity 19 Click driver.
 * @{
 */

/**
 * @defgroup proximity19_reg Proximity 19 Registers List
 * @brief List of registers of Proximity 19 Click driver.
 */

/**
 * @addtogroup proximity19_reg
 * @{
 */

/**
 * @brief Proximity 19 description register.
 * @details Specified register for description of Proximity 19 Click driver.
 */
#define PROXIMITY19_REG_SYSTEM_CONTROL    0x40
#define PROXIMITY19_REG_MODE_CONTROL0     0x41
#define PROXIMITY19_REG_MODE_CONTROL1     0x42
#define PROXIMITY19_REG_MODE_CONTROL2     0x43
#define PROXIMITY19_REG_PS_DATA_LSB       0x44
#define PROXIMITY19_REG_PS_DATA_MSB       0x45
#define PROXIMITY19_REG_PS_OFFSET_LSB     0x46
#define PROXIMITY19_REG_PS_OFFSET_MSB     0x47
#define PROXIMITY19_REG_INTERRUPT         0x4A
#define PROXIMITY19_REG_PS_TH_HIGH_LSB    0x4B
#define PROXIMITY19_REG_PS_TH_HIGH_MSB    0x4C
#define PROXIMITY19_REG_PS_TH_LOW_LSB     0x4D
#define PROXIMITY19_REG_PS_TH_LOW_MSB     0x4E
#define PROXIMITY19_REG_MANUFACT_ID       0x92


/*! @} */ // proximity19_reg

/**
 * @defgroup proximity19_set Proximity 19 Registers Settings
 * @brief Settings for registers of Proximity 19 Click driver.
 */

/**
 * @addtogroup proximity19_set
 * @{
 */

 /**
 * @brief Proximity 19 system control register bitmask.
 * @details Mode control 0 bitmask of Proximity 19 Click driver.
 */
#define PROXIMITY19_SW_RESET              0x80
#define PROXIMITY19_PART_ID_BITMASK       0x7F
#define PROXIMITY19_PART_ID_VAL           0x1C

 /**
 * @brief Proximity 19 mode control 0 register bitmask.
 * @details Mode control 0 bitmask of Proximity 19 Click driver.
 */
#define PROXIMITY19_PS_GAIN_X1            0x00
#define PROXIMITY19_PS_GAIN_X2            0x01
#define PROXIMITY19_PS_GAIN_BITMASK       0xF3
#define PROXIMITY19_PD_SEL_NO             0x00
#define PROXIMITY19_PD_SEL_FAR            0x01
#define PROXIMITY19_PD_SEL_NEAR           0x02
#define PROXIMITY19_PD_SEL_BOTH           0x03
#define PROXIMITY19_PD_SEL_BITMASK        0x03

 /**
 * @brief Proximity 19 mode control 1 register bitmask.
 * @details Mode control 1 register bitmask of Proximity 19 Click driver.
 */
#define PROXIMITY19_PERIOD_10_MS          0x00
#define PROXIMITY19_PERIOD_50_MS          0x01
#define PROXIMITY19_PERIOD_100_MS         0x02
#define PROXIMITY19_PERIOD_500_MS         0x03
#define PROXIMITY19_PERIOD_5_MS           0x04
#define PROXIMITY19_PERIOD_BITMASK        0x70
#define PROXIMITY19_PS_PULSE_50_US        0x00
#define PROXIMITY19_PS_PULSE_100_US       0x01
#define PROXIMITY19_PS_PULSE_200_US       0x02
#define PROXIMITY19_PS_PULSE_400_US       0x03
#define PROXIMITY19_PS_PULSE_BITMASK      0x0C
#define PROXIMITY19_VCSEL_CURR_3_MA       0x00
#define PROXIMITY19_VCSEL_CURR_4_MA       0x01
#define PROXIMITY19_VCSEL_CURR_5_MA       0x02
#define PROXIMITY19_VCSEL_CURR_BITMASK    0x03

 /**
 * @brief Proximity 19 mode control 2 register bitmask.
 * @details Mode control 2 register bitmask of Proximity 19 Click driver.
 */
#define PROXIMITY19_PS_DISABLE            0x00
#define PROXIMITY19_PS_ENABLE             0x01

 /**
 * @brief Proximity 19 PS threshold resolution.
 * @details PS threshold resolution of Proximity 19 Click driver.
 */
#define PROXIMITY19_PS_TH_RES             0x0F

 /**
 * @brief Proximity 19 PS data resolution.
 * @details PS data resolution of Proximity 19 Click driver.
 */
#define PROXIMITY19_PS_RES_MSB_BITMASK    0x07
#define PROXIMITY19_PS_OFFSET_BITMASK     0x01
#define PROXIMITY19_DET_RANGE_MIN         1.0f
#define PROXIMITY19_DET_RANGE_MAX         14.0f

/**
 * @brief Proximity 19 PS measurement result calculation values.
 * @details PS measurement result calculation values of Proximity 19 Click driver.
 */
#define PROXIMITY19_DATA_RANGE_50_US      0x03FEu
#define PROXIMITY19_DATA_RANGE_100_US     0x03FEu
#define PROXIMITY19_DATA_RANGE_200_US     0x07FEu
#define PROXIMITY19_DATA_RANGE_400_US     0x0FFEu

/**
 * @brief Proximity 19 PS gain.
 * @details PS gain values of Proximity 19 Click driver.
 */
#define PROXIMITY19_GAIN_X1               1.0f
#define PROXIMITY19_GAIN_X2               2.0f
#define PROXIMITY19_GAIN_X2_BOTH_PD       3.0f

/**
 * @brief Proximity 19 manufacture ID.
 * @details Manufacture ID value of Proximity 19 Click driver.
 */
#define PROXIMITY19_MANUFACT_ID           0xE0

/**
 * @brief Proximity 19 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 19 Click driver.
 */
#define PROXIMITY19_DEVICE_ADDRESS        0x39

/*! @} */ // proximity19_set

/**
 * @defgroup proximity19_map Proximity 19 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 19 Click driver.
 */

/**
 * @addtogroup proximity19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 19 Click to the selected MikroBUS.
 */
#define PROXIMITY19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity19_map
/*! @} */ // proximity19

/**
 * @brief Proximity 19 Click context object.
 * @details Context object definition of Proximity 19 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;    /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

    uint16_t data_range;     /**< Data range. */
    float gain;              /**< PS gain. */

} proximity19_t;

/**
 * @brief Proximity 19 Click configuration object.
 * @details Configuration object definition of Proximity 19 Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;        /**< Interrupt pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} proximity19_cfg_t;

/**
 * @brief Proximity 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROXIMITY19_OK = 0,
    PROXIMITY19_ERROR = -1

} proximity19_return_value_t;

/*!
 * @addtogroup proximity19 Proximity 19 Click Driver
 * @brief API for configuring and manipulating Proximity 19 Click driver.
 * @{
 */

/**
 * @brief Proximity 19 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity19_cfg_setup ( proximity19_cfg_t *cfg );

/**
 * @brief Proximity 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_init ( proximity19_t *ctx, proximity19_cfg_t *cfg );

/**
 * @brief Proximity 19 default configuration function.
 * @details This function executes a default configuration of Proximity 19
 * Click board.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity19_default_cfg ( proximity19_t *ctx );

/**
 * @brief Proximity 19 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_generic_write ( proximity19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Proximity 19 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_generic_read ( proximity19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Proximity 19 software reset function.
 * @details This function performs sensor software reset 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_sw_reset ( proximity19_t *ctx );

/**
 * @brief Proximity 19 get part ID function.
 * @details This function reads the part ID data 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[out] part_id : Part ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_get_part_id ( proximity19_t *ctx, uint8_t *part_id );

/**
 * @brief Proximity 19 set PS gain function.
 * @details This function adjusts the gain of the sensor's sensitivity to light reception
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] ps_gain : PS gain selection [0x00-0x01].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_set_ps_gain ( proximity19_t *ctx, uint8_t ps_gain );

/**
 * @brief Proximity 19 set PD photodiode function.
 * @details This function sets the desired PD photodiode 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] pd_sel : PD photodiode [0x00-0x03].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_set_pd_sel ( proximity19_t *ctx, uint8_t pd_sel );

/**
 * @brief Proximity 19 set period function.
 * @details This function sets the desired data measurement period value 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] period : Period [0x00-0x04].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_set_period ( proximity19_t *ctx, uint8_t period );

/**
 * @brief Proximity 19 set pulse width function.
 * @details This function sets the desired sensor pulse width value
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] pulse_width : VCSEL pulse width [0x00-0x03].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_set_pulse_width ( proximity19_t *ctx, uint8_t pulse_width );

/**
 * @brief Proximity 19 set VCSEL current function.
 * @details This function sets the desired VCSEL current value
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] vcsel_current : VCSEL current [0x00-0x02].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_set_vcsel_current ( proximity19_t *ctx, uint8_t vcsel_current );

/**
 * @brief Proximity 19 PS enable function.
 * @details This function performs PS data enabled
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] vcsel_current : VCSEL current [0x00-0x02].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_ps_enable ( proximity19_t *ctx );

/**
 * @brief Proximity 19 PS standby function.
 * @details This function sets PS standby mode 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] vcsel_current : VCSEL current [0x00-0x02].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_ps_disable ( proximity19_t *ctx );

/**
 * @brief Proximity 19 get PS data function.
 * @details This function reads the proximity sensor's raw data
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[out] ps_data : PS raw data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_get_ps_data ( proximity19_t *ctx, uint16_t *ps_data );

/**
 * @brief Proximity 19 get distance function.
 * @details This function reads the distance measured by the sensor in millimeters
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[out] proximity : Object distance in millimeters [1mm-15mm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_get_distance ( proximity19_t *ctx, float *distance );

/**
 * @brief Proximity 19 set PS offset function.
 * @details This function sets the desired PS offset value
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] ps_offset : PS offset data [0x0000-0x03FF].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_set_ps_offset ( proximity19_t *ctx, uint16_t ps_offset );

/**
 * @brief Proximity 19 interrupt configuration function.
 * @details This function sets the desired configuration of the interrupt register
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] ps_offset : PS offset data [0x0000-0x03FF].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_int_cfg ( proximity19_t *ctx, uint8_t int_cfg );

/**
 * @brief Proximity 19 set PS threshold function.
 * @details This function sets the desired high and low threshold data 
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[in] ps_th_high : High threshold data [0x0000-0x0FFF].
 * @param[in] ps_th_low : Low threshold data [0x0000-0x0FFF].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_set_ps_th ( proximity19_t *ctx, uint16_t ps_th_high, uint16_t ps_th_low );

/**
 * @brief Proximity 19 get manufacture ID function.
 * @details This function reads the manufacturer ID data
 * by using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @param[out] manufact_id : Manufacturer ID data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proximity19_get_manufact_id ( proximity19_t *ctx, uint8_t *manufact_id );

/**
 * @brief Proximity 19 get interrupt function.
 * @details This function get states of the Interrupt ( INT ) pin
 * of the RPR-0720, Reflective Type Photosensor Miniature Proximity Sensor
 * on the Proximity 19 Click board.
 * @param[in] ctx : Click context object.
 * See #proximity19_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t proximity19_get_int_pin ( proximity19_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY19_H

/*! @} */ // proximity19

// ------------------------------------------------------------------------ END
