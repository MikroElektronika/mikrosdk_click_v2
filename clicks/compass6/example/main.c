/*!
 * @file main.c
 * @brief Compass6 Click example
 *
 * # Description
 * This example is a showcase the ability of the device
 * to read 3 axis data of magnetic raw value when data is ready.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules (I2C, UART) and data 
 * ready pin as input. Then reads identification data and checks 
 * if some of them have wrong value, and configures device for reading.
 *
 * ## Application Task
 * Checks Data ready pin and if asserted high it will read data of all
 * 3 axes(x, y, z) and log data to Terminal and set delay of 500ms.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "compass6.h"

static compass6_t compass6;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    compass6_cfg_t compass6_cfg;  /**< Click config object. */

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

    // Click initialization.
    compass6_cfg_setup( &compass6_cfg );
    COMPASS6_MAP_MIKROBUS( compass6_cfg, MIKROBUS_1 );
    err_t init_flag = compass6_init( &compass6, &compass6_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint8_t temp_data = 0;
    compass6_generic_read( &compass6, COMPASS6_REG_WHO_I_AM, &temp_data );
    log_printf( &logger, " > Who am I: 0x%.2X\r\n", ( uint16_t )temp_data );
    if ( COMPASS6_WHO_AM_I != temp_data )
    {
        log_error( &logger, " Who am I. " );
    }
    
    compass6_generic_read( &compass6, COMPASS6_REG_INFO_VERSION, &temp_data );
    log_printf( &logger, " > Version: 0x%.2X\r\n", ( uint16_t )temp_data );
    if ( COMPASS6_VERSION != temp_data )
    {
        log_error( &logger, " Version. " );
    }
    
    compass6_generic_read( &compass6, COMPASS6_REG_INFO_ALPS, &temp_data );
    log_printf( &logger, " > ALPS: 0x%.2X\r\n", ( uint16_t )temp_data );
    if ( COMPASS6_ALPS != temp_data )
    {
        log_error( &logger, " ALPS. " );
    }

    compass6_default_cfg ( &compass6 );
    
    log_info( &logger, " Application Task " );
    Delay_ms( 2000 );
}

void application_task ( void ) 
{
    if ( compass6_data_ready( &compass6 ) )
    {      
        compass6_axes_t axes_data;
        compass6_get_axes_data( &compass6, &axes_data );
        log_printf( &logger, " > X: %d\r\n", axes_data.x );
        log_printf( &logger, " > Y: %d\r\n", axes_data.y );
        log_printf( &logger, " > Z: %d\r\n", axes_data.z );
        log_printf( &logger, "*********************\r\n" );
        Delay_ms( 500 );
    }
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
