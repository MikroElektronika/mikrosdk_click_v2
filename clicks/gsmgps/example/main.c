/*!
 * \file 
 * \brief Gsmgps Click example
 * 
 * # Description
 * This example reads and processes data from GSMGPS clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - gsmgps_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * *note:* 
 * <NOTE>
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gsmgps.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static gsmgps_t gsmgps;
static log_t logger;

// Sensor/Actuator reference
#define ACTUAROT_SW_REF   "G2C3G_TEST_AB"
#define ACTUAROT_STR_REF  "G2C3G_TEST_AS"
#define ACTUAROT_CNT_REF  "G2C3G_TEST_AC"
#define SENSOR_REF        "G2C3G_TEST_S"

// Operator settings
#define OPERATOR_APN      "vipmobile"
#define OPERATOR_USERNAME "vipmobile"
#define OPERATOR_PASSWORD "vipmobile"

// Broker(device) settings
#define DEVICE_KEY      "bc8mtmm1ztqjol75"
#define DEVICE_PASSWORD "65c64823-78e9-4f78-b154-ac0c6632d466"

static char data_buf[ 20 ] = "12.2";
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 
static uint8_t init_flag = 1;
uint8_t ring_flag = 0;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void gsmgps_process ( void )
{
    uint16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = gsmgps_generic_read( &gsmgps, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
                
                if ( uart_rx_buffer[ check_buf_cnt ] == 82 && uart_rx_buffer[ check_buf_cnt + 1 ] == 73 )
                {
                    ring_flag = 1;
                }
            }
            if ( init_flag || ring_flag )
            {
                log_printf( &logger, "%s", uart_rx_buffer );
                ring_flag = 0;
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
            Delay_100ms( );
        }
    }
}

static void parser_application ( char *rsp )
{
    char element_buf[ 200 ] = { 0 };
    
    log_printf( &logger, "\r\n-----------------------\r\n" ); 
    gsm_gps_generic_parser( rsp, GSM_GPS_NEMA_CGNSINF, GSM_GPS_CGNSINF_LATITUDE, element_buf );
    log_printf( &logger, "Latitude:  %s \r\n", element_buf );    
    gsm_gps_generic_parser( rsp, GSM_GPS_NEMA_CGNSINF, GSM_GPS_CGNSINF_LONGITUDE, element_buf );
    log_printf( &logger, "Longitude:  %s \r\n", element_buf );  
    memset( element_buf, 0, sizeof( element_buf ) );
    gsm_gps_generic_parser( rsp, GSM_GPS_NEMA_CGNSINF, GSM_GPS_CGNSINF_ALTITUDE, element_buf );
    log_printf( &logger, "Alitude: %s \r\n", element_buf );  
}
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gsmgps_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gsmgps_cfg_setup( &cfg );
    GSMGPS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsmgps_init( &gsmgps, &cfg );

    gsmgps_process(  );

    gsmgps_send_command( &gsmgps, GSMGPS_SINGLE_CMD_AT );
    gsmgps_process( );
    gsmgps_send_command( &gsmgps, GSMGPS_SINGLE_CMD_ATI );
    gsmgps_process( );
    gsmgps_send_command( &gsmgps, GSMGPS_SINGLE_CMD_ATE0 );
    gsmgps_process( );
    gsmgps_send_command( &gsmgps, GSMGPS_SINGLE_CMD_CMGF );
    gsmgps_process( );
    gsmgps_send_command( &gsmgps, GSMGPS_CMD_AT_CSCS );
    gsmgps_process( );
    log_printf( &logger, "\r\n---- GSM Init done ---\r\n" );

    gsmgps_send_command( &gsmgps, GSMGPS_CMD_CGNSPWR );
    gsmgps_process(  );
    log_printf( &logger, "\r\n---- GNSS Init done ---\r\n" );

    init_flag = 0;

    Delay_ms( 2000 );
}

void application_task ( void )
{
    gsmgps_process(  );
    
    if ( send_data_cnt == 3 )
    {
        gsmgps_send_command( &gsmgps, GSMGPS_CMD_CGNSSEQ );
        gsmgps_send_command( &gsmgps, GSMGPS_CMD_CGNSINF );
        gsmgps_process( );
        parser_application( current_parser_buf );
        send_data_cnt = 0;
    }
    send_data_cnt++;
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
