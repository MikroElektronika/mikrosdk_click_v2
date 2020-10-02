/*!
 * \file 
 * \brief WifiBle Click example
 * 
 * # Description
 * This example reads and processes data from WiFi BLE clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, power init and info module.
 * 
 * ## Application Task  
 * Connected to TCP and BLE server, and reads data.
 * 
 * ## Additional Function
 * - wifible_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "wifible.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

#define i_beacon_prefx        "0201061AFF4C000215"
#define i_beacon_UUID         "FDA50693A4E24FB1AFCFC6EB07647825"
#define i_beacon_major        "0001"
#define i_beacon_minor        "0006"
#define i_beacon_tx_power      "C5"

#define AT           "AT"
#define ATE          "ATE0"
#define AT_GMR       "AT+GMR"
#define AT_UART_CUR  "AT+UART_CUR?"

#define WIFI_AT_CWMODE      "AT+CWMODE=3"
#define WIFI_AT_CWJAP       "AT+CWJAP=\"network_ssid\",\"network_pass\""
#define WIFI_AT_CIFSR       "AT+CIFSR"
#define WIFI_AT_CIPSTART    "AT+CIPSTART=\"TCP\",\"192.168.1.4\",8080"
#define WIFI_AT_CIPSEND     "AT+CIPSEND=6"
#define WIFI_MIKROE         "MIKROE"
#define WIFI_AT_CIPCLOSE    "AT+CIPCLOSE"

#define BLE_AT_BLEINIT        "AT+BLEINIT=2"
#define BLE_AT_BLEADVSTART    "AT+BLEADVSTART"
#define BLE_AT_BLEADVDATA     "AT+BLEADVDATA="

// ------------------------------------------------------------------ VARIABLES

//#define BLUETOOTH_CONNECTION
#define WIRELESS_CONNECTION

static wifible_t wifible;
static log_t logger;

static char beacon_data[ 150 ] = { 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void wifible_process ( void )
{
    int16_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
      
    while( process_cnt != 0 )
    {
        rsp_size = wifible_generic_read( &wifible, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            log_printf( &logger, "%s", uart_rx_buffer );
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_100ms( );
        }
    }
}

void package_beacon_data ( )
{
    strcpy( beacon_data, BLE_AT_BLEADVDATA );
    strcat( beacon_data, "\"" );
    strcat( beacon_data, i_beacon_prefx );
    strcat( beacon_data, i_beacon_UUID  );
    strcat( beacon_data, i_beacon_major );
    strcat( beacon_data, i_beacon_minor );
    strcat( beacon_data, i_beacon_tx_power );
    strcat( beacon_data, "\"" );
}

void wifi_tcp_server ( )
{
    log_printf( &logger, "---- Set the Wi-Fi mode ---- \r\n" );
    wifible_send_command( &wifible, WIFI_AT_CWMODE );
    wifible_process( );
    Delay_ms( 3000 );
    log_printf( &logger, "---- Connect to the router ---- \r\n" );
    wifible_send_command( &wifible, WIFI_AT_CWJAP );
    wifible_process( );
    Delay_ms( 8000 );
    log_printf( &logger, "---- Query the device's IP ---- \r\n" );
    wifible_send_command( &wifible, WIFI_AT_CIFSR );
    wifible_process( );
    Delay_ms( 8000 );
    log_printf( &logger, "---- Connected to the TCP server ---- \r\n" ); 
    wifible_send_command( &wifible, WIFI_AT_CIPSTART );
    wifible_process( );
    Delay_ms( 8000 );
    log_printf( &logger, "---- Send data [MIKROE] ----\r\n " );
    wifible_send_command( &wifible, WIFI_AT_CIPSEND );
    wifible_process( );
    Delay_ms( 8000 );
    wifible_send_command( &wifible, WIFI_MIKROE );
    wifible_process( );
    
    for ( ; ; );
}

void ble_i_beacon ( )
{
    log_printf( &logger, "---- Set BLE server ---- \r\n " );
    wifible_send_command( &wifible, BLE_AT_BLEINIT );
    wifible_process( );
    Delay_ms( 15000 );

    log_printf( &logger, "---- iBeacon Advertisement ---- \r\n " );
    package_beacon_data( );
    wifible_send_command( &wifible, beacon_data ); 
    wifible_process( );
    Delay_ms( 15000 );

    log_printf( &logger, "---- Start advertising ---- \r\n " );
    wifible_send_command( &wifible, BLE_AT_BLEADVSTART );
    wifible_process( );
    Delay_ms( 8000 );
    
    for ( ; ; );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifible_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wifible_cfg_setup( &cfg );
    WIFIBLE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifible_init( &wifible, &cfg );

    //  MODULE POWER ON
    
    wifible_module_power( &wifible, 1 );
    Delay_ms( 2000 );

    wifible_process( );
    
    //  MODULE INIT AND INFO
    
    wifible_send_command( &wifible, AT );
    wifible_process( );
    
    log_printf( &logger, "---- AT ---- \r\n " );
    wifible_send_command( &wifible, AT );
    wifible_process( );

    log_printf( &logger, "---- ATE ---- \r\n " );
    wifible_send_command( &wifible, ATE );
    wifible_process( );

    log_printf( &logger, "---- AT_GMR ---- \r\n " );
    wifible_send_command( &wifible, AT_GMR );
    wifible_process( );

    log_printf( &logger, "---- AT_UART ---- \r\n " );
    wifible_send_command( &wifible, AT_UART_CUR );
    wifible_process( ); 

    log_printf( &logger, "----- START EXAMPLE ----- \r\n" );
}

void application_task ( void )
{
#ifdef WIRELESS_CONNECTION
    wifi_tcp_server( );
#endif    

#ifdef BLUETOOTH_CONNECTION
    ble_i_beacon( );
#endif    
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
