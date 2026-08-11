/*!
 * @file main.c
 * @brief BI Hall 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of the BI Hall 2 Click board for
 * magnetic field detection. The application reads the sensor output and
 * converts it to magnetic field strength expressed in Gauss units.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and BI Hall 2 Click driver.
 *
 * ## Application Task
 * Reads the magnetic field measurement and logs the calculated magnetic
 * field strength in Gauss.
 *
 * @note
 * Bring a magnet close to the sensor to observe positive and negative
 * magnetic field changes.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "bihall2.h"

#ifndef MIKROBUS_POSITION_BIHALL2
    #define MIKROBUS_POSITION_BIHALL2 MIKROBUS_1
#endif

static bihall2_t bihall2;   /**< BI Hall 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bihall2_cfg_t bihall2_cfg;  /**< Click config object. */

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
    bihall2_cfg_setup( &bihall2_cfg );
    BIHALL2_MAP_MIKROBUS( bihall2_cfg, MIKROBUS_POSITION_BIHALL2 );
    if ( ADC_ERROR == bihall2_init( &bihall2, &bihall2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float mag_field = 0;
    if ( BIHALL2_OK == bihall2_get_output ( &bihall2, &mag_field ) ) 
    {
        log_printf( &logger, " Magnetic field : %.2f Gauss\r\n\n", mag_field );
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
