/*!
 * \file 
 * \brief Ata663211 Click example
 * 
 * # Description
 * This application is for handling low-speed data communication in vehicles and in industrial.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes device and makes an initial log.
 * 
 * ## Application Task  
 * Checks if new data byte have received in rx buffer (ready for reading), and if ready than reads one byte from rx buffer.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ata663211.h"

// ------------------------------------------------------------------ VARIABLES

//#define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITER

static ata663211_t ata663211;
static log_t logger;

static char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ata663211_cfg_t cfg;

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

    ata663211_cfg_setup( &cfg );
    ATA663211_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ata663211_init( &ata663211, &cfg );
}

void application_task ( void )
{
    char tmp;
    
    //  Task implementation.
    
#ifdef DEMO_APP_RECEIVER

       // RECEIVER - UART polling

       tmp =  ata663211_generic_single_read( &ata663211 );
       log_printf( &logger, " %c ", tmp );
#endif
#ifdef DEMO_APP_TRANSMITER

       // TRANSMITER - TX each 2 sec
       
       ata663211_generic_multi_write( &ata663211, demo_message, 9 );
       Delay_ms( 2000 );
#endif

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
