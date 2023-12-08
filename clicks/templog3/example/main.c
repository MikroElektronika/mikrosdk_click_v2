/*!
 * \file 
 * \brief TempLog3 Click example
 * 
 * # Description
 * This application measures temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C interface and performs a device default configuration.
 * 
 * ## Application Task  
 * First ensures that the minimum conversion time is met, and then reads the
 * ambient temperature calculated to the Celsius degrees, and logs the results to the USB UART.
 * 
 * @note 
 * The temperature range that can be measured or written is from -40 to +125 Celsius degrees.
 * The user can change the measured temperature resolution, but the range remains the same.
 * The limit of the temperature resolution is always a 10bit, or 0.25 Celsius degrees.
 * If user wants to enable the EEPROM Write Protection, the A0 pin on the device 
 * must be set to the high voltage level.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "templog3.h"

// ------------------------------------------------------------------ VARIABLES

static templog3_t templog3;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void check_limit_status ( uint8_t status )
{   
    if ( ( status & TEMPLOG3_TCRIT_DETECT ) != TEMPLOG3_OK )
    {
        log_printf( &logger, "**  Critical temperature detection!  ** \r\n " );
    }
    if ( ( status & TEMPLOG3_TUPPER_DETECT ) != TEMPLOG3_OK )
    {
        log_printf( &logger,  "**  Ambient temperature is higher than upper limit temperature!  ** \r\n" );
    }
    else if ( ( status & TEMPLOG3_TLOWER_DETECT ) != TEMPLOG3_OK )
    {
        log_printf( &logger,  "**  Ambient temperature is lower than lower limit temperature!  ** \r\n" );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    templog3_cfg_t cfg;

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

    templog3_cfg_setup( &cfg );
    TEMPLOG3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    templog3_init( &templog3, &cfg );

    Delay_ms( 500 );
    
    templog3_default_cfg( &templog3 );
    
    Delay_ms( 200 );

    log_printf( &logger, "** Temp-Log 3 click is initialized ** \r\n" );
}

void application_task ( void )
{
    float temperature;
    uint8_t ret_status;

    templog3_wait_conv_done( &templog3 );

    ret_status = templog3_get_temp( &templog3, TEMPLOG3_TEMP_AMBIENT_REG, &temperature );

    log_printf( &logger, "**  Ambient temperature is : %.2f C  **\r\n", temperature );
    
    check_limit_status( ret_status );
    
    Delay_ms( 300 );
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
