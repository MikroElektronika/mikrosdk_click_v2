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
 * @file speaker2.c
 * @brief Speaker 2 Click Driver.
 */

#include "speaker2.h"
#include "speaker2_firmware.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void speaker2_cfg_setup ( speaker2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rdy  = HAL_PIN_NC;
    cfg->io5  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 600000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t speaker2_init ( speaker2_t *ctx, speaker2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->io5, cfg->io5 );
    digital_out_low ( &ctx->io5 );

    digital_in_init( &ctx->rdy, cfg->rdy );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    Delay_100ms ( );

    return SPI_MASTER_SUCCESS;
}

err_t speaker2_default_cfg ( speaker2_t *ctx ) 
{
    err_t error_flag = SPEAKER2_OK;
    error_flag |= speaker2_reset_device ( ctx );
    Delay_1sec ( );
    error_flag |= speaker2_power_up ( ctx );
    error_flag |= speaker2_check_communication ( ctx );
    if ( SPEAKER2_ERROR == error_flag )
    {
        return SPEAKER2_ERROR;
    }
    error_flag |= speaker2_chip_erase ( ctx );
    error_flag |= speaker2_write_binary ( ctx, SPEAKER2_FLASH_START, example_project_1, sizeof ( example_project_1 ) );
    error_flag |= speaker2_play_macro ( ctx, SPEAKER2_VM0_POI );
    return error_flag;
}

err_t speaker2_send_command ( speaker2_t *ctx, uint8_t cmd, uint8_t *payload, uint16_t payload_len )
{
    err_t error_flag = SPEAKER2_OK;
    uint16_t cnt = 0;
    if ( payload_len > SPEAKER2_PAYLOAD_SIZE )
    {
        return SPEAKER2_ERROR;
    }
    error_flag |= speaker2_wait_ready ( ctx );
    spi_master_select_device( ctx->chip_select );
    // Send command and read status
    if ( SPEAKER2_OK == error_flag )
    {
        spi_master_set_default_write_data( &ctx->spi, cmd );
        error_flag |= spi_master_read( &ctx->spi, &ctx->status, 1 );
    }
    for ( cnt = 0; ( cnt < payload_len ) && ( SPEAKER2_OK == error_flag ) && ( NULL != payload ); cnt++ )
    {
        // Send command payload and read response
        error_flag |= speaker2_wait_ready ( ctx );
        if ( SPEAKER2_OK == error_flag )
        {
            spi_master_set_default_write_data( &ctx->spi, payload[ cnt ] );
            error_flag |= spi_master_read( &ctx->spi, &payload[ cnt ], 1 );
        }
    }
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void speaker2_set_io5_pin ( speaker2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->io5, state );
}

uint8_t speaker2_get_rdy_pin ( speaker2_t *ctx )
{
    return digital_in_read ( &ctx->rdy );
}

uint8_t speaker2_get_int_pin ( speaker2_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t speaker2_wait_ready ( speaker2_t *ctx )
{
    err_t error_flag = SPEAKER2_OK;
    uint32_t timeout = 0;
    while ( !speaker2_get_rdy_pin ( ctx ) )
    {
        if ( ++timeout >= SPEAKER2_TIMEOUT_10S )
        {
            error_flag |= SPEAKER2_ERROR;
            break;
        }
        Delay_1ms ( );
    }
    return error_flag;
}

err_t speaker2_wait_status ( speaker2_t *ctx, uint8_t mask, uint8_t state )
{
    err_t error_flag = SPEAKER2_OK;
    uint32_t timeout = 0;
    error_flag |= speaker2_clear_interrupt ( ctx, NULL );
    while ( ( SPEAKER2_OK == error_flag ) && 
            ( state != ( ctx->status & mask ) ) )
    {
        if ( ++timeout >= SPEAKER2_TIMEOUT_10S )
        {
            error_flag |= SPEAKER2_ERROR;
            break;
        }
        Delay_1ms ( );
        error_flag |= speaker2_clear_interrupt ( ctx, NULL );
    }
    return error_flag;
}

err_t speaker2_wait_idle ( speaker2_t *ctx )
{
    // Wait for PD, CHx, and DIG flags to go low, and DBUF_RDY to go high
    return speaker2_wait_status ( ctx, ( SPEAKER2_STATUS_PD |
                                         SPEAKER2_STATUS_DBUF_RDY | 
                                         SPEAKER2_STATUS_CH2_BSY | 
                                         SPEAKER2_STATUS_CH1_BSY | 
                                         SPEAKER2_STATUS_CH0_BSY | 
                                         SPEAKER2_STATUS_DIG_BSY ), SPEAKER2_STATUS_DBUF_RDY );
}

err_t speaker2_check_communication ( speaker2_t *ctx )
{
    if ( SPEAKER2_OK == speaker2_read_device_id ( ctx, &ctx->device_id ) )
    {
        if ( ( SPEAKER2_DEVICE_ID_PART == ctx->device_id.part_id ) && 
             ( SPEAKER2_DEVICE_ID_MAN == ctx->device_id.man_id ) && 
             ( SPEAKER2_DEVICE_ID_MEM_TYPE == ctx->device_id.mem_type ) && 
             ( SPEAKER2_DEVICE_ID_DEV == ctx->device_id.dev_id ) )
        {
            return SPEAKER2_OK;
        }
    }
    return SPEAKER2_ERROR;
}

err_t speaker2_read_status ( speaker2_t *ctx, uint8_t *int_status )
{
    err_t error_flag = SPEAKER2_OK;
    memset ( ctx->cmd_payload, DUMMY, 1 );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_READ_STATUS, ctx->cmd_payload, 1 );
    if ( ( NULL != int_status ) && ( SPEAKER2_OK == error_flag ) )
    {
        *int_status = ctx->cmd_payload[ 0 ];
    }
    return error_flag;
}

err_t speaker2_clear_interrupt ( speaker2_t *ctx, uint8_t *int_status )
{
    err_t error_flag = SPEAKER2_OK;
    memset ( ctx->cmd_payload, DUMMY, 1 );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_READ_INT, ctx->cmd_payload, 1 );
    if ( ( NULL != int_status ) && ( SPEAKER2_OK == error_flag ) )
    {
        *int_status = ctx->cmd_payload[ 0 ];
    }
    return error_flag;
}

err_t speaker2_read_device_id ( speaker2_t *ctx, speaker2_device_id_t *device_id )
{
    err_t error_flag = SPEAKER2_OK;
    memset ( ctx->cmd_payload, DUMMY, 4 );
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_READ_ID, ctx->cmd_payload, 4 );
    if ( ( NULL != device_id ) && ( SPEAKER2_OK == error_flag ) )
    {
        device_id->part_id = ctx->cmd_payload[ 0 ];
        device_id->man_id = ctx->cmd_payload[ 1 ];
        device_id->mem_type = ctx->cmd_payload[ 2 ];
        device_id->dev_id = ctx->cmd_payload[ 3 ];
    }
    return error_flag;
}

err_t speaker2_power_up ( speaker2_t *ctx )
{
    err_t error_flag = SPEAKER2_OK;
    uint32_t timeout = 0;
    // Check if PD high and DBUF_RDY low
    error_flag |= speaker2_read_status ( ctx, NULL );
    if ( SPEAKER2_STATUS_PD != ( ctx->status & ( SPEAKER2_STATUS_PD |
                                                 SPEAKER2_STATUS_DBUF_RDY ) ) )
    {
        return SPEAKER2_OK;
    }
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_PWR_UP, NULL, 0 );
    error_flag |= speaker2_wait_idle ( ctx );

    // Enable RDY/BSYB functionality on GPIO4 and disable all other GPIO triggers
    error_flag |= speaker2_write_cfg_reg ( ctx, SPEAKER2_REG_ALT_FUNCTION_CONTROL_1, 
                                           ( SPEAKER2_GPIO_AF1_AF << SPEAKER2_GPIO_4_POS ) );
    error_flag |= speaker2_write_cfg_reg ( ctx, SPEAKER2_REG_ALT_FUNCTION_CONTROL_0, 
                                           ( SPEAKER2_GPIO_AF0_AF << SPEAKER2_GPIO_4_POS ) );
    return error_flag;
}

err_t speaker2_power_down ( speaker2_t *ctx )
{
    err_t error_flag = SPEAKER2_OK;
    uint32_t timeout = 0;
    // Check if PD low and DBUF_RDY high
    error_flag |= speaker2_read_status ( ctx, NULL );
    if ( SPEAKER2_STATUS_DBUF_RDY != ( ctx->status & ( SPEAKER2_STATUS_PD |
                                                       SPEAKER2_STATUS_DBUF_RDY ) ) )
    {
        return SPEAKER2_OK;
    }
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_PWR_DN, NULL, 0 );
    // Wait for PD to go high, and DBUF_RDY to go low
    error_flag |= speaker2_wait_status ( ctx, ( SPEAKER2_STATUS_PD |
                                                SPEAKER2_STATUS_DBUF_RDY ), SPEAKER2_STATUS_PD );
    return error_flag;
}

err_t speaker2_reset_device ( speaker2_t *ctx )
{
    return speaker2_send_command ( ctx, SPEAKER2_CMD_RESET, NULL, 0 );
}

err_t speaker2_memory_erase ( speaker2_t *ctx, uint32_t address )
{
    err_t error_flag = SPEAKER2_OK;
    ctx->cmd_payload[ 0 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    ctx->cmd_payload[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    ctx->cmd_payload[ 2 ] = ( uint8_t ) ( address & 0xFF );
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_ERASE_MEM, ctx->cmd_payload, 3 );
    error_flag |= speaker2_wait_idle ( ctx );
    return error_flag;
}

err_t speaker2_chip_erase ( speaker2_t *ctx )
{
    err_t error_flag = SPEAKER2_OK;
    ctx->cmd_payload[ 0 ] = 1;
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_CHIP_ERASE, ctx->cmd_payload, 1 );
    error_flag |= speaker2_wait_idle ( ctx );
    return error_flag;
}

err_t speaker2_flash_write ( speaker2_t *ctx, uint32_t address, uint8_t *data_in, uint16_t data_len )
{
    err_t error_flag = SPEAKER2_OK;
    uint32_t timeout = 0;
    if ( ( data_len > ( SPEAKER2_PAYLOAD_SIZE - 3 ) ) || ( ( data_len + address - 1 ) > SPEAKER2_FLASH_END ) )
    {
        return SPEAKER2_ERROR;
    }
    ctx->cmd_payload[ 0 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    ctx->cmd_payload[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    ctx->cmd_payload[ 2 ] = ( uint8_t ) ( address & 0xFF );
    memcpy ( &ctx->cmd_payload[ 3 ], data_in, data_len );
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_DIG_WRITE, ctx->cmd_payload, data_len + 3 );
    error_flag |= speaker2_wait_idle ( ctx );
    return error_flag;
}

err_t speaker2_flash_read ( speaker2_t *ctx, uint32_t address, uint8_t *data_out, uint16_t data_len )
{
    err_t error_flag = SPEAKER2_OK;
    if ( ( data_len > ( SPEAKER2_PAYLOAD_SIZE - 3 ) ) || ( ( data_len + address - 1 ) > SPEAKER2_FLASH_END ) )
    {
        return SPEAKER2_ERROR;
    }
    ctx->cmd_payload[ 0 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    ctx->cmd_payload[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    ctx->cmd_payload[ 2 ] = ( uint8_t ) ( address & 0xFF );
    memset ( &ctx->cmd_payload[ 3 ], DUMMY, data_len );
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_DIG_READ, ctx->cmd_payload, data_len + 3 );
    if ( ( NULL != data_out ) && ( SPEAKER2_OK == error_flag ) )
    {
        memcpy ( data_out, &ctx->cmd_payload[ 3 ], data_len );
    }
    return error_flag;
}

err_t speaker2_write_binary ( speaker2_t *ctx, uint32_t address, const uint8_t *data_in, uint16_t data_len )
{
    err_t error_flag = SPEAKER2_OK;
    uint32_t cnt = 0; 
    for ( cnt = 0; ( cnt < data_len ) && ( SPEAKER2_OK == error_flag ); cnt += ( SPEAKER2_PAYLOAD_SIZE / 2 ) )
    {
        if ( data_len >= ( cnt + ( SPEAKER2_PAYLOAD_SIZE / 2 ) ) )
        {
            memcpy ( &ctx->cmd_payload[ 3 ], &data_in[ cnt ], ( SPEAKER2_PAYLOAD_SIZE / 2 ) );
            error_flag |= speaker2_flash_write ( ctx, address + cnt, &ctx->cmd_payload[ 3 ], ( SPEAKER2_PAYLOAD_SIZE / 2 ) );
        }
        else
        {
            memcpy ( &ctx->cmd_payload[ 3 ], &data_in[ cnt ], data_len - cnt );
            error_flag |= speaker2_flash_write ( ctx, address + cnt, &ctx->cmd_payload[ 3 ], data_len - cnt );
        }
        Delay_10ms ( );
    }
    return error_flag;
}

err_t speaker2_write_cfg_reg ( speaker2_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = SPEAKER2_OK;
    ctx->cmd_payload[ 0 ] = reg;
    ctx->cmd_payload[ 1 ] = data_in;
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_WR_CFG_REG, ctx->cmd_payload, 2 );
    return error_flag;
}

err_t speaker2_read_cfg_reg ( speaker2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = SPEAKER2_OK;
    ctx->cmd_payload[ 0 ] = reg;
    ctx->cmd_payload[ 1 ] = DUMMY;
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_RD_CFG_REG, ctx->cmd_payload, 2 );
    if ( ( NULL != data_out ) && ( SPEAKER2_OK == error_flag ) )
    {
        *data_out = ctx->cmd_payload[ 1 ];
    }
    return error_flag;
}

err_t speaker2_set_clock_cfg ( speaker2_t *ctx, uint8_t clk_cfg )
{
    err_t error_flag = SPEAKER2_OK;
    ctx->cmd_payload[ 0 ] = clk_cfg;
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_SET_CLK_CFG, ctx->cmd_payload, 1 );
    return error_flag;
}

err_t speaker2_read_clock_cfg ( speaker2_t *ctx, uint8_t *clk_cfg )
{
    err_t error_flag = SPEAKER2_OK;
    ctx->cmd_payload[ 0 ] = DUMMY;
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_RD_CLK_CFG, ctx->cmd_payload, 1 );
    if ( ( NULL != clk_cfg ) && ( SPEAKER2_OK == error_flag ) )
    {
        *clk_cfg = ctx->cmd_payload[ 0 ];
    }
    return error_flag;
}

err_t speaker2_spi_audio_write ( speaker2_t *ctx, uint8_t *data_in, uint16_t data_len )
{
    err_t error_flag = SPEAKER2_OK;
    if ( data_len > SPEAKER2_PAYLOAD_SIZE )
    {
        return SPEAKER2_ERROR;
    }
    memcpy ( ctx->cmd_payload, data_in, data_len );
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_SPI_SND_DEC, ctx->cmd_payload, data_len );
    return error_flag;
}

err_t speaker2_pcm_audio_read ( speaker2_t *ctx, uint16_t *data_out, uint16_t data_len )
{
    err_t error_flag = SPEAKER2_OK;
    uint16_t cnt = 0;
    if ( data_len > ( SPEAKER2_PAYLOAD_SIZE / 2 ) )
    {
        return SPEAKER2_ERROR;
    }
    memset ( ctx->cmd_payload, DUMMY, data_len * 2 );
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_SPI_PCM_READ, ctx->cmd_payload, data_len * 2 );
    if ( ( NULL != data_out ) && ( SPEAKER2_OK == error_flag ) )
    {
        for ( cnt = 0; cnt < data_len; cnt++ )
        {
            data_out[ cnt ] = ( ( uint16_t ) ctx->cmd_payload[ cnt + 2 + 1 ] << 8 ) | ctx->cmd_payload[ cnt * 2 ];
        }
    }
    return error_flag;
}

err_t speaker2_play_voice ( speaker2_t *ctx, uint16_t index )
{
    err_t error_flag = SPEAKER2_OK;
    ctx->cmd_payload[ 0 ] = ( uint8_t ) ( ( index >> 8 ) & 0xFF );
    ctx->cmd_payload[ 1 ] = ( uint8_t ) ( index & 0xFF );
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_PLAY_VP, ctx->cmd_payload, 2 );
    error_flag |= speaker2_wait_idle ( ctx );
    return error_flag;
}

err_t speaker2_play_voice_loop ( speaker2_t *ctx, uint16_t index, uint16_t loop_cnt )
{
    err_t error_flag = SPEAKER2_OK;
    ctx->cmd_payload[ 0 ] = ( uint8_t ) ( ( index >> 8 ) & 0xFF );
    ctx->cmd_payload[ 1 ] = ( uint8_t ) ( index & 0xFF );
    ctx->cmd_payload[ 2 ] = ( uint8_t ) ( ( loop_cnt >> 8 ) & 0xFF );
    ctx->cmd_payload[ 3 ] = ( uint8_t ) ( loop_cnt & 0xFF );
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_PLAY_VP_LP, ctx->cmd_payload, 4 );
    error_flag |= speaker2_wait_idle ( ctx );
    return error_flag;
}

err_t speaker2_play_macro ( speaker2_t *ctx, uint16_t index )
{
    err_t error_flag = SPEAKER2_OK;
    ctx->cmd_payload[ 0 ] = ( uint8_t ) ( ( index >> 8 ) & 0xFF );
    ctx->cmd_payload[ 1 ] = ( uint8_t ) ( index & 0xFF );
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_EXE_VM, ctx->cmd_payload, 2 );
    error_flag |= speaker2_wait_idle ( ctx );
    return error_flag;
}

err_t speaker2_play_silence ( speaker2_t *ctx, uint8_t len )
{
    err_t error_flag = SPEAKER2_OK;
    ctx->cmd_payload[ 0 ] = len;
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_PLAY_SIL, ctx->cmd_payload, 1 );
    error_flag |= speaker2_wait_idle ( ctx );
    return error_flag;
}

err_t speaker2_stop_play ( speaker2_t *ctx )
{
    err_t error_flag = SPEAKER2_OK;
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_STOP, NULL, 0 );
    return error_flag;
}

err_t speaker2_stop_loop_play ( speaker2_t *ctx )
{
    err_t error_flag = SPEAKER2_OK;
    error_flag |= speaker2_wait_idle ( ctx );
    error_flag |= speaker2_send_command ( ctx, SPEAKER2_CMD_STOP_LP, NULL, 0 );
    return error_flag;
}

// ------------------------------------------------------------------------- END
