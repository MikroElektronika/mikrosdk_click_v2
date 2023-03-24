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
 * @file loadcell6.c
 * @brief Load Cell 6 Click Driver.
 */

#include "loadcell6.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                           0x00

/**
 * @brief SPI bit masks.
 * @details Definition of bit masks data.
 */
#define SPI_REG_ADDR_BIT_MASK           0x1F
#define SPI_READ_BIT_MASK               0x01
#define SPI_WRITE_BIT_MASK              0xFE
#define CMD_CONVERSION_MODE             0xBF
#define DATA_24_BIT_MASK                0x00FFFFFF

/**
 * @brief Load Cell 6 measure delay function.
 * @details This function executes a measure delay of the 1 microseconds.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_measure_delay ( void );

/**
 * @brief Load Cell 6 reset delay function.
 * @details This function executes a reset delay of the 100 milliseconds.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_reset_delay ( void );

/**
 * @brief Load Cell 6 sync delay function.
 * @details This function executes a sync delay of the 10 milliseconds.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_sync_delay ( void );

/**
 * @brief Load Cell 6 config delay function.
 * @details This function executes a configuration delay of the 10 milliseconds.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_config_delay ( void );

void loadcell6_cfg_setup ( loadcell6_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->syn = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t loadcell6_init ( loadcell6_t *ctx, loadcell6_cfg_t *cfg ) 
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

    digital_in_init( &ctx->syn, cfg->syn );
    digital_in_init( &ctx->rdy, cfg->rdy );

    return SPI_MASTER_SUCCESS;
}

err_t loadcell6_default_cfg ( loadcell6_t *ctx ) 
{
    err_t error_flag = LOADCELL6_OK;
    
    loadcell6_hw_reset( ctx );
    dev_config_delay( );
    
    loadcell6_write_reg( ctx, LOADCELL6_REG_CTRL1,  LOADCELL6_CTRL1_SYNC   |
                                                    LOADCELL6_CTRL1_U_B    |
                                                    LOADCELL6_CTRL1_SCYCLE |
                                                    LOADCELL6_CTRL1_CONTSC
    );
    dev_config_delay( );
    
    loadcell6_write_reg( ctx, LOADCELL6_REG_CTRL2,  LOADCELL6_CTRL2_PGAGEN |
                                                    LOADCELL6_CTRL2_PGAIN_x1
    );
    dev_config_delay( );
    
    loadcell6_write_reg( ctx, LOADCELL6_REG_CTRL3,  LOADCELL6_CTRL3_RESERVED );
    dev_config_delay( );
    
    loadcell6_write_reg( ctx, LOADCELL6_REG_CTRL4,  LOADCELL6_CTRL4_DIR1 |
                                                    LOADCELL6_CTRL4_DIO4 |
                                                    LOADCELL6_CTRL4_DIO3 |
                                                    LOADCELL6_CTRL4_DIO2
    );
    dev_config_delay( );
    
    loadcell6_write_reg( ctx, LOADCELL6_REG_CTRL5,  LOADCELL6_CTRL5_NOSYSG |
                                                    LOADCELL6_CTRL5_NOSYSO |
                                                    LOADCELL6_CTRL5_NOSCG  |
                                                    LOADCELL6_CTRL5_NOSCO
    );
    dev_reset_delay( );

    return error_flag;
}

err_t loadcell6_hw_reset ( loadcell6_t *ctx ) 
{
    err_t error_flag = LOADCELL6_OK;
    
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_reset_delay( );

    return error_flag;
}

uint8_t loadcell6_sync ( loadcell6_t *ctx ) 
{
    return digital_in_read( &ctx->syn );
}

uint8_t loadcell6_check_data_ready ( loadcell6_t *ctx ) 
{
    return digital_in_read( &ctx->rdy );
}

err_t loadcell6_generic_write ( loadcell6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t loadcell6_generic_read ( loadcell6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{   
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t loadcell6_write_reg ( loadcell6_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t tx_buf[ 2 ];
    
    reg &= SPI_REG_ADDR_BIT_MASK;
    
    tx_buf[ 0 ] = reg << 1; 
    tx_buf[ 0 ] |= LOADCELL6_CMD_START | LOADCELL6_CMD_REG_ACCESS_MODE;
    tx_buf[ 0 ] &= SPI_WRITE_BIT_MASK;
    
    tx_buf[ 1 ] = data_in; 
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t loadcell6_read_reg ( loadcell6_t *ctx, uint8_t reg, uint8_t *data_out ) 
{ 
    reg &= SPI_REG_ADDR_BIT_MASK;
    reg <<= 1; 
    reg |= LOADCELL6_CMD_START | LOADCELL6_CMD_REG_ACCESS_MODE;
    reg |= SPI_READ_BIT_MASK;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t loadcell6_write_reg_data ( loadcell6_t *ctx, uint8_t reg, uint32_t data_in ) 
{ 
    uint8_t tx_buf[ 4 ];
    
    data_in &= DATA_24_BIT_MASK;
    
    reg &= SPI_REG_ADDR_BIT_MASK;
    reg <<= 1; 
    reg |= LOADCELL6_CMD_START | LOADCELL6_CMD_REG_ACCESS_MODE;
    reg |= SPI_WRITE_BIT_MASK;
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = ( uint8_t ) ( data_in >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( data_in >> 8 );
    tx_buf[ 3 ] = ( uint8_t )  data_in;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );  

    return error_flag;
}

err_t loadcell6_read_reg_data ( loadcell6_t *ctx, uint8_t reg, uint32_t *data_out ) 
{ 
    uint8_t rx_buf[ 3 ];
    
    reg &= SPI_REG_ADDR_BIT_MASK;
    reg <<= 1; 
    reg |= LOADCELL6_CMD_START | LOADCELL6_CMD_REG_ACCESS_MODE;
    reg |= SPI_READ_BIT_MASK;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, rx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    *data_out = rx_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 1 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 2 ];

    return error_flag;
}

err_t loadcell6_set_command ( loadcell6_t *ctx, uint8_t cmd ) 
{    
    cmd |= LOADCELL6_CMD_START;
    cmd &= CMD_CONVERSION_MODE;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t loadcell6_get_status ( loadcell6_t *ctx, uint16_t *status ) 
{    
    uint8_t rx_buf[ 2 ];
    
    err_t error_flag = loadcell6_generic_read ( ctx, LOADCELL6_CMD_START           |
                                                     LOADCELL6_CMD_REG_ACCESS_MODE |
                                                     SPI_READ_BIT_MASK             |
                                                     LOADCELL6_REG_STAT, rx_buf, 2 );
    
    *status = rx_buf[ 0 ];
    *status <<= 8;
    *status |= rx_buf[ 1 ];

    return error_flag;
}

err_t loadcell6_read_adc ( loadcell6_t *ctx, uint32_t *data_out ) 
{ 
    uint16_t status = 0xFFFF;
    
    err_t error_flag = loadcell6_set_command( ctx, LOADCELL6_CMD_START );

    do
    {
        loadcell6_get_status( ctx, &status );
    }
    while ( ( status & LOADCELL6_STAT_RDY ) != 1 );
    while ( loadcell6_check_data_ready( ctx ) == 1 );
    error_flag |= loadcell6_read_reg_data( ctx, LOADCELL6_REG_DATA,  data_out );

    return error_flag;
}

err_t loadcell6_tare ( loadcell6_t *ctx, loadcell6_data_t *cell_data ) 
{
    uint32_t result;
    uint32_t sum_val;
    float average_val;
    err_t error_flag = LOADCELL6_OK;

    for (  uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ ) 
    {
        error_flag |= loadcell6_read_adc( ctx, &result );
        dev_measure_delay( );
    }

    sum_val = 0;

    for ( uint8_t n_cnt = 0; n_cnt < 100; n_cnt++ ) 
    {
        error_flag |= loadcell6_read_adc( ctx, &result );
        sum_val += result;
        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= 100.0;

    cell_data->tare = average_val;
    cell_data->tare_ok = LOADCELL6_DATA_OK;
    cell_data->weight_data_100g_ok = LOADCELL6_DATA_NO_DATA;
    cell_data->weight_data_200g_ok = LOADCELL6_DATA_NO_DATA;
    cell_data->weight_data_500g_ok = LOADCELL6_DATA_NO_DATA;
    cell_data->weight_data_1000g_ok = LOADCELL6_DATA_NO_DATA;
    cell_data->weight_data_5000g_ok = LOADCELL6_DATA_NO_DATA;
    cell_data->weight_data_10000g_ok = LOADCELL6_DATA_NO_DATA;
    
    return error_flag;
}

err_t loadcell6_calibration ( loadcell6_t *ctx, uint16_t cal_val, loadcell6_data_t *cell_data ) 
{
    uint32_t result;
    uint32_t sum_val;
    float average_val;
    float tare_val;
    float weight_val;
    err_t error_flag = LOADCELL6_OK;

    tare_val = cell_data->tare;

    sum_val = 0;

    for ( uint8_t n_cnt = 0; n_cnt < 100; n_cnt++ ) 
    {
        error_flag |= loadcell6_read_adc( ctx, &result );
        sum_val += result;
        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= 100.0;

    weight_val = average_val - tare_val;

    switch ( cal_val ) 
    {
        case LOADCELL6_WEIGHT_100G : 
        {
            cell_data->weight_coeff_100g = 100.0 / weight_val;
            cell_data->weight_data_100g_ok = LOADCELL6_DATA_OK;
            break;
        }
        case LOADCELL6_WEIGHT_200G : 
        {
            cell_data->weight_coeff_200g = 200.0 / weight_val;
            cell_data->weight_data_200g_ok = LOADCELL6_DATA_OK;
            break;
        }
        case LOADCELL6_WEIGHT_500G : 
        {
            cell_data->weight_coeff_500g = 500.0 / weight_val;
            cell_data->weight_data_500g_ok = LOADCELL6_DATA_OK;
            break;
        }
        case LOADCELL6_WEIGHT_1000G : 
        {
            cell_data->weight_coeff_1000g = 1000.0 / weight_val;
            cell_data->weight_data_1000g_ok = LOADCELL6_DATA_OK;
            break;
        }
        case LOADCELL6_WEIGHT_5000G : 
        {
            cell_data->weight_coeff_5000g = 5000.0 / weight_val;
            cell_data->weight_data_5000g_ok = LOADCELL6_DATA_OK;
            break;
        }
        case LOADCELL6_WEIGHT_10000G : 
        {
            cell_data->weight_coeff_10000g = 10000.0 / weight_val;
            cell_data->weight_data_10000g_ok = LOADCELL6_DATA_OK;
            break;
        }
        default : 
        {
            error_flag = LOADCELL6_ERROR;
            cell_data->weight_data_100g_ok = LOADCELL6_DATA_NO_DATA;
            cell_data->weight_data_200g_ok = LOADCELL6_DATA_NO_DATA;
            cell_data->weight_data_500g_ok = LOADCELL6_DATA_NO_DATA;
            cell_data->weight_data_1000g_ok = LOADCELL6_DATA_NO_DATA;
            cell_data->weight_data_5000g_ok = LOADCELL6_DATA_NO_DATA;
            cell_data->weight_data_10000g_ok = LOADCELL6_DATA_NO_DATA;
            break;
        }
    }

    return error_flag;
}

err_t loadcell6_get_weight ( loadcell6_t *ctx, loadcell6_data_t *cell_data, float *weight_g ) 
{
    uint32_t result;
    uint32_t sum_val;
    float average_val;
    float tare_val;
    float weight_val;
    err_t error_flag = LOADCELL6_OK;

    tare_val = cell_data->tare;

    sum_val = 0;

    for ( uint8_t n_cnt = 0; n_cnt < 100; n_cnt++ ) 
    {
        error_flag |= loadcell6_read_adc( ctx, &result );

        sum_val += result;

        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= 100.0;

    *weight_g = average_val - tare_val;

    if ( cell_data->weight_data_100g_ok == LOADCELL6_DATA_OK ) 
    {
        *weight_g *= cell_data->weight_coeff_100g;
    }
    
    if ( cell_data->weight_data_200g_ok == LOADCELL6_DATA_OK ) 
    {
        *weight_g *= cell_data->weight_coeff_200g;
    }
    
    if ( cell_data->weight_data_500g_ok == LOADCELL6_DATA_OK ) 
    {
        *weight_g *= cell_data->weight_coeff_500g;
    }
    
    if ( cell_data->weight_data_1000g_ok == LOADCELL6_DATA_OK ) 
    {
        *weight_g *= cell_data->weight_coeff_1000g;
    }
    
    if ( cell_data->weight_data_5000g_ok == LOADCELL6_DATA_OK ) 
    {
        *weight_g *= cell_data->weight_coeff_5000g;
    }
    
    if ( cell_data->weight_data_10000g_ok == LOADCELL6_DATA_OK ) 
    {
        *weight_g *= cell_data->weight_coeff_10000g;
    }

    if ( *weight_g < 0 ) 
    {
        *weight_g = LOADCELL6_WEIGHT_ZERO;
    }
    
    return error_flag;
}

static void dev_measure_delay ( void ) 
{
    Delay_1us( );
}

static void dev_reset_delay ( void ) 
{
    Delay_100ms( );
}

static void dev_sync_delay ( void ) 
{
    Delay_10ms( );
}

static void dev_config_delay ( void ) 
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END
