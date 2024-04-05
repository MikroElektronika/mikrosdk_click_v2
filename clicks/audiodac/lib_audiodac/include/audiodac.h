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
 * @file audiodac.h
 * @brief This file contains API for Audio DAC Click Driver.
 */

#ifndef AUDIODAC_H
#define AUDIODAC_H

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
 * @addtogroup audiodac Audio DAC Click Driver
 * @brief API for configuring and manipulating Audio DAC Click driver.
 * @{
 */

/**
 * @defgroup audiodac_reg Audio DAC Registers List
 * @brief List of registers of Audio DAC Click driver.
 */

/**
 * @addtogroup audiodac_reg
 * @{
 */

/**
 * @brief Audio DAC register list.
 * @details Specified register list of Audio DAC Click driver.
 */
#define AUDIODAC_REG_P0_PAGE_SEL            0x00
#define AUDIODAC_REG_P0_ANALOG_CTRL         0x01
#define AUDIODAC_REG_P0_STBY_PDOWN          0x02
#define AUDIODAC_REG_P0_MUTE                0x03
#define AUDIODAC_REG_P0_PLL_LOCK_PLL_EN     0x04
#define AUDIODAC_REG_P0_SPI_MISO_SEL        0x06
#define AUDIODAC_REG_P0_DEEMP_EN_SDOUT_SEL  0x07
#define AUDIODAC_REG_P0_GPIO_EN             0x08
#define AUDIODAC_REG_P0_BCK_LRCLK           0x09
#define AUDIODAC_REG_P0_DSP_GPIO_IN         0x0A
#define AUDIODAC_REG_P0_M_BCK_LRCLK_RST     0x0C
#define AUDIODAC_REG_P0_SREF                0x0D
#define AUDIODAC_REG_P0_SDAC_CLK_SRC        0x0E
#define AUDIODAC_REG_P0_GREF                0x12
#define AUDIODAC_REG_P0_SYNC_REQ            0x13
#define AUDIODAC_REG_P0_PLL_DIV_P           0x14
#define AUDIODAC_REG_P0_PLL_DIV_J           0x15
#define AUDIODAC_REG_P0_PLL_DIV_D_MSB       0x16
#define AUDIODAC_REG_P0_PLL_DIV_D_LSB       0x17
#define AUDIODAC_REG_P0_PLL_DIV_R           0x18
#define AUDIODAC_REG_P0_DSP_CLK_DIV         0x1B
#define AUDIODAC_REG_P0_DAC_CLK_DIV         0x1C
#define AUDIODAC_REG_P0_NCP_CLK_DIV         0x1D
#define AUDIODAC_REG_P0_OSR_CLK_DIV         0x1E
#define AUDIODAC_REG_P0_M_MODE_BCK_DIV      0x20
#define AUDIODAC_REG_P0_M_MODE_LRCK_DIV     0x21
#define AUDIODAC_REG_P0_FS_SPEED_MODE       0x22
#define AUDIODAC_REG_P0_IDAC_MSB            0x23
#define AUDIODAC_REG_P0_IDAC_LSB            0x24
#define AUDIODAC_REG_P0_IGNORE_ERRS         0x25
#define AUDIODAC_REG_P0_I2S_DATA_FORMAT     0x28
#define AUDIODAC_REG_P0_I2S_SHIFT           0x29
#define AUDIODAC_REG_P0_DAC_DATA_PATH       0x2A
#define AUDIODAC_REG_P0_DSP_PROGRAM_SEL     0x2B
#define AUDIODAC_REG_P0_CLK_MISS_DET_PER    0x2C
#define AUDIODAC_REG_P0_AUTO_MUTE_TIME      0x3B
#define AUDIODAC_REG_P0_DIG_VOLUME_CTRL     0x3C
#define AUDIODAC_REG_P0_DIG_VOLUME_LEFT     0x3D
#define AUDIODAC_REG_P0_DIG_VOLUME_RIGHT    0x3E
#define AUDIODAC_REG_P0_DIG_VOLUME_N_RU_RD  0x3F
#define AUDIODAC_REG_P0_DIG_VOLUME_E_RU_RD  0x40
#define AUDIODAC_REG_P0_AUTO_MUTE           0x41
#define AUDIODAC_REG_P0_GPIO1_OUT_SEL       0x50
#define AUDIODAC_REG_P0_GPIO2_OUT_SEL       0x51
#define AUDIODAC_REG_P0_GPIO3_OUT_SEL       0x52
#define AUDIODAC_REG_P0_GPIO4_OUT_SEL       0x53
#define AUDIODAC_REG_P0_GPIO5_OUT_SEL       0x54
#define AUDIODAC_REG_P0_GPIO6_OUT_SEL       0x55
#define AUDIODAC_REG_P0_GPIO_CTRL           0x56
#define AUDIODAC_REG_P0_GPIO_INV            0x57
#define AUDIODAC_REG_P0_DSP_OVERFLOW        0x5A
#define AUDIODAC_REG_P0_STAT_FS_SCK         0x5B
#define AUDIODAC_REG_P0_STAT_BCK_MSB        0x5C
#define AUDIODAC_REG_P0_STAT_BCK_LSB        0x5D
#define AUDIODAC_REG_P0_STAT_1              0x5E
#define AUDIODAC_REG_P0_STAT_2              0x5F
#define AUDIODAC_REG_P0_MON_ANALOG_MUTE     0x6C
#define AUDIODAC_REG_P0_MON_SHORT_DET       0x6D
#define AUDIODAC_REG_P0_MON_MUTE            0x72
#define AUDIODAC_REG_P0_MON_FS_SPEED_MODE   0x73
#define AUDIODAC_REG_P0_MON_POWER_STATE     0x76
#define AUDIODAC_REG_P0_GPIO_IN             0x77
#define AUDIODAC_REG_P0_AUTO_MUTE_FLAGS     0x78
#define AUDIODAC_REG_P0_DAC_MODE            0x79
#define AUDIODAC_REG_P0_EXT_INTP_FILT       0x7A
#define AUDIODAC_REG_P0_GP12_EXT_INTP_FILT  0x7B
#define AUDIODAC_REG_P0_GP34_EXT_INTP_FILT  0x7C
#define AUDIODAC_REG_P0_GP56_EXT_INTP_FILT  0x7D
#define AUDIODAC_REG_P1_OUT_AMP_TYPE        0x01
#define AUDIODAC_REG_P1_ANALOG_GAIN_CTRL    0x02
#define AUDIODAC_REG_P1_UV_PROTECT          0x05
#define AUDIODAC_REG_P1_ANALOG_MUTE_CTRL    0x06
#define AUDIODAC_REG_P1_ANALOG_GAIN_BOOST   0x07
#define AUDIODAC_REG_P1_VCOM_REF            0x08
#define AUDIODAC_REG_P1_VCOM_PD_CTRL        0x09
#define AUDIODAC_REG_P44_COEF_MEM_CTRL      0x01
#define AUDIODAC_REG_P44_P52_COEF_BUF_A     0x2C
#define AUDIODAC_REG_P62_P70_COEF_BUF_B     0x3E
#define AUDIODAC_REG_P152_P186_INS_BUF      0x98
#define AUDIODAC_REG_P253_CLK_FLEX_1_MODE   0x3F
#define AUDIODAC_REG_P253_CLK_FLEX_2_MODE   0x40

/*! @} */ // audiodac_reg

/**
 * @defgroup audiodac_set Audio DAC Registers Settings
 * @brief Settings for registers of Audio DAC Click driver.
 */

/**
 * @addtogroup audiodac_set
 * @{
 */

/**
 * @brief Audio DAC auto increment register settings.
 * @details Specified setting for auto increment register of Audio DAC Click driver.
 */
#define AUDIODAC_AUTO_INCREMENT_ENABLE      0x80

/**
 * @brief Audio DAC register page settings.
 * @details Specified setting for register page of Audio DAC Click driver.
 */
#define AUDIODAC_PAGE_0                     0
#define AUDIODAC_PAGE_1                     1
#define AUDIODAC_PAGE_44                    44
#define AUDIODAC_PAGE_62                    62
#define AUDIODAC_PAGE_152                   152
#define AUDIODAC_PAGE_253                   253

/**
 * @brief Audio DAC gpio en settings.
 * @details Specified setting for gpio en of Audio DAC Click driver.
 */
#define AUDIODAC_GPIO6_OUT_EN               0x20
#define AUDIODAC_GPIO5_OUT_EN               0x10
#define AUDIODAC_GPIO4_OUT_EN               0x08
#define AUDIODAC_GPIO3_OUT_EN               0x04
#define AUDIODAC_GPIO2_OUT_EN               0x02
#define AUDIODAC_GPIO1_OUT_EN               0x01

/**
 * @brief Audio DAC gpio out sel settings.
 * @details Specified setting for gpio out sel of Audio DAC Click driver.
 */
#define AUDIODAC_GPIO_OUT_SEL_OFF           0x00
#define AUDIODAC_GPIO_OUT_SEL_DSP           0x01
#define AUDIODAC_GPIO_OUT_SEL_REG_GPIO_OUT  0x02
#define AUDIODAC_GPIO_OUT_SEL_AUTO_MUTE_LR  0x03
#define AUDIODAC_GPIO_OUT_SEL_AUTO_MUTE_L   0x04
#define AUDIODAC_GPIO_OUT_SEL_AUTO_MUTE_R   0x05
#define AUDIODAC_GPIO_OUT_SEL_CLOCK_INVALID 0x06
#define AUDIODAC_GPIO_OUT_SEL_SDOUT         0x07
#define AUDIODAC_GPIO_OUT_SEL_AN_MUTE_L     0x08
#define AUDIODAC_GPIO_OUT_SEL_AN_MUTE_R     0x09
#define AUDIODAC_GPIO_OUT_SEL_PLL_LOCK      0x0A
#define AUDIODAC_GPIO_OUT_SEL_UV_0_7_DVDD   0x0E
#define AUDIODAC_GPIO_OUT_SEL_UV_0_3_DVDD   0x0F
#define AUDIODAC_GPIO_OUT_SEL_PLL_OUT_DIV_4 0x10

/**
 * @brief Audio DAC digital volume register settings.
 * @details Specified setting for digital volume register of Audio DAC Click driver.
 */
#define AUDIODAC_DIG_VOLUME_POS_MAX         0x00
#define AUDIODAC_DIG_VOLUME_NO_ATT          0x30
#define AUDIODAC_DIG_VOLUME_NEG_MIN         0xFE
#define AUDIODAC_DIG_VOLUME_MUTE            0xFF

/**
 * @brief Audio DAC volume control settings.
 * @details Specified setting for volume control of Audio DAC Click driver.
 */
#define AUDIODAC_VOLUME_MAX                 100
#define AUDIODAC_VOLUME_DEFAULT             48
#define AUDIODAC_VOLUME_MIN                 1
#define AUDIODAC_VOLUME_MUTE                0

/**
 * @brief Audio DAC output channel selection.
 * @details Specified selection for output channel of Audio DAC Click driver.
 */
#define AUDIODAC_CHANNEL_BOTH               0
#define AUDIODAC_CHANNEL_LEFT               1
#define AUDIODAC_CHANNEL_RIGHT              2

/**
 * @brief Audio DAC device address setting.
 * @details Specified setting for device slave address selection of
 * Audio DAC Click driver.
 */
#define AUDIODAC_DEVICE_ADDRESS             0x4C

/*! @} */ // audiodac_set

/**
 * @defgroup audiodac_map Audio DAC MikroBUS Map
 * @brief MikroBUS pin mapping of Audio DAC Click driver.
 */

/**
 * @addtogroup audiodac_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Audio DAC Click to the selected MikroBUS.
 */
#define AUDIODAC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.mute = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gpio4 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // audiodac_map
/*! @} */ // audiodac

/**
 * @brief Audio DAC Click context object.
 * @details Context object definition of Audio DAC Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t mute;         /**< Soft mute control pin (Active low). */

    // Input pins
    digital_in_t gpio4;         /**< GPIO4 pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} audiodac_t;

/**
 * @brief Audio DAC Click configuration object.
 * @details Configuration object definition of Audio DAC Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t mute;            /**< Soft mute control pin (Active low). */
    pin_name_t gpio4;           /**< GPIO4 pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} audiodac_cfg_t;

/**
 * @brief Audio DAC Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AUDIODAC_OK = 0,
    AUDIODAC_ERROR = -1

} audiodac_return_value_t;

/*!
 * @addtogroup audiodac Audio DAC Click Driver
 * @brief API for configuring and manipulating Audio DAC Click driver.
 * @{
 */

/**
 * @brief Audio DAC configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #audiodac_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void audiodac_cfg_setup ( audiodac_cfg_t *cfg );

/**
 * @brief Audio DAC initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #audiodac_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #audiodac_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audiodac_init ( audiodac_t *ctx, audiodac_cfg_t *cfg );

/**
 * @brief Audio DAC default configuration function.
 * @details This function executes a default configuration of Audio DAC
 * click board.
 * @param[in] ctx : Click context object.
 * See #audiodac_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t audiodac_default_cfg ( audiodac_t *ctx );

/**
 * @brief Audio DAC I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #audiodac_t object definition for detailed explanation.
 * @param[in] reg : Start register address, for address auto increment OR it with AUDIODAC_AUTO_INCREMENT_ENABLE.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audiodac_generic_write ( audiodac_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Audio DAC I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #audiodac_t object definition for detailed explanation.
 * @param[in] reg : Start register address, for address auto increment OR it with AUDIODAC_AUTO_INCREMENT_ENABLE.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audiodac_generic_read ( audiodac_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Audio DAC write register function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #audiodac_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audiodac_write_register ( audiodac_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Audio DAC read register function.
 * @details This function reads data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #audiodac_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audiodac_read_register ( audiodac_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Audio DAC mute output function.
 * @details This function performs soft mute output by setting the XSMT pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #audiodac_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void audiodac_mute_output ( audiodac_t *ctx );

/**
 * @brief Audio DAC unmute output function.
 * @details This function performs soft un-mute output by setting the XSMT pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #audiodac_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void audiodac_unmute_output ( audiodac_t *ctx );

/**
 * @brief Audio DAC get gpio4 pin function.
 * @details This function returns the GPIO4 pin logic state. 
 * The GPIO4 pin is mapped to auto mute flag output for both L and R channels by default.
 * @param[in] ctx : Click context object.
 * See #audiodac_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t audiodac_get_gpio4_pin ( audiodac_t *ctx );

/**
 * @brief Audio DAC select page function.
 * @details This function selects the register page.
 * @param[in] ctx : Click context object.
 * See #audiodac_t object definition for detailed explanation.
 * @param[in] page_num : Register page number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audiodac_select_page ( audiodac_t *ctx, uint8_t page_num );

/**
 * @brief Audio DAC volume control function.
 * @details This function sets the volume level for the selected output channel.
 * @param[in] ctx : Click context object.
 * See #audiodac_t object definition for detailed explanation.
 * @param[in] channel : @li @c 0 - Both left and right channels,
 *                      @li @c 1 - Left channel,
 *                      @li @c 2 - Right channel.
 * @param[in] volume : Volume level [0-100], 0 - MUTE, 100 - MAX volume.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audiodac_volume_control ( audiodac_t *ctx, uint8_t channel, uint8_t volume );

#ifdef __cplusplus
}
#endif
#endif // AUDIODAC_H

/*! @} */ // audiodac

// ------------------------------------------------------------------------ END
