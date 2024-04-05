/*!
 * \file 
 * \brief Airquality5 Click example
 * 
 * # Description
 * This application can detect gas pollution for a number of different gases.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device and configuration chip.
 * 
 * ## Application Task  
 * Reads the values of CO, NH3 and NO2 sensor and logs data on USBUART every 500ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "airquality5.h"

// ------------------------------------------------------------------ VARIABLES

static airquality5_t airquality5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality5_cfg_t cfg;
    airquality5.data_config = 0x8583;

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

    airquality5_cfg_setup( &cfg );
    AIRQUALITY5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality5_init( &airquality5, &cfg );
}

void application_task ( void )
{
    //  Task implementation.

    uint16_t NO2_sensor_data;
    uint16_t NH3_sensor_data;
    uint16_t CO_sensor_data;
 
    CO_sensor_data = airq5_read_sensor_data( &airquality5, AIRQ5_DATA_CHANNEL_CO );
      
    NO2_sensor_data = airq5_read_sensor_data( &airquality5, AIRQ5_DATA_CHANNEL_NO2 );
    log_printf( &logger, " NO2 data: %d\r\n", NO2_sensor_data );
      
    NH3_sensor_data = airq5_read_sensor_data( &airquality5, AIRQ5_DATA_CHANNEL_NH3 );
    log_printf( &logger, " NH3 data: %d\r\n", NH3_sensor_data );
     
    CO_sensor_data = airq5_read_sensor_data( &airquality5, AIRQ5_DATA_CHANNEL_CO );
    log_printf( &logger," CO data: %d\r\n", CO_sensor_data );
     
    log_printf( &logger, " -------- ");
    Delay_ms ( 200 );
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
