/*!
 * \file 
 * \brief Ldc1101 Click example
 * 
 * # Description
 * Example demonstrates measurement of inductance change depending on the linear motion of the metal object.
 * Induction of the linear metal position depends on the type of metal and the configuration.
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C module and sets CS pin as OUTPUT and PWM and INT pin sa INPUT.
 * Driver intialization, standard configurations and start measurement.
 * 
 * ## Application Task  
 * Reads RP data and logs data to USBUART every 1 sec.
 * 
 * \author Nenad Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ldc1101.h"

// ------------------------------------------------------------------ VARIABLES

static ldc1101_t ldc1101;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ldc1101_cfg_t cfg;

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

    ldc1101_cfg_setup( &cfg );
    LDC1101_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ldc1101_init( &ldc1101, &cfg );

    log_printf( &logger, "     LDC1101 Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    
    ldc1101_default_cfg ( &ldc1101 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint16_t rp_data;
    
    rp_data = ldc1101_get_rp_data( &ldc1101 );
    log_printf( &logger, " Inductive Linear Position : %u\r\n", rp_data );
    
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
