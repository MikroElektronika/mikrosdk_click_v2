/*!
 * @file main.c
 * @brief Force Cell Click Example.
 *
 * # Description
 * This example demonstrates the use of the Force Cell Click board by reading the applied force
 * in newtons (N) from a load cell sensor. The application initializes the driver, calibrates the
 * offset, and continuously measures and logs the force value to the USB UART terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click driver, performs offset calibration to null the load cell.
 *
 * ## Application Task
 * Continuously reads and displays the current force value in newtons every 100ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "forcecell.h"

static forcecell_t forcecell;   /**< Force Cell Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    forcecell_cfg_t forcecell_cfg;  /**< Click config object. */

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
    forcecell_cfg_setup( &forcecell_cfg );
    FORCECELL_MAP_MIKROBUS( forcecell_cfg, MIKROBUS_1 );
    err_t init_flag = forcecell_init( &forcecell, &forcecell_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( FORCECELL_ERROR == forcecell_calib_offset ( &forcecell ) )
    {
        log_error( &logger, " Offset calibration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float force = 0;
    if ( FORCECELL_OK == forcecell_read_force ( &forcecell, &force ) ) 
    {
        log_printf( &logger, " Force : %.3f N\r\n\n", force );
        Delay_ms ( 100 );
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
