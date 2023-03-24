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

#include "c3dhall7.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C3DHALL7_DUMMY 0

// ------------------------------------------------------------------ VARIABLES

#ifdef   C3DHALL7_DRV_I2C
static uint8_t slave_address;
#endif

static uint8_t communication;
static uint8_t I2C_COMMUNICATION = 0x00;
static uint8_t SPI_COMMUNICATION = 0x01;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void c3dhall7_i2c_write ( c3dhall7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c3dhall7_i2c_read ( c3dhall7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c3dhall7_spi_write ( c3dhall7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c3dhall7_spi_read ( c3dhall7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static int16_t package_data_16 ( uint8_t *data_in, uint8_t c_ind );

static uint16_t package_data_u16 ( uint8_t *data_in, uint8_t c_ind );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c3dhall7_cfg_setup ( c3dhall7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->it2   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->it1 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = C3DHALL7_DEVICE_SLAVE_ADDR_VCC;
    cfg->spi_speed = 100000; 
    
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;    
    
    cfg->sel = C3DHALL7_MASTER_I2C;
}

C3DHALL7_RETVAL c3dhall7_init ( c3dhall7_t *ctx, c3dhall7_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == C3DHALL7_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return C3DHALL7_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
        i2c_master_set_timeout( &ctx->i2c, 0 );
        
        digital_out_init( &ctx->cs, cfg->cs );
        digital_out_high( &ctx->cs );

        ctx->read_f = c3dhall7_i2c_read;
        ctx->write_f = c3dhall7_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        //spi_cfg.mode        = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;

        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;  

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  C3DHALL7_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, C3DHALL7_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f = c3dhall7_spi_read;
        ctx->write_f = c3dhall7_spi_write;

    }
    
    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->it2, cfg->it2 );
    digital_in_init( &ctx->it1, cfg->it1 );

    digital_out_high( &ctx->rst );

    return C3DHALL7_OK;
}


void c3dhall7_default_cfg ( c3dhall7_t *ctx )
{
    c3dhall7_configuration( ctx, C3DHALL7_REG_SENSOR_SETTINGS, 
C3DHALL7_CTRL_MODE_CONTINUOUS_100Hz | C3DHALL7_CTRL_SDR_LOW_NOISE_DRIVE |
C3DHALL7_CTRL_SMR_HIGH_SENSITIVITY );
                                                          
    c3dhall7_configuration( ctx, C3DHALL7_REG_INTERRUPT_SETTINGS,  
                                 C3DHALL7_INT_DRDY_ENBALE | 
                                 C3DHALL7_INT_SW_X1_ENABLE |
                                 C3DHALL7_INT_SW_X2_ENABLE | 
                                 C3DHALL7_INT_SW_Y1_ENABLE |
                                 C3DHALL7_INT_SW_Y2_ENABLE | 
                                 C3DHALL7_INT_SW_Z1_ENABLE |
                                 C3DHALL7_INT_SW_Z2_ENABLE  | 
                                 C3DHALL7_INT_ERROR_X_Y_ENABLE |
                                 C3DHALL7_INT_ERROR_ADC_ENABLE | 
                                 C3DHALL7_INT_INTERRUPT_ENABLE |
                                 C3DHALL7_INT_ODINT_ENABLE );

}

void c3dhall7_generic_write ( c3dhall7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void c3dhall7_generic_read ( c3dhall7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void c3dhall7_device_reset ( c3dhall7_t *ctx )
{
     digital_out_low( &ctx->rst );
     Delay_100ms( );
     Delay_100ms( );
     Delay_100ms( );
     digital_out_high( &ctx->rst );
     Delay_1sec( );
}

void c3dhall7_get_axis_data( c3dhall7_t *ctx, c3dhall7_axis_t *axis)
{
    uint8_t raw_data[ 8 ];
    
    c3dhall7_generic_read( ctx, C3DHALL7_REG_ST_AXIS_X_Y_Z, raw_data, 8 );
    raw_data[ 0 ] &= 0x03;

    axis->status.data_overrun = ( raw_data[ 0 ] & 0x02 ) >> 1;
    axis->status.err_adc      = ( raw_data[ 0 ] & 0x01 );
    axis->status.err_axis_xy  = ( raw_data[ 1 ] & 0x80 ) >> 7;
    axis->status.sw_axis_z2   = ( raw_data[ 1 ] & 0x40 ) >> 6;
    axis->status.sw_axis_z1   = ( raw_data[ 1 ] & 0x20 ) >> 5;
    axis->status.sw_axis_y2   = ( raw_data[ 1 ] & 0x10 ) >> 4;
    axis->status.sw_axis_y1   = ( raw_data[ 1 ] & 0x08 ) >> 3;
    axis->status.sw_axis_x2   = ( raw_data[ 1 ] & 0x04 ) >> 2;
    axis->status.sw_axis_x1   = ( raw_data[ 1 ] & 0x02 ) >> 1;
    axis->status.drdy         = ( raw_data[ 1 ] & 0x01 );
    
    if ( axis->status.drdy == 0x01 )
    {
        axis->x = package_data_16( raw_data, 2 );
        axis->y = package_data_16( raw_data, 4 );
        axis->z = package_data_16( raw_data, 6 );
    }
}

void c3dhall7_software_reset ( c3dhall7_t *ctx )
{
    uint8_t reset;
    
    reset = 0x01;
    c3dhall7_generic_write( ctx, C3DHALL7_REG_SOFTWARE_RESET, &reset, 1 );
    Delay_100ms();
    reset = 0x00;
    c3dhall7_generic_write( ctx, C3DHALL7_REG_SOFTWARE_RESET, &reset, 1 );
    Delay_1sec();
}

void c3dhall7_configuration ( c3dhall7_t *ctx, uint8_t reg, uint16_t data_in)
{
    uint8_t write_reg[ 2 ];
    
    if ( reg == C3DHALL7_REG_SENSOR_SETTINGS )
    {
        write_reg[ 0 ] = data_in & 0x00FF;
        c3dhall7_generic_write( ctx, reg, write_reg, 1 );
    }
    else
    {
       write_reg[ 0 ] = data_in >> 8;
       write_reg[ 1 ] = data_in & 0x00FF;
       c3dhall7_generic_write( ctx, reg, write_reg, 2 );
    }
}

void c3dhall7_device_info ( c3dhall7_t *ctx, c3dhall7_dev_info_t *info )
{
    uint8_t read_data[ 2 ];
    
    c3dhall7_generic_read( ctx, C3DHALL7_REG_DEVICE_ID, read_data, 2 );
    
    info->company_id = read_data[ 0 ];
    info->device_id = read_data[ 1 ];
}

void c3dhall7_get_status ( c3dhall7_t *ctx, c3dhall7_status_t *status )
{
    uint8_t read_status[ 2 ];

   c3dhall7_generic_read( ctx, C3DHALL7_REG_STATUS, read_status, 2 );
    
    read_status[ 0 ] &= 0x03;
    
    status->data_overrun = ( read_status[ 0 ] & 0x02 ) >> 1;
    status->err_adc      = ( read_status[ 0 ] & 0x01 );
    status->err_axis_xy  = ( read_status[ 1 ] & 0x80 ) >> 7;
    status->sw_axis_z2   = ( read_status[ 1 ] & 0x40 ) >> 6;
    status->sw_axis_z1   = ( read_status[ 1 ] & 0x20 ) >> 5;
    status->sw_axis_y2   = ( read_status[ 1 ] & 0x10 ) >> 4;
    status->sw_axis_y1   = ( read_status[ 1 ] & 0x08 ) >> 3;
    status->sw_axis_x2   = ( read_status[ 1 ] & 0x04 ) >> 2;
    status->sw_axis_x1   = ( read_status[ 1 ] & 0x02 ) >> 1;
    status->drdy         = ( read_status[ 1 ] & 0x01 );
} 

void c3dhall7_get_interrupt_state ( c3dhall7_t *ctx, c3dhall7_int_state_t *state )
{
    state->interrupt_1 = digital_in_read( &ctx->it1 );
    state->interrupt_2 = digital_in_read( &ctx->it2 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void c3dhall7_i2c_write ( c3dhall7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void c3dhall7_i2c_read ( c3dhall7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void c3dhall7_spi_write ( c3dhall7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void c3dhall7_spi_read ( c3dhall7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select ); 
}

static int16_t package_data_16 ( uint8_t *data_in, uint8_t c_ind )
{
    int16_t data_out;
    
    data_out = data_in[ c_ind ];
    data_out <<= 8;
    data_out |= data_in[ c_ind + 1 ];
    
    return data_out;
}

static uint16_t package_data_u16 ( uint8_t *data_in, uint8_t c_ind )
{
    uint16_t data_out;

    data_out = data_in[ c_ind ];
    data_out <<= 8;
    data_out |= data_in[ c_ind + 1 ];

    return data_out;
}


// ------------------------------------------------------------------------- END

