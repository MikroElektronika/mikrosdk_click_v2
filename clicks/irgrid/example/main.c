/*!
 * @file main.c
 * @brief IRGrid Click example
 *
 * # Description
 * IR Grid click is a thermal imaging sensor. It has an array of 64 very sensitive factory 
 * calibrated IR elements (pixels), arranged in 4 rows of 16 pixels, each measuring an 
 * object temperature up to 300˚C.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and IR Grid module
 * 
 * ## Application Task  
 * Reads the temperature of all pixels and creates a pixel temperature matrix that logs 
 * on usbuart every half of second
 *
 * @author Mikroe Team
 *
 */

#include "board.h"
#include "log.h"
#include "irgrid.h"

static irgrid_t irgrid;
static irgrid_data_t irgrid_data;
static log_t logger;

static float   ir_tmp[ 64 ];
static uint8_t i;
static uint8_t rc;
static uint8_t cc;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgrid_cfg_t irgrid_cfg;  /**< Click config object. */

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
    irgrid_cfg_setup( &irgrid_cfg );
    IRGRID_MAP_MIKROBUS( irgrid_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irgrid_init( &irgrid, &irgrid_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    irgrid_device_init( &irgrid, &irgrid_data, 16 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{    
    if ( 1 != irgrid_measure( &irgrid, &irgrid_data ) )
    {
        irgrid_get_temperature( &irgrid_data, &ir_tmp[ 0 ] );
    }

    for ( rc = 0; rc < 4; rc++ )
    {
        for ( cc = 0; cc < 16; cc++ )
        {
            i = ( cc * 4 ) + rc;
            log_printf( &logger, "%.3f    ", ir_tmp[ i ] );
        }
        log_printf( &logger, "\r\n" );
        Delay_ms ( 100 );
    }
    
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "\r\n" );
    Delay_ms ( 500 );
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
