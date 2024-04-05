/*!
 * @file main.c
 * @brief Speed Sense Click Example.
 *
 * # Description
 * This library contains the API for the Speed Sense Click driver 
 * for the speed and direction signal state detection for every magnetic pole pair.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO and log UART.
 *
 * ## Application Task
 * This example demonstrates the use of the Speed Sense Click board. 
 * The demo application displays the direction of movement and rotation speed (rotations per minute) 
 * of the ring magnet with three pairs of rotating poles positioned in the sensor operating range.
 *
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "speedsense.h"

#define SPEEDSENSE_MAG_POLE_PAIRS    3
#define SPEEDSENSE_CALC_RMP          SPEEDSENSE_CNV_MIN_TO_MS / SPEEDSENSE_MAG_POLE_PAIRS

uint8_t start_measure = SPEEDSENSE_STOP_MEASURE;
uint32_t time_cnt = 0;
uint32_t signal_duration = 0;
uint32_t start_timer = 0;

static speedsense_t speedsense;   /**< Speed Sense Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    speedsense_cfg_t speedsense_cfg;  /**< Click config object. */

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
    speedsense_cfg_setup( &speedsense_cfg );
    SPEEDSENSE_MAP_MIKROBUS( speedsense_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == speedsense_init( &speedsense, &speedsense_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( void ) 
{
    uint8_t direction = 0, speed = 0;
    speed = speedsense_get_speed( &speedsense );
    direction = speedsense_get_direction( &speedsense );

    if ( start_measure & speed )
    {
        signal_duration = time_cnt - start_timer;
        start_timer = time_cnt;
        
        if ( SPEEDSENSE_DIR_STATE_FWD == direction )
        {
            log_printf( &logger, " Direction: Forward\r\n" );
        }
        else
        {
            log_printf( &logger, " Direction: Reverse\r\n" );
        }
        log_printf( &logger, " Speed: %.2f [rpm]\r\n", SPEEDSENSE_CALC_RMP / signal_duration );
        log_printf( &logger, " Duration: %lu [ms]\r\n", signal_duration );
        log_printf( &logger, " Time: %lu  [ms]\r\n", time_cnt );
        log_printf( &logger, "-----------------------\r\n" );
        start_measure = SPEEDSENSE_STOP_MEASURE;
    }
    else if ( ( !start_measure ) & ( !speed ) )
    {
        start_measure = SPEEDSENSE_START_NEW_MEASURE;
    }

    time_cnt++;
    Delay_ms ( 1 );
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
