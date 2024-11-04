/*!
 * \file 
 * \brief MacAddress Click example
 * 
 * # Description
 * Provides a unique node address for your application.
 *
 * The application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C, also write log.
 * 
 * ## Application Task - (code snippet) This is an example which demonstrates the use of MAC Address Click board.
 * MAC Address Click communicates with register via I2C protocol by the write to register and read from the register.
 * This example shows write/read single byte and sequential write/read from EEPROM.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes for every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "macaddress.h"


// ------------------------------------------------------------------ VARIABLES

static macaddress_t macaddress;
static log_t logger;

static uint8_t *write_data[ 3 ] = { "MikroE", "MAC Address", "MikroElektronika" };

static uint8_t data_len[ 3 ] = { 6 , 11, 16 };

static uint8_t mac_addr[ 8 ] = { 0 };

static uint8_t data_cnt;

static uint8_t read_buff[ 50 ] = { 0 };

static uint8_t address = 0x10;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    macaddress_cfg_t cfg;

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

    macaddress_cfg_setup( &cfg );
    MACADDRESS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    macaddress_init( &macaddress, &cfg );
    
    macaddress_get_mac( &macaddress, mac_addr );
    
    log_printf( &logger, " > MAC Address: 0x" );
    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        log_printf( &logger, "%.02X", (uint16_t)mac_addr[ cnt ] );
    }
    log_printf( &logger, "\r\n" );

    Delay_ms ( 1000 );
    log_info( &logger, "---- Application Task ----" );
    data_cnt = 0;
}

void application_task ( void )
{
    log_printf( &logger, " > Writing data to memory...\r\n" );
    Delay_ms ( 100 );
    macaddress_generic_write( &macaddress, address, write_data[ data_cnt ], data_len[ data_cnt ] );
    log_printf( &logger, " > Writing done.\r\n" );
    Delay_ms ( 1000 );
    
    
    log_printf( &logger, " > Reading data from memory...\r\n" );
    macaddress_generic_read( &macaddress, address, read_buff, data_len[ data_cnt ] );
    Delay_ms ( 100 );
    log_printf( &logger, " > Read data: " );
    for( uint8_t cnt = 0; cnt < data_len[ data_cnt ]; cnt++ )
    {
        log_printf( &logger, "%c", read_buff[ cnt ] );
    }
    log_printf( &logger, "\r\n" );
    Delay_ms ( 100 );
    log_printf( &logger, " > Reading done.\r\n" );
    log_printf( &logger, "---------------------------------\r\n" );
    data_cnt++;
    if ( data_cnt >= 3 )
        data_cnt = 0;
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

