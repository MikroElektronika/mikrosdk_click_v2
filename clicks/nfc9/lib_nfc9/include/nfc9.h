/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file nfc9.h
 * @brief This file contains API for NFC 9 Click Driver.
 */

#ifndef NFC9_H
#define NFC9_H

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
 * @addtogroup nfc9 NFC 9 Click Driver
 * @brief API for configuring and manipulating NFC 9 Click driver.
 * @{
 */

/**
 * @defgroup nfc9_reg NFC 9 Registers List
 * @brief List of registers of NFC 9 Click driver.
 */

/**
 * @addtogroup nfc9_reg
 * @{
 */

/**
 * @brief NFC 9 registers list.
 * @details Specified registers list of NFC 9 Click driver.
 */
#define NFC9_REG_OPERATION_CONTROL              0x00
#define NFC9_REG_MODE                           0x01
#define NFC9_REG_BIT_RATE                       0x02
#define NFC9_REG_ISO14443A_NFC                  0x03
#define NFC9_REG_ISO14443B_1                    0x04
#define NFC9_REG_ISO14443B_2                    0x05
#define NFC9_REG_ISO14443B_3                    0x06
#define NFC9_REG_STREAM_MODE                    0x07
#define NFC9_REG_AUX                            0x08
#define NFC9_REG_RECEIVER_CONF_1                0x09
#define NFC9_REG_RECEIVER_CONF_2                0x0A
#define NFC9_REG_RECEIVER_CONF_3                0x0B
#define NFC9_REG_RECEIVER_CONF_4                0x0C
#define NFC9_REG_MASK_RX_TIMER                  0x0D
#define NFC9_REG_NO_RESPONSE_TIMER_1            0x0E
#define NFC9_REG_NO_RESPONSE_TIMER_2            0x0F
#define NFC9_REG_GPT_1                          0x10
#define NFC9_REG_GPT_2                          0x11
#define NFC9_REG_MASK_RX_TIMER_2                0x12
#define NFC9_REG_TX_DRIVER                      0x13
#define NFC9_REG_PT_MOD                         0x14
#define NFC9_REG_AUX_MOD                        0x15
#define NFC9_REG_TX_DRIVER_TIMING               0x16
#define NFC9_REG_RES_AM_MOD                     0x17
#define NFC9_REG_RX_WAIT                        0x18
#define NFC9_REG_CHANNEL                        0x19
#define NFC9_REG_CORRELATOR                     0x1A
#define NFC9_REG_RX_CONF_5                      0x1B
#define NFC9_REG_RX_CONF_6                      0x1C
#define NFC9_REG_RX_CONF_7                      0x1D
#define NFC9_REG_IO_CONF_1                      0x1E
#define NFC9_REG_IO_CONF_2                      0x1F
#define NFC9_REG_TX_MODULATION_DEPTH            0x20
#define NFC9_REG_WUP_TIMER_CONTROL              0x21
#define NFC9_REG_AMPLITUDE_MEASURE_REF          0x22
#define NFC9_REG_AMPLITUDE_MEASURE_AA           0x23
#define NFC9_REG_AMPLITUDE_MEASURE_AB           0x24
#define NFC9_REG_AMPLITUDE_MEASURE_SQUELCH      0x25
#define NFC9_REG_PHASE_MEASURE_REF              0x26
#define NFC9_REG_PHASE_MEASURE_AA               0x27
#define NFC9_REG_PHASE_MEASURE_AB               0x28
#define NFC9_REG_CAPACITANCE_MEASURE_REF        0x29
#define NFC9_REG_CAPACITANCE_MEASURE_AA         0x2A
#define NFC9_REG_CAPACITANCE_MEASURE_AB         0x2B
#define NFC9_REG_AUX_DISPLAY                    0x2C
#define NFC9_REG_OVERSHOOT_CONF_1               0x2D
#define NFC9_REG_OVERSHOOT_CONF_2               0x2E
#define NFC9_REG_UNDERSHOOT_CONF_1              0x2F
#define NFC9_REG_UNDERSHOOT_CONF_2              0x30
#define NFC9_REG_REGULATOR_CONTROL              0x31
#define NFC9_REG_REGULATOR_RESULT               0x32
#define NFC9_REG_RSSI_RESULT                    0x33
#define NFC9_REG_GAIN_REDUCTION_STATE           0x34
#define NFC9_REG_CAPACITIVE_SENSOR_CONTROL      0x35
#define NFC9_REG_FIFO_STATUS_1                  0x36
#define NFC9_REG_FIFO_STATUS_2                  0x37
#define NFC9_REG_RX_COLLISION_DISPLAY           0x38
#define NFC9_REG_IRQ_MASK_1                     0x39
#define NFC9_REG_IRQ_MASK_2                     0x3A
#define NFC9_REG_IRQ_MASK_3                     0x3B
#define NFC9_REG_IRQ_STATUS_1                   0x3C
#define NFC9_REG_IRQ_STATUS_2                   0x3D
#define NFC9_REG_IRQ_STATUS_3                   0x3E
#define NFC9_REG_IC_IDENTITY                    0x3F
#define NFC9_REG_STATUS_1                       0x40
#define NFC9_REG_STATUS_2                       0x41
#define NFC9_REG_STATIC_STATUS_1                0x42
#define NFC9_REG_STATIC_STATUS_2                0x43
#define NFC9_REG_STATIC_STATUS_3                0x44

/*! @} */ // nfc9_reg

/**
 * @defgroup nfc9_set NFC 9 Registers Settings
 * @brief Settings for registers of NFC 9 Click driver.
 */

/**
 * @addtogroup nfc9_set
 * @{
 */

/**
 * @brief NFC 9 command settings.
 * @details Specified command settings of NFC 9 Click driver.
 */
#define NFC9_SPI_DUMMY_BYTE                     0x00
#define NFC9_SPI_WRITE_MODE                     0x00
#define NFC9_SPI_READ_MODE                      0x80
#define NFC9_SPI_CMD_MODE                       0x00
#define NFC9_SPI_FIFO_WRITE                     0x5F
#define NFC9_SPI_FIFO_READ                      0xDF
#define NFC9_REG_ADDR_MASK                      0x7F
#define NFC9_CMD_MASK                           0xFF
#define NFC9_FIFO_SIZE                          256

/**
 * @brief NFC 9 IC identity setting.
 * @details Specified IC identity setting of NFC 9 Click driver.
 */
#define NFC9_IC_IDENTITY_TYPE                   0xB0
#define NFC9_IC_IDENTITY_TYPE_MASK              0xF8
#define NFC9_IC_IDENTITY_REV                    0x01
#define NFC9_IC_IDENTITY_REV_MASK               0x07

/**
 * @brief NFC 9 direct command settings.
 * @details Specified direct command settings of NFC 9 Click driver.
 */
#define NFC9_CMD_SET_DEFAULT                    0x60
#define NFC9_CMD_STOP                           0x62
#define NFC9_CMD_CLEAR_FIFO                     0x64
#define NFC9_CMD_CLEAR_RXGAIN                   0x66
#define NFC9_CMD_ADJUST_REGULATORS              0x68
#define NFC9_CMD_TRANSMIT                       0x6A
#define NFC9_CMD_TRANSMIT_EOF                   0x6C
#define NFC9_CMD_NFC_FIELD_ON                   0x6E
#define NFC9_CMD_MASK_RECEIVE_DATA              0x70
#define NFC9_CMD_UNMASK_RECEIVE_DATA            0x72
#define NFC9_CMD_CALIBRATE_WU                   0x74
#define NFC9_CMD_CLEAR_WU_CALIB                 0x76
#define NFC9_CMD_MEASURE_WU                     0x78
#define NFC9_CMD_MEASURE_IQ                     0x7A
#define NFC9_CMD_SENSE_RF                       0x7C
#define NFC9_CMD_TRIGGER_WU_EV                  0x7E
#define NFC9_CMD_START_GP_TIMER                 0xE2
#define NFC9_CMD_START_WUT                      0xE4
#define NFC9_CMD_START_MRT                      0xE6
#define NFC9_CMD_START_NRT                      0xE8
#define NFC9_CMD_STOP_NRT                       0xEA
#define NFC9_CMD_CALIBRATE_RC                   0xEE
#define NFC9_CMD_TRIGGER_DIAG                   0xF8
#define NFC9_CMD_TEST_ACCESS                    0xFC

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU.
 * Can be overwritten with @b nfc9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define NFC9_SET_DATA_SAMPLE_EDGE               SET_SPI_DATA_SAMPLE_EDGE
#define NFC9_SET_DATA_SAMPLE_MIDDLE             SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // nfc9_set

/**
 * @defgroup nfc9_map NFC 9 MikroBUS Map
 * @brief MikroBUS pin mapping of NFC 9 Click driver.
 */

/**
 * @addtogroup nfc9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NFC 9 Click to the selected MikroBUS.
 */
#define NFC9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.irq  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nfc9_map
/*! @} */ // nfc9

/**
 * @brief NFC 9 Click context object.
 * @details Context object definition of NFC 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Reset pin (active low). */

    // Input pins
    digital_in_t irq;                           /**< Interrupt request pin. */

    // Modules
    spi_master_t spi;                           /**< SPI driver object. */

    pin_name_t   chip_select;                   /**< Chip select pin descriptor (used for SPI driver). */

} nfc9_t;

/**
 * @brief NFC 9 Click tag data object.
 * @details Tag data object definition of NFC 9 Click driver.
 */
typedef struct
{
    uint16_t atqa;                               /**< Tag ATQA word. */
    uint8_t sak;                                 /**< Tag SAK byte. */
    uint8_t *uid;                                /**< Tag UID/NFCID buffer. */
    uint8_t uid_len;                             /**< Tag UID/NFCID length. */

} nfc9_tag_t;

/**
 * @brief NFC 9 Click configuration object.
 * @details Configuration object definition of NFC 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;                             /**< Reset pin (active low). */
    pin_name_t irq;                             /**< Interrupt request pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} nfc9_cfg_t;

/**
 * @brief NFC 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NFC9_OK = 0,
    NFC9_ERROR = -1

} nfc9_return_value_t;

/*!
 * @addtogroup nfc9 NFC 9 Click Driver
 * @brief API for configuring and manipulating NFC 9 Click driver.
 * @{
 */

/**
 * @brief NFC 9 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nfc9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nfc9_cfg_setup ( nfc9_cfg_t *cfg );

/**
 * @brief NFC 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nfc9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc9_init ( nfc9_t *ctx, nfc9_cfg_t *cfg );

/**
 * @brief NFC 9 default configuration function.
 * @details This function executes a default configuration of NFC 9 Click
 * board.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t nfc9_default_cfg ( nfc9_t *ctx );

/**
 * @brief NFC 9 generic write function.
 * @details This function writes a generic data buffer by using SPI serial
 * interface.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc9_generic_write ( nfc9_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NFC 9 generic read function.
 * @details This function reads a generic data buffer by using SPI serial
 * interface.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @param[out] data_out : Data buffer.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc9_generic_read ( nfc9_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NFC 9 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc9_register_write ( nfc9_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief NFC 9 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc9_register_read ( nfc9_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief NFC 9 register set bits function.
 * @details This function sets selected bits in the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] mask : Bit mask to set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc9_register_set_bits ( nfc9_t *ctx, uint8_t reg, uint8_t mask );

/**
 * @brief NFC 9 register clear bits function.
 * @details This function clears selected bits in the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] mask : Bit mask to clear.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc9_register_clear_bits ( nfc9_t *ctx, uint8_t reg, uint8_t mask );

/**
 * @brief NFC 9 direct command function.
 * @details This function sends a direct command to the device.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @param[in] command : Direct command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc9_direct_command ( nfc9_t *ctx, uint8_t command );

/**
 * @brief NFC 9 FIFO write function.
 * @details This function writes data to the FIFO.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc9_fifo_write ( nfc9_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NFC 9 FIFO read function.
 * @details This function reads data from the FIFO.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @param[out] data_out : Data buffer.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc9_fifo_read ( nfc9_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NFC 9 check communication function.
 * @details This function reads and checks the IC identity register.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc9_check_com ( nfc9_t *ctx );

/**
 * @brief NFC 9 device reset function.
 * @details This function performs a hardware reset through the RST pin.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void nfc9_reset_device ( nfc9_t *ctx );

/**
 * @brief NFC 9 interrupt pin state function.
 * @details This function reads the interrupt pin logic state.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nfc9_get_irq_pin ( nfc9_t *ctx );

/**
 * @brief NFC 9 read tag information function.
 * @details This function reads NFC-A basic tag information such as ATQA, SAK and UID.
 * @param[in] ctx : Click context object.
 * See #nfc9_t object definition for detailed explanation.
 * @param[out] tag : Pointer to tag information object.
 * See #nfc9_tag_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc9_read_tag ( nfc9_t *ctx, nfc9_tag_t *tag );

#ifdef __cplusplus
}
#endif
#endif // NFC9_H

/*! @} */ // nfc9

// ------------------------------------------------------------------------ END
