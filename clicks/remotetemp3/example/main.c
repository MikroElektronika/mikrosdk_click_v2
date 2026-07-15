/*!
 * @file main.c
 * @brief Remote Temp 3 Click example
 *
 * # Description
 * This example demonstrates the use of Remote Temp 3 Click board by reading
 * and displaying the temperature measurements from the local sensor and the
 * remote channel sensor, and monitoring the ALERT and THERM temperature alarm states.
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
 * alarm states via the ALR and THM pins.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "remotetemp3.h"

#ifndef MIKROBUS_POSITION_REMOTETEMP3
    #define MIKROBUS_POSITION_REMOTETEMP3 MIKROBUS_1
#endif

static remotetemp3_t remotetemp3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    remotetemp3_cfg_t remotetemp3_cfg;  /**< Click config object. */

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
    remotetemp3_cfg_setup( &remotetemp3_cfg );
    REMOTETEMP3_MAP_MIKROBUS( remotetemp3_cfg, MIKROBUS_POSITION_REMOTETEMP3 );
    if ( I2C_MASTER_ERROR == remotetemp3_init( &remotetemp3, &remotetemp3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( REMOTETEMP3_ERROR == remotetemp3_default_cfg ( &remotetemp3 ) )
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

    remotetemp3_read_local_temp( &remotetemp3, &local_temp );
    remotetemp3_read_remote_temp( &remotetemp3, &remote_temp );

    log_printf( &logger, " Local  temperature : %.4f degC \r\n", local_temp );
    log_printf( &logger, " Remote temperature : %.4f degC \r\n", remote_temp );
    log_printf( &logger, " ------------------------------ \r\n" );

    if ( !remotetemp3_get_alr_pin( &remotetemp3 ) )
    {
        remotetemp3_get_status( &remotetemp3, &status );
        if ( REMOTETEMP3_STATUS_LHIGH & status )
        {
            log_printf( &logger, " Alert - local temperature is above 30 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( REMOTETEMP3_STATUS_RHIGH & status )
        {
            log_printf( &logger, " Alert - remote temperature is above 30 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( REMOTETEMP3_STATUS_LLOW & status )
        {
            log_printf( &logger, " Alert - local temperature is below 0 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( REMOTETEMP3_STATUS_RLOW & status )
        {
            log_printf( &logger, " Alert - remote temperature is below 0 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
    }

    if ( !remotetemp3_get_thm_pin( &remotetemp3 ) )
    {
        remotetemp3_get_status( &remotetemp3, &status );
        if ( REMOTETEMP3_STATUS_RTHRM & status )
        {
            log_printf( &logger, " THERM - remote temperature exceeded 30 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( REMOTETEMP3_STATUS_LTHRM & status )
        {
            log_printf( &logger, " THERM - local temperature exceeded 30 degC \r\n" );
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
