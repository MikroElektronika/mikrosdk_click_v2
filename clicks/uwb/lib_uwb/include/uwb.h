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
 * \brief This file contains API for UWB Click driver.
 *
 * \addtogroup uwb UWB Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UWB_H
#define UWB_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define UWB_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.irq   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UWB_OK                           0
#define UWB_ERROR                       -1
/** \} */

/**
 * \defgroup no_sub_address_macro No sub address macro
 * \{
 */
#define UWB_SUB_NO                       0x00
/** \} */

/**
 * \defgroup register_address_macros Register address macros
 * \{
 */
#define UWB_REG_DEV_ID                   0x00
#define UWB_REG_EU_ID                    0x01
#define UWB_REG_PAN_ID                   0x03
#define UWB_REG_SYS_CFG                  0x04
#define UWB_REG_SYS_CNT                  0x06
#define UWB_REG_SYS_TX_CTRL              0x08
#define UWB_REG_TX_DATA_BUF              0x09
#define UWB_REG_DX_TIME                  0x0A
#define UWB_REG_RX_TIMEOUT               0x0C
#define UWB_REG_SYS_CTRL                 0x0D
#define UWB_REG_SYS_EVENT_MASK           0x0E
#define UWB_REG_EVENT_STATUS             0x0F
#define UWB_REG_RX_INFO                  0x10
#define UWB_REG_RX_BUF                   0x11
#define UWB_REG_RX_QUALITY_INFO          0x12
#define UWB_REG_RX_TIME_INTERVAL         0x13
#define UWB_REG_RX_TIME_OFFSET           0x14
#define UWB_REG_RX_MESSAGE_TOA           0x15
#define UWB_REG_TX_MESSAGE_TOS           0x17
#define UWB_REG_TX_ANTD                  0x18
#define UWB_REG_SYS_STATE                0x19
#define UWB_REG_ACK_RESPONSE_TIME        0x1A
#define UWB_REG_RX_SNIFF_CFG             0x1D
#define UWB_REG_TX_POWER                 0x1E
#define UWB_REG_CHN_CTRL                 0x1F
#define UWB_REG_SFD                      0x21
#define UWB_REG_AUTO_GAIN_CFG            0x23
#define UWB_REG_EXTERNAL_SYNC            0x24
#define UWB_REG_READ_AA_DATA             0x25
#define UWB_REG_GPIO_CTRL                0x26
#define UWB_REG_DRX_CFG                  0x27
#define UWB_REG_RF_CFG                   0x28
#define UWB_REG_TX_CALIBRATION           0x2A
#define UWB_REG_FREQ_SYNTH_CTRL          0x2B
#define UWB_REG_ALWAYS_ON_REG            0x2C
#define UWB_REG_OTP_INTERFACE            0x2D
#define UWB_REG_LEAD_EDGE_DET_CTRL       0x2E
#define UWB_REG_DIGITAL_DIAG_IF          0x2F
#define UWB_REG_POWER_MANAGE_SYS_CTRL    0x36
/** \} */

/**
 * \defgroup otp_memory OTP memory
 * \{
 */
#define UWB_OTP_WRITE                    0x00
#define UWB_OTP_ADR                      0x04
#define UWB_OTP_CTRL                     0x06
#define UWB_OTP_STATUS                   0x08
#define UWB_OTP_RDAT                     0x0A
#define UWB_OTP_SRDAT                    0x0E
#define UWB_OTP_SF                       0x12
/** \} */

/**
 * \defgroup data_rate Data rate
 * \{
 */
#define UWB_DATA_RATE_110KBSPS           0x00
#define UWB_DATA_RATE_850KBSPS           0x01
#define UWB_DATA_RATE_6800KBSPS          0x02
/** \} */

/**
 * \defgroup pulese_frequency Pulese frequency
 * \{
 */
#define UWB_PULSTE_FREQ_4MHZ             0x00
#define UWB_PULSTE_FREQ_16MHZ            0x01
#define UWB_PULSTE_FREQ_64MHZ            0x02
/** \} */

/**
 * \defgroup preamble_length Preamble length
 * \{
 */
#define UWB_PREAMBLE_LEN_64              0x01
#define UWB_PREAMBLE_LEN_128             0x05
#define UWB_PREAMBLE_LEN_256             0x09
#define UWB_PREAMBLE_LEN_512             0x0D
#define UWB_PREAMBLE_LEN_1024            0x02
#define UWB_PREAMBLE_LEN_1536            0x06
#define UWB_PREAMBLE_LEN_2048            0x0A
#define UWB_PREAMBLE_LEN_4096            0x03
/** \} */

/**
 * \defgroup pac_size PAC size
 * \{
 */
#define UWB_PAC_SIZE_8                   8
#define UWB_PAC_SIZE_16                  16
#define UWB_PAC_SIZE_32                  32
#define UWB_PAC_SIZE_64                  64
/** \} */

/**
 * \defgroup channel Channel
 * \{
 */
#define UWB_CHANNEL_1                    1
#define UWB_CHANNEL_2                    2
#define UWB_CHANNEL_3                    3
#define UWB_CHANNEL_4                    4
#define UWB_CHANNEL_5                    5
#define UWB_CHANNEL_7                    7
/** \} */

/**
 * \defgroup preamble_code Preamble code
 * \{
 */
#define UWB_PREAMBLE_CODE_1              1
#define UWB_PREAMBLE_CODE_2              2
#define UWB_PREAMBLE_CODE_3              3
#define UWB_PREAMBLE_CODE_4              4
#define UWB_PREAMBLE_CODE_5              5
#define UWB_PREAMBLE_CODE_6              6
#define UWB_PREAMBLE_CODE_7              7
#define UWB_PREAMBLE_CODE_8              8
#define UWB_PREAMBLE_CODE_9              9
#define UWB_PREAMBLE_CODE_10             10
#define UWB_PREAMBLE_CODE_11             11
#define UWB_PREAMBLE_CODE_12             12
#define UWB_PREAMBLE_CODE_13             13
#define UWB_PREAMBLE_CODE_14             14
#define UWB_PREAMBLE_CODE_15             15
#define UWB_PREAMBLE_CODE_16             16
#define UWB_PREAMBLE_CODE_17             17
#define UWB_PREAMBLE_CODE_18             18
#define UWB_PREAMBLE_CODE_19             19
#define UWB_PREAMBLE_CODE_20             20
#define UWB_PREAMBLE_CODE_21             21
#define UWB_PREAMBLE_CODE_22             22
#define UWB_PREAMBLE_CODE_23             23
#define UWB_PREAMBLE_CODE_24             24
/** \} */

/**
 * \defgroup frame_length Frame length
 * \{
 */
#define UWB_FRAME_LEN_NORMAL             0x00
#define UWB_FRAME_LEN_EXTENDED           0x03
/** \} */

/**
 * \defgroup configuration_tranmit_type_mode Configuration tranmit type mode
 * \{
 */
#define UWB_HIGH                         1
#define UWB_LOW                          0
/** \} */

/**
 * \defgroup device_mode Device mode
 * \{
 */
#define UWB_DEV_ERROR                    0xFF
#define UWB_DEV_OK                       0x00
/** \} */

/**
 * \defgroup pin_bit_state Pin/bit state
 * \{
 */
#define UWB_MODE_IDLE                    1
#define UWB_MODE_RX                      2
#define UWB_MODE_TX                      3
/** \} */

/**
 * \defgroup function_return Function return
 * \{
 */
#define UWB_TAG                          0xDECA
/** \} */

/**
 * \defgroup masks Masks 
 * \{
 */
#define WRITE_MASK                       0x80
#define SUB_MASK                         0x40
#define READ_MASK                        0x00
#define SUB_EXT_MASK                     0x80
/** \} */

/**
 * \defgroup tunes Tunes
 * \{
 */
#define AGC_TUNE1_SUB                    0x04
#define AGC_TUNE2_SUB                    0x0C
#define AGC_TUNE3_SUB                    0x12
#define LEN_AGC_TUNE1                    2
#define LEN_AGC_TUNE2                    4
#define LEN_AGC_TUNE3                    2
#define DRX_TUNE0b_SUB                   0x02
#define DRX_TUNE1a_SUB                   0x04
#define DRX_TUNE1b_SUB                   0x06
#define DRX_TUNE2_SUB                    0x08
#define DRX_TUNE4H_SUB                   0x26
#define LEN_DRX_TUNE0b                   2
#define LEN_DRX_TUNE1a                   2
#define LEN_DRX_TUNE1b                   2
#define LEN_DRX_TUNE2                    4
#define LEN_DRX_TUNE4H                   2
#define LDE_CFG1_SUB                     0x0806
#define LDE_RXANTD_SUB                   0x1804
#define LDE_CFG2_SUB                     0x1806
#define LDE_REPC_SUB                     0x2804
#define LEN_LDE_CFG1                     1
#define LEN_LDE_CFG2                     2
#define LEN_LDE_REPC                     2
#define LEN_LDE_RXANTD                   2
#define LEN_TX_POWER                     4
#define RF_RXCTRLH_SUB                   0x0B
#define RF_TXCTRL_SUB                    0x0C
#define LEN_RF_RXCTRLH                   1
#define LEN_RF_TXCTRL                    4
#define TC_PGDELAY_SUB                   0x0B
#define LEN_TC_PGDELAY                   1
#define TC_SARC                          0x00
#define TC_SARL                          0x03
#define FS_PLLCFG_SUB                    0x07
#define FS_PLLTUNE_SUB                   0x0B
#define FS_XTALT_SUB                     0x0E
#define LEN_FS_PLLCFG                    4
#define LEN_FS_PLLTUNE                   1
#define LEN_FS_XTALT                     1
/** \} */

/**
 * \defgroup dummy_buffer Dummy buffer
 * \{
 */
#define DUMMY_BUFFER                     1024
/** \} */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b uwb_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define UWB_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define UWB_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE
/** \} */ // End group macro 
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

    digital_out_t rst;
    digital_out_t cs;

    // Input pins 

    digital_in_t irq;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    // Sub address offset
    
    uint16_t offset;

} uwb_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t irq;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} uwb_cfg_t;

/**
 * @brief Structure for device configuration
 */
typedef struct
{
    uint8_t dev_mode;
    uint8_t extended_frame;
    uint8_t pac_size;
    uint8_t pulse_freq;
    uint8_t data_rate;
    uint8_t preamble_len;
    uint8_t preamble_code;
    uint8_t channel;
    uint16_t antenna_delay;
    uint8_t antenna_calib;
    uint8_t smart_power;
    uint8_t frame_check;
    uint8_t permanent_rx;
    uint8_t debounce_clk_en;

}uwb_dev_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
extern const uint8_t UWB_TMODE_LONGDATA_RANGE_LOWPOWER[ 3 ];
extern const uint8_t UWB_TMODE_LONGDATA_RANGE_ACCURACY[ 3 ];
extern const uint8_t UWB_TMODE_LONGDATA_FAST_LOWPOWER[ 3 ];
extern const uint8_t UWB_TMODE_LONGDATA_FAST_ACCURACY[ 3 ];
extern const uint8_t UWB_TMODE_SHORTDATA_FAST_LOWPOWER[ 3 ];
extern const uint8_t UWB_TMODE_SHORTDATA_FAST_ACCURACY[ 3 ];

/** \} */ // End constants group
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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void uwb_cfg_setup ( uwb_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t uwb_init ( uwb_t *ctx, uwb_cfg_t *cfg );

/**
 * @brief Function for writing data to register
 * 
 * @param ctx             Click object. 
 * @param reg_adr         Register address.
 * @param tx_buf          Transmit buffer.
 * @param buf_len         Transmit buffer length.
 *
 * @details This function write data to register.
 */
void uwb_generic_write ( uwb_t *ctx, uint8_t reg_adr,  uint8_t *tx_buf, uint16_t buf_len );

/**
 * @brief Function for reading data from register
 * 
 * @param ctx             Click object.  
 * @param reg_adr         Register address.
 * @param rx_buf          Receive buffer.
 * @param buf_len         Receive buffer length.
 *
 * @details This function read data from register.
 */
void uwb_generic_read ( uwb_t *ctx, uint8_t reg_adr, uint8_t *rx_buf, uint16_t buf_len );

/**
 * @brief Function for setting rst pin status
 * 
 * @param ctx             Click object.  
 * @param status          Pin status.
 *
 * @details This function sets rst pin status.
 */
void uwb_set_rst_pin_status ( uwb_t *ctx, uint8_t status );

/**
 * @brief Function for getting irq pin status
 * 
 * @param ctx             Click object. 
 * 
 * @returns QINT pin status
 *
 * @details This function gets irq pin status.
 */
uint8_t uwb_get_qint_pin_status ( uwb_t *ctx );

/**
 * @brief Function for reading OTM memory
 * 
 * @param ctx             Click object.  
 * @param otp_adr         Otp register address.
 * @param rx_buf          Receive data buffer.
 *
 * @details This function read OTM memory.
 */
void uwb_read_otp ( uwb_t *ctx, uint16_t otp_adr, uint8_t *rx_buf );

/**
 * @brief Function for setting single bit state
 * 
 * @param ctx             Click object.  
 * @param reg_adr         Register address of bit.
 * @param bit_num         Bit number.
 * @param bit_state       Bit state.
 *
 * @details This function set single bit state.
 */
void uwb_set_bit ( uwb_t *ctx, uint8_t reg_adr, uint16_t bit_num, uint8_t bit_state );

/**
 * @brief Function for getting single bit state
 * 
 * @param ctx             Click object.  
 * @param reg_adr         Register address of bit.
 * @param bit_num         Bit number.
 * 
 * @returns Bit state getting single bit state.
 *
 * @details This function 
 */
uint8_t uwb_get_bit ( uwb_t *ctx, uint8_t reg_adr, uint16_t bit_num );

/**
 * @brief Function for getting length of register data
 * 
 * @param ctx             Click object.  
 * @param reg_adr         Register address.
 * 
 * @returns Register length
 *
 * @details This function get length of register data
 */
uint16_t uwb_reg_data_len ( uint8_t reg_adr );

/**
 * @brief Function for setting device address and network ID
 * 
 * @param ctx             Click object.  
 * @param dev_adr         Device address.
 * @param net_id          Network ID.
 *
 * @details This function set device address and network ID
 */
void uwb_set_dev_adr_n_network_id ( uwb_t *ctx, uint16_t dev_adr, uint16_t net_id );

/**
 * @brief Function for setting data rate
 * 
 * @param ctx             Click object.  
 * @param rate            Data rate.
 * 
 * @returns OK or ERROR macro
 *
 * @details This function set data rate.
 */
uint8_t uwb_set_data_rate ( uwb_t *ctx, uint8_t rate );

/**
 * @brief Function for setting pulse frequency
 * 
 * @param ctx             Click object.  
 * @param freq            Device pulse frequency.
 *
 * @details This function set pulse frequency.
 */
void uwb_set_pulse_freq ( uwb_t *ctx, uint8_t freq );

/**
 * @brief Function for setting preamble length
 * 
 * @param ctx             Click object.  
 * @param prealen         Device preamble length.
 *
 * @details This function set preamble length.
 */
void uwb_set_preamble_len ( uwb_t *ctx, uint8_t prealen );

/**
 * @brief Function for setting preamble code
 * 
 * @param ctx             Click object. 
 * @param preamble        Device preamble code.
 *
 * @details This function set preamble code.
 */
void uwb_set_preable_code ( uwb_t *ctx, uint8_t preamble );

/**
 * @brief Function for setting channel
 * 
 * @param ctx             Click object.  
 * @param channel         Device channel.
 *
 * @details This function set channel.
 */
void uwb_set_channel ( uwb_t *ctx, uint8_t channel );

/**
 * @brief Function for setting transmit type mode
 * 
 * @param ctx             Click object.  
 * @param t_t             Transmit type mode.
 *
 * @details This function set transmit type mode.
 */
void uwb_set_transmit_type ( uwb_t *ctx, const uint8_t *t_t );

/**
 * @brief Function for getting transmit data
 * 
 * @param ctx             Click object.  
 * @param rx_buf          Receive buffer.
 * @param len_buf         Transmit data length.
 *
 * @details This function get transmit data.
 */
void uwb_get_transmit ( uwb_t *ctx, uint8_t *rx_buf, uint16_t len_buf );

/**
 * @brief Function for getting transmit length
 * 
 * @param ctx             Click object. 
 * 
 * @returns transmit length
 *
 * @details This function get transmit length.
 */
uint8_t uwb_get_transmit_len ( uwb_t *ctx );

/**
 * @brief Function for setting transmit data
 * 
 * @param ctx             Click object.  
 * @param tx_buf          Transmit buffer.
 * @param len_buf         Transmit data length.
 *
 * @details This function set transmit data.
 */
void uwb_set_transmit ( uwb_t *ctx, uint8_t *tx_buf, uint16_t len_buf );

/**
 * @brief Function for setting smart power option
 * 
 * @param ctx             Click object.  
 * @param smart_power     Smart power data.
 *
 * @details This function set smart power option.
 */
void uwb_use_smart_power ( uwb_t *ctx, uint8_t smart_power );

/**
 * @brief Function for setting frame check option
 * 
 * @param ctx             Click object.  
 * @param fc_val          Frame check data.
 *
 * @details This function set frame check option.
 */
void uwb_frame_check ( uint8_t fc_val );

/**
 * @brief Function for setting frame filter option
 * 
 * @param ctx             Click object.   
 * @param ff_val          Frame filter data.
 *
 * @details This function set frame filter option.
 */
void uwb_frame_filter ( uwb_t *ctx, uint8_t ff_val );

/**
 * @brief Function for setting device working mode
 * 
 * @param ctx             Click object.   
 * @param mode            Device working mode.
 * 
 * @details This function set device working mode.
 * @note Should be first function called in driver after initialization.
 */
void uwb_set_mode ( uwb_t *ctx, uint8_t mode );

/**
 * @brief Function for starting communication of device
 * 
 * @param ctx             Click object.  
 *
 * @details This function start communication of device.
 * @note Function is called to start transmiting or receiving data.
 */
void uwb_start_transceiver ( uwb_t *ctx );

/**
 * @brief Function for getting transmit status
 * 
 * @param ctx             Click object.  
 * 
 * @returns OK or ERROR macro
 *
 * @details This function get transmit status.
 * @note Returns status is relative to previous selected device mode.
 */
uint8_t uwb_get_transmit_status ( uwb_t *ctx );

/**
 * @brief Function for clearing status
 * 
 * @param ctx             Click object.  
 *
 * @details This function clear status.
 * @note Clearing status relative to previous sleceted device mode.
 */
void uwb_clear_status ( uwb_t *ctx );

/**
 * @brief Function for setting interrupt mask
 * 
 * @param ctx             Click object.  
 *
 * @details This function set interrupt mask.
 * @note Setting interrupt mask relative to previous set device mode.
 */
void uwb_int_mask_set ( uwb_t *ctx );

/**
 * @brief Function for tuneing configuration for set values
 * 
 * @param ctx             Click object.  
 *
 * @details This function tune configuration for set values.
 * @note Should be called after other configuration is set. It will do some additional 
 *       configuration to device relative to some other parameteres.
 */
void uwb_tune_config ( uwb_t *ctx );

/**
 * @brief Function for reseting device
 *
 * @param ctx             Click object.  
 *
 * @details This function reset device.
 */
void uwb_dev_reset ( uwb_t *ctx );

/**
 * @brief Function for enabling device
 *
 * @param ctx             Click object.  
 *
 * @details This function enables device.
 */
void uwb_enable ( uwb_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _UWB_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
