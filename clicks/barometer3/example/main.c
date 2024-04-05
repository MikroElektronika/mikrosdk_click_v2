/*!
 * \file 
 * \brief Barometer3 Click example
 * 
 * # Description
 * This example demonstrates the use of Barometer 3 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, sets the click board default configuration and check the 
 * communication by reading the device ID.
 * 
 * ## Application Task  
 * Reads the temperature [ Celsius ] and pressure [ mBar ] and displays the results on
 * the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "barometer3.h"

// ------------------------------------------------------------------ VARIABLES

static barometer3_t barometer3;
static log_t logger;

float pressure;
float temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    barometer3_cfg_t cfg;
    uint8_t status_val;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    barometer3_cfg_setup( &cfg );
    BAROMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barometer3_init( &barometer3, &cfg );

    barometer3_def_cfg( &barometer3 );
    Delay_ms ( 100 );
    
    barometer3_generic_read( &barometer3, BAROMETER3_PROD_ID, &status_val, 1 );
    
    if ( status_val != BAROMETER3_PRODUCT_ID )
    {
        
        log_printf( &logger, " ERROR - wrong ID\r\n" );
        log_printf( &logger, " Please restart your system.\r\n" );
        for ( ; ; );
    }
    log_info( &logger, "---- Application Task ----" );
}

void application_task ( void )
{
    barometer3_cfg_temp( &barometer3, BAROMETER3_TMP_RATE_1, BAROMETER3_TMP_PRC_128 );
    barometer3_standby( &barometer3 );
    while ( BAROMETER3_SUCCESS != barometer3_meas_temp_once( &barometer3, &temperature, BAROMETER3_TMP_PRC_128 ) );
    log_printf( &logger, " Temperature: %.2f Celsius \r\n", temperature );
    
    barometer3_cfg_pres( &barometer3, BAROMETER3_PM_RATE_1, BAROMETER3_PM_PRC_128 );
    barometer3_standby( &barometer3 );
    while ( BAROMETER3_SUCCESS != barometer3_meas_prs_once( &barometer3, &pressure, BAROMETER3_PM_PRC_128 ) );
    log_printf( &logger, " Pressure: %.2f mBar \r\n", pressure );
    log_printf( &logger, "----------------------- \r\n" );
    
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
