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

#include "vcpmonitor3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define VCPMONITOR3_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void vcpmonitor3_i2c_write ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void vcpmonitor3_i2c_read ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void vcpmonitor3_spi_write ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void vcpmonitor3_spi_read ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void dev_get_twos_comp ( int32_t *raw, uint8_t length );

static void dev_time_to_apply ( );
// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void vcpmonitor3_cfg_setup ( vcpmonitor3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->io = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = VCPMONITOR3_I2C_ADR_L_L;

    cfg->spi_speed = 40000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = VCPMONITOR3_MASTER_SPI;
}

VCPMONITOR3_RETVAL vcpmonitor3_init ( vcpmonitor3_t *ctx, vcpmonitor3_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == VCPMONITOR3_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return VCPMONITOR3_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = vcpmonitor3_i2c_read;
        ctx->write_f = vcpmonitor3_i2c_write;
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
        
        spi_cfg.default_write_data = VCPMONITOR3_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  VCPMONITOR3_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, VCPMONITOR3_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f = vcpmonitor3_spi_read;
        ctx->write_f = vcpmonitor3_spi_write;
    }

    // Output pins 

    digital_out_init( &ctx->io, cfg->io );

    // Input pins

    digital_in_init( &ctx->alr, cfg->alr );


    if ( ctx->master_sel == VCPMONITOR3_MASTER_I2C )
    {
        spi_master_select_device( ctx->chip_select );
        digital_out_low( &ctx->io );
    }
    else
    {
        spi_master_deselect_device( ctx->chip_select );  
        digital_out_high( &ctx->io );
    }

    return VCPMONITOR3_OK;
}

void vcpmonitor3_default_cfg ( vcpmonitor3_t *ctx )
{
    uint8_t tmp_data;
    
    vcpmonitor3_set_op_mode( ctx, VCPMONITOR3_CLR );
    vcpmonitor3_set_op_mode( ctx, VCPMONITOR3_NORM_OP );
    vcpmonitor3_set_op_mode( ctx, VCPMONITOR3_CONT );
    tmp_data = 0x11;
    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_GPIOSTATCL, &tmp_data, 1 );
    tmp_data = 0x00;
    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_ALERTBCTL, &tmp_data, 1 );
}

void vcpmonitor3_generic_write ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void vcpmonitor3_generic_read ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

// Write Data To Page 0
void vcpmonitor3_wr_page_0 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *wr_data, uint8_t n_bytes )
{
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;
    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );
    vcpmonitor3_generic_write( ctx, reg, wr_data, n_bytes );
}

// Read Data From Page 0
void vcpmonitor3_rd_page_0 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *rd_data, uint8_t n_bytes )
{
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;
    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );
    vcpmonitor3_generic_read ( ctx, reg, rd_data, n_bytes );
}

// Write Data To Page 1
void vcpmonitor3_wr_page_1 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *wr_data, uint8_t n_bytes )
{
    uint8_t tmp_data = VCPMONITOR3_PAGE_1;
    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );
    vcpmonitor3_generic_write( ctx, reg, wr_data, n_bytes );
}

// Read Data From Page 1
void vcpmonitor3_rd_page_1 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *rd_data, uint8_t n_bytes )
{
    uint8_t tmp_data = VCPMONITOR3_PAGE_1;
    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );
    vcpmonitor3_generic_read ( ctx, reg, rd_data, n_bytes );
}

// Set Operation Mode Function
void vcpmonitor3_set_op_mode ( vcpmonitor3_t *ctx, uint8_t op_mode )
{
    uint8_t data_buf;
    uint8_t tmp_data;

    tmp_data = VCPMONITOR3_PAGE_0;
    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    switch ( op_mode )
    {
        case ( VCPMONITOR3_NORM_OP ):
        {
            tmp_data = VCPMONITOR3_NORM_OP;
            vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_OPCTL, &tmp_data, 1 );
            dev_time_to_apply( );
            break;
        }
        case ( VCPMONITOR3_SHDN ):
        {
            tmp_data = VCPMONITOR3_SHDN;
            vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_OPCTL, &tmp_data, 1 );
            dev_time_to_apply( );
            break;
        }
        case ( VCPMONITOR3_CLR ):
        {
            tmp_data = VCPMONITOR3_CLR;
            vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_OPCTL, &tmp_data, 1 );
            dev_time_to_apply( );
            break;
        }
        case ( VCPMONITOR3_SSHOT ):
        {
            vcpmonitor3_generic_read( ctx, VCPMONITOR3_REG_OPCTL, &data_buf, 1 );
            data_buf &= ~VCPMONITOR3_CONT;
            data_buf |= VCPMONITOR3_SSHOT;
            vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_OPCTL, &data_buf, 1 );
            dev_time_to_apply( );
            break;
        }
        case ( VCPMONITOR3_CONT ):
        {
            vcpmonitor3_generic_read( ctx, VCPMONITOR3_REG_OPCTL, &data_buf, 1 );
            data_buf &= ~VCPMONITOR3_SSHOT;
            data_buf |= VCPMONITOR3_CONT;
            vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_OPCTL, &data_buf, 1 );
            dev_time_to_apply( );
            break;
        }
        case ( VCPMONITOR3_RST ):
        {
            tmp_data = VCPMONITOR3_RST;
            vcpmonitor3_generic_write( ctx,  VCPMONITOR3_REG_OPCTL, &tmp_data, 1 );
            dev_time_to_apply( );
            break;
        }
        default :
        {
            break;
        }
    }
}

// Read Current in Amps
float vcpmonitor3_read_i ( vcpmonitor3_t *ctx )
{
    uint8_t data_buf[ 3 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_I, data_buf, 3 );

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 2 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 24 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_I;
    result /= 1000.0;

    return result;
}

// Read Power in Watts
float vcpmonitor3_read_p ( vcpmonitor3_t *ctx )
{
    uint8_t data_buf[ 3 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_P, data_buf, 3 );

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 2 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 24 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_P;
    result /= 1000.0;

    return result;
}

// Read Voltage in Volts
float vcpmonitor3_read_v ( vcpmonitor3_t *ctx )
{
    uint8_t data_buf[ 2 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_V, data_buf, 2 );

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 16 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_V;
    result /= 1000.0;

    return result;
}

// Read Temperature in degrees Centigrade
float vcpmonitor3_read_temp ( vcpmonitor3_t *ctx )
{
    uint8_t data_buf[ 2 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_TEMP, data_buf, 2 );

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 16 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_TEMP;
    result += VCPMONITOR3_OFFS_TEMP;

    return result;
}

// Read Voltage at DVCC in Volts
float vcpmonitor3_read_vcc ( vcpmonitor3_t *ctx )
{
    uint8_t data_buf[ 2 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_VDVCC, data_buf, 2 );

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 16 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_VDVCC;
    result /= 1000.0;

    return result;
}

// Read Charge in Coulombs
float vcpmonitor3_read_c ( vcpmonitor3_t *ctx, uint8_t accu_set1 )
{
    uint8_t data_buf[ 4 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data = VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    if ( accu_set1 )
    {
        vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_C1, data_buf, 4 );
    }
    else
    {
        vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_C2, data_buf, 4 );
    }

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 2 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 3 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 32 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_C1;

    return result;
}

// Read Energy Joules
float vcpmonitor3_read_e ( vcpmonitor3_t *ctx, uint8_t accu_set1 )
{
    uint8_t data_buf[ 4 ];
    int32_t tmp_val;
    float result;
    uint8_t tmp_data =  VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    if ( accu_set1 )
    {
        vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_E1, data_buf, 4 );
    }
    else
    {
        vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_E2, data_buf, 4 );
    }

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 2 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 3 ];
    
    if ( data_buf[ 0 ] & 0x80 )
    {
        dev_get_twos_comp( &tmp_val, 32 );
    }

    result = ( float ) tmp_val * VCPMONITOR3_LSB_E1;

    return result;
}

// Read Time in Seconds
float vcpmonitor3_read_tb ( vcpmonitor3_t *ctx, uint8_t accu_set1 )
{
    uint8_t data_buf[ 4 ];
    uint32_t tmp_val;
    float result;
    uint8_t tmp_data =  VCPMONITOR3_PAGE_0;

    vcpmonitor3_generic_write( ctx, VCPMONITOR3_REG_PGCTL, &tmp_data, 1 );

    if ( accu_set1 )
    {
        vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_TB1, data_buf, 4 );
    }
    else
    {
        vcpmonitor3_generic_read( ctx, VCPMONITOR3_VAL_TB2, data_buf, 4 );
    }

    tmp_val = data_buf[ 0 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 1 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 2 ];
    tmp_val <<= 8;
    tmp_val |= data_buf[ 3 ];

    result = ( float ) tmp_val * VCPMONITOR3_LSB_TB1;

    return result;
}

// Check interrupt
uint8_t vcpmonitor3_get_int ( vcpmonitor3_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void vcpmonitor3_i2c_write ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 512 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );        
}

static void vcpmonitor3_i2c_read ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void vcpmonitor3_spi_write ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 512 ];
    uint8_t cnt;

    tx_buf[ 0 ] = VCPMONITOR3_SPI_WR_CMD;
    tx_buf[ 1 ] = reg;
    for ( cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 2 ] = data_buf[ cnt ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len + 2 );
    spi_master_deselect_device( ctx->chip_select );        
}

static void vcpmonitor3_spi_read ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = VCPMONITOR3_SPI_RD_CMD;
    tx_buf[ 1 ] = reg;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 2, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );      
}

static void dev_get_twos_comp ( int32_t *raw, uint8_t length )
{
    if ( *raw & ( ( uint32_t ) 1 << ( length - 1 ) ) )
    {
        *raw -= ( uint32_t ) 1 << length;
    }
}

static void dev_time_to_apply ( )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

