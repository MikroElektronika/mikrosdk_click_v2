/*!
 * \file 
 * \brief Bee Click example
 * 
 * # Description
 * The click is designed to run on 3.3V power supply only. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - SPI,
    sets initialization BEE Click as a receiver, also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of BEE Click board.
    In this example, we use BEE Click to receive data.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "bee.h"

// ------------------------------------------------------------------ VARIABLES

static bee_t bee;
static log_t logger;

static uint8_t short_address1[ 2 ];
static uint8_t short_address2[ 2 ];
static uint8_t long_address1[ 8 ];
static uint8_t long_address2[ 8 ];
static uint8_t pan_id1[ 2 ];
static uint8_t pan_id2[ 2 ];
static uint8_t cnt;
static uint8_t rx_data[ 1 ];
static uint8_t rx_data_old;
static uint8_t tmp;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    bee_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    bee_cfg_setup( &cfg );
    BEE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bee_init( &bee, &cfg );

    rx_data_old = 255;
    rx_data[ 0 ] = 0;

    for ( cnt = 0; cnt < 2; cnt++ )
    {
        short_address1[ cnt ] = 1;
        short_address2[ cnt ] = 2;
        pan_id1[ cnt ] = 3;
        pan_id2[ cnt ] = 3;
    }

    for ( cnt = 0; cnt < 8; cnt++ )
    {
        short_address1[ cnt ] = 1;
        short_address2[ cnt ] = 2;
    }

    log_printf( &logger, "    Reset and WakeUp     \r\n"  );
    bee_hw_reset( &bee );
    bee_soft_reset( &bee );
    bee_rf_reset( &bee );
    bee_enable_immediate_wake_up( &bee );
    log_printf( &logger, "    Set address and PAN ID  \r\n" );
    bee_set_long_address( &bee, &long_address2 );
    bee_set_short_address( &bee, &short_address2 );
    bee_set_pan_id( &bee, &pan_id2 );
    log_printf( &logger, "    Init ZigBee module:    \r\n" );
    log_printf( &logger, " - Set nonbeacon-enabled \r\n" );
    bee_nonbeacon_init( &bee );
    log_printf( &logger, " - Set as PAN coordinator\r\n" );
    bee_nonbeacon_pan_coordinator_device( &bee );
    log_printf( &logger, " - Set max TX power\r\n" );
    bee_set_tx_power( &bee, 31 );
    log_printf( &logger, " - All frames 3, data frame\r\n" );
    bee_set_frame_format_filter( &bee, 1 );
    log_printf( &logger, " - Set normal mode\r\n"  );
    bee_set_reception_mode( &bee, 1 );
     log_printf( &logger, " - Device Wake Up\r\n"  );
    bee_hw_wake_up( &bee );
    log_printf( &logger, " - Received data :      \r\n" );
    Delay_1sec( );
}

void application_task ( void )
{
    if ( bee_interrupt_activity( &bee ) == 0 )
    {
        tmp = bee_read_byte_short( &bee, BEE_INTSTAT );
        bee_read_rx_fifo( &bee, &rx_data );
        Delay_100ms( );

        if ( rx_data[ 0 ] != rx_data_old )
        {
           log_printf( &logger, "%d \r\n", rx_data[ 0 ] );
           rx_data_old = rx_data[ 0 ];
        }
    }
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
