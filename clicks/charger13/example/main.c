/*!
 * \file 
 * \brief Charger 13 Click example
 * 
 * # Description
 * This demo application charges the battery.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Charger 13 Click board.
 * This example shows the automatic control of the Charger 13 Click,
 * waits for valid user input and executes functions based on a set of valid commands
 * and check the battery charge status.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for approximately every 1 sec when the data value changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "charger13.h"

// ------------------------------------------------------------------ VARIABLES

static charger13_t charger13;
static log_t logger;
uint8_t charger_flag;
uint8_t enable_flag;
uint8_t status_flag;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    charger13_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    charger13_cfg_setup( &cfg );
    CHARGER13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger13_init( &charger13, &cfg );

    Delay_100ms( );

    charger_flag = 2;
    enable_flag = 0;

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "      'E' : Enable       \r\n" );
    log_printf( &logger, "      'D' : Disable      \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "Charging Status : Disable\r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_100ms( );
}

void application_task ( void )
{
    if ( enable_flag == 0 )
    {
        enable_flag = 1;
        charger13_enable( &charger13 );
        log_printf( &logger, "Charging Status : Enabled\r\n" );
        log_printf( &logger, "-------------------------\r\n" );
    }
    else if ( enable_flag == 1 )
    {
        enable_flag = 0;
        charger13_disable( &charger13 );
        log_printf( &logger, "Charging Status : Disable\r\n" );
        log_printf( &logger, "-------------------------\r\n" );
    }
    status_flag = charger13_check( &charger13 );

    if ( status_flag != charger_flag )
    {   
        charger_flag = charger13_check( &charger13 );

        if ( charger_flag == 0 )
        {
            log_printf( &logger, "   Battery is charging   \r\n" );
            log_printf( &logger, "-------------------------\r\n" );
        }
        else
        {
            log_printf( &logger, " Battery does not charge \r\n" );
            log_printf( &logger, "-------------------------\r\n" );
        }
    }    
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
