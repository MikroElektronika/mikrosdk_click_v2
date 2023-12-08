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
 * @file ccrf3.h
 * @brief This file contains API for ccRF 3 Click Driver.
 */

#ifndef CCRF3_H
#define CCRF3_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup ccrf3 ccRF 3 Click Driver
 * @brief API for configuring and manipulating ccRF 3 Click driver.
 * @{
 */

/**
 * @defgroup ccrf3_reg ccRF 3 Registers List
 * @brief List of registers of ccRF 3 Click driver.
 */

/**
 * @addtogroup ccrf3_reg
 * @{
 */

/**
 * @brief ccRF 3 description register.
 * @details Specified register for description of ccRF 3 Click driver.
 */

/**
 * @brief ccRF 3 configuration register.
 * @details Specified configuration register for description of ccRF 3 Click driver.
 */
#define CCRF3_IOCFG3                        0x0000
#define CCRF3_IOCFG2                        0x0001
#define CCRF3_IOCFG1                        0x0002
#define CCRF3_IOCFG0                        0x0003
#define CCRF3_SYNC3                         0x0004
#define CCRF3_SYNC2                         0x0005
#define CCRF3_SYNC1                         0x0006
#define CCRF3_SYNC0                         0x0007
#define CCRF3_SYNC_CFG1                     0x0008
#define CCRF3_SYNC_CFG0                     0x0009
#define CCRF3_DEVIATION_M                   0x000A
#define CCRF3_MODCFG_DEV_E                  0x000B
#define CCRF3_DCFILT_CFG                    0x000C
#define CCRF3_PREAMBLE_CFG1                 0x000D
#define CCRF3_PREAMBLE_CFG0                 0x000E
#define CCRF3_FREQ_IF_CFG                   0x000F
#define CCRF3_IQIC                          0x0010
#define CCRF3_CHAN_BW                       0x0011
#define CCRF3_MDMCFG1                       0x0012
#define CCRF3_MDMCFG0                       0x0013
#define CCRF3_SYMBOL_RATE2                  0x0014
#define CCRF3_SYMBOL_RATE1                  0x0015
#define CCRF3_SYMBOL_RATE0                  0x0016
#define CCRF3_AGC_REF                       0x0017
#define CCRF3_AGC_CS_THR                    0x0018
#define CCRF3_AGC_GAIN_ADJUST               0x0019
#define CCRF3_AGC_CFG3                      0x001A
#define CCRF3_AGC_CFG2                      0x001B
#define CCRF3_AGC_CFG1                      0x001C
#define CCRF3_AGC_CFG0                      0x001D
#define CCRF3_FIFO_CFG                      0x001E
#define CCRF3_DEV_ADDR                      0x001F
#define CCRF3_SETTLING_CFG                  0x0020
#define CCRF3_FS_CFG                        0x0021
#define CCRF3_WOR_CFG1                      0x0022
#define CCRF3_WOR_CFG0                      0x0023
#define CCRF3_WOR_EVENT0_MSB                0x0024
#define CCRF3_WOR_EVENT0_LSB                0x0025
#define CCRF3_PKT_CFG2                      0x0026
#define CCRF3_PKT_CFG1                      0x0027
#define CCRF3_PKT_CFG0                      0x0028
#define CCRF3_RFEND_CFG1                    0x0029
#define CCRF3_RFEND_CFG0                    0x002A
#define CCRF3_PA_CFG2                       0x002B
#define CCRF3_PA_CFG1                       0x002C
#define CCRF3_PA_CFG0                       0x002D
#define CCRF3_PKT_LEN                       0x002E

/**
 * @brief ccRF 3 Extended configuration register.
 * @details Specified extended configuration register for description of ccRF 3 Click driver.
 */
#define CCRF3_IF_MIX_CFG                    0x2F00
#define CCRF3_FREQOFF_CFG                   0x2F01
#define CCRF3_TOC_CFG                       0x2F02
#define CCRF3_MARC_SPARE                    0x2F03
#define CCRF3_ECG_CFG                       0x2F04
#define CCRF3_CFM_DATA_CFG                  0x2F05
#define CCRF3_EXT_CTRL                      0x2F06
#define CCRF3_RCCAL_FINE                    0x2F07
#define CCRF3_RCCAL_COARSE                  0x2F08
#define CCRF3_RCCAL_OFFSET                  0x2F09
#define CCRF3_FREQOFF1                      0x2F0A
#define CCRF3_FREQOFF0                      0x2F0B
#define CCRF3_FREQ2                         0x2F0C
#define CCRF3_FREQ1                         0x2F0D
#define CCRF3_FREQ0                         0x2F0E
#define CCRF3_IF_ADC2                       0x2F0F
#define CCRF3_IF_ADC1                       0x2F10
#define CCRF3_IF_ADC0                       0x2F11
#define CCRF3_FS_DIG1                       0x2F12
#define CCRF3_FS_DIG0                       0x2F13
#define CCRF3_FS_CAL3                       0x2F14
#define CCRF3_FS_CAL2                       0x2F15
#define CCRF3_FS_CAL1                       0x2F16
#define CCRF3_FS_CAL0                       0x2F17
#define CCRF3_FS_CHP                        0x2F18
#define CCRF3_FS_DIVTWO                     0x2F19
#define CCRF3_FS_DSM1                       0x2F1A
#define CCRF3_FS_DSM0                       0x2F1B
#define CCRF3_FS_DVC1                       0x2F1C
#define CCRF3_FS_DVC0                       0x2F1D
#define CCRF3_FS_LBI                        0x2F1E
#define CCRF3_FS_PFD                        0x2F1F
#define CCRF3_FS_PRE                        0x2F20
#define CCRF3_FS_REG_DIV_CML                0x2F21
#define CCRF3_FS_SPARE                      0x2F22
#define CCRF3_FS_VCO4                       0x2F23
#define CCRF3_FS_VCO3                       0x2F24
#define CCRF3_FS_VCO2                       0x2F25
#define CCRF3_FS_VCO1                       0x2F26
#define CCRF3_FS_VCO0                       0x2F27
#define CCRF3_GBIAS6                        0x2F28
#define CCRF3_GBIAS5                        0x2F29
#define CCRF3_GBIAS4                        0x2F2A
#define CCRF3_GBIAS3                        0x2F2B
#define CCRF3_GBIAS2                        0x2F2C
#define CCRF3_GBIAS1                        0x2F2D
#define CCRF3_GBIAS0                        0x2F2E
#define CCRF3_IFAMP                         0x2F2F
#define CCRF3_LNA                           0x2F30
#define CCRF3_RXMIX                         0x2F31
#define CCRF3_XOSC5                         0x2F32
#define CCRF3_XOSC4                         0x2F33
#define CCRF3_XOSC3                         0x2F34
#define CCRF3_XOSC2                         0x2F35
#define CCRF3_XOSC1                         0x2F36
#define CCRF3_XOSC0                         0x2F37
#define CCRF3_ANALOG_SPARE                  0x2F38
#define CCRF3_PA_CFG3                       0x2F39
#define CCRF3_IRQ0M                         0x2F3F
#define CCRF3_IRQ0F                         0x2F40

/**
 * @brief ccRF 3 Status registers.
 * @details Specified status registers for description of ccRF 3 Click driver.
 */
#define CCRF3_WOR_TIME1                     0x2F64
#define CCRF3_WOR_TIME0                     0x2F65
#define CCRF3_WOR_CAPTURE1                  0x2F66
#define CCRF3_WOR_CAPTURE0                  0x2F67
#define CCRF3_BIST                          0x2F68
#define CCRF3_DCFILTOFFSET_I1               0x2F69
#define CCRF3_DCFILTOFFSET_I0               0x2F6A
#define CCRF3_DCFILTOFFSET_Q1               0x2F6B
#define CCRF3_DCFILTOFFSET_Q0               0x2F6C
#define CCRF3_IQIE_I1                       0x2F6D
#define CCRF3_IQIE_I0                       0x2F6E
#define CCRF3_IQIE_Q1                       0x2F6F
#define CCRF3_IQIE_Q0                       0x2F70
#define CCRF3_RSSI1                         0x2F71
#define CCRF3_RSSI0                         0x2F72
#define CCRF3_MARCSTATE                     0x2F73
#define CCRF3_LQI_VAL                       0x2F74
#define CCRF3_PQT_SYNC_ERR                  0x2F75
#define CCRF3_DEM_STATUS                    0x2F76
#define CCRF3_FREQOFF_EST1                  0x2F77
#define CCRF3_FREQOFF_EST0                  0x2F78
#define CCRF3_AGC_GAIN3                     0x2F79
#define CCRF3_AGC_GAIN2                     0x2F7A
#define CCRF3_AGC_GAIN1                     0x2F7B
#define CCRF3_AGC_GAIN0                     0x2F7C
#define CCRF3_CFM_RX_DATA_OUT               0x2F7D
#define CCRF3_CFM_TX_DATA_IN                0x2F7E
#define CCRF3_ASK_SOFT_RX_DATA              0x2F7F
#define CCRF3_RNDGEN                        0x2F80
#define CCRF3_MAGN2                         0x2F81
#define CCRF3_MAGN1                         0x2F82
#define CCRF3_MAGN0                         0x2F83
#define CCRF3_ANG1                          0x2F84
#define CCRF3_ANG0                          0x2F85
#define CCRF3_CHFILT_I2                     0x2F86
#define CCRF3_CHFILT_I1                     0x2F87
#define CCRF3_CHFILT_I0                     0x2F88
#define CCRF3_CHFILT_Q2                     0x2F89
#define CCRF3_CHFILT_Q1                     0x2F8A
#define CCRF3_CHFILT_Q0                     0x2F8B
#define CCRF3_GPIO_STATUS                   0x2F8C
#define CCRF3_FSCAL_CTRL                    0x2F8D
#define CCRF3_PHASE_ADJUST                  0x2F8E
#define CCRF3_PARTNUMBER                    0x2F8F
#define CCRF3_PARTVERSION                   0x2F90
#define CCRF3_SERIAL_STATUS                 0x2F91
#define CCRF3_MODEM_STATUS1                 0x2F92
#define CCRF3_MODEM_STATUS0                 0x2F93
#define CCRF3_MARC_STATUS1                  0x2F94
#define CCRF3_MARC_STATUS0                  0x2F95
#define CCRF3_PA_IFAMP_TEST                 0x2F96
#define CCRF3_FSRF_TEST                     0x2F97
#define CCRF3_PRE_TEST                      0x2F98
#define CCRF3_PRE_OVR                       0x2F99
#define CCRF3_ADC_TEST                      0x2F9A
#define CCRF3_DVC_TEST                      0x2F9B
#define CCRF3_ATEST                         0x2F9C
#define CCRF3_ATEST_LVDS                    0x2F9D
#define CCRF3_ATEST_MODE                    0x2F9E
#define CCRF3_XOSC_TEST1                    0x2F9F
#define CCRF3_XOSC_TEST0                    0x2FA0

#define CCRF3_RXFIRST                       0x2FD2
#define CCRF3_TXFIRST                       0x2FD3
#define CCRF3_RXLAST                        0x2FD4
#define CCRF3_TXLAST                        0x2FD5
#define CCRF3_NUM_TXBYTES                   0x2FD6
#define CCRF3_NUM_RXBYTES                   0x2FD7
#define CCRF3_FIFO_NUM_TXBYTES              0x2FD8
#define CCRF3_FIFO_NUM_RXBYTES              0x2FD9

/*! @} */ // ccrf3_reg

/**
 * @defgroup ccrf3_set ccRF 3 Registers Settings
 * @brief Settings for registers of ccRF 3 Click driver.
 */

/**
 * @addtogroup ccrf3_set
 * @{
 */

/**
 * @brief ccRF 3 description setting.
 * @details Specified setting for description of ccRF 3 Click driver.
 */
#define CCRF3_STATUS_CHIP_RDYN_BM           0x80
#define CCRF3_STATUS_STATE_BM               0x70
#define CCRF3_STATUS_FIFO_BYTES_AVA_BM      0x0F

#define CCRF3_STATUS_ERROR                  0x00
#define CCRF3_STATUS_OK                     0x01

#define CCRF3_IDLE_MODE                     0x01
#define CCRF3_TX_MODE                       0x02
#define CCRF3_RX_MODE                       0x03

/**
 * @brief ccRF 3 DATA FIFO access.
 * @details Specified DATA FIFO access for description of ccRF 3 Click driver.
 */
#define CCRF3_SINGLE_TXFIFO                 0x003F
#define CCRF3_BURST_TXFIFO                  0x007F
#define CCRF3_SINGLE_RXFIFO                 0x00BF
#define CCRF3_BURST_RXFIFO                  0x00FF

#define CCRF3_LQI_CRC_OK_BM                 0x80
#define CCRF3_LQI_EST_BM                    0x7F

/**
 * @brief ccRF 3 Command strobe registers.
 * @details Specified Command strobe registers for description of ccRF 3 Click driver.
 */
#define CCRF3_SRES                          0x30
#define CCRF3_SFSTXON                       0x31
#define CCRF3_SXOFF                         0x32
#define CCRF3_SCAL                          0x33
#define CCRF3_SRX                           0x34
#define CCRF3_STX                           0x35
#define CCRF3_SIDLE                         0x36
#define CCRF3_SWOR                          0x38
#define CCRF3_SPWD                          0x39
#define CCRF3_SFRX                          0x3A
#define CCRF3_SFTX                          0x3B
#define CCRF3_SWORRST                       0x3C
#define CCRF3_SNOP                          0x3D
#define CCRF3_AFC                           0x37

/**
 * @brief ccRF 3 Chip states returned in status byte.
 * @details Specified Chip states returned in status byte for description of ccRF 3 Click driver.
 */
#define CCRF3_STATE_IDLE                    0x00
#define CCRF3_STATE_RX                      0x10
#define CCRF3_STATE_TX                      0x20
#define CCRF3_STATE_FSTXON                  0x30
#define CCRF3_STATE_CALIBRATE               0x40
#define CCRF3_STATE_SETTLING                0x50
#define CCRF3_STATE_RXFIFO_ERROR            0x60
#define CCRF3_STATE_TXFIFO_ERROR            0x70

#define CCRF3_RADIO_BURST_ACCESS            0x40
#define CCRF3_RADIO_SINGLE_ACCESS           0x00
#define CCRF3_RADIO_READ_ACCESS             0x80
#define CCRF3_RADIO_WRITE_ACCESS            0x00


/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b ccrf3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CCRF3_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define CCRF3_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // ccrf3_set

/**
 * @defgroup ccrf3_map ccRF 3 MikroBUS Map
 * @brief MikroBUS pin mapping of ccRF 3 Click driver.
 */

/**
 * @addtogroup ccrf3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ccRF 3 Click to the selected MikroBUS.
 */
#define CCRF3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gp2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp3 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ccrf3_map
/*! @} */ // ccrf3

/**
 * @brief ccRF 3 Click context object.
 * @details Context object definition of ccRF 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cs;           /**< Chip select pin descriptor for SPI driver. */
    digital_out_t  rst;         /**< Reset. */

    // Input pins
    digital_in_t  gp0;          /**< GPIO0. */
    digital_in_t  gp2;          /**< GPIO2. */
    digital_in_t  gp3;          /**< GPIO3. */
    digital_in_t  miso;         /**< Master input - slave output pin descriptor for SPI driver. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    uint16_t packet_counter;
} ccrf3_t;

/**
 * @brief ccRF 3 Click configuration object.
 * @details Configuration object definition of ccRF 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  gp0;        /**< GPIO0. */
    pin_name_t  rst;        /**< Reset. */
    pin_name_t  gp2;        /**< GPIO2. */
    pin_name_t  gp3;        /**< GPIO3. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} ccrf3_cfg_t;

/**
 * @brief ccRF 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CCRF3_OK = 0,
    CCRF3_ERROR = -1

} ccrf3_return_value_t;

/*!
 * @addtogroup ccrf3 ccRF 3 Click Driver
 * @brief API for configuring and manipulating ccRF 3 Click driver.
 * @{
 */

/**
 * @brief ccRF 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ccrf3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ccrf3_cfg_setup ( ccrf3_cfg_t *cfg );

/**
 * @brief ccRF 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ccrf3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ccrf3_init ( ccrf3_t *ctx, ccrf3_cfg_t *cfg );

/**
 * @brief ccRF 3 default configuration function.
 * @details This function executes a default configuration of ccRF 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ccrf3_default_cfg ( ccrf3_t *ctx );

/**
 * @brief Hardware reset function
 * @details The function Hardware reset - resets the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.
 * @return Nothing.
 * @note Delay aprox. 300 ms.
 */
void ccrf3_hw_reset ( ccrf3_t *ctx );

/**
 * @brief Set command strobe function.
 * @details Function sets 8-bit strobe command to the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.
 * @param[in] cmd : 8-bit command
 * @returns 8-bit status data
 */
uint8_t ccrf3_cmd_strobe ( ccrf3_t *ctx, uint8_t cmd );

/**
 * @brief Read or write burst single function.
 * @details Function reads or writes a sequential data starting to the targeted 8-bit 
 * register address of the CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.
 * @param[in] reg_address : 8-bit register address.
 * @param[in] rw_data : Pointer to the data to be written/read.
 * @param[in] n_bytes : Number of bytes to be written/read.
 * @return Nothing.
 */
void ccrf3_read_write_burst_single ( ccrf3_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint16_t n_bytes );

/**
 * @brief Access 8-bit register function
 * @details Function access to the targeted 8-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.
 * @param[in] access_type : Access type.
 * @param[in] reg_address : 8-bit register address.
 * @param[in] rw_data : Pointer to the data to be written/read.
 * @param[in] n_bytes : Number of bytes to be written/read.
 * @returns 8-bit status data.
 */
uint8_t ccrf3_8bit_reg_access ( ccrf3_t *ctx, char access_type, uint8_t reg_address, uint8_t *rw_data, 
                                              uint16_t n_bytes );

/**
 * @brief Access 16-bit register function.
 * @details Function access to the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation. 
 * @param[in] access_type : Access type.
 * @param[in] ext_address : Ext address.
 * @param[in] reg_address : 8-bit register address.
 * @param[in] rw_data : Pointer to the data to be written/read.
 * @param[in] n_bytes : Number of bytes to be written/read.
 * @returns 8-bit status data.
 */
uint8_t ccrf3_16bit_reg_access ( ccrf3_t *ctx, uint8_t access_type, uint8_t ext_address, 
                                               uint8_t reg_address, uint8_t *rw_data, uint8_t n_bytes );

/**
 * @brief Read the byte of data function.
 * @details Function read the byte of data of the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.  
 * @param[in] reg_address : 16-bit register address.
 * @param[out] read_data : Pointer to the data to be read.
 * @param[in] n_bytes : Number of bytes to be read.
 * @returns 8-bit status data.
 */
err_t ccrf3_read_reg ( ccrf3_t *ctx, uint16_t reg_address, uint8_t *read_data, uint8_t n_bytes );

/**
 * @brief Write sequential data function
 * @details Function write a sequential data starting to the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.   
 * @param[in] reg_address : 16-bit register address.
 * @param[in] write_data : Pointer to the data to be written.
 * @param[in] n_bytes : Number of bytes to be written.
 * @returns 8-bit status data.
 */
uint8_t ccrf3_write_reg ( ccrf3_t *ctx, uint16_t reg_address, uint8_t *write_data, uint8_t n_bytes );

/**
 * @brief Write one byte data function.
 * @details Function write a single byte data to the targeted 16-bit register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.   
 * @param[in] reg_address : 16-bit register address.
 * @param[in] write_data : Data to be written.
 * @returns 8-bit status data.
 */
uint8_t ccrf3_write_reg_single( ccrf3_t *ctx, uint16_t reg_address, uint8_t write_data );

/**
 * @brief Write TX FIFO register function.
 * @details Function write sequential data to the targeted 8-bit TX FIFO register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation. 
 * @param[in] write_data : Pointer to the data to be written.
 * @param[in] n_bytes : Number of bytes to be written.
 * @returns 8-bit status data
 */
uint8_t ccrf3_write_tx_fifo ( ccrf3_t *ctx, uint8_t *write_data, uint8_t n_bytes );

/**
 * @brief Read RX FIFO register function.
 * @details Function read sequential data from the targeted 8-bit RX FIFO register address of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.  
 * @param[in] read_data : Pointer to the data to be read.
 * @param[in] n_bytes : Number of bytes to be read.
 * @returns 8-bit status data
 */
uint8_t ccrf3_read_rx_fifo ( ccrf3_t *ctx, uint8_t *read_data, uint8_t n_bytes );

/**
 * @brief Manual calibration function.
 * @details Function manual calibration the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.  
 * @return Nothing.
 */
void ccrf3_manual_calibration ( ccrf3_t *ctx );

/**
 * @brief Set RX mode function.
 * @details Function set RX mode of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.  
 * @return Nothing.
 */
void ccrf3_set_rx_mode ( ccrf3_t *ctx );

/**
 * @brief Set TX mode function.
 * @details Function set TX mode of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.  
 * @return Nothing.
 */
void ccrf3_set_tx_mode ( ccrf3_t *ctx );

/**
 * @brief Read state of GP0 pin function.
 * @details Function reads state of GP0 pin of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.
 * @return State of the GP0 pin.
 */
uint8_t ccrf3_read_gp0 ( ccrf3_t *ctx );

/**
 * @brief Read state of GP2 pin function.
 * @details Function reads state of GP2 pin of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.
 * @return State of the GP2 pin.
 */
uint8_t ccrf3_read_gp2 ( ccrf3_t *ctx );

/**
 * @brief Read state of GP3 pin function
 * @details Function reads state of GP3 pin of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.
 * @return State of the GP3 pin.
 */
uint8_t ccrf3_read_gp3 ( ccrf3_t *ctx );

/**
 * @brief Send TX data function.
 * @details Function send TX data to the receive module of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.  
 * @param[in] tx_data : Pointer to the data to be send.
 * @param[in] n_bytes : Number of bytes to be send.
 * @return Nothing.
 */
void ccrf3_send_tx_data ( ccrf3_t *ctx, uint8_t *tx_data, uint8_t n_bytes );

/**
 * @brief Receive RX data function.
 * @details Function receive RX data from the transmit module of the
 * CC1120 single-chip radio transceiver on the ccRF 3 Click board.
 * @param[in] ctx : Click context object.
 * See #ccrf3_t object definition for detailed explanation.  
 * @param[out] rx_data : Pointer to the data to be receive.
 * @returns Number of the received data bytes.
 */
uint8_t ccrf3_receive_rx_data ( ccrf3_t *ctx, uint8_t *rx_data );

#ifdef __cplusplus
}
#endif
#endif // CCRF3_H

/*! @} */ // ccrf3

// ------------------------------------------------------------------------ END
