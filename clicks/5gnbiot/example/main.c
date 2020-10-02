/*!
 * \file 
 * \brief 5gNbIot Click example
 * 
 * # Description
 * This example reads and processes data from 5G NB IoT clicks.
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
 * - c5gnbiot_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c5gnbiot.h"
#include "string.h"

#define PROCESS_CNT 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static c5gnbiot_t c5gnbiot;
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

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void c5gnbiot_process ( uint8_t process_counter )
{
    uint16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_CNT;
    
    while( process_cnt != 0 )
    {
        rsp_size = c5gnbiot_generic_read( &c5gnbiot, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != 0 )
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

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c5gnbiot_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c5gnbiot_cfg_setup( &cfg );
    C5GNBIOT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c5gnbiot_init( &c5gnbiot, &cfg );

    c5gnbiot_module_power( &c5gnbiot );
    Delay_ms( 2000 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_AT );
    c5gnbiot_process( 20 );
    Delay_ms( 2000 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_ATI );
    c5gnbiot_process( 20 );
    Delay_ms( 2000 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_SET_AT_CFUN_1 );
    c5gnbiot_process( 20 );
    Delay_ms( 2000 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_SET_AT_CEREG_2 );
    c5gnbiot_process( 20 );
    Delay_ms( 2000 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_SET_AT_CGDCONT_1 );
    c5gnbiot_process( 20 );
    Delay_ms( 2000 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_AT_CIMI );
    c5gnbiot_process( 20 );
    Delay_ms( 2000 );

}

void application_task ( void )
{
    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_GET_AT_CGATT );
    c5gnbiot_process( 50 );

    c5gnbiot_send_command( &c5gnbiot, C5GNBIOT_SINGLE_CMD_GET_AT_CEREG );
    c5gnbiot_process( 50 );
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
