/*!
 * @file main.c
 * @brief LR 2 Click Example.
 *
 * # Description
 * This example shows the usage of the LR 2 Click board by transmitting and receiving data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs default configuration and reads System version.
 *
 * ## Application Task
 * Transmitter mode - sends a desired message each second and checks if it is sent successfully.
 * Receiver mode - displays all the received characters on USB UART.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "lr2.h"
#include "conversions.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

#define PROCESS_COUNTER 5
#define PROCESS_RX_BUFFER_SIZE 300

// ------------------------------------------------------------------ VARIABLES

static lr2_t lr2;
static log_t logger;

uint8_t resp_buf[ 50 ];
uint8_t send_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

/**
 * @brief LR 2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @return Nothing.
 * @note None.
 */
static void lr2_process ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr2_cfg_t lr2_cfg;  /**< Click config object. */

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
    lr2_cfg_setup( &lr2_cfg );
    LR2_MAP_MIKROBUS( lr2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr2_init( &lr2, &lr2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    lr2_default_cfg( &lr2, 0, 0 );
    lr2_process( );

    lr2_cmd( &lr2, LR2_CMD_SYS_GET_VER, resp_buf );
    log_printf( &logger, " System VER: %s \r\n", resp_buf );
    
    lr2_cmd( &lr2, LR2_CMD_MAC_PAUSE, resp_buf );
    log_printf( &logger, " MAC PAUSE: %s \r\n", resp_buf );

    lr2_cmd( &lr2, LR2_CMD_RADIO_SET_WDT, resp_buf );
    log_printf( &logger, " RADIO SET WDT 0: %s \r\n", resp_buf );
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    lr2_process( );
    
#ifdef DEMO_APP_TRANSMITTER
    uint8_t hex_buf[ 50 ] = { 0 };
    uint8_t cnt = 0;
    for ( cnt = 0; cnt < strlen( send_message ); cnt++ ) 
    {
        uint8_to_hex( send_message[ cnt ], &hex_buf[ cnt * 2 ] );
    }
    if ( LR2_OK == lr2_tx( &lr2, hex_buf ) ) 
    {
        log_printf( &logger, " Sent message: %s", send_message );
        log_printf( &logger, " Response : %s\r\n", resp_buf );
    }
    Delay_ms ( 1000 );
#else
    if ( LR2_OK == lr2_rx( &lr2, LR2_ARG_0, resp_buf ) ) 
    {
        uint8_t text_buf[ 20 ] = { 0 };
        uint8_t hex_buf[ 3 ] = { 0 };
        uint8_t cnt = 0;
        for ( cnt = 0; cnt < ( strlen( resp_buf ) - 10 ); cnt += 2 )
        {
            hex_buf[ 0 ] = resp_buf[ 10 + cnt ];
            hex_buf[ 1 ] = resp_buf[ 11 + cnt ];
            text_buf[ cnt / 2 ] = hex_to_uint8( hex_buf );
        }
        log_printf( &logger, "Received message: %s\r\n", text_buf );
    }
#endif
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

static void lr2_process ( void ) 
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while ( process_cnt != 0 ) 
    {
        rsp_size = lr2_generic_read( &lr2, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 ) 
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ ) 
            {
                lr2_put_char( &lr2, uart_rx_buffer[ check_buf_cnt ] );
                lr2_isr_process( &lr2 );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms ( 100 );
        }
    }
}

// ------------------------------------------------------------------------ END
