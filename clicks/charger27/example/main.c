/*!
 * @file main.c
 * @brief Charger 27 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Charger 27 Click board 
 * by enabling charge or discharge mode and 
 * indicating valid input supply and charging completion.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO module and log UART.
 * After driver initialization, the app sets charge mode.
 *
 * ## Application Task
 * The Charger 27 Click board operates as a switching charger to charge a 1S battery 
 * from a wide input power range of 5V to 16V, which can cover a USB PD voltage level.
 * The demo application checks and displays the charging completion indicator status.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "charger27.h"

static charger27_t charger27;   /**< Charger 27 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger27_cfg_t charger27_cfg;  /**< Click config object. */

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
    charger27_cfg_setup( &charger27_cfg );
    CHARGER27_MAP_MIKROBUS( charger27_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger27_init( &charger27, &charger27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( CHARGER27_OK == charger27_set_mode( &charger27, CHARGER27_MODE_CHARGE ) )
    {
        log_printf( &logger, " > Charge mode <\r\n" );
        Delay_ms ( 100 );
    }
}

void application_task ( void ) 
{
    if ( CHARGER27_CHG_CHARGE == charger27_check_chg_completion( &charger27 ) )
    {
        log_printf( &logger, " Charging.\r\n" );
        Delay_ms ( 1000 );
    }
    else
    {
        log_printf( &logger, " Charging has completed or is suspended.\r\n" );
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
