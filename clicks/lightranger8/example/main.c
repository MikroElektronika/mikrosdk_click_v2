/*!
 * @file main.c
 * @brief LightRanger8 Click example
 *
 * # Description
 * This demo application shows an example of distance
 * measurement via VL53L3 ranging sensor.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module, log UART and additional pins.
 * After driver init, the app powers the device and performs
 * default settings of the ranging sensor including distance
 * mode and timing budget. The optional calibration helps
 * improvement of the accuracy on the targeted distance.
 * This process takes 10 second ( which can by modifed by
 * simply lowering the Delay_ms( 5000 ) value ) so the user can
 * place an object on the exact location. When calibration is
 * finished, device starts the measurement with intermeasurement
 * period set by the user.
 *
 * ## Application Task
 * A new data ready is checked as soon as possible which signals
 * the time required for the ranging sensor to perform the
 * measurement. An acqured distance is shown on the LOG with
 * the 2 seconds delay so the terminal is possible to read.
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "lightranger8.h"

static lightranger8_t lightranger8;
static log_t logger;

static int16_t offset;
static uint16_t period_ms = 100;
static uint32_t budget_us = 1000000;
static int16_t calibration_distance_mm = 100;

void application_init ( void ) {
    log_cfg_t log_cfg;                           /**< Logger config object. */
    lightranger8_cfg_t lightranger8_cfg;         /**< Click config object. */

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

    lightranger8_cfg_setup( &lightranger8_cfg );
    LIGHTRANGER8_MAP_MIKROBUS( lightranger8_cfg, MIKROBUS_1 );
    err_t init_flag = lightranger8_init( &lightranger8, &lightranger8_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    lightranger8_power_on( &lightranger8 );
    log_printf( &logger, " Wait until the configuration of the chip is completed...\r\n" );
    if ( lightranger8_default_cfg( &lightranger8 ) != 0 ) {
        log_error( &logger, " Sensor config error. " );
        for ( ; ; );
    }
    lightranger8_set_distance_mode( &lightranger8, LIGHTRANGER8_DISTANCE_MODE_MEDIUM );
    lightranger8_set_measurement_timing_budget( &lightranger8, budget_us );
    Delay_ms( 1000 );

    log_printf( &logger, " -------------------------------------------------------------------------\r\n" );
    log_printf( &logger, " For calibration place an object at %.1f cm distance from sensor.\r\n", ( float )calibration_distance_mm / 10 );
    Delay_ms( 5000 );
    log_printf( &logger, " -------------------------------------------------------------------------\r\n" );
    log_printf( &logger, " ---------------    Sensor calibration is in progress...     ---------------\r\n" );
    Delay_ms( 5000 );
    lightranger8_calibrate_offset( &lightranger8, calibration_distance_mm, period_ms, &offset );
    Delay_ms( 500 );
    
    lightranger8_start_measurement( &lightranger8, period_ms );
    log_printf( &logger, " -------------------------------------------------------------------------\r\n" );
    log_printf( &logger, " -------------    Sensor measurement commencing...    -------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) {
    uint16_t distance;
    
    while ( lightranger8_get_interrupt_state( &lightranger8 ) != 0 ) {
        Delay_1ms();
    }

    distance = lightranger8_get_distance( &lightranger8 );
    log_printf( &logger, " ----------------------\r\n" );
    log_printf( &logger, " Distance: %.1f cm \r\n", ( float )distance / 10 );
    lightranger8_system_interrupt_clear ( &lightranger8 );
    Delay_ms( 2000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
