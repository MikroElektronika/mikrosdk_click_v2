/*!
 * \file 
 * \brief ProxFusion2 Click example
 * 
 * # Description
 * This example demontrates the use of ProxFusion 2 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and performs the click default configuration.
 * 
 * ## Application Task  
 * - Checks whether Touch is detected and measures the output detection.
 * - Measures Ambient lighting - whether it's Light or Dark, ALS range and ALS output.
 * - Checks the orientation of the magnet and measures the HALL output.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proxfusion2.h"

// ------------------------------------------------------------------ VARIABLES

static proxfusion2_t proxfusion2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proxfusion2_cfg_t proxfusion2_cfg;  /**< Click config object. */

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
    proxfusion2_cfg_setup( &proxfusion2_cfg );
    PROXFUSION2_MAP_MIKROBUS( proxfusion2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proxfusion2_init( &proxfusion2, &proxfusion2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXFUSION2_ERROR == proxfusion2_default_cfg ( &proxfusion2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t als_range = 0;
    uint8_t hall_detect = 0;
    uint16_t read_data = 0;
    if ( PROXFUSION2_TOUCH_DETECTED == proxfusion2_detect_touch( &proxfusion2 ) )
    {
        log_printf( &logger, " TOUCH: YES\r\n" );
    }
    else
    {
        log_printf( &logger, " TOUCH: NO\r\n" );
    }
    read_data = proxfusion2_read_data( &proxfusion2 , PROXFUSION2_HYSTERESIS_UI_OUTPUT );
    log_printf( &logger, " LEVEL: %u\r\n\n", read_data );
 
    if ( PROXFUSION2_AMBIENT_DARK == proxfusion2_detect_dark_light( &proxfusion2, &als_range ) )
    {
        log_printf( &logger, " AMBIENT: DARK\r\n" );
    }
    else
    {
        log_printf( &logger, " AMBIENT: LIGHT\r\n" );
    }
    log_printf( &logger, " RANGE: %u\r\n", ( uint16_t ) als_range );
 
    read_data = proxfusion2_read_data( &proxfusion2, PROXFUSION2_ALS_UI_OUTPUT );

    log_printf( &logger, " LEVEL: %u\r\n\n", read_data );
 
    hall_detect = proxfusion2_detect_hall( &proxfusion2 );
    if ( PROXFUSION2_HALL_NORTH == hall_detect )
    {
        log_printf( &logger, " HALL: NORTH\r\n" );
    }
    else if ( PROXFUSION2_HALL_SOUTH == hall_detect )
    {
        log_printf( &logger, " HALL: SOUTH\r\n" );
    }
    else
    {
        log_printf( &logger, " HALL: UNKNOWN\r\n" );
    }
    read_data = proxfusion2_read_data( &proxfusion2, PROXFUSION2_HALL_EFFECT_UI_OUTPUT );
    log_printf( &logger, " LEVEL: %u\r\n", read_data );
    
    log_printf( &logger, " --------------\r\n" );
    Delay_ms( 1000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
