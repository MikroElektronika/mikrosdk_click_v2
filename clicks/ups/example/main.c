/*!
 * \file 
 * \brief UPS Click example
 * 
 * # Description
 * This application is charger, that provides continuous power for a load connected to the output terminals.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and setting chip mode as ACTIVE
 * 
 * ## Application Task  
 * Checks the state of PGD (Power Good), PGD goes high when Vout is within 6% of target value (4.98V)
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ups.h"

// ------------------------------------------------------------------ VARIABLES

static ups_t ups;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ups_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    ups_cfg_setup( &cfg );
    UPS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ups_init( &ups, &cfg );

    usp_set_mode( &ups, UPS_MODE_ACTIVE );
}

void application_task ( )
{
    uint8_t pgd_state;

    pgd_state = ups_get_power_good( &ups );

    if ( pgd_state != 0 )
    {
        log_printf( &logger, "---> Power Good \r\n" );
    }
    Delay_1sec( );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
