/*!
 * \file 
 * \brief REED Click example
 * 
 * # Description
 * This is a example which demonstrates the use of REED Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init
 * Configuring clicks and log objects.
 * 
 * ## Application Task
 * Detect the magnetic field near the REED Click.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart when magnetic field is detected.
 * 
 * \author Nemanja Medakovic
 *
 */

#include "board.h"
#include "log.h"
#include "reed.h"

static reed_t reed;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    reed_cfg_t reed_cfg;

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
    log_info( &logger, "---- Application Init... ----" );

    //  Click initialization.

    reed_cfg_setup( &reed_cfg );
    REED_MAP_MIKROBUS( reed_cfg, MIKROBUS_1 );

    if ( reed_init( &reed, &reed_cfg ) == REED_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----" );
    log_info( &logger, "---- Application Running... ----\n" );
}

void application_task ( void )
{
    uint8_t reed_state = REED_NO_MAGNETIC_FIELD;
    static uint8_t reed_state_old = REED_NO_MAGNETIC_FIELD;

    reed_state = reed_get_status( &reed );

    if ( ( reed_state == REED_MAGNETIC_FIELD_DETECTED ) && ( reed_state_old == REED_NO_MAGNETIC_FIELD ) )
    {
        reed_state_old = reed_state;

        log_printf( &logger, "    ~ UNLOCKED ~\r\n" );
        log_printf( &logger, "--------------------\r\n" );
    }
    else if ( ( reed_state == REED_NO_MAGNETIC_FIELD ) && ( reed_state_old == REED_MAGNETIC_FIELD_DETECTED ) )
    {
        reed_state_old = reed_state;

        log_printf( &logger, "     ~ LOCKED ~\r\n" );
        log_printf( &logger, "--------------------\r\n" );
    }
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
