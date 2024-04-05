/*!
 * @file main.c
 * @brief LIN Hall 2 Click Example.
 *
 * # Description
 * This is an example which demonstrates the use of LIN Hall 2 Click board by measuring 
 * magnetic field density and showing it in mT as well as detecting the orientation of the magnet.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of ADC module and log UART.
 *
 * ## Application Task
 * The demo application reads the Magnetic field density and showing it in mT 
 * as well as the orientation of the magnet.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "linhall2.h"

static linhall2_t linhall2;   /**< LIN Hall 2 Click driver object. */
static log_t logger;          /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    linhall2_cfg_t linhall2_cfg;  /**< Click config object. */

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
    linhall2_cfg_setup( &linhall2_cfg );
    LINHALL2_MAP_MIKROBUS( linhall2_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == linhall2_init( &linhall2, &linhall2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    linhal2_set_en_pin( &linhall2, LINHALL2_ENABLE_DEVICE );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float mag_flux = 0;
    if ( LINHALL2_OK == linhal2_get_flux_density ( &linhall2, &mag_flux ) ) 
    {
        log_printf( &logger, " Magnetic flux density: %.3f[mT]\r\n", mag_flux );
        if ( 0 < mag_flux )
        {
            log_printf( &logger, " Magnetic field oriented South \r\n\n" );
        }
        else
        {
            log_printf( &logger, " Magnetic field oriented North \r\n\n" );
        }
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
