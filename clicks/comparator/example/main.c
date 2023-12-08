/*!
 * \file 
 * \brief Comparator Click example
 * 
 * # Description
 * Comparator Click represents board equipped with two 
 * independent precise voltage comparators.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * Comparator click checks state of the O1 and O2 pins. 
 * Results are being sent to the UART Terminal 
 * where you can track their changes. 
 * All data logs write on USB UART and changes for every 1 sec.
 *  
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "comparator.h"

uint8_t out_state_one;
uint8_t out_state_two;

// ------------------------------------------------------------------ VARIABLES

static comparator_t comparator;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    comparator_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 500 );

    //  Click initialization.

    comparator_cfg_setup( &cfg );
    COMPARATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    comparator_init( &comparator, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " --- Comparator Click --- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    out_state_one = comparator_check_output_one( &comparator );
    out_state_two = comparator_check_output_two( &comparator );
    
    log_printf( &logger, "   Output One: \r\n" );
    
    if ( out_state_one )
    {
        log_printf( &logger, "   High \r\n" );
    }
    else
    {
        log_printf( &logger, "   Low \r\n" );
    }
    
    Delay_ms ( 500 );
    
    log_printf( &logger, "   Output Two: \r\n" );
    
    if ( out_state_two )
    {
        log_printf( &logger, "   High \r\n" );
    }
    else
    {
        log_printf( &logger, "   Low \r\n" );
    }
    
    Delay_ms ( 500 );
    
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
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
