/*!
 * \file 
 * \brief Charger12 Click example
 * 
 * # Description
 * This application charges the batery.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Iniztializes SPI driver.
 * 
 * ## Application Task  
 * Executes additional functions based on user input.
 * 
 * *note:* 
 * Additional Functions :

 * - charger12_case_Plus()  - Increments Wiper position.
 * - charger12_case_Minus() - Decrements Wiper position.
 * - charger12_case_One()   - Selects 1st mode of operation.
 * - charger12_case_Two()   - Selects 2nd mode of operation.
 * - charger12_case_Three() - Selects 3rd mode of operation.
 * - charger12_case_Four()  - Selects 4th mode of operation.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "charger12.h"

// ------------------------------------------------------------------ VARIABLES

static charger12_t charger12;
static log_t logger;

void charger12_case_plus( )
{
   log_printf( &logger, "> Wiper incremented" );
    charger12_spi_increment_wiper( &charger12 );
    log_printf( &logger, "\r\n" );
}

void charger12_case_minus( )
{
    log_printf( &logger, "> Wiper decremented" );
    charger12_spi_increment_wiper( &charger12 );
   log_printf( &logger, "\r\n" );
}

void charger12_case_one( )
{
    charger12_mode_select( &charger12, CHARGER12_MODE_Li );
    log_printf( &logger, "> Mode : Li+ Charge");
    log_printf( &logger, "\r\n" );
}

void charger12_case_two( )
{
    charger12_mode_select( &charger12, CHARGER12_MODE_NiMh_NiCd );
    log_printf( &logger, "> Mode : NiMH/NiCd Charge" );
    log_printf( &logger, "\r\n" );
}

void charger12_case_three( )
{
    charger12_mode_select( &charger12, CHARGER12_MODE_DISABLE );
    log_printf( &logger, "> Mode : Disable" );
    log_printf( &logger, "\r\n" );
}

void charger12_case_four( )
{
    charger12_mode_select( &charger12, CHARGER12_MODE_NO_BATTERY );
    log_printf( &logger, "> Mode : No Battery" );
    log_printf( &logger, "\r\n" );
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    charger12_cfg_t cfg;

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

    charger12_cfg_setup( &cfg );
    CHARGER12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger12_init( &charger12, &cfg );

    Delay_ms(100);
    charger12_mode_select( &charger12, CHARGER12_MODE_DISABLE );
    Delay_ms(100);
    log_printf( &logger, "> App init done" );
}

void application_task ( void )
{
    charger12_case_plus(  );
    Delay_ms( 1000 );
  
    charger12_case_minus( );
    Delay_ms( 1000 );

    charger12_case_one( );
    Delay_ms( 1000 );     

    charger12_case_two( );
    Delay_ms( 1000 );   

    charger12_case_three( );
    Delay_ms( 1000 );

    charger12_case_four( );
    Delay_ms( 1000 );
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
