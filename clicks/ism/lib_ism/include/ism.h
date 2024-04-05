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
 * @file ism.h
 * @brief This file contains API for ISM Click Driver.
 */

#ifndef ISM_H
#define ISM_H

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

/*!
 * @addtogroup ism ISM Click Driver
 * @brief API for configuring and manipulating ISM Click driver.
 * @{
 */

/**
 * @defgroup ism_reg ISM Registers List
 * @brief List of registers of ISM Click driver.
 */

/**
 * @addtogroup ism_reg
 * @{
 */

/**
 * @brief ISM description register.
 * @details Specified register for description of ISM Click driver.
 */
#define ISM_REG_BANK_0_CONFIG               0x00 
#define ISM_REG_BANK_0_EN_AA                0x01 
#define ISM_REG_BANK_0_EN_RXADDR            0x02 
#define ISM_REG_BANK_0_SETUP_AW             0x03 
#define ISM_REG_BANK_0_SETUP_RETR           0x04 
#define ISM_REG_BANK_0_RF_CH                0x05 
#define ISM_REG_BANK_0_RF_SETUP             0x06 
#define ISM_REG_BANK_0_STATUS               0x07 
#define ISM_REG_BANK_0_OBSERVE_TX           0x08 
#define ISM_REG_BANK_0_CD                   0x09 
#define ISM_REG_BANK_0_RX_ADDR_P0           0x0A 
#define ISM_REG_BANK_0_RX_ADDR_P1           0x0B 
#define ISM_REG_BANK_0_RX_ADDR_P2           0x0C 
#define ISM_REG_BANK_0_RX_ADDR_P3           0x0D 
#define ISM_REG_BANK_0_RX_ADDR_P4           0x0E 
#define ISM_REG_BANK_0_RX_ADDR_P5           0x0F 
#define ISM_REG_BANK_0_TX_ADDR              0x10 
#define ISM_REG_BANK_0_RX_PW_P0             0x11 
#define ISM_REG_BANK_0_RX_PW_P1             0x12 
#define ISM_REG_BANK_0_RX_PW_P2             0x13 
#define ISM_REG_BANK_0_RX_PW_P3             0x14 
#define ISM_REG_BANK_0_RX_PW_P4             0x15 
#define ISM_REG_BANK_0_RX_PW_P5             0x16 
#define ISM_REG_BANK_0_FIFO_STATUS          0x17 
#define ISM_REG_BANK_0_PAYLOAD_WIDTH        0x1F 
#define ISM_REG_BANK_1_REG_0                0x00 
#define ISM_REG_BANK_1_REG_1                0x01 
#define ISM_REG_BANK_1_REG_2                0x02 
#define ISM_REG_BANK_1_REG_3                0x03 
#define ISM_REG_BANK_1_REG_4                0x04 
#define ISM_REG_BANK_1_REG_5                0x05 
#define ISM_REG_BANK_1_REG_6                0x06 
#define ISM_REG_BANK_1_REG_7                0x07 
#define ISM_REG_BANK_1_REG_8                0x08 
#define ISM_REG_BANK_1_REG_9                0x09 
#define ISM_REG_BANK_1_REG_A                0x0A 
#define ISM_REG_BANK_1_REG_B                0x0B 
#define ISM_REG_BANK_1_REG_C                0x0C 
#define ISM_REG_BANK_1_REG_D                0x0D 
#define ISM_REG_BANK_1_REG_E                0x0E

/*! @} */ // ism_reg

/**
 * @addtogroup ism_cmd
 * @{
 */

/**
 * @brief ISM description commands.
 * @details Specified commands for description of ISM Click driver.
 */
#define ISM_CMD_FLUSH_TX                    0xE1  
#define ISM_CMD_FLUSH_RX                    0xE2  
#define ISM_CMD_REUSE_TX_PL                 0xE3  
#define ISM_CMD_W_TX_PAYLOAD_NOACK          0xB0
#define ISM_CMD_W_ACK_PAYLOAD               0xA8
#define ISM_CMD_ACTIVATE                    0x50
#define ISM_CMD_R_RX_PL_WID                 0x60
#define ISM_CMD_NOP_NOP                     0xFF 

/*! @} */ // ism_cmd

/**
 * @defgroup ism_set ISM Registers Settings
 * @brief Settings for registers of ISM Click driver.
 */

/**
 * @addtogroup ism_set
 * @{
 */

/**
 * @brief ISM description setting.
 * @details Specified setting for description of ISM Click driver.
 */
#define ISM_STATUS_RX_DR                    0x40
#define ISM_STATUS_TX_DS                    0x20
#define ISM_STATUS_MAX_RT                   0x10
#define STATUS_TX_FULL                      0x01
#define ISM_FIFO_STATUS_TX_REUSE            0x40
#define ISM_FIFO_STATUS_TX_FULL             0x20
#define ISM_FIFO_STATUS_TX_EMPTY            0x10
#define ISM_FIFO_STATUS_RX_FULL             0x02
#define ISM_FIFO_STATUS_RX_EMPTY            0x01

/**
 * @brief ISM description bank selection.
 * @details Specified setting for bank selection of ISM Click driver.
 */
#define ISM_SEL_BANK_0                         0  
#define ISM_SEL_BANK_1                         1 

/**
 * @brief ISM maximum packet length.
 * @details Specified setting for maximum packet length of ISM Click driver.
 */
#define ISM_MAX_PACKET_LEN                    32
 
/**
 * @brief ISM description pin state.
 * @details Specified setting for pin state of ISM Click driver.
 */ 
#define ISM_RT_PIN_STATE_LOW                   0
#define ISM_RT_PIN_STATE_HIGH                  1

/**
 * @brief ISM description RX and TX payload.
 * @details Specified setting for RX and TX of ISM Click driver.
 */ 
#define ISM_RD_RX_PLOAD                     0x61  
#define ISM_WR_TX_PLOAD                     0xA0

/**
 * @brief ISM description SPI read and write bit mask.
 * @details Specified setting for SPI read and write bit mask of ISM Click driver.
 */
#define ISM_READ_BIT_MASK                   0x00 
#define ISM_WRITE_BIT_MASK                  0x20

/*! @} */ // ism_set

/**
 * @defgroup ism_map ISM MikroBUS Map
 * @brief MikroBUS pin mapping of ISM Click driver.
 */

/**
 * @addtogroup ism_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISM Click to the selected MikroBUS.
 */
#define ISM_MAP_MIKROBUS( cfg, mikrobus )           \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.tl = MIKROBUS( mikrobus, MIKROBUS_AN );     \
    cfg.ce = MIKROBUS( mikrobus, MIKROBUS_RST );    \
    cfg.rl = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ism_map
/*! @} */ // ism

/**
 * @brief ISM Click context object.
 * @details Context object definition of ISM Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  tl;          /**< TX LED pin. */
    digital_out_t  ce;          /**< Chip Enable pin. */
    digital_out_t  rl;          /**< RX LED pin. */

    // Input pins
    digital_in_t  irq;          /**< Interrupt Request pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} ism_t;

/**
 * @brief ISM Click configuration object.
 * @details Configuration object definition of ISM Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  tl;             /**< TX LED pin. */
    pin_name_t  ce;             /**< Chip Enable pin. */
    pin_name_t  rl;             /**< RX LED pin. */
    pin_name_t  irq;            /**< Interrupt Request pin. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} ism_cfg_t;

/**
 * @brief ISM Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   ISM_OK = 0,
   ISM_ERROR = -1

} ism_return_value_t;

/*!
 * @addtogroup ism ISM Click Driver
 * @brief API for configuring and manipulating ISM Click driver.
 * @{
 */

/**
 * @brief ISM configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ism_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ism_cfg_setup ( ism_cfg_t *cfg );

/**
 * @brief ISM initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ism_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism_init ( ism_t *ctx, ism_cfg_t *cfg );

/**
 * @brief ISM default configuration function.
 * @details This function executes a default configuration of ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void ism_default_cfg ( ism_t *ctx );

/**
 * @brief ISM data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism_generic_write ( ism_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ISM data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism_generic_read ( ism_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ISM set command function.
 * @details This function writes a desired command data by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @param[in] cmd : Command register address.
 * @param[in] cmd_data : Command data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism_set_cmd ( ism_t *ctx, uint8_t cmd, uint8_t cmd_data );

/**
 * @brief ISM set chip enable function.
 * @details This function set chip enable of the 
 * RFM75, Low Power High Performance 2.4 GHz GFSK Transceiver on the 
 * ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @return Noting
 * @note None.
 */
void ism_chip_enable ( ism_t *ctx );

/**
 * @brief ISM set chip disable function.
 * @details This function set chip disable of the 
 * RFM75, Low Power High Performance 2.4 GHz GFSK Transceiver on the 
 * ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void ism_chip_disable ( ism_t *ctx );

/**
 * @brief ISM RL pin setting function.
 * @details This function sets the RL pin state to the desired level of the 
 * RFM75, Low Power High Performance 2.4 GHz GFSK Transceiver on the 
 * ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @param[in] rt_pin_state : 
 *    @li @c 0 ( ISM_RT_PIN_STATE_LOW )  - Set pin state on the low level,
 *    @li @c 1 ( ISM_RT_PIN_STATE_HIGH ) - Set pin state on the high level.
 * @return Nothing.
 * @note None.
 */
void ism_set_rl_pin_state ( ism_t *ctx, uint8_t rt_pin_state );

/**
 * @brief ISM TL pin setting function.
 * @details This function sets the TL pin state to the desired level of the 
 * RFM75, Low Power High Performance 2.4 GHz GFSK Transceiver on the 
 * ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @param[in] tl_pin_state : 
 *    @li @c 0 ( ISM_RT_PIN_STATE_LOW )  - Set pin state on the low level,
 *    @li @c 1 ( ISM_RT_PIN_STATE_HIGH ) - Set pin state on the high level.
 * @return Nothing.
 * @note None.
 */
void ism_set_tl_pin_state ( ism_t *ctx, uint8_t tl_pin_state );

/**
 * @brief ISM check interrupt request function.
 * @details This function check interrupt request, get states of the IRQ ( INT ) pin of the 
 * RFM75, Low Power High Performance 2.4 GHz GFSK Transceiver on the 
 * ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t ism_check_interrupt_request ( ism_t *ctx );

/**
 * @brief ISM switch bank function.
 * @details This function switch to the desire register bank of the 
 * RFM75, Low Power High Performance 2.4 GHz GFSK Transceiver on the 
 * ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @param[in] bank_sel : Bank selection
 *         @li @c 0 - Register Bank 0,
 *         @li @c 1 - Register Bank 1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism_switch_bank ( ism_t *ctx, uint8_t bank_sel );

/**
 * @brief ISM switch RX mode function.
 * @details This function switch to RX mode of the 
 * RFM75, Low Power High Performance 2.4 GHz GFSK Transceiver on the 
 * ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism_switch_rx_mode ( ism_t *ctx );

/**
 * @brief ISM switch TX mode function.
 * @details This function switch to TX mode of the 
 * RFM75, Low Power High Performance 2.4 GHz GFSK Transceiver on the 
 * ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism_switch_tx_mode ( ism_t *ctx );

/**
 * @brief ISM device configuration function.
 * @details This function performs configuration of the 
 * RFM75, Low Power High Performance 2.4 GHz GFSK Transceiver on the 
 * ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism_device_config ( ism_t *ctx );

/**
 * @brief ISM receive packet function.
 * @details This function receive packet of data of the 
 * RFM75, Low Power High Performance 2.4 GHz GFSK Transceiver on the 
 * ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @param[out] rx_data : Pointer to the memory location where receive data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism_receive_packet ( ism_t *ctx, uint8_t *rx_data );

/**
 * @brief ISM transmit package function.
 * @details This function transmit the package of data of the 
 * RFM75, Low Power High Performance 2.4 GHz GFSK Transceiver on the 
 * ISM click board™.
 * @param[in] ctx : Click context object.
 * See #ism_t object definition for detailed explanation.
 * @param[in] type : Transmission type.
 * @param[in] tx_data : Pointer to the memory location where transmitted data be stored.
 * @param[in] len : The number of bytes to be transmitted.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism_transmit_packet ( ism_t *ctx, uint8_t type, uint8_t *tx_data, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif // ISM_H

/*! @} */ // ism

// ------------------------------------------------------------------------ END
