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
 * @file heartrate14.c
 * @brief Heart Rate 14 Click Driver.
 */

#include "heartrate14.h"

void heartrate14_cfg_setup ( heartrate14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->gpo = HAL_PIN_NC;
    cfg->gpi = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HEARTRATE14_DEVICE_ADDRESS;
}

err_t heartrate14_init ( heartrate14_t *ctx, heartrate14_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

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

    digital_out_init( &ctx->gpi, cfg->gpi );
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->gpo, cfg->gpo );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    /* Power on the sensor and allow time for the internal LDO to stabilize. */
    digital_out_high( &ctx->en );
    Delay_100ms( );

    return I2C_MASTER_SUCCESS;
}

err_t heartrate14_default_cfg ( heartrate14_t *ctx ) 
{
    err_t error_flag = HEARTRATE14_OK;

    /* Verify I2C communication by reading the part ID register. */
    if ( HEARTRATE14_ERROR == heartrate14_check_comm( ctx ) )
    {
        return HEARTRATE14_ERROR;
    }

    /* Software reset */
    error_flag |= heartrate14_sw_reset( ctx );
    Delay_100ms( );
                                        
    /* PPG Configuration 1 Register(0x11):
     *     bits[3:2] = 10 -> ADC full scale range 16384[nA] => LSB = 31.25[pA].  */
    error_flag |= heartrate14_write_reg( ctx, HEARTRATE14_REG_PPG_CFG1, HEARTRATE14_PPG_CFG1_ADC_RGE_16UA );

    /* PPG Configuration 2 Register(0x12):
     *     bits[7:3] = 00011 -> 100 samples per second
     *     bits[2:0] = 000   -> No averaging */
    error_flag |= heartrate14_write_reg( ctx, 
                                         HEARTRATE14_REG_PPG_CFG2,
                                         HEARTRATE14_PPG_CFG2_SR_100SPS |
                                         HEARTRATE14_PPG_CFG2_SMP_AVE_1 );

    /* Photo Diode Bias Register (0x15):
     *     bits[2:1] = 001 -> Smallest recommended setting, photo diode capacitance 0pF - 65pF.
     *                        Reset default (0x00) is not a recommended value per datasheet.*/
    error_flag |= heartrate14_write_reg( ctx, HEARTRATE14_REG_PD_BIAS, HEARTRATE14_PD_BIAS_0_65PF );

    /* LED sequence register 3(0x22):
     *     bits[7:4] = 00 -> LEDC6 time slot disabled
     *     bits[3:0] = 00 -> LEDC5 time slot disabled */
    error_flag |= heartrate14_write_reg( ctx, HEARTRATE14_REG_LED_SEQ3, HEARTRATE14_LED_SEQ3_DIS_LEDC56 );

    /* LED sequence register 2(0x21):
     *     bits[7:4] = 00 -> LEDC4 time slot disabled
     *     bits[3:0] = 00 -> LEDC3 time slot disabled */
    error_flag |= heartrate14_write_reg( ctx, HEARTRATE14_REG_LED_SEQ2, HEARTRATE14_LED_SEQ2_DIS_LEDC34 );

     /* LED sequence register 1(0x20):
      *    bits[7:4] = 00 -> LEDC2 time slot disabled => LED sequence stops after LEDC1 timeslot,each sample will
      *                                                  produce one 3-byte FIFO sample with TAG=0x01 (Green LED)
      *    bits[3:0] = 01 -> LEDC1 time slot enabled for Green LED (best for pulse measurement) */
    error_flag |= heartrate14_write_reg( ctx, 
                                         HEARTRATE14_REG_LED_SEQ1, 
                                         HEARTRATE14_LED_SEQ1_LEDC1_GREEN |
                                         HEARTRATE14_LED_SEQ1_LEDC2_NONE );

    /* LED range register (0x2A):
     *     bits[1:0] = 01 -> LED1 current range = 62[mA] => lsb = 0.24mA*/
    error_flag |= heartrate14_write_reg( ctx, HEARTRATE14_REG_LED_RANGE, HEARTRATE14_LED1_RGE_62MA );

    /* LED pulse amplitude registers(0x23-0x25):
     * Choose nominal current from previously set current range.
     *     LED2, LED3: disabled 
     *     LED1_PA = 0x1F → nominal current FOR LED1 = 0x1F * 0.24mA = 7.44mA */
    error_flag |= heartrate14_write_reg( ctx, HEARTRATE14_REG_LED1_PA, HEARTRATE14_LED1_PA_7P5MA );
    error_flag |= heartrate14_write_reg( ctx, HEARTRATE14_REG_LED2_PA, HEARTRATE14_LED2_PA_OFF );
    error_flag |= heartrate14_write_reg( ctx, HEARTRATE14_REG_LED3_PA, HEARTRATE14_LED3_PA_OFF );

    /* FIFO Configuration 2 register (0x0A):
     *     bit[1] = 1 -> FIFO automatically rolls over when full */
    error_flag |= heartrate14_write_reg( ctx, HEARTRATE14_REG_FIFO_CFG2, HEARTRATE14_FIFO_CFG2_FIFO_RO );

    /* Interrupt enable 1 register (0x02):
     *     bit[6] = 1 -> Enable DATA_RDY interrupt */
    error_flag |= heartrate14_write_reg( ctx, HEARTRATE14_REG_INT_ENABLE1, HEARTRATE14_INT1_DATA_RDY );

    /* System control register (0x0D):
     *     bit[3] = 1 -> Only PPG1 channel is enabled(one photo diode, one adc) */
    error_flag |= heartrate14_write_reg( ctx, HEARTRATE14_REG_SYS_CTRL, HEARTRATE14_SYS_CTRL_SINGLE_PPG );

    Delay_100ms( );

    return error_flag;
}

err_t heartrate14_write_reg ( heartrate14_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return heartrate14_write_regs( ctx, reg, &data_in, 1 );
}

err_t heartrate14_write_regs ( heartrate14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    /* S | slave_addr + W | A | reg_addr | A | data0 | A | ... dataN | A | P */
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t heartrate14_read_reg ( heartrate14_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return heartrate14_read_regs( ctx, reg, data_out, 1 );
}

err_t heartrate14_read_regs ( heartrate14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    /* S | slave_addr + W | A | reg_addr | RS | slave_addr + R | A | dummy0 | A | ... dummyN | NA | P */
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t heartrate14_check_comm ( heartrate14_t *ctx )
{
    uint8_t part_id = 0;

    /* Read part ID register(0xFF), expected value is 0x36 */
    if ( HEARTRATE14_OK == heartrate14_read_reg( ctx, HEARTRATE14_REG_PART_ID, &part_id ) )
    {
        if ( HEARTRATE14_PART_ID == part_id )
        {
            return HEARTRATE14_OK;
        }
    }
    return HEARTRATE14_ERROR;
}

err_t heartrate14_sw_reset ( heartrate14_t *ctx )
{
    /* Perform software reset by setting the RESET bit(bit 0) of System Control register(0x0D). */
    return heartrate14_write_reg( ctx, HEARTRATE14_REG_SYS_CTRL, HEARTRATE14_SYS_CTRL_RESET );
}

void heartrate14_enable_device ( heartrate14_t *ctx )
{
    digital_out_high( &ctx->en );
}

void heartrate14_disable_device ( heartrate14_t *ctx )
{
    digital_out_low( &ctx->en );
}

uint8_t heartrate14_get_int_pin ( heartrate14_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t heartrate14_get_gpo_pin ( heartrate14_t *ctx )
{
    return digital_in_read( &ctx->gpo );
}

void heartrate14_set_gpi_pin ( heartrate14_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->gpi, state );
}

err_t heartrate14_flush_fifo ( heartrate14_t *ctx )
{
    uint8_t reg_data = 0;

    /* Flush FIFO by setting FLUSH_FIFO bit(bit 4) of FIFO Configuration 2 register (0x0A).
     * Use read-modify-write sequence to avoid affecting other bits. */
    err_t error_flag = heartrate14_read_reg( ctx, HEARTRATE14_REG_FIFO_CFG2, &reg_data );
    reg_data |= HEARTRATE14_FIFO_CFG2_FLUSH;
    error_flag |= heartrate14_write_reg( ctx, HEARTRATE14_REG_FIFO_CFG2, reg_data );

    return error_flag;
}

err_t heartrate14_wait_data_ready ( heartrate14_t *ctx )
{
    uint32_t timeout_cnt = HEARTRATE14_TIMEOUT_MS;
    uint8_t int_status = 0;

    /* Poll INT pin */
    while ( heartrate14_get_int_pin( ctx ) )
    {
        if ( 0 == timeout_cnt-- )
        {
            return HEARTRATE14_ERROR;
        }
        Delay_1ms( );
    }

    /* Reading Interrupt Status register(0x00) clears all interrupt flags and deasserts INT pin. */
    return heartrate14_read_reg( ctx, HEARTRATE14_REG_INT_STATUS1, &int_status );
}

err_t heartrate14_get_fifo_data ( heartrate14_t *ctx, heartrate14_fifo_data_t *fifo_data )
{
    /* Each FIFO item is a 3-byte sample:
     *    sample[23:19] = TAG (identifies which timestamp(LEDCx) the sample corresponds to)
     *    sample[18:0]  = ADC data (19-bit unsigned integer). */
    err_t error_flag = HEARTRATE14_OK;
    uint8_t fifo_buf[ HEARTRATE14_FIFO_BYTES_PER_SAMPLE ] = { 0 };
    uint32_t raw_data = 0;
    uint8_t tag = 0;

    /* Wait for a valid data in FIFO */
    error_flag |= heartrate14_wait_data_ready( ctx );
    if ( HEARTRATE14_ERROR == error_flag )
    {
        return HEARTRATE14_ERROR;
    }

    /* Read one 3-byte sample in FIFO from FIFO data register (0x08).
     * I2C autoincrement is disabled when reading this register,however an 
     * internal FIFO pointer is used to keep track of the current position.*/
    error_flag |= heartrate14_read_regs( ctx, HEARTRATE14_REG_FIFO_DATA, fifo_buf, HEARTRATE14_FIFO_BYTES_PER_SAMPLE );
    
    /* Parse the raw data */
    raw_data = ( ( uint32_t ) fifo_buf[ 0 ] << 16 ) |
               ( ( uint32_t ) fifo_buf[ 1 ] << 8 )  |
               ( ( uint32_t ) fifo_buf[ 2 ] );

    tag = ( uint8_t ) ( ( raw_data >> 19 ) & HEARTRATE14_FIFO_TAG_MASK );

    switch ( tag )
    {
        case HEARTRATE14_FIFO_TAG_LEDC1:
            fifo_data->ledc1 = raw_data & HEARTRATE14_FIFO_ADC_MASK;
            break;
        case HEARTRATE14_FIFO_TAG_LEDC2:
            fifo_data->ledc2 = raw_data & HEARTRATE14_FIFO_ADC_MASK;
            break;
        case HEARTRATE14_FIFO_TAG_LEDC3:
            fifo_data->ledc3 = raw_data & HEARTRATE14_FIFO_ADC_MASK;
            break;
        case HEARTRATE14_FIFO_TAG_INVALID:
            return HEARTRATE14_ERROR;
        default:
            /* LEDC4-LEDC6 (0x04-0x06), TIMESTAMP (0x1F) - ignore */
            break;
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
