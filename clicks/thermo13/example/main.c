/*!
 * \file 
 * \brief Thermo13 Click example
 * 
 * # Description
 * The application measures temperature
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver init, configures the module and
 * reads the temperature Limit LOW/HIGH values that are set.
 * 
 * ## Application Task  
 * Reads ambient temperature data and this data logs to USBUART every 1500ms.
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo13.h"

// ------------------------------------------------------------------ VARIABLES

static thermo13_t thermo13;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo13_cfg_t cfg;
    
    float temp_limit_low;
    float temp_limit_high;

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

    //  Click initialization

    thermo13_cfg_setup( &cfg );
    THERMO13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo13_init( &thermo13, &cfg );

    // Configuration 
   
    thermo13_configuration( &thermo13, THERMO13_CFG_CONTINUOUS_MEASUREMENT |
                            THERMO13_CFG_FAULT_QUEUE_1 |
                            THERMO13_CFG_ALERT_ACTIVE_HIGH |
                            THERMO13_CFG_INTERRUPT_IS_ACTIVE |
                            THERMO13_CFG_WAIT_TIME_X16 );

        
    // Temperature Register
   
    log_printf( &logger, " --- Temperature register data --- \r\n \r\n" );

    temp_limit_low = thermo13_get_temp_limit ( &thermo13, THERMO13_REG_TEMPERATURE_LIMIT_LOW );
    log_printf( &logger, " --- Temp - Limit LOW : %.2f C \r\n ", temp_limit_low );

    temp_limit_high = thermo13_get_temp_limit ( &thermo13, THERMO13_REG_TEMPERATURE_LIMIT_HIGH );
    log_printf( &logger, " --- Temp - Limit HIGH :  %.2f C \r\n \r\n  ", temp_limit_high );
    
    log_printf( &logger, " --- Ambient temperature measurement --- \r\n " );

}

void application_task ( void )
{
    float temperature;

    temperature = thermo13_get_ambient_temperature_data ( &thermo13, THERMO13_TEMP_IN_CELSIUS );
    log_printf( &logger, "** temperature %.2f ** \r\n", temperature );
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms ( 1000 );
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
