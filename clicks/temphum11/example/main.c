/*!
 * \file 
 * \brief TempHum11 Click example
 * 
 * # Description
 * This Click has two sensors which can be set to sample measurements with the resolution 
 * of 8, 11 or 14 bits, based on the measurement time. Calibration coefficients that are applied 
 * to the measured value and the results are stored in the MSB/LSB format, on the output registers. 
 * These values are then used in formulas so that the final temperature or relative humidity data can be calculated.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, test comunication and configuration chip for measurement.
 * 
 * ## Application Task  
 * Reads Temperature and Humidity data. This data logs to USBUART every 1500ms.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum11.h"

// ------------------------------------------------------------------ VARIABLES

static temphum11_t temphum11;
static log_t logger;

static float temperature;
static float humidity;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum11_cfg_t cfg;

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

    temphum11_cfg_setup( &cfg );
    TEMPHUM11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum11_init( &temphum11, &cfg );

    // Test comunication

    if ( temphum11_read_data( &temphum11, TEMPHUM11_REG_DEVICE_ID ) == TEMPHUM11_DEVICE_ID )
    {
        log_printf( &logger, "--- Comunication OK!!! ---\r\n" );
    }
    else
    {
        log_printf( &logger, "--- Comunication ERROR!!! ---\r\n" );
        for ( ; ; );
    }

    temphum11_default_cfg( &temphum11 );
    log_printf( &logger, "--- Start measurement --- \r\n" );
    Delay_ms ( 500 );
}

void application_task ( void )
{
    temperature = temphum11_get_temperature( &temphum11, TEMPHUM11_TEMP_IN_CELSIUS );
    
    log_printf( &logger, " Temperature : %.2f\r\n", temperature );
    
    humidity = temphum11_get_humidity( &temphum11 );
    
    log_printf( &logger, " Humidity :  %.2f\r\n", humidity );
    
    log_printf( &logger, "-----------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
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
