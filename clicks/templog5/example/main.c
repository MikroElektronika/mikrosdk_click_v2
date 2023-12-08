/*!
 * \file 
 * \brief TempLog5 Click example
 * 
 * # Description
 * This Click measures and stores temperatures at least 10 times in second, 
 * allowing it to be retrieved by the host MCU via the I2C interface. 
 * The result can be compared to critical limits, stored into internal registers. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, Test comunication, EEPROM write/read test and
 * configuration device for measurement.
 * 
 * ## Application Task  
 * Reads Temperature data and logs data to the USBUART every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "templog5.h"

// ------------------------------------------------------------------ VARIABLES

static templog5_t templog5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    templog5_cfg_t cfg;
    uint16_t tmp;
    uint8_t ee_test_write[1];
    uint8_t ee_test_read[1];

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

    templog5_cfg_setup( &cfg );
    TEMPLOG5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    templog5_init( &templog5, &cfg );

    tmp = templog5_read_data( &templog5, TEMPLOG5_REG_MANUFACTURER_ID );

    if ( tmp == TEMPLOG5_MANUFACTURER_ID )
    {
        log_info( &logger, "Comunication OK!!!" );
    }
    else
    {
        log_info( &logger, "Comunication ERROR!!!" );
        while( 1 );
    }
   
    ee_test_write[ 0 ] = 0xAA;
    templog5_write_eeprom( &templog5, 0x10, &ee_test_write[ 0 ], 1 );
    Delay_ms( 200 );
    
    templog5_read_eeprom( &templog5, 0x10, &ee_test_read[ 0 ], 1 );
 
    log_info( &logger," EEPROM TEST READ:  %u\r\n", ee_test_read[ 0 ] ); 

    templog5_default_cfg ( &templog5 );
}

void application_task ( void )
{
    float temperature;

    temperature = templog5_get_temperature( &templog5 );
    log_info( &logger,"Temperature:  %.2f\r\n", temperature );
    Delay_ms( 1000 );
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
