/*!
 * @file main.c
 * @brief UNIQUE ID Click example.
 *
 * # Description
 * This example demonstrates the use of UNIQUE ID Click board by reading and 
 * displaying Family Code and Serial Number on the UART Terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes both logger config object and 
 * Click config object.
 *
 * ## Application Task
 * Demonstrates the usage of uniqueid_read_id function,
 * which stores the Family Code and Serial Number of the Click in 
 * family_code and serial_num variables. Both values will be displayed 
 * on the UART Terminal.
 *
 * @author Aleksandra Cvjeticanin
 *
 */

#include "board.h"
#include "log.h"
#include "uniqueid.h"

static uniqueid_t uniqueid;
static log_t logger;


void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uniqueid_cfg_t uniqueid_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization
    uniqueid_cfg_setup( &uniqueid_cfg );
    UNIQUEID_MAP_MIKROBUS( uniqueid_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == uniqueid_init( &uniqueid, &uniqueid_cfg ) ) 
    {
        log_error( &logger, " Initialization error." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t family_code;
    uint8_t serial_num[ 6 ];
    
    if ( UNIQUEID_OK == uniqueid_read_id( &uniqueid, &family_code, &serial_num[ 0 ] ) )
    {
        log_printf( &logger, "Family Code = 0x%.2X\r\n", ( uint16_t ) family_code ); 
        log_printf( &logger, "Serial Number = 0x%.2X%.2X%.2X%.2X%.2X%.2X\r\n", 
                    ( uint16_t ) serial_num[ 0 ], ( uint16_t ) serial_num[ 1 ], 
                    ( uint16_t ) serial_num[ 2 ], ( uint16_t ) serial_num[ 3 ], 
                    ( uint16_t ) serial_num[ 4 ], ( uint16_t ) serial_num[ 5 ] ); 
    }      
    
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
