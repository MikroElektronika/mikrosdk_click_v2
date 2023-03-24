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
 * @file barometer7.c
 * @brief Barometer 7 Click Driver.
 */

#include "barometer7.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                          0x00

/**
 * @brief Bit masks.
 * @details Definition of bit masks data.
 */
#define PARITY_BIT_MASK                0x01
#define DIAGNOSIS_BIT_MASK             0x1F
#define SUPPLIER_BIT_MASK              0x03
#define SILICON_VER_BIT_MASK           0x07
#define METAL_BIT_MASK                 0x07
#define DATA_OUT_10_BIT                0x03FF

/**
 * @brief Pressure and temperature calculation values.
 * @details Definition of pressure and temperature calculation values.
 */
#define PRESSURE_VALUE_MIN_kPa          40
#define PRESSURE_VALUE_MAX_kPa         115
#define PRESSURE_CONVERT_kPa_TO_mbar    10
#define TEMPERATURE_VALUE_MIN_C        -40
#define TEMPERATURE_VALUE_MAX_C        160

/**
 * @brief Check command function.
 * @details This function check the selected command.
 * @return @li @c  0 - Successfully selected command,
 *         @li @c -1 - Error selected command.
 */
static err_t dev_check_cmd ( uint8_t cmd );

/**
 * @brief Reset delay function.
 * @details This function executes a reset delay of the 100 milliseconds. 
 */
static void dev_reset_delay ( void );

/**
 * @brief Command delay function.
 * @details This function executes a command delay of the 10 milliseconds. 
 */
static void dev_cmd_delay ( void );

void barometer7_cfg_setup ( barometer7_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t barometer7_init ( barometer7_t *ctx, barometer7_cfg_t *cfg ) 
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

    return SPI_MASTER_SUCCESS;
}

err_t barometer7_default_cfg ( barometer7_t *ctx ) 
{
    uint16_t data_out;
    
    err_t error_flag = barometer7_set_reset( ctx, BAROMETER7_CMD_ACQUIRE_PRESSURE, &data_out );
    dev_reset_delay( );
    
    error_flag |= barometer7_set_reset( ctx, BAROMETER7_CMD_ACQUIRE_TEMPERATURE, &data_out );
    dev_reset_delay( );

    return error_flag;
}

err_t barometer7_generic_transfer ( barometer7_t *ctx, uint8_t cmd, uint16_t *data_out ) 
{
    uint8_t msb, lsb;
    
    if ( BAROMETER7_ERROR == dev_check_cmd( cmd ) )
    {
        return  BAROMETER7_CMD_ERROR;  
    }
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_set_default_write_data( &ctx->spi, cmd );
    error_flag |= spi_master_read( &ctx->spi, &msb, 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &lsb, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    dev_cmd_delay( );
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, cmd );
    error_flag |= spi_master_read( &ctx->spi, &msb, 1 );
    *data_out = msb;
    ctx->diagnosis = ( msb >> 3 ) & DIAGNOSIS_BIT_MASK;
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &lsb, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    ctx->parity = lsb & PARITY_BIT_MASK;
    
    *data_out <<= 8;
    *data_out |= lsb;
    *data_out >>= 1;
    *data_out &= DATA_OUT_10_BIT;

    return error_flag;
}

err_t barometer7_set_command ( barometer7_t *ctx, uint8_t cmd, uint16_t *data_out ) 
{
    uint8_t tx_buf[ 2 ];
    uint8_t msb, lsb;
    
    if ( BAROMETER7_ERROR == dev_check_cmd( cmd ) )
    {
        return  BAROMETER7_CMD_ERROR;  
    }
    
    tx_buf[ 0 ] = cmd;
    tx_buf[ 1 ] = DUMMY; 
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_set_default_write_data( &ctx->spi, cmd );
    error_flag |= spi_master_read( &ctx->spi, &msb, 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &lsb, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    ctx->diagnosis = ( msb >> 3 ) & DIAGNOSIS_BIT_MASK;
    
    *data_out = msb;
    *data_out <<= 8;
    *data_out |= lsb;
    *data_out >>= 1;
    *data_out &= DATA_OUT_10_BIT;
    
    ctx->parity = lsb & PARITY_BIT_MASK;

    return error_flag;
}

err_t barometer7_set_reset ( barometer7_t *ctx, uint8_t cmd, uint16_t *data_out ) 
{   
    cmd |= BAROMETER7_CMD_RESET_BIT_MASK;

    return barometer7_set_command( ctx, cmd, data_out );
}

err_t barometer7_get_press_data ( barometer7_t *ctx, uint16_t *press_data ) 
{
    return barometer7_generic_transfer( ctx, BAROMETER7_CMD_ACQUIRE_PRESSURE, press_data );
}

err_t barometer7_get_temp_data ( barometer7_t *ctx, uint16_t *temp_data ) 
{
    return barometer7_generic_transfer( ctx, BAROMETER7_CMD_ACQUIRE_TEMPERATURE, temp_data );
}

err_t barometer7_get_trigger_diagnosis_data ( barometer7_t *ctx, uint16_t *td_data ) 
{
    return barometer7_generic_transfer( ctx, BAROMETER7_CMD_TRIGGER_DIAGNOSIS, td_data );
}

err_t barometer7_trigger_test_mode ( barometer7_t *ctx, uint16_t *tdm_data ) 
{
    return barometer7_generic_transfer( ctx, BAROMETER7_CMD_TRIGGER_TEST_MODE, tdm_data );
}

err_t barometer7_get_id_data ( barometer7_t *ctx, uint16_t *id_data ) 
{
    uint16_t out_data;
    uint8_t msb, lsb;
    
    err_t error_flag = barometer7_set_command( ctx, BAROMETER7_CMD_ACQUIRE_IDENTIFIER, &out_data );
    dev_cmd_delay( );
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, BAROMETER7_CMD_ACQUIRE_IDENTIFIER );
    error_flag |= spi_master_read( &ctx->spi, &msb, 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &lsb, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    *id_data = msb;
    *id_data <<= 8;
    *id_data |= lsb;
    
    return error_flag;
}

err_t barometer7_get_identifier ( barometer7_t *ctx, barometer7_identifier_t *identifier ) 
{
    uint16_t data_out;
    
    err_t error_flag = barometer7_get_id_data( ctx, &data_out );
    
    identifier->supplier        = ( uint8_t ) ( ( data_out >> 14 ) & SUPPLIER_BIT_MASK );
    identifier->silicon_version = ( uint8_t ) ( ( data_out >> 11 ) & SILICON_VER_BIT_MASK );
    identifier->metal_version   = ( uint8_t ) ( ( data_out >> 8  ) & METAL_BIT_MASK );
    identifier->asic_name       = ( uint8_t )     data_out;

    return error_flag;
}

err_t barometer7_get_pressure ( barometer7_t *ctx, float *pressure ) 
{
    uint16_t data_out;

    err_t error_flag = barometer7_get_press_data( ctx, &data_out );
    
    *pressure = ( float ) data_out;
    *pressure /= DATA_OUT_10_BIT;
    *pressure *= ( PRESSURE_VALUE_MAX_kPa - PRESSURE_VALUE_MIN_kPa );
    *pressure += PRESSURE_VALUE_MIN_kPa;
    *pressure *= PRESSURE_CONVERT_kPa_TO_mbar;

    return error_flag;
}

err_t barometer7_get_temperature ( barometer7_t *ctx, float *temperature ) 
{
    uint16_t data_out;

    err_t error_flag = barometer7_get_temp_data( ctx, &data_out );
    
    *temperature = ( float ) data_out;
    *temperature /= DATA_OUT_10_BIT;
    *temperature *= ( TEMPERATURE_VALUE_MAX_C - TEMPERATURE_VALUE_MIN_C );
    *temperature += TEMPERATURE_VALUE_MIN_C;

    return error_flag;
}

static err_t dev_check_cmd ( uint8_t cmd ) 
{
    err_t error_flag = BAROMETER7_OK;
    
    switch ( cmd )
    {
        case BAROMETER7_CMD_TRIGGER_TEST_MODE: 
        {
            break;
        }
        case BAROMETER7_CMD_ACQUIRE_PRESSURE: 
        {
            break;
        }
        case BAROMETER7_CMD_ACQUIRE_TEMPERATURE: 
        {
            break;
        }
        case BAROMETER7_CMD_TRIGGER_DIAGNOSIS: 
        {
            break;
        }
        case BAROMETER7_CMD_ACQUIRE_IDENTIFIER: 
        {
            break;
        }
        default: 
        {
            error_flag = BAROMETER7_ERROR; 
            break;
        }
    }

    return error_flag;
}

static void dev_reset_delay ( void ) 
{
    Delay_100ms( );
}

static void dev_cmd_delay ( void ) 
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END
