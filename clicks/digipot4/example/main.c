/*!
 * \file 
 * \brief DigiPot4 Click example
 * 
 * # Description
 * This application is a digitally controlled dual potentiometer.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver intialization
 * 
 * ## Application Task  
 * Set the wiper position.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "digipot4.h"

// ------------------------------------------------------------------ VARIABLES

static digipot4_t digipot4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot4_cfg_t cfg;

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

    digipot4_cfg_setup( &cfg );
    DIGIPOT4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot4_init( &digipot4, &cfg );
}

void application_task ( void )
{
    //  Task implementation.

    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_1, 0 );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_2, 0 );
    Delay_1sec( );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_1, 512 );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_2, 512 );
    Delay_1sec( );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_1, 1023 );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_2, 1023 );
    Delay_1sec( );
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
