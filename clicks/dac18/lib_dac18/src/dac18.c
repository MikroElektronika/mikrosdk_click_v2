/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file dac18.c
 * @brief DAC 18 Click Driver.
 */

#include "dac18.h"

void dac18_cfg_setup ( dac18_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->gp2 = HAL_PIN_NC;
    cfg->mod = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    cfg->gp0 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DAC18_DEVICE_ADDRESS_VCC;
}

err_t dac18_init ( dac18_t *ctx, dac18_cfg_t *cfg ) 
{
    digital_out_init( &ctx->mod, cfg->mod );
    dac18_set_mode( ctx, DAC18_MODE_CONFIGURATION );
    Delay_100ms( );
    
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

   digital_in_init( &ctx->gp2, cfg->gp2 );
   digital_in_init( &ctx->gp1, cfg->gp1 );
   digital_in_init( &ctx->gp0, cfg->gp0 );

    return I2C_MASTER_SUCCESS;
}

err_t dac18_default_cfg ( dac18_t *ctx ) 
{
    err_t err_flag = DAC18_OK;

    // Set configuration mode
    dac18_set_mode( ctx, DAC18_MODE_CONFIGURATION );
    Delay_100ms( );

    uint16_t device_id = 0;
    err_flag |= dac18_register_read( ctx, DAC18_REG_GENERAL_STATUS, &device_id );
    device_id &= DAC18_GEN_STATUS_DEVICE_ID_BITMASK;
    device_id >>= 2;
    if ( DAC18_GEN_STATUS_DEVICE_ID == device_id )
    {
        // Stop the state machine
        err_flag |= dac18_register_write( ctx, DAC18_REG_STATE_MACHINE_CONFIG, 
                                               DAC18_STATE_M_CFG_SM_STOP );
        Delay_100ms( );

        // Start the function generator
        err_flag |= dac18_register_write( ctx, DAC18_REG_FUNCTION_TRIGGER, 
                                               DAC18_FUNCTION_TRG_STOP );
        Delay_10ms( );
        
        // Set the code step, slew rate, and waveform mode (SRAM)
        err_flag |= dac18_cfg_pwm_out( ctx, DAC18_FUN_CFG_F_SEL_TRIANGULAR, 
                                            DAC18_FUN_CFG_C_STEP_1LSB, 
                                            DAC18_FUN_CFG_T_STEP_8_US );
        Delay_10ms( );
        err_flag |= dac18_set_dac_code( ctx, DAC18_DAC_CODE_MAX_DEFAULT, 
                                             DAC18_DAC_CODE_MIN_DEFAULT );
        Delay_10ms( );

        // Set the programmable debounce delay (SRAM)
        err_flag |= dac18_set_debounce_delay( ctx, DAC18_GPI_DEBOUNCE_50_MS );
        Delay_10ms( );

        // Set the LUT values (SRAM)
        err_flag |= dac18_register_write( ctx, DAC18_SRAM_REG_VOUT_DATA_0, 
                                               DAC18_LUT_DEFAULT_VOUT_DATA_0 );
        Delay_10ms( );
        err_flag |= dac18_register_write( ctx, DAC18_SRAM_REG_VOUT_DATA_1, 
                                               DAC18_LUT_DEFAULT_VOUT_DATA_1 );
        Delay_10ms( );
        err_flag |= dac18_register_write( ctx, DAC18_SRAM_REG_VOUT_DATA_2, 
                                               DAC18_LUT_DEFAULT_VOUT_DATA_2 );
        Delay_10ms( );
        err_flag |= dac18_register_write( ctx, DAC18_SRAM_REG_VOUT_DATA_3, 
                                               DAC18_LUT_DEFAULT_VOUT_DATA_3 );
        Delay_10ms( );
        err_flag |= dac18_register_write( ctx, DAC18_SRAM_REG_VOUT_DATA_4, 
                                               DAC18_LUT_DEFAULT_VOUT_DATA_4 );
        Delay_10ms( );
        err_flag |= dac18_register_write( ctx, DAC18_SRAM_REG_VOUT_DATA_5, 
                                               DAC18_LUT_DEFAULT_VOUT_DATA_5 );
        Delay_10ms( );
        err_flag |= dac18_register_write( ctx, DAC18_SRAM_REG_VOUT_DATA_6, 
                                               DAC18_LUT_DEFAULT_VOUT_DATA_6 );
        Delay_10ms( );
        err_flag |= dac18_register_write( ctx, DAC18_SRAM_REG_VOUT_DATA_7, 
                                               DAC18_LUT_DEFAULT_VOUT_DATA_7 );
        Delay_10ms( );

        // Set the channel 0 reference to VDD
        err_flag |= dac18_register_write( ctx, DAC18_REG_DAC0_VOUT_CMP_CONFIG, 
                                               DAC18_DACX_VOUT_CFG_GAIN_X1 );
        Delay_10ms( );

        // Set channel 1 reference to VDD
        err_flag |= dac18_register_write( ctx, DAC18_REG_DAC1_VOUT_CMP_CONFIG, 
                                               DAC18_DACX_VOUT_CFG_GAIN_X1 );
        Delay_10ms( );

        // Power on the DAC channels
        err_flag |= dac18_register_write( ctx, DAC18_REG_COMMON_CONFIG, 
                                              DAC18_COMMON_CFG_DEFAULT );
        Delay_10ms( );

        // Set the device mode
        err_flag |= dac18_register_write( ctx, DAC18_REG_DEVICE_MODE_CONFIG, 
                                               DAC18_DEV_MODE_CFG_DEFAULT | 
                                               DAC18_DEV_MODE_CFG_EN | 
                                               DAC18_DEV_MODE_CFG_SM_IO_EN );
        Delay_10ms( );

        // Start the state machine
        err_flag |= dac18_register_write( ctx, DAC18_REG_STATE_MACHINE_CONFIG, 
                                               DAC18_STATE_M_CFG_SM_START | 
                                               DAC18_STATE_M_CFG_SM_EN );
        Delay_10ms( );

        // Save settings to NVM
        err_flag |= dac18_register_write( ctx, DAC18_REG_COMMON_TRIGGER, 
                                               DAC18_COMMON_TRG_NVM_PROG );
        Delay_10ms( );

        dac18_set_mode( ctx, DAC18_MODE_STANDALONE );
        Delay_10ms( );
    }
    else
    {
        err_flag = DAC18_ERROR;
    }
    return err_flag;
}

err_t dac18_generic_write ( dac18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t dac18_generic_read ( dac18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t dac18_register_write ( dac18_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in >> 8 );
    data_buf[ 1 ] = ( uint8_t ) data_in;
    return dac18_generic_write( ctx, reg, data_buf, 2 );
}

err_t dac18_register_read ( dac18_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = dac18_generic_read( ctx, reg, data_buf, 2 );
    *data_out = data_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 1 ];
    return err_flag;
}

err_t dac18_cfg_pwm_out ( dac18_t *ctx, uint8_t f_sel, uint8_t c_step, uint8_t t_step ) 
{
    err_t err_flag = DAC18_ERROR;
    if ( ( ( DAC18_FUN_CFG_F_SEL_TRIANGULAR == f_sel )   || 
           ( DAC18_FUN_CFG_F_SEL_SAWTOOTH == f_sel )     || 
           ( DAC18_FUN_CFG_F_SEL_INV_SAWTOOTH == f_sel ) || 
           ( DAC18_FUN_CFG_F_SEL_DISABLE == f_sel ) ) && 
           ( DAC18_FUN_CFG_C_STEP_32LSB >= c_step ) && 
           ( ( DAC18_FUN_CFG_T_STEP_5127_92_US >= t_step ) || 
             ( DAC18_FUN_CFG_T_STEP_INVALID != t_step ) ) )
    {
        uint16_t data_buf = 0;
        data_buf |= ( ( uint16_t ) f_sel )  << 8;
        data_buf |= ( ( uint16_t ) c_step ) << 4;
        data_buf |=   ( uint16_t ) t_step;
        err_flag = dac18_register_write( ctx, DAC18_SRAM_REG_FUNCTION_CONFIG, data_buf );
    }
    return err_flag;
}

err_t dac18_set_dac_code ( dac18_t *ctx, uint16_t max_dc, uint16_t min_dc ) 
{
    err_t err_flag = DAC18_ERROR;
    if ( ( DAC18_DAC_CODE_12BIT_MAX >= max_dc ) && 
         ( DAC18_DAC_CODE_12BIT_MAX >= min_dc ) && 
         ( max_dc >= min_dc ) )
    {
        max_dc <<= 5;
        min_dc <<= 5;
        err_flag = dac18_register_write( ctx, DAC18_SRAM_REG_FUNCTION_MAX, max_dc );
        err_flag |= dac18_register_write( ctx, DAC18_SRAM_REG_FUNCTION_MIN, min_dc );
    }
    return err_flag;
}

err_t dac18_set_debounce_delay ( dac18_t *ctx, float delay_ms ) 
{
    err_t err_flag = DAC18_ERROR;
    if ( DAC18_GPI_DEBOUNCE_MAX > delay_ms )
    {
        err_flag = dac18_register_write( ctx, DAC18_SRAM_REG_GPI_DEBOUNCE, 
                                             ( uint16_t ) ( delay_ms / DAC18_GPI_DEBOUNCE_SENS ) );
    }
    return err_flag;
}

void dac18_set_mode ( dac18_t *ctx, uint8_t mode ) 
{
    digital_out_write( &ctx->mod, mode );
}

uint8_t dac18_get_gp0 ( dac18_t *ctx ) 
{
    return digital_in_read( &ctx->gp0 );
}

uint8_t dac18_get_gp1 ( dac18_t *ctx ) 
{
    return digital_in_read( &ctx->gp1 );
}

uint8_t dac18_get_gp2 ( dac18_t *ctx ) 
{
    return digital_in_read( &ctx->gp2 );
}

void dac18_get_gpi_status ( dac18_t *ctx, uint8_t *gpi_status ) 
{
    *gpi_status = dac18_get_gp2( ctx );
    *gpi_status <<= 1;
    *gpi_status |= dac18_get_gp1( ctx );
    *gpi_status <<= 1;
    *gpi_status |= dac18_get_gp0( ctx );
}

// ------------------------------------------------------------------------- END
