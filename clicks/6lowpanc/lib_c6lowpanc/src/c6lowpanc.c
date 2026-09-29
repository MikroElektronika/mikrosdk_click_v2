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
 * @file c6lowpanc.c
 * @brief 6LoWPAN C Click Driver.
 */

#include "c6lowpanc.h"

/** Maximum number of one-millisecond polls while waiting for the radio. */
#define C6LOWPANC_READY_TIMEOUT_MS       100

/** Maximum number of one-millisecond polls for a complete frame transmission. */
#define C6LOWPANC_TX_TIMEOUT_MS          20

/**
 * @brief 6LoWPAN C wait status function.
 * @details This function polls 6LoWPAN C Click until all requested status bits are set.
 * @param[in] ctx : Click context object.
 * See #c6lowpanc_t object definition for detailed explanation.
 * @param[in] mask : Required status bits.
 * @return C6LOWPANC_OK, C6LOWPANC_TIMEOUT, or C6LOWPANC_ERROR.
 * @note Uses at most C6LOWPANC_READY_TIMEOUT_MS fixed one-millisecond delays.
 */
static err_t c6lowpanc_wait_status ( c6lowpanc_t *ctx, uint8_t mask );

/**
 * @brief 6LoWPAN C verified register write function.
 * @details This function writes a 6LoWPAN C Click register and compares its readback.
 * @param[in] ctx : Click context object.
 * See #c6lowpanc_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] value : Expected register value.
 * @return C6LOWPANC_OK or C6LOWPANC_ERROR.
 * @note Use only for readable configuration registers.
 */
static err_t c6lowpanc_write_verify ( c6lowpanc_t *ctx, uint8_t reg, uint8_t value );

/**
 * @brief 6LoWPAN C write FIFO function.
 * @details This function appends bytes to the 6LoWPAN C Click transmit FIFO.
 * @param[in] ctx : Click context object.
 * See #c6lowpanc_t object definition for detailed explanation.
 * @param[in] data_in : Input bytes.
 * @param[in] len : Number of bytes to append.
 * @return C6LOWPANC_OK or C6LOWPANC_ERROR.
 * @note The caller must ensure that the complete frame fits in the radio TX FIFO.
 */
static err_t c6lowpanc_write_fifo ( c6lowpanc_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief 6LoWPAN C read FIFO function.
 * @details This function removes bytes from the 6LoWPAN C Click receive FIFO.
 * @param[in] ctx : Click context object.
 * See #c6lowpanc_t object definition for detailed explanation.
 * @param[out] data_out : Output buffer.
 * @param[in] len : Number of available bytes to read.
 * @return C6LOWPANC_OK or C6LOWPANC_ERROR.
 * @note The caller must check that the FIFO contains the requested bytes.
 */
static err_t c6lowpanc_read_fifo ( c6lowpanc_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief 6LoWPAN C flush receive FIFO function.
 * @details This function discards queued 6LoWPAN C Click frames and clears receive FIFO errors.
 * @param[in] ctx : Click context object.
 * See #c6lowpanc_t object definition for detailed explanation.
 * @return C6LOWPANC_OK or C6LOWPANC_ERROR.
 * @note Flushes twice as required by the radio errata. An active receiver recalibrates after a flush.
 */
static err_t c6lowpanc_flush_rx ( c6lowpanc_t *ctx );

void c6lowpanc_cfg_setup ( c6lowpanc_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->gp0  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->ven  = HAL_PIN_NC;
    cfg->gp1  = HAL_PIN_NC;

    cfg->spi_speed   = C6LOWPANC_DEFAULT_SPI_SPEED;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t c6lowpanc_init ( c6lowpanc_t *ctx, c6lowpanc_cfg_t *cfg ) 
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, C6LOWPANC_CMD_SNOP ) ) 
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
    digital_out_init( &ctx->ven, cfg->ven );
    digital_out_low( &ctx->rst );
    digital_out_low( &ctx->ven );

    digital_in_init( &ctx->gp0, cfg->gp0 );
    digital_in_init( &ctx->gp1, cfg->gp1 );

    ctx->pan_id = C6LOWPANC_DEFAULT_PAN_ID;
    ctx->short_addr = C6LOWPANC_DEFAULT_SHORT_ADDR;
    ctx->sequence = 0;
    ctx->mode = C6LOWPANC_MODE_TX;

    return C6LOWPANC_OK;
}

err_t c6lowpanc_default_cfg ( c6lowpanc_t *ctx ) 
{
    uint8_t config[][ 2 ] =
    {
        { C6LOWPANC_REG_TXPOWER, C6LOWPANC_DEFAULT_TX_POWER },
        { C6LOWPANC_REG_CCACTRL0, C6LOWPANC_DEFAULT_CCACTRL0 },
        { C6LOWPANC_REG_MDMCTRL0, C6LOWPANC_DEFAULT_MDMCTRL0 },
        { C6LOWPANC_REG_MDMCTRL1, C6LOWPANC_DEFAULT_MDMCTRL1 },
        { C6LOWPANC_REG_RXCTRL, C6LOWPANC_DEFAULT_RXCTRL },
        { C6LOWPANC_REG_FSCTRL, C6LOWPANC_DEFAULT_FSCTRL },
        { C6LOWPANC_REG_FSCAL1, C6LOWPANC_DEFAULT_FSCAL1 },
        { C6LOWPANC_REG_AGCCTRL1, C6LOWPANC_DEFAULT_AGCCTRL1 },
        { C6LOWPANC_REG_ADCTEST0, C6LOWPANC_DEFAULT_ADCTEST0 },
        { C6LOWPANC_REG_ADCTEST1, C6LOWPANC_DEFAULT_ADCTEST1 },
        { C6LOWPANC_REG_ADCTEST2, C6LOWPANC_DEFAULT_ADCTEST2 },
        { C6LOWPANC_REG_FRMFILT0, C6LOWPANC_DEFAULT_FRMFILT0 },
        { C6LOWPANC_REG_FRMFILT1, C6LOWPANC_ACCEPT_DATA_FRAMES },
        { C6LOWPANC_REG_SRCMATCH, C6LOWPANC_DEFAULT_SRCMATCH },
        { C6LOWPANC_REG_FRMCTRL0, C6LOWPANC_AUTOCRC },
        { C6LOWPANC_REG_FRMCTRL1, C6LOWPANC_DEFAULT_FRMCTRL1 },
        { C6LOWPANC_REG_FIFOPCTRL, C6LOWPANC_DEFAULT_FIFOPCTRL },
        { C6LOWPANC_REG_GPIOCTRL0, C6LOWPANC_GPIO_SFD },
        { C6LOWPANC_REG_GPIOCTRL1, C6LOWPANC_GPIO_FIFOP }
    };
    uint8_t index;
    err_t error_flag;

    error_flag = c6lowpanc_reset( ctx );
    // Apply the datasheet's analog tuning, then enable data-frame filtering and hardware CRC.
    for ( index = 0; ( index < sizeof( config ) / sizeof( config[ 0 ] ) ) &&
                     ( C6LOWPANC_OK == error_flag ); index++ )
    {
        error_flag = c6lowpanc_write_reg( ctx, config[ index ][ 0 ], config[ index ][ 1 ] );
    }
    if ( C6LOWPANC_OK == error_flag )
    {
        error_flag = c6lowpanc_set_channel( ctx, C6LOWPANC_DEFAULT_CHANNEL );
    }
    if ( C6LOWPANC_OK == error_flag )
    {
        error_flag = c6lowpanc_set_address( ctx, C6LOWPANC_DEFAULT_PAN_ID, C6LOWPANC_DEFAULT_SHORT_ADDR );
    }
    if ( C6LOWPANC_OK == error_flag )
    {
        error_flag = c6lowpanc_send_command( ctx, C6LOWPANC_CMD_SFLUSHTX );
    }
    if ( C6LOWPANC_OK == error_flag )
    {
        error_flag = c6lowpanc_flush_rx( ctx );
    }

    return error_flag;
}

err_t c6lowpanc_write_reg ( c6lowpanc_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return c6lowpanc_write_regs( ctx, reg, &data_in, 1 );
}

err_t c6lowpanc_write_regs ( c6lowpanc_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t command;
    err_t error_flag = C6LOWPANC_ERROR;

    if ( ( NULL != data_in ) && ( len > 0 ) && ( reg <= C6LOWPANC_REG_END ) &&
         ( len <= C6LOWPANC_REG_END + 1 - reg ) )
    {
        spi_master_select_device( ctx->chip_select );
        // REGWR addresses FREG only. MEMWR is required for SREG and boundary-crossing bursts.
        if ( ( reg < C6LOWPANC_FREG_LIMIT ) && ( len <= C6LOWPANC_FREG_LIMIT - reg ) )
        {
            command = C6LOWPANC_CMD_REGWR | reg;
            error_flag = spi_master_write( &ctx->spi, &command, 1 );
        }
        else
        {
            command = C6LOWPANC_CMD_MEMWR;
            error_flag = spi_master_write( &ctx->spi, &command, 1 );
            if ( C6LOWPANC_OK == error_flag )
            {
                command = reg;
                error_flag = spi_master_write( &ctx->spi, &command, 1 );
            }
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = spi_master_write( &ctx->spi, data_in, len );
        }
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

err_t c6lowpanc_read_reg ( c6lowpanc_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return c6lowpanc_read_regs( ctx, reg, data_out, 1 );
}

err_t c6lowpanc_read_regs ( c6lowpanc_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t command[ 2 ];
    err_t error_flag = C6LOWPANC_ERROR;

    if ( ( NULL != data_out ) && ( len > 0 ) && ( reg <= C6LOWPANC_REG_END ) &&
         ( len <= C6LOWPANC_REG_END + 1 - reg ) )
    {
        spi_master_select_device( ctx->chip_select );
        // REGRD addresses FREG only. MEMRD is required for SREG and boundary-crossing bursts.
        if ( ( reg < C6LOWPANC_FREG_LIMIT ) && ( len <= C6LOWPANC_FREG_LIMIT - reg ) )
        {
            command[ 0 ] = C6LOWPANC_CMD_REGRD | reg;
            error_flag = spi_master_write_then_read( &ctx->spi, command, 1, data_out, len );
        }
        else
        {
            command[ 0 ] = C6LOWPANC_CMD_MEMRD;
            command[ 1 ] = reg;
            error_flag = spi_master_write_then_read( &ctx->spi, command, 2, data_out, len );
        }
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

err_t c6lowpanc_write_memory ( c6lowpanc_t *ctx, uint16_t address, uint8_t *data_in, uint16_t len )
{
    uint8_t command[ 2 ];
    err_t error_flag = C6LOWPANC_ERROR;

    if ( ( NULL != data_in ) && ( len > 0 ) &&
         ( ( ( address <= C6LOWPANC_REG_END ) && ( len <= C6LOWPANC_REG_END + 1 - address ) ) ||
           ( ( address >= C6LOWPANC_MEM_RAM_START ) && ( address <= C6LOWPANC_MEM_RAM_END ) &&
             ( len <= C6LOWPANC_MEM_RAM_END + 1 - address ) ) ) )
    {
        // MEMWR includes the upper address nibble, allowing access to both registers and RAM.
        command[ 0 ] = C6LOWPANC_CMD_MEMWR | ( uint8_t ) ( address >> 8 );
        command[ 1 ] = ( uint8_t ) address;
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_write( &ctx->spi, command, 2 );
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = spi_master_write( &ctx->spi, data_in, len );
        }
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

err_t c6lowpanc_read_memory ( c6lowpanc_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len )
{
    uint8_t command[ 2 ];
    err_t error_flag = C6LOWPANC_ERROR;

    if ( ( NULL != data_out ) && ( len > 0 ) &&
         ( ( ( address <= C6LOWPANC_REG_END ) && ( len <= C6LOWPANC_REG_END + 1 - address ) ) ||
           ( ( address >= C6LOWPANC_MEM_RAM_START ) && ( address <= C6LOWPANC_MEM_RAM_END ) &&
             ( len <= C6LOWPANC_MEM_RAM_END + 1 - address ) ) ) )
    {
        command[ 0 ] = C6LOWPANC_CMD_MEMRD | ( uint8_t ) ( address >> 8 );
        command[ 1 ] = ( uint8_t ) address;
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_write_then_read( &ctx->spi, command, 2, data_out, len );
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

err_t c6lowpanc_send_command ( c6lowpanc_t *ctx, uint8_t command )
{
    uint8_t data_buf[ 2 ];
    uint8_t len = 1;
    err_t error_flag = C6LOWPANC_ERROR;

    if ( ( C6LOWPANC_CMD_SNOP == command ) || ( C6LOWPANC_CMD_SRES == command ) ||
         ( ( command >= C6LOWPANC_CMD_SXOSCON ) && ( command <= C6LOWPANC_CMD_SNACK ) ) )
    {
        data_buf[ 0 ] = command;
        data_buf[ 1 ] = C6LOWPANC_CMD_SNOP;
        // Reset needs an operand byte; oscillator start must be followed immediately by SNOP.
        if ( ( C6LOWPANC_CMD_SRES == command ) || ( C6LOWPANC_CMD_SXOSCON == command ) )
        {
            len = 2;
        }
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_write( &ctx->spi, data_buf, len );
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

err_t c6lowpanc_get_status ( c6lowpanc_t *ctx, uint8_t *status )
{
    err_t error_flag = C6LOWPANC_ERROR;

    if ( NULL != status )
    {
        // The SPI read clocks the configured SNOP dummy byte and receives the simultaneous status byte.
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_read( &ctx->spi, status, 1 );
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

err_t c6lowpanc_reset ( c6lowpanc_t *ctx )
{
    uint8_t chip_id;
    uint8_t version;
    err_t error_flag;

    // Hold reset low until the internal regulator is stable before releasing the oscillator.
    digital_out_low( &ctx->rst );
    digital_out_low( &ctx->ven );
    Delay_1ms( );
    digital_out_high( &ctx->ven );
    Delay_1ms( );
    digital_out_high( &ctx->rst );
    Delay_1ms( );

    ctx->mode = C6LOWPANC_MODE_TX;
    ctx->sequence = 0;
    ctx->pan_id = C6LOWPANC_DEFAULT_PAN_ID;
    ctx->short_addr = C6LOWPANC_DEFAULT_SHORT_ADDR;
    error_flag = c6lowpanc_wait_status( ctx, C6LOWPANC_STATUS_XOSC_STABLE );
    if ( C6LOWPANC_OK == error_flag )
    {
        error_flag = c6lowpanc_get_id( ctx, &chip_id, &version );
        if ( ( C6LOWPANC_OK == error_flag ) && ( C6LOWPANC_CHIP_ID != chip_id ) )
        {
            error_flag = C6LOWPANC_ERROR;
        }
    }

    return error_flag;
}

err_t c6lowpanc_get_id ( c6lowpanc_t *ctx, uint8_t *chip_id, uint8_t *version )
{
    err_t error_flag = C6LOWPANC_ERROR;

    if ( ( NULL != chip_id ) && ( NULL != version ) )
    {
        error_flag = c6lowpanc_read_reg( ctx, C6LOWPANC_REG_CHIPID, chip_id );
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = c6lowpanc_read_reg( ctx, C6LOWPANC_REG_VERSION, version );
        }
    }

    return error_flag;
}

err_t c6lowpanc_set_mode ( c6lowpanc_t *ctx, uint8_t mode )
{
    uint8_t status;
    err_t error_flag = C6LOWPANC_ERROR;

    if ( ( C6LOWPANC_MODE_TX == mode ) || ( C6LOWPANC_MODE_RX == mode ) )
    {
        error_flag = c6lowpanc_get_status( ctx, &status );
        if ( ( C6LOWPANC_OK == error_flag ) &&
             ( status & ( C6LOWPANC_STATUS_TX_ACTIVE | C6LOWPANC_STATUS_RX_ACTIVE ) ) )
        {
            error_flag = c6lowpanc_send_command( ctx, C6LOWPANC_CMD_SRFOFF );
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = c6lowpanc_flush_rx( ctx );
        }
        if ( ( C6LOWPANC_OK == error_flag ) && ( C6LOWPANC_MODE_RX == mode ) )
        {
            error_flag = c6lowpanc_send_command( ctx, C6LOWPANC_CMD_SRXON );
            if ( C6LOWPANC_OK == error_flag )
            {
                // Mode changes discard any partial frame left by the command-strobe erratum.
                error_flag = c6lowpanc_flush_rx( ctx );
                Delay_1ms( );
            }
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            ctx->mode = mode;
        }
    }

    return error_flag;
}

err_t c6lowpanc_set_channel ( c6lowpanc_t *ctx, uint8_t channel )
{
    err_t error_flag = C6LOWPANC_ERROR;

    if ( ( channel >= C6LOWPANC_CHANNEL_MIN ) && 
         ( channel <= C6LOWPANC_CHANNEL_MAX ) &&
         ( C6LOWPANC_MODE_TX == ctx->mode ) )
    {
        // FREQCTRL uses its own base value; the displayed center frequency uses the channel frequency base.
        error_flag = c6lowpanc_write_verify( ctx, C6LOWPANC_REG_FREQCTRL, C6LOWPANC_FREQCTRL_BASE + 
                                                                          C6LOWPANC_CHANNEL_FREQUENCY_STEP *
                                                                          ( channel - C6LOWPANC_CHANNEL_MIN ) );
    }

    return error_flag;
}

err_t c6lowpanc_set_address ( c6lowpanc_t *ctx, uint16_t pan_id, uint16_t short_addr )
{
    uint8_t address[ 4 ];
    uint8_t readback[ 4 ];
    err_t error_flag = C6LOWPANC_ERROR;

    if ( ( C6LOWPANC_MODE_TX == ctx->mode ) && 
         ( pan_id <= C6LOWPANC_MAX_PAN_ID ) &&
         ( short_addr <= C6LOWPANC_MAX_SHORT_ADDR ) )
    {
        // PAN and short address are consecutive little-endian words in the address-filter RAM.
        address[ 0 ] = ( uint8_t ) pan_id;
        address[ 1 ] = ( uint8_t ) ( pan_id >> 8 );
        address[ 2 ] = ( uint8_t ) short_addr;
        address[ 3 ] = ( uint8_t ) ( short_addr >> 8 );
        error_flag = c6lowpanc_write_memory( ctx, C6LOWPANC_MEM_PAN_ID, address, sizeof( address ) );
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = c6lowpanc_read_memory( ctx, C6LOWPANC_MEM_PAN_ID, readback, sizeof( readback ) );
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            if ( 0 == memcmp( address, readback, sizeof( address ) ) )
            {
                ctx->pan_id = pan_id;
                ctx->short_addr = short_addr;
            }
            else
            {
                error_flag = C6LOWPANC_ERROR;
            }
        }
    }

    return error_flag;
}

err_t c6lowpanc_send_packet ( c6lowpanc_t *ctx, uint16_t destination, uint8_t *data_in, uint8_t len )
{
    uint8_t header[ C6LOWPANC_MAC_HEADER_SIZE + C6LOWPANC_LENGTH_FIELD_SIZE ];
    uint8_t restore_mode = ctx->mode;
    uint8_t status;
    uint8_t elapsed;
    uint8_t complete = 0;
    err_t error_flag = C6LOWPANC_ERROR;
    err_t cleanup_flag;

    if ( ( NULL != data_in ) && ( len > 0 ) && 
         ( len <= C6LOWPANC_MAX_PAYLOAD_SIZE ) &&
         ( destination != C6LOWPANC_RESERVED_SHORT_ADDR ) )
    {
        // Length includes the hardware-generated FCS, which is not written to the TX FIFO.
        header[ 0 ] = C6LOWPANC_MAC_HEADER_SIZE + len + C6LOWPANC_FCS_SIZE;
        header[ 1 ] = C6LOWPANC_FCF_DATA_LOW;
        header[ 2 ] = C6LOWPANC_FCF_DATA_HIGH;
        header[ 3 ] = ctx->sequence++;
        header[ 4 ] = ( uint8_t ) ctx->pan_id;
        header[ 5 ] = ( uint8_t ) ( ctx->pan_id >> 8 );
        header[ 6 ] = ( uint8_t ) destination;
        header[ 7 ] = ( uint8_t ) ( destination >> 8 );
        header[ 8 ] = ( uint8_t ) ctx->short_addr;
        header[ 9 ] = ( uint8_t ) ( ctx->short_addr >> 8 );

        error_flag = c6lowpanc_set_mode( ctx, C6LOWPANC_MODE_TX );
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = c6lowpanc_send_command( ctx, C6LOWPANC_CMD_SFLUSHTX );
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            // Exception flags are cleared by writing zero; leave unrelated bits unchanged.
            error_flag = c6lowpanc_write_reg( ctx, C6LOWPANC_REG_EXCFLAG0,
                         ( uint8_t ) ~( C6LOWPANC_EXC_TX_FRM_DONE | C6LOWPANC_EXC_TX_UNDERFLOW |
                                        C6LOWPANC_EXC_TX_OVERFLOW ) );
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = c6lowpanc_write_fifo( ctx, header, sizeof( header ) );
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = c6lowpanc_write_fifo( ctx, data_in, len );
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = c6lowpanc_set_mode( ctx, C6LOWPANC_MODE_RX );
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            // CCA is meaningful only after the receiver has produced a valid RSSI sample.
            error_flag = c6lowpanc_wait_status( ctx, C6LOWPANC_STATUS_RSSI_VALID );
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = c6lowpanc_send_command( ctx, C6LOWPANC_CMD_STXONCCA );
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = c6lowpanc_read_reg( ctx, C6LOWPANC_REG_FSMSTAT1, &status );
            if ( ( C6LOWPANC_OK == error_flag ) && !( status & C6LOWPANC_FSM_SAMPLED_CCA ) )
            {
                error_flag = C6LOWPANC_CHANNEL_BUSY;
            }
        }
        for ( elapsed = 0; ( elapsed < C6LOWPANC_TX_TIMEOUT_MS ) &&
                           ( C6LOWPANC_OK == error_flag ) && !complete; elapsed++ )
        {
            error_flag = c6lowpanc_read_reg( ctx, C6LOWPANC_REG_EXCFLAG0, &status );
            if ( C6LOWPANC_OK == error_flag )
            {
                if ( status & ( C6LOWPANC_EXC_TX_UNDERFLOW | C6LOWPANC_EXC_TX_OVERFLOW ) )
                {
                    error_flag = C6LOWPANC_ERROR;
                }
                else if ( status & C6LOWPANC_EXC_TX_FRM_DONE )
                {
                    complete = 1;
                }
                else
                {
                    Delay_1ms( );
                }
            }
        }
        if ( ( C6LOWPANC_OK == error_flag ) && !complete )
        {
            error_flag = C6LOWPANC_TIMEOUT;
        }

        // Stop a timed-out transmission before clearing its FIFO, then restore the selected role.
        cleanup_flag = c6lowpanc_set_mode( ctx, C6LOWPANC_MODE_TX );
        if ( C6LOWPANC_OK == cleanup_flag )
        {
            cleanup_flag = c6lowpanc_send_command( ctx, C6LOWPANC_CMD_SFLUSHTX );
        }
        if ( ( C6LOWPANC_OK == cleanup_flag ) && ( C6LOWPANC_MODE_RX == restore_mode ) )
        {
            cleanup_flag = c6lowpanc_set_mode( ctx, restore_mode );
        }
        if ( C6LOWPANC_OK != cleanup_flag )
        {
            error_flag = C6LOWPANC_ERROR;
        }
    }

    return error_flag;
}

err_t c6lowpanc_receive_packet ( c6lowpanc_t *ctx, uint8_t *data_out, uint8_t capacity, c6lowpanc_packet_info_t *info )
{
    uint8_t frame[ C6LOWPANC_MAX_FRAME_SIZE ];
    uint8_t status;
    uint8_t status_check;
    uint8_t count;
    uint8_t length;
    uint8_t recover_rx = 0;
    err_t error_flag = C6LOWPANC_ERROR;

    if ( NULL != info )
    {
        info->length = 0;
    }
    if ( ( NULL != data_out ) && ( NULL != info ) && ( capacity > 0 ) )
    {
        error_flag = c6lowpanc_read_reg( ctx, C6LOWPANC_REG_EXCFLAG0, &status );
        if ( ( C6LOWPANC_OK == error_flag ) &&
             ( status & ( C6LOWPANC_EXC_RX_OVERFLOW | C6LOWPANC_EXC_RX_UNDERFLOW ) ) )
        {
            recover_rx = 1;
            error_flag = C6LOWPANC_FRAME_ERROR;
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = c6lowpanc_read_reg( ctx, C6LOWPANC_REG_FSMSTAT1, &status );
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            // Read FIFOP twice to suppress the short false pulses described in the radio errata.
            error_flag = c6lowpanc_read_reg( ctx, C6LOWPANC_REG_FSMSTAT1, &status_check );
            if ( ( C6LOWPANC_OK == error_flag ) && !( status & status_check & C6LOWPANC_FSM_FIFOP ) )
            {
                error_flag = C6LOWPANC_NO_DATA;
            }
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = c6lowpanc_read_reg( ctx, C6LOWPANC_REG_RXFIFOCNT, &count );
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            error_flag = c6lowpanc_read_reg( ctx, C6LOWPANC_REG_RXFIRST, &length );
            if ( C6LOWPANC_OK == error_flag )
            {
                if ( ( length < C6LOWPANC_MAC_HEADER_SIZE + C6LOWPANC_FCS_SIZE ) ||
                     ( length > C6LOWPANC_MAX_FRAME_SIZE ) )
                {
                    recover_rx = 1;
                    error_flag = C6LOWPANC_FRAME_ERROR;
                }
                else if ( count < length + C6LOWPANC_LENGTH_FIELD_SIZE )
                {
                    error_flag = C6LOWPANC_NO_DATA;
                }
            }
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            // Leave partial frames untouched. A complete frame consists of length, MAC data, and two status bytes.
            recover_rx = 1;
            error_flag = c6lowpanc_read_fifo( ctx, &length, C6LOWPANC_LENGTH_FIELD_SIZE );
            if ( ( C6LOWPANC_OK == error_flag ) &&
                 ( length >= C6LOWPANC_MAC_HEADER_SIZE + C6LOWPANC_FCS_SIZE ) &&
                 ( length <= C6LOWPANC_MAX_FRAME_SIZE ) )
            {
                error_flag = c6lowpanc_read_fifo( ctx, frame, length );
                if ( C6LOWPANC_OK == error_flag )
                {
                    recover_rx = 0;
                }
            }
            else if ( C6LOWPANC_OK == error_flag )
            {
                error_flag = C6LOWPANC_FRAME_ERROR;
            }
        }
        if ( C6LOWPANC_OK == error_flag )
        {
            // AUTOCRC replaces the received FCS with RSSI and CRC_OK/correlation.
            if ( !( frame[ length - 1 ] & C6LOWPANC_CRC_OK ) ||
                 ( C6LOWPANC_FCF_DATA_LOW != frame[ 0 ] ) || 
                 ( C6LOWPANC_FCF_DATA_HIGH != frame[ 1 ] ) )
            {
                error_flag = C6LOWPANC_FRAME_ERROR;
            }
            else if ( length - C6LOWPANC_MAC_HEADER_SIZE - C6LOWPANC_FCS_SIZE > capacity )
            {
                error_flag = C6LOWPANC_BUFFER_ERROR;
            }
            else
            {
                info->sequence = frame[ 2 ];
                info->pan_id = ( uint16_t ) frame[ 3 ] | ( ( uint16_t ) frame[ 4 ] << 8 );
                info->destination = ( uint16_t ) frame[ 5 ] | ( ( uint16_t ) frame[ 6 ] << 8 );
                info->source = ( uint16_t ) frame[ 7 ] | ( ( uint16_t ) frame[ 8 ] << 8 );
                info->rssi = frame[ length - 2 ];
                if ( info->rssi & C6LOWPANC_RSSI_SIGN_BIT )
                {
                    info->rssi -= 256;
                }
                info->rssi -= C6LOWPANC_RSSI_OFFSET;
                info->correlation = frame[ length - 1 ] & C6LOWPANC_CORRELATION_MASK;
                info->length = length - C6LOWPANC_MAC_HEADER_SIZE - C6LOWPANC_FCS_SIZE;
                memcpy( data_out, &frame[ C6LOWPANC_MAC_HEADER_SIZE ], info->length );
            }
        }
        if ( recover_rx && ( C6LOWPANC_OK != c6lowpanc_flush_rx( ctx ) ) )
        {
            error_flag = C6LOWPANC_ERROR;
        }
    }

    return error_flag;
}

static err_t c6lowpanc_wait_status ( c6lowpanc_t *ctx, uint8_t mask )
{
    uint8_t elapsed;
    uint8_t status = 0;
    err_t error_flag = C6LOWPANC_OK;

    for ( elapsed = 0; ( elapsed < C6LOWPANC_READY_TIMEOUT_MS ) &&
                       ( C6LOWPANC_OK == error_flag ) && ( ( status & mask ) != mask ); elapsed++ )
    {
        error_flag = c6lowpanc_get_status( ctx, &status );
        if ( ( C6LOWPANC_OK == error_flag ) && ( ( status & mask ) != mask ) )
        {
            Delay_1ms( );
        }
    }
    if ( ( C6LOWPANC_OK == error_flag ) && ( ( status & mask ) != mask ) )
    {
        error_flag = C6LOWPANC_TIMEOUT;
    }

    return error_flag;
}

static err_t c6lowpanc_write_verify ( c6lowpanc_t *ctx, uint8_t reg, uint8_t value )
{
    uint8_t readback;
    err_t error_flag;

    error_flag = c6lowpanc_write_reg( ctx, reg, value );
    if ( C6LOWPANC_OK == error_flag )
    {
        error_flag = c6lowpanc_read_reg( ctx, reg, &readback );
        if ( ( C6LOWPANC_OK == error_flag ) && ( value != readback ) )
        {
            error_flag = C6LOWPANC_ERROR;
        }
    }

    return error_flag;
}

static err_t c6lowpanc_write_fifo ( c6lowpanc_t *ctx, uint8_t *data_in, uint8_t len )
{
    uint8_t command = C6LOWPANC_CMD_TXBUF;
    err_t error_flag;

    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write( &ctx->spi, &command, 1 );
    if ( C6LOWPANC_OK == error_flag )
    {
        error_flag = spi_master_write( &ctx->spi, data_in, len );
    }
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t c6lowpanc_read_fifo ( c6lowpanc_t *ctx, uint8_t *data_out, uint8_t len )
{
    uint8_t command = C6LOWPANC_CMD_RXBUF;
    err_t error_flag;

    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write_then_read( &ctx->spi, &command, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t c6lowpanc_flush_rx ( c6lowpanc_t *ctx )
{
    err_t error_flag;

    // Two consecutive strobes remove the possible extra byte left by the first flush.
    error_flag = c6lowpanc_send_command( ctx, C6LOWPANC_CMD_SFLUSHRX );
    if ( C6LOWPANC_OK == error_flag )
    {
        error_flag = c6lowpanc_send_command( ctx, C6LOWPANC_CMD_SFLUSHRX );
    }
    if ( C6LOWPANC_OK == error_flag )
    {
        error_flag = c6lowpanc_write_reg( ctx, C6LOWPANC_REG_EXCFLAG0,
                     ( uint8_t ) ~( C6LOWPANC_EXC_RX_OVERFLOW | C6LOWPANC_EXC_RX_UNDERFLOW ) );
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
