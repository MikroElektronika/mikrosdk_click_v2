/*!
 * @file main.c
 * @brief GNSS RTK Click Example.
 *
 * # Description
 * This example reads and processes data from GNSS RTK click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and starts the module.
 *
 * ## Application Task
 * Reads the received data and parses it.
 *
 * ## Additional Functions
 * - static err_t gnssrtk_process ( void ) - The general process of collecting responses
 *   sent from the module.
 * - static void parser_application ( char *rsp ) - Parsing the response into a more
 *   readable form and printing it on the UART terminal.
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "gnssrtk.h"
#include "string.h"

#define PROCESS_COUNTER                         10
#define PROCESS_RX_BUFFER_SIZE                  500
#define PROCESS_PARSER_BUFFER_SIZE              500

#define ELEMENT_BUFFER_NULL                     0

static gnssrtk_t gnssrtk;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void gnssrtk_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
{
        rsp_size = gnssrtk_generic_read( &gnssrtk, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
}

static void parser_application ( char *rsp )
{
    char element_buf[ 200 ] = { 0 };
    
    log_printf( &logger, "\r\n-----------------------\r\n", element_buf ); 
    
    gnssrtk_generic_parser( rsp, GNSSRTK_NMEA_GNGGA, GNSSRTK_GNGGA_LATITUDE, element_buf );
    if ( element_buf[ 0 ] == ELEMENT_BUFFER_NULL )
    {
        log_printf( &logger, "Latitude: No data available!", element_buf );
    }
    else log_printf( &logger, "Latitude:  %s ", element_buf ); 
    
    memset( element_buf, 0, sizeof( element_buf ) );
    
    gnssrtk_generic_parser( rsp, GNSSRTK_NMEA_GNGGA, GNSSRTK_GNGGA_LATITUDE_SIDE, element_buf );
    log_printf( &logger, "%s \r\n", element_buf );
    
    gnssrtk_generic_parser( rsp, GNSSRTK_NMEA_GNGGA, GNSSRTK_GNGGA_LONGITUDE, element_buf );
    if ( element_buf[ 0 ] == ELEMENT_BUFFER_NULL )
    {
        log_printf( &logger, "Longitude: No data available!", element_buf );
    }
    else log_printf( &logger, "Longitude:  %s ", element_buf );
    
    memset( element_buf, 0, sizeof( element_buf ) );
    
    gnssrtk_generic_parser( rsp, GNSSRTK_NMEA_GNGGA, GNSSRTK_GNGGA_LONGITUDE_SIDE, element_buf );
    log_printf( &logger, "%s \r\n", element_buf );
    
    gnssrtk_generic_parser( rsp, GNSSRTK_NMEA_GNGGA, GNSSRTK_GNGGA_ALTITUDE, element_buf );
    if ( element_buf[ 0 ] == ELEMENT_BUFFER_NULL )
    {
        log_printf( &logger, "Alitude: No data available!", element_buf );
    }
    else log_printf( &logger, "Alitude: %s ", element_buf ); 
    
    memset( element_buf, 0, sizeof( element_buf ) );
    
    gnssrtk_generic_parser( rsp, GNSSRTK_NMEA_GNGGA, GNSSRTK_GNGGA_ALTITUDE_UNIT, element_buf );
    log_printf( &logger, "%s \r\n", element_buf );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssrtk_cfg_t gnssrtk_cfg;  /**< Click config object. */

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

    gnssrtk_cfg_setup( &gnssrtk_cfg );
    GNSSRTK_MAP_MIKROBUS( gnssrtk_cfg, MIKROBUS_1 );
    Delay_ms( 100 );
    err_t init_flag  = gnssrtk_init( &gnssrtk, &gnssrtk_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    gnssrtk_default_cfg ( &gnssrtk );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) {
    gnssrtk_process();
    parser_application( current_parser_buf );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
