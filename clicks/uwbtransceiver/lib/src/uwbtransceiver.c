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
 */

#include "uwbtransceiver.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define UWBTRANSCEIVER_DUMMY 0

// ------------------------------------------------------------------ CONSTANTS

const uint8_t UWB_TMODE_LONGDATA_RANGE_LOWPOWER[ 3 ] 
          = { UWB_DATA_RATE_110KBSPS,
              UWB_PULSTE_FREQ_16MHZ,
              UWB_PREAMBLE_LEN_2048 };
const uint8_t UWB_TMODE_LONGDATA_RANGE_ACCURACY[ 3 ] 
          = { UWB_DATA_RATE_110KBSPS,
              UWB_PULSTE_FREQ_64MHZ,
              UWB_PREAMBLE_LEN_2048 };
const uint8_t UWB_TMODE_LONGDATA_FAST_LOWPOWER[ 3 ] 
          = { UWB_DATA_RATE_6800KBSPS,
              UWB_PULSTE_FREQ_16MHZ,
              UWB_PREAMBLE_LEN_1024 };
const uint8_t UWB_TMODE_LONGDATA_FAST_ACCURACY[ 3 ] 
          = { UWB_DATA_RATE_6800KBSPS,
              UWB_PULSTE_FREQ_64MHZ,
              UWB_PREAMBLE_LEN_1024 };
const uint8_t UWB_TMODE_SHORTDATA_FAST_LOWPOWER[ 3 ] 
          = { UWB_DATA_RATE_6800KBSPS,
              UWB_PULSTE_FREQ_16MHZ,
              UWB_PREAMBLE_LEN_128 };
const uint8_t UWB_TMODE_SHORTDATA_FAST_ACCURACY[ 3 ] 
          = { UWB_DATA_RATE_6800KBSPS,
              UWB_PULSTE_FREQ_64MHZ,
              UWB_PREAMBLE_LEN_128 };
              
// ------------------------------------------------------------------ VARIABLES

/**
 * @brief Default configuration for device
 */
static uwb_dev_t dev_cfg = 
{ 
    UWB_MODE_IDLE,
    UWB_FRAME_LEN_NORMAL,
    UWB_PAC_SIZE_8,
    UWB_PULSTE_FREQ_16MHZ,
    UWB_DATA_RATE_850KBSPS,
    UWB_PREAMBLE_LEN_256,
    UWB_PREAMBLE_CODE_3,
    UWB_CHANNEL_5,
    16384,
    0,
    1,
    1,
    1,
    0
};

static uint8_t uwb_dummy[ 1024 ] = { 0x00 };

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Converts value to array
 */
static void dev_value_to_array ( uint32_t value, uint8_t *array, uint8_t array_len );

/**
 * @brief Configuration function
 */
static void dev_agc_tune_1 ( uint8_t *agc_tune );

/**
 * @brief Configuration function
 */
static void dev_agc_tune_2 ( uint8_t *agc_tune );

/**
 * @brief Configuration function
 */
static void dev_agc_tune_3 ( uint8_t *agc_tune );

/**
 * @brief Configuration function
 */
static void dev_drx_tune_0b ( uint8_t *drx_tune );

/**
 * @brief Configuration function
 */
static void dev_drx_tune_1a ( uint8_t *drx_tune );

/**
 * @brief Configuration function
 */
static void dev_drx_tune_1b ( uint8_t *drx_tune );

/**
 * @brief Configuration function
 */
static void dev_drx_tune_2 ( uint8_t *drx_tune );

/**
 * @brief Configuration function
 */
static void dev_drx_tune_4h ( uint8_t *drx_tune );

/**
 * @brief Configuration function
 */
static void dev_lde_cfg_1 ( uint8_t *lde_cfg );

/**
 * @brief Configuration function
 */
static void dev_lde_cfg_2 ( uint8_t *lde_cfg );

/**
 * @brief Configuration function
 */
static void dev_lde_repc_help ( uint8_t *lde_cfg , uint32_t r_110, uint32_t r_o );

/**
 * @brief Configuration function
 */
static void dev_lde_repc ( uint8_t *lde_cfg );

/**
 * @brief Configuration function
 */
static void dev_tx_power_help ( uint8_t *tx_power , uint32_t sp, uint32_t nsp );

/**
 * @brief Configuration function
 */
static void dev_tx_power ( uint8_t *tx_power );

/**
 * @brief Configuration function
 */
static void dev_rf_rx_ctrl ( uint8_t *rf_ctrl );

/**
 * @brief Configuration function
 */
static void dev_rf_tx_ctrl ( uint8_t *rf_ctrl );

/**
 * @brief Configuration function
 */
static void dev_tcpg_delay ( uint8_t *tcpg_delay );

/**
 * @brief Configuration function
 */
static void dev_fs_pll_cfg ( uint8_t *fs );

/**
 * @brief Configuration function
 */
static void dev_fs_pll_tune ( uint8_t *fs );

/**
 * @brief Configuration function
 */
static void dev_fs_xtalt ( uwbtransceiver_t *ctx, uint8_t *fs );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void uwbtransceiver_cfg_setup ( uwbtransceiver_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->irq = HAL_PIN_NC;

    cfg->spi_speed = SPI_MEDIUM; 
    cfg->spi_mode = SPI_MODE_0;
}

UWBTRANSCEIVER_RETVAL uwbtransceiver_init ( uwbtransceiver_t *ctx, uwbtransceiver_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode        = cfg->spi_mode;
    spi_cfg.speed       = cfg->spi_speed;
    spi_cfg.pins.sck    = cfg->sck;
    spi_cfg.pins.miso   = cfg->miso;
    spi_cfg.pins.mosi   = cfg->mosi;
    spi_cfg.chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) != SPI_SUCCESS )
    {
        return UWBTRANSCEIVER_INIT_ERROR;
    }

    spi_master_set_dummy_data( &ctx->spi, UWBTRANSCEIVER_DUMMY );

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->irq, cfg->irq );
    

    spi_master_stop( &ctx->spi );    
    digital_out_high( &ctx->rst );

    return UWBTRANSCEIVER_OK;
}

void uwbtransceiver_generic_transfer ( uwbtransceiver_t *ctx, spi_master_transfer_data_t *block )
{
    spi_master_start( &ctx->spi );
    spi_master_transfer( &ctx->spi, block );
    spi_master_stop( &ctx->spi );    
}

void uwb_generic_write ( uwbtransceiver_t *ctx, uint8_t reg_adr,  uint8_t *tx_buf, uint16_t buf_len )
{
    uint8_t address_data[ 3 ];
    uint8_t address_len = 1;
    uint16_t data_cnt = 0;

    address_data[ 0 ] = WRITE_MASK | reg_adr;

    if ( UWB_SUB_NO != ctx->offset )
    {
        address_data[ 0 ] |= SUB_MASK;
        if ( ctx->offset < 128 )
        {
            address_data[ 1 ] = ( uint8_t ) ctx->offset & 0x7F;
            address_len++;
        }
        else
        {
            address_data[ 1 ] = SUB_EXT_MASK | ( uint8_t )( ctx->offset & 0xFF );
            address_data[ 2 ] = ( uint8_t )( ( ctx->offset >> 8 ) & 0xFF );
            address_len += 2;
        }
    }

    spi_master_start( &ctx->spi );

    for ( data_cnt = 0; data_cnt < address_len; data_cnt++ )
    {
        spi_master_write( &ctx->spi, address_data[ data_cnt ] );
    }

    for ( data_cnt = 0; data_cnt < buf_len; data_cnt++ )
    {
        spi_master_write( &ctx->spi, tx_buf[ data_cnt ] );
    }

    spi_master_stop( &ctx->spi );
    Delay_10ms(  );
}

void uwb_generic_read ( uwbtransceiver_t *ctx, uint8_t reg_adr, uint8_t *rx_buf, uint16_t buf_len )
{
    uint8_t address_data[ 3 ];
    uint8_t address_len = 1;
    uint16_t data_cnt = 0;

    address_data[ 0 ] = READ_MASK | reg_adr;

    if ( UWB_SUB_NO != ctx->offset )
    {
        address_data[ 0 ] |= SUB_MASK;
        if ( ctx->offset < 128 )
        {
            address_data[ 1 ] = ( uint8_t )ctx->offset & 0x7F;
            address_len++;
        }
        else
        {
            address_data[ 1 ] = SUB_EXT_MASK | ( uint8_t )( ctx->offset & 0xFF );
            address_data[ 2 ] = ( uint8_t )( ( ctx->offset >> 8 ) & 0xFF );
            address_len += 2;
        }
    }
    
    spi_master_start( &ctx->spi );

    for ( data_cnt = 0; data_cnt < address_len; data_cnt++ )
    {
        spi_master_write( &ctx->spi, address_data[ data_cnt ] );
    }

    for ( data_cnt = 0; data_cnt < buf_len; data_cnt++ )
    {
        rx_buf[ data_cnt ] = spi_master_read( &ctx->spi );
    }

    spi_master_stop( &ctx->spi );
    Delay_10ms(  );
    
    Delay_10ms(  );
}

void uwb_set_rst_pin_status ( uwbtransceiver_t *ctx, uint8_t status )
{
    digital_out_write( &ctx->rst, status );
}

uint8_t uwb_get_qint_pin_status ( uwbtransceiver_t *ctx )
{
    return digital_in_read( &ctx->irq );
}

void uwb_read_otp ( uwbtransceiver_t *ctx, uint16_t otp_adr, uint8_t *rx_buf )
{
    uint8_t address_bytes[ 2 ];
    uint8_t temp_dat;
        
        address_bytes[ 0 ] = ( otp_adr & 0xFF );
        address_bytes[ 1 ] = ( ( otp_adr >> 8 ) & 0xFF );

    ctx->offset = UWB_OTP_ADR;
    uwb_generic_write( ctx, UWB_REG_OTP_INTERFACE, address_bytes, 2 );
    temp_dat = 0x03;
    ctx->offset = UWB_OTP_CTRL;
    uwb_generic_write( ctx, UWB_REG_OTP_INTERFACE, &temp_dat, 1 );
    temp_dat = 0x01;
    uwb_generic_write( ctx, UWB_REG_OTP_INTERFACE, &temp_dat, 1 );
    ctx->offset = UWB_OTP_RDAT;
    uwb_generic_read( ctx, UWB_REG_OTP_INTERFACE, rx_buf, 4 );
    temp_dat = 0x00;
    ctx->offset = UWB_OTP_CTRL;
    uwb_generic_write( ctx, UWB_REG_OTP_INTERFACE, &temp_dat, 1 );
}

void uwb_set_bit ( uwbtransceiver_t *ctx, uint8_t reg_adr, uint16_t bit_num, uint8_t bit_state )
{
    uint8_t reg_data[ 1024 ] = { 0 };
    uint8_t byte_num = 0;
    uint8_t temp_bit;
    uint16_t data_len;

    data_len = uwb_reg_data_len( reg_adr );

    if ( UWB_ERROR == data_len )
    {
        return;
    }
    ctx->offset = UWB_SUB_NO;
    uwb_generic_read( ctx, reg_adr, reg_data, data_len );

    byte_num = bit_num / 8;

    if ( byte_num > data_len )
    {
        return;
    }

    if ( 0 != byte_num )
    {
        temp_bit = bit_num % 8;
    }
    else
    {
        temp_bit = bit_num;
    }

    if ( bit_state )
    {
        reg_data[ byte_num ] |= ( 1 << temp_bit );
    }
    else
    {
        reg_data[ byte_num ]  &= ~( 1 << bit_num );
    }

    ctx->offset = UWB_SUB_NO;
    uwb_generic_write( ctx, reg_adr, reg_data, data_len );
}

uint8_t uwb_get_bit ( uwbtransceiver_t *ctx, uint8_t reg_adr, uint16_t bit_num )
{
    uint8_t reg_data[ 1024 ] = { 0 };
    uint8_t byte_num = 0;
    uint8_t temp_bit;
    uint8_t temp_mask;
    uint16_t data_len;

    data_len = uwb_reg_data_len( reg_adr );

    if ( UWB_ERROR == data_len )
    {
        return UWB_ERROR;
    }
    ctx->offset = UWB_SUB_NO;
    uwb_generic_read( ctx, reg_adr, reg_data, data_len );
    
    byte_num = bit_num / 8;

    if ( byte_num > data_len )
    {
        return UWB_ERROR;
    }

    if ( 0 != byte_num )
    {
        temp_bit = bit_num % 8;
    }
    else
    {
        temp_bit = bit_num;
    }

    temp_mask = reg_data[ byte_num ] >> temp_bit;
    temp_mask &= 0x01;

    return temp_mask;
}

uint16_t uwb_reg_data_len ( uint8_t reg_adr )
{
    switch ( reg_adr )
    {
        case UWB_REG_DEV_ID:
            return 4;
        case UWB_REG_EU_ID:
            return 8;
        case UWB_REG_PAN_ID:
            return 4;
        case UWB_REG_SYS_CFG:
            return 4;
        case UWB_REG_SYS_CNT:
            return 5;
        case UWB_REG_SYS_TX_CTRL:
            return 5;
        case UWB_REG_DX_TIME:
            return 5;
        case UWB_REG_RX_TIMEOUT:
            return 2;
        case UWB_REG_SYS_CTRL:
            return 4;
        case UWB_REG_SYS_EVENT_MASK:
            return 4;
        case UWB_REG_EVENT_STATUS:
            return 5;
        case UWB_REG_RX_INFO:
            return 4;
        case UWB_REG_RX_QUALITY_INFO:
            return 8;
        case UWB_REG_RX_TIME_INTERVAL:
            return 4;
        case UWB_REG_RX_TIME_OFFSET:
            return 5;
        case UWB_REG_RX_MESSAGE_TOA:
            return 14;
        case UWB_REG_TX_MESSAGE_TOS:
            return 10;
        case UWB_REG_TX_ANTD:
            return 2;
        case UWB_REG_SYS_STATE:
            return 5;
        case UWB_REG_ACK_RESPONSE_TIME:
            return 4;
        case UWB_REG_RX_SNIFF_CFG:
            return 4;
        case UWB_REG_TX_POWER:
            return 4;
        case UWB_REG_CHN_CTRL:
            return 4;
        case UWB_REG_SFD:
            return 41;
        case UWB_REG_AUTO_GAIN_CFG:
            return 33;
        case UWB_REG_EXTERNAL_SYNC:
            return 12;
        case UWB_REG_READ_AA_DATA:
            return 4064;
        case UWB_REG_GPIO_CTRL:
            return 44;
        case UWB_REG_DRX_CFG:
            return 44;
        case UWB_REG_RF_CFG:
            return 58;
        case UWB_REG_TX_CALIBRATION:
            return 52;
        case UWB_REG_FREQ_SYNTH_CTRL:
            return 21;
        case UWB_REG_ALWAYS_ON_REG:
            return 12;
        case UWB_REG_OTP_INTERFACE:
            return 18;
        case UWB_REG_DIGITAL_DIAG_IF:
            return 41;
        case UWB_REG_POWER_MANAGE_SYS_CTRL:
            return 48;
        case UWB_REG_TX_DATA_BUF:
            return 1024;
        case UWB_REG_RX_BUF:
            return 1024;
        default:
            return UWB_ERROR;
    }
}

void uwb_set_dev_adr_n_network_id ( uwbtransceiver_t *ctx, uint16_t dev_adr, uint16_t net_id )
{
    uint8_t temp_id[ 4 ] = { 0 };
    uint8_t id_len;

    temp_id[ 0 ] = ( dev_adr >> 8 ) & 0xFF;
    temp_id[ 1 ] = dev_adr & 0xFF;
    temp_id[ 2 ] = ( net_id >> 8 ) & 0xFF;
    temp_id[ 3 ] = net_id & 0xFF;

    id_len = uwb_reg_data_len( UWB_REG_PAN_ID );
    ctx->offset = UWB_SUB_NO;
    uwb_generic_write( ctx, UWB_REG_PAN_ID, temp_id, id_len );
}

uint8_t uwb_set_data_rate ( uwbtransceiver_t *ctx, uint8_t rate )
{
    uint8_t sfd_len;
    uint8_t tx_ctrl[ 5 ];
    uint16_t adr_len;

    switch ( rate )
    {
        case UWB_DATA_RATE_110KBSPS:
        {
            uwb_set_bit( ctx, UWB_REG_SYS_CFG, 22, UWB_HIGH );      //rxm110k
            uwb_set_bit( ctx, UWB_REG_CHN_CTRL, 17, UWB_HIGH );     //dwsfd
            uwb_set_bit( ctx, UWB_REG_CHN_CTRL, 20, UWB_LOW );      //tnssfd
            uwb_set_bit( ctx, UWB_REG_CHN_CTRL, 21, UWB_LOW );      //rnssfd
            sfd_len = 0x40;
            break;
        }
        case UWB_DATA_RATE_850KBSPS:
        {
            uwb_set_bit( ctx, UWB_REG_SYS_CFG, 22, UWB_LOW );       //rxm110k
            uwb_set_bit( ctx, UWB_REG_CHN_CTRL, 17, UWB_HIGH );     //dwsfd
            uwb_set_bit( ctx, UWB_REG_CHN_CTRL, 20, UWB_HIGH );     //tnssfd
            uwb_set_bit( ctx, UWB_REG_CHN_CTRL, 21, UWB_HIGH );     //rnssfd
            sfd_len = 0x10;
            break;
        }
        case UWB_DATA_RATE_6800KBSPS:
        {
            uwb_set_bit( ctx, UWB_REG_SYS_CFG, 22, UWB_LOW );       //rxm110k
            uwb_set_bit( ctx, UWB_REG_CHN_CTRL, 17, UWB_LOW );      //dwsfd
            uwb_set_bit( ctx, UWB_REG_CHN_CTRL, 20, UWB_LOW );      //tnssfd
            uwb_set_bit( ctx, UWB_REG_CHN_CTRL, 21, UWB_LOW );      //rnssfd
            sfd_len = 0x08;
            break;
        }
        default:
        {
            return UWB_ERROR;
        }
    }
    adr_len = uwb_reg_data_len( UWB_REG_SYS_TX_CTRL );
    ctx->offset = UWB_SUB_NO;
    uwb_generic_read ( ctx, UWB_REG_SYS_TX_CTRL, tx_ctrl, adr_len );
    tx_ctrl[ 1 ] &= 0x83;
    tx_ctrl[ 1 ] |= ( rate << 5 ) & 0xFF;
    uwb_generic_write( ctx, UWB_REG_SYS_TX_CTRL, tx_ctrl, adr_len );
    uwb_generic_write( ctx, UWB_REG_SFD, &sfd_len, 1 );
    dev_cfg.data_rate = rate;
    return UWB_OK;
}

void uwb_set_pulse_freq ( uwbtransceiver_t *ctx, uint8_t freq )
{
    uint8_t tx_ctrl[ 5 ];
    uint16_t tx_len;
    uint8_t chn_ctrl[ 4 ];
    uint16_t chn_len;

    tx_len = uwb_reg_data_len( UWB_REG_SYS_TX_CTRL );
    chn_len = uwb_reg_data_len( UWB_REG_CHN_CTRL );

    ctx->offset = UWB_SUB_NO;
    uwb_generic_read( ctx, UWB_REG_SYS_TX_CTRL, tx_ctrl, tx_len );
    uwb_generic_read( ctx, UWB_REG_CHN_CTRL, chn_ctrl, chn_len );

    freq &= 0x03;
    tx_ctrl[ 2 ] &= 0xFC;
    tx_ctrl[ 2 ] |= freq & 0xFF;
    chn_ctrl[ 2 ] &= 0xF3;
    chn_ctrl[ 2 ] |= ( freq << 2 ) & 0xFF;

    uwb_generic_write( ctx, UWB_REG_SYS_TX_CTRL, tx_ctrl, tx_len );
    uwb_generic_write( ctx, UWB_REG_CHN_CTRL, chn_ctrl, chn_len );
    dev_cfg.pulse_freq = freq;
}

void uwb_set_preamble_len ( uwbtransceiver_t *ctx, uint8_t prealen )
{
    uint8_t tx_ctrl[ 5 ];
    uint16_t tx_len;

    tx_len = uwb_reg_data_len( UWB_REG_SYS_TX_CTRL );

    ctx->offset = UWB_SUB_NO;
    uwb_generic_read( ctx, UWB_REG_SYS_TX_CTRL, tx_ctrl, tx_len );

    prealen &= 0x0F;
    tx_ctrl[ 2 ] &= 0xC3;
    tx_ctrl[ 2 ] |= ( prealen << 2 ) & 0xFF;

    if ( ( UWB_PREAMBLE_LEN_64 == prealen ) || ( UWB_PREAMBLE_LEN_128 == prealen ) )
    {
        dev_cfg.pac_size = UWB_PAC_SIZE_8;
    }
    else if ( ( UWB_PREAMBLE_LEN_256 == prealen ) || ( UWB_PREAMBLE_LEN_512 == prealen ) )
    {
        dev_cfg.pac_size = UWB_PAC_SIZE_16;
    }
    else if ( UWB_PREAMBLE_LEN_1024 == prealen )
    {
        dev_cfg.pac_size = UWB_PAC_SIZE_32;
    }
    else
    {
        dev_cfg.pac_size = UWB_PAC_SIZE_64;
    }
    
    dev_cfg.preamble_len = prealen;

    uwb_generic_write( ctx, UWB_REG_SYS_TX_CTRL, tx_ctrl, tx_len );
}

void uwb_set_preable_code ( uwbtransceiver_t *ctx, uint8_t preamble )
{
    uint8_t chn_ctrl[ 4 ];
    uint16_t chn_len;

    preamble &= 0x1F;

    chn_len = uwb_reg_data_len( UWB_REG_CHN_CTRL );
    ctx->offset = UWB_SUB_NO;
    uwb_generic_read( ctx, UWB_REG_CHN_CTRL, chn_ctrl, chn_len );

    chn_ctrl[ 2 ] &= 0x3F;
    chn_ctrl[ 2 ] |= ( preamble << 6 ) & 0xFF;
    chn_ctrl[ 3 ] = 0x00;
    chn_ctrl[ 3 ] = ( ( ( ( preamble >> 2 ) & 0x07 ) | ( preamble << 3 ) ) & 0xFF );

    uwb_generic_write( ctx, UWB_REG_CHN_CTRL, chn_ctrl, chn_len );
    dev_cfg.preamble_code = preamble;
}

void uwb_set_channel ( uwbtransceiver_t *ctx, uint8_t channel )
{
    channel &= 0xF;
    dev_cfg.channel = channel;

    if ( UWB_CHANNEL_1 == channel )
    {
        if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
        {
            uwb_set_preable_code( ctx, UWB_PREAMBLE_CODE_2 );
        }
        else
        {
            uwb_set_preable_code( ctx, UWB_PREAMBLE_CODE_10 );
        }
    }
    else if ( UWB_CHANNEL_3 == channel )
    {
        if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
        {
            uwb_set_preable_code( ctx, UWB_PREAMBLE_CODE_6 );
        }
        else
        {
            uwb_set_preable_code( ctx, UWB_PREAMBLE_CODE_10 );
        }
    }
    else if ( ( UWB_CHANNEL_4 == channel ) || 
              ( UWB_CHANNEL_7 == channel ) )
    {
        if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
        {
            uwb_set_preable_code( ctx, UWB_PREAMBLE_CODE_8 );
        }
        else
        {
            uwb_set_preable_code( ctx, UWB_PREAMBLE_CODE_18 );
        }
    }
    else if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
    {
        uwb_set_preable_code( ctx, UWB_PREAMBLE_CODE_4 );
    }
    else
    {
        uwb_set_preable_code( ctx, UWB_PREAMBLE_CODE_10 );
    }
}

void uwb_set_transmit_type ( uwbtransceiver_t *ctx, const uint8_t *t_t )
{
    uwb_set_data_rate( ctx, t_t[ 0 ] );
    uwb_set_pulse_freq( ctx, t_t[ 1 ] );
    uwb_set_preamble_len( ctx, t_t[ 2 ] );
}

void uwb_get_transmit ( uwbtransceiver_t *ctx, uint8_t *rx_buf, uint16_t len_buf )
{
    ctx->offset = UWB_SUB_NO;
    uwb_generic_read( ctx, UWB_REG_RX_BUF, rx_buf, len_buf );
}

uint8_t uwb_get_transmit_len ( uwbtransceiver_t *ctx )
{
    uint8_t reg_data[ 4 ];
    uint8_t temp_len;

    ctx->offset = UWB_SUB_NO;
    uwb_generic_read( ctx, UWB_REG_RX_INFO, reg_data, 4 );

    temp_len = reg_data[ 0 ] & 0x7F;

    return temp_len;
}

void uwb_set_transmit ( uwbtransceiver_t *ctx, uint8_t *tx_buf, uint16_t len_buf )
{
    ctx->offset = UWB_SUB_NO;
    uwb_generic_write( ctx, UWB_REG_TX_DATA_BUF, uwb_dummy, DUMMY_BUFFER );
                                 
    uwb_generic_write( ctx, UWB_REG_TX_DATA_BUF, tx_buf, len_buf );
}

void uwb_use_smart_power ( uwbtransceiver_t *ctx, uint8_t smart_power )
{
    uwb_set_bit( ctx, UWB_REG_SYS_CFG, 18, smart_power );

    dev_cfg.smart_power = smart_power;
}

void uwb_frame_check ( uint8_t fc )
{
    dev_cfg.frame_check = !fc;
}

void uwb_frame_filter ( uwbtransceiver_t *ctx, uint8_t ff )
{
    uwb_set_bit( ctx, UWB_REG_SYS_CFG, 0, ff );
}

void uwb_set_mode ( uwbtransceiver_t *ctx, uint8_t mode )
{
    dev_cfg.dev_mode = mode;
    if ( UWB_MODE_IDLE == mode )
    {
        uwb_set_bit( ctx, UWB_REG_SYS_CTRL, 6, UWB_HIGH );
    }
    else if ( UWB_MODE_RX == mode )
    {
        uwb_tune_config( ctx );
        uwb_set_bit( ctx, UWB_REG_SYS_CTRL, 6, UWB_LOW );
        uwb_set_bit( ctx, UWB_REG_SYS_CFG, 29, UWB_HIGH );
    }
    else if ( UWB_MODE_TX == mode )
    {
        uwb_tune_config( ctx );
        uwb_set_bit( ctx, UWB_REG_SYS_CTRL, 6, UWB_LOW );
    }
}

void uwb_start_transceiver ( uwbtransceiver_t *ctx )
{
    uwb_set_bit( ctx, UWB_REG_SYS_CTRL, 0, !dev_cfg.frame_check );
    if ( UWB_MODE_RX == dev_cfg.dev_mode )
    {
        uwb_set_bit( ctx, UWB_REG_SYS_CTRL, 8, UWB_HIGH );
    }
    else if ( UWB_MODE_TX == dev_cfg.dev_mode )
    {
        uwb_set_bit( ctx, UWB_REG_SYS_CTRL, 1, UWB_HIGH );
    }
}

uint8_t uwb_get_transmit_status ( uwbtransceiver_t *ctx )
{
    uint8_t temp_status;

    if ( UWB_MODE_RX == dev_cfg.dev_mode )
    {
        temp_status = uwb_get_bit( ctx, UWB_REG_EVENT_STATUS, 8 );
    }
    else if ( UWB_MODE_TX == dev_cfg.dev_mode )
    {
        temp_status = uwb_get_bit( ctx, UWB_REG_EVENT_STATUS, 7 );
    }
    else
    {
        return UWB_ERROR;
    }
    
    return temp_status;
}

void uwb_clear_status ( uwbtransceiver_t *ctx )
{
    uint8_t temp_clr[ 5 ] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    if ( UWB_MODE_RX == dev_cfg.dev_mode )
    {
        uwb_set_bit( ctx, UWB_REG_EVENT_STATUS, 13, UWB_HIGH );
        uwb_set_bit( ctx, UWB_REG_EVENT_STATUS, 10, UWB_HIGH );
        uwb_set_bit( ctx, UWB_REG_EVENT_STATUS, 18, UWB_HIGH );
        uwb_set_bit( ctx, UWB_REG_EVENT_STATUS, 12, UWB_HIGH );
        uwb_set_bit( ctx, UWB_REG_EVENT_STATUS, 15, UWB_HIGH );
        uwb_set_bit( ctx, UWB_REG_EVENT_STATUS, 14, UWB_HIGH );
        uwb_set_bit( ctx, UWB_REG_EVENT_STATUS, 16, UWB_HIGH );
    }
    else if ( UWB_MODE_TX == dev_cfg.dev_mode )
    {
        uwb_set_bit( ctx, UWB_REG_EVENT_STATUS, 4, UWB_HIGH );
        uwb_set_bit( ctx, UWB_REG_EVENT_STATUS, 5, UWB_HIGH );
        uwb_set_bit( ctx, UWB_REG_EVENT_STATUS, 6, UWB_HIGH );
        uwb_set_bit( ctx, UWB_REG_EVENT_STATUS, 7, UWB_HIGH );
    }
}

void uwb_int_mask_set ( uwbtransceiver_t *ctx )
{
    uint8_t int_mask[ 4 ];
    uint32_t int_mask_val;
    
    if ( UWB_MODE_TX == dev_cfg.dev_mode )
    {
        int_mask_val = 0x00000020;
    }
    else if ( UWB_MODE_RX == dev_cfg.dev_mode )
    {
        int_mask_val = 0x00006000;
    }
    
    dev_value_to_array( int_mask_val, int_mask, 4 );
    ctx->offset = UWB_SUB_NO;
    uwb_generic_write( ctx, UWB_REG_SYS_EVENT_MASK, int_mask, 4 );
}

void uwb_tune_config ( uwbtransceiver_t *ctx )
{
    uint8_t agc_cfg_1[ 2 ];
    uint8_t agc_cfg_2[ 4 ];
    uint8_t agc_cfg_3[ 2 ];
    uint8_t drx_cfg_0b[ 2 ];
    uint8_t drx_cfg_1a[ 2 ];
    uint8_t drx_cfg_1b[ 2 ];
    uint8_t drx_cfg_2[ 4 ];
    uint8_t drx_cfg_4h[ 2 ];
    uint8_t lde_cfg_1[ 1 ];
    uint8_t lde_cfg_2[ 2 ];
    uint8_t lde_repc[ 2 ];
    uint8_t tx_power[ 4 ];
    uint8_t rf_rx_ctrl[ 1 ];
    uint8_t rf_tx_ctrl[ 4 ];
    uint8_t tcpg_delay[ 1 ];
    uint8_t fs_pll_cfg[ 4 ];
    uint8_t fs_pll_tune[ 1 ];
    uint8_t fs_xtalt[ 1 ];

    dev_agc_tune_1( agc_cfg_1 );
    dev_agc_tune_2( agc_cfg_2 );
    dev_agc_tune_3( agc_cfg_3 );
    dev_drx_tune_0b( drx_cfg_0b );
    dev_drx_tune_1a( drx_cfg_1a );
    dev_drx_tune_1b( drx_cfg_1b );
    dev_drx_tune_2( drx_cfg_2 );
    dev_drx_tune_4h( drx_cfg_4h );
    dev_lde_cfg_1( lde_cfg_1 );
    dev_lde_cfg_2( lde_cfg_2 );
    dev_lde_repc( lde_repc );
    dev_tx_power( tx_power );
    dev_rf_rx_ctrl( rf_rx_ctrl );
    dev_rf_tx_ctrl( rf_tx_ctrl );
    dev_tcpg_delay( tcpg_delay );
    dev_fs_pll_cfg( fs_pll_cfg );
    dev_fs_pll_tune( fs_pll_tune );
    dev_fs_xtalt( ctx, fs_xtalt );

    ctx->offset = AGC_TUNE1_SUB;
    uwb_generic_write( ctx, UWB_REG_AUTO_GAIN_CFG, agc_cfg_1, LEN_AGC_TUNE1 );
    ctx->offset = AGC_TUNE2_SUB;
    uwb_generic_write( ctx, UWB_REG_AUTO_GAIN_CFG, agc_cfg_2, LEN_AGC_TUNE2 );
    ctx->offset = AGC_TUNE3_SUB;
    uwb_generic_write( ctx, UWB_REG_AUTO_GAIN_CFG, agc_cfg_3, LEN_AGC_TUNE3 );
    ctx->offset = DRX_TUNE0b_SUB;
    uwb_generic_write( ctx, UWB_REG_DRX_CFG, drx_cfg_0b, LEN_DRX_TUNE0b );
    ctx->offset = DRX_TUNE1a_SUB;
    uwb_generic_write( ctx, UWB_REG_DRX_CFG, drx_cfg_1a, LEN_DRX_TUNE1a );
    ctx->offset = DRX_TUNE1b_SUB;
    uwb_generic_write( ctx, UWB_REG_DRX_CFG, drx_cfg_1b, LEN_DRX_TUNE1b );
    ctx->offset = DRX_TUNE2_SUB;
    uwb_generic_write( ctx, UWB_REG_DRX_CFG, drx_cfg_2, LEN_DRX_TUNE2 );
    ctx->offset = DRX_TUNE4H_SUB;
    uwb_generic_write( ctx, UWB_REG_DRX_CFG, drx_cfg_4h, LEN_DRX_TUNE4H );
    ctx->offset = LDE_CFG1_SUB;
    uwb_generic_write( ctx, UWB_REG_LEAD_EDGE_DET_CTRL, lde_cfg_1, LEN_LDE_CFG1 );
    ctx->offset = LDE_CFG2_SUB;
    uwb_generic_write( ctx, UWB_REG_LEAD_EDGE_DET_CTRL, lde_cfg_2, LEN_LDE_CFG2 );
    ctx->offset = LDE_REPC_SUB;
    uwb_generic_write( ctx, UWB_REG_LEAD_EDGE_DET_CTRL, lde_repc, LEN_LDE_REPC );
    ctx->offset = UWB_SUB_NO;
    uwb_generic_write( ctx, UWB_REG_TX_POWER, tx_power, LEN_TX_POWER );
    ctx->offset = RF_RXCTRLH_SUB;
    uwb_generic_write( ctx, UWB_REG_RF_CFG, rf_rx_ctrl, LEN_RF_RXCTRLH );
    ctx->offset = RF_TXCTRL_SUB;
    uwb_generic_write( ctx, UWB_REG_RF_CFG, rf_tx_ctrl, LEN_RF_TXCTRL );
    ctx->offset = TC_PGDELAY_SUB;
    uwb_generic_write( ctx, UWB_REG_TX_CALIBRATION, tcpg_delay, LEN_TC_PGDELAY );
    ctx->offset = FS_PLLTUNE_SUB;
    uwb_generic_write( ctx, UWB_REG_FREQ_SYNTH_CTRL, fs_pll_cfg, LEN_FS_PLLTUNE );
    ctx->offset = FS_PLLCFG_SUB;
    uwb_generic_write( ctx, UWB_REG_FREQ_SYNTH_CTRL, fs_pll_tune, LEN_FS_PLLCFG );
    ctx->offset = FS_XTALT_SUB;
    uwb_generic_write( ctx, UWB_REG_FREQ_SYNTH_CTRL, fs_xtalt, LEN_FS_XTALT );
}

void uwb_dev_reset ( uwbtransceiver_t *ctx )
{
    uwb_set_rst_pin_status( ctx, 0 );
    Delay_100ms(  );
    uwb_set_rst_pin_status( ctx, 1 );
    Delay_100ms(  );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_value_to_array ( uint32_t value, uint8_t *array, uint8_t array_len )
{
    uint8_t array_cnt;

    for ( array_cnt = 0; array_cnt < array_len; array_cnt++ )
    {
        array[ array_cnt ] = ( value >> ( array_cnt * 8 ) ) & 0xFF;
    }
}

static void dev_agc_tune_1 ( uint8_t *agc_tune )
{
    if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
    {
        dev_value_to_array( 0x8870, agc_tune, LEN_AGC_TUNE1 );
    }
    else if ( UWB_PULSTE_FREQ_64MHZ == dev_cfg.pulse_freq )
    {
        dev_value_to_array( 0x889B, agc_tune, LEN_AGC_TUNE1 );
    }
}

static void dev_agc_tune_2 ( uint8_t *agc_tune )
{
    dev_value_to_array( 0x2502A907, agc_tune, LEN_AGC_TUNE2 );
}

static void dev_agc_tune_3 ( uint8_t *agc_tune )
{
    dev_value_to_array( 0x0035, agc_tune, LEN_AGC_TUNE3 );
}

static void dev_drx_tune_0b ( uint8_t *drx_tune )
{
    if ( UWB_DATA_RATE_110KBSPS == dev_cfg.data_rate )
    {
        dev_value_to_array( 0x0016, drx_tune, LEN_DRX_TUNE0b );
    }
    else if ( UWB_DATA_RATE_850KBSPS == dev_cfg.data_rate ) 
    {
        dev_value_to_array(  0x0006, drx_tune,LEN_DRX_TUNE0b );
    }
    else if ( UWB_DATA_RATE_6800KBSPS == dev_cfg.data_rate ) 
    {
        dev_value_to_array ( 0x0001, drx_tune, LEN_DRX_TUNE0b );
    }
}

static void dev_drx_tune_1a ( uint8_t *drx_tune )
{
    if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
    {
        dev_value_to_array( 0x0087, drx_tune, LEN_DRX_TUNE1a );
    }
    else if ( UWB_PULSTE_FREQ_64MHZ == dev_cfg.pulse_freq )
    {
        dev_value_to_array( 0x008D, drx_tune, LEN_DRX_TUNE1a );
    }
}

static void dev_drx_tune_1b ( uint8_t *drx_tune )
{
    if ( ( UWB_PREAMBLE_LEN_1536 == dev_cfg.preamble_len ) || 
         ( UWB_PREAMBLE_LEN_2048 == dev_cfg.preamble_len ) ||
         ( UWB_PREAMBLE_LEN_4096 == dev_cfg.preamble_len ) )
    {
        if ( UWB_DATA_RATE_110KBSPS == dev_cfg.data_rate ) 
        {
            dev_value_to_array( 0x0064, drx_tune, LEN_DRX_TUNE1b );
        }
    }
    else if ( UWB_PREAMBLE_LEN_64 == dev_cfg.preamble_len )
    {
        if ( ( UWB_DATA_RATE_850KBSPS == dev_cfg.data_rate ) || 
            ( UWB_DATA_RATE_6800KBSPS == dev_cfg.data_rate ) ) 
        {
            dev_value_to_array(  0x0020, drx_tune,LEN_DRX_TUNE1b );
        }
    }
    else
    {
        if ( UWB_DATA_RATE_6800KBSPS == dev_cfg.data_rate ) 
        {
            dev_value_to_array( 0x0010, drx_tune, LEN_DRX_TUNE1b );
        }
    }
}

static void dev_drx_tune_2 ( uint8_t *drx_tune )
{
    if ( UWB_PAC_SIZE_8 == dev_cfg.pac_size )
    {
        if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
        {
            dev_value_to_array( 0x311A002D, drx_tune, LEN_DRX_TUNE2 );
        }
        else if ( UWB_PULSTE_FREQ_64MHZ == dev_cfg.pulse_freq )
        {
            dev_value_to_array( 0x313B006B, drx_tune, LEN_DRX_TUNE2 );
        }
    }
    else if ( UWB_PAC_SIZE_16 == dev_cfg.pac_size )
    {
        if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
        {
            dev_value_to_array( 0x331A0052, drx_tune, LEN_DRX_TUNE2 );
        }
        else if ( UWB_PULSTE_FREQ_64MHZ == dev_cfg.pulse_freq )
        {
            dev_value_to_array( 0x333B00BE, drx_tune, LEN_DRX_TUNE2 );
        }
    }
    else if ( UWB_PAC_SIZE_32 == dev_cfg.pac_size )
    {
        if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
        {
            dev_value_to_array( 0x351A009A, drx_tune, LEN_DRX_TUNE2 );
        }
        else if ( UWB_PULSTE_FREQ_64MHZ == dev_cfg.pulse_freq )
        {
            dev_value_to_array( 0x353B015E, drx_tune, LEN_DRX_TUNE2 );
        }
    }
    else if ( UWB_PAC_SIZE_64 == dev_cfg.pac_size )
    {
        if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
        {
            dev_value_to_array( 0x371A011D, drx_tune, LEN_DRX_TUNE2 );
        }
        else if ( UWB_PULSTE_FREQ_64MHZ == dev_cfg.pulse_freq )
        {
            dev_value_to_array( 0x373B0296, drx_tune, LEN_DRX_TUNE2 );
        }
    }
}

static void dev_drx_tune_4h ( uint8_t *drx_tune )
{
    if ( UWB_PREAMBLE_LEN_64 == dev_cfg.preamble_len )
    {
        dev_value_to_array( 0x0010, drx_tune, LEN_DRX_TUNE4H );
    }
    else
    {
        dev_value_to_array( 0x0028, drx_tune, LEN_DRX_TUNE4H );
    }
}

static void dev_lde_cfg_1 ( uint8_t *lde_cfg )
{
    dev_value_to_array( 0xD, lde_cfg, LEN_LDE_CFG1 );
}

static void dev_lde_cfg_2 ( uint8_t *lde_cfg )
{
    if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
    {
        dev_value_to_array( 0x1607, lde_cfg, LEN_LDE_CFG2 );
    }
    else if ( UWB_PULSTE_FREQ_64MHZ == dev_cfg.pulse_freq )
    {
        dev_value_to_array( 0x0607, lde_cfg, LEN_LDE_CFG2 );
    }
}

static void dev_lde_repc_help ( uint8_t *lde_cfg , uint32_t r_110, uint32_t r_o )
{
    if ( UWB_DATA_RATE_110KBSPS == dev_cfg.data_rate )
    {
        dev_value_to_array( r_110, lde_cfg, LEN_LDE_REPC );
    }
    else
    {
        dev_value_to_array( r_o, lde_cfg, LEN_LDE_REPC );
    }
}

static void dev_lde_repc ( uint8_t *lde_cfg )
{
    if ( ( UWB_PREAMBLE_CODE_1 == dev_cfg.preamble_code ) || 
         ( UWB_PREAMBLE_CODE_2 == dev_cfg.preamble_code ) )
    {
        dev_lde_repc_help( lde_cfg, ( ( 0x5998 >> 3 ) & 0xFFFF ), 0x5998 );
    }
    else if ( ( UWB_PREAMBLE_CODE_3 == dev_cfg.preamble_code ) || 
              ( UWB_PREAMBLE_CODE_8 == dev_cfg.preamble_code ) )
    {
        dev_lde_repc_help( lde_cfg, ( ( 0x51EA >> 3 ) & 0xFFFF ), 0x51EA );
    }
    else if ( UWB_PREAMBLE_CODE_4 == dev_cfg.preamble_code )
    {
        dev_lde_repc_help( lde_cfg, ( ( 0x428E >> 3 ) & 0xFFFF ), 0x428E );
    }
    else if ( UWB_PREAMBLE_CODE_5 == dev_cfg.preamble_code )
    {
        dev_lde_repc_help( lde_cfg, ( ( 0x451E >> 3 ) & 0xFFFF ), 0x451E );
    }
    else if ( UWB_PREAMBLE_CODE_6 == dev_cfg.preamble_code )
    {
        dev_lde_repc_help( lde_cfg, ( ( 0x2E14 >> 3 ) & 0xFFFF ), 0x2E14 );
    }
    else if ( UWB_PREAMBLE_CODE_7 == dev_cfg.preamble_code )
    {
        dev_lde_repc_help( lde_cfg, ( ( 0x8000 >> 3 ) & 0xFFFF ), 0x8000 );
    }
    else if ( UWB_PREAMBLE_CODE_9 == dev_cfg.preamble_code )
    {
        dev_lde_repc_help( lde_cfg, ( ( 0x28F4 >> 3 ) & 0xFFFF ), 0x28F4 );
    }
    else if ( ( UWB_PREAMBLE_CODE_10 == dev_cfg.preamble_code ) || 
              ( UWB_PREAMBLE_CODE_17 == dev_cfg.preamble_code ) )
    {
        dev_lde_repc_help( lde_cfg, ( ( 0x3332 >> 3 ) & 0xFFFF ), 0x3332 );
    }
    else if ( UWB_PREAMBLE_CODE_11 == dev_cfg.preamble_code )
    {
        dev_lde_repc_help( lde_cfg, ( ( 0x3AE0 >> 3 ) & 0xFFFF ), 0x3AE0 );
    }
    else if ( UWB_PREAMBLE_CODE_12 == dev_cfg.preamble_code )
    {
        dev_lde_repc_help( lde_cfg, ( ( 0x3D70 >> 3 ) & 0xFFFF ), 0x3D70 );
    }
    else if ( ( UWB_PREAMBLE_CODE_18 == dev_cfg.preamble_code ) || 
              ( UWB_PREAMBLE_CODE_19 == dev_cfg.preamble_code ) )
    {
        dev_lde_repc_help( lde_cfg, ( ( 0x35C2 >> 3 ) & 0xFFFF ), 0x35C2 );
    }
    else if ( UWB_PREAMBLE_CODE_20 == dev_cfg.preamble_code ) 
    {
        dev_lde_repc_help( lde_cfg, ( ( 0x47AE >> 3 ) & 0xFFFF ), 0x47AE );
    }
}

static void dev_tx_power_help ( uint8_t *tx_power , uint32_t sp, uint32_t nsp )
{
    if ( dev_cfg.smart_power )
    {
        dev_value_to_array( sp, tx_power, LEN_TX_POWER );
    }
    else
    {
        dev_value_to_array( nsp, tx_power, LEN_TX_POWER );
    }
}

static void dev_tx_power ( uint8_t *tx_power )
{
    if ( ( UWB_CHANNEL_1 == dev_cfg.channel ) || 
         ( UWB_CHANNEL_2 == dev_cfg.channel ) )
    {
        if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
        {
            dev_tx_power_help( tx_power, 0x15355575, 0x75757575 );
        }
        else if ( UWB_PULSTE_FREQ_64MHZ == dev_cfg.pulse_freq )
        {
            dev_tx_power_help( tx_power, 0x07274767, 0x67676767 );
        }
    }
    else if ( UWB_CHANNEL_3 == dev_cfg.channel )
    {
        if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
        {
            dev_tx_power_help( tx_power, 0x0F2F4F6F, 0x6F6F6F6F );
        }
        else if ( UWB_PULSTE_FREQ_64MHZ == dev_cfg.pulse_freq )
        {
            dev_tx_power_help( tx_power, 0x2B4B6B8B, 0x8B8B8B8B );
        }
    }
    else if ( UWB_CHANNEL_4 == dev_cfg.channel )
    {
        if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
        {
            dev_tx_power_help( tx_power, 0x1F1F3F5F, 0x5F5F5F5F );
        }
        else if ( UWB_PULSTE_FREQ_64MHZ == dev_cfg.pulse_freq )
        {
            dev_tx_power_help( tx_power, 0x3A5A7A9A, 0x9A9A9A9A );
        }
    }
    else if ( UWB_CHANNEL_5 == dev_cfg.channel )
    {
        if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq )
        {
            dev_tx_power_help( tx_power, 0x0E082848, 0x48484848 );
        }
        else if ( UWB_PULSTE_FREQ_64MHZ == dev_cfg.pulse_freq )
        {
            dev_tx_power_help( tx_power, 0x25456585, 0x85858585 );
        }
    }
    else if ( UWB_CHANNEL_7 == dev_cfg.channel )
    {
        if ( UWB_PULSTE_FREQ_16MHZ == dev_cfg.pulse_freq  )
        {
            dev_tx_power_help( tx_power, 0x32527292, 0x92929292 );
        }
        else if ( UWB_PULSTE_FREQ_64MHZ == dev_cfg.pulse_freq  )
        {
            dev_tx_power_help( tx_power, 0x5171B1D1, 0xD1D1D1D1 );
        }
    }
}

static void dev_rf_rx_ctrl ( uint8_t *rf_ctrl )
{
    if ( ( UWB_CHANNEL_4 != dev_cfg.channel ) && 
        ( UWB_CHANNEL_7 != dev_cfg.channel ) )
    {
        dev_value_to_array( 0xD8, rf_ctrl, LEN_RF_RXCTRLH );
    }
    else
    {
        dev_value_to_array( 0xBC, rf_ctrl, LEN_RF_RXCTRLH );
    }
}

static void dev_rf_tx_ctrl ( uint8_t *rf_ctrl )
{
    if ( UWB_CHANNEL_1 == dev_cfg.channel )
    {
        dev_value_to_array(0x00005C40,  rf_ctrl, LEN_RF_TXCTRL );
    }
    else if ( UWB_CHANNEL_2 == dev_cfg.channel )
    {
        dev_value_to_array( 0x00045CA0, rf_ctrl, LEN_RF_TXCTRL );
    }
    else if ( UWB_CHANNEL_3 == dev_cfg.channel )
    {
        dev_value_to_array( 0x00086CC0, rf_ctrl, LEN_RF_TXCTRL );
    }
    else if ( UWB_CHANNEL_4 == dev_cfg.channel )
    {
        dev_value_to_array( 0x00045C80, rf_ctrl, LEN_RF_TXCTRL );
    }
    else if ( UWB_CHANNEL_5 == dev_cfg.channel )
    {
        dev_value_to_array( 0x001E3FE0, rf_ctrl, LEN_RF_TXCTRL );
    }
    else if ( UWB_CHANNEL_7 == dev_cfg.channel )
    {
        dev_value_to_array( 0x001E7DE0, rf_ctrl, LEN_RF_TXCTRL );
    }
}

static void dev_tcpg_delay ( uint8_t *tcpg_delay )
{
    if ( UWB_CHANNEL_1 == dev_cfg.channel )
    {
        dev_value_to_array( 0xC9, tcpg_delay, LEN_TC_PGDELAY );
    }
    else if ( UWB_CHANNEL_2 == dev_cfg.channel )
    {
        dev_value_to_array( 0xC2, tcpg_delay, LEN_TC_PGDELAY );
    }
    else if ( UWB_CHANNEL_3 == dev_cfg.channel )
    {
        dev_value_to_array( 0xC5, tcpg_delay, LEN_TC_PGDELAY );
    }
    else if ( UWB_CHANNEL_4 == dev_cfg.channel )
    {
        dev_value_to_array( 0x95, tcpg_delay, LEN_TC_PGDELAY );
    }
    else if (UWB_CHANNEL_5 == dev_cfg.channel )
    {
        dev_value_to_array( 0xC0, tcpg_delay, LEN_TC_PGDELAY );
    }
    else if ( UWB_CHANNEL_7 == dev_cfg.channel )
    {
        dev_value_to_array( 0x93, tcpg_delay, LEN_TC_PGDELAY );
    }
}

static void dev_fs_pll_cfg ( uint8_t *fs )
{
    if ( UWB_CHANNEL_1 == dev_cfg.channel )
    {
        dev_value_to_array( 0x09000407, fs, LEN_FS_PLLCFG );
    }
    else if ( ( UWB_CHANNEL_2 == dev_cfg.channel ) || 
              ( UWB_CHANNEL_4 == dev_cfg.channel ) )
    {
        dev_value_to_array( 0x08400508, fs, LEN_FS_PLLCFG );
    }
    else if ( UWB_CHANNEL_3 == dev_cfg.channel )
    {
        dev_value_to_array( 0x08401009, fs, LEN_FS_PLLCFG );
    }
    else if ( ( UWB_CHANNEL_5 == dev_cfg.channel ) || 
             ( UWB_CHANNEL_7 == dev_cfg.channel ) )
    {
        dev_value_to_array( 0x0800041D, fs, LEN_FS_PLLCFG );
    }
}

static void dev_fs_pll_tune ( uint8_t *fs )
{
    if ( UWB_CHANNEL_1 == dev_cfg.channel )
    {
        dev_value_to_array( 0x1E, fs, LEN_FS_PLLTUNE );
    }
    else if ( ( UWB_CHANNEL_2 == dev_cfg.channel ) || 
              ( UWB_CHANNEL_4 == dev_cfg.channel ) )
    {
        dev_value_to_array( 0x26, fs, LEN_FS_PLLTUNE );
    }
    else if ( UWB_CHANNEL_3 == dev_cfg.channel )
    {
        dev_value_to_array( 0x56, fs, LEN_FS_PLLTUNE );
    }
    else if ( ( UWB_CHANNEL_5 == dev_cfg.channel ) || 
              ( UWB_CHANNEL_7 == dev_cfg.channel ) )
    {
        dev_value_to_array( 0xBE, fs, LEN_FS_PLLTUNE );
    }
}

static void dev_fs_xtalt ( uwbtransceiver_t *ctx, uint8_t *fs )
{
    uint8_t otp_data[ 4 ];

    uwb_read_otp( ctx, 0x01E, otp_data );

    if ( 0 == otp_data[ 0 ] )
    {
        dev_value_to_array( ( ( 0x10 & 0x1F ) | 0x60 ), fs, LEN_FS_XTALT );
    }
    else
    {
        dev_value_to_array( ( ( otp_data[ 0 ] & 0x1F ) | 0x60 ), fs, LEN_FS_XTALT );
    }
}

// ------------------------------------------------------------------------- END

