/*!
 * \file 
 * \brief TempHum10 Click example
 * 
 * # Description
 * This application measures temperature and humidity.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and sets device mode
 * 
 * ## Application Task  
 * Reads Temperature and Humidity data and logs this data to USBUART every 1 sec.
 * 
 *  ## NOTE
 * If you are expiriencing issues with comunication, please try another mikroBUS socket or set the VCC SEL jumper at 5V.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum10.h"

// ------------------------------------------------------------------ VARIABLES

static temphum10_t temphum10;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum10_cfg_t cfg;
    uint8_t tmp;

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

    temphum10_cfg_setup( &cfg );
    TEMPHUM10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum10_init( &temphum10, &cfg );

    log_info( &logger, "---- Device config ----" );
    
    temphum10_set_device_mode( &temphum10, TEMPHUM10_MODE_STANDBY );
    Delay_ms ( 100 );
    
    tmp = TEMPHUM10_RST_NORMAL_OPERATION;
    temphum10_generic_write( &temphum10, TEMPHUM10_REG_DEVICE_RESET, &tmp, 1 );
    Delay_ms ( 100 );
    log_info( &logger, "---- Device calibration ----" );
    tmp = TEMPHUM10_AM_TIMES_AVERAGE_MODE_8 | TEMPHUM10_AM_TEMP_AVERAGE_MODE_TIMES_16;
    temphum10_repeat_measurement( &temphum10, tmp );
    temphum10_get_temperature( &temphum10 );
    temphum10_get_humidity( &temphum10 );
    Delay_ms ( 100 );
    temphum10_repeat_measurement( &temphum10, tmp );
    temphum10_get_temperature( &temphum10 );
    temphum10_get_humidity( &temphum10 );
    log_info( &logger, "---- Application Task ----" );
}

void application_task ( )
{
    float temperature = 0;
    float humidity = 0;
    uint8_t tmp;
    
    tmp = TEMPHUM10_AM_TIMES_AVERAGE_MODE_8 | TEMPHUM10_AM_TEMP_AVERAGE_MODE_TIMES_16;
    temphum10_repeat_measurement( &temphum10, tmp );
    temperature = temphum10_get_temperature( &temphum10 );
    humidity = temphum10_get_humidity( &temphum10 );
    
    log_printf( &logger, " Temperature : %.2f \r\n", temperature );
    log_printf( &logger, " Humidity :  %.2f \r\n", humidity );
    log_printf( &logger, "---------------------\r\n" );

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
