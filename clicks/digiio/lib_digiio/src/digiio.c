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
 * @file digiio.c
 * @brief DIGI IO Click Driver.
 */

#include "digiio.h"

/**
 * @brief Dummy data and SPI write bit.
 * @details Definition of dummy data and SPI write bit.
 */
#define DUMMY               0x00
#define DIGIIO_WRITE_BIT    0x01

/** 
 * @brief Calculation for CRC 5 function.
 * @details This function calculates CRC 5 with parameteres: 
 * @li @c  Width 5 bit
 * @li @c  Polynomial 0x15 ( x5 + x4 + x2 + 1 )
 * @li @c  Initialization 0x1F
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] data_in : Data array to calculate the CRC from.
 * @param[in] len : Data len.
 * @param[in] read_crc : 1-CRC calculation for read (two MSbs excluded), 0-CRC calculation for write.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t digiio_calculate_crc_5 ( uint8_t *data_in, uint8_t len, bool crc_for_read );

void digiio_cfg_setup ( digiio_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rdy  = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->syn  = HAL_PIN_NC;
    cfg->flt  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t digiio_init ( digiio_t *ctx, digiio_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->syn, cfg->syn );

    digital_in_init( &ctx->rdy, cfg->rdy );
    digital_in_init( &ctx->flt, cfg->flt );

    ctx->device_address = DIGIIO_DEVICE_ADDRESS_0;
    ctx->crc_en = DIGIIO_CRC_ENABLED;

    return SPI_MASTER_SUCCESS;
}

err_t digiio_default_cfg ( digiio_t *ctx ) 
{
    err_t error_flag = DIGIIO_OK;

    digiio_disable_output ( ctx );
    Delay_100ms ( );
    digiio_enable_output ( ctx );
    Delay_100ms ( );

    error_flag |= digiio_write_reg ( ctx, DIGIIO_REG_SET_OUT, DIGIIO_SET_OUT_SET_DI4_INPUT | 
                                                              DIGIIO_SET_OUT_SET_DI3_INPUT | 
                                                              DIGIIO_SET_OUT_SET_DI2_OUTPUT | 
                                                              DIGIIO_SET_OUT_SET_DI1_OUTPUT | 
                                                              DIGIIO_SET_OUT_HIGH_O4_LOW | 
                                                              DIGIIO_SET_OUT_HIGH_O3_LOW | 
                                                              DIGIIO_SET_OUT_HIGH_O2_LOW | 
                                                              DIGIIO_SET_OUT_HIGH_O1_LOW );
    
    error_flag |= digiio_write_reg ( ctx, DIGIIO_REG_SET_LED, DIGIIO_SET_LED_SLED4_OFF | 
                                                              DIGIIO_SET_LED_SLED3_OFF | 
                                                              DIGIIO_SET_LED_SLED2_OFF | 
                                                              DIGIIO_SET_LED_SLED1_OFF | 
                                                              DIGIIO_SET_LED_FLED4_OFF | 
                                                              DIGIIO_SET_LED_FLED3_OFF | 
                                                              DIGIIO_SET_LED_FLED2_OFF | 
                                                              DIGIIO_SET_LED_FLED1_OFF );

    error_flag |= digiio_write_reg ( ctx, DIGIIO_REG_OPN_WR_EN, DIGIIO_OPN_WR_EN_G_DRV_EN4_ON | 
                                                                DIGIIO_OPN_WR_EN_G_DRV_EN3_ON | 
                                                                DIGIIO_OPN_WR_EN_G_DRV_EN2_ON | 
                                                                DIGIIO_OPN_WR_EN_G_DRV_EN1_ON | 
                                                                DIGIIO_OPN_WR_EN_OW_OFF_EN4_OFF | 
                                                                DIGIIO_OPN_WR_EN_OW_OFF_EN3_OFF | 
                                                                DIGIIO_OPN_WR_EN_OW_OFF_EN2_OFF | 
                                                                DIGIIO_OPN_WR_EN_OW_OFF_EN1_OFF );
    
    error_flag |= digiio_write_reg ( ctx, DIGIIO_REG_SHT_VDD_EN, DIGIIO_SHT_VDD_EN_VDD_OV_EN4_ON | 
                                                                 DIGIIO_SHT_VDD_EN_VDD_OV_EN3_ON | 
                                                                 DIGIIO_SHT_VDD_EN_VDD_OV_EN2_ON | 
                                                                 DIGIIO_SHT_VDD_EN_VDD_OV_EN1_ON | 
                                                                 DIGIIO_SHT_VDD_EN_SH_VDD_EN4_ON | 
                                                                 DIGIIO_SHT_VDD_EN_SH_VDD_EN3_ON | 
                                                                 DIGIIO_SHT_VDD_EN_SH_VDD_EN2_ON | 
                                                                 DIGIIO_SHT_VDD_EN_SH_VDD_EN1_ON );

    error_flag |= digiio_write_reg ( ctx, DIGIIO_REG_CONFIG_1, DIGIIO_CONFIG_1_LED_CURR_LIM_ON | 
                                                               DIGIIO_CONFIG_1_FLATCH_EN_ON | 
                                                               DIGIIO_CONFIG_1_FILTER_LONG_4_MS | 
                                                               DIGIIO_CONFIG_1_FFILTER_EN_ON | 
                                                               DIGIIO_CONFIG_1_FLED_STRETCH_1_S | 
                                                               DIGIIO_CONFIG_1_SLED_SET_DOI | 
                                                               DIGIIO_CONFIG_1_SLED_SET_DOI );
    
    error_flag |= digiio_write_reg ( ctx, DIGIIO_REG_CONFIG_2, DIGIIO_CONFIG_2_WDTO_OFF | 
                                                               DIGIIO_CONFIG_2_OW_OFF_C_S_60_UA | 
                                                               DIGIIO_CONFIG_2_SHT_VDD_THR_9_V | 
                                                               DIGIIO_CONFIG_2_SYNCH_WD_EN_OFF | 
                                                               DIGIIO_CONFIG_2_VDD_ON_THR_OFF );
    
    error_flag |= digiio_write_reg ( ctx, DIGIIO_REG_CONFIG_DI, DIGIIO_CONFIG_DI_TYP_2_DI_TYPE_1_3 | 
                                                                DIGIIO_CONFIG_DI_VDD_FAULT_DIS_OFF | 
                                                                DIGIIO_CONFIG_DI_VDD_FAULT_SEL_DOI | 
                                                                DIGIIO_CONFIG_DI_ABOVE_VDD_PROT_EN_ON | 
                                                                DIGIIO_CONFIG_DI_OVL_STRETCH_EN_OFF | 
                                                                DIGIIO_CONFIG_DI_OVL_BLANK_OFF );

    error_flag |= digiio_write_reg ( ctx, DIGIIO_REG_CONFIG_DO, DIGIIO_CONFIG_DO_MODE4_HIGH_SIDE | 
                                                                DIGIIO_CONFIG_DO_MODE3_HIGH_SIDE | 
                                                                DIGIIO_CONFIG_DO_MODE2_SIMPLE_PP | 
                                                                DIGIIO_CONFIG_DO_MODE1_SIMPLE_PP );
    
    error_flag |= digiio_write_reg ( ctx, DIGIIO_REG_CURR_LIM, DIGIIO_CURR_LIM_CL4_600_MA | 
                                                               DIGIIO_CURR_LIM_CL3_600_MA | 
                                                               DIGIIO_CURR_LIM_CL2_600_MA | 
                                                               DIGIIO_CURR_LIM_CL1_600_MA );
    
    error_flag |= digiio_write_reg ( ctx, DIGIIO_REG_MASK, DIGIIO_MASK_COMM_ERR_M | 
                                                           DIGIIO_MASK_SUPPLY_ERR_M | 
                                                           DIGIIO_MASK_VDD_OK_M |
                                                           DIGIIO_MASK_SHT_VDD_M |
                                                           DIGIIO_MASK_ABOVE_VDD_M |
                                                           DIGIIO_MASK_OW_OFF_M |
                                                           DIGIIO_MASK_CURR_LIM_M |
                                                           DIGIIO_MASK_OVER_LD_M );

    digiio_sync_io ( ctx );
    Delay_100ms ( );

    return error_flag;
}

void digiio_set_address ( digiio_t *ctx, uint8_t device_address )
{
    ctx->device_address = device_address;
}

err_t digiio_write_reg ( digiio_t *ctx, uint8_t reg, uint8_t data_in )
{
    if ( reg > DIGIIO_REG_MASK )
    {
        return DIGIIO_ERROR;
    }
    err_t error_flag = DIGIIO_OK;
    uint8_t data_buf[ 3 ] = { DUMMY };
    data_buf[ 0 ] = ctx->device_address | ( reg << 1 ) | DIGIIO_WRITE_BIT;
    data_buf[ 1 ] = data_in;

    if ( DIGIIO_CRC_ENABLED == ctx->crc_en )
    {
        data_buf[ 2 ] = digiio_calculate_crc_5 ( data_buf, 3, false );
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, data_buf[ 0 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, data_buf[ 1 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );

    if ( DIGIIO_CRC_ENABLED == ctx->crc_en )
    {
        spi_master_set_default_write_data( &ctx->spi, data_buf[ 2 ] );
        error_flag |= spi_master_read( &ctx->spi, &data_buf[ 2 ], 1 );
    }
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_deselect_device( ctx->chip_select );
    
    if ( ( DIGIIO_CRC_ENABLED == ctx->crc_en ) && 
         ( ( data_buf[ 2 ] & 0x1F ) != digiio_calculate_crc_5 ( data_buf, 3, true ) ) )
    {
        error_flag |= DIGIIO_ERROR;
    }
    return error_flag;
}

err_t digiio_read_reg ( digiio_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( ( reg > DIGIIO_REG_MASK ) || ( NULL == data_out ) )
    {
        return DIGIIO_ERROR;
    }
    err_t error_flag = DIGIIO_OK;
    uint8_t data_buf[ 3 ] = { DUMMY };
    data_buf[ 0 ] = ctx->device_address | ( reg << 1 );

    if ( DIGIIO_CRC_ENABLED == ctx->crc_en )
    {
        data_buf[ 2 ] = digiio_calculate_crc_5 ( data_buf, 3, false );
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, data_buf[ 0 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, data_buf[ 1 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );

    if ( DIGIIO_CRC_ENABLED == ctx->crc_en )
    {
        spi_master_set_default_write_data( &ctx->spi, data_buf[ 2 ] );
        error_flag |= spi_master_read( &ctx->spi, &data_buf[ 2 ], 1 );
    }
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_deselect_device( ctx->chip_select );

    if ( ( DIGIIO_CRC_ENABLED == ctx->crc_en ) && 
         ( ( data_buf[ 2 ] & 0x1F ) != digiio_calculate_crc_5 ( data_buf, 3, true ) ) )
    {
        error_flag |= DIGIIO_ERROR;
    }

    if ( DIGIIO_OK == error_flag )
    {
        *data_out = data_buf[ 1 ];
    }
    return error_flag;
}

void digiio_enable_output ( digiio_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void digiio_disable_output ( digiio_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void digiio_sync_io ( digiio_t *ctx )
{
    digital_out_high ( &ctx->syn );
    Delay_1ms ( );
    digital_out_low ( &ctx->syn );
    Delay_1ms ( );
}

void digiio_set_sync_pin ( digiio_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->syn, state );
}

uint8_t digiio_get_ready_pin ( digiio_t *ctx )
{
    return digital_in_read ( &ctx->rdy );
}

uint8_t digiio_get_fault_pin ( digiio_t *ctx )
{
    return digital_in_read ( &ctx->flt );
}

static uint8_t digiio_calculate_crc_5 ( uint8_t *data_in, uint8_t len, bool crc_for_read )
{
    uint8_t crc5_start = 0x1F;
    uint8_t crc5_poly  = 0x15;
    uint8_t crc_result = crc5_start;
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;

    for ( byte_cnt = 0; byte_cnt < ( len - 1 ); byte_cnt++ )
    {
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( ( true == crc_for_read ) && ( 0 == byte_cnt ) && ( 0 == bit_cnt ) )
            {
                bit_cnt = 2;
            }
            if ( ( ( data_in[ byte_cnt ] >> ( 7 - bit_cnt ) ) & 0x01 ) ^ ( ( crc_result >> 4 ) & 0x01 ) )
            {
                crc_result = ( uint8_t ) ( crc5_poly ^ ( crc_result << 1 ) );
            }
            else
            {
                crc_result = ( uint8_t ) ( crc_result << 1 );
            }
        }
    }

    for ( bit_cnt = 0; bit_cnt < 3; bit_cnt++ )
    {
        if ( ( ( data_in[ byte_cnt ] >> ( 7 - bit_cnt ) ) & 0x01 ) ^ ( ( crc_result >> 4 ) & 0x01 ) )
        {
            crc_result = ( uint8_t ) ( crc5_poly ^ ( crc_result << 1 ) );
        }
        else
        {
            crc_result = ( uint8_t ) ( crc_result << 1 );
        }
    }

    return ( crc_result & 0x1F );
}

// ------------------------------------------------------------------------- END
