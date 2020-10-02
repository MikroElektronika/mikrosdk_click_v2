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

#include "C6dotimu3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C6DOTIMU3_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void C6dotimu3_i2c_write ( C6dotimu3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void C6dotimu3_i2c_read ( C6dotimu3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void C6dotimu3_spi_write ( C6dotimu3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void C6dotimu3_spi_read ( C6dotimu3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void C6dotimu3_cfg_setup ( C6dotimu3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;


    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = C6DOFIMU3_REG_I2C_ADDR_0;
    cfg->sel = C6DOTIMU3_MASTER_I2C;
    
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

C6DOTIMU3_RETVAL C6dotimu3_init ( C6dotimu3_t *ctx, C6dotimu3_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;
    
    if ( ctx->master_sel == C6DOTIMU3_MASTER_I2C )
    { 
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return C6DOTIMU3_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        digital_out_init( &ctx->rst, cfg->cs );
        ctx->read_f = C6dotimu3_i2c_read;
        ctx->write_f = C6dotimu3_i2c_write;
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
        
        spi_cfg.default_write_data = C6DOTIMU3_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  C6DOTIMU3_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, C6DOTIMU3_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f = C6dotimu3_spi_read;
        ctx->write_f = C6dotimu3_spi_write;
    }
    
    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
 
    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_low( &ctx->rst );
    
    return C6DOTIMU3_OK;
}

void C6dotimu3_default_cfg ( C6dotimu3_t *ctx )
{
   uint8_t tmp[ 1 ];

    // Set to standby mode
    c6dofimu3_standby( ctx );

    // Configure the accelerometer
    // Set the full scale range to 4g.
    tmp[ 0 ] = 0x01;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_XYZ_DATA_CFG, tmp, 1 );

    C6dotimu3_generic_read( ctx, C6DOFIMU3_CTRL_REG1, tmp, 1 );
    tmp[ 0 ] &= 0xC5;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_CTRL_REG1, tmp, 1 );
    
    C6dotimu3_generic_read( ctx, C6DOFIMU3_CTRL_REG1, tmp, 1 );
    tmp[ 0 ] = tmp[ 0 ] |  0x10;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_CTRL_REG1, tmp, 1 );

    C6dotimu3_generic_read( ctx, C6DOFIMU3_CTRL_REG2, tmp, 1 );
    tmp[ 0 ] &= 0xFC;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_CTRL_REG2, tmp, 1 );
    
    // Set high resolution mode
    C6dotimu3_generic_read( ctx, C6DOFIMU3_CTRL_REG2, tmp, 1 );
    tmp[ 0 ] = tmp[ 0 ] |  0x02;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_CTRL_REG2, tmp, 1 );

    // Configure the magnetometer
    // Set auto-calibration, set oversampling, enable hybrid mode
    tmp[ 0 ] = 0xB7;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_M_CTRL_REG1, tmp, 1 );

    // Configure interrupts 1 and 2
    C6dotimu3_generic_read( ctx, C6DOFIMU3_CTRL_REG3, tmp, 1 );
    tmp[ 0 ] &= 0xFD;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_CTRL_REG3, tmp, 1 );
    
    // Set ACTIVE HIGH, push-pull interrupts
    C6dotimu3_generic_read( ctx, C6DOFIMU3_CTRL_REG3, tmp, 1 );
    tmp[ 0 ] = tmp[ 0 ] |  0x02;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_CTRL_REG3, tmp, 1 );
    
    C6dotimu3_generic_read( ctx, C6DOFIMU3_CTRL_REG4, tmp, 1 );
    tmp[ 0 ] &= 0xE2;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_CTRL_REG4, tmp, 1 );
    
    // DRDY, Freefall/Motion, P/L and tap ints enabled
    C6dotimu3_generic_read( ctx, C6DOFIMU3_CTRL_REG4, tmp, 1 );
    tmp[ 0 ] = tmp[ 0 ] |  0x1D;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_CTRL_REG4, tmp, 1 );
    
    // DRDY on INT1, P/L and taps on INT2
    tmp[ 0 ] = 0x01;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_CTRL_REG5, tmp , 1 );

    // Set to active to start reading
    c6dofimu3_active( ctx );
}

void C6dotimu3_generic_write ( C6dotimu3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void C6dotimu3_generic_read ( C6dotimu3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void c6dofimu3_set_rst ( C6dotimu3_t *ctx, uint8_t rst_state )
{
    if ( rst_state == C6DOFIMU3_RST_PIN_STATE_HIGH )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
    Delay_1ms( );
}

void c6dofimu3_multi_write ( C6dotimu3_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes )
{   
    uint16_t n_cnt;
    uint8_t tx_buf[ 256 ];

    tx_buf[ 0 ] = reg;

    for ( n_cnt = 0; n_cnt < n_bytes; n_cnt++ )
    {
        tx_buf[ n_cnt + 2 ] = p_tx_data[ n_cnt ];
    }

    if ( ctx->master_sel == C6DOTIMU3_MASTER_I2C )
    {
        i2c_master_write( &ctx->i2c, tx_buf, n_bytes + 1 );  
    }
    else
    {
        tx_buf[ 0 ] |= C6DOFIMU3_BIT_MASK_SPI_CMD_WRITE;
        tx_buf[ 1 ] = reg;
        tx_buf[ 1 ] &= C6DOFIMU3_BIT_MASK_BIT_7;

        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, tx_buf, n_bytes + 2 );
        spi_master_deselect_device( ctx->chip_select );     
        Delay_1ms( );   
    }

}  
void c6dofimu3_multi_read ( C6dotimu3_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes )
{
    uint8_t tx_buf[ 3 ];

    tx_buf[ 0 ] = reg;

    if ( ctx->master_sel == C6DOTIMU3_MASTER_I2C )
    {
        i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, p_rx_data, n_bytes );
    }
    else
    {
        tx_buf[ 0 ] = reg;
        tx_buf[ 0 ] &= C6DOFIMU3_BIT_MASK_SPI_CMD_READ;
        tx_buf[ 1 ] = reg;
        tx_buf[ 1 ] &= C6DOFIMU3_BIT_MASK_BIT_7;

        spi_master_select_device( ctx->chip_select );
        spi_master_write_then_read( &ctx->spi, tx_buf, 2, p_rx_data, n_bytes );
        spi_master_deselect_device( ctx->chip_select );
        Delay_1ms( );   
    }  
}

C6DOFIMU3_RETVAL_T c6dofimu3_check_id ( C6dotimu3_t *ctx )
{
    uint8_t id_val;

    C6dotimu3_generic_read( ctx, C6DOFIMU3_WHO_AM_I, &id_val, 1 );

    if ( id_val == C6DOFIMU3_DEVICE_ID_VAL )
    {
        return C6DOFIMU3_SUCCESS;
    }
    else
    {
        return C6DOFIMU3_ERROR;
    }
}

C6DOFIMU3_RETVAL_T c6dofimu3_check_data_ready ( C6dotimu3_t *ctx )
{
    uint8_t status_val;

    C6dotimu3_generic_read( ctx, C6DOFIMU3_STATUS, &status_val, 1 );

    if ( status_val != C6DOFIMU3_DR_STATUS_XYZ_DATA_ERROR )
    {
        return C6DOFIMU3_SUCCESS;
    }
    else
    {
        return C6DOFIMU3_ERROR;
    }
}
void c6dofimu3_standby ( C6dotimu3_t *ctx )
{
    uint8_t tmp;
    
    C6dotimu3_generic_read( ctx, C6DOFIMU3_CTRL_REG1, &tmp, 1 );
    
    tmp &= 0xFE;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_CTRL_REG1, &tmp, 1 );
}

void c6dofimu3_active ( C6dotimu3_t *ctx )
{
    uint8_t tmp;

    C6dotimu3_generic_read( ctx, C6DOFIMU3_CTRL_REG1, &tmp, 1 );

    tmp = tmp | 0x01;
    C6dotimu3_generic_write( ctx, C6DOFIMU3_CTRL_REG1, &tmp, 1 );
}

void c6dofimu3_read_accel_data ( C6dotimu3_t *ctx, c6dofimu3_accel_t *accel_data )
{
    uint8_t rx_buf[ 6 ];
    uint16_t tmp;
    int16_t temp;
  
    c6dofimu3_multi_read( ctx, C6DOFIMU3_OUT_X_MSB, rx_buf, 6 );
  
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp = tmp | rx_buf[ 1 ];
    temp = ( int16_t ) tmp;
    temp >>= 2;
    accel_data->x = temp;

    tmp = rx_buf[ 2 ];
    tmp <<= 8;
    tmp = tmp | rx_buf[ 3 ];
    temp = ( int16_t ) tmp;
    temp >>= 2;
    accel_data->y = temp;

    tmp = rx_buf[ 4 ];
    tmp <<= 8;
    tmp = tmp | rx_buf[ 5 ];
    temp = ( int16_t ) tmp;
    temp >>= 2;
    accel_data->z = temp;
}

void c6dofimu3_read_mag_data ( C6dotimu3_t *ctx, c6dofimu3_mag_t *mag_data )
{
    uint8_t rx_buf[ 6 ];
    uint16_t tmp;
    
    c6dofimu3_multi_read( ctx, C6DOFIMU3_M_OUT_X_MSB, rx_buf, 6 );

    tmp = rx_buf[ 0 ];
    tmp = tmp << 8;
    tmp = tmp | rx_buf[ 1 ];
    mag_data->x = ( int16_t ) tmp;

    tmp = rx_buf[ 2 ];
    tmp <<= 8;
    tmp = tmp | rx_buf[ 3 ];
    mag_data->y = ( int16_t ) tmp;

    tmp = rx_buf[ 4 ];
    tmp <<= 8;
    tmp = tmp | rx_buf[ 5 ];
    mag_data->z = ( int16_t ) tmp;
}

void c6dofimu3_get_data ( C6dotimu3_t *ctx, c6dofimu3_accel_t *accel_data, c6dofimu3_mag_t *mag_data )
{
    c6dofimu3_read_accel_data ( ctx, accel_data );

    c6dofimu3_read_mag_data ( ctx, mag_data );
}

uint8_t c6dofimu3_check_int1 ( C6dotimu3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void C6dotimu3_i2c_write ( C6dotimu3_t *ctx, uint8_t reg, uint8_t *tx_data, uint8_t len )
{
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data[ 0 ];

    i2c_master_write( &ctx->i2c, tx_buf, 2 );    
}

static void C6dotimu3_i2c_read ( C6dotimu3_t *ctx, uint8_t reg, uint8_t *read_data, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];

    tx_buf [ 0 ] = reg;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 1 );
    read_data[ 0 ] = rx_buf[ 0 ];
}

static void C6dotimu3_spi_write ( C6dotimu3_t *ctx, uint8_t reg, uint8_t *tx_data, uint8_t len )
{
    uint8_t tx_buf[ 3 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= C6DOFIMU3_BIT_MASK_SPI_CMD_WRITE;
    tx_buf[ 1 ] = reg;
    tx_buf[ 1 ] &= C6DOFIMU3_BIT_MASK_BIT_7;
    tx_buf[ 2 ] = tx_data[ 0 ];

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = tx_data[ cnt - 1 ]; 
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );     
    Delay_1ms( );   
}

static void C6dotimu3_spi_read ( C6dotimu3_t *ctx, uint8_t reg, uint8_t *read_data, uint8_t len )
{
    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf[ 3 ];

    tx_buf[ 0 ] = reg | 0x80;
    tx_buf[ 0 ] &= C6DOFIMU3_BIT_MASK_SPI_CMD_READ;
    tx_buf[ 1 ] = reg;
    tx_buf[ 1 ] &= C6DOFIMU3_BIT_MASK_BIT_7;
    tx_buf[ 2 ] = C6DOFIMU3_SPI_COMMUNICATION_DUMMY;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 3, rx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select ); 
    Delay_1ms();

    read_data[ 0 ] = rx_buf[ 2 ]; 
}

// ------------------------------------------------------------------------- END

