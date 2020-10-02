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

#include "mcp2518fd.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MCP2518FD_DUMMY 0

// ------------------------------------------------------------------ CONSTANTS

// Reverse order of bits in byte
const uint8_t bit_reverse_table256[ 256 ] =
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

// Look-up table for CRC calculation 
const uint16_t crc16table[ 256 ] = 
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
    // Address 0x010 to 0x01C 
    0x00000000, 0x00000000, 0x40400040, 0x00000000,
    // Address 0x020 to 0x02C
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    // Address 0x030 to 0x03C
    0x00000000, 0x00200000, 0x00000000, 0x00000000,
    // Address 0x040 to 0x04C
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

#ifdef MCP2518FD

static uint32_t mcp2517_control_reset_values[ ] = 
{
    0x00000460, 0x00000003, 0x00000000, 0x00000000, 0x00000000
};

#endif

// ------------------------------------------------------------------ VARIABLES

// SPI Transmit buffer
uint8_t spi_transmit_buffer[ SPI_DEFAULT_BUFFER_LENGTH ];

// SPI Receive buffer
uint8_t spi_receive_buffer[ SPI_DEFAULT_BUFFER_LENGTH ];

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mcp2518fd_cfg_setup ( mcp2518fd_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    // Additional gpio pins

    cfg->stby    = HAL_PIN_NC;
    cfg->clko    = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

MCP2518FD_RETVAL mcp2518fd_init ( mcp2518fd_t *ctx, mcp2518fd_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = MCP2518FD_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return MCP2518FD_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, MCP2518FD_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->stby, cfg->stby );

    // Input pins

    digital_in_init( &ctx->clko, cfg->clko );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    ctx->glb_data.rx_flags = 0;
    ctx->glb_data.tx_id = TX_RESPONSE_ID;
    ctx->glb_data.selected_bit_time = MCP2518FD_500K_2M;

    return MCP2518FD_OK;
}

void mcp2518fd_default_cfg ( mcp2518fd_t *ctx )
{
    uint32_t osc_byte;
    mcp2518fd_config_t config_obj;

    config_obj.iso_crc_enable = ISO_CRC;
    config_obj.store_in_tef = 0;
    config_obj.tx_fifo_size = 8;
    config_obj.tx_pay_load_size = MCP2518FD_PLSIZE_8;
    config_obj.tx_priority = 1;
    config_obj.rx_fifo_size = 8;
    config_obj.rx_pay_load_size = MCP2518FD_PLSIZE_8;
    config_obj.standard_id = 0;
    config_obj.extended_id = 0;
    config_obj.fd_frame = 1;
    config_obj.switch_bit_rate = 1;
    config_obj.ide = 0;
    config_obj.remote_frame_req = 0;
    config_obj.seq = 1;

    // Reset device
    mcp2518fd_reset( ctx );
    Delay_100ms( );
    Delay_100ms( );
    
    mcp2518fd_operation_mode_select( ctx, MCP2518FD_CONFIG_MODE );
    Delay_100ms( );

    // Enable ECC and initialize RAM
    mcp2518fd_ecc_enable( ctx);
    mcp2518fd_ram_init( ctx, 0xFF );

    // Configure device
    mcp2518fd_configure_object_reset( &ctx->glb_data.config );
    ctx->glb_data.config.iso_crc_enable = config_obj.iso_crc_enable;
    ctx->glb_data.config.store_in_tef = config_obj.store_in_tef;
    mcp2518fd_configure( ctx, &ctx->glb_data.config );

    // Setup TX FIFO
    mcp2518fd_transmit_channel_configure_object_reset( &ctx->glb_data.tx_config );
    ctx->glb_data.tx_config.fifo_size = config_obj.tx_fifo_size;
    ctx->glb_data.tx_config.pay_load_size = config_obj.tx_pay_load_size;
    ctx->glb_data.tx_config.tx_priority = config_obj.tx_priority;
    mcp2518fd_transmit_channel_configure( ctx, MCP2518FD_FIFO_CH2, &ctx->glb_data.tx_config );

    // Setup RX FIFO
    mcp2518fd_receive_channel_configure_object_reset( &ctx->glb_data.rx_config );
    ctx->glb_data.rx_config.fifo_size = config_obj.rx_fifo_size;
    ctx->glb_data.rx_config.pay_load_size = config_obj.rx_pay_load_size;
    mcp2518fd_receive_channel_configure( ctx, MCP2518FD_FIFO_CH1, &ctx->glb_data.rx_config );

    // Setup RX Filter
    ctx->glb_data.f_obj.word = 0;
    ctx->glb_data.f_obj.bf.sid = 0xDA;
    ctx->glb_data.f_obj.bf.exide = 0;
    ctx->glb_data.f_obj.bf.eid = 0x00;
    mcp2518fd_filter_object_configure( ctx, MCP2518FD_FILT0, &ctx->glb_data.f_obj.bf );

    // Setup RX Mask
    ctx->glb_data.m_obj.word = 0;
    ctx->glb_data.m_obj.bf.msid = 0x0;
    ctx->glb_data.m_obj.bf.mide = 1;                                // Only allow standard IDs
    ctx->glb_data.m_obj.bf.meid = 0x0;
    mcp2518fd_filter_mask_configure( ctx, MCP2518FD_FILT0, &ctx->glb_data.m_obj.bf );

    // Link FIFO and Filter
    mcp2518fd_filter_to_fifo_link( ctx, MCP2518FD_FILT0, MCP2518FD_FIFO_CH1, true);

    // Setup Bit Time
    mcp2518fd_bit_time_configure( ctx, ctx->glb_data.selected_bit_time, MCP2518FD_SSP_MODE_AUTO, MCP2518FD_SYSCLK_40M );

    // Initialize ID and Control bits
    ctx->glb_data.tx_obj.word[ 0 ] = 0;
    ctx->glb_data.tx_obj.word[ 1 ] = 0;

    ctx->glb_data.tx_obj.bf.id.sid = config_obj.standard_id;        // Standard or Base ID
    ctx->glb_data.tx_obj.bf.id.eid = config_obj.extended_id;

    ctx->glb_data.tx_obj.bf.ctrl.fdf = config_obj.fd_frame;         // CAN FD frame
    ctx->glb_data.tx_obj.bf.ctrl.brs = config_obj.switch_bit_rate;  // Switch bit rate
    ctx->glb_data.tx_obj.bf.ctrl.ide = config_obj.ide;              // Standard frame
    ctx->glb_data.tx_obj.bf.ctrl.rtr = config_obj.remote_frame_req; // Not a remote frame request
    // Sequence: doesn't get transmitted, but will be stored in TEF
    ctx->glb_data.tx_obj.bf.ctrl.seq = config_obj.seq;

    // Setup Transmit and Receive Interrupts
    mcp2518fd_gpio_mode_configure( ctx, MCP2518FD_PINMODE_INT, MCP2518FD_PINMODE_INT );
    mcp2518fd_transmit_channel_event_enable( ctx, MCP2518FD_FIFO_CH2, MCP2518FD_TX_FIFO_NOT_FULL_EVENT );
    mcp2518fd_receive_channel_event_enable( ctx, MCP2518FD_FIFO_CH1, MCP2518FD_RX_FIFO_NOT_EMPTY_EVENT );
    mcp2518fd_module_event_enable( ctx, MCP2518FD_TX_EVENT | MCP2518FD_RX_EVENT );
    
    mcp2518fd_write_word( ctx, 0x1C, 0xFF1F0000 );
    mcp2518fd_read_word( ctx, MCP2518FD_REG_OSC, &osc_byte );
    osc_byte &= 0x000000F3;
    //  osc_byte |= MCP2518FD_LOW_POWER_MODE_EN;
    mcp2518fd_write_word( ctx, MCP2518FD_REG_OSC, osc_byte );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );

    // Select Normal Mode
    mcp2518fd_operation_mode_select( ctx, MCP2518FD_NORMAL_MODE );
    Delay_1sec( );
}

void mcp2518fd_generic_transfer ( mcp2518fd_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );    
}

void mcp2518fd_set_cs ( mcp2518fd_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->int_pin, state );
}

void mcp2518fd_transmit_message ( mcp2518fd_t *ctx, uint8_t num_data_bytes, uint8_t *transmit_flag, uint8_t *data_in )
{
    uint8_t n;
    uint8_t attempts = MAX_TXQUEUE_ATTEMPTS;

    ctx->glb_data.tx_obj.bf.ctrl.dlc = num_data_bytes;  // number of data bytes

    // Check if FIFO is not full
    do
    {
       mcp2518fd_transmit_channel_event_get( ctx, MCP2518FD_FIFO_CH2, &ctx->glb_data.tx_flags );

        if ( attempts == 0 )
        {
            asm nop;
            asm nop;
            mcp2518fd_error_count_state_get( ctx, &ctx->glb_data.tec, &ctx->glb_data.rec, &ctx->glb_data.error_flags );
            *transmit_flag = 0;
            return;
        }
        attempts--;
    }
    while ( ! ( ctx->glb_data.tx_flags & MCP2518FD_TX_FIFO_NOT_FULL_EVENT ) );

    // Load message and transmit
    n = mcp2518fd_dlc_to_data_bytes( ctx->glb_data.tx_obj.bf.ctrl.dlc );
    ctx->func_data.txd = data_in;
    ctx->func_data.txd_num_bytes = n;

    mcp2518fd_transmit_channel_load( ctx, MCP2518FD_FIFO_CH2, &ctx->glb_data.tx_obj, true );
    *transmit_flag = 1;
}

void mcp2518fd_receive_message ( mcp2518fd_t *ctx, uint8_t *receive_flag, uint8_t *data_out )
{
    uint16_t rcv_length;

    // Check if FIFO is not empty
    mcp2518fd_receive_channel_event_get( ctx, MCP2518FD_FIFO_CH1, &ctx->glb_data.rx_flags );

    if ( ctx->glb_data.rx_flags & MCP2518FD_RX_FIFO_NOT_EMPTY_EVENT )
    {
        // Get message
        ctx->func_data.rxd = data_out;
        ctx->func_data.n_bytes = MAX_DATA_BYTES;
        mcp2518fd_receive_message_get( ctx, MCP2518FD_FIFO_CH1, &ctx->glb_data.rx_obj );
    }
    else
    {
        *receive_flag = 0;
        return;
    }

    rcv_length = ctx->glb_data.rx_obj.bf.ctrl.dlc;
    data_out[ rcv_length ] = '\0';
    *receive_flag = 1;
}

int8_t mcp2518fd_reset ( mcp2518fd_t *ctx )
{
    uint16_t spi_transfer_size = 2;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( MCP2518FD_INS_RESET << 4 );
    spi_transmit_buffer[ 1 ] = 0;

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, 1, spi_receive_buffer, spi_transfer_size );

    return spi_transfer_error;
}

int8_t mcp2518fd_read_byte ( mcp2518fd_t *ctx, uint16_t address, uint8_t *rxd )
{
    uint16_t spi_transfer_size = 3;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP2518FD_INS_READ << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );
    spi_transmit_buffer[ 2 ] = 0;

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, 2, spi_receive_buffer, spi_transfer_size );

    // Update data
    *rxd = spi_receive_buffer[ 2 ];

    return spi_transfer_error;
}

int8_t mcp2518fd_write_byte ( mcp2518fd_t *ctx, uint16_t address, uint8_t txd )
{
    uint16_t spi_transfer_size = 3;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP2518FD_INS_WRITE << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );
    spi_transmit_buffer[ 2 ] = txd;

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, 3, spi_receive_buffer, spi_transfer_size );

    return spi_transfer_error;
}

int8_t mcp2518fd_read_word ( mcp2518fd_t *ctx, uint16_t address, uint32_t *rxd )
{
    uint8_t i;
    uint32_t x;
    uint16_t spi_transfer_size = 6;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP2518FD_INS_READ << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, 2, spi_receive_buffer, spi_transfer_size );

    if ( spi_transfer_error ) 
    {
        return spi_transfer_error;
    }

    // Update data
    *rxd = 0;
    for ( i = 2; i < 6; i++ ) 
    {
        x = ( uint32_t ) spi_receive_buffer[ i ];
        *rxd += x << ( ( i - 2 ) * 8 );
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_write_word ( mcp2518fd_t *ctx, uint16_t address, uint32_t txd )
{
    uint8_t i;
    uint16_t spi_transfer_size = 6;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP2518FD_INS_WRITE << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    // Split word into 4 bytes and add them to buffer
    for ( i = 0; i < 4; i++ ) 
    {
        spi_transmit_buffer[ i + 2 ] = ( uint8_t ) ( ( txd >> ( i * 8 ) ) & 0xFF );
    }

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, 2, spi_receive_buffer, spi_transfer_size );

    return spi_transfer_error;
}

int8_t mcp2518fd_read_half_word ( mcp2518fd_t *ctx, uint16_t address, uint16_t *rxd )
{
    uint8_t i;
    uint32_t x;
    uint16_t spi_transfer_size = 4;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP2518FD_INS_READ << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, 2, spi_receive_buffer, spi_transfer_size );

    if ( spi_transfer_error ) 
    {
        return spi_transfer_error;
    }

    // Update data
    *rxd = 0;
    for ( i = 2; i < 4; i++ ) 
    {
        x = ( uint32_t ) spi_receive_buffer[ i ];
        *rxd += x << ( ( i - 2 ) * 8 );
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_write_half_word ( mcp2518fd_t *ctx, uint16_t address, uint16_t txd )
{
    uint8_t i;
    uint16_t spi_transfer_size = 4;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP2518FD_INS_WRITE << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    // Split word into 2 bytes and add them to buffer
    for ( i = 0; i < 2; i++ ) 
    {
        spi_transmit_buffer[ i + 2 ] = ( uint8_t ) ( ( txd >> ( i * 8 ) ) & 0xFF );
    }

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, 2, spi_receive_buffer, spi_transfer_size );

    return spi_transfer_error;
}

int8_t mcp2518fd_write_byte_safe ( mcp2518fd_t *ctx, uint16_t address, uint8_t txd )
{
    uint16_t crc_result = 0;
    uint16_t spi_transfer_size = 5;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP2518FD_INS_WRITE_SAFE << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );
    spi_transmit_buffer[ 2 ] = txd;

    // Add CRC
    crc_result = mcp2518fd_calculate_crc16( spi_transmit_buffer, 3 );
    spi_transmit_buffer[ 3 ] = ( crc_result >> 8 ) & 0xFF;
    spi_transmit_buffer[ 4 ] = crc_result & 0xFF;

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, 5, spi_receive_buffer, spi_transfer_size );

    return spi_transfer_error;
}

int8_t mcp2518fd_write_word_safe ( mcp2518fd_t *ctx, uint16_t address, uint32_t txd )
{
    uint8_t i;
    uint16_t crc_result = 0;
    uint16_t spi_transfer_size = 8;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP2518FD_INS_WRITE_SAFE << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    // Split word into 4 bytes and add them to buffer
    for ( i = 0; i < 4; i++ ) 
    {
        spi_transmit_buffer[ i + 2 ] = ( uint8_t ) ( ( txd >> ( i * 8 ) ) & 0xFF );
    }

    // Add CRC
    crc_result = mcp2518fd_calculate_crc16( spi_transmit_buffer, 6 );
    spi_transmit_buffer[ 6 ] = ( crc_result >> 8 ) & 0xFF;
    spi_transmit_buffer[ 7 ] = crc_result & 0xFF;

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, 8, spi_receive_buffer, spi_transfer_size );

    return spi_transfer_error;
}

int8_t mcp2518fd_read_byte_array ( mcp2518fd_t *ctx, uint16_t address, uint8_t *rxd, uint16_t n_bytes )
{
    uint16_t i;
    uint16_t spi_transfer_size = n_bytes + 2;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP2518FD_INS_READ << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    // Clear data_pointer
    for ( i = 2; i < spi_transfer_size; i++ ) 
    {
        spi_transmit_buffer[ i ] = 0;
    }

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, spi_transfer_size, spi_receive_buffer, spi_transfer_size );

    // Update data
    for ( i = 0; i < n_bytes; i++ ) 
    {
        rxd[ i ] = spi_receive_buffer[ i + 2 ];
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_read_byte_array_with_crc ( mcp2518fd_t *ctx, bool from_ram, bool *crc_is_correct )
{
    uint8_t i;
    uint16_t crc_from_spi_slave = 0;
    uint16_t crc_at_controller = 0;
    uint16_t spi_transfer_size = ctx->func_data.n_bytes + 5; //first two bytes for sending command & address, third for size, last two bytes for CRC
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP2518FD_INS_READ_CRC << 4 ) + ( ( ctx->func_data.address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( ctx->func_data.address & 0xFF );
    if ( from_ram ) 
    {
        spi_transmit_buffer[ 2 ] = ctx->func_data.n_bytes >> 2;
    } 
    else 
    {
        spi_transmit_buffer[ 2 ] = ctx->func_data.n_bytes;
    }

    // Clear data_pointer
    for ( i = 3; i < spi_transfer_size; i++ ) 
    {
        spi_transmit_buffer[ i ] = 0;
    }

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, spi_transfer_size, spi_receive_buffer, spi_transfer_size );

    if ( spi_transfer_error ) 
    {
        return spi_transfer_error;
    }

    // Get CRC from controller
    crc_from_spi_slave = ( uint16_t ) ( spi_receive_buffer[ spi_transfer_size - 2 ] << 8 ) + ( uint16_t ) ( spi_receive_buffer[ spi_transfer_size - 1 ] );

    // Use the receive buffer to calculate CRC
    // First three bytes need to be command
    spi_receive_buffer[ 0 ] = spi_transmit_buffer[ 0 ];
    spi_receive_buffer[ 1 ] = spi_transmit_buffer[ 1 ];
    spi_receive_buffer[ 2 ] = spi_transmit_buffer[ 2 ];
    crc_at_controller = mcp2518fd_calculate_crc16( spi_receive_buffer, ctx->func_data.n_bytes + 3 );

    // Compare CRC readings
    if ( crc_from_spi_slave == crc_at_controller ) 
    {
        *crc_is_correct = true;
    } 
    else 
    {
        *crc_is_correct = false;
    }

    // Update data
    for ( i = 0; i < ctx->func_data.n_bytes; i++ ) 
    {
        ctx->func_data.rxd[ i ] = spi_receive_buffer[ i + 3 ];
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_write_byte_array ( mcp2518fd_t *ctx, uint16_t address, uint8_t *txd, uint16_t n_bytes )
{
    uint16_t i;
    uint16_t spi_transfer_size = n_bytes + 2;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP2518FD_INS_WRITE << 4 ) + ( ( address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    // Add data_pointer
    for ( i = 2; i < spi_transfer_size; i++ ) 
    {
        spi_transmit_buffer[ i ] = txd[ i - 2 ];
    }

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, spi_transfer_size, spi_receive_buffer, spi_transfer_size );

    return spi_transfer_error;
}

int8_t mcp2518fd_write_byte_array_with_crc ( mcp2518fd_t *ctx, bool from_ram )
{
    uint16_t i;
    uint16_t crc_result = 0;
    uint16_t spi_transfer_size = ctx->func_data.n_bytes + 5;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( uint8_t ) ( ( MCP2518FD_INS_WRITE_CRC << 4 ) + ( ( ctx->func_data.address >> 8 ) & 0xF ) );
    spi_transmit_buffer[ 1 ] = ( uint8_t ) ( ctx->func_data.address & 0xFF );
    if ( from_ram ) 
    {
        spi_transmit_buffer[ 2 ] = ctx->func_data.n_bytes >> 2;
    } 
    else 
    {
        spi_transmit_buffer[ 2 ] = ctx->func_data.n_bytes;
    }

    // Add data_pointer
    for ( i = 0; i < ctx->func_data.n_bytes; i++ ) 
    {
        spi_transmit_buffer[ i + 3 ] = ctx->func_data.txd[ i ];
    }

    // Add CRC
    crc_result = mcp2518fd_calculate_crc16( spi_transmit_buffer, spi_transfer_size - 2 ); 
    spi_transmit_buffer[ spi_transfer_size - 2 ]  = ( uint8_t ) ( ( crc_result >> 8 ) & 0xFF );
    spi_transmit_buffer[ spi_transfer_size - 1 ]  = ( uint8_t ) ( crc_result & 0xFF );

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, spi_transfer_size, spi_receive_buffer, spi_transfer_size );

    return spi_transfer_error;
}

int8_t mcp2518fd_read_word_array ( mcp2518fd_t *ctx, uint16_t address, uint32_t *rxd, uint16_t n_words )
{
    uint16_t i, j, n;
    mcp2518fd_reg_t w;
    uint16_t spi_transfer_size = n_words * 4 + 2;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( MCP2518FD_INS_READ << 4 ) + ( ( address >> 8 ) & 0xF );
    spi_transmit_buffer[ 1 ] = address & 0xFF;

    // Clear data_pointer
    for ( i = 2; i < spi_transfer_size; i++ ) 
    {
        spi_transmit_buffer[ i ] = 0;
    }

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, spi_transfer_size, spi_receive_buffer, spi_transfer_size );

    if ( spi_transfer_error ) 
    {
        return spi_transfer_error;
    }

    // Convert Byte array to Word array
    n = 2;
    for ( i = 0; i < n_words; i++ ) 
    {
        w.word = 0;
        for ( j = 0; j < 4; j++, n++ ) 
        {
            w.byte[ j ] = spi_receive_buffer[ n ];
        }
        rxd[ i ] = w.word;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_write_word_array ( mcp2518fd_t *ctx, uint16_t address, uint32_t *txd, uint16_t n_words )
{
    uint16_t i, j, n;
    mcp2518fd_reg_t w;
    uint16_t spi_transfer_size = n_words * 4 + 2;
    int8_t spi_transfer_error = 0;

    // Compose command
    spi_transmit_buffer[ 0 ] = ( MCP2518FD_INS_WRITE << 4 ) + ( ( address >> 8 ) & 0xF );
    spi_transmit_buffer[ 1 ] = address & 0xFF;

    // Convert ByteArray to word array
    n = 2;
    for ( i = 0; i < n_words; i++ ) 
    {
        w.word = txd[ i ];
        for ( j = 0; j < 4; j++, n++ ) 
        {
            spi_transmit_buffer[ n ] = w.byte[ j ];
        }
    }

    mcp2518fd_generic_transfer ( ctx, spi_transmit_buffer, spi_transfer_size, spi_receive_buffer, spi_transfer_size );

    return spi_transfer_error;
}

// *****************************************************************************
// Section: Configuration

int8_t mcp2518fd_configure ( mcp2518fd_t *ctx, mcp2518fd_can_cfg_t *config )
{
    mcp2518fd_ctl_t ci_Con;
    int8_t spi_transfer_error = 0;

    ci_Con.word = can_control_reset_values[ MCP2518FD_REG_CiCON / 4 ];

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

    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiCON, ci_Con.word );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_configure_object_reset ( mcp2518fd_can_cfg_t *config )
{
    mcp2518fd_ctl_t ci_Con;
    ci_Con.word = can_control_reset_values[ MCP2518FD_REG_CiCON / 4 ];

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

    return 0;
}

// *****************************************************************************
// Section: Operating mode

int8_t mcp2518fd_operation_mode_select ( mcp2518fd_t *ctx, uint8_t op_mode )
{
    uint8_t d = 0;
    int8_t spi_transfer_error = 0;

    // Read
    spi_transfer_error = mcp2518fd_read_byte( ctx, MCP2518FD_REG_CiCON + 3, &d );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    d &= ~0x07;
    d |= op_mode;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, MCP2518FD_REG_CiCON + 3, d );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

uint8_t mcp2518fd_operation_mode_get ( mcp2518fd_t *ctx )
{
    uint8_t d = 0;
    uint8_t mode = MCP2518FD_INVALID_MODE;
    int8_t spi_transfer_error = 0;

    // Read Op_mode
    spi_transfer_error = mcp2518fd_read_byte( ctx, MCP2518FD_REG_CiCON + 2, &d );
    if ( spi_transfer_error ) 
    {
        return MCP2518FD_INVALID_MODE;
    }

    // Get Op_mode bits
    d = ( d >> 5 ) & 0x7;

    // Decode Op_mode
    switch ( d ) 
    {
        case MCP2518FD_NORMAL_MODE:
        {
            mode = MCP2518FD_NORMAL_MODE;
            break;
        }
        case MCP2518FD_SLEEP_MODE:
        {
            mode = MCP2518FD_SLEEP_MODE;
            break;
        }
        case MCP2518FD_INT_LOOP_MODE:
        {
            mode = MCP2518FD_INT_LOOP_MODE;
            break;
        }
        case MCP2518FD_EXT_LOOP_MODE:
        {
            mode = MCP2518FD_EXT_LOOP_MODE;
            break;
        }
        case MCP2518FD_LISTEN_ONLY_MODE:
        {
            mode = MCP2518FD_LISTEN_ONLY_MODE;
            break;
        }
        case MCP2518FD_CONFIG_MODE:
        {
            mode = MCP2518FD_CONFIG_MODE;
            break;
        }
        case MCP2518FD_CLASSIC_MODE:
        {
            mode = MCP2518FD_CLASSIC_MODE;
            break;
        }
        case MCP2518FD_RESTRICT_MODE:
        {
            mode = MCP2518FD_RESTRICT_MODE;
            break;
        }
        default:
        {
            mode = MCP2518FD_INVALID_MODE;
            break;
        }
    }

    return mode;
}

// *****************************************************************************
// Section: CAN Transmit

int8_t mcp2518fd_transmit_channel_configure ( mcp2518fd_t *ctx, uint8_t channel, mcp2518fd_tx_fifo_cfg_t *config )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;

    // Setup FIFO
    mcp2518fd_fifo_ctl_t ci_fifo_con;
    ci_fifo_con.word = can_control_reset_values[ MCP2518FD_REG_CiFIFOCON  / 4 ];
    ci_fifo_con.tx_bf.tx_enable = 1;
    ci_fifo_con.tx_bf.fifo_size = config->fifo_size;
    ci_fifo_con.tx_bf.pay_load_size = config->pay_load_size;
    ci_fifo_con.tx_bf.tx_attempts = config->tx_attempts;
    ci_fifo_con.tx_bf.tx_priority = config->tx_priority;
    ci_fifo_con.tx_bf.rtr_enable = config->rtr_enable;

    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET );

    spi_transfer_error = mcp2518fd_write_word( ctx, a, ci_fifo_con.word );

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_channel_configure_object_reset ( mcp2518fd_tx_fifo_cfg_t *config )
{
    mcp2518fd_fifo_ctl_t ci_fifo_con;
    ci_fifo_con.word = can_control_reset_values[ MCP2518FD_REG_CiFIFOCON  / 4 ];

    config->rtr_enable = ci_fifo_con.tx_bf.rtr_enable;
    config->tx_priority = ci_fifo_con.tx_bf.tx_priority;
    config->tx_attempts = ci_fifo_con.tx_bf.tx_attempts;
    config->fifo_size = ci_fifo_con.tx_bf.fifo_size;
    config->pay_load_size = ci_fifo_con.tx_bf.pay_load_size;

    return 0;
}

int8_t mcp2518fd_transmit_queue_configure ( mcp2518fd_t *ctx, mcp2518fd_tx_que_cfg_t *config )
{
#ifndef CAN_TXQUEUE_IMPLEMENTED
    config;
    return -100;
#else
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;

    // Setup FIFO
   mcp2518fd_tx_que_ctl_t ci_fifo_con;
    ci_fifo_con.word = can_control_reset_values[ MCP2518FD_REG_CiFIFOCON  / 4 ];

    ci_fifo_con.tx_bf.tx_enable = 1;
    ci_fifo_con.tx_bf.fifo_size = config->fifo_size;
    ci_fifo_con.tx_bf.pay_load_size = config->pay_load_size;
    ci_fifo_con.tx_bf.tx_attempts = config->tx_attempts;
    ci_fifo_con.tx_bf.tx_priority = config->tx_priority;

    a = MCP2518FD_REG_CiTXQCON;
    spi_transfer_error = mcp2518fd_write_word ( ctx, a, ci_fifo_con.word );

    return spi_transfer_error;

#endif
}

int8_t mcp2518fd_transmit_queue_configure_object_reset ( mcp2518fd_tx_que_cfg_t *config )
{
    mcp2518fd_fifo_ctl_t ci_fifo_con;
    ci_fifo_con.word = can_control_reset_values[ MCP2518FD_REG_CiFIFOCON  / 4 ];

    config->tx_priority = ci_fifo_con.tx_bf.tx_priority;
    config->tx_attempts = ci_fifo_con.tx_bf.tx_attempts;
    config->fifo_size = ci_fifo_con.tx_bf.fifo_size;
    config->pay_load_size = ci_fifo_con.tx_bf.pay_load_size;

    return 0;
}

int8_t mcp2518fd_transmit_channel_load ( mcp2518fd_t *ctx, uint8_t channel, mcp2518fd_tx_msg_obj_t *tx_obj, bool flush )
{
    uint16_t n = 0;
    uint8_t j = 0;
    uint8_t i;
    uint8_t tx_buffer[ MAX_MSG_SIZE ];
    uint16_t a;
    uint32_t fifo_reg[ 3 ];
    uint32_t data_pointerbytes_in_object;
    mcp2518fd_fifo_ctl_t ci_fifo_con;
    mcp2518fd_fifo_stat_t ci_fifo_sta;
    mcp2518fd_fifo_user_cfg_t ci_fifo_ua;
    int8_t spi_transfer_error = 0;

    // Get FIFO registers
    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET );

    spi_transfer_error = mcp2518fd_read_word_array( ctx, a, fifo_reg, 3 );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Check that it is a transmit buffer
    ci_fifo_con.word = fifo_reg[ 0 ];
    if ( !ci_fifo_con.tx_bf.tx_enable ) 
    {
        return -2;
    }

    // Check that dlc is big enough for data_pointer
    data_pointerbytes_in_object = mcp2518fd_dlc_to_data_bytes( (  uint8_t ) tx_obj->bf.ctrl.dlc );
    if ( data_pointerbytes_in_object < ctx->func_data.txd_num_bytes ) 
    {
        return -3;
    }

    // Get status
    ci_fifo_sta.word = fifo_reg[ 1 ];

    // Get address
    ci_fifo_ua.word = fifo_reg[ 2 ];
#ifdef USERADDRESS_TIMES_FOUR
    a = 4 * ci_fifo_ua.bf.user_address;
#else
    a = ci_fifo_ua.bf.user_address;
#endif
    a += MCP2518FD_RAMADDR_START;

    tx_buffer[ 0 ] = tx_obj->byte[ 0 ]; //not using 'for' to reduce no of instructions
    tx_buffer[ 1 ] = tx_obj->byte[ 1 ];
    tx_buffer[ 2 ] = tx_obj->byte[ 2 ];
    tx_buffer[ 3 ] = tx_obj->byte[ 3 ];

    tx_buffer[ 4 ] = tx_obj->byte[ 4 ];
    tx_buffer[ 5 ] = tx_obj->byte[ 5 ];
    tx_buffer[ 6 ] = tx_obj->byte[ 6 ];
    tx_buffer[ 7 ] = tx_obj->byte[ 7 ];

    for ( i = 0; i < ctx->func_data.txd_num_bytes; i++ ) 
    {
        tx_buffer[ i + 8 ] = ctx->func_data.txd[ i ];
    }

    // Make sure we write a multiple of 4 bytes to RAM

    if ( ctx->func_data.txd_num_bytes % 4 ) 
    {
        // Need to add bytes
        n = 4 - ( ctx->func_data.txd_num_bytes % 4 );
        i = ctx->func_data.txd_num_bytes + 8;

        for ( j = 0; j < n; j++ ) 
        {
            tx_buffer[ i + 8 + j ] = 0;
        }
    }

    spi_transfer_error = mcp2518fd_write_byte_array( ctx, a, tx_buffer, ctx->func_data.txd_num_bytes + 8 + n );
    if ( spi_transfer_error ) 
    {
        return -4;
    }

    // Set UINC and TXREQ
    spi_transfer_error = mcp2518fd_transmit_channel_update( ctx, channel, flush );
    if ( spi_transfer_error ) 
    {
        return -5;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_channel_flush ( mcp2518fd_t *ctx, uint8_t channel )
{
    uint8_t d = 0;
    uint16_t a = 0;
    int8_t spi_transfer_error = 0;

    // Address of TXREQ
    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET );
    a += 1;

    // Set TXREQ
    d = 0x02;

    // Write
    spi_transfer_error = mcp2518fd_write_byte( ctx, a, d );

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_channel_status_get ( mcp2518fd_t *ctx, uint8_t channel, uint16_t *status )
{
    uint16_t a = 0;
    uint32_t sta = 0;
    uint32_t fifo_reg[ 2 ];
    mcp2518fd_fifo_stat_t ci_fifo_sta;
    mcp2518fd_fifo_ctl_t ci_fifo_con;
    int8_t spi_transfer_error = 0;

    // Get FIFO registers
    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET );

    spi_transfer_error = mcp2518fd_read_word_array( ctx, a, fifo_reg, 2 ); 
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    ci_fifo_con.word = fifo_reg[ 0 ];
    ci_fifo_sta.word = fifo_reg[ 1 ];

    // Update status
    sta = ci_fifo_sta.byte[ 0 ];

    if ( ci_fifo_con.tx_bf.tx_request ) 
    {
        sta |= MCP2518FD_TX_FIFO_TRANSMITTING;
    }

    *status = ( uint16_t ) ( sta & MCP2518FD_TX_FIFO_STATUS_MASK );

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_channel_reset ( mcp2518fd_t *ctx, uint8_t channel )
{
    return mcp2518fd_receive_channel_reset( ctx, channel );
}

int8_t mcp2518fd_transmit_channel_update ( mcp2518fd_t *ctx, uint8_t channel, bool flush )
{
    uint16_t a;
    mcp2518fd_fifo_ctl_t ci_fifo_con;
    int8_t spi_transfer_error = 0;

    // Set UINC
    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET ) + 1; // Byte that contains FRESET
    ci_fifo_con.word = 0;
    ci_fifo_con.tx_bf.uinc = 1;

    // Set TXREQ
    if ( flush ) 
    {
        ci_fifo_con.tx_bf.tx_request = 1;
    }

    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_fifo_con.byte[ 1 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_request_set ( mcp2518fd_t *ctx, uint32_t tx_req )
{
    int8_t spi_transfer_error = 0;

    // Write TXREQ register
    uint32_t w = tx_req;

    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiTXREQ, w );

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_request_get ( mcp2518fd_t *ctx, uint32_t* tx_req )
{
    int8_t spi_transfer_error = 0;

    spi_transfer_error = mcp2518fd_read_word( ctx, MCP2518FD_REG_CiTXREQ, tx_req );

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_channel_abort ( mcp2518fd_t *ctx, uint8_t channel )
{
    uint16_t a;
    uint8_t d;
    int8_t spi_transfer_error = 0;

    // Address
    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET );
    a += 1; // byte address of TXREQ

    // Clear TXREQ
    d = 0x00;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, d );

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_abort_all ( mcp2518fd_t *ctx)
{
    uint8_t d;
    int8_t spi_transfer_error = 0;

    // Read Ci_CON byte 3
    spi_transfer_error = mcp2518fd_read_byte( ctx, ( MCP2518FD_REG_CiCON + 3 ), &d );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    d |= 0x8;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, ( MCP2518FD_REG_CiCON + 3 ), d );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_band_width_sharing_set ( mcp2518fd_t *ctx, uint8_t tx_bws )
{
    uint8_t d = 0;
    int8_t spi_transfer_error = 0;

    // Read Ci_CON byte 3
    spi_transfer_error = mcp2518fd_read_byte( ctx, ( MCP2518FD_REG_CiCON + 3 ), &d );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    d &= 0x0f;
    d |= ( tx_bws << 4 );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, ( MCP2518FD_REG_CiCON + 3 ), d );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}


// *****************************************************************************
// Section: CAN Receive

int8_t mcp2518fd_filter_object_configure ( mcp2518fd_t *ctx, uint8_t filter, mcp2518fd_filt_obj_id_t *id )
{
    uint16_t a;
    mcp2518fd_filt_obj_t f_obj;
    int8_t spi_transfer_error = 0;

    // Setup
    f_obj.word = 0;
    f_obj.bf = *id;
    a = MCP2518FD_REG_CiFLTOBJ + ( filter * MCP2518FD_FILTER_OFFSET );

    spi_transfer_error = mcp2518fd_write_word ( ctx, a, f_obj.word );

    return spi_transfer_error;
}

int8_t mcp2518fd_filter_mask_configure ( mcp2518fd_t *ctx, uint8_t filter, mcp2518fd_mask_obj_id_t *mask )
{
    uint16_t a;
    mcp2518fd_mask_obj_t m_obj;
    int8_t spi_transfer_error = 0;

    // Setup
    m_obj.word = 0;
    m_obj.bf = *mask;
    a = MCP2518FD_REG_CiMASK + ( filter * MCP2518FD_FILTER_OFFSET );

    spi_transfer_error = mcp2518fd_write_word ( ctx, a, m_obj.word );

    return spi_transfer_error;
}

int8_t mcp2518fd_filter_to_fifo_link ( mcp2518fd_t *ctx, uint8_t filter, uint8_t channel, bool enable )
{
    uint16_t a;
    mcp2518fd_filt_ctl_t f_ctrl;
    int8_t spi_transfer_error = 0;

    // Enable
    if ( enable ) 
    {
        f_ctrl.bf.enable = 1;
    } 
    else 
    {
        f_ctrl.bf.enable = 0;
    }

    // Link
    f_ctrl.bf.buffer_pointer = channel;
    a = MCP2518FD_REG_CiFLTCON + filter;

    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, f_ctrl.byte );

    return spi_transfer_error;
}

int8_t mcp2518fd_filter_enable ( mcp2518fd_t *ctx, uint8_t filter )
{
    uint16_t a;
    mcp2518fd_filt_ctl_t f_ctrl;
    int8_t spi_transfer_error = 0;

    // Read
    a = MCP2518FD_REG_CiFLTCON + filter;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &f_ctrl.byte );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    f_ctrl.bf.enable = 1;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, f_ctrl.byte );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_filter_disable ( mcp2518fd_t *ctx, uint8_t filter )
{
    uint16_t a;
    mcp2518fd_filt_ctl_t f_ctrl;
    int8_t spi_transfer_error = 0;

    // Read
    a = MCP2518FD_REG_CiFLTCON + filter;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &f_ctrl.byte );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    f_ctrl.bf.enable = 0;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, f_ctrl.byte );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_device_net_filter_count_set ( mcp2518fd_t *ctx, uint8_t dnfc )
{
    uint8_t d = 0;
    int8_t spi_transfer_error = 0;

    // Read Ci_CON byte 0
    spi_transfer_error = mcp2518fd_read_byte( ctx, MCP2518FD_REG_CiCON, &d );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    d &= 0x1f;
    d |= dnfc;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, MCP2518FD_REG_CiCON, d );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_receive_channel_configure ( mcp2518fd_t *ctx, uint8_t channel, mcp2518fd_rx_fifo_cfg_t *config )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_fifo_ctl_t ci_fifo_con;

#ifdef CAN_TXQUEUE_IMPLEMENTED
    if ( channel == CAN_TXQUEUE_CH0 ) 
    {
        return -100;
    }
#endif

    // Setup FIFO
    ci_fifo_con.word = can_control_reset_values[ MCP2518FD_REG_CiFIFOCON  / 4 ];

    ci_fifo_con.rx_bf.tx_enable = 0;
    ci_fifo_con.rx_bf.fifo_size = config->fifo_size;
    ci_fifo_con.rx_bf.pay_load_size = config->pay_load_size;
    ci_fifo_con.rx_bf.rx_time_stamp_enable = config->rx_time_stamp_enable;

    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET );

    spi_transfer_error = mcp2518fd_write_word ( ctx, a, ci_fifo_con.word );

    return spi_transfer_error;
}

int8_t mcp2518fd_receive_channel_configure_object_reset ( mcp2518fd_rx_fifo_cfg_t *config )
{
    mcp2518fd_fifo_ctl_t ci_fifo_con;
    ci_fifo_con.word = can_control_reset_values[ MCP2518FD_REG_CiFIFOCON  / 4 ];

    config->fifo_size = ci_fifo_con.rx_bf.fifo_size;
    config->pay_load_size = ci_fifo_con.rx_bf.pay_load_size;
    config->rx_time_stamp_enable = ci_fifo_con.rx_bf.rx_time_stamp_enable;

    return 0;
}

int8_t mcp2518fd_receive_channel_status_get ( mcp2518fd_t *ctx, uint8_t channel, uint8_t *status )
{
    uint16_t a;
    mcp2518fd_fifo_stat_t ci_fifo_sta;
    int8_t spi_transfer_error = 0;

    // Read
    ci_fifo_sta.word = 0;
    a = MCP2518FD_REG_CiFIFOSTA + ( channel * MCP2518FD_FIFO_OFFSET );

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_fifo_sta.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *status = ( uint8_t ) ( ci_fifo_sta.byte[ 0 ] & 0x0F );

    return spi_transfer_error;
}

int8_t mcp2518fd_receive_message_get ( mcp2518fd_t *ctx, uint8_t channel, mcp2518fd_rx_msg_obj_t* rx_obj )
{
    uint8_t n = 0;
    uint8_t i = 0;
    uint16_t a;
    uint8_t ba[ MAX_MSG_SIZE ];
    uint32_t fifo_reg[ 3 ];
    mcp2518fd_fifo_ctl_t ci_fifo_con;
    mcp2518fd_fifo_stat_t ci_fifo_sta;
    mcp2518fd_fifo_user_cfg_t ci_fifo_ua;
    int8_t spi_transfer_error = 0;
    mcp2518fd_reg_t my_reg;

    // Get FIFO registers
    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET );

    spi_transfer_error = mcp2518fd_read_word_array( ctx, a, fifo_reg, 3 );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Check that it is a receive buffer
    ci_fifo_con.word = fifo_reg[ 0 ];
    if ( ci_fifo_con.tx_bf.tx_enable ) 
    {
        return -2;
    }

    // Get Status
    ci_fifo_sta.word = fifo_reg[ 1 ];

    // Get address
    ci_fifo_ua.word = fifo_reg[ 2 ];
#ifdef USERADDRESS_TIMES_FOUR
    a = 4 * ci_fifo_ua.bf.user_address;
#else
    a = ci_fifo_ua.bf.user_address;
#endif
    a += MCP2518FD_RAMADDR_START;

    // Number of bytes to read
    n = ctx->func_data.n_bytes + 8; // Add 8 header bytes

    if ( ci_fifo_con.rx_bf.rx_time_stamp_enable ) 
    {
        n += 4; // Add 4 time stamp bytes
    }

    // Make sure we read a multiple of 4 bytes from RAM
    if ( n % 4 ) 
    {
        n = n + 4 - ( n % 4 );
    }

    // Read rx_obj using one access
    if ( n > MAX_MSG_SIZE) 
    {
        n = MAX_MSG_SIZE;
    }

    spi_transfer_error = mcp2518fd_read_byte_array( ctx, a, ba, n );
    if ( spi_transfer_error ) 
    {
        return -3;
    }

    // Assign message header

    my_reg.byte[ 0 ] = ba[ 0 ];
    my_reg.byte[ 1 ] = ba[ 1 ];
    my_reg.byte[ 2 ] = ba[ 2 ];
    my_reg.byte[ 3 ] = ba[ 3 ];
    rx_obj->word[ 0 ] = my_reg.word;

    my_reg.byte[ 0 ] = ba[ 4 ];
    my_reg.byte[ 1 ] = ba[ 5 ];
    my_reg.byte[ 2 ] = ba[ 6 ];
    my_reg.byte[ 3 ] = ba[ 7 ];
    rx_obj->word[ 1 ] = my_reg.word;

    if ( ci_fifo_con.rx_bf.rx_time_stamp_enable ) 
    {
        my_reg.byte[ 0 ] = ba[ 8 ];
        my_reg.byte[ 1 ] = ba[ 9 ];
        my_reg.byte[ 2 ] = ba[ 10 ];
        my_reg.byte[ 3 ] = ba[ 11 ];
        rx_obj->word[ 2 ] = my_reg.word;

        // Assign message data_pointer
        for ( i = 0; i < ctx->func_data.n_bytes; i++ ) 
        {
            ctx->func_data.rxd[ i ] = ba[ i + 12 ];
        }
    } 
    else 
    {
        rx_obj->word[ 2 ] = 0;

        // Assign message data_pointer
        for ( i = 0; i < ctx->func_data.n_bytes; i++ ) 
        {
            ctx->func_data.rxd[ i ] = ba[ i + 8 ];
        }
    }

    // UINC channel
    spi_transfer_error = mcp2518fd_receive_channel_update( ctx, channel );
    if ( spi_transfer_error ) 
    {
        return -4;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_receive_channel_reset ( mcp2518fd_t *ctx, uint8_t channel )
{
    uint16_t a = 0;
    mcp2518fd_fifo_ctl_t ci_fifo_con;
    int8_t spi_transfer_error = 0;

    // Address and data_pointer
    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET ) + 1; // Byte that contains FRESET
    ci_fifo_con.word = 0;
    ci_fifo_con.rx_bf.freset = 1;

    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_fifo_con.byte[ 1 ] );

    return spi_transfer_error;
}

int8_t mcp2518fd_receive_channel_update ( mcp2518fd_t *ctx, uint8_t channel )
{
    uint16_t a = 0;
    mcp2518fd_fifo_ctl_t ci_fifo_con;
    int8_t spi_transfer_error = 0;
    ci_fifo_con.word = 0;

    // Set UINC
    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET ) + 1; // Byte that contains FRESET
    ci_fifo_con.rx_bf.uinc = 1;

    // Write byte
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_fifo_con.byte[ 1 ] );

    return spi_transfer_error;
}

// *****************************************************************************
// Section: Transmit Event FIFO

int8_t mcp2518fd_tef_status_get ( mcp2518fd_t *ctx, uint8_t *status )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;

    // Read
   mcp2518fd_tef_t ci_tef_sta;
    ci_tef_sta.word = 0;
    a = MCP2518FD_REG_CiTEFSTA;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_tef_sta.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *status = ( uint8_t ) ( ci_tef_sta.byte[ 0 ] & MCP2518FD_TEF_FIFO_STATUS_MASK );

    return spi_transfer_error;
}

int8_t mcp2518fd_tef_message_get ( mcp2518fd_t *ctx, mcp2518fd_tef_msg_obj_t *tef_obj )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint32_t fifo_reg[ 3 ];
    uint8_t n = 0;
    uint8_t ba[ 12 ];
    mcp2518fd_reg_t my_reg;
    mcp2518fd_tef_ctl_t ci_tef_con;
    mcp2518fd_tef_t ci_tef_sta;
    mcp2518fd_fifo_user_cfg_t ci_tef_ua;

    // Get FIFO registers
    a = MCP2518FD_REG_CiTEFCON;

    spi_transfer_error = mcp2518fd_read_word_array( ctx, a, fifo_reg, 3 );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Get control

    ci_tef_con.word = fifo_reg[ 0 ];

    // Get status
    ci_tef_sta.word = fifo_reg[ 1 ];

    // Get address
    ci_tef_ua.word = fifo_reg[ 2 ];
#ifdef USERADDRESS_TIMES_FOUR
    a = 4 * ci_tef_ua.bf.user_address;
#else
    a = ci_tef_ua.bf.user_address;
#endif
    a += MCP2518FD_RAMADDR_START;

    // Number of bytes to read
    n = 8; // 8 header bytes

    if ( ci_tef_con.bf.time_stamp_enable ) 
    {
        n += 4; // Add 4 time stamp bytes
    }

    // Read rx_obj using one access

    spi_transfer_error = mcp2518fd_read_byte_array( ctx, a, ba, n );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    // Assign message header

    my_reg.byte[ 0 ] = ba[ 0 ];
    my_reg.byte[ 1 ] = ba[ 1 ];
    my_reg.byte[ 2 ] = ba[ 2 ];
    my_reg.byte[ 3 ] = ba[ 3 ];
    tef_obj ->word[ 0 ] = my_reg.word;

    my_reg.byte[ 0 ] = ba[ 4 ];
    my_reg.byte[ 1 ] = ba[ 5 ];
    my_reg.byte[ 2 ] = ba[ 6 ];
    my_reg.byte[ 3 ] = ba[ 7 ];
    tef_obj ->word[ 1 ] = my_reg.word;

    if ( ci_tef_con.bf.time_stamp_enable ) 
    {
        my_reg.byte[ 0 ] = ba[ 8 ];
        my_reg.byte[ 1 ] = ba[ 9 ];
        my_reg.byte[ 2 ] = ba[ 10 ];
        my_reg.byte[ 3 ] = ba[ 11 ];
        tef_obj ->word[ 2 ] = my_reg.word;
    } 
    else 
    {
        tef_obj ->word[ 2 ] = 0;
    }

    // Set UINC
    spi_transfer_error = mcp2518fd_tef_update( ctx );
    if ( spi_transfer_error ) 
    {
        return -3;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_tef_reset ( mcp2518fd_t *ctx )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_tef_ctl_t ci_tef_con;

    // Set FRESET
    a = MCP2518FD_REG_CiTEFCON + 1;
    ci_tef_con.word = 0;
    ci_tef_con.bf.freset = 1;

    // Write byte
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_tef_con.byte[ 1 ] );

    return spi_transfer_error;
}

int8_t mcp2518fd_tef_update ( mcp2518fd_t *ctx )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_tef_ctl_t ci_tef_con;

    // Set UINC
    a = MCP2518FD_REG_CiTEFCON + 1;
    ci_tef_con.word = 0;
    ci_tef_con.bf.uinc = 1;

    // Write byte
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_tef_con.byte[ 1 ] );

    return spi_transfer_error;
}

int8_t mcp2518fd_tef_configure ( mcp2518fd_t *ctx, mcp2518fd_tef_cfg_t *config )
{
    int8_t spi_transfer_error = 0;

    // Setup FIFO
    mcp2518fd_tef_ctl_t ci_tef_con;
    ci_tef_con.word = can_control_reset_values[ MCP2518FD_REG_CiTEFCON / 4 ];

    ci_tef_con.bf.fifo_size = config->fifo_size;
    ci_tef_con.bf.time_stamp_enable  = config->time_stamp_enable ;

    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiTEFCON, ci_tef_con.word );

    return spi_transfer_error;
}

int8_t mcp2518fd_tef_configure_object_reset ( mcp2518fd_tef_cfg_t *config )
{
    mcp2518fd_tef_ctl_t ci_tef_con;
    ci_tef_con.word = can_control_reset_values[ MCP2518FD_REG_CiFIFOCON  / 4 ];

    config->fifo_size = ci_tef_con.bf.fifo_size;
    config->time_stamp_enable  = ci_tef_con.bf.time_stamp_enable;

    return 0;
}


// *****************************************************************************
// Section: Module Events

int8_t mcp2518fd_module_event_get ( mcp2518fd_t *ctx, uint16_t *flags )
{
    int8_t spi_transfer_error = 0;

    // Read Interrupt flags
    mcp2518fd_int_flag_t int_flags;
    int_flags.word = 0;

    spi_transfer_error = mcp2518fd_read_half_word ( ctx, MCP2518FD_REG_CiINTFLAG, &int_flags.word );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *flags = ( uint16_t ) ( int_flags.word & MCP2518FD_ALL_EVENTS );

    return spi_transfer_error;
}

int8_t mcp2518fd_module_event_enable ( mcp2518fd_t *ctx, uint16_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_int_cfg_t int_enables;

    // Read Interrupt Enables
    a = MCP2518FD_REG_CiINTENABLE;
    int_enables.word = 0;

    spi_transfer_error = mcp2518fd_read_half_word ( ctx, a, &int_enables.word );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    int_enables.word |= ( flags & MCP2518FD_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_half_word ( ctx, a, int_enables.word );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_module_event_disable ( mcp2518fd_t *ctx, uint16_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_int_cfg_t int_enables;

    // Read Interrupt Enables
    a = MCP2518FD_REG_CiINTENABLE;
    int_enables.word = 0;

    spi_transfer_error = mcp2518fd_read_half_word ( ctx, a, &int_enables.word );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    int_enables.word &= ~( flags & MCP2518FD_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_half_word( ctx, a, int_enables.word );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_module_event_clear ( mcp2518fd_t *ctx, uint16_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_int_flag_t int_flags;

    // Read Interrupt flags
    a = MCP2518FD_REG_CiINTFLAG;
    int_flags.word = 0;

    // Write 1 to all flags except the ones that we want to clear
    // Writing a 1 will not set the flag
    // Only writing a 0 will clear it
    // The flags are HS/C
    int_flags.word = MCP2518FD_ALL_EVENTS;
    int_flags.word &= ~flags;

    // Write
    spi_transfer_error = mcp2518fd_write_half_word( ctx, a, int_flags.word );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_module_event_rx_code_get ( mcp2518fd_t *ctx, uint8_t *rx_code )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint8_t rx_code_byte = 0;

    // Read
    a = MCP2518FD_REG_CiVEC + 3;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &rx_code_byte );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Decode data_pointer
    // 0x40 = "no interrupt" ( MCP2518FD_FIFO_CIVEC_NOINTERRUPT )
    if ( ( rx_code_byte < MCP2518FD_RXCODE_TOTAL_CHANNELS ) || ( rx_code_byte == MCP2518FD_RXCODE_NO_INT ) ) 
    {
        *rx_code = ( uint8_t ) rx_code_byte;
    } 
    else 
    {
        *rx_code = MCP2518FD_RXCODE_RESERVED; // shouldn't get here
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_module_event_tx_code_get ( mcp2518fd_t *ctx, uint8_t *tx_code )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint8_t tx_code_byte = 0;

    // Read
    a = MCP2518FD_REG_CiVEC + 2;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &tx_code_byte );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Decode data_pointer
    // 0x40 = "no interrupt" ( MCP2518FD_FIFO_CIVEC_NOINTERRUPT)
    if ( ( tx_code_byte < MCP2518FD_TXCODE_TOTAL_CHANNELS ) || ( tx_code_byte == MCP2518FD_TXCODE_NO_INT ) ) 
    {
        *tx_code = ( uint8_t ) tx_code_byte;
    } 
    else 
    {
        *tx_code = MCP2518FD_TXCODE_RESERVED; // shouldn't get here
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_module_event_filter_hit_get ( mcp2518fd_t *ctx, uint8_t *filter_hit )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint8_t filter_hit_byte = 0;

    // Read
    a = MCP2518FD_REG_CiVEC + 1;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &filter_hit_byte );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *filter_hit  = ( uint8_t ) filter_hit_byte;

    return spi_transfer_error;
}

int8_t mcp2518fd_module_event_icode_get ( mcp2518fd_t *ctx, uint8_t *icode )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint8_t icode_byte = 0;

    // Read
    a = MCP2518FD_REG_CiVEC;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &icode_byte );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Decode
    if ( ( icode_byte < MCP2518FD_ICODE_RESERVED ) && ( ( icode_byte < MCP2518FD_ICODE_TOTAL_CHANNELS ) || ( icode_byte >= MCP2518FD_ICODE_NO_INT ) ) ) 
    {
        *icode = ( uint8_t ) icode_byte;
    } 
    else 
    {
        *icode = MCP2518FD_ICODE_RESERVED; // shouldn't get here
    }

    return spi_transfer_error;
}

// *****************************************************************************
// Section: Transmit FIFO Events

int8_t mcp2518fd_transmit_channel_event_get ( mcp2518fd_t *ctx, uint8_t channel, uint8_t *flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;

    // Read Interrupt flags
    mcp2518fd_fifo_stat_t ci_fifo_sta;
    ci_fifo_sta.word = 0;
    a = MCP2518FD_REG_CiFIFOSTA + ( channel * MCP2518FD_FIFO_OFFSET );

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_fifo_sta.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *flags = ( uint8_t ) ( ci_fifo_sta.byte[ 0 ] & MCP2518FD_TX_FIFO_ALL_EVENTS );

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_event_get ( mcp2518fd_t *ctx, uint32_t *txif )
{
    int8_t spi_transfer_error = 0;

    spi_transfer_error = mcp2518fd_read_word ( ctx, MCP2518FD_REG_CiTXIF, txif );

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_event_attempt_get ( mcp2518fd_t *ctx, uint32_t *txatif )
{
    int8_t spi_transfer_error = 0;

    spi_transfer_error = mcp2518fd_read_word( ctx, MCP2518FD_REG_CiTXATIF, txatif );

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_channel_index_get ( mcp2518fd_t *ctx, uint8_t channel, uint8_t *idx )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;

    // Read ctx
    mcp2518fd_fifo_stat_t ci_fifo_sta;
    ci_fifo_sta.word = 0;
    a = MCP2518FD_REG_CiFIFOSTA + ( channel * MCP2518FD_FIFO_OFFSET );

    spi_transfer_error = mcp2518fd_read_word( ctx, a, &ci_fifo_sta.word );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *idx = ci_fifo_sta.tx_bf.fifo_index;

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_channel_event_enable( mcp2518fd_t *ctx, uint8_t channel, uint8_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_fifo_ctl_t ci_fifo_con;

    // Read Interrupt Enables
    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET );
    ci_fifo_con.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_fifo_con.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    ci_fifo_con.byte[ 0 ] |= ( flags & MCP2518FD_TX_FIFO_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_fifo_con.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_channel_event_disable ( mcp2518fd_t *ctx, uint8_t channel, uint8_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_fifo_ctl_t ci_fifo_con;

    // Read Interrupt Enables
    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET );
    ci_fifo_con.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_fifo_con.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    ci_fifo_con.byte[ 0 ] &= ~( flags & MCP2518FD_TX_FIFO_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_fifo_con.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_transmit_channel_event_attempt_clear ( mcp2518fd_t *ctx, uint8_t channel )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_fifo_stat_t ci_fifo_sta;

    // Read Interrupt Enables
    a = MCP2518FD_REG_CiFIFOSTA + ( channel * MCP2518FD_FIFO_OFFSET );
    ci_fifo_sta.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_fifo_sta.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    ci_fifo_sta.byte[ 0 ] &= ~MCP2518FD_TX_FIFO_ATTEMPTS_EXHAUSTED_EVENT;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_fifo_sta.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}


// *****************************************************************************
// Section: Receive FIFO Events

int8_t mcp2518fd_receive_channel_event_get ( mcp2518fd_t *ctx, uint8_t channel, uint8_t *flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_fifo_stat_t ci_fifo_sta;

#ifdef CAN_TXQUEUE_IMPLEMENTED
    if ( channel == CAN_TXQUEUE_CH0 ) 
    {
        return -100;
    }
#endif

    // Read Interrupt flags
    ci_fifo_sta.word = 0;
    a = MCP2518FD_REG_CiFIFOSTA + ( channel * MCP2518FD_FIFO_OFFSET );

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_fifo_sta.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *flags = ( uint8_t ) ( ci_fifo_sta.byte[ 0 ] & MCP2518FD_RX_FIFO_ALL_EVENTS );

    return spi_transfer_error;
}

int8_t mcp2518fd_receive_event_get ( mcp2518fd_t *ctx, uint32_t *rxif )
{
    int8_t spi_transfer_error = 0;

    spi_transfer_error = mcp2518fd_read_word( ctx, MCP2518FD_REG_CiRXIF, rxif );

    return spi_transfer_error;
}

int8_t mcp2518fd_receive_event_overflow_get ( mcp2518fd_t *ctx, uint32_t *rxovif )
{
    int8_t spi_transfer_error = 0;

    spi_transfer_error = mcp2518fd_read_word( ctx, MCP2518FD_REG_CiRXOVIF, rxovif );

    return spi_transfer_error;
}

int8_t mcp2518fd_receive_channel_index_get ( mcp2518fd_t *ctx, uint8_t channel, uint8_t *idx )
{
    return mcp2518fd_transmit_channel_index_get( ctx, channel, idx );
}

int8_t mcp2518fd_receive_channel_event_enable ( mcp2518fd_t *ctx, uint8_t channel, uint8_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_fifo_ctl_t ci_fifo_con;

#ifdef CAN_TXQUEUE_IMPLEMENTED
    if ( channel == CAN_TXQUEUE_CH0 ) 
    {
        return -100;
    }
#endif 

    // Read Interrupt Enables
    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET );
    ci_fifo_con.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_fifo_con.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    ci_fifo_con.byte[ 0 ] |= ( flags & MCP2518FD_RX_FIFO_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_fifo_con.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_receive_channel_event_disable ( mcp2518fd_t *ctx, uint8_t channel, uint8_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_fifo_ctl_t ci_fifo_con;

#ifdef CAN_TXQUEUE_IMPLEMENTED
    if ( channel == CAN_TXQUEUE_CH0) 
    {
        return -100;
    }
#endif

    // Read Interrupt Enables
    a = MCP2518FD_REG_CiFIFOCON  + ( channel * MCP2518FD_FIFO_OFFSET );
    ci_fifo_con.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_fifo_con.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    ci_fifo_con.byte[ 0 ] &= ~( flags & MCP2518FD_RX_FIFO_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_fifo_con.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_receive_channel_event_overflow_clear ( mcp2518fd_t *ctx, uint8_t channel )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_fifo_stat_t ci_fifo_sta;

#ifdef CAN_TXQUEUE_IMPLEMENTED
    if ( channel == CAN_TXQUEUE_CH0 )
    {
         return -100;
    }
#endif

    // Read Interrupt Flags
    ci_fifo_sta.word = 0;
    a = MCP2518FD_REG_CiFIFOSTA + ( channel * MCP2518FD_FIFO_OFFSET );

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_fifo_sta.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    ci_fifo_sta.byte[ 0 ] &= ~( MCP2518FD_RX_FIFO_OVERFLOW_EVENT );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_fifo_sta.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}


// *****************************************************************************
// Section: Transmit Event FIFO Events

int8_t mcp2518fd_tef_event_get ( mcp2518fd_t *ctx, uint8_t *flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_tef_t ci_tef_sta;

    // Read Interrupt flags
    ci_tef_sta.word = 0;
    a = MCP2518FD_REG_CiTEFSTA;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_tef_sta.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *flags = ( uint8_t ) ( ci_tef_sta.byte[ 0 ] & MCP2518FD_TEF_FIFO_ALL_EVENTS );

    return spi_transfer_error;
}

int8_t mcp2518fd_tef_event_enable ( mcp2518fd_t *ctx, uint8_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_tef_ctl_t ci_tef_con;

    // Read Interrupt Enables
    a = MCP2518FD_REG_CiTEFCON;
    ci_tef_con.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_tef_con.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    ci_tef_con.byte[ 0 ] |= ( flags & MCP2518FD_TEF_FIFO_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_tef_con.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_tef_event_disable ( mcp2518fd_t *ctx, uint8_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_tef_ctl_t ci_tef_con;

    // Read Interrupt Enables
    a = MCP2518FD_REG_CiTEFCON;
    ci_tef_con.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_tef_con.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    ci_tef_con.byte[ 0 ] &= ~( flags & MCP2518FD_TEF_FIFO_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_tef_con.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_tef_event_overflow_clear ( mcp2518fd_t *ctx )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_tef_t ci_tef_sta;

    // Read Interrupt Flags
    ci_tef_sta.word = 0;
    a = MCP2518FD_REG_CiTEFSTA;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ci_tef_sta.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    ci_tef_sta.byte[ 0 ] &= ~( MCP2518FD_TEF_FIFO_OVERFLOW_EVENT );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ci_tef_sta.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}


// *****************************************************************************
// Section: Error Handling

int8_t mcp2518fd_error_count_transmit_get ( mcp2518fd_t *ctx, uint8_t *tec )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;

    // Read Error count
    a = MCP2518FD_REG_CiTREC + 1;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, tec);

    return spi_transfer_error;
}

int8_t mcp2518fd_error_count_receive_get ( mcp2518fd_t *ctx, uint8_t *rec )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;

    // Read Error count
    a = MCP2518FD_REG_CiTREC;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, rec );

    return spi_transfer_error;
}

int8_t mcp2518fd_error_state_get ( mcp2518fd_t *ctx, uint8_t *flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint8_t f = 0;

    // Read Error state
    a = MCP2518FD_REG_CiTREC + 2;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &f );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *flags = ( uint8_t ) ( f & MCP2518FD_ERROR_ALL );

    return spi_transfer_error;
}

int8_t mcp2518fd_error_count_state_get ( mcp2518fd_t *ctx, uint8_t *tec, uint8_t *rec, uint8_t *flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_trec_t ci_trec;

    // Read Error
    a = MCP2518FD_REG_CiTREC;
    ci_trec.word = 0;

    spi_transfer_error = mcp2518fd_read_word( ctx, a, &ci_trec.word );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *tec = ci_trec.byte[ 1 ];
    *rec = ci_trec.byte[ 0 ];
    *flags = ( uint8_t ) ( ci_trec.byte[ 2 ] & MCP2518FD_ERROR_ALL );

    return spi_transfer_error;
}

int8_t mcp2518fd_bus_diagnostics_get ( mcp2518fd_t *ctx, mcp2518fd_bus_diag_t *bd )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint32_t w[ 2 ];
    mcp2518fd_bus_diag_t b;

    // Read diagnostic registers all in one shot
    a = MCP2518FD_REG_CiBDIAG0;

    spi_transfer_error = mcp2518fd_read_word_array( ctx, a, w, 2 ); 
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    b.word[ 0 ] = w[ 0 ];
    b.word[ 1 ] = w[ 1 ] & 0x0000ffff;
    b.word[ 2 ] = ( w[ 1 ] >> 16 ) & 0x0000ffff;
    *bd = b;

    return spi_transfer_error;
}

int8_t mcp2518fd_bus_diagnostics_clear ( mcp2518fd_t *ctx )
{
    int8_t spi_transfer_error = 0;
    uint8_t a = 0;
    uint32_t w[ 2 ];

    // Clear diagnostic registers all in one shot
    a = MCP2518FD_REG_CiBDIAG0;
    w[ 0 ] = 0;
    w[ 1 ] = 0;

    spi_transfer_error = mcp2518fd_write_word_array( ctx, a, w, 2 ); 

    return spi_transfer_error;
}


// *****************************************************************************
// Section: ECC

int8_t mcp2518fd_ecc_enable ( mcp2518fd_t *ctx )
{
    int8_t spi_transfer_error = 0;
    uint8_t d = 0;

    // Read
    spi_transfer_error = mcp2518fd_read_byte( ctx, MCP2518FD_REG_ECCCON, &d );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    d |= 0x01;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, MCP2518FD_REG_ECCCON, d );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return 0;
}

int8_t mcp2518fd_ecc_disable ( mcp2518fd_t *ctx )
{
    int8_t spi_transfer_error = 0;
    uint8_t d = 0;

    // Read
    spi_transfer_error = mcp2518fd_read_byte( ctx, MCP2518FD_REG_ECCCON, &d );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    d &= ~0x01;

    // Write
    spi_transfer_error = mcp2518fd_write_byte( ctx, MCP2518FD_REG_ECCCON, d );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return 0;
}

int8_t mcp2518fd_ecc_event_get ( mcp2518fd_t *ctx, uint8_t *flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;

    // Read Interrupt flags
    uint8_t ecc_status = 0;
    a = MCP2518FD_REG_ECCSTA;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ecc_status );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *flags = ( uint8_t ) ( ecc_status & MCP2517_ECC_ALL_EVENTS );

    return spi_transfer_error;
}

int8_t mcp2518fd_ecc_parity_set ( mcp2518fd_t *ctx, uint8_t parity )
{
    int8_t spi_transfer_error = 0;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, MCP2518FD_REG_ECCCON + 1, parity );

    return spi_transfer_error;
}

int8_t mcp2518fd_ecc_parity_get ( mcp2518fd_t *ctx, uint8_t *parity )
{
    int8_t spi_transfer_error = 0;

    // Read
    spi_transfer_error = mcp2518fd_read_byte( ctx, MCP2518FD_REG_ECCCON + 1, parity );

    return spi_transfer_error;
}

int8_t mcp2518fd_ecc_error_address_get ( mcp2518fd_t *ctx, uint16_t *a )
{
    int8_t spi_transfer_error = 0;
    mcp2518fd_ecc_sta_t reg;

    // Read
    spi_transfer_error = mcp2518fd_read_word( ctx, MCP2518FD_REG_ECCSTA, &reg.word );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *a = reg.bf.error_address;

    return spi_transfer_error;
}

int8_t mcp2518fd_ecc_event_enable ( mcp2518fd_t *ctx, uint8_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint8_t ecc_interrupts = 0;

    // Read
    a = MCP2518FD_REG_ECCCON;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ecc_interrupts );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    ecc_interrupts |= ( flags & MCP2517_ECC_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ecc_interrupts );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_ecc_event_disable ( mcp2518fd_t *ctx, uint8_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint8_t ecc_interrupts = 0;

    // Read
    a = MCP2518FD_REG_ECCCON;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ecc_interrupts );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    ecc_interrupts &= ~( flags & MCP2517_ECC_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ecc_interrupts );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_ecc_event_clear ( mcp2518fd_t *ctx, uint8_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint8_t ecc_stat = 0;

    // Read
    a = MCP2518FD_REG_ECCSTA;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &ecc_stat );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    ecc_stat &= ~( flags & MCP2517_ECC_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, ecc_stat );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

// *****************************************************************************
// Section: CRC

int8_t mcp2518fd_crc_event_enable ( mcp2518fd_t *ctx, uint8_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint8_t crc;

    // Read interrupt control bits of CRC Register
    a = MCP2518FD_REG_CRC + 3;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &crc );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    crc |= ( flags & MCP2518FD_CRC_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, crc );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_crc_event_disable ( mcp2518fd_t *ctx, uint8_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint8_t crc;

    // Read interrupt control bits of CRC Register
    a = MCP2518FD_REG_CRC + 3;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &crc );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    crc &= ~( flags & MCP2518FD_CRC_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, crc );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_crc_event_clear ( mcp2518fd_t *ctx, uint8_t flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint8_t crc;

    // Read interrupt flags of CRC Register
    a = MCP2518FD_REG_CRC + 2;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &crc );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    crc &= ~( flags & MCP2518FD_CRC_ALL_EVENTS );

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, crc );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_crc_event_get ( mcp2518fd_t *ctx, uint8_t *flags )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    uint8_t crc;

    // Read interrupt flags of CRC Register
    a = MCP2518FD_REG_CRC + 2;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &crc );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *flags = ( uint8_t ) ( crc & MCP2518FD_CRC_ALL_EVENTS );

    return spi_transfer_error;
}

int8_t mcp2518fd_crc_value_get ( mcp2518fd_t *ctx, uint16_t *crc )
{
    int8_t spi_transfer_error = 0;

    // Read CRC value from CRC Register
    spi_transfer_error = mcp2518fd_read_half_word ( ctx, MCP2518FD_REG_CRC, crc );

    return spi_transfer_error;
}

int8_t mcp2518fd_ram_init ( mcp2518fd_t *ctx, uint8_t d )
{
    uint8_t txd[ 64 ];
    uint32_t k;
    int8_t spi_transfer_error = 0;
    uint16_t a = MCP2518FD_RAMADDR_START;

    // Prepare data_pointer
    for ( k = 0; k < 64; k++ )
        txd[ k ] = d;

    for ( k = 0; k < 32; k++ )
    {
        spi_transfer_error = mcp2518fd_write_byte_array( ctx, a, txd, 64 );
        if ( spi_transfer_error )
            return -1;
        a += 64;
    }

    return spi_transfer_error;
}


// *****************************************************************************
// Section: Time Stamp

int8_t mcp2518fd_time_stamp_enable ( mcp2518fd_t *ctx )
{
    int8_t spi_transfer_error = 0;
    uint8_t d = 0;

    // Read
    spi_transfer_error = mcp2518fd_read_byte( ctx, MCP2518FD_REG_CiTSCON + 2, &d );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    d |= 0x01;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, MCP2518FD_REG_CiTSCON + 2, d );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_time_stamp_disable ( mcp2518fd_t *ctx )
{
    int8_t spi_transfer_error = 0;
    uint8_t d = 0;

    // Read
    spi_transfer_error = mcp2518fd_read_byte( ctx, MCP2518FD_REG_CiTSCON + 2, &d );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    d &= 0x06;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, MCP2518FD_REG_CiTSCON + 2, d );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_time_stamp_get ( mcp2518fd_t *ctx, uint32_t *ts )
{
    int8_t spi_transfer_error = 0;

    // Read
    spi_transfer_error = mcp2518fd_read_word( ctx, MCP2518FD_REG_CiTBC, ts );

    return spi_transfer_error;
}

int8_t mcp2518fd_time_stamp_set ( mcp2518fd_t *ctx, uint32_t ts )
{
    int8_t spi_transfer_error = 0;

    // Write
    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiTBC, ts );

    return spi_transfer_error;
}

int8_t mcp2518fd_time_stamp_mode_configure ( mcp2518fd_t *ctx, uint8_t mode )
{
    int8_t spi_transfer_error = 0;
    uint8_t d = 0;

    // Read
    spi_transfer_error = mcp2518fd_read_byte( ctx, MCP2518FD_REG_CiTSCON + 2, &d );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    d &= 0x01;
    d |= mode << 1;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, MCP2518FD_REG_CiTSCON + 2, d );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_time_stamp_prescaler_set ( mcp2518fd_t *ctx, uint16_t ps )
{
    int8_t spi_transfer_error = 0;

    // Write
    spi_transfer_error = mcp2518fd_write_half_word( ctx, MCP2518FD_REG_CiTSCON, ps );

    return spi_transfer_error;
}


// *****************************************************************************
// Section: Oscillator and Bit Time

int8_t mcp2518fd_oscillator_enable ( mcp2518fd_t *ctx )
{
    int8_t spi_transfer_error = 0;
    uint8_t d = 0;

    // Read
    spi_transfer_error = mcp2518fd_read_byte( ctx, MCP2518FD_REG_OSC, &d );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    d &= ~0x4;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, MCP2518FD_REG_OSC, d );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_oscillator_control_set ( mcp2518fd_t *ctx, mcp2518fd_div_ctl_t ctrl )
{
    int8_t spi_transfer_error = 0;

    mcp2518fd_osc_ctl_t osc;
    osc.word = 0;

    osc.bf.pll_enable = ctrl.pll_enable;
    osc.bf.osc_disable = ctrl.osc_disable;
    osc.bf.sclk_divide = ctrl.sclk_divide;
    osc.bf.clk_out_divide = ctrl.clk_out_divide;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, MCP2518FD_REG_OSC, osc.byte[ 0 ] );

    return spi_transfer_error;
}

int8_t mcp2518fd_oscillator_control_object_reset ( mcp2518fd_div_ctl_t *ctrl )
{
    mcp2518fd_osc_ctl_t osc;
    osc.word = mcp2517_control_reset_values[ 0 ];

    ctrl->pll_enable = osc.bf.pll_enable;
    ctrl->osc_disable = osc.bf.osc_disable;
    ctrl->sclk_divide = osc.bf.sclk_divide;
    ctrl->clk_out_divide = osc.bf.clk_out_divide;

    return 0;
}

int8_t mcp2518fd_oscillator_status_get ( mcp2518fd_t *ctx, mcp2518fd_osc_sta_t *status )
{
    int8_t spi_transfer_error = 0;
    mcp2518fd_osc_sta_t stat;
    mcp2518fd_osc_ctl_t osc;

    osc.word = 0;
    // Read
    spi_transfer_error = mcp2518fd_read_byte( ctx, MCP2518FD_REG_OSC + 1, &osc.byte[ 1 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    stat.pll_ready = osc.bf.pll_ready;
    stat.osc_ready = osc.bf.osc_ready;
    stat.sclk_ready = osc.bf.sclk_ready;

    *status = stat;

    return spi_transfer_error;
}

int8_t mcp2518fd_bit_time_configure ( mcp2518fd_t *ctx, uint8_t bit_time, uint8_t ssp_mode, uint8_t clk )
{
    int8_t spi_transfer_error = 0;

    // Decode clk
    switch ( clk) 
    {
        case MCP2518FD_SYSCLK_40M:
        {
            spi_transfer_error = mcp2518fd_bit_time_configure_nominal_40_mhz( ctx, bit_time );
            if ( spi_transfer_error ) 
            {
                return spi_transfer_error;
            }
            spi_transfer_error = mcp2518fd_bit_time_configure_data_40_mhz( ctx, bit_time, ssp_mode );
            break;
        }
        case MCP2518FD_SYSCLK_20M:
        {
            spi_transfer_error = mcp2518fd_bit_time_configure_nominal_20_mhz( ctx, bit_time );
            if ( spi_transfer_error ) 
            {
                return spi_transfer_error;
            }
            spi_transfer_error = mcp2518fd_bit_time_configure_data_20_mhz( ctx, bit_time, ssp_mode );
            break;
        }
        case MCP2518FD_SYSCLK_10M:
        {
            spi_transfer_error = mcp2518fd_bit_time_configure_nominal_10_mhz( ctx, bit_time );
            if ( spi_transfer_error ) 
            {
                return spi_transfer_error;
            }
            spi_transfer_error = mcp2518fd_bit_time_configure_data_10_mhz( ctx, bit_time, ssp_mode );
            break;
        }
        default:
        {
            spi_transfer_error = -1;
            break;
        }
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_bit_time_configure_nominal_40_mhz ( mcp2518fd_t *ctx, uint8_t bit_time )
{
    int8_t spi_transfer_error = 0;
    mcp2518fd_nbt_cfg_t ci_nbt_cfg;

    ci_nbt_cfg.word = can_control_reset_values[ MCP2518FD_REG_CiNBTCFG / 4 ];

    // Arbitration Bit rate
    switch ( bit_time ) 
    {
            // All 500K
        case MCP2518FD_500K_1M:
        case MCP2518FD_500K_2M:
        case MCP2518FD_500K_3M:
        case MCP2518FD_500K_4M:
        case MCP2518FD_500K_5M:
        case MCP2518FD_500K_6M7:
        case MCP2518FD_500K_8M:
        case MCP2518FD_500K_10M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 62;
            ci_nbt_cfg.bf.tseg2 = 15;
            ci_nbt_cfg.bf.swj = 15;
            break;
        }
            // All 250K
        case MCP2518FD_250K_500K:
        case MCP2518FD_250K_833K:
        case MCP2518FD_250K_1M:
        case MCP2518FD_250K_1M5:
        case MCP2518FD_250K_2M:
        case MCP2518FD_250K_3M:
        case MCP2518FD_250K_4M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 126;
            ci_nbt_cfg.bf.tseg2 = 31;
            ci_nbt_cfg.bf.swj = 31;
            break;
        }
        case MCP2518FD_1000K_4M:
        case MCP2518FD_1000K_8M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 30;
            ci_nbt_cfg.bf.tseg2 = 7;
            ci_nbt_cfg.bf.swj = 7;
            break;
        }
        case MCP2518FD_125K_500K:
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

    // Write Bit time registers
    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiNBTCFG, ci_nbt_cfg.word );

    return spi_transfer_error;
}

int8_t mcp2518fd_bit_time_configure_data_40_mhz ( mcp2518fd_t *ctx, uint8_t bit_time, uint8_t ssp_mode )
{
    int8_t spi_transfer_error = 0;
    mcp2518fd_dbt_cfg_t ci_dbt_cfg;
    mcp2518fd_tdc_cfg_t ci_tdc;
    uint32_t tdc_value = 0;

    //    ssp_mode;
    ci_dbt_cfg.word = can_control_reset_values[ MCP2518FD_REG_CiDBTCFG / 4 ];
    ci_tdc.word = 0;

    // Configure Bit time and sample point
    ci_tdc.bf.tdc_mode = MCP2518FD_SSP_MODE_AUTO;

    // Data Bit rate and SSP
    switch ( bit_time ) 
    {
        case MCP2518FD_500K_1M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 30;
            ci_dbt_cfg.bf.tseg2 = 7;
            ci_dbt_cfg.bf.swj = 7;
            // SSP
            ci_tdc.bf.tdc_offset = 31;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_500K_2M:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 14;
            ci_dbt_cfg.bf.tseg2 = 3;
            ci_dbt_cfg.bf.swj = 3;
            // SSP
            ci_tdc.bf.tdc_offset = 15;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_500K_3M:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 8;
            ci_dbt_cfg.bf.tseg2 = 2;
            ci_dbt_cfg.bf.swj = 2;
            // SSP
            ci_tdc.bf.tdc_offset = 9;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_500K_4M:
        case MCP2518FD_1000K_4M:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 6;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            // SSP
            ci_tdc.bf.tdc_offset = 7;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_500K_5M:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 4;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            // SSP
            ci_tdc.bf.tdc_offset = 5;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_500K_6M7:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 3;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            // SSP
            ci_tdc.bf.tdc_offset = 4;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_500K_8M:
        case MCP2518FD_1000K_8M:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 2;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            // SSP
            ci_tdc.bf.tdc_offset = 3;
            ci_tdc.bf.tdc_value = 1;
            break;
        }
        case MCP2518FD_500K_10M:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 1;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            // SSP
            ci_tdc.bf.tdc_offset = 2;
            ci_tdc.bf.tdc_value = 0;
            break;
        }
        case MCP2518FD_250K_500K:
        case MCP2518FD_125K_500K:
        {
            ci_dbt_cfg.bf.brp = 1;
            ci_dbt_cfg.bf.tseg1 = 30;
            ci_dbt_cfg.bf.tseg2 = 7;
            ci_dbt_cfg.bf.swj = 7;
            // SSP
            ci_tdc.bf.tdc_offset = 31;
            ci_tdc.bf.tdc_value = tdc_value;
            ci_tdc.bf.tdc_mode = MCP2518FD_SSP_MODE_OFF;
            break;
        }
        case MCP2518FD_250K_833K:
        {
            ci_dbt_cfg.bf.brp = 1;
            ci_dbt_cfg.bf.tseg1 = 17;
            ci_dbt_cfg.bf.tseg2 = 4;
            ci_dbt_cfg.bf.swj = 4;
            // SSP
            ci_tdc.bf.tdc_offset = 18;
            ci_tdc.bf.tdc_value = tdc_value;
            ci_tdc.bf.tdc_mode = MCP2518FD_SSP_MODE_OFF;
            break;
        }
        case MCP2518FD_250K_1M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 30;
            ci_dbt_cfg.bf.tseg2 = 7;
            ci_dbt_cfg.bf.swj = 7;
            // SSP
            ci_tdc.bf.tdc_offset = 31;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_250K_1M5:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 18;
            ci_dbt_cfg.bf.tseg2 = 5;
            ci_dbt_cfg.bf.swj = 5;
            // SSP
            ci_tdc.bf.tdc_offset = 19;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_250K_2M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 14;
            ci_dbt_cfg.bf.tseg2 = 3;
            ci_dbt_cfg.bf.swj = 3;
            // SSP
            ci_tdc.bf.tdc_offset = 15;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_250K_3M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 8;
            ci_dbt_cfg.bf.tseg2 = 2;
            ci_dbt_cfg.bf.swj = 2;
            // SSP
            ci_tdc.bf.tdc_offset = 9;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_250K_4M:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 6;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            // SSP
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

    // Write Bit time registers
    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiDBTCFG, ci_dbt_cfg.word );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    // Write Transmitter Delay Compensation
#ifdef REV_A
    ci_tdc.bf.tdc_offset = 0;
    ci_tdc.bf.tdc_value = 0;
#endif

    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiTDC, ci_tdc.word );
    if ( spi_transfer_error ) 
    {
        return -3;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_bit_time_configure_nominal_20_mhz ( mcp2518fd_t *ctx, uint8_t bit_time )
{
    int8_t spi_transfer_error = 0;
    mcp2518fd_nbt_cfg_t ci_nbt_cfg;

    ci_nbt_cfg.word = can_control_reset_values[ MCP2518FD_REG_CiNBTCFG / 4 ];

    // Arbitration Bit rate
    switch ( bit_time ) 
    {
            // All 500K
        case MCP2518FD_500K_1M:
        case MCP2518FD_500K_2M:
        case MCP2518FD_500K_4M:
        case MCP2518FD_500K_5M:
        case MCP2518FD_500K_6M7:
        case MCP2518FD_500K_8M:
        case MCP2518FD_500K_10M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 30;
            ci_nbt_cfg.bf.tseg2 = 7;
            ci_nbt_cfg.bf.swj = 7;
            break;
        }
            // All 250K
        case MCP2518FD_250K_500K:
        case MCP2518FD_250K_833K:
        case MCP2518FD_250K_1M:
        case MCP2518FD_250K_1M5:
        case MCP2518FD_250K_2M:
        case MCP2518FD_250K_3M:
        case MCP2518FD_250K_4M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 62;
            ci_nbt_cfg.bf.tseg2 = 15;
            ci_nbt_cfg.bf.swj = 15;
            break;
        }
        case MCP2518FD_1000K_4M:
        case MCP2518FD_1000K_8M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 14;
            ci_nbt_cfg.bf.tseg2 = 3;
            ci_nbt_cfg.bf.swj = 3;
            break;
        }
        case MCP2518FD_125K_500K:
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

    // Write Bit time registers
    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiNBTCFG, ci_nbt_cfg.word );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_bit_time_configure_data_20_mhz ( mcp2518fd_t *ctx, uint8_t bit_time, uint8_t ssp_mode )
{
    int8_t spi_transfer_error = 0;
    mcp2518fd_dbt_cfg_t ci_dbt_cfg;
    mcp2518fd_tdc_cfg_t ci_tdc;
    uint32_t tdc_value = 0;

    //    ssp_mode;

    ci_dbt_cfg.word = can_control_reset_values[ MCP2518FD_REG_CiDBTCFG / 4 ];
    ci_tdc.word = 0;

    // Configure Bit time and sample point
    ci_tdc.bf.tdc_mode = MCP2518FD_SSP_MODE_AUTO;

    // Data Bit rate and SSP
    switch ( bit_time ) 
    {
        case MCP2518FD_500K_1M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 14;
            ci_dbt_cfg.bf.tseg2 = 3;
            ci_dbt_cfg.bf.swj = 3;
            // SSP
            ci_tdc.bf.tdc_offset = 15;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_500K_2M:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 6;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            // SSP
            ci_tdc.bf.tdc_offset = 7;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_500K_4M:
        case MCP2518FD_1000K_4M:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 2;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            // SSP
            ci_tdc.bf.tdc_offset = 3;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_500K_5M:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 1;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            // SSP
            ci_tdc.bf.tdc_offset = 2;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_500K_6M7:
        case MCP2518FD_500K_8M:
        case MCP2518FD_500K_10M:
        case MCP2518FD_1000K_8M:
        {
            //qDebug("Data Bitrate not feasible with this clock!");
            return -1;
            break;
        }
        case MCP2518FD_250K_500K:
        case MCP2518FD_125K_500K:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 30;
            ci_dbt_cfg.bf.tseg2 = 7;
            ci_dbt_cfg.bf.swj = 7;
            // SSP
            ci_tdc.bf.tdc_offset = 31;
            ci_tdc.bf.tdc_value = tdc_value;
            ci_tdc.bf.tdc_mode = MCP2518FD_SSP_MODE_OFF;
            break;
        }
        case MCP2518FD_250K_833K:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 17;
            ci_dbt_cfg.bf.tseg2 = 4;
            ci_dbt_cfg.bf.swj = 4;
            // SSP
            ci_tdc.bf.tdc_offset = 18;
            ci_tdc.bf.tdc_value = tdc_value;
            ci_tdc.bf.tdc_mode = MCP2518FD_SSP_MODE_OFF;
            break;
        }
        case MCP2518FD_250K_1M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 14;
            ci_dbt_cfg.bf.tseg2 = 3;
            ci_dbt_cfg.bf.swj = 3;
            // SSP
            ci_tdc.bf.tdc_offset = 15;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_250K_1M5:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 8;
            ci_dbt_cfg.bf.tseg2 = 2;
            ci_dbt_cfg.bf.swj = 2;
            // SSP
            ci_tdc.bf.tdc_offset = 9;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_250K_2M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 6;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            // SSP
            ci_tdc.bf.tdc_offset = 7;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_250K_3M:
        {
            //qDebug("Data Bitrate not feasible with this clock!");
            return -1;
            break;
        }
        case MCP2518FD_250K_4M:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 2;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            // SSP
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

    // Write Bit time registers
    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiDBTCFG, ci_dbt_cfg.word );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    // Write Transmitter Delay Compensation
#ifdef REV_A
    ci_tdc.bf.tdc_offset = 0;
    ci_tdc.bf.tdc_value = 0;
#endif

    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiTDC, ci_tdc.word );
    if ( spi_transfer_error ) 
    {
        return -3;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_bit_time_configure_nominal_10_mhz ( mcp2518fd_t *ctx, uint8_t bit_time )
{
    int8_t spi_transfer_error = 0;
    mcp2518fd_nbt_cfg_t ci_nbt_cfg;

    ci_nbt_cfg.word = can_control_reset_values[ MCP2518FD_REG_CiNBTCFG / 4 ];

    // Arbitration Bit rate
    switch ( bit_time ) 
    {
            // All 500K
        case MCP2518FD_500K_1M:
        case MCP2518FD_500K_2M:
        case MCP2518FD_500K_4M:
        case MCP2518FD_500K_5M:
        case MCP2518FD_500K_6M7:
        case MCP2518FD_500K_8M:
        case MCP2518FD_500K_10M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 14;
            ci_nbt_cfg.bf.tseg2 = 3;
            ci_nbt_cfg.bf.swj = 3;
            break;
        }
            // All 250K
        case MCP2518FD_250K_500K:
        case MCP2518FD_250K_833K:
        case MCP2518FD_250K_1M:
        case MCP2518FD_250K_1M5:
        case MCP2518FD_250K_2M:
        case MCP2518FD_250K_3M:
        case MCP2518FD_250K_4M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 30;
            ci_nbt_cfg.bf.tseg2 = 7;
            ci_nbt_cfg.bf.swj = 7;
            break;
        }
        case MCP2518FD_1000K_4M:
        case MCP2518FD_1000K_8M:
        {
            ci_nbt_cfg.bf.brp = 0;
            ci_nbt_cfg.bf.tseg1 = 7;
            ci_nbt_cfg.bf.tseg2 = 2;
            ci_nbt_cfg.bf.swj = 2;
            break;
        }
        case MCP2518FD_125K_500K:
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

    // Write Bit time registers
    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiNBTCFG, ci_nbt_cfg.word );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_bit_time_configure_data_10_mhz ( mcp2518fd_t *ctx, uint8_t bit_time, uint8_t ssp_mode )
{
    int8_t spi_transfer_error = 0;
    mcp2518fd_dbt_cfg_t ci_dbt_cfg;
    mcp2518fd_tdc_cfg_t ci_tdc;
    uint32_t tdc_value = 0;
    //    ssp_mode;

    ci_dbt_cfg.word = can_control_reset_values[ MCP2518FD_REG_CiDBTCFG / 4 ];
    ci_tdc.word = 0;

    // Configure Bit time and sample point
    ci_tdc.bf.tdc_mode = MCP2518FD_SSP_MODE_AUTO;

    // Data Bit rate and SSP
    switch ( bit_time ) 
    {
        case MCP2518FD_500K_1M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 6;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            // SSP
            ci_tdc.bf.tdc_offset = 7;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_500K_2M:
        {
            // Data BR
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 2;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            // SSP
            ci_tdc.bf.tdc_offset = 3;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_500K_4M:
        case MCP2518FD_500K_5M:
        case MCP2518FD_500K_6M7:
        case MCP2518FD_500K_8M:
        case MCP2518FD_500K_10M:
        case MCP2518FD_1000K_4M:
        case MCP2518FD_1000K_8M:
            // qDebug("Data Bitrate not feasible with this clock!");
            return -1;
            break;

        case MCP2518FD_250K_500K:
        case MCP2518FD_125K_500K:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 14;
            ci_dbt_cfg.bf.tseg2 = 3;
            ci_dbt_cfg.bf.swj = 3;
            // SSP
            ci_tdc.bf.tdc_offset = 15;
            ci_tdc.bf.tdc_value = tdc_value;
            ci_tdc.bf.tdc_mode = MCP2518FD_SSP_MODE_OFF;
            break;
        }
        case MCP2518FD_250K_833K:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 7;
            ci_dbt_cfg.bf.tseg2 = 2;
            ci_dbt_cfg.bf.swj = 2;
            // SSP
            ci_tdc.bf.tdc_offset = 8;
            ci_tdc.bf.tdc_value = tdc_value;
            ci_tdc.bf.tdc_mode = MCP2518FD_SSP_MODE_OFF;
            break;
        }
        case MCP2518FD_250K_1M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 6;
            ci_dbt_cfg.bf.tseg2 = 1;
            ci_dbt_cfg.bf.swj = 1;
            // SSP
            ci_tdc.bf.tdc_offset = 7;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_250K_1M5:
        {
            //qDebug("Data Bitrate not feasible with this clock!");
            return -1;
            break;
        }
        case MCP2518FD_250K_2M:
        {
            ci_dbt_cfg.bf.brp = 0;
            ci_dbt_cfg.bf.tseg1 = 2;
            ci_dbt_cfg.bf.tseg2 = 0;
            ci_dbt_cfg.bf.swj = 0;
            // SSP
            ci_tdc.bf.tdc_offset = 3;
            ci_tdc.bf.tdc_value = tdc_value;
            break;
        }
        case MCP2518FD_250K_3M:
        case MCP2518FD_250K_4M:
        {
            //qDebug("Data Bitrate not feasible with this clock!");
            return -1;
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    // Write Bit time registers
    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiDBTCFG, ci_dbt_cfg.word );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    // Write Transmitter Delay Compensation
#ifdef REV_A
    ci_tdc.bf.tdc_offset = 0;
    ci_tdc.bf.tdc_value = 0;
#endif

    spi_transfer_error = mcp2518fd_write_word ( ctx, MCP2518FD_REG_CiTDC, ci_tdc.word );
    if ( spi_transfer_error ) 
    {
        return -3;
    }

    return spi_transfer_error;
}


// *****************************************************************************
// *****************************************************************************
// Section: GPIO

int8_t mcp2518fd_gpio_mode_configure ( mcp2518fd_t *ctx, uint8_t gpio0, uint8_t gpio1 )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_io_ctl_t iocon;

    // Read
    a = MCP2518FD_REG_IOCON + 3;
    iocon.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &iocon.byte[ 3 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    iocon.bf.pin_mode0 = gpio0;
    iocon.bf.pin_mode1 = gpio1;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, iocon.byte[ 3 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_gpio_direction_configure ( mcp2518fd_t *ctx, uint8_t gpio0, uint8_t gpio1 )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_io_ctl_t iocon;

    // Read
    a = MCP2518FD_REG_IOCON;
    iocon.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &iocon.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    iocon.bf.tris0 = gpio0;
    iocon.bf.tris1 = gpio1;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, iocon.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_gpio_standby_control_enable ( mcp2518fd_t *ctx )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_io_ctl_t iocon;

    // Read
    a = MCP2518FD_REG_IOCON;
    iocon.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &iocon.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    iocon.bf.xcr_stby_enable = 1;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, iocon.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_gpio_standby_control_disable ( mcp2518fd_t *ctx )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_io_ctl_t iocon;

    // Read
    a = MCP2518FD_REG_IOCON;
    iocon.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &iocon.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    iocon.bf.xcr_stby_enable = 0;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, iocon.byte[ 0 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_gpio_interrupt_pins_open_drain_configure ( mcp2518fd_t *ctx, uint8_t mode )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_io_ctl_t iocon;

    // Read
    a = MCP2518FD_REG_IOCON + 3;
    iocon.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &iocon.byte[ 3 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    iocon.bf.int_pin_open_drain = mode;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, iocon.byte[ 3 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_gpio_transmit_pin_open_drain_configure ( mcp2518fd_t *ctx, uint8_t mode )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_io_ctl_t iocon;

    // Read
    a = MCP2518FD_REG_IOCON + 3;
    iocon.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &iocon.byte[ 3 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    iocon.bf.tx_can_open_drain = mode;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, iocon.byte[ 3 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_gpio_pin_set ( mcp2518fd_t *ctx, uint8_t pos, uint8_t latch )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_io_ctl_t iocon;

    // Read
    a = MCP2518FD_REG_IOCON + 1;
    iocon.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &iocon.byte[ 1 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    switch (pos ) 
    {
        case MCP2518FD_PIN_0:
        {
            iocon.bf.lat0 = latch;
            break;
        }
        case MCP2518FD_PIN_1:
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

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, iocon.byte[ 1 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}

int8_t mcp2518fd_gpio_pin_read ( mcp2518fd_t *ctx, uint8_t pos, uint8_t *state )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_io_ctl_t iocon;

    // Read
    a = MCP2518FD_REG_IOCON + 2;
    iocon.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &iocon.byte[ 2 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    switch (pos ) 
    {
        case MCP2518FD_PIN_0:
        {
            *state = ( uint8_t ) iocon.bf.gpio0;
            break;
        }
        case MCP2518FD_PIN_1:
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

    return spi_transfer_error;
}

int8_t mcp2518fd_gpio_clock_output_configure ( mcp2518fd_t *ctx, int8_t mode )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;
    mcp2518fd_io_ctl_t iocon;

    // Read
    a = MCP2518FD_REG_IOCON + 3;
    iocon.word = 0;

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &iocon.byte[ 3 ] );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Modify
    iocon.bf.sof_output_enable = mode;

    // Write
    spi_transfer_error = mcp2518fd_write_byte ( ctx, a, iocon.byte[ 3 ] );
    if ( spi_transfer_error ) 
    {
        return -2;
    }

    return spi_transfer_error;
}


// *****************************************************************************
// Section: Miscellaneous

uint32_t mcp2518fd_dlc_to_data_bytes ( uint8_t dlc )
{
    uint32_t data_pointerbytes_in_object = 0;

    //asm nop;
    //asm nop;

    if ( dlc < MCP2518FD_DLC_12 )   
    {
        data_pointerbytes_in_object = dlc;
    } 
    else 
    {
        switch ( dlc ) 
        {
            case MCP2518FD_DLC_12:
            {
                data_pointerbytes_in_object = 12;
                break;
            }
            case MCP2518FD_DLC_16:
            {
                data_pointerbytes_in_object = 16;
                break;
            }
            case MCP2518FD_DLC_20:
            {
                data_pointerbytes_in_object = 20;
                break;
            }
            case MCP2518FD_DLC_24:
            {
                data_pointerbytes_in_object = 24;
                break;
            }
            case MCP2518FD_DLC_32:
            {
                data_pointerbytes_in_object = 32;
                break;
            }
            case MCP2518FD_DLC_48:
            {
                data_pointerbytes_in_object = 48;
                break;
            }
            case MCP2518FD_DLC_64:
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

int8_t mcp2518fd_fifo_index_get ( mcp2518fd_t *ctx, uint8_t channel, uint8_t* mi )
{
    int8_t spi_transfer_error = 0;
    uint16_t a = 0;

    // Read Status register
    uint8_t b = 0;
    a = MCP2518FD_REG_CiFIFOSTA + ( channel * MCP2518FD_FIFO_OFFSET );
    a += 1; // byte[ 1 ]

    spi_transfer_error = mcp2518fd_read_byte( ctx, a, &b );
    if ( spi_transfer_error ) 
    {
        return -1;
    }

    // Update data
    *mi = b & 0x1f;

    return spi_transfer_error;
}

uint16_t mcp2518fd_calculate_crc16 ( uint8_t *data_pointer, uint16_t size )
{
    uint16_t init = CRCBASE;
    uint8_t ctx;

    while ( size-- != 0 ) 
    {
        ctx = ( ( uint8_t* ) & init )[ CRCUPPER ] ^ *data_pointer++;
        init = ( init << 8 ) ^ crc16table[ ctx ];
    }

    return init;
}

uint8_t mcp2518fd_data_bytes_to_dlc ( uint8_t n )
{
    uint8_t dlc = MCP2518FD_DLC_0;

    if ( n <= 4 ) 
    {
        dlc = MCP2518FD_DLC_4;
    } 
    else if ( n <= 8 ) 
    {
        dlc = MCP2518FD_DLC_8;
    } 
    else if ( n <= 12 )   
    {
        dlc = MCP2518FD_DLC_12;
    } 
    else if ( n <= 16 ) 
    {
        dlc = MCP2518FD_DLC_16;
    } 
    else if ( n <= 20) 
    {
        dlc = MCP2518FD_DLC_20;
    } 
    else if ( n <= 24 ) 
    {
        dlc = MCP2518FD_DLC_24;
    } 
    else if ( n <= 32 )   {
        dlc = MCP2518FD_DLC_32;
    } 
    else if ( n <= 48 ) 
    {
        dlc = MCP2518FD_DLC_48;
    } 
    else if ( n <= 64 ) 
    {
        dlc = MCP2518FD_DLC_64;
    }

    return dlc;
}

// ------------------------------------------------------------------------- END


