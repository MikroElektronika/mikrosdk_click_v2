/*!
 * @file main.c
 * @brief Temp Alarm 2 Click example
 *
 * # Description
 * This example demonstrates the use of Temp Alarm 2 Click board by reading
 * and displaying the temperature measurements from the local sensor and 
 * the remote channel sensor, and monitoring the ALERT and THERM
 * temperature alarm states.
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
 * alarm states via the ALT pin and the status register.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "tempalarm2.h"

#ifndef MIKROBUS_POSITION_TEMPALARM2
    #define MIKROBUS_POSITION_TEMPALARM2 MIKROBUS_1
#endif

static tempalarm2_t tempalarm2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tempalarm2_cfg_t tempalarm2_cfg;  /**< Click config object. */

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
    tempalarm2_cfg_setup( &tempalarm2_cfg );
    TEMPALARM2_MAP_MIKROBUS( tempalarm2_cfg, MIKROBUS_POSITION_TEMPALARM2 );
    if ( I2C_MASTER_ERROR == tempalarm2_init( &tempalarm2, &tempalarm2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPALARM2_ERROR == tempalarm2_default_cfg ( &tempalarm2 ) )
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

    tempalarm2_read_local_temp( &tempalarm2, &local_temp );
    tempalarm2_read_remote_temp( &tempalarm2, &remote_temp );

    log_printf( &logger, " Local  temperature : %.4f degC \r\n", local_temp );
    log_printf( &logger, " Remote temperature : %.4f degC \r\n", remote_temp );
    log_printf( &logger, " ------------------------------ \r\n" );
    
    /* Status flags are latched => read the status register in order to update them */
    tempalarm2_get_status( &tempalarm2, &status );

    if ( !tempalarm2_get_alt_pin( &tempalarm2 ) )
    {
        if ( TEMPALARM2_STATUS_LHIGH & status )
        {
            log_printf( &logger, " Alert - local temperature is above 28 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( TEMPALARM2_STATUS_RHIGH & status )
        {
            log_printf( &logger, " Alert - remote temperature is above 28 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( TEMPALARM2_STATUS_LLOW & status )
        {
            log_printf( &logger, " Alert - local temperature is below 0 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( TEMPALARM2_STATUS_RLOW & status )
        {
            log_printf( &logger, " Alert - remote temperature is below 0 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( TEMPALARM2_STATUS_OPEN & status )
        {
            log_printf( &logger, " Alert - remote sensor open circuit detected \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }

        /* Alert pin is also latched.
         * Send Alert Response Address command to reset it only if status flags confirm
         * that the temperature is back under high limit or above low limit =>
         * "Condition for Alert is over but the pin is still latched" */
        if ( !( status & ( TEMPALARM2_STATUS_LHIGH | TEMPALARM2_STATUS_RHIGH | 
                           TEMPALARM2_STATUS_LLOW  | TEMPALARM2_STATUS_RLOW  | 
                           TEMPALARM2_STATUS_OPEN ) ) )
        {
            tempalarm2_clear_alert( &tempalarm2 );
        }
    }

    if ( TEMPALARM2_STATUS_RTHRM & status )
    {
        log_printf( &logger, " THERM - remote temperature exceeded 30 degC \r\n" );
        log_printf( &logger, " ------------------------------ \r\n" );
    }
    if ( TEMPALARM2_STATUS_LTHRM & status )
    {
        log_printf( &logger, " THERM - local temperature exceeded 30 degC \r\n" );
        log_printf( &logger, " ------------------------------ \r\n" );
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
