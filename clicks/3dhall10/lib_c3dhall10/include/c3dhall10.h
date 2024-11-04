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
 * @file c3dhall10.h
 * @brief This file contains API for 3D Hall 10 Click Driver.
 */

#ifndef C3DHALL10_H
#define C3DHALL10_H

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
 * @addtogroup c3dhall10 3D Hall 10 Click Driver
 * @brief API for configuring and manipulating 3D Hall 10 Click driver.
 * @{
 */

/**
 * @defgroup c3dhall10_reg 3D Hall 10 Registers List
 * @brief List of registers of 3D Hall 10 Click driver.
 */

/**
 * @addtogroup c3dhall10_reg
 * @{
 */

/**
 * @brief 3D Hall 10 register list.
 * @details Specified register list of 3D Hall 10 Click driver.
 */
#define C3DHALL10_REG_DEVICE_CONFIG             0x00
#define C3DHALL10_REG_SENSOR_CONFIG             0x01
#define C3DHALL10_REG_SYSTEM_CONFIG             0x02
#define C3DHALL10_REG_ALERT_CONFIG              0x03
#define C3DHALL10_REG_X_THRX_CONFIG             0x04
#define C3DHALL10_REG_Y_THRX_CONFIG             0x05
#define C3DHALL10_REG_Z_THRX_CONFIG             0x06
#define C3DHALL10_REG_T_THRX_CONFIG             0x07
#define C3DHALL10_REG_CONV_STATUS               0x08
#define C3DHALL10_REG_X_CH_RESULT               0x09
#define C3DHALL10_REG_Y_CH_RESULT               0x0A
#define C3DHALL10_REG_Z_CH_RESULT               0x0B
#define C3DHALL10_REG_TEMP_RESULT               0x0C
#define C3DHALL10_REG_AFE_STATUS                0x0D
#define C3DHALL10_REG_SYS_STATUS                0x0E
#define C3DHALL10_REG_TEST_CONFIG               0x0F
#define C3DHALL10_REG_OSC_MONITOR               0x10
#define C3DHALL10_REG_MAG_GAIN_CONFIG           0x11
#define C3DHALL10_REG_MAG_OFFSET_CONFIG         0x12
#define C3DHALL10_REG_ANGLE_RESULT              0x13
#define C3DHALL10_REG_MAGNITUDE_RESULT          0x14

/*! @} */ // c3dhall10_reg

/**
 * @defgroup c3dhall10_set 3D Hall 10 Registers Settings
 * @brief Settings for registers of 3D Hall 10 Click driver.
 */

/**
 * @addtogroup c3dhall10_set
 * @{
 */

/**
 * @brief 3D Hall 10 device config register settings.
 * @details Specified settings for device config register of 3D Hall 10 Click driver.
 */
#define C3DHALL10_CONV_AVG_1X                   0x0000
#define C3DHALL10_CONV_AVG_2X                   0x1000
#define C3DHALL10_CONV_AVG_4X                   0x2000
#define C3DHALL10_CONV_AVG_8X                   0x3000
#define C3DHALL10_CONV_AVG_16X                  0x4000
#define C3DHALL10_CONV_AVG_32X                  0x5000
#define C3DHALL10_CONV_AVG_BIT_MASK             0x7000
#define C3DHALL10_MAG_TEMPCO_0                  0x0000
#define C3DHALL10_MAG_TEMPCO_0p12               0x0100
#define C3DHALL10_MAG_TEMPCO_0p03               0x0200
#define C3DHALL10_MAG_TEMPCO_0p2                0x0300
#define C3DHALL10_MAG_TEMPCO_BIT_MASK           0x0300
#define C3DHALL10_OPERATING_MODE_CONFIG         0x0000
#define C3DHALL10_OPERATING_MODE_STANDBY        0x0010
#define C3DHALL10_OPERATING_MODE_MEASURE        0x0020
#define C3DHALL10_OPERATING_MODE_TRIGGER        0x0030
#define C3DHALL10_OPERATING_MODE_DUTY_CYCLED    0x0040
#define C3DHALL10_OPERATING_MODE_SLEEP          0x0050
#define C3DHALL10_OPERATING_MODE_DEEP_SLEEP     0x0060
#define C3DHALL10_OPERATING_MODE_BIT_MASK       0x0070
#define C3DHALL10_T_CH_EN_DISABLE               0x0000
#define C3DHALL10_T_CH_EN_ENABLE                0x0008
#define C3DHALL10_T_CH_EN_BIT_MASK              0x0008
#define C3DHALL10_T_RATE_PER_CONV_AVG           0x0000
#define C3DHALL10_T_RATE_ONCE_PER_CONV          0x0004
#define C3DHALL10_T_RATE_BIT_MASK               0x0004
#define C3DHALL10_T_HLT_EN_DISABLE              0x0000
#define C3DHALL10_T_HLT_EN_ENABLE               0x0002
#define C3DHALL10_T_HLT_EN_BIT_MASK             0x0002

/**
 * @brief 3D Hall 10 sensor config register settings.
 * @details Specified settings for sensor config register of 3D Hall 10 Click driver.
 */
#define C3DHALL10_ANGLE_EN_NO_ANGLE             0x0000
#define C3DHALL10_ANGLE_EN_XY_ANGLE             0x4000
#define C3DHALL10_ANGLE_EN_YZ_ANGLE             0x8000
#define C3DHALL10_ANGLE_EN_XZ_ANGLE             0xC000
#define C3DHALL10_ANGLE_EN_BIT_MASK             0xC000
#define C3DHALL10_SLEEPTIME_1MS                 0x0000
#define C3DHALL10_SLEEPTIME_5MS                 0x0400
#define C3DHALL10_SLEEPTIME_10MS                0x0800
#define C3DHALL10_SLEEPTIME_15MS                0x0C00
#define C3DHALL10_SLEEPTIME_20MS                0x1000
#define C3DHALL10_SLEEPTIME_30MS                0x1400
#define C3DHALL10_SLEEPTIME_50MS                0x1800
#define C3DHALL10_SLEEPTIME_100MS               0x1C00
#define C3DHALL10_SLEEPTIME_500MS               0x2000
#define C3DHALL10_SLEEPTIME_1000MS              0x2400
#define C3DHALL10_SLEEPTIME_BIT_MASK            0x3C00
#define C3DHALL10_MAG_CH_EN_DISABLE             0x0000
#define C3DHALL10_MAG_CH_EN_ENABLE_X            0x0040
#define C3DHALL10_MAG_CH_EN_ENABLE_Y            0x0080
#define C3DHALL10_MAG_CH_EN_ENABLE_XY           0x00C0
#define C3DHALL10_MAG_CH_EN_ENABLE_Z            0x0100
#define C3DHALL10_MAG_CH_EN_ENABLE_ZX           0x0140
#define C3DHALL10_MAG_CH_EN_ENABLE_YZ           0x0180
#define C3DHALL10_MAG_CH_EN_ENABLE_XYZ          0x01C0
#define C3DHALL10_MAG_CH_EN_ENABLE_XYX          0x0200
#define C3DHALL10_MAG_CH_EN_ENABLE_YXY          0x0240
#define C3DHALL10_MAG_CH_EN_ENABLE_YZY          0x0280
#define C3DHALL10_MAG_CH_EN_ENABLE_ZYZ          0x02C0
#define C3DHALL10_MAG_CH_EN_ENABLE_ZXZ          0x0300
#define C3DHALL10_MAG_CH_EN_ENABLE_XZX          0x0340
#define C3DHALL10_MAG_CH_EN_ENABLE_XYZYX        0x0380
#define C3DHALL10_MAG_CH_EN_ENABLE_XYZZYX       0x03C0
#define C3DHALL10_MAG_CH_EN_BIT_MASK            0x03C0
#define C3DHALL10_Z_RANGE_50mT                  0x0000
#define C3DHALL10_Z_RANGE_25mT                  0x0010
#define C3DHALL10_Z_RANGE_100mT                 0x0020
#define C3DHALL10_Z_RANGE_BIT_MASK              0x0030
#define C3DHALL10_Y_RANGE_50mT                  0x0000
#define C3DHALL10_Y_RANGE_25mT                  0x0004
#define C3DHALL10_Y_RANGE_100mT                 0x0008
#define C3DHALL10_Y_RANGE_BIT_MASK              0x000C
#define C3DHALL10_X_RANGE_50mT                  0x0000
#define C3DHALL10_X_RANGE_25mT                  0x0001
#define C3DHALL10_X_RANGE_100mT                 0x0002
#define C3DHALL10_X_RANGE_BIT_MASK              0x0003

/**
 * @brief 3D Hall 10 system config register settings.
 * @details Specified settings for system config register of 3D Hall 10 Click driver.
 */
#define C3DHALL10_DIAG_SEL_ALL_DP_DIAG_ALL      0x0000
#define C3DHALL10_DIAG_SEL_EN_DP_ONLY_DIAG_ALL  0x1000
#define C3DHALL10_DIAG_SEL_ALL_DP_DIAG_SEQ      0x2000
#define C3DHALL10_DIAG_SEL_EN_DP_ONLY_DIAG_SEQ  0x3000
#define C3DHALL10_DIAG_SEL_BIT_MASK             0x3000
#define C3DHALL10_TRIGGER_MODE_SPI_CMD          0x0000
#define C3DHALL10_TRIGGER_MODE_CS_PULSE         0x0200
#define C3DHALL10_TRIGGER_MODE_ALERT_PULSE      0x0400
#define C3DHALL10_TRIGGER_MODE_BIT_MASK         0x0600
#define C3DHALL10_DATA_TYPE_32BIT_REG           0x0000
#define C3DHALL10_DATA_TYPE_12BIT_XY_DATA       0x0040
#define C3DHALL10_DATA_TYPE_12BIT_XZ_DATA       0x0080
#define C3DHALL10_DATA_TYPE_12BIT_ZY_DATA       0x00C0
#define C3DHALL10_DATA_TYPE_12BIT_XT_DATA       0x0100
#define C3DHALL10_DATA_TYPE_12BIT_YT_DATA       0x0140
#define C3DHALL10_DATA_TYPE_12BIT_ZT_DATA       0x0180
#define C3DHALL10_DATA_TYPE_12BIT_AM_DATA       0x01C0
#define C3DHALL10_DATA_TYPE_BIT_MASK            0x01C0
#define C3DHALL10_DIAG_EN_DISABLE               0x0000
#define C3DHALL10_DIAG_EN_ENABLE                0x0020
#define C3DHALL10_DIAG_EN_BIT_MASK              0x0020
#define C3DHALL10_Z_HLT_EN_DISABLE              0x0000
#define C3DHALL10_Z_HLT_EN_ENABLE               0x0004
#define C3DHALL10_Z_HLT_EN_BIT_MASK             0x0004
#define C3DHALL10_Y_HLT_EN_DISABLE              0x0000
#define C3DHALL10_Y_HLT_EN_ENABLE               0x0002
#define C3DHALL10_Y_HLT_EN_BIT_MASK             0x0002
#define C3DHALL10_X_HLT_EN_DISABLE              0x0000
#define C3DHALL10_X_HLT_EN_ENABLE               0x0001
#define C3DHALL10_X_HLT_EN_BIT_MASK             0x0001

/**
 * @brief 3D Hall 10 alert config register settings.
 * @details Specified settings for alert config register of 3D Hall 10 Click driver.
 */
#define C3DHALL10_ALERT_LATCH_DISABLE           0x0000
#define C3DHALL10_ALERT_LATCH_ENABLE            0x2000
#define C3DHALL10_ALERT_LATCH_BIT_MASK          0x2000
#define C3DHALL10_ALERT_MODE_INTERRUPT          0x0000
#define C3DHALL10_ALERT_MODE_SWITCH             0x1000
#define C3DHALL10_ALERT_MODE_BIT_MASK           0x1000
#define C3DHALL10_STATUS_ALRT_AFE_SYS_NO_ASSERT 0x0000
#define C3DHALL10_STATUS_ALRT_AFE_SYS_ASSERT    0x0800
#define C3DHALL10_STATUS_ALRT_BIT_MASK          0x0800
#define C3DHALL10_RSLT_ALRT_NO_CONV_COMPLETE    0x0000
#define C3DHALL10_RSLT_ALRT_CONV_COMPLETE       0x0100
#define C3DHALL10_RSLT_ALRT_BIT_MASK            0x0100
#define C3DHALL10_THRX_COUNT_1_CONV             0x0000
#define C3DHALL10_THRX_COUNT_2_CONV             0x0010
#define C3DHALL10_THRX_COUNT_3_CONV             0x0020
#define C3DHALL10_THRX_COUNT_4_CONV             0x0030
#define C3DHALL10_THRX_COUNT_BIT_MASK           0x0030
#define C3DHALL10_T_THRX_ALRT_NO_CROSSED        0x0000
#define C3DHALL10_T_THRX_ALRT_CROSSED           0x0008
#define C3DHALL10_T_THRX_ALRT_BIT_MASK          0x0008
#define C3DHALL10_Z_THRX_ALRT_NO_CROSSED        0x0000
#define C3DHALL10_Z_THRX_ALRT_CROSSED           0x0004
#define C3DHALL10_Z_THRX_ALRT_BIT_MASK          0x0004
#define C3DHALL10_Y_THRX_ALRT_NO_CROSSED        0x0000
#define C3DHALL10_Y_THRX_ALRT_CROSSED           0x0002
#define C3DHALL10_Y_THRX_ALRT_BIT_MASK          0x0002
#define C3DHALL10_X_THRX_ALRT_NO_CROSSED        0x0000
#define C3DHALL10_X_THRX_ALRT_CROSSED           0x0001
#define C3DHALL10_X_THRX_ALRT_BIT_MASK          0x0001

/**
 * @brief 3D Hall 10 mag gain config register settings.
 * @details Specified settings for mag gain config register of 3D Hall 10 Click driver.
 */
#define C3DHALL10_GAIN_SELECTION_NO_AXIS        0x0000
#define C3DHALL10_GAIN_SELECTION_X_AXIS         0x4000
#define C3DHALL10_GAIN_SELECTION_Y_AXIS         0x8000
#define C3DHALL10_GAIN_SELECTION_Z_AXIS         0xC000
#define C3DHALL10_GAIN_SELECTION_BIT_MASK       0xC000
#define C3DHALL10_GAIN_VALUE_BIT_MASK           0x07FF

/**
 * @brief 3D Hall 10 conv status register settings.
 * @details Specified settings for conv status register of 3D Hall 10 Click driver.
 */
#define C3DHALL10_CONV_STATUS_RDY               0x2000
#define C3DHALL10_CONV_STATUS_A                 0x1000
#define C3DHALL10_CONV_STATUS_T                 0x0800
#define C3DHALL10_CONV_STATUS_Z                 0x0400
#define C3DHALL10_CONV_STATUS_Y                 0x0200
#define C3DHALL10_CONV_STATUS_X                 0x0100
#define C3DHALL10_CONV_STATUS_SET_COUNT         0x0070
#define C3DHALL10_CONV_STATUS_ALRT_STATUS       0x0003

/**
 * @brief 3D Hall 10 calculation values.
 * @details Specified calculation values of 3D Hall 10 Click driver.
 */
#define C3DHALL10_ANGLE_RESOLUTION              16.0
#define C3DHALL10_TEMP_SENS_T0                  25.0
#define C3DHALL10_TEMP_ADC_T0                   17522
#define C3DHALL10_TEMP_ADC_RESOLUTION           60.0
#define C3DHALL10_XYZ_RESOLUTION                32768.0

/**
 * @brief 3D Hall 10 SPI read/write bit mask.
 * @details Specified SPI read/write bit mask of 3D Hall 10 Click driver.
 */
#define C3DHALL10_SPI_READ_MASK                 0x80
#define C3DHALL10_SPI_WRITE_MASK                0x7F

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c3dhall10_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C3DHALL10_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define C3DHALL10_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c3dhall10_set

/**
 * @defgroup c3dhall10_map 3D Hall 10 MikroBUS Map
 * @brief MikroBUS pin mapping of 3D Hall 10 Click driver.
 */

/**
 * @addtogroup c3dhall10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 3D Hall 10 Click to the selected MikroBUS.
 */
#define C3DHALL10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c3dhall10_map
/*! @} */ // c3dhall10

/**
 * @brief 3D Hall 10 Click data object.
 * @details Data object definition of 3D Hall 10 Click driver.
 */
typedef struct
{
    float x_axis;
    float y_axis;
    float z_axis;
    float angle;
    uint16_t magnitude;
    float temperature;
    
} c3dhall10_data_t;

/**
 * @brief 3D Hall 10 Click context object.
 * @details Context object definition of 3D Hall 10 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  alr;                                  /**< Alert pin. */

    // Modules
    spi_master_t  spi;                                  /**< SPI driver object. */

    pin_name_t  chip_select;                            /**< Chip select pin descriptor (used for SPI driver). */

} c3dhall10_t;

/**
 * @brief 3D Hall 10 Click configuration object.
 * @details Configuration object definition of 3D Hall 10 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  alr;                                    /**< Alert pin. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} c3dhall10_cfg_t;

/**
 * @brief 3D Hall 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3DHALL10_OK = 0,
    C3DHALL10_ERROR = -1

} c3dhall10_return_value_t;

/*!
 * @addtogroup c3dhall10 3D Hall 10 Click Driver
 * @brief API for configuring and manipulating 3D Hall 10 Click driver.
 * @{
 */

/**
 * @brief 3D Hall 10 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c3dhall10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c3dhall10_cfg_setup ( c3dhall10_cfg_t *cfg );

/**
 * @brief 3D Hall 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c3dhall10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c3dhall10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall10_init ( c3dhall10_t *ctx, c3dhall10_cfg_t *cfg );

/**
 * @brief 3D Hall 10 default configuration function.
 * @details This function executes a default configuration of 3D Hall 10
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c3dhall10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c3dhall10_default_cfg ( c3dhall10_t *ctx );

/**
 * @brief 3D Hall 10 write frame function.
 * @details This function writes a desired data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall10_t object definition for detailed explanation.
 * @param[in] reg_addr : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note CMD bits are fixed to 0.
 */
err_t c3dhall10_write_frame ( c3dhall10_t *ctx, uint8_t reg_addr, uint16_t data_in );

/**
 * @brief 3D Hall 10 read frame function.
 * @details This function reads data and status from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall10_t object definition for detailed explanation.
 * @param[in] reg_addr : Register address.
 * @param[out] data_out : 16-bit data output read.
 * @param[out] status : 12-bit status output read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The CRC must be enabled and CMD bits are fixed to 0.
 */
err_t c3dhall10_read_frame ( c3dhall10_t *ctx, uint8_t reg_addr, uint16_t *data_out, uint16_t *status );

/**
 * @brief 3D Hall 10 read data function.
 * @details This function reads new data which consists of X, Y, and Z axis values in mT, 
 * and temperature in Celsius. It also reads the angle in Degrees between X and Y by default, 
 * and magnitude data as well.
 * @param[in] ctx : Click context object.
 * See #c3dhall10_t object definition for detailed explanation.
 * @param[out] data_out : 16-bit data output read.
 * See #c3dhall10_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall10_read_data ( c3dhall10_t *ctx, c3dhall10_data_t *data_out );

/**
 * @brief 3D Hall 10 get alert pin function.
 * @details This function returns the alert (ALR) pin logic state.
 * The alert pin is configured as a conversion complete interrupt by default.
 * @param[in] ctx : Click context object.
 * See #c3dhall10_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3dhall10_get_alert_pin ( c3dhall10_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // C3DHALL10_H

/*! @} */ // c3dhall10

// ------------------------------------------------------------------------ END
