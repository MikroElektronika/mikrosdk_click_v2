/*!
 * @file main.c
 * @brief Temp Alarm Click example
 *
 * # Description
 * This example demonstrates the use of Temp Alarm click board by reading and displaying
 * the temperature measurements and monitoring it.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the Local sensor critical temperature at 30 degC with hysteresis of 1 degC,
 * and Remote sensor alarm temperature at 30 degC.
 *
 * ## Application Task
 * Reads the temperature measurement in degrees Celsius and displays the results on the USB UART
 * approximately once per second. Monitoring alarm and critical state.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "tempalarm.h"

static tempalarm_t tempalarm;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tempalarm_cfg_t tempalarm_cfg;  /**< Click config object. */

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
    tempalarm_cfg_setup( &tempalarm_cfg );
    TEMPALARM_MAP_MIKROBUS( tempalarm_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == tempalarm_init( &tempalarm, &tempalarm_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPALARM_ERROR == tempalarm_default_cfg ( &tempalarm ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t flag_data = 0; 
    int8_t local_temp = 0;
    float remote_temp = 0;
    tempalarm_get_alarms( &tempalarm, &flag_data );
    if ( TEMPALARM_ADC_BUSY_MASK != ( TEMPALARM_ADC_BUSY_MASK & flag_data ) )
    {
        tempalarm_read_temperature( &tempalarm, &local_temp );
        tempalarm_read_remote_temp( &tempalarm, &remote_temp );
        log_printf( &logger, " Local temperature : %d degC \r\n" , ( int16_t ) local_temp );
        log_printf( &logger, " Remote temperature : %.3f degC \r\n" , remote_temp );
        log_printf( &logger, " -------------------------------- \r\n" );
    }
    if ( TEMPALARM_PIN_STATE_LOW == tempalarm_get_alr_pin( &tempalarm ) )
    {
        log_printf( &logger, " Alarm is on, remote temperature  \r\n" );
        log_printf( &logger, "      is higher then 30 degC      \r\n" );
        log_printf( &logger, " -------------------------------- \r\n" );
    }
    if ( TEMPALARM_PIN_STATE_LOW == tempalarm_get_tcr_pin( &tempalarm ) )
    {
        log_printf( &logger, " Alarm is on, local temperature  \r\n" );
        log_printf( &logger, "      is higher then 30 degC      \r\n" );
        log_printf( &logger, " -------------------------------- \r\n" );
    }
    Delay_ms( 1000 );
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
