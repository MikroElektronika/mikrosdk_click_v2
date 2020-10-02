/*!
 * \file 
 * \brief Dmx Click example
 * 
 * # Description
 * This example reads and processes data from DMX clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - dmx_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dmx.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

static dmx_t dmx;
static log_t logger;

static uint8_t device_mode;
static uint8_t master_mode;

static uint8_t sadr_cmd        [ 10 ] = "@SADR,001";
static uint8_t blen_cmd        [ 10 ] = "@BLEN,006";
static uint8_t itmr_cmd        [ 10 ] = "@ITMR,000";
static uint8_t ftmr_cmd        [ 10 ] = "@FTMR,001";
static uint8_t flen_master_cmd [ 10 ] = "@FLEN,010";
static uint8_t flen_slave_cmd  [ 10 ] = "@FLEN,006";
static uint8_t purgebfr_cmd    [ 10 ] = "!PURGEBFR";

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void dmx_process ( void )
{
    uint16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while( process_cnt != 0 )
    {
        rsp_size = dmx_generic_read( &dmx, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            log_printf( &logger, "%s \r\n", uart_rx_buffer );  
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_100ms( );
        }
    }
}

void application_demo( dmx_t *ctx )
{
    uint8_t tx_buff[ 6 ] = { 0 };
    uint16_t i;
    uint8_t j;

    tx_buff[ 1 ] = 255;
    for ( i = 0; i < 256; i++ )
    {
        tx_buff[ 0 ] = i;
        dmx_generic_write( ctx, &tx_buff[ 0 ], 6 );
    }
    for ( i = 254; i > 0; i-- )
    {
        tx_buff[ 0 ] = i;
        dmx_generic_write( ctx, &tx_buff[ 0  ], 6  );
    }

    tx_buff[ 1 ] = 0;
    tx_buff[ 2 ] = 255;
    for ( i = 0; i < 256; i++ )
    {
        tx_buff[ 0 ] = i;
        dmx_generic_write( ctx, &tx_buff[ 0  ], 6  );
    }
    for ( i = 254; i > 0; i-- )
    {
        tx_buff[ 0 ] = i;
        dmx_generic_write( ctx, &tx_buff[ 0  ], 6  );
    }

    tx_buff[ 2 ] = 0;
    tx_buff[ 3 ] = 255;
    for ( i = 0; i < 256; i++ )
    {
        tx_buff[ 0 ] = i;
        dmx_generic_write( ctx, &tx_buff[ 0  ], 6  );
    }
    for ( i = 254; i > 0; i-- )
    {
        tx_buff[ 0 ] = i;
        dmx_generic_write( ctx, &tx_buff[ 0  ], 6  );
    }

    tx_buff[ 0 ] = 255;
    for ( j = 0; j < 5; j++ )
    {
        for ( i = 0; i < 256; i++ )
        {
            tx_buff[ 1 ] = 255 - i;
            tx_buff[ 3 ] = i;
            if ( ( i % 128 ) == 0 )
            {
                tx_buff[ 2 ] = 255;
            }
            dmx_generic_write( ctx, &tx_buff[ 0  ], 6  );
            tx_buff[ 2 ] = 0;
        }
        for ( i = 0; i < 256; i++ )
        {
            tx_buff[ 1 ] = i;
            tx_buff[ 3 ] = 255 - i;
            if ( ( i % 128 ) == 0 )
            {
                tx_buff[ 2 ] = 255;
            }
            dmx_generic_write( ctx, &tx_buff[ 0  ], 6  );
            tx_buff[ 2 ] = 0;
        }
    }

    tx_buff[ 1 ] = 255;
    tx_buff[ 2 ] = 255;
    tx_buff[ 3 ] = 255;
    tx_buff[ 4 ] = 255;
    for ( i = 1; i < 7; i++ )
    {
        tx_buff[ 5 ] = i * 40;
        dmx_generic_write( ctx, &tx_buff[ 0  ], 6  );
        Delay_ms( 2500 );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dmx_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dmx_cfg_setup( &cfg );
    DMX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dmx_init( &dmx, &cfg );

    dmx_auto_baud_rate( &dmx );
    Delay_ms( 100 );

/** 
 * This is the only place where user needs to set the device mode,
 * master or slave.
 */

    device_mode = DMX_MASTER;
    master_mode = DMX_MASTER_DEMO_CTRL;

    dmx_reset( &dmx, device_mode );
    dmx_process( );
    dmx_run( &dmx, DMX_CONFIG_MODE );
    Delay_ms( 100 );

    if ( device_mode == DMX_SLAVE )
    {
        dmx_generic_write( &dmx, &sadr_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &flen_slave_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &itmr_cmd[ 0 ], 9 );
        dmx_process( );
    }
    else
    {
        dmx_generic_write( &dmx, &purgebfr_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &sadr_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &blen_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &flen_master_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &itmr_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &ftmr_cmd[ 0 ], 9 );
        dmx_process( );
    }

    dmx_run( &dmx, DMX_RUN_MODE );

    log_printf( &logger, "************************************\r\n" );
    log_printf( &logger, "***   SmartDMX is ready now...   ***\r\n" );
    log_printf( &logger, "************************************\r\n" );

    Delay_ms( 500 );
}

void application_task ( void )
{
    uint8_t test[ 6 ] = { 0 };

    if ( device_mode == DMX_SLAVE )
    {
        dmx_process(  );
    }
    else
    {
        application_demo( &dmx );
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
