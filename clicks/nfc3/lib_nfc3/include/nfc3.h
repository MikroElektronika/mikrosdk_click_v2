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
 * @file nfc3.h
 * @brief This file contains API for NFC 3 Click Driver.
 */

#ifndef NFC3_H
#define NFC3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup nfc3 NFC 3 Click Driver
 * @brief API for configuring and manipulating NFC 3 Click driver.
 * @{
 */

/**
 * @defgroup nfc3_command NFC 3 Commands List
 * @brief List of registers of NFC 3 Click driver.
 */

/**
 * @addtogroup nfc3_command
 * @{
 */

/**
 * @brief NFC 3 commands description.
 * @details Specified command description of NFC 3 Click driver.
 */
#define NFC3_CMD_WRITE_REGISTER                     0x00
#define NFC3_CMD_WRITE_REGISTER_OR_MASK             0x01
#define NFC3_CMD_WRITE_REGISTER_AND_MASK            0x02
#define NFC3_CMD_WRITE_REGISTER_MULTIPLE            0x03
#define NFC3_CMD_READ_REGISTER                      0x04
#define NFC3_CMD_READ_REGISTER_MULTIPLE             0x05
#define NFC3_CMD_WRITE_EEPROM                       0x06
#define NFC3_CMD_READ_EEPROM                        0x07
#define NFC3_CMD_WRITE_TX_DATA                      0x08
#define NFC3_CMD_SEND_DATA                          0x09
#define NFC3_CMD_READ_DATA                          0x0A
#define NFC3_CMD_SWITCH_MODE                        0x0B
#define NFC3_CMD_MIFARE_AUTHENTICATE                0x0C
#define NFC3_CMD_EPC_INVENTORY                      0x0D
#define NFC3_CMD_EPC_RESUME_INVENTORY               0x0E
#define NFC3_CMD_EPC_RETRIEVE_INVENTORY_RESULT_SIZE 0x0F
#define NFC3_CMD_EPC_RETRIEVE_INVENTORY_RESULT      0x10
#define NFC3_CMD_LOAD_RF_CONFIG                     0x11
#define NFC3_CMD_UPDATE_RF_CONFIG                   0x12
#define NFC3_CMD_RETRIEVE_RF_CONFIG_SIZE            0x13
#define NFC3_CMD_RETRIEVE_RF_CONFIG                 0x14
#define NFC3_CMD_RF_ON                              0x16
#define NFC3_CMD_RF_OFF                             0x17
#define NFC3_CMD_CONFIGURE_TESTBUS_DIGITAL          0x18
#define NFC3_CMD_CONFIGURE_TESTBUS_ANALOG           0x19


/*! @} */ // nfc3_reg


/**
 * @defgroup nfc3_reg NFC 3 Registers List
 * @brief List of registers of NFC 3 Click driver.
 */

/**
 * @addtogroup nfc3_reg
 * @{
 */

/**
 * @brief NFC 3 register description.
 * @details Specified register description of NFC 3 Click driver.
 */
#define NFC3_REG_SYSTEM_CONFIG                      0x00
#define NFC3_REG_IRQ_ENABLE                         0x01
#define NFC3_REG_IRQ_STATUS                         0x02
#define NFC3_REG_IRQ_CLEAR                          0x03
#define NFC3_REG_TRANSCEIVER_CONFIG                 0x04
#define NFC3_REG_PADCONFIG                          0x05
#define NFC3_REG_PADOUT                             0x07
#define NFC3_REG_TIMER0_STATUS                      0x08
#define NFC3_REG_TIMER1_STATUS                      0x09
#define NFC3_REG_TIMER2_STATUS                      0x0A
#define NFC3_REG_TIMER0_RELOAD                      0x0B
#define NFC3_REG_TIMER1_RELOAD                      0x0C
#define NFC3_REG_TIMER2_RELOAD                      0x0D
#define NFC3_REG_TIMER0_CONFIG                      0x0E
#define NFC3_REG_TIMER1_CONFIG                      0x0F
#define NFC3_REG_TIMER2_CONFIG                      0x10
#define NFC3_REG_RX_WAIT_CONFIG                     0x11
#define NFC3_REG_CRC_RX_CONFIG                      0x12
#define NFC3_REG_RX_STATUS                          0x13
#define NFC3_REG_TX_UNDERSHOOT_CONFIG               0x14
#define NFC3_REG_TX_OVERSHOOT_CONFIG                0x15
#define NFC3_REG_TX_DATA_MOD                        0x16
#define NFC3_REG_TX_WAIT_CONFIG                     0x17
#define NFC3_REG_TX_CONFIG                          0x18
#define NFC3_REG_CRC_TX_CONFIG                      0x19
#define NFC3_REG_SIGPRO_CONFIG                      0x1A
#define NFC3_REG_SIGPRO_CM_CONFIG                   0x1B
#define NFC3_REG_SIGPRO_RM_CONFIG                   0x1C
#define NFC3_REG_RF_STATUS                          0x1D
#define NFC3_REG_AGC_CONFIG                         0x1E
#define NFC3_REG_AGC_VALUE                          0x1F
#define NFC3_REG_RF_CONTROL_TX                      0x20
#define NFC3_REG_RF_CONTROL_TX_CLK                  0x21
#define NFC3_REG_RF_CONTROL_RX                      0x22
#define NFC3_REG_LD_CONTROL                         0x23
#define NFC3_REG_SYSTEM_STATUS                      0x24
#define NFC3_REG_TEMP_CONTROL                       0x25
#define NFC3_REG_CECK_CARD_RESULT                   0x26
#define NFC3_REG_DPC_CONFIG                         0x27
#define NFC3_REG_EMD_CONTROL                        0x28
#define NFC3_REG_ANT_CONTROL                        0x29

/**
 * @brief NFC 3 EEPROM register description.
 * @details Specified EEPROM register description of NFC 3 Click driver.
 */
#define NFC3_EEPROM_DIE_ID                          0x00
#define NFC3_EEPROM_PRODUCT_VERSION                 0x10
#define NFC3_EEPROM_FIRMWARE_VERSION                0x12
#define NFC3_EEPROM_EEPROM_VERSION                  0x14
#define NFC3_EEPROM_IDLE_IRQ_AFTER_BOOT             0x16
#define NFC3_EEPROM_TESTBUS_ENABLE                  0x17
#define NFC3_EEPROM_XTAL_BOOT_TIME                  0x18
#define NFC3_EEPROM_IRQ_PIN_CONFIG                  0x1A
#define NFC3_EEPROM_MISO_PULLUP_ENABLE              0x1B
#define NFC3_EEPROM_PLL_DEFAULT_SETTING             0x1C
#define NFC3_EEPROM_PLL_DEFAULT_SETTING_ALM         0x24
#define NFC3_EEPROM_PLL_LOCK_SETTING                0x2C
#define NFC3_EEPROM_CLOCK_CONFIG                    0x30
#define NFC3_EEPROM_MFC_AUTH_TIMEOUT                0x32
#define NFC3_EEPROM_LPCD_REFERENCE_VALUE            0x34
#define NFC3_EEPROM_LPCD_FIELD_ON_TIME              0x36
#define NFC3_EEPROM_LPCD_THRESHOLD                  0x37
#define NFC3_EEPROM_LPCD_REFVAL_GPO_CONTROL         0x38
#define NFC3_EEPROM_LPCD_GPO_TOGGLE_BEFORE_FIELD_ON 0x39
#define NFC3_EEPROM_LPCD_GPO_TOGGLE_AFTER_FIELD_OFF 0x3A
#define NFC3_EEPROM_NFCLD_SENSITIVITY_VAL           0x3B
#define NFC3_EEPROM_FIELD_ON_CP_SETTLE_TIME         0x3C
#define NFC3_EEPROM_RF_DEBOUNCE_TIMEOUT             0x3F
#define NFC3_EEPROM_SENS_RES                        0x40
#define NFC3_EEPROM_NFCID1                          0x42
#define NFC3_EEPROM_SEL_RES                         0x45
#define NFC3_EEPROM_FELICA_POLLING_RESPONSE         0x46
#define NFC3_EEPROM_RANDOMUID_ENABLE                0x51
#define NFC3_EEPROM_RANDOM_UID_ENABLE               0x58
#define NFC3_EEPROM_DPC_CONTROL                     0x59
#define NFC3_EEPROM_DPC_TIME                        0x5A
#define NFC3_EEPROM_DPC_XI                          0x5C
#define NFC3_EEPROM_AGC_CONTROL                     0x5D
#define NFC3_EEPROM_DPC_THRSH_HIGH                  0x5F
#define NFC3_EEPROM_DPC_THRSH_LOW                   0x7D
#define NFC3_EEPROM_DPC_DEBUG                       0x7F
#define NFC3_EEPROM_DPC_AGC_SHIFT_VALUE             0x80
#define NFC3_EEPROM_DPC_AGC_GEAR_LUT_SIZE           0x81
#define NFC3_EEPROM_DPC_AGC_GEAR_LUT                0x82
#define NFC3_EEPROM_DPC_GUARD_FAST_MODE             0x91
#define NFC3_EEPROM_DPC_GUARD_SOF_DETECTED          0x93
#define NFC3_EEPROM_DPC_GUARD_FIELD_ON              0x95
#define NFC3_EEPROM_PCD_AWC_DRC_LUT_SIZE            0x97
#define NFC3_EEPROM_PCD_AWC_DRC_LUT                 0x98
#define NFC3_EEPROM_MISC_CONFIG                     0xE8
#define NFC3_EEPROM_DIGIDELAY_A_848_RW              0xE9
#define NFC3_EEPROM_DIGIDELAY_B_848_RW              0xEA
#define NFC3_EEPROM_DIGIDELAY_F_424_RW              0xEB
#define NFC3_EEPROM_DIGIDELAY_15693_RW_FASTHIGH     0xEC
#define NFC3_EEPROM_DIGIDELAY_18000_2_848           0xED
#define NFC3_EEPROM_DIGIDELAY_18000_4_848           0xEE
#define NFC3_EEPROM_TESTBUSMODE                     0xF0
#define NFC3_EEPROM_TBSELECT                        0xF1
#define NFC3_EEPROM_MAPTB1_TO_TB0                   0xF2
#define NFC3_EEPROM_NUMPADSIGNALMAPS                0xF3
#define NFC3_EEPROM_PADSIGNALMAP                    0xF4
#define NFC3_EEPROM_TBDAC1                          0xF5
#define NFC3_EEPROM_TBDAC2                          0xF6

/*! @} */ // nfc3_reg

/**
 * @defgroup nfc3_set NFC 3 Registers Settings
 * @brief Settings for registers of NFC 3 Click driver.
 */

/**
 * @addtogroup nfc3_set
 * @{
 */

/**
 * @brief NFC 3 setting description.
 * @details Specified setting for description of NFC 3 Click driver.
 */
#define NFC3_RX_IRQ_STAT                            (1<<0)  // End of RF rececption IRQ
#define NFC3_TX_IRQ_STAT                            (1<<1)  // End of RF transmission IRQ
#define NFC3_IDLE_IRQ_STAT                          (1<<2)  // IDLE IRQ
#define NFC3_RFOFF_DET_IRQ_STAT                     (1<<6)  // RF Field OFF detection IRQ
#define NFC3_RFON_DET_IRQ_STAT                      (1<<7)  // RF Field ON detection IRQ
#define NFC3_TX_RFOFF_IRQ_STAT                      (1<<8)  // RF Field OFF in PCD IRQ
#define NFC3_TX_RFON_IRQ_STAT                       (1<<9)  // RF Field ON in PCD IRQ
#define NFC3_RX_SOF_DET_IRQ_STAT                    (1<<14) // RF SOF Detection IRQ
#define NFC3_GENERAL_ERROR_IRQ_STAT                 (1ul<<17) // General error IRQ
#define NFC3_LPCD_IRQ_STAT                          (1ul<<19) // LPCD Detection IRQ
/*! @} */ // nfc3_set

/**
 * @defgroup nfc3_map NFC 3 MikroBUS Map
 * @brief MikroBUS pin mapping of NFC 3 Click driver.
 */

/**
 * @addtogroup nfc3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NFC 3 Click to the selected MikroBUS.
 */
#define NFC3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.aux = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.bsy = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nfc3_map
/*! @} */ // nfc3

/**
 * @brief NFC 3 Click context object.
 * @details Context object definition of NFC 3 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t rst;          /**< Reset pin (Active low). */

    // Input pins

    digital_in_t  aux;          /**< Analog test bus or Download request pin. */
    digital_in_t  bsy;          /**< Busy pin. */
    digital_in_t  irq;          /**< Interrupt request pin. */

    // Modules

    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} nfc3_t;

/**
 * @brief NFC 3 Click configuration object.
 * @details Configuration object definition of NFC 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins

    pin_name_t  aux;            /**< Analog test bus or Download request pin. */
    pin_name_t  rst;            /**< Reset pin (Active low). */
    pin_name_t  bsy;            /**< Busy pin. */
    pin_name_t  irq;            /**< Interrupt request pin. */

    // static variable

    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} nfc3_cfg_t;

/**
 * @brief NFC 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NFC3_OK = 0,
    NFC3_ERROR = -1

} nfc3_return_value_t;

/**
 * @brief NFC 3 Click transceive status value data.
 * @details Predefined enum values for transceive status values.
 */
typedef enum 
{
    NFC3_TS_IDLE = 0,
    NFC3_TS_WAIT_TRANSMIT = 1,
    NFC3_TS_TRANSMITTING = 2,
    NFC3_TS_WAIT_RECEIVE = 3,
    NFC3_TS_WAIT_FOR_DATA = 4,
    NFC3_TS_RECEIVING = 5,
    NFC3_TS_LOOPBACK = 6,
    NFC3_TS_RESERVED = 7
    
} nfc3_transceive_stat_t;

/*!
 * @addtogroup nfc3 NFC 3 Click Driver
 * @brief API for configuring and manipulating NFC 3 Click driver.
 * @{
 */

/**
 * @brief NFC 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nfc3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nfc3_cfg_setup ( nfc3_cfg_t *cfg );

/**
 * @brief NFC 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nfc3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_init ( nfc3_t *ctx, nfc3_cfg_t *cfg );

/**
 * @brief NFC 3 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_generic_write ( nfc3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief NFC 3 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_generic_transfer ( nfc3_t *ctx, uint8_t *data_in, uint8_t tx_len, uint8_t *data_out, uint8_t rx_len );

/**
 * @brief NFC 3 writing EEPROM function.
 * @details This function writes a desired number of data bytes to EEPROM starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_write_eeprom ( nfc3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief NFC 3 reading EEPROM function.
 * @details This function reads a desired number of data bytes from EEPROM starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_read_eeprom ( nfc3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief NFC 3 writing register function with AND mask.
 * @details This function writes 32-bit data to the selected register with AND mask
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_write_reg_with_and_mask ( nfc3_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief NFC 3 writing register function with OR mask.
 * @details This function writes 32-bit data to the selected register with OR mask 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_write_reg_with_or_mask ( nfc3_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief NFC 3 writing register function.
 * @details This function writes 32-bit data to the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_write_reg ( nfc3_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief NFC 3 reading register function.
 * @details This function reads 32-bit data from the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_read_reg ( nfc3_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief NFC 3 send data function.
 * @details This function writes data to the RF transmission buffer and starts the RF transmission.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @param[in] valid_bits : Indicates the exact number of bits to be transmitted for the last byte (for non-byte aligned frames).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_send_data ( nfc3_t *ctx, uint8_t *data_in, uint16_t len, uint8_t valid_bits );

/**
 * @brief NFC 3 read data function.
 * @details This function reads data from the RF reception buffer, after a successful reception.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[out] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_read_data ( nfc3_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NFC 3 load RF config function.
 * @details This function loads desired RF config.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[out] tx_conf : Transmitter Configuration.
 * @param[out] rx_conf : Receiver Configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_load_rf_config ( nfc3_t *ctx, uint8_t tx_conf, uint8_t rx_conf );

/**
 * @brief NFC 3 reading firmware version function.
 * @details This function reads the firmware version from 
 * the desired EEPROM register.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_read_firmware_version ( nfc3_t *ctx, uint16_t *data_out );

/**
 * @brief NFC 3 reading product version function.
 * @details This function reads the product version from 
 * the desired EEPROM register.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_read_product_version ( nfc3_t *ctx, uint16_t *data_out );

/**
 * @brief NFC 3 reading EEPROM version function.
 * @details This function reads the EEPROM version from 
 * the desired EEPROM register.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_read_eeprom_version ( nfc3_t *ctx, uint16_t *data_out );

/**
 * @brief NFC 3 reset function.
 * @details This function performs the device reset.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void nfc3_reset ( nfc3_t *ctx );

/**
 * @brief NFC 3 set RST pin function.
 * @details This function sets RST pin to the desired state.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 * @return None.
 * @note None.
 */
void nfc3_set_rst ( nfc3_t *ctx, uint8_t state );

/**
 * @brief NFC 3 get IRQ pin function.
 * @details This function gets IRQ pin state.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nfc3_get_irq ( nfc3_t *ctx );

/**
 * @brief NFC 3 get BSY pin function.
 * @details This function gets BSY pin state.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nfc3_get_bsy ( nfc3_t *ctx );

/**
 * @brief NFC 3 get AUX pin function.
 * @details This function gets AUX pin state.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nfc3_get_aux ( nfc3_t *ctx );

/**
 * @brief NFC 3 get TRANSCEIVE_STATE from RF_STATUS register function.
 * @details This function reads TRANSCEIVE_STATE from RF_STATUS register.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - idle,
 *         @li @c  1 - wait transmit,
 *         @li @c  2 - transmitting,
 *         @li @c  3 - wait receive,
 *         @li @c  4 - wait for data,
 *         @li @c  5 - receiving,
 *         @li @c  6 - loopback,
 *         @li @c  7 - reserved.
 * See nfc3_transceive_stat_t definition for detailed explanation.
 * @note None.
 */
nfc3_transceive_stat_t nfc3_get_transceive_state ( nfc3_t *ctx );

/**
 * @brief NFC 3 get number of received bytes function.
 * @details This function reads the number of bytes received.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @return Number of data bytes received.
 * @note None.
 */
uint16_t nfc3_rx_num_bytes_received( nfc3_t *ctx );

/**
 * @brief NFC 3 activate ISO/IEC 14443 type A and read card UID function.
 * @details This function activates ISO/IEC 14443 type A and reads card UID.
 * @param[in] ctx : Click context object.
 * @param[out] data_out : Card serial must be 10 byte array:
 *                        data_out[0-1] is ATQA
 *                        data_out[2] is sak
 *                        data_out[3-6] is 4 byte UID
 *                        data_out[7-9] is remaining 3 bytes of UID for 7 Byte UID tags
 * @param[in] kind : 0 we send REQA, 1 we send WUPA
 * See #nfc3_t object definition for detailed explanation.
 * @return @li @c  0 - no tag was recognized,
 *         @li @c  4 - single Size UID (4 byte),
 *         @li @c  7 - double Size UID (7 byte).
 * @note None.
 */
uint8_t nfc3_activate_type_a ( nfc3_t *ctx, uint8_t *data_out, uint8_t kind );

/**
 * @brief NFC 3 MIFARE block read function.
 * @details This function reads a desired block of memory from MIFARE card.
 * @param[in] ctx : Click context object.
 * @param[out] data_out : The block content (16 bytes).
 * @param[in] blockno : Number of the block.
 * See #nfc3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_mifare_block_read( nfc3_t *ctx, uint8_t *data_out, uint8_t blockno );

/**
 * @brief NFC 3 MIFARE block write function.
 * @details This function writes 16 bytes data to a desired block of memory of MIFARE card.
 * @param[in] ctx : Click context object.
 * @param[in] data_out : Data to be written.
 * @param[in] blockno : Number of the block.
 * See #nfc3_t object definition for detailed explanation.
 * @return ACK/NAK value
 * @note None.
 */
uint8_t nfc3_mifare_block_write_16( nfc3_t *ctx, uint8_t *data_in, uint8_t blockno );

/**
 * @brief NFC 3 MIFARE Halt function.
 * @details This function halts MIFARE card.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_mifare_halt( nfc3_t *ctx );

/**
 * @brief NFC 3 read card UID function.
 * @details This function reads card UID.
 * @param[in] ctx : Click context object.
 * @param[out] data_out : Card UID must be 7 byte array:
 *                        data_out[0-3] is 4 byte UID
 *                        data_out[4-6] is remaining 3 bytes of UID for 7 Byte UID tags
 * See #nfc3_t object definition for detailed explanation.
 * @return @li @c  0 - no tag was recognized,
 *         @li @c  4 - single Size UID (4 byte),
 *         @li @c  7 - double Size UID (7 byte).
 * @note None.
 */
uint8_t nfc3_read_card_uid ( nfc3_t *ctx, uint8_t *data_out );

/**
 * @brief NFC 3 clear RX and TX CRC function.
 * @details This function clears RX and TX CRC.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_clear_rx_tx_crc ( nfc3_t *ctx );

/**
 * @brief NFC 3 enable RX and TX CRC calculation function.
 * @details This function enables RX and TX CRC calculation.
 * @param[in] ctx : Click context object.
 * See #nfc3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc3_enable_rx_tx_crc ( nfc3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // NFC3_H

/*! @} */ // nfc3

// ------------------------------------------------------------------------ END
