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
 * @file spiextend.h
 * @brief This file contains API for SPI Extend Click Driver.
 */

#ifndef SPIEXTEND_H
#define SPIEXTEND_H

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
 * @addtogroup spiextend SPI Extend Click Driver
 * @brief API for configuring and manipulating SPI Extend Click driver.
 * @{
 */

/**
 * @defgroup spiextend_reg SPI Extend Registers List
 * @brief List of registers of SPI Extend Click driver.
 */

/**
 * @addtogroup spiextend_reg
 * @{
 */

/**
 * @brief SPI Extend description register.
 * @details Specified register for description of SPI Extend Click driver.
 */
#define SPIEXTEND_REG_CONFIG                                     0x00
#define SPIEXTEND_REG_STATUS                                     0x01
#define SPIEXTEND_REG_EVENT                                      0x02
#define SPIEXTEND_REG_INT_EN                                     0x03
#define SPIEXTEND_REG_FAULT                                      0x04
#define SPIEXTEND_REG_WORD_LENGTH                                0x05
#define SPIEXTEND_REG_SCRATCH                                    0x06

/**
 * @brief Aceel 14 description register.
 * @details Specified register for description of Aceel 14 for SPI Extend Click driver.
 */
#define SPIEXTEND_ACCEL14_REG_WHO_AM_I                           0x0F
#define SPIEXTEND_ACCEL14_REG_CTRL1_XL                           0x10
#define SPIEXTEND_ACCEL14_REG_CTRL3_C                            0x12
#define SPIEXTEND_ACCEL14_REG_OUT_TEMP_L                         0x20
#define SPIEXTEND_ACCEL14_REG_OUT_TEMP_H                         0x21
#define SPIEXTEND_ACCEL14_REG_OUTX_L_A                           0x28
#define SPIEXTEND_ACCEL14_REG_OUTX_H_A                           0x29
#define SPIEXTEND_ACCEL14_REG_OUTY_L_A                           0x2A
#define SPIEXTEND_ACCEL14_REG_OUTY_H_A                           0x2B
#define SPIEXTEND_ACCEL14_REG_OUTZ_L_A                           0x2C
#define SPIEXTEND_ACCEL14_REG_OUTZ_H_A                           0x2D
/*! @} */ // spiextend_reg

/**
 * @defgroup spiextend_set SPI Extend Registers Settings
 * @brief Settings for registers of SPI Extend Click driver.
 */

/**
 * @addtogroup spiextend_set
 * @{
 */

/**
 * @brief SPI Extend status.
 * @details Status of SPI Extend Click driver.
 */
#define SPIEXTEND_STATUS_ACTIVE                                  0x00
#define SPIEXTEND_STATUS_INACTIVE                                0x01

/**
 * @brief SPI Extend description setting for Accel 14 config.
 * @details Accel 14 config for SPI Extend Click driver.
 */
#define SPIEXTEND_ACCEL14_CTRL1_XL_POWER_UP                      0xA0
#define SPIEXTEND_ACCEL14_CTRL1_XL_HIGH_RES_FS                   0x00
#define SPIEXTEND_ACCEL14_CTRL1_XL_GSEL_4G                       0x08
#define SPIEXTEND_ACCEL14_CTRL3_C_BOOT_NORMAL                    0x00
#define SPIEXTEND_ACCEL14_CTRL3_C_BDU_READ_UPDATE                0x40
#define SPIEXTEND_ACCEL14_CTRL3_C_INT_ACTIVE_HIGH                0x00
#define SPIEXTEND_ACCEL14_CTRL3_C_PP_OD_PUSH_PULL                0x00
#define SPIEXTEND_ACCEL14_CTRL3_C_SIM_SPI_4_WIRE                 0x00
#define SPIEXTEND_ACCEL14_CTRL3_C_IF_INC_ENABLE                  0x04
#define SPIEXTEND_ACCEL14_CTRL3_C_SW_RESET_DIS                   0x00

/**
 * @brief SPI Extend Accel 14 communication.
 * @details Accel 14 communication for SPI Extend Click driver.
 */
#define SPIEXTEND_ACCEL14_SPI_WRITE                              0x00
#define SPIEXTEND_ACCEL14_SPI_READ                               0x80

/**
 * @brief SPI Extend clear event.
 * @details SClear event for SPI Extend Click driver.
 */
#define SPIEXTEND_CMD_CLEAR_EVENT                                0x00

/**
 * @brief SPI Extend slave select.
 * @details Slave select for SPI Extend Click driver.
 */
#define SPIEXTEND_SLAVE_SELECT_SS1                               0x01
#define SPIEXTEND_SLAVE_SELECT_SS2                               0x02
#define SPIEXTEND_SLAVE_SELECT_SS3                               0x03

/**
 * @brief SPI Extend pin state.
 * @details Pin state for SPI Extend Click driver.
 */
#define SPIEXTEND_PIN_STATE_LOW                                  0x00
#define SPIEXTEND_PIN_STATE_HIGH                                 0x01
 
 /**
 * @brief SPI Extend communication. 
 * @details Communication for SPI Extend Click driver.
 */                                                
#define SPIEXTEND_SPI_WRITE                                      0x00
#define SPIEXTEND_SPI_READ                                       0x01

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b spiextend_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SPIEXTEND_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define SPIEXTEND_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // spiextend_set

/**
 * @defgroup spiextend_map SPI Extend MikroBUS Map
 * @brief MikroBUS pin mapping of SPI Extend Click driver.
 */

/**
 * @addtogroup spiextend_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SPI Extend Click to the selected MikroBUS.
 */
#define SPIEXTEND_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ss3 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.ss2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ssc = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // spiextend_map
/*! @} */ // spiextend

/**
 * @brief SPI Extend Click context object.
 * @details Context object definition of SPI Extend Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  ss3;        /** Remote Slave Select 3. */
    digital_out_t  ss2;        /** Slave Select 2. */
    digital_out_t  ssc;        /** SPI Chip Select. */

    // Input pins
    digital_in_t  int_pin;     /** Interrupt pin. */

    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

} spiextend_t;

/**
 * @brief SPI Extend Click configuration object.
 * @details Configuration object definition of SPI Extend Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t   ss3;           /** Remote Slave Select 3. */
    pin_name_t  ss2;            /** Slave Select 2. */
    pin_name_t  ssc;            /** SPI Chip Select. */
    pin_name_t  int_pin;        /** Interrupt pin. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} spiextend_cfg_t;

/**
 * @brief SPI Extend Click configuration data.
 * @details Configuration data definition of SPI Extend Click.
 */
typedef struct
{
    uint8_t rem_ss3_pol;
    uint8_t rem_ss3_pha;
    uint8_t rem_ss2_pol;
    uint8_t rem_ss2_pha;
    uint8_t rem_ss1_pol;
    uint8_t rem_ss1_pha;
}
spiextend_config_data_t;

/**
 * @brief SPI Extend Click status data.
 * @details Status data definition of SPI Extend Click.
 */
typedef struct
{
    uint8_t nlink;
    uint8_t nint;
    uint8_t rmt_nint;
    uint8_t speed_idx;
}
spiextend_status_data_t;

/**
 * @brief SPI Extend Click event data.
 * @details Event definition of SPI Extend Click.
 */
typedef struct
{
    uint8_t e_link_good;
    uint8_t e_link_lost;
    uint8_t e_fault;
}
spiextend_event_data_t;

/**
 * @brief SPI Extend Click Fault data.
 * @details Fault definition of SPI Extend Click.
 */
typedef struct
{
    uint8_t spi_write_fault;
    uint8_t link_fault;
    uint8_t rmt_spi_fault;
    uint8_t tx_buf_overflow;
    uint8_t tx_buf_underflow;
}
spiextend_fault_data_t;

/**
 * @brief SPI Extend Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   SPIEXTEND_OK = 0,
   SPIEXTEND_ERROR = -1

} spiextend_return_value_t;

/*!
 * @addtogroup spiextend SPI Extend Click Driver
 * @brief API for configuring and manipulating SPI Extend Click driver.
 * @{
 */

/**
 * @brief SPI Extend configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #spiextend_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void spiextend_cfg_setup ( spiextend_cfg_t *cfg );

/**
 * @brief SPI Extend initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #spiextend_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiextend_init ( spiextend_t *ctx, spiextend_cfg_t *cfg );

/**
 * @brief SPI Extend default configuration function.
 * @details This function executes a default configuration of SPI Extend
 * click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t spiextend_default_cfg ( spiextend_t *ctx );

/**
 * @brief SPI Extend data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t spiextend_generic_write ( spiextend_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief SPI Extend data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t spiextend_generic_read ( spiextend_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief SPI Extend get the configuration function.
 * @details Function get configuration of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[out] config_data : structure where data be stored.
 * @return Nothing.
 */
void spiextend_get_config ( spiextend_t *ctx, spiextend_config_data_t *config_data );

/**
 * @brief SPI Extend set the configuration function.
 * @details Function set configuration of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] config_data : Structure where data be stored.
 * @return Nothing.
 */
void spiextend_set_config ( spiextend_t *ctx, spiextend_config_data_t config_data );

/**
 * @brief SPI Extend get the status function.
 * @details Function set configuration of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[out] status_data : Pointer to the memory location where data be stored.
 * @return Nothing.
 */
void spiextend_get_status ( spiextend_t *ctx, spiextend_status_data_t *status_data );

/**
 * @brief SPI Extend get the event function.
 * @details Function get events of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[out] event_data : Pointer to the memory location where data be stored.
 * @return Nothing.
 * @note Set by the system and cleared by the user.
 */
void spiextend_get_event ( spiextend_t *ctx, spiextend_event_data_t *event_data );

/**
 * @brief SPI Extend clear the event function.
 * @details Function clear events of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @return Nothing.
 */
void spiextend_clear_event ( spiextend_t *ctx );

/**
 * @brief SPI Extend enable int function.
 * @details Function enable int of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] event_data : Memory location where data be stored.
 * @return Nothing.
 */
void spiextend_enable_int ( spiextend_t *ctx, spiextend_event_data_t event_data );

/**
 * @brief SPI Extend get the fault state function.
 * @details Function read fault register and update fault state data structe of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[out] fault_data : Pointer to the memory location where data be stored.
 * @return Nothing.
 */
void spiextend_get_fault ( spiextend_t *ctx, spiextend_fault_data_t *fault_data );

/**
 * @brief SPI Extend get the word length function.
 * @details Function read word length register and return word length data of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @return 8-bit word length.
 */
uint8_t spiextend_get_word_length ( spiextend_t *ctx );

/**
 * @brief SPI Extend set the word length function.
 * @details Function read fault register and update fault state data structe of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] word_length : 8-bit word length ( from 8 to 32 ).
 * @return Nothing.
 */
void spiextend_set_word_length ( spiextend_t *ctx, uint8_t word_length );

/**
 * @brief SPI Extend get scratch function.
 * @details Function read scratch register and return scratch data of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @return 8-bit scratch data.
 */
uint8_t spiextend_get_scratch (  spiextend_t *ctx );

/**
 * @brief SPI Extend set scratch function.
 * @details Function set scratch data of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] scratch : 8-bit scratch data.
 * @return Nothing
 */
void spiextend_set_scratch ( spiextend_t *ctx, uint8_t scratch );

/**
 * @brief SPI Extend set SS1 pin state function.
 * @details Function set SS1 pin state of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] en_cs : SS1 pin state.
 * @return Nothing
 */
void spiextend_set_ss1 ( spiextend_t *ctx, uint8_t en_cs );

/**
 * @brief SPI Extend set SS2 pin state function.
 * @details Function set SS2 pin state of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] en_rst : SS2 pin state.
 * @return Nothing
 */
void spiextend_set_ss2 ( spiextend_t *ctx, uint8_t en_rst );

/**
 * @brief SPI Extend set SS3 pin state function.
 * @details Function set SS3 pin state of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] en_an : SS3 pin state.
 * @return Nothing
 */
void spiextend_set_ss3 ( spiextend_t *ctx, uint8_t en_an );

/**
 * @brief SPI Extend check interrupt status function.
 * @details Function check interrupt state by return state of the INT pin of the LTC4332 SPI Extender Over Rugged
 * Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @return @li @c  0 - State high,
 *         @li @c  1 - State low.
 */
uint8_t spiextend_check_int ( spiextend_t *ctx );

/**
 * @brief SPI Extend generic SPI write data in Remote Mode function.
 * @details Function SPI writes a the byte of data to the targeted 8-bit register address of the click board
 * connected to the LTC4332 SPI Extender Over Rugged Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] p_tx_data : Pointer to the memory location where data be stored.
 * @param[in] n_bytes : 16-bit number of bytes to be written.
 * @return Nothing.
 */
void spiextend_rmt_spi_write ( spiextend_t *ctx, uint8_t *p_tx_data, uint16_t n_bytes );

/**
 * @brief SPI Extend generic SPI read data in Remote Mode function.
 * @details Function SPI read a the byte of data to the targeted 8-bit register address of the click board connected
 * to the LTC4332 SPI Extender Over Rugged Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[out] p_rx_data : Pointer to the memory location where data be stored.
 * @param[in] n_bytes : 16-bit number of bytes to be read.
 * @return Nothing.
 */
void spiextend_rmt_spi_read ( spiextend_t *ctx, uint8_t *p_rx_data, uint16_t n_bytes );

/**
 * @brief SPI Extend generic write data in Remote Mode function.
 * @details Function writes a the byte of data to the targeted 8-bit register address of the click board connected
 * to the LTC4332 SPI Extender Over Rugged Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] tx_data : Data to be written.
 * @param[in] sel_slave : Slave select.
 * @return Nothing.
 */
void spiextend_rmt_write ( spiextend_t *ctx, uint8_t reg, uint8_t tx_data, uint8_t sel_slave );

/**
 * @brief SPI Extend generic read data in Remote Mode function.
 * @details Function read a the byte of data from the targeted 8-bit register address of the click board connected
 * to the LTC4332 SPI Extender Over Rugged Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] sel_slave : Slave select.
 * @return 8-bit read data.
 */
uint8_t spiextend_rmt_read ( spiextend_t *ctx, uint8_t reg, uint8_t sel_slave );

/**
 * @brief SPI Extend generic multi write data in Remote Mode function.
 * @details Function writes a the byte of data to the targeted 8-bit register address of the click board connected
 * to the LTC4332 SPI Extender Over Rugged Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] p_tx_data : Pointer to the memory location where data be stored.
 * @param[in] n_bytes : 16-bit number of bytes to be written.
 * @param[in] sel_slave : Slave select.
 * @return Nothing.
 */
void spiextend_rmt_multi_write ( spiextend_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint16_t n_bytes, uint8_t sel_slave );

/**
 * @brief SPI Extend generic multi read data in Remote Mode function.
 * @details Function multi read a the byte of data to the targeted 8-bit register address of the click board connected
 * to the LTC4332 SPI Extender Over Rugged Differential Link on the SPI Extend click board.
 * @param[in] ctx : Click context object.
 * See #spiextend_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[out] p_rx_data : Pointer to the memory location where data be stored.
 * @param[in] n_bytes : 16-bit number of bytes to be written.
 * @param[in] sel_slave : Slave select.
 * @return Nothing.
 */
void spiextend_rmt_multi_read ( spiextend_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes, uint8_t sel_slave );

#ifdef __cplusplus
}
#endif
#endif // SPIEXTEND_H

/*! @} */ // spiextend

// ------------------------------------------------------------------------ END
