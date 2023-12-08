/*!
 * \file 
 * \brief DigiPot3 Click example
 * 
 * # Description
 * This app get value from digital potentiometer and stored to the EEMEM memory.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Increments the wiper position by 6dB every 2 seconds. When wiper position
 * reaches the desired value (0x0200), then the wiper position be decremented by 6dB every 2 seconds, until position 
 * value reaches the new desired value (0x0002). After that the new position value will be stored to the EEMEM memory,
 * if that value does not already exist in the EEMEM memory.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "digipot3.h"

// ------------------------------------------------------------------ VARIABLES

static digipot3_t digipot3;
static log_t logger;

uint16_t digital_value;
uint16_t eemem_value;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot3_cfg_t cfg;

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

    digipot3_cfg_setup( &cfg );
    DIGIPOT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot3_init( &digipot3, &cfg );

    Delay_ms( 200 );
    
    digipot3_read_dac(  &digipot3, &digital_value );
    digipot3_read_eemem( &digipot3, DIGIPOT3_RDAC_EEMEM_LOC, &eemem_value );
    
    if ( eemem_value != digital_value )
    {
        digipot3_send_command( &digipot3, DIGIPOT3_RESTORE_EEMEM_TO_RDAC_COMM );
    }

    log_printf( &logger, "DIGI POT 3 is initialized \r\n" );
    Delay_ms( 200 );
}

void application_task ( void )
{
    while ( digital_value < 0x0200 )
    {
        digipot3_send_command( &digipot3, DIGIPOT3_INCREMENT_RDAC_6DB_COMM );
        digipot3_read_dac( &digipot3, &digital_value );
        log_printf( &logger, "DAC value is: %u \r\n", digital_value );
        Delay_ms( 2000 );
    }

    while ( digital_value > 0x0002 )
    {
        digipot3_send_command( &digipot3, DIGIPOT3_DECREMENT_RDAC_6DB_COMM );
        digipot3_read_dac( &digipot3, &digital_value );
        log_printf( &logger, "DAC value is: %u \r\n", digital_value );
        Delay_ms( 2000 );
    }

    if ( eemem_value != digital_value )
    {
        digipot3_send_command( &digipot3, DIGIPOT3_STORE_RDAC_TO_EEMEM_COMM );
        eemem_value = digital_value;
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
