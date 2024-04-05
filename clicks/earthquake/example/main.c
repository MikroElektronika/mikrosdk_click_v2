/*!
 * \file 
 * \brief Earthquake Click example
 * 
 * # Description
 * Intializes I2C module, LOG and GPIO structure, sets INT and PWM pins as 
 * input and sets CS pin as output.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Intializes of I2C driver and makes initial log.
 * 
 * ## Application Task  
 * This is an example that shows most of the functions that Earthquake click
 * has. Results are being sent to the Usart Terminal where you can track their 
 * changes.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "earthquake.h"

// ------------------------------------------------------------------ VARIABLES

static earthquake_t earthquake;
static log_t logger;
uint16_t read_data;
uint8_t cnt;

void display_status( uint8_t status_data )
{
    if ( status_data == EARTHQUAKE_STANDBY_MODE )
    {
        log_printf( &logger, "Standby  Mode \r\n" );
    }

    if ( status_data == EARTHQUAKE_NORMAL_MODE )
    {
        log_printf( &logger, "Normal Mode \r\n" );
    }
    
    if ( status_data == EARTHQUAKE_INIT_INST )
    {
        log_printf( &logger, "Initial Installation Mode \r\n" );
    }
    
    if ( status_data == EARTHQUAKE_OFFSET_ACQ )
    {
        log_printf( &logger, "Offset Acquisition Mode \r\n" );
    }
    
    if ( status_data == EARTHQUAKE_SELF_DIAGNOSTIC )
    {
        log_printf( &logger, "Self-Diagnostic Mode \r\n" );
    }
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    earthquake_cfg_t cfg;

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
    earthquake_cfg_setup( &cfg );
    EARTHQUAKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    earthquake_init( &earthquake, &cfg );
    Delay_ms ( 1000 );
    display_status( earthquake_read_status( &earthquake ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    earthquake_clear_memory( &earthquake );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "    Earthquake Click    \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}

void application_task ( void )
{
    if ( earthquake_proc_notify( &earthquake ) )
    {
        log_printf( &logger, "  Earthquake detected!  \r\n" );
        log_printf( &logger, "------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );

        for ( cnt = 20; cnt > 0; cnt-- )
        {
            log_printf( &logger, " Status : " );
            display_status( earthquake_read_status( &earthquake ) );

            read_data = earthquake_read_si( &earthquake );
            log_printf( &logger, " Max SI : %d\r\n", read_data );
            log_printf( &logger, "------------------------ \r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }

        earthquake_clear_memory( &earthquake );
        log_printf( &logger, " Afterquake  processing \r\n" );
        log_printf( &logger, "     please wait...     \r\n" );
        // 20 seconds delay
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );

        log_printf( &logger, "------------------------\r\n" );
        log_printf( &logger, " Waiting for a quake... \r\n" );
        log_printf( &logger, "------------------------\r\n" );
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
