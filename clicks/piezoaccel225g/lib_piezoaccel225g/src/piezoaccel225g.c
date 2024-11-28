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
 * @file piezoaccel225g.c
 * @brief Piezo Accel 2 25g Click Driver.
 */

#include "piezoaccel225g.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void piezoaccel225g_cfg_setup ( piezoaccel225g_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->clk  = HAL_PIN_NC;
    cfg->irq  = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t piezoaccel225g_init ( piezoaccel225g_t *ctx, piezoaccel225g_cfg_t *cfg ) 
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

    digital_in_init( &ctx->clk, cfg->clk );
    digital_in_init( &ctx->irq, cfg->irq );

    return SPI_MASTER_SUCCESS;
}

err_t piezoaccel225g_default_cfg ( piezoaccel225g_t *ctx ) 
{
    err_t error_flag = PIEZOACCEL225G_OK;
    error_flag |= piezoaccel225g_fast_cmd_write ( ctx, PIEZOACCEL225G_FAST_CMD_FULL_RESET );
    Delay_1sec ( );
    error_flag |= piezoaccel225g_unlock_reg_write ( ctx );
    Delay_10ms ( );
    error_flag |= piezoaccel225g_reg_write_8 ( ctx, PIEZOACCEL225G_REG_CONFIG0, PIEZOACCEL225G_CONFIG0_VREF_SEL_INT_2_4_V | 
                                                                          PIEZOACCEL225G_CONFIG0_EXIT_PART_SHUTDOWN | 
                                                                          PIEZOACCEL225G_CONFIG0_CLK_SEL_INT | 
                                                                          PIEZOACCEL225G_CONFIG0_CS_SEL_NO_IN_CURR | 
                                                                          PIEZOACCEL225G_CONFIG0_ADC_MODE_SHUTDOWN );
    error_flag |= piezoaccel225g_reg_write_8 ( ctx, PIEZOACCEL225G_REG_CONFIG1, PIEZOACCEL225G_CONFIG1_PRE_DIV_8 | 
                                                                          PIEZOACCEL225G_CONFIG1_OSR_256 );
    error_flag |= piezoaccel225g_reg_write_8 ( ctx, PIEZOACCEL225G_REG_CONFIG2, PIEZOACCEL225G_CONFIG2_BOOST_X1 | 
                                                                          PIEZOACCEL225G_CONFIG2_GAIN_X1 |
                                                                          PIEZOACCEL225G_CONFIG2_AZ_REF_EN | 
                                                                          PIEZOACCEL225G_CONFIG2_RESERVED );
    error_flag |= piezoaccel225g_reg_write_8 ( ctx, PIEZOACCEL225G_REG_CONFIG3, PIEZOACCEL225G_CONFIG3_CONV_MODE_ONES_SHD | 
                                                                          PIEZOACCEL225G_CONFIG3_DATA_FMT_24B );
    error_flag |= piezoaccel225g_reg_write_8 ( ctx, PIEZOACCEL225G_REG_IRQ, PIEZOACCEL225G_IRQ_MODE1_IRQOUT | 
                                                                      PIEZOACCEL225G_IRQ_MODE0_INACT_HIGH_Z |
                                                                      PIEZOACCEL225G_IRQ_EN_FAST_CMD | 
                                                                      PIEZOACCEL225G_IRQ_EN_STP );
    error_flag |= piezoaccel225g_reg_write_24 ( ctx, PIEZOACCEL225G_REG_SCAN, PIEZOACCEL225G_SCAN_DLY_64_DMCLK | 
                                                                        PIEZOACCEL225G_SCAN_CH_SINGLE_ENDED_CH3 | 
                                                                        PIEZOACCEL225G_SCAN_CH_SINGLE_ENDED_CH2 | 
                                                                        PIEZOACCEL225G_SCAN_CH_SINGLE_ENDED_CH1 | 
                                                                        PIEZOACCEL225G_SCAN_CH_SINGLE_ENDED_CH0 );
    Delay_10ms ( );
    error_flag |= piezoaccel225g_lock_reg_write ( ctx );
    return error_flag;
}

err_t piezoaccel225g_fast_cmd_write ( piezoaccel225g_t *ctx, uint8_t fast_cmd )
{
    if ( ( fast_cmd < PIEZOACCEL225G_FAST_CMD_ADC_START ) || ( fast_cmd > PIEZOACCEL225G_FAST_CMD_FULL_RESET ) )
    {
        return PIEZOACCEL225G_ERROR;
    }
    err_t error_flag = PIEZOACCEL225G_OK;
    uint8_t cmd_byte = ( PIEZOACCEL225G_CMD_DEV_ADDR << 6 ) | ( fast_cmd << 2 ) | PIEZOACCEL225G_CMD_TYPE_FAST_CMD;
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, cmd_byte );
    error_flag |= spi_master_read( &ctx->spi, &ctx->status, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_deselect_device( ctx->chip_select );
    if ( ( PIEZOACCEL225G_CMD_DEV_ADDR != ( ctx->status >> 4 ) ) || ( ctx->status & PIEZOACCEL225G_STATUS_DEV_ADDR_FLAG ) )
    {
        error_flag |= PIEZOACCEL225G_ERROR;
    }
    return error_flag;
}

err_t piezoaccel225g_reg_write_multi ( piezoaccel225g_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    if ( ( NULL == data_in ) || ( reg < PIEZOACCEL225G_REG_CONFIG0 ) || ( reg > PIEZOACCEL225G_REG_LOCK ) )
    {
        return PIEZOACCEL225G_ERROR;
    }
    err_t error_flag = PIEZOACCEL225G_OK;
    uint8_t cmd_byte = ( PIEZOACCEL225G_CMD_DEV_ADDR << 6 ) | ( reg << 2 ) | PIEZOACCEL225G_CMD_TYPE_INC_REG_WRITE;
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, cmd_byte );
    error_flag |= spi_master_read( &ctx->spi, &ctx->status, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    if ( ( PIEZOACCEL225G_CMD_DEV_ADDR != ( ctx->status >> 4 ) ) || ( ctx->status & PIEZOACCEL225G_STATUS_DEV_ADDR_FLAG ) )
    {
        error_flag |= PIEZOACCEL225G_ERROR;
    }
    if ( ( PIEZOACCEL225G_OK == error_flag ) && ( len > 0 ) )
    {
        error_flag |= spi_master_write( &ctx->spi, data_in, len );
    }
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t piezoaccel225g_reg_write_8 ( piezoaccel225g_t *ctx, uint8_t reg, uint8_t data_in )
{
    if ( ( reg >= PIEZOACCEL225G_REG_SCAN ) && ( reg <= PIEZOACCEL225G_REG_GAINCAL ) )
    {
        return PIEZOACCEL225G_ERROR;
    }
    return piezoaccel225g_reg_write_multi ( ctx, reg, &data_in, 1 );
}

err_t piezoaccel225g_reg_write_24 ( piezoaccel225g_t *ctx, uint8_t reg, uint32_t data_in )
{
    if ( ( reg < PIEZOACCEL225G_REG_SCAN ) || ( reg > PIEZOACCEL225G_REG_GAINCAL ) )
    {
        return PIEZOACCEL225G_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return piezoaccel225g_reg_write_multi ( ctx, reg, data_buf, 3 );
}

err_t piezoaccel225g_reg_read_multi ( piezoaccel225g_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    if ( ( NULL == data_out ) || ( reg > PIEZOACCEL225G_REG_CRCCFG ) )
    {
        return PIEZOACCEL225G_ERROR;
    }
    err_t error_flag = PIEZOACCEL225G_OK;
    uint8_t cmd_byte = ( PIEZOACCEL225G_CMD_DEV_ADDR << 6 ) | ( reg << 2 ) | PIEZOACCEL225G_CMD_TYPE_INC_REG_READ;
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, cmd_byte );
    error_flag |= spi_master_read( &ctx->spi, &ctx->status, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    if ( ( PIEZOACCEL225G_CMD_DEV_ADDR != ( ctx->status >> 4 ) ) || ( ctx->status & PIEZOACCEL225G_STATUS_DEV_ADDR_FLAG ) )
    {
        error_flag |= PIEZOACCEL225G_ERROR;
    }
    if ( ( PIEZOACCEL225G_OK == error_flag ) && ( len > 0 ) )
    {
        error_flag |= spi_master_read( &ctx->spi, data_out, len );
    }
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t piezoaccel225g_reg_read_8 ( piezoaccel225g_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( ( PIEZOACCEL225G_REG_ADCDATA == reg ) || 
         ( ( reg >= PIEZOACCEL225G_REG_SCAN ) && ( reg <= PIEZOACCEL225G_REG_GAINCAL ) ) )
    {
        return PIEZOACCEL225G_ERROR;
    }
    return piezoaccel225g_reg_read_multi ( ctx, reg, data_out, 1 );
}

err_t piezoaccel225g_reg_read_24 ( piezoaccel225g_t *ctx, uint8_t reg, uint32_t *data_out )
{
    if ( ( NULL == data_out ) || ( ( PIEZOACCEL225G_REG_ADCDATA != reg ) && 
                                   ( ( reg < PIEZOACCEL225G_REG_SCAN ) || 
                                     ( reg > PIEZOACCEL225G_REG_GAINCAL ) ) ) )
    {
        return PIEZOACCEL225G_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    err_t error_flag = piezoaccel225g_reg_read_multi ( ctx, reg, data_buf, 3 );
    if ( PIEZOACCEL225G_OK == error_flag )
    {
        *data_out = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ]; 
    }
    return error_flag;
}

err_t piezoaccel225g_reg_read_32 ( piezoaccel225g_t *ctx, uint8_t reg, uint32_t *data_out )
{
    if ( ( NULL == data_out ) || ( PIEZOACCEL225G_REG_ADCDATA != reg ) )
    {
        return PIEZOACCEL225G_ERROR;
    }
    uint8_t data_buf[ 4 ] = { 0 };
    err_t error_flag = piezoaccel225g_reg_read_multi ( ctx, reg, data_buf, 4 );
    if ( PIEZOACCEL225G_OK == error_flag )
    {
        *data_out = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) | 
                    ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ]; 
    }
    return error_flag;
}

err_t piezoaccel225g_unlock_reg_write ( piezoaccel225g_t *ctx )
{
    return piezoaccel225g_reg_write_8 ( ctx, PIEZOACCEL225G_REG_LOCK, PIEZOACCEL225G_UNLOCK_BYTE );
}

err_t piezoaccel225g_lock_reg_write ( piezoaccel225g_t *ctx )
{
    return piezoaccel225g_reg_write_8 ( ctx, PIEZOACCEL225G_REG_LOCK, PIEZOACCEL225G_LOCK_BYTE );
}

uint8_t piezoaccel225g_get_clk_pin ( piezoaccel225g_t *ctx )
{
    return digital_in_read ( &ctx->clk );
}

uint8_t piezoaccel225g_get_irq_pin ( piezoaccel225g_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}

err_t piezoaccel225g_wait_data_ready ( piezoaccel225g_t *ctx, uint16_t timeout_ms )
{
    uint32_t timeout_cnt = 0;
    uint8_t irq_status = 0;
    for ( ; ; )
    {
        while ( piezoaccel225g_get_irq_pin ( ctx ) )
        {
            Delay_50us ( );
            if ( ( ++timeout_cnt / 20 ) > timeout_ms )
            {
                return PIEZOACCEL225G_ERROR;
            }
        }
        if ( ( PIEZOACCEL225G_OK == piezoaccel225g_reg_read_8 ( ctx, PIEZOACCEL225G_REG_IRQ, &irq_status ) ) && 
             ( PIEZOACCEL225G_IRQ_DR_STATUS != ( irq_status & PIEZOACCEL225G_IRQ_DR_STATUS ) ) )
        {
            return PIEZOACCEL225G_OK;
        }
    }
}

err_t piezoaccel225g_read_adc_data ( piezoaccel225g_t *ctx, piezoaccel225g_adc_data_t *data_out )
{
    if ( NULL == data_out )
    {
        return PIEZOACCEL225G_ERROR;
    }
    uint32_t raw_adc = 0;
    err_t error_flag = piezoaccel225g_fast_cmd_write ( ctx, PIEZOACCEL225G_FAST_CMD_ADC_START );

    error_flag |= piezoaccel225g_wait_data_ready ( ctx, PIEZOACCEL225G_DATA_READY_TIMEOUT_MS );
    error_flag |= piezoaccel225g_reg_read_24 ( ctx, PIEZOACCEL225G_REG_ADCDATA, &raw_adc );
    data_out->raw_temp = raw_adc;
    
    error_flag |= piezoaccel225g_wait_data_ready ( ctx, PIEZOACCEL225G_DATA_READY_TIMEOUT_MS );
    error_flag |= piezoaccel225g_reg_read_24 ( ctx, PIEZOACCEL225G_REG_ADCDATA, &raw_adc );
    data_out->raw_x = raw_adc;

    error_flag |= piezoaccel225g_wait_data_ready ( ctx, PIEZOACCEL225G_DATA_READY_TIMEOUT_MS );
    error_flag |= piezoaccel225g_reg_read_24 ( ctx, PIEZOACCEL225G_REG_ADCDATA, &raw_adc );
    data_out->raw_y = raw_adc;
    
    error_flag |= piezoaccel225g_wait_data_ready ( ctx, PIEZOACCEL225G_DATA_READY_TIMEOUT_MS );
    error_flag |= piezoaccel225g_reg_read_24 ( ctx, PIEZOACCEL225G_REG_ADCDATA, &raw_adc );
    data_out->raw_z = raw_adc;

    return error_flag;
}

// ------------------------------------------------------------------------- END
