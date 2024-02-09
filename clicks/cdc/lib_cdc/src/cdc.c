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
 * @file cdc.c
 * @brief CDC Click Driver.
 */

#include "cdc.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief Standard FW array.
 * @details Definition of standard FW array data generated using ScioSense PCap04 application.
 */
const uint8_t standard_fw[ ] =
{
    0x24, 0x05, 0xA0, 0x01, 0x20, 0x55, 0x42, 0x5C, 0x48, 0xB1, 0x07, 0x92, 0x02, 0x20, 0x13, 0x02, 
    0x20, 0x93, 0x02, 0xB2, 0x02, 0x78, 0x20, 0x54, 0xB3, 0x06, 0x91, 0x00, 0x7F, 0x20, 0x86, 0x20, 
    0x54, 0xB6, 0x03, 0x72, 0x62, 0x20, 0x54, 0xB7, 0x00, 0x00, 0x42, 0x5C, 0xA1, 0x00, 0x49, 0xB0, 
    0x00, 0x49, 0x40, 0xAB, 0x5D, 0x92, 0x1C, 0x90, 0x02, 0x7F, 0x20, 0x86, 0x66, 0x67, 0x76, 0x77, 
    0x66, 0x7A, 0xCF, 0xCD, 0xE6, 0x43, 0xF1, 0x44, 0x29, 0xE0, 0x7A, 0xDC, 0xE7, 0x41, 0x32, 0xAA, 
    0x01, 0x99, 0xFD, 0x7B, 0x01, 0x7A, 0xCF, 0xEB, 0xE6, 0x43, 0xF1, 0x44, 0x29, 0xE0, 0x7A, 0xC1, 
    0xE7, 0x41, 0x32, 0x6A, 0xDE, 0x44, 0x7A, 0xCF, 0xEA, 0xE6, 0x43, 0xF1, 0x44, 0x29, 0xE0, 0x6A, 
    0xDF, 0x44, 0x7A, 0xC4, 0xE7, 0x41, 0x32, 0xAB, 0x05, 0x7A, 0xC1, 0xE1, 0x43, 0xE0, 0x3A, 0x7A, 
    0xC0, 0xE1, 0x43, 0xE0, 0x3A, 0x02, 0x7A, 0xCF, 0xE6, 0xE6, 0x43, 0xF1, 0x44, 0x29, 0xE0, 0x7A, 
    0xEF, 0x44, 0x02, 0x20, 0x9D, 0x84, 0x01, 0x21, 0x2E, 0x21, 0x74, 0x20, 0x37, 0xC8, 0x7A, 0xE7, 
    0x43, 0x49, 0x11, 0x6A, 0xD4, 0x44, 0x7A, 0xC1, 0xD8, 0xE6, 0x43, 0xE9, 0x44, 0x1C, 0x43, 0x13, 
    0xAB, 0x63, 0x6A, 0xDE, 0x41, 0xAB, 0x0B, 0x46, 0x46, 0x46, 0x7A, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xE3, 0x41, 0x32, 0x1C, 0x44, 0xE9, 0x13, 0x6A, 0xD4, 0x13, 0x41, 0xAA, 0xDF, 0x7A, 0xC5, 0xE1, 
    0x43, 0x49, 0xE0, 0x34, 0x7A, 0xCF, 0xE3, 0xE6, 0x43, 0xF1, 0x44, 0x29, 0xE0, 0xDB, 0xC0, 0x27, 
    0xE5, 0x6A, 0xDF, 0x43, 0x7A, 0xC8, 0xE7, 0x41, 0x30, 0xAB, 0x03, 0x86, 0x01, 0x92, 0x37, 0x7A, 
    0xC6, 0xE7, 0x41, 0x7A, 0xFA, 0xE7, 0x43, 0xEA, 0x44, 0x7A, 0xC1, 0xE1, 0xE6, 0x43, 0xE9, 0x44, 
    0x25, 0xE0, 0x7A, 0xC6, 0xE7, 0x41, 0x7A, 0xFA, 0xE7, 0x43, 0xEA, 0x44, 0x7A, 0xC0, 0xE7, 0x43, 
    0xE9, 0x44, 0x25, 0xE0, 0x92, 0x10, 0x7A, 0xE1, 0x44, 0xE2, 0x44, 0xE3, 0x44, 0xE4, 0x44, 0xE5, 
    0x44, 0xE6, 0x44, 0xE7, 0x44, 0xE8, 0x44, 0xC1, 0xD8, 0x24, 0x3E, 0x92, 0xFF, 0x02, 0x7A, 0xCF, 
    0xD7, 0xE6, 0x43, 0xF1, 0x44, 0x7A, 0xD0, 0xE7, 0x43, 0x2A, 0x2A, 0x32, 0xAB, 0x03, 0x42, 0x5C, 
    0x92, 0x03, 0x7A, 0xC0, 0xE1, 0x43, 0xD9, 0x27, 0x90, 0x6A, 0xDF, 0x43, 0x7A, 0xC8, 0xE7, 0x41, 
    0x32, 0xAB, 0x03, 0x86, 0x01, 0x92, 0x11, 0x7A, 0xC2, 0x43, 0x7A, 0xE7, 0x44, 0x6A, 0xC6, 0x44, 
    0x7A, 0xC3, 0x43, 0x7A, 0xE8, 0x44, 0x6A, 0xC7, 0x44, 0xC1, 0xD4, 0x24, 0x57, 0x7A, 0xC8, 0xE1, 
    0x43, 0xE0, 0x3A, 0x02, 0x7A, 0xCF, 0xE7, 0xE6, 0x43, 0xF1, 0x44, 0x29, 0xE0, 0x7A, 0xC7, 0xE1, 
    0x41, 0x6A, 0xD4, 0x45, 0x5A, 0x25, 0x36, 0x46, 0x46, 0x46, 0x46, 0x7A, 0xE9, 0x44, 0x7A, 0xC0, 
    0xE7, 0x43, 0x55, 0x7A, 0xEA, 0x45, 0x7A, 0xE9, 0x51, 0x1C, 0x43, 0x6A, 0xCA, 0x44, 0x1D, 0x43, 
    0x6A, 0xCB, 0x44, 0x7A, 0xC1, 0xCA, 0xE6, 0x43, 0xE9, 0x44, 0x7A, 0xC1, 0xE1, 0x43, 0x7A, 0xCC, 
    0xE0, 0xE6, 0x41, 0x2C, 0x42, 0x7A, 0xC5, 0xE1, 0x43, 0x49, 0xE0, 0x34, 0x7A, 0xC1, 0xCC, 0xE6, 
    0x43, 0xE9, 0x44, 0x7A, 0xC1, 0xE1, 0x43, 0x2C, 0x70, 0x7A, 0xCC, 0x43, 0x7A, 0xCF, 0x44, 0x7A, 
    0xCD, 0x43, 0x7A, 0xCE, 0x44, 0x6A, 0xCA, 0x43, 0xC1, 0xCA, 0x7A, 0xE6, 0x41, 0xE9, 0x45, 0x2B, 
    0xAE, 0xEE, 0x44, 0x7A, 0xC1, 0xCA, 0xE6, 0x43, 0xE9, 0x44, 0x7A, 0xC1, 0xE1, 0x43, 0x7A, 0xCC, 
    0xEC, 0xE6, 0x41, 0x2C, 0x42, 0x7A, 0xC5, 0xE1, 0x43, 0x49, 0xE0, 0x34, 0x7A, 0xC1, 0xCC, 0xE6, 
    0x43, 0xE9, 0x44, 0x7A, 0xC1, 0xE1, 0x43, 0x2C, 0x70, 0x7A, 0xCC, 0x43, 0x7A, 0xCF, 0x44, 0x7A, 
    0xCD, 0x43, 0x7A, 0xCE, 0x44, 0x6A, 0xCB, 0x43, 0xC1, 0xCA, 0x7A, 0xE6, 0x41, 0xE9, 0x45, 0x2B, 
    0xAE, 0xED, 0x44, 0x02
};

/**
 * @brief Standard config array.
 * @details Definition of standard config array data generated using ScioSense PCap04 application.
 * @note
 * - CDC Frontend settings:
 * All CDC channels are enabled in Floating|Single scheme with stray compensation set to both, and
 * discharge/charge resistance set to 10K. C0/C1 port is used for external C reference.
 * - CDC settings:
 * Precharge time 20us, fullcharge time 200us, and discharge time 100us.
 * Conversions cycle is read triggered.
 */
const uint8_t standard_cfg[ ] = 
{
    0x1D, 0x00, 0xF8, 0x10, 0x31, 0x00, 0x3F, 0x20, 0x00, 0xD0, 0x07, 0x00, 0x04, 0x04, 0x00, 0x00,
    0x09, 0x24, 0x00, 0x00, 0x00, 0x01, 0x50, 0x30, 0x73, 0x04, 0x50, 0x08, 0x5A, 0x00, 0x82, 0x08,
    0x08, 0x00, 0x47, 0x40, 0x00, 0x00, 0x00, 0x71, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01
};

void cdc_cfg_setup ( cdc_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->sis  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CDC_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = CDC_DRV_SEL_I2C;
}

void cdc_drv_interface_sel ( cdc_cfg_t *cfg, cdc_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t cdc_init ( cdc_t *ctx, cdc_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( CDC_DRV_SEL_I2C == ctx->drv_sel ) 
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

        digital_out_init( &ctx->sis, cfg->sis );
        digital_out_high( &ctx->sis );
    } 
    else 
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

        digital_out_init( &ctx->sis, cfg->sis );
        digital_out_low( &ctx->sis );
    }

    return CDC_OK;
}

err_t cdc_default_cfg ( cdc_t *ctx ) 
{
    err_t error_flag = CDC_OK;
    if ( CDC_DRV_SEL_SPI == ctx->drv_sel ) 
    {
        CDC_SET_DATA_SAMPLE_EDGE;
    }
    if ( CDC_ERROR == cdc_check_communication ( ctx ) )
    {
        return CDC_ERROR;
    }
    error_flag |= cdc_send_opcode ( ctx, CDC_OPCODE_INITIALIZE );
    Delay_1sec ( );
    error_flag |= cdc_write_memory ( ctx, CDC_MEM_ADDRESS_START, standard_fw, sizeof ( standard_fw ) );
    Delay_1sec ( );
    error_flag |= cdc_write_config ( ctx, CDC_REG_CFG0, standard_cfg, sizeof ( standard_cfg ) );
    Delay_1sec ( );
    return error_flag;
}

err_t cdc_write_memory ( cdc_t *ctx, uint16_t address, const uint8_t *data_in, uint16_t len )
{
    if ( ( NULL == data_in ) || 
         ( address > CDC_MEM_ADDRESS_END ) || 
         ( ( len + address ) > ( CDC_MEM_ADDRESS_END + 1 ) ) )
    {
        return CDC_ERROR;
    }
    err_t error_flag = CDC_OK;
    uint8_t data_buf[ CDC_MEM_ADDRESS_WR_BLOCK_SIZE + 2 ] = { 0 };
    uint16_t mem_address = address;
    uint16_t data_cnt = 0;
    uint8_t wr_block_size = 0;

    while ( data_cnt < len )
    {
        if ( ( len - data_cnt ) >= CDC_MEM_ADDRESS_WR_BLOCK_SIZE )
        {
            wr_block_size = CDC_MEM_ADDRESS_WR_BLOCK_SIZE;
        }
        else
        {
            wr_block_size = len - data_cnt;
        }

        data_buf[ 0 ] = CDC_OPCODE_WR_MEM | ( uint8_t ) ( ( mem_address >> 8 ) & 0x03 );
        data_buf[ 1 ] = ( uint8_t ) ( mem_address & 0xFF );
        memcpy ( &data_buf[ 2 ], &data_in[ data_cnt ], wr_block_size );
        if ( CDC_DRV_SEL_I2C == ctx->drv_sel )
        {
            error_flag = i2c_master_write( &ctx->i2c, data_buf, wr_block_size + 2 );
        }
        else
        {
            spi_master_select_device( ctx->chip_select );
            error_flag = spi_master_write( &ctx->spi, data_buf, wr_block_size + 2 );
            spi_master_deselect_device( ctx->chip_select );
        }
        data_cnt += wr_block_size;
        mem_address += wr_block_size;
    }
    
    return error_flag;
}

err_t cdc_read_memory ( cdc_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len )
{
    if ( ( NULL == data_out ) || 
         ( address > CDC_MEM_ADDRESS_END ) || 
         ( ( len + address ) > ( CDC_MEM_ADDRESS_END + 1 ) ) )
    {
        return CDC_ERROR;
    }
    err_t error_flag = CDC_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = CDC_OPCODE_RD_MEM | ( uint8_t ) ( ( address >> 8 ) & 0x03 );
    data_buf[ 1 ] = ( uint8_t ) ( address & 0xFF );
    if ( CDC_DRV_SEL_I2C == ctx->drv_sel )
    {
        error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
        error_flag |= i2c_master_read( &ctx->i2c, data_out, len );
    }
    else
    {
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_write_then_read( &ctx->spi, data_buf, 2, data_out, len );
        spi_master_deselect_device( ctx->chip_select );
    }
    return error_flag;
}

err_t cdc_write_config ( cdc_t *ctx, uint8_t address, const uint8_t *data_in, uint8_t len )
{
    if ( ( NULL == data_in ) || 
         ( address > CDC_REG_CFG63 ) || 
         ( ( len + address ) > ( CDC_REG_CFG63 + 1 ) ) )
    {
        return CDC_ERROR;
    }
    return cdc_write_memory ( ctx, address + CDC_MEM_ADDRESS_CFG_OFFSET, data_in, len );
}

err_t cdc_read_config ( cdc_t *ctx, uint8_t address, uint8_t *data_out, uint8_t len )
{
    if ( ( NULL == data_out ) || 
         ( address > CDC_REG_CFG63 ) || 
         ( ( len + address ) > ( CDC_REG_CFG63 + 1 ) ) )
    {
        return CDC_ERROR;
    }
    return cdc_read_memory ( ctx, address + CDC_MEM_ADDRESS_CFG_OFFSET, data_out, len );
}

err_t cdc_read_result ( cdc_t *ctx, uint8_t address, uint8_t *data_out, uint8_t len )
{
    if ( ( NULL == data_out ) || 
         ( address > CDC_REG_STATUS_2 ) || 
         ( ( len + address ) > ( CDC_REG_STATUS_2 + 1 ) ) )
    {
        return CDC_ERROR;
    }
    err_t error_flag = CDC_OK;
    uint8_t opcode = CDC_OPCODE_RD_RES | address;
    if ( CDC_DRV_SEL_I2C == ctx->drv_sel )
    {
        error_flag = i2c_master_write_then_read( &ctx->i2c, &opcode, 1, data_out, len );
    }
    else
    {
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_write_then_read( &ctx->spi, &opcode, 1, data_out, len );
        spi_master_deselect_device( ctx->chip_select );
    }
    return error_flag;
}

err_t cdc_send_opcode ( cdc_t *ctx, uint8_t opcode )
{
    err_t error_flag = CDC_OK;
    if ( CDC_DRV_SEL_I2C == ctx->drv_sel )
    {
        error_flag = i2c_master_write ( &ctx->i2c, &opcode, 1 );
    }
    else
    {
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_write( &ctx->spi, &opcode, 1 );
        spi_master_deselect_device( ctx->chip_select );
    }
    return error_flag;
}

err_t cdc_check_communication ( cdc_t *ctx )
{
    err_t error_flag = CDC_OK;
    uint8_t opcode = CDC_OPCODE_TEST_READ;
    uint8_t response = 0;
    if ( CDC_DRV_SEL_I2C == ctx->drv_sel )
    {
        error_flag = i2c_master_write_then_read ( &ctx->i2c, &opcode, 1, &response, 1 );
    }
    else
    {
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_write_then_read( &ctx->spi, &opcode, 1, &response, 1 );
        spi_master_deselect_device( ctx->chip_select );
    }
    if ( CDC_TEST_READ_RES != response )
    {
        error_flag = CDC_ERROR;
    }
    return error_flag;
}

err_t cdc_read_results ( cdc_t *ctx, cdc_results_t *results )
{
    if ( NULL == results )
    {
        return CDC_ERROR;
    }
    uint8_t data_buf[ 35 ] = { 0 };
    uint32_t result_u32 = 0;
    err_t error_flag = cdc_read_result ( ctx, CDC_REG_RES0, data_buf, 35 );
    if ( CDC_OK == error_flag )
    {
        result_u32 = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
                     ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        results->res_0 = ( float ) result_u32 / ( 1ul << CDC_FIXED_POINT_NUM_FRACTIONAL );
        result_u32 = ( ( uint32_t ) data_buf[ 7 ] << 24 ) | ( ( uint32_t ) data_buf[ 6 ] << 16 ) | 
                     ( ( uint16_t ) data_buf[ 5 ] << 8 ) | data_buf[ 4 ];
        results->res_1 = ( float ) result_u32 / ( 1ul << CDC_FIXED_POINT_NUM_FRACTIONAL );
        result_u32 = ( ( uint32_t ) data_buf[ 11 ] << 24 ) | ( ( uint32_t ) data_buf[ 10 ] << 16 ) | 
                     ( ( uint16_t ) data_buf[ 9 ] << 8 ) | data_buf[ 8 ];
        results->res_2 = ( float ) result_u32 / ( 1ul << CDC_FIXED_POINT_NUM_FRACTIONAL );
        result_u32 = ( ( uint32_t ) data_buf[ 15 ] << 24 ) | ( ( uint32_t ) data_buf[ 14 ] << 16 ) | 
                     ( ( uint16_t ) data_buf[ 13 ] << 8 ) | data_buf[ 12 ];
        results->res_3 = ( float ) result_u32 / ( 1ul << CDC_FIXED_POINT_NUM_FRACTIONAL );
        result_u32 = ( ( uint32_t ) data_buf[ 19 ] << 24 ) | ( ( uint32_t ) data_buf[ 18 ] << 16 ) | 
                     ( ( uint16_t ) data_buf[ 17 ] << 8 ) | data_buf[ 16 ];
        results->res_4 = ( float ) result_u32 / ( 1ul << CDC_FIXED_POINT_NUM_FRACTIONAL );
        result_u32 = ( ( uint32_t ) data_buf[ 23 ] << 24 ) | ( ( uint32_t ) data_buf[ 22 ] << 16 ) | 
                     ( ( uint16_t ) data_buf[ 21 ] << 8 ) | data_buf[ 20 ];
        results->res_5 = ( float ) result_u32 / ( 1ul << CDC_FIXED_POINT_NUM_FRACTIONAL );
        result_u32 = ( ( uint32_t ) data_buf[ 27 ] << 24 ) | ( ( uint32_t ) data_buf[ 26 ] << 16 ) | 
                     ( ( uint16_t ) data_buf[ 25 ] << 8 ) | data_buf[ 24 ];
        results->res_6 = ( float ) result_u32 / ( 1ul << CDC_FIXED_POINT_NUM_FRACTIONAL );
        result_u32 = ( ( uint32_t ) data_buf[ 31 ] << 24 ) | ( ( uint32_t ) data_buf[ 30 ] << 16 ) | 
                     ( ( uint16_t ) data_buf[ 29 ] << 8 ) | data_buf[ 28 ];
        results->res_7 = ( float ) result_u32 / ( 1ul << CDC_FIXED_POINT_NUM_FRACTIONAL );
        results->status_0 = data_buf[ 32 ] & 0xF7;
        results->status_1 = data_buf[ 33 ] & 0x0F;
        results->status_2 = data_buf[ 34 ] & 0x7F;
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END
