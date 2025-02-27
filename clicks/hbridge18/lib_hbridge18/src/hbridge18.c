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
 * @file hbridge18.c
 * @brief H-Bridge 18 Click Driver.
 */

#include "hbridge18.h"

/**
 * @brief Dummy and spi read bit macros.
 * @details Definition of dummy and spi read bit macros.
 */
#define DUMMY                       0x00
#define HBRIDGE18_SPI_READ_BIT      0x40

void hbridge18_cfg_setup ( hbridge18_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->sleep = HAL_PIN_NC;
    cfg->fault = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t hbridge18_init ( hbridge18_t *ctx, hbridge18_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->sleep, cfg->sleep );

    digital_in_init( &ctx->fault, cfg->fault );

    return SPI_MASTER_SUCCESS;
}

err_t hbridge18_default_cfg ( hbridge18_t *ctx ) 
{
    err_t error_flag = HBRIDGE18_OK;

    HBRIDGE18_SET_DATA_SAMPLE_EDGE;
    
    hbridge18_enable_device ( ctx );
    Delay_100ms ( );
    if ( HBRIDGE18_ERROR == hbridge18_check_communication ( ctx ) )
    {
        return HBRIDGE18_ERROR;
    }
    // Disable open-load detection on half-bridges 1-4
    error_flag |= hbridge18_write_reg ( ctx, HBRIDGE18_REG_OLD_CTRL_1, 
                                        HBRIDGE18_OLD_CTRL_1_HB4_OLD_DIS | 
                                        HBRIDGE18_OLD_CTRL_1_HB3_OLD_DIS | 
                                        HBRIDGE18_OLD_CTRL_1_HB2_OLD_DIS | 
                                        HBRIDGE18_OLD_CTRL_1_HB1_OLD_DIS );
    return error_flag;
}

err_t hbridge18_write_reg ( hbridge18_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = HBRIDGE18_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( reg > HBRIDGE18_REG_OLD_CTRL_6 )
    {
        return HBRIDGE18_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, reg );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, data_in );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    if ( HBRIDGE18_OK == error_flag )
    {
        ctx->ic_status = ( data_buf[ 0 ] & 0x3F );
    }
    return error_flag;
}

err_t hbridge18_read_reg ( hbridge18_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = HBRIDGE18_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( reg > HBRIDGE18_REG_OLD_CTRL_6 )
    {
        return HBRIDGE18_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, reg | HBRIDGE18_SPI_READ_BIT );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    if ( HBRIDGE18_OK == error_flag )
    {
        ctx->ic_status = ( data_buf[ 0 ] & 0x3F );
        if ( NULL != data_out )
        {
            *data_out = data_buf[ 1 ];
        }
    }
    return error_flag;
}

void hbridge18_enable_device ( hbridge18_t *ctx )
{
    digital_out_high ( &ctx->sleep );
}

void hbridge18_disable_device ( hbridge18_t *ctx )
{
    digital_out_low ( &ctx->sleep );
}

uint8_t hbridge18_get_fault_pin ( hbridge18_t *ctx )
{
    return digital_in_read ( &ctx->fault );
}

err_t hbridge18_check_communication ( hbridge18_t *ctx )
{
    uint8_t config_ctrl = 0;
    if ( HBRIDGE18_OK == hbridge18_read_reg ( ctx, HBRIDGE18_REG_CONFIG_CTRL, &config_ctrl ) )
    {
        if ( HBRIDGE18_CONFIG_CTRL_IC_ID_DRV8904 == ( config_ctrl & HBRIDGE18_CONFIG_CTRL_IC_ID_MASK ) )
        {
            return HBRIDGE18_OK;
        }
    }
    return HBRIDGE18_ERROR;
}

err_t hbridge18_set_motor_state ( hbridge18_t *ctx, uint8_t motor, uint8_t state )
{
    err_t error_flag = HBRIDGE18_OK;
    uint8_t op_ctrl_1 = 0;
    if ( ( motor > HBRIDGE18_MOTOR_1 ) || ( state > HBRIDGE18_MOTOR_STATE_BRAKE_HS ) )
    {
        return HBRIDGE18_ERROR;
    }
    error_flag |= hbridge18_read_reg ( ctx, HBRIDGE18_REG_OP_CTRL_1, &op_ctrl_1 );
    if ( HBRIDGE18_OK == error_flag )
    {
        if ( HBRIDGE18_MOTOR_0 == motor )
        {
            op_ctrl_1 &= ( ~HBRIDGE18_OP_CTRL_1_HB12_MASK );
        }
        else
        {
            op_ctrl_1 &= ( ~HBRIDGE18_OP_CTRL_1_HB34_MASK );
        }

        switch ( state )
        {
            case HBRIDGE18_MOTOR_STATE_COAST:
            {
                break;
            }
            case HBRIDGE18_MOTOR_STATE_FORWARD:
            {
                if ( HBRIDGE18_MOTOR_0 == motor )
                {
                    op_ctrl_1 |= ( HBRIDGE18_OP_CTRL_1_HB1_HS_EN | HBRIDGE18_OP_CTRL_1_HB2_LS_EN );
                }
                else
                {
                    op_ctrl_1 |= ( HBRIDGE18_OP_CTRL_1_HB3_HS_EN | HBRIDGE18_OP_CTRL_1_HB4_LS_EN );
                }
                break;
            }
            case HBRIDGE18_MOTOR_STATE_REVERSE:
            {
                if ( HBRIDGE18_MOTOR_0 == motor )
                {
                    op_ctrl_1 |= ( HBRIDGE18_OP_CTRL_1_HB1_LS_EN | HBRIDGE18_OP_CTRL_1_HB2_HS_EN );
                }
                else
                {
                    op_ctrl_1 |= ( HBRIDGE18_OP_CTRL_1_HB3_LS_EN | HBRIDGE18_OP_CTRL_1_HB4_HS_EN );
                }
                break;
            }
            case HBRIDGE18_MOTOR_STATE_BRAKE_LS:
            {
                if ( HBRIDGE18_MOTOR_0 == motor )
                {
                    op_ctrl_1 |= ( HBRIDGE18_OP_CTRL_1_HB1_LS_EN | HBRIDGE18_OP_CTRL_1_HB2_LS_EN );
                }
                else
                {
                    op_ctrl_1 |= ( HBRIDGE18_OP_CTRL_1_HB3_LS_EN | HBRIDGE18_OP_CTRL_1_HB4_LS_EN );
                }
                break;
            }
            case HBRIDGE18_MOTOR_STATE_BRAKE_HS:
            {
                if ( HBRIDGE18_MOTOR_0 == motor )
                {
                    op_ctrl_1 |= ( HBRIDGE18_OP_CTRL_1_HB1_HS_EN | HBRIDGE18_OP_CTRL_1_HB2_HS_EN );
                }
                else
                {
                    op_ctrl_1 |= ( HBRIDGE18_OP_CTRL_1_HB3_HS_EN | HBRIDGE18_OP_CTRL_1_HB4_HS_EN );
                }
                break;
            }
            default:
            {
                break;
            }
        }
        error_flag |= hbridge18_write_reg ( ctx, HBRIDGE18_REG_OP_CTRL_1, op_ctrl_1 );
    }
    return HBRIDGE18_ERROR;
}

// ------------------------------------------------------------------------- END
