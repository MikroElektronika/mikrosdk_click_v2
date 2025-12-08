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
 * @file uarti2cspi2.h
 * @brief This file contains API for UART I2C SPI 2 Click Driver.
 */

#ifndef UARTI2CSPI2_H
#define UARTI2CSPI2_H

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
 * @addtogroup uarti2cspi2 UART I2C SPI 2 Click Driver
 * @brief API for configuring and manipulating UART I2C SPI 2 Click driver.
 * @{
 */

/**
 * @defgroup uarti2cspi2 UART I2C SPI 2 Registers List
 * @brief List of registers of UART I2C SPI 2 Click driver.
 */

/**
 * @addtogroup uarti2cspi2_reg
 * @{
 */

/**
 * @brief UART I2C SPI 2 register list.
 * @details Specified register list of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_REG_RHR                         0x00
#define UARTI2CSPI2_REG_THR                         0x00
#define UARTI2CSPI2_REG_IRQEN                       0x01
#define UARTI2CSPI2_REG_IRQSTS                      0x02
#define UARTI2CSPI2_REG_LSR_IRQEN                   0x03
#define UARTI2CSPI2_REG_LSR_IRQSTS                  0x04
#define UARTI2CSPI2_REG_SPCHR_IRQEN                 0x05
#define UARTI2CSPI2_REG_SPCHR_IRQSTS                0x06
#define UARTI2CSPI2_REG_STS_IRQEN                   0x07
#define UARTI2CSPI2_REG_STS_IRQSTS                  0x08
#define UARTI2CSPI2_REG_MODE1                       0x09
#define UARTI2CSPI2_REG_MODE2                       0x0A
#define UARTI2CSPI2_REG_LCR                         0x0B
#define UARTI2CSPI2_REG_RXTO                        0x0C
#define UARTI2CSPI2_REG_HDPIXDELAY                  0x0D
#define UARTI2CSPI2_REG_IRDA                        0x0E
#define UARTI2CSPI2_REG_FLOWLVL                     0x0F
#define UARTI2CSPI2_REG_FIFOTRIGLVL                 0x10
#define UARTI2CSPI2_REG_TXFIFOLVL                   0x11
#define UARTI2CSPI2_REG_RXFIFOLVL                   0x12
#define UARTI2CSPI2_REG_FLOWCTRL                    0x13
#define UARTI2CSPI2_REG_XON1                        0x14
#define UARTI2CSPI2_REG_XON2                        0x15
#define UARTI2CSPI2_REG_XOFF1                       0x16
#define UARTI2CSPI2_REG_XOFF2                       0x17
#define UARTI2CSPI2_REG_GPIOCFG                     0x18
#define UARTI2CSPI2_REG_GPIODATA                    0x19
#define UARTI2CSPI2_REG_PLLCFG                      0x1A
#define UARTI2CSPI2_REG_BRGCFG                      0x1B
#define UARTI2CSPI2_REG_BRGDIVLSB                   0x1C
#define UARTI2CSPI2_REG_BRGDIVMSB                   0x1D
#define UARTI2CSPI2_REG_CLKSRC                      0x1E
#define UARTI2CSPI2_REG_GLOBAL_IRQ                  0x1F
#define UARTI2CSPI2_REG_GLOBAL_CMD                  0x1F
#define UARTI2CSPI2_REG_TXSYNCH                     0x20
#define UARTI2CSPI2_REG_SYNCHDELAY1                 0x21
#define UARTI2CSPI2_REG_SYNCHDELAY2                 0x22
#define UARTI2CSPI2_REG_TIMER1                      0x23
#define UARTI2CSPI2_REG_TIMER2                      0x24
#define UARTI2CSPI2_REG_REVID                       0x25

/*! @} */ // uarti2cspi2_reg

/**
 * @defgroup uarti2cspi2_set UART I2C SPI 2 Registers Settings
 * @brief Settings for registers of UART I2C SPI 2 Click driver.
 */

/**
 * @addtogroup uarti2cspi2_set
 * @{
 */

/**
 * @brief UART I2C SPI 2 IRQEN/IRQSTS register setting.
 * @details Specified setting for IRQEN/IRQSTS register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_IRQ_CTS                         0x80
#define UARTI2CSPI2_IRQ_RX_EMPTY                    0x40
#define UARTI2CSPI2_IRQ_TX_FIFO_EMPTY               0x20
#define UARTI2CSPI2_IRQ_TX_TRG                      0x10
#define UARTI2CSPI2_IRQ_RX_TRG                      0x08
#define UARTI2CSPI2_IRQ_STS                         0x04
#define UARTI2CSPI2_IRQ_SP_CHR                      0x02
#define UARTI2CSPI2_IRQ_LSR_ERR                     0x01

/**
 * @brief UART I2C SPI 2 LSR_IRQEN/LSR_IRQSTS register setting.
 * @details Specified setting for LSR_IRQEN/LSR_IRQSTS register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_LSR_IRQ_CTS                     0x80
#define UARTI2CSPI2_LSR_IRQ_NOISE_INT               0x20
#define UARTI2CSPI2_LSR_IRQ_R_BREAK                 0x10
#define UARTI2CSPI2_LSR_IRQ_FRAME_ERR               0x08
#define UARTI2CSPI2_LSR_IRQ_PARITY                  0x04
#define UARTI2CSPI2_LSR_IRQ_R_OVERR                 0x02
#define UARTI2CSPI2_LSR_IRQ_R_TIMEOUT               0x01

/**
 * @brief UART I2C SPI 2 SPCHR_IRQEN/SPCHR_IRQSTS register setting.
 * @details Specified setting for SPCHR_IRQEN/SPCHR_IRQSTS register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_SPCHR_IRQ_MULTI_DROP            0x20
#define UARTI2CSPI2_SPCHR_IRQ_BREAK                 0x10
#define UARTI2CSPI2_SPCHR_IRQ_XOFF2                 0x08
#define UARTI2CSPI2_SPCHR_IRQ_XOFF1                 0x04
#define UARTI2CSPI2_SPCHR_IRQ_XON2                  0x02
#define UARTI2CSPI2_SPCHR_IRQ_XON1                  0x01

/**
 * @brief UART I2C SPI 2 STS_IRQEN/STS_IRQSTS register setting.
 * @details Specified setting for STS_IRQEN/STS_IRQSTS register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_STS_IRQ_TX_EMPTY                0x80
#define UARTI2CSPI2_STS_IRQ_SLEEP                   0x40
#define UARTI2CSPI2_STS_IRQ_CLK_READY               0x20
#define UARTI2CSPI2_STS_IRQ_GPI3                    0x08
#define UARTI2CSPI2_STS_IRQ_GPI2                    0x04
#define UARTI2CSPI2_STS_IRQ_GPI1                    0x02
#define UARTI2CSPI2_STS_IRQ_GPI0                    0x01

/**
 * @brief UART I2C SPI 2 MODE1 register setting.
 * @details Specified setting for MODE1 register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_MODE1_AUTO_SLEEP                0x40
#define UARTI2CSPI2_MODE1_FORCED_SLEEP              0x20
#define UARTI2CSPI2_MODE1_TRNSCV_CTRL               0x10
#define UARTI2CSPI2_MODE1_RTS_HIZ                   0x08
#define UARTI2CSPI2_MODE1_TX_HIZ                    0x04
#define UARTI2CSPI2_MODE1_TX_DISABLE                0x02
#define UARTI2CSPI2_MODE1_RX_DISABLE                0x01

/**
 * @brief UART I2C SPI 2 MODE2 register setting.
 * @details Specified setting for MODE2 register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_MODE2_ECHO_SUPRS                0x80
#define UARTI2CSPI2_MODE2_MULTI_DROP                0x40
#define UARTI2CSPI2_MODE2_LOOPBACK                  0x20
#define UARTI2CSPI2_MODE2_SPECIAL_CHR               0x10
#define UARTI2CSPI2_MODE2_R_FIFO_EMPTY_INV          0x08
#define UARTI2CSPI2_MODE2_RX_TRIG_INV               0x04
#define UARTI2CSPI2_MODE2_FIFO_RST                  0x02
#define UARTI2CSPI2_MODE2_RST                       0x01

/**
 * @brief UART I2C SPI 2 LCR register setting.
 * @details Specified setting for LCR register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_LCR_RTS_BIT                     0x80
#define UARTI2CSPI2_LCR_TX_BREAK                    0x40
#define UARTI2CSPI2_LCR_FORCE_PARITY                0x20
#define UARTI2CSPI2_LCR_EVEN_PARITY                 0x10
#define UARTI2CSPI2_LCR_PARITY_EN                   0x08
#define UARTI2CSPI2_LCR_STOP_BITS_1                 0x00
#define UARTI2CSPI2_LCR_STOP_BITS_2_OR_1_5          0x04
#define UARTI2CSPI2_LCR_STOP_BITS_MASK              0x04
#define UARTI2CSPI2_LCR_WORD_LENGTH_5               0x00
#define UARTI2CSPI2_LCR_WORD_LENGTH_6               0x01
#define UARTI2CSPI2_LCR_WORD_LENGTH_7               0x02
#define UARTI2CSPI2_LCR_WORD_LENGTH_8               0x03
#define UARTI2CSPI2_LCR_WORD_LENGTH_MASK            0x03

/**
 * @brief UART I2C SPI 2 IRDA register setting.
 * @details Specified setting for IRDA register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_IRDA_TX_INV                     0x20
#define UARTI2CSPI2_IRDA_RX_INV                     0x10
#define UARTI2CSPI2_IRDA_MIR                        0x08
#define UARTI2CSPI2_IRDA_SIR                        0x02
#define UARTI2CSPI2_IRDA_IRDA_EN                    0x01

/**
 * @brief UART I2C SPI 2 FLOWCTRL register setting.
 * @details Specified setting for FLOWCTRL register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_FLOWCTRL_SW_FLOW_NO_FLOW        0x00
#define UARTI2CSPI2_FLOWCTRL_SW_FLOW_MASK           0xF0

/**
 * @brief UART I2C SPI 2 BRGCFG register setting.
 * @details Specified setting for BRGCFG register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_BRGCFG_4XMODE                   0x20
#define UARTI2CSPI2_BRGCFG_2XMODE                   0x10
#define UARTI2CSPI2_BRGCFG_FRACT_MASK               0x0F

/**
 * @brief UART I2C SPI 2 CLKSRC register setting.
 * @details Specified setting for CLKSRC register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_CLKSRC_CLK_TO_RTS               0x80
#define UARTI2CSPI2_CLKSRC_PLL_BYPASS               0x08
#define UARTI2CSPI2_CLKSRC_PLL_EN                   0x04
#define UARTI2CSPI2_CLKSRC_CRYSTAL_EN               0x02

/**
 * @brief UART I2C SPI 2 GLOBAL_IRQ register setting.
 * @details Specified setting for GLOBAL_IRQ register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_GLOBAL_IRQ_IRQ1                 0x02
#define UARTI2CSPI2_GLOBAL_IRQ_IRQ0                 0x01

/**
 * @brief UART I2C SPI 2 GLOBAL_CMD register setting.
 * @details Specified setting for GLOBAL_CMD register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_GLOBAL_CMD_TX0                  0xE0
#define UARTI2CSPI2_GLOBAL_CMD_TX1                  0xE1
#define UARTI2CSPI2_GLOBAL_CMD_TX2                  0xE2
#define UARTI2CSPI2_GLOBAL_CMD_TX3                  0xE3
#define UARTI2CSPI2_GLOBAL_CMD_TX4                  0xE4
#define UARTI2CSPI2_GLOBAL_CMD_TX5                  0xE5
#define UARTI2CSPI2_GLOBAL_CMD_TX6                  0xE6
#define UARTI2CSPI2_GLOBAL_CMD_TX7                  0xE7
#define UARTI2CSPI2_GLOBAL_CMD_TX8                  0xE8
#define UARTI2CSPI2_GLOBAL_CMD_TX9                  0xE9
#define UARTI2CSPI2_GLOBAL_CMD_TX10                 0xEA
#define UARTI2CSPI2_GLOBAL_CMD_TX11                 0xEB
#define UARTI2CSPI2_GLOBAL_CMD_TX12                 0xEC
#define UARTI2CSPI2_GLOBAL_CMD_TX13                 0xED
#define UARTI2CSPI2_GLOBAL_CMD_TX14                 0xEE
#define UARTI2CSPI2_GLOBAL_CMD_TX15                 0xEF
#define UARTI2CSPI2_GLOBAL_CMD_EN_EXT_REGMAP        0xCE
#define UARTI2CSPI2_GLOBAL_CMD_DIS_EXT_REGMAP       0xCD

/**
 * @brief UART I2C SPI 2 TXSYNCH register setting.
 * @details Specified setting for TXSYNCH register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_TXSYNCH_CLK_TO_GPIO             0x80
#define UARTI2CSPI2_TXSYNCH_TX_AUTO_DIS             0x40
#define UARTI2CSPI2_TXSYNCH_TRIG_DELAY              0x20
#define UARTI2CSPI2_TXSYNCH_SYNCH_EN                0x10
#define UARTI2CSPI2_TXSYNCH_TRIG_SEL3               0x08
#define UARTI2CSPI2_TXSYNCH_TRIG_SEL2               0x04
#define UARTI2CSPI2_TXSYNCH_TRIG_SEL1               0x02
#define UARTI2CSPI2_TXSYNCH_TRIG_SEL0               0x01

/**
 * @brief UART I2C SPI 2 REVID register setting.
 * @details Specified setting for REVID register of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_REVID_MAJOR                     0xC0
#define UARTI2CSPI2_REVID_MAJOR_MASK                0xF0
#define UARTI2CSPI2_REVID_MINOR_MASK                0x0F

/**
 * @brief UART I2C SPI 2 uart baud rate setting.
 * @details Specified setting for uart baud rate of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_BAUDRATE_1200                   1200ul
#define UARTI2CSPI2_BAUDRATE_2400                   2400ul
#define UARTI2CSPI2_BAUDRATE_4800                   4800ul
#define UARTI2CSPI2_BAUDRATE_9600                   9600ul
#define UARTI2CSPI2_BAUDRATE_14400                  14400ul
#define UARTI2CSPI2_BAUDRATE_19200                  19200ul
#define UARTI2CSPI2_BAUDRATE_38400                  38400ul
#define UARTI2CSPI2_BAUDRATE_57600                  57600ul
#define UARTI2CSPI2_BAUDRATE_115200                 115200ul
#define UARTI2CSPI2_BAUDRATE_230400                 230400ul
#define UARTI2CSPI2_BAUDRATE_460800                 460800ul
#define UARTI2CSPI2_CRYSTAL_FREQ                    1843200ul

/**
 * @brief UART I2C SPI 2 interface setting.
 * @details Specified setting for interface of UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_UART_SEL_0                      0
#define UARTI2CSPI2_UART_SEL_1                      1
#define UARTI2CSPI2_SPI_UART_SEL_0                  0x00
#define UARTI2CSPI2_SPI_UART_SEL_1                  0x20
#define UARTI2CSPI2_SPI_UART_SEL_MASK               0x20
#define UARTI2CSPI2_SPI_REG_MASK                    0x1F
#define UARTI2CSPI2_SPI_WRITE_BIT                   0x80
#define UARTI2CSPI2_I2C_UART_SEL_0                  0x20
#define UARTI2CSPI2_I2C_UART_SEL_1                  0x10
#define UARTI2CSPI2_I2C_UART_SEL_MASK               0x30
#define UARTI2CSPI2_FIFO_LEN                        128

/**
 * @brief UART I2C SPI 2 device address setting.
 * @details Specified setting for device slave address selection of
 * UART I2C SPI 2 Click driver.
 */
#define UARTI2CSPI2_DEVICE_ADDRESS_A1A0_00          0x6C
#define UARTI2CSPI2_DEVICE_ADDRESS_A1A0_01          0x61
#define UARTI2CSPI2_DEVICE_ADDRESS_A1A0_10          0x64
#define UARTI2CSPI2_DEVICE_ADDRESS_A1A0_11          0x65

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b uarti2cspi2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define UARTI2CSPI2_SET_DATA_SAMPLE_EDGE            SET_SPI_DATA_SAMPLE_EDGE
#define UARTI2CSPI2_SET_DATA_SAMPLE_MIDDLE          SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // uarti2cspi2_set

/**
 * @defgroup uarti2cspi2_map UART I2C SPI 2 MikroBUS Map
 * @brief MikroBUS pin mapping of UART I2C SPI 2 Click driver.
 */

/**
 * @addtogroup uarti2cspi2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UART I2C SPI 2 Click to the selected MikroBUS.
 */
#define UARTI2CSPI2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // uarti2cspi2_map
/*! @} */ // uarti2cspi2

/**
 * @brief UART I2C SPI 2 Click driver selector.
 * @details Selects target driver interface of UART I2C SPI 2 Click driver.
 */
typedef enum
{
    UARTI2CSPI2_DRV_SEL_SPI,        /**< SPI driver descriptor. */
    UARTI2CSPI2_DRV_SEL_I2C         /**< I2C driver descriptor. */

} uarti2cspi2_drv_t;

/**
 * @brief UART I2C SPI 2 Click driver interface.
 * @details Definition of driver interface of UART I2C SPI 2 Click driver.
 */
struct uarti2cspi2_s;
typedef err_t ( *uarti2cspi2_master_io_t )( struct uarti2cspi2_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief UART I2C SPI 2 Click context object.
 * @details Context object definition of UART I2C SPI 2 Click driver.
 */
typedef struct uarti2cspi2_s
{
    digital_out_t rst;                  /**< Device RST pin (active low). */

    digital_in_t int_pin;               /**< Device interrupt pin (active low). */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    uarti2cspi2_drv_t drv_sel;          /**< Master driver interface selector. */

    uarti2cspi2_master_io_t write_f;    /**< Master write function. */
    uarti2cspi2_master_io_t read_f;     /**< Master read function. */

    uint8_t act_uart;                   /**< Active UART number, 0 or 1. */ 

} uarti2cspi2_t;

/**
 * @brief UART I2C SPI 2 Click configuration object.
 * @details Configuration object definition of UART I2C SPI 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t rst;                     /**< Device RST pin (active low). */
    pin_name_t int_pin;                 /**< Device interrupt pin (active low). */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    uarti2cspi2_drv_t drv_sel;          /**< Master driver interface selector. */

} uarti2cspi2_cfg_t;

/**
 * @brief UART I2C SPI 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    UARTI2CSPI2_OK = 0,
    UARTI2CSPI2_ERROR = -1

} uarti2cspi2_return_value_t;

/*!
 * @addtogroup uarti2cspi2 UART I2C SPI 2 Click Driver
 * @brief API for configuring and manipulating UART I2C SPI 2 Click driver.
 * @{
 */

/**
 * @brief UART I2C SPI 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #uarti2cspi2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void uarti2cspi2_cfg_setup ( uarti2cspi2_cfg_t *cfg );

/**
 * @brief UART I2C SPI 2 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #uarti2cspi2_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #uarti2cspi2_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void uarti2cspi2_drv_interface_sel ( uarti2cspi2_cfg_t *cfg, uarti2cspi2_drv_t drv_sel );

/**
 * @brief UART I2C SPI 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #uarti2cspi2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarti2cspi2_init ( uarti2cspi2_t *ctx, uarti2cspi2_cfg_t *cfg );

/**
 * @brief UART I2C SPI 2 default configuration function.
 * @details This function executes a default configuration of UART I2C SPI 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t uarti2cspi2_default_cfg ( uarti2cspi2_t *ctx );

/**
 * @brief UART I2C SPI 2 write registers function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register address.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarti2cspi2_write_regs ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief UART I2C SPI 2 read registers function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register address.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarti2cspi2_read_regs ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief UART I2C SPI 2 write register function.
 * @details This function writes a single byte of data to the selected register address.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarti2cspi2_write_reg ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief UART I2C SPI 2 read register function.
 * @details This function reads a single byte of data from the selected register address.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarti2cspi2_read_reg ( uarti2cspi2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief UART I2C SPI 2 communication check function.
 * @details This function checks communication by reading the revision ID
 * and validating its major revision.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarti2cspi2_check_com ( uarti2cspi2_t *ctx );

/**
 * @brief UART I2C SPI 2 enable device function.
 * @details This function enables the device by setting the RST pin high.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void uarti2cspi2_enable_device ( uarti2cspi2_t *ctx );

/**
 * @brief UART I2C SPI 2 disable device function.
 * @details This function disables the device by setting the RST pin low.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void uarti2cspi2_disable_device ( uarti2cspi2_t *ctx );

/**
 * @brief UART I2C SPI 2 get INT pin function.
 * @details This function reads the state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @return Pin state.
 * @note None.
 */
uint8_t uarti2cspi2_get_int_pin ( uarti2cspi2_t *ctx );

/**
 * @brief UART I2C SPI 2 select UART 0 function.
 * @details This function selects UART 0 as the active UART channel.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void uarti2cspi2_select_uart_0 ( uarti2cspi2_t *ctx );

/**
 * @brief UART I2C SPI 2 select UART 1 function.
 * @details This function selects UART 1 as the active UART channel.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void uarti2cspi2_select_uart_1 ( uarti2cspi2_t *ctx );

/**
 * @brief UART I2C SPI 2 set baud rate function.
 * @details This function sets the baud rate for the active UART channel.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @param[in] baud_rate : Desired baud rate.
 * @param[out] act_baud_rate : Actual baud rate set by the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarti2cspi2_set_baud_rate ( uarti2cspi2_t *ctx, uint32_t baud_rate, uint32_t *act_baud_rate );

/**
 * @brief UART I2C SPI 2 write data function.
 * @details This function writes a block of data to the transmit buffer.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarti2cspi2_write_data ( uarti2cspi2_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief UART I2C SPI 2 read data function.
 * @details This function reads a block of data from the receive buffer.
 * @param[in] ctx : Click context object.
 * See #uarti2cspi2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarti2cspi2_read_data ( uarti2cspi2_t *ctx, uint8_t *data_out, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif // UARTI2CSPI2_H

/*! @} */ // uarti2cspi2

// ------------------------------------------------------------------------ END
