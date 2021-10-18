/*!
 * @file main.c
 * @brief HeartRate10 Click example
 *
 * # Description
 * This example showcases ability for device to read Heart Rate with 4 different diodes.
 * There is IR, Red, Green and Blue. You can control every one of them individualy, and 
 * change theirs sequence in FIFO register. All leds data is read from FIFO register, 
 * it's 19bit data for every led.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of host communication periphrials and interrupt pin. Configures default
 * configuration to device where device is reset, checks Part ID and enables all 4 leds 
 * and sets sequence as IR-Red-Green-Blue. Sets their power to maximum, and enables 
 * interrupt on new data ready.
 *
 * ## Application Task
 * Reads FIFO data for all 4 didoes and logs them with separation character ','.
 *
 * @note
 * For testing this example application SerialPlot was used. 
 * There you can see heart rate graphicly shown.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "heartrate10.h"

static heartrate10_t heartrate10;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate10_cfg_t heartrate10_cfg;  /**< Click config object. */

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

    // Click initialization.
    heartrate10_cfg_setup( &heartrate10_cfg );
    HEARTRATE10_MAP_MIKROBUS( heartrate10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate10_init( &heartrate10, &heartrate10_cfg ) ) 
    {
        log_error( &logger, " Initializtion." );
        log_info( &logger, " Please, run example again... " );

        for ( ; ; );
    }
    
    if ( HEARTRATE10_ERROR == heartrate10_default_cfg ( &heartrate10 ) ) 
    {
        log_error( &logger, " Configuration." );
        log_info( &logger, " Please, run example again... " );

        for ( ; ; );
    }
}

void application_task ( void ) 
{   
    uint8_t rd_dat = 0;
    heartrate10_generic_read( &heartrate10, HEARTRATE10_REG_INT_STATUS, &rd_dat );
    if ( ( rd_dat & 0x40 ) )
    {        
        uint32_t ir, red, green, blue = 0;
        heartrate10_read_complete_fifo_data( &heartrate10, &ir, &red, &green, &blue );
        log_printf( &logger, "%lu,%lu,%lu,%lu\r\n", ir, red, green, blue );
    }
    Delay_ms( 3 );
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
