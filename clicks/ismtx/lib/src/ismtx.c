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
 * @file ismtx.c
 * @brief ISM TX Click Driver.
 */

#include "ismtx.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Library macros.
 * @details Library help macros.
 */
#define CRYSTAL_FREQ        16.0
#define CONST_MOD_FREQ      65536.0
#define MAX_FREQ            950000000
#define MIN_FREQ            250000000
#define MAX_BAUD            200000
#define MIN_BAUD            195
#define MIN_MAN_DATA_RATE   1
#define MAX_MAN_DATA_RATE   50
#define BASE_MAN_DATA_RATE  500
#define SPI_DELAY_VALUE     2
#define MEGA                1000000
#define MATRIX_CFG_LEN      29
#define CFG_MACRO_INDEX     0
#define REG_ADR_INDEX       1
#define MAX_VALUE_INDEX     2
#define OFFSET_INDEX        3
#define MASK_INDEX          4

/**
 * @brief ISM TX configuration data.
 * @details Configuration parameteres(cfg_macro/reg_adr/max_value/offset/mask).
 */
const uint8_t CFG_MATRIX[ 29 ][ 5 ] =
{
    { ISMTX_CFG_XO_CLK_DELAY,       ISMTX_REG_CFG1, 0x3,    6, 0x3F },      
    { ISMTX_CFG_XO_CLK_DIV,         ISMTX_REG_CFG1, 0x3,    3, 0xCF },      
    { ISMTX_CFG_FSK_SHAPE,          ISMTX_REG_CFG1, 0x1,    2, 0xFB },      
    { ISMTX_CFG_SYNC,               ISMTX_REG_CFG1, 0x1,    1, 0xFD },      
    { ISMTX_CFG_MODE,               ISMTX_REG_CFG1, 0x1,    0, 0xFE },      
    { ISMTX_CFG_CLKOUT_DELAY,       ISMTX_REG_CFG2, 0x3,    6, 0x3F },      
    { ISMTX_CFG_BCLK_POSTDIV,       ISMTX_REG_CFG2, 0x7,    0, 0xF8 },      
    { ISMTX_CFG_BCLK_PREDIV,        ISMTX_REG_CFG3, 0xFF,   0, 0x00 },     
    { ISMTX_CFG_PWDN_MODE,          ISMTX_REG_CFG4, 0x3,    0, 0xFC },      
    { ISMTX_CFG_PA_MODE,            ISMTX_REG_SHDN, 0x1,    0, 0xFE },      
    { ISMTX_CFG_PA_DRIVERS,         ISMTX_REG_PA1,  0x7,    0, 0xF8 },      
    { ISMTX_CFG_PA_SHUNT,           ISMTX_REG_PA2,  0x1F,   0, 0xE0 },     
    { ISMTX_CFG_PA_OFFSET_CUR,      ISMTX_REG_PLL1, 0x3,    6, 0x3F },      
    { ISMTX_CFG_PA_PLL_N,           ISMTX_REG_PLL1, 0x1,    5, 0xDF },      
    { ISMTX_CFG_PA_LCVCO_DIV,       ISMTX_REG_PLL1, 0x3,    1, 0xF9 },      
    { ISMTX_CFG_PA_LCVCO_MODE,      ISMTX_REG_PLL1, 0x1,    0, 0xFE },      
    { ISMTX_CFG_CP_CURRENT,         ISMTX_REG_PLL2, 0x3,    0, 0xFC },      
    { ISMTX_CFG_SPITXEN1,           ISMTX_REG_CFG6, 0x1,    1, 0xFD },      
    { ISMTX_CFG_FOURWIRE1,          ISMTX_REG_CFG6, 0x1,    0, 0xFE },      
    { ISMTX_CFG_SPITXEN2,           ISMTX_REG_CFG7, 0x1,    1, 0xFD },      
    { ISMTX_CFG_FOURWIRE2,          ISMTX_REG_CFG7, 0x1,    0, 0xFE },      
    { ISMTX_CFG_DELTAF,             ISMTX_REG_PLL6, 0x7F,   0, 0x8F },     
    { ISMTX_CFG_DELTAF_SHAPE,       ISMTX_REG_PLL7, 0xF,    0, 0xF0 },      
    { ISMTX_CFG_TSTEP,              ISMTX_REG_CFG5, 0x3F,   0, 0xC0 },     
    { ISMTX_CFG_EN_LDO,             ISMTX_REG_SHDN, 0x1,    2, 0xFB },      
    { ISMTX_CFG_DIS_LDO_FUNC_EN,    ISMTX_REG_SHDN, 0x1,    1, 0xFD },      
    { ISMTX_CFG_PLL_LOOP_BAND,      ISMTX_REG_PLL1, 0x3,    3, 0xE7 },      
    { ISMTX_CFG_LCVCO_FAST_START,   ISMTX_REG_PLL2, 0x1,    6, 0xBF },      
    { ISMTX_CFG_LCVCO_PWR,          ISMTX_REG_PLL2, 0x1,    7, 0x7F }
};

/**
 * @brief Static cfg value.
 * @details Static configuration value for initialization.
 */
static uint32_t spi_speed;       
static spi_master_mode_t spi_mode;        
static spi_master_chip_select_polarity_t cs_polarity;     

/**
 * @brief Manchester initialization.
 * @details This function initializes device to transmit data.
 * Closes spi comunication and initializes GPIO(mosi).
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @return Nothing.
 */
static void ismtx_manchester_init ( ismtx_t *ctx );

/**
 * @brief SPI initialization.
 * @details This function initializes device to spi communication.
 * @param[in] ctx : Click context object.
 * See #ismtx_t object definition for detailed explanation.
 * @return Nothing.
 */
static void ismtx_spi_init ( ismtx_t *ctx );

void ismtx_cfg_setup ( ismtx_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    spi_speed = 100000;
    spi_mode = SPI_MASTER_MODE_0;
    cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t ismtx_init ( ismtx_t *ctx, ismtx_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );
    
    
    ctx->tx_data = cfg->mosi;
    ctx->spi_config = spi_cfg;

    return SPI_MASTER_SUCCESS;
}

err_t ismtx_default_cfg ( ismtx_t *ctx )
{
    ismtx_generic_write( ctx, ISMTX_REG_CFG6, 0x03 );
    if ( ISM_TX_MODULATION_FSK == ctx->modulation )
    {
        ismtx_generic_write( ctx, ISMTX_REG_CFG1, 0x95 );
        ismtx_generic_write( ctx, ISMTX_REG_PA1, 0x90 );
        ismtx_set_frequency( ctx, 433920000 );
        ismtx_set_cfg( ctx, ISMTX_CFG_FSK_SHAPE, ISMTX_FSK_SHAPE_ENABLED );
        ismtx_adjust_frequency_deviation( ctx, 40000 );
    }   
    else if ( ISM_TX_MODULATION_ASK == ctx->modulation )
    {
        ismtx_generic_write( ctx, ISMTX_REG_CFG1, 0x90 );
        ismtx_generic_write( ctx, ISMTX_REG_PA1, 0x87 );
        ismtx_set_frequency( ctx, 433920000 );
    }
    else
    {
        return ISMTX_ERROR;
    }
    
    ismtx_generic_write( ctx, ISMTX_REG_CFG6, 0x00 );
    
    return ISMTX_OK;
}

err_t ismtx_generic_write ( ismtx_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg & 0x7F;
    tx_buf[ 1 ] = data_in;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t ismtx_generic_read ( ismtx_t *ctx, uint8_t reg, uint8_t *data_out )
{
    reg |= 0x80;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void ismtx_soft_reset ( ismtx_t *ctx )
{
    ismtx_generic_write( ctx, ISMTX_REG_CFG8, 0x01 );
    Delay_100ms(  );
    ismtx_generic_write( ctx, ISMTX_REG_CFG8, 0x00 );
    Delay_1sec(  );
}

err_t ismtx_set_cfg ( ismtx_t *ctx, uint8_t cfg_macro, uint8_t cfg_value )
{
    for ( uint8_t cnt = 0; cnt < MATRIX_CFG_LEN; cnt++ )
    {
        if ( CFG_MATRIX[ cnt ][ CFG_MACRO_INDEX ] == cfg_macro )
        {
            if ( CFG_MATRIX[ cnt ][ MAX_VALUE_INDEX ] < cfg_value )
            {
                return ISMTX_PARAMETER_ERROR;
            }

            uint8_t temp_data = 0;
            
            ismtx_generic_read( ctx, CFG_MATRIX[ cnt ][ REG_ADR_INDEX ], &temp_data );
            temp_data &= CFG_MATRIX[ cnt ][ MASK_INDEX ];
            temp_data |= ( cfg_value << CFG_MATRIX[ cnt ][ OFFSET_INDEX ] );
            ismtx_generic_write( ctx, CFG_MATRIX[ cnt ][ REG_ADR_INDEX ], temp_data );
            
            return ISMTX_OK;
        }
    }
    return ISMTX_PARAMETER_ERROR;
}

err_t ismtx_get_cfg ( ismtx_t *ctx, uint8_t cfg_macro, uint8_t *cfg_value )
{
    for ( uint8_t cnt = 0; cnt < MATRIX_CFG_LEN; cnt++ )
    {
        if ( CFG_MATRIX[ cnt ][ CFG_MACRO_INDEX ] == cfg_macro )
        {
            ismtx_generic_read( ctx, CFG_MATRIX[ cnt ][ REG_ADR_INDEX ], cfg_value );
            uint8_t mask = ~CFG_MATRIX[ cnt ][ MASK_INDEX ];
            *cfg_value &= mask;
            *cfg_value >>=  CFG_MATRIX[ cnt ][ OFFSET_INDEX ];
            
            return ISMTX_OK;
        }
    }
    return ISMTX_PARAMETER_ERROR;
}

err_t ismtx_set_frequency ( ismtx_t *ctx, uint32_t freq )
{
    float temp_freq;
    uint32_t fin_freq;

    if ( ( freq > MAX_FREQ ) || ( freq < MIN_FREQ ) )
    {
        return ISMTX_PARAMETER_ERROR;
    }

    temp_freq = ( float )freq / MEGA;
    temp_freq *= CONST_MOD_FREQ;
    temp_freq /= CRYSTAL_FREQ;
    fin_freq = ( uint32_t )temp_freq;

    ismtx_generic_write( ctx, ISMTX_REG_PLL3, ( fin_freq >> 16 ) );
    ismtx_generic_write( ctx, ISMTX_REG_PLL4, ( fin_freq >> 8 ) );
    ismtx_generic_write( ctx, ISMTX_REG_PLL5, fin_freq );

    return ISMTX_OK;
}

uint32_t get_frequency ( ismtx_t *ctx )
{
    uint32_t return_freq;
    float temp_freq;
    uint8_t temp_data;

    ismtx_generic_read( ctx, ISMTX_REG_PLL3, &temp_data );
    return_freq = temp_data;
    return_freq <<= 8;
    ismtx_generic_read( ctx, ISMTX_REG_PLL4, &temp_data );
    return_freq |= temp_data;
    return_freq <<= 8;
    ismtx_generic_read( ctx, ISMTX_REG_PLL5, &temp_data );
    return_freq |= temp_data;

    temp_freq = ( float )return_freq / CONST_MOD_FREQ;
    temp_freq *= CRYSTAL_FREQ;
    return_freq = ( uint32_t )( temp_freq * MEGA );

    return return_freq;
}

err_t ismtx_adjust_frequency_deviation ( ismtx_t *ctx, uint32_t deviation_freq )
{
    float temp;
    uint32_t frequency;
    uint8_t fskshape;

    frequency = get_frequency( ctx );
    frequency -= deviation_freq;
    ismtx_set_frequency( ctx, frequency );

    ismtx_get_cfg( ctx, ISMTX_CFG_FSK_SHAPE, &fskshape );

    if ( ISMTX_FSK_SHAPE_DISABLED == fskshape )
    {
        temp = (float)deviation_freq / 1000000;
        temp *= 8192;
        temp /= CRYSTAL_FREQ;
        temp *= 2;
        return ismtx_set_cfg( ctx, ISMTX_CFG_DELTAF, ( uint8_t )ceil( temp ) );
    }
    else
    {
        temp = (float)deviation_freq / 1000000;
        temp *= 819.2;
        temp /= CRYSTAL_FREQ;
        temp *= 2;
        
        return ismtx_set_cfg( ctx, ISMTX_CFG_DELTAF_SHAPE, ( uint8_t )ceil( temp ) );
    }
}

err_t ismtx_adjust_manchester_bitrate ( ismtx_t *ctx, uint8_t baud )
{
    uint8_t prediv;
    err_t error_flag;

    if ( ( baud > MAX_BAUD) || ( baud < MIN_BAUD ) )
    {
        return ISMTX_PARAMETER_ERROR;
    }

    prediv = 3;

    if ( baud < 12500 )
    {
        error_flag = ismtx_set_cfg( ctx, ISMTX_CFG_BCLK_POSTDIV, ISMTX_BCLK_POSTDIV_5 );
        prediv = ( uint8_t )( ( 50000 / baud ) - 1 );
    }
    else if ( baud < 25000.0 )
    {
        error_flag = ismtx_set_cfg( ctx, ISMTX_CFG_BCLK_POSTDIV, ISMTX_BCLK_POSTDIV_4 );
        prediv = ( uint8_t )( ( 100000 / baud ) - 1 );
    }
    else if ( baud < 50000 )
    {
        error_flag = ismtx_set_cfg( ctx, ISMTX_CFG_BCLK_POSTDIV, ISMTX_BCLK_POSTDIV_3 );
        prediv = ( uint8_t )( ( 200000 / baud ) - 1 );
    }
    else if ( baud < 100000 )
    {
        error_flag = ismtx_set_cfg( ctx, ISMTX_CFG_BCLK_POSTDIV, ISMTX_BCLK_POSTDIV_2 );
        prediv = ( uint8_t )( ( 400000 / baud ) - 1 );
    }
    else
    {
        error_flag = ismtx_set_cfg( ctx, ISMTX_CFG_BCLK_POSTDIV, ISMTX_BCLK_POSTDIV_1 );
        prediv = ( uint8_t )( ( 800000 / baud ) - 1 );
    }

    if ( prediv < 3 )
    {
        return ISMTX_PARAMETER_ERROR;
    }
    
    return ismtx_set_cfg( ctx, ISMTX_CFG_BCLK_PREDIV, prediv ) | error_flag;
}

err_t ismtx_transmit_raw_data ( ismtx_t *ctx, uint8_t *tx_data, uint8_t tx_len )
{
    uint8_t bits_array[ 512 ] = { 0 };
    uint8_t manchester_array[ 1024 ] = { 0 };
    uint16_t cnt_1;
    uint16_t cnt_2;
    uint16_t array_len;
    uint8_t temp_data;
    
    if ( tx_len > 64 )
    {
        return ISMTX_PARAMETER_ERROR;
    }

    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    temp_data = 0x0A;
    spi_master_write( &ctx->spi, &temp_data, 1 );
    temp_data = 0x01;
    Delay_22us();
    spi_master_write( &ctx->spi, &temp_data, 1 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms();
    spi_master_select_device( ctx->chip_select );
    Delay_1us( );
    temp_data = 0x10;
    spi_master_write( &ctx->spi, &temp_data, 1 );
    Delay_22us();
    temp_data = 0x03;
    spi_master_write( &ctx->spi, &temp_data, 1 );
    Delay_22us();

    for ( cnt_1 = 0; cnt_1 < tx_len; cnt_1++ )
    {
        for ( cnt_2 = 0; cnt_2 < 8; cnt_2++ )
        {
            if ( ( ( *tx_data >> 7 - cnt_2  ) & 1 ) != 0 )
            {
                bits_array[ cnt_1 * 8 + cnt_2 ] = 1;
            }
            else
            {
                bits_array[ cnt_1 * 8 + cnt_2 ] = 0;
            }
        }
        tx_data++;
    }

    array_len = tx_len * 8;

    for ( cnt_1 = 0; cnt_1 < array_len; cnt_1++ )
    {
        if ( 0 == bits_array[ cnt_1 ]  )
        {
            manchester_array[2 * cnt_1] = 1;
            manchester_array[2 * cnt_1 + 1] = 0;
        }
        else
        {
            manchester_array[2 * cnt_1] = 0;
            manchester_array[2 * cnt_1 + 1] = 1;
        }
    }

    cnt_1 = 0;
    array_len = tx_len * 8 * 2;

    ismtx_manchester_init( ctx );
    
    digital_out_low( &ctx->mosi );
    Delay_50us( );
    Delay_50us( );
    digital_out_high( &ctx->mosi );
    Delay_10us( );
    Delay_10us( );
    Delay_10us( );
    Delay_80us( );
    Delay_80us( );
    Delay_80us( );
    Delay_80us( );
    digital_out_low( &ctx->mosi );
    Delay_10us( );

    for ( cnt_1 = 0; cnt_1 < array_len; cnt_1++ )
    {
        if ( 0 == manchester_array[ cnt_1 ] )
        {
            digital_out_low( &ctx->mosi );
        }
        else
        {
            digital_out_high( &ctx->mosi );
        }

        Delay_50us( );
        Delay_50us( );
        Delay_50us( );
        Delay_50us( );
    }
    
    digital_out_low( &ctx->mosi );
    ismtx_spi_init( ctx );
    
    spi_master_deselect_device( ctx->chip_select );
    
    return ISMTX_OK;
}

err_t ismtx_transmit_data ( ismtx_t *ctx, uint8_t preamble_byte, uint8_t *tx_data, uint8_t tx_data_len )
{
    uint8_t transmit_buffer[ 64 ] = { 0 };

    if ( tx_data_len > 62 )
    {
        return ISMTX_PARAMETER_ERROR;
    }

    transmit_buffer[ 0 ] = preamble_byte;
    transmit_buffer[ 1 ] = tx_data_len;
    strcat( &transmit_buffer[ 2 ], tx_data );

    ismtx_transmit_raw_data( ctx, transmit_buffer, tx_data_len + 2 );
    
    return ISMTX_OK;
}

static void ismtx_manchester_init ( ismtx_t *ctx )
{
    spi_master_close( &ctx->spi );
    digital_out_init( &ctx->cs, ctx->chip_select );
    digital_out_init( &ctx->mosi, ctx->tx_data );
}

static void ismtx_spi_init ( ismtx_t *ctx )
{
    spi_master_open( &ctx->spi, &ctx->spi_config );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_set_mode( &ctx->spi, spi_mode );
    spi_master_set_speed( &ctx->spi, spi_speed );
    spi_master_set_chip_select_polarity( cs_polarity );
    spi_master_deselect_device( ctx->chip_select );
}

// ------------------------------------------------------------------------- END
