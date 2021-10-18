/*!
 * \file 
 * \brief G2c3G Click example
 * 
 * # Description
 * This example reads and processes data from G2C 3G clicks.
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
 * - g2c3g_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * \author Katarina Perendic
 * 
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "g2c3g.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

static g2c3g_t g2c3g;
static log_t   logger;

#define G2C3G_AT          "AT"
#define G2C3G_ATE         "ATE0"
#define G2C3G_AT_GMR      "AT+GMR"
#define G2C3G_AT_CEN      "AT+CEN=1"
#define G2C3G_AT_NWC      "AT+NWC=1"
#define G2C3G_AT_BRC      "AT+BRC=1"
#define G2C3G_AT_PUB      "AT+PUB"

// Sensor/Actuator reference
#define ACTUATOR_SW_REF   "G2C3G_TEST_AB"
#define ACTUATOR_STR_REF  "G2C3G_TEST_AS"
#define ACTUATOR_CNT_REF  "G2C3G_TEST_AC"
#define SENSOR_REF        "G2C3G_TEST_S"

// Operator settings
#define OPERATOR_APN      "vipmobile"
#define OPERATOR_USERNAME "vipmobile"
#define OPERATOR_PASSWORD "vipmobile"

// Broker(device) settings
#define DEVICE_KEY        "bc8mtmm1ztqjol75"
#define DEVICE_PASSWORD   "65c64823-78e9-4f78-b154-ac0c6632d466"

static char data_buf[ 20 ] = "12.2";
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

void g2c3g_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt = 4;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    rsp_cnt = 0;
    
    while( process_cnt != 0 )
    {
        rsp_size = g2c3g_generic_read( &g2c3g, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 )
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

static void actuator_demo( char *rsp )
{
    uint8_t sw_state;
    int16_t cnt_state;
    char str_data_buf[ 50 ];

    uint8_t err = G2C3G_PARSER_NO_ERROR;
    
    // Actuator switch example
    err = g2c3g_actuator_sw_parser( rsp, ACTUATOR_SW_REF, &sw_state );
    if ( err == G2C3G_PARSER_NO_ERROR )
    {
        log_printf( &logger, ">> ACTUATOR SW STATE: %d\r\n", sw_state );
    }

    // Actuator counter example
    err = g2c3g_actuator_cnt_parser( rsp, ACTUATOR_CNT_REF, &cnt_state );
    if ( err == G2C3G_PARSER_NO_ERROR )
    {
        log_printf( &logger, ">> ACTUATOR CNT NUM: %d\r\n", cnt_state );
    }

    // Actuator string example
    err = g2c3g_actuator_str_parser( rsp, ACTUATOR_STR_REF, &str_data_buf[ 0 ] );
    if ( err == G2C3G_PARSER_NO_ERROR )
    {
        log_printf( &logger, ">> ACTUATOR TEXT DATA: %s\r\n", str_data_buf );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    g2c3g_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    g2c3g_cfg_setup( &cfg );
    
    G2C3G_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    g2c3g_init( &g2c3g, &cfg );
    
    //g2c3g_module_reset( &g2c3g );
    g2c3g_process( );
    while ( ( g2c3g_led_net( &g2c3g ) != 0 ) || ( g2c3g_led_conn( &g2c3g ) != 0 ) );
    g2c3g_process( );
    
    
    g2c3g_send_command( &g2c3g, G2C3G_AT );
    g2c3g_process( );
    
    g2c3g_send_command( &g2c3g, G2C3G_AT_GMR );
    g2c3g_process( );

    g2c3g_send_command( &g2c3g, G2C3G_AT_CEN );
    g2c3g_process( );
    
    g2c3g_send_operator_cfg( &g2c3g, OPERATOR_APN, OPERATOR_USERNAME, OPERATOR_PASSWORD );
    
    g2c3g_process( );
    g2c3g_send_command( &g2c3g, G2C3G_AT_NWC );
    g2c3g_process( );
    
    while ( g2c3g_led_net( &g2c3g  ) != 1 );
    
    g2c3g_send_broker_cfg( &g2c3g, DEVICE_KEY, DEVICE_PASSWORD );
    g2c3g_process( );

    g2c3g_send_command( &g2c3g, G2C3G_AT_BRC );
    g2c3g_process( );

    while ( g2c3g_led_conn( &g2c3g ) != 1 );
    Delay_ms( 2000 );
}

void application_task ( void )
{
    g2c3g_process( );
    actuator_demo( current_parser_buf );
    
    if ( send_data_cnt == 5 )
    {
       g2c3g_send_data_ref( &g2c3g, SENSOR_REF, &data_buf[ 0 ] );
       g2c3g_process( );
       g2c3g_send_command( &g2c3g, G2C3G_AT_PUB );
       g2c3g_process( );
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
