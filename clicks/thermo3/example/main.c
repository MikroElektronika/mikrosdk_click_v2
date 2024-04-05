/*!
 * \file 
 * \brief Thermo3 Click example
 * 
 * # Description
 * This application read the temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Thermo 3 Click board.
 * Detects the temperature and write on usb uart changes for every 3 sec.
 * 
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo3.h"

// ------------------------------------------------------------------ VARIABLES

static thermo3_t thermo3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo3_cfg_t cfg;

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

    thermo3_cfg_setup( &cfg );
    THERMO3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo3_init( &thermo3, &cfg );
}

void application_task ( void )
{
    float read_temp;

    read_temp = get_temperature( &thermo3 );

    log_printf( &logger, "Temperature: %.2f C\r\n", read_temp );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
