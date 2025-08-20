/*!
 * @file main.c
 * @brief Counter 2 Click example
 *
 * # Description
 * This example demonstrates the use of the Counter 2 Click board. The application reads the current
 * pulse count from the board and handles rollover events using the loop counter mechanism. It logs
 * the total number of detected pulses, including those beyond the register's capacity.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click board driver and resets the internal pulse counter.
 *
 * ## Application Task
 * Periodically reads the counter value and checks for rollover (loop) events.
 * Logs the total pulse count every second.
 *
 * @note
 * Ensure that the input signal to the counting channel is within electrical and timing specifications 
 * to avoid missed or incorrect counts.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "counter2.h"

static counter2_t counter2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    counter2_cfg_t counter2_cfg;  /**< Click config object. */

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
    counter2_cfg_setup( &counter2_cfg );
    COUNTER2_MAP_MIKROBUS( counter2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == counter2_init( &counter2, &counter2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    counter2_reset_counter ( &counter2 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t loop_cnt = 0;
    uint32_t counter = 0;
    if ( COUNTER2_OK == counter2_get_counter ( &counter2, &counter ) )
    {
        loop_cnt += counter2_check_loop ( &counter2 );
        log_printf ( &logger, " Counter: %lu\r\n\n", 
                     ( uint32_t ) loop_cnt * COUNTER2_LOOP_THRESHOLD + counter );
        Delay_ms ( 1000 );
    }
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
