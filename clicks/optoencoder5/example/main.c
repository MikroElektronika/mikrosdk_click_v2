/*!
 * @file main.c
 * @brief Opto Encoder 5 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Opto Encoder 5 Click board
 * by detecting eclipse states.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO module, log UART and enables the slotted optical switch.
 *
 * ## Application Task
 * When the beam from the slotted optical switch is broken by placing an object in
 * the gap ( like a piece of paper ), the counter is incremented by one 
 * when the sensor is triggered.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "optoencoder5.h"

static optoencoder5_t optoencoder5;     /**< Opto Encoder 5 Click driver object. */
static log_t logger;                    /**< Logger object. */
static uint8_t out_state = 0;
static uint8_t cmp_state = 0;
static uint16_t cnt = 0;

void application_init ( void ) 
{
    log_cfg_t log_cfg;                      /**< Logger config object. */
    optoencoder5_cfg_t optoencoder5_cfg;    /**< Click config object. */

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
    optoencoder5_cfg_setup( &optoencoder5_cfg );
    OPTOENCODER5_MAP_MIKROBUS( optoencoder5_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == optoencoder5_init( &optoencoder5, &optoencoder5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    optoencoder5_enable( &optoencoder5 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    out_state = optoencoder5_get_out_state( &optoencoder5 );
    if ( cmp_state != out_state )
    {
        if ( OPTOENCODER5_OUT_STATE_SWITCH_CLOSED == out_state )
        {
            log_printf( &logger, " Counter: %u \r\n", cnt );
            cnt++;
        }
        cmp_state = out_state;
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
