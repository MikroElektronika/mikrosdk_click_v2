/*!
 * @file main.c
 * @brief Motion 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of Motion 3 Click boards.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the motion sensor.
 *
 * ## Application Task
 * It checks if the sensor has detected movement and therefore displays 
 * the desired message on the USB UART.
 *
 * @author Jelena Milosavljevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "motion3.h"

// ------------------------------------------------------------------ VARIABLES

static motion3_t motion3;   /**< Motion 3 Click driver object. */
static log_t logger;    /**< Logger object. */

motion3_detect_state_t motion_state;
motion3_detect_state_t motion_old_state;
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    motion3_cfg_t motion3_cfg;  /**< Click config object. */

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

    motion3_cfg_setup( &motion3_cfg );
    MOTION3_MAP_MIKROBUS( motion3_cfg, MIKROBUS_5 );
    if ( motion3_init( &motion3, &motion3_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
       
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    motion3_enable( &motion3, MOTION3_MODULE_ENABLE );
    Delay_ms ( 100 );
    log_printf( &logger, "The sensor is ready.\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( void ) {
    uint8_t int_status;

    int_status = motion3_detect_state( &motion3 );

    if ( int_status == MOTION3_DETECT_OBJECT )
    {
        log_printf( &logger, "Motion detected!\r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        while ( int_status == MOTION3_DETECT_OBJECT ) {
           
            int_status = motion3_detect_state( &motion3 );
        }
        log_printf( &logger, "The sensor is ready.\r\n" );
        log_printf( &logger, "-----------------------\r\n" );
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
