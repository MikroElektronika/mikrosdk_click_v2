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

#include "accel13.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ACCEL13_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void accel13_i2c_write ( accel13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel13_i2c_read ( accel13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel13_spi_write ( accel13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel13_spi_read ( accel13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accel13_cfg_setup ( accel13_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int2 = HAL_PIN_NC;
    cfg->int1 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ACCEL13_DEVICE_SLAVE_ADDR_VCC;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = 0;
    cfg->sel = ACCEL13_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

ACCEL13_RETVAL accel13_init ( accel13_t *ctx, accel13_cfg_t *cfg )
{
    
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == ACCEL13_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return ACCEL13_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = accel13_i2c_read;
        ctx->write_f = accel13_i2c_write;

        // Hardware select communication
        
        spi_master_deselect_device( ctx->chip_select ); 
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
            return  ACCEL13_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, ACCEL13_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_mode( &ctx->spi, cfg->spi_mode );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        
        ctx->read_f = accel13_spi_read;
        ctx->write_f = accel13_spi_write;
         
        // Hardware select communication
        
        spi_master_select_device( ctx->chip_select );

    }

    // Input pins

    digital_in_init( &ctx->int2, cfg->int2 );
    digital_in_init( &ctx->int1, cfg->int1 );

    return ACCEL13_OK;
}

void accel13_default_cfg ( accel13_t *ctx )
{
    
    accel13_generic_write_single_byte( ctx, ACCEL13_REG_CTRL_1, ACCEL13_CTRL1_ODR_LOW_POWER_MODE_400_200Hz |
                                                                ACCEL13_CTRL1_MODE_HIGH_PERFORMANCE_MODE_14bit |
                                                                ACCEL13_CTRL1_LP_MODE_1 );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_CTRL_2, ACCEL13_CTRL2_BOOT_ENABLE |
                                                                ACCEL13_CTRL2_SOFT_RESET_DISABLE |
                                                                ACCEL13_CTRL2_PULLUP_CS_PIN_ENABLE |
                                                                ACCEL13_CTRL2_BDU_CONTINUOUS_UPDATE |
                                                                ACCEL13_CTRL2_IF_ADD_INC_ENABLED |
                                                                ACCEL13_CTRL2_I2C_AND_SPI_ENABLE |
                                                                ACCEL13_CTRL2_SPI_4_WIRE );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_CTRL_3, ACCEL13_CTRL3_SELF_TEST_DISABLE |
                                                                ACCEL13_CTRL3_OPEN_DRAIN_INT_PAD |
                                                                ACCEL13_CTRL3_LATCHED_INT_DISABLE |
                                                                ACCEL13_CTRL3_INT_ACTIVE_HIGH |
                                                                ACCEL13_CTRL3_SLP_MODE_SEL_EN_INT2 );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_CTRL_4_INT1, ACCEL13_CTRL4_INT1_6D_DISABLED |
                                                                     ACCEL13_CTRL4_INT1_SINGLE_TAP_DISABLED |
                                                                     ACCEL13_CTRL4_INT1_WAKEUP_DISABLED |
                                                                     ACCEL13_CTRL4_INT1_FREE_FALL_DISABLED |
                                                                     ACCEL13_CTRL4_INT1_TAP_ENABLED |
                                                                     ACCEL13_CTRL4_INT1_DIFF5_DISABLED |
                                                                     ACCEL13_CTRL4_INT1_FTH_DISABLED |
                                                                     ACCEL13_CTRL4_INT1_DRDY_DISABLED );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_CTRL_5_INT2, ACCEL13_CTRL5_INT2_SLEEP_STATE_DISABLED |
                                                                     ACCEL13_CTRL5_INT2_SLEEP_CHG_DISABLED |
                                                                     ACCEL13_CTRL5_INT2_BOOT_DISABLED |
                                                                     ACCEL13_CTRL5_INT2_T_DRDY_DISABLED |
                                                                     ACCEL13_CTRL5_INT2_OVR_DISABLED |
                                                                     ACCEL13_CTRL4_INT2_DIFF5_DISABLED |
                                                                     ACCEL13_CTRL4_INT2_DRDY_ENABLED );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_WAKE_UP_DURATION, 0x00 );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_FREE_FALL_CONFIG, 0x33 );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_CTRL_7, 0x20 );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_TAP_AXIS_X, 0x09 );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_TAP_AXIS_Y, 0xE9 );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_TAP_AXIS_Z, 0xE9 );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_INT_DURATION, 0x06 );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_X_OFFSET_USER, 0x00 );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_Y_OFFSET_USER, 0x00 );

    accel13_generic_write_single_byte( ctx, ACCEL13_REG_Z_OFFSET_USER, 0x40 );
}

void accel13_generic_write_bytes ( accel13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void accel13_generic_write_single_byte ( accel13_t *ctx, uint8_t reg, uint8_t data_in )
{
    ctx->write_f( ctx, reg, &data_in, 1 ); 
}

void accel13_generic_read_bytes ( accel13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

int16_t accel13_generic_read_word ( accel13_t *ctx, uint8_t reg )
{
    uint8_t read_buf[ 2 ];
    int16_t ret_val[ 1 ];

    ctx->read_f( ctx, reg, read_buf, 2 );

    *ret_val = read_buf[ 1 ];
    *ret_val <<= 8;

    return *ret_val |= read_buf[ 0 ];
}

float accel13_get_temperature ( accel13_t *ctx )
{
    int16_t raw_temp;
    float temp_data;
    
    raw_temp = accel13_generic_read_word( ctx, ACCEL13_REG_TEMPERATURE_DATA_LSB );
    raw_temp >>= 4;
    
    temp_data = raw_temp * 0.0625;
    temp_data += 25;
    
    return temp_data;
}

void accel13_get_axis_data ( accel13_t *ctx, accel13_axis_t *axis )
{
    axis->x = accel13_generic_read_word( ctx, ACCEL13_REG_AXIS_X_LSB );
    axis->y = accel13_generic_read_word( ctx, ACCEL13_REG_AXIS_Y_LSB );
    axis->z = accel13_generic_read_word( ctx, ACCEL13_REG_AXIS_Z_LSB );
}

void accel13_get_status ( accel13_t *ctx, accel13_status_t *status)
{
    uint8_t raw_status[ 1 ];
    
    accel13_generic_read_bytes( ctx, ACCEL13_REG_STATUS, raw_status, 1 );
    status->fifo_threshold  = ( raw_status[ 0 ] & 0x80 ) >> 7;
    status->wakeup_event    = ( raw_status[ 0 ] & 0x40 ) >> 6;
    status->sleep_event     = ( raw_status[ 0 ] & 0x20 ) >> 5;
    status->double_tap_event = ( raw_status[ 0 ] & 0x10 ) >> 4;
    status->single_tap_event = ( raw_status[ 0 ] & 0x08 ) >> 3;
    status->event_6d        = ( raw_status[ 0 ] & 0x04 ) >> 2;
    status->free_fall_event  = ( raw_status[ 0 ] & 0x02 ) >> 1;
    status->drdy_event      = ( raw_status[ 0 ] & 0x01 );
}

void accel13_get_wake_up_status ( accel13_t *ctx, accel13_wake_up_t *wu_status )
{
    uint8_t raw_status[ 1 ];

    accel13_generic_read_bytes( ctx, ACCEL13_REG_WAKE_UP_SOURCE, raw_status, 1 );
    wu_status->free_fall_event  = ( raw_status[ 0 ] & 0x20 ) >> 5;
    wu_status->sleep_event      = ( raw_status[ 0 ] & 0x10 ) >> 4;
    wu_status->wakeup_event     = ( raw_status[ 0 ] & 0x08 ) >> 3;
    wu_status->wakeup_x        = ( raw_status[ 0 ] & 0x04 ) >> 2;
    wu_status->wakeup_y        = ( raw_status[ 0 ] & 0x02 ) >> 1;
    wu_status->wakeup_z        = ( raw_status[ 0 ] & 0x01 );
}

void accel13_get_tap_status ( accel13_t *ctx, accel13_tap_t *tap_status )
{
    uint8_t raw_status[ 1 ];

    accel13_generic_read_bytes( ctx, ACCEL13_REG_TAP_SOURCE, raw_status, 1 );
    tap_status->tap          = ( raw_status[ 0 ] & 0x40 ) >> 6;
    tap_status->single_tap    = ( raw_status[ 0 ] & 0x20 ) >> 5;
    tap_status->double_tap    = ( raw_status[ 0 ] & 0x10 ) >> 4;
    tap_status->sign_tap      = ( raw_status[ 0 ] & 0x08 ) >> 3;
    tap_status->tap_x        = ( raw_status[ 0 ] & 0x04 ) >> 2;
    tap_status->tap_y        = ( raw_status[ 0 ] & 0x02 ) >> 1;
    tap_status->tap_z        = ( raw_status[ 0 ] & 0x01 );
}

void accel13_get_6d_status ( accel13_t *ctx, accel13_6d_t *sixd_status )
{
    uint8_t raw_status[ 1 ];

    *raw_status = accel13_generic_read_word( ctx, ACCEL13_REG_6D_SOURCE );
    sixd_status->event_6d  = ( raw_status[ 0 ] & 0x40 ) >> 6;
    sixd_status->z_high    = ( raw_status[ 0 ] & 0x20 ) >> 5;
    sixd_status->z_low     = ( raw_status[ 0 ] & 0x10 ) >> 4;
    sixd_status->y_high    = ( raw_status[ 0 ] & 0x08 ) >> 3;
    sixd_status->y_low     = ( raw_status[ 0 ] & 0x04 ) >> 2;
    sixd_status->x_high    = ( raw_status[ 0 ] & 0x02 ) >> 1;
    sixd_status->x_low     = ( raw_status[ 0 ] & 0x01 );
}

void accel13_get_user_offset ( accel13_t *ctx, accel13_user_offset_t *axis )
{
    uint8_t offset[ 1 ];

    accel13_generic_read_bytes( ctx, ACCEL13_REG_X_OFFSET_USER, offset, 1 );
    axis->x = offset[ 0 ];
    accel13_generic_read_bytes( ctx, ACCEL13_REG_Y_OFFSET_USER, offset, 1 );
    axis->y = offset[ 0 ];
    accel13_generic_read_bytes( ctx, ACCEL13_REG_Z_OFFSET_USER, offset, 1 );
    axis->z = offset[ 0 ];
}

void accel13_set_user_offset ( accel13_t *ctx, accel13_user_offset_t *axis )
{
    accel13_generic_write_single_byte( ctx, ACCEL13_REG_X_OFFSET_USER, axis->x );
    accel13_generic_write_single_byte( ctx, ACCEL13_REG_Y_OFFSET_USER, axis->y );
    accel13_generic_write_single_byte( ctx, ACCEL13_REG_Z_OFFSET_USER, axis->z );
}

uint8_t accel13_get_interrupt ( accel13_t *ctx, uint8_t int_num )
{
    if ( int_num == ACCEL13_INT_PIN_INTERRUPT_1 )
    {
        return digital_in_read( &ctx->int1 );
    }
    else
    {
        return digital_in_read( &ctx->int2 );
    }
}



// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void accel13_i2c_write ( accel13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void accel13_i2c_read ( accel13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void accel13_spi_write ( accel13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void accel13_spi_read ( accel13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt + 1];
    }
}

// ------------------------------------------------------------------------- END

