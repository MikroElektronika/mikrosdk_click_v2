/*!
 * @file main.c
 * @brief Water Detect 2 Click Example.
 *
 * # Description
 * This library contains API for Water Detect 2 Click driver.
 * Water Detect 2 click is used for detecting water and other electroconductive liquids. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and performs the default configuration.
 *
 * ## Application Task
 * Reads fluid presence status and determines if there is fluid presence or not.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "waterdetect2.h"

static waterdetect2_t waterdetect2;   /**< Water Detect 2 Click driver object. */
static log_t logger;                  /**< Logger object. */
static uint8_t fluid_status_old = 2;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    waterdetect2_cfg_t waterdetect2_cfg;  /**< Click config object. */

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
    waterdetect2_cfg_setup( &waterdetect2_cfg );
    WATERDETECT2_MAP_MIKROBUS( waterdetect2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == waterdetect2_init( &waterdetect2, &waterdetect2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    waterdetect2_default_cfg( &waterdetect2 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t fluid_status = waterdetect2_get_fluid_status( &waterdetect2 );
    if ( fluid_status != fluid_status_old )
    {
        if ( WATERDETECT2_FLUID_DETECTED == fluid_status )
        {
            log_printf( &logger, " Fluid present! \r\n" );
        }
        else
        {
            log_printf( &logger, " No fluid present. \r\n" );
        }
        log_printf( &logger, "------------------- \r\n" );
        fluid_status_old = fluid_status;
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
