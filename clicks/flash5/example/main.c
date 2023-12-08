/*!
 * \file 
 * \brief Flash5 Click example
 * 
 * # Description
 * This application is for storing mass storage.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, resets device, erasing one page of memory, tests communication and configures device.
 * 
 * ## Application Task  
 * Writes "MikroE" to device memory and then reads it and sends it to log.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "flash5.h"

// ------------------------------------------------------------------ VARIABLES

static flash5_t flash5;
static log_t logger;
static char write_buf[ 7 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    flash5_cfg_t cfg;
    uint8_t device_check = 0;

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

    flash5_cfg_setup( &cfg );
    FLASH5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash5_init( &flash5, &cfg );

    log_printf( &logger, " - Reseting device... \r\n" );
 
    flash5_software_reset( &flash5 );
    Delay_ms( 1000 );
    
    log_printf( &logger, " - Erasing memory... \r\n" );   
    
    flash5_send_cmd( &flash5, FLASH5_CMD_WRITE_ENABLE );
    flash5_erase_page_data( &flash5, 0x0001 );
    
    device_check = flash5_device_id_check( &flash5 );

    if ( device_check == FLASH5_DEVICE_OK )
    {
        log_printf( &logger, " - Device OK \r\n" );  
    }
    else
    {
        log_printf( &logger, " - Device Error \r\n" );  
        for( ; ; );
    }
    Delay_ms( 100 );

    log_printf( &logger, " - Configuring device \r\n" );  

    flash5_write_status_data( &flash5, FLASH5_CMD_WRITE_REG_STATUS1, FLASH5_REG_STATUS_1, FLASH5_RS1_WRITE_PROTECTION_DISABLE | 
                                                                                          FLASH5_RS1_SRP1_ENABLE );
    flash5_write_status_data( &flash5, FLASH5_CMD_WRITE_REG_STATUS1, FLASH5_REG_STATUS_1, FLASH5_RS2_PAGE_READ_MODE );
    Delay_ms( 1000 );
    
    log_printf( &logger, "***** App init ***** \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms( 500 );
}

void application_task ( )
{
    char read_buf[ 6 ];
    uint8_t n_counter;

    flash5_send_cmd( &flash5, FLASH5_CMD_WRITE_ENABLE );
    flash5_page_load_memory( &flash5, 0x000A, &write_buf[ 0 ], 6 );
    flash5_page_read_memory( &flash5, 0x000A, &read_buf[ 0 ], 6 );

    for( n_counter = 0; n_counter < 6; n_counter++ )
    {
        log_printf( &logger, " %c ", read_buf[ n_counter ] );
        Delay_ms( 100 );
    }
    
    log_printf( &logger, " \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms( 5000 );
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
