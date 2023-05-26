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

#include "heartrate2.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t heartrate2_bool_check ( uint8_t value );

static uint8_t heartrate2_ppg_tint_check ( uint8_t value );

static uint8_t heartrate2_led_range_check ( uint8_t value );

static uint8_t heartrate2_smp_rate_check ( uint8_t value );

static uint8_t heartrate2_smo_freq_check ( uint8_t value );

static uint8_t heartrate2_led_range_curr_check ( uint8_t value );

static uint8_t heartrate2_sequence_check ( uint8_t value );

static void heartrate2_soft_reset_delay( void );

static void heartrate2_dev_i2c_delay( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void heartrate2_cfg_setup ( heartrate2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = HEARTRATE2_SLAVE_ADDRESS;
}

HEARTRATE2_RETVAL heartrate2_init ( heartrate2_t *ctx, heartrate2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return HEARTRATE2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->cs, cfg->cs );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return HEARTRATE2_OK_OK;
}

void heartrate2_default_cfg ( heartrate2_t *ctx, uint8_t cfg_led )
{
    heartrate2_ppg_cfg_t ppg_cfg_object;
    heartrate2_ledpa_t ledpa_object;
    heartrate2_ledsq_cfg_t ledsq_object;
    heartrate2_int_t int_object;

    ppg_cfg_object.alc = HEARTRATE2_PPG_CFG_ALC_DS;
    ppg_cfg_object.offset = HEARTRATE2_PPG_CFG_OFFSET_NO;
    ppg_cfg_object.ppg_tint = HEARTRATE2_PPG_CFG_TINT_58p7_US;
    ppg_cfg_object.led_range = HEARTRATE2_PPG_CFG_LED_RANGE_32k;
    ppg_cfg_object.smp_rate = HEARTRATE2_PPG_CFG_SMP_RATE_P1_4096sps;
    ppg_cfg_object.smp_freq = HEARTRATE2_PPG_CFG_SMP_AVG_8;

    switch ( cfg_led )
    {
        case HEARTRATE2_CONFIG_GREEN:
        {
            ledpa_object.green = 0xFF;
            ledpa_object.ir = 0x00;
            ledpa_object.red = 0x00;
            ledsq_object.ledsq1 = HEARTRATE2_LEDSQ_GREEN;
            break;
        }
        case HEARTRATE2_CONFIG_IR:
        {
            ledpa_object.green = 0x00;
            ledpa_object.ir = 0xFF;
            ledpa_object.red = 0x00;
            ledsq_object.ledsq1 = HEARTRATE2_LEDSQ_IR;
            break;
        }
        case HEARTRATE2_CONFIG_RED:
        {
            ledpa_object.green = 0x00;
            ledpa_object.ir = 0x00;
            ledpa_object.red = 0xFF;
            ledsq_object.ledsq1 = HEARTRATE2_LEDSQ_RED;
            break;
        }
        default:
            return;
    }

    ledsq_object.ledsq2 = HEARTRATE2_LEDSQ_OFF;
    ledsq_object.ledsq3 = HEARTRATE2_LEDSQ_OFF;
    ledsq_object.ledsq4 = HEARTRATE2_LEDSQ_OFF;
    ledsq_object.ledsq5 = HEARTRATE2_LEDSQ_OFF;
    ledsq_object.ledsq6 = HEARTRATE2_LEDSQ_OFF;

    int_object.full_fifo = HEARTRATE2_INT_ENABLE;
    int_object.data_rdy = HEARTRATE2_INT_ENABLE;
    int_object.alc_ovf = HEARTRATE2_INT_DISABLE;
    int_object.proxy = HEARTRATE2_INT_DISABLE;
    int_object.led_compliant = HEARTRATE2_INT_DISABLE;
    int_object.die_temp = HEARTRATE2_INT_DISABLE;
    int_object.sha = HEARTRATE2_INT_DISABLE;

    heartrate2_ppg_config( ctx, &ppg_cfg_object );
    heartrate2_ledpa_config( ctx, &ledpa_object );
    heartrate2_led_sequence_config( ctx, &ledsq_object );
    heartrate2_int_control( ctx, &int_object );
}

void heartrate2_generic_write ( heartrate2_t *ctx, uint8_t reg, uint8_t write_data )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = write_data; 

    i2c_master_write( &ctx->i2c, tx_buf, 2 );      
}

uint8_t heartrate2_generic_read ( heartrate2_t *ctx, uint8_t reg )
{
    uint8_t tx_buf[ 1 ];
    uint8_t temp_data[ 1 ];

    tx_buf [ 0 ] = reg;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, temp_data, 1 );

    return temp_data[ 0 ];
}

void heartrate2_read_buf ( heartrate2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void heartrate2_read_fifo ( heartrate2_t *ctx, heartrate2_fifo_data_t *fifo )
{
    uint32_t temp_data;
    uint8_t temp_buf[ 4 ];
    uint8_t data_rdy;

    for ( ; ; )
    {
        data_rdy = heartrate2_generic_read( ctx, HEARTRATE2_REG_INT_STATUS_1 );
        if ( ( data_rdy & HEARTRATE2_INT_1_DATA_RDY ) > 0 )
        {
            break;
        }
        heartrate2_dev_i2c_delay(  );
    }

    heartrate2_read_buf( ctx, HEARTRATE2_REG_FIFO_DATA_REG, temp_buf, 3 );

    temp_data = temp_buf[ 0 ];
    temp_data <<= 8;
    temp_data |= temp_buf[ 1 ];
    temp_data <<= 8;
    temp_data |= temp_buf[ 2 ];
    
    fifo->data_val = ( temp_data & HEARTRATE2_FIFO_DATA_MASK );
    fifo->tag = ( ( temp_data >> HEARTRATE2_FIFO_RES ) & 
                                 HEARTRATE2_FIFO_TAG_MASK );
}

float heartrate2_read_temp ( heartrate2_t *ctx )
{
    uint8_t temp_data;
    float return_data;
    uint8_t data_buf[ 2 ];

    heartrate2_generic_write( ctx, HEARTRATE2_REG_DIE_TEMP_CFG, 0x01 );

    for ( ; ; )
    {
        temp_data = heartrate2_generic_read( ctx, HEARTRATE2_REG_INT_ENABLE_1 );
        if ( ( temp_data & HEARTRATE2_INT_1_DIE_TEMP_RDY ) > 0 )
        {
            break;
        }
    }

    heartrate2_read_buf( ctx, HEARTRATE2_REG_DIE_TEMP_INT, data_buf, 2 );

    return_data = data_buf[ 0 ] + ( float )data_buf[ 1 ] * HEARTRATE2_TEMPERATURE_RESOLUTION;
    
    return return_data;
}

void heartrate2_soft_reset ( heartrate2_t *ctx )
{
    volatile uint8_t status = 0;

    heartrate2_generic_write( ctx, HEARTRATE2_REG_SYSTEM_CTRL,
                              HEARTRATE2_SYS_CTRL_SW_RESET );

    heartrate2_soft_reset_delay(  );
                              
    for ( ; ; )
    {
        status = heartrate2_generic_read( ctx, HEARTRATE2_REG_SYSTEM_CTRL );
        if ( status == 0 )
        {
            break;
        }
        heartrate2_dev_i2c_delay(  );
    }
}

uint8_t heartrate2_ppg_config ( heartrate2_t *ctx, heartrate2_ppg_cfg_t *ppg_cfg )
{
    if ( ( heartrate2_bool_check ( ppg_cfg->alc ) &
           heartrate2_bool_check ( ppg_cfg->offset ) &
           heartrate2_ppg_tint_check ( ppg_cfg->ppg_tint ) &
           heartrate2_led_range_check ( ppg_cfg->led_range ) &
           heartrate2_smp_rate_check ( ppg_cfg->smp_rate ) &
           heartrate2_smo_freq_check ( ppg_cfg->smp_freq ) ) != HEARTRATE2_OK )
    {
        return HEARTRATE2_ERROR;
    }

    heartrate2_generic_write( ctx, HEARTRATE2_REG_PPG_CFG_1, ( 
                            ( ppg_cfg->alc << HEARTRATE2_PPG_CFG_ALC ) | 
                            ( ppg_cfg->offset << HEARTRATE2_PPG_CFG_OFFSET ) | 
                            ( ppg_cfg->led_range << HEARTRATE2_PPG_CFG_ADC_RANGE ) | 
                            ( ppg_cfg->ppg_tint << HEARTRATE2_PPG_CFG_TINT ) ) );

    heartrate2_generic_write( ctx, HEARTRATE2_REG_PPG_CFG_2, ( 
                            ( ppg_cfg->smp_rate << HEARTRATE2_PPG_CFG_SMP_RATE ) | 
                            ( ppg_cfg->smp_freq << HEARTRATE2_PPG_CFG_SMP_AVG ) ) );

    return HEARTRATE2_OK;
}

void heartrate2_ledpa_config ( heartrate2_t *ctx, heartrate2_ledpa_t *ledpa )
{
    heartrate2_generic_write( ctx, HEARTRATE2_REG_LED_1_PA, ledpa->green );
    heartrate2_generic_write( ctx, HEARTRATE2_REG_LED_2_PA, ledpa->ir );
    heartrate2_generic_write( ctx, HEARTRATE2_REG_LED_3_PA, ledpa->red );
}

uint8_t heartrate2_led_range_curr_config ( heartrate2_t *ctx, heartrate2_led_range_curr_t *led_range )
{
    if ( ( heartrate2_led_range_curr_check ( led_range->green ) &
           heartrate2_led_range_curr_check ( led_range->ir ) &
           heartrate2_led_range_curr_check ( led_range->red ) ) != HEARTRATE2_OK )
    {
        return HEARTRATE2_ERROR;
    }

    heartrate2_generic_write( ctx, HEARTRATE2_REG_LED_RANGE_1, ( 
                            ( led_range->green << HEARTRATE2_LED_RANGE_SHIFT_GREEN ) | 
                            ( led_range->ir << HEARTRATE2_LED_RANGE_SHIFT_IR ) | 
                            ( led_range->red << HEARTRATE2_LED_RANGE_SHIFT_RED ) ) );

    return HEARTRATE2_OK;                            
}

uint8_t heartrate2_led_sequence_config ( heartrate2_t *ctx, heartrate2_ledsq_cfg_t *ledsq )
{
    if ( ( heartrate2_sequence_check ( ledsq->ledsq1 ) &
           heartrate2_sequence_check ( ledsq->ledsq2 ) &
           heartrate2_sequence_check ( ledsq->ledsq3 ) &
           heartrate2_sequence_check ( ledsq->ledsq4 ) &
           heartrate2_sequence_check ( ledsq->ledsq5 ) &
           heartrate2_sequence_check ( ledsq->ledsq6 ) ) != HEARTRATE2_OK )
    {
        return HEARTRATE2_ERROR;
    }

    heartrate2_generic_write( ctx, HEARTRATE2_REG_LED_SQUENCE_REG_1, 
    ( ( ledsq->ledsq2 << HEARTRATE2_LEDSQ_SHIFT ) | ( ledsq->ledsq1 ) ) );

    heartrate2_generic_write( ctx, HEARTRATE2_REG_LED_SQUENCE_REG_2, 
    ( ( ledsq->ledsq4 << HEARTRATE2_LEDSQ_SHIFT ) | ( ledsq->ledsq3 ) ) );

    heartrate2_generic_write( ctx, HEARTRATE2_REG_LED_SQUENCE_REG_3, 
    ( ( ledsq->ledsq6 << HEARTRATE2_LEDSQ_SHIFT ) | ( ledsq->ledsq5 ) ) );

    return HEARTRATE2_OK;
}

uint8_t heartrate2_int_control ( heartrate2_t *ctx, heartrate2_int_t *int_ctrl )
{
    if ( ( heartrate2_bool_check ( int_ctrl->sha ) &
           heartrate2_bool_check ( int_ctrl->proxy ) &
           heartrate2_bool_check ( int_ctrl->led_compliant ) &
           heartrate2_bool_check ( int_ctrl->full_fifo ) &
           heartrate2_bool_check ( int_ctrl->data_rdy ) &
           heartrate2_bool_check ( int_ctrl->alc_ovf ) &
           heartrate2_bool_check ( int_ctrl->die_temp ) ) != HEARTRATE2_OK )
    {
        return HEARTRATE2_ERROR;
    }

    heartrate2_generic_write( ctx, HEARTRATE2_REG_INT_ENABLE_1, ( 
                            ( int_ctrl->full_fifo << HEARTRATE2_INT_SHIFT_FULL ) | 
                            ( int_ctrl->data_rdy << HEARTRATE2_INT_SHIFT_DATA_RDY ) | 
                            ( int_ctrl->alc_ovf << HEARTRATE2_INT_SHIFT_ALC_OVF ) | 
                            ( int_ctrl->proxy << HEARTRATE2_INT_SHIFT_PROXY ) | 
                            ( int_ctrl->led_compliant << HEARTRATE2_INT_SHIFT_LED_COMPLIANT ) | 
                            ( int_ctrl->die_temp << HEARTRATE2_INT_SHIFT_DIE_TEMEP ) ) );

    heartrate2_generic_write( ctx, HEARTRATE2_REG_INT_ENABLE_2, ( 
                            ( int_ctrl->sha << HEARTRATE2_INT_SHIFT_SHA ) ) );

    return HEARTRATE2_OK;
}

void heartrate2_int_status ( heartrate2_t *ctx, heartrate2_int_t *int_status )
{
    uint8_t int_status_value;

    int_status_value = heartrate2_generic_read( ctx, HEARTRATE2_REG_INT_STATUS_1 );
    int_status->pwr_rdy = ( ( int_status_value >> HEARTRATE2_INT_SHIFT_PWR_RDY ) &
                                                  HEARTRATE2_INT_MASK );
    int_status->die_temp = ( ( int_status_value >> HEARTRATE2_INT_SHIFT_DIE_TEMEP ) &
                                                   HEARTRATE2_INT_MASK );
    int_status->led_compliant = ( ( int_status_value >> HEARTRATE2_INT_SHIFT_LED_COMPLIANT ) &
                                                        HEARTRATE2_INT_MASK );
    int_status->proxy = ( ( int_status_value >> HEARTRATE2_INT_SHIFT_PROXY ) &
                                                HEARTRATE2_INT_MASK );
    int_status->alc_ovf = ( ( int_status_value >> HEARTRATE2_INT_SHIFT_ALC_OVF ) &
                                                  HEARTRATE2_INT_MASK );
    int_status->data_rdy = ( ( int_status_value >> HEARTRATE2_INT_SHIFT_DATA_RDY ) &
                                                   HEARTRATE2_INT_MASK );
    int_status->full_fifo = ( ( int_status_value >> HEARTRATE2_INT_SHIFT_FULL ) &
                                                    HEARTRATE2_INT_MASK );

    int_status_value = heartrate2_generic_read( ctx, HEARTRATE2_REG_INT_STATUS_2 );
    int_status->sha = ( ( int_status_value >> HEARTRATE2_INT_SHIFT_SHA ) &
                                              HEARTRATE2_INT_MASK );
}

uint8_t heartrate2_get_int ( heartrate2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t heartrate2_get_gp ( heartrate2_t *ctx )
{
    return digital_in_read( &ctx->an );
}

void heartrate2_set_en ( heartrate2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->cs, state );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t heartrate2_bool_check ( uint8_t value )
{
    switch ( value )
    {
        case 0x00:
        {
            return HEARTRATE2_OK;
        }
        case 0x01:
        {
            return HEARTRATE2_OK;
        }
        default:
            return HEARTRATE2_ERROR;
    }
}

static uint8_t heartrate2_ppg_tint_check ( uint8_t value )
{
    switch ( value )
    {
        case HEARTRATE2_PPG_CFG_TINT_14p8_US:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_TINT_29p4_US:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_TINT_58p7_US:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_TINT_117p3_US:
        {
            return HEARTRATE2_OK;
        }
        default:
            return HEARTRATE2_ERROR;
    }
}

static uint8_t heartrate2_led_range_check ( uint8_t value )
{
    switch ( value )
    {
        case HEARTRATE2_PPG_CFG_LED_RANGE_4k:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_LED_RANGE_8k:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_LED_RANGE_16k:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_LED_RANGE_32k:
        {
            return HEARTRATE2_OK;
        }
        default:
            return HEARTRATE2_ERROR;
    }
}

static uint8_t heartrate2_smp_rate_check ( uint8_t value )
{
    switch ( value )
    {
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_24sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_50sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_84sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_99sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_199sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_399sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P2_24sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P2_50sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P2_84sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P2_99sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_8sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_16sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_32sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_64sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_128sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_256sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_512sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_1024sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_2048sps:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_RATE_P1_4096sps:
        {
            return HEARTRATE2_OK;
        }
        default:
            return HEARTRATE2_ERROR;
    }
}

static uint8_t heartrate2_smo_freq_check ( uint8_t value )
{
    switch ( value )
    {
        case HEARTRATE2_PPG_CFG_SMP_AVG_1:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_AVG_2:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_AVG_4:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_AVG_8:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_AVG_16:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_AVG_32:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_AVG_64:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_PPG_CFG_SMP_AVG_128:
        {
            return HEARTRATE2_OK;
        }
        default:
            return HEARTRATE2_ERROR;
    }
}

static uint8_t heartrate2_led_range_curr_check ( uint8_t value )
{
    switch ( value )
    {
        case HEARTRATE2_LED_RANGE_CURRENT_31_MA:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_LED_RANGE_CURRENT_62_MA:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_LED_RANGE_CURRENT_93_MA:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_LED_RANGE_CURRENT_124_MA:
        {
            return HEARTRATE2_OK;
        }
        default:
            return HEARTRATE2_ERROR;
    }
}

static uint8_t heartrate2_sequence_check ( uint8_t value )
{
    switch ( value )
    {
        case HEARTRATE2_LEDSQ_GREEN:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_LEDSQ_IR:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_LEDSQ_RED:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_LEDSQ_PILOT_LED1:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_LEDSQ_DIRECT_AMBIENT:
        {
            return HEARTRATE2_OK;
        }
        case HEARTRATE2_LEDSQ_OFF:
        {
            return HEARTRATE2_OK;
        }
        default:
            return HEARTRATE2_ERROR;
    }
}

static void heartrate2_soft_reset_delay( void )
{
    Delay_100ms(  );
}

static void heartrate2_dev_i2c_delay( void )
{
    Delay_10ms(  );
}

// ------------------------------------------------------------------------- END

