/*!
 * @file main.c
 * @brief Brushless 16 Click Example.
 *
 * # Description
 * This example showcases ability to enable and disable motor output,
 * and check the status pins.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializon of UART module for log and pins for motor control.
 *
 * ## Application Task
 * Checks state of information pins every ms, and stop and start motor
 * output every second.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless16.h"

static brushless16_t brushless16;   /**< Brushless 16 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless16_cfg_t brushless16_cfg;  /**< Click config object. */

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
    brushless16_cfg_setup( &brushless16_cfg );
    BRUSHLESS16_MAP_MIKROBUS( brushless16_cfg, MIKROBUS_1 );
    if ( brushless16_init( &brushless16, &brushless16_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 500 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint16_t timer = 5000;
    static uint8_t state = 1;
    
    if ( brushless16_get_rd( &brushless16 ) )
    {
        log_info( &logger, " Motor Lock" );
        Delay_ms( 500 );
    }
    
    if ( brushless16_get_fg( &brushless16 ) )
    {
        log_info( &logger, " FG" );
        Delay_ms( 500 );
    }
    
    if ( !( timer-- ) )
    {
        timer = 5000;
        
        if ( state )
        {
            log_info( &logger, " Motor stop" );
        }
        else
        {
            log_info( &logger, " Motor rotating" );
        }
        
        brushless16_set_en( &brushless16, state );
        state = !state;
    }
    
    Delay_ms( 1 );
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
