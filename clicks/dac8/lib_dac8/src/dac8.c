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

#include "dac8.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define DAC8_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dac8_i2c_write ( dac8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void dac8_i2c_read ( dac8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void dac8_spi_write ( dac8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void dac8_spi_read ( dac8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void dac8_ldac_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dac8_cfg_setup ( dac8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = DAC8_I2C_SLAVE_ADDR;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

DAC8_RETVAL dac8_init ( dac8_t *ctx, dac8_cfg_t *cfg, uint8_t master_mode )
{
    // Only in case it is necessary to check somewhere which communication is set
    cfg->sel = master_mode;
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == DAC8_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return DAC8_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = dac8_i2c_read;
        ctx->write_f = dac8_i2c_write;
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
        
        spi_cfg.default_write_data = DAC8_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  DAC8_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, DAC8_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f = dac8_spi_read;
        ctx->write_f = dac8_spi_write;
    }
   
    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->pwm, cfg->pwm );

    spi_master_deselect_device( ctx->chip_select );
    digital_out_low( &ctx->pwm );
    digital_out_high( &ctx->rst );

    return DAC8_OK;
}

void dac8_generic_write ( dac8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void dac8_generic_read ( dac8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

DAC8_RETVAL dac8_enable_sync ( dac8_t *ctx, uint8_t en_sync )
{
    uint16_t write_data;
    DAC8_RETVAL status;
    uint8_t tmp_buff[ 3 ];

    status = DAC8_ERROR;
    
    if ( en_sync == DAC8_SYNC_ENABLE )
    {
        write_data = DAC8_SYNC_ENABLE;
        tmp_buff[ 0 ] = ( uint8_t ) ( write_data >> 8 );
        tmp_buff[ 1 ] = ( uint8_t ) write_data;
        dac8_i2c_write( ctx, DAC8_REG_SYNC, tmp_buff, 2 );
        status = DAC8_SUCCESS;
    }
    else if ( en_sync == DAC8_SYNC_DISABLE )
    {
        write_data = DAC8_SYNC_DISABLE;
        tmp_buff[ 0 ] = ( uint8_t ) ( write_data >> 8 );
        tmp_buff[ 1 ] = ( uint8_t ) write_data;
        dac8_i2c_write( ctx, DAC8_REG_SYNC, tmp_buff, 2 );
        status = DAC8_SUCCESS;
    }
    return status;
}

DAC8_RETVAL dac8_set_config ( dac8_t *ctx, uint16_t en_ref_pwdwn, uint16_t en_dac_pwdwn )
{
    DAC8_RETVAL status;
    uint16_t tmp;
    uint8_t tmp_buff[ 3 ];
    
    en_ref_pwdwn &= DAC8_CONFIG_REF_PWDWN_BIT_MASK;
    en_dac_pwdwn &= DAC8_CONFIG_DAC_PWDWN_BIT_MASK;
    
    dac8_i2c_read( ctx, DAC8_REG_CONFIG, tmp_buff, 2 );
    tmp = tmp_buff[ 0 ];
    tmp <<= 8;
    tmp |= tmp_buff[ 1 ];

    if ( ( en_ref_pwdwn & en_dac_pwdwn ) > 
         ( DAC8_CONFIG_REF_PWDWN_BIT_MASK | DAC8_CONFIG_DAC_PWDWN_BIT_MASK ) )
    {
        status = DAC8_ERROR;
    }
    else
    {
        tmp |= ( uint16_t ) ( en_ref_pwdwn << 8 );
        tmp |= ( uint16_t ) en_dac_pwdwn;
        tmp_buff[ 0 ] = ( uint8_t ) ( tmp >> 8 );
        tmp_buff[ 1 ] = ( uint8_t ) tmp;

        dac8_i2c_write( ctx, DAC8_REG_CONFIG, tmp_buff, 2 );
        status = DAC8_SUCCESS;
    }

    return status;
}

DAC8_RETVAL dac8_set_gain ( dac8_t *ctx, uint16_t en_ref_div, uint16_t en_buff_gain )
{
    DAC8_RETVAL status;
    uint16_t tmp;
    uint8_t tmp_buff[ 3 ];

    en_ref_div &= DAC8_GAIN_REF_DIV_BIT_MASK;
    en_buff_gain &= DAC8_GAIN_BUFF_GAIN_BIT_MASK;

    dac8_i2c_read( ctx, DAC8_REG_GAIN, tmp_buff, 2 );
    tmp = tmp_buff[ 0 ];
    tmp <<= 8;
    tmp |= tmp_buff[ 1 ];

    if ( ( en_ref_div & en_buff_gain ) > 
         ( DAC8_GAIN_REF_DIV_BIT_MASK | DAC8_GAIN_BUFF_GAIN_BIT_MASK ) 
       )
    {
        status = DAC8_ERROR;
    }
    else
    {
        tmp |= ( uint16_t ) ( en_ref_div << 8 );
        tmp |= ( uint16_t ) en_buff_gain;
        tmp_buff[ 0 ] = ( uint8_t ) ( tmp >> 8 );
        tmp_buff[ 1 ] = ( uint8_t ) tmp;

        dac8_i2c_write( ctx, DAC8_REG_GAIN, tmp_buff, 2 );
        status = DAC8_SUCCESS;
    }

    return status;
}

void dac8_set_synchronously_load ( dac8_t *ctx )
{
    uint16_t write_data = DAC8_TRIGGER_LDAC;
    uint8_t tmp_buff[ 3 ];

    tmp_buff[ 0 ] = ( uint8_t ) ( write_data >> 8 );
    tmp_buff[ 1 ] = ( uint8_t ) write_data;
    dac8_i2c_write( ctx, DAC8_REG_TRIGGER, tmp_buff, 2 );
}

void dac8_soft_reset ( dac8_t *ctx )
{
    uint16_t write_data = DAC8_TRIGGER_SOFT_RESET;
    uint8_t tmp_buff[ 3 ];
    
    tmp_buff[ 0 ] = ( uint8_t ) ( write_data >> 8 );
    tmp_buff[ 1 ] = ( uint8_t ) write_data;
    dac8_i2c_write( ctx, DAC8_REG_TRIGGER, tmp_buff, 2 );
}

uint8_t dac8_get_ref_alarm ( dac8_t *ctx )
{
    uint8_t ref_alarm;
    uint16_t status_val;
    uint8_t tmp_buff[ 3 ];
    
    dac8_i2c_read( ctx, DAC8_REG_STATUS, tmp_buff, 2 );
    status_val = tmp_buff[ 0 ];
    status_val <<= 8;
    status_val |= tmp_buff[ 1 ];

    status_val &= DAC8_STATUS_REF_ALARM_BIT_MASK;
    
    ref_alarm = ( uint8_t ) status_val;
    
    return ref_alarm;
}

DAC8_RETVAL dac8_set_vref ( dac8_t *ctx, uint16_t vref_mv )
{
    DAC8_RETVAL status;
    float v_data;
    uint16_t vref_data;
    uint8_t tmp_buff[ 3 ];
    
    if ( vref_mv > 2500 )
    {
        status = DAC8_ERROR;
    }
    else
    {
        status = DAC8_SUCCESS;
        
        v_data = ( float ) vref_mv;
        v_data *= 1.6355;
        vref_data = ( uint16_t ) v_data;
        
        if ( vref_data > 4095 )
        {
            vref_data = 4095;
        }

        vref_data <<= 4;
        tmp_buff[ 0 ] = ( uint8_t ) ( vref_data >> 8 );
        tmp_buff[ 1 ] = ( uint8_t ) vref_data;
        dac8_i2c_write( ctx, DAC8_REG_DAC, tmp_buff, 2 );
    }

    return status;
}

// DAC8554 - SPI
void dac8_device_enable ( dac8_t *ctx, uint8_t en_sel )
{
    if ( en_sel == DAC8_DAC8554_ENABLE )
    {
        digital_out_low( &ctx->rst );
    }
    else
    {
        digital_out_high( &ctx->rst );
    }
}

void dac8_set_ldac ( dac8_t *ctx, uint8_t ldac_sel )
{
    if ( ldac_sel == DAC8_LDAC_LOW )
    {
        digital_out_low( &ctx->pwm );
    }
    else
    {
        digital_out_high( &ctx->pwm );
    }
}

void dac8_load_dac ( dac8_t *ctx )
{
    dac8_set_ldac( ctx, DAC8_LDAC_LOW );
    dac8_ldac_delay( );
    dac8_set_ldac( ctx, DAC8_LDAC_HIGH );
    dac8_ldac_delay( );
}

void dac8_generic_spi_write ( dac8_t *ctx, uint32_t tx_data )
{
    uint8_t tx_buf[ 3 ];

    tx_data &= DAC8_24_BIT_BIT_MASK;

    tx_buf[ 0 ] = ( uint8_t ) ( tx_data >> 16 );
    tx_buf[ 1 ] = ( uint8_t ) ( tx_data >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) tx_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );      
}

void dac8_device_config ( dac8_t *ctx, dac8_cfg_data_t cfg_data )
{
    uint8_t tx_buf[ 3 ];

    tx_buf[ 0 ]  = ( cfg_data.addr & DAC8_ADDR_BIT_MASK ) << 6;
    tx_buf[ 0 ] |= ( cfg_data.ctrl_upd_an_out & DAC8_CTRL_UPD_AN_OUT_BIT_MASK ) << 4;

    if ( cfg_data.ctrl_upd_an_out == DAC8_CTRL_UPD_AN_OUT_BROADCAST_UPDATE )
    {
        tx_buf[ 0 ] |= DAC8_DAC_SEL_ALL_CH_BROADCAST;
    }

    tx_buf[ 0 ] |= ( cfg_data.dac_sel & DAC8_DAC_SEL_CH_BIT_MASK ) << 1;
    tx_buf[ 0 ] |= cfg_data.pwr_mode & DAC8_PWR_UP_MODE_BIT_MASK;

    if ( cfg_data.pwr_mode != DAC8_PWR_MODE_POWER_UP )
    {
        tx_buf[ 1 ] = ( cfg_data.pwr_mode & DAC8_PWR_DOWN_MODE_BIT_MASK ) << 4;
        tx_buf[ 2 ] = ( uint8_t ) DAC8_DAC_OUT_DATA_MIN;
    }
    else
    {
        tx_buf[ 1 ] = ( uint8_t ) ( cfg_data.dac_val >> 8 );
        tx_buf[ 2 ] = ( uint8_t ) cfg_data.dac_val;
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );    
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dac8_i2c_write ( dac8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void dac8_i2c_read ( dac8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void dac8_spi_write ( dac8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
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

static void dac8_spi_read ( dac8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 256 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select ); 
}

static void dac8_ldac_delay ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

