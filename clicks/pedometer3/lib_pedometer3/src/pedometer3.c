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

#include "pedometer3.h"

// ------------------------------------------------------------- PRIVATE MACROS

#define PEDOMETER3_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void pedometer3_i2c_write ( pedometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void pedometer3_i2c_read ( pedometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void pedometer3_spi_write ( pedometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void pedometer3_spi_read ( pedometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static uint16_t read_data_u16 ( pedometer3_t *ctx, uint8_t reg_addr );
static void write_data_u8 ( pedometer3_t *ctx, uint8_t reg_addr, uint8_t tx_data );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pedometer3_cfg_setup ( pedometer3_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->trg     = HAL_PIN_NC;
    cfg->it2     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PEDOMETER3_SLAVE_ADDRESS_1;

    cfg->spi_speed   = 100000;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_mode    = SPI_MASTER_MODE_0;

    cfg->sel         = PEDOMETER3_MASTER_I2C;
}

err_t pedometer3_init ( pedometer3_t *ctx, pedometer3_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set

    ctx->master_sel = cfg->sel;

    if ( PEDOMETER3_MASTER_I2C == ctx->master_sel )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed = cfg->i2c_speed;
        i2c_cfg.scl   = cfg->scl;
        i2c_cfg.sda   = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) )
        {
            return PEDOMETER3_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f  = pedometer3_i2c_read;
        ctx->write_f = pedometer3_i2c_write;
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

        spi_cfg.default_write_data = PEDOMETER3_DUMMY; 
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) )
        {
            return  PEDOMETER3_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, PEDOMETER3_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 

        ctx->read_f  = pedometer3_spi_read;
        ctx->write_f = pedometer3_spi_write;
    }

    // Input pins
    digital_in_init( &ctx->trg, cfg->trg );
    digital_in_init( &ctx->it2, cfg->it2 );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PEDOMETER3_OK;
}

void pedometer3_default_cfg ( pedometer3_t *ctx )
{
    uint8_t tmp = 0;
    // CTRL register 1
    tmp = PEDOMETER3_CNTL1_MODE_STAND_BY | PEDOMETER3_CNTL1_RES_MODE_HIGHER_NOISE |
          PEDOMETER3_CNTL1_DATA_READY_DISABLE | PEDOMETER3_CNTL1_G_RANGE_8g |
          PEDOMETER3_CNTL1_PEDOMETER_DISABLE | PEDOMETER3_CNTL1_TILT_DISABLE |
          PEDOMETER3_CNTL1_TAP_DISABLE;

    pedometer3_generic_write( ctx, PEDOMETER3_REG_CONTROL_1, &tmp, 1 );

    // CTRL register 2
    tmp = PEDOMETER3_CNTL2_SOFTWARE_RESET_NO_ACTIVE | PEDOMETER3_CNTL2_COMMAND_TEST_NO_ACTIVE |
          PEDOMETER3_CNTL2_DOWN_STATE_ENABLE | PEDOMETER3_CNTL2_FACE_DOWN_STATE_ENABLE |
          PEDOMETER3_CNTL2_FACE_UP_STATE_ENABLE | PEDOMETER3_CNTL2_LEFT_STATE_ENABLE |
          PEDOMETER3_CNTL2_RIGHT_STATE_ENABLE | PEDOMETER3_CNTL2_UP_STATE_ENABLE;

    pedometer3_generic_write( ctx, PEDOMETER3_REG_CONTROL_2, &tmp, 1 );

    // CTRL register 3
    tmp = PEDOMETER3_CNTL3_OTP_OUTPUT_DATA_RATE_12_5Hz | PEDOMETER3_CNTL3_TAP_OUTPUT_DATA_RATE_400Hz |
          PEDOMETER3_CNTL3_OWUF_OUTPUT_DATA_RATE_0_781Hz;

    pedometer3_generic_write( ctx, PEDOMETER3_REG_CONTROL_3, &tmp, 1 );

    // CTRL register 4
    tmp = PEDOMETER3_CNTL4_COUNTER_DECREMENT_MODE | PEDOMETER3_CNTL4_THRESHOLD_MODE_ABSOLUTE |
          PEDOMETER3_CNTL4_WAKE_UP_DISABLE | PEDOMETER3_CNTL4_BACK_TO_SLEEP_DISABLE |
          PEDOMETER3_CNTL4_HIGH_PASS_ENABLE | PEDOMETER3_CNTL4_OBTS_OUTPUT_DATA_RATE_0_781Hz;

    pedometer3_generic_write( ctx, PEDOMETER3_REG_CONTROL_4, &tmp, 1 );

    // CTRL register 5
    tmp = PEDOMETER3_CNTL5_MANUAL_WAKE_UP_0 | PEDOMETER3_CNTL5_MANUAL_SLEEP_UP_0;

    pedometer3_generic_write( ctx, PEDOMETER3_REG_CONTROL_5, &tmp, 1 );

    // Output data ctrl
    tmp = PEDOMETER3_ODCNTL_IR_BYPASS_FILTERING_APPLIED | PEDOMETER3_ODCNTL_LPRO_ODR_9 |
          PEDOMETER3_ODCNTL_OSA_OUTPUT_DATA_RATE_50Hz;

    pedometer3_generic_write( ctx, PEDOMETER3_REG_OUTPUT_DATA_CONTROL, &tmp, 1 );

    // Pedometer step watermark
    pedometer3_set_step_watermark( ctx, 10000 );

    // PED CTRL 2
    tmp = PEDOMETER3_PED_CNTL2_HIGH_PASS_FILTER_4 | PEDOMETER3_PED_CNTL2_ODR_SELECT_100Hz;
    pedometer3_generic_write( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_2, &tmp, 1 );

    // Low power ctrl
    write_data_u8( ctx, PEDOMETER3_REG_LOW_POWER_CONTROL, 0x7B );

    // Interrupt 7 register
    tmp = PEDOMETER3_INC7_STEP_OVERFLOW_INTERRUPT_2_ENABLE |
          PEDOMETER3_INC7_STEP_WATERMARK_INTERRUPT_2_ENABLE |
          PEDOMETER3_INC7_STEP_INCREMENT_INTERRUPT_1_ENABLE;

    pedometer3_generic_write( ctx, PEDOMETER3_REG_INTERRUPT_CONTROL_7, &tmp, 1 );

    // Interrupt ctrl
    write_data_u8( ctx, PEDOMETER3_REG_INTERRUPT_CONTROL_1, PEDOMETER3_INC1_PHYSICAL_INTERRUPT_ENABLE );
    write_data_u8( ctx, PEDOMETER3_REG_INTERRUPT_CONTROL_5, PEDOMETER3_INC5_PHYSICAL_INTERRUPT_ENABLE );

    //  Pedometer config
    pedometer3_pedometer_cfg( ctx, 100 ); // 100Hz or 50Hz
}

void pedometer3_generic_write ( pedometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len );
}

void pedometer3_generic_read ( pedometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void pedometer3_get_accel_axis ( pedometer3_t *ctx, pedometer3_axis_t *axis )
{
    axis->x = read_data_u16( ctx, PEDOMETER3_REG_X_AXIS_OUTPUT_LOW );
    axis->y = read_data_u16( ctx, PEDOMETER3_REG_Y_AXIS_OUTPUT_LOW );
    axis->z = read_data_u16( ctx, PEDOMETER3_REG_Z_AXIS_OUTPUT_LOW );
}

void pedometer3_get_hp_accel_axis ( pedometer3_t *ctx, pedometer3_axis_t *axis )
{
    axis->x = read_data_u16( ctx, PEDOMETER3_REG_X_AXIS_HIGH_PASS_LOW );
    axis->y = read_data_u16( ctx, PEDOMETER3_REG_Y_AXIS_HIGH_PASS_LOW );
    axis->z = read_data_u16( ctx, PEDOMETER3_REG_Z_AXIS_HIGH_PASS_LOW );
}

void pedometer3_set_step_watermark ( pedometer3_t *ctx, uint16_t value )
{
    write_data_u8( ctx, PEDOMETER3_REG_PED_STPWM_LOW, value >> 8 );
    write_data_u8( ctx, PEDOMETER3_REG_PED_STPWM_HIGH, value & 0x00FF );
}

void pedometer3_pedometer_cfg ( pedometer3_t *ctx, uint8_t odr )
{
    if ( 100 == odr )
    {
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_1, 0x66 );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_2, 0x2C );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_3, 0x17 );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_4, 0x1F );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_5, 0x24 );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_6, 0x13 );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_7, 0x0B );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_8, 0x08 );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_9, 0x19 );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_10, 0x1C );
    }
    else
    {
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_1, 0x56 );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_2, 0x26 );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_3, 0x17 );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_4, 0x1F );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_5, 0x0E );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_6, 0x0B );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_7, 0x02 );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_8, 0x03 );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_9, 0x0D );
        write_data_u8( ctx, PEDOMETER3_REG_PEDOMETER_CONTROL_10, 0x10 );
    }
}

uint16_t pedometer3_get_step_counter ( pedometer3_t *ctx )
{
    return read_data_u16 ( ctx, PEDOMETER3_REG_PAD_STEP_LOW );
}

void pedometer3_get_tilt_position ( pedometer3_t *ctx, pedometer3_tilt_position_t *tilt )
{
    uint8_t tilt_position = 0;

    tilt_position = read_data_u16( ctx, PEDOMETER3_REG_CURRENT_TILT_POSITION );

    if ( tilt_position & 0x20 )
    {
        tilt->current_pos = PEDOMETER3_TILT_POSITION_LEFT;
    }
    else if ( tilt_position & 0x10 )
    {
        tilt->current_pos = PEDOMETER3_TILT_POSITION_RIGHT;
    }
    else if ( tilt_position & 0x08 )
    {
        tilt->current_pos = PEDOMETER3_TILT_POSITION_DOWN;
    }
    else if ( tilt_position & 0x04 )
    {
        tilt->current_pos = PEDOMETER3_TILT_POSITION_UP;
    }
    else if ( tilt_position & 0x02 )
    {
        tilt->current_pos = PEDOMETER3_TILT_POSITION_FACE_DOWN;
    }
    else if ( tilt_position & 0x01 )
    {
        tilt->current_pos = PEDOMETER3_TILT_POSITION_FACE_UP;
    }

    tilt_position = read_data_u16( ctx, PEDOMETER3_REG_PREVIOUS_TILT_POSITION );

    if ( tilt_position & 0x20 )
    {
        tilt->previous_pos = PEDOMETER3_TILT_POSITION_LEFT;
    }
    else if ( tilt_position & 0x10 )
    {
        tilt->previous_pos = PEDOMETER3_TILT_POSITION_RIGHT;
    }
    else if ( tilt_position & 0x08 )
    {
        tilt->previous_pos = PEDOMETER3_TILT_POSITION_DOWN;
    }
    else if ( tilt_position & 0x04 )
    {
        tilt->previous_pos = PEDOMETER3_TILT_POSITION_UP;
    }
    else if ( tilt_position & 0x02 )
    {
        tilt->previous_pos = PEDOMETER3_TILT_POSITION_FACE_DOWN;
    }
    else if ( tilt_position & 0x01 )
    {
        tilt->previous_pos = PEDOMETER3_TILT_POSITION_FACE_UP;
    }
}

uint8_t pedometer3_get_tap_detection ( pedometer3_t *ctx )
{
    uint8_t read_tap = 0;

    pedometer3_generic_read( ctx, 0x14, &read_tap, 1 );

    if ( read_tap & 0x20 )
    {
        return PEDOMETER3_TAP_X_NEGATIVE;
    }
    else if ( read_tap & 0x10 )
    {
        return  PEDOMETER3_TAP_X_POSITIVE;
    }
    else if ( read_tap & 0x08 )
    {
        return PEDOMETER3_TAP_Y_NEGATIVE;
    }
    else if ( read_tap & 0x04 )
    {
        return PEDOMETER3_TAP_Y_POSITIVE;
    }
    else if ( read_tap & 0x02 )
    {
        return PEDOMETER3_TAP_Z_NEGATIVE;
    }
    else if ( read_tap & 0x01 )
    {
        return PEDOMETER3_TAP_Z_POSITIVE;
    }
}

err_t pedometer3_test_communication ( pedometer3_t *ctx )
{
    uint8_t device_id[ 4 ] = { 0 };

    pedometer3_generic_read( ctx, 0x00, device_id, 4);

    if ( ( 0x4B == device_id[ 0 ] ) && ( 0x69 == device_id[ 1 ] ) &&
         ( 0x6F == device_id[ 2 ] ) && ( 0x6E == device_id[ 3 ] ) )
    {
        return PEDOMETER3_OK;
    }
    return PEDOMETER3_ERROR;
}

uint8_t pedometer3_get_interrupt_1 ( pedometer3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t pedometer3_get_interrupt_2 ( pedometer3_t *ctx )
{
    return digital_in_read( &ctx->it2 );
}

uint8_t pedometer3_get_trigger_int ( pedometer3_t *ctx )
{
    return digital_in_read( &ctx->trg );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void pedometer3_i2c_write ( pedometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static void pedometer3_i2c_read ( pedometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void pedometer3_spi_write ( pedometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &reg, 1 );
    spi_master_write( &ctx->spi, data_buf, len );
    spi_master_deselect_device( ctx->chip_select ); 
}

static void pedometer3_spi_read ( pedometer3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_data = reg | 0x80;
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &tx_data, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select ); 
}

static uint16_t read_data_u16 ( pedometer3_t *ctx, uint8_t reg_addr )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    uint16_t rx_data = 0;

    pedometer3_generic_read( ctx, reg_addr, rx_buf, 2 );

    rx_data = rx_buf[ 1 ];
    rx_data <<= 8;
    rx_data |= rx_buf[ 0 ];

    return rx_data;
}

static void write_data_u8 ( pedometer3_t *ctx, uint8_t reg_addr, uint8_t tx_data )
{
    pedometer3_generic_write( ctx, reg_addr, &tx_data, 1 );
}

// ------------------------------------------------------------------------- END
