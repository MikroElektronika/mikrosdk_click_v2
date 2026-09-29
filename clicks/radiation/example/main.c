/*!
 * @file main.c
 * @brief Radiation Click Example.
 *
 * # Description
 * This example demonstrates the use of the Radiation Click board by counting the pulses
 * that the BG51 sensor generates for each detected radiation event and converting
 * the average count rate to the radiation dose rate.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Counts the sensor pulses in consecutive one-minute windows and displays the number of
 * pulses in the last window, as well as the average count rate [CPM] and dose rate [uSv/h]
 * calculated from all windows since the start, on the USB UART.
 *
 * @note
 * The dose rate is calculated from the BG51 sensitivity of 5 CPM for 1 uSv/h (+/-15%),
 * (BG51 datasheet, page 2).
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "radiation.h"

#ifndef MIKROBUS_POSITION_RADIATION
    #define MIKROBUS_POSITION_RADIATION MIKROBUS_1
#endif

static radiation_t radiation;   /**< Radiation Click driver object. */
static log_t logger;    /**< Logger object. */

// Application demo makros
static uint32_t total_pulses = 0; 
static uint32_t minute_cnt = 0;   

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    radiation_cfg_t radiation_cfg;  /**< Click config object. */

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
    radiation_cfg_setup( &radiation_cfg );
    RADIATION_MAP_MIKROBUS( radiation_cfg, MIKROBUS_POSITION_RADIATION );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == radiation_init( &radiation, &radiation_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint32_t pulse_cnt = 0;
    float avg_cpm = 0;

    if ( RADIATION_OK == radiation_count_pulses( &radiation, RADIATION_ONE_MINUTE_MS, &pulse_cnt ) )
    {
        total_pulses += pulse_cnt;
        minute_cnt++;
        avg_cpm = ( float ) total_pulses / minute_cnt;

        log_printf( &logger, " Minute: %lu\r\n", minute_cnt );
        log_printf( &logger, " Last minute: %lu CPM -> %.2f uSv/h\r\n", pulse_cnt, ( float ) pulse_cnt / RADIATION_CPM_PER_USV_H );                    
        log_printf( &logger, " Average: %.2f CPM -> %.2f uSv/h\r\n", avg_cpm, avg_cpm / RADIATION_CPM_PER_USV_H );                    
        log_printf( &logger, "--------------------------------\r\n" );
    }
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
