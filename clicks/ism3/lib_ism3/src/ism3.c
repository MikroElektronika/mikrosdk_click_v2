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
 * @file ism3.c
 * @brief ISM 3 Click Driver.
 */

#include "ism3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void ism3_cfg_setup ( ism3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->gp0  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->gp2  = HAL_PIN_NC;
    cfg->gp1  = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t ism3_init ( ism3_t *ctx, ism3_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_high( &ctx->cs );

    digital_in_init( &ctx->gp0, cfg->gp0 );
    digital_in_init( &ctx->gp1, cfg->gp1 );
    digital_in_init( &ctx->gp2, cfg->gp2 );
    
    return SPI_MASTER_SUCCESS;
}

err_t ism3_default_cfg ( ism3_t *ctx ) 
{
    uint8_t reg_data[ 6 ] = { 0 };
    err_t error_flag = ISM3_OK;
    ism3_disable_device ( ctx );
    Delay_100ms ( );
    ism3_enable_device ( ctx );
    Delay_100ms ( );

    error_flag |= ism3_write_cmd ( ctx, ISM3_CMD_SRES );
    Delay_100ms ( );

    if ( ISM3_ERROR == ism3_check_communication ( ctx ) )
    {
        return ISM3_ERROR;
    }

    // Set GPIO1 pin as IRQ
    reg_data[ 0 ] = ISM3_GPIO1_CONF_GPIO_SELECT_NIRQ | ISM3_GPIO1_CONF_GPIO_MODE_DIG_OUTPUT_LP;
    error_flag |= ism3_write_reg ( ctx, ISM3_REG_GPIO1_CONF, reg_data[ 0 ] );

    // radio config
    error_flag |= ism3_read_reg ( ctx, ISM3_REG_XO_RCO_CONF1, reg_data );
    if ( ISM3_XO_RCO_CONF1_PD_CLKDIV != ( reg_data[ 0 ] & ISM3_XO_RCO_CONF1_PD_CLKDIV ) )
    {
        error_flag |= ism3_write_cmd ( ctx, ISM3_CMD_STANDBY );
        error_flag |= ism3_wait_mc_state ( ctx, ISM3_MC_STATE_STANDBY, ISM3_DEFAULT_TIMEOUT_MS );

        error_flag |= ism3_read_reg ( ctx, ISM3_REG_XO_RCO_CONF1, reg_data );
        reg_data[ 0 ] |= ISM3_XO_RCO_CONF1_PD_CLKDIV;
        error_flag |= ism3_write_reg ( ctx, ISM3_REG_XO_RCO_CONF1, reg_data[ 0 ] );

        error_flag |= ism3_write_cmd ( ctx, ISM3_CMD_READY );
        error_flag |= ism3_wait_mc_state ( ctx, ISM3_MC_STATE_READY, ISM3_DEFAULT_TIMEOUT_MS );
    }

    // Set intermediate frequency to 300 kHz
    reg_data[ 0 ] = ISM3_IF_OFFSET_ANA_DEFAULT;
    reg_data[ 1 ] = ISM3_IF_OFFSET_DIG_DEFAULT;
    error_flag |= ism3_write_regs ( ctx, ISM3_REG_IF_OFFSET_ANA, reg_data, 2 );

    // Set datarate to 38400bps for digital domain frequency (fdig) of 25MHz
    reg_data[ 0 ] = ISM3_MOD4_DATARATE_M_15_8_DEFAULT;
    reg_data[ 1 ] = ISM3_MOD3_DATARATE_M_7_0_DEFAULT;
    reg_data[ 2 ] = ISM3_MOD2_MOD_TYPE_2FSK | ISM3_MOD2_DATARATE_E_DEFAULT;

    // Set frequency deviation to 20 kHz
    error_flag |= ism3_read_reg ( ctx, ISM3_REG_MOD1, &reg_data[ 3 ] );
    reg_data[ 3 ] &= ~( ISM3_MOD1_FDEV_E_MASK );
    reg_data[ 3 ] |= ISM3_MOD1_FDEV_E_DEFAULT;
    reg_data[ 4 ] = ISM3_MOD0_FDEV_M_DEFAULT;

    // Set bandwidth to 100 kHz
    reg_data[ 5 ] = ISM3_CHFLT_M_DEFAULT | ISM3_CHFLT_E_DEFAULT;
    error_flag |= ism3_write_regs ( ctx, ISM3_REG_MOD4, reg_data, 6 );

    // Set PA power
    error_flag |= ism3_read_regs ( ctx, ISM3_REG_PA_POWER0, reg_data, 3 );
    reg_data[ 0 ] &= ~( ISM3_PA_POWER0_DIG_SMOOTH_EN );
    reg_data[ 1 ] &= ~( ISM3_PA_CONFIG1_FIR_EN );
    reg_data[ 2 ] &= ~( ISM3_PA_CONFIG0_PA_FC_MASK );
    reg_data[ 2 ] |= ISM3_PA_CONFIG0_PA_FC_50_KHZ;
    error_flag |= ism3_write_regs ( ctx, ISM3_REG_PA_POWER0, reg_data, 3 );

    // Enable AFC freeze on sync
    error_flag |= ism3_read_reg ( ctx, ISM3_REG_AFC2, reg_data );
    reg_data[ 0 ] |= ISM3_AFC2_AFC_FREEZE_ON_SYNC;
    error_flag |= ism3_write_reg ( ctx, ISM3_REG_AFC2, reg_data[ 0 ] );

    // Set synthesizer for frequency base of 433 MHz
    error_flag |= ism3_read_reg ( ctx, ISM3_REG_SYNTH_CONFIG2, reg_data );
    reg_data[ 0 ] |= ISM3_SYNTH_CONFIG2_PLL_PFD_SPLIT_EN;
    error_flag |= ism3_write_reg ( ctx, ISM3_REG_SYNTH_CONFIG2, reg_data[ 0 ] );
    reg_data[ 0 ] = ISM3_SYNT3_PLL_CP_ISEL_DEFAULT | ISM3_SYNT3_BS_8_MIDDLE_BAND | ISM3_SYNT3_SYNT_27_24_DEFAULT;
    reg_data[ 1 ] = ISM3_SYNT2_SYNT_23_16_DEFAULT;
    reg_data[ 2 ] = ISM3_SYNT1_SYNT_15_8_DEFAULT;
    reg_data[ 3 ] = ISM3_SYNT0_SYNT_7_0_DEFAULT;
    error_flag |= ism3_write_regs ( ctx, ISM3_REG_SYNT3, reg_data, 4 );

    // Set max PA level
    error_flag |= ism3_read_reg ( ctx, ISM3_REG_PA_POWER0, reg_data );
    reg_data[ 0 ] &= ~( ISM3_PA_POWER0_PA_MAXDBM );
    error_flag |= ism3_write_reg ( ctx, ISM3_REG_PA_POWER0, reg_data[ 0 ] );

    // Set PA level
    error_flag |= ism3_write_reg ( ctx, ISM3_REG_PA_POWER8, ISM3_PA_POWER8_PA_LEVEL8_DEFAULT );

    // Set PA level max index
    error_flag |= ism3_read_reg ( ctx, ISM3_REG_PA_POWER0, reg_data );
    reg_data[ 0 ] &= ~( ISM3_PA_POWER0_PA_LEVEL_MAX_IDX_MASK );
    reg_data[ 0 ] |= ISM3_PA_POWER0_PA_LEVEL_MAX_IDX_DEFAULT;
    error_flag |= ism3_write_reg ( ctx, ISM3_REG_PA_POWER0, reg_data[ 0 ] );

    // Set auto packet filtering
    error_flag |= ism3_read_reg ( ctx, ISM3_REG_PROTOCOL1, reg_data );
    reg_data[ 0 ] |= ISM3_PROTOCOL1_AUTO_PCKT_FLT;
    error_flag |= ism3_write_reg ( ctx, ISM3_REG_PROTOCOL1, reg_data[ 0 ] );

    // Basic packet config
    reg_data[ 0 ] = ISM3_PCKTCTRL6_SYNC_LEN_DEFAULT | ISM3_PCKTCTRL6_PREAMBLE_LEN_DEFAULT;
    reg_data[ 1 ] = ISM3_PCKTCTRL5_PREAMBLE_LEN_DEFAULT;
    reg_data[ 2 ] = ISM3_PCKTCTRL4_LEN_WID_1BYTE | ISM3_PCKTCTRL4_ADDRESS_LEN_NOT_INCLUDED;
    error_flag |= ism3_read_regs ( ctx, ISM3_REG_PCKTCTRL3, &reg_data[ 3 ], 3 );
    reg_data[ 3 ] &= ~( ISM3_PCKTCTRL3_PCKT_FRMT_MASK | ISM3_PCKTCTRL3_RX_MODE_MASK );
    reg_data[ 3 ] |= ( ISM3_PCKTCTRL3_PCKT_FRMT_BASIC | ISM3_PCKTCTRL3_RX_MODE_NORMAL );
    reg_data[ 4 ] &= ~( ISM3_PCKTCTRL2_MBUS_3OF6_EN | ISM3_PCKTCTRL2_MANCHESTER_EN );
    reg_data[ 4 ] |= ISM3_PCKTCTRL2_FIX_VAR_LEN;
    reg_data[ 5 ] &= ~( ISM3_PCKTCTRL1_CRC_MODE_MASK | ISM3_PCKTCTRL1_TXSOURCE_MASK | ISM3_PCKTCTRL1_FEC_EN );
    reg_data[ 5 ] |= ( ISM3_PCKTCTRL1_CRC_MODE_POLY_07 | ISM3_PCKTCTRL1_WHIT_EN );
    error_flag |= ism3_write_regs ( ctx, ISM3_REG_PCKTCTRL6, reg_data, 6 );

    // Set CRC check
    error_flag |= ism3_read_reg ( ctx, ISM3_REG_PCKT_FLT_OPTIONS, reg_data );
    reg_data[ 0 ] |= ISM3_PCKT_FLT_OPTIONS_CRC_FLT;
    error_flag |= ism3_write_reg ( ctx, ISM3_REG_PCKT_FLT_OPTIONS, reg_data[ 0 ] );

    // Config IRQ
    error_flag |= ism3_set_irq_mask ( ctx, ISM3_IRQ_NONE );

    // Set packet length
    reg_data[ 0 ] = ( uint8_t ) ( ( ISM3_PACKET_LEN >> 8 ) & 0xFF );
    reg_data[ 1 ] = ( uint8_t ) ( ISM3_PACKET_LEN & 0xFF );
    error_flag |= ism3_write_regs ( ctx, ISM3_REG_PCKTLEN1, reg_data, 2 );
    
    // Set RX timer to 2000ms
    reg_data[ 0 ] = ISM3_RX_TIMER_CNT_2000MS;
    reg_data[ 1 ] = ISM3_RX_TIMER_PSC_2000MS;
    error_flag |= ism3_write_regs ( ctx, ISM3_REG_TIMERS5, reg_data, 2 );

    // Go to RX as initial state
    error_flag |= ism3_go_to_rx ( ctx );
    Delay_1sec ( );
    return error_flag;
}

err_t ism3_write_regs ( ism3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t status_buf[ 2 ] = { 0 };
    err_t error_flag = ISM3_OK;
    digital_out_low( &ctx->cs );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, ISM3_HEADER_WRITE_REG );
    error_flag |= spi_master_read( &ctx->spi, &status_buf[ 0 ], 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, reg );
    error_flag |= spi_master_read( &ctx->spi, &status_buf[ 1 ], 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    digital_out_high( &ctx->cs );
    ctx->status = ( ( uint16_t ) status_buf[ 0 ] << 8 ) | status_buf[ 1 ]; 
    return error_flag;
}

err_t ism3_write_reg ( ism3_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ism3_write_regs ( ctx, reg, &data_in, 1 );
}

err_t ism3_read_regs ( ism3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t status_buf[ 2 ] = { 0 };
    err_t error_flag = ISM3_OK;
    digital_out_low( &ctx->cs );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, ISM3_HEADER_READ_REG );
    error_flag |= spi_master_read( &ctx->spi, &status_buf[ 0 ], 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, reg );
    error_flag |= spi_master_read( &ctx->spi, &status_buf[ 1 ], 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, data_out, len );
    digital_out_high( &ctx->cs );
    ctx->status = ( ( uint16_t ) status_buf[ 0 ] << 8 ) | status_buf[ 1 ]; 
    return error_flag;
}

err_t ism3_read_reg ( ism3_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ism3_read_regs ( ctx, reg, data_out, 1 );
}

err_t ism3_write_cmd ( ism3_t *ctx, uint8_t cmd )
{
    uint8_t status_buf[ 2 ] = { 0 };
    err_t error_flag = ISM3_OK;
    digital_out_low( &ctx->cs );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, ISM3_HEADER_WRITE_CMD );
    error_flag |= spi_master_read( &ctx->spi, &status_buf[ 0 ], 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, cmd );
    error_flag |= spi_master_read( &ctx->spi, &status_buf[ 1 ], 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    digital_out_high( &ctx->cs );
    ctx->status = ( ( uint16_t ) status_buf[ 0 ] << 8 ) | status_buf[ 1 ]; 
    return error_flag;
}

void ism3_enable_device ( ism3_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void ism3_disable_device ( ism3_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

uint8_t ism3_get_gp0_pin ( ism3_t *ctx )
{
    return digital_in_read ( &ctx->gp0 );
}

uint8_t ism3_get_gp1_pin ( ism3_t *ctx )
{
    return digital_in_read ( &ctx->gp1 );
}

uint8_t ism3_get_gp2_pin ( ism3_t *ctx )
{
    return digital_in_read ( &ctx->gp2 );
}

err_t ism3_check_communication ( ism3_t *ctx )
{
    uint8_t part_number = 0;
    if ( ISM3_OK == ism3_read_reg ( ctx, ISM3_REG_DEVICE_INFO1, &part_number ) )
    {
        if ( ISM3_PART_NUMBER == part_number )
        {
            return ISM3_OK;
        }
    }
    return ISM3_ERROR;
}

err_t ism3_wait_mc_state ( ism3_t *ctx, uint8_t mc_state, uint16_t timeout_ms )
{
    uint32_t timeout_cnt = 0;
    uint8_t reg_data = 0;
    err_t error_flag = ISM3_OK;
    do
    {
        Delay_50us ( );
        error_flag |= ism3_read_reg ( ctx, ISM3_REG_MC_STATE0, &reg_data );
        timeout_cnt++;
        if ( ( timeout_cnt / 20 ) > timeout_ms )
        {
            error_flag = ISM3_TIMEOUT;
        }
    }
    while ( ( ( ( reg_data >> 1 ) & ISM3_MC_STATE_MASK ) != mc_state ) && ( ISM3_OK == error_flag ) );

    return error_flag;
}

err_t ism3_go_to_ready ( ism3_t *ctx )
{
    uint8_t reg_data = 0;
    err_t error_flag = ism3_read_reg ( ctx, ISM3_REG_MC_STATE0, &reg_data );
    reg_data = ( uint8_t ) ( ( reg_data >> 1 ) & ISM3_MC_STATE_MASK );
    if ( ISM3_MC_STATE_READY != reg_data )
    {
        if ( ( ISM3_MC_STATE_STANDBY == reg_data ) || 
             ( ISM3_MC_STATE_SLEEP_NOFIFO == reg_data ) || 
             ( ISM3_MC_STATE_SLEEP == reg_data ) || 
             ( ISM3_MC_STATE_LOCKON == reg_data ) )
        {
            error_flag |= ism3_write_cmd ( ctx, ISM3_CMD_RX );
        }
        else if ( ( ISM3_MC_STATE_TX == reg_data ) || 
                  ( ISM3_MC_STATE_RX == reg_data ) || 
                  ( ISM3_MC_STATE_LOCKST == reg_data ) )
        {
            error_flag |= ism3_write_cmd ( ctx, ISM3_CMD_SABORT );
        }
        error_flag |= ism3_wait_mc_state ( ctx, ISM3_MC_STATE_READY, ISM3_DEFAULT_TIMEOUT_MS );
    }
    return error_flag;
}

err_t ism3_go_to_rx ( ism3_t *ctx )
{
    err_t error_flag = ISM3_OK;
    error_flag |= ism3_go_to_ready ( ctx );
    error_flag |= ism3_write_cmd ( ctx, ISM3_CMD_RX );
    error_flag |= ism3_clear_irq_status ( ctx );
    return error_flag;
}

err_t ism3_set_irq_mask ( ism3_t *ctx, uint32_t irq_mask )
{
    uint8_t reg_data[ 4 ] = { 0 };
    reg_data[ 0 ] = ( uint8_t ) ( ( irq_mask >> 24 ) & 0xFF );
    reg_data[ 1 ] = ( uint8_t ) ( ( irq_mask >> 16 ) & 0xFF );
    reg_data[ 2 ] = ( uint8_t ) ( ( irq_mask >> 8 ) & 0xFF );
    reg_data[ 3 ] = ( uint8_t ) ( irq_mask & 0xFF );
    return ism3_write_regs ( ctx, ISM3_REG_IRQ_MASK3, reg_data, 4 );
}

err_t ism3_read_irq_mask ( ism3_t *ctx, uint32_t *irq_mask )
{
    uint8_t reg_data[ 4 ] = { 0 };
    err_t error_flag = ism3_read_regs ( ctx, ISM3_REG_IRQ_MASK3, reg_data, 4 );
    *irq_mask = ( ( uint32_t ) reg_data[ 0 ] << 24 ) | ( ( uint32_t ) reg_data[ 1 ] << 16 ) | 
                ( ( uint16_t ) reg_data[ 2 ] << 8 ) | reg_data[ 3 ];
    return error_flag;
}

err_t ism3_clear_irq_status ( ism3_t *ctx )
{
    uint8_t reg_data[ 4 ] = { 0 };
    return ism3_read_regs ( ctx, ISM3_REG_IRQ_STATUS3, reg_data, 4 );
}

err_t ism3_read_irq_status ( ism3_t *ctx, uint32_t *irq_status )
{
    uint8_t reg_data[ 4 ] = { 0 };
    err_t error_flag = ism3_read_regs ( ctx, ISM3_REG_IRQ_STATUS3, reg_data, 4 );
    *irq_status = ( ( uint32_t ) reg_data[ 0 ] << 24 ) | ( ( uint32_t ) reg_data[ 1 ] << 16 ) | 
                  ( ( uint16_t ) reg_data[ 2 ] << 8 ) | reg_data[ 3 ];
    return error_flag;
}

err_t ism3_transmit_packet ( ism3_t *ctx, uint8_t *data_in, uint8_t len )
{
    uint32_t irq_status = 0;
    uint32_t timeout_cnt = 0;
    uint8_t data_buf[ ISM3_PACKET_LEN ] = { 0 };
    err_t error_flag = ISM3_OK;

    if ( ( NULL == data_in ) || ( len > ISM3_PACKET_LEN ) )
    {
        return ISM3_ERROR;
    }
    memcpy ( data_buf, data_in, len );

    error_flag |= ism3_set_irq_mask ( ctx, ISM3_IRQ_TX_DATA_SENT );
    error_flag |= ism3_clear_irq_status ( ctx );

    error_flag |= ism3_go_to_ready ( ctx );

    error_flag |= ism3_write_cmd ( ctx, ISM3_CMD_FLUSHTXFIFO );
    error_flag |= ism3_write_regs ( ctx, ISM3_REG_LINEAR_FIFO, data_buf, ISM3_PACKET_LEN );
    error_flag |= ism3_write_reg ( ctx, ISM3_REG_PM_CONF3, ISM3_PM_CONF3_TX );
    error_flag |= ism3_write_cmd ( ctx, ISM3_CMD_TX );

    while ( ism3_get_gp1_pin ( ctx ) )
    {
        Delay_1ms ( );
        if ( ++timeout_cnt >= ISM3_DEFAULT_TIMEOUT_MS )
        {
            error_flag = ISM3_TIMEOUT;
            break;
        }
    }

    if ( ISM3_OK == error_flag )
    {
        error_flag |= ism3_read_irq_status ( ctx, &irq_status );
        error_flag |= ism3_write_cmd ( ctx, ISM3_CMD_RX );
        if ( ISM3_IRQ_TX_DATA_SENT != ( irq_status & ISM3_IRQ_TX_DATA_SENT ) )
        {
            error_flag = ISM3_ERROR;
        }
    }
    return error_flag;
}

err_t ism3_receive_packet ( ism3_t *ctx, uint8_t *data_out, uint8_t *len )
{
    uint32_t irq_status = 0;
    uint32_t timeout_cnt = 0;
    uint8_t fifo_size = 0;
    err_t error_flag = ISM3_OK;

    if ( NULL == data_out )
    {
        return ISM3_ERROR;
    }
    error_flag |= ism3_set_irq_mask ( ctx, ISM3_IRQ_RX_DATA_READY | ISM3_IRQ_RX_DATA_DISC );
    error_flag |= ism3_clear_irq_status ( ctx );

    error_flag |= ism3_wait_mc_state ( ctx, ISM3_MC_STATE_READY, ISM3_DEFAULT_TIMEOUT_MS );
    error_flag |= ism3_write_reg ( ctx, ISM3_REG_PM_CONF3, ISM3_PM_CONF3_RX );
    error_flag |= ism3_write_cmd ( ctx, ISM3_CMD_RX );

    while ( ism3_get_gp1_pin ( ctx ) )
    {
        Delay_1ms ( );
        if ( ++timeout_cnt >= ISM3_DEFAULT_RX_TIMEOUT_MS )
        {
            ism3_go_to_rx ( ctx );
            error_flag = ISM3_TIMEOUT;
            break;
        }
    }

    if ( ISM3_OK == error_flag )
    {
        error_flag |= ism3_read_irq_status ( ctx, &irq_status );

        if ( irq_status & ISM3_IRQ_RX_DATA_READY )
        {
            error_flag |= ism3_read_reg ( ctx, ISM3_REG_RX_FIFO_STATUS, &fifo_size );
            if ( fifo_size > ISM3_PACKET_LEN )
            {
                fifo_size = ISM3_PACKET_LEN;
            }
            error_flag |= ism3_read_regs ( ctx, ISM3_REG_LINEAR_FIFO, data_out, fifo_size );
            error_flag |= ism3_write_cmd ( ctx, ISM3_CMD_FLUSHRXFIFO );
            if ( NULL != len )
            {
                *len = fifo_size;
            }
        }
        else if ( irq_status & ISM3_IRQ_RX_DATA_DISC )
        {
            error_flag = ISM3_ERROR;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
