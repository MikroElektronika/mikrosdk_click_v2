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
 * @file loadcell5.h
 * @brief This file contains API for Load Cell 5 Click Driver.
 */

#ifndef LOADCELL5_H
#define LOADCELL5_H

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
#include "drv_spi_master.h"
    
    
/*!
 * @addtogroup loadcell5 Load Cell 5 Click Driver
 * @brief API for configuring and manipulating Load Cell 5 Click driver.
 * @{
 */

/**
 * @defgroup loadcell5_set Load Cell 5 Registers Settings
 * @brief Settings for registers of Load Cell 5 Click driver.
 */

/**
 * @addtogroup loadcell5_set
 * @{
 */

/**
 * @addtogroup pwr_mode
 * @{
 */

/**
 * @brief Load Cell 5 ADC power mode setting.
 * @details Specified setting for ADC power mode
 * of Load Cell 5 Click driver.
 */
#define LOADCELL5_MODE_POWER_DOWN             0x00
#define LOADCELL5_MODE_POWER_UP               0x01

/*! @} */ // pwr_mode

/**
 * @addtogroup fil_sel
 * @{
 */

/**
 * @brief Load Cell 5 Filter Select setting.
 * @details Specified setting for update rate
 * of Load Cell 5 Click driver.
 */
#define LOADCELL5_UPDATE_RATE_16_7_Hz         0x00
#define LOADCELL5_UPDATE_RATE_10_Hz           0x01

/*! @} */ // fil_sel

/**
 * @addtogroup gain
 * @{
 */

/**
 * @brief Load Cell 5 gain setting.
 * @details Specified gain setting 
 * of Load Cell 5 Click driver.
 */
#define LOADCELL5_GAIN_1                        1
#define LOADCELL5_GAIN_128                    128

/*! @} */ // gain


/*! @} */ // loadcell5_set

/**
 * @defgroup loadcell5_set Load Cell 5 Registers Settings
 * @brief Settings for registers of Load Cell 5 Click driver.
 */

/**
 * @addtogroup loadcell5_get
 * @{
 */

/**
 * @addtogroup check_data_ready
 * @{
 */

/**
 * @brief Load Cell 5 check data ready.
 * @details Specified check new data is available
 * of Load Cell 5 Click driver.
 */
#define LOADCELL5_NEW_DATA_IS_AVAILABLE         0
#define LOADCELL5_NO_DATA                       1

/*! @} */ // check_data_ready

/**
 * @addtogroup status
 * @{
 */

/**
 * @brief Load Cell 5 status.
 * @details Specified check status
 * of Load Cell 5 Click driver.
 */
#define LOADCELL5_STATUS_PAT_ADC_PERFORMED_NOT_CORRECTLY           0x00
#define LOADCELL5_STATUS_PAT_ADC_PERFORMED_CORRECTLY               0x01
#define LOADCELL5_STATUS_GAIN_128                                  0x00
#define LOADCELL5_STATUS_GAIN_1                                    0x04
#define LOADCELL5_STATUS_BITS_ID_0                                 0x08
#define LOADCELL5_STATUS_BITS_ID_1                                 0x10    
#define LOADCELL5_STATUS_ERROR                                     0x20
#define LOADCELL5_STATUS_FILTER_UPDATE_RATE_16_7_HZ                0x00
#define LOADCELL5_STATUS_FILTER_UPDATE_RATE_10_HZ                  0x40
#define LOADCELL5_STATUS_CONVERSION_NOT_AVAILABLE                  0x80
#define LOADCELL5_STATUS_CONVERSION_IS_AVAILABLE                   0x00
#define LOADCELL5_STATUS_CONVERSION_NOT_AVAILABLE                  0x80

/**
 * @brief Load Cell 5 data status.
 * @details Specified check data status
 * of Load Cell 5 Click driver.
 */
#define LOADCELL5_DATA_NO_DATA                                     0
#define LOADCELL5_DATA_OK                                          1   

/*! @} */ // status


/*! @} */ // loadcell5_get

/**
 * @addtogroup loadcell5_cfg_data
 * @{
 */

/**
 * @addtogroup weight
 * @{
 */

/**
 * @brief Load Cell 5 weight data.
 * @details Specified weight data.
 */
#define LOADCELL5_WEIGHT_ZERO                                      0
#define LOADCELL5_WEIGHT_100G                                      100
#define LOADCELL5_WEIGHT_500G                                      500
#define LOADCELL5_WEIGHT_1000G                                     1000
#define LOADCELL5_WEIGHT_5000G                                     5000
#define LOADCELL5_WEIGHT_10000G                                    10000

/*! @} */ // weight

/**
 * @addtogroup status
 * @{
 */

/**
 * @brief Load Cell 5 status.
 * @details Specified check status
 * of Load Cell 5 Click driver.
 */
#define LOADCELL5_STATUS_PAT_ADC_PERFORMED_NOT_CORRECTLY           0x00
#define LOADCELL5_STATUS_PAT_ADC_PERFORMED_CORRECTLY               0x01
#define LOADCELL5_STATUS_GAIN_128                                  0x00
#define LOADCELL5_STATUS_GAIN_1                                    0x04
#define LOADCELL5_STATUS_BITS_ID_0                                 0x08
#define LOADCELL5_STATUS_BITS_ID_1                                 0x10    
#define LOADCELL5_STATUS_ERROR                                     0x20
#define LOADCELL5_STATUS_FILTER_UPDATE_RATE_16_7_HZ                0x00
#define LOADCELL5_STATUS_FILTER_UPDATE_RATE_10_HZ                  0x40
#define LOADCELL5_STATUS_CONVERSION_NOT_AVAILABLE                  0x80
#define LOADCELL5_STATUS_CONVERSION_IS_AVAILABLE                   0x00
#define LOADCELL5_STATUS_CONVERSION_NOT_AVAILABLE                  0x80

/*! @} */ // status


/*! @} */ // loadcell5_cfg_data

/**
 * @defgroup loadcell5_map Load Cell 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Load Cell 5 Click driver.
 */

/**
 * @addtogroup loadcell5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Load Cell 5 Click to the selected MikroBUS.
 */
#define LOADCELL5_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.gn = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // loadcell5_map
/*! @} */ // loadcell5

/**
 * @brief Load Cell 5 Click context object.
 * @details Context object definition of Load Cell 5 Click driver.
 */
typedef struct
{
    // Output pins

     digital_out_t  rst;     /**< Power-down pin and a reset pin. */
     digital_out_t  gn;      /**< GAIN pin. */

    // Input pins

    digital_in_t  rdy;       /**< Data Ready pin. */

    // Modules

    spi_master_t  spi;       /**< SPI driver object. */

    pin_name_t  chip_select; /**< Chip select pin descriptor (used for SPI driver). */

} loadcell5_t;

/**
 * @brief Load Cell 5 Click configuration object.
 * @details Configuration object definition of Load Cell 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Filter Select pin. */

    // Additional gpio pins

    pin_name_t  rst;        /**< Power-down pin and a reset pin. */
    pin_name_t  gn;         /**< GAIN pin. */
    pin_name_t  rdy;        /**< Data Ready pin. */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} loadcell5_cfg_t;

/**
 * @brief Load Cell 5 Click data structure definition.
 * @details Data object definition of Load Cell 5 Click driver.
 */
typedef struct
{
    float tare;
    uint8_t tare_ok;
    float weight_coeff_100g;
    uint8_t weight_data_100g_ok;
    float weight_coeff_500g;
    uint8_t weight_data_500g_ok;
    float weight_coeff_1000g;
    uint8_t weight_data_1000g_ok;
    float weight_coeff_5000g;
    uint8_t weight_data_5000g_ok;
    float weight_coeff_10000g;
    uint8_t weight_data_10000g_ok;
}
loadcell5_data_t;

/**
 * @brief Load Cell 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LOADCELL5_OK = 0,
    LOADCELL5_ERROR = -1

} loadcell5_return_value_t;

/*!
 * @addtogroup loadcell5 Load Cell 5 Click Driver
 * @brief API for configuring and manipulating Load Cell 5 Click driver.
 * @{
 */

/**
 * @brief Load Cell 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #loadcell5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void loadcell5_cfg_setup ( loadcell5_cfg_t *cfg );

/**
 * @brief Load Cell 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #loadcell5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #loadcell5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell5_init ( loadcell5_t *ctx, loadcell5_cfg_t *cfg );

/**
 * @brief Load Cell 5 default configuration function.
 * @details This function executes a default configuration of Load Cell 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #loadcell5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t loadcell5_default_cfg ( loadcell5_t *ctx );

/**
 * @brief Load Cell 5 set power mode function.
 * @details This function performs power up or power down of the 
 * he AD7780 24-Bit, Pin-Programmable, Ultralow Power Sigma-Delta ADC
 * on Load Cell 5 Click board.
 * @param[in] ctx : Click context object.
 * See #loadcell5_t object definition for detailed explanation.
 * @param[in] pwr_mode : 
 *         @li @c 0x00 ( LOADCELL5_MODE_POWER_DOWN ) : Power OFF,
 *         @li @c 0x01 ( LOADCELL5_MODE_POWER_UP )   : Power ON.
 * @return @li @c    0 - Success,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell5_set_power_mode ( loadcell5_t *ctx, uint8_t pwr_mode );

/**
 * @brief Load Cell 5 set hardware reset function.
 * @details This function performs hardware reset of the 
 * he AD7780 24-Bit, Pin-Programmable, Ultralow Power Sigma-Delta ADC
 * on Load Cell 5 Click board.
 * @param[in] ctx : Click context object.
 * See #loadcell5_t object definition for detailed explanation.
 * @return Nothing.
 * @note Function delay is approximately 20 ms.
 */
void loadcell5_hw_reset ( loadcell5_t *ctx );

/**
 * @brief Load Cell 5 filter select function.
 * @details This function adjusts the selection for the filter of the 
 * he AD7780 24-Bit, Pin-Programmable, Ultralow Power Sigma-Delta ADC
 * on Load Cell 5 Click board.
 * @param[in] ctx : Click context object.
 * See #loadcell5_t object definition for detailed explanation.
 * @param[in] fil_sel : 
 *         @li @c 0x00 ( LOADCELL5_UPDATE_RATE_16_7_Hz ) : Fast settling filter, update rate is set to 16.7 Hz,
 *         @li @c 0x01 ( LOADCELL5_UPDATE_RATE_10_Hz )   : Update rate is set to 10 Hz.
 * @return @li @c    0 - Success,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell5_filter_select ( loadcell5_t *ctx, uint8_t fil_sel );

/**
 * @brief Load Cell 5 set gain function.
 * @details This function adjusts the selection for the gain of the 
 * he AD7780 24-Bit, Pin-Programmable, Ultralow Power Sigma-Delta ADC
 * on Load Cell 5 Click board.
 * @param[in] ctx : Click context object.
 * See #loadcell5_t object definition for detailed explanation.
 * @param[in] gain : 
 *         @li @c   1 ( LOADCELL5_GAIN_1 )   : The gain is set to 1,
 *         @li @c 128 ( LOADCELL5_GAIN_128 ) : The gain is set to 128.
 * @return @li @c   0 - Success,
 *         @li @c  -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell5_set_gain ( loadcell5_t *ctx, uint8_t gain );

/**
 * @brief Load Cell 5 data reading function.
 * @details This function reads a status and ADC data from
 * the AD7780 24-Bit, Pin-Programmable, Ultralow Power Sigma-Delta ADC
 * on Load Cell 5 Click board.
 * @param[in] ctx : Click context object.
 * See #loadcell5_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @param[out] adc_data : 24-bit ADC data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell5_get_data ( loadcell5_t *ctx, uint8_t *status, uint32_t *adc_data );

/**
 * @brief Load Cell 5 reading ADC data function.
 * @details This function reads the ADC data from
 * the AD7780 24-Bit, Pin-Programmable, Ultralow Power Sigma-Delta ADC
 * on Load Cell 5 Click board.
 * @param[in] ctx : Click context object.
 * See #loadcell5_t object definition for detailed explanation.
 * @return 24-bit ADC data.
 *
 * @note None.
 */
uint32_t loadcell5_read_adc ( loadcell5_t *ctx );

/**
 * @brief Load Cell 5 tare the scales function.
 * @details This function for the tare scales sets the tara value into the cell data structure of
 * the AD7780 24-Bit, Pin-Programmable, Ultralow Power Sigma-Delta ADC
 * on Load Cell 5 Click board.
 * @param[in] ctx : Click context object.
 * See #loadcell5_t object definition for detailed explanation.
 * @param[out] cell_data : Pointer to the memory location of the structure where data be stored.
 * @return Nothing.
 *
 * @note Function delay is approximately 1800 ms.
 */
void loadcell5_tare ( loadcell5_t *ctx, loadcell5_data_t *cell_data );

/**
 * @brief Load Cell 5 calibration function.
 * @details This function for the calibration sets the calibration value into the cell data structure of
 * the AD7780 24-Bit, Pin-Programmable, Ultralow Power Sigma-Delta ADC
 * on Load Cell 5 Click board.
 * @param[in] ctx : Click context object.
 * See #loadcell5_t object definition for detailed explanation.
 * @param[in] cal_val : Etalon weight value
 *         @li @c   100 ( LOADCELL4_WEIGHT_100G )   :   100g etalon,
 *         @li @c   500 ( LOADCELL4_WEIGHT_500G )   :   500g etalon,
 *         @li @c  1000 ( LOADCELL4_WEIGHT_1000G )  :  1000g etalon,
 *         @li @c  5000 ( LOADCELL4_WEIGHT_5000G )  :  5000g etalon,
 *         @li @c 10000 ( LOADCELL4_WEIGHT_10000G ) : 10000g etalon.
 * @param[out] cell_data : Pointer to the memory location of the structure where data be stored.
 * @return @li @c     0 - Success,
 *         @li @c    -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 *
 * @note Function delay is approximately 1800 ms.
 */
err_t loadcell5_calibration ( loadcell5_t *ctx, uint16_t cal_val, loadcell5_data_t *cell_data );

/**
 * @brief Load Cell 5 get weight function.
 * @details This function gets float value of the scales measurements [ g ] of
 * the AD7780 24-Bit, Pin-Programmable, Ultralow Power Sigma-Delta ADC
 * on Load Cell 5 Click board.
 * @param[in] ctx : Click context object.
 * See #loadcell5_t object definition for detailed explanation.
 * @param[out] cell_data : Pointer to the memory location of the structure where data be stored.
 * @return Float value of the scales measurements [ g ].
 *
 * @note Function delay is approximately 1800 ms.
 */
float loadcell5_get_weight ( loadcell5_t *ctx, loadcell5_data_t *cell_data );

/**
 * @brief Load Cell 5 get error function.
 * @details This function reads the state of the RDY ( INT ) pin of Load Cell 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #loadcell5_t object definition for detailed explanation.
 * @return @li @c 0 - INT pin state low,
 *         @li @c 1 - INT pin state high.
 *
 * @note None.
 */
uint8_t loadcell5_check_data_ready ( loadcell5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LOADCELL5_H

/*! @} */ // loadcell5

// ------------------------------------------------------------------------ END
