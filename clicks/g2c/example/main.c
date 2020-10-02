/*!
 * \file 
 * \brief G2C Click example
 * 
 * # Description
 * This example reads and processes data from G2C clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and power module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - g2c_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "g2c.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

static g2c_t g2c;
static log_t logger;

// AT commands
#define ATE               "ATE1"
#define AT                "AT"
#define AT_CEN            "AT+CEN=1"
#define AT_NWCR           "AT+NWCR"
#define AT_NWC            "AT+NWC=1"
#define AT_BRCR           "AT+BRCR"
#define AT_BRC            "AT+BRC=1"
#define AT_DSET           "AT+DSET"
#define AT_PUB            "AT+PUB"

// Sensor/Actuator reference
#define ACTUATOR_SW_REF   "G2C_TEST_AB"
#define ACTUATOR_STR_REF  "G2C_TEST_AS"
#define ACTUATOR_CNT_REF  "G2C_TEST_AC"
#define SENSOR_REF        "G2C_TEST_S"

// Operator settings
#define NETWORK_USERNAME  "network_username"
#define NETWORK_PASSWORD  "network_password"

// Broker(device) settings
#define DEVICE_KEY        "device_key"
#define DEVICE_PASSWORD   "device_password"

static char data_buf[ 20 ] = "12.2";
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void g2c_process ( void )
{
    uint16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = g2c_generic_read( &g2c, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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

static void actuator_demo( char *rsp )
{
    uint8_t sw_state;
    int16_t cnt_state;
    char str_data_buf[ 50 ];
    
    uint8_t err = G2C_PARSER_NO_ERROR;
    
    // Actuator switch example
    err = g2c_actuator_sw_parser( rsp, ACTUATOR_SW_REF, &sw_state );
    if ( err == G2C_PARSER_NO_ERROR )
    {
        log_printf( &logger, ">> ACTUATOR SW STATE: %d\r\n", sw_state );
    }

    // Actuator counter example
    err = g2c_actuator_cnt_parser(  rsp, ACTUATOR_CNT_REF, &cnt_state );
    if ( err == G2C_PARSER_NO_ERROR )
    {
        log_printf( &logger, ">> ACTUATOR CNT NUM: %d\r\n", cnt_state );
    }
    
    // Actuator string example
    err = g2c_actuator_str_parser(  rsp, ACTUATOR_STR_REF, str_data_buf );
    if ( err == G2C_PARSER_NO_ERROR )
    {
        log_printf( &logger, ">> ACTUATOR TEXT DATA: %s\r\n", str_data_buf );
    }
}
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    g2c_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    g2c_cfg_setup( &cfg );
    G2C_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    g2c_init( &g2c, &cfg );

    // Power module.

    g2c_module_power( &g2c, true, 0 );
    g2c_reset( &g2c );
    
    // Send command.

    log_printf( &logger, ">> ATE \r\n" );
    g2c_send_command( &g2c, ATE );
    Delay_ms( 3000 );
    g2c_process( );

    log_printf( &logger, ">> AT \r\n" );
    g2c_send_command( &g2c, AT );
    Delay_ms( 3000 );
    g2c_process( );

    log_printf( &logger, ">> AT_CEN \r\n" );
    g2c_send_command( &g2c, AT_CEN );
    g2c_process( );

    log_printf( &logger, ">> NETWORK \r\n" );
    g2c_send_operator_cfg( &g2c, NETWORK_USERNAME, NETWORK_PASSWORD );
    g2c_process( );

    log_printf( &logger, ">> AT NWC \r\n" );
    g2c_send_command( &g2c, AT_NWC );
    g2c_process( );

    log_printf( &logger, ">> DEVICE \r\n" );
    g2c_send_broker_cfg( &g2c, DEVICE_KEY, DEVICE_PASSWORD );
    g2c_process( );

    log_printf( &logger, ">> AT BRC \r\n" );
    g2c_send_command( &g2c, AT_BRC ); 
    g2c_process( );

    Delay_ms( 3000 );
}

void application_task ( void )
{
    g2c_process( );
    actuator_demo( current_parser_buf );
    
    if ( send_data_cnt == 5 )
    {
       log_printf( &logger, ">> ACTUATOR REF \r\n" );  
       g2c_send_data_ref( &g2c, ACTUATOR_STR_REF, data_buf );
       g2c_process( );

       log_printf( &logger, ">> AT PUB \r\n" );
       g2c_send_command( &g2c, AT_PUB );
       g2c_process( );
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
