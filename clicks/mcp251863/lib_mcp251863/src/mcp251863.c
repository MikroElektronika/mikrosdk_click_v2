/****************************************************************************
** Copyright (C) 2020 MikroElektronika rx_data.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining address copy
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
 * @file mcp251863.c
 * @brief MCP251863 Click Driver.
 */

#include "mcp251863.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

// ------------------------------------------------------------------ CONSTANTS

static const uint8_t bit_reverse_table256[ 256 ] =
{
    0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0,
    0x30, 0xB0, 0x70, 0xF0, 0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8,
    0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 0x04, 0x84, 0x44, 0xC4,
    0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
    0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC,
    0x3C, 0xBC, 0x7C, 0xFC, 0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2,
    0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, 0x0A, 0x8A, 0x4A, 0xCA,
    0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
    0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6,
    0x36, 0xB6, 0x76, 0xF6, 0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE,
    0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE, 0x01, 0x81, 0x41, 0xC1,
    0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
    0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9,
    0x39, 0xB9, 0x79, 0xF9, 0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5,
    0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5, 0x0D, 0x8D, 0x4D, 0xCD,
    0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
    0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3,
    0x33, 0xB3, 0x73, 0xF3, 0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB,
    0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB, 0x07, 0x87, 0x47, 0xC7,
    0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
    0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF,
    0x3F, 0xBF, 0x7F, 0xFF
};

static const uint16_t crc16table[ 256 ] = 
{
    0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
    0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
    0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
    0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
    0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
    0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
    0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
    0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
    0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
    0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
    0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
    0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
    0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
    0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
    0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
    0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
    0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
    0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
    0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
    0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
    0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
    0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
    0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
    0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
    0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
    0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
    0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
    0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
    0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
    0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
    0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
    0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202
};

static uint32_t can_control_reset_values[ ] =
{
    // Address 0x000 to 0x00C 
#ifdef CAN_TXQUEUE_IMPLEMENTED
    0x04980760, 0x003E0F0F, 0x000E0303, 0x00021000,
#else
    0x04880760, 0x003E0F0F, 0x000E0303, 0x00021000,
#endif
    0x00000000, 0x00000000, 0x40400040, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00200000, 0x00000000, 0x00000000,
    0x00000400, 0x00000000, 0x00000000, 0x00000000
};

static uint32_t can_fifo_reset_values[ ] =
{
    0x00600400, 0x00000000, 0x00000000
};

static uint32_t can_filter_control_reset_value = 0x00000000;

static uint32_t can_filter_object_reset_values[ ] =
{
    0x00000000, 0x00000000
};

#ifdef MCP251863

static uint32_t mcp2518_control_reset_values[ ] = 
{
    0x00000460, 0x00000003, 0x00000000, 0x00000000, 0x00000000
};

#endif

// ------------------------------------------------------------------ VARIABLES

// SPI Transmit buffer
static uint8_t spi_transmit_buffer[ MCP251863_SPI_DEFAULT_BUFFER_LENGTH ];

// SPI Receive buffer
static uint8_t spi_receive_buffer[ MCP251863_SPI_DEFAULT_BUFFER_LENGTH ];

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mcp251863_cfg_setup ( mcp251863_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->stby = HAL_PIN_NC;
    cfg->clk  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t mcp251863_init ( mcp251863_t *ctx, mcp251863_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->stby, cfg->stby );

    digital_in_init( &ctx->clk, cfg->clk );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    ctx->glb_data.rx_flags = 0;
    ctx->glb_data.tx_id = MCP251863_TX_RESPONSE_ID;
    ctx->glb_data.selected_bit_time = MCP251863_500K_2M;

    return SPI_MASTER_SUCCESS;
}

err_t mcp251863_default_cfg ( mcp251863_t *ctx ) 
{
    err_t error_flag = MCP251863_OK;
    
    uint8_t osc_byte;
    mcp251863_config_t config_obj;

    config_obj.iso_crc_enable = MCP251863_ISO_CRC;
    config_obj.store_in_tef = 0;
    config_obj.tx_fifo_size = 8;
    config_obj.tx_pay_load_size = MCP251863_PLSIZE_8;
    config_obj.tx_priority = 1;
    config_obj.rx_fifo_size = 8;
    config_obj.rx_pay_load_size = MCP251863_PLSIZE_8;
    config_obj.standard_id = 0;
    config_obj.extended_id = 0;
    config_obj.fd_frame = 1;
    config_obj.switch_bit_rate = 1;
    config_obj.ide = 0;
    config_obj.remote_frame_req = 0;
    config_obj.seq = 1;

    // Reset device
    mcp251863_reset( ctx );
    Delay_100ms( );
    Delay_100ms( );
    
    mcp251863_operation_mode_select( ctx, MCP251863_CONFIG_MODE );
    Delay_100ms( );

    // Enable ECC and initialize RAM
    mcp251863_ecc_enable( ctx);
    mcp251863_ram_init( ctx, 0xFF );

    // Configure device
    mcp251863_configure_object_reset( &ctx->glb_data.config );
    ctx->glb_data.config.iso_crc_enable = config_obj.iso_crc_enable;
    ctx->glb_data.config.store_in_tef = config_obj.store_in_tef;
    mcp251863_configure( ctx, &ctx->glb_data.config );

    // Setup TX FIFO
    mcp251863_transmit_channel_configure_object_reset( &ctx->glb_data.tx_config );
    ctx->glb_data.tx_config.fifo_size = config_obj.tx_fifo_size;
    ctx->glb_data.tx_config.pay_load_size = config_obj.tx_pay_load_size;
    ctx->glb_data.tx_config.tx_priority = config_obj.tx_priority;
    mcp251863_transmit_channel_configure( ctx, MCP251863_FIFO_CH2, &ctx->glb_data.tx_config );

    // Setup RX FIFO
    mcp251863_receive_channel_configure_object_reset( &ctx->glb_data.rx_config );
    ctx->glb_data.rx_config.fifo_size = config_obj.rx_fifo_size;
    ctx->glb_data.rx_config.pay_load_size = config_obj.rx_pay_load_size;
    mcp251863_receive_channel_configure( ctx, MCP251863_FIFO_CH1, &ctx->glb_data.rx_config );

    // Setup RX Filter
    ctx->glb_data.f_obj.word = 0;
    ctx->glb_data.f_obj.bf.sid = 0xDA;
    ctx->glb_data.f_obj.bf.exide = 0;
    ctx->glb_data.f_obj.bf.eid = 0x00;
    mcp251863_filter_object_configure( ctx, MCP251863_FILT0, &ctx->glb_data.f_obj.bf );

    // Setup RX Mask
    ctx->glb_data.m_obj.word = 0;
    ctx->glb_data.m_obj.bf.msid = 0x0;
    ctx->glb_data.m_obj.bf.mide = 1; // Only allow standard IDs
    ctx->glb_data.m_obj.bf.meid = 0x0;
    mcp251863_filter_mask_configure( ctx, MCP251863_FILT0, &ctx->glb_data.m_obj.bf );

    // Link FIFO and Filter
    mcp251863_filter_to_fifo_link( ctx, MCP251863_FILT0, MCP251863_FIFO_CH1, true);

    // Setup Bit Time
    mcp251863_bit_time_configure( ctx, ctx->glb_data.selected_bit_time, MCP251863_SYSCLK_40M );

    // Initialize ID and Control bits
    ctx->glb_data.tx_obj.word[ 0 ] = 0;
    ctx->glb_data.tx_obj.word[ 1 ] = 0;

    ctx->glb_data.tx_obj.bf.id.sid = config_obj.standard_id; // Standard or Base ID
    ctx->glb_data.tx_obj.bf.id.eid = config_obj.extended_id;

    ctx->glb_data.tx_obj.bf.ctrl.fdf = config_obj.fd_frame; // CAN FD frame
    ctx->glb_data.tx_obj.bf.ctrl.brs = config_obj.switch_bit_rate; // Switch bit rate
    ctx->glb_data.tx_obj.bf.ctrl.ide = config_obj.ide; // Standard frame
    ctx->glb_data.tx_obj.bf.ctrl.rtr = config_obj.remote_frame_req; // Not address remote frame request
    // Sequence: doesn't get transmitted, but will be stored in TEF
    ctx->glb_data.tx_obj.bf.ctrl.seq = config_obj.seq;

    // Setup Transmit and Receive Interrupts
    mcp251863_gpio_mode_configure( ctx, MCP251863_PINMODE_INT, MCP251863_PINMODE_INT );
    mcp251863_transmit_channel_event_enable( ctx, MCP251863_FIFO_CH2, MCP251863_TX_FIFO_NOT_FULL_EVENT );
    mcp251863_receive_channel_event_enable( ctx, MCP251863_FIFO_CH1, MCP251863_RX_FIFO_NOT_EMPTY_EVENT );
    mcp251863_module_event_enable( ctx, MCP251863_TX_EVENT | MCP251863_RX_EVENT );
    
    mcp251863_read_byte( ctx, MCP251863_REG_CIINT + 3, &osc_byte );
    osc_byte |= MCP251863_WAKEUP_INTERR_EN;
    mcp251863_write_byte( ctx, MCP251863_REG_CIINT + 3, osc_byte );
    mcp251863_read_byte( ctx, MCP251863_REG_OSC, &osc_byte );
    osc_byte &= 0xF3;
    mcp251863_write_byte( ctx, MCP251863_REG_OSC, osc_byte );
    Delay_100ms( );
    Delay_100ms( );

    // Select Normal Mode
    mcp251863_operation_mode_select( ctx, MCP251863_NORMAL_MODE );
    Delay_1sec( );

    return error_flag;
}

err_t mcp251863_generic_write ( mcp251863_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t mcp251863_generic_read ( mcp251863_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t mcp251863_transmit_message ( mcp251863_t *ctx, uint8_t *data_in, uint16_t data_len )
{
    uint8_t n;
    uint8_t attempts = MCP251863_MAX_TXQUEUE_ATTEMPTS;

    ctx->glb_data.tx_obj.bf.ctrl.dlc = data_len;

    // Check if FIFO is not full
    do
    {
       mcp251863_transmit_channel_event_get( ctx, MCP251863_FIFO_CH2, &ctx->glb_data.tx_flags );

        if ( attempts == 0 )
        {
            mcp251863_error_count_state_get( ctx, &ctx->glb_data.tec, &ctx->glb_data.rec, &ctx->glb_data.error_flags );
            return MCP251863_ERROR;
        }
        attempts--;
    }
    while ( ! ( ctx->glb_data.tx_flags & MCP251863_TX_FIFO_NOT_FULL_EVENT ) );

    // Load message and transmit
    n = mcp251863_dlc_to_data_bytes( ctx->glb_data.tx_obj.bf.ctrl.dlc );
    ctx->func_data.txd = data_in;
    ctx->func_data.txd_num_bytes = n;

    mcp251863_transmit_channel_load( ctx, MCP251863_FIFO_CH2, &ctx->glb_data.tx_obj, true );
    return MCP251863_OK;
}

err_t mcp251863_receive_message ( mcp251863_t *ctx, uint8_t *data_out, uint16_t *data_len )
{
    uint16_t rcv_length;

    // Check if FIFO is not empty
    mcp251863_receive_channel_event_get( ctx, MCP251863_FIFO_CH1, &ctx->glb_data.rx_flags );

    if ( ctx->glb_data.rx_flags & MCP251863_RX_FIFO_NOT_EMPTY_EVENT )
    {
        ctx->func_data.rxd = data_out;
        ctx->func_data.n_bytes = MCP251863_MAX_DATA_BYTES;
        mcp251863_receive_message_get( ctx, MCP251863_FIFO_CH1, &ctx->glb_data.rx_obj );
    }
    else
    {
        return MCP251863_ERROR;
    }

    rcv_length = ctx->glb_data.rx_obj.bf.ctrl.dlc;
    data_out = ctx->func_data.rxd;
    *data_len = rcv_length;
    return MCP251863_OK;
}

err_t mcp251863_reset ( mcp251863_t *ctx )
{
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( MCP251863_INS_RESET << 4 );
    spi_transmit_buffer[ 1 ] = 0;

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write( &ctx->spi, spi_transmit_buffer, 2);
    spi_master_deselect_device( ctx->chip_select );  

    return error_flag;
}

err_t mcp251863_read_byte ( mcp251863_t *ctx, uint16_t address, uint8_t *data_out )
{
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP251863_INS_READ << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write_then_read( &ctx->spi, spi_transmit_buffer, 2, spi_receive_buffer, 1 );
    spi_master_deselect_device( ctx->chip_select );  
    
    *data_out = spi_receive_buffer[ 0 ];

    return error_flag;
}

err_t mcp251863_write_byte ( mcp251863_t *ctx, uint16_t address, uint8_t data_in )
{
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP251863_INS_WRITE << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );
    spi_transmit_buffer[ 2 ] = data_in;

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write( &ctx->spi, spi_transmit_buffer, 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t mcp251863_read_word ( mcp251863_t *ctx, uint16_t address, uint32_t *data_out )
{
    uint32_t temp;
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP251863_INS_READ << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write_then_read( &ctx->spi, spi_transmit_buffer, 2, spi_receive_buffer, 4 );
    spi_master_deselect_device( ctx->chip_select );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return error_flag;
    }

    *data_out = 0;
    for ( uint8_t cnt = 0; cnt < 4; cnt++ ) 
    {
        temp = ( uint32_t ) spi_receive_buffer[ cnt ];
        *data_out += temp << ( cnt * 8 );
    }

    return error_flag;
}

err_t mcp251863_write_word ( mcp251863_t *ctx, uint16_t address, uint32_t data_in )
{
    uint8_t cnt;
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP251863_INS_WRITE << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    for ( cnt = 0; cnt < 4; cnt++ ) 
    {
        spi_transmit_buffer[ cnt + 2 ] = ( uint8_t ) ( ( data_in >> ( cnt * 8 ) ) & 0xFF );
    }

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write( &ctx->spi, spi_transmit_buffer, 6 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t mcp251863_read_half_word ( mcp251863_t *ctx, uint16_t address, uint16_t *data_out )
{
    uint32_t temp;
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP251863_INS_READ << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write_then_read( &ctx->spi, spi_transmit_buffer, 2, spi_receive_buffer, 2 );
    spi_master_deselect_device( ctx->chip_select );

    if ( error_flag == MCP251863_ERROR ) 
    {
        return error_flag;
    }

    *data_out = 0;
    for ( uint8_t cnt = 0; cnt < 2; cnt++ ) 
    {
        temp = ( uint32_t ) spi_receive_buffer[ cnt ];
        *data_out += temp << ( cnt * 8 );
    }

    return error_flag;
}

err_t mcp251863_write_half_word ( mcp251863_t *ctx, uint16_t address, uint16_t data_in )
{
    uint8_t cnt;
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP251863_INS_WRITE << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    for ( cnt = 0; cnt < 2; cnt++ ) 
    {
        spi_transmit_buffer[ cnt + 2 ] = ( uint8_t ) ( ( data_in >> ( cnt * 8 ) ) & 0xFF );
    }

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write( &ctx->spi, spi_transmit_buffer, 4 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t mcp251863_write_byte_safe ( mcp251863_t *ctx, uint16_t address, uint8_t data_in )
{
    uint16_t crc_result = 0;
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP251863_INS_WRITE_SAFE << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );
    spi_transmit_buffer[ 2 ] = data_in;

    crc_result = mcp251863_calculate_crc16( spi_transmit_buffer, 3 );
    spi_transmit_buffer[ 3 ] = ( crc_result >> 8 ) & 0xFF;
    spi_transmit_buffer[ 4 ] = crc_result & 0xFF;

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write( &ctx->spi, spi_transmit_buffer, 5 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t mcp251863_write_word_safe ( mcp251863_t *ctx, uint16_t address, uint32_t data_in )
{
    uint8_t cnt;
    uint16_t crc_result = 0;
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP251863_INS_WRITE_SAFE << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    for ( cnt = 0; cnt < 4; cnt++ ) 
    {
        spi_transmit_buffer[ cnt + 2 ] = ( uint8_t ) ( ( data_in >> ( cnt * 8 ) ) & 0xFF );
    }

    crc_result = mcp251863_calculate_crc16( spi_transmit_buffer, 6 );
    spi_transmit_buffer[6] = ( crc_result >> 8 ) & 0xFF;
    spi_transmit_buffer[7] = crc_result & 0xFF;

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write( &ctx->spi, spi_transmit_buffer, 8 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t mcp251863_read_byte_array ( mcp251863_t *ctx, uint16_t address, 
                                   uint8_t *data_out, uint16_t n_bytes )
{
    uint16_t cnt;
    uint16_t spi_transfer_size = n_bytes + 2;
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP251863_INS_READ << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    for ( cnt = 2; cnt < spi_transfer_size; cnt++ ) 
    {
        spi_transmit_buffer[ cnt ] = 0;
    }

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write_then_read( &ctx->spi, spi_transmit_buffer, 2, spi_receive_buffer, n_bytes );
    spi_master_deselect_device( ctx->chip_select );

    for ( cnt = 0; cnt < n_bytes; cnt++ ) 
    {
        data_out[ cnt ] = spi_receive_buffer[ cnt ];
    }

    return error_flag;
}

err_t mcp251863_read_byte_array_with_crc ( mcp251863_t *ctx, bool from_ram, bool *crc_is_correct )
{
    uint8_t cnt;
    uint16_t crc_from_spi_slave = 0;
    uint16_t crc_at_controller = 0;
    uint16_t spi_transfer_size = ctx->func_data.n_bytes + 5; 
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP251863_INS_READ_CRC << 4 ) + ( ( ctx->func_data.address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( ctx->func_data.address & 0xFF );
    if ( from_ram ) 
    {
        spi_transmit_buffer[ 2 ] = ctx->func_data.n_bytes >> 2;
    } 
    else 
    {
        spi_transmit_buffer[ 2 ] = ctx->func_data.n_bytes;
    }

    for ( cnt = 3; cnt < spi_transfer_size; cnt++ ) 
    {
        spi_transmit_buffer[ cnt ] = 0;
    }

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write_then_read( &ctx->spi, spi_transmit_buffer, 3, spi_receive_buffer, ctx->func_data.n_bytes );
    spi_master_deselect_device( ctx->chip_select );

    if ( error_flag == MCP251863_ERROR ) 
    {
        return error_flag;
    }

    crc_from_spi_slave = ( uint16_t ) ( spi_receive_buffer[ ctx->func_data.n_bytes - 2 ] << 8 ) + 
                         ( uint16_t ) ( spi_receive_buffer[ ctx->func_data.n_bytes - 1 ] );

    spi_receive_buffer[ 0 ] = spi_transmit_buffer[ 0 ];
    spi_receive_buffer[ 1 ] = spi_transmit_buffer[ 1 ];
    spi_receive_buffer[ 2 ] = spi_transmit_buffer[ 2 ];
    crc_at_controller = mcp251863_calculate_crc16( spi_receive_buffer, ctx->func_data.n_bytes + 3 );

    if ( crc_from_spi_slave == crc_at_controller ) 
    {
        *crc_is_correct = true;
    } 
    else 
    {
        *crc_is_correct = false;
    }

    for ( cnt = 0; cnt < ctx->func_data.n_bytes; cnt++ ) 
    {
        ctx->func_data.rxd[ cnt ] = spi_receive_buffer[ cnt + 3 ];
    }

    return error_flag;
}

err_t mcp251863_write_byte_array ( mcp251863_t *ctx, uint16_t address, uint8_t *data_in, uint16_t n_bytes )
{
    uint16_t cnt;
    uint16_t spi_transfer_size = n_bytes + 2;
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP251863_INS_WRITE << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    for ( cnt = 2; cnt < spi_transfer_size; cnt++ ) 
    {
        spi_transmit_buffer[ cnt ] = data_in[ cnt - 2 ];
    }

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write( &ctx->spi, spi_transmit_buffer, spi_transfer_size );
    spi_master_deselect_device( ctx->chip_select );
    

    return error_flag;
}

err_t mcp251863_write_byte_array_with_crc ( mcp251863_t *ctx, bool from_ram )
{
    uint16_t cnt;
    uint16_t crc_result = 0;
    uint16_t spi_transfer_size = ctx->func_data.n_bytes + 5;
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP251863_INS_WRITE_CRC << 4 ) + 
                                           ( ( ctx->func_data.address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( ctx->func_data.address & 0xFF );
    if ( from_ram ) 
    {
        spi_transmit_buffer[ 2 ] = ctx->func_data.n_bytes >> 2;
    } 
    else 
    {
        spi_transmit_buffer[ 2 ] = ctx->func_data.n_bytes;
    }

    for ( cnt = 0; cnt < ctx->func_data.n_bytes; cnt++ ) 
    {
        spi_transmit_buffer[ cnt + 3 ] = ctx->func_data.txd[ cnt ];
    }

    crc_result = mcp251863_calculate_crc16( spi_transmit_buffer, spi_transfer_size - 2 ) ; 
    spi_transmit_buffer[ spi_transfer_size - 2 ]  = ( uint8_t ) ( ( crc_result >> 8 ) & 0xFF );
    spi_transmit_buffer[ spi_transfer_size - 1 ]  = ( uint8_t ) ( crc_result & 0xFF );

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write( &ctx->spi, spi_transmit_buffer, spi_transfer_size );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t mcp251863_read_word_array ( mcp251863_t *ctx, uint16_t address, 
                                   uint32_t *data_out, uint16_t n_words )
{
    uint16_t cnt, j, n;
    mcp251863_reg_t w;
    uint16_t spi_transfer_size = n_words * 4;
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( MCP251863_INS_READ << 4 ) + ( ( address >> 8 ) & 0xF );
    spi_transmit_buffer[ 1 ] = address & 0xFF;

    for ( cnt = 2; cnt < spi_transfer_size; cnt++ ) 
    {
        spi_transmit_buffer[ cnt ] = 0;
    }

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write_then_read( &ctx->spi, spi_transmit_buffer, 2, spi_receive_buffer, spi_transfer_size );
    spi_master_deselect_device( ctx->chip_select );

    if ( error_flag == MCP251863_ERROR ) 
    {
        return error_flag;
    }

    n = 0;
    for ( cnt = 0; cnt < n_words; cnt++ ) 
    {
        w.word = 0;
        for ( j = 0; j < 4; j++, n++ ) 
        {
            w.byte[ j ] = spi_receive_buffer[ n ];
        }
        data_out[ cnt ] = w.word;
    }

    return error_flag;
}

err_t mcp251863_write_word_array ( mcp251863_t *ctx, uint16_t address,
                                    uint32_t *data_in, uint16_t n_words )
{
    uint16_t cnt, j, n;
    mcp251863_reg_t w;
    uint16_t spi_transfer_size = n_words * 4 + 2;
    err_t error_flag;

    spi_transmit_buffer[ 0 ] = ( MCP251863_INS_WRITE << 4 ) + ( ( address >> 8 ) & 0xF );
    spi_transmit_buffer[ 1 ] = address & 0xFF;

    n = 2;
    for ( cnt = 0; cnt < n_words; cnt++ ) 
    {
        w.word = data_in[ cnt ];
        for ( j = 0; j < 4; j++, n++ ) 
        {
            spi_transmit_buffer[ n ] = w.byte[ j ];
        }
    }

    spi_master_select_device( ctx->chip_select );  
    error_flag = spi_master_write( &ctx->spi, spi_transmit_buffer, spi_transfer_size );
    spi_master_deselect_device( ctx->chip_select );
    

    return error_flag;
}

err_t mcp251863_configure ( mcp251863_t *ctx, mcp251863_can_cfg_t *config )
{
    mcp251863_ctl_t ci_Con;
    err_t error_flag;

    ci_Con.word = can_control_reset_values[ MCP251863_REG_CICON / 4 ];

    ci_Con.bf.d_net_filter_count = config->d_net_filter_count;
    ci_Con.bf.iso_crc_enable = config->iso_crc_enable;
    ci_Con.bf.protocol_exception_event_disable = config->protocol_expection_event_disable;
    ci_Con.bf.wake_up_filter_enable = config->wake_up_filter_enable;
    ci_Con.bf.wake_up_filter_time = config->wake_up_filter_time;
    ci_Con.bf.bit_rate_switch_disable = config->bit_rate_switch_disable;
    ci_Con.bf.restrict_re_tx_attempts = config->restrict_re_tx_attempts;
    ci_Con.bf.esi_in_gateway_mode = config->esi_in_gateway_mode;
    ci_Con.bf.system_error_to_listen_only = config->system_error_to_listen_only;
    ci_Con.bf.store_in_tef = config->store_in_tef;
    ci_Con.bf.txq_enable = config->txq_enable;
    ci_Con.bf.tx_band_width_sharing = config->tx_band_width_sharing;

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CICON, ci_Con.word);

    return error_flag;
}

void mcp251863_configure_object_reset ( mcp251863_can_cfg_t *config )
{
    mcp251863_ctl_t ci_Con;
    ci_Con.word = can_control_reset_values[ MCP251863_REG_CICON / 4 ];

    config->d_net_filter_count = ci_Con.bf.d_net_filter_count;
    config->iso_crc_enable = ci_Con.bf.iso_crc_enable;
    config->protocol_expection_event_disable = ci_Con.bf.protocol_exception_event_disable;
    config->wake_up_filter_enable = ci_Con.bf.wake_up_filter_enable;
    config->wake_up_filter_time = ci_Con.bf.wake_up_filter_time;
    config->bit_rate_switch_disable = ci_Con.bf.bit_rate_switch_disable;
    config->restrict_re_tx_attempts = ci_Con.bf.restrict_re_tx_attempts;
    config->esi_in_gateway_mode = ci_Con.bf.esi_in_gateway_mode;
    config->system_error_to_listen_only = ci_Con.bf.system_error_to_listen_only;
    config->store_in_tef = ci_Con.bf.store_in_tef;
    config->txq_enable = ci_Con.bf.txq_enable;
    config->tx_band_width_sharing = ci_Con.bf.tx_band_width_sharing;
}

err_t mcp251863_operation_mode_select ( mcp251863_t *ctx, uint8_t op_mode )
{
    uint8_t rx_data = 0;
    err_t error_flag;

    error_flag = mcp251863_read_byte( ctx, MCP251863_REG_CICON + 3, &rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    rx_data &= ~0x07;
    rx_data |= op_mode;

    error_flag = mcp251863_write_byte ( ctx, MCP251863_REG_CICON + 3, rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_operation_mode_get ( mcp251863_t *ctx )
{
    uint8_t rx_data = 0;
    uint8_t mode = MCP251863_INVALID_MODE;
    err_t error_flag;

    error_flag = mcp251863_read_byte( ctx, MCP251863_REG_CICON + 2, &rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return MCP251863_INVALID_MODE;
    }

    rx_data = ( rx_data >> 5 ) & 0x7;

    switch ( rx_data ) 
    {
        case MCP251863_NORMAL_MODE:
        {
            mode = MCP251863_NORMAL_MODE;
            break;
        }
        case MCP251863_SLEEP_MODE:
        {
            mode = MCP251863_SLEEP_MODE;
            break;
        }
        case MCP251863_INT_LOOP_MODE:
        {
            mode = MCP251863_INT_LOOP_MODE;
            break;
        }
        case MCP251863_EXT_LOOP_MODE:
        {
            mode = MCP251863_EXT_LOOP_MODE;
            break;
        }
        case MCP251863_LISTEN_ONLY_MODE:
        {
            mode = MCP251863_LISTEN_ONLY_MODE;
            break;
        }
        case MCP251863_CONFIG_MODE:
        {
            mode = MCP251863_CONFIG_MODE;
            break;
        }
        case MCP251863_CLASSIC_MODE:
        {
            mode = MCP251863_CLASSIC_MODE;
            break;
        }
        case MCP251863_RESTRICT_MODE:
        {
            mode = MCP251863_RESTRICT_MODE;
            break;
        }
        default:
        {
            mode = MCP251863_INVALID_MODE;
            break;
        }
    }

    return mode;
}

err_t mcp251863_transmit_channel_configure ( mcp251863_t *ctx, uint8_t channel, mcp251863_tx_fifo_cfg_t *config )
{
    err_t error_flag;
    uint16_t address = 0;

    mcp251863_fifo_ctl_t ci_fifo_con;
    ci_fifo_con.word = can_control_reset_values[ MCP251863_REG_CIFIFOCON  / 4 ];
    ci_fifo_con.tx_bf.tx_enable = 1;
    ci_fifo_con.tx_bf.fifo_size = config->fifo_size;
    ci_fifo_con.tx_bf.pay_load_size = config->pay_load_size;
    ci_fifo_con.tx_bf.tx_attempts = config->tx_attempts;
    ci_fifo_con.tx_bf.tx_priority = config->tx_priority;
    ci_fifo_con.tx_bf.rtr_enable = config->rtr_enable;

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET );

    error_flag = mcp251863_write_word( ctx, address, ci_fifo_con.word );

    return error_flag;
}

void mcp251863_transmit_channel_configure_object_reset ( mcp251863_tx_fifo_cfg_t *config )
{
    mcp251863_fifo_ctl_t ci_fifo_con;
    ci_fifo_con.word = can_control_reset_values[ MCP251863_REG_CIFIFOCON  / 4 ];

    config->rtr_enable = ci_fifo_con.tx_bf.rtr_enable;
    config->tx_priority = ci_fifo_con.tx_bf.tx_priority;
    config->tx_attempts = ci_fifo_con.tx_bf.tx_attempts;
    config->fifo_size = ci_fifo_con.tx_bf.fifo_size;
    config->pay_load_size = ci_fifo_con.tx_bf.pay_load_size;
}

err_t mcp251863_transmit_queue_configure ( mcp251863_t *ctx, mcp251863_tx_que_cfg_t *config )
{
#ifndef CAN_TXQUEUE_IMPLEMENTED
    config;
    return -100;
#else
    err_t error_flag;
    uint16_t address = 0;

    mcp251863_tx_que_ctl_t ci_fifo_con;
    ci_fifo_con.word = can_control_reset_values[ MCP251863_REG_CIFIFOCON  / 4 ];

    ci_fifo_con.tx_bf.tx_enable = 1;
    ci_fifo_con.tx_bf.fifo_size = config->fifo_size;
    ci_fifo_con.tx_bf.pay_load_size = config->pay_load_size;
    ci_fifo_con.tx_bf.tx_attempts = config->tx_attempts;
    ci_fifo_con.tx_bf.tx_priority = config->tx_priority;

    address = MCP251863_REG_CITXQCON;
    error_flag = mcp251863_write_word ( ctx, address, ci_fifo_con.word);

    return error_flag;

#endif
}

void mcp251863_transmit_queue_configure_object_reset ( mcp251863_tx_que_cfg_t *config )
{
    mcp251863_fifo_ctl_t ci_fifo_con;
    ci_fifo_con.word = can_control_reset_values[ MCP251863_REG_CIFIFOCON  / 4 ];

    config->tx_priority = ci_fifo_con.tx_bf.tx_priority;
    config->tx_attempts = ci_fifo_con.tx_bf.tx_attempts;
    config->fifo_size = ci_fifo_con.tx_bf.fifo_size;
    config->pay_load_size = ci_fifo_con.tx_bf.pay_load_size;
}

err_t mcp251863_transmit_channel_load ( mcp251863_t *ctx, uint8_t channel, mcp251863_tx_msg_obj_t *tx_obj, bool flush )
{
    uint16_t n = 0;
    uint8_t j = 0;
    uint8_t cnt;
    uint8_t tx_buffer[ MCP251863_MAX_MSG_SIZE ];
    uint16_t address;
    uint32_t fifo_reg[ 3 ];
    uint32_t data_pointerbytes_in_object;
    mcp251863_fifo_ctl_t ci_fifo_con;
    mcp251863_fifo_stat_t ci_fifo_sta;
    mcp251863_fifo_user_cfg_t ci_fifo_ua;
    err_t error_flag;

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET );

    error_flag = mcp251863_read_word_array( ctx, address, fifo_reg, 3);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_fifo_con.word = fifo_reg[ 0 ];
    if ( !ci_fifo_con.tx_bf.tx_enable ) 
    {
        return -2;
    }

    data_pointerbytes_in_object = mcp251863_dlc_to_data_bytes( (  uint8_t ) tx_obj->bf.ctrl.dlc );
    if ( data_pointerbytes_in_object < ctx->func_data.txd_num_bytes ) 
    {
        return -3;
    }

    ci_fifo_sta.word = fifo_reg[ 1 ];

    ci_fifo_ua.word = fifo_reg[ 2 ];
#ifdef USERADDRESS_TIMES_FOUR
    address = 4 * ci_fifo_ua.bf.user_address;
#else
    address = ci_fifo_ua.bf.user_address;
#endif
    address += MCP251863_RAMADDR_START;

    tx_buffer[ 0 ] = tx_obj->byte[ 0 ]; 
    tx_buffer[ 1 ] = tx_obj->byte[ 1 ];
    tx_buffer[ 2 ] = tx_obj->byte[ 2 ];
    tx_buffer[ 3 ] = tx_obj->byte[ 3 ];

    tx_buffer[ 4 ] = tx_obj->byte[ 4 ];
    tx_buffer[5] = tx_obj->byte[5 ];
    tx_buffer[6] = tx_obj->byte[6 ];
    tx_buffer[7] = tx_obj->byte[7 ];

    for ( cnt = 0; cnt < ctx->func_data.txd_num_bytes; cnt++ ) 
    {
        tx_buffer[ cnt + 8] = ctx->func_data.txd[ cnt ];
    }

    if ( ctx->func_data.txd_num_bytes % 4 ) 
    {
        n = 4 - ( ctx->func_data.txd_num_bytes % 4 );
        cnt = ctx->func_data.txd_num_bytes + 8;

        for ( j = 0; j < n; j++ ) 
        {
            tx_buffer[ cnt + 8 + j] = 0;
        }
    }

    error_flag = mcp251863_write_byte_array( ctx, address, tx_buffer, ctx->func_data.txd_num_bytes + 8 + n );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -4;
    }

    error_flag = mcp251863_transmit_channel_update( ctx, channel, flush );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -5;
    }

    return error_flag;
}

err_t mcp251863_transmit_channel_flush ( mcp251863_t *ctx, uint8_t channel )
{
    uint8_t tx_data = 0;
    uint16_t address = 0;
    err_t error_flag;

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET );
    address += 1;

    tx_data = 0x02;

    error_flag = mcp251863_write_byte( ctx, address, tx_data );

    return error_flag;
}

err_t mcp251863_transmit_channel_status_get ( mcp251863_t *ctx, uint8_t channel, uint16_t *status )
{
    uint16_t address = 0;
    uint32_t sta = 0;
    uint32_t fifo_reg[ 2 ];
    mcp251863_fifo_stat_t ci_fifo_sta;
    mcp251863_fifo_ctl_t ci_fifo_con;
    err_t error_flag;

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET );

    error_flag = mcp251863_read_word_array( ctx, address, fifo_reg, 2 ) ; 
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_fifo_con.word = fifo_reg[ 0 ];
    ci_fifo_sta.word = fifo_reg[ 1 ];

    sta = ci_fifo_sta.byte[ 0 ];

    if ( ci_fifo_con.tx_bf.tx_request ) 
    {
        sta |= MCP251863_TX_FIFO_TRANSMITTING;
    }

    *status = ( uint16_t ) ( sta & MCP251863_TX_FIFO_STATUS_MASK );

    return error_flag;
}

int8_t mcp251863_transmit_channel_reset ( mcp251863_t *ctx, uint8_t channel )
{
    return mcp251863_receive_channel_reset( ctx, channel );
}

err_t mcp251863_transmit_channel_update ( mcp251863_t *ctx, uint8_t channel, bool flush )
{
    uint16_t address;
    mcp251863_fifo_ctl_t ci_fifo_con;
    err_t error_flag;

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET ) + 1; // Byte that contains FRESET
    ci_fifo_con.word = 0;
    ci_fifo_con.tx_bf.uinc = 1;

    if ( flush ) 
    {
        ci_fifo_con.tx_bf.tx_request = 1;
    }

    error_flag = mcp251863_write_byte ( ctx, address, ci_fifo_con.byte[ 1 ] );
    
    return error_flag;
}

err_t mcp251863_transmit_request_set ( mcp251863_t *ctx, uint32_t tx_req )
{
    err_t error_flag;

    uint32_t tx_data = tx_req;

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CITXREQ, tx_data );

    return error_flag;
}

err_t mcp251863_transmit_request_get ( mcp251863_t *ctx, uint32_t* tx_req )
{
    err_t error_flag;

    error_flag = mcp251863_read_word( ctx, MCP251863_REG_CITXREQ, tx_req );

    return error_flag;
}

err_t mcp251863_transmit_channel_abort ( mcp251863_t *ctx, uint8_t channel )
{
    uint16_t address;
    uint8_t tx_data;
    err_t error_flag;

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET );
    address += 1;

    tx_data = 0x00;

    error_flag = mcp251863_write_byte ( ctx, address, tx_data );

    return error_flag;
}

err_t mcp251863_transmit_abort_all ( mcp251863_t *ctx)
{
    uint8_t rx_data;
    err_t error_flag;

    error_flag = mcp251863_read_byte( ctx, ( MCP251863_REG_CICON + 3 ), &rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    rx_data |= 0x8;

    error_flag = mcp251863_write_byte ( ctx, ( MCP251863_REG_CICON + 3 ), rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_transmit_band_width_sharing_set ( mcp251863_t *ctx, uint8_t tx_bws )
{
    uint8_t tx_data = 0;
    err_t error_flag;

    error_flag = mcp251863_read_byte( ctx, ( MCP251863_REG_CICON + 3), &tx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    tx_data &= 0x0f;
    tx_data |= ( tx_bws << 4 );

    error_flag = mcp251863_write_byte ( ctx, ( MCP251863_REG_CICON + 3), tx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_filter_object_configure ( mcp251863_t *ctx, uint8_t filter, mcp251863_filt_obj_id_t *id )
{
    uint16_t address;
    mcp251863_filt_obj_t f_obj;
    err_t error_flag;

    f_obj.word = 0;
    f_obj.bf = *id;
    address = MCP251863_REG_CIFLTOBJ + ( filter * MCP251863_FILTER_OFFSET );

    error_flag = mcp251863_write_word ( ctx, address, f_obj.word );

    return error_flag;
}

err_t mcp251863_filter_mask_configure ( mcp251863_t *ctx, uint8_t filter, mcp251863_mask_obj_id_t *mask )
{
    uint16_t address;
    mcp251863_mask_obj_t m_obj;
    err_t error_flag;

    m_obj.word = 0;
    m_obj.bf = *mask;
    address = MCP251863_REG_CIMASK + ( filter * MCP251863_FILTER_OFFSET);

    error_flag = mcp251863_write_word ( ctx, address, m_obj.word);

    return error_flag;
}

err_t mcp251863_filter_to_fifo_link ( mcp251863_t *ctx, uint8_t filter, uint8_t channel, bool enable )
{
    uint16_t address;
    mcp251863_filt_ctl_t f_ctrl;
    err_t error_flag;

    if ( enable ) 
    {
        f_ctrl.bf.enable = 1;
    } 
    else 
    {
        f_ctrl.bf.enable = 0;
    }

    f_ctrl.bf.buffer_pointer = channel;
    address = MCP251863_REG_CIFLTCON + filter;

    error_flag = mcp251863_write_byte ( ctx, address, f_ctrl.byte);

    return error_flag;
}

err_t mcp251863_filter_enable ( mcp251863_t *ctx, uint8_t filter )
{
    uint16_t address;
    mcp251863_filt_ctl_t f_ctrl;
    err_t error_flag;

    address = MCP251863_REG_CIFLTCON + filter;

    error_flag = mcp251863_read_byte( ctx, address, &f_ctrl.byte);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    f_ctrl.bf.enable = 1;

    error_flag = mcp251863_write_byte ( ctx, address, f_ctrl.byte);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_filter_disable ( mcp251863_t *ctx, uint8_t filter)
{
    uint16_t address;
    mcp251863_filt_ctl_t f_ctrl;
    err_t error_flag;

    address = MCP251863_REG_CIFLTCON + filter;

    error_flag = mcp251863_read_byte( ctx, address, &f_ctrl.byte);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    f_ctrl.bf.enable = 0;

    error_flag = mcp251863_write_byte ( ctx, address, f_ctrl.byte);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_device_net_filter_count_set ( mcp251863_t *ctx, uint8_t dnfc )
{
    uint8_t tx_data = 0;
    err_t error_flag;

    error_flag = mcp251863_read_byte( ctx, MCP251863_REG_CICON, &tx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    tx_data &= 0x1f;
    tx_data |= dnfc;

    error_flag = mcp251863_write_byte ( ctx, MCP251863_REG_CICON, tx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_receive_channel_configure ( mcp251863_t *ctx, uint8_t channel, 
                                            mcp251863_rx_fifo_cfg_t *config )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_fifo_ctl_t ci_fifo_con;

#ifdef CAN_TXQUEUE_IMPLEMENTED
    if ( channel == CAN_TXQUEUE_CH0 ) 
    {
        return -100;
    }
#endif

    ci_fifo_con.word = can_control_reset_values[ MCP251863_REG_CIFIFOCON  / 4 ];

    ci_fifo_con.rx_bf.tx_enable = 0;
    ci_fifo_con.rx_bf.fifo_size = config->fifo_size;
    ci_fifo_con.rx_bf.pay_load_size = config->pay_load_size;
    ci_fifo_con.rx_bf.rx_time_stamp_enable = config->rx_time_stamp_enable;

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET );

    error_flag = mcp251863_write_word ( ctx, address, ci_fifo_con.word );

    return error_flag;
}

void mcp251863_receive_channel_configure_object_reset ( mcp251863_rx_fifo_cfg_t *config )
{
    mcp251863_fifo_ctl_t ci_fifo_con;
    ci_fifo_con.word = can_control_reset_values[ MCP251863_REG_CIFIFOCON  / 4 ];

    config->fifo_size = ci_fifo_con.rx_bf.fifo_size;
    config->pay_load_size = ci_fifo_con.rx_bf.pay_load_size;
    config->rx_time_stamp_enable = ci_fifo_con.rx_bf.rx_time_stamp_enable;
}

err_t mcp251863_receive_channel_status_get ( mcp251863_t *ctx, uint8_t channel, uint8_t *status )
{
    uint16_t address;
    mcp251863_fifo_stat_t ci_fifo_sta;
    err_t error_flag;

    ci_fifo_sta.word = 0;
    address = MCP251863_REG_CIFIFOSTA + ( channel * MCP251863_FIFO_OFFSET );

    error_flag = mcp251863_read_byte( ctx, address, &ci_fifo_sta.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *status = ( uint8_t ) ( ci_fifo_sta.byte[ 0 ] & 0x0F );

    return error_flag;
}

err_t mcp251863_receive_message_get ( mcp251863_t *ctx, uint8_t channel, mcp251863_rx_msg_obj_t* rx_obj )
{
    uint8_t cnt_n = 0;
    uint16_t address;
    uint8_t rx_data[ MCP251863_MAX_MSG_SIZE ];
    uint32_t fifo_reg[ 3 ];
    mcp251863_fifo_ctl_t ci_fifo_con;
    mcp251863_fifo_stat_t ci_fifo_sta;
    mcp251863_fifo_user_cfg_t ci_fifo_ua;
    err_t error_flag;
    mcp251863_reg_t my_reg;

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET );

    error_flag = mcp251863_read_word_array( ctx, address, fifo_reg, 3 );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_fifo_con.word = fifo_reg[ 0 ];
    if ( ci_fifo_con.tx_bf.tx_enable ) 
    {
        return -2;
    }

    ci_fifo_sta.word = fifo_reg[ 1 ];

    ci_fifo_ua.word = fifo_reg[ 2 ];
#ifdef USERADDRESS_TIMES_FOUR
    address = 4 * ci_fifo_ua.bf.user_address;
#else
    address = ci_fifo_ua.bf.user_address;
#endif
    address += MCP251863_RAMADDR_START;

    cnt_n = ctx->func_data.n_bytes + 8; 

    if ( ci_fifo_con.rx_bf.rx_time_stamp_enable ) 
    {
        cnt_n += 4; 
    }

    if ( cnt_n % 4 ) 
    {
        cnt_n = cnt_n + 4 - ( cnt_n % 4 );
    }

    if ( cnt_n > MCP251863_MAX_MSG_SIZE) 
    {
        cnt_n = MCP251863_MAX_MSG_SIZE;
    }

    error_flag = mcp251863_read_byte_array( ctx, address, rx_data, cnt_n );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -3;
    }

    my_reg.byte[ 0 ] = rx_data[ 0 ];
    my_reg.byte[ 1 ] = rx_data[ 1 ];
    my_reg.byte[ 2 ] = rx_data[ 2 ];
    my_reg.byte[ 3 ] = rx_data[ 3 ];
    rx_obj->word[ 0 ] = my_reg.word;

    my_reg.byte[ 0 ] = rx_data[ 4 ];
    my_reg.byte[ 1 ] = rx_data[5 ];
    my_reg.byte[ 2 ] = rx_data[6 ];
    my_reg.byte[ 3 ] = rx_data[7 ];
    rx_obj->word[ 1 ] = my_reg.word;

    if ( ci_fifo_con.rx_bf.rx_time_stamp_enable ) 
    {
        my_reg.byte[ 0 ] = rx_data[8 ];
        my_reg.byte[ 1 ] = rx_data[9 ];
        my_reg.byte[ 2 ] = rx_data[10 ];
        my_reg.byte[ 3 ] = rx_data[11 ];
        rx_obj->word[ 2 ] = my_reg.word;

        for ( uint8_t cnt = 0; cnt < ctx->func_data.n_bytes; cnt++ ) 
        {
            ctx->func_data.rxd[ cnt ] = rx_data[ cnt + 12 ];
        }
    } 
    else 
    {
        rx_obj->word[ 2 ] = 0;

        for ( uint8_t cnt = 0; cnt < ctx->func_data.n_bytes; cnt++ ) 
        {
            ctx->func_data.rxd[ cnt ] = rx_data[ cnt + 8 ];
        }
    }

    error_flag = mcp251863_receive_channel_update( ctx, channel );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -4;
    }

    return error_flag;
}

err_t mcp251863_receive_channel_reset ( mcp251863_t *ctx, uint8_t channel )
{
    uint16_t address = 0;
    mcp251863_fifo_ctl_t ci_fifo_con;
    err_t error_flag;

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET ) + 1;
    ci_fifo_con.word = 0;
    ci_fifo_con.rx_bf.freset = 1;

    error_flag = mcp251863_write_byte ( ctx, address, ci_fifo_con.byte[ 1 ] );

    return error_flag;
}

err_t mcp251863_receive_channel_update ( mcp251863_t *ctx, uint8_t channel )
{
    uint16_t address = 0;
    mcp251863_fifo_ctl_t ci_fifo_con;
    err_t error_flag;
    ci_fifo_con.word = 0;

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET ) + 1;
    ci_fifo_con.rx_bf.uinc = 1;

    error_flag = mcp251863_write_byte ( ctx, address, ci_fifo_con.byte[ 1 ] );

    return error_flag;
}

err_t mcp251863_tef_status_get ( mcp251863_t *ctx, uint8_t *status )
{
    err_t error_flag;
    uint16_t address = 0;

    mcp251863_tef_t ci_tef_sta;
    ci_tef_sta.word = 0;
    address = MCP251863_REG_CITEFSTA;

    error_flag = mcp251863_read_byte( ctx, address, &ci_tef_sta.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *status = ( uint8_t ) ( ci_tef_sta.byte[ 0 ] & MCP251863_TEF_FIFO_STATUS_MASK);

    return error_flag;
}

err_t mcp251863_tef_message_get ( mcp251863_t *ctx, mcp251863_tef_msg_obj_t *tef_obj )
{
    err_t error_flag;
    uint16_t address = 0;
    uint32_t fifo_reg[ 3 ];
    uint8_t cnt_n = 0;
    uint8_t rx_data[ 12 ];
    mcp251863_reg_t my_reg;
    mcp251863_tef_ctl_t ci_tef_con;
    mcp251863_tef_t ci_tef_sta;
    mcp251863_fifo_user_cfg_t ci_tef_ua;

    address = MCP251863_REG_CITEFCON;

    error_flag = mcp251863_read_word_array( ctx, address, fifo_reg, 3);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_tef_con.word = fifo_reg[ 0 ];

    ci_tef_sta.word = fifo_reg[ 1 ];

    ci_tef_ua.word = fifo_reg[ 2 ];
#ifdef USERADDRESS_TIMES_FOUR
    address = 4 * ci_tef_ua.bf.user_address;
#else
    address = ci_tef_ua.bf.user_address;
#endif
    address += MCP251863_RAMADDR_START;

    cnt_n = 8;

    if ( ci_tef_con.bf.time_stamp_enable ) 
    {
        cnt_n += 4;
    }

    error_flag = mcp251863_read_byte_array( ctx, address, rx_data, cnt_n );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    my_reg.byte[ 0 ] = rx_data[ 0 ];
    my_reg.byte[ 1 ] = rx_data[ 1 ];
    my_reg.byte[ 2 ] = rx_data[ 2 ];
    my_reg.byte[ 3 ] = rx_data[ 3 ];
    tef_obj ->word[ 0 ] = my_reg.word;

    my_reg.byte[ 0 ] = rx_data[ 4 ];
    my_reg.byte[ 1 ] = rx_data[5 ];
    my_reg.byte[ 2 ] = rx_data[6 ];
    my_reg.byte[ 3 ] = rx_data[7 ];
    tef_obj ->word[ 1 ] = my_reg.word;

    if ( ci_tef_con.bf.time_stamp_enable ) 
    {
        my_reg.byte[ 0 ] = rx_data[8 ];
        my_reg.byte[ 1 ] = rx_data[9 ];
        my_reg.byte[ 2 ] = rx_data[10 ];
        my_reg.byte[ 3 ] = rx_data[11 ];
        tef_obj ->word[ 2 ] = my_reg.word;
    } 
    else 
    {
        tef_obj ->word[ 2 ] = 0;
    }

    error_flag = mcp251863_tef_update( ctx );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -3;
    }

    return error_flag;
}

err_t mcp251863_tef_reset ( mcp251863_t *ctx )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_tef_ctl_t ci_tef_con;

    address = MCP251863_REG_CITEFCON + 1;
    ci_tef_con.word = 0;
    ci_tef_con.bf.freset = 1;

    error_flag = mcp251863_write_byte ( ctx, address, ci_tef_con.byte[ 1 ] );

    return error_flag;
}

err_t mcp251863_tef_update ( mcp251863_t *ctx )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_tef_ctl_t ci_tef_con;

    address = MCP251863_REG_CITEFCON + 1;
    ci_tef_con.word = 0;
    ci_tef_con.bf.uinc = 1;

    error_flag = mcp251863_write_byte ( ctx, address, ci_tef_con.byte[ 1 ] );

    return error_flag;
}

err_t mcp251863_tef_configure ( mcp251863_t *ctx, mcp251863_tef_cfg_t *config )
{
    err_t error_flag;

    mcp251863_tef_ctl_t ci_tef_con;
    ci_tef_con.word = can_control_reset_values[ MCP251863_REG_CITEFCON / 4 ];

    ci_tef_con.bf.fifo_size = config->fifo_size;
    ci_tef_con.bf.time_stamp_enable  = config->time_stamp_enable ;

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CITEFCON, ci_tef_con.word );

    return error_flag;
}

void mcp251863_tef_configure_object_reset ( mcp251863_tef_cfg_t *config )
{
    mcp251863_tef_ctl_t ci_tef_con;
    ci_tef_con.word = can_control_reset_values[ MCP251863_REG_CIFIFOCON  / 4 ];

    config->fifo_size = ci_tef_con.bf.fifo_size;
    config->time_stamp_enable  = ci_tef_con.bf.time_stamp_enable ;
}

err_t mcp251863_module_event_get ( mcp251863_t *ctx, uint16_t *flags )
{
    err_t error_flag;

    mcp251863_int_flag_t int_flags;
    int_flags.word = 0;

    error_flag = mcp251863_read_half_word ( ctx, MCP251863_REG_CIINTFLAG, &int_flags.word);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *flags = ( uint16_t ) ( int_flags.word & MCP251863_ALL_EVENTS );

    return error_flag;
}

err_t mcp251863_module_event_enable ( mcp251863_t *ctx, uint16_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_int_cfg_t int_enables;

    address = MCP251863_REG_CIINTENABLE;
    int_enables.word = 0;

    error_flag = mcp251863_read_half_word ( ctx, address, &int_enables.word);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    int_enables.word |= ( flags & MCP251863_ALL_EVENTS );

    error_flag = mcp251863_write_half_word ( ctx, address, int_enables.word );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_module_event_disable ( mcp251863_t *ctx, uint16_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_int_cfg_t int_enables;

    address = MCP251863_REG_CIINTENABLE;
    int_enables.word = 0;

    error_flag = mcp251863_read_half_word ( ctx, address, &int_enables.word);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    int_enables.word &= ~( flags & MCP251863_ALL_EVENTS );

    error_flag = mcp251863_write_half_word( ctx, address, int_enables.word );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_module_event_clear ( mcp251863_t *ctx, uint16_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_int_flag_t int_flags;

    address = MCP251863_REG_CIINTFLAG;
    int_flags.word = 0;

    int_flags.word = MCP251863_ALL_EVENTS;
    int_flags.word &= ~flags;

    error_flag = mcp251863_write_half_word( ctx, address, int_flags.word );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_module_event_rx_code_get ( mcp251863_t *ctx, uint8_t *rx_code )
{
    err_t error_flag;
    uint16_t address = 0;
    uint8_t rx_code_byte = 0;

    address = MCP251863_REG_CIVEC + 3;

    error_flag = mcp251863_read_byte( ctx, address, &rx_code_byte );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    if ( ( rx_code_byte < MCP251863_RXCODE_TOTAL_CHANNELS ) || ( rx_code_byte == MCP251863_RXCODE_NO_INT ) ) 
    {
        *rx_code = ( uint8_t ) rx_code_byte;
    } 
    else 
    {
        *rx_code = MCP251863_RXCODE_RESERVED; 
    }

    return error_flag;
}

err_t mcp251863_module_event_tx_code_get ( mcp251863_t *ctx, uint8_t *tx_code )
{
    err_t error_flag;
    uint16_t address = 0;
    uint8_t tx_code_byte = 0;

    address = MCP251863_REG_CIVEC + 2;

    error_flag = mcp251863_read_byte( ctx, address, &tx_code_byte );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    if ( ( tx_code_byte < MCP251863_TXCODE_TOTAL_CHANNELS ) || ( tx_code_byte == MCP251863_TXCODE_NO_INT ) ) 
    {
        *tx_code = ( uint8_t ) tx_code_byte;
    } 
    else 
    {
        *tx_code = MCP251863_TXCODE_RESERVED;
    }

    return error_flag;
}

err_t mcp251863_module_event_filter_hit_get ( mcp251863_t *ctx, uint8_t *filter_hit )
{
    err_t error_flag;
    uint16_t address = 0;
    uint8_t filter_hit_byte = 0;

    address = MCP251863_REG_CIVEC + 1;

    error_flag = mcp251863_read_byte( ctx, address, &filter_hit_byte );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *filter_hit  = ( uint8_t ) filter_hit_byte;

    return error_flag;
}

err_t mcp251863_module_event_icode_get ( mcp251863_t *ctx, uint8_t *icode )
{
    err_t error_flag;
    uint16_t address = 0;
    uint8_t icode_byte = 0;

    address = MCP251863_REG_CIVEC;

    error_flag = mcp251863_read_byte( ctx, address, &icode_byte);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    if ( ( icode_byte < MCP251863_ICODE_RESERVED ) && ( ( icode_byte < MCP251863_ICODE_TOTAL_CHANNELS ) || ( icode_byte >= MCP251863_ICODE_NO_INT ) ) ) 
    {
        *icode = ( uint8_t ) icode_byte;
    } 
    else 
    {
        *icode = MCP251863_ICODE_RESERVED;
    }

    return error_flag;
}

err_t mcp251863_transmit_channel_event_get ( mcp251863_t *ctx, uint8_t channel, uint8_t *flags )
{
    err_t error_flag;
    uint16_t address = 0;

    mcp251863_fifo_stat_t ci_fifo_sta;
    ci_fifo_sta.word = 0;
    address = MCP251863_REG_CIFIFOSTA + ( channel * MCP251863_FIFO_OFFSET );

    error_flag = mcp251863_read_byte( ctx, address, &ci_fifo_sta.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *flags = ( uint8_t ) ( ci_fifo_sta.byte[ 0 ] & MCP251863_TX_FIFO_ALL_EVENTS );

    return error_flag;
}

err_t mcp251863_transmit_event_get ( mcp251863_t *ctx, uint32_t *txif )
{
    err_t error_flag;

    error_flag = mcp251863_read_word ( ctx, MCP251863_REG_CITXIF, txif );

    return error_flag;
}

err_t mcp251863_transmit_event_attempt_get ( mcp251863_t *ctx, uint32_t *txatif )
{
    err_t error_flag;

    error_flag = mcp251863_read_word( ctx, MCP251863_REG_CITXATIF, txatif );

    return error_flag;
}

err_t mcp251863_transmit_channel_index_get ( mcp251863_t *ctx, uint8_t channel, uint8_t *idx )
{
    err_t error_flag;
    uint16_t address = 0;

    mcp251863_fifo_stat_t ci_fifo_sta;
    ci_fifo_sta.word = 0;
    address = MCP251863_REG_CIFIFOSTA + ( channel * MCP251863_FIFO_OFFSET );

    error_flag = mcp251863_read_word( ctx, address, &ci_fifo_sta.word);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *idx = ci_fifo_sta.tx_bf.fifo_index;

    return error_flag;
}

err_t mcp251863_transmit_channel_event_enable( mcp251863_t *ctx, uint8_t channel, uint8_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_fifo_ctl_t ci_fifo_con;

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET );
    ci_fifo_con.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &ci_fifo_con.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_fifo_con.byte[ 0 ] |= ( flags & MCP251863_TX_FIFO_ALL_EVENTS );

    error_flag = mcp251863_write_byte ( ctx, address, ci_fifo_con.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_transmit_channel_event_disable ( mcp251863_t *ctx, uint8_t channel, uint8_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_fifo_ctl_t ci_fifo_con;

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET );
    ci_fifo_con.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &ci_fifo_con.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_fifo_con.byte[ 0 ] &= ~( flags & MCP251863_TX_FIFO_ALL_EVENTS );

    error_flag = mcp251863_write_byte ( ctx, address, ci_fifo_con.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_transmit_channel_event_attempt_clear ( mcp251863_t *ctx, uint8_t channel )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_fifo_stat_t ci_fifo_sta;

    address = MCP251863_REG_CIFIFOSTA + ( channel * MCP251863_FIFO_OFFSET );
    ci_fifo_sta.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &ci_fifo_sta.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_fifo_sta.byte[ 0 ] &= ~MCP251863_TX_FIFO_ATTEMPTS_EXHAUSTED_EVENT;

    error_flag = mcp251863_write_byte ( ctx, address, ci_fifo_sta.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_receive_channel_event_get ( mcp251863_t *ctx, uint8_t channel, uint8_t *flags )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_fifo_stat_t ci_fifo_sta;

#ifdef CAN_TXQUEUE_IMPLEMENTED
    if ( channel == CAN_TXQUEUE_CH0 ) 
    {
        return -100;
    }
#endif

    ci_fifo_sta.word = 0;
    address = MCP251863_REG_CIFIFOSTA + ( channel * MCP251863_FIFO_OFFSET );

    error_flag = mcp251863_read_byte( ctx, address, &ci_fifo_sta.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *flags = ( uint8_t ) ( ci_fifo_sta.byte[ 0 ] & MCP251863_RX_FIFO_ALL_EVENTS );

    return error_flag;
}

err_t mcp251863_receive_event_get ( mcp251863_t *ctx, uint32_t *rxif )
{
    err_t error_flag;

    error_flag = mcp251863_read_word( ctx, MCP251863_REG_CIRXIF, rxif );

    return error_flag;
}

err_t mcp251863_receive_event_overflow_get ( mcp251863_t *ctx, uint32_t *rxovif )
{
    err_t error_flag;

    error_flag = mcp251863_read_word( ctx, MCP251863_REG_CIRXOVIF, rxovif );

    return error_flag;
}

int8_t mcp251863_receive_channel_index_get ( mcp251863_t *ctx, uint8_t channel, uint8_t *idx )
{
    return mcp251863_transmit_channel_index_get( ctx, channel, idx );
}

err_t mcp251863_receive_channel_event_enable ( mcp251863_t *ctx, uint8_t channel, uint8_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_fifo_ctl_t ci_fifo_con;

#ifdef CAN_TXQUEUE_IMPLEMENTED
    if ( channel == CAN_TXQUEUE_CH0 ) 
    {
        return -100;
    }
#endif 

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET );
    ci_fifo_con.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &ci_fifo_con.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_fifo_con.byte[ 0 ] |= ( flags & MCP251863_RX_FIFO_ALL_EVENTS );

    error_flag = mcp251863_write_byte ( ctx, address, ci_fifo_con.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_receive_channel_event_disable ( mcp251863_t *ctx, uint8_t channel, uint8_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_fifo_ctl_t ci_fifo_con;

#ifdef CAN_TXQUEUE_IMPLEMENTED
    if ( channel == CAN_TXQUEUE_CH0) 
    {
        return -100;
    }
#endif

    address = MCP251863_REG_CIFIFOCON  + ( channel * MCP251863_FIFO_OFFSET );
    ci_fifo_con.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &ci_fifo_con.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_fifo_con.byte[ 0 ] &= ~( flags & MCP251863_RX_FIFO_ALL_EVENTS );

    error_flag = mcp251863_write_byte ( ctx, address, ci_fifo_con.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_receive_channel_event_overflow_clear ( mcp251863_t *ctx, uint8_t channel )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_fifo_stat_t ci_fifo_sta;

#ifdef CAN_TXQUEUE_IMPLEMENTED
    if ( channel == CAN_TXQUEUE_CH0)
    {
         return -100;
    }
#endif

    ci_fifo_sta.word = 0;
    address = MCP251863_REG_CIFIFOSTA + ( channel * MCP251863_FIFO_OFFSET );

    error_flag = mcp251863_read_byte( ctx, address, &ci_fifo_sta.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_fifo_sta.byte[ 0 ] &= ~( MCP251863_RX_FIFO_OVERFLOW_EVENT);

    error_flag = mcp251863_write_byte ( ctx, address, ci_fifo_sta.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_tef_event_get ( mcp251863_t *ctx, uint8_t* flags )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_tef_t ci_tef_sta;

    ci_tef_sta.word = 0;
    address = MCP251863_REG_CITEFSTA;

    error_flag = mcp251863_read_byte( ctx, address, &ci_tef_sta.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *flags = ( uint8_t ) ( ci_tef_sta.byte[ 0 ] & MCP251863_TEF_FIFO_ALL_EVENTS );

    return error_flag;
}

err_t mcp251863_tef_event_enable ( mcp251863_t *ctx, uint8_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_tef_ctl_t ci_tef_con;

    address = MCP251863_REG_CITEFCON;
    ci_tef_con.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &ci_tef_con.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_tef_con.byte[ 0 ] |= ( flags & MCP251863_TEF_FIFO_ALL_EVENTS );

    error_flag = mcp251863_write_byte ( ctx, address, ci_tef_con.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_tef_event_disable ( mcp251863_t *ctx, uint8_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_tef_ctl_t ci_tef_con;

    address = MCP251863_REG_CITEFCON;
    ci_tef_con.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &ci_tef_con.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_tef_con.byte[ 0 ] &= ~( flags & MCP251863_TEF_FIFO_ALL_EVENTS );

    error_flag = mcp251863_write_byte ( ctx, address, ci_tef_con.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_tef_event_overflow_clear ( mcp251863_t *ctx )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_tef_t ci_tef_sta;

    ci_tef_sta.word = 0;
    address = MCP251863_REG_CITEFSTA;

    error_flag = mcp251863_read_byte( ctx, address, &ci_tef_sta.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ci_tef_sta.byte[ 0 ] &= ~( MCP251863_TEF_FIFO_OVERFLOW_EVENT );

    error_flag = mcp251863_write_byte ( ctx, address, ci_tef_sta.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_error_count_transmit_get ( mcp251863_t *ctx, uint8_t *tec )
{
    err_t error_flag;
    uint16_t address = 0;

    address = MCP251863_REG_CITREC + 1;

    error_flag = mcp251863_read_byte( ctx, address, tec);

    return error_flag;
}

err_t mcp251863_error_count_receive_get ( mcp251863_t *ctx, uint8_t *rec )
{
    err_t error_flag;
    uint16_t address = 0;

    address = MCP251863_REG_CITREC;

    error_flag = mcp251863_read_byte( ctx, address, rec );

    return error_flag;
}

err_t mcp251863_error_state_get ( mcp251863_t *ctx, uint8_t* flags )
{
    err_t error_flag;
    uint16_t address = 0;
    uint8_t rx_data = 0;

    address = MCP251863_REG_CITREC + 2;

    error_flag = mcp251863_read_byte( ctx, address, &rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *flags = ( uint8_t ) ( rx_data & MCP251863_ERROR_ALL );

    return error_flag;
}

err_t mcp251863_error_count_state_get ( mcp251863_t *ctx, uint8_t *tec, uint8_t *rec, uint8_t *flags )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_trec_t ci_trec;

    address = MCP251863_REG_CITREC;
    ci_trec.word = 0;

    error_flag = mcp251863_read_word( ctx, address, &ci_trec.word );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *tec = ci_trec.byte[ 1 ];
    *rec = ci_trec.byte[ 0 ];
    *flags = ( uint8_t ) ( ci_trec.byte[ 2 ] & MCP251863_ERROR_ALL );

    return error_flag;
}

err_t mcp251863_bus_diagnostics_get ( mcp251863_t *ctx, mcp251863_bus_diag_t *bus_diag )
{
    err_t error_flag;
    uint16_t address = 0;
    uint32_t rx_data[ 2 ];
    mcp251863_bus_diag_t bus_diag_t;

    address = MCP251863_REG_CIBDIAG0;

    error_flag = mcp251863_read_word_array( ctx, address, rx_data, 2 ) ; 
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    bus_diag_t.word[ 0 ] = rx_data[ 0 ];
    bus_diag_t.word[ 1 ] = rx_data[ 1 ] & 0x0000ffff;
    bus_diag_t.word[ 2 ] = ( rx_data[ 1 ] >> 16 ) & 0x0000ffff;
    *bus_diag = bus_diag_t;

    return error_flag;
}

err_t mcp251863_bus_diagnostics_clear ( mcp251863_t *ctx )
{
    err_t error_flag;
    uint8_t address = 0;
    uint32_t tx_data[ 2 ];

    address = MCP251863_REG_CIBDIAG0;
    tx_data[ 0 ] = 0;
    tx_data[ 1 ] = 0;

    error_flag = mcp251863_write_word_array( ctx, address, tx_data, 2 ) ; 

    return error_flag;
}

err_t mcp251863_ecc_enable ( mcp251863_t *ctx )
{
    err_t error_flag;
    uint8_t rx_data = 0;

    error_flag = mcp251863_read_byte( ctx, MCP251863_REG_ECCCON, &rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    rx_data |= 0x01;

    error_flag = mcp251863_write_byte ( ctx, MCP251863_REG_ECCCON, rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_ecc_disable ( mcp251863_t *ctx )
{
    err_t error_flag;
    uint8_t rx_data = 0;

    error_flag = mcp251863_read_byte( ctx, MCP251863_REG_ECCCON, &rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    rx_data &= ~0x01;

    error_flag = mcp251863_write_byte ( ctx, MCP251863_REG_ECCCON, rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_ecc_event_get ( mcp251863_t *ctx, uint8_t *flags )
{
    err_t error_flag;
    uint16_t address = 0;

    uint8_t ecc_status = 0;
    address = MCP251863_REG_ECCSTA;

    error_flag = mcp251863_read_byte( ctx, address, &ecc_status );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *flags = ( uint8_t ) ( ecc_status & MCP2518_ECC_ALL_EVENTS );

    return error_flag;
}

err_t mcp251863_ecc_parity_set ( mcp251863_t *ctx, uint8_t parity )
{
    err_t error_flag;

    error_flag = mcp251863_write_byte ( ctx, MCP251863_REG_ECCCON + 1, parity );

    return error_flag;
}

err_t mcp251863_ecc_parity_get ( mcp251863_t *ctx, uint8_t *parity )
{
    err_t error_flag;

    error_flag = mcp251863_read_byte( ctx, MCP251863_REG_ECCCON + 1, parity );

    return error_flag;
}

err_t mcp251863_ecc_error_address_get ( mcp251863_t *ctx, uint16_t *address )
{
    err_t error_flag;
    mcp251863_ecc_sta_t reg;

    error_flag = mcp251863_read_word( ctx, MCP251863_REG_ECCSTA, &reg.word );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *address = reg.bf.error_address;

    return error_flag;
}

err_t mcp251863_ecc_event_enable ( mcp251863_t *ctx, uint8_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    uint8_t ecc_interrupts = 0;

    address = MCP251863_REG_ECCCON;

    error_flag = mcp251863_read_byte( ctx, address, &ecc_interrupts );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ecc_interrupts |= ( flags & MCP2518_ECC_ALL_EVENTS );

    error_flag = mcp251863_write_byte ( ctx, address, ecc_interrupts );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_ecc_event_disable ( mcp251863_t *ctx, uint8_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    uint8_t ecc_interrupts = 0;

    address = MCP251863_REG_ECCCON;

    error_flag = mcp251863_read_byte( ctx, address, &ecc_interrupts );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ecc_interrupts &= ~( flags & MCP2518_ECC_ALL_EVENTS );

    error_flag = mcp251863_write_byte ( ctx, address, ecc_interrupts );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_ecc_event_clear ( mcp251863_t *ctx, uint8_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    uint8_t ecc_stat = 0;

    address = MCP251863_REG_ECCSTA;

    error_flag = mcp251863_read_byte( ctx, address, &ecc_stat );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    ecc_stat &= ~( flags & MCP2518_ECC_ALL_EVENTS );

    error_flag = mcp251863_write_byte ( ctx, address, ecc_stat );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_crc_event_enable ( mcp251863_t *ctx, uint8_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    uint8_t crc;

    address = MCP251863_REG_CRC + 3;

    error_flag = mcp251863_read_byte( ctx, address, &crc );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    crc |= ( flags & MCP251863_CRC_ALL_EVENTS );

    error_flag = mcp251863_write_byte ( ctx, address, crc );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_crc_event_disable ( mcp251863_t *ctx, uint8_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    uint8_t crc;

    address = MCP251863_REG_CRC + 3;

    error_flag = mcp251863_read_byte( ctx, address, &crc);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    crc &= ~( flags & MCP251863_CRC_ALL_EVENTS );

    error_flag = mcp251863_write_byte ( ctx, address, crc);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_crc_event_clear ( mcp251863_t *ctx, uint8_t flags )
{
    err_t error_flag;
    uint16_t address = 0;
    uint8_t crc;

    address = MCP251863_REG_CRC + 2;

    error_flag = mcp251863_read_byte( ctx, address, &crc);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    crc &= ~( flags & MCP251863_CRC_ALL_EVENTS );

    error_flag = mcp251863_write_byte ( ctx, address, crc );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_crc_event_get ( mcp251863_t *ctx, uint8_t *flags )
{
    err_t error_flag;
    uint16_t address = 0;
    uint8_t crc;

    address = MCP251863_REG_CRC + 2;

    error_flag = mcp251863_read_byte( ctx, address, &crc );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *flags = ( uint8_t ) ( crc & MCP251863_CRC_ALL_EVENTS );

    return error_flag;
}

err_t mcp251863_crc_value_get ( mcp251863_t *ctx, uint16_t *crc )
{
    err_t error_flag;

    error_flag = mcp251863_read_half_word ( ctx, MCP251863_REG_CRC, crc );

    return error_flag;
}

err_t mcp251863_ram_init ( mcp251863_t *ctx, uint8_t tx_data )
{
    uint8_t tx_buf[ 64 ];
    uint16_t address = MCP251863_RAMADDR_START;
    err_t error_flag = MCP251863_OK;
    
    for ( uint32_t cnt = 0; cnt < 64; cnt++ )
        tx_buf[ cnt ] = tx_data;

    for ( uint32_t cnt = 0; cnt < 32; cnt++ )
    {
        error_flag |= mcp251863_write_byte_array( ctx, address, tx_buf, 64 );
        if ( error_flag == MCP251863_ERROR )
            return -1;
        address += 64;
    }

    return error_flag;
}

err_t mcp251863_time_stamp_enable ( mcp251863_t *ctx )
{
    err_t error_flag;
    uint8_t rx_data = 0;

    error_flag = mcp251863_read_byte( ctx, MCP251863_REG_CITSCON + 2, &rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    rx_data |= 0x01;

    error_flag = mcp251863_write_byte ( ctx, MCP251863_REG_CITSCON + 2, rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_time_stamp_disable ( mcp251863_t *ctx )
{
    err_t error_flag;
    uint8_t rx_data = 0;

    error_flag = mcp251863_read_byte( ctx, MCP251863_REG_CITSCON + 2, &rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    rx_data &= 0x06;

    error_flag = mcp251863_write_byte ( ctx, MCP251863_REG_CITSCON + 2, rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_time_stamp_get ( mcp251863_t *ctx, uint32_t *time_stamp )
{
    err_t error_flag;

    error_flag = mcp251863_read_word( ctx, MCP251863_REG_CITBC, time_stamp );

    return error_flag;
}

err_t mcp251863_time_stamp_set ( mcp251863_t *ctx, uint32_t time_stamp )
{
    err_t error_flag;

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CITBC, time_stamp );

    return error_flag;
}

err_t mcp251863_time_stamp_mode_configure ( mcp251863_t *ctx, uint8_t mode )
{
    err_t error_flag;
    uint8_t rx_data = 0;

    error_flag = mcp251863_read_byte( ctx, MCP251863_REG_CITSCON + 2, &rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    rx_data &= 0x01;
    rx_data |= mode << 1;

    error_flag = mcp251863_write_byte ( ctx, MCP251863_REG_CITSCON + 2, rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_time_stamp_prescaler_set ( mcp251863_t *ctx, uint16_t time_stamp )
{
    err_t error_flag;

    error_flag = mcp251863_write_half_word( ctx, MCP251863_REG_CITSCON, time_stamp );

    return error_flag;
}

err_t mcp251863_oscillator_enable ( mcp251863_t *ctx )
{
    err_t error_flag;
    uint8_t rx_data = 0;

    error_flag = mcp251863_read_byte( ctx, MCP251863_REG_OSC, &rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    rx_data &= ~0x4;

    error_flag = mcp251863_write_byte ( ctx, MCP251863_REG_OSC, rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_oscillator_control_set ( mcp251863_t *ctx, mcp251863_div_ctl_t ctrl )
{
    err_t error_flag;

    mcp251863_osc_ctl_t osc;
    osc.word = 0;

    osc.bf.pll_enable = ctrl.pll_enable;
    osc.bf.osc_disable = ctrl.osc_disable;
    osc.bf.sclk_divide = ctrl.sclk_divide;
    osc.bf.clk_out_divide = ctrl.clk_out_divide;

    error_flag = mcp251863_write_byte ( ctx, MCP251863_REG_OSC, osc.byte[ 0 ] );

    return error_flag;
}

void mcp251863_oscillator_control_object_reset ( mcp251863_div_ctl_t *ctrl )
{
    mcp251863_osc_ctl_t osc;
    osc.word = mcp2518_control_reset_values[ 0 ];

    ctrl->pll_enable = osc.bf.pll_enable;
    ctrl->osc_disable = osc.bf.osc_disable;
    ctrl->sclk_divide = osc.bf.sclk_divide;
    ctrl->clk_out_divide = osc.bf.clk_out_divide;
}

err_t mcp251863_oscillator_status_get ( mcp251863_t *ctx, mcp251863_osc_sta_t *status )
{
    err_t error_flag;
    mcp251863_osc_sta_t stat;
    mcp251863_osc_ctl_t osc;

    osc.word = 0;
    error_flag = mcp251863_read_byte( ctx, MCP251863_REG_OSC + 1, &osc.byte[ 1 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    stat.pll_ready = osc.bf.pll_ready;
    stat.osc_ready = osc.bf.osc_ready;
    stat.sclk_ready = osc.bf.sclk_ready;

    *status = stat;

    return error_flag;
}

err_t mcp251863_bit_time_configure ( mcp251863_t *ctx, uint8_t bit_time, uint8_t clk )
{
    err_t error_flag;

    switch ( clk) 
    {
        case MCP251863_SYSCLK_40M:
        {
            error_flag = mcp251863_bit_time_configure_nominal_40_mhz( ctx, bit_time );
            if ( error_flag == MCP251863_ERROR ) 
            {
                return error_flag;
            }
            error_flag = mcp251863_bit_time_configure_data_40_mhz( ctx, bit_time );
            break;
        }
        case MCP251863_SYSCLK_20M:
        {
            error_flag = mcp251863_bit_time_configure_nominal_20_mhz( ctx, bit_time );
            if ( error_flag == MCP251863_ERROR ) 
            {
                return error_flag;
            }
            error_flag = mcp251863_bit_time_configure_data_20_mhz( ctx, bit_time );
            break;
        }
        case MCP251863_SYSCLK_10M:
        {
            error_flag = mcp251863_bit_time_configure_nominal_10_mhz( ctx, bit_time );
            if ( error_flag == MCP251863_ERROR ) 
            {
                return error_flag;
            }
            error_flag = mcp251863_bit_time_configure_data_10_mhz( ctx, bit_time );
            break;
        }
        default:
        {
            error_flag = -1;
            break;
        }
    }

    return error_flag;
}

err_t mcp251863_bit_time_configure_nominal_40_mhz ( mcp251863_t *ctx, uint8_t bit_time )
{
    err_t error_flag;
    mcp251863_nbt_cfg_t ci_nbt_cfg;

    ci_nbt_cfg.word = can_control_reset_values[ MCP251863_REG_CINBTCFG / 4 ];

    switch ( bit_time ) 
    {
        case MCP251863_500K_1M:
        case MCP251863_500K_2M:
        case MCP251863_500K_3M:
        case MCP251863_500K_4M:
        case MCP251863_500K_5M:
        case MCP251863_500K_6M7:
        case MCP251863_500K_8M:
        case MCP251863_500K_10M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 62;
            ci_nbt_cfg.bf.tseg2 = 15;
            ci_nbt_cfg.bf.swj = 15;
            break;
        }
        case MCP251863_250K_500K:
        case MCP251863_250K_833K:
        case MCP251863_250K_1M:
        case MCP251863_250K_1M5:
        case MCP251863_250K_2M:
        case MCP251863_250K_3M:
        case MCP251863_250K_4M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 126;
            ci_nbt_cfg.bf.tseg2 = 31;
            ci_nbt_cfg.bf.swj = 31;
            break;
        }
        case MCP251863_1000K_4M:
        case MCP251863_1000K_8M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 30;
            ci_nbt_cfg.bf.tseg2 = 7;
            ci_nbt_cfg.bf.swj = 7;
            break;
        }
        case MCP251863_125K_500K:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 254;
            ci_nbt_cfg.bf.tseg2 = 63;
            ci_nbt_cfg.bf.swj = 63;
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CINBTCFG, ci_nbt_cfg.word);

    return error_flag;
}

err_t mcp251863_bit_time_configure_data_40_mhz ( mcp251863_t *ctx, uint8_t bit_time )
{
    err_t error_flag;
    mcp251863_dbt_cfg_t ci_dbt_cfg;
    mcp251863_tdc_cfg_t ci_tdc;
    uint32_t tdc_value = 0;

    ci_dbt_cfg.word = can_control_reset_values[ MCP251863_REG_CIDBTCFG / 4 ];
    ci_tdc.word = 0;

    ci_tdc.bf.tdc_mode = MCP251863_SSP_MODE_AUTO;

    switch ( bit_time ) 
    {
        case MCP251863_500K_1M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 30;
            ci_dbt_cfg.bf.tseg2 = 7;
            ci_dbt_cfg.bf.swj = 7;
            ci_tdc.bf.tdc_offset = 31;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_500K_2M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 14;
            ci_dbt_cfg.bf.tseg2 = 3;
            ci_dbt_cfg.bf.swj = 3;
            ci_tdc.bf.tdc_offset = 15;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_500K_3M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 8;
            ci_dbt_cfg.bf.tseg2 = 2;
            ci_dbt_cfg.bf.swj = 2;
            ci_tdc.bf.tdc_offset = 9;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_500K_4M:
        case MCP251863_1000K_4M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 6;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            ci_tdc.bf.tdc_offset = 7;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_500K_5M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 4;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            ci_tdc.bf.tdc_offset = 5;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_500K_6M7:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 3;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            ci_tdc.bf.tdc_offset = 4;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_500K_8M:
        case MCP251863_1000K_8M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 2;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            ci_tdc.bf.tdc_offset = 3;
            ci_tdc.bf.tdc_value = 1;
            break;
        }
        case MCP251863_500K_10M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 1;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            ci_tdc.bf.tdc_offset = 2;
            ci_tdc.bf.tdc_value = 0;
            break;
        }
        case MCP251863_250K_500K:
        case MCP251863_125K_500K:
        {
            ci_dbt_cfg.bf.brp = 1;
            ci_dbt_cfg.bf.tseg1 = 30;
            ci_dbt_cfg.bf.tseg2 = 7;
            ci_dbt_cfg.bf.swj = 7;
            ci_tdc.bf.tdc_offset = 31;
            ci_tdc.bf.tdc_value = tdc_value;
            ci_tdc.bf.tdc_mode = MCP251863_SSP_MODE_OFF;
            break;
        }
        case MCP251863_250K_833K:
        {
            ci_dbt_cfg.bf.brp = 1;
            ci_dbt_cfg.bf.tseg1 = 17;
            ci_dbt_cfg.bf.tseg2 = 4;
            ci_dbt_cfg.bf.swj = 4;
            ci_tdc.bf.tdc_offset = 18;
            ci_tdc.bf.tdc_value = tdc_value;
            ci_tdc.bf.tdc_mode = MCP251863_SSP_MODE_OFF;
            break;
        }
        case MCP251863_250K_1M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 30;
            ci_dbt_cfg.bf.tseg2 = 7;
            ci_dbt_cfg.bf.swj = 7;
            ci_tdc.bf.tdc_offset = 31;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_250K_1M5:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 18;
            ci_dbt_cfg.bf.tseg2 = 5;
            ci_dbt_cfg.bf.swj = 5;
            ci_tdc.bf.tdc_offset = 19;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_250K_2M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 14;
            ci_dbt_cfg.bf.tseg2 = 3;
            ci_dbt_cfg.bf.swj = 3;
            ci_tdc.bf.tdc_offset = 15;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_250K_3M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 8;
            ci_dbt_cfg.bf.tseg2 = 2;
            ci_dbt_cfg.bf.swj = 2;
            ci_tdc.bf.tdc_offset = 9;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_250K_4M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 6;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            ci_tdc.bf.tdc_offset = 7;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CIDBTCFG, ci_dbt_cfg.word);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

#ifdef REV_A
    ci_tdc.bf.tdc_offset = 0;
    ci_tdc.bf.tdc_value = 0;
#endif

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CITDC, ci_tdc.word);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -3;
    }

    return error_flag;
}

err_t mcp251863_bit_time_configure_nominal_20_mhz ( mcp251863_t *ctx, uint8_t bit_time )
{
    err_t error_flag;
    mcp251863_nbt_cfg_t ci_nbt_cfg;

    ci_nbt_cfg.word = can_control_reset_values[ MCP251863_REG_CINBTCFG / 4 ];

    switch ( bit_time ) 
    {
        case MCP251863_500K_1M:
        case MCP251863_500K_2M:
        case MCP251863_500K_4M:
        case MCP251863_500K_5M:
        case MCP251863_500K_6M7:
        case MCP251863_500K_8M:
        case MCP251863_500K_10M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 30;
            ci_nbt_cfg.bf.tseg2 = 7;
            ci_nbt_cfg.bf.swj = 7;
            break;
        }
        case MCP251863_250K_500K:
        case MCP251863_250K_833K:
        case MCP251863_250K_1M:
        case MCP251863_250K_1M5:
        case MCP251863_250K_2M:
        case MCP251863_250K_3M:
        case MCP251863_250K_4M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 62;
            ci_nbt_cfg.bf.tseg2 = 15;
            ci_nbt_cfg.bf.swj = 15;
            break;
        }
        case MCP251863_1000K_4M:
        case MCP251863_1000K_8M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 14;
            ci_nbt_cfg.bf.tseg2 = 3;
            ci_nbt_cfg.bf.swj = 3;
            break;
        }
        case MCP251863_125K_500K:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 126;
            ci_nbt_cfg.bf.tseg2 = 31;
            ci_nbt_cfg.bf.swj = 31;
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CINBTCFG, ci_nbt_cfg.word);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_bit_time_configure_data_20_mhz ( mcp251863_t *ctx, uint8_t bit_time )
{
    err_t error_flag;
    mcp251863_dbt_cfg_t ci_dbt_cfg;
    mcp251863_tdc_cfg_t ci_tdc;
    uint32_t tdc_value = 0;

    ci_dbt_cfg.word = can_control_reset_values[ MCP251863_REG_CIDBTCFG / 4 ];
    ci_tdc.word = 0;

    ci_tdc.bf.tdc_mode = MCP251863_SSP_MODE_AUTO;

    switch ( bit_time ) 
    {
        case MCP251863_500K_1M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 14;
            ci_dbt_cfg.bf.tseg2 = 3;
            ci_dbt_cfg.bf.swj = 3;
            ci_tdc.bf.tdc_offset = 15;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_500K_2M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 6;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            ci_tdc.bf.tdc_offset = 7;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_500K_4M:
        case MCP251863_1000K_4M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 2;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            ci_tdc.bf.tdc_offset = 3;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_500K_5M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 1;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            ci_tdc.bf.tdc_offset = 2;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_500K_6M7:
        case MCP251863_500K_8M:
        case MCP251863_500K_10M:
        case MCP251863_1000K_8M:
        {
            return -1;
            break;
        }
        case MCP251863_250K_500K:
        case MCP251863_125K_500K:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 30;
            ci_dbt_cfg.bf.tseg2 = 7;
            ci_dbt_cfg.bf.swj = 7;
            ci_tdc.bf.tdc_offset = 31;
            ci_tdc.bf.tdc_value = tdc_value;
            ci_tdc.bf.tdc_mode = MCP251863_SSP_MODE_OFF;
            break;
        }
        case MCP251863_250K_833K:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 17;
            ci_dbt_cfg.bf.tseg2 = 4;
            ci_dbt_cfg.bf.swj = 4;
            ci_tdc.bf.tdc_offset = 18;
            ci_tdc.bf.tdc_value = tdc_value;
            ci_tdc.bf.tdc_mode = MCP251863_SSP_MODE_OFF;
            break;
        }
        case MCP251863_250K_1M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 14;
            ci_dbt_cfg.bf.tseg2 = 3;
            ci_dbt_cfg.bf.swj = 3;
            ci_tdc.bf.tdc_offset = 15;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_250K_1M5:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 8;
            ci_dbt_cfg.bf.tseg2 = 2;
            ci_dbt_cfg.bf.swj = 2;
            ci_tdc.bf.tdc_offset = 9;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_250K_2M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 6;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            ci_tdc.bf.tdc_offset = 7;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_250K_3M:
        {
            return -1;
            break;
        }
        case MCP251863_250K_4M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 2;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            ci_tdc.bf.tdc_offset = 3;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CIDBTCFG, ci_dbt_cfg.word);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

#ifdef REV_A
    ci_tdc.bf.tdc_offset = 0;
    ci_tdc.bf.tdc_value = 0;
#endif

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CITDC, ci_tdc.word);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -3;
    }

    return error_flag;
}

err_t mcp251863_bit_time_configure_nominal_10_mhz ( mcp251863_t *ctx, uint8_t bit_time )
{
    err_t error_flag;
    mcp251863_nbt_cfg_t ci_nbt_cfg;

    ci_nbt_cfg.word = can_control_reset_values[ MCP251863_REG_CINBTCFG / 4 ];

    switch ( bit_time ) 
    {
        case MCP251863_500K_1M:
        case MCP251863_500K_2M:
        case MCP251863_500K_4M:
        case MCP251863_500K_5M:
        case MCP251863_500K_6M7:
        case MCP251863_500K_8M:
        case MCP251863_500K_10M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 14;
            ci_nbt_cfg.bf.tseg2 = 3;
            ci_nbt_cfg.bf.swj = 3;
            break;
        }
        case MCP251863_250K_500K:
        case MCP251863_250K_833K:
        case MCP251863_250K_1M:
        case MCP251863_250K_1M5:
        case MCP251863_250K_2M:
        case MCP251863_250K_3M:
        case MCP251863_250K_4M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 30;
            ci_nbt_cfg.bf.tseg2 = 7;
            ci_nbt_cfg.bf.swj = 7;
            break;
        }
        case MCP251863_1000K_4M:
        case MCP251863_1000K_8M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 7;
            ci_nbt_cfg.bf.tseg2 = 2;
            ci_nbt_cfg.bf.swj = 2;
            break;
        }
        case MCP251863_125K_500K:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 62;
            ci_nbt_cfg.bf.tseg2 = 15;
            ci_nbt_cfg.bf.swj = 15;
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CINBTCFG, ci_nbt_cfg.word);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_bit_time_configure_data_10_mhz ( mcp251863_t *ctx, uint8_t bit_time )
{
    err_t error_flag;
    mcp251863_dbt_cfg_t ci_dbt_cfg;
    mcp251863_tdc_cfg_t ci_tdc;
    uint32_t tdc_value = 0;

    ci_dbt_cfg.word = can_control_reset_values[ MCP251863_REG_CIDBTCFG / 4 ];
    ci_tdc.word = 0;

    ci_tdc.bf.tdc_mode = MCP251863_SSP_MODE_AUTO;

    switch ( bit_time ) 
    {
        case MCP251863_500K_1M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 6;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            ci_tdc.bf.tdc_offset = 7;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_500K_2M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 2;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            ci_tdc.bf.tdc_offset = 3;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_500K_4M:
        case MCP251863_500K_5M:
        case MCP251863_500K_6M7:
        case MCP251863_500K_8M:
        case MCP251863_500K_10M:
        case MCP251863_1000K_4M:
        case MCP251863_1000K_8M:
            return -1;
            break;

        case MCP251863_250K_500K:
        case MCP251863_125K_500K:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 14;
            ci_dbt_cfg.bf.tseg2 = 3;
            ci_dbt_cfg.bf.swj = 3;
            ci_tdc.bf.tdc_offset = 15;
            ci_tdc.bf.tdc_value = tdc_value;
            ci_tdc.bf.tdc_mode = MCP251863_SSP_MODE_OFF;
            break;
        }
        case MCP251863_250K_833K:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 7;
            ci_dbt_cfg.bf.tseg2 = 2;
            ci_dbt_cfg.bf.swj = 2;
            ci_tdc.bf.tdc_offset = 8;
            ci_tdc.bf.tdc_value = tdc_value;
            ci_tdc.bf.tdc_mode = MCP251863_SSP_MODE_OFF;
            break;
        }
        case MCP251863_250K_1M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 6;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            ci_tdc.bf.tdc_offset = 7;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_250K_1M5:
        {
            return -1;
            break;
        }
        case MCP251863_250K_2M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 2;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            ci_tdc.bf.tdc_offset = 3;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP251863_250K_3M:
        case MCP251863_250K_4M:
        {
            return -1;
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CIDBTCFG, ci_dbt_cfg.word);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

#ifdef REV_A
    ci_tdc.bf.tdc_offset = 0;
    ci_tdc.bf.tdc_value = 0;
#endif

    error_flag = mcp251863_write_word ( ctx, MCP251863_REG_CITDC, ci_tdc.word);
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -3;
    }

    return error_flag;
}

err_t mcp251863_gpio_mode_configure ( mcp251863_t *ctx, uint8_t gpio0, uint8_t gpio1 )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_io_ctl_t iocon;

    address = MCP251863_REG_IOCON + 3;
    iocon.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &iocon.byte[ 3 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    iocon.bf.pin_mode0 = gpio0;
    iocon.bf.pin_mode1 = gpio1;

    error_flag = mcp251863_write_byte ( ctx, address, iocon.byte[ 3 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_gpio_direction_configure ( mcp251863_t *ctx, uint8_t gpio0, uint8_t gpio1 )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_io_ctl_t iocon;

    address = MCP251863_REG_IOCON;
    iocon.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &iocon.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    iocon.bf.tris0 = gpio0;
    iocon.bf.tris1 = gpio1;

    error_flag = mcp251863_write_byte ( ctx, address, iocon.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_gpio_standby_control_enable ( mcp251863_t *ctx )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_io_ctl_t iocon;

    address = MCP251863_REG_IOCON;
    iocon.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &iocon.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    iocon.bf.xcr_stby_enable = 1;

    error_flag = mcp251863_write_byte ( ctx, address, iocon.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_gpio_standby_control_disable ( mcp251863_t *ctx )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_io_ctl_t iocon;

    address = MCP251863_REG_IOCON;
    iocon.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &iocon.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    iocon.bf.xcr_stby_enable = 0;

    error_flag = mcp251863_write_byte ( ctx, address, iocon.byte[ 0 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_gpio_interrupt_pins_open_drain_configure ( mcp251863_t *ctx, uint8_t mode )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_io_ctl_t iocon;

    address = MCP251863_REG_IOCON + 3;
    iocon.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &iocon.byte[ 3 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    iocon.bf.int_pin_open_drain = mode;

    error_flag = mcp251863_write_byte ( ctx, address, iocon.byte[ 3 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_gpio_transmit_pin_open_drain_configure ( mcp251863_t *ctx, uint8_t mode )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_io_ctl_t iocon;

    address = MCP251863_REG_IOCON + 3;
    iocon.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &iocon.byte[ 3 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    iocon.bf.tx_can_open_drain = mode;

    error_flag = mcp251863_write_byte ( ctx, address, iocon.byte[ 3 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_gpio_pin_set ( mcp251863_t *ctx, uint8_t pos, uint8_t latch )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_io_ctl_t iocon;

    address = MCP251863_REG_IOCON + 1;
    iocon.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &iocon.byte[ 1 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    switch (pos ) 
    {
        case MCP251863_PIN_0:
        {
            iocon.bf.lat0 = latch;
            break;
        }
        case MCP251863_PIN_1:
        {
            iocon.bf.lat1 = latch;
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    error_flag = mcp251863_write_byte ( ctx, address, iocon.byte[ 1 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

err_t mcp251863_gpio_pin_read ( mcp251863_t *ctx, uint8_t pos, uint8_t *state )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_io_ctl_t iocon;

    address = MCP251863_REG_IOCON + 2;
    iocon.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &iocon.byte[ 2 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    switch (pos ) 
    {
        case MCP251863_PIN_0:
        {
            *state = ( uint8_t ) iocon.bf.gpio0;
            break;
        }
        case MCP251863_PIN_1:
        {
            *state = ( uint8_t ) iocon.bf.gpio1;
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    return error_flag;
}

err_t mcp251863_gpio_clock_output_configure ( mcp251863_t *ctx, int8_t mode )
{
    err_t error_flag;
    uint16_t address = 0;
    mcp251863_io_ctl_t iocon;

    address = MCP251863_REG_IOCON + 3;
    iocon.word = 0;

    error_flag = mcp251863_read_byte( ctx, address, &iocon.byte[ 3 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    iocon.bf.sof_output_enable = mode;

    error_flag = mcp251863_write_byte ( ctx, address, iocon.byte[ 3 ] );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -2;
    }

    return error_flag;
}

uint32_t mcp251863_dlc_to_data_bytes ( uint8_t dlc )
{
    uint32_t data_pointerbytes_in_object = 0;

    if ( dlc < MCP251863_DLC_12 )   
    {
        data_pointerbytes_in_object = dlc;
    } 
    else 
    {
        switch ( dlc ) 
        {
            case MCP251863_DLC_12:
            {
                data_pointerbytes_in_object = 12;
                break;
            }
            case MCP251863_DLC_16:
            {
                data_pointerbytes_in_object = 16;
                break;
            }
            case MCP251863_DLC_20:
            {
                data_pointerbytes_in_object = 20;
                break;
            }
            case MCP251863_DLC_24:
            {
                data_pointerbytes_in_object = 24;
                break;
            }
            case MCP251863_DLC_32:
            {
                data_pointerbytes_in_object = 32;
                break;
            }
            case MCP251863_DLC_48:
            {
                data_pointerbytes_in_object = 48;
                break;
            }
            case MCP251863_DLC_64:
            {
                data_pointerbytes_in_object = 64;
                break;
            }
            default:
            {
                break;
            }
        }
    }

    return data_pointerbytes_in_object;
}

err_t mcp251863_fifo_index_get ( mcp251863_t *ctx, uint8_t channel, uint8_t* data_out )
{
    err_t error_flag;
    uint16_t address = 0;

    uint8_t rx_data = 0;
    address = MCP251863_REG_CIFIFOSTA + ( channel * MCP251863_FIFO_OFFSET );
    address += 1; 

    error_flag = mcp251863_read_byte( ctx, address, &rx_data );
    if ( error_flag == MCP251863_ERROR ) 
    {
        return -1;
    }

    *data_out = rx_data & 0x1f;

    return error_flag;
}

uint16_t mcp251863_calculate_crc16 ( uint8_t *data_pointer, uint16_t size )
{
    uint16_t init = MCP251863_CRCBASE;
    uint8_t ctx;

    while ( size-- != 0 ) 
    {
        ctx = ( ( uint8_t* ) & init )[ MCP251863_CRCUPPER ] ^ *data_pointer++;
        init = ( init << 8 ) ^ crc16table[ ctx ];
    }

    return init;
}

uint8_t mcp251863_data_bytes_to_dlc ( uint8_t num )
{
    uint8_t dlc = MCP251863_DLC_0;

    if ( num <= 4 ) 
    {
        dlc = MCP251863_DLC_4;
    } 
    else if ( num <= 8 ) 
    {
        dlc = MCP251863_DLC_8;
    } 
    else if ( num <= 12 )   
    {
        dlc = MCP251863_DLC_12;
    } 
    else if ( num <= 16 ) 
    {
        dlc = MCP251863_DLC_16;
    } 
    else if ( num <= 20) 
    {
        dlc = MCP251863_DLC_20;
    } 
    else if ( num <= 24 ) 
    {
        dlc = MCP251863_DLC_24;
    } 
    else if ( num <= 32 )   {
        dlc = MCP251863_DLC_32;
    } 
    else if ( num <= 48 ) 
    {
        dlc = MCP251863_DLC_48;
    } 
    else if ( num <= 64 ) 
    {
        dlc = MCP251863_DLC_64;
    }

    return dlc;
}

// ------------------------------------------------------------------------- END
