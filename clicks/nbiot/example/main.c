/*!
 * \file 
 * \brief NbIot Click example
 * 
 * # Description
 * This example reads and processes data from NB IoT clicks.
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
 * - nbiot_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "nbiot.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static nbiot_t nbiot;
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

static void nbiot_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = nbiot_generic_read( &nbiot, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    nbiot_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    nbiot_cfg_setup( &cfg );
    NBIOT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nbiot_init( &nbiot, &cfg );

    nbiot_module_power( &nbiot );
    
    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_AT );
    nbiot_process(  );

    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_ATE1 );
    nbiot_process(  );

    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_ATI );
    nbiot_process(  );

    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_SET_AT_CFUN );
    nbiot_process(  );

    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_AT_CIMI );
    nbiot_process(  );

    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_TEST_ATAT_CGDCONT );
    nbiot_process(  );

    nbiot_send_command( &nbiot, C5GNBIOT_SINGLE_CMD_GET_AT_CGATT );
    nbiot_process(  );

    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "--- UDP server - AT command ---\r\n" );

    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NCONFIG );
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NCONFIG1 );
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NCONFIG2 );
    nbiot_process(  );


    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NBAND );
    nbiot_process(  );

    nbiot_send_command( &nbiot, C5GNBIOT_SINGLE_CMD_SET_AT_CGDCONT_1 );
    nbiot_process(  );


    
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_CEREG );
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_COPS ); 
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NSOCR ); 
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NSOST );
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_CMD_AT_NSOCL );
    nbiot_process(  );

    Delay_ms( 2000 );
}

void application_task ( void )
{
    nbiot_process(  );
    nbiot_send_command( &nbiot, NBIOT_SINGLE_CMD_AT_CIMI );
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
