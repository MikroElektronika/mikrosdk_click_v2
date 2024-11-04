/*!
 * \file 
 * \brief Barometer2 Click example
 * 
 * # Description
 * This application measures temperature and pressure data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes and configures the Click and logger modules and tests the communication for errors.
 * 
 * ## Application Task  
 * Reads and displays temperature and pressure values every second. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "barometer2.h"

// ------------------------------------------------------------------ VARIABLES

static barometer2_t barometer2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    barometer2_cfg_t cfg;
    
    uint8_t test;

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

    barometer2_cfg_setup( &cfg );
    BAROMETER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barometer2_init( &barometer2, &cfg );

    // Test communication

    test = barometer2_read_byte( &barometer2, BAROMETER2_REG_WHO_AM_I ); 

    if ( test == BAROMETER2_WHO_AM_I )
    {
        log_printf( &logger, "---- Communication OK!!! ----\r\n" );
    }
    else
    {
        log_printf( &logger, "---- Communication ERROR!!! ----\r\n" );
        for ( ; ; );
    } 

    // Software reset 

    barometer2_software_reset( &barometer2 );
    Delay_ms ( 1000 );
    
    barometer2_default_cfg( &barometer2 );
    Delay_ms ( 1000 );
    log_printf( &logger, "---- Start Measurement ---- \r\n" );
}

void application_task ( )
{
    float temperature;
    float pressure;
     
    temperature = barometer2_get_temperature( &barometer2, BAROMETER2_TEMPERATURE_IN_CELSIUS );
    log_printf( &logger, " Temperature : %.2f C\r\n", temperature );

    pressure = barometer2_get_pressure( &barometer2, BAROMETER2_PRESSURE_DATA_IN_mBar );
    log_printf( &logger, " Pressure : %.2f mbar\r\n", pressure );

    log_printf( &logger, "-------------------------- \r\n" );
    Delay_ms ( 1000 );
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
