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
 * @file lcdmini.c
 * @brief LCD mini Click Driver.
 */

#include "lcdmini.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define LCDMINI_DUMMY  0x00

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief LCD mini dev enable on function.
 * @details This function performs enable cycle necessary to send comands to 
 * LCD screen of LCD mini Click.
 * @param[in] ctx : Click context object.
 * See #lcdmini_t object definition for detailed explanation.
 * @param[in] data_in : Command to be written.
 * @return Nothing.
 */
void dev_enable_on ( lcdmini_t *ctx, uint8_t data_in );

/**
 * @brief LCD mini dev delay.
 * @details This function is used to set delay with a specified duration.
 * @param[in] duration : Duration of the delay.
 * @return Nothing.
 */
void dev_delay ( uint8_t duration );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void lcdmini_cfg_setup ( lcdmini_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->cs2  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->dev_pwm_freq = LCDMINI_DEF_FREQ;
    
    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t lcdmini_init ( lcdmini_t *ctx, lcdmini_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, LCDMINI_DUMMY ) ) {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) {
        return SPI_MASTER_ERROR;
    }
    
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) ) {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    digital_out_init( &ctx->cs2, cfg->cs2 );
    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    digital_out_low( &ctx->rst );
    digital_out_high( &ctx->cs2 );

    return SPI_MASTER_SUCCESS;
}

err_t lcdmini_default_cfg ( lcdmini_t *ctx ) 
{
    lcdmini_hw_reset( ctx );
    
    lcdmini_write_register( ctx, LCDMINI_IOCON_BANK0, LCDMINI_DUMMY );
    dev_delay( 20 );
    lcdmini_write_register( ctx, LCDMINI_GPIO_REGISTER, LCDMINI_DUMMY );
    dev_delay( 20 );
    lcdmini_write_register( ctx, LCDMINI_IODIRB_BANK0, LCDMINI_DUMMY );
    dev_delay( 20 );
    
    lcdmini_send_cmd( ctx, LCDMINI_RETURN_HOME );
    dev_delay( 20 );
    lcdmini_send_cmd( ctx, LCDMINI_2_LINE_5X7 );
    dev_delay( 20 );
    lcdmini_send_cmd( ctx, LCDMINI_DISPLAY_OFF_CURSOR_OFF );
    dev_delay( 20 );
    lcdmini_send_cmd( ctx, LCDMINI_CLEAR );
    dev_delay( 20 );
    lcdmini_send_cmd( ctx, LCDMINI_CURSOR_OFF );
    dev_delay( 20 );
    
    lcdmini_send_cmd( ctx, LCDMINI_2_LINE_5X7 );
    dev_delay( 20 );
    lcdmini_send_cmd( ctx, LCDMINI_RETURN_HOME );
    dev_delay( 20 );
    lcdmini_send_cmd( ctx, LCDMINI_MOVE_CURSOR_LEFT );
    dev_delay( 20 );
    lcdmini_send_cmd( ctx, LCDMINI_CLEAR );
    dev_delay( 20 );
    lcdmini_send_cmd( ctx, LCDMINI_BLINK_CURSOR_ON );
    dev_delay( 20 );
    lcdmini_send_cmd( ctx, LCDMINI_2_LINE_5X7 );
    dev_delay( 20 );
    lcdmini_send_cmd( ctx, LCDMINI_CLEAR );
    dev_delay( 20 );
    lcdmini_send_cmd( ctx, LCDMINI_CURSOR_OFF );
    dev_delay( 20 );
        
    return LCDMINI_OK;
}

err_t lcdmini_generic_write ( lcdmini_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t lcdmini_generic_read ( lcdmini_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t lcdmini_set_duty_cycle ( lcdmini_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t lcdmini_pwm_stop ( lcdmini_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t lcdmini_pwm_start ( lcdmini_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void lcdmini_set_backlight ( lcdmini_t *ctx, float backlight_value )
{
    lcdmini_set_duty_cycle( ctx, backlight_value );
    dev_delay( 10 );
    lcdmini_pwm_start( ctx );
}

void lcdmini_set_contrast ( lcdmini_t *ctx, uint8_t contrast_value )
{
    uint8_t tx_buf[2];
    
    tx_buf[ 0 ] = LCDMINI_DUMMY;
    tx_buf[ 1 ] = ~contrast_value;
    
    digital_out_low( &ctx->cs2 );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    digital_out_high( &ctx->cs2 );
}

uint8_t lcdmini_get_interrupt ( lcdmini_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void lcdmini_hw_reset ( lcdmini_t *ctx )
{
    digital_out_low( &ctx->rst );
    dev_delay( 1000 );
    digital_out_high( &ctx->rst );
    dev_delay( 500 );
}

err_t lcdmini_read_register ( lcdmini_t *ctx, uint8_t reg , uint8_t *data_out )
{
    uint8_t tx_buf[ 2 ];
    tx_buf[ 0 ] = LCDMINI_ADDRESS_CODE | LCDMINI_OP_CODE_READ;
    tx_buf[ 1 ] = reg;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 2, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t lcdmini_write_register ( lcdmini_t *ctx, uint8_t reg , uint8_t data_in )
{
    uint8_t tx_buf[ 3 ];
    tx_buf[ 0 ] = LCDMINI_ADDRESS_CODE & LCDMINI_OP_CODE_WRITE;
    tx_buf[ 1 ] = reg;
    tx_buf[ 2 ] = data_in;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void lcdmini_send_cmd ( lcdmini_t *ctx, uint8_t command )
{
    uint8_t temp;
    
    temp = command & 0XF0;
    lcdmini_write_register( ctx, LCDMINI_OLATB_BANK0, temp );
    dev_enable_on( ctx, temp );

    temp = ( command & 0x0F ) << 4;
    lcdmini_write_register( ctx, LCDMINI_OLATB_BANK0, temp );
    dev_enable_on( ctx, temp );
    
    dev_delay( 5 );
}

void lcdmini_send_char ( lcdmini_t *ctx, uint8_t character )
{
    uint8_t temp;
    
    temp = character & 0xF0;
    lcdmini_write_register( ctx, LCDMINI_OLATB_BANK0, temp );
    temp |= LCDMINI_RESET;
    dev_enable_on( ctx, temp );
    
    temp = ( character & 0x0F ) << 4;
    lcdmini_write_register( ctx, LCDMINI_OLATB_BANK0, temp );
    temp |= LCDMINI_RESET;
    dev_enable_on( ctx, temp );
    
    dev_delay( 1 );
}

void lcdmini_display_char ( lcdmini_t *ctx, uint8_t row, uint8_t column, char character )
{
    switch ( row ) {
        case 1: row = LCDMINI_FIRST_ROW;  break;
        case 2: row = LCDMINI_SECOND_ROW; break;
        case 3: row = LCDMINI_THIRD_ROW;  break;
        case 4: row = LCDMINI_FOURTH_ROW; break;
        default: row = LCDMINI_FIRST_ROW;
    }
    row += ( column - 1 );
    
    lcdmini_send_char( ctx, character );
}

void lcdmini_display_text ( lcdmini_t *ctx, uint8_t row, uint8_t column, char *data_in )
{
    uint8_t cnt = 0;
    
    switch ( row ) {
        case 1: row = LCDMINI_FIRST_ROW;  break;
        case 2: row = LCDMINI_SECOND_ROW; break;
        case 3: row = LCDMINI_THIRD_ROW;  break;
        case 4: row = LCDMINI_FOURTH_ROW; break;
        default: row = LCDMINI_FIRST_ROW;
    }
    row += ( column - 1 );
  
    lcdmini_send_cmd( ctx, row);
    while ( data_in[ cnt ] ) {
        lcdmini_send_char( ctx, data_in[ cnt ] );
        cnt++;
    }
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void  dev_enable_on ( lcdmini_t *ctx, uint8_t data_in )
{
    uint8_t temp;
    temp = data_in;
    
    temp |= LCDMINI_ENABLE;
    lcdmini_write_register( ctx, LCDMINI_OLATB_BANK0, temp );
    Delay_1us();
    temp &= ~LCDMINI_ENABLE;
    lcdmini_write_register( ctx, LCDMINI_OLATB_BANK0, temp );
}

void dev_delay ( uint8_t duration )
{
    for ( uint32_t cnt = 0; cnt < duration; cnt++ ) {
        Delay_1ms( );
    }
}

// ------------------------------------------------------------------------- END
