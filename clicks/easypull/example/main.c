/*!
 * @file main.c
 * @brief EasyPull Click Example.
 *
 * # Description
 * This example demonstrates the use of EasyPull Click boards.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and USB UART logger.
 *
 * ## Application Task
 * It checks the state of the pins and displays their state on the USB UART.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "easypull.h"

static easypull_t easypull;   /**< EasyPull Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    easypull_cfg_t easypull_cfg;  /**< Click config object. */

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
    easypull_cfg_setup( &easypull_cfg );
    EASYPULL_MAP_MIKROBUS( easypull_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == easypull_init( &easypull, &easypull_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_an_pin( &easypull ) )
    {
        log_printf( &logger, " AN pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " AN pin state: LOW \n" );
    }

    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_rst_pin( &easypull ) )
    {
        log_printf( &logger, " RST pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " RST pin state: LOW \n" );
    }

    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_cs_pin( &easypull ) )
    {
        log_printf( &logger, " CS pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " CS pin state: LOW \n" );
    }

    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_pwm_pin( &easypull ) )
    {
        log_printf( &logger, " PWM pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " PWM pin state: LOW \n" );
    }

    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_int_pin( &easypull ) )
    {
        log_printf( &logger, " INT pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " INT pin state: LOW \n" );
    }
    log_printf( &logger, "- - - - - - - - - - - - - \r\n" );
    Delay_ms ( 1000 );

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
