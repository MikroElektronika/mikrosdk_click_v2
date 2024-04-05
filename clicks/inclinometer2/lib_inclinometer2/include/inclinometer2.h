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
 * @file inclinometer2.h
 * @brief This file contains API for Inclinometer 2 Click Driver.
 */

#ifndef INCLINOMETER2_H
#define INCLINOMETER2_H

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
 * @addtogroup inclinometer2 Inclinometer 2 Click Driver
 * @brief API for configuring and manipulating Inclinometer 2 Click driver.
 * @{
 */

/**
 * @defgroup inclinometer2_reg Inclinometer 2 Registers List
 * @brief List of registers of Inclinometer 2 Click driver.
 */

/**
 * @addtogroup inclinometer2_reg
 * @{
 */

/**
 * @brief Inclinometer 2 register map.
 * @details Specified register map of Inclinometer 2 Click driver.
 */
#define INCLINOMETER2_REG_FUNC_CFG_ACCESS           0x01
#define INCLINOMETER2_REG_PIN_CTRL                  0x02
#define INCLINOMETER2_REG_FIFO_CTRL1                0x07
#define INCLINOMETER2_REG_FIFO_CTRL2                0x08
#define INCLINOMETER2_REG_FIFO_CTRL3                0x09
#define INCLINOMETER2_REG_FIFO_CTRL4                0x0A
#define INCLINOMETER2_REG_COUNTER_BDR_REG1          0x0B
#define INCLINOMETER2_REG_COUNTER_BDR_REG2          0x0C
#define INCLINOMETER2_REG_INT1_CTRL                 0x0D
#define INCLINOMETER2_REG_INT2_CTRL                 0x0E
#define INCLINOMETER2_REG_WHO_AM_I                  0x0F
#define INCLINOMETER2_REG_CTRL1_XL                  0x10
#define INCLINOMETER2_REG_CTRL3_C                   0x12
#define INCLINOMETER2_REG_CTRL4_C                   0x13
#define INCLINOMETER2_REG_CTRL5_C                   0x14
#define INCLINOMETER2_REG_CTRL6_C                   0x15
#define INCLINOMETER2_REG_CTRL7_XL                  0x16
#define INCLINOMETER2_REG_CTRL8_XL                  0x17
#define INCLINOMETER2_REG_CTRL9_XL                  0x18
#define INCLINOMETER2_REG_CTRL10_C                  0x19
#define INCLINOMETER2_REG_ALL_INT_SRC               0x1A
#define INCLINOMETER2_REG_WAKE_UP_SRC               0x1B
#define INCLINOMETER2_REG_TAP_SRC                   0x1C
#define INCLINOMETER2_REG_DEN_SRC                   0x1D
#define INCLINOMETER2_REG_STATUS                    0x1E
#define INCLINOMETER2_REG_OUT_TEMP_L                0x20
#define INCLINOMETER2_REG_OUT_TEMP_H                0x21
#define INCLINOMETER2_REG_OUTX_L_A                  0x28
#define INCLINOMETER2_REG_OUTX_H_A                  0x29
#define INCLINOMETER2_REG_OUTY_L_A                  0x2A
#define INCLINOMETER2_REG_OUTY_H_A                  0x2B
#define INCLINOMETER2_REG_EMB_FUNC_STATUS_MAINPAGE  0x35
#define INCLINOMETER2_REG_FSM_STATUS_A_MAINPAGE     0x36
#define INCLINOMETER2_REG_FSM_STATUS_B_MAINPAGE     0x37
#define INCLINOMETER2_REG_MLC_STATUS_MAINPAGE       0x38
#define INCLINOMETER2_REG_STATUS_MASTER_MAINPAGE    0x39
#define INCLINOMETER2_REG_FIFO_STATUS1              0x3A
#define INCLINOMETER2_REG_FIFO_STATUS2              0x3B
#define INCLINOMETER2_REG_TIMESTAMP0                0x40
#define INCLINOMETER2_REG_TIMESTAMP1                0x41
#define INCLINOMETER2_REG_TIMESTAMP2                0x42
#define INCLINOMETER2_REG_TIMESTAMP3                0x43
#define INCLINOMETER2_REG_TAP_CFG0                  0x56
#define INCLINOMETER2_REG_TAP_CFG1                  0x57
#define INCLINOMETER2_REG_TAP_CFG2                  0x58
#define INCLINOMETER2_REG_INT_DUR2                  0x5A
#define INCLINOMETER2_REG_WAKE_UP_THS               0x5B
#define INCLINOMETER2_REG_WAKE_UP_DUR               0x5C
#define INCLINOMETER2_REG_MD1_CFG                   0x5E
#define INCLINOMETER2_REG_MD2_CFG                   0x5F
#define INCLINOMETER2_REG_INTERNAL_FREQ_FINE        0x63
#define INCLINOMETER2_REG_X_OFS_USR                 0x73
#define INCLINOMETER2_REG_Y_OFS_USR                 0x74
#define INCLINOMETER2_REG_FIFO_DATA_OUT_TAG         0x78
#define INCLINOMETER2_REG_FIFO_DATA_OUT_X_L         0x79
#define INCLINOMETER2_REG_FIFO_DATA_OUT_X_H         0x7A
#define INCLINOMETER2_REG_FIFO_DATA_OUT_Y_L         0x7B
#define INCLINOMETER2_REG_FIFO_DATA_OUT_Y_H         0x7C
#define INCLINOMETER2_REG_FIFO_DATA_OUT_Z_L         0x7D
#define INCLINOMETER2_REG_FIFO_DATA_OUT_Z_H         0x7E

/**
 * @brief Inclinometer 2 embedded functions register map.
 * @details Specified embedded functions register map of Inclinometer 2 Click driver.
 */
#define INCLINOMETER2_FUNC_REG_PAGE_SEL             0x02
#define INCLINOMETER2_FUNC_REG_EMB_FUNC_EN_B        0x05
#define INCLINOMETER2_FUNC_REG_PAGE_ADDRESS         0x08
#define INCLINOMETER2_FUNC_REG_PAGE_VALUE           0x09
#define INCLINOMETER2_FUNC_REG_EMB_FUNC_INT1        0x0A
#define INCLINOMETER2_FUNC_REG_FSM_INT1_A           0x0B
#define INCLINOMETER2_FUNC_REG_FSM_INT1_B           0x0C
#define INCLINOMETER2_FUNC_REG_MLC_INT1             0x0D
#define INCLINOMETER2_FUNC_REG_EMB_FUNC_INT2        0x0E
#define INCLINOMETER2_FUNC_REG_FSM_INT2_A           0x0F
#define INCLINOMETER2_FUNC_REG_FSM_INT2_B           0x10
#define INCLINOMETER2_FUNC_REG_MLC_INT2             0x11
#define INCLINOMETER2_FUNC_REG_EMB_FUNC_STATUS      0x12
#define INCLINOMETER2_FUNC_REG_FSM_STATUS_A         0x13
#define INCLINOMETER2_FUNC_REG_FSM_STATUS_B         0x14
#define INCLINOMETER2_FUNC_REG_MLC_STATUS           0x15
#define INCLINOMETER2_FUNC_REG_PAGE_RW              0x17
#define INCLINOMETER2_FUNC_REG_FSM_ENABLE_A         0x46
#define INCLINOMETER2_FUNC_REG_FSM_ENABLE_B         0x47
#define INCLINOMETER2_FUNC_REG_FSM_LONG_COUNTER_L   0x48
#define INCLINOMETER2_FUNC_REG_FSM_LONG_COUNTER_H   0x49
#define INCLINOMETER2_FUNC_REG_FSM_LONG_COUNTER_CLR 0x4A
#define INCLINOMETER2_FUNC_REG_FSM_OUTS1            0x4C
#define INCLINOMETER2_FUNC_REG_FSM_OUTS2            0x4D
#define INCLINOMETER2_FUNC_REG_FSM_OUTS3            0x4E
#define INCLINOMETER2_FUNC_REG_FSM_OUTS4            0x4F
#define INCLINOMETER2_FUNC_REG_FSM_OUTS5            0x50
#define INCLINOMETER2_FUNC_REG_FSM_OUTS6            0x51
#define INCLINOMETER2_FUNC_REG_FSM_OUTS7            0x52
#define INCLINOMETER2_FUNC_REG_FSM_OUTS8            0x53
#define INCLINOMETER2_FUNC_REG_FSM_OUTS9            0x54
#define INCLINOMETER2_FUNC_REG_FSM_OUTS10           0x55
#define INCLINOMETER2_FUNC_REG_FSM_OUTS11           0x56
#define INCLINOMETER2_FUNC_REG_FSM_OUTS12           0x57
#define INCLINOMETER2_FUNC_REG_FSM_OUTS13           0x58
#define INCLINOMETER2_FUNC_REG_FSM_OUTS14           0x59
#define INCLINOMETER2_FUNC_REG_FSM_OUTS15           0x5A
#define INCLINOMETER2_FUNC_REG_FSM_OUTS16           0x5B
#define INCLINOMETER2_FUNC_REG_EMB_FUNC_ODR_CFG_B   0x5F
#define INCLINOMETER2_FUNC_REG_EMB_FUNC_ODR_CFG_C   0x60
#define INCLINOMETER2_FUNC_REG_EMB_FUNC_INIT_B      0x67
#define INCLINOMETER2_FUNC_REG_MCL0_SRC             0x70
#define INCLINOMETER2_FUNC_REG_MCL1_SRC             0x71
#define INCLINOMETER2_FUNC_REG_MCL2_SRC             0x72
#define INCLINOMETER2_FUNC_REG_MCL3_SRC             0x73
#define INCLINOMETER2_FUNC_REG_MCL4_SRC             0x74
#define INCLINOMETER2_FUNC_REG_MCL5_SRC             0x75
#define INCLINOMETER2_FUNC_REG_MCL6_SRC             0x76
#define INCLINOMETER2_FUNC_REG_MCL7_SRC             0x77

/**
 * @brief Inclinometer 2 sensor hub register map.
 * @details Specified sensor hub register map of Inclinometer 2 Click driver.
 */
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_1         0x02
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_2         0x03
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_3         0x04
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_4         0x05
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_5         0x06
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_6         0x07
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_7         0x08
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_8         0x09
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_9         0x0A
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_10        0x0B
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_11        0x0C
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_12        0x0D
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_13        0x0E
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_14        0x0F
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_15        0x10
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_16        0x11
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_17        0x12
#define INCLINOMETER2_SHUB_REG_SENSOR_HUB_18        0x13
#define INCLINOMETER2_SHUB_REG_MASTER_CONFIG        0x14
#define INCLINOMETER2_SHUB_REG_SLV0_ADD             0x15
#define INCLINOMETER2_SHUB_REG_SLV0_SUBADD          0x16
#define INCLINOMETER2_SHUB_REG_SLV0_CONFIG          0x17
#define INCLINOMETER2_SHUB_REG_SLV1_ADD             0x18
#define INCLINOMETER2_SHUB_REG_SLV1_SUBADD          0x19
#define INCLINOMETER2_SHUB_REG_SLV1_CONFIG          0x1A
#define INCLINOMETER2_SHUB_REG_SLV2_ADD             0x1B
#define INCLINOMETER2_SHUB_REG_SLV2_SUBADD          0x1C
#define INCLINOMETER2_SHUB_REG_SLV2_CONFIG          0x1D
#define INCLINOMETER2_SHUB_REG_SLV3_ADD             0x1E
#define INCLINOMETER2_SHUB_REG_SLV3_SUBADD          0x1F
#define INCLINOMETER2_SHUB_REG_SLV3_CONFIG          0x20
#define INCLINOMETER2_SHUB_REG_DATAWRITE_SLV0       0x21
#define INCLINOMETER2_SHUB_REG_STATUS_MASTER        0x22

/*! @} */ // inclinometer2_reg

/**
 * @defgroup inclinometer2_set Inclinometer 2 Registers Settings
 * @brief Settings for registers of Inclinometer 2 Click driver.
 */

/**
 * @addtogroup inclinometer2_set
 * @{
 */

/**
 * @brief Inclinometer 2 INT1_CTRL register settings.
 * @details Specified INT1_CTRL register settings of Inclinometer 2 Click driver.
 */
#define INCLINOMETER2_INT1_CTRL_DEN_DRDY            0x80
#define INCLINOMETER2_INT1_CTRL_CNT_BDR             0x40
#define INCLINOMETER2_INT1_CTRL_FIFO_FULL           0x20
#define INCLINOMETER2_INT1_CTRL_FIFO_OVR            0x10
#define INCLINOMETER2_INT1_CTRL_FIFO_TH             0x08
#define INCLINOMETER2_INT1_CTRL_BOOT                0x04
#define INCLINOMETER2_INT1_CTRL_DRDY_XL             0x01

/**
 * @brief Inclinometer 2 STATUS register values.
 * @details Specified STATUS register values of Inclinometer 2 Click driver.
 */
#define INCLINOMETER2_STATUS_TEMP_DRDY              0x04
#define INCLINOMETER2_STATUS_ACCEL_DRDY             0x01

/**
 * @brief Inclinometer 2 calculation values.
 * @details Specified calculation values of Inclinometer 2 Click driver.
 */
#define INCLINOMETER2_ACCEL_FSR_0p5G_RES            0.015f
#define INCLINOMETER2_ACCEL_FSR_1G_RES              0.031f
#define INCLINOMETER2_ACCEL_FSR_2G_RES              0.061f
#define INCLINOMETER2_ACCEL_FSR_3G_RES              0.122f
#define INCLINOMETER2_ROOM_TEMP                     25.0f
#define INCLINOMETER2_TEMP_SENS                     256.0f

/**
 * @brief Inclinometer 2 WHO_AM_I register value.
 * @details Specified WHO_AM_I register value of Inclinometer 2 Click driver.
 */
#define INCLINOMETER2_WHO_AM_I                      0x6B

/**
 * @brief Inclinometer 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Inclinometer 2 Click driver.
 */
#define INCLINOMETER2_DEVICE_ADDRESS_0              0x6A
#define INCLINOMETER2_DEVICE_ADDRESS_1              0x6B

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b inclinometer2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define INCLINOMETER2_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define INCLINOMETER2_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // inclinometer2_set

/**
 * @defgroup inclinometer2_map Inclinometer 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Inclinometer 2 Click driver.
 */

/**
 * @addtogroup inclinometer2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Inclinometer 2 Click to the selected MikroBUS.
 */
#define INCLINOMETER2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // inclinometer2_map
/*! @} */ // inclinometer2

/**
 * @brief Inclinometer 2 Click driver selector.
 * @details Selects target driver interface of Inclinometer 2 Click driver.
 */
typedef enum
{
    INCLINOMETER2_DRV_SEL_SPI,          /**< SPI driver descriptor. */
    INCLINOMETER2_DRV_SEL_I2C           /**< I2C driver descriptor. */

} inclinometer2_drv_t;

/**
 * @brief Inclinometer 2 Click driver interface.
 * @details Definition of driver interface of Inclinometer 2 Click driver.
 */
struct inclinometer2_s;
typedef err_t ( *inclinometer2_master_io_t )( struct inclinometer2_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Inclinometer 2 Click context object.
 * @details Context object definition of Inclinometer 2 Click driver.
 */
typedef struct inclinometer2_s
{
    digital_in_t  int_pin;              /**< Interrupt pin. */

    i2c_master_t  i2c;                  /**< I2C driver object. */
    spi_master_t  spi;                  /**< SPI driver object. */

    uint8_t     slave_address;          /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;            /**< Chip select pin descriptor (used for SPI driver). */
    inclinometer2_drv_t  drv_sel;       /**< Master driver interface selector. */

    inclinometer2_master_io_t  write_f; /**< Master write function. */
    inclinometer2_master_io_t  read_f;  /**< Master read function. */
    float resolution;                   /**< Accel full-scale range resolution. */

} inclinometer2_t;

/**
 * @brief Inclinometer 2 Click configuration object.
 * @details Configuration object definition of Inclinometer 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                    /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                    /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                     /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  int_pin;                /**< Interrupt pin. */

    uint32_t  i2c_speed;                /**< I2C serial speed. */
    uint8_t   i2c_address;              /**< I2C slave address. */

    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

    inclinometer2_drv_t  drv_sel;       /**< Master driver interface selector. */

} inclinometer2_cfg_t;

/**
 * @brief Inclinometer 2 Click accel full-scale range selection.
 * @details Predefined enum values for driver accel full-scale range selection.
 */
typedef enum
{
    INCLINOMETER2_FSR_0p5G = 0x00,
    INCLINOMETER2_FSR_3G,
    INCLINOMETER2_FSR_1G,
    INCLINOMETER2_FSR_2G,
    INCLINOMETER2_FSR_BIT_MASK = 0x0C

} inclinometer2_fsr_t;

/**
 * @brief Inclinometer 2 Click output data rate.
 * @details Predefined enum values for driver output data rate.
 */
typedef enum
{
    INCLINOMETER2_ODR_POWER_DOWN = 0x00,
    INCLINOMETER2_ODR_12p5HZ,
    INCLINOMETER2_ODR_26HZ,
    INCLINOMETER2_ODR_52HZ,
    INCLINOMETER2_ODR_104HZ,
    INCLINOMETER2_ODR_208HZ,
    INCLINOMETER2_ODR_416HZ,
    INCLINOMETER2_ODR_833HZ,
    INCLINOMETER2_ODR_BIT_MASK = 0xF0

} inclinometer2_odr_t;

/**
 * @brief Inclinometer 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    INCLINOMETER2_OK = 0,
    INCLINOMETER2_ERROR = -1

} inclinometer2_return_value_t;

/*!
 * @addtogroup inclinometer2 Inclinometer 2 Click Driver
 * @brief API for configuring and manipulating Inclinometer 2 Click driver.
 * @{
 */

/**
 * @brief Inclinometer 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #inclinometer2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void inclinometer2_cfg_setup ( inclinometer2_cfg_t *cfg );

/**
 * @brief Inclinometer 2 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #inclinometer2_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #inclinometer2_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void inclinometer2_drv_interface_selection ( inclinometer2_cfg_t *cfg, inclinometer2_drv_t drv_sel );

/**
 * @brief Inclinometer 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #inclinometer2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer2_init ( inclinometer2_t *ctx, inclinometer2_cfg_t *cfg );

/**
 * @brief Inclinometer 2 default configuration function.
 * @details This function executes a default configuration of Inclinometer 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t inclinometer2_default_cfg ( inclinometer2_t *ctx );

/**
 * @brief Inclinometer 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer2_generic_write ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Inclinometer 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer2_generic_read ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Inclinometer 2 write register function.
 * @details This function writes a data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer2_write_register ( inclinometer2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Inclinometer 2 read register function.
 * @details This function reads data from the selected register.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer2_read_register ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Inclinometer 2 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer2_check_communication ( inclinometer2_t *ctx );

/**
 * @brief Inclinometer 2 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
uint8_t inclinometer2_get_int_pin ( inclinometer2_t *ctx );

/**
 * @brief Inclinometer 2 set fsr and odr function.
 * @details This function sets the accel full-scale range (FSR) and output data rate (ODR) bits in CTRL1_XL register.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @param[in] fsr : Accel full-scale range bits setting.
 * See #inclinometer2_fsr_t enum definition for detailed explanation.
 * @param[in] odr : Output data rate bits setting.
 * See #inclinometer2_odr_t enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer2_set_fsr_and_odr ( inclinometer2_t *ctx, inclinometer2_fsr_t fsr, inclinometer2_odr_t odr );

/**
 * @brief Inclinometer 2 get accel function.
 * @details This function checks if the accel data is ready and than reads the accel X and Y axis in mg.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @param[out] x_axis : Accel X-axis data in mg.
 * @param[out] y_axis : Accel Y-axis data in mg.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer2_get_accel ( inclinometer2_t *ctx, float *x_axis, float *y_axis );

/**
 * @brief Inclinometer 2 get temperature function.
 * @details This function checks if the temperature data is ready and than reads the temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t inclinometer2_get_temperature ( inclinometer2_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // INCLINOMETER2_H

/*! @} */ // inclinometer2

// ------------------------------------------------------------------------ END
