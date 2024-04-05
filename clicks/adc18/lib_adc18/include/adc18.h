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
 * @file adc18.h
 * @brief This file contains API for ADC 18 Click Driver.
 */

#ifndef ADC18_H
#define ADC18_H

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
#include "spi_specifics.h"

/*!
 * @addtogroup adc18 ADC 18 Click Driver
 * @brief API for configuring and manipulating ADC 18 Click driver.
 * @{
 */

/**
 * @defgroup adc18_reg ADC 18 Registers List
 * @brief List of registers of ADC 18 Click driver.
 */

/**
 * @addtogroup adc18_reg
 * @{
 */

/**
 * @brief ADC 18 register map.
 * @details Specified register map of ADC 18 Click driver.
 */
#define ADC18_REG_GEN_PROD                  0x00
#define ADC18_REG_GEN_REV                   0x01
#define ADC18_REG_GEN_CNFG                  0x02
#define ADC18_REG_GEN_CHNL_CTRL             0x03
#define ADC18_REG_GEN_GPIO_CTRL             0x04
#define ADC18_REG_GEN_GPI_INT               0x05
#define ADC18_REG_GEN_GPI_DATA              0x06
#define ADC18_REG_GEN_INT                   0x07
#define ADC18_REG_GEN_INTEN                 0x08
#define ADC18_REG_GEN_PWR_CTRL              0x09
#define ADC18_REG_DCHNL_CMD                 0x20
#define ADC18_REG_DCHNL_STA                 0x21
#define ADC18_REG_DCHNL_CTRL1               0x22
#define ADC18_REG_DCHNL_CTRL2               0x23
#define ADC18_REG_DCHNL_DATA                0x24
#define ADC18_REG_DCHNL_N_SEL               0x25
#define ADC18_REG_DCHNL_N_SOC               0x26
#define ADC18_REG_DCHNL_N_SGC               0x27

/*! @} */ // adc18_reg

/**
 * @defgroup adc18_set ADC 18 Registers Settings
 * @brief Settings for registers of ADC 18 Click driver.
 */

/**
 * @addtogroup adc18_set
 * @{
 */

/**
 * @brief ADC 18 description setting.
 * @details Specified setting for description of ADC 18 Click driver.
 */
#define ADC18_PRODUCT_ID                    0x18

/**
 * @brief ADC 18 SPI CRC enable values.
 * @details Specified values for SPI CRC enable of ADC 18 Click driver.
 */
#define ADC18_GEN_CNFG_CRC_EN               0x800000ul

/**
 * @brief ADC 18 voltage calculation values.
 * @details Specified voltage calculation values of ADC 18 Click driver.
 */
#define ADC18_DATA_RESOLUTION               0x7FFFFFul
#define ADC18_FULL_SCALE_VOLTAGE            12.5

/**
 * @brief ADC 18 DCHNL_CMD register settings.
 * @details Specified DCHNL_CMD register settings of ADC 18 Click driver.
 */
#define ADC18_START_CONVERSION              0x30
#define ADC18_STOP_CONVERSION               0x10
#define ADC18_DATA_RATE_5_SPS               0x00
#define ADC18_DATA_RATE_10_SPS              0x01
#define ADC18_DATA_RATE_15_SPS              0x02
#define ADC18_DATA_RATE_30_SPS              0x03
#define ADC18_DATA_RATE_50_SPS              0x04
#define ADC18_DATA_RATE_60_SPS              0x05
#define ADC18_DATA_RATE_225_SPS             0x06
#define ADC18_DATA_RATE_450_SPS             0x07
#define ADC18_DATA_RATE_900_SPS             0x08
#define ADC18_DATA_RATE_1800_SPS            0x09
#define ADC18_DATA_RATE_3600_SPS            0x0A
#define ADC18_DATA_RATE_7200_SPS            0x0B
#define ADC18_DATA_RATE_14400_SPS           0x0C
#define ADC18_DATA_RATE_28800_SPS           0x0D
#define ADC18_DATA_RATE_57600_SPS           0x0E
#define ADC18_DATA_RATE_115200_SPS          0x0F

/**
 * @brief ADC 18 DCHNL_CTRL1 register settings.
 * @details Specified DCHNL_CTRL1 register settings of ADC 18 Click driver.
 */
#define ADC18_PD_STATE_STANDBY              0x00
#define ADC18_PD_STATE_RESET                0x10
#define ADC18_CONV_MODE_CONTINUOUS          0x00
#define ADC18_CONV_MODE_SINGLE_CYCLE        0x02
#define ADC18_CONV_MODE_CONT_SINGLE_CYCLE   0x03

/**
 * @brief ADC 18 channel selection values.
 * @details Specified channel selection values of ADC 18 Click driver.
 */
#define ADC18_CH_AI1_SINGLE_ENDED           0x00
#define ADC18_CH_AI2_SINGLE_ENDED           0x01
#define ADC18_CH_AI3_SINGLE_ENDED           0x02
#define ADC18_CH_AI4_SINGLE_ENDED           0x03
#define ADC18_CH_AI5_SINGLE_ENDED           0x04
#define ADC18_CH_AI6_SINGLE_ENDED           0x05
#define ADC18_CH_AI7_SINGLE_ENDED           0x06
#define ADC18_CH_AI8_SINGLE_ENDED           0x07
#define ADC18_CH_AI9_SINGLE_ENDED           0x08
#define ADC18_CH_AI10_SINGLE_ENDED          0x09
#define ADC18_CH_AI11_SINGLE_ENDED          0x0A
#define ADC18_CH_AI12_SINGLE_ENDED          0x0B
#define ADC18_CH_AI1_AI2_DIFFERENTIAL       0x0C
#define ADC18_CH_AI3_AI4_DIFFERENTIAL       0x0D
#define ADC18_CH_AI5_AI6_DIFFERENTIAL       0x0E
#define ADC18_CH_AI7_AI8_DIFFERENTIAL       0x0F
#define ADC18_CH_AI9_AI10_DIFFERENTIAL      0x10
#define ADC18_CH_AI11_AI12_DIFFERENTIAL     0x11
#define ADC18_CH_AI1_COM_AI2_MULTI_DIFF     0x12
#define ADC18_CH_AI1_COM_AI3_MULTI_DIFF     0x13
#define ADC18_CH_AI4_COM_AI5_MULTI_DIFF     0x14
#define ADC18_CH_AI4_COM_AI6_MULTI_DIFF     0x15
#define ADC18_CH_AI7_COM_AI8_MULTI_DIFF     0x16
#define ADC18_CH_AI7_COM_AI9_MULTI_DIFF     0x17
#define ADC18_CH_AI10_COM_AI11_MULTI_DIFF   0x18
#define ADC18_CH_AI10_COM_AI12_MULTI_DIFF   0x19
#define ADC18_AIP_TEST_DISABLED             0x00
#define ADC18_AIP_TEST_2MOHM_TO_AGND        0x40
#define ADC18_AIP_TEST_2MOHM_TO_HVDD        0x80
#define ADC18_AIP_TEST_2MOHM_TO_HVDD_AGND   0xC0
#define ADC18_AIN_TEST_DISABLED             0x00
#define ADC18_AIN_TEST_2MOHM_TO_AGND        0x10
#define ADC18_AIN_TEST_2MOHM_TO_HVDD        0x20
#define ADC18_AIN_TEST_2MOHM_TO_HVDD_AGND   0x30

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adc18_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC18_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define ADC18_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc18_set

/**
 * @defgroup adc18_map ADC 18 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 18 Click driver.
 */

/**
 * @addtogroup adc18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 18 Click to the selected MikroBUS.
 */
#define ADC18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adc18_map
/*! @} */ // adc18

/**
 * @brief ADC 18 Click context object.
 * @details Context object definition of ADC 18 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Active-Low reset pin. */

    // Input pins
    digital_in_t  rdy;          /**< Active-Low data ready pin. */
    digital_in_t  int_pin;      /**< Active-Low interrupt pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    bool spi_crc_enable;        /**< SPI CRC enable flag */

} adc18_t;

/**
 * @brief ADC 18 Click configuration object.
 * @details Configuration object definition of ADC 18 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;            /**< Active-Low reset pin. */
    pin_name_t  rdy;            /**< Active-Low data ready pin. */
    pin_name_t  int_pin;        /**< Active-Low interrupt pin. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} adc18_cfg_t;

/**
 * @brief ADC 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC18_OK = 0,
    ADC18_ERROR = -1

} adc18_return_value_t;

/*!
 * @addtogroup adc18 ADC 18 Click Driver
 * @brief API for configuring and manipulating ADC 18 Click driver.
 * @{
 */

/**
 * @brief ADC 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc18_cfg_setup ( adc18_cfg_t *cfg );

/**
 * @brief ADC 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc18_init ( adc18_t *ctx, adc18_cfg_t *cfg );

/**
 * @brief ADC 18 default configuration function.
 * @details This function executes a default configuration of ADC 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adc18_default_cfg ( adc18_t *ctx );

/**
 * @brief ADC 18 write register function.
 * @details This function writes a 24-bit data to the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 24-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc18_write_register ( adc18_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief ADC 18 read register function.
 * @details This function reads a 24-bit data from the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : 24-bit data output read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc18_read_register ( adc18_t *ctx, uint8_t reg, uint32_t *data_out );

/** 
 * @brief ADC 18 enable spi crc function.
 * @details This function enables SPI CRC. 
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adc18_enable_spi_crc ( adc18_t *ctx );

/** 
 * @brief ADC 18 disable spi crc function.
 * @details This function disables SPI CRC. 
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adc18_disable_spi_crc ( adc18_t *ctx );

/** 
 * @brief ADC 18 check communication function.
 * @details This function checks the communication by reading and verifying the product ID. 
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adc18_check_communication ( adc18_t *ctx );

/** 
 * @brief ADC 18 reset device function.
 * @details This function resets the device by toggling the RST pin. 
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void adc18_reset_device ( adc18_t *ctx );

/** 
 * @brief ADC 18 get rdy pin function.
 * @details This function returns the RDY pin logic state. 
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t adc18_get_rdy_pin ( adc18_t *ctx );

/** 
 * @brief ADC 18 get int pin function.
 * @details This function returns the INT pin logic state. 
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t adc18_get_int_pin ( adc18_t *ctx );

/** 
 * @brief ADC 18 start conversion function.
 * @details This function starts the conversion with the selected data rate. 
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @param[in] data_rate : Data rate [0x00-0x0F].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adc18_start_conversion ( adc18_t *ctx, uint8_t data_rate );

/** 
 * @brief ADC 18 stop conversion function.
 * @details This function stops the conversion. 
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adc18_stop_conversion ( adc18_t *ctx );

/** 
 * @brief ADC 18 set conversion mode function.
 * @details This function sets the conversion mode by writing to the DCHNL_CTRL1 register. 
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @param[in] mode : Conversion mode.
 *                  @li @c 0 - Continuous,
 *                  @li @c 2 - Single-Cycle,
 *                  @li @c 3 - Continuous - Single-Cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adc18_set_conversion_mode ( adc18_t *ctx, uint8_t mode );

/** 
 * @brief ADC 18 set active channel function.
 * @details This function sets the active channel. 
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @param[in] channel : Channel selection byte [0x00-0x19].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adc18_set_active_channel ( adc18_t *ctx, uint8_t channel );

/** 
 * @brief ADC 18 read raw adc function.
 * @details This function reads RAW ADC value of previous conversion. 
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @param[out] raw_adc : 24-bit RAW ADC value (signed).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adc18_read_raw_adc ( adc18_t *ctx, int32_t *raw_adc );

/** 
 * @brief ADC 18 read voltage function.
 * @details This function reads RAW ADC value of previous conversion and converts it to voltage. 
 * @param[in] ctx : Click context object.
 * See #adc18_t object definition for detailed explanation.
 * @param[out] voltage : Voltage in range -12.5V to +12.5V.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adc18_read_voltage ( adc18_t *ctx, float *voltage );

#ifdef __cplusplus
}
#endif
#endif // ADC18_H

/*! @} */ // adc18

// ------------------------------------------------------------------------ END
