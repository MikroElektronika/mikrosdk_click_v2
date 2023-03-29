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

#include "ecg6.h"

// ------------------------------------------------------------------ VARIABLES

#define DEVICE_OK 0
#define DEVICE_ERROR 1

// ----------------------------------------------- PRIVATE FUNCTION DECLARATION

static void dev_get_fifo_elements( ecg6_t *ctx, ecg6_element_t *sample );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ecg6_cfg_setup ( ecg6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ECG6_DEVICE_SLAVE_ADDRESS;
}

ECG6_RETVAL ecg6_init ( ecg6_t *ctx, ecg6_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ECG6_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return ECG6_OK;
}

void ecg6_default_cfg ( ecg6_t *ctx )
{
    ecg6_cfg_element_t cfg;
    
    ecg6_write_data( ctx, ECG6_REG_INTERRUPT_ENABLE_1,
                     ECG6_INTS1_A_FULL_OFF | ECG6_INTS1_PPG_RDY_OFF |
                     ECG6_INTS1_ALC_OVF_OFF | ECG6_INTS1_PROX_INIT_OFF |
                     ECG6_INTS1_PWR_RDY_OFF );

    ecg6_write_data( ctx, ECG6_REG_INTERRUPT_ENABLE_2, ECG6_INTS2_VDD_OOR_OFF |
                                                  ECG6_INTS2_DRDY_ENABLE );

    ecg6_write_data( ctx, ECG6_REG_SYSTEM_CTRL, ECG6_SYSCTRL_RESET_ENABLE );
    Delay_100ms( );
    ecg6_write_data( ctx, ECG6_REG_FIFO_CFG, ECG6_FCFG_A_FULL_CLR |
                               ECG6_FCFG_A_FULL_TYPE_ONCE |
                               ECG6_FCFG_FIFO_ROLLS_ON_FULL_ON | 0x0F );


    cfg.element_1 = ECG6_SENSOR_ECG;
    cfg.element_2 = ECG6_SENSOR_NONE;
    cfg.element_3 = ECG6_SENSOR_NONE;
    cfg.element_4 = ECG6_SENSOR_NONE;
    ecg6_cfg_element( ctx, &cfg );

    ecg6_write_data( ctx, ECG6_REG_PPG_CFG_1, ECG6_PPGCFG1_PPG_ADC_RGE_32768nA |
                                         ECG6_PPGCFG1_PPG_SR_100n1 |
                                         ECG6_PPGCFG1_PPG_PW_100us );

    ecg6_write_data( ctx, ECG6_REG_PPG_CFG_2, 0x06 );

    ecg6_write_data( ctx, ECG6_REG_LED_RANGE, ECG6_LRANG_LED2_SMP_AVE_50 |
                                         ECG6_LRANG_LED1_SMP_AVE_50 );

    ecg6_write_data( ctx, ECG6_REG_SYSTEM_CTRL, ECG6_SYSCTRL_FIFO_ENABLE |
                                           ECG6_SYSCTRL_SHUTDOWN_DISABLE |
                                           ECG6_SYSCTRL_RESET_DISABLE );

    ecg6_write_data( ctx, ECG6_REG_CONFIG_1, ECG6_CFG1_ADC_OSR_3200 );
    ecg6_write_data( ctx, ECG6_REG_CONFIG_3, ECG6_CFG3_PGA_GAIN_4 | ECG6_CFG3_IA_GAIN_5 );

    ecg6_set_led_pulse( ctx, 0x00, 0x00 );

    // Clear FIFO
    ecg6_write_data( ctx, ECG6_REG_FIFO_WRITE, 0 );
    ecg6_write_data( ctx, ECG6_REG_OVERFLOW_CNT, 0 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0 );

    Delay_100ms();
}

void ecg6_write_data( ecg6_t *ctx, uint8_t reg, uint8_t in_data )
{
    uint8_t buf_data[ 2 ];

    buf_data[ 0 ] = reg;
    buf_data[ 1 ] = in_data;
    
    i2c_master_write( &ctx->i2c, buf_data, 2 );    
}

void ecg6_write_data_buf( ecg6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{    
    uint8_t tx_data[ 256 ];
    uint8_t cnt;
    
    tx_data[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_data[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_data, len + 1 );    
   
}

uint8_t ecg6_read_data( ecg6_t *ctx, uint8_t reg )
{
    uint8_t reg_data;

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, &reg_data, 1 );

    return reg_data;
}

void ecg6_read_data_buf( ecg6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t ecg6_check_path_id ( ecg6_t *ctx )
{
    uint8_t part_id;

    part_id = ecg6_read_data( ctx, ECG6_REG_PART_ID );

    if ( part_id == ECG6_DEF_PART_ID )
    {
        return DEVICE_OK;
    }
    return DEVICE_ERROR;
}

void ecg6_cfg_element( ecg6_t *ctx, ecg6_cfg_element_t *cfg )
{
    uint8_t tmp;

    tmp = cfg->element_2;
    tmp <<= 4;
    tmp |= cfg->element_1;
    ecg6_write_data( ctx, ECG6_REG_FIFO_DATA_CTRL_1, tmp );

    tmp = cfg->element_4;
    tmp <<= 4;
    tmp |= cfg->element_3;
    ecg6_write_data( ctx, ECG6_REG_FIFO_DATA_CTRL_2, tmp );
}

void ecg6_set_led_pulse( ecg6_t *ctx, uint8_t ir_led, uint8_t red_led )
{
    ecg6_write_data( ctx, ECG6_REG_LED_PULSE_AMPLITUDE_2, red_led );
    ecg6_write_data( ctx, ECG6_REG_LED_PULSE_AMPLITUDE_1, ir_led );
}

uint8_t ecg6_ppg_default_config ( ecg6_t *ctx )
{
    ecg6_cfg_element_t cfg;
    
    uint8_t tmp = ECG6_INTS1_A_FULL_OFF |
                        ECG6_INTS1_PPG_RDY_ON | ECG6_INTS1_ALC_OVF_OFF | 
                        ECG6_INTS1_PROX_INIT_OFF | ECG6_INTS1_PWR_RDY_OFF;
                        
    ecg6_write_data( ctx, ECG6_REG_INTERRUPT_ENABLE_1, tmp );
                     
    ecg6_write_data( ctx, ECG6_REG_INTERRUPT_ENABLE_2, ECG6_INTS2_VDD_OOR_OFF |
                                                  ECG6_INTS2_DRDY_OFF );
    
    tmp = ECG6_SYSCTRL_RESET_ENABLE;
    ecg6_write_data( ctx, ECG6_REG_SYSTEM_CTRL, tmp );
    Delay_100ms( );
    
     tmp = ECG6_FCFG_A_FULL_CLR | ECG6_FCFG_A_FULL_TYPE_ONCE | 
     ECG6_FCFG_FIFO_ROLLS_ON_FULL_ON | 0x0F;
    ecg6_write_data( ctx, ECG6_REG_FIFO_CFG, tmp );
                     

    cfg.element_1 = ECG6_SENSOR_PPG_LED_1;
    cfg.element_2 = ECG6_SENSOR_PPG_LED_2;
    cfg.element_3 = ECG6_SENSOR_ECG;
    cfg.element_4 = ECG6_SENSOR_NONE;
    ecg6_cfg_element( ctx, &cfg );
    
    tmp = ECG6_PPGCFG1_PPG_ADC_RGE_32768nA | 
             ECG6_PPGCFG1_PPG_SR_100n1 | ECG6_PPGCFG1_PPG_PW_100us;
    ecg6_write_data( ctx, ECG6_REG_PPG_CFG_1, tmp );
    tmp = 0x06;
    ecg6_write_data( ctx, ECG6_REG_PPG_CFG_2, tmp );
    
    ecg6_write_data( ctx, ECG6_REG_LED_RANGE, ECG6_LRANG_LED2_SMP_AVE_50 |
                                         ECG6_LRANG_LED1_SMP_AVE_50 );
    
    tmp = ECG6_SYSCTRL_FIFO_ENABLE | 
            ECG6_SYSCTRL_SHUTDOWN_DISABLE | ECG6_SYSCTRL_RESET_DISABLE;
    ecg6_write_data( ctx, ECG6_REG_SYSTEM_CTRL, tmp );
    
    tmp = ECG6_CFG1_ADC_OSR_3200;
    ecg6_write_data( ctx, ECG6_REG_CONFIG_1, tmp );
    tmp = ECG6_CFG3_PGA_GAIN_4 | ECG6_CFG3_IA_GAIN_5;
    ecg6_write_data( ctx, ECG6_REG_CONFIG_3, tmp );

    ecg6_set_led_pulse( ctx , 0xFF, 0xFF );

    // Clear FIFO
    ecg6_write_data( ctx, ECG6_REG_FIFO_WRITE, 0 );
    ecg6_write_data( ctx, ECG6_REG_OVERFLOW_CNT, 0 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0 );
    
    return tmp;
    
    Delay_100ms();
}

void ecg6_get_sample_data( ecg6_t *ctx, ecg6_element_t *element, uint8_t num_sample )
{
    uint8_t rx_data_buff[ 3 ];
    
    if ( num_sample > 31 )
    {
        num_sample = 31;
    }

    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, num_sample );
    Delay_50us( );
    dev_get_fifo_elements( ctx, element );
}

void ecg6_get_all_samples( ecg6_t *ctx, ecg6_fifo_t *fifo_data )
{
    uint32_t rx_data_buff[ 3 ];

    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x00 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_0 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x01 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_1 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x02 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_2 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x03 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_3 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x04 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_4 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x05 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_5 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x06 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_6 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x07 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_7 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x08 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_8 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x09 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_9 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x0A );
    dev_get_fifo_elements( ctx, &fifo_data->sample_10 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x0B );
    dev_get_fifo_elements( ctx, &fifo_data->sample_11 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x0C );
    dev_get_fifo_elements( ctx, &fifo_data->sample_12 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x0D );
    dev_get_fifo_elements( ctx, &fifo_data->sample_13 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x0E );
    dev_get_fifo_elements( ctx, &fifo_data->sample_14 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x0F );
    dev_get_fifo_elements( ctx, &fifo_data->sample_15 );
    
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x10 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_16 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x11 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_17 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x12 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_18 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x13 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_19 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x14 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_20 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x15 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_21 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x16 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_22 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x17 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_23 );
    ecg6_write_data(ctx, ECG6_REG_FIFO_READ, 0x18 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_24 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x19 );
    dev_get_fifo_elements( ctx, &fifo_data->sample_25 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x1A );
    dev_get_fifo_elements( ctx, &fifo_data->sample_26 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x1B );
    dev_get_fifo_elements( ctx, &fifo_data->sample_27 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x1C );
    dev_get_fifo_elements( ctx, &fifo_data->sample_28 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x1D );
    dev_get_fifo_elements( ctx, &fifo_data->sample_29 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x1E );
    dev_get_fifo_elements( ctx, &fifo_data->sample_30 );
    ecg6_write_data( ctx, ECG6_REG_FIFO_READ, 0x1F );
    dev_get_fifo_elements( ctx, &fifo_data->sample_31 );
}

void ecg6_get_interrupt_status ( ecg6_t *ctx, ecg6_int_status_t *status )
{
    uint8_t raw_data;
    
    raw_data = ecg6_read_data( ctx, ECG6_REG_INTERRUPT_STATUS_1 );
    status->a_full    = ( raw_data & 0x80 ) ? 1 : 0;
    status->ppg_rdy   = ( raw_data & 0x40 ) ? 1 : 0;
    status->alc_ovf   = ( raw_data & 0x20 ) ? 1 : 0;
    status->prox_int  = ( raw_data & 0x10 ) ? 1 : 0;
    status->pwr_rdy   = ( raw_data & 0x01 );
    
    raw_data = ecg6_read_data( ctx, ECG6_REG_INTERRUPT_STATUS_2 );
    status->vdd_oor = ( raw_data & 0x80 ) ? 1 : 0;
    status->ecg_rdy = ( raw_data & 0x04 ) ? 1 : 0;
}

uint8_t ecg6_int_pin_state ( ecg6_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_get_fifo_elements( ecg6_t *ctx, ecg6_element_t *sample )
{
    uint8_t rx_data_buff[ 3 ];
    
    ecg6_read_data_buf( ctx, ECG6_REG_FIFO_DATA, rx_data_buff, 3 );
    sample->element_1 = rx_data_buff[ 0 ];
    sample->element_1 <<= 8;
    sample->element_1 |= rx_data_buff[ 1 ];
    sample->element_1 <<= 8;
    sample->element_1 |= rx_data_buff[ 2 ];
    Delay_50us( );
    
    ecg6_read_data_buf( ctx, ECG6_REG_FIFO_DATA, rx_data_buff, 3 );
    sample->element_2 = rx_data_buff[ 0 ];
    sample->element_2 <<= 8;
    sample->element_2 |= rx_data_buff[ 1 ];
    sample->element_2 <<= 8;
    sample->element_2 |= rx_data_buff[ 2 ];
    Delay_50us( );
    
    ecg6_read_data_buf( ctx, ECG6_REG_FIFO_DATA, rx_data_buff, 3 );
    sample->element_3 = rx_data_buff[ 0 ];
    sample->element_3 <<= 8;
    sample->element_3 |= rx_data_buff[ 1 ];
    sample->element_3 <<= 8;
    sample->element_3 |= rx_data_buff[ 2 ];
    Delay_50us( );
    
    ecg6_read_data_buf( ctx, ECG6_REG_FIFO_DATA, rx_data_buff, 3 );
    sample->element_4 = rx_data_buff[ 0 ];
    sample->element_4 <<= 8;
    sample->element_4 |= rx_data_buff[ 1 ];
    sample->element_4 <<= 8;
    sample->element_4 |= rx_data_buff[ 2 ];
    Delay_50us( );
}

// ------------------------------------------------------------------------- END

