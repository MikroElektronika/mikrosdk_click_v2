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
 * @file digiin.c
 * @brief DIGI IN Click Driver.
 */

#include "digiin.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/** 
 * @brief Calculation for CRC 5 function.
 * @details This function calculates CRC 5 with parameteres: 
 * @li @c  Width 5 bit
 * @li @c  Polynomial 0x35 ( x5 + x4 + x2 + 1 )
 * @li @c  Initialization 0x07
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] byte1 : Byte 1 for CRC calculation.
 * @param[in] byte2 : Byte 2 for CRC calculation.
 * @param[in] byte3 : Byte 3 for CRC calculation.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t digiin_crc5_encode_3byte( uint8_t byte1, uint8_t byte2, uint8_t byte3 );

void digiin_cfg_setup ( digiin_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rdy  = HAL_PIN_NC;
    cfg->ltc  = HAL_PIN_NC;
    cfg->flt  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t digiin_init ( digiin_t *ctx, digiin_cfg_t *cfg ) 
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

    digital_out_init( &ctx->ltc, cfg->ltc );

    digital_in_init( &ctx->rdy, cfg->rdy );
    digital_in_init( &ctx->flt, cfg->flt );

    ctx->crc_en = DIGIIN_M0_0;

    return SPI_MASTER_SUCCESS;
}

err_t digiin_default_cfg ( digiin_t *ctx ) 
{
    err_t error_flag = DIGIIN_OK;

    error_flag |= digiin_write_reg( ctx, DIGIIN_REG_FILTER_IN1, DIGIIN_FILTER_BYPASSED );
    error_flag |= digiin_write_reg( ctx, DIGIIN_REG_FILTER_IN2, DIGIIN_FILTER_BYPASSED );
    error_flag |= digiin_write_reg( ctx, DIGIIN_REG_FILTER_IN3, DIGIIN_FILTER_BYPASSED );
    error_flag |= digiin_write_reg( ctx, DIGIIN_REG_FILTER_IN4, DIGIIN_FILTER_BYPASSED );
    error_flag |= digiin_write_reg( ctx, DIGIIN_REG_FILTER_IN5, DIGIIN_FILTER_BYPASSED );
    error_flag |= digiin_write_reg( ctx, DIGIIN_REG_FILTER_IN6, DIGIIN_FILTER_BYPASSED );
    error_flag |= digiin_write_reg( ctx, DIGIIN_REG_FILTER_IN7, DIGIIN_FILTER_BYPASSED );
    error_flag |= digiin_write_reg( ctx, DIGIIN_REG_FILTER_IN8, DIGIIN_FILTER_BYPASSED );
    error_flag |= digiin_write_reg( ctx, DIGIIN_REG_INOPUT_ENABLE, DIGIIN_CHANNEL_ALL_MASK );
    error_flag |= digiin_write_reg( ctx, DIGIIN_REG_FAULT1_ENABLE, DIGIIN_CRC_ERROR_FLAG_MASK | 
                                         DIGIIN_FAULT2_MASK | DIGIIN_TERMAL_SHUTDOWN_MASK | 
                                         DIGIIN_TEMPERATURE_ALARM_MASK | DIGIIN_V24_UNDERVOLTAGE_MASK | 
                                         DIGIIN_VM_VOLTAGE_LOW_MASK );
    error_flag |= digiin_write_reg( ctx, DIGIIN_REG_FAULT1, DIGIIN_POR_CLEAR_MASK  );

    return error_flag;
}

err_t digiin_generic_write ( digiin_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t digiin_generic_read ( digiin_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void digiin_set_ltc_pin ( digiin_t *ctx, uint8_t pin_state )
{
    if ( DIGIIN_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->ltc );
    }
    else
    {
        digital_out_low( &ctx->ltc );
    }
}

uint8_t digiin_get_rdy_pin ( digiin_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

uint8_t digiin_get_flt_pin ( digiin_t *ctx )
{
    return digital_in_read( &ctx->flt );
}

err_t digiin_write_reg ( digiin_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = DIGIIN_OK;
    uint8_t reg_data = reg | DIGIIN_SPI_WRITE_MASK;

    if ( DIGIIN_M0_0 == ctx->crc_en )
    {
        uint8_t tmp_data[ 2 ] = { 0 };
        tmp_data[ 0 ] = data_in;
        tmp_data[ 1 ] = digiin_crc5_encode_3byte( reg_data, data_in, 0 );
        error_flag |= digiin_generic_write( ctx, reg_data, tmp_data, 2 );
    }
    else
    {
        error_flag |= digiin_generic_write( ctx, reg_data, &data_in, 1 );
    }

    return error_flag;
}

err_t digiin_read_reg ( digiin_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = DIGIIN_OK;
    uint8_t reg_data = reg;

    if ( DIGIIN_M0_0 == ctx->crc_en )
    {
        uint8_t read_data1 = 0;
        uint8_t read_data2 = 0;
        uint8_t read_data3 = 0;
        uint8_t crc_data = 0;

        spi_master_set_default_write_data( &ctx->spi, reg_data );
        spi_master_select_device( ctx->chip_select );

        err_t error_flag = spi_master_read( &ctx->spi, &read_data1, 1 );
        spi_master_set_default_write_data( &ctx->spi, DUMMY );

        error_flag |= spi_master_read( &ctx->spi, &read_data2, 1 );
        crc_data = digiin_crc5_encode_3byte( reg_data, DUMMY, DUMMY );
        spi_master_set_default_write_data( &ctx->spi, crc_data );

        error_flag |= spi_master_read( &ctx->spi, &read_data3, 1 );
        spi_master_deselect_device( ctx->chip_select );
        spi_master_set_default_write_data( &ctx->spi, DUMMY );

        *data_out = read_data2;
        crc_data = digiin_crc5_encode_3byte( read_data1, read_data2, read_data3 );
        if ( crc_data != ( read_data3 & DIGIIN_CRC_MASK ) )
        {
            return DIGIIN_ERROR;
        }
    }
    else
    {
        error_flag |= digiin_generic_read( ctx, reg_data, data_out, 1 );
    }

    return error_flag;
}

void digiin_pulse_latch ( digiin_t *ctx )
{
    digiin_set_ltc_pin( ctx, DIGIIN_PIN_STATE_LOW );
    Delay_10ms( );
    digiin_set_ltc_pin( ctx, DIGIIN_PIN_STATE_HIGH );
}

static uint8_t digiin_crc5_encode_3byte( uint8_t byte1, uint8_t byte2, uint8_t byte3 )
{
    const uint8_t length = 19;        //19-Bit data
    const uint8_t crc_init = 0x07;    //5-Bit init word, constant, 00111
    const uint8_t crc_poly = 0x35;    //6-Bit polynomial, constant, 110101
    uint8_t loop_cnt;
    uint8_t crc_step;
    uint8_t crc_result;
    uint8_t tmp;
    
    //  Construct 24-bit data frame
    uint32_t data_input = ( uint32_t ) byte1 << 16 | ( uint32_t ) byte2 << 8 | byte3;
    //  Append 5-bit init word to first 19-bit data
    data_input = ( data_input & 0xFFFFE0 ) + crc_init;
    
    //  First step, get crc_step 0
    tmp = ( uint8_t ) ( ( data_input & 0xFC0000 ) >> 18 ); //crc_step 0= data[18:13]
    //  Next crc_step = crc_step[5] = 1 ? (crc_step[5:0] ^ crc_poly) : crc_step[5:0]
    if ( ( tmp & 0x20 ) == 0x20 ) 
    {
        crc_step = (uint8_t)(tmp ^ crc_poly);
    }
    else
    {
        crc_step = tmp;
    }
    //  Step 1-18
    for (loop_cnt = 0; loop_cnt < length - 1; loop_cnt++)
    {
        //  Append next data bit to previous crc_step[4:0], {crc_step[4:0], next data bit}
        tmp = ( uint8_t ) ( ( ( crc_step & 0x1F ) << 1 ) + ( ( data_input >> ( length - 2 - loop_cnt ) ) & 0x01 ) );
        //  Next crc_step = crc_step[5] = 1 ? (crc_step[5:0] ^ crc_poly) : crc_step[5:0]
        if ( ( tmp & 0x20 ) == 0x20 )
        {
            crc_step = ( uint8_t ) ( tmp ^ crc_poly );
        }
        else
        {
            crc_step = tmp;
        }
    }
    crc_result = ( uint8_t ) ( crc_step & 0x1F ); // Crc result = crc_step[4:0]
    return crc_result;
}

// ------------------------------------------------------------------------- END
