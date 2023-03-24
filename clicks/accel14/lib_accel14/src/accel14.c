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

#include "accel14.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accel14_cfg_setup ( accel14_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->i2 = HAL_PIN_NC;
    cfg->i1 = HAL_PIN_NC;

    cfg->spi_speed = 100000;
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

ACCEL14_RETVAL accel14_init ( accel14_t *ctx, accel14_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ACCEL14_DUMMY;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ACCEL14_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ACCEL14_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    // Input pins

    digital_in_init( &ctx->i2, cfg->i2 );
    digital_in_init( &ctx->i1, cfg->i1 );

    return ACCEL14_OK;
}

void accel14_generic_transfer 
( 
    accel14_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );
}

void accel14_generic_write ( accel14_t *ctx, uint8_t reg, uint8_t tx_data )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= ACCEL14_SPI_WRITE;
    tx_buf[ 1 ] = tx_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf[ 0 ], 1 );
    spi_master_write( &ctx->spi, &tx_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
}

uint8_t accel14_generic_read ( accel14_t *ctx, uint8_t reg )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= ACCEL14_SPI_READ;

    accel14_generic_transfer( ctx, tx_buf, 1, rx_buf, 1 );

    return rx_buf[ 0 ];
}

void accel14_multi_read ( accel14_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= ACCEL14_SPI_READ;

    accel14_generic_transfer( ctx, tx_buf, 1, p_rx_data, n_bytes );
}

uint8_t accel14_check_communication ( accel14_t *ctx )
{
    uint8_t id_val;

    id_val = accel14_generic_read( ctx, ACCEL14_REG_WHO_AM_I );

    if ( id_val == ACCEL14_ID_VALUE )
    {
        return ACCEL14_CHECK_ID_SUCCESS;
    }
    else
    {
        return ACCEL14_CHECK_ID_ERROR;
    }
}

void accel14_default_cfg ( accel14_t *ctx )
{
    accel14_generic_write( ctx, ACCEL14_REG_CTRL1_XL, ACCEL14_CTRL1_XL_POWER_UP
                                               | ACCEL14_CTRL1_XL_HIGH_RES_FS
                                               | ACCEL14_CTRL1_XL_GSEL_4G );
    accel14_generic_write( ctx, ACCEL14_REG_CTRL3_C, ACCEL14_CTRL3_C_BOOT_NORMAL
                                              | ACCEL14_CTRL3_C_BDU_READ_UPDATE
                                              | ACCEL14_CTRL3_C_INT_ACTIVE_HIGH
                                              | ACCEL14_CTRL3_C_PP_OD_PUSH_PULL
                                              | ACCEL14_CTRL3_C_SIM_SPI_4_WIRE
                                              | ACCEL14_CTRL3_C_IF_INC_ENABLE
                                              | ACCEL14_CTRL3_C_SW_RESET_DIS );
    accel14_generic_write( ctx, ACCEL14_REG_CTRL4_C, ACCEL14_CTRL4_C_INT1_2_DIV
                                              | ACCEL14_CTRL4_C_DRDY_MASK_DIS
                                              | ACCEL14_CTRL4_C_I2C_DISABLE
                                              | ACCEL14_CTRL4_C_3REGOUT_EN );
    accel14_generic_write( ctx, ACCEL14_REG_CTRL5_C, ACCEL14_CTRL5_C_ROUNDING_NO
                                              | ACCEL14_CTRL5_C_ST_NORMAL );
    accel14_generic_write( ctx, ACCEL14_REG_CTRL6_C, ACCEL14_CTRL6_C_USR_OFF_W_10
                                              | ACCEL14_CTRL6_C_SEL_3_AXES );
    accel14_generic_write( ctx, ACCEL14_REG_CTRL7_C, ACCEL14_CTRL7_C_USR_OFF_OUT );
    accel14_generic_write( ctx, ACCEL14_REG_CTRL8_XL, ACCEL14_CTRL8_ODR_4
                                               | ACCEL14_CTRL8_HIGH_PASS_DIS
                                               | ACCEL14_CTRL8_LPF2_HPF_DIS );
    accel14_generic_write( ctx, ACCEL14_REG_CTRL10_C, ACCEL14_CTRL10_TIMESTAMP_DIS );
}

uint8_t accel14_check_accel_data_ready ( accel14_t *ctx )
{
    uint8_t status_val;

    status_val = accel14_generic_read( ctx, ACCEL14_REG_STATUS_REG );

    if ( status_val && ACCEL14_STATUS_ACCEL_READY )
    {
        return ACCEL14_NEW_DATA_AVAILABLE;
    }
    else
    {
        return ACCEL14_NEW_DATA_NO_DATA;
    }
}

uint8_t accel14_check_temp_data_ready ( accel14_t *ctx )
{
    uint8_t status_val;

    status_val = accel14_generic_read( ctx, ACCEL14_REG_STATUS_REG );

    if ( status_val && ACCEL14_STATUS_TEMP_READY )
    {
        return ACCEL14_NEW_DATA_AVAILABLE;
    }
    else
    {
        return ACCEL14_NEW_DATA_NO_DATA;
    }
}

void accel14_get_data ( accel14_t *ctx, accel14_accel_t *accel_data )
{
    uint8_t rx_buf[ 6 ];
    int16_t tmp;

    accel14_multi_read( ctx, ACCEL14_REG_OUTX_L_A, rx_buf, 6 );

    tmp = rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 0 ];

    accel_data->x = ( int16_t ) tmp;

    tmp = rx_buf[ 3 ];
    tmp <<= 8;
    tmp |= rx_buf[ 2 ];

    accel_data->y = ( int16_t ) tmp;

    tmp = rx_buf[ 5 ];
    tmp <<= 8;
    tmp |= rx_buf[ 4 ];

    accel_data->z = ( int16_t ) tmp;
}

float accel14_get_temperature ( accel14_t *ctx )
{
    uint8_t rx_buf[ 2 ];
    int16_t tmp;
    float temperature;

    accel14_multi_read( ctx, ACCEL14_REG_OUT_TEMP_L, rx_buf, 2 );

    tmp = rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 0 ];

    temperature = ( float ) tmp;
    temperature /= 256.0;
    temperature += 25.0;

    return temperature;
}

void accel14_read_accel ( accel14_t *ctx, accel14_accel_fs_xl_t *accel_fs )
{
    uint8_t c_tmp;
    accel14_accel_t accel_data;

    accel14_get_data( ctx, &accel_data );

    c_tmp = accel14_generic_read( ctx, ACCEL14_REG_CTRL1_XL );
    c_tmp &= ACCEL14_CTRL1_XL_GSEL_BIT_MASK;

    switch ( c_tmp )
    {
        case ACCEL14_CTRL1_XL_GSEL_2G:
        {
            accel_fs->accel_x = ( float ) accel_data.x;
            accel_fs->accel_x *= ACCEL14_COEF_RES_2G;
            accel_fs->accel_y = ( float ) accel_data.y;
            accel_fs->accel_y *= ACCEL14_COEF_RES_2G;
            accel_fs->accel_z = ( float ) accel_data.z;
            accel_fs->accel_z *= ACCEL14_COEF_RES_2G;
            break;
        }
        case ACCEL14_CTRL1_XL_GSEL_4G:
        {
            accel_fs->accel_x = ( float ) accel_data.x;
            accel_fs->accel_x *= ACCEL14_COEF_RES_4G;
            accel_fs->accel_y = ( float ) accel_data.y;
            accel_fs->accel_y *= ACCEL14_COEF_RES_4G;
            accel_fs->accel_z = ( float ) accel_data.z;
            accel_fs->accel_z *= ACCEL14_COEF_RES_4G;
            break;
        }
        case ACCEL14_CTRL1_XL_GSEL_8G:
        {
            accel_fs->accel_x = ( float ) accel_data.x;
            accel_fs->accel_x *= ACCEL14_COEF_RES_8G;
            accel_fs->accel_y = ( float ) accel_data.y;
            accel_fs->accel_y *= ACCEL14_COEF_RES_8G;
            accel_fs->accel_z = ( float ) accel_data.z;
            accel_fs->accel_z *= ACCEL14_COEF_RES_8G;
            break;
        }
        case ACCEL14_CTRL1_XL_GSEL_16G:
        {
            accel_fs->accel_x = ( float ) accel_data.x;
            accel_fs->accel_x *= ACCEL14_COEF_RES_16G;
            accel_fs->accel_y = ( float ) accel_data.y;
            accel_fs->accel_y *= ACCEL14_COEF_RES_16G;
            accel_fs->accel_z = ( float ) accel_data.z;
            accel_fs->accel_z *= ACCEL14_COEF_RES_16G;
            break;
        }
    }
}

uint8_t accel14_check_int1 ( accel14_t *ctx )
{
    return digital_in_read( &ctx->i1 );
}

uint8_t accel14_check_int2 ( accel14_t *ctx )
{
    return digital_in_read( &ctx->i2 );
}

// ------------------------------------------------------------------------ END
