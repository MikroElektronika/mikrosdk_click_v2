/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */
/*!
 * \file
 *
 * \brief This file contains API for CAN FD 2 Click driver.
 *
 * \addtogroup canfd2 CAN FD 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CANFD2_H
#define CANFD2_H

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
#include "drv_uart.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define CANFD2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
  cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
  cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
  cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CANFD2_OK                         0
#define CANFD2_ERROR                     -1
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define CANFD2_DRV_TX_BUFFER_SIZE         100
#define CANFD2_DRV_RX_BUFFER_SIZE         300
/** \} */

/**
 * \defgroup control_registers Control Registers
 * \{
 */
#define CANFD2_REG_MODE_CTRL              0x01
#define CANFD2_REG_HW_CTRL                0x02
#define CANFD2_REG_TXD_TO_CTRL            0x03
#define CANFD2_REG_SUPPLY_CTRL            0x04
/** \} */

/**
 * \defgroup selective_wake_registers Selective Wake Registers
 * \{
 */
#define CANFD2_REG_SWK_CTRL_1             0x05
#define CANFD2_REG_SWK_CTRL_2             0x06
#define CANFD2_REG_SWK_ID3_CTRL           0x07
#define CANFD2_REG_SWK_ID2_CTRL           0x08
#define CANFD2_REG_SWK_ID1_CTRL           0x09
#define CANFD2_REG_SWK_ID0_CTRL           0x0A
#define CANFD2_REG_SWK_MASK_ID3_CTRL      0x0B
#define CANFD2_REG_SWK_MASK_ID2_CTRL      0x0C
#define CANFD2_REG_SWK_MASK_ID1_CTRL      0x0D
#define CANFD2_REG_SWK_MASK_ID0_CTRL      0x0E
#define CANFD2_REG_SWK_DLC_CTRL           0x0F
#define CANFD2_REG_SWK_DATA7_CTRL         0x10
#define CANFD2_REG_SWK_DATA6_CTRL         0x11
#define CANFD2_REG_SWK_DATA5_CTRL         0x12
#define CANFD2_REG_SWK_DATA4_CTRL         0x13
#define CANFD2_REG_SWK_DATA3_CTRL         0x14
#define CANFD2_REG_SWK_DATA2_CTRL         0x15
#define CANFD2_REG_SWK_DATA1_CTRL         0x16
#define CANFD2_REG_SWK_DATA0_CTRL         0x17
/** \} */

/**
 * \defgroup stastus_registers Status Registers
 * \{
 */
#define CANFD2_REG_TRANS_STAT             0x18
#define CANFD2_REG_TRANS_UV_STAT          0x19
#define CANFD2_REG_ERR_STAT               0x1A
#define CANFD2_REG_WAKE_STAT              0x1B
/** \} */

/**
 * \defgroup selective_wake_status_registers Selective Wake Status Registers
 * \{
 */
#define CANFD2_REG_SWK_STAT               0x1C
#define CANFD2_REG_SWK_ECNT_STAT          0x1D
/** \} */

/**
 * \defgroup mode_control_commands Mode Control Commands
 * \{
 */
#define CANFD2_CTRL_MODE_SLEEP            0x01
#define CANFD2_CTRL_MODE_STANDBY          0x02
#define CANFD2_CTRL_MODE_REC_ONLY         0x04
#define CANFD2_CTRL_MODE_NORMAL_OP        0x08 
/** \} */

/**
 * \defgroup hardware_control_commands Hardware Control Commands
 * \{
 */
#define CANFD2_HW_CTRL_VBAT_CON           0x01
#define CANFD2_HW_CTRL_WAKE_TOG           0x02
#define CANFD2_HW_CTRL_LWU_POS            0x20
#define CANFD2_HW_CTRL_LWU_NEG            0x40
#define CANFD2_HW_CTRL_STTS_EN            0x80 
/** \} */

/**
 * \defgroup txd_timeout_control_commands TXD Timeout Control Commands
 * \{
 */
#define CANFD2_TXD_TO_1_4                 0x01
#define CANFD2_TXD_TO_2_5                 0x02
#define CANFD2_TXD_TO_5_10                0x03
#define CANFD2_TXD_TO_DISABLE             0x04
/** \} */

/**
 * \defgroup supply_control_commands Supply Control Commands
 * \{
 */
#define CANFD2_SUP_CTRL_VCC_UV_T_100      0x01
#define CANFD2_SUP_CTRL_VCC_UV_T_200      0x02
#define CANFD2_SUP_CTRL_VCC_UV_T_300      0x03
#define CANFD2_SUP_CTRL_VCC_UV_T_400      0x04
#define CANFD2_SUP_CTRL_VCC_UV_T_500      0x05
#define CANFD2_SUP_CTRL_VCC_UV_T_600      0x06
#define CANFD2_SUP_CTRL_VCC_UV_T_700      0x07
#define CANFD2_SUP_CTRL_VCC_UV_T_800      0x08
#define CANFD2_SUP_CTRL_VCC_UV_T_900      0x09
#define CANFD2_SUP_CTRL_VCC_UV_T_1000     0x0A
#define CANFD2_SUP_CTRL_VCC_UV_T_1100     0x0B
#define CANFD2_SUP_CTRL_VCC_UV_T_1200     0x0C
#define CANFD2_SUP_CTRL_VCC_UV_T_1300     0x0D
#define CANFD2_SUP_CTRL_VCC_UV_T_1400     0x0E
#define CANFD2_SUP_CTRL_VCC_UV_T_1500     0x0F

#define CANFD2_SUP_CTRL_VIO_UV_T_100      0x10
#define CANFD2_SUP_CTRL_VIO_UV_T_200      0x20
#define CANFD2_SUP_CTRL_VIO_UV_T_300      0x30
#define CANFD2_SUP_CTRL_VIO_UV_T_400      0x40
#define CANFD2_SUP_CTRL_VIO_UV_T_500      0x50
#define CANFD2_SUP_CTRL_VIO_UV_T_600      0x60
#define CANFD2_SUP_CTRL_VIO_UV_T_700      0x70
#define CANFD2_SUP_CTRL_VIO_UV_T_800      0x80
#define CANFD2_SUP_CTRL_VIO_UV_T_900      0x90
#define CANFD2_SUP_CTRL_VIO_UV_T_1000     0xA0
#define CANFD2_SUP_CTRL_VIO_UV_T_1100     0xB0
#define CANFD2_SUP_CTRL_VIO_UV_T_1200     0xC0
#define CANFD2_SUP_CTRL_VIO_UV_T_1300     0xD0
#define CANFD2_SUP_CTRL_VIO_UV_T_1400     0xE0
#define CANFD2_SUP_CTRL_VIO_UV_T_1500     0xF0 
/** \} */

/**
 * \defgroup selective_wake_control_commands Selective Wake Control Commands
 * \{
 */
#define CANFD2_SWK_CTRL_1_CFG_VAL         0x01
/** \} */

/**
 * \defgroup supply_control_commands Supply Control Commands
 * \{
 */
#define CANFD2_SWK_CTRL_2_BR_125K         0x01
#define CANFD2_SWK_CTRL_2_BR_250K         0x02
#define CANFD2_SWK_CTRL_2_BR_500K         0x03
#define CANFD2_SWK_CTRL_2_BR_1M           0x04
#define CANFD2_SWK_CTRL_2_BR_RATIO_4      0x00
#define CANFD2_SWK_CTRL_2_BR_RATIO_10     0x10
#define CANFD2_SWK_CTRL_2_SWK_EN          0x80
/** \} */

/**
 * \defgroup identifier_3_control_commands Identifier 3 Control Commands
 * \{
 */
#define CANFD2_SWK_ID3_CTRL_IDE           0x20
/** \} */

/**
 * \defgroup data_length_code_control_commands Data Length Code Control Commands
 * \{
 */
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_0  0x00
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_1  0x01
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_2  0x02
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_3  0x03
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_4  0x04
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_5  0x05
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_6  0x06
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_7  0x07
#define CANFD2_SWK_DLC_CTRL_DATA_BYTES_8  0x08
/** \} */

/**
 * \defgroup transceiver_status_commands Transceiver Status Commands
 * \{
 */
#define CANFD2_TRANS_STAT_TSD             0x02
#define CANFD2_TRANS_STAT_TXD_TO          0x04
#define CANFD2_TRANS_STAT_POR             0x80
/** \} */

/**
 * \defgroup transceiver_undervoltage_status_commands Transceiver Undervoltage Status Commands
 * \{
 */
#define CANFD2_TRANS_UV_STAT_VIO_STUV     0x01
#define CANFD2_TRANS_UV_STAT_VIO_LTUV     0x02
#define CANFD2_TRANS_UV_STAT_VCC_STUV     0x10
#define CANFD2_TRANS_UV_STAT_VCC_LTUV     0x20
#define CANFD2_TRANS_UV_STAT_VBAT_UV      0x80
/** \} */

/**
 * \defgroup error_status_commands Error Status Commands
 * \{
 */
#define CANFD2_ERR_STAT_CMD_ERR           0x01
#define CANFD2_ERR_STAT_COM_ERR           0x02
/** \} */

/**
 * \defgroup wake_status_commands Wake Status Commands
 * \{
 */
#define CANFD2_WAKE_STAT_WUF              0x01
#define CANFD2_WAKE_STAT_WUP              0x02
#define CANFD2_WAKE_STAT_LWU              0x04
#define CANFD2_WAKE_STAT_LWU_DIR          0x08
/** \} */

/**
 * \defgroup selective_wake_status_commands Selective Wake Status Commands
 * \{
 */
#define CANFD2_SWK_STAT_SWK_ACT          0x01
#define CANFD2_SWK_STAT_CANSIL           0x02
#define CANFD2_SWK_STAT_CANTO            0x04
#define CANFD2_SWK_STAT_SYNC             0x08
#define CANFD2_SWK_STAT_SYSERR           0x10
/** \} */

/**
 * \defgroup select_operation_mode Select Operation Mode
 * \{
 */
#define CANFD2_OP_MODE_SLEEP              0x01
#define CANFD2_OP_MODE_STANDBY            0x02
#define CANFD2_OP_MODE_RECEIVE_ONLY       0x03
#define CANFD2_OP_MODE_NORMAL             0x04
#define CANFD2_OP_MODE_UNKNOWN            0x05

#define DUMMY                                0
#define CANFD2_READ_CMD_MASK              0x7F
#define CANFD2_WRITE_CMD                  0x80
/** \} */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b canfd2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CANFD2_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define CANFD2_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*  \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

     digital_out_t cs;

    // Modules 

    uart_t uart;
    spi_master_t spi;
    pin_name_t chip_select;

    uint8_t uart_rx_buffer[ CANFD2_DRV_RX_BUFFER_SIZE ];
    uint8_t uart_tx_buffer[ CANFD2_DRV_TX_BUFFER_SIZE ];

} canfd2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.   

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} canfd2_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t canfd2_error_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void canfd2_cfg_setup ( canfd2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t canfd2_init ( canfd2_t *ctx, canfd2_cfg_t *cfg );

/**
 * @brief Generic write function.
 * 
 * @param canfd2 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void canfd2_generic_write ( canfd2_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param canfd2 Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * 
 * @return Number of reads data.
 */
int32_t canfd2_generic_read ( canfd2_t *ctx, uint8_t *data_buf, uint16_t max_len );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void canfd2_generic_transfer ( canfd2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Generic read the byte of data function
 *
 * @param ctx          Click object.
 * @param reg_addr     8-bit register address.
 * @return read_data
 *
 * @description This function read the the byte of data from the target 8-bit register address
 * of TLE9255W HS CAN Transceiver with Partial Networking
 * on CAN FD 2 Click board.
 */
uint8_t canfd2_read_data ( canfd2_t *ctx, uint8_t reg_addr );

/**
 * @brief Generic write the byte of data function
 *
 * @param ctx           Click object.
 * @param reg_addr      8-bit register address.
 * @param write_data    Byte of data to write.
 *
 * @return
 * 8-bit write status
 *
 * @description This function write the byte of data to the target 8-bit register address
 * of TLE9255W HS CAN Transceiver with Partial Networking
 * on CAN FD 2 Click board.
 */
void canfd2_write_data ( canfd2_t *ctx, uint8_t reg_addr, uint8_t write_data );

/**
 * @brief Set operating mode function
 *
 * @param ctx           Click object.
 * @param op_mode
 * - 1 ( CANFD2_OP_MODE_SLEEP )        : Normal mode;
 * - 2 ( CANFD2_OP_MODE_STANDBY )      : Receive mode;
 * - 3 ( CANFD2_OP_MODE_RECEIVE_ONLY ) : Stand-by mode;
 * - 4 ( CANFD2_OP_MODE_NORMAL )       : Sleep mode;
 *
 * @description This function set desired soperating mode
 * of TLE9255W HS CAN Transceiver with Partial Networking
 * on CAN FD 2 Click board.
 */
void canfd2_set_mode ( canfd2_t *ctx, uint8_t op_mode );

/**
 * @brief Get operating mode function
 *
 * @param ctx           Click object.
 *
 * @return operation mode:
 * - 1 ( CANFD2_OP_MODE_SLEEP )        : Normal mode;
 * - 2 ( CANFD2_OP_MODE_STANDBY )      : Receive mode;
 * - 3 ( CANFD2_OP_MODE_RECEIVE_ONLY ) : Stand-by mode;
 * - 4 ( CANFD2_OP_MODE_NORMAL )       : Sleep mode;
 *
 * @description This function set desired soperating mode
 * of TLE9255W HS CAN Transceiver with Partial Networking
 * on CAN FD 2 Click board.
 */
uint8_t canfd2_get_mode ( canfd2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _CANFD2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
