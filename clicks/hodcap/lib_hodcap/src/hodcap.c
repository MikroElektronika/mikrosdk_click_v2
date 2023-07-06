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
 * @file hodcap.c
 * @brief HOD CAP Click Driver.
 */

#include "hodcap.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                        0x00

/**
 * @brief Data ready timeout.
 * @details Definition of data ready timeout.
 */
#define HODCAP_DATA_READY_TIMEOUT    5000

void hodcap_cfg_setup ( hodcap_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->clk  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH;
}

err_t hodcap_init ( hodcap_t *ctx, hodcap_cfg_t *cfg ) 
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

    digital_out_init( &ctx->clk, cfg->clk );
    
    return SPI_MASTER_SUCCESS;
}

err_t hodcap_default_cfg ( hodcap_t *ctx ) 
{
    uint16_t sensor_id;
    err_t err_flag = hodcap_get_sensor_id( ctx, &sensor_id );
    if ( HODCAP_SENSOR_ID == sensor_id )
    {
        // Set frequency dividing factor to 12
        hodcap_write_reg( ctx, HODCAP_REG_EDIV, HODCAP_SET_EDIV_12 );
        Delay_10ms( );
    
        // Set the sine wave generator frequency to 125kHz
        hodcap_write_reg( ctx, HODCAP_REG_FREQ, HODCAP_SET_FREQ_125KHZ );
        Delay_10ms( );
    
        //  Set Output Voltage (Peak-Peak) to 1V
        hodcap_write_reg( ctx, HODCAP_REG_TXV, HODCAP_SET_TXV_1V );
        Delay_10ms( );
    
        // Select SEN0 Channel
        // Set sensor driver mode
        hodcap_write_reg( ctx, HODCAP_REG_MUX_CTRL, HODCAP_SET_MUX_CTRL_SEL_SEN0 
                                                  | HODCAP_SET_MUX_CTRL_MODE_SENSOR_DRV );
        Delay_10ms( );
    
        // Set PGA gain
        hodcap_write_reg( ctx, HODCAP_REG_PGA, HODCAP_SET_PGA_GAIN_36 );
        Delay_10ms( );
    
        // Set PGA I offset
        hodcap_write_reg( ctx, HODCAP_REG_PGA_OFFSET_I, HODCAP_SET_DEFAULT_PGA_OFFSET_I );
        Delay_10ms( );
    
        // Set PGA Q offset
        hodcap_write_reg( ctx, HODCAP_REG_PGA_OFFSET_Q, HODCAP_SET_DEFAULT_PGA_OFFSET_Q );
        Delay_10ms( );
    
        // Set system settling time periods to 400 µs
        // Set 16 samples calculated for I and Q Channel 
        // Set ADC frequency to 1000kHz
        // Reset DSP and stop ADC activities
        hodcap_write_reg( ctx, HODCAP_REG_ADCTL, HODCAP_SET_ADCTL_TS_400US 
                                               | HODCAP_SET_ADCTL_ACCU_NUMB_OF_SAMPLES_16 
                                               | HODCAP_SET_ADCTL_CS_CLK_1000KHZ 
                                               | HODCAP_SET_ADCTL_MODE_RESET_STOP );
        Delay_100ms( );
    
        // Start continuous conversation
        hodcap_set_adc_op_mode( ctx, HODCAP_SET_ADCTL_MODE_START_CONT_CONVO );
        Delay_100ms( );
    
        hodcap_write_reg( ctx, HODCAP_REG_DIAG_MUX_CTRL, HODCAP_SET_MUX_CTRL_MINUS_NONE 
                                                       | HODCAP_SET_MUX_CTRL_PLUS_NONE );
        Delay_10ms( );
    }
    else
    {
        err_flag = HODCAP_ERROR;
    }
    
    return err_flag;
}

err_t hodcap_generic_write ( hodcap_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    reg |= HODCAP_CMD_WRITE;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t hodcap_generic_read ( hodcap_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    reg |= HODCAP_CMD_READ;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t hodcap_write_reg ( hodcap_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in >> 8 );
    data_buf[ 1 ] = ( uint8_t )   data_in;
    return hodcap_generic_write( ctx, reg, data_buf, 2 );
}

err_t hodcap_read_reg ( hodcap_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = hodcap_generic_read( ctx, reg, data_buf, 2 );
    *data_out = data_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 1 ];
    return err_flag;
}

err_t hodcap_get_sensor_id ( hodcap_t *ctx, uint16_t *sensor_id ) 
{
    return hodcap_read_reg( ctx, HODCAP_REG_SENSOR_ID, sensor_id );
}

err_t hodcap_get_status ( hodcap_t *ctx, hodcap_status_t *status ) 
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = hodcap_read_reg( ctx, HODCAP_REG_STATUS, &data_buf );
    status->r_ediv = ( uint8_t ) ( ( data_buf >> 13 ) & 0x07 );
    status->otpf   = ( uint8_t ) ( ( data_buf >> 12 ) & 0x01 );
    status->ppsf   = ( uint8_t ) ( ( data_buf >> 11 ) & 0x01 );
    status->bpff   = ( uint8_t ) ( ( data_buf >> 10 ) & 0x01 );
    status->regf   = ( uint8_t ) ( ( data_buf >>  9 ) & 0x01 );
    status->ocsld  = ( uint8_t ) ( ( data_buf >>  8 ) & 0x01 );
    status->ocsen  = ( uint8_t ) ( ( data_buf >>  7 ) & 0x01 );
    status->test   = ( uint8_t ) ( ( data_buf >>  6 ) & 0x01 );
    status->tx1f   = ( uint8_t ) ( ( data_buf >>  5 ) & 0x01 );
    status->tx2f   = ( uint8_t ) ( ( data_buf >>  4 ) & 0x01 );
    status->pga1f  = ( uint8_t ) ( ( data_buf >>  3 ) & 0x01 );
    status->pga2f  = ( uint8_t ) ( ( data_buf >>  2 ) & 0x01 );
    status->nclk   = ( uint8_t ) ( ( data_buf >>  1 ) & 0x01 );
    status->cbf    = ( uint8_t ) (   data_buf         & 0x01 );
    return err_flag;
}

err_t hodcap_check_adc_data_ready ( hodcap_t *ctx, uint16_t *data_ready ) 
{
    return hodcap_read_reg( ctx, HODCAP_REG_ADC_STATUS, data_ready );
}

err_t hodcap_set_adc_op_mode ( hodcap_t *ctx, uint16_t adc_op_mode ) 
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = hodcap_read_reg( ctx, HODCAP_REG_ADCTL, &data_buf );
    data_buf &= ~HODCAP_SET_ADCTL_MODE_BIT_MASK;
    data_buf |= ( adc_op_mode & HODCAP_SET_ADCTL_MODE_BIT_MASK );
    err_flag |= hodcap_write_reg( ctx, HODCAP_REG_ADCTL, data_buf );
    return err_flag;
}

err_t hodcap_mux_channel_selection ( hodcap_t *ctx, uint8_t sen_pos ) 
{
    err_t err_flag = HODCAP_ERROR;
    uint16_t data_buf = DUMMY;
    if ( sen_pos < HODCAP_TOTAL_NUMBER_OF_CHANNELS )
    {
        sen_pos <<= 2;
        sen_pos &= ( uint8_t ) HODCAP_SET_MUX_CTRL_SEL_BIT_MASK;
        err_flag = hodcap_read_reg( ctx, HODCAP_REG_MUX_CTRL, &data_buf );
        Delay_55us( );
        
        data_buf &= ~HODCAP_SET_MUX_CTRL_MODE_NO_OP;
        err_flag |= hodcap_write_reg( ctx, HODCAP_REG_MUX_CTRL, data_buf );
        Delay_55us( );
        
        data_buf &= ~HODCAP_SET_MUX_CTRL_SEL_BIT_MASK;
        data_buf |= ( uint16_t ) sen_pos;
        data_buf |= HODCAP_SET_MUX_CTRL_MODE_SENSOR_DRV;
        err_flag |= hodcap_write_reg( ctx, HODCAP_REG_MUX_CTRL, data_buf );
        Delay_1ms( );
    }
    return err_flag;
}

err_t hodcap_get_i_q_data ( hodcap_t *ctx, uint16_t *i_data, uint16_t *q_data ) 
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t err_flag = hodcap_generic_read( ctx, HODCAP_CMD_QUICK_READ, data_buf, 4 );
    *i_data = data_buf[ 0 ];
    *i_data <<= 8;
    *i_data |= data_buf[ 1 ];
    *q_data = data_buf[ 2 ];
    *q_data <<= 8;
    *q_data |= data_buf[ 3 ];
    return err_flag;
}

err_t hodcap_wait_adc_data_ready ( hodcap_t *ctx ) 
{
    err_t err_flag = HODCAP_OK;
    uint16_t adc_ready = DUMMY, timeout_cnt = DUMMY;
    do
    {
        err_flag |= hodcap_check_adc_data_ready( ctx, &adc_ready );
        timeout_cnt++;
        if ( HODCAP_DATA_READY_TIMEOUT < timeout_cnt )
        {
            return HODCAP_ERROR;
        }
        Delay_1ms( );
    }
    while ( HODCAP_ADC_DATA_READY != adc_ready );
    return err_flag;
}

void hodcap_set_clk_state ( hodcap_t *ctx, uint8_t clk_state ) 
{
    digital_out_write( &ctx->clk, clk_state );
}

// ------------------------------------------------------------------------- END
