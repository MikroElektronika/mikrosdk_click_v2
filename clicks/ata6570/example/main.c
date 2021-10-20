/*!
 * \file 
 * \brief Ata6570 Click example
 * 
 * # Description
 * This application is interfaces a Controller Area Network (CAN) protocol controller and the physical two-wire CAN bus.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * In addition to this module is palced inside normal working mode cappable of tranmission and reception of data.
 * 
 * ## Application Task  
 * Tranismiter/Receiver task depend on uncommented code
  Receiver logging each received byte to the UART for data logging, while transmiter send message each
  2 seconds.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ata6570.h"


// ------------------------------------------------------------------ VARIABLES

#define PROCESS_RX_BUFFER_SIZE 500

// #define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITER

static ata6570_t ata6570;
static log_t logger;

static char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
static int32_t rsp_size;
static char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ata6570_cfg_t cfg;

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

    ata6570_cfg_setup( &cfg );
    ATA6570_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ata6570_init( &ata6570, &cfg );
    ata6570_write_reg( &ata6570, ATA6570_DMCR, ATA6570_OPMODE_NORMAL );
    Delay_ms( 500 );
}

void application_task ( void )
{
    //  Task implementation.
    
#ifdef DEMO_APP_RECEIVER
       // RECEIVER - UART polling
      rsp_size = ata6570_generic_read( &ata6570, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

      if ( rsp_size > 0 )
        {  
            log_printf( &logger, "%s", uart_rx_buffer );
            memset( uart_rx_buffer, 0, rsp_size );
        }  
#endif
       
#ifdef DEMO_APP_TRANSMITER
       // TRANSMITER - TX each 2 sec
       for( uint8_t i = 0; i < 8; i++ )
       {
           ata6570_generic_write( &ata6570, &demo_message[ i ], 1 );
       }
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
