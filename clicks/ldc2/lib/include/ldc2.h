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
 * @file ldc2.h
 * @brief This file contains API for LDC 2 Click Driver.
 */

#ifndef LDC2_H
#define LDC2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup ldc2 LDC 2 Click Driver
 * @brief API for configuring and manipulating LDC 2 Click driver.
 * @{
 */

/**
 * @defgroup ldc2_reg LDC 2 Registers List
 * @brief List of registers of LDC 2 Click driver.
 */

/**
 * @addtogroup ldc2_reg
 * @{
 */

/**
 * @brief LDC 2 register map.
 * @details Specified register map of LDC 2 Click driver.
 */
#define LDC2_REG_DEVICE_ID                      0x00
#define LDC2_REG_RP_MAX                         0x01
#define LDC2_REG_RP_MIN                         0x02
#define LDC2_REG_WDT_FREQ                       0x03
#define LDC2_REG_LDC_CONFIG                     0x04
#define LDC2_REG_COMPARATOR_THLD_HIGH           0x07  
#define LDC2_REG_COMPARATOR_THLD_LOW            0x09              
#define LDC2_REG_INTB_TERMINAL_CONFIG           0x0A
#define LDC2_REG_POWER_CONFIG                   0x0B
#define LDC2_REG_STATUS                         0x20
#define LDC2_REG_PROXIMITY_DATA                 0x22
#define LDC2_REG_FREQ_CNT_DATA_LSB              0x23
#define LDC2_REG_FREQ_CNT_DATA_MID_BYTE         0x24
#define LDC2_REG_FREQ_CNT_DATA_MSB              0x25

/*! @} */ // ldc2_reg

/**
 * @defgroup ldc2_set LDC 2 Registers Settings
 * @brief Settings for registers of LDC 2 Click driver.
 */

/**
 * @addtogroup ldc2_set
 * @{
 */

/**
 * @brief LDC 2 Device ID value.
 * @details Specified value for device ID of LDC 2 Click driver.
 */
#define LDC2_DEVICE_ID                          0x84

/**
 * @brief LDC 2 SPI read/write bit mask.
 * @details Specified bit mask for SPI read/write of LDC 2 Click driver.
 */
#define LDC2_SPI_READ_MASK                      0x80
#define LDC2_SPI_WRITE_MASK                     0x7F

/**
 * @brief LDC 2 Comparator threshold range.
 * @details Specified range for comparator threshold of LDC 2 Click driver.
 */
#define LDC2_COMPARATOR_THLD_MIN                0x00
#define LDC2_COMPARATOR_THLD_MAX                0xFF

/**
 * @brief LDC 2 status register flags.
 * @details Specified flags for status register of LDC 2 Click driver.
 */
#define LDC2_STATUS_OSC_STOPPED                 0x80
#define LDC2_STATUS_NO_NEW_DATA                 0x40
#define LDC2_STATUS_WAKE_UP_DISABLED            0x20
#define LDC2_STATUS_PROX_DATA_LESS_THAN_THLD    0x10

/**
 * @brief LDC 2 contants.
 * @details Specified constants for LDC 2 Click driver.
 */
#define LDC2_MHZ_TO_HZ                          1000000.0
#define LDC2_EXTERNAL_OSC_MHZ                   1.8432
#define LDC2_PARALLEL_CAPACITANCE_uF            0.000047
#define LDC2_MIN_SENSOR_FREQ_CONST              68.94
#define LDC2_MIN_SENSOR_FREQ_DIVIDER            2500.0
#define LDC2_ROUND_TO_NEAREST_INT               0.5

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b ldc2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define LDC2_SET_DATA_SAMPLE_EDGE               SET_SPI_DATA_SAMPLE_EDGE
#define LDC2_SET_DATA_SAMPLE_MIDDLE             SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // ldc2_set

/**
 * @defgroup ldc2_map LDC 2 MikroBUS Map
 * @brief MikroBUS pin mapping of LDC 2 Click driver.
 */

/**
 * @addtogroup ldc2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LDC 2 Click to the selected MikroBUS.
 */
#define LDC2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ldc2_map
/*! @} */ // ldc2

/**
 * @brief LDC 2 Click context object.
 * @details Context object definition of LDC 2 Click driver.
 */
typedef struct
{
    digital_in_t  int_pin;          /**< Interrupt pin. */

    // Modules
    spi_master_t  spi;              /**< SPI driver object. */

    pin_name_t  chip_select;        /**< Chip select pin descriptor (used for SPI driver). */

} ldc2_t;

/**
 * @brief LDC 2 Click configuration object.
 * @details Configuration object definition of LDC 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  int_pin;                                /**< Interrupt pin. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} ldc2_cfg_t;

/**
 * @brief LDC 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LDC2_OK = 0,
    LDC2_ERROR = -1

} ldc2_return_value_t;

/**
 * @brief LDC 2 Click Rp range values.
 * @details Enum values for Rp range settings.
 */
typedef enum
{
    LDC2_RP_3926p991 = 0,
    LDC2_RP_3141p593,
    LDC2_RP_2243p995,
    LDC2_RP_1745p329,
    LDC2_RP_1308p997,
    LDC2_RP_981p748,
    LDC2_RP_747p998,
    LDC2_RP_581p776,
    LDC2_RP_436p332,
    LDC2_RP_349p066,
    LDC2_RP_249p333,
    LDC2_RP_193p926,
    LDC2_RP_145p444,
    LDC2_RP_109p083,
    LDC2_RP_83p111,
    LDC2_RP_64p642,
    LDC2_RP_48p481,
    LDC2_RP_38p785,
    LDC2_RP_27p704,
    LDC2_RP_21p547,
    LDC2_RP_16p160,
    LDC2_RP_12p120,
    LDC2_RP_9p235,
    LDC2_RP_7p182,
    LDC2_RP_5p387,
    LDC2_RP_4p309,
    LDC2_RP_3p078,
    LDC2_RP_2p394,
    LDC2_RP_1p796,
    LDC2_RP_1p347,
    LDC2_RP_1p026,
    LDC2_RP_0p798

} ldc2_rp_range_t;

/**
 * @brief LDC 2 Click amplitude values.
 * @details Enum values for amplitude settings.
 */
typedef enum
{
    LDC2_AMPLITUDE_1V = 0,
    LDC2_AMPLITUDE_2V,
    LDC2_AMPLITUDE_4V,
    
} ldc2_amplitude_t;

/**
 * @brief LDC 2 Click response time values.
 * @details Enum values for response time settings.
 */
typedef enum
{
    LDC2_RESPONSE_TIME_192 = 2,
    LDC2_RESPONSE_TIME_384,
    LDC2_RESPONSE_TIME_768,
    LDC2_RESPONSE_TIME_1536,
    LDC2_RESPONSE_TIME_3072,
    LDC2_RESPONSE_TIME_6144,
    
} ldc2_resp_time_t;

/**
 * @brief LDC 2 Click INTB Terminal configuration values.
 * @details Enum values for INTB terminal settings.
 */
typedef enum
{
    LDC2_INTB_MODE_DISABLED = 0,
    LDC2_INTB_MODE_WAKE_UP,
    LDC2_INTB_MODE_COMPARATOR_OUT,
    LDC2_INTB_MODE_DRDY = 4,
    
} ldc2_int_mode_t;

/**
 * @brief LDC 2 Click Power configuration values.
 * @details Enum values for Power settings.
 */
typedef enum
{
    LDC2_PWR_MODE_STANDBY = 0,
    LDC2_PWR_MODE_ACTIVE
    
} ldc2_pwr_mode_t;

/*!
 * @addtogroup ldc2 LDC 2 Click Driver
 * @brief API for configuring and manipulating LDC 2 Click driver.
 * @{
 */

/**
 * @brief LDC 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ldc2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ldc2_cfg_setup ( ldc2_cfg_t *cfg );

/**
 * @brief LDC 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ldc2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_init ( ldc2_t *ctx, ldc2_cfg_t *cfg );

/**
 * @brief LDC 2 default configuration function.
 * @details This function executes a default configuration of LDC 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ldc2_default_cfg ( ldc2_t *ctx );

/**
 * @brief LDC 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_generic_write ( ldc2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LDC 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_generic_read ( ldc2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LDC 2 check device ID function.
 * @details This function reads and verifies the device ID.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error, wrong ID read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_check_device_id ( ldc2_t *ctx );

/**
 * @brief LDC 2 set Rp range function.
 * @details This function sets the Rp min and max registers.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[in] rp_min : Rp min value.
 * @param[in] rp_max : Rp max value.
 * See #ldc2_rp_range_t enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_set_rp_range ( ldc2_t *ctx, ldc2_rp_range_t rp_min, ldc2_rp_range_t rp_max );

/**
 * @brief LDC 2 set LDC config function.
 * @details This function sets the oscillation amplitude and response time of the LDC config register.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[in] amplitude : Oscillation amplitude.
 * See #ldc2_amplitude_t enum definition for detailed explanation.
 * @param[in] res_time : Response time.
 * See #ldc2_resp_time_t enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_set_ldc_config ( ldc2_t *ctx, ldc2_amplitude_t amplitude, ldc2_resp_time_t res_time );

/**
 * @brief LDC 2 set comparator threshold function.
 * @details This function sets the comparator threshold low and high values.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[in] thld_low : Low threshold.
 * @param[in] thld_high : High threshold.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_set_comparator_threshold ( ldc2_t *ctx, uint8_t thld_low, uint8_t thld_high );

/**
 * @brief LDC 2 set interrupt mode function.
 * @details This function sets the interrupt pin mode.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[in] mode : Interrupt mode.
 * See #ldc2_int_mode_t enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_set_interrupt_mode ( ldc2_t *ctx, ldc2_int_mode_t mode );

/**
 * @brief LDC 2 set power mode function.
 * @details This function sets the power mode.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[in] mode : Power mode.
 * See #ldc2_pwr_mode_t enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_set_power_mode ( ldc2_t *ctx, ldc2_pwr_mode_t mode );

/**
 * @brief LDC 2 get status function.
 * @details This function reads the status register.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[out] status : Status register content.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_get_status ( ldc2_t *ctx, uint8_t *status );

/**
 * @brief LDC 2 read raw data function.
 * @details This function reads the proximity and frequency counter data.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[out] prox_data : Proximity data [8-bit].
 * @param[out] freq_cnt : Frequency counter data [24-bit].
 * @return @li @c  0 - Success,
 *         @li @c  0x40 - No new data available,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_read_raw_data ( ldc2_t *ctx, uint8_t *prox_data, uint32_t *freq_cnt );

/**
 * @brief LDC 2 get response time function.
 * @details This function reads the response time value from the desired register and converts it to 
 * real response time value.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[out] res_time : Real response time value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_get_response_time ( ldc2_t *ctx, uint16_t *res_time );

/**
 * @brief LDC 2 get sensor frequency function.
 * @details This function reads and calculates the sensor frequency.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[out] freq : Sensor frequency in MHz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_get_sensor_frequency ( ldc2_t *ctx, float *freq );

/**
 * @brief LDC 2 get Rp range function.
 * @details This function reads the Rp min and max values from the desired registers and converts them
 * to resistance in kOhm.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[out] rp_min : Rp min value in kOhm.
 * @param[out] rp_max : Rp max value in kOhm.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_get_rp_range ( ldc2_t *ctx, float *rp_min, float *rp_max );

/**
 * @brief LDC 2 set watchdog timer frequency function.
 * @details This function sets the watchdog timer frequency based on the lowest sensor frequency.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_set_wdt_frequency ( ldc2_t *ctx );

/**
 * @brief LDC 2 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ldc2_get_int_pin ( ldc2_t *ctx );

/**
 * @brief LDC 2 measure resonance impedance function.
 * @details This function measures the resonance impedance and proximity data.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[out] prox_data : Proximity data.
 * @param[out] rp_data : Resonance impedance value in kOhm.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_measure_resonance_impedance ( ldc2_t *ctx, uint8_t *prox_data, float *rp_data );

/**
 * @brief LDC 2 measure inductance function.
 * @details This function measures the inductance and sensor frequency.
 * @param[in] ctx : Click context object.
 * See #ldc2_t object definition for detailed explanation.
 * @param[out] freq : Sensor frequency in MHz.
 * @param[out] inductance : Inductance in uH.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ldc2_measure_inductance ( ldc2_t *ctx, float *freq, float *inductance );

#ifdef __cplusplus
}
#endif
#endif // LDC2_H

/*! @} */ // ldc2

// ------------------------------------------------------------------------ END
