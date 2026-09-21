/*!
 * @file main.c
 * @brief Thermocouple Click example
 *
 * # Description
 * This example demonstrates the use of the Thermocouple Click board for
 * temperature measurement using thermocouple sensors. The application
 * alternates between two channels, reading temperature values from
 * different thermocouple types, and also retrieves ambient and delta
 * temperatures.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Thermocouple Click driver, and applies the
 * default configuration.
 *
 * ## Application Task
 * Configures the active thermocouple channel, waits for measurement
 * completion, reads hot junction temperature, ambient temperature,
 * and delta temperature, and logs the results while alternating between channels.
 *
 * @note
 * Thermocouple connections:
 * - Connect the Type K thermocouple to channel CH1 input terminals on the Click board.
 * - Connect the Type J thermocouple to channel CH2 input terminals on the Click board.
 * Ensure correct polarity when connecting thermocouples (positive and negative leads).
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermocouple.h"

#ifndef MIKROBUS_POSITION_THERMOCOUPLE
    #define MIKROBUS_POSITION_THERMOCOUPLE MIKROBUS_1
#endif

static thermocouple_t thermocouple;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermocouple_cfg_t thermocouple_cfg;  /**< Click config object. */

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
    thermocouple_cfg_setup( &thermocouple_cfg );
    THERMOCOUPLE_MAP_MIKROBUS( thermocouple_cfg, MIKROBUS_POSITION_THERMOCOUPLE );
    if ( THERMOCOUPLE_ERROR == thermocouple_init( &thermocouple, &thermocouple_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMOCOUPLE_ERROR == thermocouple_default_cfg ( &thermocouple ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t active_channel = THERMOCOUPLE_CHANNEL_1;
    err_t error_flag = THERMOCOUPLE_OK;
    float tc_temp = 0;
    float amb_temp = 0;
    float delta_temp = 0;
    uint32_t timeout = 0;
    uint8_t status = 0;

    if ( THERMOCOUPLE_CHANNEL_1 == active_channel )
    {
        error_flag = thermocouple_set_sensor_cfg( &thermocouple,
                                                  active_channel,
                                                  THERMOCOUPLE_TYPE_K,
                                                  THERMOCOUPLE_FILTER_OFF );
    }
    else
    {
        error_flag = thermocouple_set_sensor_cfg( &thermocouple,
                                                  active_channel,
                                                  THERMOCOUPLE_TYPE_J,
                                                  THERMOCOUPLE_FILTER_OFF );
    }
    Delay_ms ( 10 );

    if ( THERMOCOUPLE_OK == error_flag )
    {
        while ( ( THERMOCOUPLE_STATUS_TH_UPDATE != ( status & THERMOCOUPLE_STATUS_TH_UPDATE ) ) && 
                ( ++timeout < THERMOCOUPLE_STATUS_TIMEOUT ) )
        {
            thermocouple_get_status ( &thermocouple, &status );
            Delay_ms ( 1 );
        }
        error_flag = thermocouple_get_hot_junction( &thermocouple, &tc_temp );
        error_flag |= thermocouple_clear_status( &thermocouple );
    }

    if ( THERMOCOUPLE_OK == error_flag )
    {
        if ( THERMOCOUPLE_CHANNEL_1 == active_channel )
        {
            log_printf( &logger, " CH1 Type K: %.2f C\r\n", tc_temp );
            active_channel = THERMOCOUPLE_CHANNEL_2;
        }
        else
        {
            log_printf( &logger, " CH2 Type J: %.2f C\r\n", tc_temp );
            active_channel = THERMOCOUPLE_CHANNEL_1;
        }
        error_flag |= thermocouple_get_cold_junction( &thermocouple, &amb_temp );
        log_printf( &logger, " Ambient Temp: %.2f C\r\n", amb_temp );
        error_flag |= thermocouple_get_delta_temp( &thermocouple, &delta_temp );
        log_printf( &logger, " Delta Temp: %.2f C\r\n\n", delta_temp );
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
