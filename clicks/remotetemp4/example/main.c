/*!
 * @file main.c
 * @brief Remote Temp 4 Click example
 *
 * # Description
 * This example demonstrates the use of Remote Temp 4 Click board by reading
 * and displaying the temperature measurements from the local and remote
 * channels, and monitoring the ALERT and THERM temperature alarm states.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the temperature measurements in degrees Celsius from both the local
 * sensor and the remote channel, and displays the results on the USB UART
 * approximately once per second. Also monitors and reports the ALERT and THERM
 * alarm states.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "remotetemp4.h"

#ifndef MIKROBUS_POSITION_REMOTETEMP4
    #define MIKROBUS_POSITION_REMOTETEMP4 MIKROBUS_1
#endif

static remotetemp4_t remotetemp4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    remotetemp4_cfg_t remotetemp4_cfg;  /**< Click config object. */

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
    remotetemp4_cfg_setup( &remotetemp4_cfg );
    REMOTETEMP4_MAP_MIKROBUS( remotetemp4_cfg, MIKROBUS_POSITION_REMOTETEMP4 );
    if ( I2C_MASTER_ERROR == remotetemp4_init( &remotetemp4, &remotetemp4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( REMOTETEMP4_ERROR == remotetemp4_default_cfg ( &remotetemp4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t status = 0;
    float local_temp = 0;
    float remote_temp = 0;

    remotetemp4_read_local_temp( &remotetemp4, &local_temp );
    remotetemp4_read_remote_temp( &remotetemp4, &remote_temp );

    log_printf( &logger, " Local  temperature : %.3f degC \r\n", local_temp );
    log_printf( &logger, " Remote temperature : %.3f degC \r\n", remote_temp );
    log_printf( &logger, " ------------------------------ \r\n" );

    if ( !remotetemp4_get_alr_pin( &remotetemp4 ) )
    {
        remotetemp4_get_status( &remotetemp4, &status );
        if ( REMOTETEMP4_STATUS_REMOTE_OPEN & status )
        {
            log_printf( &logger, " Fault - remote diode is open or disconnected \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( REMOTETEMP4_STATUS_LOCAL_HIGH & status )
        {
            log_printf( &logger, " Alert - local temperature is above 30 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( REMOTETEMP4_STATUS_REMOTE_HIGH & status )
        {
            log_printf( &logger, " Alert - remote temperature is above 30 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( REMOTETEMP4_STATUS_REMOTE_LOW & status )
        {
            log_printf( &logger, " Alert - remote temperature is below 0 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
    }

    if ( !remotetemp4_get_thm_pin( &remotetemp4 ) )
    {
        remotetemp4_get_status( &remotetemp4, &status );
        if ( REMOTETEMP4_STATUS_LOCAL_THERM & status )
        {
            log_printf( &logger, " THERM - local temperature exceeded 30 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( REMOTETEMP4_STATUS_REMOTE_THERM & status )
        {
            log_printf( &logger, " THERM - remote temperature exceeded 30 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
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
