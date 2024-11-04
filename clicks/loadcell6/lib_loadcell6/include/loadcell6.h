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
 * @file loadcell6.h
 * @brief This file contains API for Load Cell 6 Click Driver.
 */

#ifndef LOADCELL6_H
#define LOADCELL6_H

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
    
/* REGISTERS */



/* CMD BITS */



    


/*!
 * @addtogroup loadcell6 Load Cell 6 Click Driver
 * @brief API for configuring and manipulating Load Cell 6 Click driver.
 * @{
 */

/**
 * @defgroup loadcell6_reg Load Cell 6 Registers List
 * @brief List of registers of Load Cell 6 Click driver.
 */

/**
 * @addtogroup loadcell6_reg
 * @{
 */

/**
 * @brief Load Cell 6 description register.
 * @details Specified register for description of Load Cell 6 Click driver.
 */
#define LOADCELL6_REG_STAT               0x00
#define LOADCELL6_REG_CTRL1              0x01
#define LOADCELL6_REG_CTRL2              0x02
#define LOADCELL6_REG_CTRL3              0x03
#define LOADCELL6_REG_CTRL4              0x04
#define LOADCELL6_REG_CTRL5              0x05
#define LOADCELL6_REG_DATA               0x06
#define LOADCELL6_REG_SOC_SPI            0x07
#define LOADCELL6_REG_SCG_SPI            0x08
#define LOADCELL6_REG_SCOC_SPI           0x09
#define LOADCELL6_REG_SCGC_SPI           0x0A
#define LOADCELL6_REG_RAM                0x0C
#define LOADCELL6_REG_SYNC_SPI           0x0D
#define LOADCELL6_REG_SOC_ADC            0x15
#define LOADCELL6_REG_SCG_ADC            0x16
#define LOADCELL6_REG_SCOC_ADC           0x17
#define LOADCELL6_REG_SCGC_ADC           0x18

/*! @} */ // loadcell6_reg

/**
 * @defgroup loadcell6_set Load Cell 6 Registers Settings
 * @brief Settings for registers of Load Cell 6 Click driver.
 */

/**
 * @addtogroup loadcell6_set
 * @{
 */

/**
 * @brief Load Cell 6 description setting.
 * @details Specified setting for description of Load Cell 6 Click driver.
 */

/**
 * @brief Load Cell 6 commands description.
 * @details Specified commands for description of Load Cell 6 Click driver.
 */
#define LOADCELL6_CMD_RATE0              0x01
#define LOADCELL6_CMD_RATE1              0x02
#define LOADCELL6_CMD_RATE2              0x04
#define LOADCELL6_CMD_RATE3              0x08
#define LOADCELL6_CMD_IMPD               0x10
#define LOADCELL6_CMD_CAL                0x20
#define LOADCELL6_CMD_START              0x80
#define LOADCELL6_CMD_REG_ACCESS_MODE    0x40

/**
 * @brief Load Cell 6 STAT register bits description.
 * @details Specified STAT register bits for description of Load Cell 6 Click driver.
 */
#define LOADCELL6_STAT_RDY               0x0001
#define LOADCELL6_STAT_MSTAT             0x0002
#define LOADCELL6_STAT_DOR               0x0004
#define LOADCELL6_STAT_SYSGOR            0x0008
#define LOADCELL6_STAT_RATE0             0x0010
#define LOADCELL6_STAT_RATE1             0x0020
#define LOADCELL6_STAT_RATE2             0x0040
#define LOADCELL6_STAT_RATE3             0x0080
#define LOADCELL6_STAT_AOR               0x0100
#define LOADCELL6_STAT_RDERR             0x0200
#define LOADCELL6_STAT_PDSTAT0           0x0400
#define LOADCELL6_STAT_PDSTAT1           0x0800
#define LOADCELL6_STAT_ERROR             0x4000
#define LOADCELL6_STAT_INRESET           0x8000

/**
 * @brief Load Cell 6 CTRL1 register bits description.
 * @details Specified CTRL1 register bits for description of Load Cell 6 Click driver.
 */
#define LOADCELL6_CTRL1_CONTSC           0x01
#define LOADCELL6_CTRL1_SCYCLE           0x02
#define LOADCELL6_CTRL1_FORMAT           0x04
#define LOADCELL6_CTRL1_U_B              0x08
#define LOADCELL6_CTRL1_PD0              0x10
#define LOADCELL6_CTRL1_PD1              0x20
#define LOADCELL6_CTRL1_SYNC             0x40
#define LOADCELL6_CTRL1_EXTCK            0x80

/**
 * @brief Load Cell 6 CTRL2 register bits description.
 * @details Specified CTRL2 register bits for description of Load Cell 6 Click driver.
 */
#define LOADCELL6_CTRL2_PGAIN_x1         0x00
#define LOADCELL6_CTRL2_PGAIN_x2         0x01
#define LOADCELL6_CTRL2_PGAIN_x4         0x02
#define LOADCELL6_CTRL2_PGAIN_x8         0x03
#define LOADCELL6_CTRL2_PGAIN_x16        0x04
#define LOADCELL6_CTRL2_PGAIN_x32        0x05
#define LOADCELL6_CTRL2_PGAIN_x64        0x06
#define LOADCELL6_CTRL2_PGAIN_x128       0x07
#define LOADCELL6_CTRL2_PGAGEN           0x08
#define LOADCELL6_CTRL2_LPMODE           0x10
#define LOADCELL6_CTRL2_BUFEN            0x20
#define LOADCELL6_CTRL2_DGAIN_x1         0x00
#define LOADCELL6_CTRL2_DGAIN_x2         0x40
#define LOADCELL6_CTRL2_DGAIN_x4         0x80
#define LOADCELL6_CTRL2_DGAIN_x8         0xC0
#define LOADCELL6_CTRL2_DGAIN0           0x40
#define LOADCELL6_CTRL2_DGAIN1           0x80

/**
 * @brief Load Cell 6 CTRL3 register bits description.
 * @details Specified CTRL3 register bits for description of Load Cell 6 Click driver.
 */
#define LOADCELL6_CTRL3_DATA32           0x08
#define LOADCELL6_CTRL3_MODBITS          0x10
#define LOADCELL6_CTRL3_ENMSYNC          0x20
#define LOADCELL6_CTRL3_RESERVED         0x41

/**
 * @brief Load Cell 6 CTRL4 register bits description.
 * @details Specified CTRL4 register bits for description of Load Cell 6 Click driver.
 */
#define LOADCELL6_CTRL4_DIO1             0x01
#define LOADCELL6_CTRL4_DIO2             0x02
#define LOADCELL6_CTRL4_DIO3             0x04
#define LOADCELL6_CTRL4_DIO4             0x08
#define LOADCELL6_CTRL4_DIR1             0x10
#define LOADCELL6_CTRL4_DIR2             0x20
#define LOADCELL6_CTRL4_DIR3             0x40
#define LOADCELL6_CTRL4_DIR4             0x80

/**
 * @brief Load Cell 6 CTRL5 register bits description.
 * @details Specified CTRL5 register bits for description of Load Cell 6 Click driver.
 */
#define LOADCELL6_CTRL5_NOSCO            0x01
#define LOADCELL6_CTRL5_NOSCG            0x02
#define LOADCELL6_CTRL5_NOSYSO           0x04
#define LOADCELL6_CTRL5_NOSYSG           0x08
#define LOADCELL6_CTRL5_CAL0             0x40
#define LOADCELL6_CTRL5_CAL1             0x80


/**
 * @brief Load Cell 6 weight data description.
 * @details Specified weight data for description of Load Cell 6 Click driver.
 */
#define LOADCELL6_DATA_NO_DATA           0
#define LOADCELL6_DATA_OK                1  
#define LOADCELL6_WEIGHT_ZERO            0
#define LOADCELL6_WEIGHT_100G            100
#define LOADCELL6_WEIGHT_200G            200
#define LOADCELL6_WEIGHT_500G            500
#define LOADCELL6_WEIGHT_1000G           1000
#define LOADCELL6_WEIGHT_5000G           5000
#define LOADCELL6_WEIGHT_10000G          10000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b loadcell6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define LOADCELL6_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define LOADCELL6_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // loadcell6_set

/**
 * @defgroup loadcell6_map Load Cell 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Load Cell 6 Click driver.
 */

/**
 * @addtogroup loadcell6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Load Cell 6 Click to the selected MikroBUS.
 */
#define LOADCELL6_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.syn = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // loadcell6_map
/*! @} */ // loadcell6

/**
 * @brief Load Cell 6 Click context object.
 * @details Context object definition of Load Cell 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;      /**< Description. */

    // Input pins
    digital_in_t  syn;       /**< Description. */
    digital_in_t  rdy;       /**< Description. */

    // Modules
    spi_master_t  spi;       /**< SPI driver object. */

    pin_name_t  chip_select; /**< Chip select pin descriptor (used for SPI driver). */

} loadcell6_t;

/**
 * @brief Load Cell 6 Click configuration object.
 * @details Configuration object definition of Load Cell 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;        /**< Description. */
    pin_name_t  syn;        /**< Description. */
    pin_name_t  rdy;        /**< Description. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} loadcell6_cfg_t;

/**
 * @brief Load Cell 6 Click load cell data object.
 * @details Load cell data object definition of Load Cell 6 Click driver.
 */
typedef struct
{
    float tare;
    uint8_t tare_ok;
    float weight_coeff_100g;
    uint8_t weight_data_100g_ok;
    float weight_coeff_200g;
    uint8_t weight_data_200g_ok;
    float weight_coeff_500g;
    uint8_t weight_data_500g_ok;
    float weight_coeff_1000g;
    uint8_t weight_data_1000g_ok;
    float weight_coeff_5000g;
    uint8_t weight_data_5000g_ok;
    float weight_coeff_10000g;
    uint8_t weight_data_10000g_ok;
}
loadcell6_data_t;

/**
 * @brief Load Cell 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LOADCELL6_OK = 0,
    LOADCELL6_ERROR = -1

} loadcell6_return_value_t;

/*!
 * @addtogroup loadcell6 Load Cell 6 Click Driver
 * @brief API for configuring and manipulating Load Cell 6 Click driver.
 * @{
 */

/**
 * @brief Load Cell 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #loadcell6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void loadcell6_cfg_setup ( loadcell6_cfg_t *cfg );

/**
 * @brief Load Cell 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #loadcell6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_init ( loadcell6_t *ctx, loadcell6_cfg_t *cfg );

/**
 * @brief Load Cell 6 default configuration function.
 * @details This function executes a default configuration of Load Cell 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t loadcell6_default_cfg ( loadcell6_t *ctx );

/**
 * @brief Load Cell 6 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_generic_write ( loadcell6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Load Cell 6 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_generic_read ( loadcell6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Load Cell 6 hw reset function.
 * @details This function executes a hardware reset 
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_hw_reset ( loadcell6_t *ctx );

/**
 * @brief Load Cell 6 get sync function.
 * @details This function get sync state
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6  Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @return @li @c  0 - Low pin state,
 *         @li @c -1 - High pin state.
 *
 * @note None.
 */
uint8_t loadcell6_sync ( loadcell6_t *ctx );

/**
 * @brief Load Cell 6 check data ready function.
 * @details This function check data ready state
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @return @li @c  0 - Low pin state,
 *         @li @c -1 - High pin state.
 *
 * @note None.
 */
uint8_t loadcell6_check_data_ready ( loadcell6_t *ctx );

/**
 * @brief Load Cell 6 write reg function.
 * @details This function writes a byte of the data to the selected register
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6 Click board™
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_write_reg ( loadcell6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Load Cell 6 read reg function.
 * @details This function reads a byte of data from the selected register 
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_read_reg ( loadcell6_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Load Cell 6 read reg data function.
 * @details This function writes a 24-bit data to the selected register
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_write_reg_data ( loadcell6_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief Load Cell 6 read reg data function.
 * @details This function reads a 24-bit data from the selected register 
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_read_reg_data ( loadcell6_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief Load Cell 6 set command function.
 * @details This function writes a desired commands
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_set_command ( loadcell6_t *ctx, uint8_t cmd );

/**
 * @brief Load Cell 6 get status function.
 * @details This function reads status
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_get_status ( loadcell6_t *ctx, uint16_t *status );

/**
 * @brief Load Cell 6 read ADC data function.
 * @details This function reads the ADC data
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[out] data_out : ADC data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_read_adc ( loadcell6_t *ctx, uint32_t *data_out );

/**
 * @brief Load Cell 6 tare the scales function.
 * @details This function for the tare scales sets the tara value into the cell data structure
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[out] cell_data : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_tare ( loadcell6_t *ctx, loadcell6_data_t *cell_data );

/**
 * @brief Load Cell 6 calibration function.
 * @details This function for the calibration sets the calibration value into the cell data structure
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[in] cal_val : Etalon weight value
 *         @li @c   100 ( LOADCELL6_WEIGHT_100G )   :   100g etalon,
 *         @li @c   200 ( LOADCELL6_WEIGHT_200G )   :   200g etalon,
 *         @li @c   500 ( LOADCELL6_WEIGHT_500G )   :   500g etalon,
 *         @li @c  1000 ( LOADCELL6_WEIGHT_1000G )  :  1000g etalon,
 *         @li @c  5000 ( LOADCELL6_WEIGHT_5000G )  :  5000g etalon,
 *         @li @c 10000 ( LOADCELL6_WEIGHT_10000G ) : 10000g etalon.
 * @param[out] cell_data : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_calibration ( loadcell6_t *ctx, uint16_t cal_val, loadcell6_data_t *cell_data );

/**
 * @brief Load Cell 6 get weight function.
 * @details This function gets float value of the scales measurements [ g ]
 * of the MAX11270 24-Bit, 10mW, 130dB SNR, 64ksps Delta-Sigma ADC with Integrated PGA
 * on the Load Cell 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #loadcell6_t object definition for detailed explanation.
 * @param[out] cell_data : Pointer to the memory location of the structure where data be stored.
 * @param[out] weight_g : Float value of the scales measurements [ g ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell6_get_weight ( loadcell6_t *ctx, loadcell6_data_t *cell_data, float *weight_g );

#ifdef __cplusplus
}
#endif
#endif // LOADCELL6_H

/*! @} */ // loadcell6

// ------------------------------------------------------------------------ END
