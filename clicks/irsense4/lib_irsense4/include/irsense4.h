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
 * @file irsense4.h
 * @brief This file contains API for IR Sense 4 Click Driver.
 */

#ifndef IRSENSE4_H
#define IRSENSE4_H

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
 * @addtogroup irsense4 IR Sense 4 Click Driver
 * @brief API for configuring and manipulating IR Sense 4 Click driver.
 * @{
 */

/**
 * @defgroup irsense4_reg IR Sense 4 Registers List
 * @brief List of registers of IR Sense 4 Click driver.
 */

/**
 * @addtogroup irsense4_reg
 * @{
 */

/**
 * @brief IR Sense 4 description register.
 * @details Specified register for description of IR Sense 4 Click driver.
 */

#define IRSENSE4_REG_LPF1                    0x0C
#define IRSENSE4_REG_LPF2                    0x0D
#define IRSENSE4_REG_WHO_AM_I                0x0F
#define IRSENSE4_REG_AVG_TRIM                0x10
#define IRSENSE4_REG_CTRL0                   0x17
#define IRSENSE4_REG_SENS_DATA               0x1D
#define IRSENSE4_REG_CTRL1                   0x20
#define IRSENSE4_REG_CTRL2                   0x21
#define IRSENSE4_REG_CTRL3                   0x22
#define IRSENSE4_REG_STATUS                  0x23
#define IRSENSE4_REG_FUNC_STATUS             0x25
#define IRSENSE4_REG_TOBJECT_L               0x26
#define IRSENSE4_REG_TOBJECT_H               0x27
#define IRSENSE4_REG_TAMBIENT_L              0x28
#define IRSENSE4_REG_TAMBIENT_H              0x29
#define IRSENSE4_REG_TOBJ_COMP_L             0x38
#define IRSENSE4_REG_TOBJ_COMP_H             0x39
#define IRSENSE4_REG_TPRESENCE_L             0x3A
#define IRSENSE4_REG_TPRESENCE_H             0x3B
#define IRSENSE4_REG_TMOTION_L               0x3C
#define IRSENSE4_REG_TMOTION_H               0x3D
#define IRSENSE4_REG_TAMB_SHOCK_L            0x3E
#define IRSENSE4_REG_TAMB_SHOCK_H            0x3F

/**
 * @brief IR Sense 4 description embedded register.
 * @details Specified embedded register for description of IR Sense 4 Click driver.
 */
#define IRSENSE4_REG_EMB_FUNC_CFG_ADDR       0x08
#define IRSENSE4_REG_EMB_FUNC_CFG_DATA       0x09
#define IRSENSE4_REG_EMB_PAGE_RW             0x11
#define IRSENSE4_REG_EMB_PRESENCE_THS_L      0x20
#define IRSENSE4_REG_EMB_PRESENCE_THS_H      0x21
#define IRSENSE4_REG_EMB_MOTION_THS_L        0x22
#define IRSENSE4_REG_EMB_MOTION_THS_H        0x23
#define IRSENSE4_REG_EMB_TAMB_SHOCK_THS_L    0x24
#define IRSENSE4_REG_EMB_TAMB_SHOCK_THS_H    0x25
#define IRSENSE4_REG_EMB_HYST_MOTION         0x26
#define IRSENSE4_REG_EMB_HYST_PRESENCE       0x27
#define IRSENSE4_REG_EMB_ALGO_CONFIG         0x28
#define IRSENSE4_REG_EMB_HYST_TAMB_SHOCK     0x29
#define IRSENSE4_REG_EMB_RESET_ALGO          0x2A

/*! @} */ // irsense4_reg

/**
 * @defgroup irsense4_set IR Sense 4 Registers Settings
 * @brief Settings for registers of IR Sense 4 Click driver.
 */

/**
 * @addtogroup irsense4_set
 * @{
 */

/**
 * @brief IR Sense 4 description of low-pass filter configuration for motion and presence detection.
 * @details Specified setting low-pass filter configuration for motion and presence detection 
 * of IR Sense 4 Click driver.
 */
#define IRSENSE4_LPF1_M_ODR_9                0x00
#define IRSENSE4_LPF1_M_ODR_20               0x01
#define IRSENSE4_LPF1_M_ODR_50               0x02
#define IRSENSE4_LPF1_M_ODR_100              0x03
#define IRSENSE4_LPF1_M_ODR_200              0x04
#define IRSENSE4_LPF1_M_ODR_400              0x05
#define IRSENSE4_LPF1_M_ODR_800              0x06
#define IRSENSE4_LPF1_M_BIT_MASK             0x07
#define IRSENSE4_LPF1_P_M_ODR_9              0x00
#define IRSENSE4_LPF1_P_M_ODR_20             0x08
#define IRSENSE4_LPF1_P_M_ODR_50             0x10
#define IRSENSE4_LPF1_P_M_ODR_100            0x18
#define IRSENSE4_LPF1_P_M_ODR_200            0x20
#define IRSENSE4_LPF1_P_M_ODR_400            0x28
#define IRSENSE4_LPF1_P_M_ODR_800            0x30

/**
 * @brief IR Sense 4 description of low-pass filter configuration 
 * for ambient temperature and presence detection.
 * @details Specified setting low-pass filter configuration for ambient temperature and presence detection 
 * of IR Sense 4 Click driver.
 */
#define IRSENSE4_LPF2_A_T_ODR_9              0x00
#define IRSENSE4_LPF2_A_T_ODR_20             0x01
#define IRSENSE4_LPF2_A_T_ODR_50             0x02
#define IRSENSE4_LPF2_A_T_ODR_100            0x03
#define IRSENSE4_LPF2_A_T_ODR_200            0x04
#define IRSENSE4_LPF2_A_T_ODR_400            0x05
#define IRSENSE4_LPF2_A_T_ODR_800            0x06
#define IRSENSE4_LPF2_A_T_BIT_MASK           0x07
#define IRSENSE4_LPF2_P_ODR_9                0x00
#define IRSENSE4_LPF2_P_ODR_20               0x08
#define IRSENSE4_LPF2_P_ODR_50               0x10
#define IRSENSE4_LPF2_P_ODR_100              0x18
#define IRSENSE4_LPF2_P_ODR_200              0x20
#define IRSENSE4_LPF2_P_ODR_400              0x28
#define IRSENSE4_LPF2_P_ODR_800              0x30
#define IRSENSE4_LPF2_P_BIT_MASK             0x38

/**
 * @brief IR Sense 4 description of device identification value.
 * @details Specified setting device identification – Who am I value
 * of IR Sense 4 Click driver.
 */
#define IRSENSE4_DEVICE_ID                   0xD3

/**
 * @brief IR Sense 4 description of selection number of averages 
 * for ambient and object temperature.
 * @details Specified setting description of selection number 
 * of averages for ambient and object temperature of IR Sense 4 Click driver.
 */
#define IRSENSE4_AVG_TRIM_TMOS_2             0x00
#define IRSENSE4_AVG_TRIM_TMOS_8             0x01
#define IRSENSE4_AVG_TRIM_TMOS_32            0x02
#define IRSENSE4_AVG_TRIM_TMOS_128           0x03
#define IRSENSE4_AVG_TRIM_TMOS_256           0x04
#define IRSENSE4_AVG_TRIM_TMOS_512           0x05
#define IRSENSE4_AVG_TRIM_TMOS_1024          0x06
#define IRSENSE4_AVG_TRIM_TMOS_2048          0x07
#define IRSENSE4_AVG_TRIM_TMOS_BIT_MASK      0x07
#define IRSENSE4_AVG_TRIM_T_8                0x00
#define IRSENSE4_AVG_TRIM_T_4                0x10
#define IRSENSE4_AVG_TRIM_T_2                0x20
#define IRSENSE4_AVG_TRIM_T_1                0x30
#define IRSENSE4_AVG_TRIM_T_BIT_MASK         0x30

/**
 * @brief IR Sense 4 description of temperature gain mode.
 * @details Specified setting description of temperature gain mode of IR Sense 4 Click driver.
 */
#define IRSENSE4_CTRL0_GAIN_1                0x00
#define IRSENSE4_CTRL0_GAIN_2                0x10
#define IRSENSE4_CTRL0_GAIN_3                0x20
#define IRSENSE4_CTRL0_GAIN_4                0x30
#define IRSENSE4_CTRL0_GAIN_5                0x40
#define IRSENSE4_CTRL0_GAIN_6                0x50
#define IRSENSE4_CTRL0_GAIN_7                0x60
#define IRSENSE4_CTRL0_GAIN_8                0x70
#define IRSENSE4_CTRL0_DEFAULT               0x81

/**
 * @brief IR Sense 4 description of sensitivity data of the component.
 * @details Specified setting description of sensitivity data 
 * of the component of IR Sense 4 Click driver.
 */
#define IRSENSE4_SENS_DATA_CALC_DEV          16u
#define IRSENSE4_SENS_DATA_MIN               2048u
#define IRSENSE4_SENS_DATA_MAX               6128u

/**
 * @brief IR Sense 4 description of block data update for output and ODR configuration.
 * @details Specified setting description of block data update 
 * for output and ODR configuration of IR Sense 4 Click driver.
 */
#define IRSENSE4_CTRL1_ODR_POWER_DOWN        0x00
#define IRSENSE4_CTRL1_ODR_0_25              0x01
#define IRSENSE4_CTRL1_ODR_0_5               0x02
#define IRSENSE4_CTRL1_ODR_1                 0x03
#define IRSENSE4_CTRL1_ODR_2                 0x04
#define IRSENSE4_CTRL1_ODR_4                 0x05
#define IRSENSE4_CTRL1_ODR_8                 0x06
#define IRSENSE4_CTRL1_ODR_15                0x07
#define IRSENSE4_CTRL1_ODR_30                0x08
#define IRSENSE4_CTRL1_ODR_BIT_MASK          0x0F
#define IRSENSE4_CTRL1_BDU_DIS               0x00
#define IRSENSE4_CTRL1_BDU_EN                0x01

/**
 * @brief IR Sense 4 description of one shot mode.
 * @details Specified setting description of one shot mode of IR Sense 4 Click driver.
 */
#define IRSENSE4_CTRL2_ONE_SHOT_DIS          0x00
#define IRSENSE4_CTRL2_ONE_SHOT_EN           0x01
#define IRSENSE4_CTRL2_F_CFG_ACCESS_DIS      0x00
#define IRSENSE4_CTRL2_F_CFG_ACCESS_EN       0x10

/**
 * @brief IR Sense 4 description of interrupt configuration.
 * @details Specified setting description of interrupt configuration of IR Sense 4 Click driver.
 */
#define IRSENSE4_CTRL3_IEN_HIGH_Z            0x00
#define IRSENSE4_CTRL3_IEN_DRDY              0x01
#define IRSENSE4_CTRL3_IEN_INT_OR            0x02
#define IRSENSE4_CTRL3_IEN_BIT_MASK          0x03
#define IRSENSE4_CTRL3_INT_LATCHED_PLS       0x00
#define IRSENSE4_CTRL3_INT_LATCHED_LAT       0x04
#define IRSENSE4_CTRL3_INT_MSK_T_SHOCK       0x08
#define IRSENSE4_CTRL3_INT_MSK_MOT           0x10
#define IRSENSE4_CTRL3_INT_MSK_PRES          0x20
#define IRSENSE4_CTRL3_PP_OD_PUSH_PULL       0x00
#define IRSENSE4_CTRL3_PP_OD_OPEN_DRAIN      0x04
#define IRSENSE4_CTRL3_INT_H_L_HIGH          0x00
#define IRSENSE4_CTRL3_INT_H_L_LOW           0x80
#define IRSENSE4_CTRL3_BIT_MASK              0x38

/**
 * @brief IR Sense 4 description of status data ready value.
 * @details Specified setting description of status data ready value of IR Sense 4 Click driver.
 */
#define IRSENSE4_STATUS_TAMB_SHOCK_FLAG       0x01
#define IRSENSE4_STATUS_MOT_FLAG              0x02
#define IRSENSE4_STATUS_PRES_FLAG             0x04
#define IRSENSE4_STATUS_DETECT_FLAG           0x07
#define IRSENSE4_STATUS_NOT_DRDY              0x00
#define IRSENSE4_STATUS_DRDY                  0x04

/**
 * @brief IR Sense 4 description of threshold default configuration.
 * @details Specified setting description of hreshold default configuration 
 * of IR Sense 4 Click driver.
 */
#define IRSENSE4_SET_THS_PRESENCE_DEFAULT     5000u
#define IRSENSE4_SET_THS_MOTION_DEFAULT       3000u
#define IRSENSE4_SET_THS_T_SHOCK_DEFAULT      2000u
#define IRSENSE4_SET_THS_MAX                  0x7FFFu

/**
 * @brief IR Sense 4 description of object, ambient and compensated temperature sensitivity values.
 * @details Specified setting description of object, ambient and compensated temperature sensitivity 
 * of IR Sense 4 Click driver.
 */
#define IRSENSE4_SENS_TOBJECT                2000.0f
#define IRSENSE4_SENS_TAMBIENT               100.0f
#define IRSENSE4_SENS_TOBJ_COMP              2000.0f

/**
 * @brief IR Sense 4 description of embedded functions data values.
 * @details Specified setting description of embedded functions data values 
 * of IR Sense 4 Click driver.
 */
#define IRSENSE4_EMB_PAGE_RW_READ_DIS        0x00
#define IRSENSE4_EMB_PAGE_RW_READ_EN         0x20
#define IRSENSE4_EMB_PAGE_RW_WRITE_DIS       0x00
#define IRSENSE4_EMB_PAGE_RW_WRITE_EN        0x40

/**
 * @brief IR Sense 4 device address setting.
 * @details Specified setting for device slave address selection of
 * IR Sense 4 Click driver.
 */
#define IRSENSE4_DEVICE_ADDRESS              0x5A

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b irsense4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define IRSENSE4_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define IRSENSE4_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // irsense4_set

/**
 * @defgroup irsense4_map IR Sense 4 MikroBUS Map
 * @brief MikroBUS pin mapping of IR Sense 4 Click driver.
 */

/**
 * @addtogroup irsense4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Sense 4 Click to the selected MikroBUS.
 */
#define IRSENSE4_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // irsense4_map
/*! @} */ // irsense4

/**
 * @brief IR Sense 4 Click driver selector.
 * @details Selects target driver interface of IR Sense 4 Click driver.
 */
typedef enum
{
    IRSENSE4_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    IRSENSE4_DRV_SEL_I2C       /**< I2C driver descriptor. */

} irsense4_drv_t;

/**
 * @brief IR Sense 4 Click driver interface.
 * @details Definition of driver interface of IR Sense 4 Click driver.
 */
typedef err_t ( *irsense4_master_io_t )( struct irsense4_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief IR Sense 4 Click context object.
 * @details Context object definition of IR Sense 4 Click driver.
 */
typedef struct irsense4_s
{
    digital_in_t int_pin;    /**< Interrupt pin. */

    i2c_master_t i2c;        /**< I2C driver object. */
    spi_master_t spi;        /**< SPI driver object. */

    uint8_t      slave_address;      /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    irsense4_drv_t drv_sel;          /**< Master driver interface selector. */

    irsense4_master_io_t write_f;    /**< Master write function. */
    irsense4_master_io_t read_f;     /**< Master read function. */

} irsense4_t;

/**
 * @brief IR Sense 4 Click configuration object.
 * @details Configuration object definition of IR Sense 4 Click driver.
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

    irsense4_drv_t drv_sel;    /**< Master driver interface selector. */

} irsense4_cfg_t;

/**
 * @brief IR Sense 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IRSENSE4_OK = 0,
    IRSENSE4_ERROR = -1

} irsense4_return_value_t;

/**
 * @brief IR Sense 4 Click threshold selection data value for detection algorithm.
 * @details Predefined enum values for driver threshold selection data value.
 */
typedef enum
{
    IRSENSE4_THS_PRESENCE = 0,     /**< Presence threshold selection. */
    IRSENSE4_THS_MOTION = 2,       /**< Motion threshold selection. */
    IRSENSE4_THS_TAMB_SHOCK = 4    /**< Ambient temperature shock threshold selection. */

} irsense4_ths_sel_t;

/*!
 * @addtogroup irsense4 IR Sense 4 Click Driver
 * @brief API for configuring and manipulating IR Sense 4 Click driver.
 * @{
 */

/**
 * @brief IR Sense 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irsense4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irsense4_cfg_setup ( irsense4_cfg_t *cfg );

/**
 * @brief IR Sense 4 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #irsense4_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #irsense4_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void irsense4_drv_interface_selection ( irsense4_cfg_t *cfg, irsense4_drv_t drv_sel );

/**
 * @brief IR Sense 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irsense4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_init ( irsense4_t *ctx, irsense4_cfg_t *cfg );

/**
 * @brief IR Sense 4 default configuration function.
 * @details This function executes a default configuration of IR Sense 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t irsense4_default_cfg ( irsense4_t *ctx );

/**
 * @brief IR Sense 4 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_generic_write ( irsense4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief IR Sense 4 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_generic_read ( irsense4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief IR Sense 4 write register function.
 * @details This function writes a desired data bytes to the selected register
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_write_reg ( irsense4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief IR Sense 4 read register function.
 * @details This function reads a data bytes from the selected register
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_read_reg ( irsense4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief IR Sense 4 read word function.
 * @details This function reads a 16-bit data starting from the selected register
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 16-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_read_word ( irsense4_t *ctx, uint8_t reg, int16_t *data_out );

/**
 * @brief IR Sense 4 set low-pass filter for motion function.
 * @details This function low-pass filter configuration for motion
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] lpf_m : Motion low-pass filter configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_set_lp_filter_motion ( irsense4_t *ctx, uint8_t lpf_m );

/**
 * @brief IR Sense 4 set low-pass filter for presence function.
 * @details This function low-pass filter configuration for presence
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] lpf_p : Presence low-pass filter configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_set_lp_filter_presence ( irsense4_t *ctx, uint8_t lpf_p );

/**
 * @brief IR Sense 4 set low-pass filter for ambient temperature function.
 * @details This function low-pass filter configuration for ambient temperature
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] lpf_at : Ambient temperature low-pass filter configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_set_lp_filter_amb_temp ( irsense4_t *ctx, uint8_t lpf_at );

/**
 * @brief IR Sense 4 get device ID function.
 * @details This function reads device ID
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[out] device_id : Device ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_get_device_id ( irsense4_t *ctx, uint8_t *device_id );

/**
 * @brief IR Sense 4 set averages for temperature function.
 * @details This function select the number of averages for ambient and object temperature
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] avr_amp_temp : Number of averages for ambient temperature.
 * @param[in] avr_obj_temp : Number of averages for object temperature.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_set_avr_temp ( irsense4_t *ctx, uint8_t avr_amp_temp, uint8_t avr_obj_temp );

/**
 * @brief IR Sense 4 set gain mode function.
 * @details This function set gain mode to cover a wide operating temperature range
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] gain_mode : Gain modes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_set_gain_mode ( irsense4_t *ctx, uint8_t gain_mode );

/**
 * @brief IR Sense 4 set sensitivity data function.
 * @details This function set sensitivity data of the component 
 * that can be used for the compensation algorithm
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] sens : Sensitivity data [2048-6128].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_set_sens_data ( irsense4_t *ctx, uint16_t sens );

/**
 * @brief IR Sense 4 set output data rate function.
 * @details This function sets output data rate
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] odr : Output data rate.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_config_odr ( irsense4_t *ctx, uint8_t odr );

/**
 * @brief IR Sense 4 enable one-shot mode function.
 * @details This function enable the one-shot mode (new data set is acquired)
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_enable_one_shot ( irsense4_t *ctx );

/**
 * @brief IR Sense 4 set interrupt masks for flag function.
 * @details This function sets interrupt masks for flag 
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] int_mask : Interrupt masks for flag.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_set_int_mask ( irsense4_t *ctx, uint8_t int_mask );

/**
 * @brief IR Sense 4 configur interrupt the signal function.
 * @details This function configur the signal routed to the interrupt pin
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] int_sr : Interrupt signal configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_config_int_signal ( irsense4_t *ctx, uint8_t int_sr );

/**
 * @brief IR Sense 4 wait new data ready function.
 * @details This function wait until new set of output data is available
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_wait_new_data_ready ( irsense4_t *ctx );

/**
 * @brief IR Sense 4 get status function.
 * @details This function reads the status for the presence, motion 
 * or ambient temperature shock detection flags
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[out] status : Status of the detection flags.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_get_status ( irsense4_t *ctx, uint8_t *status );

/**
 * @brief IR Sense 4 get the object temperature function.
 * @details This function reads the object temperature output value
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[out] temperature : Object temperature output value [degrees Celsius].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_get_obj_temperature ( irsense4_t *ctx, float *temperature );

/**
 * @brief IR Sense 4 get the ambient temperature function.
 * @details This function reads the ambient temperature output value
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[out] temperature : Ambient temperature output value [degrees Celsius].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_get_amb_temperature ( irsense4_t *ctx, float *temperature );

/**
 * @brief IR Sense 4 get the compensated temperature function.
 * @details This function reads the compensated temperature output value
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[out] temperature : Compensated temperature output value [degrees Celsius].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_get_comp_temperature ( irsense4_t *ctx, float *temperature );

/**
 * @brief IR Sense 4 get the presence detection data function.
 * @details This function reads the presence output value
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[out] presence : Presence detection output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_get_presence_data ( irsense4_t *ctx, int16_t *presence );

/**
 * @brief IR Sense 4 get the motion detection data function.
 * @details This function reads the motion output value
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[out] motion : Motion detection output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_get_motion_data ( irsense4_t *ctx, int16_t *motion );

/**
 * @brief IR Sense 4 get the ambient shock detection data function.
 * @details This function reads the ambient shock detection output value
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[out] shock : Ambient shock detection output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_get_amb_shock_data ( irsense4_t *ctx, int16_t *shock );

/**
 * @brief IR Sense 4 write the embedded register function.
 * @details This function writes a desired data bytes to the selected embedded register address
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] reg_emb : Embedded register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_write_emb_reg ( irsense4_t *ctx, uint8_t reg_emb, uint8_t data_in );

/**
 * @brief IR Sense 4 write register function.
 * @details This function writes a desired data bytes to the selected register
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] reg_emb : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_read_emb_reg ( irsense4_t *ctx, uint8_t reg_emb, uint8_t *data_out );

/**
 * @brief IR Sense 4 set threshold data function.
 * @details This function sets threshold data for detection algorithms
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] ths_sel : Threshold data selection.
 * See #irsense4_ths_sel_t object definition for detailed explanation.
 * @param[in] threshold : Threshold data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_set_threshold ( irsense4_t *ctx, irsense4_ths_sel_t ths_sel, uint16_t threshold );

/**
 * @brief IR Sense 4 get the threshold data function.
 * @details This function reads the threshold data for detection algorithms
 * of the STHS34PF80, Low-power, high-sensitivity infrared sensor for presence and motion detection
 * on the IR Sense 4 Click board™.
 * @param[in] ctx : Click context object.
 * See #irsense4_t object definition for detailed explanation.
 * @param[in] ths_sel : Threshold data selection.
 * See #irsense4_ths_sel_t object definition for detailed explanation.
 * @param[out] threshold : Threshold data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense4_get_threshold ( irsense4_t *ctx, irsense4_ths_sel_t ths_sel, uint16_t *threshold );

#ifdef __cplusplus
}
#endif
#endif // IRSENSE4_H

/*! @} */ // irsense4

// ------------------------------------------------------------------------ END
