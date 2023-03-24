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

#include "lightranger4.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

// Calc time function
static uint32_t calc_macro_period ( lightranger4_t *ctx, uint8_t vcsel_period );
static uint32_t timeout_microseconds_to_mclks ( uint32_t timeout_us, uint32_t macro_period_us );
static uint16_t encode_timeout ( uint32_t timeout_mclks );

// Easy function for read/write data
static void write_data_u8 ( lightranger4_t *ctx, uint16_t addr, uint8_t _data );
static void write_data_u16 ( lightranger4_t *ctx, uint16_t addr, uint16_t _data );
static void write_data_u32 ( lightranger4_t *ctx, uint16_t addr, uint32_t _data );
static uint8_t read_data_u8 ( lightranger4_t *ctx, uint16_t addr );
static uint16_t read_data_u16 ( lightranger4_t *ctx, uint16_t addr );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lightranger4_cfg_setup ( lightranger4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->xsh = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = LR4_DEFAULT_SLAVE_ADDRESS;
}

LIGHTRANGER4_RETVAL lightranger4_init ( lightranger4_t *ctx, lightranger4_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return LIGHTRANGER4_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->xsh, cfg->xsh );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return LIGHTRANGER4_OK;
}

LIGHTRANGER4_RETVAL lightranger4_default_cfg ( lightranger4_t *ctx )
{
    uint16_t model_id;
    uint8_t cnt = 0;
    uint16_t result;
    uint8_t reg_val;
    uint16_t _data;
    uint8_t status;

    // Click default configuration

    digital_out_high( &ctx->xsh );  // shutdown

    Delay_100ms();
    Delay_100ms();

    model_id = read_data_u8( ctx, LR4_IDENTIFICATION_MODEL_ID );

    if ( model_id != 0xEA )
    {
        return LR4_RESP_DEVICE_ERROR_ID_IS_NOT_VALID;
    }

    Delay_100ms();

    lightranger4_software_reset( ctx );

    Delay_100ms();
    Delay_100ms();
    Delay_100ms();

    status = read_data_u8( ctx, LR4_FIRMWARE_SYSTEM_STATUS );

    while ( ( status & 0x01 ) == 0 )
    {
        status = read_data_u8( ctx, LR4_FIRMWARE_SYSTEM_STATUS );
        Delay_10ms();
        Delay_10ms();

        if ( cnt++ == 100 )
        {
            return LR4_RESP_FIRMWARE_TIMEOUT_ERROR;
        }
    }

    result = read_data_u16( ctx, LR4_PAD_I2C_HV_EXTSUP_CONFIG );
    result = ( result & 0xFE ) | 0x01;

    write_data_u16( ctx, LR4_PAD_I2C_HV_EXTSUP_CONFIG, result );
    Delay_10ms();
    ctx->fast_osc_frequency = read_data_u16( ctx, LR4_REG_FAST_OSC_FREQUENCY );
    ctx->osc_calibrate_val = read_data_u16( ctx, LR4_RESULT_OSC_CALIBRATE_VAL );

    write_data_u8( ctx, LR4_GPIO_TIO_HV_STATUS, 0x02 );
    Delay_10ms();
    write_data_u8( ctx, LR4_SIGMA_ESTIMATOR_EFFECTIVE_PULSE_WIDTH_NS, 8 );
    Delay_10ms();
    write_data_u8( ctx, LR4_SIGMA_ESTIMATOR_EFFECTIVE_AMBIENT_WIDTH_NS, 16 );
    Delay_10ms();
    write_data_u8( ctx, LR4_ALGO_CROSSTALK_COMPENSATION_VALID_HEIGHT_MM, 0x01 );
    Delay_10ms();
    write_data_u8( ctx, LR4_ALGO_RANGE_IGNORE_VALID_HEIGHT_MM, 0xFF );
    Delay_10ms();
    write_data_u8( ctx, LR4_ALGO_RANGE_MIN_CLIP, 0 );
    Delay_10ms();
    write_data_u8( ctx, LR4_ALGO_CONSISTENCY_CHECK_TOLERANCE, 2 );
    Delay_10ms();

    // general config
    write_data_u16( ctx, LR4_SYSTEM_THRESH_RATE_HIGH, 0x0000 );
    Delay_10ms();
    write_data_u16( ctx, LR4_SYSTEM_THRESH_RATE_LOW, 0x0000 );
    Delay_10ms();
    write_data_u8( ctx, LR4_DSS_CONFIG_APERTURE_ATTENUATION, 0x38 );

    // timing config
    Delay_10ms();
    write_data_u16( ctx, LR4_RANGE_CONFIG_SIGMA_THRESH, 360 );
    Delay_10ms();
    write_data_u16( ctx, LR4_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS, 192 );

    // dynamic config
    Delay_10ms();
    write_data_u8( ctx, LR4_SYSTEM_GROUPED_PARAMETER_HOLD_0, 0x01 );
    Delay_10ms();
    write_data_u8( ctx, LR4_SYSTEM_GROUPED_PARAMETER_HOLD_1, 0x01 );
    Delay_10ms();
    write_data_u8( ctx, LR4_SD_CONFIG_QUANTIFIER, 2 );
    Delay_10ms();
    write_data_u8( ctx, LR4_SYSTEM_GROUPED_PARAMETER_HOLD, 0x00 );
    Delay_10ms();
    write_data_u8( ctx, LR4_SYSTEM_SEED_CONFIG, 1 );
    Delay_10ms();
    write_data_u8( ctx, LR4_SYSTEM_SEQUENCE_CONFIG, 0x8B );
    Delay_10ms();
    write_data_u16( ctx, LR4_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT, 200 << 8 );
    Delay_10ms();
    write_data_u8( ctx, LR4_DSS_CONFIG_ROI_MODE_CONTROL, 2 );
    Delay_10ms();

    _data = read_data_u16( ctx, LR4_REG_OUTER_OFFSET_MM );
    Delay_10ms();
    write_data_u16( ctx, LR4_REG_PART_TO_PART_RANGE_OFFSET_MM, _data * 4 );
    Delay_10ms();

    return LR4_RESP_INIT_IS_SUCCESSFUL;
}

void lightranger4_generic_write ( lightranger4_t *ctx, uint16_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg  >> 8;
    tx_buf[ 1 ] = reg & 0x00FF;

    for ( cnt = 2; cnt <= len + 1; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 2 ];
    }

    i2c_master_write( &ctx->i2c, tx_buf, len + 2 ); 
}

void lightranger4_generic_read ( lightranger4_t *ctx, uint16_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg  >> 8;
    tx_buf[ 1 ] = reg & 0x00FF;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, data_buf, len );
}

void lightranger4_software_reset( lightranger4_t *ctx )
{
    write_data_u8( ctx, LR4_REG_SOFT_RESET, 0x00 );
    Delay_1ms();
    write_data_u8( ctx, LR4_REG_SOFT_RESET, 0x01 );
}


void lightranger4_start_measurement ( lightranger4_t *ctx, uint32_t period_ms )
{
    write_data_u32( ctx, LR4_SYSTEM_INTERMEASUREMENT_PERIOD, period_ms * ctx->osc_calibrate_val);

    write_data_u8( ctx, LR4_SYSTEM_INTERRUPT_CLEAR, 0x01);
    write_data_u8( ctx, LR4_SYSTEM_MODE_START, 0x40);
}

uint8_t lightranger4_new_data_ready ( lightranger4_t *ctx )
{
    uint8_t tmp;

    tmp = read_data_u8 ( ctx, LR4_GPIO_TIO_HV_STATUS);

    if ( tmp != 0x03 )
    {
        return 0;
    }
    return 1;
}


uint16_t lightranger4_get_distance ( lightranger4_t *ctx )
{
    uint16_t distance;

    distance = read_data_u16( ctx, LR4_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0 );
    return distance;
}

uint16_t lightranger4_get_signal_rate ( lightranger4_t *ctx )
{
    uint16_t reading;

    reading = read_data_u16( ctx, LR4_RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0 );
    return reading;
}

uint8_t lightranger4_set_distance_mode ( lightranger4_t *ctx, uint8_t mode )
{
    switch ( mode )
    {
        case LR4_DISTANCE_MODE_SHORT:
        {
            write_data_u8( ctx, LR4_RANGE_CONFIG_VCSEL_PERIOD_A, 0x07);
            write_data_u8( ctx, LR4_RANGE_CONFIG_VCSEL_PERIOD_B, 0x05);
            write_data_u8( ctx, LR4_RANGE_CONFIG_VALID_PHASE_HIGH, 0x38);
            write_data_u8( ctx, LR4_SD_CONFIG_WOI_SD0, 0x07);
            write_data_u8( ctx, LR4_SD_CONFIG_WOI_SD1, 0x05);
            write_data_u8( ctx, LR4_SD_CONFIG_INITIAL_PHASE_SD0, 6);
            write_data_u8( ctx, LR4_SD_CONFIG_INITIAL_PHASE_SD1, 6);

            break;
        }
        case LR4_DISTANCE_MODE_MEDIUM:
        {
            write_data_u8( ctx, LR4_RANGE_CONFIG_VCSEL_PERIOD_A, 0x0B);
            write_data_u8( ctx, LR4_RANGE_CONFIG_VCSEL_PERIOD_B, 0x09);
            write_data_u8( ctx, LR4_RANGE_CONFIG_VALID_PHASE_HIGH, 0x78);
            write_data_u8( ctx, LR4_SD_CONFIG_WOI_SD0, 0x0B);
            write_data_u8( ctx, LR4_SD_CONFIG_WOI_SD1, 0x09);
            write_data_u8( ctx, LR4_SD_CONFIG_INITIAL_PHASE_SD0, 10);
            write_data_u8( ctx, LR4_SD_CONFIG_INITIAL_PHASE_SD1, 10);
            break;
        }
        case LR4_DISTANCE_MODE_LONG:
        {
            write_data_u8( ctx, LR4_RANGE_CONFIG_VCSEL_PERIOD_A, 0x0F);
            write_data_u8( ctx, LR4_RANGE_CONFIG_VCSEL_PERIOD_B, 0x0D);
            write_data_u8( ctx, LR4_RANGE_CONFIG_VALID_PHASE_HIGH, 0xB8);
            write_data_u8( ctx, LR4_SD_CONFIG_WOI_SD0, 0x0F);
            write_data_u8( ctx, LR4_SD_CONFIG_WOI_SD1, 0x0D);
            write_data_u8( ctx, LR4_SD_CONFIG_INITIAL_PHASE_SD0, 14);
            write_data_u8( ctx, LR4_SD_CONFIG_INITIAL_PHASE_SD1, 14);
            break;
        }
        default:
        {
            return LR4_RESP_WRONG_MODE;
        }
    }
    return LR4_RESP_MODE_SUCCESSFULLY_SET;
}

uint8_t lightranger4_get_range_status ( lightranger4_t *ctx )
{
    uint8_t m_status;

    m_status = read_data_u8( ctx, LR4_RESULT_RANGE_STATUS ) & 0x1F;

    return m_status;
}

void lightranger4_set_center ( lightranger4_t *ctx, uint8_t center_x, uint8_t center_y )
{
    uint8_t center_val;

    if ( center_y > 7 )
    {
        center_val = 128 + ( center_x << 3 ) + ( 15 - center_y );
    }
    else
    {
        center_val = ( ( 15 - center_x ) << 3 ) + center_y;
    }
    write_data_u8( ctx, LR4_ROI_CONFIG_USER_ROI_CENTRE_SPAD, center_val );
}

void lightranger4_set_zone_size ( lightranger4_t *ctx, uint8_t width, uint8_t height )
{
    uint8_t dimensions;

    dimensions = ( height << 4 )  + width;
    write_data_u8( ctx, LR4_ROI_CONFIG_USER_ROI_REQUESTED_GLOBAL_XY_SIZE, dimensions );
}

void lightranger4_set_user_roi ( lightranger4_t *ctx, lightranger4_user_roi_t *roi )
{
    uint8_t center_x;
    uint8_t center_y;
    uint8_t width;
    uint8_t height;

    center_x = ( roi->top_left_x + roi->bottom_right_x + 1 ) / 2;
    center_y = ( roi->top_left_y + roi->bottom_right_y + 1 ) / 2;
    width   = roi->bottom_right_x - roi->top_left_x;
    height  = roi->top_left_y - roi->bottom_right_y;

    if (width < 3 || height < 3)
    {
        lightranger4_set_center( ctx, 0x08, 0x08 );
        lightranger4_set_zone_size( ctx, 0x0F, 0x0F );
    }
    else
    {
        lightranger4_set_center( ctx, center_x, center_y );
        lightranger4_set_zone_size( ctx, width, height );
    }
}

LIGHTRANGER4_RETVAL lightranger4_set_measurement_timing_budget ( lightranger4_t *ctx, uint32_t budget_us )
{
    uint32_t range_config_timeout_us;
    uint32_t macro_period_us;
    uint32_t phasecal_timeout_mclks;
    uint16_t _data16;
    uint8_t _data8;

    if ( budget_us <= 4528 )
    {
        return LR4_RESP_INSUFFICIENT_BUDGET;
    }
    budget_us -= 4528;
    range_config_timeout_us = budget_us;

    if ( range_config_timeout_us > 1100000 )
    {
        return LR4_RESP_TOO_HIGH_BUDGET;
    }
    range_config_timeout_us /= 2;

    _data8 = read_data_u8( ctx, LR4_RANGE_CONFIG_VCSEL_PERIOD_A );
    macro_period_us = calc_macro_period( ctx, _data8 );

    phasecal_timeout_mclks = timeout_microseconds_to_mclks( 1000, macro_period_us );

    if ( phasecal_timeout_mclks > 0xFF )
    {
        phasecal_timeout_mclks = 0xFF;
    }

    write_data_u8( ctx, LR4_PHASECAL_CONFIG_TIMEOUT_MACROP, phasecal_timeout_mclks );

    _data16 = timeout_microseconds_to_mclks(1, macro_period_us);
    _data16 = encode_timeout( _data16 );
    write_data_u16( ctx, LR4_MM_CONFIG_TIMEOUT_MACROP_A_HI, _data16);

    _data16 = timeout_microseconds_to_mclks(range_config_timeout_us, macro_period_us);
    _data16 = encode_timeout( _data16 );
    write_data_u16( ctx, LR4_RANGE_CONFIG_TIMEOUT_MACROP_A_HI, _data16);

    _data8 = read_data_u8( ctx, LR4_RANGE_CONFIG_VCSEL_PERIOD_B );
    macro_period_us = calc_macro_period( ctx, _data8 );

    _data16 = timeout_microseconds_to_mclks(1, macro_period_us);
    _data16 = encode_timeout( _data16 );
    write_data_u16( ctx, LR4_MM_CONFIG_TIMEOUT_MACROP_B_HI, _data16 );

    _data16 =  timeout_microseconds_to_mclks(range_config_timeout_us, macro_period_us);
    _data16 = encode_timeout( _data16 );
    write_data_u16( ctx, LR4_RANGE_CONFIG_TIMEOUT_MACROP_B_HI, _data16);

    return LR4_RESP_BUDGET_IS_SUCCESSFULLY_SET;
}

uint8_t lightranger4_get_intrrupt_state ( lightranger4_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void lightranger4_set_xshut_pin ( lightranger4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->xsh, state );
}

void lightranger4_power_on ( lightranger4_t *ctx )
{
    lightranger4_set_xshut_pin( ctx, 0);
    Delay_100ms();
    lightranger4_set_xshut_pin( ctx, 1);
    Delay_1sec();
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint32_t calc_macro_period ( lightranger4_t *ctx, uint8_t vcsel_period )
{
    uint32_t pll_period_us;
    uint8_t vcsel_period_pclks;
    uint32_t macro_period_us;

    pll_period_us = ( ( uint32_t ) 0x01 << 30 ) / ctx->fast_osc_frequency;
    vcsel_period_pclks = ( vcsel_period + 1 ) << 1;
    macro_period_us = ( uint32_t ) 2304 * pll_period_us;
    macro_period_us >>= 6;
    macro_period_us *= vcsel_period_pclks;
    macro_period_us >>= 6;

    return macro_period_us;
}

static uint32_t timeout_microseconds_to_mclks ( uint32_t timeout_us, uint32_t macro_period_us )
{
    return ( ( ( uint32_t ) timeout_us << 12 ) + ( macro_period_us >> 1 ) ) / macro_period_us;
}

static uint16_t encode_timeout ( uint32_t timeout_mclks )
{
    uint32_t ls_byte = 0;
    uint16_t ms_byte = 0;

    if ( timeout_mclks > 0 )
    {
        ls_byte = timeout_mclks - 1;

        while ( ( ls_byte & 0xFFFFFF00 ) > 0 )
        {
            ls_byte >>= 1;
            ms_byte++;
        }
        return ( ms_byte << 8 ) | ( ls_byte & 0xFF );
    }
    return 0;
}

static void write_data_u8 ( lightranger4_t *ctx, uint16_t addr, uint8_t _data )
{
    lightranger4_generic_write( ctx, addr, &_data, 1);
}

static void write_data_u16 ( lightranger4_t *ctx, uint16_t addr, uint16_t _data )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = _data >> 8;
    tx_buf[ 1 ] = _data & 0x00FF;

    lightranger4_generic_write( ctx, addr, tx_buf, 2);
}

static void write_data_u32 ( lightranger4_t *ctx, uint16_t addr, uint32_t _data )
{
    uint8_t tx_buf[ 4 ];

    tx_buf[ 0 ] = _data >> 24;
    tx_buf[ 1 ] = _data >> 16;
    tx_buf[ 2 ] = _data >> 8;
    tx_buf[ 3 ] = _data & 0x000000FF;

    lightranger4_generic_write( ctx, addr, tx_buf, 4);
}

static uint8_t read_data_u8 ( lightranger4_t *ctx, uint16_t addr )
{
    uint8_t rx_data;

    lightranger4_generic_read( ctx, addr, &rx_data, 1);

    return rx_data;
}

static uint16_t read_data_u16 ( lightranger4_t *ctx, uint16_t addr )
{
    uint8_t rx_buf[ 2 ];
    uint16_t read_data;

    lightranger4_generic_read( ctx, addr, rx_buf, 2);

    read_data = rx_buf[ 0 ];
    read_data <<= 8;
    read_data |= rx_buf[ 1 ];

    return read_data;
}

// ------------------------------------------------------------------------- END

