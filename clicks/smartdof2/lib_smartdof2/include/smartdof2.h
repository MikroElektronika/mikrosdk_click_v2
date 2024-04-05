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
 * @file smartdof2.h
 * @brief This file contains API for Smart DOF 2 Click Driver.
 */

#ifndef SMARTDOF2_H
#define SMARTDOF2_H

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
 * @addtogroup smartdof2 Smart DOF 2 Click Driver
 * @brief API for configuring and manipulating Smart DOF 2 Click driver.
 * @{
 */

/**
 * @defgroup smartdof2_reg Smart DOF 2 Registers List
 * @brief List of registers of Smart DOF 2 Click driver.
 */

/**
 * @addtogroup smartdof2_reg
 * @{
 */

/**
 * @brief Smart DOF 2 description register.
 * @details Specified register for description of Smart DOF 2 Click driver.
 */
#define SMARTDOF2_REG_FUNC_CFG_ACCESS             0x01
#define SMARTDOF2_REG_PIN_CTRL                    0x02
#define SMARTDOF2_REG_IF_CFG                      0x03
#define SMARTDOF2_REG_S4S_TPH_L                   0x04
#define SMARTDOF2_REG_S4S_TPH_H                   0x05
#define SMARTDOF2_REG_S4S_RR                      0x06
#define SMARTDOF2_REG_FIFO_CTRL1                  0x07
#define SMARTDOF2_REG_FIFO_CTRL2                  0x08
#define SMARTDOF2_REG_FIFO_CTRL3                  0x09
#define SMARTDOF2_REG_FIFO_CTRL4                  0x0A
#define SMARTDOF2_REG_COUNTER_BDR_REG1            0x0B
#define SMARTDOF2_REG_COUNTER_BDR_REG2            0x0C
#define SMARTDOF2_REG_INT1_CTRL                   0x0D
#define SMARTDOF2_REG_INT2_CTRL                   0x0E
#define SMARTDOF2_REG_WHO_AM_I                    0x0F
#define SMARTDOF2_REG_CTRL1                       0x10
#define SMARTDOF2_REG_CTRL2                       0x11
#define SMARTDOF2_REG_CTRL3                       0x12
#define SMARTDOF2_REG_CTRL4                       0x13
#define SMARTDOF2_REG_CTRL5                       0x14
#define SMARTDOF2_REG_CTRL6                       0x15
#define SMARTDOF2_REG_CTRL7                       0x16
#define SMARTDOF2_REG_CTRL8                       0x17
#define SMARTDOF2_REG_CTRL9                       0x18
#define SMARTDOF2_REG_CTRL10                      0x19
#define SMARTDOF2_REG_CTRL_STATUS                 0x1A
#define SMARTDOF2_REG_FIFO_STATUS1                0x1B
#define SMARTDOF2_REG_FIFO_STATUS2                0x1C
#define SMARTDOF2_REG_ALL_INT_SRC                 0x1D
#define SMARTDOF2_REG_STATUS_REG                  0x1E
#define SMARTDOF2_REG_OUT_TEMP_L                  0x20
#define SMARTDOF2_REG_OUT_TEMP_H                  0x21
#define SMARTDOF2_REG_OUTX_L_G                    0x22
#define SMARTDOF2_REG_OUTX_H_G                    0x23
#define SMARTDOF2_REG_OUTY_L_G                    0x24
#define SMARTDOF2_REG_OUTY_H_G                    0x25
#define SMARTDOF2_REG_OUTZ_L_G                    0x26
#define SMARTDOF2_REG_OUTZ_H_G                    0x27
#define SMARTDOF2_REG_OUTX_L_A                    0x28
#define SMARTDOF2_REG_OUTX_H_A                    0x29
#define SMARTDOF2_REG_OUTY_L_A                    0x2A
#define SMARTDOF2_REG_OUTY_H_A                    0x2B
#define SMARTDOF2_REG_OUTZ_L_A                    0x2C
#define SMARTDOF2_REG_OUTZ_H_A                    0x2D
#define SMARTDOF2_REG_UI_OUTX_L_G_OIS_EIS         0x2E
#define SMARTDOF2_REG_UI_OUTX_H_G_OIS_EIS         0x2F
#define SMARTDOF2_REG_UI_OUTY_L_G_OIS_EIS         0x30
#define SMARTDOF2_REG_UI_OUTY_H_G_OIS_EIS         0x31
#define SMARTDOF2_REG_UI_OUTZ_L_G_OIS_EIS         0x32
#define SMARTDOF2_REG_UI_OUTZ_H_G_OIS_EIS         0x33
#define SMARTDOF2_REG_UI_OUTX_L_A_OIS_DUALC       0x34
#define SMARTDOF2_REG_UI_OUTX_H_A_OIS_DUALC       0x35
#define SMARTDOF2_REG_UI_OUTY_L_A_OIS_DUALC       0x36
#define SMARTDOF2_REG_UI_OUTY_H_A_OIS_DUALC       0x37
#define SMARTDOF2_REG_UI_OUTZ_L_A_OIS_DUALC       0x38
#define SMARTDOF2_REG_UI_OUTZ_H_A_OIS_DUALC       0x39
#define SMARTDOF2_REG_AH_QVAR_OUT_L               0x3A
#define SMARTDOF2_REG_AH_QVAR_OUT_H               0x3B
#define SMARTDOF2_REG_TIMESTAMP0                  0x40
#define SMARTDOF2_REG_TIMESTAMP1                  0x41
#define SMARTDOF2_REG_TIMESTAMP2                  0x42
#define SMARTDOF2_REG_TIMESTAMP3                  0x43
#define SMARTDOF2_REG_UI_STATUS_REG_OIS           0x44
#define SMARTDOF2_REG_WAKE_UP_SRC                 0x45
#define SMARTDOF2_REG_TAP_SRC                     0x46
#define SMARTDOF2_REG_D6D_SRC                     0x47
#define SMARTDOF2_REG_STATUS_MASTER_MAINPAGE      0x48
#define SMARTDOF2_REG_EMB_FUNC_STATUS_MAINPAGE    0x49
#define SMARTDOF2_REG_FSM_STATUS_MAINPAGE         0x4A
#define SMARTDOF2_REG_MLC_STATUS_MAINPAGE         0x4B
#define SMARTDOF2_REG_INTERNAL_FREQ               0x4F
#define SMARTDOF2_REG_FUNCTIONS_ENABLE            0x50
#define SMARTDOF2_REG_DEN                         0x51
#define SMARTDOF2_REG_INACTIVITY_DUR              0x54
#define SMARTDOF2_REG_INACTIVITY_THS              0x55
#define SMARTDOF2_REG_TAP_CFG0                    0x56
#define SMARTDOF2_REG_TAP_CFG1                    0x57
#define SMARTDOF2_REG_TAP_CFG2                    0x58
#define SMARTDOF2_REG_TAP_THS_6D                  0x59
#define SMARTDOF2_REG_INT_DUR2                    0x5A
#define SMARTDOF2_REG_WAKE_UP_THS                 0x5B
#define SMARTDOF2_REG_WAKE_UP_DUR                 0x5C
#define SMARTDOF2_REG_FREE_FALL                   0x5D
#define SMARTDOF2_REG_MD1_CFG                     0x5E
#define SMARTDOF2_REG_MD2_CFG                     0x5F
#define SMARTDOF2_REG_S4S_ST_CMD_CODE             0x60
#define SMARTDOF2_REG_S4S_DT_REG                  0x61
#define SMARTDOF2_REG_EMB_FUNC_CFG                0x63
#define SMARTDOF2_REG_UI_HANDSHAKE_CTRL           0x64
#define SMARTDOF2_REG_UI_SPI2_SHARED_0            0x65
#define SMARTDOF2_REG_UI_SPI2_SHARED_1            0x66
#define SMARTDOF2_REG_UI_SPI2_SHARED_2            0x67
#define SMARTDOF2_REG_UI_SPI2_SHARED_3            0x68
#define SMARTDOF2_REG_UI_SPI2_SHARED_4            0x69
#define SMARTDOF2_REG_UI_SPI2_SHARED_5            0x6A
#define SMARTDOF2_REG_CTRL_EIS                    0x6B
#define SMARTDOF2_REG_UI_INT_OIS                  0x6F
#define SMARTDOF2_REG_UI_CTRL1_OIS                0x70
#define SMARTDOF2_REG_UI_CTRL2_OIS                0x71
#define SMARTDOF2_REG_UI_CTRL3_OIS                0x72
#define SMARTDOF2_REG_X_OFS_USR                   0x73
#define SMARTDOF2_REG_Y_OFS_USR                   0x74
#define SMARTDOF2_REG_Z_OFS_USR                   0x75
#define SMARTDOF2_REG_FIFO_DATA_OUT_TAG           0x78
#define SMARTDOF2_REG_FIFO_DATA_OUT_X_L           0x79
#define SMARTDOF2_REG_FIFO_DATA_OUT_X_H           0x7A
#define SMARTDOF2_REG_FIFO_DATA_OUT_Y_L           0x7B
#define SMARTDOF2_REG_FIFO_DATA_OUT_Y_H           0x7C
#define SMARTDOF2_REG_FIFO_DATA_OUT_Z_L           0x7D
#define SMARTDOF2_REG_FIFO_DATA_OUT_Z_H           0x7E


/*! @} */ // smartdof2_reg

/**
 * @defgroup smartdof2_set Smart DOF 2 Registers Settings
 * @brief Settings for registers of Smart DOF 2 Click driver.
 */

/**
 * @addtogroup smartdof2_set
 * @{
 */

/**
 * @brief Smart DOF 2 SMARTDOF2_REG_WHO_AM_I register value.
 * @details Specified SMARTDOF2_REG_WHO_AM_I register value for description of Smart DOF 2 Click driver.
 */
#define SMARTDOF2_DEVICE_ID                       0x70

/**
 * @brief Smart DOF 2 SMARTDOF2_REG_CTRL3 register value.
 * @details Specified SMARTDOF2_REG_CTRL3 register value for description of Smart DOF 2 Click driver.
 */
#define SMARTDOF2_IF_INC_DISABLE                  0x00
#define SMARTDOF2_IF_INC_ENABLE                   0x04
#define SMARTDOF2_IF_INC_BIT_MASK                 0xFB
#define SMARTDOF2_BDU_DISABLE                     0x00
#define SMARTDOF2_BDU_ENABLE                      0x40
#define SMARTDOF2_BDU_BIT_MASK                    0xBF

/**
 * @brief Smart DOF 2 SMARTDOF2_REG_FIFO_CTRL4 register value.
 * @details Specified SMARTDOF2_REG_FIFO_CTRL4 register value for description of Smart DOF 2 Click driver.
 */
#define SMARTDOF2_FIFO_MODE_BYPASS                0x00
#define SMARTDOF2_FIFO_MODE_FIFO                  0x01
#define SMARTDOF2_FIFO_MODE_STREAM_WTM_TO_FULL    0x02
#define SMARTDOF2_FIFO_MODE_STREAM_TO_FIFO        0x03
#define SMARTDOF2_FIFO_MODE_BYPASS_TO_STREAM      0x04
#define SMARTDOF2_FIFO_MODE_STREAM                0x06
#define SMARTDOF2_FIFO_MODE_BYPASS_TO_FIFO        0x07
#define SMARTDOF2_FIFO_MODE_BIT_MASK              0xF8

/**
 * @brief Smart DOF 2 SMARTDOF2_REG_CTRL1 register value.
 * @details Specified SMARTDOF2_REG_CTRL1 register value for description of Smart DOF 2 Click driver.
 */
#define SMARTDOF2_ODR_OFF                         0x00
#define SMARTDOF2_ODR_AT_1Hz875                   0x01
#define SMARTDOF2_ODR_AT_7Hz5                     0x02
#define SMARTDOF2_ODR_AT_15Hz                     0x03
#define SMARTDOF2_ODR_AT_30Hz                     0x04
#define SMARTDOF2_ODR_AT_60Hz                     0x05
#define SMARTDOF2_ODR_AT_120Hz                    0x06
#define SMARTDOF2_ODR_AT_240Hz                    0x07
#define SMARTDOF2_ODR_AT_480Hz                    0x08
#define SMARTDOF2_ODR_AT_960Hz                    0x09
#define SMARTDOF2_ODR_AT_1920Hz                   0x0A
#define SMARTDOF2_ODR_AT_3840Hz                   0x0B
#define SMARTDOF2_ODR_AT_7680Hz                   0x0C
#define SMARTDOF2_ODR_BIT_MASK                    0xF0

/**
 * @brief Smart DOF 2 SMARTDOF2_REG_CTRL2/8 register value.
 * @details Specified SMARTDOF2_REG_CTRL2/8 register value for description of Smart DOF 2 Click driver.
 */
#define SMARTDOF2_XL_FULL_SCALE_2g                0x00
#define SMARTDOF2_XL_FULL_SCALE_4g                0x01
#define SMARTDOF2_XL_FULL_SCALE_8g                0x02
#define SMARTDOF2_XL_FULL_SCALE_16g               0x03
#define SMARTDOF2_XL_FULL_SCALE_BIT_MASK          0xF8

/**
 * @brief Smart DOF 2 SMARTDOF2_REG_CTRL6 register value.
 * @details Specified SMARTDOF2_REG_CTRL6 register value for description of Smart DOF 2 Click driver.
 */
#define SMARTDOF2_GY_FULL_SCALE_125dps            0x00
#define SMARTDOF2_GY_FULL_SCALE_250dps            0x01
#define SMARTDOF2_GY_FULL_SCALE_500dps            0x02
#define SMARTDOF2_GY_FULL_SCALE_1000dps           0x03
#define SMARTDOF2_GY_FULL_SCALE_2000dps           0x04
#define SMARTDOF2_GY_FULL_SCALE_4000dps           0x0C
#define SMARTDOF2_GY_FULL_SCALE_BIT_MASK          0xF0

/**
 * @brief Smart DOF 2 accel sensitivity data value.
 * @details Specified accelerometer sensitivity value for description of Smart DOF 2 Click driver.
 */
#define SMARTDOF2_ACC_SENSITIVITY_FS_2g            0.061
#define SMARTDOF2_ACC_SENSITIVITY_FS_4g            0.122
#define SMARTDOF2_ACC_SENSITIVITY_FS_8g            0.244
#define SMARTDOF2_ACC_SENSITIVITY_FS_16g           0.488

/**
 * @brief Smart DOF 2 gyro sensitivity data value.
 * @details Specified gyroscope sensitivity value for description of Smart DOF 2 Click driver.
 */
#define SMARTDOF2_GYRO_SENSITIVITY_FS_125dps       4.375
#define SMARTDOF2_GYRO_SENSITIVITY_FS_250dps       8.750
#define SMARTDOF2_GYRO_SENSITIVITY_FS_500dps      17.500
#define SMARTDOF2_GYRO_SENSITIVITY_FS_1000dps     35.000
#define SMARTDOF2_GYRO_SENSITIVITY_FS_2000dps     70.000
#define SMARTDOF2_GYRO_SENSITIVITY_FS_4000dps    140.000

/**
 * @brief Smart DOF 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Smart DOF 2 Click driver.
 */
#define SMARTDOF2_DEVICE_ADDRESS_GND              0x6A
#define SMARTDOF2_DEVICE_ADDRESS_VCC              0x6B

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b smartdof2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SMARTDOF2_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define SMARTDOF2_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // smartdof2_set

/**
 * @defgroup smartdof2_map Smart DOF 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Smart DOF 2 Click driver.
 */

/**
 * @addtogroup smartdof2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart DOF 2 Click to the selected MikroBUS.
 */
#define SMARTDOF2_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // smartdof2_map
/*! @} */ // smartdof2

/**
 * @brief Smart DOF 2 Click driver selector.
 * @details Selects target driver interface of Smart DOF 2 Click driver.
 */
typedef enum
{
    SMARTDOF2_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    SMARTDOF2_DRV_SEL_I2C       /**< I2C driver descriptor. */

} smartdof2_drv_t;

/**
 * @brief Smart DOF 2 Click driver interface.
 * @details Definition of driver interface of Smart DOF 2 Click driver.
 */
typedef err_t ( *smartdof2_master_io_t )( struct smartdof2_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Smart DOF 2 Click context object.
 * @details Context object definition of Smart DOF 2 Click driver.
 */
typedef struct smartdof2_s
{
    digital_in_t int_pin;   /**< Interrupt pin. */

    i2c_master_t i2c;       /**< I2C driver object. */
    spi_master_t spi;       /**< SPI driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;      /**< Chip select pin descriptor (used for SPI driver). */
    smartdof2_drv_t drv_sel;       /**< Master driver interface selector. */

    smartdof2_master_io_t write_f;    /**< Master write function. */
    smartdof2_master_io_t read_f;     /**< Master read function. */

} smartdof2_t;

/**
 * @brief Smart DOF 2 Click configuration object.
 * @details Configuration object definition of Smart DOF 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int_pin;    /**< Interrupt pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */

    smartdof2_drv_t drv_sel;    /**< Master driver interface selector. */

} smartdof2_cfg_t;

/**
 * @brief Smart DOF 2 Click axis raw data structure object.
 * @details Axis raw data object definition of Smart DOF 2 Click driver.
 */
typedef struct 
{
    int16_t x;
    int16_t y;
    int16_t z;

} smartdof2_axis_data_t;

/**
 * @brief Smart DOF 2 Click sensor axes structure object.
 * @details Sensor axes object definition of Smart DOF 2 Click driver.
 */
typedef struct 
{
    float x;
    float y;
    float z;

} smartdof2_axis_t;

/**
 * @brief Smart DOF 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTDOF2_OK = 0,
    SMARTDOF2_ERROR = -1

} smartdof2_return_value_t;

/*!
 * @addtogroup smartdof2 Smart DOF 2 Click Driver
 * @brief API for configuring and manipulating Smart DOF 2 Click driver.
 * @{
 */

/**
 * @brief Smart DOF 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartdof2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartdof2_cfg_setup ( smartdof2_cfg_t *cfg );

/**
 * @brief Smart DOF 2 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #smartdof2_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #smartdof2_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void smartdof2_drv_interface_selection ( smartdof2_cfg_t *cfg, smartdof2_drv_t drv_sel );

/**
 * @brief Smart DOF 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartdof2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_init ( smartdof2_t *ctx, smartdof2_cfg_t *cfg );

/**
 * @brief Smart DOF 2 default configuration function.
 * @details This function executes a default configuration of Smart DOF 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartdof2_default_cfg ( smartdof2_t *ctx );

/**
 * @brief Smart DOF 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_generic_write ( smartdof2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart DOF 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_generic_read ( smartdof2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smart DOF 2 get device ID function.
 * @details This function reads a device ID value
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[out] device_id : Device ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_get_device_id ( smartdof2_t *ctx, uint8_t *device_id );

/**
 * @brief Smart DOF 2 enable auto increment function.
 * @details This function enable automatically incremented during 
 * a multiple byte access with a serial interface
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_enable_auto_increment ( smartdof2_t *ctx );

/**
 * @brief Smart DOF 2 enable block data update function.
 * @details This function enable block data, 
 * output registers are not updated until LSB and MSB have been read,
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_enable_block_data_update ( smartdof2_t *ctx );

/**
 * @brief Smart DOF 2 set FIFO mode function.
 * @details This function selects the FIFO mode
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[in] fifo_mode : FIFO mode selection
 *         @li @c  0x00 (SMARTDOF2_FIFO_MODE_BYPASS)             - Bypass mode, FIFO disabled,
 *         @li @c  0x01 (SMARTDOF2_FIFO_MODE_FIFO)               - FIFO mode,
 *         @li @c  0x02 (SMARTDOF2_FIFO_MODE_STREAM_WTM_TO_FULL) - ContinuousWTM,
 *         @li @c  0x03 (SMARTDOF2_FIFO_MODE_STREAM_TO_FIFO)     - Continuous-to-FIFO mode,
 *         @li @c  0x04 (SMARTDOF2_FIFO_MODE_BYPASS_TO_STREAM)   - Bypass-to-continuous mode,
 *         @li @c  0x06 (SMARTDOF2_FIFO_MODE_STREAM)             - Continuous mode,
 *         @li @c  0x07 (SMARTDOF2_FIFO_MODE_BYPASS_TO_FIFO)     - Bypass-to-FIFO mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_set_fifo_mode ( smartdof2_t *ctx, uint8_t fifo_mode );

/**
 * @brief Smart DOF 2 set accel data rate function.
 * @details This function selects the accelerometer data rate
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[in] data_rate : Accelerometer ODR selection
 *         @li @c  0x00 (SMARTDOF2_ODR_OFF)       - Power-down,
 *         @li @c  0x01 (SMARTDOF2_ODR_AT_1Hz875) - 1.875 Hz (low-power mode),
 *         @li @c  0x02 (SMARTDOF2_ODR_AT_7Hz5)   - 7.5Hz (high-performance, normal mode),
 *         @li @c  0x03 (SMARTDOF2_ODR_AT_15Hz)   - 15Hz (low-power, high-performance, normal mode),
 *         @li @c  0x04 (SMARTDOF2_ODR_AT_30Hz)   - 30Hz (low-power, high-performance, normal mode),
 *         @li @c  0x05 (SMARTDOF2_ODR_AT_60Hz)   - 60Hz (low-power, high-performance, normal mode),
 *         @li @c  0x06 (SMARTDOF2_ODR_AT_120Hz)  - 120Hz (low-power, high-performance, normal mode),
 *         @li @c  0x07 (SMARTDOF2_ODR_AT_120Hz)  - 240Hz (low-power, high-performance, normal mode),
 *         @li @c  0x08 (SMARTDOF2_ODR_AT_120Hz)  - 480Hz (high-performance, normal mode),
 *         @li @c  0x09 (SMARTDOF2_ODR_AT_120Hz)  - 960Hz (high-performance, normal mode),
 *         @li @c  0x0A (SMARTDOF2_ODR_AT_120Hz)  - 1.92kHz (high-performance, normal mode),
 *         @li @c  0x0B (SMARTDOF2_ODR_AT_120Hz)  - 3.84kHz (high-performance mode),
 *         @li @c  0x0C (SMARTDOF2_ODR_AT_120Hz)  - 7.68kHz (high-performance mode).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_set_acc_data_rate ( smartdof2_t *ctx, uint8_t data_rate );

/**
 * @brief Smart DOF 2 get full-scale accel range function.
 * @details This function reads selected the full-scale acceleration range
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[out] data_scale : Accelerometer full-scale selection. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_get_acc_full_scale ( smartdof2_t *ctx, uint8_t *data_scale );

/**
 * @brief Smart DOF 2 set full-scale accel range function.
 * @details This function selects the full-scale acceleration range
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[in] data_scale : Accelerometer full-scale selection
 *         @li @c  0x00 (SMARTDOF2_XL_FULL_SCALE_2g)  - ±2g,
 *         @li @c  0x01 (SMARTDOF2_XL_FULL_SCALE_4g)  - ±4g,
 *         @li @c  0x02 (SMARTDOF2_XL_FULL_SCALE_8g)  - ±8g,
 *         @li @c  0x03 (SMARTDOF2_XL_FULL_SCALE_16g) - ±16g.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_set_acc_full_scale ( smartdof2_t *ctx, uint8_t data_scale );

/**
 * @brief Smart DOF 2 set gyro data rate function.
 * @details This function  selects the gyroscope data rate
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[in] data_rate : Accelerometer full-scale selection
 *         @li @c  0x00 (SMARTDOF2_XL_FULL_SCALE_2g)  - ±2g,
 *         @li @c  0x01 (SMARTDOF2_XL_FULL_SCALE_4g)  - ±4g,
 *         @li @c  0x02 (SMARTDOF2_XL_FULL_SCALE_8g)  - ±8g,
 *         @li @c  0x03 (SMARTDOF2_XL_FULL_SCALE_16g) - ±16g.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_set_gyro_data_rate ( smartdof2_t *ctx, uint8_t data_rate );

/**
 * @brief Smart DOF 2 get full-scale gyro range function.
 * @details This function reads selected the full-scale gyroscope range
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[out] data_scale : Gyroscope full-scale selection. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_get_gyro_full_scale ( smartdof2_t *ctx, uint8_t *data_scale );

/**
 * @brief Smart DOF 2 set full-scale gyro range function.
 * @details This function selects the full-scale gyroscope range
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[in] data_scale : Accelerometer full-scale selection
 *         @li @c  0x00 (SMARTDOF2_XL_FULL_SCALE_2g)  - ±2g,
 *         @li @c  0x01 (SMARTDOF2_XL_FULL_SCALE_4g)  - ±4g,
 *         @li @c  0x02 (SMARTDOF2_XL_FULL_SCALE_8g)  - ±8g,
 *         @li @c  0x03 (SMARTDOF2_XL_FULL_SCALE_16g) - ±16g.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_set_gyro_full_scale ( smartdof2_t *ctx, uint8_t data_scale );

/**
 * @brief Smart DOF 2 get accel data function.
 * @details This function reads the accelerometer raw data 
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[out] acc_axis : Accelerometer raw data object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_get_acc_axis_data ( smartdof2_t *ctx, smartdof2_axis_data_t *acc_axis );

/**
 * @brief Smart DOF 2 get gyro data function.
 * @details This function reads the gyroscope raw data 
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[out] gyro_axis : Gyroscope raw data object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_get_gyro_axis_data ( smartdof2_t *ctx, smartdof2_axis_data_t *gyro_axis );

/**
 * @brief Smart DOF 2 get accel sensitivity function.
 * @details This function reads the accelerometer sensitivity data 
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[out] sensitivity : Accelerometer sensitivity data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_get_acc_sensitivity ( smartdof2_t *ctx, float *sensitivity );

/**
 * @brief Smart DOF 2 get gyro sensitivity function.
 * @details This function reads the gyroscope sensitivity data 
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[out] sensitivity : Gyroscope sensitivity data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_get_gyro_sensitivity ( smartdof2_t *ctx, float *sensitivity );

/**
 * @brief Smart DOF 2 get accel sensor axes function.
 * @details This function reads the accelerometer sensor axes data 
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[out] acc_axis : Linear acceleration output data object (mg).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_get_acc_axis ( smartdof2_t *ctx, smartdof2_axis_t *acc_axis );

/**
 * @brief Smart DOF 2 get gyro sensor axes function.
 * @details This function reads the gyroscope sensor axes data 
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[out] gyro_axis : Angular rate output data object (dps).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_get_gyro_axis ( smartdof2_t *ctx, smartdof2_axis_t *gyro_axis );

/**
 * @brief Smart DOF 2 get temperature data function.
 * @details This function reads the temperature raw data 
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[out] temp_raw : Temperature raw data (16-bit word in two’s complement).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof2_get_temperature_raw ( smartdof2_t *ctx, int16_t *temp_raw );

/**
 * @brief Smart DOF 2 get temperature function.
 * @details This function reads the temperature data 
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @param[out] temperature : Temperature (degrees Celsius).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Typical specifications are not guaranteed.
 * The output of the temperature sensor is 0 LSB (typ.) at 25 °C.
 */
err_t smartdof2_get_temperature ( smartdof2_t *ctx, float *temperature );

/**
 * @brief Smart DOF 2 get interrupt function.
 * @details This function get states of the Interrupt ( INT ) pin
 * of the LSM6DSV16X, High-performance 6-axis IMU with sensor fusion, ASC, MLC, Qvar, OIS/EIS paths
 * on the Smart DOF 2 click board™.
 * @param[in] ctx : Click context object.
 * See #smartdof2_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t smartdof2_get_int_pin ( smartdof2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SMARTDOF2_H

/*! @} */ // smartdof2

// ------------------------------------------------------------------------ END
