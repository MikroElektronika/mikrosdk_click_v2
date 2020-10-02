/*!
 * \file 
 * \brief BLE4 Click example
 * 
 * # Description
 * This example reads and processes data from BLE 4 clicks.
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
 * - ble4_process ( ) - The general process of collecting presponce 
 *                      that sends a module.
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ble4.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

#define TX_MODE
//#define RX_MODE

static ble4_t ble4;
static log_t logger;

uint8_t message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
uint8_t dev_name[ 14 ] = { 'B', 'L', 'E', ' ', '4', ' ', 'c', 'l', 'i', 'c', 'k', 13, 10, 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void ble4_process ( void )
{
    uint16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char rx_buf[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while( process_cnt != 0 )
    {
        rsp_size = ble4_generic_read( &ble4, &rx_buf, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != 0 )
        {  
            rx_buf[ rsp_size ] = 0;
            log_printf( &logger, " %s\r\n", rx_buf );
            
            // Clear RX buffer
            memset( rx_buf, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ble4_cfg_setup( &cfg );
    BLE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble4_init( &ble4, &cfg );

    //  Module configuration.

    ble4_hardware_reset( &ble4 );
    Delay_ms( 1000 );
    ble4_factory_reset( &ble4 );
    Delay_ms( 1000 );
    ble4_set_device_name( &ble4, dev_name );
    Delay_ms( 1000 );
    ble4_set_data_mode( &ble4, BLE4_DATA_MODE );
    Delay_ms( 1000 );
#ifdef TX_MODE
    log_printf( &logger, " * Device mode: TX *\r\n" );
#endif
#ifdef RX_MODE
    log_printf( &logger, " * Device mode: RX *\r\n" );
#endif
    log_printf( &logger, "----Initialized----\r\n" );
    Delay_ms( 1000 );

    //process_cnt = 0;
}

void application_task ( void )
{
#ifdef TX_MODE
    uint8_t cnt;

    for( cnt = 0; cnt < 9; cnt++ ) 
    {
        ble4_generic_write( &ble4, &message[ cnt ], 1 );
        Delay_ms( 1000 );
    }
#endif 
#ifdef RX_MODE

    ble4_process( );
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
