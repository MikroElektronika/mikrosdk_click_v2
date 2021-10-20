/*!
 * \file 
 * \brief UNI HALL Click example
 * 
 * # Description
 * This is a example which demonstrates the use of UNI HALL Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO and start write log.
 * 
 * ## Application Task  
 * Detect the north pole magnetic fields near the UNI HALL Click.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart when magnetic field is detected.
 * 
 * \author Mikroe Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "unihall.h"

// ------------------------------------------------------------------ VARIABLES

static unihall_t unihall;
static log_t logger;

static uint8_t unihall_state;
static uint8_t unihall_state_old;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    unihall_cfg_t cfg;

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
    log_printf(&logger, " --- Application Init ---\r\n");

    //  Click initialization.

    unihall_cfg_setup( &cfg );
    UNIHALL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    unihall_init( &unihall, &cfg );

    unihall_state = UNIHALL_NORTH_POLE_DETECTED;
    unihall_state_old = UNIHALL_NORTH_POLE_DETECTED;

    log_printf(&logger, "---------------------------\r\n");
    log_printf(&logger, "        Initialization     \r\n");
    log_printf(&logger, "---------------------------\r\n");
    log_printf(&logger, " Detecting magnetic fields \r\n");
    log_printf(&logger, "---------------------------\r\n");

    Delay_ms( 100 );
}

void application_task ( void )
{
    unihall_state = unihall_detecting_magnetic_fields( &unihall );

    if ( ( unihall_state == UNIHALL_NORTH_POLE_NOT_DETECTED ) && ( unihall_state_old == UNIHALL_NORTH_POLE_DETECTED ) )
    {
        unihall_state_old = UNIHALL_NORTH_POLE_NOT_DETECTED;
        log_printf(&logger, "      ~ NOT DETECTED ~\r\n");
    }

    if ( ( unihall_state == UNIHALL_NORTH_POLE_DETECTED ) && ( unihall_state_old == UNIHALL_NORTH_POLE_NOT_DETECTED ) )
    {
        
        log_printf(&logger, "        ~ DETECTED ~\r\n");
        unihall_state_old = UNIHALL_NORTH_POLE_DETECTED;
    }
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
