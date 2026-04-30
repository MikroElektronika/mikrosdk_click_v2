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
 * @file geomagnetic2.c
 * @brief GeoMagnetic 2 Click Driver.
 */

#include "geomagnetic2.h"

/**
 * @brief GeoMagnetic 2 OTP memory word indices setting.
 * @details Specified setting for OTP memory word indices of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_OTP_IDX_TEMP_OFF_SENS       0x0D
#define GEOMAGNETIC2_OTP_IDX_MAG_OFFSET_X        0x0E
#define GEOMAGNETIC2_OTP_IDX_MAG_OFFSET_Y        0x0F
#define GEOMAGNETIC2_OTP_IDX_MAG_OFFSET_Z        0x0E
#define GEOMAGNETIC2_OTP_IDX_MAG_SENS_X          0x10
#define GEOMAGNETIC2_OTP_IDX_MAG_SENS_Y          0x10
#define GEOMAGNETIC2_OTP_IDX_MAG_SENS_Z          0x11
#define GEOMAGNETIC2_OTP_IDX_MAG_TCO_X           0x12
#define GEOMAGNETIC2_OTP_IDX_MAG_TCO_Y           0x13
#define GEOMAGNETIC2_OTP_IDX_MAG_TCO_Z           0x14
#define GEOMAGNETIC2_OTP_IDX_MAG_TCS_X           0x12
#define GEOMAGNETIC2_OTP_IDX_MAG_TCS_Y           0x13
#define GEOMAGNETIC2_OTP_IDX_MAG_TCS_Z           0x14
#define GEOMAGNETIC2_OTP_IDX_MAG_CROSS_XY        0x15
#define GEOMAGNETIC2_OTP_IDX_MAG_CROSS_ZX        0x16
#define GEOMAGNETIC2_OTP_IDX_MAG_DUT_T0          0x18

/**
 * @brief GeoMagnetic 2 total number of OTP words setting.
 * @details Specified setting for total number of OTP words of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_OTP_WORD_COUNT              0x19

/**
 * @brief GeoMagnetic 2 12-bit sign extension function.
 * @details This function sign-extends a 12-bit unsigned value to a signed 16-bit integer.
 * @param[in] val : Raw 12-bit unsigned value to sign-extend.
 * @return Signed 16-bit representation of the input value.
 * @note None.
 */
static int16_t geomagnetic_sign_extend_12bit ( uint16_t val );

/**
 * @brief GeoMagnetic 2 delay function.
 * @details This function performs a software delay of the requested duration.
 * @param[in] timeout_ms : Delay duration in milliseconds.
 * @return Nothing.
 * @note None.
 */
static void geomagnetic2_delay_ms ( uint16_t timeout_ms );

void geomagnetic2_cfg_setup ( geomagnetic2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GEOMAGNETIC2_DEVICE_ADDRESS;
}

err_t geomagnetic2_init ( geomagnetic2_t *ctx, geomagnetic2_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    /* Cache the current powermode(suspend mode) as the default after init */
    ctx->powermode = GEOMAGNETIC2_PMU_CMD_SUS;

    return I2C_MASTER_SUCCESS;
}

err_t geomagnetic2_default_cfg ( geomagnetic2_t *ctx )
{
    uint8_t otp_lock_cmd = GEOMAGNETIC2_OTP_CMD_LOCK;

    /* Init flow starts with soft reset */
    if ( GEOMAGNETIC2_OK != geomagnetic2_soft_reset( ctx ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* Verify chip ID */
    if ( GEOMAGNETIC2_OK != geomagnetic2_check_chip_id( ctx ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* Read OTP compensation coefficients */
    if ( GEOMAGNETIC2_OK != geomagnetic2_update_comp( ctx ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* Terminate boot phase / power off OTP */
    if ( GEOMAGNETIC2_OK != geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_OTP_CMD_REG, &otp_lock_cmd, 1 ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* Magnetic reset after OTP power-off */
    if ( GEOMAGNETIC2_OK != geomagnetic2_magnetic_reset( ctx ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* Enable all axes */
    if ( GEOMAGNETIC2_OK != geomagnetic2_enable_axes( ctx, GEOMAGNETIC2_AXIS_EN_ALL ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* Configure ODR = 6.25Hz, AVG = 2 */
    if ( GEOMAGNETIC2_OK != geomagnetic2_set_odr_avg( ctx, GEOMAGNETIC2_ODR_6_25HZ, GEOMAGNETIC2_AVG_2 ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* Configure default interrupt pin behavior */
    if ( GEOMAGNETIC2_OK != geomagnetic2_config_interrupt( ctx ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* Enter normal mode -> BMM350 will automatically start measuring */
    if ( GEOMAGNETIC2_OK != geomagnetic2_set_powermode( ctx, GEOMAGNETIC2_PMU_CMD_NM ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    return GEOMAGNETIC2_OK;
}

err_t geomagnetic2_generic_write ( geomagnetic2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ 2 ] = { 0 };
    uint8_t cnt;
    err_t err_flag = GEOMAGNETIC2_OK;

    /* BMM350 does not support address auto-increment on writes.
     * Each byte must be sent as an individual address + data pair. */
    for ( cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ 0 ] = reg + cnt;
        tx_buf[ 1 ] = data_in[ cnt ];
        err_flag |= i2c_master_write( &ctx->i2c, tx_buf, 2 );
    }

    return err_flag;
}

err_t geomagnetic2_generic_read ( geomagnetic2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    /* When performing repeated start for read, BMM350 always sends out 2 dummy bytes at the start 
     * which would be discarded - > read n+2 bytes */
    uint8_t rx_buf[ GEOMAGNETIC2_BMM350_MAX_LEN + GEOMAGNETIC2_DUMMY_BYTES ] = { 0 };
    err_t err_flag = GEOMAGNETIC2_OK;
    uint8_t cnt;
    
    /* Check if the requested length is within the supported range */
    if ( len > GEOMAGNETIC2_BMM350_MAX_LEN )
    {
        return GEOMAGNETIC2_ERROR;
    }
                                           
    err_flag |= i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, len + GEOMAGNETIC2_DUMMY_BYTES );

    /* Skip the two dummy bytes at the beginning */
    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_out[ cnt ] = rx_buf[ GEOMAGNETIC2_DUMMY_BYTES + cnt ];
    }

    return err_flag;
}

err_t geomagnetic2_check_chip_id ( geomagnetic2_t *ctx )
{
    uint8_t chip_id;

    if ( GEOMAGNETIC2_OK != geomagnetic2_generic_read( ctx, GEOMAGNETIC2_REG_CHIP_ID,  &chip_id, 1 ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    if ( GEOMAGNETIC2_CHIP_ID != chip_id )
    {
        return GEOMAGNETIC2_ERROR;
    }

    return GEOMAGNETIC2_OK;
}

err_t geomagnetic2_soft_reset ( geomagnetic2_t *ctx )
{
    uint8_t cmd = GEOMAGNETIC2_CMD_SOFT_RESET;
    if ( GEOMAGNETIC2_OK != geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_CMD, &cmd, 1 ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* Wait for reset to complete and OTP to become accessible */
    geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_SOFT_RESET_MS );
    
    /* Cache the current powermode(suspend mode) */ 
    ctx->powermode = GEOMAGNETIC2_PMU_CMD_SUS;

    return GEOMAGNETIC2_OK;
}

err_t geomagnetic2_set_powermode ( geomagnetic2_t *ctx, uint8_t powermode )
{
    uint8_t cmd;
    uint8_t status0;
    uint8_t status1;
    err_t err_flag = GEOMAGNETIC2_OK;
    
    /* Check the current PMU status to see if the device is in Normal mode */
    if ( GEOMAGNETIC2_OK != geomagnetic2_get_pmu_status( ctx, &status0, &status1 ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* If device is currently in Normal mode, it must first go to Suspend
     * before entering Forced / Forced Fast mode. */
    if ( ( status0 & GEOMAGNETIC2_PMU_IS_NORMAL_MASK ) &&
         ( ( GEOMAGNETIC2_PMU_CMD_FM == powermode ) ||
           ( GEOMAGNETIC2_PMU_CMD_FM_FAST == powermode ) ) )
    {   
        /* Switch to Suspend mode */
        cmd = GEOMAGNETIC2_PMU_CMD_SUS;
        err_flag |= geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_PMU_CMD, &cmd, 1 );

        /* Wait for the transition to complete */
        geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_NM_TO_SUS_MS );

        /* Verify PMU is ready for the next command */
        err_flag |= geomagnetic2_wait_pmu_ready( ctx );

        if ( GEOMAGNETIC2_OK != err_flag )
        {
            return GEOMAGNETIC2_ERROR;
        }
    }

    /* Issue requested power mode command */
    cmd = powermode;
    err_flag |= geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_PMU_CMD, &cmd, 1 );

    /* Wait for the power mode change to complete */
    switch ( powermode )
    {
        case GEOMAGNETIC2_PMU_CMD_NM:
        {
            geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_SUS_TO_NM_MS );
            break;
        }
        case GEOMAGNETIC2_PMU_CMD_SUS:
        {
            geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_NM_TO_SUS_MS );
            break;
        }
        case GEOMAGNETIC2_PMU_CMD_FM:
        {
            geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_FM_MS );
            break;
        }
        case GEOMAGNETIC2_PMU_CMD_FM_FAST:
        {
            geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_FM_MS );
            break;
        }
        case GEOMAGNETIC2_PMU_CMD_FGR:
        {
            geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_FGR_MS );
            break;
        }
        case GEOMAGNETIC2_PMU_CMD_FGR_FAST:
        {
            geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_FGR_MS );
            break;
        }
        case GEOMAGNETIC2_PMU_CMD_BR:
        {
            geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_BR_MS );
            break;
        }
        case GEOMAGNETIC2_PMU_CMD_BR_FAST:
        {
            geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_BR_MS );
            break;
        }
        default:
        {
            Delay_1ms( );
            break;
        }
    }
    
    /* Verify PMU is ready after the power mode change */
    err_flag |= geomagnetic2_wait_pmu_ready( ctx );

    if ( GEOMAGNETIC2_OK != err_flag )
    {
        return GEOMAGNETIC2_ERROR;
    }
    
    /* Cache the current powermode */
    ctx->powermode = powermode;

    return GEOMAGNETIC2_OK;
}

err_t geomagnetic2_set_odr_avg ( geomagnetic2_t *ctx, uint8_t odr, uint8_t avg )
{
    uint8_t reg_val;
    uint8_t cmd;
    err_t err_flag = GEOMAGNETIC2_OK;
    
    /* Create register value for ODR and AVG parameters */
    reg_val = ( ( avg << GEOMAGNETIC2_AVG_SHIFT  ) | ( odr & GEOMAGNETIC2_ODR_MASK ) );
    err_flag |= geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_PMU_CMD_AGGR_SET, &reg_val, 1 );
    
    /* update ODR and AVG parameters */
    cmd = GEOMAGNETIC2_PMU_CMD_UPD_OAE;
    err_flag |= geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_PMU_CMD, &cmd, 1 );

    Delay_1ms( );

    return err_flag;
}

err_t geomagnetic2_enable_axes ( geomagnetic2_t *ctx, uint8_t axes )
{
    uint8_t reg_val;
    uint8_t status0;
    uint8_t status1;
    uint8_t was_normal = 0;

    reg_val = axes & GEOMAGNETIC2_AXIS_EN_MASK;
    
    /* Get PMU status to determine current power mode */
    if ( GEOMAGNETIC2_OK != geomagnetic2_get_pmu_status( ctx, &status0, &status1 ) )
    {
        return GEOMAGNETIC2_ERROR;
    }
    
    /* If the device is in normal mode, switch to suspend mode before enabling axes */
    if ( status0 & GEOMAGNETIC2_PMU_IS_NORMAL_MASK )
    {
        was_normal = 1;

        if ( GEOMAGNETIC2_OK != geomagnetic2_set_powermode( ctx, GEOMAGNETIC2_PMU_CMD_SUS ) )
        {
            return GEOMAGNETIC2_ERROR;
        }
    }
    
    /* Enable specified axes */
    if ( GEOMAGNETIC2_OK != geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_PMU_CMD_AXIS_EN, &reg_val, 1 ) )
    {
        return GEOMAGNETIC2_ERROR;
    }
    
    /* If the device was in normal mode, switch back to normal mode */
    if ( was_normal )
    {
        if ( GEOMAGNETIC2_OK != geomagnetic2_set_powermode( ctx, GEOMAGNETIC2_PMU_CMD_NM ) )
        {
            return GEOMAGNETIC2_ERROR;
        }
    }

    return GEOMAGNETIC2_OK;
}

err_t geomagnetic2_config_interrupt ( geomagnetic2_t *ctx )
{
    /* Configure interrupt:
     *    mapped to INT pin
     *    active high
     *    push-pull
     *    latched mode */
    uint8_t reg_val = GEOMAGNETIC2_INT_DRDY_EN |
                      GEOMAGNETIC2_INT_OUTPUT_EN |
                      GEOMAGNETIC2_INT_OD_PUSH_PULL |
                      GEOMAGNETIC2_INT_POL_HIGH |
                      GEOMAGNETIC2_INT_MODE_LATCHED;

    return geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_INT_CTRL, &reg_val, 1 );
}

err_t geomagnetic2_enable_interrupt ( geomagnetic2_t *ctx, uint8_t enable )
{
    uint8_t reg_val;
    
    /* Perform a read-modify-write on the interrupt control register */
    if ( GEOMAGNETIC2_OK != geomagnetic2_generic_read( ctx, GEOMAGNETIC2_REG_INT_CTRL, &reg_val, 1 ) )
    {                                       
        return GEOMAGNETIC2_ERROR;
    }

    if ( enable )
    {
        reg_val |= GEOMAGNETIC2_INT_DRDY_EN;
    }
    else
    {
        reg_val &= ~GEOMAGNETIC2_INT_DRDY_EN;
    }

    return geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_INT_CTRL, &reg_val, 1 );
}

err_t geomagnetic2_get_int_status ( geomagnetic2_t *ctx, uint8_t *int_status )
{
    return geomagnetic2_generic_read( ctx, GEOMAGNETIC2_REG_INT_STATUS, int_status, 1 );
}

uint8_t geomagnetic2_get_int_pin ( geomagnetic2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t geomagnetic2_read_data ( geomagnetic2_t *ctx, geomagnetic2_data_t *mag_data )
{
    uint8_t raw[ GEOMAGNETIC2_DATA_LEN ] = { 0 };

    int32_t raw_x;
    int32_t raw_y;
    int32_t raw_z;
    int32_t raw_temp;

    float raw_x_f;
    float raw_y_f;
    float raw_z_f;
    float dut_temp;

    float comp_x;
    float comp_y;
    float comp_z;
    float delta_temp;

    float denom;
    float out_x;
    float out_y;
    float out_z;

    /* Burst read all 15 data bytes(XLSB,LSB and MSB for x,y,z,temp, and sensortime) starting at 0x31 */
    if ( GEOMAGNETIC2_OK != geomagnetic2_generic_read( ctx, GEOMAGNETIC2_REG_MAG_X_XLSB, raw, GEOMAGNETIC2_DATA_LEN ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* ---- Reconstruct 24-bit signed integers ---- */
    /* MAG X: bytes [0..2] */
    raw_x = ( ( int32_t ) raw[ 2 ] << 16 ) | ( ( int32_t ) raw[ 1 ] << 8 ) | raw[ 0 ];
    if ( raw_x & GEOMAGNETIC2_RAW_SIGN_BIT )
    {
        raw_x |= ( int32_t ) GEOMAGNETIC2_RAW_SIGN_EXT_MASK;
    }

    /* MAG Y: bytes [3..5] */
    raw_y = ( ( int32_t ) raw[ 5 ] << 16 ) | ( ( int32_t ) raw[ 4 ] << 8 ) | raw[ 3 ];
    if ( raw_y & GEOMAGNETIC2_RAW_SIGN_BIT )
    {
        raw_y |= ( int32_t ) GEOMAGNETIC2_RAW_SIGN_EXT_MASK;
    }

    /* MAG Z: bytes [6..8] */
    raw_z = ( ( int32_t ) raw[ 8 ] << 16 ) | ( ( int32_t ) raw[ 7 ] << 8 ) | raw[ 6 ];
    if ( raw_z & GEOMAGNETIC2_RAW_SIGN_BIT )
    {
        raw_z |= ( int32_t ) GEOMAGNETIC2_RAW_SIGN_EXT_MASK;
    }

    /* TEMP: bytes [9..11] */
    raw_temp = ( ( int32_t ) raw[ 11 ] << 16 ) | ( ( int32_t ) raw[ 10 ] << 8 ) | raw[ 9 ];
    if ( raw_temp & GEOMAGNETIC2_RAW_SIGN_BIT )
    {
        raw_temp |= ( int32_t ) GEOMAGNETIC2_RAW_SIGN_EXT_MASK;
    }

    /* Compensated temperature in degrees C :
     *    temp_pre = raw_temp * lsb_to_ut_degc - 25.49
     *    temp_comp = ( 1 + t_sens ) * temp_pre + t_offs */
    dut_temp = ( ( float ) raw_temp * GEOMAGNETIC2_TEMP_LSB_TO_DEGC ) - GEOMAGNETIC2_TEMP_OFFSET_BASE;
    dut_temp = ( ( 1.0f + ctx->comp.dut_t_sens ) * dut_temp ) + ctx->comp.dut_t_offs;
    mag_data->temperature = dut_temp;

    /* Convert raw counts to pre-compensation float */ 
    raw_x_f = ( float ) raw_x * GEOMAGNETIC2_MAG_XY_LSB_TO_UT;
    raw_y_f = ( float ) raw_y * GEOMAGNETIC2_MAG_XY_LSB_TO_UT;
    raw_z_f = ( float ) raw_z * GEOMAGNETIC2_MAG_Z_LSB_TO_UT;

    /* Temperature delta from reference */
    delta_temp = dut_temp - ctx->comp.dut_t0;

    /* Apply offset, sensitivity, temperature coefficient of offset (TCO),
     * and temperature coefficient of sensitivity (TCS) per axis */
    comp_x = ( ( 1.0f + ctx->comp.dut_sensx ) * raw_x_f +
               ctx->comp.dut_offx +
               ctx->comp.dut_tcox * delta_temp ) /
             ( 1.0f + ctx->comp.dut_tcsx * delta_temp );

    comp_y = ( ( 1.0f + ctx->comp.dut_sensy ) * raw_y_f +
               ctx->comp.dut_offy +
               ctx->comp.dut_tcoy * delta_temp ) /
             ( 1.0f + ctx->comp.dut_tcsy * delta_temp );

    comp_z = ( ( 1.0f + ctx->comp.dut_sensz ) * raw_z_f +
               ctx->comp.dut_offz +
               ctx->comp.dut_tcoz * delta_temp ) /
             ( 1.0f + ctx->comp.dut_tcsz * delta_temp );

    /* Cross-axis compensation */
    denom = 1.0f - ( ctx->comp.cross_y_x * ctx->comp.cross_x_y );

    out_x = ( comp_x - ( ctx->comp.cross_x_y * comp_y ) ) / denom;
    out_y = ( comp_y - ( ctx->comp.cross_y_x * comp_x ) ) / denom;

    out_z = comp_z + 
          ( comp_x * ( ( ctx->comp.cross_y_x * ctx->comp.cross_z_y ) -
                           ctx->comp.cross_z_x ) -
            comp_y * ( ctx->comp.cross_z_y -
                     ( ctx->comp.cross_x_y * ctx->comp.cross_z_x ) ) ) / denom;

    mag_data->mag_x = out_x;
    mag_data->mag_y = out_y;
    mag_data->mag_z = out_z;    

    return GEOMAGNETIC2_OK;
}

err_t geomagnetic2_magnetic_reset ( geomagnetic2_t *ctx )
{
    uint8_t prev_mode = ctx->powermode;
    uint8_t cmd;
    err_t err_flag = GEOMAGNETIC2_OK;

    /* Must be in suspend mode for magnetic reset */
    if ( GEOMAGNETIC2_PMU_CMD_NM == ctx->powermode )
    {   
        cmd = GEOMAGNETIC2_PMU_CMD_SUS;
        err_flag |= geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_PMU_CMD, &cmd, 1 );
        geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_NM_TO_SUS_MS );
        err_flag |= geomagnetic2_wait_pmu_ready( ctx );
        ctx->powermode = GEOMAGNETIC2_PMU_CMD_SUS;
    }

    /* Issue Flux-Guide Reset (FGR) */
    cmd = GEOMAGNETIC2_PMU_CMD_FGR;
    err_flag |= geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_PMU_CMD, &cmd, 1 );
    geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_FGR_MS );
    err_flag |= geomagnetic2_wait_pmu_ready( ctx );

    /* Issue Bit Reset (BR) */
    cmd = GEOMAGNETIC2_PMU_CMD_BR;
    err_flag |= geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_PMU_CMD, &cmd, 1 );
    geomagnetic2_delay_ms( GEOMAGNETIC2_DELAY_BR_MS );
    err_flag |= geomagnetic2_wait_pmu_ready( ctx );

    /* Restore previous power mode if it was normal mode */
    if ( GEOMAGNETIC2_PMU_CMD_NM == prev_mode )
    {
        err_flag |= geomagnetic2_set_powermode( ctx, GEOMAGNETIC2_PMU_CMD_NM );
    }

    return err_flag;
}

err_t geomagnetic2_otp_read_word ( geomagnetic2_t *ctx, uint8_t addr, uint16_t *otp_word )
{
    uint8_t reg_data;
    uint8_t otp_buf[ 2 ] = { 0 };
    uint8_t timeout = GEOMAGNETIC2_OTP_TIMEOUT_MS;

    /* Write the word address and direct read command to otp command register */
    reg_data = ( addr & GEOMAGNETIC2_OTP_ADDR_MASK ) | GEOMAGNETIC2_OTP_CMD_DIR_READ;
    if ( GEOMAGNETIC2_OK != geomagnetic2_generic_write( ctx, GEOMAGNETIC2_REG_OTP_CMD_REG, &reg_data, 1 ) )                                                    
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* wait for otp command done */
    do
    {
        Delay_1ms( );
        if ( GEOMAGNETIC2_OK != geomagnetic2_generic_read( ctx, GEOMAGNETIC2_REG_OTP_STATUS_REG, &reg_data, 1 ) )                                             
        {
            return GEOMAGNETIC2_ERROR;
        }   
        timeout--;
    } while ( !( reg_data & GEOMAGNETIC2_OTP_STATUS_CMD_DONE ) && timeout );

    if ( 0 == timeout )
    {
        return GEOMAGNETIC2_ERROR;
    }

    /* Read the 16-bit OTP data word (MSB first) */
    if ( GEOMAGNETIC2_OK != geomagnetic2_generic_read( ctx, GEOMAGNETIC2_REG_OTP_DATA_MSB_REG, otp_buf, 2 ) )                                               
    {
        return GEOMAGNETIC2_ERROR;
    }
    
    /* Reconstruct the 16-bit OTP data word */
    *otp_word = ( ( uint16_t ) otp_buf[ 0 ] << 8 ) | otp_buf[ 1 ];

    return GEOMAGNETIC2_OK;
}

err_t geomagnetic2_update_comp ( geomagnetic2_t *ctx )
{
    uint16_t otp[ GEOMAGNETIC2_OTP_WORD_COUNT ] = { 0 };
    uint8_t cnt;

    uint16_t off_x_lsb_msb;
    uint16_t off_y_lsb_msb;
    uint16_t off_z_lsb_msb;
    uint8_t t_off;

    uint8_t sens_x;
    uint8_t sens_y;
    uint8_t sens_z;
    uint8_t t_sens;

    uint8_t tco_x;
    uint8_t tco_y;
    uint8_t tco_z;

    uint8_t tcs_x;
    uint8_t tcs_y;
    uint8_t tcs_z;

    uint8_t cross_x_y;
    uint8_t cross_y_x;
    uint8_t cross_z_x;
    uint8_t cross_z_y;

    /* Read all needed OTP words */
    for ( cnt = GEOMAGNETIC2_OTP_IDX_TEMP_OFF_SENS; cnt < GEOMAGNETIC2_OTP_WORD_COUNT; cnt++ )
    {
        if ( GEOMAGNETIC2_OK != geomagnetic2_otp_read_word( ctx, cnt, &otp[ cnt ] ) )
        {
            return GEOMAGNETIC2_ERROR;
        }
    }

    /* Extract offset values */
    off_x_lsb_msb = otp[ GEOMAGNETIC2_OTP_IDX_MAG_OFFSET_X ] & 0x0FFF;
    off_y_lsb_msb = ( ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_OFFSET_X ] & 0xF000 ) >> 4 ) |
                    ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_OFFSET_Y ] & 0x00FF );
    off_z_lsb_msb = ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_OFFSET_Y ] & 0x0F00 ) |
                    ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_SENS_X ] & 0x00FF );
    t_off = ( uint8_t ) ( otp[ GEOMAGNETIC2_OTP_IDX_TEMP_OFF_SENS ] & 0x00FF );
    
    ctx->comp.dut_offx = ( float ) geomagnetic_sign_extend_12bit( off_x_lsb_msb );
    ctx->comp.dut_offy = ( float ) geomagnetic_sign_extend_12bit( off_y_lsb_msb );
    ctx->comp.dut_offz = ( float ) geomagnetic_sign_extend_12bit( off_z_lsb_msb );
    ctx->comp.dut_t_offs = ( float ) ( int8_t ) t_off / GEOMAGNETIC2_OTP_T_OFFS_SCALE;
    
    /* Extract sensitivity and temperature compensation values */
    sens_x = ( uint8_t ) ( ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_SENS_X ] & 0xFF00 ) >> 8 );
    sens_y = ( uint8_t ) ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_SENS_Y ] & 0x00FF );
    sens_z = ( uint8_t ) ( ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_SENS_Z ] & 0xFF00 ) >> 8 );
    t_sens = ( uint8_t ) ( ( otp[ GEOMAGNETIC2_OTP_IDX_TEMP_OFF_SENS ] & 0xFF00 ) >> 8 );

    ctx->comp.dut_sensx  = ( float ) ( int8_t ) sens_x / GEOMAGNETIC2_OTP_SENS_SCALE;
    ctx->comp.dut_sensy  = ( float ) ( int8_t ) sens_y / GEOMAGNETIC2_OTP_SENS_SCALE;
    ctx->comp.dut_sensz  = ( float ) ( int8_t ) sens_z / GEOMAGNETIC2_OTP_SENS_SCALE;
    ctx->comp.dut_t_sens = ( float ) ( int8_t ) t_sens / GEOMAGNETIC2_OTP_T_SENS_SCALE;
    
    /* Extract temperature compensation offset values */
    tco_x = ( uint8_t ) ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_TCO_X ] & 0x00FF );
    tco_y = ( uint8_t ) ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_TCO_Y ] & 0x00FF );
    tco_z = ( uint8_t ) ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_TCO_Z ] & 0x00FF );

    ctx->comp.dut_tcox = ( float ) ( int8_t ) tco_x / GEOMAGNETIC2_OTP_TCO_SCALE;
    ctx->comp.dut_tcoy = ( float ) ( int8_t ) tco_y / GEOMAGNETIC2_OTP_TCO_SCALE;
    ctx->comp.dut_tcoz = ( float ) ( int8_t ) tco_z / GEOMAGNETIC2_OTP_TCO_SCALE;
    
    /* Extract temperature compensation scale values */
    tcs_x = ( uint8_t ) ( ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_TCS_X ] & 0xFF00 ) >> 8 );
    tcs_y = ( uint8_t ) ( ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_TCS_Y ] & 0xFF00 ) >> 8 );
    tcs_z = ( uint8_t ) ( ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_TCS_Z ] & 0xFF00 ) >> 8 );

    ctx->comp.dut_tcsx = ( float ) ( int8_t ) tcs_x / GEOMAGNETIC2_OTP_TCS_SCALE;
    ctx->comp.dut_tcsy = ( float ) ( int8_t ) tcs_y / GEOMAGNETIC2_OTP_TCS_SCALE;
    ctx->comp.dut_tcsz = ( float ) ( int8_t ) tcs_z / GEOMAGNETIC2_OTP_TCS_SCALE;
    
    ctx->comp.dut_t0 = ( ( float ) ( int16_t ) otp[ GEOMAGNETIC2_OTP_IDX_MAG_DUT_T0 ] / GEOMAGNETIC2_OTP_T_SENS_SCALE ) + GEOMAGNETIC2_OTP_T0_BASE;
    
    /* Extract cross compensation values */
    cross_x_y = ( uint8_t ) ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_CROSS_XY ] & 0x00FF );
    cross_y_x = ( uint8_t ) ( ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_CROSS_XY ] & 0xFF00 ) >> 8 );
    cross_z_x = ( uint8_t ) ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_CROSS_ZX ] & 0x00FF );
    cross_z_y = ( uint8_t ) ( ( otp[ GEOMAGNETIC2_OTP_IDX_MAG_CROSS_ZX ] & 0xFF00 ) >> 8 );

    ctx->comp.cross_x_y = ( float ) ( int8_t ) cross_x_y / GEOMAGNETIC2_OTP_CROSS_SCALE;
    ctx->comp.cross_y_x = ( float ) ( int8_t ) cross_y_x / GEOMAGNETIC2_OTP_CROSS_SCALE;
    ctx->comp.cross_z_x = ( float ) ( int8_t ) cross_z_x / GEOMAGNETIC2_OTP_CROSS_SCALE;
    ctx->comp.cross_z_y = ( float ) ( int8_t ) cross_z_y / GEOMAGNETIC2_OTP_CROSS_SCALE;

    return GEOMAGNETIC2_OK;
}

err_t geomagnetic2_get_pmu_status ( geomagnetic2_t *ctx, uint8_t *status0, uint8_t *status1 )
{
    if ( GEOMAGNETIC2_OK != geomagnetic2_generic_read( ctx, GEOMAGNETIC2_REG_PMU_CMD_STATUS_0, status0, 1 ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    if ( GEOMAGNETIC2_OK != geomagnetic2_generic_read( ctx, GEOMAGNETIC2_REG_PMU_CMD_STATUS_1, status1, 1 ) )
    {
        return GEOMAGNETIC2_ERROR;
    }

    return GEOMAGNETIC2_OK;
}

err_t geomagnetic2_wait_pmu_ready ( geomagnetic2_t *ctx )
{
    uint8_t status0;
    uint8_t status1;
    uint8_t timeout = GEOMAGNETIC2_PMU_TIMEOUT_MS;

    do
    {
        Delay_1ms( );
        
        /* Get PMU status and check for illegal command or busy flag */
        if ( GEOMAGNETIC2_OK != geomagnetic2_get_pmu_status( ctx, &status0, &status1 ) )
        {
            return GEOMAGNETIC2_ERROR;
        }

        if ( status0 & GEOMAGNETIC2_PMU_CMD_ILLEGAL_MASK )
        {
            return GEOMAGNETIC2_ERROR;
        }

        timeout--;
    }
    while ( ( status0 & GEOMAGNETIC2_PMU_CMD_BUSY_MASK ) && timeout );

    return ( timeout > 0 ) ? GEOMAGNETIC2_OK : GEOMAGNETIC2_ERROR;
}

static int16_t geomagnetic_sign_extend_12bit ( uint16_t val )
{
    if ( val >= GEOMAGNETIC2_OTP_12BIT_SIGN_THRESH )
    {
        return ( int16_t ) ( val - ( uint16_t ) ( GEOMAGNETIC2_OTP_12BIT_SIGN_THRESH * 2 ) );
    }
    return ( int16_t ) val;
}

static void geomagnetic2_delay_ms ( uint16_t timeout_ms )
{
    switch ( timeout_ms )
    {
        case GEOMAGNETIC2_DELAY_SOFT_RESET_MS: 
        {
            Delay_1ms( );
            Delay_1ms( );
            break;
        }
        case GEOMAGNETIC2_DELAY_OTP_RDY_MS:   
        {
            Delay_5ms( );
            break;
        }
        case GEOMAGNETIC2_DELAY_NM_TO_SUS_MS: 
        {
            Delay_5ms( );
            Delay_1ms( );
            break;
        }
        case GEOMAGNETIC2_DELAY_BR_MS: 
        {
            Delay_8ms( );
            Delay_5ms( );
            Delay_1ms( );
            break;
        }
        case GEOMAGNETIC2_DELAY_FM_MS:  
        {
            Delay_10ms( );
            Delay_5ms( );
            break;
        }
        case GEOMAGNETIC2_DELAY_FGR_MS:      
        {
            Delay_10ms( );
            Delay_8ms( );
            break;
        }
        case GEOMAGNETIC2_DELAY_SUS_TO_NM_MS: 
        {
            Delay_10ms( );
            Delay_10ms( );
            Delay_10ms( );
            Delay_8ms( );
            break;
        }
        default:
        {
            Delay_1ms( );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
