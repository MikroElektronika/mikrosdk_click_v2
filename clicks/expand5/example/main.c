/*!
 * \file 
 * \brief Expand5 Click example
 * 
 * # Description
 * This example demonstrates the use of Expand 5 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, resets the device, configures all pins as output and makes an initial log.
 * 
 * ## Application Task  
 * This example shows the capabilities of the EXPAND 5 Click by toggling each of the 24 available pins.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "expand5.h"

// ------------------------------------------------------------------ VARIABLES

static expand5_t expand5;
static log_t logger;

uint8_t pin_num;
uint8_t bank_out = 0x00;
uint8_t bank_low = 0x00;
char log_txt[ 50 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand5_cfg_t cfg;

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

    expand5_cfg_setup( &cfg );
    EXPAND5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand5_init( &expand5, &cfg );

    Delay_ms ( 100 );

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   EXPAND 5 Click   \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    expand5_reset( &expand5 );
    expand5_set_all_dir( &expand5, bank_out, bank_out, bank_out );
    Delay_ms ( 100 );
    log_printf( &logger, "  Pins configured   \r\n" );
    log_printf( &logger, "     as output      \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}

void application_task ( void )
{
    for ( pin_num = EXPAND5_P00; pin_num <= EXPAND5_P27; pin_num++ )
    {
        expand5_write_all_banks ( &expand5, bank_low, bank_low, bank_low );
        expand5_write_pin ( &expand5, pin_num, EXPAND5_HIGH );
        log_printf( &logger, "Pin %u is high \r\n", ( uint16_t ) pin_num );

        Delay_ms ( 200 );
        expand5_write_all_banks ( &expand5, bank_low, bank_low, bank_low );
    }
    log_printf( &logger, "------------------- \r\n" );
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
