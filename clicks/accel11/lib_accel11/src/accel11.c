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

#include "accel11.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ACCEL11_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void accel11_i2c_write ( accel11_t *ctx, uint8_t reg, uint8_t *data_buf, 
uint8_t len );
static void accel11_i2c_read ( accel11_t *ctx, uint8_t reg, uint8_t *data_buf, 
uint8_t len );
static void accel11_spi_write ( accel11_t *ctx, uint8_t reg, uint8_t *data_buf, 
uint8_t len );
static void accel11_spi_read ( accel11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void wait_for_finish ( );
static void wait_accel_drdy ( accel11_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accel11_cfg_setup ( accel11_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->it1   = HAL_PIN_NC;
    cfg->it2 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ACCEL11_SLAVE_ADDRESS_GND;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = 0;
    cfg->sel = ACCEL11_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

ACCEL11_RETVAL accel11_init ( accel11_t *ctx, accel11_cfg_t *cfg )
{
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == ACCEL11_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return ACCEL11_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
		i2c_master_set_timeout( &ctx->i2c, 0 );

        ctx->read_f = accel11_i2c_read;
        ctx->write_f = accel11_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode        = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  ACCEL11_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, ACCEL11_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_mode( &ctx->spi, cfg->spi_mode );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        
        ctx->read_f = accel11_spi_read;
        ctx->write_f = accel11_spi_write;
    }
    
    // Input pins

    digital_in_init( &ctx->it1, cfg->it1 );
    digital_in_init( &ctx->it2, cfg->it2 );

    return ACCEL11_OK;
}

void accel11_default_cfg ( accel11_t *ctx )
{
    accel11_software_reset( ctx );
    accel11_power_on_procedure( ctx );

    // Configuration sensor 
    accel11_write_byte( ctx, ACCEL11_REG_ACCEL_CONFIG, ACCEL11_ACFG_BWP_AVERAGING_2_SAMPLES | ACCEL11_CFG_ODR_50Hz );
    accel11_write_byte( ctx, ACCEL11_REG_ACCEL_RANGE, ACCEL11_RANGE_2g );
}

void accel11_generic_write ( accel11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void accel11_generic_read ( accel11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void accel11_write_byte ( accel11_t *ctx, uint8_t addr, uint8_t data_in )
{
    accel11_i2c_write( ctx, addr, &data_in, 1 );

}

uint8_t accel11_read_byte ( accel11_t *ctx, uint8_t addr )
{
    uint8_t read_reg;

    accel11_generic_read( ctx, addr, &read_reg, 1 );

    return read_reg;
}

uint8_t accel11_test_comunication ( accel11_t *ctx )
{
    uint8_t chip_id;

    chip_id = accel11_read_byte( ctx, ACCEL11_REG_CHIP_ID );
    
    if( chip_id == ACCEL11_CHIP_ID )
    {
        return 0;
    }
    return 1;
}

void accel11_software_reset ( accel11_t *ctx )
{
    accel11_write_byte( ctx, ACCEL11_REG_COMMAND, ACCEL11_CMD_SW_RESET );
    wait_for_finish( );
}

int16_t accel11_get_axis_data ( accel11_t *ctx, uint8_t axis )
{
    uint8_t data_lsb = 0;
    uint8_t data_msb = 0;
    int16_t axis_data = 0;

    wait_accel_drdy( ctx );

    data_lsb = accel11_read_byte( ctx, axis );
    data_msb = accel11_read_byte( ctx, axis + 1 );

    axis_data = data_msb;
    axis_data = axis_data << 8;
    axis_data = axis_data | data_lsb;

    return axis_data;
}

void accel11_power_on_procedure ( accel11_t *ctx )
{
    accel11_write_byte( ctx, ACCEL11_REG_POWER_CTRL, ACCEL11_PWRCTRL_ACCEL_ENABLE );
    accel11_write_byte( ctx, ACCEL11_REG_POWER_CONFIG, ACCEL11_PWRCFG_FSW_ON | ACCEL11_PWRCFG_APS_ON );
}

int8_t accel11_get_temperature ( accel11_t *ctx )
{
    int8_t temp;

    temp = accel11_read_byte( ctx, ACCEL11_REG_TEMPERATURE );
    temp = temp + 23;

    return temp;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void accel11_i2c_write ( accel11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void accel11_i2c_read ( accel11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void accel11_spi_write ( accel11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void accel11_spi_read ( accel11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select ); 
}

static void wait_for_finish ( )
{
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
}

static void wait_accel_drdy ( accel11_t *ctx )
{
    uint8_t status;
    uint8_t cnt = 0;

    do
    {
        status = accel11_read_byte( ctx, ACCEL11_REG_STATUS );
        cnt++;
        Delay_10ms( );
        if ( cnt > 20 )
        {
            return;
        }

    } while( ( status & ACCEL11_STATUS_DRDY_ACCEL ) == 0 );
}

// ------------------------------------------------------------------------- END

