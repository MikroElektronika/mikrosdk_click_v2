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
 * @file nrfc.c
 * @brief nRF C Click Driver.
 */

#include "nrfc.h"

/**
 * @brief nRF C SPI dummy byte.
 * @details Dummy data shifted out while reading nRF C Click.
 */
#define NRFC_DUMMY_DATA      0xFF

/**
 * @brief nRF C transmit timeout.
 * @details Maximum number of one-ms waits for an nRF C Click transmit completion event.
 */
#define NRFC_TX_TIMEOUT_MS   100

/**
 * @brief nRF C validate register access function.
 * @details This function checks the nRF C Click register address and transfer length.
 * @param[in] reg : Register address.
 * @param[in] len : Number of bytes.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note Only RX_ADDR_P0, RX_ADDR_P1, and TX_ADDR accept multiple bytes. Reserved registers are excluded.
 */
static err_t nrfc_check_reg_access ( uint8_t reg, uint8_t len );

/**
 * @brief nRF C write data function.
 * @details This function sends an nRF C Click command and its data under one chip-select assertion.
 * @param[in] ctx : Click context object.
 * @param[in] command : SPI command byte.
 * @param[in] data_in : Input data, or NULL for a command without data.
 * @param[in] len : Number of data bytes.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static err_t nrfc_write_data ( nrfc_t *ctx, uint8_t command, uint8_t *data_in, uint8_t len );

/**
 * @brief nRF C read data function.
 * @details This function reads nRF C Click data while keeping chip select active after the command.
 * @param[in] ctx : Click context object.
 * @param[in] command : SPI command byte.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Number of bytes to read.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static err_t nrfc_read_data ( nrfc_t *ctx, uint8_t command, uint8_t *data_out, uint8_t len );

/**
 * @brief nRF C write and verify register function.
 * @details This function writes and verifies one nRF C Click configuration register.
 * @param[in] ctx : Click context object.
 * @param[in] reg : Register address.
 * @param[in] value : Expected register value.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note Use only for ordinary read/write registers, not interrupt flags or read-only status.
 */
static err_t nrfc_write_check ( nrfc_t *ctx, uint8_t reg, uint8_t value );

void nrfc_cfg_setup ( nrfc_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->ce   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t nrfc_init ( nrfc_t *ctx, nrfc_cfg_t *cfg ) 
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, NRFC_DUMMY_DATA ) ) 
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

    digital_out_init( &ctx->ce, cfg->ce );
    digital_out_low( &ctx->ce );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t nrfc_default_cfg ( nrfc_t *ctx ) 
{
    err_t error_flag;
    uint8_t address[ NRFC_MAX_ADDRESS_SIZE ] = NRFC_DEFAULT_ADDRESS;
    uint8_t reg;

    // Hold the radio inactive through the maximum power-on reset time.
    digital_out_low( &ctx->ce );
    Delay_100ms( );

    // Configure the control registers before enabling the radio state machine.
    error_flag = nrfc_write_check( ctx, NRFC_REG_CONFIG, NRFC_DEFAULT_CONFIG );
    error_flag |= nrfc_write_check( ctx, NRFC_REG_EN_AA, NRFC_PIPE_0 );
    error_flag |= nrfc_write_check( ctx, NRFC_REG_EN_RXADDR, NRFC_PIPE_0 );
    error_flag |= nrfc_write_check( ctx, NRFC_REG_SETUP_RETR, NRFC_DEFAULT_RETRIES );
    // Both boards must use the same channel and address for acknowledged packets.
    error_flag |= nrfc_set_channel( ctx, NRFC_DEFAULT_CHANNEL );
    error_flag |= nrfc_write_check( ctx, NRFC_REG_RF_SETUP, NRFC_DEFAULT_RF_SETUP );
    error_flag |= nrfc_set_tx_address( ctx, address, sizeof( address ) );

    // Pipe 0 uses fixed-length packets; all other receive pipes remain disabled.
    error_flag |= nrfc_write_check( ctx, NRFC_REG_RX_PW_P0, NRFC_DEFAULT_PAYLOAD_SIZE );
    for ( reg = NRFC_REG_RX_PW_P1; reg <= NRFC_REG_RX_PW_P5; reg++ )
    {
        error_flag |= nrfc_write_check( ctx, reg, 0 );
    }
    error_flag |= nrfc_write_check( ctx, NRFC_REG_DYNPD, 0 );
    error_flag |= nrfc_write_check( ctx, NRFC_REG_FEATURE, 0 );
    // Remove stale packets and pending interrupt flags from a previous session.
    error_flag |= nrfc_send_command( ctx, NRFC_CMD_FLUSH_TX );
    error_flag |= nrfc_send_command( ctx, NRFC_CMD_FLUSH_RX );
    error_flag |= nrfc_write_reg( ctx, NRFC_REG_STATUS, NRFC_STATUS_IRQ_MASK );

    if ( NRFC_OK == error_flag )
    {
        error_flag = nrfc_set_mode( ctx, NRFC_MODE_TX );
    }

    return error_flag;
}

err_t nrfc_write_reg ( nrfc_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return nrfc_write_regs( ctx, reg, &data_in, 1 );
}

err_t nrfc_write_regs ( nrfc_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = nrfc_check_reg_access( reg, len );

    if ( NULL == data_in )
    {
        error_flag = NRFC_ERROR;
    }
    if ( NRFC_OK == error_flag )
    {
        error_flag = nrfc_write_data( ctx, NRFC_CMD_W_REGISTER | reg, data_in, len );
    }

    return error_flag;
}

err_t nrfc_read_reg ( nrfc_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return nrfc_read_regs( ctx, reg, data_out, 1 );
}

err_t nrfc_read_regs ( nrfc_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t error_flag = nrfc_check_reg_access( reg, len );

    if ( NULL == data_out )
    {
        error_flag = NRFC_ERROR;
    }
    if ( NRFC_OK == error_flag )
    {
        error_flag = nrfc_read_data( ctx, NRFC_CMD_R_REGISTER | reg, data_out, len );
    }

    return error_flag;
}

err_t nrfc_send_command ( nrfc_t *ctx, uint8_t command )
{
    err_t error_flag = NRFC_ERROR;

    if ( ( NRFC_CMD_FLUSH_TX == command ) || ( NRFC_CMD_FLUSH_RX == command ) ||
         ( NRFC_CMD_REUSE_TX_PL == command ) || ( NRFC_CMD_NOP == command ) )
    {
        error_flag = nrfc_write_data( ctx, command, NULL, 0 );
    }

    return error_flag;
}

err_t nrfc_set_mode ( nrfc_t *ctx, uint8_t mode )
{
    err_t error_flag = NRFC_ERROR;
    uint8_t config;
    uint8_t previous_config;

    if ( mode <= NRFC_MODE_RX )
    {
        digital_out_low( &ctx->ce );
        error_flag = nrfc_read_reg( ctx, NRFC_REG_CONFIG, &previous_config );
        // A set reserved bit indicates invalid readback, for example a disconnected MISO line.
        if ( ( NRFC_OK == error_flag ) && ( previous_config & 0x80 ) )
        {
            error_flag = NRFC_ERROR;
        }
        if ( NRFC_OK == error_flag )
        {
            // Allow an empty automatic acknowledgment to finish before changing modes.
            if ( previous_config & NRFC_CONFIG_PRIM_RX )
            {
                Delay_1ms( );
            }
            config = previous_config & ~( NRFC_CONFIG_PWR_UP | NRFC_CONFIG_PRIM_RX );
            if ( NRFC_MODE_POWER_DOWN != mode )
            {
                config |= NRFC_CONFIG_PWR_UP;
                if ( NRFC_MODE_RX == mode )
                {
                    config |= NRFC_CONFIG_PRIM_RX;
                }
            }
            error_flag = nrfc_write_check( ctx, NRFC_REG_CONFIG, config );
        }
        if ( ( NRFC_OK == error_flag ) && ( NRFC_MODE_POWER_DOWN != mode ) )
        {
            // The crystal must settle after leaving power-down before CE is asserted.
            if ( !( previous_config & NRFC_CONFIG_PWR_UP ) )
            {
                Delay_10ms( );
            }
            if ( NRFC_MODE_RX == mode )
            {
                digital_out_high( &ctx->ce );
                Delay_1ms( );
            }
        }
    }

    return error_flag;
}

err_t nrfc_set_channel ( nrfc_t *ctx, uint8_t channel )
{
    err_t error_flag = NRFC_ERROR;

    if ( channel <= NRFC_MAX_CHANNEL )
    {
        error_flag = nrfc_write_check( ctx, NRFC_REG_RF_CH, channel );
    }

    return error_flag;
}

err_t nrfc_set_tx_address ( nrfc_t *ctx, uint8_t *address, uint8_t len )
{
    err_t error_flag = NRFC_ERROR;
    uint8_t readback[ NRFC_MAX_ADDRESS_SIZE ];

    if ( ( NULL != address ) && ( len >= 3 ) && ( len <= NRFC_MAX_ADDRESS_SIZE ) )
    {
        // Pipe 0 must match TX_ADDR for the transmitter to recognize acknowledgments.
        error_flag = nrfc_write_check( ctx, NRFC_REG_SETUP_AW, len - 2 );
        error_flag |= nrfc_write_regs( ctx, NRFC_REG_TX_ADDR, address, len );
        error_flag |= nrfc_write_regs( ctx, NRFC_REG_RX_ADDR_P0, address, len );
        if ( NRFC_OK == error_flag )
        {
            error_flag = nrfc_read_regs( ctx, NRFC_REG_TX_ADDR, readback, len );
            if ( ( NRFC_OK == error_flag ) && memcmp( address, readback, len ) )
            {
                error_flag = NRFC_ERROR;
            }
        }
        if ( NRFC_OK == error_flag )
        {
            error_flag = nrfc_read_regs( ctx, NRFC_REG_RX_ADDR_P0, readback, len );
            if ( ( NRFC_OK == error_flag ) && memcmp( address, readback, len ) )
            {
                error_flag = NRFC_ERROR;
            }
        }
    }

    return error_flag;
}

err_t nrfc_send_packet ( nrfc_t *ctx, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = NRFC_ERROR;
    uint8_t status = 0;
    uint8_t elapsed;

    if ( ( NULL != data_in ) && ( len > 0 ) && ( len <= NRFC_MAX_PAYLOAD_SIZE ) )
    {
        error_flag = nrfc_set_mode( ctx, NRFC_MODE_TX );
        if ( NRFC_OK == error_flag )
        {
            error_flag = nrfc_send_command( ctx, NRFC_CMD_FLUSH_TX );
            error_flag |= nrfc_write_reg( ctx, NRFC_REG_STATUS, NRFC_STATUS_TX_IRQ_MASK );
        }
        if ( NRFC_OK == error_flag )
        {
            error_flag = nrfc_write_data( ctx, NRFC_CMD_W_TX_PAYLOAD, data_in, len );
        }
        if ( NRFC_OK == error_flag )
        {
            // A CE pulse longer than 10 us starts exactly one packet transaction.
            digital_out_high( &ctx->ce );
            Delay_10us( );
            Delay_10us( );
            digital_out_low( &ctx->ce );

            for ( elapsed = 0; elapsed < NRFC_TX_TIMEOUT_MS; elapsed++ )
            {
                error_flag = nrfc_read_reg( ctx, NRFC_REG_STATUS, &status );
                if ( ( NRFC_OK != error_flag ) || ( status & 0x80 ) )
                {
                    error_flag = NRFC_ERROR;
                    break;
                }
                if ( status & NRFC_STATUS_TX_IRQ_MASK )
                {
                    break;
                }
                Delay_1ms( );
            }
            if ( NRFC_OK == error_flag )
            {
                if ( status & NRFC_STATUS_MAX_RT )
                {
                    error_flag = NRFC_MAX_RETRIES;
                }
                else if ( !( status & NRFC_STATUS_TX_DS ) )
                {
                    error_flag = NRFC_TIMEOUT;
                }
            }
        }

        // Stop a failed transaction before discarding its payload; leave RX flags alone.
        if ( ( NRFC_ERROR == error_flag ) || ( NRFC_TIMEOUT == error_flag ) )
        {
            if ( NRFC_OK != nrfc_set_mode( ctx, NRFC_MODE_POWER_DOWN ) )
            {
                error_flag = NRFC_ERROR;
            }
        }
        if ( NRFC_OK != nrfc_write_reg( ctx, NRFC_REG_STATUS, NRFC_STATUS_TX_IRQ_MASK ) )
        {
            error_flag = NRFC_ERROR;
        }
        if ( NRFC_OK != error_flag )
        {
            if ( NRFC_OK != nrfc_send_command( ctx, NRFC_CMD_FLUSH_TX ) )
            {
                error_flag = NRFC_ERROR;
            }
        }
    }

    return error_flag;
}

err_t nrfc_receive_packet ( nrfc_t *ctx, uint8_t *data_out, uint8_t *len )
{
    err_t error_flag = NRFC_ERROR;
    uint8_t status;
    uint8_t pipe;
    uint8_t payload_len;

    if ( NULL != len )
    {
        *len = 0;
    }
    if ( ( NULL != data_out ) && ( NULL != len ) )
    {
        // FIFO state is authoritative even if RX_DR was cleared for an earlier packet.
        error_flag = nrfc_read_reg( ctx, NRFC_REG_FIFO_STATUS, &status );
        if ( NRFC_OK == error_flag )
        {
            // Reserved FIFO bits must read zero, including when no packet is queued.
            if ( status & 0x8C )
            {
                error_flag = NRFC_ERROR;
            }
            else if ( status & NRFC_FIFO_RX_EMPTY )
            {
                error_flag = NRFC_NO_DATA;
            }
        }
        if ( NRFC_OK == error_flag )
        {
            error_flag = nrfc_read_reg( ctx, NRFC_REG_STATUS, &status );
            pipe = ( status & NRFC_STATUS_RX_PIPE_MASK ) >> 1;
            if ( ( NRFC_OK == error_flag ) && ( ( status & 0x80 ) || ( pipe > 5 ) ) )
            {
                error_flag = NRFC_ERROR;
            }
        }
        if ( NRFC_OK == error_flag )
        {
            error_flag = nrfc_read_reg( ctx, NRFC_REG_RX_PW_P0 + pipe, &payload_len );
            if ( ( NRFC_OK == error_flag ) && ( ( 0 == payload_len ) || ( payload_len > NRFC_MAX_PAYLOAD_SIZE ) ) )
            {
                error_flag = NRFC_ERROR;
            }
        }
        if ( NRFC_OK == error_flag )
        {
            error_flag = nrfc_read_data( ctx, NRFC_CMD_R_RX_PAYLOAD, data_out, payload_len );
            if ( NRFC_OK == error_flag )
            {
                error_flag = nrfc_write_reg( ctx, NRFC_REG_STATUS, NRFC_STATUS_RX_DR );
                if ( NRFC_OK == error_flag )
                {
                    *len = payload_len;
                }
            }
        }
    }

    return error_flag;
}

uint8_t nrfc_get_interrupt ( nrfc_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

static err_t nrfc_check_reg_access ( uint8_t reg, uint8_t len )
{
    err_t error_flag = NRFC_OK;

    if ( ( reg > NRFC_REG_FEATURE ) || ( ( reg > NRFC_REG_FIFO_STATUS ) && ( reg < NRFC_REG_DYNPD ) ) ||
         ( 0 == len ) || ( len > NRFC_MAX_ADDRESS_SIZE ) )
    {
        error_flag = NRFC_ERROR;
    }
    else if ( ( len > 1 ) && ( NRFC_REG_RX_ADDR_P0 != reg ) &&
              ( NRFC_REG_RX_ADDR_P1 != reg ) && ( NRFC_REG_TX_ADDR != reg ) )
    {
        error_flag = NRFC_ERROR;
    }

    return error_flag;
}

static err_t nrfc_write_data ( nrfc_t *ctx, uint8_t command, uint8_t *data_in, uint8_t len )
{
    err_t error_flag;

    // Keep CS asserted while the command and its payload form one SPI transaction.
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write( &ctx->spi, &command, 1 );
    if ( ( SPI_MASTER_SUCCESS == error_flag ) && ( len > 0 ) )
    {
        error_flag = spi_master_write( &ctx->spi, data_in, len );
    }
    spi_master_deselect_device( ctx->chip_select );

    return ( SPI_MASTER_SUCCESS == error_flag ) ? NRFC_OK : NRFC_ERROR;
}

static err_t nrfc_read_data ( nrfc_t *ctx, uint8_t command, uint8_t *data_out, uint8_t len )
{
    err_t error_flag;

    // The radio shifts STATUS during the command byte and data during the read phase.
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write_then_read( &ctx->spi, &command, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return ( SPI_MASTER_SUCCESS == error_flag ) ? NRFC_OK : NRFC_ERROR;
}

static err_t nrfc_write_check ( nrfc_t *ctx, uint8_t reg, uint8_t value )
{
    err_t error_flag;
    uint8_t readback;

    // Readback catches an invalid SPI transaction before the next configuration step.
    error_flag = nrfc_write_reg( ctx, reg, value );
    if ( NRFC_OK == error_flag )
    {
        error_flag = nrfc_read_reg( ctx, reg, &readback );
        if ( ( NRFC_OK == error_flag ) && ( readback != value ) )
        {
            error_flag = NRFC_ERROR;
        }
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
