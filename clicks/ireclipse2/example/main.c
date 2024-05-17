/*!
 * @file main.c
 * @brief IR Eclipse 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of the IR Eclipse 2 Click board
 * by detecting eclipse states.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO module, log UART and enables the transmitter of the photo-microsensor.
 *
 * ## Application Task
 * When the beam from the transmitter is eclipsed by placing an object in
 * the gap ( like a piece of paper ), the counter is incremented by one 
 * when the sensor is triggered.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ireclipse2.h"

static ireclipse2_t ireclipse2;  /**< IR Eclipse 2 Click driver object. */
static log_t logger;             /**< Logger object. */
static uint8_t ecls_state = 0;
static uint8_t cmp_state = 0;
static uint16_t cnt = 0;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ireclipse2_cfg_t ireclipse2_cfg;  /**< Click config object. */

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
    ireclipse2_cfg_setup( &ireclipse2_cfg );
    IRECLIPSE2_MAP_MIKROBUS( ireclipse2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ireclipse2_init( &ireclipse2, &ireclipse2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ireclipse2_enable( &ireclipse2 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    ecls_state = ireclipse2_get_state( &ireclipse2 );
    if ( cmp_state != ecls_state )
    {
        if ( IRECLIPSE2_STATE_ECLIPSE == ecls_state )
        {
            log_printf( &logger, " Counter: %u\n", cnt );
            cnt++;
        }
        cmp_state = ecls_state;
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
