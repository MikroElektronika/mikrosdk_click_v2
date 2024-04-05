/*!
 * \file main.c
 * \brief Charger 5 Click example
 *
 * # Description
 * This example demonstrates the use of the Charger 5 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes peripherals and pins used for the Charger 5 click and prepares
 * the Charger 5 click for properly working.
 *
 * ## Application Task
 * Demonstrates the use of driver functions. It will set charging current to
 * 500 mA, then will increment that value by 10 steps, and after that will
 * decrement it by 5 steps.
 *
 * ## Note
 * Increment/decrement command can only be issued to volatile memory locations.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "charger5.h"

// ------------------------------------------------------------------ VARIABLES

static charger5_t charger5;
static log_t console;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    charger5_cfg_t charger5_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    charger5_cfg_setup( &charger5_cfg );
    CHARGER5_MAP_MIKROBUS( charger5_cfg, MIKROBUS_1 );
    charger5_init( &charger5, &charger5_cfg );
    charger5_default_cfg( &charger5 );

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( console_cfg );
    log_init( &console, &console_cfg );
    log_printf( &console, "***  Charger 5 initialization done  ***\r\n" );
    log_printf( &console, "***************************************\r\n" );
}

void application_task( void )
{
    charger5_generic_write( &charger5, CHARGER5_REG_WIPER0_VOL,
                            CHARGER5_CURRENT_500MA );
    log_printf( &console, "Output current is set to 500 mA.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    charger5_increment_wiper( &charger5, CHARGER5_REG_WIPER0_VOL,
                              CHARGER5_STEPS_10 );
    log_printf( &console, "Output current value is incremented by 10 steps.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    charger5_decrement_wiper( &charger5, CHARGER5_REG_WIPER0_VOL,
                              CHARGER5_STEPS_5 );
    log_printf( &console, "Output current value is decremented by 5 steps.\r\n" );
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
