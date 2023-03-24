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
 * @file lriot.c
 * @brief LR IoT Click Driver.
 */

#include "lriot.h"
#include "transceiver/lr1110_system.h"
#include "transceiver/lr1110_wifi.h"
#include "transceiver/lr1110_gnss.h"
#include "transceiver/lr1110_radio.h"
#include "modem/lr1110_modem_lorawan.h"
#include "modem/lr1110_modem_wifi.h"
#include "modem/lr1110_modem_system.h"
#include "modem/lr1110_modem_gnss.h"
#include "modem/lr1110_modem_helper.h"
#include "firmware_update/lr1110_firmware_update.h"
#include "firmware_update/lr1110_transceiver_0307.h"
#include "firmware_update/lr1110_modem_010107.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void lriot_cfg_setup ( lriot_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->bsy  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t lriot_init ( lriot_t *ctx, lriot_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->bsy, cfg->bsy );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    ctx->bsy_pin_name = cfg->bsy;

    return SPI_MASTER_SUCCESS;
}

err_t lriot_default_cfg ( lriot_t *ctx ) 
{
    err_t error_flag = LRIOT_OK;
    lriot_set_rst_pin ( ctx, 1 );
    Delay_1sec ( );

#if LRIOT_UPDATE_FIRMWARE
    error_flag |= lriot_update_firmware ( ctx );
    Delay_1sec ( );
#endif
    
#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
    error_flag |= lr1110_system_set_tcxo_mode ( ctx, LR1110_SYSTEM_TCXO_CTRL_1_8V, LRIOT_TCXO_DELAY_2SEC );
    Delay_1sec ( );
    Delay_1sec ( );
    lr1110_system_rfswitch_cfg_t rf_switch_cfg = { 0 };
    rf_switch_cfg.enable = LR1110_SYSTEM_RFSW0_HIGH | LR1110_SYSTEM_RFSW1_HIGH | LR1110_MODEM_SYSTEM_RFSW2_HIGH | LR1110_MODEM_SYSTEM_RFSW3_HIGH;
    rf_switch_cfg.standby = 0;
    rf_switch_cfg.tx_mode = LR1110_SYSTEM_RFSW0_HIGH | LR1110_SYSTEM_RFSW1_HIGH;
    rf_switch_cfg.tx_hp   = LR1110_SYSTEM_RFSW1_HIGH;
    rf_switch_cfg.rx_mode = LR1110_SYSTEM_RFSW0_HIGH;
    rf_switch_cfg.gnss = LR1110_MODEM_SYSTEM_RFSW3_HIGH;
    rf_switch_cfg.wifi = LR1110_MODEM_SYSTEM_RFSW2_HIGH;
    
    error_flag |= lr1110_system_set_dio_as_rf_switch ( ctx, &rf_switch_cfg );
    
    ctx->wifi_settings.signal_type         = LR1110_WIFI_TYPE_SCAN_B_G_N,
    ctx->wifi_settings.channels            = LR1110_WIFI_ALL_CHANNELS,
    ctx->wifi_settings.scan_mode           = LR1110_WIFI_SCAN_MODE_FULL_BEACON,
    ctx->wifi_settings.max_results         = LRIOT_WIFI_SCAN_MAX_RESULTS,
    ctx->wifi_settings.nb_scan_per_channel = 30,
    ctx->wifi_settings.timeout_in_ms       = 110,
    ctx->wifi_settings.abort_on_timeout    = true;
    
    error_flag |= lr1110_gnss_set_constellations_to_use( ctx, LR1110_GNSS_GPS_MASK | LR1110_GNSS_BEIDOU_MASK );
    
    error_flag |= lr1110_gnss_set_scan_mode( ctx, LR1110_GNSS_SCAN_MODE_0_SINGLE_SCAN_LEGACY );
    
    // Config LoRa
    // 0. Reset the device (Init)
    error_flag |= lr1110_system_set_reg_mode ( ctx, LR1110_SYSTEM_REG_MODE_DCDC );
    error_flag |= lr1110_system_cfg_lfclk ( ctx, LR1110_SYSTEM_LFCLK_XTAL, true );
    error_flag |= lr1110_system_clear_errors ( ctx );
    error_flag |= lr1110_system_calibrate ( ctx, 0x3F );
    uint16_t errors;
    error_flag |= lr1110_system_get_errors ( ctx, &errors );
    error_flag |= lr1110_system_clear_errors ( ctx );
    error_flag |= lr1110_system_clear_irq_status ( ctx, LR1110_SYSTEM_IRQ_ALL_MASK );
    
    // 1. Set packet type
    error_flag |= lr1110_radio_set_pkt_type ( ctx, LR1110_RADIO_PKT_TYPE_LORA );
    
    // 2. Set RF frequency
    error_flag |= lr1110_radio_set_rf_freq( ctx, LRIOT_LORA_DEFAULT_FREQ );

    // 3. Set PA configuration
    lr1110_radio_pa_cfg_t pa_cfg;
    pa_cfg.pa_sel = LR1110_RADIO_PA_SEL_HP;
    pa_cfg.pa_reg_supply = LR1110_RADIO_PA_REG_SUPPLY_VREG;
    pa_cfg.pa_duty_cycle = 0x04;
    pa_cfg.pa_hp_sel = 0x07;
    error_flag |= lr1110_radio_set_pa_cfg( ctx, &pa_cfg );

    // 4. Set tx output power
    error_flag |= lr1110_radio_set_tx_params( ctx, 14, LR1110_RADIO_RAMP_48_US );
    error_flag |= lr1110_radio_set_rx_tx_fallback_mode( ctx, LR1110_RADIO_FALLBACK_STDBY_RC );
    error_flag |= lr1110_radio_cfg_rx_boosted( ctx, false );
    
    // 5. Set modulation and packet parameters
    lr1110_radio_mod_params_lora_t mod_params_lora;
    mod_params_lora.sf = LR1110_RADIO_LORA_SF7;
    mod_params_lora.bw = LR1110_RADIO_LORA_BW_125;
    mod_params_lora.cr = LR1110_RADIO_LORA_CR_4_5;
    mod_params_lora.ldro = 0;
    error_flag |= lr1110_radio_set_lora_mod_params ( ctx, &mod_params_lora );
    lr1110_radio_pkt_params_lora_t pkt_params_lora;
    pkt_params_lora.preamble_len_in_symb = 8;
    pkt_params_lora.pld_len_in_bytes = LRIOT_LORA_PKT_PAYLOAD_LEN;
    pkt_params_lora.header_type = LR1110_RADIO_LORA_PKT_EXPLICIT;
    pkt_params_lora.iq = LR1110_RADIO_LORA_IQ_INVERTED;
    pkt_params_lora.crc = LR1110_RADIO_LORA_CRC_ON;
    error_flag |= lr1110_radio_set_lora_pkt_params ( ctx, &pkt_params_lora );

    // 6. Set public network
    error_flag |= lr1110_radio_set_lora_sync_word ( ctx, 0x12 ); // 0x12 Private Network, 0x34 Public Network
    
    // 7. Enable IRQs
    error_flag |= lr1110_system_set_dio_irq_params( ctx, LR1110_SYSTEM_IRQ_TX_DONE | 
                                                         LR1110_SYSTEM_IRQ_RX_DONE | 
                                                         LR1110_SYSTEM_IRQ_TIMEOUT | 
                                                         LR1110_SYSTEM_IRQ_CRC_ERROR, 0 );
    error_flag |= lr1110_system_clear_irq_status ( ctx, LR1110_SYSTEM_IRQ_ALL_MASK );
    
#else
    error_flag |= lr1110_modem_system_set_tcxo_mode ( ctx, LR1110_MODEM_SYSTEM_TCXO_CTRL_1_8V, LRIOT_TCXO_DELAY_2SEC );
    Delay_1sec ( );
    Delay_1sec ( );
    lr1110_modem_system_rf_switch_cfg_t rf_switch_cfg = { 0 };
    rf_switch_cfg.enable = LR1110_MODEM_SYSTEM_RFSW2_HIGH | LR1110_MODEM_SYSTEM_RFSW3_HIGH;
    rf_switch_cfg.gnss = LR1110_MODEM_SYSTEM_RFSW3_HIGH;
    rf_switch_cfg.wifi = LR1110_MODEM_SYSTEM_RFSW2_HIGH;
    
    error_flag |= lr1110_modem_system_set_dio_as_rf_switch ( ctx, &rf_switch_cfg );
    
    ctx->wifi_settings.signal_type         = LR1110_MODEM_WIFI_TYPE_SCAN_B_G_N,
    ctx->wifi_settings.channels            = LR1110_MODEM_WIFI_ALL_CHANNELS,
    ctx->wifi_settings.scan_mode           = LR1110_MODEM_WIFI_SCAN_MODE_FULL_BEACON,
    ctx->wifi_settings.max_results         = LRIOT_WIFI_SCAN_MAX_RESULTS,
    ctx->wifi_settings.nb_scan_per_channel = 30,
    ctx->wifi_settings.timeout_in_ms       = 110,
    ctx->wifi_settings.abort_on_timeout    = true;
    ctx->wifi_settings.result_format       = LR1110_MODEM_WIFI_RESULT_FORMAT_BASIC_COMPLETE;

    /* GNSS Parameters */
    lr1110_modem_gnss_set_constellations_to_use( ctx, LR1110_MODEM_GNSS_GPS_MASK | LR1110_MODEM_GNSS_BEIDOU_MASK );
#endif
    return error_flag;
}

void lriot_set_rst_pin ( lriot_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t lriot_get_busy_pin ( lriot_t *ctx )
{
    return digital_in_read ( &ctx->bsy );
}

uint8_t lriot_get_int_pin ( lriot_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t lriot_get_chip_info ( lriot_t *ctx, lriot_chip_info_t *info )
{
    err_t error_flag = LRIOT_OK;
#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
    error_flag |= lr1110_system_get_version ( ctx, &info->version );
    error_flag |= lr1110_system_read_uid ( ctx, info->uid );
    error_flag |= lr1110_system_read_join_eui ( ctx, info->join_eui );
    error_flag |= lr1110_system_read_pin ( ctx, info->pin );
#else
    error_flag |= lr1110_modem_get_version ( ctx, &info->version );
    error_flag |= lr1110_modem_get_chip_eui ( ctx, info->chip_eui );
    error_flag |= lr1110_modem_get_dev_eui ( ctx, info->dev_eui );
    error_flag |= lr1110_modem_get_join_eui ( ctx, info->join_eui );
    error_flag |= lr1110_modem_get_pin ( ctx, &info->pin );
#endif
    return error_flag;
}

err_t lriot_get_wifi_scan_results ( lriot_t *ctx, lriot_wifi_scan_results_t *results )
{
    err_t error_flag = LRIOT_OK;
#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
    /* Prepare event interrupt line */
    error_flag |= lr1110_system_set_dio_irq_params( ctx, LR1110_SYSTEM_IRQ_WIFI_SCAN_DONE, 0 );
    
    error_flag |= lr1110_wifi_reset_cumulative_timing( ctx );

    /* Start up wifi scan, function itself is not blocking, 
     * however, we wait for WIFI_SCAN_DONE event. */
    error_flag |= lr1110_wifi_scan( ctx, 
                                    ctx->wifi_settings.signal_type, 
                                    ctx->wifi_settings.channels, 
                                    ctx->wifi_settings.scan_mode, 
                                    ctx->wifi_settings.max_results, 
                                    ctx->wifi_settings.nb_scan_per_channel, 
                                    ctx->wifi_settings.timeout_in_ms, 
                                    ctx->wifi_settings.abort_on_timeout );

    /* Blocking wait */
    while ( !lriot_get_int_pin( ctx ) );

    /* Read scanning time */
    lr1110_wifi_read_cumulative_timing( ctx, &results->timings );
    
    /* Clear event interrupt line */
    error_flag |= lr1110_system_clear_irq_status( ctx, LR1110_SYSTEM_IRQ_WIFI_SCAN_DONE );

    /* Get number of wifi scan results */
    error_flag |= lr1110_wifi_get_nb_results( ctx, &results->num_wifi_results );
    
    error_flag |= lr1110_wifi_read_extended_full_results( ctx, LRIOT_WIFI_SCAN_DISPLAY_ALL, 
                                                          results->num_wifi_results, results->scan_results );
#else
    uint8_t wifi_max_results = ctx->wifi_settings.max_results;
    error_flag |= lr1110_modem_wifi_reset_cumulative_timing( ctx );
    if ( ctx->wifi_settings.max_results > LRIOT_WIFI_SCAN_MAX_RESULTS )
    {
        wifi_max_results = LRIOT_WIFI_SCAN_MAX_RESULTS;
    }
    
    if ( LRIOT_ERROR == lr1110_modem_wifi_passive_scan( ctx, ctx->wifi_settings.signal_type, 
                                                        ctx->wifi_settings.channels, 
                                                        ctx->wifi_settings.scan_mode, 
                                                        wifi_max_results,
                                                        ctx->wifi_settings.nb_scan_per_channel, 
                                                        ctx->wifi_settings.timeout_in_ms, 
                                                        ctx->wifi_settings.abort_on_timeout,
                                                        ctx->wifi_settings.result_format ) )
    {
        return LRIOT_ERROR;
    }
    while ( !lriot_get_int_pin( ctx ) );
    
    lr1110_modem_event_t modem_event;
    lr1110_modem_helper_get_event_data( ctx, &modem_event );
    if ( LR1110_MODEM_LORAWAN_EVENT_WIFI_SCAN_DONE != modem_event.event_type )
    {
        return LRIOT_ERROR;
    }
    lr1110_modem_wifi_read_cumulative_timing( ctx, &results->timings );
    if ( ctx->wifi_settings.scan_mode == LR1110_MODEM_WIFI_SCAN_MODE_FULL_BEACON )
    {
        /* Parse result buffer */
        lr1110_modem_wifi_read_extended_full_results( modem_event.event_data.wifi.buffer, modem_event.event_data.wifi.len,
                                                      results->scan_results, &results->num_wifi_results );
    }
    else
    {
        memcpy( results->scan_results, modem_event.event_data.wifi.buffer, modem_event.event_data.wifi.len );
        results->num_wifi_results = modem_event.event_data.wifi.len;
    }
#endif
    return error_flag;
}

err_t lriot_get_gnss_scan_results ( lriot_t *ctx, lriot_gnss_scan_results_t *results )
{
    err_t error_flag = LRIOT_OK;
#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
    /* Prepare event interrupt line */
    error_flag |= lr1110_system_set_dio_irq_params( ctx, LR1110_SYSTEM_IRQ_GNSS_SCAN_DONE, 0 );

    /* Start up GNSS scan, function itself is not blocking, 
     * however, we wait for GNSS_SCAN_DONE event. */
    error_flag |= lr1110_gnss_scan_autonomous( ctx, 
                                               0, 
                                               LR1110_GNSS_OPTION_DEFAULT, 
                                               LR1110_GNSS_RESULTS_LEGACY_PSEUDO_RANGE_MASK | 
                                               LR1110_GNSS_RESULTS_LEGACY_DOPPLER_MASK, 
                                               LRIOT_GNSS_SCAN_DISPLAY_ALL );

    /* Blocking wait */
    while ( !lriot_get_int_pin( ctx ) );

    /* Clear event interrupt line */
    error_flag |= lr1110_system_clear_irq_status( ctx, LR1110_SYSTEM_IRQ_GNSS_SCAN_DONE );

    /* Get number of GNSS scan results */
    error_flag |= lr1110_gnss_get_nb_detected_satellites( ctx, &results->num_satellites );
    
    if ( ( results->num_satellites > 0 ) && ( LRIOT_OK == error_flag ) )
    {
        error_flag |= lr1110_gnss_get_detected_satellites( ctx, results->num_satellites, results->satellite_id_cnr_doppler );
        error_flag |= lr1110_gnss_get_result_size( ctx, &results->scan_results_len );
        error_flag |= lr1110_gnss_read_results( ctx, results->scan_results, results->scan_results_len );
        error_flag |= lr1110_gnss_get_result_destination( results->scan_results, 
                                                          results->scan_results_len, 
                                                          &results->destination_id );
    }
#else
    if ( LRIOT_ERROR == lr1110_modem_gnss_scan_autonomous( ctx, LR1110_MODEM_GNSS_OPTION_BEST_EFFORT, 
                                                           LR1110_MODEM_GNSS_PSEUDO_RANGE_MASK, LRIOT_GNSS_SCAN_MAX_SATELLITES ) )
    {
        return LRIOT_ERROR;
    }
    while ( !lriot_get_int_pin( ctx ) );
    
    lr1110_modem_event_t modem_event;
    lr1110_modem_helper_get_event_data( ctx, &modem_event );
    if ( LR1110_MODEM_LORAWAN_EVENT_GNSS_SCAN_DONE != modem_event.event_type )
    {
        return LRIOT_ERROR;
    }
    memcpy( results->scan_results, modem_event.event_data.gnss.nav_message, modem_event.event_data.gnss.len );
    results->scan_results_len = modem_event.event_data.gnss.len;
    lr1110_modem_gnss_get_nb_detected_satellites( ctx, &results->num_satellites );
    lr1110_modem_gnss_get_detected_satellites( ctx, results->num_satellites, results->satellite_id_cnr );
    lr1110_modem_helper_gnss_get_result_destination( modem_event.event_data.gnss.nav_message, 
                                                     modem_event.event_data.gnss.len, &results->destination_id );
#endif
    return error_flag;
}

err_t lriot_update_firmware ( lriot_t *ctx )
{
#if LRIOT_UPDATE_FIRMWARE
    return lr1110_update_firmware ( ctx, LR1110_FIRMWARE_VERSION, lr1110_firmware_image, LR1110_FIRMWARE_IMAGE_SIZE );
#endif
    return LRIOT_ERROR;
}

#if ( LRIOT_FIRMWARE_SELECTOR == LRIOT_TRANSCEIVE_FIRMWARE )
err_t lriot_get_temperature ( lriot_t *ctx, float *temperature )
{
    uint16_t raw_temp = 0;
    err_t error_flag = lr1110_system_get_temp ( ctx, &raw_temp );
    *temperature = LRIOT_TEMP_NOMINAL + 
                   ( LRIOT_TEMP_SLOPE_DIVIDEND / LRIOT_TEMP_SLOPE ) * 
                   ( ( ( raw_temp / LRIOT_TEMP_RESOLUTION ) * LRIOT_TEMP_INT_VREF ) - LRIOT_TEMP_VOLTAGE_AT_25C );
    return error_flag;
}

err_t lriot_send_lora_message ( lriot_t *ctx, uint8_t *message )
{
    err_t error_flag = LRIOT_OK;
    lr1110_system_irq_mask_t irq_status;
    error_flag |= lr1110_radio_set_pkt_type ( ctx, LR1110_RADIO_PKT_TYPE_LORA );
    error_flag |= lr1110_radio_set_rf_freq( ctx, LRIOT_LORA_DEFAULT_FREQ );
    error_flag |= lr1110_system_set_dio_irq_params( ctx, LR1110_SYSTEM_IRQ_TX_DONE | 
                                                         LR1110_SYSTEM_IRQ_TIMEOUT, 0 );
    error_flag |= lr1110_system_clear_irq_status ( ctx, LR1110_SYSTEM_IRQ_ALL_MASK );
    error_flag |= lr1110_regmem_write_buffer8 ( ctx, message, LRIOT_LORA_PKT_PAYLOAD_LEN );
    error_flag |= lr1110_radio_set_tx ( ctx, 0 );
    /* Blocking wait */
    while ( !lriot_get_int_pin(  ctx ) );
    /* Clear event interrupt line */
    error_flag |= lr1110_system_get_and_clear_irq_status ( ctx, &irq_status );
    
    if ( LR1110_SYSTEM_IRQ_TX_DONE == ( irq_status & LR1110_SYSTEM_IRQ_TX_DONE ) )
    {
        return error_flag;
    }
    return LRIOT_ERROR;
}

err_t lriot_read_lora_message ( lriot_t *ctx, lriot_lora_packet_status_t *pkt_status, uint8_t *message )
{
    err_t error_flag = LRIOT_OK;
    lr1110_system_irq_mask_t irq_regs;
    error_flag |= lr1110_radio_set_pkt_type ( ctx, LR1110_RADIO_PKT_TYPE_LORA );
    error_flag |= lr1110_radio_set_rf_freq( ctx, LRIOT_LORA_DEFAULT_FREQ );
    error_flag |= lr1110_system_set_dio_irq_params( ctx, LR1110_SYSTEM_IRQ_RX_DONE | 
                                                         LR1110_SYSTEM_IRQ_TIMEOUT | 
                                                         LR1110_SYSTEM_IRQ_CRC_ERROR, 0 );
    error_flag |= lr1110_system_clear_irq_status ( ctx, LR1110_SYSTEM_IRQ_ALL_MASK );
    error_flag |= lr1110_radio_set_rx( ctx, 0 );
    /* Blocking wait */
    while ( !lriot_get_int_pin(  ctx ) );
    /* Clear event interrupt line */
    error_flag |= lr1110_system_get_and_clear_irq_status( ctx, &irq_regs );
    
    if ( LR1110_SYSTEM_IRQ_TIMEOUT == ( irq_regs & LR1110_SYSTEM_IRQ_TIMEOUT ) )
    {
        return LRIOT_ERROR;
    }
    if ( LR1110_SYSTEM_IRQ_RX_DONE == ( irq_regs & LR1110_SYSTEM_IRQ_RX_DONE ) )
    {
        if ( LR1110_SYSTEM_IRQ_CRC_ERROR == ( irq_regs & LR1110_SYSTEM_IRQ_CRC_ERROR ) )
        {
            return LRIOT_ERROR;
        }
        else
        {
            lr1110_radio_rx_buffer_status_t rx_buffer_status;
            lr1110_radio_pkt_status_lora_t lr_pkt_status;
            
            error_flag |= lr1110_radio_get_rx_buffer_status( ctx, &rx_buffer_status );

            error_flag |= lr1110_regmem_read_buffer8( ctx, message, rx_buffer_status.buffer_start_pointer,
                                                      rx_buffer_status.pld_len_in_bytes );
            if ( LRIOT_OK == lr1110_radio_get_lora_pkt_status( ctx, &lr_pkt_status ) )
            {
                pkt_status->rssi_pkt_in_dbm = lr_pkt_status.rssi_pkt_in_dbm;
                pkt_status->signal_rssi_pkt_in_dbm = lr_pkt_status.signal_rssi_pkt_in_dbm;
                pkt_status->snr_pkt_in_db = lr_pkt_status.snr_pkt_in_db;
                return error_flag;
            }
        }
    }
    return LRIOT_ERROR;
}
#endif

// ------------------------------------------------------------------------- END
