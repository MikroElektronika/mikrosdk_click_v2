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
 * @file lr6.c
 * @brief LR 6 Click Driver.
 */

#include "lr6.h"

/**
 * @brief Dummy and timeout data.
 * @details Definition of dummy and timeout data.
 */
#define DUMMY        0x00
#define LR6_TIMEOUT  5000

void lr6_cfg_setup ( lr6_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->md   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->bsy  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t lr6_init ( lr6_t *ctx, lr6_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->md, cfg->md );
    digital_in_init( &ctx->bsy, cfg->bsy );

    return SPI_MASTER_SUCCESS;
}

err_t lr6_default_cfg ( lr6_t *ctx ) 
{
    lr6_hw_reset( ctx );
    Delay_10ms( );
    
    err_t err_flag = lr6_wait_for_idle( ctx );
    Delay_10ms( );

    uint8_t data_buf[ 2 ] = { 0 };
    err_flag |= lr6_reg_read( ctx, LR6_REG_LORA_SYNC_WORD_MSB, data_buf, 2 );
    uint16_t sync_word = ( data_buf[ 0 ] << 8 ) + data_buf[ 1 ];
    if ( sync_word != LR6_SYNC_WORD_PUBLIC && sync_word != LR6_SYNC_WORD_PRIVATE ) 
    {
        return LR6_ERROR;
    }
    
    err_flag |= lr6_set_standby( ctx, LR6_STANDBY_RC );
    Delay_10ms( );

    err_flag |= lr6_set_dio2_rf_switch( ctx, LR6_DIO2_AS_RF_SWITCH );
    Delay_10ms( );

    err_flag |= lr6_set_calibrate( ctx, LR6_CALIBRATE_IMAGE_ON | 
                                        LR6_CALIBRATE_ADC_BULK_P_ON | 
                                        LR6_CALIBRATE_ADC_BULK_N_ON |
                                        LR6_CALIBRATE_ADC_PULSE_ON |
                                        LR6_CALIBRATE_PLL_ON |
                                        LR6_CALIBRATE_RC13M_ON |
                                        LR6_CALIBRATE_RC64K_ON );
    Delay_10ms( );

    err_flag |= lr6_set_regulator_mode( ctx, LR6_REGULATOR_DC_DC );
    Delay_10ms( );

    err_flag |= lr6_set_buff_base_addr( ctx, LR6_TX_BASE_ADDR_DEFAULT, 
                                             LR6_RX_BASE_ADDR_DEFAULT );
    Delay_10ms( );

    err_flag |= lr6_set_pa_config( ctx, LR6_PA_CONFIG_DUTY_CYCLE, 
                                        LR6_PA_CONFIG_HP_MAX, 
                                        LR6_PA_CONFIG_SX1268, 
                                        LR6_PA_CONFIG_PA_LUT );
    Delay_10ms( );

    err_flag |= lr6_set_ovc_protection( ctx, LR6_OVC_PROTECT_DEFAULT );
    Delay_10ms( );

    err_flag |= lr6_set_power_config( ctx, LR6_TX_OUTPUT_POWER, 
                                           LR6_PWR_CONFIG_RNP_TIME );
    Delay_10ms( );

    err_flag |= lr6_set_rf_frequency( ctx, LR6_RF_FREQUENCY_433_MHZ );
    Delay_10ms( );

    lr6_lora_cfg_t lora_cfg;
    lora_cfg.spd_fact = LR6_LORA_SPREADING_FACTOR;
    lora_cfg.bandwidth = LR6_LORA_BANDWIDTH_125_KHZ;
    lora_cfg.c_rate = LR6_LORA_CODINGRATE_4_5;
    lora_cfg.prmb_len = LR6_LORA_PREAMBLE_LENGTH;
    lora_cfg.pl_len = LR6_LORA_PAYLOADLENGTH;
    lora_cfg.crc_on = LR6_LORA_CRC_ON;
    lora_cfg.inv_irq = LR6_LORA_INV_IRQ_OFF;
    err_flag |= lr6_set_lr_config( ctx, lora_cfg );
    Delay_10ms( );

    return err_flag;
}

void lr6_hw_reset ( lr6_t *ctx )
{
    Delay_10ms( );
    digital_out_low( &ctx->rst );
    Delay_10ms( );
    Delay_10ms( );
    digital_out_high( &ctx->rst );
    Delay_10ms( );

    while ( digital_in_read( &ctx->bsy ) )
    {
        Delay_1ms( );
    }
}

uint8_t lr6_check_bsy_pin ( lr6_t *ctx )
{
    return digital_in_read( &ctx->bsy );
}

err_t lr6_wait_for_idle ( lr6_t *ctx )
{
    err_t err_flag = LR6_OK;
    uint16_t timeout = DUMMY;
    while ( ( lr6_check_bsy_pin( ctx ) ) && ( timeout < LR6_TIMEOUT ) )
    {
        timeout++;
        Delay_1ms( );
    }
    if ( timeout > LR6_TIMEOUT )
    {
        err_flag = LR6_ERROR;
    }
    return err_flag;
} 

err_t lr6_generic_write ( lr6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, &reg, 1 );
    err_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t lr6_generic_read ( lr6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t lr6_reg_write ( lr6_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_data[ 3 ] = { 0 };
    tx_data[ 0 ] = LR6_CMD_WRITE_REGISTER;
    tx_data[ 1 ] = ( uint8_t ) ( ( reg & 0xFF00 )  >> 8 );
    tx_data[ 2 ] = ( uint8_t ) ( reg & 0x00FF );
    err_t err_flag = lr6_wait_for_idle( ctx );
    spi_master_select_device( ctx->chip_select );
    err_flag |=  spi_master_write( &ctx->spi, tx_data, 3 );
    err_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t lr6_reg_read ( lr6_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t tx_data[ 4 ] = { 0 };
    tx_data[ 0 ] = LR6_CMD_READ_REGISTER;
    tx_data[ 1 ] = ( uint8_t ) ( ( reg & 0xFF00 )  >> 8 );
    tx_data[ 2 ] = ( uint8_t ) ( reg & 0x00FF );
    tx_data[ 3 ] = DUMMY;
    err_t err_flag = lr6_wait_for_idle( ctx );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_write( &ctx->spi, tx_data, 4 );
    err_flag |= spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t lr6_cmd_write ( lr6_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len ) 
{
    uint8_t status = DUMMY;
    err_t err_flag = lr6_wait_for_idle( ctx );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        err_flag |= spi_master_set_default_write_data( &ctx->spi, data_in[ cnt ] );
        err_flag |= spi_master_read( &ctx->spi, &status, 1 );

        if ( ( ( status & LR6_STATUS_CMD_BIT_MASK ) == LR6_STATUS_CMD_TIMEOUT ) ||
             ( ( status & LR6_STATUS_CMD_BIT_MASK ) == LR6_STATUS_CMD_INVALID ) ||
             ( ( status & LR6_STATUS_CMD_BIT_MASK ) == LR6_STATUS_CMD_FAILED ) ) 
        {
            status &= LR6_STATUS_CMD_BIT_MASK;
            break;
        } 
        else if ( ( LR6_STATUS_DATA_ERROR == status ) || 
                  ( LR6_STATUS_SPI_FAILED == status ) ) 
        {
            err_flag = LR6_ERROR;
            break;
        }
    }
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t lr6_cmd_write_check ( lr6_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len ) 
{
    err_t err_flag = LR6_OK;
    for ( uint8_t cnt = 0; cnt < 10; cnt++ )
    {
        err_flag = lr6_cmd_write( ctx, cmd, data_in, len );
        if ( LR6_OK == err_flag ) 
        {
            break;
        }
    }   
    return err_flag;
}

err_t lr6_cmd_read ( lr6_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len ) 
{
    err_t err_flag = lr6_wait_for_idle( ctx ); 
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    err_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    err_flag |= spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t lr6_buffer_write ( lr6_t *ctx, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = LR6_CMD_WRITE_BUFFER; 
    data_buf[ 1 ] = DUMMY;
    err_t err_flag = lr6_wait_for_idle( ctx );
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    err_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    lr6_wait_for_idle( ctx );
    return err_flag;
}

err_t lr6_buffer_read ( lr6_t *ctx, uint8_t *data_out, uint8_t len, uint8_t *pl_len )
{
    uint8_t offset = DUMMY;
    uint8_t len_buf = DUMMY;
    err_t err_flag = lr6_get_rx_buff_status( ctx, &len_buf, &offset );
    err_flag |= lr6_wait_for_idle( ctx );
    uint8_t data_buf [ 3 ] = { 0 };
    data_buf[ 0 ] = LR6_CMD_READ_BUFFER;
    data_buf[ 1 ] = offset;
    data_buf[ 2 ] = DUMMY;
    spi_master_select_device( ctx->chip_select );
    err_flag |= spi_master_write( &ctx->spi, data_buf, 3 );
    err_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    err_flag |= spi_master_read( &ctx->spi, data_out, len_buf );
    spi_master_deselect_device( ctx->chip_select );
    err_flag |= lr6_wait_for_idle( ctx );
    *pl_len = len_buf;
    return err_flag;
}

err_t lr6_set_standby ( lr6_t *ctx, uint8_t mode )
{
    return lr6_cmd_write_check( ctx, LR6_CMD_SET_STANDBY, &mode, 1 );
}

err_t lr6_set_dio2_rf_switch ( lr6_t *ctx, uint8_t enable )
{
    return lr6_cmd_write_check( ctx, LR6_CMD_SET_DIO2_AS_RF_SWITCH_CTRL, &enable, 1 );
}

err_t lr6_set_calibrate ( lr6_t *ctx, uint8_t calib_data )
{
    return lr6_cmd_write_check( ctx, LR6_CMD_CALIBRATE, &calib_data, 1 );
}

err_t lr6_set_regulator_mode ( lr6_t *ctx, uint8_t mode )
{
    return lr6_cmd_write_check( ctx, LR6_CMD_SET_REGULATOR_MODE, &mode, 1 );
}

err_t lr6_set_pa_config ( lr6_t *ctx, uint8_t pa_duty_cycle, uint8_t hp_max, uint8_t device_sel, uint8_t pa_lut )
{
  uint8_t data_buf[ 4 ] = { 0 };
  data_buf[ 0 ] = pa_duty_cycle;
  data_buf[ 1 ] = hp_max;
  data_buf[ 2 ] = device_sel;
  data_buf[ 3 ] = pa_lut;
  return lr6_cmd_write_check( ctx, LR6_CMD_SET_PA_CONFIG, data_buf, 4 );
}

err_t lr6_set_buff_base_addr ( lr6_t *ctx, uint8_t tx_base_addr, uint8_t rx_base_addr )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = tx_base_addr;
    data_buf[ 1 ] = rx_base_addr;
    return lr6_cmd_write_check( ctx, LR6_CMD_SET_BUFFER_BASE_ADDRESS, data_buf, 2 );
}

err_t lr6_set_ovc_protection ( lr6_t *ctx, float current_limit )
{
    err_t err_flag = LR6_ERROR;
    if ( ( current_limit >= LR6_OVC_PROTECT_MIN ) && ( current_limit <= LR6_OVC_PROTECT_MAX ) )
    {
        uint8_t data_buf = ( uint8_t ) ( current_limit / 2.5 );
        err_flag = lr6_reg_write( ctx, LR6_REG_OCP_CONFIGURATION, &data_buf, 1 );
    }
    return err_flag;
}

err_t lr6_set_power_config ( lr6_t *ctx, int8_t power, uint8_t rmp_time )
{
    err_t err_flag = LR6_ERROR;
    if ( ( power <= LR6_TX_OUTPUT_POWER_MAX ) && ( power >= LR6_TX_OUTPUT_POWER_MIN ) )
    {
        uint8_t data_buf[ 2 ] = { 0 };
        data_buf[ 0 ] = ( uint8_t ) power;
        data_buf[ 1 ] = ( uint8_t ) rmp_time;
        err_flag = lr6_cmd_write_check( ctx, LR6_CMD_SET_TX_PARAMS, data_buf, 2 );
    }
    return err_flag;
}

err_t lr6_set_tx_power ( lr6_t *ctx, int8_t tx_pwr_dbm )
{
    return lr6_set_power_config( ctx, tx_pwr_dbm, LR6_PWR_CONFIG_RNP_TIME );
}

err_t lr6_set_calib_image ( lr6_t *ctx, uint32_t freq )
{
    err_t err_flag = LR6_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( freq > LR6_RF_FREQUENCY_900_MHZ )
    {
        data_buf[ 0 ] = LR6_RF_FREQ_CALIB_IMG_900_H;
        data_buf[ 1 ] = LR6_RF_FREQ_CALIB_IMG_900_L;
    }
    else if ( freq > LR6_RF_FREQUENCY_850_MHZ )
    {
        data_buf[ 0 ] = LR6_RF_FREQ_CALIB_IMG_850_H;
        data_buf[ 1 ] = LR6_RF_FREQ_CALIB_IMG_850_L;
    }
    else if ( freq > LR6_RF_FREQUENCY_700_MHZ )
    {
        data_buf[ 0 ] = LR6_RF_FREQ_CALIB_IMG_700_H;
        data_buf[ 1 ] = LR6_RF_FREQ_CALIB_IMG_700_L;
    }
    else if ( freq > LR6_RF_FREQUENCY_460_MHZ )
    {
        data_buf[ 0 ] = LR6_RF_FREQ_CALIB_IMG_460_H;
        data_buf[ 1 ] = LR6_RF_FREQ_CALIB_IMG_460_L;
    }
    else if ( freq > LR6_RF_FREQUENCY_425_MHZ )
    {
        data_buf[ 0 ] = LR6_RF_FREQ_CALIB_IMG_425_H;
        data_buf[ 1 ] = LR6_RF_FREQ_CALIB_IMG_425_L;
    }
    else 
    {
        err_flag = LR6_ERROR;
    }
    err_flag |= lr6_cmd_write_check( ctx, LR6_CMD_CALIBRATE_IMAGE, data_buf, 2 );
    return err_flag;
}

err_t lr6_set_rf_frequency ( lr6_t *ctx, uint32_t freq )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t err_flag = lr6_set_calib_image( ctx, freq );
    freq = ( uint32_t ) ( ( float ) freq / LR6_RF_FREQ_CALIB_IMG_SENS );
    data_buf[ 0 ] = ( uint8_t ) ( ( freq >> 24 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( freq >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( freq >> 8 )  & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) (   freq         & 0xFF );
    err_flag |= lr6_cmd_write_check( ctx, LR6_CMD_SET_RF_FREQUENCY, data_buf, 4 );
    return err_flag;
}

err_t lr6_set_stop_rx_timer ( lr6_t *ctx, uint8_t enable )
{
    return lr6_cmd_write_check( ctx, LR6_CMD_STOP_TIMER_ON_PREAMBLE, &enable, 1 );
}

err_t lr6_set_lr_symb_num_timeout ( lr6_t *ctx, uint8_t symb_num )
{
    return lr6_cmd_write_check( ctx, LR6_CMD_SET_LORA_SYMB_NUM_TIMEOUT, &symb_num, 1 );
}

err_t lr6_set_packet_type ( lr6_t *ctx, uint8_t pck_type )
{
    return lr6_cmd_write_check( ctx, LR6_CMD_SET_PACKET_TYPE, &pck_type, 1 );
}

err_t lr6_set_modulation_params ( lr6_t *ctx, uint8_t spd_fact, uint8_t bandwidth, uint8_t c_rate, uint8_t ldr_opt )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = spd_fact;
    data_buf[ 1 ] = bandwidth;
    data_buf[ 2 ] = c_rate;
    data_buf[ 3 ] = ldr_opt;
    return lr6_cmd_write_check( ctx, LR6_CMD_SET_MODULATION_PARAMS, data_buf, 4 );
}

err_t lr6_set_fix_inverted_iq (  lr6_t *ctx, uint8_t iq_cfg )
{
    uint8_t iq_cfg_curr = DUMMY;
    err_t err_flag = lr6_reg_read( ctx, LR6_REG_IQ_POLARITY_SETUP, &iq_cfg_curr, 1 );
    if ( iq_cfg == LR6_IQ_POLARITY_SETUP_INV )
    {
        iq_cfg_curr &= LR6_IQ_POLARITY_SETUP_CLR;
    } 
    else 
    {
        iq_cfg_curr |= LR6_IQ_POLARITY_SETUP_SET;
    }
    err_flag |= lr6_reg_write( ctx, LR6_REG_IQ_POLARITY_SETUP, &iq_cfg_curr, 1 );
    return err_flag;
}

err_t lr6_set_dio_irq_params ( lr6_t *ctx, uint16_t irq, uint16_t dio1, uint16_t dio2, uint16_t dio3 )
{
    uint8_t data_buf[ 8 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( irq >> 8 ) & 0x00FF );
    data_buf[ 1 ] = ( uint8_t ) ( irq & 0x00FF );
    data_buf[ 2 ] = ( uint8_t ) ( ( dio1 >> 8 ) & 0x00FF );
    data_buf[ 3 ] = ( uint8_t ) ( dio1 & 0x00FF );
    data_buf[ 4 ] = ( uint8_t ) ( ( dio2 >> 8 ) & 0x00FF );
    data_buf[ 5 ] = ( uint8_t ) ( dio2 & 0x00FF );
    data_buf[ 6 ] = ( uint8_t ) ( ( dio3 >> 8 ) & 0x00FF );
    data_buf[ 7 ] = ( uint8_t ) ( dio3 & 0x00FF );
    return lr6_cmd_write_check( ctx, LR6_CMD_SET_DIO_IRQ_PARAMS, data_buf, 8 );
}

err_t lr6_get_status ( lr6_t *ctx, uint8_t *status )
{
    return lr6_cmd_read( ctx, LR6_CMD_GET_STATUS, status, 1 );
}

err_t lr6_set_rx ( lr6_t *ctx, uint32_t timeout )
{
    uint8_t data_buf[ 3 ] = { 0 };
    err_t err_flag = lr6_set_standby( ctx, LR6_STANDBY_RC );
    data_buf[ 0 ] = ( uint8_t ) ( ( timeout >> 16 ) & 0xFF);
    data_buf[ 1 ] = ( uint8_t ) ( ( timeout >> 8 )  & 0xFF);
    data_buf[ 2 ] = ( uint8_t ) (   timeout         & 0xFF);
    err_flag |= lr6_cmd_write_check( ctx, LR6_CMD_SET_RX, data_buf, 3 );
    
    for ( uint8_t cnt = 0; cnt < 10; cnt++ ) 
    {
        uint8_t status = 0;
        err_flag |= lr6_get_status( ctx, &status );
        if ( ( status & LR6_STATUS_BITMASK ) == LR6_STATUS_SET_RX_OK )
        {
          break;
        }
        Delay_1ms( );
    }
    return err_flag;
}

err_t lr6_set_lr_config ( lr6_t *ctx, lr6_lora_cfg_t lora_cfg ) 
{
    err_t err_flag = lr6_set_stop_rx_timer( ctx, LR6_STOP_TIMER_ON_PREAMBLE_ON );
    err_flag |= lr6_set_lr_symb_num_timeout( ctx, LR6_SET_LORA_SYMB_NUM_TIMEOUT ); 
    err_flag |= lr6_set_packet_type( ctx, LR6_SET_PACKET_TYPE );
    err_flag |= lr6_set_modulation_params( ctx, lora_cfg.spd_fact, lora_cfg.bandwidth, lora_cfg.c_rate, 0 );
  
    ctx->packet_params[ 0 ] = ( lora_cfg.prmb_len >> 8 ) & 0xFF;
    ctx->packet_params[ 1 ] = lora_cfg.prmb_len;
    if ( lora_cfg.pl_len )
    {
      ctx->packet_params[ 2 ] = LR6_SET_PREMBLE_LEN_ON;
      ctx->packet_params[ 3 ] = lora_cfg.pl_len;
    }
    else
    {
      ctx->packet_params[ 2 ] = LR6_SET_PREMBLE_LEN_ON;
      ctx->packet_params[ 3 ] = LR6_SET_PREMBLE_LEN_DUMMY;
    }

    if ( lora_cfg.crc_on )
    {
        ctx->packet_params[ 4 ] = LR6_SET_CRC_ON;
    }
    else
    {
        ctx->packet_params[ 4 ] = LR6_SET_CRC_OFF;
    }

    if ( lora_cfg.inv_irq )
    {
        ctx->packet_params[ 5 ] = LR6_SET_INV_IRQ_ON;
    }
    else
    {
        ctx->packet_params[ 5 ] = LR6_SET_INV_IRQ_OFF;
    }
    
    err_flag |= lr6_set_fix_inverted_iq( ctx, ctx->packet_params[ 5 ] );
    err_flag |= lr6_cmd_write_check( ctx, LR6_CMD_SET_PACKET_PARAMS, ctx->packet_params, 6 );
    err_flag |= lr6_set_dio_irq_params(ctx, LR6_IRQ_ALL, LR6_IRQ_DIO_CLR, 
                                                         LR6_IRQ_DIO_CLR, 
                                                         LR6_IRQ_DIO_CLR );
    err_flag |= lr6_set_rx( ctx, LR6_SET_RX_DEFAULT );

    return err_flag;
}

err_t lr6_clear_irq_status ( lr6_t *ctx, uint16_t irq )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( ( uint16_t ) irq >> 8 ) & 0x00FF );
    data_buf[ 1 ] = ( uint8_t ) ( ( uint16_t)  irq & 0x00FF );
    return lr6_cmd_write_check( ctx, LR6_CMD_CLEAR_IRQ_STATUS, data_buf, 2 );
}

err_t lr6_set_tx ( lr6_t *ctx, uint32_t timeout_ms )
{
    err_t err_flag = lr6_set_standby( ctx, LR6_STANDBY_RC );
    uint8_t data_buf[ 3 ] = { 0 };
    uint32_t tout = timeout_ms;
    if ( timeout_ms != 0 )
    {
        uint32_t timeout_us = timeout_ms * 1000;
        tout = ( uint32_t ) ( timeout_us / 15.625 );
    }
    
    data_buf[ 0 ] = ( uint8_t ) ( ( tout >> 16 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( tout >> 8 ) & 0xFF) ;
    data_buf[ 2 ] = ( uint8_t ) ( tout & 0xFF);
    err_flag |= lr6_cmd_write_check( ctx, LR6_CMD_SET_TX, data_buf, 3 );
    
    for( uint8_t cnt = 0; cnt < 10; cnt++ )
    {
        uint8_t status = DUMMY;
        err_flag |= lr6_get_status( ctx, &status );
        if ( ( status & LR6_STATUS_BITMASK ) == LR6_STATUS_SET_TX_OK )
        {
            break;
        }
        Delay_1ms( );
    }
    return err_flag;
}

err_t lr6_get_irq_status ( lr6_t *ctx, uint16_t *irq_status )
{
  uint8_t data_buf[ 3 ] = { 0 };
  err_t err_flag = lr6_cmd_read( ctx, LR6_CMD_GET_IRQ_STATUS, data_buf, 3 );
  *irq_status = ( data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
  return err_flag;
}

err_t lr6_send_data ( lr6_t *ctx, uint8_t *send_data, uint8_t len, uint8_t mode ) 
{
    uint16_t irq_status = 0;
    ctx->packet_params[ 3 ] = len;
    err_t err_flag = lr6_cmd_write_check( ctx, LR6_CMD_SET_PACKET_PARAMS, ctx->packet_params, 6);
    err_flag |= lr6_clear_irq_status( ctx, LR6_CLEAR_IRQ_STATUS );
    err_flag |= lr6_buffer_write( ctx, send_data, len);
    err_flag |= lr6_set_tx( ctx, 500 );

    if ( mode & LR6_TX_MODE_SYNC )
    {
        err_flag |= lr6_get_irq_status( ctx, &irq_status );
        while ( ( !( irq_status & LR6_IRQ_TX_DONE ) ) && ( !( irq_status & LR6_IRQ_TIMEOUT ) ) )
        {
            Delay_1ms( );
            err_flag |= lr6_get_irq_status( ctx, &irq_status );
        }
        err_flag |= lr6_set_rx( ctx, LR6_SET_RX_DEFAULT );
        if ( !( irq_status & LR6_IRQ_TX_DONE ) ) 
        {
            err_flag = LR6_ERROR;
        }
    }
    return err_flag;
}

err_t lr6_get_rx_buff_status ( lr6_t *ctx, uint8_t *pl_len, uint8_t *rx_start_buff )
{
    uint8_t data_buf[ 3 ] = { 0 };
    err_t err_flag = lr6_cmd_read( ctx, LR6_CMD_GET_RX_BUFFER_STATUS, data_buf, 3 );
    *pl_len = data_buf[ 1 ];
    *rx_start_buff = data_buf[ 2 ];
    return err_flag;
}

err_t lr6_receive_data ( lr6_t *ctx, uint8_t *receive_data, uint16_t buff_len, uint8_t *rx_len ) 
{
    uint16_t irq_data = 0;
    err_t err_flag = lr6_get_irq_status( ctx, &irq_data );
    if ( irq_data & LR6_IRQ_ALL )
    {
        err_flag |= lr6_clear_irq_status( ctx, LR6_CLEAR_IRQ_STATUS );
        err_flag |= lr6_buffer_read( ctx, receive_data, buff_len, rx_len );
    }
    return err_flag;
}

err_t lr6_get_packet_status ( lr6_t *ctx, int8_t *rssi, int8_t *snr )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t err_flag = lr6_cmd_read( ctx, LR6_CMD_GET_PACKET_STATUS, data_buf, 4 );
    *rssi = ( ( int8_t ) data_buf[ 0 ] ) >> 1;
    *snr =  ( ( int8_t ) data_buf[ 2 ] ) >> 2;
    return err_flag;
}

// ------------------------------------------------------------------------- END
