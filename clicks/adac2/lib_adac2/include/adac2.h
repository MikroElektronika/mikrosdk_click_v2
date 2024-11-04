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
 * @file adac2.h
 * @brief This file contains API for ADAC 2 Click Driver.
 */

#ifndef ADAC2_H
#define ADAC2_H

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
 * @addtogroup adac2 ADAC 2 Click Driver
 * @brief API for configuring and manipulating ADAC 2 Click driver.
 * @{
 */

/**
 * @defgroup adac2_reg ADAC 2 Registers List
 * @brief List of registers of ADAC 2 Click driver.
 */

/**
 * @addtogroup adac2_reg
 * @{
 */

/**
 * @brief ADAC 2 register map.
 * @details Specified register map of ADAC 2 Click driver.
 */
#define ADAC2_REG_GEN_PROD                  0x00
#define ADAC2_REG_GEN_REV                   0x01
#define ADAC2_REG_GEN_CNFG                  0x02
#define ADAC2_REG_GEN_CHNL_CTRL             0x03
#define ADAC2_REG_GEN_GPIO_CTRL             0x04
#define ADAC2_REG_GEN_GPI_INT               0x05
#define ADAC2_REG_GEN_GPI_DATA              0x06
#define ADAC2_REG_GEN_INT                   0x07
#define ADAC2_REG_GEN_INTEN                 0x08
#define ADAC2_REG_GEN_PWR_CTRL              0x09
#define ADAC2_REG_DCHNL_CMD                 0x20
#define ADAC2_REG_DCHNL_STA                 0x21
#define ADAC2_REG_DCHNL_CTRL1               0x22
#define ADAC2_REG_DCHNL_CTRL2               0x23
#define ADAC2_REG_DCHNL_DATA                0x24
#define ADAC2_REG_DCHNL_N_SEL               0x25
#define ADAC2_REG_DCHNL_N_SOC               0x26
#define ADAC2_REG_DCHNL_N_SGC               0x27
#define ADAC2_REG_AO_DATA_WR                0x40
#define ADAC2_REG_AO_OFFSET_CORR_WR         0x41
#define ADAC2_REG_AO_GAIN_CORR_WR           0x42
#define ADAC2_REG_AO_CNFG_WR                0x43
#define ADAC2_REG_AO_DATA_RD                0x44
#define ADAC2_REG_AO_OFFSET_CORR_RD         0x45
#define ADAC2_REG_AO_GAIN_CORR_RD           0x46
#define ADAC2_REG_AO_STA_RD                 0x47

/*! @} */ // adac2_reg

/**
 * @defgroup adac2_set ADAC 2 Registers Settings
 * @brief Settings for registers of ADAC 2 Click driver.
 */

/**
 * @addtogroup adac2_set
 * @{
 */

/**
 * @brief ADAC 2 description setting.
 * @details Specified setting for description of ADAC 2 Click driver.
 */
#define ADAC2_PRODUCT_ID                    0x2D

/**
 * @brief ADAC 2 GEN_CNFG register settings.
 * @details Specified GEN_CNFG register settings of ADAC 2 Click driver.
 */
#define ADAC2_GEN_CNFG_CRC_EN_DISABLE       0x000000ul
#define ADAC2_GEN_CNFG_CRC_EN_ENABLE        0x800000ul
#define ADAC2_GEN_CNFG_CRC_EN_MASK          0x800000ul
#define ADAC2_GEN_CNFG_DACREF_SEL_INT       0x000000ul
#define ADAC2_GEN_CNFG_DACREF_SEL_EXT       0x400000ul
#define ADAC2_GEN_CNFG_DACREF_SEL_MASK      0x400000ul
#define ADAC2_GEN_CNFG_ADCREF_SEL_INT       0x000000ul
#define ADAC2_GEN_CNFG_ADCREF_SEL_EXT       0x200000ul
#define ADAC2_GEN_CNFG_ADCREF_SEL_MASK      0x200000ul
#define ADAC2_GEN_CNFG_LINE_CNFG_OPEN       0x000000ul
#define ADAC2_GEN_CNFG_LINE_CNFG_CLOSED     0x100000ul
#define ADAC2_GEN_CNFG_LINE_CNFG_MASK       0x100000ul
#define ADAC2_GEN_CNFG_AO_CNFG_HIGH_Z       0x000000ul
#define ADAC2_GEN_CNFG_AO_CNFG_25V          0x010000ul
#define ADAC2_GEN_CNFG_AO_CNFG_12p5V        0x020000ul
#define ADAC2_GEN_CNFG_AO_CNFG_25mA         0x060000ul
#define ADAC2_GEN_CNFG_AO_CNFG_12p5mA       0x080000ul
#define ADAC2_GEN_CNFG_AO_CNFG_MASK         0x0F0000ul
#define ADAC2_GEN_CNFG_AI1_2_CNFG_BOTH_PD   0x000000ul
#define ADAC2_GEN_CNFG_AI1_2_CNFG_AI1_SE    0x002000ul
#define ADAC2_GEN_CNFG_AI1_2_CNFG_AI2_SE    0x004000ul
#define ADAC2_GEN_CNFG_AI1_2_CNFG_BOTH_SE   0x006000ul
#define ADAC2_GEN_CNFG_AI1_2_CNFG_DIFF      0x008000ul
#define ADAC2_GEN_CNFG_AI1_2_CNFG_MASK      0x00E000ul
#define ADAC2_GEN_CNFG_AI3_CNFG_PD          0x000000ul
#define ADAC2_GEN_CNFG_AI3_CNFG_SE          0x001000ul
#define ADAC2_GEN_CNFG_AI3_CNFG_MASK        0x001000ul
#define ADAC2_GEN_CNFG_AI4_CNFG_PD          0x000000ul
#define ADAC2_GEN_CNFG_AI4_CNFG_SE          0x000800ul
#define ADAC2_GEN_CNFG_AI4_CNFG_MASK        0x000800ul
#define ADAC2_GEN_CNFG_AI5_6_CNFG_PD        0x000000ul
#define ADAC2_GEN_CNFG_AI5_6_CNFG_DIFF      0x000400ul
#define ADAC2_GEN_CNFG_AI5_6_CNFG_MASK      0x000700ul
#define ADAC2_GEN_CNFG_AI5_DF_GAIN_12p5V    0x000000ul
#define ADAC2_GEN_CNFG_AI5_DF_GAIN_0p5V     0x000040ul
#define ADAC2_GEN_CNFG_AI5_DF_GAIN_0p25V    0x000080ul
#define ADAC2_GEN_CNFG_AI5_DF_GAIN_0p125V   0x0000C0ul
#define ADAC2_GEN_CNFG_AI5_DF_GAIN_MASK     0x0000C0ul
#define ADAC2_GEN_CNFG_OVC_CTRL_AUTO        0x000000ul
#define ADAC2_GEN_CNFG_OVC_CTRL_HOST        0x000008ul
#define ADAC2_GEN_CNFG_OVC_CTRL_MASK        0x000008ul

/**
 * @brief ADAC 2 voltage calculation values.
 * @details Specified voltage calculation values of ADAC 2 Click driver.
 */
#define ADAC2_ADC_DATA_RESOLUTION           0x7FFFFFul
#define ADAC2_DAC_DATA_RESOLUTION           0x03FFFFul
#define ADAC2_DAC_MIN_VALUE                 -131072l
#define ADAC2_DAC_MAX_VALUE                 131071l
#define ADAC2_FULL_SCALE_RANGE_25V          25.0f
#define ADAC2_FULL_SCALE_RANGE_12p5V        12.5f
#define ADAC2_FULL_SCALE_RANGE_2p5V         2.5f
#define ADAC2_FULL_SCALE_RANGE_0p5V         0.5f
#define ADAC2_FULL_SCALE_RANGE_0p25V        0.25f
#define ADAC2_FULL_SCALE_RANGE_0p125V       0.125f

/**
 * @brief ADAC 2 DCHNL_CMD register settings.
 * @details Specified DCHNL_CMD register settings of ADAC 2 Click driver.
 */
#define ADAC2_START_CONVERSION              0x30
#define ADAC2_STOP_CONVERSION               0x10
#define ADAC2_DATA_RATE_5_SPS               0x00
#define ADAC2_DATA_RATE_10_SPS              0x01
#define ADAC2_DATA_RATE_15_SPS              0x02
#define ADAC2_DATA_RATE_30_SPS              0x03
#define ADAC2_DATA_RATE_50_SPS              0x04
#define ADAC2_DATA_RATE_60_SPS              0x05
#define ADAC2_DATA_RATE_225_SPS             0x06
#define ADAC2_DATA_RATE_450_SPS             0x07
#define ADAC2_DATA_RATE_900_SPS             0x08
#define ADAC2_DATA_RATE_1800_SPS            0x09
#define ADAC2_DATA_RATE_3600_SPS            0x0A
#define ADAC2_DATA_RATE_7200_SPS            0x0B
#define ADAC2_DATA_RATE_14400_SPS           0x0C
#define ADAC2_DATA_RATE_28800_SPS           0x0D
#define ADAC2_DATA_RATE_57600_SPS           0x0E
#define ADAC2_DATA_RATE_115200_SPS          0x0F

/**
 * @brief ADAC 2 DCHNL_CTRL1 register settings.
 * @details Specified DCHNL_CTRL1 register settings of ADAC 2 Click driver.
 */
#define ADAC2_PD_STATE_STANDBY              0x00
#define ADAC2_PD_STATE_RESET                0x10
#define ADAC2_CONV_MODE_CONTINUOUS          0x00
#define ADAC2_CONV_MODE_SINGLE_CYCLE        0x02
#define ADAC2_CONV_MODE_CONT_SINGLE_CYCLE   0x03

/**
 * @brief ADAC 2 channel selection values.
 * @details Specified channel selection values of ADAC 2 Click driver.
 */
#define ADAC2_CH_NONE                       0x00
#define ADAC2_CH_AI1_SINGLE_ENDED           0x01
#define ADAC2_CH_AI2_SINGLE_ENDED           0x02
#define ADAC2_CH_AI1_AI2_DIFFERENTIAL       0x03
#define ADAC2_CH_AI3_SINGLE_ENDED           0x04
#define ADAC2_CH_AI4_SINGLE_ENDED           0x05
#define ADAC2_CH_AI3_AI4_DIFFERENTIAL       0x06
#define ADAC2_CH_AI5_AI6_DIFFERENTIAL_25V   0x09
#define ADAC2_CH_AI5_AI6_DIFFERENTIAL_2p5V  0x0C
#define ADAC2_CH_AUX1_SINGLE_ENDED          0x0D
#define ADAC2_CH_AUX2_SINGLE_ENDED          0x0E
#define ADAC2_CH_AUX1_AUX2_DIFFERENTIAL     0x0F
#define ADAC2_CH_MASK                       0x000F00ul

/**
 * @brief ADAC 2 gpio selection values.
 * @details Specified gpio selection values of ADAC 2 Click driver.
 */
#define ADAC2_GPIO_0_MASK                   0x01
#define ADAC2_GPIO_1_MASK                   0x02
#define ADAC2_GPIO_2_MASK                   0x04
#define ADAC2_GPIO_3_MASK                   0x08
#define ADAC2_GPIO_4_MASK                   0x10
#define ADAC2_GPIO_5_MASK                   0x20
#define ADAC2_GPIO_ALL_MASK                 0x3F

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adac2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADAC2_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define ADAC2_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adac2_set

/**
 * @defgroup adac2_map ADAC 2 MikroBUS Map
 * @brief MikroBUS pin mapping of ADAC 2 Click driver.
 */

/**
 * @addtogroup adac2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADAC 2 Click to the selected MikroBUS.
 */
#define ADAC2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adac2_map
/*! @} */ // adac2

/**
 * @brief ADAC 2 Click context object.
 * @details Context object definition of ADAC 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (Active low). */

    // Input pins
    digital_in_t rdy;           /**< Data ready pin (Active low). */
    digital_in_t int_pin;       /**< Interrupt pin (Active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */
    
    bool spi_crc_enable;        /**< SPI CRC enable flag */

} adac2_t;

/**
 * @brief ADAC 2 Click configuration object.
 * @details Configuration object definition of ADAC 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rdy;             /**< Data ready pin (Active low). */
    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t int_pin;         /**< Interrupt pin (Active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} adac2_cfg_t;

/**
 * @brief ADAC 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADAC2_OK = 0,
    ADAC2_ERROR = -1

} adac2_return_value_t;

/*!
 * @addtogroup adac2 ADAC 2 Click Driver
 * @brief API for configuring and manipulating ADAC 2 Click driver.
 * @{
 */

/**
 * @brief ADAC 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adac2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adac2_cfg_setup ( adac2_cfg_t *cfg );

/**
 * @brief ADAC 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adac2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adac2_init ( adac2_t *ctx, adac2_cfg_t *cfg );

/**
 * @brief ADAC 2 default configuration function.
 * @details This function executes a default configuration of ADAC 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adac2_default_cfg ( adac2_t *ctx );

/**
 * @brief ADAC 2 write register function.
 * @details This function writes a 24-bit data to the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 24-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adac2_write_register ( adac2_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief ADAC 2 read register function.
 * @details This function reads a 24-bit data from the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : 24-bit data output read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adac2_read_register ( adac2_t *ctx, uint8_t reg, uint32_t *data_out );

/** 
 * @brief ADAC 2 enable spi crc function.
 * @details This function enables SPI CRC. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac2_enable_spi_crc ( adac2_t *ctx );

/** 
 * @brief ADAC 2 disable spi crc function.
 * @details This function disables SPI CRC. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac2_disable_spi_crc ( adac2_t *ctx );

/** 
 * @brief ADAC 2 check communication function.
 * @details This function checks the communication by reading and verifying the product ID. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac2_check_communication ( adac2_t *ctx );

/** 
 * @brief ADAC 2 reset device function.
 * @details This function resets the device by toggling the RST pin. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void adac2_reset_device ( adac2_t *ctx );

/** 
 * @brief ADAC 2 get rdy pin function.
 * @details This function returns the RDY pin logic state. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t adac2_get_rdy_pin ( adac2_t *ctx );

/** 
 * @brief ADAC 2 get int pin function.
 * @details This function returns the INT pin logic state. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t adac2_get_int_pin ( adac2_t *ctx );

/** 
 * @brief ADAC 2 start conversion function.
 * @details This function starts the conversion with the selected data rate. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @param[in] data_rate : Data rate [0x00-0x0F].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac2_start_conversion ( adac2_t *ctx, uint8_t data_rate );

/** 
 * @brief ADAC 2 stop conversion function.
 * @details This function stops the conversion. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac2_stop_conversion ( adac2_t *ctx );

/** 
 * @brief ADAC 2 set conversion mode function.
 * @details This function sets the conversion mode by writing to the DCHNL_CTRL1 register. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @param[in] mode : Conversion mode.
 *                  @li @c 0 - Continuous,
 *                  @li @c 2 - Single-Cycle,
 *                  @li @c 3 - Continuous - Single-Cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac2_set_conversion_mode ( adac2_t *ctx, uint8_t mode );

/** 
 * @brief ADAC 2 set active ain channel function.
 * @details This function sets the active analog input channel. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @param[in] channel : Channel selection byte [0x00-0x19].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac2_set_active_ain_channel ( adac2_t *ctx, uint8_t channel );

/** 
 * @brief ADAC 2 read raw adc function.
 * @details This function reads RAW ADC value of previous conversion. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @param[out] raw_adc : 24-bit RAW ADC value (signed).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac2_read_raw_adc ( adac2_t *ctx, int32_t *raw_adc );

/** 
 * @brief ADAC 2 read voltage function.
 * @details This function reads RAW ADC value of previous conversion and converts it to voltage. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @param[in] fsr : Full scale range for analog input.
 * @param[out] voltage : Voltage in @b fsr range.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac2_read_voltage ( adac2_t *ctx, float fsr, float *voltage );

/** 
 * @brief ADAC 2 write dac function.
 * @details This function sets the analog output by writing to the AO_DATA_WR register. 
 * @param[in] ctx : Click context object.
 * See #adac2_t object definition for detailed explanation.
 * @param[in] dac : DAC raw data [-131072, +131071].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t adac2_write_dac ( adac2_t *ctx, int32_t dac );

#ifdef __cplusplus
}
#endif
#endif // ADAC2_H

/*! @} */ // adac2

// ------------------------------------------------------------------------ END
