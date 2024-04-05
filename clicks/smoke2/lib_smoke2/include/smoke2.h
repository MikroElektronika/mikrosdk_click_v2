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
 * @file smoke2.h
 * @brief This file contains API for Smoke 2 Click Driver.
 */

#ifndef SMOKE2_H
#define SMOKE2_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup smoke2 Smoke 2 Click Driver
 * @brief API for configuring and manipulating Smoke 2 Click driver.
 * @{
 */

/**
 * @defgroup smoke2_reg Smoke 2 Registers List
 * @brief List of registers of Smoke 2 Click driver.
 */

/**
 * @addtogroup smoke2_reg
 * @{
 */

/**
 * @brief Smoke 2 description register.
 * @details Specified register for description of Smoke 2 Click driver.
 */
#define SMOKE2_REG_STATUS                   0x00
#define SMOKE2_REG_INT_MASK                 0x01
#define SMOKE2_REG_GPIO_DRV                 0x02
#define SMOKE2_REG_BG_STATUS                0x04
#define SMOKE2_REG_FIFO_THR                 0x06
#define SMOKE2_REG_DEVID                    0x08
#define SMOKE2_REG_I2CS_ID                  0x09
#define SMOKE2_REG_CLK_RATIO                0x0A
#define SMOKE2_REG_GPIO_CTRL                0x0B
#define SMOKE2_REG_SLAVE_ADDR_KEY           0x0D
#define SMOKE2_REG_SW_RESET                 0x0F
#define SMOKE2_REG_MODE                     0x10
#define SMOKE2_REG_SLOT_EN                  0x11
#define SMOKE2_REG_FSAMPLE                  0x12
#define SMOKE2_REG_PD_LED_SELECT            0x14
#define SMOKE2_REG_NUM_AVG                  0x15
#define SMOKE2_REG_BIG_MEAS_A               0x16
#define SMOKE2_REG_INT_SEQ_A                0x17
#define SMOKE2_REG_SLOTA_CH1_OFFSET         0x18
#define SMOKE2_REG_SLOTA_CH2_OFFSET         0x19
#define SMOKE2_REG_SLOTA_CH3_OFFSET         0x1A
#define SMOKE2_REG_SLOTA_CH4_OFFSET         0x1B
#define SMOKE2_REG_BIG_MEAS_B               0x1C
#define SMOKE2_REG_INT_SEQ_B                0x1D
#define SMOKE2_REG_SLOTB_CH1_OFFSET         0x1E
#define SMOKE2_REG_SLOTB_CH2_OFFSET         0x1F
#define SMOKE2_REG_SLOTB_CH3_OFFSET         0x20
#define SMOKE2_REG_SLOTB_CH4_OFFSET         0x21
#define SMOKE2_REG_ILED3_COARSE             0x22
#define SMOKE2_REG_ILED1_COARSE             0x23
#define SMOKE2_REG_ILED2_COARSE             0x24
#define SMOKE2_REG_ILED_FINE                0x25
#define SMOKE2_REG_SLOTA_LED_PULSE          0x30
#define SMOKE2_REG_SLOTA_NUM_PULSES         0x31
#define SMOKE2_REG_LED_DISABLE              0x34
#define SMOKE2_REG_SLOTB_LED_PULSE          0x35
#define SMOKE2_REG_SLOTB_NUM_PULSES         0x36
#define SMOKE2_REG_ALT_PWR_DN               0x37
#define SMOKE2_REG_EXT_SYNC_STARTUP         0x38
#define SMOKE2_REG_SLOTA_AFE_WINDOW         0x39
#define SMOKE2_REG_SLOTB_AFE_WINDOW         0x3B
#define SMOKE2_REG_AFE_PWR_CFG1             0x3C
#define SMOKE2_REG_SLOTA_FLOAT_LED          0x3E
#define SMOKE2_REG_SLOTB_FLOAT_LED          0x3F
#define SMOKE2_REG_SLOTA_TIA_CFG            0x42
#define SMOKE2_REG_SLOTA_AFE_CFG            0x43
#define SMOKE2_REG_SLOTB_TIA_CFG            0x44
#define SMOKE2_REG_SLOTB_AFE_CFG            0x45
#define SMOKE2_REG_SAMPLE_CLK               0x4B
#define SMOKE2_REG_CLK32M_ADJUST            0x4D
#define SMOKE2_REG_EXT_SYNC_SEL             0x4F
#define SMOKE2_REG_CLK32M_CAL_EN            0x50
#define SMOKE2_REG_AFE_PWR_CFG2             0x54
#define SMOKE2_REG_TIA_INDEP_GAIN           0x55
#define SMOKE2_REG_MATH                     0x58
#define SMOKE2_REG_FLT_CONFIG_B             0x59
#define SMOKE2_REG_FLT_LED_FIRE             0x5A
#define SMOKE2_REG_FLT_CONFIG_A             0x5E
#define SMOKE2_REG_DATA_ACCESS_CTL          0x5F
#define SMOKE2_REG_FIFO_ACCESS              0x60
#define SMOKE2_REG_SLOTA_CH1                0x64
#define SMOKE2_REG_SLOTA_CH2                0x65
#define SMOKE2_REG_SLOTA_CH3                0x66
#define SMOKE2_REG_SLOTA_CH4                0x67
#define SMOKE2_REG_SLOTB_CH1                0x68
#define SMOKE2_REG_SLOTB_CH2                0x69
#define SMOKE2_REG_SLOTB_CH3                0x6A
#define SMOKE2_REG_SLOTB_CH4                0x6B
#define SMOKE2_REG_A_CH1_LOW                0x70
#define SMOKE2_REG_A_CH2_LOW                0x71
#define SMOKE2_REG_A_CH3_LOW                0x72
#define SMOKE2_REG_A_CH4_LOW                0x73
#define SMOKE2_REG_A_CH1_HIGH               0x74
#define SMOKE2_REG_A_CH2_HIGH               0x75
#define SMOKE2_REG_A_CH3_HIGH               0x76
#define SMOKE2_REG_A_CH4_HIGH               0x77
#define SMOKE2_REG_B_CH1_LOW                0x78
#define SMOKE2_REG_B_CH2_LOW                0x79
#define SMOKE2_REG_B_CH3_LOW                0x7A
#define SMOKE2_REG_B_CH4_LOW                0x7B
#define SMOKE2_REG_B_CH1_HIGH               0x7C
#define SMOKE2_REG_B_CH2_HIGH               0x7D
#define SMOKE2_REG_B_CH3_HIGH               0x7E
#define SMOKE2_REG_B_CH4_HIGH               0x7F

/*! @} */ // smoke2_reg

/**
 * @defgroup smoke2_set Smoke 2 Registers Settings
 * @brief Settings for registers of Smoke 2 Click driver.
 */

/**
 * @addtogroup smoke2_set
 * @{
 */

/**
 * @brief Smoke 2 description setting.
 * @details Specified setting for description of Smoke 2 Click driver.
 */
#define SMOKE2_SLOT_A                       0
#define SMOKE2_SLOT_B                       4

/**
 * @brief Smoke 2 description setting to select channel.
 * @details Specified setting for select channel Smoke 2 Click driver.
 */
#define SMOKE2_CHN_1                        0
#define SMOKE2_CHN_2                        1
#define SMOKE2_CHN_3                        2
#define SMOKE2_CHN_4                        3

/**
 * @brief Smoke 2 description setting to select mode.
 * @details Specified setting for select mdoe Smoke 2 Click driver.
 */
#define SMOKE2_MODE_IDLE                    0
#define SMOKE2_MODE_PROGRAM                 1
#define SMOKE2_MODE_NORMAL                  2

/**
 * @brief Smoke 2 description setting for detection smoke.
 * @details Specified setting for detection smoke Smoke 2 Click driver.
 */
#define SMOKE2_SMOKE_DETECTED               0xCC
#define SMOKE2_SMOKE_NOT_DETECTED           0xDD

/**
 * @brief Smoke 2 description setting for read and write.
 * @details Specified setting for read and write Smoke 2 Click driver.
 */
#define SMOKE2_READ_CMD                     0
#define SMOKE2_WRITE_CMD                    1

/**
 * @brief Smoke 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Smoke 2 Click driver.
 */
#define SMOKE2_SET_DEV_ADDR                 0x64

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b smoke2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SMOKE2_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define SMOKE2_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // smoke2_set

/**
 * @defgroup smoke2_map Smoke 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Smoke 2 Click driver.
 */

/**
 * @addtogroup smoke2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smoke 2 Click to the selected MikroBUS.
 */
#define SMOKE2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // smoke2_map
/*! @} */ // smoke2

/**
 * @brief Smoke 2 Click driver selector.
 * @details Selects target driver interface of Smoke 2 Click driver.
 */
typedef enum
{
    SMOKE2_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    SMOKE2_DRV_SEL_I2C       /**< I2C driver descriptor. */

} smoke2_drv_t;

/**
 * @brief Smoke 2 Click driver interface.
 * @details Definition of driver interface of Smoke 2 Click driver.
 */
typedef err_t ( *smoke2_master_io_t )( struct smoke2_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Smoke 2 Click context object.
 * @details Context object definition of Smoke 2 Click driver.
 */
typedef struct smoke2_s
{
    digital_in_t  int_pin;               /**< Interrupt. */

    i2c_master_t  i2c;                   /**< I2C driver object. */
    spi_master_t  spi;                   /**< SPI driver object. */
    
    uint8_t     slave_address;           /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;             /**< Chip select pin descriptor (used for SPI driver). */
    smoke2_drv_t  drv_sel;                /**< Master driver interface selector. */

    smoke2_master_io_t  write_f;          /**< Master write function. */
    smoke2_master_io_t  read_f;           /**< Master read function. */

    uint16_t calibration_value;
    uint16_t threshold_value;
    uint8_t enabled_slot;
    
} smoke2_t;

/**
 * @brief Smoke 2 Click configuration object.
 * @details Configuration object definition of Smoke 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  int_pin;    /**< Interrupt. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    smoke2_drv_t  drv_sel;                               /**< Master driver interface selector. */

} smoke2_cfg_t;

/**
 * @brief Smoke 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMOKE2_OK = 0,
    SMOKE2_ERROR = -1

} smoke2_return_value_t;

/*!
 * @addtogroup smoke2 Smoke 2 Click Driver
 * @brief API for configuring and manipulating Smoke 2 Click driver.
 * @{
 */

/**
 * @brief Smoke 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smoke2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smoke2_cfg_setup ( smoke2_cfg_t *cfg );

/**
 * @brief Smoke 2 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #smoke2_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #smoke2_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void smoke2_drv_interface_selection ( smoke2_cfg_t *cfg, smoke2_drv_t drv_sel );

/**
 * @brief Smoke 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smoke2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smoke2_init ( smoke2_t *ctx, smoke2_cfg_t *cfg );

/**
 * @brief Smoke 2 default configuration function.
 * @details This function executes a default configuration of Smoke 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void smoke2_default_cfg ( smoke2_t *ctx );

/**
 * @brief Smoke 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smoke2_generic_write ( smoke2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smoke 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smoke2_generic_read ( smoke2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smoke 2 get state of int pin function.
 * @details This function eget state of int pin of Smoke 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @return Pin state.
 * @note None.
 */
uint8_t smoke2_get_int_pin ( smoke2_t *ctx );

/**
 * @brief Smoke 2 generic function for writing data to register function.
 * @details This function is generic for writing data to register of Smoke 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] reg : register address.
 * @param[in] tx_data : data to be written.
 * @return Nothing.
 * @note None.
 */
void smoke2_write_data( smoke2_t *ctx, uint8_t reg, uint16_t tx_data );

/**
 * @brief Smoke 2 generic function for reading data from registar.
 * @details This function is generic for reading data from registar of Smoke 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] reg : register address.
 * @return Read data.
 * @note None.
 */
uint16_t smoke2_read_data( smoke2_t *ctx, uint8_t reg );

/**
 * @brief Smoke 2 generic function for writing bit state.
 * @details This function is generic for writing bit state of Smoke 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] reg : register address.
 * @param[in] bit_num : bit to be written.
 * @param[in] val : value to be written.
 * @return Nothing.
 * @note None.
 */
void smoke2_set_bit ( smoke2_t *ctx, uint8_t reg, uint8_t bit_num , uint8_t val );

/**
 * @brief Smoke 2 generic function for reading bit state.
 * @details This function is generic for reading bit state of Smoke 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] reg : register address.
 * @param[in] bit_num : bit to be written.
 * @return Read data.
 * @note None.
 */
uint8_t smoke2_get_bit ( smoke2_t *ctx, uint8_t reg, uint8_t bit_num );

/**
 * @brief Smoke 2 setting mode function.
 * @details This function setting mode of Smoke 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] mode : device mode.
 * @return Nothing.
 * @note None.
 */
void smoke2_set_mode ( smoke2_t *ctx, uint8_t mode );

/**
 * @brief Smoke 2 get mode function.
 * @details This function get mode of Smoke 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[out] fifo : fifo data.
 * @param[out] slot_a : slot a int.
 * @param[out] slot_b : slot b int. 
 * @return Nothing.
 * @note None.
 */
void smoke2_get_int ( smoke2_t *ctx, uint8_t *fifo, uint8_t *slot_a, uint8_t *slot_b );

/**
 * @brief Smoke 2 reading bit state function.
 * @details This function reading bit state of Smoke 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] slot  : slot to be read.
 * @param[in] chn : channel to be read
 * @return Read data.
 * @note None.
 */
uint16_t smoke2_read_sens_data ( smoke2_t *ctx, uint8_t slot, uint8_t chn );

/**
 * @brief Smoke 2 reseting device function.
 * @details This function reseting device of Smoke 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void smoke2_soft_reset ( smoke2_t *ctx );

/**
 * @brief Smoke 2 calibrating data and setting threshold function.
 * @details This function calibrating data and setting threshold of Smoke 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] threshold : threshold for smoke detection.
 * @return Calibrated data.
 * @note None.
 */
uint16_t smoke2_smoke_calibration ( smoke2_t *ctx, uint16_t threshold );

/**
 * @brief Smoke 2 checking smoke detection function.
 * @details This function checking smoke detection of Smoke 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @return SMOKE2_SMOKE_DETECTED or SMOKE2_SMOKE_NOT_DETECTED macro.
 * @note None.
 */
uint8_t smoke2_check_smoke ( smoke2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SMOKE2_H

/*! @} */ // smoke2

// ------------------------------------------------------------------------ END
