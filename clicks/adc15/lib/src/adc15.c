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
 * @file adc15.c
 * @brief ADC 15 Click Driver.
 */

#include "adc15.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Voltage calculation macros.
 * @details Definition of voltage calculation macros.
 */
#define GAIN(x) 2.4 / ( float )x

/**
 * @brief CRC macros.
 * @details Definition of crc marcos.
 */
#define CRC_INIT_VAL 0xFFFF
#define CRC_POLYNOM  0x1021

/**
 * @brief Frequency calculation macros.
 * @details Definition of frequency calculation marcos.
 */
#define OCT_DIVIDER     1039.0
#define OCT_RES         3.322
#define DAC_OFFSET      2048.0
#define DAC_RES         2078
#define DAC_OCT_OFFSET  10

/**
 * @brief Bytes macros.
 * @details Definition of bytes marcos.
 */
#define LEN16BITS       2
#define LEN24BITS       3
#define LEN32BITS       4

/**
 * @brief CCITT-CRC16 calculation function.
 * @details This function calculates the ccitt-crc16 from buffer.
 * @param[in] ptr : Buffer address to calculate CRC from.
 * @param[in] count : Number of bytes to calculate.
 * @return Calculated CRC.
 */
static uint16_t crc16_ccitt ( char *ptr, int16_t count );

/**
 * @brief Buffer to word output data value.
 * @details This function gets word data from buffer.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] start_byte : Buffer address to get data from.
 * @param[out] output_data : Word data.
 * @return Nothing.
 */
static void buf_to_val ( adc15_t *ctx, uint8_t *start_byte, int32_t *output_data );

/**
 * @brief Word input data to buffer.
 * @details This function separates word input data in to buffer.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] input_data : Word data.
 * @param[out] start_byte : Buffer address to get data in.
 * @return Nothing.
 */
static void val_to_buf ( adc15_t *ctx, int32_t input_data, uint8_t *start_byte );

void adc15_cfg_setup ( adc15_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cs2 = HAL_PIN_NC;
    cfg->drdy = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t adc15_init ( adc15_t *ctx, adc15_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs2, cfg->cs2 );

    digital_in_init( &ctx->drdy, cfg->drdy );
    
    /* Set default values to context object */
    digital_out_high( &ctx->cs2 );
    ctx->word_len = ADC15_24bit + LEN16BITS;
    ctx->resolution = pow( 2, ctx->word_len * 8 ) + 0.1;
    ctx->gain1 = 1;
    ctx->gain2 = 1;

    return SPI_MASTER_SUCCESS;
}

err_t adc15_default_cfg ( adc15_t *ctx ) 
{
    err_t ret_val = ADC15_OK;
    ADC15_SET_DATA_SAMPLE_EDGE;
    ret_val |= adc15_set_frequency( ctx, ADC15_FREQ_MODE_HIGH_RESOLUTION );
    
    digital_out_low( &ctx->rst );
    Delay_1ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    
    ret_val |= adc15_set_word_len( ctx, ADC15_24bit );
    ret_val |= adc15_set_gain( ctx, ADC15_CHANNEL1, ADC15_GAIN1 );
    ret_val |= adc15_set_gain( ctx, ADC15_CHANNEL2, ADC15_GAIN1 );
    
    return ret_val;
}

err_t adc15_adc_write ( adc15_t *ctx, uint8_t *data_in, uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t adc15_reg_write ( adc15_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t temp_buf[ 16 ] = { 0 };
    uint32_t temp_data = ADC15_CMD_WREG | ( ( ( uint16_t )( reg & 0x3F ) ) << 7 );
    temp_data <<= ( 8 * ( ctx->word_len - 2 ) );
    val_to_buf( ctx, temp_data, temp_buf );
    
    temp_data = ( uint32_t )data_in << ( 8 * ( ctx->word_len - 2 ) );
    val_to_buf( ctx, temp_data, &temp_buf[ ctx->word_len ] );
    
    temp_data = crc16_ccitt( temp_buf, ctx->word_len * 2 );
    temp_data <<= ( 8 * ( ctx->word_len - 2 ) );
    val_to_buf( ctx, temp_data, &temp_buf[ ctx->word_len * 2 ] );
    
    err_t ret_val = adc15_adc_write( ctx, temp_buf, ctx->word_len * 3 );
    
    return ret_val;
}

err_t adc15_multiple_reg_write ( adc15_t *ctx, uint8_t reg, uint16_t *data_in, uint8_t data_size )
{
    uint8_t temp_buf[ 88 ] = { 0 };
    uint32_t temp_data = ADC15_CMD_WREG | 
                        ( ( ( uint16_t )( reg & 0x3F ) ) << 7 ) | 
                        ( ( data_size - 1 ) & 0x7F );
    temp_data <<= ( 8 * ( ctx->word_len - 2 ) );
    val_to_buf( ctx, temp_data, temp_buf );
    
    
    
    for ( uint8_t cnt = 0; cnt < data_size; cnt++ )
    {
        temp_data = ( uint32_t )data_in[ cnt ] << ( 8 * ( ctx->word_len - 2 ) );
        val_to_buf( ctx, temp_data, &temp_buf[ ctx->word_len * ( 1 + cnt ) ] );
    }
    
    temp_data = crc16_ccitt( temp_buf, ctx->word_len * ( data_size + 1 ) );
    temp_data <<= ( 8 * ( ctx->word_len - 2 ) );
    val_to_buf( ctx, temp_data, &temp_buf[ ctx->word_len * ( data_size + 1 ) ] );
    
    err_t ret_val = adc15_adc_write( ctx, temp_buf, ctx->word_len * ( 2 + data_size ) );
    
    return ret_val;
}

err_t adc15_adc_read ( adc15_t *ctx, uint8_t *data_out, uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t adc15_adc_transfer ( adc15_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t len )
{
    err_t ret_val = ADC15_OK;
    spi_master_select_device( ctx->chip_select );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        spi_master_set_default_write_data( &ctx->spi, data_in[ cnt ] );
        ret_val |= spi_master_read( &ctx->spi, &data_out[ cnt ], 1 );
    }
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    
    return ret_val;
}

err_t adc15_reg_read ( adc15_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t temp_buf[ 16 ] = { 0 };
    int32_t temp_data = ADC15_CMD_RREG | ( ( ( uint16_t )( reg & 0x3F ) ) << 7 );
    temp_data <<= ( 8 * ( ctx->word_len - 2 ) );
    val_to_buf( ctx, temp_data, temp_buf );
    
    temp_data = crc16_ccitt( temp_buf, ctx->word_len );
    temp_data <<= ( 8 * ( ctx->word_len - 2 ) );
    val_to_buf( ctx, temp_data, &temp_buf[ ctx->word_len ] );
    
    err_t ret_val = adc15_adc_write( ctx, temp_buf, ctx->word_len * 2 );
    ret_val |= adc15_adc_read( ctx, temp_buf, ctx->word_len );
    buf_to_val( ctx, temp_buf, &temp_data );
    *data_out = temp_data >> ( 8 * ( ctx->word_len - 2 ) );
    
    return ret_val;
}

err_t adc15_multiple_reg_read ( adc15_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t data_size )
{
    uint8_t temp_buf[ 88 ] = { 0 };
    int32_t temp_data = ADC15_CMD_RREG | 
                        ( ( ( uint16_t )( reg & 0x3F ) ) << 7 ) | 
                        ( ( data_size - 1 ) & 0x7F );
                        
    temp_data <<= ( 8 * ( ctx->word_len - 2 ) );
    val_to_buf( ctx, temp_data, temp_buf );
    
    temp_data = crc16_ccitt( temp_buf, ctx->word_len );
    temp_data <<= ( 8 * ( ctx->word_len - 2 ) );
    val_to_buf( ctx, temp_data, &temp_buf[ ctx->word_len ] );
    
    err_t ret_val = adc15_adc_write( ctx, temp_buf, ctx->word_len * 2 );
    ret_val |= adc15_adc_read( ctx, temp_buf, ctx->word_len * ( data_size + 1 ) );
    
    for ( uint8_t cnt = 1; cnt < data_size; cnt++ )
    {
        buf_to_val( ctx, &temp_buf[ cnt * ctx->word_len ], &temp_data );
        data_out[ cnt - 1 ] = temp_data >> ( 8 * ( ctx->word_len - 2 ) );
    }
    
    return ret_val;
}

err_t adc15_ltc_write ( adc15_t *ctx, uint8_t oct, uint16_t dac, uint8_t cfg )
{
    spi_master_set_mode( &ctx->spi, SPI_MASTER_MODE_0 );
    ADC15_SET_DATA_SAMPLE_MIDDLE;
    uint16_t temp_data = 0;
    temp_data |= ( uint16_t )( oct & 0xF ) << 12;
    temp_data |= ( uint16_t )( dac & 0x3FF ) << 2;
    temp_data |= ( uint16_t )( cfg & 0x3 ) << 0;
    uint8_t tx_data[ 2 ] = { temp_data >> 8, temp_data };
    
    digital_out_low( &ctx->cs2 );
    err_t error_flag = spi_master_write( &ctx->spi, tx_data, 2 );
    digital_out_high( &ctx->cs2 );
    spi_master_set_mode( &ctx->spi, SPI_MASTER_MODE_1 );
    ADC15_SET_DATA_SAMPLE_EDGE;
    
    return error_flag;
}

err_t adc15_set_frequency ( adc15_t *ctx, uint32_t frequency )
{
    uint8_t oct = OCT_RES * log10( frequency / OCT_DIVIDER );
    uint16_t dac = DAC_OFFSET - ( ( DAC_RES * pow( 2, DAC_OCT_OFFSET + oct ) ) / ( float )frequency );
    return adc15_ltc_write( ctx, oct, dac, ADC15_LDC_CFG_POWER_ON );
}

err_t adc15_read_adc_value ( adc15_t *ctx, uint16_t *status, int32_t *ch1_out, int32_t *ch2_out )
{
    err_t ret_val = ADC15_OK;
    int32_t temp_data = 0;
    uint8_t out_buf[ 16 ] = { DUMMY };
    *ch1_out = 0;
    *ch2_out = 0;
    *status = 0;
    
    ret_val = adc15_adc_read( ctx, out_buf, ctx->word_len * 4 );
    
    if ( !ret_val )
    {       
        buf_to_val( ctx, out_buf, &temp_data );
        *status = temp_data >> ( 8 * ( ctx->word_len - 2 ) );
        buf_to_val( ctx, &out_buf[ ctx->word_len ] , ch1_out );
        buf_to_val( ctx, &out_buf[ ctx->word_len * 2 ], ch2_out );
        
        buf_to_val( ctx, &out_buf[ ctx->word_len * 3 ], &temp_data );
        volatile uint16_t crc_val = temp_data >> ( 8 * ( ctx->word_len - 2 ) );
        volatile uint16_t calculated_crc = crc16_ccitt( out_buf, ctx->word_len * 3 );
        if ( calculated_crc != crc_val )
        {
            ret_val = ADC15_ERROR;
        }
    }
    
    return ret_val;
}

err_t adc15_read_voltage ( adc15_t *ctx, uint16_t *status, float *ch1_out, float *ch2_out )
{
    int32_t channel1 = 0;
    int32_t channel2 = 0;
    err_t ret_val = adc15_read_adc_value( ctx, status, &channel1, &channel2 );
    if ( !ret_val )
    {
        *ch1_out = channel1 * GAIN(ctx->gain1);
        *ch1_out /= ( float )ctx->resolution;
        *ch2_out = channel2 * GAIN(ctx->gain2);
        *ch2_out /= ( float )ctx->resolution;
    }
    return ret_val;
}

uint8_t adc15_data_ready ( adc15_t *ctx )
{
    return digital_in_read( &ctx->drdy );
}

err_t adc15_set_gain ( adc15_t *ctx, adc15_channel_t channel, adc15_gain_t gain )
{
    uint16_t current_gain = 0;
    err_t ret_val = adc15_reg_read( ctx, ADC15_REG_GAIN, &current_gain );
    current_gain &= ~( ADC15_GAIN128 << channel );
    current_gain |= gain << channel;
    ret_val |= adc15_reg_write( ctx, ADC15_REG_GAIN, current_gain );
    
    if ( channel )
    {
        ctx->gain2 = pow( 2, gain ) + 0.1;
    }
    else
    {
        ctx->gain1 = pow( 2, gain ) + 0.1;
    }
    
    return ret_val;
}

err_t adc15_set_word_len ( adc15_t *ctx, adc15_word_t word_len )
{
    uint16_t current_gain = 0;
    err_t ret_val = adc15_reg_read( ctx, ADC15_REG_MODE, &current_gain );
    current_gain &= ~( 3 << 8 );/**< Clear word len cfgs*/
    current_gain |= word_len << 8;
    ret_val |= adc15_reg_write( ctx, ADC15_REG_MODE, current_gain );
    ctx->word_len = LEN16BITS + word_len;
    ctx->resolution = pow( 2, ctx->word_len * 8 ) + 0.1;
    return ret_val;
}

static uint16_t crc16_ccitt ( char *ptr, int16_t count )
{
   uint16_t crc;
   char i;
   crc = CRC_INIT_VAL;
   while ( --count >= 0 )
   {
      crc = crc ^ ( uint16_t ) *ptr++ << 8;
      i = 8;
      do
      {
         if ( crc & 0x8000 )
         {
             crc = crc << 1 ^ CRC_POLYNOM;
        }
         else
         {
             crc = crc << 1;
        }
      } while ( --i );
   }
   return crc;
}

static void buf_to_val ( adc15_t *ctx, uint8_t *start_byte, int32_t *output_data )
{
    switch ( ctx->word_len )
    {
        case LEN16BITS:/**< 16bits*/
        {
            *output_data = ( ( ( int32_t )start_byte[ 0 ] << 24 ) | 
                             ( ( int32_t )start_byte[ 1 ] << 16 ) );
            *output_data >>= 16;
            break;
        }
        case LEN24BITS:/**< 24bits*/
        {
            *output_data = ( ( ( int32_t )start_byte[ 0 ] << 24 ) | 
                             ( ( int32_t )start_byte[ 1 ] << 16 ) | 
                             ( ( int32_t )start_byte[ 2 ] << 8  ) );
            *output_data >>= 8;
            break;
        }
        case LEN32BITS:/**< 32bits*/
        {
            *output_data = ( ( ( int32_t )start_byte[ 0 ] << 24 ) | 
                             ( ( int32_t )start_byte[ 1 ] << 16 ) | 
                             ( ( int32_t )start_byte[ 2 ] << 8  ) | 
                             ( ( int32_t )start_byte[ 3 ] << 0  ) );
            break;
        }
        default:
        {
            *output_data = 0;
            break;
        }
    }
}

static void val_to_buf ( adc15_t *ctx, int32_t input_data, uint8_t *start_byte )
{
    switch ( ctx->word_len )
    {
        case LEN16BITS:/**< 16bits*/
        {
            start_byte[ 0 ] = ( uint8_t )( input_data >> 8 );
            start_byte[ 1 ] = ( uint8_t )input_data;
            break;
        }
        case LEN24BITS:/**< 24bits*/
        {
            start_byte[ 0 ] = ( uint8_t )( input_data >> 16 );
            start_byte[ 1 ] = ( uint8_t )( input_data >> 8 );
            start_byte[ 2 ] = ( uint8_t )input_data;
            break;
        }
        case LEN32BITS:/**< 32bits*/
        {
            start_byte[ 0 ] = ( uint8_t )( input_data >> 24 );
            start_byte[ 1 ] = ( uint8_t )( input_data >> 16 );
            start_byte[ 2 ] = ( uint8_t )( input_data >> 8 );
            start_byte[ 3 ] = ( uint8_t )input_data;
            break;
        }
        default:
        {
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
