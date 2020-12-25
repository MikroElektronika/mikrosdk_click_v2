/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "lps22hb.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define LPS22HB_DUMMY             0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void lps22hb_i2c_write ( lps22hb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void lps22hb_i2c_read ( lps22hb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void lps22hb_spi_write ( lps22hb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void lps22hb_spi_read ( lps22hb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void dev_comm_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lps22hb_cfg_setup ( lps22hb_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin     = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = LPS22HB_I2C_ADDRESS_0;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel         = LPS22HB_MASTER_I2C;
}

LPS22HB_RETVAL lps22hb_init ( lps22hb_t *ctx, lps22hb_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == LPS22HB_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return LPS22HB_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f  = lps22hb_i2c_read;
        ctx->write_f = lps22hb_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        spi_cfg.default_write_data = LPS22HB_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  LPS22HB_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, LPS22HB_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f  = lps22hb_spi_read;
        ctx->write_f = lps22hb_spi_write;
    }

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return LPS22HB_OK;
}

void lps22hb_default_cfg ( lps22hb_t *ctx, lps22hb_cfg_t *cfg  )
{
    uint8_t tmp;
    uint8_t rmp;
    
    ctx->master_sel = cfg->sel;
    
    tmp = LPS22HB_CTRL_I2C;
    rmp = LPS22HB_CTRL_SPI;
    
    if ( ctx->master_sel == LPS22HB_MASTER_I2C )
    {
        lps22hb_generic_write( ctx, LPS22HB_CTRL_REG_R2, &tmp, 1 );
        lps22hb_start_configuration( ctx );
        dev_comm_delay( );
    }
    else
    {
        lps22hb_generic_write( ctx, LPS22HB_CTRL_REG_R2, &rmp, 1 );
        lps22hb_start_configuration( ctx );
        dev_comm_delay( );
    }
}

void lps22hb_generic_write ( lps22hb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void lps22hb_generic_read ( lps22hb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void lps22hb_soft_reset ( lps22hb_t *ctx )
{
    uint8_t tmp;
    uint8_t rx_buf[ 1 ];

    lps22hb_generic_read( ctx, LPS22HB_CTRL_REG_R2, rx_buf, 1 );
    tmp = rx_buf[ 0 ];
    dev_comm_delay( );

    tmp |= LPS22HB_MASK_DATA_RESET;

    lps22hb_generic_write( ctx, LPS22HB_CTRL_REG_R2, &tmp, 1 );
}

void lps22hb_start_configuration ( lps22hb_t *ctx )
{
    uint8_t tmp;
    uint8_t rx_buf[ 1 ];

    lps22hb_generic_read( ctx, LPS22HB_REG_RES_CONF, rx_buf, 1 );
    tmp  = rx_buf[ 0 ];
    dev_comm_delay( );
    tmp &= ~LPS22HB_RES_CONF_LOW_CURRENT_MODE;
    tmp |= LPS22HB_RES_CONF_LOW_CURRENT_MODE;
    
    lps22hb_generic_write( ctx, LPS22HB_REG_RES_CONF, &tmp, 1 );
    dev_comm_delay( );
    
    lps22hb_generic_read( ctx, LPS22HB_CTRL_REG_R1, rx_buf, 1 );
    tmp  = rx_buf[ 0 ];
    dev_comm_delay( );
    tmp &= ~LPS22HB_MASK_REG1_ODR;

    tmp |= LPS22HB_MASK_DATA_ODR;
    
    tmp &= ~LPS22HB_MASK_REG1_BDU;
    tmp |= LPS22HB_MASK_REG1_BDU;
    
    lps22hb_generic_write( ctx, LPS22HB_CTRL_REG_R1, &tmp, 1 );
}

void lps22hb_update_reg ( lps22hb_t *ctx, uint8_t reg_adr, uint8_t reg_val )
{
    uint8_t tmp;

    lps22hb_generic_read( ctx, reg_adr, &tmp, 1 );

    tmp |= reg_val;

    lps22hb_generic_write( ctx, reg_adr, &tmp, 1 );
}

float lps22hb_get_pressure ( lps22hb_t *ctx )
{
    uint8_t pres_xl;
    uint8_t pres_l;
    uint8_t pres_h;
    uint32_t temp_val;
    float ret_val;

    lps22hb_generic_read( ctx, LPS22HB_REG_PRESS_OUT_XL, &pres_xl, 1 );
    lps22hb_generic_read( ctx, LPS22HB_REG_PRESS_OUT_L, &pres_l, 1 );
    lps22hb_generic_read( ctx, LPS22HB_REG_PRESS_OUT_H, &pres_h, 1 );
    
    temp_val   = pres_h;
    temp_val <<= 8;
    temp_val  |= pres_l;
    temp_val <<= 8;
    temp_val  |= pres_xl;
     
    ret_val  = ( float ) temp_val;
    ret_val /= LPS22HB_DEV_RES_PRES;
     
    return ret_val;
}

float lps22hb_get_temp ( lps22hb_t *ctx )
{
    uint8_t temp_l;
    uint8_t temp_h;
    uint16_t tmp_val;
    float ret_val;

    lps22hb_generic_read( ctx, LPS22HB_REG_TEMP_OUT_L, &temp_l, 1 );
    lps22hb_generic_read( ctx, LPS22HB_REG_TEMP_OUT_H, &temp_h, 1 );

    tmp_val   = temp_h;
    tmp_val <<= 8;
    tmp_val  |= temp_l;

    ret_val   = ( float )tmp_val;
    ret_val  /= LPS22HB_DEV_RES_TEMP;

    return ret_val;
}

void lps22hb_set_fifo_mode ( lps22hb_t *ctx, uint8_t mode_sel, uint8_t wm_lvl )
{
    uint8_t tmp;

    lps22hb_generic_read( ctx, LPS22HB_CTRL_REG_FIFO, &tmp, 1 );

    tmp |= mode_sel;
    tmp |= wm_lvl;

    lps22hb_generic_write( ctx, LPS22HB_CTRL_REG_FIFO, &tmp, 1 );
}

uint8_t lps22hb_check_int ( lps22hb_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void lps22hb_i2c_write ( lps22hb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }

    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );        
}

static void lps22hb_i2c_read ( lps22hb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void lps22hb_spi_write ( lps22hb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );         
}

static void lps22hb_spi_read ( lps22hb_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg | 0x80;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );  
}

static void dev_comm_delay ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

