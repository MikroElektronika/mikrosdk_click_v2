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
 * @file lr6.h
 * @brief This file contains API for LR 6 Click Driver.
 */

#ifndef LR6_H
#define LR6_H

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
 * @addtogroup lr6 LR 6 Click Driver
 * @brief API for configuring and manipulating LR 6 Click driver.
 * @{
 */

/**
 * @defgroup lr6_reg LR 6 Registers List
 * @brief List of registers of LR 6 Click driver.
 */

/**
 * @addtogroup lr6_reg
 * @{
 */

/**
 * @brief LR 6 description command.
 * @details Specified command for description of LR 6 Click driver.
 */
#define LR6_CMD_SET_SLEEP                          0x84
#define LR6_CMD_SET_STANDBY                        0x80
#define LR6_CMD_SET_FS                             0xC1
#define LR6_CMD_SET_TX                             0x83
#define LR6_CMD_SET_RX                             0x82
#define LR6_CMD_STOP_TIMER_ON_PREAMBLE             0x9F
#define LR6_CMD_SET_RX_DUTY_CYCLE                  0x94
#define LR6_CMD_SET_CAD                            0xC5
#define LR6_CMD_SET_TX_CONTINUOUS_WAVE             0xD1
#define LR6_CMD_SET_TX_INFINITE_PREAMBLE           0xD2
#define LR6_CMD_SET_REGULATOR_MODE                 0x96
#define LR6_CMD_CALIBRATE                          0x89
#define LR6_CMD_CALIBRATE_IMAGE                    0x98
#define LR6_CMD_SET_PA_CONFIG                      0x95
#define LR6_CMD_SET_RX_TX_FALLBACK_MODE            0x93
#define LR6_CMD_WRITE_REGISTER                     0x0D
#define LR6_CMD_READ_REGISTER                      0x1D
#define LR6_CMD_WRITE_BUFFER                       0x0E
#define LR6_CMD_READ_BUFFER                        0x1E
#define LR6_CMD_SET_DIO_IRQ_PARAMS                 0x08
#define LR6_CMD_GET_IRQ_STATUS                     0x12
#define LR6_CMD_CLEAR_IRQ_STATUS                   0x02
#define LR6_CMD_SET_DIO2_AS_RF_SWITCH_CTRL         0x9D
#define LR6_CMD_SET_DIO3_AS_TCXO_CTRL              0x97
#define LR6_CMD_SET_RF_FREQUENCY                   0x86
#define LR6_CMD_SET_PACKET_TYPE                    0x8A
#define LR6_CMD_GET_PACKET_TYPE                    0x11
#define LR6_CMD_SET_TX_PARAMS                      0x8E
#define LR6_CMD_SET_MODULATION_PARAMS              0x8B
#define LR6_CMD_SET_PACKET_PARAMS                  0x8C
#define LR6_CMD_SET_CAD_PARAMS                     0x88
#define LR6_CMD_SET_BUFFER_BASE_ADDRESS            0x8F
#define LR6_CMD_SET_LORA_SYMB_NUM_TIMEOUT          0xA0
#define LR6_CMD_GET_STATUS                         0xC0
#define LR6_CMD_GET_RSSI_INST                      0x15
#define LR6_CMD_GET_RX_BUFFER_STATUS               0x13
#define LR6_CMD_GET_PACKET_STATUS                  0x14
#define LR6_CMD_GET_DEVICE_ERRORS                  0x17
#define LR6_CMD_CLEAR_DEVICE_ERRORS                0x07
#define LR6_CMD_GET_STATS                          0x10
#define LR6_CMD_RESET_STATS                        0x00

/**
 * @brief LR 6 description register.
 * @details Specified register for description of LR 6 Click driver.
 */
#define LR6_REG_HOPPING_ENABLE                     0x0385u
#define LR6_REG_PACKECT_LENGTH                     0x0386u
#define LR6_REG_NB_HOPPING_BLOCKS                  0x0387u
#define LR6_REG_NB_SYMBOLS0                        0x0388u
#define LR6_REG_FREQ0                              0x038Au
#define LR6_REG_NB_SYMBOLS15                       0x03E2u
#define LR6_REG_FREQ15                             0x03E4u
#define LR6_REG_DIOX_OUTPUT_ENABLE                 0x0580u
#define LR6_REG_DIOX_INPUT_ENABLE                  0x0583u
#define LR6_REG_DIOX_PILL_UP_CONTROL               0x0584u
#define LR6_REG_DIOX_PULL_DOWN_CONTROL             0x0585u
#define LR6_REG_WHITENING_INITIAL_MSB              0x06B8u
#define LR6_REG_WHITENING_INITIAL_LSB              0x06B9u
#define LR6_REG_CRC_INITIAL_MSB                    0x06BCu
#define LR6_REG_CRC_INITIAL_LSB                    0x06BDu
#define LR6_REG_CRC_POLYNOMIAL_MSB                 0x06BEu
#define LR6_REG_CRC_POLYNOMIAL_LSB                 0x06BFu
#define LR6_REG_SYNC_WORD_0                        0x06C0u
#define LR6_REG_SYNC_WORD_1                        0x06C1u
#define LR6_REG_SYNC_WORD_2                        0x06C2u
#define LR6_REG_SYNC_WORD_3                        0x06C3u
#define LR6_REG_SYNC_WORD_4                        0x06C4u
#define LR6_REG_SYNC_WORD_5                        0x06C5u
#define LR6_REG_SYNC_WORD_6                        0x06C6u
#define LR6_REG_SYNC_WORD_7                        0x06C7u
#define LR6_REG_NODE_ADDRESS                       0x06CDu
#define LR6_REG_BROADCAST_ADDRESS                  0x06CEu
#define LR6_REG_IQ_POLARITY_SETUP                  0x0736u
#define LR6_REG_LORA_SYNC_WORD_MSB                 0x0740u
#define LR6_REG_LORA_SYNC_WORD_LSB                 0x0741u
#define LR6_REG_RANDOM_NUMBER_0                    0x0819u
#define LR6_REG_RANDOM_NUMBER_1                    0x081Au
#define LR6_REG_RANDOM_NUMBER_2                    0x081Bu
#define LR6_REG_RANDOM_NUMBER_3                    0x081Cu
#define LR6_REG_TX_MODULETION                      0x0889u
#define LR6_REG_RX_GAIN                            0x08ACu
#define LR6_REG_TX_CLAMP_CONFIG                    0x08D8u
#define LR6_REG_OCP_CONFIGURATION                  0x08E7u
#define LR6_REG_RTC_CONTROL                        0x0902u
#define LR6_REG_XTA_TRIM                           0x0911u
#define LR6_REG_XTB_TRIM                           0x0912u
#define LR6_REG_DIO3_OUTPUT_VOLTAGE_CONTROL        0x0920u
#define LR6_REG_EVENT_MASK                         0x0944u

/*! @} */ // lr6_reg

/**
 * @defgroup lr6_set LR 6 Registers Settings
 * @brief Settings for registers of LR 6 Click driver.
 */

/**
 * @addtogroup lr6_set
 * @{
 */

/**
 * @brief LR 6 status data values.
 * @details Status data values of LR 6 Click driver.
 */
#define LR6_STATUS_DATA_ERROR                      0x00
#define LR6_STATUS_DATA_AVAILABLE                  0x04
#define LR6_STATUS_CMD_OK                          0x00
#define LR6_STATUS_CMD_TIMEOUT                     0x06
#define LR6_STATUS_CMD_INVALID                     0x08
#define LR6_STATUS_CMD_FAILED                      0x0A
#define LR6_STATUS_CMD_BIT_MASK                    0x0E
#define LR6_STATUS_TX_DONE                         0x0C
#define LR6_STATUS_MODE_STDBY_RC                   0x20    
#define LR6_STATUS_MODE_STDBY_XOSC                 0x30   
#define LR6_STATUS_MODE_FS                         0x40
#define LR6_STATUS_MODE_RX                         0x50
#define LR6_STATUS_MODE_TX                         0x60
#define LR6_STATUS_SPI_FAILED                      0xFF

/**
 * @brief LR 6 sync word data values.
 * @details Sync word data of LR 6 Click driver.
 */
#define LR6_SYNC_WORD_PUBLIC                       0x3444u
#define LR6_SYNC_WORD_PRIVATE                      0x1424u

/**
 * @brief LR 6 standby mode data values.
 * @details Standby mode data of LR 6 Click driver.
 */
#define LR6_STANDBY_RC                             0x00
#define LR6_STANDBY_XOSC                           0x01

/**
 * @brief LR 6 PA and PWR config data values.
 * @details PA and PWR configuration data values of LR 6 Click driver.
 */
#define LR6_PA_CONFIG_DUTY_CYCLE                   0x04
#define LR6_PA_CONFIG_HP_MAX                       0x07
#define LR6_PA_CONFIG_SX1268                       0x00
#define LR6_PA_CONFIG_PA_LUT                       0x01
#define LR6_PWR_CONFIG_RNP_TIME                    0x04

/**
 * @brief LR 6 RF frequency config data values.
 * @details RF frequency configuration data values of LR 6 Click driver.
 */
#define LR6_RF_FREQUENCY_900_MHZ                   900000000ul
#define LR6_RF_FREQ_CALIB_IMG_900_H                0xE1
#define LR6_RF_FREQ_CALIB_IMG_900_L                0xE9
#define LR6_RF_FREQUENCY_850_MHZ                   850000000ul
#define LR6_RF_FREQ_CALIB_IMG_850_H                0xD7
#define LR6_RF_FREQ_CALIB_IMG_850_L                0xD8
#define LR6_RF_FREQUENCY_700_MHZ                   770000000ul
#define LR6_RF_FREQ_CALIB_IMG_700_H                0xC1
#define LR6_RF_FREQ_CALIB_IMG_700_L                0xC5
#define LR6_RF_FREQUENCY_460_MHZ                   460000000ul
#define LR6_RF_FREQ_CALIB_IMG_460_H                0x75
#define LR6_RF_FREQ_CALIB_IMG_460_L                0x81
#define LR6_RF_FREQUENCY_433_MHZ                   433000000ul
#define LR6_RF_FREQUENCY_425_MHZ                   425000000ul
#define LR6_RF_FREQ_CALIB_IMG_425_H                0x6B
#define LR6_RF_FREQ_CALIB_IMG_425_L                0x6F
#define LR6_RF_FREQ_CALIB_IMG_SENS                 ( 32000000.0 / 33554432.0 )

/**
 * @brief LR 6 TX output power and LoRa config data values.
 * @details TX output power and LoRa configuration data values of LR 6 Click driver.
 */
#define LR6_TX_OUTPUT_POWER                        22
#define LR6_TX_OUTPUT_POWER_MIN                    -3
#define LR6_TX_OUTPUT_POWER_MAX                    22
#define LR6_LORA_BANDWIDTH_31_25_KHZ               2
#define LR6_LORA_BANDWIDTH_62_5_KHZ                3
#define LR6_LORA_BANDWIDTH_125_KHZ                 4
#define LR6_LORA_BANDWIDTH_250_KHZ                 5
#define LR6_LORA_BANDWIDTH_500_KHZ                 6
#define LR6_LORA_SPREADING_FACTOR                  7
#define LR6_LORA_CODINGRATE_4_5                    1
#define LR6_LORA_CODINGRATE_4_6                    2
#define LR6_LORA_CODINGRATE_4_7                    3
#define LR6_LORA_CODINGRATE_4_8                    4
#define LR6_LORA_PREAMBLE_LENGTH                   8
#define LR6_LORA_PAYLOADLENGTH                     0
#define LR6_LORA_CRC_ON                            1
#define LR6_LORA_CRC_OFF                           0
#define LR6_LORA_INV_IRQ_ON                        1
#define LR6_LORA_INV_IRQ_OFF                       0
#define LR6_LORA_CFG_SPD_FACT_DEFAULT              4
#define LR6_TX_BASE_ADDR_DEFAULT                   0
#define LR6_RX_BASE_ADDR_DEFAULT                   0

/**
 * @brief LR 6 OVC protection data values.
 * @details OVC protection data values of LR 6 Click driver.
 */
#define LR6_OVC_PROTECT_MIN                        0.0f
#define LR6_OVC_PROTECT_DEFAULT                    60.0f
#define LR6_OVC_PROTECT_MAX                        140.0f

/**
 * @brief LR 6 status data values.
 * @details Status data values of LR 6 Click driver.
 */
#define LR6_STATUS_SET_RX_OK                       0x50
#define LR6_STATUS_SET_TX_OK                       0x60
#define LR6_STATUS_BITMASK                         0x70

/**
 * @brief LR 6 calibrate image data values.
 * @details Calibrate image data values of LR 6 Click driver.
 */
#define LR6_CALIBRATE_IMAGE_OFF                    0x00
#define LR6_CALIBRATE_IMAGE_ON                     0x40
#define LR6_CALIBRATE_ADC_BULK_P_OFF               0x00
#define LR6_CALIBRATE_ADC_BULK_P_ON                0x20
#define LR6_CALIBRATE_ADC_BULK_N_OFF               0x00
#define LR6_CALIBRATE_ADC_BULK_N_ON                0x10
#define LR6_CALIBRATE_ADC_PULSE_OFF                0x00
#define LR6_CALIBRATE_ADC_PULSE_ON                 0x08
#define LR6_CALIBRATE_PLL_OFF                      0x00
#define LR6_CALIBRATE_PLL_ON                       0x04
#define LR6_CALIBRATE_RC13M_OFF                    0x00
#define LR6_CALIBRATE_RC13M_ON                     0x02
#define LR6_CALIBRATE_RC64K_OFF                    0x00
#define LR6_CALIBRATE_RC64K_ON                     0x01

/**
 * @brief LR 6 regulator config data values.
 * @details Regulator config data values of LR 6 Click driver.
 */
#define LR6_REGULATOR_LDO                          0x00
#define LR6_REGULATOR_DC_DC                        0x01

/**
 * @brief LR 6 IQ polarity data values.
 * @details IQ polarity data values of LR 6 Click driver.
 */
#define LR6_IQ_POLARITY_SETUP_INV                  0x00
#define LR6_IQ_POLARITY_SETUP_CLR                  0xFB
#define LR6_IQ_POLARITY_SETUP_NRM                  0x01
#define LR6_IQ_POLARITY_SETUP_SET                  0x04

/**
 * @brief LR 6 LoRa packet and symb data values.
 * @details LoRa packet and symb data values of LR 6 Click driver.
 */
#define LR6_SET_LORA_SYMB_NUM_TIMEOUT              0x00
#define LR6_SET_PACKET_TYPE                        0x01

/**
 * @brief LR 6 preambular length data values.
 * @details Preambular length data values of LR 6 Click driver.
 */
#define LR6_SET_PREMBLE_LEN_OFF                    0x00
#define LR6_SET_PREMBLE_LEN_ON                     0x01
#define LR6_SET_PREMBLE_LEN_DUMMY                  0xFF
#define LR6_STOP_TIMER_ON_PREAMBLE_ON              0x00

/**
 * @brief LR 6 CRC config data values.
 * @details CRC configuration data values of LR 6 Click driver.
 */
#define LR6_SET_CRC_OFF                            0x00
#define LR6_SET_CRC_ON                             0x01

/**
 * @brief LR 6 IRQ and DIO data values.
 * @details IRQ and DIO data value of LR 6 Click driver.
 */
#define LR6_IRQ_TIMEOUT                            0x0200u
#define LR6_IRQ_CAD_DETECTED                       0x0100u
#define LR6_IRQ_CAD_DONE                           0x0080u
#define LR6_IRQ_CRC_ERR                            0x0040u
#define LR6_IRQ_HEADER_ERR                         0x0020u
#define LR6_IRQ_HEADER_VALID                       0x0010u
#define LR6_IRQ_SYNC_WORD_VALID                    0x0008u
#define LR6_IRQ_PREAMBLE_DETECTED                  0x0004u
#define LR6_IRQ_RX_DONE                            0x0002u
#define LR6_IRQ_TX_DONE                            0x0001u
#define LR6_IRQ_ALL                                0x03FFu
#define LR6_IRQ_NONE                               0x0000u
#define LR6_CLEAR_IRQ_STATUS                       0x03FFu
#define LR6_IRQ_DIO_CLR                            0x00
#define LR6_IRQ_DIO_SET                            0x01
#define LR6_DIO2_AS_IRQ                            0x00
#define LR6_DIO2_AS_RF_SWITCH                      0x01
#define LR6_SET_INV_IRQ_OFF                        0x00
#define LR6_SET_INV_IRQ_ON                         0x01

/**
 * @brief LR 6 RX default data values.
 * @details Set RX default data value of LR 6 Click driver.
 */
#define LR6_SET_RX_DEFAULT                         0xFFFFFFul

/**
 * @brief LR 6 TX mode config data values.
 * @details TX mode configuration data value of LR 6 Click driver.
 */
#define LR6_TX_MODE_ASYNC                          0x01
#define LR6_TX_MODE_SYNC                           0x02
#define LR6_TX_MODE_BACK2RX                        0x04

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b lr6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define LR6_SET_DATA_SAMPLE_EDGE                    SET_SPI_DATA_SAMPLE_EDGE
#define LR6_SET_DATA_SAMPLE_MIDDLE                  SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // lr6_set

/**
 * @defgroup lr6_map LR 6 MikroBUS Map
 * @brief MikroBUS pin mapping of LR 6 Click driver.
 */

/**
 * @addtogroup lr6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LR 6 Click to the selected MikroBUS.
 */
#define LR6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.md   = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST );  \
    cfg.bsy  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lr6_map
/*! @} */ // lr6

/**
 * @brief LR 6 Click context object.
 * @details Context object definition of LR 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */

    // Input pins
    digital_in_t md;            /**< MD - DIO pin. */
    digital_in_t bsy;           /**< Busy pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t packet_params[ 6 ]; /**< Packet params. */

} lr6_t;

/**
 * @brief LR 6 Click configuration object.
 * @details Configuration object definition of LR 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t md;              /**< MD - DIO pin. */
    pin_name_t rst;             /**< Reset pin. */
    pin_name_t bsy;             /**< Busy pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} lr6_cfg_t;

/**
 * @brief LR 6 Click LoRa configuration object.
 * @details LoRa configuration object definition of LR 6 Click driver.
 */
typedef struct
{
    uint8_t spd_fact;           /**< Spreading Factor. */
    uint8_t bandwidth;          /**< Bandwidth. */
    uint8_t c_rate;             /**< Coding Rate. */
    uint16_t prmb_len;          /**< Preamble Length. */
    uint8_t pl_len;             /**< Payload Length. */
    uint8_t crc_on;             /**< CRC On. */
    uint8_t inv_irq;            /**< Invert IRQ. */

} lr6_lora_cfg_t;

/**
 * @brief LR 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LR6_OK = 0,
    LR6_ERROR = -1

} lr6_return_value_t;

/*!
 * @addtogroup lr6 LR 6 Click Driver
 * @brief API for configuring and manipulating LR 6 Click driver.
 * @{
 */

/**
 * @brief LR 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lr6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lr6_cfg_setup ( lr6_cfg_t *cfg );

/**
 * @brief LR 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lr6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_init ( lr6_t *ctx, lr6_cfg_t *cfg );

/**
 * @brief LR 6 default configuration function.
 * @details This function executes a default configuration of LR 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lr6_default_cfg ( lr6_t *ctx );

/**
 * @brief LR 6 HW reset function.
 * @details This function performs a hardware reset.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void lr6_hw_reset ( lr6_t *ctx );

/**
 * @brief LR 6 check BSY pin function.
 * @details This function check logic state of the BSY pin.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @return BSY pin logic state.
 * @note None.
 */
uint8_t lr6_check_bsy_pin ( lr6_t *ctx );

/**
 * @brief LR 6 wait for idle function.
 * @details This function wait for the idle state of the module.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_wait_for_idle ( lr6_t *ctx );

/**
 * @brief LR 6 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_generic_write ( lr6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LR 6 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_generic_read ( lr6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LR 6 register writing function.
 * @details This function writes a desired number of data bytes to the selected register 
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_reg_write ( lr6_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LR 6 register reading function.
 * @details This function reads a desired number of data bytes from the selected register 
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @param[in] reg : Rgister address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_reg_read ( lr6_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LR 6 command writing function.
 * @details This function writes a desired number of data bytes to the selected command 
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_cmd_write ( lr6_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief LR 6 command writing check function.
 * @details This function writes a desired number of data bytes to the selected command 
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_cmd_write_check ( lr6_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief LR 6 command reading function.
 * @details This function reads a desired number of data bytes from the selected command 
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_cmd_read ( lr6_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief LR 6 buffer writing function.
 * @details This function writes a desired number of data bytes to the buffer 
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_buffer_write ( lr6_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief LR 6 buffer reading function.
 * @details This function reads a desired number of data bytes from the buffer 
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_buffer_read ( lr6_t *ctx, uint8_t *data_out, uint8_t len, uint8_t *pl_len );

/**
 * @brief LR 6 set standby function.
 * @details This function sets the standby mode of the module
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] mode : Standby mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_standby ( lr6_t *ctx, uint8_t mode );

/**
 * @brief LR 6 set DIO2 RF switch function.
 * @details This function sets the desired state of DIO2 RF switch
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] enable : Enable/disable DIO2 RF switch.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_dio2_rf_switch ( lr6_t *ctx, uint8_t enable );

/**
 * @brief LR 6 set calibrateion function.
 * @details This function sets the desired calibrateion data value
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] calib_data : Calibrateion data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_calibrate ( lr6_t *ctx, uint8_t calib_data );

/**
 * @brief LR 6 set regulator mode function.
 * @details This function sets the desired regulator mode data value
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] mode : Regulator mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_regulator_mode ( lr6_t *ctx, uint8_t mode );

/**
 * @brief LR 6 set PA config function.
 * @details This function sets the desired PA configuration
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] pa_duty_cycle : PA duty cycle config.
 * @mode[in] hp_max : HP max config.
 * @mode[in] device_sel : Device selection.
 * @mode[in] pa_lut : PA LUT.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_pa_config ( lr6_t *ctx, uint8_t pa_duty_cycle, uint8_t hp_max, uint8_t device_sel, uint8_t pa_lut );

/**
 * @brief LR 6 set buff base addr function.
 * @details This function sets the desired buff base address
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] tx_base_addr : TX buff base address.
 * @mode[in] rx_base_addr : RX buff base address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_buff_base_addr ( lr6_t *ctx, uint8_t tx_base_addr, uint8_t rx_base_addr );

/**
 * @brief LR 6 set OVC protection function.
 * @details This function sets the desired overcurrent protection
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] current_limit : overcurrent protection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_ovc_protection ( lr6_t *ctx, float current_limit );

/**
 * @brief LR 6 set power config function.
 * @details This function sets the desired power configuration data value
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] power : power configuration data.
 * @mode[in] rmp_time : Ramp time data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_power_config ( lr6_t *ctx, int8_t power, uint8_t rmp_time );

/**
 * @brief LR 6 set TX power config function.
 * @details This function sets the desired TX power configuration data value
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] tx_pwr_dbm : TX power configuration data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_tx_power ( lr6_t *ctx, int8_t tx_pwr_dbm );

/**
 * @brief LR 6 set TX calib image function.
 * @details This function sets the desired calibrate image frequency data value
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] freq : Calibrate image frequency data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_calib_image ( lr6_t *ctx, uint32_t freq );

/**
 * @brief LR 6 set RF frequency function.
 * @details This function sets the desired RF frequency data value
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] freq : RF frequency data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_rf_frequency ( lr6_t *ctx, uint32_t freq );

/**
 * @brief LR 6 set stop RX timer function.
 * @details This function sets the desired state of the stop RX timer
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] enable : Enable/dsable stop RX timer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_stop_rx_timer ( lr6_t *ctx, uint8_t enable );

/**
 * @brief LR 6 set symb num timeout function.
 * @details This function sets the desired LoRa symbol number timeout data values
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] symb_num : LoRa symbol number timeout data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_lr_symb_num_timeout ( lr6_t *ctx, uint8_t symb_num );

/**
 * @brief LR 6 set packet type function.
 * @details This function sets the desired packet type mode
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] pck_type : Packet type mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_packet_type ( lr6_t *ctx, uint8_t pck_type );

/**
 * @brief LR 6 set modulation params function.
 * @details This function sets the desired configuration of the modulation
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] spd_fact : Spreading Factor.
 * @mode[in] bandwidth : Bandwidth.
 * @mode[in] c_rate : Spreading Factor.
 * @mode[in] ldr_opt : Low Data Rate Optimize.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_modulation_params ( lr6_t *ctx, uint8_t spd_fact, uint8_t bandwidth, uint8_t c_rate, uint8_t ldr_opt );

/**
 * @brief LR 6 set fix inverted IQ function.
 * @details This function sets the desired optimizing the inverted IQ operation
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] iq_cfg : Inverted IQ operation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_fix_inverted_iq (  lr6_t *ctx, uint8_t iq_cfg );

/**
 * @brief LR 6 set DIO IRQ param function.
 * @details This function sets the desired configuration of the DIO IRQ parameters
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] irq : IRQ parameters.
 * @mode[in] dio1 : Digital I/O 1 configuration.
 * @mode[in] dio2 : Digital I/O 1 configuration.
 * @mode[in] dio3 : Digital I/O 1 configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_dio_irq_params ( lr6_t *ctx, uint16_t irq, uint16_t dio1, uint16_t dio2, uint16_t dio3 );

/**
 * @brief LR 6 get status function.
 * @details This function retrieves chip status directly through the command
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[out] status : Chip status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_get_status ( lr6_t *ctx, uint8_t *status );

/**
 * @brief LR 6 set RX function.
 * @details This function sets the desired RX timeout data values 
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] timeout : RX timeout data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_rx ( lr6_t *ctx, uint32_t timeout );

/**
 * @brief LR 6 set LoRa config function.
 * @details This function performs the desired LoRa configuration
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] lora_cfg : LoRa configuration object.
 * See #lr6_lora_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_lr_config ( lr6_t *ctx, lr6_lora_cfg_t lora_cfg );

/**
 * @brief LR 6 clear IRQ status function.
 * @details This function clears the desired IRQ status 
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] irq : IRQ status bitmask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_clear_irq_status ( lr6_t *ctx, uint16_t irq );

/**
 * @brief LR 6 set TX function.
 * @details This function sets the desired TX timeout data values 
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] timeout : TX timeout data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_set_tx ( lr6_t *ctx, uint32_t timeout );

/**
 * @brief LR 6 get IRQ status function.
 * @details This function retrieves IRQ status directly through the command
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[out] irq_status : IRQ status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_get_irq_status ( lr6_t *ctx, uint16_t *irq_status );

/**
 * @brief LR 6 send data function.
 * @details This function sends a desired number of data bytes to the buffer by using the selected mode
 * using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[in] send_data : Data to be sent.
 * @mode[in] len : Number of bytes to be sent.
 * @mode[in] mode : Mode selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_send_data ( lr6_t *ctx, uint8_t *send_data, uint8_t len, uint8_t mode );

/**
 * @brief LR 6 get RX buffer status function.
 * @details This function retrieves RX buffer status directly through the command
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[out] pl_len : Number of bytes of the payload.
 * @mode[out] rx_start_buff : RX start buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_get_rx_buff_status ( lr6_t *ctx, uint8_t *pl_len, uint8_t *rx_start_buff );

/**
 * @brief LR 6 receive data function.
 * @details This function receives a desired number of data bytes to the buffer 
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[out] receive_data : Received data.
 * @mode[in] len : Received buffer length.
 * @mode[in] rx_len : Number of bytes to be received.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_receive_data ( lr6_t *ctx, uint8_t *receive_data, uint16_t buff_len, uint8_t *rx_len );

/**
 * @brief LR 6 get packet status function.
 * @details This function retrieves packet status directly through the command
 * by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #lr6_t object definition for detailed explanation.
 * @mode[out] rssi : Average over last packet received of RSSI.
 * @mode[out] snr : Estimation of SNR on the last packet received.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr6_get_packet_status ( lr6_t *ctx, int8_t *rssi, int8_t *snr );

#ifdef __cplusplus
}
#endif
#endif // LR6_H

/*! @} */ // lr6

// ------------------------------------------------------------------------ END
