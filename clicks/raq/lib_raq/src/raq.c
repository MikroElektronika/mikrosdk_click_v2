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
 * @file raq.c
 * @brief RAQ Click Driver.
 */

#include "raq.h"

/* ------------------------------------------------------------------------
 * Continuous measurement configuration datasets
 * These vendor-defined byte sequences configure the sensor sequencer
 * for continuous operation mode (written to 0x50 / 0x60 / 0x68).
 * ------------------------------------------------------------------------ */
static uint8_t raq_data_set_4450_continuous_1[ RAQ_CONT_DS1_LEN ] = { 0x20, 0x04, 0x40, 0x09 };
static uint8_t raq_data_set_4450_continuous_2[ RAQ_CONT_DS2_LEN ] = { 0x03 };
static uint8_t raq_data_set_4450_continuous_3[ RAQ_CONT_DS3_LEN ] = { 0x00, 0x00, 0x80, 0x08 };

/* ------------------------------------------------------------------------
 * Sensor initialization datasets
 * Vendor-defined initialization sequences used during sensor INIT flow
 * to enable calibration and extraction of MOX_LR / MOX_ER parameters
 * (written to 0x50 / 0x60 / 0x68).
 * ------------------------------------------------------------------------ */
static uint8_t raq_data_set_4450i_1[ RAQ_INIT_DS1_LEN ] = { 0x00, 0x28 };
static uint8_t raq_data_set_4450i_2[ RAQ_INIT_DS2_LEN ] = { 0xC3, 0xE3 };
static uint8_t raq_data_set_4450i_3[ RAQ_INIT_DS3_LEN ] = { 0x00, 0x00, 0x80, 0x40  };

void raq_cfg_setup ( raq_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RAQ_DEVICE_ADDRESS;
}

err_t raq_init ( raq_t *ctx, raq_cfg_t *cfg )
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    /* leave reset state */
    digital_out_high( &ctx->rst );

    /* init cache */
    ctx->mox_lr = 0;
    ctx->mox_er = 0;
    ctx->calib_valid = false;

    return I2C_MASTER_SUCCESS;
}

err_t raq_generic_write ( raq_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t raq_generic_read ( raq_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void raq_hw_reset ( raq_t *ctx )
{
    /* Hardware reset via RST pin */
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

err_t raq_get_sensor_info ( raq_t *ctx, raq_info_t *info )
{
    uint8_t rx_pid[ RAQ_LEN_PID ] = { 0 };
    uint8_t status = 0;
    uint16_t n_cnt = 0;

    if ( NULL == info )
    {
        return RAQ_ERROR_SENSOR;
    }

    /* wait for the sensor to finish current sequence by writing RAQ_CMD_STOP(0x00) until status bit7 clears. */
    do
    {
        uint8_t cmd = RAQ_CMD_STOP;

        if ( I2C_MASTER_SUCCESS != raq_generic_write( ctx, RAQ_REG_CMD, &cmd, 1 ) )
        {
            return RAQ_ERROR_I2C;
        }

        Delay_100ms( );
        Delay_100ms( );

        status = raq_get_status( ctx );
        n_cnt++;
    }
    while ( ( status & RAQ_STATUS_SEQUENCER_RUNNING_MASK ) && ( n_cnt < RAQ_GAS_INIT_TIMEOUT_CNT ) );
    
    /* read product ID (2 Bytes)  */
    if ( I2C_MASTER_SUCCESS != raq_generic_read( ctx, RAQ_REG_PID, rx_pid, 2 ) )
    {
        return RAQ_ERROR_I2C;
    }

    info->pid = ( ( uint16_t ) rx_pid[ 0 ] << 8 ) | rx_pid[ 1 ];
    
    /* Read factory configuration, CONF bytes [2..5] (used later for HSPF calibration coefficient calculation). */
    if ( I2C_MASTER_SUCCESS != raq_generic_read( ctx, RAQ_REG_CONF, info->conf, RAQ_LEN_CONF ) )
    {
        return RAQ_ERROR_I2C;
    }

    /* Read production data containing calibration coefficients used for sensor initialization. */
    if ( I2C_MASTER_SUCCESS != raq_generic_read( ctx, RAQ_REG_PROD_DATA, info->prod_data, RAQ_LEN_PROD_DATA ) )
    {
        return RAQ_ERROR_I2C;
    }

    if ( n_cnt >= RAQ_GAS_INIT_TIMEOUT_CNT )
    {
        return RAQ_ERROR_GAS_TIMEOUT;
    }

    return RAQ_OK;
}

err_t raq_init_sensor ( raq_t *ctx, uint16_t *mox_lr, uint16_t *mox_er )
{
    uint8_t buf[ RAQ_LEN_WORK_BUF ] = { 0 };
    uint8_t rx_cfg[ RAQ_LEN_CONF ] = { 0 }; 

    if ( ( NULL == mox_lr ) || ( NULL == mox_er ) )
    {
        return RAQ_ERROR_SENSOR;
    }

    /* read one Byte from address RAQ_REG_ERR(0xB7), will not be nedded later */
    uint8_t dummy = 0;

    if ( I2C_MASTER_SUCCESS != raq_generic_read( ctx, RAQ_REG_ERR, &dummy, 1 ) )
    {
        return RAQ_ERROR_I2C;
    }
    
    /* Read factory configuration, CONF bytes [2..5] (used for HSPF calibration coefficient calculation). */
    if ( I2C_MASTER_SUCCESS != raq_generic_read( ctx, RAQ_REG_CONF, rx_cfg, RAQ_LEN_CONF ) )
    {
        return RAQ_ERROR_I2C;
    }

    float hspf = ( -( ( float ) rx_cfg[ 2 ] * 256.0f + ( float ) rx_cfg[ 3 ] ) *
                 ( ( ( float ) rx_cfg[ 4 ] + 640.0f ) * ( ( float ) rx_cfg[ 5 ] + 80.0f ) - 512000.0f ) )
                 / 12288000.0f;

    if ( ( hspf < RAQ_HSPF_MIN  ) || ( hspf > RAQ_HSPF_MAX  ) )
    {
        return RAQ_ERROR_INIT_OUT_OF_RANGE;
    }
        
    /* Convert computed HSPF coefficient to 16-bit and pack as big-endian (MSB first). */
    buf[ 0 ] = ( uint8_t ) ( ( ( uint16_t ) hspf >> 8 ) & 0xFF );
    buf[ 1 ] = ( uint8_t ) ( ( ( uint16_t ) hspf ) & 0xFF );

    if ( I2C_MASTER_SUCCESS != raq_generic_write( ctx, RAQ_REG_HSPF, buf, RAQ_LEN_HSPF ) )
    {
        return RAQ_ERROR_I2C;
    }
    
    /* Load vendor initialization datasets to RAM for init state. */
    if ( I2C_MASTER_SUCCESS != raq_generic_write( ctx, RAQ_REG_DATA_SET_1, raq_data_set_4450i_1, RAQ_INIT_DS1_LEN ) )
    {
        return RAQ_ERROR_I2C;
    }

    if ( I2C_MASTER_SUCCESS != raq_generic_write( ctx, RAQ_REG_DATA_SET_2, raq_data_set_4450i_2, RAQ_INIT_DS2_LEN ) )
    {
        return RAQ_ERROR_I2C;
    }

    if ( I2C_MASTER_SUCCESS != raq_generic_write( ctx, RAQ_REG_DATA_SET_3, raq_data_set_4450i_3, RAQ_INIT_DS3_LEN ) )
    {
        return RAQ_ERROR_I2C;
    }

    /* Start sequencer (INIT) */
    uint8_t cmd = RAQ_CMD_INIT;

    if ( I2C_MASTER_SUCCESS != raq_generic_write( ctx, RAQ_REG_CMD, &cmd, 1 ) )
    {
        return RAQ_ERROR_I2C;
    }

    /* Give it some time after start (POR + first run) */
    Delay_100ms( );
    
    /* wait for valid MOX_LR, MOX_ER after initialisation*/
    uint16_t timeout_ms = 5000;   
    uint8_t err_flag = 0;

    while ( timeout_ms-- )
    {
        /* Read error flags */
        if ( I2C_MASTER_SUCCESS == raq_generic_read( ctx, RAQ_REG_ERR, &err_flag, RAQ_LEN_ERR_FLAG ) )
        {
            if ( err_flag & RAQ_STATUS_ACCESS_CONFLICT_MASK )
            {
                return RAQ_ERROR_ACCESS_CONFLICT;
            }

            if ( err_flag & RAQ_STATUS_POR_EVENT_MASK )
            {
                return RAQ_ERROR_POR_EVENT;
            }
        }

        /* Read sensor specific parameters ( MOX_LR, MOX_ER ) */
        if ( I2C_MASTER_SUCCESS != raq_generic_read( ctx, RAQ_REG_MOX_PARAMS, buf, RAQ_LEN_MOX_PARAMS ) )
        {
            return RAQ_ERROR_I2C;
        }

        uint16_t mox_lr_val = ( ( uint16_t ) buf[ 0 ] << 8 ) | buf[ 1 ];
        uint16_t mox_er_val = ( ( uint16_t ) buf[ 2 ] << 8 ) | buf[ 3 ];

        /* Treat all-zeros / all-ones as "not ready yet" */
        if ( ( 0x0000 != mox_lr_val ) && ( 0xFFFF != mox_lr_val ) && 
             ( 0x0000 != mox_er_val ) && ( 0xFFFF != mox_er_val ) )
        {
            *mox_lr = mox_lr_val;
            *mox_er = mox_er_val;

            /* Cache into ctx */
            ctx->mox_lr = *mox_lr;
            ctx->mox_er = *mox_er;
            ctx->calib_valid = true;

            return RAQ_OK;
        }

        Delay_1ms( );
    }

    return RAQ_ERROR_GAS_TIMEOUT;
}

err_t raq_init_measurement ( raq_t *ctx )
{
    uint8_t buf[ RAQ_LEN_WORK_BUF ] = { 0 };
    uint8_t rx_cfg[ RAQ_LEN_CONF ] = { 0 };

    /* Read one Byte from RAQ_REG_ERR(0xB7), will not be nedded later */
    uint8_t dummy = 0;
    raq_generic_read( ctx, RAQ_REG_ERR, &dummy, 1 );
    
    /* Read factory configuration, CONF bytes [2..5] (used for HSPF calibration coefficient calculation). */
    if ( I2C_MASTER_SUCCESS != raq_generic_read( ctx, RAQ_REG_CONF, rx_cfg, RAQ_LEN_CONF ) )
    {
        return RAQ_ERROR_I2C;
    }

    float hspf = ( -( ( float ) rx_cfg[ 2 ] * 256.0f + ( float ) rx_cfg[ 3 ] ) *
                 ( ( ( float ) rx_cfg[ 4 ] + 640.0f ) * ( ( float ) rx_cfg[ 5 ] + 80.0f ) - 512000.0f ) )
                 / 12288000.0f;

    if ( ( hspf < RAQ_HSPF_MIN  ) || ( hspf > RAQ_HSPF_MAX  ) )
    {
        return RAQ_ERROR_INIT_OUT_OF_RANGE;
    }
        
    /* Convert computed HSPF coefficient to 16-bit and pack as big-endian (MSB first). */
    buf[ 0 ] = ( uint8_t ) ( ( ( uint16_t ) hspf >> 8 ) & 0xFF );
    buf[ 1 ] = ( uint8_t ) ( ( ( uint16_t ) hspf ) & 0xFF );

    /* write previously calculated hspf(2 Bytes) to address RAQ_REG_HSPF */
    if ( I2C_MASTER_SUCCESS != raq_generic_write( ctx, RAQ_REG_HSPF, buf, RAQ_LEN_HSPF ) )
    {
        return RAQ_ERROR_I2C;
    }

    /* Program sensor's internal configuration blocks for continuous measurement mode */
    if ( I2C_MASTER_SUCCESS != raq_generic_write( ctx, RAQ_REG_DATA_SET_1, raq_data_set_4450_continuous_1, RAQ_CONT_DS1_LEN ) )
    {
        return RAQ_ERROR_I2C;
    }

    if ( I2C_MASTER_SUCCESS != raq_generic_write( ctx, RAQ_REG_DATA_SET_2, raq_data_set_4450_continuous_2, RAQ_CONT_DS2_LEN ) )
    {
        return RAQ_ERROR_I2C;
    }

    if ( I2C_MASTER_SUCCESS != raq_generic_write( ctx, RAQ_REG_DATA_SET_3, raq_data_set_4450_continuous_3, RAQ_CONT_DS3_LEN ) )
    {
        return RAQ_ERROR_I2C;
    }

    return RAQ_OK;
}

err_t raq_start_measurement ( raq_t *ctx )
{
    /* start measurement by writing RAQ_CMD_START_CONT(0xC0) to 0x93 (CMD) */
    uint8_t cmd = RAQ_CMD_START_CONT;
    if ( I2C_MASTER_SUCCESS  != raq_generic_write( ctx, RAQ_REG_CMD, &cmd, RAQ_LEN_CMD ) )
    {
        return RAQ_ERROR_I2C;
    }
    return RAQ_OK;
}

uint8_t raq_get_status ( raq_t *ctx )
{
    uint8_t status_val = 0;
    if ( RAQ_OK != raq_generic_read( ctx, RAQ_REG_STATUS, &status_val, RAQ_LEN_STATUS ) )  
    {
        return 0;
    }
    return status_val;
}

err_t raq_read_rmox ( raq_t *ctx, float *r_mox, uint16_t mox_lr, uint16_t mox_er )
{
    uint8_t rx_cfg[ RAQ_LEN_CONF ] = { 0 };
    uint8_t buf2[ RAQ_LEN_ADC_RESULT ] = { 0 };
    uint8_t err_flag = 0;
    uint16_t adc_result = 0;

    if ( NULL == r_mox )
    {
        return RAQ_ERROR_SENSOR;
    }

    /* Read CONF */
    if ( I2C_MASTER_SUCCESS != raq_generic_read( ctx, RAQ_REG_CONF, rx_cfg, RAQ_LEN_CONF ) )
    {
        return RAQ_ERROR_I2C;
    }

    /* Read ADC result storred in RAQ_REG_ADC_RESULT */
    if ( I2C_MASTER_SUCCESS != raq_generic_read( ctx, RAQ_REG_ADC_RESULT, buf2, RAQ_LEN_ADC_RESULT ) )
    {
        return RAQ_ERROR_I2C;
    }
    
    /* Reconstruct 16-bit ADC result from MSB/LSB bytes (big-endian). */
    adc_result = ( ( uint16_t ) buf2[ 0 ] << 8 ) | buf2[ 1 ];

    /* Read error flags */
    if ( I2C_MASTER_SUCCESS != raq_generic_read( ctx, RAQ_REG_ERR, &err_flag, RAQ_LEN_ERR_FLAG ) )
    {
        return RAQ_ERROR_I2C;
    }

    /* If sensor reports access conflict / POR event -> dont compute */
    if ( err_flag & RAQ_STATUS_ACCESS_CONFLICT_MASK )
    {
        return RAQ_ERROR_ACCESS_CONFLICT;
    }

    if ( err_flag & RAQ_STATUS_POR_EVENT_MASK )
    {
        return RAQ_ERROR_POR_EVENT;
    }

    /* ADC sanity: if 0x0000 or 0xFFFF, treat as invalid data */
    if ( ( RAQ_ADC_INVALID_MIN == adc_result ) || ( RAQ_ADC_INVALID_MAX == adc_result ) )
    {
        return RAQ_ERROR_SENSOR;
    }

    /* calculate RMOX */
    float k_val = ( float ) mox_er / ( float ) mox_lr;
    float rmox_val = k_val * ( float ) adc_result;

    /* Sanity guard against overflowed or corrupted RMOX computation results. */
    if ( rmox_val > RAQ_RMOX_MAX_VALID )
    {
        return RAQ_ERROR_SENSOR;
    }

    *r_mox = rmox_val;

    return RAQ_OK;
}

err_t raq_cont_init ( raq_t *ctx )
{
    uint8_t status_val = 0;

    if ( RAQ_OK != raq_start_measurement( ctx ) )
    {
        return RAQ_ERROR_I2C;
    }

    /* Synchronize with the sensor state machine by waiting for step 0 for a start of a valid measurement cycle. */
    do
    {
        Delay_100ms( );
        status_val = raq_get_status( ctx );
    }
    while ( status_val & RAQ_STATUS_LAST_SEQ_STEP_MASK );

    return RAQ_OK;
}

err_t raq_cont_run ( raq_t *ctx, float *r_mox )
{
    uint8_t status_val = 0;
    float rmox_val = 0;

    if ( ( NULL == ctx ) || ( NULL == r_mox ) )
    {
        return RAQ_ERROR_SENSOR;
    }

    /* Init only once (calibration cache) */
    if ( false == ctx->calib_valid )
    {
        uint16_t tmp_lr = 0, tmp_er = 0;

        err_t ret = raq_init_sensor( ctx, &tmp_lr, &tmp_er );

        if ( RAQ_OK != ret )
        {
            return ret;   
        }
    }

    /* wait until sequencer reaches LAST step (new sample ready). */
    uint16_t timeout = 50;
    do
    {
        status_val = raq_get_status( ctx );

        if ( RAQ_LAST_SEQ_STEP == ( status_val & RAQ_STATUS_LAST_SEQ_STEP_MASK ) )
        {
            break;
        }
        
        /* avoid access conflict */
        Delay_100ms( );
    }
    while ( timeout-- );

    if ( 0 == timeout )
    {
        return RAQ_ERROR_GAS_TIMEOUT;
    }

    /* Read RMOX for that sample */
    err_t ret = raq_read_rmox( ctx, &rmox_val, ctx->mox_lr, ctx->mox_er );

    if ( RAQ_OK != ret )
    {
        return ret;
    }

    *r_mox = rmox_val;

    /* wait until sequencer returns to FIRST step (avoid re-reading same sample) */
    timeout = 50;
    do
    {
        status_val = raq_get_status( ctx );

        if ( RAQ_FIRST_SEQ_STEP == ( status_val & RAQ_STATUS_LAST_SEQ_STEP_MASK ) )
        {
            break;
        }
        
        /* avoid access conflict */
        Delay_100ms( );
    }
    while ( timeout-- );

    if ( 0 == timeout )
    {
        return RAQ_ERROR_GAS_TIMEOUT;
    }

    return RAQ_OK;
}

uint8_t raq_check_interrupt ( raq_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
