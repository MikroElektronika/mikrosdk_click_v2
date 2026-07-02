/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file adc28.c
 * @brief ADC 28 Click Driver.
 */

#include "adc28.h"

void adc28_cfg_setup ( adc28_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ADC28_DEVICE_ADDRESS;
}

err_t adc28_init ( adc28_t *ctx, adc28_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    ctx->vdd = ADC28_VDD_3V3;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_in_init( &ctx->alt, cfg->alt );

    return I2C_MASTER_SUCCESS;
}

err_t adc28_default_cfg ( adc28_t *ctx ) 
{
    err_t error_flag = ADC28_OK;

    /* Software reset and I2C address update */
    error_flag |= adc28_write_reg( ctx, ADC28_REG_GENERAL_CFG, ADC28_GENERAL_CFG_RST );
    Delay_10ms( );

    /* Enable LAST_VALUE to be updated in addresses A0-AF.
     * Required for Autonomous Mode results to be stored and readable */
    error_flag |= adc28_write_reg( ctx, ADC28_REG_GENERAL_CFG, ADC28_GENERAL_CFG_STATS_EN );

    /* Set conversion time to 1.2us */
    error_flag |= adc28_write_reg( ctx, ADC28_REG_BUSY_CFG, ADC28_BUSY_CFG_BUSYTIME_1_2US );

    /* Select all 8 channels for Autonomous Mode */
    error_flag |= adc28_write_reg( ctx, ADC28_REG_AUTO_SEQ_CH_SEL, ADC28_AUTO_SEQ_ALL_CH );

    /* OPMODE_CFG register:
     *    bit[6:5] = 01 -> Autonomous Mode
     *    bit[1:0] = 00 -> 0.75ms interval at Autonomous Mode */
    error_flag |= adc28_write_reg( ctx, ADC28_REG_OPMODE_CFG, 
                                        ADC28_OPMODE_CFG_CONV_MODE_AUTO | 
                                        ADC28_OPMODE_CFG_CLK_DIV_0_75MS );

    /* SEQUENCE_CFG register:
     *    bit[1:0] = 01 -> select Auto Sequence Mode or Autonomous Mode 
     *    bit[4]   = 1  -> start channel sequencer */
    error_flag |= adc28_write_reg( ctx, ADC28_REG_SEQUENCE_CFG, 
                                        ADC28_SEQUENCE_CFG_SEQ_MODE_AUTO | 
                                        ADC28_SEQUENCE_CFG_SEQ_START );

    Delay_10ms( );

    return error_flag;
}

err_t adc28_write_reg ( adc28_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return adc28_write_regs( ctx, reg, &data_in, 1 );
}

err_t adc28_write_regs ( adc28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    /* S | addr + W | A | OPCODE 0x28 | A | reg_addr | A | data[0] | A | ... | A | P */
    uint8_t data_buf[ 258 ] = { 0 };
    data_buf[ 0 ] = ADC28_OPCODE_BLOCK_WRITE;
    data_buf[ 1 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 2 );
}

err_t adc28_read_reg ( adc28_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return adc28_read_regs( ctx, reg, data_out, 1 );
}

err_t adc28_read_regs ( adc28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    /* S | addr + W | A | OPCODE 0x30 | A | reg_addr | A | Sr | addr + R | A | DUMMY | A | ... | P 
     * Works with STOP then START instead of REPEATED START as well */
    err_t error_flag = ADC28_OK;
    uint8_t cmd_buf[ 2 ] = { ADC28_OPCODE_BLOCK_READ, reg };
    error_flag = i2c_master_write( &ctx->i2c, cmd_buf, 2 );
    error_flag |= i2c_master_read( &ctx->i2c, data_out, len );

    return error_flag;
}

uint8_t adc28_get_alert_pin ( adc28_t *ctx )
{
    return digital_in_read( &ctx->alt );
}

err_t adc28_set_high_threshold ( adc28_t *ctx, uint8_t channel, uint16_t high_th )
{
    uint8_t base_reg = 0;
    uint8_t hyst_reg = 0;
    err_t error_flag = ADC28_OK;

    if ( ( channel > ADC28_CHANNEL_7 ) || ( high_th > ADC28_THRESHOLD_LIMIT ) )
    {
        return ADC28_ERROR;
    }
    
    /* Each channel has 4 consecutive bytes for hysteresis, high/low threshold and event count:
     *    LSB_LOW[3:0]  = Hysteresis
     *    LSB_LOW[7:4]  = HIGH_THR D[3:0]
     *    LSB_HIGH[7:0] = HIGH_THR D[11:4]
     *    MSB_LOW[3:0]  = EVENT_COUNT
     *    MSB_LOW[7:4]  = LOW_THR D[3:0]
     *    MSB_HIGH[7:0] = LOW_THR D[11:4]
     * make sure to save current hysteresis value when updating high threshold */
    base_reg = ADC28_REG_HYSTERESIS_CH0 + ( channel * 4 );
    error_flag = adc28_read_reg( ctx, base_reg, &hyst_reg );
    hyst_reg = ( hyst_reg & ADC28_HYSTERESIS_MASK ) | ( uint8_t ) ( ( high_th & ADC28_4_LSB_MASK ) << 4 );
    error_flag |= adc28_write_reg( ctx, base_reg, hyst_reg );
    error_flag |= adc28_write_reg( ctx, base_reg + 1, ( uint8_t ) ( ( high_th >> 4 ) & ADC28_HIGH_THR_MSB_MASK ) );

    return error_flag;
}

err_t adc28_set_low_threshold ( adc28_t *ctx, uint8_t channel, uint16_t low_th )
{
    uint8_t base_reg = 0;
    uint8_t cnt_reg = 0;
    err_t error_flag = ADC28_OK;

    if ( ( channel > ADC28_CHANNEL_7 ) || ( low_th > ADC28_THRESHOLD_LIMIT ) )
    {
        return ADC28_ERROR;
    }

    /* Each channel has 4 consecutive bytes for hysteresis, high/low threshold and event count:
     *    LSB_LOW[3:0]  = Hysteresis
     *    LSB_LOW[7:4]  = HIGH_THR D[3:0]
     *    LSB_HIGH[7:0] = HIGH_THR D[11:4]
     *    MSB_LOW[3:0]  = EVENT_COUNT
     *    MSB_LOW[7:4]  = LOW_THR D[3:0]
     *    MSB_HIGH[7:0] = LOW_THR D[11:4]
     * make sure to save current event count value when updating low threshold */
    base_reg = ADC28_REG_HYSTERESIS_CH0 + ( channel * 4 );
    error_flag = adc28_read_reg( ctx, base_reg + 2, &cnt_reg );
    cnt_reg = ( cnt_reg & ADC28_EVENT_COUNT_MASK ) | ( uint8_t ) ( ( low_th & ADC28_4_LSB_MASK ) << 4 );
    error_flag |= adc28_write_reg( ctx, base_reg + 2, cnt_reg );
    error_flag |= adc28_write_reg( ctx, base_reg + 3, ( uint8_t ) ( ( low_th >> 4 ) & ADC28_LOW_THR_MSB_MASK ) );

    return error_flag;
}

err_t adc28_set_hysteresis ( adc28_t *ctx, uint8_t channel, uint8_t hysteresis )
{
    uint8_t base_reg = 0;
    uint8_t hyst_reg = 0;
    err_t error_flag = ADC28_OK;

    if ( ( channel > ADC28_CHANNEL_7 ) || ( hysteresis > ADC28_HYSTERESIS_LIMIT ) )
    {
        return ADC28_ERROR;
    }

    /* Each channel has 4 consecutive bytes for hysteresis, high/low threshold and event count:
     *    LSB_LOW[3:0]  = Hysteresis
     *    LSB_LOW[7:4]  = HIGH_THR D[3:0]
     *    LSB_HIGH[7:0] = HIGH_THR D[11:4]
     *    MSB_LOW[3:0]  = EVENT_COUNT
     *    MSB_LOW[7:4]  = LOW_THR D[3:0]
     *    MSB_HIGH[7:0] = LOW_THR D[11:4]
     * make sure to save current high threshold nibble when updating hysteresis */
    base_reg = ADC28_REG_HYSTERESIS_CH0 + ( channel * 4 );
    error_flag = adc28_read_reg( ctx, base_reg, &hyst_reg );
    hyst_reg = ( hyst_reg & ADC28_HIGH_THR_LSB_MASK ) | ( hysteresis & ADC28_HYSTERESIS_MASK );
    error_flag |= adc28_write_reg( ctx, base_reg, hyst_reg );

    return error_flag;
}

err_t adc28_set_event_count ( adc28_t *ctx, uint8_t channel, uint8_t event_count )
{
    uint8_t base_reg = 0;
    uint8_t cnt_reg = 0;
    err_t error_flag = ADC28_OK;

    if ( ( channel > ADC28_CHANNEL_7 ) || ( event_count > ADC28_EVENT_COUNT_LIMIT ) )
    {
        return ADC28_ERROR;
    }

    /* Each channel has 4 consecutive bytes for hysteresis, high/low threshold and event count:
     *    LSB_LOW[3:0]  = Hysteresis
     *    LSB_LOW[7:4]  = HIGH_THR D[3:0]
     *    LSB_HIGH[7:0] = HIGH_THR D[11:4]
     *    MSB_LOW[3:0]  = EVENT_COUNT
     *    MSB_LOW[7:4]  = LOW_THR D[3:0]
     *    MSB_HIGH[7:0] = LOW_THR D[11:4]
     * make sure to save current low threshold nibble when updating event count */
    base_reg = ADC28_REG_HYSTERESIS_CH0 + ( channel * 4 );
    error_flag = adc28_read_reg( ctx, base_reg + 2, &cnt_reg );
    cnt_reg = ( cnt_reg & ADC28_LOW_THR_LSB_MASK ) | ( event_count & ADC28_EVENT_COUNT_MASK );
    error_flag |= adc28_write_reg( ctx, base_reg + 2, cnt_reg );

    return error_flag;
}

err_t adc28_read_raw_adc ( adc28_t *ctx, uint8_t channel, uint16_t *raw_data )
{
    err_t error_flag = ADC28_OK;
    uint8_t lsb = 0;
    uint8_t msb = 0;
    uint8_t lsb_reg = 0;

    if ( ( channel > ADC28_CHANNEL_7 ) || ( NULL == raw_data ) )
    {
        return ADC28_ERROR;
    }

    /* calculate LSB reg address:
     * Each channel occupies 2 bytes (LSB,MSB) for storing the result.
     * MSB register bits[7:0] + LSB register bits[7:4]. 
     * Channel 0 LSB is at the lowest address. */
    lsb_reg = ADC28_REG_RECENT_CH0_LSB + ( channel * 2 );

    /* Read LSB and MSB registers for the selected channel */
    error_flag |= adc28_read_reg( ctx, lsb_reg, &lsb );
    error_flag |= adc28_read_reg( ctx, lsb_reg + 1, &msb );

    if ( ADC28_OK == error_flag )
    {
        /* Reconstruct 12-bit result: D[11:4] from MSB, D[3:0] from LSB[7:4] */
        *raw_data = ( ( uint16_t ) msb << 4 ) | ( lsb >> 4 );
    }

    return error_flag;
}

err_t adc28_read_voltage ( adc28_t *ctx, uint8_t channel, float *voltage )
{
    err_t error_flag = ADC28_OK;
    uint16_t raw_data = 0;

    if ( NULL == voltage )
    {
        return ADC28_ERROR;
    }

    error_flag |= adc28_read_raw_adc( ctx, channel, &raw_data );

    if ( ADC28_OK == error_flag )
    {
        /* LSB = VDD / resolution 
         * voltage = raw * LSB */
        *voltage = ( float ) raw_data * ctx->vdd / ADC28_ADC_RESOLUTION;
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
