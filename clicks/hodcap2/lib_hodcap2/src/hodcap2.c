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
 * @file hodcap2.c
 * @brief HOD CAP 2 Click Driver.
 */

#include "hodcap2.h"

/**
 * @brief HOD CAP 2 SPI command data.
 * @details Definition of SPI command data of HOD CAP 2 Click.
 */
#define HODCAP2_SPI_DUMMY           0x00
#define HODCAP2_SPI_RW_WRITE        0x00
#define HODCAP2_SPI_RW_READ         0x80
#define HODCAP2_SPI_RW_MASK         0x80
#define HODCAP2_SPI_REG_MASK        0x7C
#define HODCAP2_SPI_SR_MASK         0x02
#define HODCAP2_SPI_PARITY_BIT      0x01

/**
 * @brief Three bytes to dword macro.
 * @details Definition of three bytes to dword conversion.
 */
#define THREE_BYTES_TO_DWORD( x )  ( ( ( uint32_t ) x[ 0 ] << 16 ) | ( ( uint16_t ) x[ 1 ] << 8 ) | x[ 2 ] )

/**
 * @brief HOD CAP 2 calculate parity bit function.
 * @details This function calculates the parity bit.
 * @param[in] data_in : 24-bit SPI frame data from which it will calculate the parity bit.
 * @return @li @c 0 - Even parity,
 *         @li @c 1 - ODD parity.
 * @note None.
 */
static uint8_t hodcap2_get_parity ( uint32_t data_in );

void hodcap2_cfg_setup ( hodcap2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->trg  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t hodcap2_init ( hodcap2_t *ctx, hodcap2_cfg_t *cfg ) 
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, HODCAP2_SPI_DUMMY ) ) 
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

    digital_in_init( &ctx->trg, cfg->trg );
    ctx->bank = 255;
    Delay_100ms ( );

    return SPI_MASTER_SUCCESS;
}

err_t hodcap2_default_cfg ( hodcap2_t *ctx ) 
{
    err_t error_flag = HODCAP2_OK;
    // Power up sequence with stop and clear not init commands
    error_flag |= hodcap2_select_bank ( ctx, HODCAP2_BANK_0 );
    error_flag |= hodcap2_send_cmd ( ctx, HODCAP2_CMD_STOP, HODCAP2_TABLE_1 );
    error_flag |= hodcap2_send_cmd ( ctx, HODCAP2_CMD_CLEAR_NOT_INIT, HODCAP2_TABLE_1 );
    
    // Read unique ID
    if ( HODCAP2_OK != hodcap2_read_unique_id ( ctx, ctx->unique_id ) )
    {
        return HODCAP2_ERROR;
    }
    
    // Initialize and enable first 5 table measurements
    error_flag |= hodcap2_send_cmd ( ctx, HODCAP2_CMD_INIT_MODE, HODCAP2_TABLE_1 );
    error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_B0_MEMT_SEQ, HODCAP2_MEMT_SEQ_TABLE_5_EN | 
                                                                    HODCAP2_MEMT_SEQ_TABLE_4_EN | 
                                                                    HODCAP2_MEMT_SEQ_TABLE_3_EN | 
                                                                    HODCAP2_MEMT_SEQ_TABLE_2_EN | 
                                                                    HODCAP2_MEMT_SEQ_TABLE_1_EN );
    error_flag |= hodcap2_clear_diag ( ctx, NULL );

    // Assign and configure SEN0 to table 1 measurement
    error_flag |= hodcap2_select_bank ( ctx, HODCAP2_BANK_1 );
    error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_BX_MEMT_CFG1_TBLX, HODCAP2_MEMT_CFG1_TBLX_PRESCALER_1 | 
                                                                          HODCAP2_MEMT_CFG1_TBLX_FREQ_DEF | 
                                                                          HODCAP2_MEMT_CFG1_TBLX_SEN_E0_SEL );
    error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_BX_MEMT_CFG3_TBLX, HODCAP2_MEMT_CFG3_TBLX_PGA_OV_ISET_DEF | 
                                                                          HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G11 | 
                                                                          HODCAP2_MEMT_CFG3_TBLX_ACCU_8 );
    
    // Assign and configure SEN1 to table 2 measurement
    error_flag |= hodcap2_select_bank ( ctx, HODCAP2_BANK_2 );
    error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_BX_MEMT_CFG1_TBLX, HODCAP2_MEMT_CFG1_TBLX_PRESCALER_1 | 
                                                                          HODCAP2_MEMT_CFG1_TBLX_FREQ_DEF | 
                                                                          HODCAP2_MEMT_CFG1_TBLX_SEN_E1_SEL );
    error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_BX_MEMT_CFG3_TBLX, HODCAP2_MEMT_CFG3_TBLX_PGA_OV_ISET_DEF | 
                                                                          HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G11 | 
                                                                          HODCAP2_MEMT_CFG3_TBLX_ACCU_8 );
    
    // Assign and configure SEN2 to table 3 measurement
    error_flag |= hodcap2_select_bank ( ctx, HODCAP2_BANK_3 );
    error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_BX_MEMT_CFG1_TBLX, HODCAP2_MEMT_CFG1_TBLX_PRESCALER_1 | 
                                                                          HODCAP2_MEMT_CFG1_TBLX_FREQ_DEF | 
                                                                          HODCAP2_MEMT_CFG1_TBLX_SEN_E2_SEL );
    error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_BX_MEMT_CFG3_TBLX, HODCAP2_MEMT_CFG3_TBLX_PGA_OV_ISET_DEF | 
                                                                          HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G11 | 
                                                                          HODCAP2_MEMT_CFG3_TBLX_ACCU_8 );
    
    // Assign and configure SEN3 to table 4 measurement
    error_flag |= hodcap2_select_bank ( ctx, HODCAP2_BANK_4 );
    error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_BX_MEMT_CFG1_TBLX, HODCAP2_MEMT_CFG1_TBLX_PRESCALER_1 | 
                                                                          HODCAP2_MEMT_CFG1_TBLX_FREQ_DEF | 
                                                                          HODCAP2_MEMT_CFG1_TBLX_SEN_E3_SEL );
    error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_BX_MEMT_CFG3_TBLX, HODCAP2_MEMT_CFG3_TBLX_PGA_OV_ISET_DEF | 
                                                                          HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G11 | 
                                                                          HODCAP2_MEMT_CFG3_TBLX_ACCU_8 );
    
    // Assign and configure REF to table 5 measurement
    error_flag |= hodcap2_select_bank ( ctx, HODCAP2_BANK_5 );
    error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_BX_MEMT_CFG1_TBLX, HODCAP2_MEMT_CFG1_TBLX_PRESCALER_1 | 
                                                                          HODCAP2_MEMT_CFG1_TBLX_FREQ_DEF | 
                                                                          HODCAP2_MEMT_CFG1_TBLX_SEN_REF_SEL );
    error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_BX_MEMT_CFG3_TBLX, HODCAP2_MEMT_CFG3_TBLX_PGA_OV_ISET_DEF | 
                                                                          HODCAP2_MEMT_CFG3_TBLX_PGA_GAIN_ISET_G11 | 
                                                                          HODCAP2_MEMT_CFG3_TBLX_ACCU_8 );
    
    // Go to wait mode
    error_flag |= hodcap2_select_bank ( ctx, HODCAP2_BANK_0 );
    error_flag |= hodcap2_send_cmd ( ctx, HODCAP2_CMD_STOP, HODCAP2_TABLE_1 );

    return error_flag;
}

err_t hodcap2_write_reg ( hodcap2_t *ctx, uint8_t reg, uint16_t data_in )
{
    err_t error_flag = HODCAP2_OK;
    uint8_t wr_buf[ 3 ] = { 0 };
    uint8_t rd_buf[ 3 ] = { 0 };
    wr_buf[ 0 ] = ( ( reg << 2 ) & HODCAP2_SPI_REG_MASK );
    wr_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    wr_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    wr_buf[ 0 ] |= hodcap2_get_parity ( THREE_BYTES_TO_DWORD ( wr_buf ) );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, wr_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, rd_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    if ( ( ( rd_buf[ 0 ] & HODCAP2_SPI_PARITY_BIT ) != hodcap2_get_parity ( THREE_BYTES_TO_DWORD ( rd_buf ) ) ) || 
         ( ( wr_buf[ 0 ] & HODCAP2_SPI_REG_MASK ) != ( rd_buf[ 0 ] & HODCAP2_SPI_REG_MASK ) ) )
    {
        error_flag |= HODCAP2_ERROR;
    }
    return error_flag;
}

err_t hodcap2_read_reg ( hodcap2_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = HODCAP2_OK;
    uint8_t wr_buf[ 3 ] = { 0 };
    uint8_t rd_buf[ 3 ] = { 0 };
    wr_buf[ 0 ] = HODCAP2_SPI_RW_READ | ( ( reg << 2 ) & HODCAP2_SPI_REG_MASK );
    wr_buf[ 1 ] = HODCAP2_SPI_DUMMY;
    wr_buf[ 2 ] = HODCAP2_SPI_DUMMY;
    wr_buf[ 0 ] |= hodcap2_get_parity ( THREE_BYTES_TO_DWORD ( wr_buf ) );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, wr_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, rd_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    if ( ( ( rd_buf[ 0 ] & HODCAP2_SPI_PARITY_BIT ) != hodcap2_get_parity ( THREE_BYTES_TO_DWORD ( rd_buf ) ) ) || 
         ( ( wr_buf[ 0 ] & HODCAP2_SPI_REG_MASK ) != ( rd_buf[ 0 ] & HODCAP2_SPI_REG_MASK ) ) )
    {
        error_flag |= HODCAP2_ERROR;
    }
    if ( HODCAP2_OK == error_flag )
    {
        if ( NULL != data_out )
        {
            *data_out = ( ( uint16_t ) rd_buf[ 1 ] << 8 ) | rd_buf[ 2 ];
        }
    }
    return error_flag;
}

uint8_t hodcap2_get_trg_pin ( hodcap2_t *ctx )
{
    return digital_in_read ( &ctx->trg );
}

err_t hodcap2_select_bank ( hodcap2_t *ctx, uint8_t bank )
{
    err_t error_flag = HODCAP2_OK;
    uint16_t bank_sel = 0;
    if ( bank > HODCAP2_BANK_17 )
    {
        error_flag = HODCAP2_ERROR;
    }
    if ( ( ctx->bank != bank ) && ( HODCAP2_OK == error_flag ) )
    {
        ctx->bank = bank;
        bank_sel = HODCAP2_BANK_SEL_ACCESS_WORD | bank;
        error_flag = hodcap2_write_reg ( ctx, HODCAP2_REG_BANK_SEL, bank_sel );
        Delay_1ms ( );
    }
    return error_flag;
}

err_t hodcap2_read_unique_id ( hodcap2_t *ctx, uint16_t *unique_id )
{
    err_t error_flag = HODCAP2_OK;
    uint8_t old_bank = ctx->bank;
    if ( old_bank > HODCAP2_BANK_17 )
    {
        old_bank = HODCAP2_BANK_0;
    }
    if ( HODCAP2_BANK_17 != ctx->bank )
    {
        error_flag |= hodcap2_select_bank ( ctx, HODCAP2_BANK_17 );
    }
    if ( HODCAP2_OK == error_flag )
    {
        error_flag |= hodcap2_read_reg ( ctx, HODCAP2_REG_B17_CHIP_ID_0, &unique_id[ 0 ] );
    }
    if ( HODCAP2_OK == error_flag )
    {
        error_flag |= hodcap2_read_reg ( ctx, HODCAP2_REG_B17_CHIP_ID_1, &unique_id[ 1 ] );
    }
    if ( HODCAP2_OK == error_flag )
    {
        error_flag |= hodcap2_read_reg ( ctx, HODCAP2_REG_B17_CHIP_ID_2, &unique_id[ 2 ] );
    }
    if ( HODCAP2_OK == error_flag )
    {
        if ( old_bank != ctx->bank )
        {
            error_flag |= hodcap2_select_bank ( ctx, old_bank );
        }
    }
    return error_flag;
}

err_t hodcap2_send_cmd ( hodcap2_t *ctx, uint8_t cmd, uint8_t start_table )
{
    err_t error_flag = HODCAP2_OK;
    uint16_t reg_data = 0;
    uint8_t old_bank = ctx->bank;
    if ( ( cmd > HODCAP2_CMD_LOW_PWR_MODE ) || ( start_table > HODCAP2_TABLE_16 ) )
    {
        return HODCAP2_ERROR;
    }
    if ( old_bank > HODCAP2_BANK_17 )
    {
        old_bank = HODCAP2_BANK_0;
    }
    if ( HODCAP2_BANK_0 != ctx->bank )
    {
        error_flag |= hodcap2_select_bank ( ctx, HODCAP2_BANK_0 );
    }
    if ( HODCAP2_OK == error_flag )
    {
        reg_data = ( ( uint16_t ) cmd << 8 ) | ( start_table << 4 );
        error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_B0_MEMT_CTL_2, reg_data );
        Delay_1ms ( );
    }
    if ( HODCAP2_OK == error_flag )
    {
        if ( old_bank != ctx->bank )
        {
            error_flag |= hodcap2_select_bank ( ctx, old_bank );
        }
    }
    return error_flag;
}

err_t hodcap2_clear_diag ( hodcap2_t *ctx, uint16_t *diag )
{
    err_t error_flag = HODCAP2_OK;
    uint16_t reg_data[ 3 ] = { 0 };
    uint8_t old_bank = ctx->bank;
    if ( old_bank > HODCAP2_BANK_17 )
    {
        old_bank = HODCAP2_BANK_0;
    }
    if ( HODCAP2_BANK_0 != ctx->bank )
    {
        error_flag |= hodcap2_select_bank ( ctx, HODCAP2_BANK_0 );
    }
    if ( HODCAP2_OK == error_flag )
    {
        error_flag |= hodcap2_read_reg ( ctx, HODCAP2_REG_B0_DIAG_REG_1, &reg_data[ 0 ] );
        if ( ( HODCAP2_OK == error_flag ) && reg_data[ 0 ] )
        {
            error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_B0_DIAG_REG_1, reg_data[ 0 ] );
        }
    }
    if ( HODCAP2_OK == error_flag )
    {
        error_flag |= hodcap2_read_reg ( ctx, HODCAP2_REG_B0_DIAG_REG_2, &reg_data[ 1 ] );
        if ( ( HODCAP2_OK == error_flag ) && reg_data[ 1 ] )
        {
            error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_B0_DIAG_REG_2, reg_data[ 1 ] );
        }
    }
    if ( HODCAP2_OK == error_flag )
    {
        error_flag |= hodcap2_read_reg ( ctx, HODCAP2_REG_B0_DIAG_REG_3, &reg_data[ 2 ] );
        if ( ( HODCAP2_OK == error_flag ) && reg_data[ 2 ] )
        {
            error_flag |= hodcap2_write_reg ( ctx, HODCAP2_REG_B0_DIAG_REG_3, reg_data[ 2 ] );
        }
    }
    if ( HODCAP2_OK == error_flag )
    {
        if ( old_bank != ctx->bank )
        {
            error_flag |= hodcap2_select_bank ( ctx, old_bank );
        }
    }
    if ( ( HODCAP2_OK == error_flag ) && ( NULL != diag ) )
    {
        diag[ 0 ] = reg_data[ 0 ];
        diag[ 1 ] = reg_data[ 1 ];
        diag[ 2 ] = reg_data[ 2 ];
    }
    return error_flag;
}

err_t hodcap2_read_measurement ( hodcap2_t *ctx, uint8_t table, uint16_t *data_out )
{
    err_t error_flag = HODCAP2_OK;
    uint16_t reg_data = 0;
    uint8_t old_bank = ctx->bank;
    if ( table > HODCAP2_TABLE_16 )
    {
        return HODCAP2_ERROR;
    }
    if ( HODCAP2_OK == error_flag )
    {
        error_flag |= hodcap2_send_cmd ( ctx, HODCAP2_CMD_SINGLE_MODE, table );
    }
    if ( HODCAP2_OK == error_flag )
    {
        error_flag |= hodcap2_send_cmd ( ctx, HODCAP2_CMD_STOP, table );
    }
    if ( HODCAP2_OK == error_flag )
    {
        error_flag |= hodcap2_read_reg ( ctx, HODCAP2_REG_MEMT_DATA_1 + table, &reg_data );
    }
    if ( ( HODCAP2_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = reg_data >> 1;
    }
    return error_flag;
}

static uint8_t hodcap2_get_parity ( uint32_t data_in )
{
    uint32_t temp_data = data_in & 0xFEFFFF;
    uint8_t parity = 0;
    while ( temp_data )
    {
        parity += ( temp_data & 1 );
        temp_data >>= 1;
    }
    return ( parity & 1 );
}

// ------------------------------------------------------------------------- END
