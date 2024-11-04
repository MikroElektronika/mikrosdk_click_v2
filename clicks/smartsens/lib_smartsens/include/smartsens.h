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
 * @file smartsens.h
 * @brief This file contains API for Smart Sens Click Driver.
 */

#ifndef SMARTSENS_H
#define SMARTSENS_H

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
 * @addtogroup smartsens Smart Sens Click Driver
 * @brief API for configuring and manipulating Smart Sens Click driver.
 * @{
 */

/**
 * @defgroup smartsens_reg Smart Sens Registers List
 * @brief List of registers of Smart Sens Click driver.
 */

/**
 * @addtogroup smartsens_reg
 * @{
 */

/**
 * @brief Smart Sens application preset.
 * @details Specified application will use flash or RAM. If you use
 * flash and firmware image is already uploaded to flash you can 
 * set @b SMARTSENS_FLASHIMG to 0 to not include firmware image.
 * @note If you want to use RAM example you need to set flash selectors
 * to 0. When RAM selector is being used it will include firmware image
 * because it needs to be booted every time on the start of the application.
 * When Flash selector is selected and you already have flash image in your
 * devices flash you can disable flash image slector because you don't need
 * to include it in your project.
 */
#define SMARTSENS_FLASHIMG                                      0   /*< Firmware image for flash include */
#define SMARTSENS_FLASH                                         1   /*< Boot firmware from flash */
#define SMARTSENS_RAM                                           0   /*< Upload and boot firmware from RAM */

/**
 * @brief Smart Sens description register.
 * @details Specified register for description of Smart Sens Click driver.
 */
#define SMARTSENS_REG_COMMAND_INPUT                             0x00
#define SMARTSENS_REG_WAKE_UP_FIFO                              0x01
#define SMARTSENS_REG_NON_WAKE_UP_FIFO                          0x02
#define SMARTSENS_REG_STATUS_DEBUG_FIFO                         0x03
#define SMARTSENS_REG_CHIP_CTRL                                 0x05
#define SMARTSENS_REG_HOST_INTERFACE_CTRL                       0x06
#define SMARTSENS_REG_HOST_INTERRUPT_CTRL                       0x07
#define SMARTSENS_REG_RESET_REQUEST                             0x14
#define SMARTSENS_REG_TIMESTAMP_EVENT_REQUEST                   0x15
#define SMARTSENS_REG_HOST_CTRL                                 0x16
#define SMARTSENS_REG_HOST_STATUS                               0x17
#define SMARTSENS_REG_HOST_CRC                                  0x18191A1B
#define SMARTSENS_REG_FUSER2_PRODUCT_ID                         0x1C
#define SMARTSENS_REG_FUSER2_REVISION_ID                        0x1D
#define SMARTSENS_REG_ROM_VERSION                               0x1E1F
#define SMARTSENS_REG_KERNEL_VERSION                            0x2021
#define SMARTSENS_REG_USER_VERSION                              0x2223
#define SMARTSENS_REG_FEATURE_STATUS                            0x24
#define SMARTSENS_REG_BOOT_STATUS                               0x25
#define SMARTSENS_REG_HOST_INTERRUPT_TIMESTAMP                  0x26  // Start of interrupt state. Length 5 Bytes. [0x26..0x2A]
#define SMARTSENS_REG_CHIP_ID                                   0x2B
#define SMARTSENS_REG_INTERRUPT_STATUS                          0x2D
#define SMARTSENS_REG_ERROR_VALUE                               0x2E
#define SMARTSENS_REG_ERROR_AUX                                 0x2F
#define SMARTSENS_REG_DEBUG_VALUE                               0x30
#define SMARTSENS_REG_DEBUG_STATE                               0x31

/**
 * @brief Smart Sens control commands.
 * @details Specified commands for control of Smart Sens Click driver.
 */
#define SMARTSENS_CMD_DOWNLOAD_POST_MORTEM_DATA                 0x0001
#define SMARTSENS_CMD_UPLOAD_TO_RAM                             0x0002
#define SMARTSENS_CMD_BOOT_RAM                                  0x0003
#define SMARTSENS_CMD_ERASE_FLASH                               0x0004
#define SMARTSENS_CMD_WRITE_FLASH                               0x0005
#define SMARTSENS_CMD_BOOT_FLASH                                0x0006
#define SMARTSENS_CMD_SET_SENSOR_DATA_INJECTION                 0x0007
#define SMARTSENS_CMD_INJECT_SENSOR_DATA                        0x0008
#define SMARTSENS_CMD_FIFO_FLUSH                                0x0009
#define SMARTSENS_CMD_SOFT_PASS_THROUGH                         0x000A
#define SMARTSENS_CMD_REQUEST_SENSOR_SELF_TEST                  0x000B
#define SMARTSENS_CMD_REQUEST_SENSOR_FAST_OFFSET_COMPENSATION   0x000C
#define SMARTSENS_CMD_CONFIGURE_SENSOR                          0x000D
#define SMARTSENS_CMD_CHANGE_SENSOR_DYNAMIC_RANGE               0x000E
#define SMARTSENS_CMD_SET_CHANGE_SENSITIVITY                    0x000F
#define SMARTSENS_CMD_DEBUG_TEST                                0x0010
#define SMARTSENS_CMD_DUT_CONTINUE                              0x0011
#define SMARTSENS_CMD_DUT_START_TEST                            0x0012
#define SMARTSENS_CMD_CTRL_FIFO_FORMAT                          0x0015
#define SMARTSENS_CMD_RAISE_SPEED                               0x0017
/*
 * COMMANDS WITH PARAMETERS:
 *      0x0100..0x01FF -> System Parameters
 *      0x0200..0x02FF -> BSX Algorithm Parameters
 *      0x0300..0x03FF -> Virual Sensor Information Parameters
 *      0x0500..0x05FF -> Virtual Sensor Configuration Parameters
 *      0x0800..0x0DFF -> Costumer Defined
 *      0x0E00..0x0EFF -> Physical Sensor Control Parameters
 */
// System Parameters
#define SMARTSENS_CMD_SYSTEM_PARAMETERS_READ_MASK               0x1000
#define SMARTSENS_CMD_META_EVENT_CTRL_NON_WAKE_UP_FIFO          0x0101
#define SMARTSENS_CMD_META_EVENT_CTRL_WAKE_UP_FIFO              0x0102
#define SMARTSENS_CMD_META_EVENT_CTRL_FIFO_CTRL                 0x0103
#define SMARTSENS_CMD_META_EVENT_CTRL_FIRMWARE_VERSION          0x0104
#define SMARTSENS_CMD_META_EVENT_CTRL_TIMESTAMPS                0x0105
#define SMARTSENS_CMD_META_EVENT_CTRL_FRAMEWORK_STATUS          0x0106
#define SMARTSENS_CMD_META_EVENT_CTRL_VIRUAL_SENSOR_PRESENT     0x011F
#define SMARTSENS_CMD_META_EVENT_CTRL_PHYSICAL_SENSOR_PRESENT   0x0120
#define SMARTSENS_CMD_META_EVENT_CTRL_PHYSICAL_SENSOR_INFO      0x0121 //0x0121..0x0160
// BSX Algorithm Parameters
#define SMARTSENS_CMD_CALIBRATION_STATE_ACCELEROMETER           0x0201
#define SMARTSENS_CMD_CALIBRATION_STATE_GYROSCOPE               0x0203
#define SMARTSENS_CMD_CALIBRATION_STATE_MAGNETOMETER            0x0205
#define SMARTSENS_CMD_SIC_MATRIX                                0x027D
#define SMARTSENS_CMD_BSX_VERSION                               0x027E
// Virual Sensor Information Parameters
#define SMARTSENS_CMD_VIRTUAL_SENSOR_INFO                       0x0300

/**
 * @brief Smart Sens flash start adress for firmware.
 * @details Recommended flash address to start writing firmware image.
 */
#define SMARTSENS_START_FLASH_ADR                               0x00001F84

/*! @} */ // smartsens_reg

/**
 * @defgroup smartsens_set Smart Sens Registers Settings
 * @brief Settings for registers of Smart Sens Click driver.
 */

/**
 * @addtogroup smartsens_set
 * @{
 */

/**
 * @brief Smart Sens virtual sensor IDs.
 * @details IDs of the virtual sensors of Smart Sens firmware image.
 */
#define SMARTSENS_SENSOR_ID_CUSTOM_START                        160
#define SMARTSENS_SENSOR_ID_CUSTOM_END                          191
#define SMARTSENS_SENSOR_ID_MAX                                 200
#define SMARTSENS_SENSOR_ID_TBD                                 SMARTSENS_SENSOR_ID_MAX - 1
#define SMARTSENS_SENSOR_ID_ACC_PASS                            1   /* Accelerometer passthrough */
#define SMARTSENS_SENSOR_ID_ACC_RAW                             3   /* Accelerometer uncalibrated */
#define SMARTSENS_SENSOR_ID_ACC                                 4   /* Accelerometer corrected */
#define SMARTSENS_SENSOR_ID_ACC_BIAS                            5   /* Accelerometer offset */
#define SMARTSENS_SENSOR_ID_ACC_WU                              6   /* Accelerometer corrected wake up */
#define SMARTSENS_SENSOR_ID_ACC_RAW_WU                          7   /* Accelerometer uncalibrated wake up */
#define SMARTSENS_SENSOR_ID_GYRO_PASS                           10  /* Gyroscope passthrough */
#define SMARTSENS_SENSOR_ID_GYRO_RAW                            12  /* Gyroscope uncalibrated */
#define SMARTSENS_SENSOR_ID_GYRO                                13  /* Gyroscope corrected */
#define SMARTSENS_SENSOR_ID_GYRO_BIAS                           14  /* Gyroscope offset */
#define SMARTSENS_SENSOR_ID_GYRO_WU                             15  /* Gyroscope wake up */
#define SMARTSENS_SENSOR_ID_GYRO_RAW_WU                         16  /* Gyroscope uncalibrated wake up */
#define SMARTSENS_SENSOR_ID_MAG_PASS                            19  /* Magnetometer passthrough */
#define SMARTSENS_SENSOR_ID_MAG_RAW                             21  /* Magnetometer uncalibrated */
#define SMARTSENS_SENSOR_ID_MAG                                 22  /* Magnetometer corrected */
#define SMARTSENS_SENSOR_ID_MAG_BIAS                            23  /* Magnetometer offset */
#define SMARTSENS_SENSOR_ID_MAG_WU                              24  /* Magnetometer wake up */
#define SMARTSENS_SENSOR_ID_MAG_RAW_WU                          25  /* Magnetometer uncalibrated wake up */
#define SMARTSENS_SENSOR_ID_GRA                                 28  /* Gravity vector */
#define SMARTSENS_SENSOR_ID_GRA_WU                              29  /* Gravity vector wake up */
#define SMARTSENS_SENSOR_ID_LACC                                31  /* Linear acceleration */
#define SMARTSENS_SENSOR_ID_LACC_WU                             32  /* Linear acceleration wake up */
#define SMARTSENS_SENSOR_ID_RV                                  34  /* Rotation vector */
#define SMARTSENS_SENSOR_ID_RV_WU                               35  /* Rotation vector wake up */
#define SMARTSENS_SENSOR_ID_GAMERV                              37  /* Game rotation vector */
#define SMARTSENS_SENSOR_ID_GAMERV_WU                           38  /* Game rotation vector wake up */
#define SMARTSENS_SENSOR_ID_GEORV                               40  /* Geo-magnetic rotation vector */
#define SMARTSENS_SENSOR_ID_GEORV_WU                            41  /* Geo-magnetic rotation vector wake up */
#define SMARTSENS_SENSOR_ID_ORI                                 43  /* Orientation */
#define SMARTSENS_SENSOR_ID_ORI_WU                              44  /* Orientation wake up */
#define SMARTSENS_SENSOR_ID_TILT_DETECTOR                       48  /* Tilt detector */
#define SMARTSENS_SENSOR_ID_STD                                 50  /* Step detector */
#define SMARTSENS_SENSOR_ID_STC                                 52  /* Step counter */
#define SMARTSENS_SENSOR_ID_STC_WU                              53  /* Step counter wake up */
#define SMARTSENS_SENSOR_ID_SIG                                 55  /* Significant motion */
#define SMARTSENS_SENSOR_ID_WAKE_GESTURE                        57  /* Wake gesture */
#define SMARTSENS_SENSOR_ID_GLANCE_GESTURE                      59  /* Glance gesture */
#define SMARTSENS_SENSOR_ID_PICKUP_GESTURE                      61  /* Pickup gesture */
#define SMARTSENS_SENSOR_ID_AR                                  63  /* Activity recognition */
#define SMARTSENS_SENSOR_ID_WRIST_TILT_GESTURE                  67  /* Wrist tilt gesture */
#define SMARTSENS_SENSOR_ID_DEVICE_ORI                          69  /* Device orientation */
#define SMARTSENS_SENSOR_ID_DEVICE_ORI_WU                       70  /* Device orientation wake up */
#define SMARTSENS_SENSOR_ID_STATIONARY_DET                      75  /* Stationary detect */
#define SMARTSENS_SENSOR_ID_MOTION_DET                          77  /* Motion detect */
#define SMARTSENS_SENSOR_ID_ACC_BIAS_WU                         91  /* Accelerometer offset wake up */
#define SMARTSENS_SENSOR_ID_GYRO_BIAS_WU                        92  /* Gyroscope offset wake up */
#define SMARTSENS_SENSOR_ID_MAG_BIAS_WU                         93  /* Magnetometer offset wake up */
#define SMARTSENS_SENSOR_ID_STD_WU                              94  /* Step detector wake up */
#define SMARTSENS_SENSOR_ID_TEMP                                128 /* Temperature */
#define SMARTSENS_SENSOR_ID_BARO                                129 /* Barometer */
#define SMARTSENS_SENSOR_ID_HUM                                 130 /* Humidity */
#define SMARTSENS_SENSOR_ID_GAS                                 131 /* Gas */
#define SMARTSENS_SENSOR_ID_TEMP_WU                             132 /* Temperature wake up */
#define SMARTSENS_SENSOR_ID_BARO_WU                             133 /* Barometer wake up */
#define SMARTSENS_SENSOR_ID_HUM_WU                              134 /* Humidity wake up */
#define SMARTSENS_SENSOR_ID_GAS_WU                              135 /* Gas wake up */
#define SMARTSENS_SENSOR_ID_STC_HW                              136 /* Hardware Step counter */
#define SMARTSENS_SENSOR_ID_STD_HW                              137 /* Hardware Step detector */
#define SMARTSENS_SENSOR_ID_SIG_HW                              138 /* Hardware Significant motion */
#define SMARTSENS_SENSOR_ID_STC_HW_WU                           139 /* Hardware Step counter wake up */
#define SMARTSENS_SENSOR_ID_STD_HW_WU                           140 /* Hardware Step detector wake up */
#define SMARTSENS_SENSOR_ID_SIG_HW_WU                           141 /* Hardware Significant motion wake up */
#define SMARTSENS_SENSOR_ID_ANY_MOTION                          142 /* Any motion */
#define SMARTSENS_SENSOR_ID_ANY_MOTION_WU                       143 /* Any motion wake up */
#define SMARTSENS_SENSOR_ID_EXCAMERA                            144 /* External camera trigger */
#define SMARTSENS_SENSOR_ID_GPS                                 145 /* GPS */
#define SMARTSENS_SENSOR_ID_LIGHT                               146 /* Light */
#define SMARTSENS_SENSOR_ID_PROX                                147 /* Proximity */
#define SMARTSENS_SENSOR_ID_LIGHT_WU                            148 /* Light wake up */
#define SMARTSENS_SENSOR_ID_PROX_WU                             149 /* Proximity wake up */
#define SMARTSENS_IS_SYS_ID( sid )                              ( ( sid ) >= 224 )
#define SMARTSENS_SYS_ID_PADDING                                0
#define SMARTSENS_SYS_ID_TS_SMALL_DELTA                         251
#define SMARTSENS_SYS_ID_TS_LARGE_DELTA                         252
#define SMARTSENS_SYS_ID_TS_FULL                                253
#define SMARTSENS_SYS_ID_META_EVENT                             254
#define SMARTSENS_SYS_ID_TS_SMALL_DELTA_WU                      245
#define SMARTSENS_SYS_ID_TS_LARGE_DELTA_WU                      246
#define SMARTSENS_SYS_ID_TS_FULL_WU                             247
#define SMARTSENS_SYS_ID_META_EVENT_WU                          248
#define SMARTSENS_SYS_ID_FILLER                                 255
#define SMARTSENS_SYS_ID_DEBUG_MSG                              250
#define SMARTSENS_SYS_ID_SMARTSENS_LOG_UPDATE_SUB               243
#define SMARTSENS_SYS_ID_SMARTSENS_LOG_DOSTEP                   244
#define SMARTSENS_N_VIRTUAL_SENSOR_MAX                          256 /* Maximum no of available virtual sensor */
#define SMARTSENS_SPECIAL_SENSOR_ID_OFFSET                      245 /* Special & debug virtual sensor id starts at 245 */

/**
 * @brief Smart Sens meta event definitions.
 * @details Definitions of the meta event of the Smart Sens firmware image.
 */
#define SMARTSENS_META_EVENT_FLUSH_COMPLETE                     1
#define SMARTSENS_META_EVENT_SAMPLE_RATE_CHANGED                2
#define SMARTSENS_META_EVENT_POWER_MODE_CHANGED                 3
#define SMARTSENS_META_EVENT_ALGORITHM_EVENTS                   5
#define SMARTSENS_META_EVENT_SENSOR_STATUS                      6
#define SMARTSENS_META_EVENT_BSX_DO_STEPS_MAIN                  7
#define SMARTSENS_META_EVENT_BSX_DO_STEPS_CALIB                 8
#define SMARTSENS_META_EVENT_BSX_GET_OUTPUT_SIGNAL              9
#define SMARTSENS_META_EVENT_RESERVED1                          10
#define SMARTSENS_META_EVENT_SENSOR_ERROR                       11
#define SMARTSENS_META_EVENT_FIFO_OVERFLOW                      12
#define SMARTSENS_META_EVENT_DYNAMIC_RANGE_CHANGED              13
#define SMARTSENS_META_EVENT_FIFO_WATERMARK                     14
#define SMARTSENS_META_EVENT_RESERVED2                          15
#define SMARTSENS_META_EVENT_INITIALIZED                        16
#define SMARTSENS_META_TRANSFER_CAUSE                           17
#define SMARTSENS_META_EVENT_SENSOR_FRAMEWORK                   18
#define SMARTSENS_META_EVENT_RESET                              19
#define SMARTSENS_META_EVENT_SPACER                             20

/**
 * @brief Smart Sens IDs.
 * @details Chip and product IDs of the Smart Sens.
 */
#define SMARTSENS_CHIP_ID_VALUE                                 0x70
#define SMARTSENS_FUSER2_PRODUCT_ID_VALUE                       0x89

/**
 * @brief Boot status
 * @details Boot status masks of the Smart Sens.
 */
#define SMARTSENS_BOOTSTATUS_FLASH_DETECTED                     0x01
#define SMARTSENS_BOOTSTATUS_FLASH_VERIFY_DONE                  0x02
#define SMARTSENS_BOOTSTATUS_FLASH_VERIFY_ERROR                 0x04
#define SMARTSENS_BOOTSTATUS_NO_FLASH                           0x08
#define SMARTSENS_BOOTSTATUS_HOST_INTERFACE_READY               0x10
#define SMARTSENS_BOOTSTATUS_HOST_FW_VERIFY_DONE                0x20
#define SMARTSENS_BOOTSTATUS_HOST_FW_VERIFY_ERROR               0x40
#define SMARTSENS_BOOTSTATUS_HOST_FW_IDLE                       0x80

/**
 * @brief Host status
 * @details Host status masks of the Smart Sens.
 */
#define SMARTSENS_HOSTSTATUS_POWER_STATE                        0x01
#define SMARTSENS_HOSTSTATUS_HOST_PROTOCOL                      0x02
#define SMARTSENS_HOSTSTATUS_HOST_CHANNEL_0                     0x10
#define SMARTSENS_HOSTSTATUS_HOST_CHANNEL_1                     0x20
#define SMARTSENS_HOSTSTATUS_HOST_CHANNEL_2                     0x40
#define SMARTSENS_HOSTSTATUS_HOST_CHANNEL_3                     0x80

/**
 * @brief Interrupt status
 * @details Interrupt status masks of the Smart Sens.
 */
#define SMARTSENS_IST_MASK_ASSERTED                             0x1
#define SMARTSENS_IST_MASK_FIFO_W                               0x6
#define SMARTSENS_IST_MASK_FIFO_NW                              0x18
#define SMARTSENS_IST_MASK_STATUS                               0x20
#define SMARTSENS_IST_MASK_DEBUG                                0x40
#define SMARTSENS_IST_MASK_RESET_FAULT                          0x80
#define SMARTSENS_IST_FIFO_W_DRDY                               0x2
#define SMARTSENS_IST_FIFO_W_LTCY                               0x4
#define SMARTSENS_IST_FIFO_W_WM                                 0x6
#define SMARTSENS_IST_FIFO_NW_DRDY                              0x8
#define SMARTSENS_IST_FIFO_NW_LTCY                              0x10
#define SMARTSENS_IST_FIFO_NW_WM                                0x18
#define SMARTSENS_IS_INT_FIFO_W( status )                       ( status & SMARTSENS_IST_MASK_FIFO_W )
#define SMARTSENS_IS_INT_FIFO_NW( status )                      ( status & SMARTSENS_IST_MASK_FIFO_NW )
#define SMARTSENS_IS_INT_STATUS( status )                       ( status & SMARTSENS_IST_MASK_STATUS )
#define SMARTSENS_IS_INT_ASYNC_STATUS( status )                 ( status & SMARTSENS_IST_MASK_DEBUG )
#define SMARTSENS_IS_INT_RESET( status )                        ( status & SMARTSENS_IST_MASK_RESET_FAULT )
#define SMARTSENS_IST_MASK_FIFO                                 ( SMARTSENS_IST_MASK_FIFO_W | SMARTSENS_IST_MASK_FIFO_NW )
#define SMARTSENS_IS_INT_FIFO( status )                         ( status & SMARTSENS_IST_MASK_FIFO )

/**
 * @brief Interrupt control
 * @details Interrupt control bits of the Smart Sens.
 */
#define SMARTSENS_ICTL_DISABLE_FIFO_W                           0x01
#define SMARTSENS_ICTL_DISABLE_FIFO_NW                          0x02
#define SMARTSENS_ICTL_DISABLE_STATUS_FIFO                      0x04
#define SMARTSENS_ICTL_DISABLE_DEBUG                            0x08
#define SMARTSENS_ICTL_DISABLE_FAULT                            0x10
#define SMARTSENS_ICTL_ACTIVE_LOW                               0x20
#define SMARTSENS_ICTL_EDGE                                     0x40
#define SMARTSENS_ICTL_OPEN_DRAIN                               0x80

/**
 * @brief Host interface control
 * @details Host interface control bits of the Smart Sens.
 */
#define SMARTSENS_HIF_CTRL_ABORT_TRANSFER_CHANNEL_0             0x01
#define SMARTSENS_HIF_CTRL_ABORT_TRANSFER_CHANNEL_1             0x02
#define SMARTSENS_HIF_CTRL_ABORT_TRANSFER_CHANNEL_2             0x04
#define SMARTSENS_HIF_CTRL_ABORT_TRANSFER_CHANNEL_3             0x08
#define SMARTSENS_HIF_CTRL_AP_SUSPENDED                         0x10
#define SMARTSENS_HIF_CTRL_TIMESTAMP_EV_CTRL                    0x40
#define SMARTSENS_HIF_CTRL_ASYNC_STATUS_CHANNEL                 0x80

/**
 * @brief Converter macros
 * @details Macros for converting arrays to whole value.
 */
#define SMARTSENS_LE2U16( x )                                   ( ( uint16_t )( ( x )[ 0 ] | ( x )[ 1 ] << 8 ) )
#define SMARTSENS_LE2S16( x )                                   ( ( int16_t )SMARTSENS_LE2U16( x ) )
#define SMARTSENS_LE2U24( x )                                   ( ( uint32_t )( ( x )[ 0 ] | \
                                                                  ( uint32_t )( x )[ 1 ] << 8 | \
                                                                  ( uint32_t )( x )[ 2 ] << 16 ) )
#define SMARTSENS_LE2U32( x )                                   ( ( uint32_t )( ( x )[ 0 ] | \
                                                                  ( uint32_t )( x )[ 1 ] << 8 | \
                                                                  ( uint32_t )( x )[ 2 ] << 16 | \
                                                                  ( uint32_t )( x )[ 3 ] << 24 ) )
#define SMARTSENS_LE2S32( x )                                   ( ( int32_t )SMARTSENS_LE2U32( x ) )
#define SMARTSENS_LE2U40( x )                                   ( SMARTSENS_LE2U32( x ) | ( uint32_t )( x )[ 4 ] << 32 )
#define SMARTSENS_TIMESTAMP_TO_SEC( x )                         ( ( uint32_t ) ( x * ( 15625.0 / UINT32_C( 1000000000 ) ) ) )

/**
 * @brief Smart Sens device address setting.
 * @details Specified setting for device slave address selection of
 * Smart Sens Click driver.
 */
#define SMARTSENS_SLAVE_ADDRESS_1                               0x29
#define SMARTSENS_SLAVE_ADDRESS_0                               0x28

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b smartsens_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SMARTSENS_SET_DATA_SAMPLE_EDGE                          SET_SPI_DATA_SAMPLE_EDGE
#define SMARTSENS_SET_DATA_SAMPLE_MIDDLE                        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // smartsens_set

/**
 * @defgroup smartsens_map Smart Sens MikroBUS Map
 * @brief MikroBUS pin mapping of Smart Sens Click driver.
 */

/**
 * @addtogroup smartsens_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart Sens Click to the selected MikroBUS.
 */
#define SMARTSENS_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // smartsens_map
/*! @} */ // smartsens

/**
 * @brief Smart Sens Click driver selector.
 * @details Selects target driver interface of Smart Sens Click driver.
 */
typedef enum
{
    SMARTSENS_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    SMARTSENS_DRV_SEL_I2C       /**< I2C driver descriptor. */

} smartsens_drv_t;

/**
 * @brief Fifo type enum.
 * @details Enum types of FIFO of the Smart Sens Click driver.
 */
enum smartsens_fifo_type 
{
    SMARTSENS_FIFO_TYPE_WAKEUP,
    SMARTSENS_FIFO_TYPE_NON_WAKEUP,
    SMARTSENS_FIFO_TYPE_STATUS,
    SMARTSENS_FIFO_TYPE_MAX
};

/**
 * @brief Parsing data info.
 * @details Struct for parsing fifo data of the Smart Sens Click driver.
 */
struct smartsens_fifo_parse_data_info
{
    uint8_t sensor_id;
    enum smartsens_fifo_type fifo_type;
    uint8_t data_size;
    uint8_t *data_ptr;
    uint32_t *time_stamp;
};

/**
 * @brief Smart Sens Click driver interface.
 * @details Definition of driver interface of Smart Sens Click driver.
 */
/**< Driver serial interface. */
typedef err_t ( *smartsens_master_io_t )( struct smartsens_s*, uint8_t, uint8_t*, uint8_t ); 
/**< Driver callback interface. */
typedef void ( *smartsens_fifo_parse_callback_t )( struct smartsens_fifo_parse_data_info *callback_info, void *private_data ); 

/**
 * @brief U16 converter union
 * @details Union converting uint16_t to uint8_t array.
 */
union smartsens_u16_conv
{
    uint16_t u16_val;
    uint8_t bytes[ 2 ];
};

/**
 * @brief U32 converter union
 * @details Union converting uint32_t to uint8_t array.
 */
union smartsens_u32_conv
{
    uint32_t u32_val;
    uint8_t bytes[ 4 ];
};

/**
 * @brief Float converter union
 * @details Union converting uint32_t to uint8_t array.
 */
union smartsens_float_conv
{
    float f_val;
    uint32_t u32_val;
    uint8_t bytes[ 4 ];
};

/**
 * @brief Sensor info.
 * @details Struct for sensor info of the Smart Sens Click driver.
 */
struct smartsens_sensor_info
{
    uint8_t sensor_type;
    uint8_t driver_id;
    uint8_t driver_version;
    uint8_t power;
    union smartsens_u16_conv max_range;
    union smartsens_u16_conv resolution;
    union smartsens_float_conv max_rate;
    union smartsens_u32_conv fifo_reserved;
    union smartsens_u32_conv fifo_max;
    uint8_t event_size;
    union smartsens_float_conv min_rate;
};

/**
 * @brief Callback prase.
 * @details Struct for fifo prase callback of the Smart Sens Click driver.
 */
struct smartsens_fifo_parse_callback_table
{
    uint8_t event_size;
    smartsens_fifo_parse_callback_t callback;
    void *callback_ref;
};

/**
 * @brief Fifo buffer.
 * @details Struct for fifo buffer of the Smart Sens Click driver.
 */
struct smartsens_fifo_buffer
{
    uint32_t read_pos;
    uint32_t read_length;
    uint32_t remain_length;
    uint32_t buffer_size;
    uint8_t *buffer;
};

/**
 * @brief Smart Sens Click context object.
 * @details Context object definition of Smart Sens Click driver.
 */
typedef struct smartsens_s
{
    digital_out_t rst;                  /**< Reset pin. */

    digital_in_t  int_pin;              /**< Interrupt pin. */

    i2c_master_t  i2c;                  /**< I2C driver object. */
    spi_master_t  spi;                  /**< SPI driver object. */

    uint8_t     slave_address;          /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;            /**< Chip select pin descriptor (used for SPI driver). */
    smartsens_drv_t  drv_sel;          /**< Master driver interface selector. */

    smartsens_master_io_t  write_f;    /**< Master write function. */
    smartsens_master_io_t  read_f;     /**< Master read function. */

    struct smartsens_fifo_parse_callback_table table[ SMARTSENS_N_VIRTUAL_SENSOR_MAX ];
    uint32_t last_time_stamp[ SMARTSENS_FIFO_TYPE_MAX ];
    
} smartsens_t;

/**
 * @brief Smart Sens Click configuration object.
 * @details Configuration object definition of Smart Sens Click driver.
 */
typedef struct
{
    pin_name_t  scl;                    /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                    /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                     /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  rst;                    /**< Reset pin. */
    pin_name_t  int_pin;                /**< Interrupt pin. */

    uint32_t  i2c_speed;                /**< I2C serial speed. */
    uint8_t   i2c_address;              /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    smartsens_drv_t  drv_sel;          /**< Master driver interface selector. */

} smartsens_cfg_t;

/**
 * @brief Smart Sens Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTSENS_OK = 0,
    SMARTSENS_ERROR = -1,
    SMARTSENS_ERROR_TIMEOUT = -2

} smartsens_return_value_t;

/*!
 * @addtogroup smartsens Smart Sens Click Driver
 * @brief API for configuring and manipulating Smart Sens Click driver.
 * @{
 */

/**
 * @brief Smart Sens configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartsens_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartsens_cfg_setup ( smartsens_cfg_t *cfg );

/**
 * @brief Smart Sens driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #smartsens_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #smartsens_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void smartsens_drv_interface_selection ( smartsens_cfg_t *cfg, smartsens_drv_t drv_sel );

/**
 * @brief Smart Sens initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartsens_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartsens_init ( smartsens_t *ctx, smartsens_cfg_t *cfg );

/**
 * @brief Smart Sens default configuration function.
 * @details This function executes a default configuration of Smart Sens
 * Click board.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartsens_default_cfg ( smartsens_t *ctx );

/**
 * @brief Smart Sens data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartsens_generic_write ( smartsens_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart Sens data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartsens_generic_read ( smartsens_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Byte writing function.
 * @details This function writes a byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartsens_byte_write ( smartsens_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Byte reading function.
 * @details This function reads a byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartsens_byte_read ( smartsens_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Get interrupt.
 * @details This function reads interrupt pin state.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @return Interrupt pin state.
 */
uint8_t smartsens_get_interrupt ( smartsens_t *ctx );

/**
 * @brief Send command.
 * @details This function sends command and it's parameters to the device.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[in] cmd_buf : Command parameter buffer.
 * @param[in] cmd_len : Command parameter buffer length.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note If command doesn't have parameter set @b cmd_buf to @b NULL and 
 * @b cmd_len to 0.
 */
err_t smartsens_cmd_write ( smartsens_t *ctx, uint16_t cmd, uint8_t *cmd_buf, uint16_t cmd_len );

/**
 * @brief Read Status and Debug FIFO.
 * @details This function reads status and debug fifo for command and it's length,
 * if @b cmd_len is >0 it will also read command parameter resposne.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[out] cmd : Command read.
 * @param[out] cmd_buf : Command parameter buffer.
 * @param[out] cmd_len : Command parameter buffer length.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t smartsens_status_read ( smartsens_t *ctx, uint16_t *cmd, uint8_t *cmd_buf, uint16_t *cmd_len );

/**
 * @brief Get command parameters response.
 * @details This function sends command and awaits response from status and debug FIFO.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[in] parameter : Command to read parameters from.
 * @param[out] parameter_buf : Command parameter buffer.
 * @param[out] parameter_len : Command parameter buffer length.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t smartsens_get_parameter ( smartsens_t *ctx, uint16_t parameter, 
                                uint8_t *parameter_buf, uint16_t *parameter_len );

/**
 * @brief Reset device.
 * @details This function hardware resets device by toggling @b rst pin.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @return Nothing.
 */
void smartsens_reset ( smartsens_t *ctx );

/**
 * @brief SW Reset device.
 * @details This function software resets device by setting reset bit
 * in Reset Request register(0x14).
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t smartsens_sw_reset ( smartsens_t *ctx );

/**
 * @brief Upload firmware image to the device.
 * @details This function will upload firmware image to device RAM or FLASH
 * depending of your define setup.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note If you want to upload firmware to the device Flash you need both 
 * @b SMARTSENS_FLASHIMG and @b SMARTSENS_FLASH to set to 1, but if you 
 * want to use only device RAM both of that macros should be set to 0 and 
 * @b SMARTSENS_RAM should be set to 1.
 */
err_t smartsens_update_firmware ( smartsens_t *ctx );

/**
 * @brief Boot firmware image.
 * @details This function boots firmware and starts firmware from RAM or FLASH
 * depending of your define setup.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note If you want to upload firmware to the device Flash you need to 
 * set @b SMARTSENS_FLASH to 1, but if you want to boot from RAM that 
 * macro should be set to 0 and set @b SMARTSENS_RAM to 1.
 */
err_t smartsens_boot_firmware( smartsens_t *ctx );

/**
 * @brief Power on device boot/upload firmware to device.
 * @details This function sends command and its parameters to the device.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note If you want to upload firmware to the device Flash you need to 
 * set @b SMARTSENS_FLASH to 1, but if you want to boot from RAM that 
 * macro should be set to 0 and set @b SMARTSENS_RAM to 1.
 */
err_t smartsens_power_on_device( smartsens_t *ctx );

/**
 * @brief Update the callback table's information
 * @details Function to update the callback table's information
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t smartsens_update_virtual_sensor_list ( smartsens_t *ctx );

/**
 * @brief Get the virtual sensor list.
 * @details Function to get the virtual sensor list.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[out] sensor_list  : Reference to the 32byte data buffer that 
 * stores the sensor list as a bit format.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t smartsens_get_virt_sensor_list ( smartsens_t *ctx, uint8_t *sensor_list );

/**
 * @brief Set configuration fro virtual sensor.
 * @details Function to set the sample rate and latency of the virtual sensor.
 * @param[in] ctx : Click context object.
 * See #smartsens_t object definition for detailed explanation.
 * @param[in] sensor_id     : Sensor ID of the virtual sensor
 * @param[in] sample_rate   : Sample rate in Hz
 * @param[in] latency       : Report latency in milliseconds
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t smartsens_set_virt_sensor_cfg( smartsens_t *ctx, uint8_t sensor_id, float sample_rate, uint32_t latency );

/**
 * @brief Get and process the FIFO.
 * @details Function to get and process the FIFOs.
 * @param[in] work_buffer   : Reference to the data buffer where the FIFO 
 * data is copied to before parsing.
 * @param[in] buffer_size   : Size of the data buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t smartsens_get_and_process_fifo ( smartsens_t *ctx, uint8_t *work_buffer, uint32_t buffer_size );

/**
 * @brief Link a callback to virtual sensor.
 * @details Function to link a callback and relevant reference when the 
 * sensor event is available in the FIFO.
 * @param[in] sensor_id     : Sensor ID of the virtal sensor
 * @param[in] callback      : Reference of the callback function
 * @param[in] callback_ref  : Reference needed inside the callback function. Can be NULL.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t smartsens_register_fifo_parse_callback ( smartsens_t *ctx, uint8_t sensor_id,
                                               smartsens_fifo_parse_callback_t callback, void *callback_ref );

#ifdef __cplusplus
}
#endif
#endif // SMARTSENS_H

/*! @} */ // smartsens

// ------------------------------------------------------------------------ END
