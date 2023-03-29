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
 * @file fingerprint4.c
 * @brief Fingerprint 4 Click Driver.
 */

#include "fingerprint4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Fingerprint 4 crc32 table array.
 * @details The constants here are for the CRC-32 generator polynomial, as defined in
 * the Microsoft Systems Journal, March 1995, pp. 107-108.
 */
static const uint32_t fingerprint4_crc32_table[ ] = 
{
    0x00000000ul, 0x77073096ul, 0xEE0E612Cul, 0x990951BAul, 0x076DC419ul, 0x706AF48Ful,
    0xE963A535ul, 0x9E6495A3ul, 0x0EDB8832ul, 0x79DCB8A4ul, 0xE0D5E91Eul, 0x97D2D988ul,
    0x09B64C2Bul, 0x7EB17CBDul, 0xE7B82D07ul, 0x90BF1D91ul, 0x1DB71064ul, 0x6AB020F2ul,
    0xF3B97148ul, 0x84BE41DEul, 0x1ADAD47Dul, 0x6DDDE4EBul, 0xF4D4B551ul, 0x83D385C7ul,
    0x136C9856ul, 0x646BA8C0ul, 0xFD62F97Aul, 0x8A65C9ECul, 0x14015C4Ful, 0x63066CD9ul,
    0xFA0F3D63ul, 0x8D080DF5ul, 0x3B6E20C8ul, 0x4C69105Eul, 0xD56041E4ul, 0xA2677172ul,
    0x3C03E4D1ul, 0x4B04D447ul, 0xD20D85FDul, 0xA50AB56Bul, 0x35B5A8FAul, 0x42B2986Cul,
    0xDBBBC9D6ul, 0xACBCF940ul, 0x32D86CE3ul, 0x45DF5C75ul, 0xDCD60DCFul, 0xABD13D59ul,
    0x26D930ACul, 0x51DE003Aul, 0xC8D75180ul, 0xBFD06116ul, 0x21B4F4B5ul, 0x56B3C423ul,
    0xCFBA9599ul, 0xB8BDA50Ful, 0x2802B89Eul, 0x5F058808ul, 0xC60CD9B2ul, 0xB10BE924ul,
    0x2F6F7C87ul, 0x58684C11ul, 0xC1611DABul, 0xB6662D3Dul, 0x76DC4190ul, 0x01DB7106ul,
    0x98D220BCul, 0xEFD5102Aul, 0x71B18589ul, 0x06B6B51Ful, 0x9FBFE4A5ul, 0xE8B8D433ul,
    0x7807C9A2ul, 0x0F00F934ul, 0x9609A88Eul, 0xE10E9818ul, 0x7F6A0DBBul, 0x086D3D2Dul,
    0x91646C97ul, 0xE6635C01ul, 0x6B6B51F4ul, 0x1C6C6162ul, 0x856530D8ul, 0xF262004Eul,
    0x6C0695EDul, 0x1B01A57Bul, 0x8208F4C1ul, 0xF50FC457ul, 0x65B0D9C6ul, 0x12B7E950ul,
    0x8BBEB8EAul, 0xFCB9887Cul, 0x62DD1DDFul, 0x15DA2D49ul, 0x8CD37CF3ul, 0xFBD44C65ul,
    0x4DB26158ul, 0x3AB551CEul, 0xA3BC0074ul, 0xD4BB30E2ul, 0x4ADFA541ul, 0x3DD895D7ul,
    0xA4D1C46Dul, 0xD3D6F4FBul, 0x4369E96Aul, 0x346ED9FCul, 0xAD678846ul, 0xDA60B8D0ul,
    0x44042D73ul, 0x33031DE5ul, 0xAA0A4C5Ful, 0xDD0D7CC9ul, 0x5005713Cul, 0x270241AAul,
    0xBE0B1010ul, 0xC90C2086ul, 0x5768B525ul, 0x206F85B3ul, 0xB966D409ul, 0xCE61E49Ful,
    0x5EDEF90Eul, 0x29D9C998ul, 0xB0D09822ul, 0xC7D7A8B4ul, 0x59B33D17ul, 0x2EB40D81ul,
    0xB7BD5C3Bul, 0xC0BA6CADul, 0xEDB88320ul, 0x9ABFB3B6ul, 0x03B6E20Cul, 0x74B1D29Aul,
    0xEAD54739ul, 0x9DD277AFul, 0x04DB2615ul, 0x73DC1683ul, 0xE3630B12ul, 0x94643B84ul,
    0x0D6D6A3Eul, 0x7A6A5AA8ul, 0xE40ECF0Bul, 0x9309FF9Dul, 0x0A00AE27ul, 0x7D079EB1ul,
    0xF00F9344ul, 0x8708A3D2ul, 0x1E01F268ul, 0x6906C2FEul, 0xF762575Dul, 0x806567CBul,
    0x196C3671ul, 0x6E6B06E7ul, 0xFED41B76ul, 0x89D32BE0ul, 0x10DA7A5Aul, 0x67DD4ACCul,
    0xF9B9DF6Ful, 0x8EBEEFF9ul, 0x17B7BE43ul, 0x60B08ED5ul, 0xD6D6A3E8ul, 0xA1D1937Eul,
    0x38D8C2C4ul, 0x4FDFF252ul, 0xD1BB67F1ul, 0xA6BC5767ul, 0x3FB506DDul, 0x48B2364Bul,
    0xD80D2BDAul, 0xAF0A1B4Cul, 0x36034AF6ul, 0x41047A60ul, 0xDF60EFC3ul, 0xA867DF55ul,
    0x316E8EEFul, 0x4669BE79ul, 0xCB61B38Cul, 0xBC66831Aul, 0x256FD2A0ul, 0x5268E236ul,
    0xCC0C7795ul, 0xBB0B4703ul, 0x220216B9ul, 0x5505262Ful, 0xC5BA3BBEul, 0xB2BD0B28ul,
    0x2BB45A92ul, 0x5CB36A04ul, 0xC2D7FFA7ul, 0xB5D0CF31ul, 0x2CD99E8Bul, 0x5BDEAE1Dul,
    0x9B64C2B0ul, 0xEC63F226ul, 0x756AA39Cul, 0x026D930Aul, 0x9C0906A9ul, 0xEB0E363Ful,
    0x72076785ul, 0x05005713ul, 0x95BF4A82ul, 0xE2B87A14ul, 0x7BB12BAEul, 0x0CB61B38ul,
    0x92D28E9Bul, 0xE5D5BE0Dul, 0x7CDCEFB7ul, 0x0BDBDF21ul, 0x86D3D2D4ul, 0xF1D4E242ul,
    0x68DDB3F8ul, 0x1FDA836Eul, 0x81BE16CDul, 0xF6B9265Bul, 0x6FB077E1ul, 0x18B74777ul,
    0x88085AE6ul, 0xFF0F6A70ul, 0x66063BCAul, 0x11010B5Cul, 0x8F659EFFul, 0xF862AE69ul,
    0x616BFFD3ul, 0x166CCF45ul, 0xA00AE278ul, 0xD70DD2EEul, 0x4E048354ul, 0x3903B3C2ul,
    0xA7672661ul, 0xD06016F7ul, 0x4969474Dul, 0x3E6E77DBul, 0xAED16A4Aul, 0xD9D65ADCul,
    0x40DF0B66ul, 0x37D83BF0ul, 0xA9BCAE53ul, 0xDEBB9EC5ul, 0x47B2CF7Ful, 0x30B5FFE9ul,
    0xBDBDF21Cul, 0xCABAC28Aul, 0x53B39330ul, 0x24B4A3A6ul, 0xBAD03605ul, 0xCDD70693ul,
    0x54DE5729ul, 0x23D967BFul, 0xB3667A2Eul, 0xC4614AB8ul, 0x5D681B02ul, 0x2A6F2B94ul,
    0xB40BBE37ul, 0xC30C8EA1ul, 0x5A05DF1Bul, 0x2D02EF8Dul
};

/**
 * @brief Fingerprint 4 calculate crc function.
 * @details This function calculates CRC 32 value of the input parameters.
 * @param[in] buf : Input buffer to calculate the CRC from.
 * @param[in] size : The size of the buffer for calculation in bytes.
 * @return Calculated CRC-32 value.
 * @note None.
 */
static uint32_t fingerprint4_calculate_crc ( void *buf, uint32_t size );

/**
 * @brief Fingerprint 4 rx link function.
 * @details This function reads the received packet on the physical layer and stores it in
 * the @b ctx->phy_pkt.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
static err_t fingerprint4_rx_link ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 tx link function.
 * @details This function sends the the @b ctx->phy_pkt packet on the physical layer.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
static err_t fingerprint4_tx_link ( fingerprint4_t *ctx );

void fingerprint4_cfg_setup ( fingerprint4_cfg_t *cfg ) 
{    
#if ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_SPI )
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->irq  = HAL_PIN_NC;
    
    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
#elif ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_UART )
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    cfg->rst    = HAL_PIN_NC;
    
    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
#endif
}

err_t fingerprint4_init ( fingerprint4_t *ctx, fingerprint4_cfg_t *cfg ) 
{
#if ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_SPI )
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
    
    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->irq, cfg->irq );

#elif ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_UART )
    uart_config_t uart_cfg;

    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    digital_out_init( &ctx->rst, cfg->rst );
#endif
    return FINGERPRINT4_RES_OK;
}

err_t fingerprint4_generic_write ( fingerprint4_t *ctx, uint8_t *data_in, uint16_t len )
{
#if ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_SPI )
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
#elif ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_UART )
    uart_write( &ctx->uart, data_in, len );
    return FINGERPRINT4_RES_OK;
#endif
}

err_t fingerprint4_generic_read ( fingerprint4_t *ctx, uint8_t *data_out, uint16_t len )
{
#if ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_SPI )
    uint32_t timeout_cnt = 0;
    while ( !fingerprint4_get_irq_pin ( ctx ) )
    {
        if ( ctx->phy_rx_timeout && ( timeout_cnt++ > ctx->phy_rx_timeout ) )
        {
            return FINGERPRINT4_RES_TIMEOUT;
        }
        Delay_1ms ( );
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
#elif ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_UART )
    uint32_t timeout_cnt = 0;
    uint16_t cnt = 0;
    while ( cnt < len )
    {
        if ( ctx->phy_rx_timeout && ( timeout_cnt++ > ctx->phy_rx_timeout ) )
        {
            return FINGERPRINT4_RES_TIMEOUT;
        }
        if ( 1 == uart_read( &ctx->uart, &data_out[ cnt ], 1 ) )
        {
            cnt++;
        }
        Delay_1ms ( );
    }
    return FINGERPRINT4_RES_OK;
#endif
}

void fingerprint4_set_rst_pin ( fingerprint4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

#if ( FINGERPRINT4_DRV_INTERFACE == FINGERPRINT4_DRV_INTERFACE_SPI )
uint8_t fingerprint4_get_irq_pin ( fingerprint4_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}
#endif

void fingerprint4_reset_device ( fingerprint4_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

err_t fingerprint4_init_cmd ( fingerprint4_t *ctx, uint16_t cmd, uint16_t arg_key )
{
    ctx->phy_pkt.hcp_packet.cmd_id = cmd;
    ctx->phy_pkt.hcp_packet.num_args = 0;
    ctx->phy_pkt.t_size = 4;
    if ( FINGERPRINT4_ARG_NONE != arg_key ) 
    {
        return fingerprint4_add_arg ( ctx, arg_key, NULL, 0 );
    }    
    return FINGERPRINT4_RES_OK;
}

err_t fingerprint4_add_arg ( fingerprint4_t *ctx, uint16_t arg_key, void *arg_data, uint16_t arg_size )
{
    if ( ( ctx->phy_pkt.t_size + 4 + arg_size ) > FINGERPRINT4_TRANSPORT_LAYER_PLD_SIZE ) 
    {
        return FINGERPRINT4_RES_NO_MEMORY;
    }
    ctx->phy_pkt.hcp_packet.num_args++;
    memcpy ( &ctx->phy_pkt.hcp_packet.args[ ctx->phy_pkt.t_size - 4 ], ( uint8_t * ) &arg_key, 2 );
    memcpy ( &ctx->phy_pkt.hcp_packet.args[ ctx->phy_pkt.t_size - 2 ], ( uint8_t * ) &arg_size, 2 );
    if ( arg_size )
    {
        memcpy( &ctx->phy_pkt.hcp_packet.args[ ctx->phy_pkt.t_size ], arg_data, arg_size );
    }
    ctx->phy_pkt.t_size += 4 + arg_size;
    return FINGERPRINT4_RES_OK;
}

err_t fingerprint4_get_arg ( fingerprint4_t *ctx, uint16_t arg_key )
{
    uint16_t cnt = 0, arg, arg_size, offset = 0;
    memcpy ( ( uint8_t * ) &arg, &ctx->phy_pkt.hcp_packet.args[ offset ], 2 );
    memcpy ( ( uint8_t * ) &arg_size, &ctx->phy_pkt.hcp_packet.args[ offset + 2 ], 2 );
    while ( cnt < ctx->phy_pkt.hcp_packet.num_args ) 
    {
        if ( arg == arg_key ) 
        {
            ctx->arg.arg = arg;
            ctx->arg.size = arg_size;
            memcpy ( &ctx->arg.payload, &ctx->phy_pkt.hcp_packet.args[ offset + 4 ], arg_size );
            return FINGERPRINT4_RES_OK;
        } 
        else 
        {
            cnt++;
            offset += 4 + arg_size;
            memcpy ( ( uint8_t * ) &arg, &ctx->phy_pkt.hcp_packet.args[ offset ], 2 );
            memcpy ( ( uint8_t * ) &arg_size, &ctx->phy_pkt.hcp_packet.args[ offset + 2 ], 2 );
        }
    }
    return FINGERPRINT4_RES_INVALID_ARGUMENT;
}

err_t fingerprint4_copy_arg ( fingerprint4_t *ctx, uint16_t arg_key, void *arg_data, uint16_t arg_size )
{
    if ( FINGERPRINT4_RES_OK == fingerprint4_get_arg ( ctx, arg_key ) ) 
    {
        if ( NULL == arg_data ) 
        {
            return FINGERPRINT4_RES_NO_MEMORY;
        }
        if ( arg_size < ctx->arg.size )
        {
            memcpy ( arg_data, &ctx->arg.payload, arg_size );
        }
        else
        {
            memcpy ( arg_data, &ctx->arg.payload, ctx->arg.size );
        }
        return FINGERPRINT4_RES_OK;
    }
    return FINGERPRINT4_RES_INVALID_ARGUMENT;
}

err_t fingerprint4_transceive ( fingerprint4_t *ctx )
{
    err_t error_flag = fingerprint4_send ( ctx );
    if ( FINGERPRINT4_RES_OK == error_flag ) 
    {
        error_flag = fingerprint4_receive ( ctx );
        fingerprint4_get_arg ( ctx, FINGERPRINT4_ARG_RESULT );
    }
    return error_flag;
}

err_t fingerprint4_receive ( fingerprint4_t *ctx )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    uint16_t seq_nr = 0;
    uint16_t seq_len = 1;
    while ( seq_nr < seq_len ) 
    {
        error_flag = fingerprint4_rx_link ( ctx );
        if ( error_flag ) 
        {
            return error_flag;
        }
        seq_nr = ctx->phy_pkt.t_seq_nr;
        seq_len = ctx->phy_pkt.t_seq_len;
        if ( ctx->phy_pkt.t_size != ( ctx->phy_pkt.lnk_size - 6 ) ) 
        {
            error_flag = FINGERPRINT4_RES_IO_ERROR;
            return error_flag;
        }
    }
    return error_flag;
}

err_t fingerprint4_send ( fingerprint4_t *ctx )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    uint16_t data_left = ctx->phy_pkt.t_size;

    // Calculate sequence length
    uint16_t seq_len = ( data_left / FINGERPRINT4_TRANSPORT_LAYER_PLD_SIZE ) + 1;

    ctx->phy_pkt.lnk_chn = 0;
    ctx->phy_pkt.t_seq_len = seq_len;

    for ( uint16_t seq_nr = 1; ( seq_nr <= seq_len ) && ( FINGERPRINT4_RES_OK == error_flag ); seq_nr++ ) 
    {
        ctx->phy_pkt.t_seq_nr = seq_nr;
        if ( data_left < FINGERPRINT4_TRANSPORT_LAYER_PLD_SIZE ) 
        {
            ctx->phy_pkt.t_size = data_left;
        } 
        else
        {
            ctx->phy_pkt.t_size = FINGERPRINT4_TRANSPORT_LAYER_PLD_SIZE;
        }
        ctx->phy_pkt.lnk_size = ctx->phy_pkt.t_size + 6;
        data_left -= ctx->phy_pkt.t_size;
        error_flag = fingerprint4_tx_link( ctx );
    }
    return error_flag;
}

err_t fingerprint4_send_cmd ( fingerprint4_t *ctx, uint16_t cmd, uint16_t arg_key )
{
    err_t error_flag = fingerprint4_init_cmd ( ctx, cmd, arg_key );
    if ( error_flag )
    {
        return error_flag;
    }
    return fingerprint4_transceive ( ctx );
}

err_t fingerprint4_send_cmd_arg ( fingerprint4_t *ctx, uint16_t cmd, uint16_t arg1_key, 
                                  uint16_t arg2_key, void *arg2_data, uint16_t arg2_length )
{
    err_t error_flag = fingerprint4_init_cmd ( ctx, cmd, arg1_key );
    if ( error_flag )
    {
        return error_flag;
    }
    error_flag = fingerprint4_add_arg ( ctx, arg2_key, arg2_data, arg2_length );
    if ( error_flag )
    {
        return error_flag;
    }
    return fingerprint4_transceive ( ctx );
}

err_t fingerprint4_identify_finger ( fingerprint4_t *ctx, uint32_t timeout, uint16_t *template_id, bool *match )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    *match = false;
    uint32_t prev_timeout = ctx->phy_rx_timeout;
    ctx->phy_rx_timeout = timeout;
    error_flag = fingerprint4_send_cmd_arg ( ctx, FINGERPRINT4_CMD_CAPTURE, FINGERPRINT4_ARG_NONE, 
                                             FINGERPRINT4_ARG_TIMEOUT, &timeout, sizeof ( timeout ) );
    ctx->phy_rx_timeout = prev_timeout;
    if ( error_flag )
    {
        return error_flag;
    }
    error_flag = fingerprint4_image_extract ( ctx );
    if ( error_flag )
    {
        return error_flag;
    }
    error_flag = fingerprint4_identify ( ctx );
    if ( error_flag )
    {
        return error_flag;
    }
    error_flag = fingerprint4_get_arg ( ctx, FINGERPRINT4_ARG_MATCH );
    if ( error_flag )
    {
        return error_flag;
    }
    *match = ctx->arg.payload[ 0 ] & 0x01;
    if ( *match ) 
    {
        fingerprint4_copy_arg ( ctx, FINGERPRINT4_ARG_ID, ( uint8_t * ) template_id, 2 );
        // Delay for possible updating template on BM-Lite
        Delay_100ms ( );
    }
    return error_flag;    
}

err_t fingerprint4_wait_finger_present ( fingerprint4_t *ctx, uint32_t timeout )
{
    uint32_t prev_timeout = ctx->phy_rx_timeout;
    ctx->phy_rx_timeout = timeout;
    err_t error_flag = fingerprint4_send_cmd_arg ( ctx, FINGERPRINT4_CMD_WAIT, FINGERPRINT4_ARG_FINGER_DOWN, 
                                                   FINGERPRINT4_ARG_TIMEOUT, &timeout, sizeof ( timeout ) );
    ctx->phy_rx_timeout = prev_timeout;
    return error_flag;
}

err_t fingerprint4_wait_finger_not_present ( fingerprint4_t *ctx, uint32_t timeout )
{
    uint32_t prev_timeout = ctx->phy_rx_timeout;
    ctx->phy_rx_timeout = timeout;
    err_t error_flag = fingerprint4_send_cmd_arg ( ctx, FINGERPRINT4_CMD_WAIT, FINGERPRINT4_ARG_FINGER_UP, 
                                                   FINGERPRINT4_ARG_TIMEOUT, &timeout, sizeof ( timeout ) );
    ctx->phy_rx_timeout = prev_timeout;
    return error_flag;
}

err_t fingerprint4_image_get_size ( fingerprint4_t *ctx, uint32_t *size )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    error_flag = fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_IMAGE, FINGERPRINT4_ARG_SIZE );
    if ( error_flag )
    {
        return error_flag;
    }
    error_flag = fingerprint4_get_arg ( ctx, FINGERPRINT4_ARG_SIZE );
    if ( error_flag )
    {
        return error_flag;
    }
    memcpy ( ( uint8_t * ) size, &ctx->arg.payload[ 0 ], 4 );
    return FINGERPRINT4_RES_OK;
}

err_t fingerprint4_image_create ( fingerprint4_t *ctx )
{
    return fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_IMAGE, FINGERPRINT4_ARG_CREATE );
}

err_t fingerprint4_image_delete ( fingerprint4_t *ctx )
{
    return fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_IMAGE, FINGERPRINT4_ARG_DELETE );
}

err_t fingerprint4_image_get ( fingerprint4_t *ctx, uint8_t *data_out, uint32_t size )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    error_flag = fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_IMAGE, FINGERPRINT4_ARG_UPLOAD );
    if ( error_flag )
    {
        return error_flag;
    }
    return fingerprint4_copy_arg ( ctx, FINGERPRINT4_ARG_DATA, data_out, size );
}

err_t fingerprint4_image_put ( fingerprint4_t *ctx, uint8_t *data_in, uint32_t size )
{
    return fingerprint4_send_cmd_arg ( ctx, FINGERPRINT4_CMD_IMAGE, FINGERPRINT4_ARG_DOWNLOAD, 
                                       FINGERPRINT4_ARG_DATA, data_in, sizeof ( size ) );
}

err_t fingerprint4_image_extract ( fingerprint4_t *ctx )
{
    return fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_IMAGE, FINGERPRINT4_ARG_EXTRACT );
}

err_t fingerprint4_identify ( fingerprint4_t *ctx )
{
    return fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_IDENTIFY, FINGERPRINT4_ARG_NONE );
}

err_t fingerprint4_template_save ( fingerprint4_t *ctx, uint16_t template_id )
{
    return fingerprint4_send_cmd_arg ( ctx, FINGERPRINT4_CMD_TEMPLATE, FINGERPRINT4_ARG_SAVE, 
                                       FINGERPRINT4_ARG_ID, &template_id, sizeof ( template_id ) );
}

err_t fingerprint4_template_remove_ram ( fingerprint4_t *ctx )
{
    return fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_TEMPLATE, FINGERPRINT4_ARG_DELETE );
}

err_t fingerprint4_template_get ( fingerprint4_t *ctx, uint8_t *data_out, uint32_t size )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    error_flag = fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_TEMPLATE, FINGERPRINT4_ARG_UPLOAD );
    if ( error_flag )
    {
        return error_flag;
    }
    return fingerprint4_copy_arg ( ctx, FINGERPRINT4_ARG_DATA, data_out, size );
}

err_t fingerprint4_template_put ( fingerprint4_t *ctx, uint8_t *data_in, uint16_t size )
{
    return fingerprint4_send_cmd_arg ( ctx, FINGERPRINT4_CMD_TEMPLATE, FINGERPRINT4_ARG_DOWNLOAD, 
                                       FINGERPRINT4_ARG_DATA, data_in, size );
}

err_t fingerprint4_template_remove ( fingerprint4_t *ctx, uint16_t template_id )
{
    return fingerprint4_send_cmd_arg ( ctx, FINGERPRINT4_CMD_STORAGE_TEMPLATE, FINGERPRINT4_ARG_DELETE, 
                                       FINGERPRINT4_ARG_ID, &template_id, sizeof ( template_id ) );
}

err_t fingerprint4_template_remove_all ( fingerprint4_t *ctx )
{
    return fingerprint4_send_cmd_arg ( ctx, FINGERPRINT4_CMD_STORAGE_TEMPLATE, FINGERPRINT4_ARG_DELETE, 
                                       FINGERPRINT4_ARG_ALL, 0, 0 );
}

err_t fingerprint4_template_load_storage ( fingerprint4_t *ctx, uint16_t template_id )
{
    return fingerprint4_send_cmd_arg ( ctx, FINGERPRINT4_CMD_STORAGE_TEMPLATE, FINGERPRINT4_ARG_UPLOAD, 
                                       FINGERPRINT4_ARG_ID, &template_id, sizeof ( template_id ) );
}

err_t fingerprint4_template_get_count ( fingerprint4_t *ctx, uint16_t *count )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    error_flag = fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_STORAGE_TEMPLATE, FINGERPRINT4_ARG_COUNT );
    if ( error_flag )
    {
        return error_flag;
    }
    error_flag = fingerprint4_get_arg ( ctx, FINGERPRINT4_ARG_COUNT );
    if ( error_flag )
    {
        return error_flag;
    }
    memcpy ( ( uint8_t * ) count, &ctx->arg.payload[ 0 ], 2 );
    return FINGERPRINT4_RES_OK;
}

err_t fingerprint4_template_get_ids ( fingerprint4_t *ctx )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    error_flag = fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_STORAGE_TEMPLATE, FINGERPRINT4_ARG_ID );
    if ( error_flag )
    {
        return error_flag;
    }
    return fingerprint4_get_arg ( ctx, FINGERPRINT4_ARG_DATA );
}

err_t fingerprint4_sw_reset ( fingerprint4_t *ctx )
{
    return fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_RESET, FINGERPRINT4_ARG_NONE );
}

err_t fingerprint4_sensor_calibrate ( fingerprint4_t *ctx )
{
    return fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_STORAGE_CALIBRATION, FINGERPRINT4_ARG_NONE );
}

err_t fingerprint4_sensor_calibrate_remove ( fingerprint4_t *ctx )
{
    return fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_STORAGE_CALIBRATION, FINGERPRINT4_ARG_DELETE );
}

err_t fingerprint4_version ( fingerprint4_t *ctx, char *version, uint8_t len )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    error_flag = fingerprint4_send_cmd_arg ( ctx, FINGERPRINT4_CMD_INFO, FINGERPRINT4_ARG_GET, 
                                             FINGERPRINT4_ARG_VERSION, 0, 0 );
    if ( error_flag )
    {
        return error_flag;
    }
    return fingerprint4_copy_arg ( ctx, FINGERPRINT4_ARG_VERSION, version, len );
}

err_t fingerprint4_unique_id_get ( fingerprint4_t *ctx, uint8_t *unique_id )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    error_flag = fingerprint4_send_cmd_arg ( ctx, FINGERPRINT4_CMD_INFO, FINGERPRINT4_ARG_GET, 
                                             FINGERPRINT4_ARG_UNIQUE_ID, 0, 0 );
    if ( error_flag )
    {
        return error_flag;
    }
    return fingerprint4_copy_arg ( ctx, FINGERPRINT4_ARG_UNIQUE_ID, unique_id, 12 );
}

err_t fingerprint4_uart_speed_set ( fingerprint4_t *ctx, uint32_t speed )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    error_flag = fingerprint4_init_cmd ( ctx, FINGERPRINT4_CMD_COMMUNICATION, FINGERPRINT4_ARG_SPEED );
    if ( error_flag )
    {
        return error_flag;
    }
    error_flag = fingerprint4_add_arg ( ctx, FINGERPRINT4_ARG_SET, 0, 0 );
    if ( error_flag )
    {
        return error_flag;
    }
    error_flag = fingerprint4_add_arg ( ctx, FINGERPRINT4_ARG_DATA, ( uint8_t * ) &speed, sizeof ( speed ) );
    if ( error_flag )
    {
        return error_flag;
    }
    return fingerprint4_transceive ( ctx );
}

err_t fingerprint4_uart_speed_get ( fingerprint4_t *ctx, uint32_t *speed )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    error_flag = fingerprint4_init_cmd ( ctx, FINGERPRINT4_CMD_COMMUNICATION, FINGERPRINT4_ARG_SPEED );
    if ( error_flag )
    {
        return error_flag;
    }
    error_flag = fingerprint4_add_arg ( ctx, FINGERPRINT4_ARG_GET, 0, 0 );
    if ( error_flag )
    {
        return error_flag;
    }
    error_flag = fingerprint4_transceive ( ctx );
    if ( error_flag )
    {
        return error_flag;
    }
    return fingerprint4_copy_arg ( ctx, FINGERPRINT4_ARG_DATA, speed, sizeof ( speed ) );
}

err_t fingerprint4_sensor_reset ( fingerprint4_t *ctx )
{
    // Delay for possible updating template on BM-Lite
    Delay_100ms ( );
    return fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_SENSOR, FINGERPRINT4_ARG_RESET );    
}

static uint32_t fingerprint4_calculate_crc ( void *buf, uint32_t size )
{
    uint8_t *ptr = ( uint8_t * ) buf;
    uint32_t crc = 0xFFFFFFFFul;
    while ( size-- ) 
    {
        crc = fingerprint4_crc32_table [ ( crc ^ *ptr++ ) & 0xFF ] ^ ( crc >> 8 );
    }
    return crc ^ 0xFFFFFFFFul;
}

static err_t fingerprint4_rx_link ( fingerprint4_t *ctx )
{
    // Get link layer channel and size
    err_t error_flag = fingerprint4_generic_read ( ctx, ( uint8_t * ) &ctx->phy_pkt, 4 );
    if ( error_flag ) 
    {
        return error_flag;
    }
    // Check if size plus header and crc is larger than max package size.
    if ( FINGERPRINT4_PHY_MTU_SIZE < ( ctx->phy_pkt.lnk_size + 8 ) ) 
    {
        return FINGERPRINT4_RES_IO_ERROR;
    }
        
    fingerprint4_generic_read ( ctx, ( uint8_t * ) &ctx->phy_pkt.t_size, ctx->phy_pkt.lnk_size + 4 );
    memcpy ( ( uint8_t * ) &ctx->phy_pkt.crc, &ctx->phy_pkt.hcp_packet.args[ ctx->phy_pkt.lnk_size - 10 ], 4 );

    if ( ctx->phy_pkt.crc != fingerprint4_calculate_crc ( &ctx->phy_pkt.t_size, ctx->phy_pkt.lnk_size ) ) 
    {
        return FINGERPRINT4_RES_IO_ERROR;
    }
    
    // Send Ack
    uint32_t com_ack = FINGERPRINT4_ACK_BYTES;
    fingerprint4_generic_write ( ctx, ( uint8_t * ) &com_ack, 4 );
    return FINGERPRINT4_RES_OK;
}

static err_t fingerprint4_tx_link ( fingerprint4_t *ctx )
{
    ctx->phy_pkt.crc = fingerprint4_calculate_crc ( &ctx->phy_pkt.t_size, ctx->phy_pkt.lnk_size );
    memcpy ( &ctx->phy_pkt.hcp_packet.args[ ctx->phy_pkt.lnk_size - 10 ], ( uint8_t * ) &ctx->phy_pkt.crc, 4 );
    err_t error_flag = fingerprint4_generic_write ( ctx, ( uint8_t * ) &ctx->phy_pkt, ctx->phy_pkt.lnk_size + 8 );

    // Wait for ACK
    uint32_t ack = 0;
    error_flag = fingerprint4_generic_read ( ctx, ( uint8_t * ) &ack, 4 );
    if ( ( FINGERPRINT4_RES_TIMEOUT == error_flag ) || ( FINGERPRINT4_ACK_BYTES != ack ) ) 
    {
        return FINGERPRINT4_RES_IO_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
