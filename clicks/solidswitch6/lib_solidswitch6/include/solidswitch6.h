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
 * @file solidswitch6.h
 * @brief This file contains API for SolidSwitch 6 Click Driver.
 */

#ifndef SOLIDSWITCH6_H
#define SOLIDSWITCH6_H

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
 * @addtogroup solidswitch6 SolidSwitch 6 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 6 Click driver.
 * @{
 */

/**
 * @defgroup solidswitch6_reg SolidSwitch 6 Registers List
 * @brief List of registers of SolidSwitch 6 Click driver.
 */

/**
 * @addtogroup solidswitch6_reg
 * @{
 */

/**
 * @brief SolidSwitch 6 description register.
 * @details Specified register for description of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_REG_CTRL_1                 0x01
#define SOLIDSWITCH6_REG_CTRL_2                 0x02
#define SOLIDSWITCH6_REG_CTRL_3                 0x03
#define SOLIDSWITCH6_REG_STATUS_1               0x11
#define SOLIDSWITCH6_REG_STATUS_2               0x12
#define SOLIDSWITCH6_REG_STATUS_3               0x13
#define SOLIDSWITCH6_REG_STATUS_4               0x14
#define SOLIDSWITCH6_REG_STATUS_5               0x15
#define SOLIDSWITCH6_REG_STATUS_6               0x16
#define SOLIDSWITCH6_REG_STATUS_7               0x17
#define SOLIDSWITCH6_REG_STATUS_8               0x18
#define SOLIDSWITCH6_REG_ADV_OPC                0x3F

/**
 * @brief SolidSwitch 6 description ROM memory register.
 * @details Specified ROM memory register for description of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_REG_ROM_CCODE              0x00
#define SOLIDSWITCH6_REG_ROM_DEVF               0x01
#define SOLIDSWITCH6_REG_ROM_PR_CODE_1          0x02
#define SOLIDSWITCH6_REG_ROM_PR_CODE_2          0x03
#define SOLIDSWITCH6_REG_ROM_PR_CODE_3          0x04
#define SOLIDSWITCH6_REG_ROM_PR_CODE_4          0x05
#define SOLIDSWITCH6_REG_ROM_SIL_VER            0x0A
#define SOLIDSWITCH6_REG_ROM_SPI_MODE           0x10
#define SOLIDSWITCH6_REG_ROM_WD_TYPE            0x11
#define SOLIDSWITCH6_REG_ROM_WD_P1              0x13
#define SOLIDSWITCH6_REG_ROM_WD_P2              0x14
#define SOLIDSWITCH6_REG_ROM_ADV_OPC            0x3F

/*! @} */ // solidswitch6_reg

/**
 * @defgroup solidswitch6_set SolidSwitch 6 Registers Settings
 * @brief Settings for registers of SolidSwitch 6 Click driver.
 */

/**
 * @addtogroup solidswitch6_set
 * @{
 */

/**
 * @brief SolidSwitch 6 ROM memory device information data values.
 * @details Specified setting for description of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_ROM_COMPANY_CODE           0x00
#define SOLIDSWITCH6_ROM_DEVICE_FAMILY          0x01
#define SOLIDSWITCH6_ROM_PRODUCT_CODE_1         0x55
#define SOLIDSWITCH6_ROM_PRODUCT_CODE_2         0x52
#define SOLIDSWITCH6_ROM_PRODUCT_CODE_3         0x05
#define SOLIDSWITCH6_ROM_PRODUCT_CODE_4         0x4A
#define SOLIDSWITCH6_ROM_SILICON_VERSION        0x02

/**
 * @brief SolidSwitch 6 control register 1 data values.
 * @details Control register 1 data values of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_CTRL_1_GOSTBY_DIS          0x00
#define SOLIDSWITCH6_CTRL_1_GOSTBY_EN           0x01
#define SOLIDSWITCH6_CTRL_1_EN_DIS              0x00
#define SOLIDSWITCH6_CTRL_1_EN                  0x01
#define SOLIDSWITCH6_CTRL_1_S_T_START_DIS       0x00
#define SOLIDSWITCH6_CTRL_1_S_T_START_EN        0x01
#define SOLIDSWITCH6_CTRL_1_S_T_STOP_DIS        0x00
#define SOLIDSWITCH6_CTRL_1_S_T_STOP_EN         0x01
#define SOLIDSWITCH6_CTRL_1_S_T_CFG_NO          0x00
#define SOLIDSWITCH6_CTRL_1_S_T_CFG_CS          0x01
#define SOLIDSWITCH6_CTRL_1_S_T_CFG_VDS         0x02
#define SOLIDSWITCH6_CTRL_1_S_T_CFG_CS_VDS      0x03
#define SOLIDSWITCH6_CTRL_1_S_T_CFG_PWRS        0x04
#define SOLIDSWITCH6_CTRL_1_S_T_CFG_CS_PWRS     0x05
#define SOLIDSWITCH6_CTRL_1_S_T_CFG_VDS_PWRS    0x06
#define SOLIDSWITCH6_CTRL_1_S_T_CFG_ALL         0x07
#define SOLIDSWITCH6_CTRL_1_OUTCTL_OFF          0x00
#define SOLIDSWITCH6_CTRL_1_OUTCTL_ON           0x01
#define SOLIDSWITCH6_CTRL_1_BYPASSCTL_OFF       0x00
#define SOLIDSWITCH6_CTRL_1_BYPASSCTL_ON        0x01
#define SOLIDSWITCH6_CTRL_1_WD_TRI_DIS          0x00
#define SOLIDSWITCH6_CTRL_1_WD_TRI_EN           0x01
#define SOLIDSWITCH6_CTRL_1_PARITY_BIT          0x01

/**
 * @brief SolidSwitch 6 control register 2 data values.
 * @details Control register 2 data values of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_CTRL_2_T_NOM_1SEC          0x00
#define SOLIDSWITCH6_CTRL_2_T_NOM_511SEC        0xFF
#define SOLIDSWITCH6_CTRL_2_OVC_THR_6_MV        0x00
#define SOLIDSWITCH6_CTRL_2_OVC_THR_90_MV       0x1F
#define SOLIDSWITCH6_CTRL_2_HSHT_THR_20_MV      0x00
#define SOLIDSWITCH6_CTRL_2_HSHT_THR_160_MV     0x0F
#define SOLIDSWITCH6_CTRL_2_VDS_THR_0_3_V       0x00
#define SOLIDSWITCH6_CTRL_2_VDS_THR_1_8_V       0x1F
#define SOLIDSWITCH6_CTRL_2_WD_TRI_EN           0x01
#define SOLIDSWITCH6_CTRL_2_PARITY_BIT          0x01

/**
 * @brief SolidSwitch 6 control register 3 data values.
 * @details Control register 3 data values of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_CTRL_3_UNLOCK_DIS          0x00
#define SOLIDSWITCH6_CTRL_3_UNLOCK_EN           0x01
#define SOLIDSWITCH6_CTRL_3_NTC_THR_37_5        0x00
#define SOLIDSWITCH6_CTRL_3_NTC_THR_110_92      0x0F
#define SOLIDSWITCH6_CTRL_3_WD_TIME_50_MS       0x00
#define SOLIDSWITCH6_CTRL_3_WD_TIME_100_MS      0x01
#define SOLIDSWITCH6_CTRL_3_WD_TIME_150_MS      0x02
#define SOLIDSWITCH6_CTRL_3_WD_TIME_200_MS      0x03
#define SOLIDSWITCH6_CTRL_3_DIS_OUT_MODE_DIS    0x00
#define SOLIDSWITCH6_CTRL_3_DIS_OUT_MODE_EN     0x01
#define SOLIDSWITCH6_CTRL_3_WD_TRI_EN           0x01
#define SOLIDSWITCH6_CTRL_3_PARITY_BITMASK      0x00000001ul
#define SOLIDSWITCH6_CTRL_3_WD_TRIG             0x00000002ul
#define SOLIDSWITCH6_CTRL_3_GOTO_UNLOCK         0x00000200ul

/**
 * @brief SolidSwitch 6 Current sense amplifier.
 * @details Current sense amplifier data values of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_CURR_SENSE_RANGE_MV         160.0f
#define SOLIDSWITCH6_CURR_SENSE_RES              0x1FFFu

/**
 * @brief SolidSwitch 6 ADC conversion related to TJ.
 * @details ADC conversion related to TJ (Device temperature) data values of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_TJ_TEMP_MIN                 -40.0f
#define SOLIDSWITCH6_TJ_TEMP_MAX                 150.0f
#define SOLIDSWITCH6_TJ_RANGE                    190.0f
#define SOLIDSWITCH6_TJ_RES                      0x03FFu

 /**
 * @brief SolidSwitch 6 ADC conversion of the VDS self-test data values.
 * @details ADC conversion related of the VDS, performed during VDS self-test and content 
 * of VDS register latched during selftest execution data values of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_S_T_VDS_MIN_START           300.0f
#define SOLIDSWITCH6_S_T_VDS_RANGE_MV            1500.0f
#define SOLIDSWITCH6_S_T_VDS_RES                 0x03FFu

/**
 * @brief SolidSwitch 6 ADC conversion related to NTC data values.
 * @details ADC conversion related to NTC data values of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_VNTC_MIN_3V3               -0.3f
#define SOLIDSWITCH6_VNTC_MIN_5V                 1.7f
#define SOLIDSWITCH6_VNTC_RANGE_3V3              3.9f
#define SOLIDSWITCH6_VNTC_RANGE_5V               3.6f
#define SOLIDSWITCH6_VNTC_RES                    0x03FFu

/**
 * @brief SolidSwitch 6 ADC conversion of the voltage across HS switch data values.
 * @details ADC conversion of the voltage across HS switch data values of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_VDS_MIN_MV                  300.0f
#define SOLIDSWITCH6_VDS_MAX_MV                  1800.0f
#define SOLIDSWITCH6_VDS_RANGE_MV                1500.0f
#define SOLIDSWITCH6_VDS_CONVERT_TO_V            1000.0f
#define SOLIDSWITCH6_VDS_RES                     0x03FFu

 /**
 * @brief SolidSwitch 6 ADC conversion of the OUT data values.
 * @details ADC conversion related of the OUT data values of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_VOUT_RANGE                  60.0f
#define SOLIDSWITCH6_VOUT_RES                    0x03FFu

/**
 * @brief SolidSwitch 6 Current sense amplifier.
 * @details Current sense amplifier data values of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_S_T_CURR_RANGE_MV           160.0f
#define SOLIDSWITCH6_S_T_CURR_RES                0x1FFFu

 /**
 * @brief SolidSwitch 6 ADC conversion of the VDS STUCK ON data values.
 * @details ADC conversion related of the VDS, performed during STUCK ON
 * self-test data values of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_S_T_STUCK_MIN_MIN           300.0f
#define SOLIDSWITCH6_S_T_STUCK_RANGE_MV          1500.0f
#define SOLIDSWITCH6_S_T_STUCK_RES               0x03FFu

/**
 * @brief SolidSwitch 6 Current sense amplifier.
 * @details Current sense amplifier data values of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_HSHT_SAR_RANGE_MV           160.0f
#define SOLIDSWITCH6_HSHT_SAR_RES                0x03FFu

/**
 * @brief SolidSwitch 6 VCC selection.
 * @details VCC selection of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_VCC_SEL_3V3                 0
#define SOLIDSWITCH6_VCC_SEL_5V                  1

/**
 * @brief SolidSwitch 6 global status byte bitmasks.
 * @details Global status byte of SolidSwitch 6 Click driver.
 */
#define SOLIDSWITCH6_GS_GSBN_BIT                 0x80
#define SOLIDSWITCH6_GS_RSTB_BIT                 0x40
#define SOLIDSWITCH6_GS_SPIE_BIT                 0x20
#define SOLIDSWITCH6_GS_AUTOON_BIT               0x10
#define SOLIDSWITCH6_GS_DIAGS_BIT                0x08
#define SOLIDSWITCH6_GS_DE_BIT                   0x04
#define SOLIDSWITCH6_GS_OVC_BIT                  0x02
#define SOLIDSWITCH6_GS_FS_BIT                   0x01
#define SOLIDSWITCH6_GS_OK                       0x00

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b solidswitch6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SOLIDSWITCH6_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define SOLIDSWITCH6_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // solidswitch6_set

/**
 * @defgroup solidswitch6_map SolidSwitch 6 MikroBUS Map
 * @brief MikroBUS pin mapping of SolidSwitch 6 Click driver.
 */

/**
 * @addtogroup solidswitch6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SolidSwitch 6 Click to the selected MikroBUS.
 */
#define SOLIDSWITCH6_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.hwl = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.dgn = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // solidswitch6_map
/*! @} */ // solidswitch6

/**
 * @brief SolidSwitch 6 Click context object.
 * @details Context object definition of SolidSwitch 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t hwl;         /**< Write lock pin. */

    // Input pins
    digital_in_t dgn;          /**< Diagnostic feedback pin. */

    // Modules
    spi_master_t spi;          /**< SPI driver object. */

    pin_name_t chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t global_status;     /**< Global Status Byte. */
    uint8_t vcc_sel;           /**< VCC selection. */

} solidswitch6_t;

/**
 * @brief SolidSwitch 6 Click configuration object.
 * @details Configuration object definition of SolidSwitch 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t hwl;             /**< Write lock pin. */
    pin_name_t dgn;             /**< Diagnostic feedback pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} solidswitch6_cfg_t;

/**
 * @brief SolidSwitch 6 Click device information object.
 * @details Device information object definition of SolidSwitch 6 Click driver.
 */
typedef struct
{
    uint8_t co_code;    /**< STMicroelectronics company code. */
    uint8_t d_family;   /**< BCD product family. */
    uint8_t pc1;        /**< Product Code 1. */
    uint8_t pc2;        /**< Product Code 2. */
    uint8_t pc3;        /**< Product Code 3. */
    uint8_t pc4;        /**< Product Code 4. */
    uint8_t sil_ver;    /**< Silicon version. */
    uint8_t spi_mode;   /**< SPI Mode. */
    uint8_t wd_type;    /**< WD Type. */
    uint8_t wd_bp1;     /**< WD bit pos. 1. */
    uint8_t wd_bp2;     /**< WD bit pos. 2. */

} solidswitch6_device_info_t;

/**
 * @brief SolidSwitch 6 Click control object.
 * @details Control object definition of SolidSwitch 6 Click driver.
 */
typedef struct
{
    uint8_t gostby;       /**< Go to StandBy Mode. */
    uint8_t en;           /**< Enable To send a GoToUnlocked sequence. */
    uint8_t s_t_start;    /**< Transition to Self-Test state. */
    uint8_t s_t_stop;     /**< Stops execution of selected self-test. */
    uint8_t s_t_cfg;      /**< Self Test selection. */
    uint8_t outctl;       /**< HS Gate driver. */
    uint8_t bypassctl;    /**< Enables Low Current Bypass. */
    uint8_t t_nom;        /**< Configures the value of Nominal Time. */
    uint8_t ovc_thr;      /**< Configures the value of Nominal Overcurrent Threshold. */
    uint8_t hsht_thr;     /**< Configures a threshold for Hard Short Circuit Latch-off. */
    uint8_t vds_thr;      /**< Configures a threshold for External MOSFET desaturation shut-down. */
    uint8_t unlock;       /**< Unlock driver. */
    uint8_t ntc_thr;      /**< Configures a threshold for External MOSFET over-temperature shutdown via NTC. */
    uint8_t wd_time;      /**< Watchdog time selection. */
    uint8_t dis_out_mode; /**< Outputs status in Locked state. */
    uint8_t wd_trig;      /**< Watchdog trigger. */

} solidswitch6_ctrl_t;

/**
 * @brief SolidSwitch 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SOLIDSWITCH6_OK = 0,
    SOLIDSWITCH6_ERROR = -1

} solidswitch6_return_value_t;

/*!
 * @addtogroup solidswitch6 SolidSwitch 6 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 6 Click driver.
 * @{
 */

/**
 * @brief SolidSwitch 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #solidswitch6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void solidswitch6_cfg_setup ( solidswitch6_cfg_t *cfg );

/**
 * @brief SolidSwitch 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #solidswitch6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_init ( solidswitch6_t *ctx, solidswitch6_cfg_t *cfg );

/**
 * @brief SolidSwitch 6 default configuration function.
 * @details This function executes a default configuration of SolidSwitch 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t solidswitch6_default_cfg ( solidswitch6_t *ctx );

/**
 * @brief SolidSwitch 6 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_generic_write ( solidswitch6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief SolidSwitch 6 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_generic_read ( solidswitch6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief SolidSwitch 6 SPI frame data writing function.
 * @details This function writes 24-bit data 
 * to the selected register using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_frame_write ( solidswitch6_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief SolidSwitch 6 SPI frame data reading function.
 * @details This function reads 24-bit data
 * from the selected register using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_frame_read ( solidswitch6_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief SolidSwitch 6 SPI frame data read and clear function.
 * @details This function reads and clears 24-bit data
 * from the selected register using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_frame_read_clear ( solidswitch6_t *ctx, uint8_t reg, uint32_t data_in, uint32_t *data_out );

/**
 * @brief SolidSwitch 6 SPI ROM frame data reading function.
 * @details This function reads data byte
 * from the selected ROM memory using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[in] reg : ROM memory address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_read_rom ( solidswitch6_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief SolidSwitch 6 get global status function.
 * @details This function reads global status flag using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_get_global_status ( solidswitch6_t *ctx );

/**
 * @brief SolidSwitch 6 get device information function.
 * @details This function reads device information of 
 * Company Code, Device family, Product Code and Silicon version
 * from the ROM memory using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[out] device_info : Device information object.
 * See #solidswitch6_device_info_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_get_device_info ( solidswitch6_t *ctx, solidswitch6_device_info_t *device_info );

/**
 * @brief SolidSwitch 6 lock write function.
 * @details This function performs transitions to states 
 * where the registers are locked from writing using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void solidswitch6_lock_write ( solidswitch6_t *ctx );

/**
 * @brief SolidSwitch 6 unlock write function.
 * @details This function performs transitions to states 
 * where the registers are unlocked from writing using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void solidswitch6_unlock_write ( solidswitch6_t *ctx );

/**
 * @brief SolidSwitch 6 set control function.
 * @details This function writes control registers 
 * to configure the switch controller using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[] ctrl : Control object.
 * See #solidswitch6_ctrl_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_set_control ( solidswitch6_t *ctx, solidswitch6_ctrl_t ctrl );

/**
 * @brief SolidSwitch 6 get Vsense function.
 * @details This function reads the raw ADC value
 * and converts it to a proportional current sense amplifier voltage level 
 * using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[out] vsense : Current sense amplifier voltage [0-160mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_get_vsense ( solidswitch6_t *ctx, float *vsense );

/**
 * @brief SolidSwitch 6 get device temperature function.
 * @details This function reads the raw ADC value 
 * and converts it to device temperature in degrees Celsius 
 * using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[out] tj : Temperature in degrees of Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_get_device_temp ( solidswitch6_t *ctx, float *tj );

/**
 * @brief SolidSwitch 6 get Vntc function.
 * @details This function reads the raw ADC value
 * and converts it to a proportional NTC voltage level 
 * using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[out] vntc : NTC voltage level [0/1.7-3.6/5.3V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_get_vntc ( solidswitch6_t *ctx, float *vntc );

/**
 * @brief SolidSwitch 6 get VDS function.
 * @details This function reads the raw ADC value
 * and converts it to a proportional voltage level across HS switch (VS-OUT) 
 * using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[out] vds : Voltage across HS switch [300-1800mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_get_vds ( solidswitch6_t *ctx, float *vds );

/**
 * @brief SolidSwitch 6 get Vout function.
 * @details This function reads the raw ADC value
 * and converts it to a proportional voltage level
 * using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[out] vout : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_get_vout ( solidswitch6_t *ctx, float *vout );

/**
 * @brief SolidSwitch 6 get VDS self-test function.
 * @details This function reads the raw ADC value
 * and converts it to a proportional voltage level across HS switch (VS-OUT)
 * performed during VDS self-test and content of VDS register latched during selftest execution 
 * using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[out] st_vds : Voltage across HS switch during self-test [300-1800mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_get_st_vds ( solidswitch6_t *ctx, float *st_vds );

/**
 * @brief SolidSwitch 6 get VDS STUCK ON self-test function.
 * @details This function reads the raw ADC value
 * and converts it to a proportional voltage level across HS switch (VS-OUT) STUCK ON
 * performed during STUCK ON self-test using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[out] st_stuck : Voltage across HS switch during STUCK ON self-test [300-1800mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_get_st_stuck ( solidswitch6_t *ctx, float *st_stuck );

/**
 * @brief SolidSwitch 6 get self-test current sense amplifier function.
 * @details This function reads the raw ADC value
 * and converts it to a proportional self-test current sense amplifier voltage level 
 * performed during CURRENT SENSE self-test and content of HSHT_SAR register latched 
 * during self-test execution using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[out] st_curr : Current sense amplifier voltage self-test [0-160mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_get_st_curr ( solidswitch6_t *ctx, float *st_curr );

/**
 * @brief SolidSwitch 6 get Vsense HSHD function.
 * @details This function reads the raw ADC value
 * and converts it to a proportional SAR fast current sense amplifier voltage level 
 * ranging from 0 V to 160 mV; unidirectional current through an external sense resistor
 * during self-test execution using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch6_t object definition for detailed explanation.
 * @param[out] vsense_hshd : SAR fast current sense amplifier voltage [0-160mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch6_get_vsense_hshd ( solidswitch6_t *ctx, float *vsense_hshd );



#ifdef __cplusplus
}
#endif
#endif // SOLIDSWITCH6_H

/*! @} */ // solidswitch6

// ------------------------------------------------------------------------ END
