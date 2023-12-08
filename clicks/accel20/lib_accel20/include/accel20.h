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
 * @file accel20.h
 * @brief This file contains API for Accel 20 Click Driver.
 */

#ifndef ACCEL20_H
#define ACCEL20_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup accel20 Accel 20 Click Driver
 * @brief API for configuring and manipulating Accel 20 Click driver.
 * @{
 */

/**
 * @defgroup accel20_reg Accel 20 Registers List
 * @brief List of registers of Accel 20 Click driver.
 */

/**
 * @addtogroup accel20_reg
 * @{
 */

/**
 * @brief Accel 20 description register.
 * @details Specified register for description of Accel 20 Click driver.
 */
#define ACCEL20_REG_MAN_ID           0x00
#define ACCEL20_REG_PART_ID          0x01
#define ACCEL20_REG_XADP_L           0x02
#define ACCEL20_REG_XADP_H           0x03
#define ACCEL20_REG_YADP_L           0x04
#define ACCEL20_REG_YADP_H           0x05
#define ACCEL20_REG_ZADP_L           0x06
#define ACCEL20_REG_ZADP_H           0x07
#define ACCEL20_REG_XOUT_L           0x08
#define ACCEL20_REG_XOUT_H           0x09
#define ACCEL20_REG_YOUT_L           0x0A
#define ACCEL20_REG_YOUT_H           0x0B
#define ACCEL20_REG_ZOUT_L           0x0C
#define ACCEL20_REG_ZOUT_H           0x0D
#define ACCEL20_REG_COTR             0x12
#define ACCEL20_REG_WHO_AM_I         0x13
#define ACCEL20_REG_TSCP             0x14
#define ACCEL20_REG_TSPP             0x15
#define ACCEL20_REG_INS1             0x16
#define ACCEL20_REG_INS2             0x17
#define ACCEL20_REG_INS3             0x18
#define ACCEL20_REG_STATUS_REG       0x19
#define ACCEL20_REG_INT_REL          0x1A
#define ACCEL20_REG_CNTL1            0x1B
#define ACCEL20_REG_CNTL2            0x1C
#define ACCEL20_REG_CNTL3            0x1D
#define ACCEL20_REG_CNTL4            0x1E
#define ACCEL20_REG_CNTL5            0x1F
#define ACCEL20_REG_CNTL6            0x20
#define ACCEL20_REG_ODCNTL           0x21
#define ACCEL20_REG_INC1             0x22
#define ACCEL20_REG_INC2             0x23
#define ACCEL20_REG_INC3             0x24
#define ACCEL20_REG_INC4             0x25
#define ACCEL20_REG_INC5             0x26
#define ACCEL20_REG_INC6             0x27
#define ACCEL20_REG_TILT_TIMER       0x29
#define ACCEL20_REG_TDTRC            0x2A
#define ACCEL20_REG_TDTC             0x2B
#define ACCEL20_REG_TTH              0x2C
#define ACCEL20_REG_TTL              0x2D
#define ACCEL20_REG_FTD              0x2E
#define ACCEL20_REG_STD              0x2F
#define ACCEL20_REG_TLT              0x30
#define ACCEL20_REG_TWS              0x31
#define ACCEL20_REG_FFTH             0x32
#define ACCEL20_REG_FFC              0x33
#define ACCEL20_REG_FFCNTL           0x34
#define ACCEL20_REG_TILT_ANGLE_LL    0x37
#define ACCEL20_REG_TILT_ANGLE_HL    0x38
#define ACCEL20_REG_HYST_SET         0x39
#define ACCEL20_REG_LP_CNTL1         0x3A
#define ACCEL20_REG_LP_CNTL2         0x3B
#define ACCEL20_REG_WUFTH            0x49
#define ACCEL20_REG_BTSWUFTH         0x4A
#define ACCEL20_REG_BTSTH            0x4B
#define ACCEL20_REG_BTSC             0x4C
#define ACCEL20_REG_WUFC             0x4D
#define ACCEL20_REG_SELF_TEST        0x5D
#define ACCEL20_REG_BUF_CNTL1        0x5E
#define ACCEL20_REG_BUF_CNTL2        0x5F
#define ACCEL20_REG_BUF_STATUS_1     0x60
#define ACCEL20_REG_BUF_STATUS_2     0x61
#define ACCEL20_REG_BUF_CLEAR        0x62
#define ACCEL20_REG_BUF_READ         0x63
#define ACCEL20_REG_ADP_CNTL1        0x64
#define ACCEL20_REG_ADP_CNTL2        0x65
#define ACCEL20_REG_ADP_CNTL3        0x66
#define ACCEL20_REG_ADP_CNTL4        0x67
#define ACCEL20_REG_ADP_CNTL5        0x68
#define ACCEL20_REG_ADP_CNTL6        0x69
#define ACCEL20_REG_ADP_CNTL7        0x6A
#define ACCEL20_REG_ADP_CNTL8        0x6B
#define ACCEL20_REG_ADP_CNTL9        0x6C
#define ACCEL20_REG_ADP_CNTL10       0x6D
#define ACCEL20_REG_ADP_CNTL11       0x6E
#define ACCEL20_REG_ADP_CNTL12       0x6F
#define ACCEL20_REG_ADP_CNTL13       0x70
#define ACCEL20_REG_ADP_CNTL14       0x71
#define ACCEL20_REG_ADP_CNTL15       0x72
#define ACCEL20_REG_ADP_CNTL16       0x73
#define ACCEL20_REG_ADP_CNTL17       0x74
#define ACCEL20_REG_ADP_CNTL18       0x75
#define ACCEL20_REG_ADP_CNTL19       0x76
#define ACCEL20_REG_INTERNAL         0x7F

/*! @} */ // accel20_reg

/**
 * @defgroup accel20_set Accel 20 Registers Settings
 * @brief Settings for registers of Accel 20 Click driver.
 */

/**
 * @addtogroup accel20_set
 * @{
 */

/**
 * @brief Accel 20 description setting.
 * @details Specified setting for description of Accel 20 Click driver.
 */
#define ACCEL20_INTERNAL_SOFT_RESET  0x00
#define ACCEL20_SOFT_RESET_PWR_CYC   0x00
#define ACCEL20_SOFT_RESET_REBOOT    0x80

#define ACCEL20_CNTL1_RANGE_8g       0x00
#define ACCEL20_CNTL1_RANGE_16g      0x01
#define ACCEL20_CNTL1_RANGE_32g      0x02
#define ACCEL20_CNTL1_RANGE_64g      0x03
#define ACCEL20_RANGE_BIT_MASK       0xE7

#define ACCEL20_ODCNTL_ODR_0_781_Hz  0x00
#define ACCEL20_ODCNTL_ODR_1_563_Hz  0x01
#define ACCEL20_ODCNTL_ODR_3_125_Hz  0x02
#define ACCEL20_ODCNTL_ODR_6_25_Hz   0x03
#define ACCEL20_ODCNTL_ODR_12_5_Hz   0x04
#define ACCEL20_ODCNTL_ODR_25_Hz     0x05
#define ACCEL20_ODCNTL_ODR_50_Hz     0x06
#define ACCEL20_ODCNTL_ODR_100_Hz    0x07
#define ACCEL20_ODCNTL_ODR_200_Hz    0x08
#define ACCEL20_ODCNTL_ODR_400_Hz    0x09
#define ACCEL20_ODCNTL_ODR_800_Hz    0x0A
#define ACCEL20_ODCNTL_ODR_1600_Hz   0x0B
#define ACCEL20_ODCNTL_ODR_3200_Hz   0x0C
#define ACCEL20_ODCNTL_ODR_6400_Hz   0x0D
#define ACCEL20_ODCNTL_ODR_12800_Hz  0x0E
#define ACCEL20_ODCNTL_ODR_25600_Hz  0x0F
#define ACCEL20_ODR_BIT_MASK         0x0F

#define ACCEL20_CNTL1_OP_MODE_STB    0x00
#define ACCEL20_CNTL1_OP_MODE_L_PWR  0x02
#define ACCEL20_CNTL1_OP_MODE_HP     0x03
#define ACCEL20_OP_MODE_BIT_MASK     0xC0

#define ACCEL20_ENABLE_INT_1         0x30
#define ACCEL20_ENABLE_DATA_READY    0x10

#define ACCEL20_DATA_READY_BIT_MASK  0x10

#define ACCEL20_INT1_DATA_READY      0x00

#define ACCEL20_CHIP_ID              0x46

#define ACCEL20_TRIGGER_DISABLE      0x00
#define ACCEL20_TRIGGER_ENABLE       0x01

/**
 * @brief Accel 20 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 20 Click driver.
 */
#define ACCEL20_SET_DEV_ADDR_GND     0x1E
#define ACCEL20_SET_DEV_ADDR_VCC     0x1F

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b accel20_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ACCEL20_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ACCEL20_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // accel20_set

/**
 * @defgroup accel20_map Accel 20 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 20 Click driver.
 */

/**
 * @addtogroup accel20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 20 Click to the selected MikroBUS.
 */
#define ACCEL20_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.i2 = MIKROBUS( mikrobus, MIKROBUS_AN );     \
    cfg.trg = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.i1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accel20_map
/*! @} */ // accel20

/**
 * @brief Accel 20 Click driver selector.
 * @details Selects target driver interface of Accel 20 Click driver.
 */
typedef enum
{
   ACCEL20_DRV_SEL_SPI,      /**< SPI driver descriptor. */
   ACCEL20_DRV_SEL_I2C       /**< I2C driver descriptor. */

} accel20_drv_t;

/**
 * @brief Accel 20 Click driver interface.
 * @details Definition of driver interface of Accel 20 Click driver.
 */
typedef err_t ( *accel20_master_io_t )( struct accel20_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Accel 20 Click context object.
 * @details Context object definition of Accel 20 Click driver.
 */
typedef struct accel20_s
{
    digital_out_t  trg;     /**< Trigger pin for FIFO buffer control. */

    digital_in_t  i2;       /**< Interrupt 2 pin. */
    digital_in_t  i1;       /**< Interrupt 1 pin. */

    i2c_master_t  i2c;      /**< I2C driver object. */
    spi_master_t  spi;      /**< SPI driver object. */

    uint8_t     slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
   accel20_drv_t  drv_sel;         /**< Master driver interface selector. */

   accel20_master_io_t  write_f;   /**< Master write function. */
   accel20_master_io_t  read_f;    /**< Master read function. */

} accel20_t;

/**
 * @brief Accel 20 Click configuration object.
 * @details Configuration object definition of Accel 20 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  i2;         /**< Interrupt 2 pin. */
    pin_name_t  trg;        /**< Trigger pin for FIFO buffer control. */
    pin_name_t  i1;         /**< Interrupt 1 pin. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

   accel20_drv_t  drv_sel;                              /**< Master driver interface selector. */

} accel20_cfg_t;

/**
 * @brief Accel 20 axis data structure.
 * @details Axis object definition of Accel 20 Click driver.
 */
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;

} accel20_axis_t;

/**
 * @brief Accel 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   ACCEL20_OK = 0,
   ACCEL20_ERROR = -1

} accel20_return_value_t;

/*!
 * @addtogroup accel20 Accel 20 Click Driver
 * @brief API for configuring and manipulating Accel 20 Click driver.
 * @{
 */

/**
 * @brief Accel 20 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel20_cfg_setup ( accel20_cfg_t *cfg );

/**
 * @brief Accel 20 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accel20_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accel20_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accel20_drv_interface_selection ( accel20_cfg_t *cfg, accel20_drv_t drv_sel );

/**
 * @brief Accel 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel20_init ( accel20_t *ctx, accel20_cfg_t *cfg );

/**
 * @brief Accel 20 default configuration function.
 * @details This function executes a default configuration of Accel 20
 * click board.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel20_default_cfg ( accel20_t *ctx );

/**
 * @brief Accel 20 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel20_generic_write ( accel20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 20 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel20_generic_read ( accel20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 20 soft reset function.
 * @details This function executes a software reset
 * of the KX134 tri-axis ±8g, ±16g, ±32g, ±64g silicon micromachined accelerometer
 * on the Accel 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel20_soft_reset ( accel20_t *ctx );

/**
 * @brief Accel 20 check ID function.
 * @details This function check device ID and communication
 * of the KX134 tri-axis ±8g, ±16g, ±32g, ±64g silicon micromachined accelerometer
 * on the Accel 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @return @li @c  0 - Communication OK,
 *         @li @c -1 - Communication Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel20_check_id ( accel20_t *ctx );

/**
 * @brief Accel 20 check data ready function.
 * @details This function check data ready interrupt reporte
 * of the KX134 tri-axis ±8g, ±16g, ±32g, ±64g silicon micromachined accelerometer
 * on the Accel 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @return @li @c  0 - Data is ready,
 *         @li @c -1 - Data is not ready.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t accel20_data_ready (accel20_t *ctx );

/**
 * @brief Accel 20 set operating mode function.
 * @details This function sets operating mode
 * of the KX134 tri-axis ±8g, ±16g, ±32g, ±64g silicon micromachined accelerometer
 * on the Accel 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @param[in] op_mode : Operating mode:
 *         @li @c 0x00 ( ACCEL20_CNTL1_OP_MODE_STB )   - Stand-by mode,
 *         @li @c 0x02 ( ACCEL20_CNTL1_OP_MODE_L_PWR ) - Low Power mode,
 *         @li @c 0x03 ( ACCEL20_CNTL1_OP_MODE_HP )    - High-Performance mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel20_set_operating_mode ( accel20_t *ctx, uint8_t op_mode );

/**
 * @brief Accel 20 enable INT 1 pin function.
 * @details This function enable I1 ( INT ) pin data 2 ready interrupt reported
 * of the KX134 tri-axis ±8g, ±16g, ±32g, ±64g silicon micromachined accelerometer
 * on the Accel 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel20_enable_int_1_pin ( accel20_t *ctx );

/**
 * @brief Accel 20 enable INT 2 pin function.
 * @details This function enable I2 ( AN ) pin data 2 ready interrupt reported
 * of the KX134 tri-axis ±8g, ±16g, ±32g, ±64g silicon micromachined accelerometer
 * on the Accel 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel20_enable_int_2_pin ( accel20_t *ctx );

/**
 * @brief Accel 20 set accel range function.
 * @details This function sets accel G-range 
 * of the KX134 tri-axis ±8g, ±16g, ±32g, ±64g silicon micromachined accelerometer
 * on the Accel 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @param[in] range : Acceleration range:
 *         @li @c 0x00 ( ACCEL20_CNTL1_RANGE_8g )  - G-range  +-8g,
 *         @li @c 0x01 ( ACCEL20_CNTL1_RANGE_16g ) - G-range +-16g,
 *         @li @c 0x02 ( ACCEL20_CNTL1_RANGE_32g ) - G-range +-32g,
 *         @li @c 0x03 ( ACCEL20_CNTL1_RANGE_64g ) - G-range +-64g.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel20_set_accel_range ( accel20_t *ctx, uint8_t range );

/**
 * @brief Accel 20 set output data rate function.
 * @details This function sets output data rate
 * of the KX134 tri-axis ±8g, ±16g, ±32g, ±64g silicon micromachined accelerometer
 * on the Accel 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @param[in] odr : Acceleration odr:
 *         @li @c 0x00 ( ACCEL20_ODCNTL_ODR_0_781_Hz ) -     0.781 Hz,
 *         @li @c 0x01 ( ACCEL20_ODCNTL_ODR_1_563_Hz ) -     1.563 Hz,
 *         @li @c 0x02 ( ACCEL20_ODCNTL_ODR_3_125_Hz ) -     3.125 Hz,
 *         @li @c 0x03 ( ACCEL20_ODCNTL_ODR_6_25_Hz )  -     6.25 Hz,
 *         @li @c 0x04 ( ACCEL20_ODCNTL_ODR_12_5_Hz )  -    12.5 Hz,
 *         @li @c 0x05 ( ACCEL20_ODCNTL_ODR_25_Hz )    -    25 Hz,
 *         @li @c 0x06 ( ACCEL20_ODCNTL_ODR_50_Hz )    -    50 Hz,
 *         @li @c 0x07 ( ACCEL20_ODCNTL_ODR_100_Hz )   -   100 Hz,
 *         @li @c 0x08 ( ACCEL20_ODCNTL_ODR_200_Hz )   -   200 Hz,
 *         @li @c 0x09 ( ACCEL20_ODCNTL_ODR_400_Hz )   -   400 Hz,
 *         @li @c 0x0A ( ACCEL20_ODCNTL_ODR_800_Hz )   -   800 Hz,
 *         @li @c 0x0B ( ACCEL20_ODCNTL_ODR_1600_Hz )  -  1600 Hz,
 *         @li @c 0x0C ( ACCEL20_ODCNTL_ODR_3200_Hz )  -  3200 Hz,
 *         @li @c 0x0D ( ACCEL20_ODCNTL_ODR_6400_Hz )  -  6400 Hz,
 *         @li @c 0x0E ( ACCEL20_ODCNTL_ODR_12800_Hz ) - 12800 Hz,
 *         @li @c 0x0F ( ACCEL20_ODCNTL_ODR_25600_Hz ) - 25600 Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel20_set_output_data_rate ( accel20_t *ctx, uint8_t odr );

/**
 * @brief Accel 20 get accelerometer axis function.
 * @details This function get accelerometer data
 * of the KX134 tri-axis ±8g, ±16g, ±32g, ±64g silicon micromachined accelerometer
 * on the Accel 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @param[out] axis : An object that contains X , Y and Z axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel20_get_axis_data ( accel20_t *ctx, accel20_axis_t *axis );

/**
 * @brief Accel 20 set trigger function.
 * @details This function set trigger,  FIFO buffer control
 * of the KX134 tri-axis ±8g, ±16g, ±32g, ±64g silicon micromachined accelerometer
 * on the Accel 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @param[in] en_trg : 
 *         @li @c 0x00 ( ACCEL20_TRIGGER_DISABLE ) - Not using external trigger option,
 *         @li @c 0x01 ( ACCEL20_TRIGGER_ENABLE )  - Using external trigger option.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel20_set_trigger ( accel20_t *ctx, uint8_t en_trg );

/**
 * @brief Accel 20 get Interrupt 1 function.
 * @details This function get states of the Interrupt 1 ( INT pin )
 * of the KX134 tri-axis ±8g, ±16g, ±32g, ±64g silicon micromachined accelerometer
 * on the Accel 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @return @li @c  0 - Low pin state,
 *         @li @c -1 - High pin state.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t accel20_get_int_1 ( accel20_t *ctx );

/**
 * @brief Accel 20 get Interrupt 2 function.
 * @details This function get states of the Interrupt 2 ( AN pin )
 * of the KX134 tri-axis ±8g, ±16g, ±32g, ±64g silicon micromachined accelerometer
 * on the Accel 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @return @li @c  0 - Low pin state,
 *         @li @c -1 - High pin state.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t accel20_get_int_2 ( accel20_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCEL20_H

/*! @} */ // accel20

// ------------------------------------------------------------------------ END
