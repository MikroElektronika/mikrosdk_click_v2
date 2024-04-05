/*!
 * @file main.c
 * @brief LR Click Example.
 *
 * # Description
 * This example shows the usage of the LR Click board by transmitting and receiving data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs default configuration and reads System version.
 *
 * ## Application Task
 * Transmitter mode - sends one-by-one byte sequence of the desired message each second and 
 * checks if it is sent successfully
 * Receiver mode - displays all the received characters on USB UART.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "lr.h"
#include "conversions.h"

#define PROCESS_COUNTER 5
#define PROCESS_RX_BUFFER_SIZE 300

// ------------------------------------------------------------------ VARIABLES

// #define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITTER

static lr_t lr;
static log_t logger;

char send_hex[ 50 ];
char resp_buf[ 50 ];
uint8_t send_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

/**
 * @brief LR data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @return Nothing.
 * @note None.
 */
static void lr_process ( void );

/**
 * @brief LR data is digit check function.
 * @details This function checks if data is a digit.
 * @param[in] c : Data to be checked.
 * @return @li @c 0 - Data isn't digit,
 *         @li @c 1 - Data is digit.
 * @note None.
 */
static bool is_digit ( char c );

/**
 * @brief LR hex data to int function.
 * @details This function is used to convert hex data into an int.
 * @param[in] origin : Hex data.
 * @param[out] result : Int data.
 * @return Nothing.
 * @note None.
 */
static void hex_to_int ( char *origin, uint8_t *result );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr_cfg_t lr_cfg;  /**< Click config object. */

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
    lr_cfg_setup( &lr_cfg );
    LR_MAP_MIKROBUS( lr_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr_init( &lr, &lr_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    lr_default_cfg( &lr, 0, 0 );

    lr_cmd( &lr, LR_CMD_SYS_GET_VER, resp_buf );
    log_printf( &logger, "System VER: %s \r\n", resp_buf );
    
    lr_cmd( &lr, LR_CMD_MAC_PAUSE, resp_buf );
    log_printf( &logger, "MAC PAUSE: %s \r\n", resp_buf );

    lr_cmd( &lr, LR_CMD_RADIO_SET_WDT, resp_buf );
    log_printf( &logger, "RADIO SET WDT 0: %s \r\n", resp_buf );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    lr_process( );
    
#ifdef DEMO_APP_RECEIVER
    char *ptr;
    uint8_t int_data;
    if ( LR_OK == lr_rx( &lr, LR_ARG_0, resp_buf ) ) 
    {
        resp_buf[ 12 ] = 0;
        ptr = ( char* ) &int_data;
        hex_to_int( &resp_buf[ 10 ], ptr );
        log_printf( &logger, "%c", int_data  );
    }
#endif
#ifdef DEMO_APP_TRANSMITTER
    for ( uint8_t cnt = 0; cnt < 9; cnt++ ) 
    {
        int8_to_hex( send_message[ cnt ], send_hex );
        if ( LR_OK == lr_tx( &lr, &send_hex[ 0 ] ) ) 
        {
            log_printf( &logger, " Response : %s \r\n", resp_buf );
        }
        Delay_ms ( 1000 );
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

static void lr_process ( void ) 
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while ( process_cnt != 0 ) 
    {
        rsp_size = lr_generic_read( &lr, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 ) 
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ ) 
            {
                lr_put_char( &lr, uart_rx_buffer[ check_buf_cnt ] );
                lr_isr_process( &lr );
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

static bool is_digit ( char c ) 
{
    if ( c >= '0' && c <= '9' ) 
    {
        return true;
    }

    return false;
}

static void hex_to_int ( char* origin, uint8_t* result ) 
{
    uint8_t len = strlen( origin );
    uint8_t idx, ptr, factor;

    if ( len > 0 ) 
    {
        *result = 0;
        factor = 1;

        for ( idx = len - 1; idx >= 0; idx-- ) 
        {
            if ( is_digit( *( origin + idx ) ) ) 
            {
                *result += ( *( origin + idx ) - '0' ) * factor;
               } else {
                    if ( *( origin + idx ) >= 'A' && *( origin + idx ) <= 'Z' ) 
                    {
                        
                        ptr = ( *( origin + idx ) - 'A' ) + 10;
                        
                    } 
                    else 
                    {
                        return;
                    }
                    *result += ( ptr * factor );
                }
                factor *= 16;
        }
    }
}

// ------------------------------------------------------------------------ END
