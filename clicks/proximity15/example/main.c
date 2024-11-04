/*!
 * @file main.c
 * @brief Proximity15 Click example
 *
 * # Description
 * This example demonstrates the use of Proximity 15 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which 
 * enables the sensor and sets it to long distance mode with 50ms timing budget and 100ms
 * inter measurement periods.
 *
 * ## Application Task
 * Reads the distance measured by the sensor in milimeters and displays the 
 * value on the USB UART approximately every 100ms.
 * 
 * @note 
 * In order to measure longer distance, increase the timing budget and inter measurement periods.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity15.h"

static proximity15_t proximity15;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    proximity15_cfg_t proximity15_cfg;  /**< Click config object. */

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
    proximity15_cfg_setup( &proximity15_cfg );
    PROXIMITY15_MAP_MIKROBUS( proximity15_cfg, MIKROBUS_1 );
    err_t init_flag = proximity15_init( &proximity15, &proximity15_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    init_flag = proximity15_default_cfg ( &proximity15 );
    if ( PROXIMITY15_ERROR == init_flag ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t distance = 0;
    
    if ( PROXIMITY15_OK == proximity15_get_distance ( &proximity15, &distance ) )
    {
        log_printf( &logger, " Distance(mm): %u\r\n\n", distance );
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
