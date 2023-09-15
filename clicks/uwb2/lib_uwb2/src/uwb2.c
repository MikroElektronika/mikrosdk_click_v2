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
 * @file uwb2.c
 * @brief UWB 2 Click Driver.
 */

#include "uwb2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void uwb2_cfg_setup ( uwb2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->wup  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->ext  = HAL_PIN_NC;
    cfg->irq  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t uwb2_init ( uwb2_t *ctx, uwb2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->wup, cfg->wup );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_low( &ctx->rst );
    digital_out_low( &ctx->wup );

    digital_in_init( &ctx->ext, cfg->ext );
    digital_in_init( &ctx->irq, cfg->irq );

    return SPI_MASTER_SUCCESS;
}

err_t uwb2_default_cfg ( uwb2_t *ctx ) 
{
    err_t error_flag = UWB2_OK;
    uwb2_chip_cfg_t config = { 0 };
    error_flag |= uwb2_power_up_ic ( ctx );
    if ( UWB2_OK == error_flag )
    {
        error_flag |= uwb2_initialize_ic ( ctx );
    }
    if ( UWB2_OK == error_flag )
    {
        error_flag |= uwb2_set_rx_tx_leds ( ctx, UWB2_RX_TX_LEDS_ENABLE );
    }
    if ( UWB2_OK == error_flag )
    {
        config.channel = UWB2_DEFAULT_CHANNEL;
        config.tx_plen = UWB2_DEFAULT_TX_PLEN;
        config.pac = UWB2_DEFAULT_PAC;
        config.tx_code = UWB2_DEFAULT_TX_CODE;
        config.rx_code = UWB2_DEFAULT_RX_CODE;
        config.sfd_type = UWB2_DEFAULT_SFD_TYPE;
        config.data_rate = UWB2_DEFAULT_DATA_RATE;
        config.sfd_to = UWB2_DEFAULT_SFD_TO;
        error_flag |= uwb2_configure_ic ( ctx, &config );
    }
    return error_flag;
}

err_t uwb2_send_cmd ( uwb2_t *ctx, uint8_t cmd )
{
    err_t error_flag = UWB2_OK;
    uint8_t data_wr = 0;
    if ( cmd > UWB2_CMD_DB_TOGGLE )
    {
        return UWB2_ERROR;
    }
    data_wr = ( uint8_t ) ( ( UWB2_SPI_WRITE | UWB2_SPI_FAST_CMD ) >> 8 ) | ( cmd << 1 );
    spi_master_select_device ( ctx->chip_select );
    error_flag |= spi_master_write ( &ctx->spi, &data_wr, 1 );
    spi_master_deselect_device ( ctx->chip_select );
    return error_flag;
}

err_t uwb2_read_reg ( uwb2_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len )
{
    err_t error_flag = UWB2_OK;
    uint8_t data_wr[ 2 ] = { 0 };
    uint16_t header = 0;
    if ( ( reg > UWB2_REG_PTR_OFFSET_B ) || ( NULL == data_out ) )
    {
        return UWB2_ERROR;
    }
    header = ( ( reg << 1 ) & UWB2_SPI_BASE_ADDR_MASK ) | ( ( reg << 2 ) & UWB2_SPI_SUB_ADDR_MASK );
    spi_master_select_device ( ctx->chip_select );
    if ( header & UWB2_SPI_SUB_ADDR_MASK )
    {
        header |= UWB2_SPI_16BIT_ADDR;
        data_wr[ 0 ] = ( uint8_t ) ( ( header >> 8 ) & 0xFF );
        data_wr[ 1 ] = ( uint8_t ) ( header & 0xFF );
        error_flag |= spi_master_write ( &ctx->spi, data_wr, 2 );
    }
    else
    {
        data_wr[ 0 ] = ( uint8_t ) ( ( header >> 8 ) & 0xFF );
        error_flag |= spi_master_write ( &ctx->spi, data_wr, 1 );
    }
    error_flag |= spi_master_read ( &ctx->spi, data_out, len );
    spi_master_deselect_device ( ctx->chip_select );
    return error_flag;
}

err_t uwb2_write_reg ( uwb2_t *ctx, uint16_t reg, uint8_t *data_in, uint16_t len )
{
    err_t error_flag = UWB2_OK;
    uint8_t data_wr[ 2 ] = { 0 };
    uint16_t header = 0;
    if ( ( reg > UWB2_REG_PTR_OFFSET_B ) || ( NULL == data_in ) )
    {
        return UWB2_ERROR;
    }
    header = UWB2_SPI_WRITE | 
             ( ( reg << 1 ) & UWB2_SPI_BASE_ADDR_MASK ) | ( ( reg << 2 ) & UWB2_SPI_SUB_ADDR_MASK );
    spi_master_select_device ( ctx->chip_select );
    if ( header & UWB2_SPI_SUB_ADDR_MASK )
    {
        header |= UWB2_SPI_16BIT_ADDR;
        data_wr[ 0 ] = ( uint8_t ) ( ( header >> 8 ) & 0xFF );
        data_wr[ 1 ] = ( uint8_t ) ( header & 0xFF );
        error_flag |= spi_master_write ( &ctx->spi, data_wr, 2 );
    }
    else
    {
        data_wr[ 0 ] = ( uint8_t ) ( ( header >> 8 ) & 0xFF );
        error_flag |= spi_master_write ( &ctx->spi, data_wr, 1 );
    }
    error_flag |= spi_master_write ( &ctx->spi, data_in, len );
    spi_master_deselect_device ( ctx->chip_select );
    return error_flag;
}

err_t uwb2_read_reg_8bit ( uwb2_t *ctx, uint16_t reg, uint8_t *data_out )
{
    uint8_t data_rd = 0;
    err_t error_flag = uwb2_read_reg ( ctx, reg, &data_rd, 1 );
    if ( UWB2_OK == error_flag )
    {
        *data_out = data_rd;
    }
    return error_flag;
}

err_t uwb2_read_reg_16bit ( uwb2_t *ctx, uint16_t reg, uint16_t *data_out )
{
    uint8_t data_rd[ 2 ] = { 0 };
    err_t error_flag = uwb2_read_reg ( ctx, reg, data_rd, 2 );
    if ( UWB2_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_rd[ 1 ] << 8 ) | data_rd[ 0 ];
    }
    return error_flag;
}

err_t uwb2_read_reg_32bit ( uwb2_t *ctx, uint16_t reg, uint32_t *data_out )
{
    uint8_t data_rd[ 4 ] = { 0 };
    err_t error_flag = uwb2_read_reg ( ctx, reg, data_rd, 4 );
    if ( UWB2_OK == error_flag )
    {
        *data_out = ( ( uint32_t ) data_rd[ 3 ] << 24 ) | ( ( uint32_t ) data_rd[ 2 ] << 16 ) | 
                    ( ( uint16_t ) data_rd[ 1 ] << 8 ) | data_rd[ 0 ];
    }
    return error_flag;
}

err_t uwb2_write_reg_8bit ( uwb2_t *ctx, uint16_t reg, uint8_t data_in )
{
    return uwb2_write_reg ( ctx, reg, &data_in, 1 );
}

err_t uwb2_write_reg_16bit ( uwb2_t *ctx, uint16_t reg, uint16_t data_in )
{
    uint8_t data_wr[ 2 ] = { 0 };
    data_wr[ 0 ] = ( uint8_t ) ( data_in & 0xFF );
    data_wr[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return uwb2_write_reg ( ctx, reg, data_wr, 2 );
}

err_t uwb2_write_reg_32bit ( uwb2_t *ctx, uint16_t reg, uint32_t data_in )
{
    uint8_t data_wr[ 4 ] = { 0 };
    data_wr[ 0 ] = ( uint8_t ) ( data_in & 0xFF );
    data_wr[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_wr[ 2 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_wr[ 3 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    return uwb2_write_reg ( ctx, reg, data_wr, 4 );
}

err_t uwb2_modify_reg_8bit ( uwb2_t *ctx, uint16_t reg, uint8_t and_mask, uint8_t or_mask )
{
    err_t error_flag = UWB2_OK;
    uint8_t data_wr[ 4 ] = { 0 };
    uint16_t header = 0;
    if ( reg > UWB2_REG_PTR_OFFSET_B )
    {
        return UWB2_ERROR;
    }
    header = UWB2_SPI_WRITE | UWB2_SPI_16BIT_ADDR | UWB2_SPI_MASKED_WRITE_8BIT |
             ( ( reg << 1 ) & UWB2_SPI_BASE_ADDR_MASK ) | ( ( reg << 2 ) & UWB2_SPI_SUB_ADDR_MASK );
    data_wr[ 0 ] = ( uint8_t ) ( ( header >> 8 ) & 0xFF );
    data_wr[ 1 ] = ( uint8_t ) ( header & 0xFF );
    data_wr[ 2 ] = and_mask;
    data_wr[ 3 ] = or_mask;
    spi_master_select_device ( ctx->chip_select );
    error_flag |= spi_master_write ( &ctx->spi, data_wr, 4 );
    spi_master_deselect_device ( ctx->chip_select );
    return error_flag;
}

err_t uwb2_modify_reg_16bit ( uwb2_t *ctx, uint16_t reg, uint16_t and_mask, uint16_t or_mask )
{
    err_t error_flag = UWB2_OK;
    uint8_t data_wr[ 6 ] = { 0 };
    uint16_t header = 0;
    if ( reg > UWB2_REG_PTR_OFFSET_B )
    {
        return UWB2_ERROR;
    }
    header = UWB2_SPI_WRITE | UWB2_SPI_16BIT_ADDR | UWB2_SPI_MASKED_WRITE_16BIT |
             ( ( reg << 1 ) & UWB2_SPI_BASE_ADDR_MASK ) | ( ( reg << 2 ) & UWB2_SPI_SUB_ADDR_MASK );
    data_wr[ 0 ] = ( uint8_t ) ( ( header >> 8 ) & 0xFF );
    data_wr[ 1 ] = ( uint8_t ) ( header & 0xFF );
    data_wr[ 2 ] = ( uint8_t ) ( and_mask & 0xFF );
    data_wr[ 3 ] = ( uint8_t ) ( ( and_mask >> 8 ) & 0xFF );
    data_wr[ 4 ] = ( uint8_t ) ( or_mask & 0xFF );
    data_wr[ 5 ] = ( uint8_t ) ( ( or_mask >> 8 ) & 0xFF );
    spi_master_select_device ( ctx->chip_select );
    error_flag |= spi_master_write ( &ctx->spi, data_wr, 6 );
    spi_master_deselect_device ( ctx->chip_select );
    return error_flag;
}

err_t uwb2_modify_reg_32bit ( uwb2_t *ctx, uint16_t reg, uint32_t and_mask, uint32_t or_mask )
{
    err_t error_flag = UWB2_OK;
    uint8_t data_wr[ 10 ] = { 0 };
    uint16_t header = 0;
    if ( reg > UWB2_REG_PTR_OFFSET_B )
    {
        return UWB2_ERROR;
    }
    header = UWB2_SPI_WRITE | UWB2_SPI_16BIT_ADDR | UWB2_SPI_MASKED_WRITE_32BIT |
             ( ( reg << 1 ) & UWB2_SPI_BASE_ADDR_MASK ) | ( ( reg << 2 ) & UWB2_SPI_SUB_ADDR_MASK );
    data_wr[ 0 ] = ( uint8_t ) ( ( header >> 8 ) & 0xFF );
    data_wr[ 1 ] = ( uint8_t ) ( header & 0xFF );
    data_wr[ 2 ] = ( uint8_t ) ( and_mask & 0xFF );
    data_wr[ 3 ] = ( uint8_t ) ( ( and_mask >> 8 ) & 0xFF );
    data_wr[ 4 ] = ( uint8_t ) ( ( and_mask >> 16 ) & 0xFF );
    data_wr[ 5 ] = ( uint8_t ) ( ( and_mask >> 24 ) & 0xFF );
    data_wr[ 6 ] = ( uint8_t ) ( or_mask & 0xFF );
    data_wr[ 7 ] = ( uint8_t ) ( ( or_mask >> 8 ) & 0xFF );
    data_wr[ 8 ] = ( uint8_t ) ( ( or_mask >> 16 ) & 0xFF );
    data_wr[ 9 ] = ( uint8_t ) ( ( or_mask >> 24 ) & 0xFF );
    spi_master_select_device ( ctx->chip_select );
    error_flag |= spi_master_write ( &ctx->spi, data_wr, 10 );
    spi_master_deselect_device ( ctx->chip_select );
    return error_flag;
}

err_t uwb2_read_otp ( uwb2_t *ctx, uint16_t address, uint32_t *data_out, uint16_t len )
{
    err_t error_flag = UWB2_OK;
    uint32_t data_rd = 0;
    if ( ( address + len ) > ( UWB2_OTP_ADR_AES_KEY_END + 1 ) || ( NULL == data_out ) )
    {
        return UWB2_ERROR;
    }
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        // Set manual access mode
        error_flag |= uwb2_write_reg_16bit ( ctx, UWB2_REG_OTP_CFG, UWB2_OTP_CFG_OTP_MAN_MASK );
        // Set the address
        error_flag |= uwb2_write_reg_16bit ( ctx, UWB2_REG_OTP_ADDR, address + cnt );
        // Assert the read strobe
        error_flag |= uwb2_write_reg_16bit ( ctx, UWB2_REG_OTP_CFG, UWB2_OTP_CFG_OTP_READ_MASK );
        // Attempt a read from OTP address
        error_flag |= uwb2_read_reg_32bit ( ctx, UWB2_REG_OTP_RDATA, &data_rd );
        if ( UWB2_OK != error_flag )
        {
            break;
        }
        data_out[ cnt ] = data_rd;
    }
    return error_flag;
}

void uwb2_set_rst_pin ( uwb2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void uwb2_set_wup_pin ( uwb2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wup, state );
}

uint8_t uwb2_get_ext_pin ( uwb2_t *ctx )
{
    return digital_in_read ( &ctx->ext );
}

uint8_t uwb2_get_irq_pin ( uwb2_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}

void uwb2_reset_device ( uwb2_t *ctx )
{
    digital_out_low ( &ctx->wup );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->wup );
    Delay_1ms ( );
    digital_out_low ( &ctx->wup );
}

err_t uwb2_check_communication ( uwb2_t *ctx )
{
    uint32_t dev_id = 0;
    if ( UWB2_OK == uwb2_read_reg_32bit ( ctx, UWB2_REG_DEV_ID, &dev_id ) )
    {
        if ( ( UWB2_DEV_ID & ( UWB2_DEV_ID_RIDTAG_MASK | UWB2_DEV_ID_MODEL_MASK ) ) == 
             ( dev_id & ( UWB2_DEV_ID_RIDTAG_MASK | UWB2_DEV_ID_MODEL_MASK ) ) )
        {
            return UWB2_OK;
        }
    }
    return UWB2_ERROR;
}

err_t uwb2_power_up_ic ( uwb2_t *ctx )
{
    uint32_t sys_status = 0;
    uint32_t timeout_cnt = 0;
    uwb2_reset_device ( ctx );
    Delay_100ms ( );
    if ( UWB2_ERROR == uwb2_check_communication ( ctx ) )
    {
        return UWB2_ERROR;
    }
    // Need to make sure the IC is in IDLE_RC before proceeding.
    while ( UWB2_SYS_STATUS_LO_RCINIT_MASK != ( sys_status & UWB2_SYS_STATUS_LO_RCINIT_MASK ) )
    {
        if ( ( UWB2_OK != uwb2_read_reg_32bit ( ctx, UWB2_REG_SYS_STATUS_LO, &sys_status ) ) || 
             ( UWB2_WAIT_TIMEOUT_MS == ++timeout_cnt ) )
        {
            return UWB2_ERROR;
        }
    }
    return UWB2_OK;
}

err_t uwb2_initialize_ic ( uwb2_t *ctx )
{
    err_t error_flag = UWB2_OK;
    uint32_t data_rd32 = 0;
    uint32_t ldo_tune_lo = 0;
    uint32_t ldo_tune_hi = 0;
    uint8_t bias_tune = 0;
    uint8_t init_xtrim = 0;
    // Read LDO_TUNE and BIAS_TUNE from OTP
    error_flag |= uwb2_read_otp ( ctx, UWB2_OTP_ADR_LDOTUNE_LO, &ldo_tune_lo, 1 );
    error_flag |= uwb2_read_otp ( ctx, UWB2_OTP_ADR_LDOTUNE_LO, &ldo_tune_hi, 1 );
    error_flag |= uwb2_read_otp ( ctx, UWB2_OTP_ADR_BIASTUNE, &data_rd32, 1 );
    bias_tune = ( uint8_t ) ( ( data_rd32 >> 16 ) & UWB2_BIAS_CTRL_MASK );
    
    if ( ldo_tune_lo && ldo_tune_hi && bias_tune )
    {
        error_flag |= uwb2_modify_reg_16bit ( ctx, UWB2_REG_OTP_CFG, UWB2_MASK_ALL_32, 
                                              UWB2_OTP_CFG_LDO_KICK_MASK | UWB2_OTP_CFG_BIAS_KICK_MASK );
        error_flag |= uwb2_modify_reg_8bit ( ctx, UWB2_REG_BIAS_CTRL, ~UWB2_BIAS_CTRL_MASK, bias_tune );
    }
    
    error_flag |= uwb2_read_otp ( ctx, UWB2_OTP_ADR_XTAL_TRIM, &data_rd32, 1 );
    init_xtrim = ( uint8_t ) ( data_rd32 & UWB2_XTAL_TRIM_MASK );
    if ( !init_xtrim )
    {
        init_xtrim = UWB2_XTAL_TRIM_DEFAULT;
    }
    error_flag |= uwb2_write_reg_8bit ( ctx, UWB2_REG_XTAL, init_xtrim );
    
    error_flag |= uwb2_read_otp ( ctx, UWB2_OTP_ADR_PLL_LOCK_CODE, &data_rd32, 1 );
    if ( data_rd32 )
    {
        error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_PLL_CC, data_rd32 );
    }
    return error_flag;
}

err_t uwb2_configure_ic ( uwb2_t *ctx, uwb2_chip_cfg_t *config )
{
    err_t error_flag = UWB2_OK;
    uint32_t data_rd32 = 0;
    uint16_t data_rd16 = 0;
    uint8_t data_rd8 = 0;
    uint16_t preamble_len = 0;
    if ( NULL == config )
    {
        return UWB2_ERROR;
    }
    switch ( config->tx_plen )
    {
        case UWB2_TX_PLEN_32:
        {
            preamble_len = 32;
            break;
        }
        case UWB2_TX_PLEN_64:
        {
            preamble_len = 64;
            break;
        }
        case UWB2_TX_PLEN_128:
        {
            preamble_len = 128;
            break;
        }
        default:
        {
            preamble_len = 256;
            break;
        }
    }
    // Disable PDOA and STS, and set PHR mode and rate to standard
    error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_SYS_CFG, 
                                          ~( UWB2_SYS_CFG_PDOA_MODE_MASK |
                                             UWB2_SYS_CFG_CP_SDC_SPC_MASK | 
                                             UWB2_SYS_CFG_PHR_6M8_MASK | 
                                             UWB2_SYS_CFG_PHR_MODE_MASK ), UWB2_MASK_NONE_32 );
    
    // Disable ADC count and peak growth checks
    error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_STS_CONF_1, 
                                          ~( UWB2_STS_CONF_1_STS_PGR_EN_MASK | 
                                             UWB2_STS_CONF_1_STS_SS_EN_MASK | 
                                             UWB2_STS_CONF_1_RES_B0_MASK ), UWB2_STS_CONF_1_RES_B0_DEFAULT );
    // configure OPS tables for non-SCP mode
    if ( preamble_len > 256 )
    {
        error_flag |= uwb2_modify_reg_16bit ( ctx, UWB2_REG_OTP_CFG, ~( UWB2_OTP_CFG_OPS_SEL_MASK ), 
                                              ( UWB2_OTP_CFG_OPS_SEL_LONG | UWB2_OTP_CFG_OPS_KICK_MASK ) );
    }
    else
    {
        error_flag |= uwb2_modify_reg_16bit ( ctx, UWB2_REG_OTP_CFG, ~( UWB2_OTP_CFG_OPS_SEL_MASK ), 
                                              ( UWB2_OTP_CFG_OPS_SEL_SHORT | UWB2_OTP_CFG_OPS_KICK_MASK ) );
    }
    // Enable STS CMF, and configure PAC size.
    error_flag |= uwb2_modify_reg_8bit ( ctx, UWB2_REG_DTUNE_0, ~( UWB2_DTUNE_0_PAC_MASK ), 
                                         ( UWB2_DTUNE_0_DTOB4_MASK | ( config->pac & UWB2_DTUNE_0_PAC_MASK ) ) );
    // Set STS length to 64us.
    error_flag |= uwb2_write_reg_8bit ( ctx, UWB2_REG_STS_CFG, UWB2_STS_CFG_CPS_LEN_64 );
    // Clear the setting in the FINE_PLEN register.
    error_flag |= uwb2_write_reg_8bit ( ctx, UWB2_REG_TX_FCTRL_HI + 1, 0 );
    // Configure optimal preamble detection threshold.
    error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DTUNE_3, UWB2_DTUNE_3_OPTIMAL );
    // Configure channel control register
    error_flag |= uwb2_read_reg_16bit ( ctx, UWB2_REG_CHAN_CTRL, &data_rd16 );
    data_rd16 &= ( ~ ( UWB2_CHAN_CTRL_RX_PCODE_MASK | UWB2_CHAN_CTRL_TX_PCODE_MASK | 
                       UWB2_CHAN_CTRL_SFD_TYPE_MASK | UWB2_CHAN_CTRL_RF_CHAN_MASK ) );
    if ( UWB2_CHANNEL_9 == config->channel )
    {
        data_rd16 |= UWB2_CHAN_CTRL_RF_CHAN_MASK;
    }
    data_rd16 |= ( ( ( uint16_t ) config->rx_code << 8 ) & UWB2_CHAN_CTRL_RX_PCODE_MASK );
    data_rd16 |= ( ( ( uint16_t ) config->tx_code << 3 ) & UWB2_CHAN_CTRL_TX_PCODE_MASK );
    data_rd16 |= ( ( ( uint16_t ) config->sfd_type << 1 ) & UWB2_CHAN_CTRL_SFD_TYPE_MASK );
    error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_CHAN_CTRL, data_rd16 );
    // Set TX preamble length and data rate, clear TX offset and TR bit
    error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_TX_FCTRL_LO, 
                                          ~( UWB2_TX_FCTRL_LO_TXB_OFFSET_MASK | UWB2_TX_FCTRL_LO_TXPSR_MASK | 
                                             UWB2_TX_FCTRL_LO_TR_MASK | UWB2_TX_FCTRL_LO_TX_BR_MASK ), 
                                          ( ( ( uint32_t ) config->data_rate << 10 ) | 
                                            ( ( uint32_t ) config->tx_plen << 12 ) ) );
    // Set SFD timeout. Don't allow 0 - SFD timeout will always be enabled
    if ( 0 == config->sfd_to )
    {
        config->sfd_to = UWB2_RX_SFD_TOC_DEFAULT;
    }
    error_flag |= uwb2_write_reg_16bit ( ctx, UWB2_REG_RX_SFD_TOC, config->sfd_to );
    // Check PMSC state
    error_flag |= uwb2_read_reg_32bit ( ctx, UWB2_REG_SYS_STATE, &data_rd32 );
    // If in IDLE_PLL then need to switch to IDLE_RC prior to re-calibrating the PLL for different channel
    if ( UWB2_SYS_STATE_PMSC_STATE_IDLE == ( data_rd32 & UWB2_SYS_STATE_PMSC_STATE_MASK ) )
    {
        error_flag |= uwb2_set_ic_state ( ctx, UWB2_IC_STATE_IDLE_RC );
        // Clear the auto INIT2IDLE bit and set FORCE2INIT
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_SEQ_CTRL, 
                                              ~( UWB2_SEQ_CTRL_AINIT2IDLE_MASK ), 
                                              UWB2_SEQ_CTRL_FORCE2INIT_MASK );
        // Clear force bits (device will stay in IDLE_RC)
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_SEQ_CTRL, 
                                             ~( UWB2_SEQ_CTRL_FORCE2INIT_MASK ), UWB2_MASK_NONE_32 );
        // Switch clock to auto
        error_flag |= uwb2_write_reg_16bit ( ctx, UWB2_REG_CLK_CTRL, 
                                             ( uint16_t ) UWB2_CLK_CTRL_RESERVED_BITS );
    }
    // RF setting
    if ( UWB2_CHANNEL_9 == config->channel )
    {
        // Setup TX analog for ch9
        error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_RF_TX_CTRL_2, UWB2_RF_TX_CTRL_2_CHANNEL_9 );
        error_flag |= uwb2_write_reg_16bit ( ctx, UWB2_REG_PLL_CFG, UWB2_PLL_CFG_CHANNEL_9 );
    }
    else
    {
        // Setup TX analog for ch5
        error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_RF_TX_CTRL_2, UWB2_RF_TX_CTRL_2_CHANNEL_5 );
        error_flag |= uwb2_write_reg_16bit ( ctx, UWB2_REG_PLL_CFG, UWB2_PLL_CFG_CHANNEL_5 );
    }
    error_flag |= uwb2_write_reg_8bit ( ctx, UWB2_REG_LDO_RLOAD, UWB2_LDO_RLOAD_OPTIMAL );
    error_flag |= uwb2_write_reg_8bit ( ctx, UWB2_REG_RF_TX_CTRL_1, UWB2_RF_TX_CTRL_1_OPTIMAL );
    // Extend the lock delay
    error_flag |= uwb2_write_reg_8bit ( ctx, UWB2_REG_PLL_CAL, ( uint8_t ) UWB2_PLL_CAL_OPTIMAL );
    // Verify PLL lock bit is cleared
    error_flag |= uwb2_write_reg_8bit ( ctx, UWB2_REG_SYS_STATUS_LO, 
                                        ( uint8_t ) UWB2_SYS_STATUS_LO_CPLOCK_MASK );
    // Auto cal the PLL and change to IDLE_PLL state
    error_flag |= uwb2_set_ic_state ( ctx, UWB2_IC_STATE_IDLE );
    Delay_5ms ( );
    error_flag |= uwb2_read_reg_8bit ( ctx, UWB2_REG_SYS_STATUS_LO, &data_rd8 );
    if ( UWB2_SYS_STATUS_LO_CPLOCK_MASK != ( data_rd8 & ( ( uint8_t ) UWB2_SYS_STATUS_LO_CPLOCK_MASK ) ) )
    { 
        // PLL is locked
        return UWB2_ERROR;
    }
    
    if ( ( config->rx_code >= UWB2_RX_CODE_9 ) && ( config->rx_code <= UWB2_RX_CODE_24 ) )
    {
        // Load RX LUTs
        error_flag |= uwb2_load_ic_rx_lut ( ctx, config->channel );
        error_flag |= uwb2_modify_reg_16bit ( ctx, UWB2_REG_DGC_CFG, 
                                              ~( UWB2_RX_TUNE_DGC_CFG_THR_64_MASK ), 
                                              UWB2_RX_TUNE_DGC_CFG_THR_64_OPTIMISED );
    }
    else
    {
        error_flag |= uwb2_modify_reg_8bit ( ctx, UWB2_REG_DGC_CFG, 
                                             ( uint8_t ) ~( UWB2_RX_TUNE_DGC_CFG_RX_TUNE_EN_MASK ), 
                                             UWB2_MASK_NONE_8 );
    }
    if ( preamble_len > 64 )
    {
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_DTUNE_4, ~( UWB2_DTUNE_4_RX_SFD_HLDOFF_MASK ), 
                                              UWB2_DTUNE_4_RX_SFD_HLDOFF );
    }
    else
    {
        // Set default value for <= 64
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_DTUNE_4, ~( UWB2_DTUNE_4_RX_SFD_HLDOFF_MASK ), 
                                              UWB2_DTUNE_4_RX_SFD_HLDOFF_DEFAULT );
    }
    // PGF setting - if the RX calibration routine fails the device receiver performance will be severely affected,
    // the application should reset and try again
    error_flag |= uwb2_calibrate_ic_pgf ( ctx );
    return error_flag;
}

err_t uwb2_set_ic_state ( uwb2_t *ctx, uint8_t state )
{
    err_t error_flag = UWB2_OK;
    // Set the auto INIT2IDLE bit so that IC enters IDLE mode before switching clocks to system PLL
    if ( UWB2_IC_STATE_IDLE == state )
    {
        // PLL should be configured prior to this, and the device should be in IDLE_RC
        // (if the PLL does not lock device will remain in IDLE_RC)
        
        // Switch clock to auto - if coming here from INIT_RC the clock will be FOSC/4,
        // need to switch to auto prior to setting auto INIT2IDLE bit
        error_flag |= uwb2_write_reg_16bit ( ctx, UWB2_REG_CLK_CTRL, ( uint16_t ) UWB2_CLK_CTRL_RESERVED_BITS );
        error_flag |= uwb2_modify_reg_16bit ( ctx, UWB2_REG_PLL_CAL, UWB2_MASK_ALL_16, 
                                            ( UWB2_PLL_CAL_CAL_EN_MASK | UWB2_PLL_CAL_USE_OLD_MASK ) );
        error_flag |= uwb2_modify_reg_16bit ( ctx, UWB2_REG_SEQ_CTRL, UWB2_MASK_ALL_16, 
                                            UWB2_SEQ_CTRL_AINIT2IDLE_MASK );
    }
    else if ( UWB2_IC_STATE_IDLE_RC == state )
    {
        // Change state to IDLE_RC and clear auto INIT2IDLE bit
        
        // Switch clock to FOSC
        error_flag |= uwb2_modify_reg_8bit ( ctx, UWB2_REG_CLK_CTRL, UWB2_MASK_ALL_8, 
                                             ( uint8_t ) UWB2_CLK_CTRL_SYS_CLK_FORCE_FC );
        // Clear the auto INIT2IDLE bit and set FORCE2INIT
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_SEQ_CTRL, 
                                              ~( UWB2_SEQ_CTRL_AINIT2IDLE_MASK ), 
                                              UWB2_SEQ_CTRL_FORCE2INIT_MASK );
        // Clear force bits (device will stay in IDLE_RC)
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_SEQ_CTRL, 
                                             ~( UWB2_SEQ_CTRL_FORCE2INIT_MASK ), UWB2_MASK_NONE_32 );
        // Switch clock to auto
        error_flag |= uwb2_write_reg_16bit ( ctx, UWB2_REG_CLK_CTRL, 
                                             ( uint16_t ) UWB2_CLK_CTRL_RESERVED_BITS );
    }
    else
    {
        error_flag |= uwb2_modify_reg_8bit ( ctx, UWB2_REG_CLK_CTRL, UWB2_MASK_ALL_8,
                                             ( uint8_t ) UWB2_CLK_CTRL_SYS_CLK_FORCE_FC_4 );
        // Clear the auto INIT2IDLE bit and set FORCE2INIT
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_SEQ_CTRL, 
                                              ~( UWB2_SEQ_CTRL_AINIT2IDLE_MASK ), 
                                              UWB2_SEQ_CTRL_FORCE2INIT_MASK );
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_SEQ_CTRL, 
                                             ~( UWB2_SEQ_CTRL_FORCE2INIT_MASK ), UWB2_MASK_NONE_32 );
    }
    return error_flag;
}

err_t uwb2_load_ic_rx_lut ( uwb2_t *ctx, uint8_t channel )
{
    err_t error_flag = UWB2_OK;
    uint32_t data_rd32 = 0;
    error_flag |= uwb2_read_otp ( ctx, UWB2_OTP_ADR_DGC_TUNE, &data_rd32, 1 );
    if ( UWB2_RX_TUNE_DGC_CFG_0 == data_rd32 )
    {
        // If the OTP has DGC info programmed into it, do a manual kick from OTP.
        // The DGC_SEL bit must be set to '0' for channel 5 and '1' for channel 9.
        if ( UWB2_CHANNEL_5 == channel )
        {
            error_flag |= uwb2_modify_reg_16bit ( ctx, UWB2_REG_OTP_CFG, ~( UWB2_OTP_CFG_DGC_SEL_MASK ), 
                                                  UWB2_OTP_CFG_DGC_KICK_MASK );
        }
        else
        {
            error_flag |= uwb2_modify_reg_16bit ( ctx, UWB2_REG_OTP_CFG, ~( UWB2_OTP_CFG_DGC_SEL_MASK ), 
                                                  ( UWB2_OTP_CFG_DGC_SEL_MASK | UWB2_OTP_CFG_DGC_KICK_MASK ) );
        }
    }
    else
    {
        // Else we manually program hard-coded values into the DGC registers.
        if ( UWB2_CHANNEL_5 == channel )
        {
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_0, UWB2_RX_TUNE_DGC_LUT_0_CH5 );
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_1, UWB2_RX_TUNE_DGC_LUT_1_CH5 );
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_2, UWB2_RX_TUNE_DGC_LUT_2_CH5 );
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_3, UWB2_RX_TUNE_DGC_LUT_3_CH5 );
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_4, UWB2_RX_TUNE_DGC_LUT_4_CH5 );
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_5, UWB2_RX_TUNE_DGC_LUT_5_CH5 );
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_6, UWB2_RX_TUNE_DGC_LUT_6_CH5 );
        }
        else
        {
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_0, UWB2_RX_TUNE_DGC_LUT_0_CH9 );
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_1, UWB2_RX_TUNE_DGC_LUT_1_CH9 );
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_2, UWB2_RX_TUNE_DGC_LUT_2_CH9 );
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_3, UWB2_RX_TUNE_DGC_LUT_3_CH9 );
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_4, UWB2_RX_TUNE_DGC_LUT_4_CH9 );
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_5, UWB2_RX_TUNE_DGC_LUT_5_CH9 );
            error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_LUT_6, UWB2_RX_TUNE_DGC_LUT_6_CH9 );
        }
        error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_CFG_0, UWB2_RX_TUNE_DGC_CFG_0 );
        error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_DGC_CFG_1, UWB2_RX_TUNE_DGC_CFG_1 );
    }
    return error_flag;
}

err_t uwb2_calibrate_ic_pgf ( uwb2_t *ctx )
{
    err_t error_flag = UWB2_OK;
    uint32_t data_rd32 = 0;
    uint16_t data_rd16 = 0;
    uint8_t data_rd8 = 0;
    // PGF needs LDOs turned on - ensure PGF LDOs are enabled
    error_flag |= uwb2_read_reg_16bit ( ctx, UWB2_REG_LDO_CTRL, &data_rd16 );
    error_flag |= uwb2_modify_reg_16bit ( ctx, UWB2_REG_LDO_CTRL, UWB2_MASK_ALL_16, 
                                          ( uint16_t) ( UWB2_LDO_CTRL_VDDIF2_EN_MASK | 
                                                        UWB2_LDO_CTRL_VDDMS3_EN_MASK | 
                                                        UWB2_LDO_CTRL_VDDMS1_EN_MASK ) );
    // Give the reference time to settle after enabling LDOs simultaneously
    Delay_10us ( );
    Delay_10us ( );
    // Run PGF Cal - Put into cal mode and turn on delay mode
    error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_RX_CAL, ( UWB2_RX_CAL_COMP_DLY_OPTIMAL | 
                                                                 UWB2_RX_CAL_CAL_MODE_CALIBRATION ) );
    // Trigger PGF Cal
    error_flag |= uwb2_modify_reg_8bit ( ctx, UWB2_REG_RX_CAL, UWB2_MASK_ALL_8, 
                                         ( uint8_t ) UWB2_RX_CAL_CAL_EN_MASK );
    Delay_80us ( );
    error_flag |= uwb2_read_reg_8bit ( ctx, UWB2_REG_RX_CAL_STS, &data_rd8 );
    if ( UWB2_RX_CAL_STS_CALIBRATION_DONE != data_rd8 )
    { 
        // PGF cal is not complete
        error_flag |= UWB2_ERROR;
    }
    // Put into normal mode
    error_flag |= uwb2_write_reg_8bit ( ctx, UWB2_REG_RX_CAL, ( uint8_t ) UWB2_RX_CAL_CAL_MODE_NORMAL );
    // Clear the status
    error_flag |= uwb2_write_reg_8bit ( ctx, UWB2_REG_RX_CAL_STS, UWB2_RX_CAL_STS_CALIBRATION_DONE ); 
    // Enable reading
    error_flag |= uwb2_modify_reg_8bit ( ctx, UWB2_REG_RX_CAL, UWB2_MASK_ALL_32, UWB2_RX_CAL_COMP_DLY_EN_READ ); 
    error_flag |= uwb2_read_reg_32bit ( ctx, UWB2_REG_RX_CAL_RESI, &data_rd32 );
    if ( UWB2_RX_CAL_RESI_CALIBRATION_FAILED == data_rd32 )
    {
        // PGF I calibration failed
        error_flag = UWB2_ERROR;
    }
    error_flag |= uwb2_read_reg_32bit ( ctx, UWB2_REG_RX_CAL_RESQ, &data_rd32 );
    if ( UWB2_RX_CAL_RESQ_CALIBRATION_FAILED == data_rd32 )
    {
        // PGF Q calibration failed
        error_flag = UWB2_ERROR;
    }
    // Turn off RX LDOs if previously off - Restore LDO values
    error_flag |= uwb2_modify_reg_16bit ( ctx, UWB2_REG_LDO_CTRL, data_rd16, UWB2_MASK_NONE_16 );
    return error_flag;
}

err_t uwb2_set_rx_tx_leds ( uwb2_t *ctx, uint8_t mode )
{
    err_t error_flag = UWB2_OK;
    if ( UWB2_RX_TX_LEDS_ENABLE == mode )
    {
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_GPIO_MODE, 
                                              ~( UWB2_GPIO_MODE_MSGP3_MASK | UWB2_GPIO_MODE_MSGP0_MASK ), 
                                              UWB2_GPIO_MODE_MSGP3_TXLED | UWB2_GPIO_MODE_MSGP0_RXOKLED );
        // Enable LP Oscillator to run from counter and turn on de-bounce clock.
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_CLK_CTRL, UWB2_MASK_ALL_32, 
                                              UWB2_CLK_CTRL_LP_CLK_EN_MASK | UWB2_CLK_CTRL_GPIO_DCLK_EN_MASK );
        // Enable LEDs to blink and set default blink time.
        error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_LED_CTRL, UWB2_LED_CTRL_FORCE_TRIG_MASK | 
                                                                     UWB2_LED_CTRL_BLINK_EN_MASK | 
                                                                     UWB2_LED_CTRL_BLINK_TIM_200MS );
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_LED_CTRL, 
                                              ~UWB2_LED_CTRL_FORCE_TRIG_MASK, UWB2_MASK_NONE_32 );
    }
    else
    {
        // Clear the GPIO bits that are used for LED control.
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_GPIO_MODE, 
                                              ~( UWB2_GPIO_MODE_MSGP3_MASK | UWB2_GPIO_MODE_MSGP0_MASK ), 
                                              UWB2_MASK_NONE_32 );
        error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_LED_CTRL, 
                                              ~UWB2_LED_CTRL_BLINK_EN_MASK, UWB2_MASK_NONE_32 );
    }
    
    return error_flag;
}

err_t uwb2_wait_for_status_lo ( uwb2_t *ctx, uint32_t status )
{
    uint32_t timeout_cnt = 0;
    uint32_t status_lo = 0;
    err_t error_flag = uwb2_read_reg_32bit ( ctx, UWB2_REG_SYS_STATUS_LO, &status_lo );
    while ( ( status_lo & status ) != status )
    {
        Delay_1ms ( );
        error_flag |= uwb2_read_reg_32bit ( ctx, UWB2_REG_SYS_STATUS_LO, &status_lo );
        if ( ( UWB2_OK != error_flag ) || ( UWB2_WAIT_TIMEOUT_MS == ++timeout_cnt ) )
        {
            error_flag |= UWB2_ERROR;
            break;
        }
    }
    if ( UWB2_OK == error_flag )
    { 
        // Clear status bits
        error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_SYS_STATUS_LO, status );
    }
    return error_flag;
}

err_t uwb2_clear_status ( uwb2_t *ctx )
{
    uint32_t status_lo = 0;
    uint16_t status_hi = 0;
    err_t error_flag = UWB2_OK;
    error_flag |= uwb2_read_reg_32bit ( ctx, UWB2_REG_SYS_STATUS_LO, &status_lo );
    error_flag |= uwb2_read_reg_16bit ( ctx, UWB2_REG_SYS_STATUS_HI, &status_hi );
    if ( UWB2_OK == error_flag )
    {
        error_flag |= uwb2_write_reg_32bit ( ctx, UWB2_REG_SYS_STATUS_LO, status_lo );
        error_flag |= uwb2_write_reg_16bit ( ctx, UWB2_REG_SYS_STATUS_HI, status_hi );
    }
    return error_flag;
}

err_t uwb2_send_message ( uwb2_t *ctx, uint8_t *data_in, uint16_t len )
{
    err_t error_flag = UWB2_OK;
    if ( NULL == data_in )
    {
        return UWB2_ERROR;
    }
    // Write data to TX_BUFFER register (without FSC/CRC bytes which are automatically appended by the IC)
    error_flag |= uwb2_write_reg ( ctx, UWB2_REG_TX_BUFFER, data_in, len );
    // Set tx message size (len + FCS/CRC bytes)
    error_flag |= uwb2_modify_reg_32bit ( ctx, UWB2_REG_TX_FCTRL_LO, 
                                          ~( UWB2_TX_FCTRL_LO_TXFLEN_MASK ), len + 2 );
    // Start transmission.
    error_flag |= uwb2_send_cmd ( ctx, UWB2_CMD_TX );
    // Wait for a TX Frame Sent event.
    error_flag |= uwb2_wait_for_status_lo ( ctx, UWB2_SYS_STATUS_LO_TXFRS_MASK );
    return error_flag;
}

err_t uwb2_read_message ( uwb2_t *ctx, uint8_t *data_out, uint16_t *len )
{
    err_t error_flag = UWB2_OK;
    uint16_t rx_msg_size = 0;
    if ( ( NULL == data_out ) || ( NULL == len ) )
    {
        return UWB2_ERROR;
    }
    // Activate reception immediately.
    error_flag |= uwb2_send_cmd ( ctx, UWB2_CMD_RX );
    // Poll until a frame is properly received or an error/timeout occurs.
    error_flag |= uwb2_wait_for_status_lo ( ctx, UWB2_SYS_STATUS_LO_RXFCG_MASK );
    if ( UWB2_OK == error_flag )
    {
        // A frame has been received, copy it to output buffer.
        error_flag |= uwb2_read_reg_16bit ( ctx, UWB2_REG_RX_FINFO, &rx_msg_size );
        rx_msg_size &= ( ( uint16_t ) UWB2_RX_FINFO_RXFLEN_MASK );
        // No need to read the FCS/CRC.
        rx_msg_size -= 2;
        // Limit data read to len number of bytes
        if ( rx_msg_size > *len )
        {
            rx_msg_size = *len;
        }
        // Read data
        error_flag |= uwb2_read_reg ( ctx, UWB2_REG_RX_BUFFER_0, data_out, rx_msg_size );
        // Update the number of data bytes actually read
        *len = rx_msg_size;
    }
    return error_flag;
}
    
// ------------------------------------------------------------------------- END
