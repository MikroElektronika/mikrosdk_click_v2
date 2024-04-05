/*!
 * @file main.c
 * @brief BleTx Click example
 *
 * # Description
 * This library contains API for the BLE TX Click driver.
 * This example processes data from BLE TX Click, BLE TX Click 
 * Bluetooth® Low Energy compliant advertising transmission 
 * can be achieved by simply configuring the transmission power, 
 * data, and transmission - start trigger.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * Initializes driver and set performs the default configuration.
 * Configure Bluetooth Low Energy Beacons to transmit so-called advertising frames.
 * Configuration of the Eddystone URI, UID, or TLM 
 * Bluetooth Low Energy Beacons profile task depends on uncommented code.
 * Eddystone ( URI ) : broadcasts a URL of at most 15 characters 
 * that redirects to a website that is secured using SSL.
 * Eddystone ( UID ) : broadcasts an identifying code 
 * that allows apps to retrieve information from app servers. 
 * Eddystone ( TLM ) : broadcasts information about the beacon,
 * include battery level, sensor data, or other relevant information 
 * to beacon administrators.
 *
 * ## Application Task
 * This is an example that shows the use of a BLE TX click board™.
 * In this example, the application turns the selected advertising frames
 * ON and OFF for a period of 10 seconds.
 *
 * @note
 * For scanning BLE TX click board™ BLE Scanner is a recommended Android application 
 * and you can find it at the link:
 * https://play.google.com/store/apps/details?id=com.macdom.ble.blescanner
 * 
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "bletx.h"

static bletx_t bletx;
static log_t logger;

#define URI
// #define UID
// #define TLM

bletx_adv_cfg_t adv_cfg;
bletx_eddystone_data_t adv_data;

void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    bletx_cfg_t bletx_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    bletx_cfg_setup( &bletx_cfg );
    BLETX_MAP_MIKROBUS( bletx_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == bletx_init( &bletx, &bletx_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    bletx_default_cfg ( &bletx );
    Delay_ms ( 1000 );
    
    adv_cfg.adv_ch_1_frequency = ADVCH1_37_Ch_2402_MHz;
    adv_cfg.adv_ch_2_frequency = ADVCH2_38_Ch_2426_MHz;
    adv_cfg.adv_ch_3_frequency = ADVCH3_39_Ch_2480_MHz;
    adv_cfg.tx_output_power = TX_POWER_0_dBm;
    adv_cfg.txdata_loop = 0;
    adv_cfg.txdata_cw = 0;
    adv_cfg.eventnum = 0;
    adv_cfg.advdelay_enb = BLETX_ADV_DELAY_ENABLE;
    adv_cfg.avdintvl_interval_ms = 0;
    adv_cfg.crc_enb = BLETX_CRC_ENABLE;
    adv_cfg.white_enb = BLETX_WHITE_ENABLE;
    adv_cfg.pdu_len = 39;
    
    adv_cfg.uuid[ 0 ] = 0x11;
    adv_cfg.uuid[ 1 ] = 0x22;
    adv_cfg.uuid[ 2 ] = 0x33;
    adv_cfg.uuid[ 3 ] = 0x44;
    adv_cfg.uuid[ 4 ] = 0x55;
    adv_cfg.uuid[ 5 ] = 0x66;
    
    if ( BLETX_OK != bletx_set_configuration( &bletx, adv_cfg ) ) 
    {
        log_error( &logger, " Set configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
#ifdef URI
    adv_data.length_of_service_list = 3;
    adv_data.param_service_list = 3;
    adv_data.eddystone_id = BLETX_EDDYSTONE_SERVICE_UUID;
    adv_data.length_of_service_data = 13;
    adv_data.service_data = BLETX_EDDYSTONE_SERVICE_DATA_TYPE_VALUE;
    adv_data.frame_type_url = BLETX_EDDYSTONE_FRAME_TYPE_URL;
    adv_data.power = BLETX_TX_POWER_LVL_MODE_LOWEST;
    adv_data.spec_data = BLETX_EDDYSTONE_SPEC_DATA_HTTPS_WWW;
    adv_data.advdata_url[ 0 ] = 'm';
    adv_data.advdata_url[ 1 ] = 'i';
    adv_data.advdata_url[ 2 ] = 'k';
    adv_data.advdata_url[ 3 ] = 'r';
    adv_data.advdata_url[ 4 ] = 'o';
    adv_data.advdata_url[ 5 ] = 'e';
    adv_data.domain = BLETX_CHARACTER_CODES_DOT_COM;
    
    bletx_create_eddystone_uri ( &bletx, adv_data );
#endif

#ifdef UID
    adv_data.length_of_service_list = 3;
    adv_data.param_service_list = 3;
    adv_data.eddystone_id = BLETX_EDDYSTONE_SERVICE_UUID;
    adv_data.length_of_service_data = 23;
    adv_data.service_data = BLETX_EDDYSTONE_SERVICE_DATA_TYPE_VALUE;
    adv_data.frame_type_url = BLETX_EDDYSTONE_FRAME_TYPE_UID;
    adv_data.power = BLETX_TX_POWER_LVL_MODE_LOW;          
    
    adv_data.name_space_id[ 0 ] = 0x01;
    adv_data.name_space_id[ 1 ] = 0x02;
    adv_data.name_space_id[ 2 ] = 0x03;
    adv_data.name_space_id[ 3 ] = 0x04;
    adv_data.name_space_id[ 4 ] = 0x05;
    adv_data.name_space_id[ 5 ] = 0x06;
    adv_data.name_space_id[ 6 ] = 0x07;
    adv_data.name_space_id[ 7 ] = 0x08;
    adv_data.name_space_id[ 8 ] = 0x09;
    adv_data.name_space_id[ 9 ] = 0x0A;
    
    adv_data.instance_id[ 0 ] = 0x01;
    adv_data.instance_id[ 1 ] = 0x23;
    adv_data.instance_id[ 2 ] = 0x45;
    adv_data.instance_id[ 3 ] = 0x67;
    adv_data.instance_id[ 4 ] = 0x89;
    adv_data.instance_id[ 5 ] = 0xAB;
    
    bletx_create_eddystone_uid ( &bletx, adv_data );
#endif

#ifdef TLM
    adv_data.length_of_service_list = 3;
    adv_data.param_service_list = 3;
    adv_data.eddystone_id = BLETX_EDDYSTONE_SERVICE_UUID;
    adv_data.length_of_service_data = 23;
    adv_data.service_data = BLETX_EDDYSTONE_SERVICE_DATA_TYPE_VALUE;
    adv_data.frame_type_url = BLETX_EDDYSTONE_FRAME_TYPE_TLM;
    adv_data.tlm_version = 0;          // TLM version
    adv_data.spec_data = BLETX_EDDYSTONE_SPEC_DATA_TLM;
    
    adv_data.battery_voltage = 3600;
    adv_data.beacon_temperature = 20.21;
    adv_data.pdu_count = 11223344;
    
    bletx_create_eddystone_tlm ( &bletx, adv_data );
#endif
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{  
    log_printf( &logger, ">>>\tStart Advertising \r\n" );
    bletx_start_advertising( &bletx );
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">>>\tStop Advertising \r\n" );
    bletx_stop_advertising( &bletx );
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
