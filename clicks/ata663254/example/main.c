/*!
 * \file 
 * \brief Ata663254 Click example
 * 
 * # Description
 * This application demonstates the use of ATA663254 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the click driver and enables the click board.
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads all the received data or sends the desired message
 * each 2 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ata663254.h"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITTER

static ata663254_t ata663254;
static log_t logger;

static char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
static char rec_buf[ 50 ] = { 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ata663254_cfg_t cfg;

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

    ata663254_cfg_setup( &cfg );
    ATA663254_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ata663254_init( &ata663254, &cfg );
    
    ata663254_enable( &ata663254, 1 );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER

    // RECEIVER - UART polling
    
    int32_t len = ata663254_generic_read( &ata663254, rec_buf, 50 );
    if ( len > 0 )
    {
        log_printf( &logger, "Received data: " );
        for ( int32_t cnt = 0; cnt < len; cnt++  )
        {
            log_printf( &logger, "%c", rec_buf[ cnt ] );
        }
        memset( rec_buf, 0 , 50 );
    }
    Delay_ms ( 100 );
#endif
#ifdef DEMO_APP_TRANSMITTER

    // TRANSMITER - TX each 2 sec
       
    ata663254_generic_write( &ata663254, demo_message, 9 );
    log_info( &logger, "--- Data sent ---" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
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
