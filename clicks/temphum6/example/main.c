/*!
 * \file 
 * \brief TempHum6 Click example
 * 
 * # Description
 * This application emasures temperature and humidity.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and reset device and read Part ID
 * 
 * ## Application Task  
 * Reads Temperature and Huminidy data and logs this data to USBUART every 1sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum6.h"

// ------------------------------------------------------------------ VARIABLES

static temphum6_t temphum6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum6_cfg_t cfg;
    uint16_t part_id;

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

    temphum6_cfg_setup( &cfg );
    TEMPHUM6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum6_init( &temphum6, &cfg );

    temphum6_reset( &temphum6 );
    
    part_id = temphum6_get_part_id( &temphum6 );
    if ( part_id == TEMPHUM6_PART_ID )
    {
        log_printf( &logger, "Device OK - read ID is OK  0x%x\r\n", part_id );
    }
    else
    {
        log_printf( &logger, "Device ERROR - read ID is NOT OK 0x%x\r\n", part_id  );
        for ( ; ; );
    }
}

void application_task ( void )
{
    //  Task implementation.

    float temp;
    float hum;

    temp = temphum6_read_temperature( &temphum6, TEMPHUM6_TEMP_IN_CELSIUS );
    log_printf( &logger, "Temperature is %.2f C\r\n", temp );
    
    hum = temphum6_read_relative_huminidy( &temphum6 );
    log_printf( &logger, "Huminidy is %.2f %%RH\r\n", hum );
    
    log_printf( &logger, "------------------\r\n");
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
