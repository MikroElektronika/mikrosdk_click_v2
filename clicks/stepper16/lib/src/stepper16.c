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
 * @file stepper16.c
 * @brief Stepper16 Click Driver.
 */

#include "stepper16.h"

/**
 * @brief Communication mask data.
 * @details Definition of communication help data.
 */
#define DUMMY           0x00
#define WRITE_BIT       0x80

/**
 * @brief Driver macros for calculation.
 */
#define FULL_CIRCLE     360.0
#define RESOLUTION      4096.0
#define VREF            3330.0

/**
 * @brief Set delay for controling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper16_speed_delay( uint8_t speed_macro );

/**
 * @brief Filter value for register.
 * @details This function masks data for register.
 * @param[in] reg : Register that data is related to/from.
 * @param[in/out] return_value : Data to be masked for selected register.
 * @return Nothing.
 */
static void stepper16_filter_return ( uint8_t reg, uint16_t *return_value );

/**
 * @brief Create parity bit.
 * @details This function creates parity bit for write command.
 * @param[in] dat_val : Data to create parity bit from.
 * @return Parity bit for write command.
 */
static uint8_t stepper16_create_parity_write ( uint16_t dat_val );

/**
 * @brief Create parity bit.
 * @details This function creates parity bit for read command.
 * @param[in] dat_val : Data to create parity bit from.
 * @return Parity bit for read command.
 */
static uint8_t stepper16_create_parity_read ( uint8_t dat_val );


void stepper16_cfg_setup ( stepper16_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->nxt = HAL_PIN_NC;
    cfg->err = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t stepper16_init ( stepper16_t *ctx, stepper16_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );
    
    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->nxt, cfg->nxt );
    digital_out_init( &ctx->cs, cfg->cs );
    
    digital_in_init( &ctx->err, cfg->err );

    ctx->steps = 0;
    ctx->resolution = 0.0;
    ctx->step_resolution = 0;

    return SPI_MASTER_SUCCESS;
}

err_t stepper16_default_cfg ( stepper16_t *ctx ) 
{
    uint16_t read_data;
    err_t error_flag;
    
    stepper16_hard_reset( ctx );
    stepper16_wake_up( ctx );
    
    error_flag |= stepper16_generic_read( ctx, STEPPER16_REG_SR1, &read_data );
    error_flag |= stepper16_generic_read( ctx, STEPPER16_REG_SR2, &read_data );
    error_flag |= stepper16_generic_read( ctx, STEPPER16_REG_SR3, &read_data );
    error_flag |= stepper16_generic_read( ctx, STEPPER16_REG_SR4, &read_data );
    error_flag |= stepper16_generic_read( ctx, STEPPER16_REG_SR5, &read_data );
    error_flag |= stepper16_generic_read( ctx, STEPPER16_REG_SR6, &read_data );
    
    error_flag |= stepper16_generic_write( ctx, STEPPER16_REG_CR1, 0x008F );
    error_flag |= stepper16_generic_write( ctx, STEPPER16_REG_CR2, 0x0000 );
    error_flag |= stepper16_generic_write( ctx, STEPPER16_REG_CR3, 0x0388 );
    error_flag |= stepper16_generic_write( ctx, STEPPER16_REG_CR4, 0x0000 );
    error_flag |= stepper16_generic_write( ctx, STEPPER16_REG_CR5, 0x03FF );
    error_flag |= stepper16_generic_write( ctx, STEPPER16_REG_CR6, 0x0000 );
    
    ctx->steps = 200;
    stepper16_calculate_resolution( ctx );
    
    return error_flag;
}

err_t stepper16_generic_write ( stepper16_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t tx_buf[ 2 ];
    uint16_t data_write = data_in;
    
    stepper16_filter_return( reg, &data_write );
    
    tx_buf[ 0 ] = ( ( reg & 0xF ) << 3 );
    tx_buf[ 0 ] |= ( uint8_t )( data_write >> 8 );
    tx_buf[ 0 ] |= WRITE_BIT;
    tx_buf[ 1 ] = ( uint8_t )data_write;
    
    uint8_t parity = stepper16_create_parity_write( ( ( uint16_t )tx_buf[ 0 ] << 8 ) | tx_buf[ 1 ] );
    
    tx_buf[ 0 ] |= parity << 2;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t stepper16_generic_read ( stepper16_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    uint8_t wreg = ( reg & 0xF ) << 2;
    uint8_t read_data[ 2 ] = { 0 };
    uint8_t parity = stepper16_create_parity_read( wreg );
    wreg |= parity << 1;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, wreg );
    err_t error_flag = spi_master_read( &ctx->spi, &read_data[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &read_data[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    *data_out = ( ( uint16_t )read_data[ 0 ] << 8 ) | read_data[ 1 ];
    
    ctx->spierr = ( read_data[ 0 ] >> 7 ) & 1;
    ctx->uv = ( read_data[ 0 ] >> 5 ) & 1;
    ctx->eldef = ( read_data[ 0 ] >> 4 ) & 1;
    ctx->tsd = ( read_data[ 0 ] >> 3 ) & 1;
    ctx->tw = ( read_data[ 0 ] >> 2 ) & 1;
    
    stepper16_filter_return( reg, data_out );

    return error_flag;
}

void stepper16_set_next ( stepper16_t *ctx, uint8_t value )
{
    digital_out_write( &ctx->nxt, value );
}

void stepper16_set_dir ( stepper16_t *ctx, uint8_t value )
{
    digital_out_write( &ctx->dir, value );
}

uint8_t stepper16_get_error_flag ( stepper16_t *ctx )
{
    return digital_in_read( &ctx->err );
}

void stepper16_hard_reset ( stepper16_t *ctx )
{
    stepper16_set_dir( ctx, 0 );
    stepper16_set_next( ctx, 1 );
    Delay_1us( );
    Delay_1us( );
    Delay_1us( );
    
    stepper16_set_dir( ctx, 1 );
    Delay_1us( );
    Delay_1us( );
    Delay_1us( );
    stepper16_set_dir( ctx, 0 );
    Delay_22us( );
    
    stepper16_set_dir( ctx, 1 );
    Delay_1us( );
    Delay_1us( );
    Delay_1us( );
    stepper16_set_dir( ctx, 0 );
    Delay_22us( );
    
    stepper16_set_dir( ctx, 1 );
    Delay_1us( );
    Delay_1us( );
    Delay_1us( );
    stepper16_set_dir( ctx, 0 );
    Delay_22us( );
    
    stepper16_set_dir( ctx, 1 );
    Delay_1us( );
    Delay_1us( );
    Delay_1us( );
    stepper16_set_dir( ctx, 0 );
    Delay_22us( );
    
    stepper16_set_dir( ctx, 1 );
    Delay_1us( );
    Delay_1us( );
    Delay_1us( );
    stepper16_set_dir( ctx, 0 );
    Delay_22us( );
    Delay_100ms( );
}

void stepper16_wake_up ( stepper16_t *ctx )
{
    digital_out_low( &ctx->cs );
    Delay_10us( );
    digital_out_high( &ctx->cs );
    Delay_500us();
}

void stepper16_set_step_resolution ( stepper16_t *ctx, uint8_t step_res )
{
    uint16_t sr2_data;
    stepper16_generic_read( ctx, STEPPER16_REG_CR2, &sr2_data );
    sr2_data &= 0xFFF8;//Clear step resolution bits [0..3]
    step_res &= 0x3;//Make sure that resolution is 3bits
    sr2_data |= step_res;
    stepper16_generic_write( ctx, STEPPER16_REG_CR2, sr2_data );
    stepper16_calculate_resolution( ctx );
}

void stepper16_move_motor_angle ( stepper16_t *ctx, float degree, uint8_t speed )
{
    if ( ( 0 == ctx->resolution ) || ( 0 == ctx->step_resolution )  )
    {
        stepper16_calculate_resolution( ctx );
    }
    
    uint16_t steps_to_move = ( uint16_t )( degree / ctx->resolution );
    
    steps_to_move *= ctx->step_resolution;
    
    for ( uint16_t step_cnt = 0; step_cnt < steps_to_move; step_cnt++ )
    {
        stepper16_set_next( ctx, 1 );
        stepper16_speed_delay( speed );
        stepper16_set_next( ctx, 0 );
        stepper16_speed_delay( speed );
    }
}

void stepper16_move_motor_step ( stepper16_t *ctx, uint16_t steps, uint8_t speed )
{
    if ( ( 0 == ctx->resolution ) || ( 0 == ctx->step_resolution )  )
    {
        stepper16_calculate_resolution( ctx );
    }
    
    uint16_t steps_to_move = ctx->step_resolution * steps;
    
    for ( uint16_t step_cnt = 0; step_cnt < steps_to_move; step_cnt++ )
    {
        stepper16_set_next( ctx, 1 );
        stepper16_speed_delay( speed );
        stepper16_set_next( ctx, 0 );
        stepper16_speed_delay( speed );
    }
}

void stepper16_calculate_resolution ( stepper16_t *ctx )
{
    ctx->resolution = FULL_CIRCLE / ctx->steps;
    
    uint16_t sr2_data = 0;
    stepper16_generic_read( ctx, STEPPER16_REG_CR2, &sr2_data );
    sr2_data &= 0x3;
    
    switch ( sr2_data )
    {
        case STEPPER16_STEP_RES_FULL:
        {
            ctx->step_resolution = 1;
            break;
        }
        case STEPPER16_STEP_RES_HALF:
        {
            ctx->step_resolution = 2;
            break;
        }
        case STEPPER16_STEP_RES_QUARTER:
        {
            ctx->step_resolution = 4;
            break;
        }
        case STEPPER16_STEP_RES_1div8:
        {
            ctx->step_resolution = 8;
            break;
        }
        case STEPPER16_STEP_RES_1div16:
        {
            ctx->step_resolution = 16;
            break;
        }
        default:
        {
            ctx->step_resolution = 1;
            break;
        }
    }
}

static void stepper16_speed_delay( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER16_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER16_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER16_SPEED_MEDIUM:
        {
            Delay_1ms( );
            break;
        }
        case STEPPER16_SPEED_FAST:
        {
            Delay_500us();
            Delay_80us();
            Delay_80us();
            Delay_50us();
            break;
        }
        case STEPPER16_SPEED_VERY_FAST:
        {
            Delay_500us();
            break;
        }
        default:
        {
            Delay_1ms( );
            break;
        }
    }
}

static void stepper16_filter_return ( uint8_t reg, uint16_t *return_value )
{
    switch ( reg )
    {
        case STEPPER16_REG_CR6:
        case STEPPER16_REG_SR1:
        case STEPPER16_REG_SR2:
        case STEPPER16_REG_SR3:
        case STEPPER16_REG_SR4:
        case STEPPER16_REG_SR5:
        case STEPPER16_REG_SR6:
        {
            *return_value &= 0xFF;
            break;
        }
        case STEPPER16_REG_CR4:
        {
            *return_value &= 0x1F;
            break;
        }
        case STEPPER16_REG_CR1:
        case STEPPER16_REG_CR3:
        case STEPPER16_REG_CR5:
        {
            *return_value &= 0x3FF;
            break;
        }
        case STEPPER16_REG_CR2:
        {
            *return_value &= 0x3FF;
            break;
        }
        default:
            *return_value &= 0xFF;
            break;
    }
}

static uint8_t stepper16_create_parity_write ( uint16_t dat_val )
{
    uint8_t parity = 0;
    
    parity = 1 ^//Write command bit
             ( ( dat_val >> 14 ) & 1 ) ^ //Reg address 3bit
             ( ( dat_val >> 13 ) & 1 ) ^ //Reg address 2bit
             ( ( dat_val >> 12 ) & 1 ) ^ //Reg address 1bit
             ( ( dat_val >> 11 ) & 1 ) ^ //Reg address 0bit
             ( ( dat_val >> 9 ) & 1 ) ^ //Data 9bit
             ( ( dat_val >> 8 ) & 1 ) ^ //Data 8bit
             ( ( dat_val >> 7 ) & 1 ) ^ //Data 7bit
             ( ( dat_val >> 6 ) & 1 ) ^ //Data 6bit
             ( ( dat_val >> 5 ) & 1 ) ^ //Data 5bit
             ( ( dat_val >> 4 ) & 1 ) ^ //Data 4bit
             ( ( dat_val >> 3 ) & 1 ) ^ //Data 3bit
             ( ( dat_val >> 2 ) & 1 ) ^ //Data 2bit
             ( ( dat_val >> 1 ) & 1 ) ^ //Data 1bit
             ( ( dat_val >> 0 ) & 1 );  //Data 0bit
                 
    parity = !parity;
    
    return parity & 1;
}

static uint8_t stepper16_create_parity_read ( uint8_t dat_val )
{
    uint8_t parity = 0;
    
    parity = 0 ^ //Read command bit
            ( ( dat_val >> 2 ) & 1 ) ^//Reg address 4bit
            ( ( dat_val >> 3 ) & 1 ) ^//Reg address 3bit
            ( ( dat_val >> 4 ) & 1 ) ^//Reg address 2bit
            ( ( dat_val >> 5 ) & 1 ) ^//Reg address 1bit
            ( ( dat_val >> 6 ) & 1 ); //Reg address 0bit
                 
    parity = !parity;
    
    return parity & 1;
}

// ------------------------------------------------------------------------- END
