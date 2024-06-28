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
 * @file compass8.c
 * @brief Compass 8 Click Driver.
 */

#include "compass8.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY            0x00
#define DRDY_TIMEOUT     10000u

void compass8_cfg_setup ( compass8_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COMPASS8_DEVICE_ADDRESS;
}

err_t compass8_init ( compass8_t *ctx, compass8_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    return I2C_MASTER_SUCCESS;
}

err_t compass8_default_cfg ( compass8_t *ctx ) 
{
    compass8_device_enable( ctx );
    Delay_100ms( );

    uint8_t dev_id = DUMMY;
    err_t err_flag = compass8_get_device_id( ctx, &dev_id );
    if ( COMPASS8_DEVICE_ID == dev_id )
    {
        err_flag |= compass8_get_company_id( ctx, &dev_id );
        if ( COMPASS8_COMPANY_ID == dev_id )
        {
            err_flag |= compass8_set_operation_mode( ctx, COMPASS8_CNTL2_MODE_PD );
            Delay_10ms( );

            err_flag |= compass8_set_control( ctx, COMPASS8_REG_CNTL1, 
                                                   COMPASS8_CNTL1_WM_STEP_1 | 
                                                   COMPASS8_CNTL1_ITS_OFF );
            Delay_10ms( );

            err_flag |= compass8_set_control( ctx, COMPASS8_REG_CNTL2, 
                                                   COMPASS8_CNTL2_MODE_PD  | 
                                                   COMPASS8_CNTL2_IBIP_DIS |
                                                   COMPASS8_CNTL2_SDR_DIS  |
                                                   COMPASS8_CNTL2_FIFO_DIS );
            Delay_10ms( );

            err_flag |= compass8_set_operation_mode( ctx, COMPASS8_CNTL2_MODE_CONT4 );
            Delay_10ms( );
        }
    }
    return err_flag;
}

void compass8_device_enable ( compass8_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

void compass8_device_disable ( compass8_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

err_t compass8_generic_write ( compass8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t compass8_generic_read ( compass8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t compass8_get_company_id ( compass8_t *ctx, uint8_t *company_id ) 
{
    return compass8_generic_read( ctx, COMPASS8_REG_WIA1, company_id, 1 );
}

err_t compass8_get_device_id ( compass8_t *ctx, uint8_t *device_id ) 
{
    return compass8_generic_read( ctx, COMPASS8_REG_WIA2, device_id, 1 );
}

err_t compass8_wait_data_ready ( compass8_t *ctx ) 
{
    err_t err_flag = COMPASS8_OK;
    uint8_t data_buf = DUMMY;
    uint16_t timeout = DUMMY;
    while ( !data_buf )
    {
        err_flag |= compass8_generic_read( ctx, COMPASS8_REG_ST1, &data_buf, 1 );
        data_buf &= COMPASS8_ST1_DATA_READY;
        timeout++;
        if ( DRDY_TIMEOUT < timeout )
        {
            err_flag = COMPASS8_ERROR;
            break;
        }
         Delay_1ms( );
    }
    
    return err_flag;
}

err_t compass8_get_raw_data ( compass8_t *ctx, int16_t *axis_x, int16_t *axis_y, int16_t *axis_z ) 
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t err_flag = compass8_generic_read( ctx, COMPASS8_REG_HXH, data_buf, 6 );
    *axis_x  = data_buf[ 0 ];
    *axis_x <<= 8;
    *axis_x |= data_buf[ 1 ];
    *axis_y  = data_buf[ 2 ];
    *axis_y <<= 8;
    *axis_y |= data_buf[ 3 ];
    *axis_z  = data_buf[ 4 ];
    *axis_z <<= 8;
    *axis_z |= data_buf[ 5 ];
    err_flag |= compass8_generic_read( ctx, COMPASS8_REG_ST2, data_buf, 1 );
    return err_flag;
}


err_t compass8_get_magnetic_data ( compass8_t *ctx, compass8_axes_t *axis ) 
{
    int16_t x_val = DUMMY, y_val = DUMMY, z_val = DUMMY;
    err_t err_flag = compass8_wait_data_ready( ctx );
    err_flag |= compass8_get_raw_data( ctx, &x_val, &y_val, &z_val );
    axis->x = ( float ) x_val;
    axis->x *= COMPASS8_MAG_AXIS_SENS;
    axis->y = ( float ) y_val;
    axis->y *= COMPASS8_MAG_AXIS_SENS;
    axis->z = ( float ) z_val;
    axis->z *= COMPASS8_MAG_AXIS_SENS;
    err_flag |= compass8_set_operation_mode( ctx, COMPASS8_CNTL2_MODE_CONT4 );
    return err_flag;
}

err_t compass8_set_operation_mode ( compass8_t *ctx, uint8_t op_mode ) 
{
    err_t err_flag = COMPASS8_ERROR;
    if ( ( COMPASS8_CNTL2_MODE_PD    == op_mode ) ||
         ( COMPASS8_CNTL2_MODE_SNGL  == op_mode ) ||
         ( COMPASS8_CNTL2_MODE_CONT1 == op_mode ) ||
         ( COMPASS8_CNTL2_MODE_CONT2 == op_mode ) ||
         ( COMPASS8_CNTL2_MODE_CONT3 == op_mode ) ||
         ( COMPASS8_CNTL2_MODE_CONT4 == op_mode ) ||
         ( COMPASS8_CNTL2_MODE_CONT5 == op_mode ) || 
         ( COMPASS8_CNTL2_MODE_ST    == op_mode ) ) 
    {
        uint8_t data_buf = DUMMY;
        err_flag = compass8_generic_read( ctx, COMPASS8_REG_CNTL2, &data_buf, 1 );
        data_buf &= COMPASS8_CNTL2_MODE_BITMASK;
        data_buf |= op_mode;
        err_flag |= compass8_generic_write( ctx, COMPASS8_REG_CNTL2, &op_mode, 1 );
    }
    return err_flag;
}

err_t compass8_get_operation_mode ( compass8_t *ctx, uint8_t *op_mode ) 
{
    return compass8_generic_read( ctx, COMPASS8_REG_CNTL2, op_mode, 1 );
}

err_t compass8_set_control ( compass8_t *ctx, uint8_t ctrl_reg, uint8_t data_in ) 
{
    err_t err_flag = COMPASS8_ERROR;
    if ( ( COMPASS8_REG_CNTL1 == ctrl_reg ) || 
         ( COMPASS8_REG_CNTL2 == ctrl_reg ) ||
         ( COMPASS8_REG_CNTL3 == ctrl_reg ) )
    {
        err_flag = compass8_generic_write( ctx, COMPASS8_REG_CNTL2, &data_in, 1 );
    }
    return err_flag;
}

err_t compass8_sw_reset ( compass8_t *ctx ) 
{
    uint8_t data_buf = COMPASS8_CNTL3_SRST_RESET;
    return compass8_generic_write( ctx, COMPASS8_REG_CNTL3, &data_buf, 1 );
}

// ------------------------------------------------------------------------- END
