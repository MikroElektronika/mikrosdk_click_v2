/*!
 * \file 
 * \brief Manometer Click example
 * 
 * # Description
 * This application carries a piezoresistive silicon pressure sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C and start write log to Usart Terminal.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Manometer Click board.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "manometer.h"

// ------------------------------------------------------------------ VARIABLES

static manometer_t manometer;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    manometer_cfg_t cfg;

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

    manometer_cfg_setup( &cfg );
    MANOMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    manometer_init( &manometer, &cfg );
}

void application_task ( void )
{
    //  Task implementation.

    float read_data;

    read_data = manometer_get_pressure( &manometer );
    Delay_10ms( );

    log_printf( &logger, " Pressure: %.2f mbar\r\n", read_data );

    read_data = manometer_get_temperature( &manometer );
    Delay_10ms( );

    log_printf( &logger, " Temperature:  %.2f C\r\n", read_data );
    log_printf( &logger, "--------------------------\r\n" );

    Delay_1sec( );
    Delay_1sec( );
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
