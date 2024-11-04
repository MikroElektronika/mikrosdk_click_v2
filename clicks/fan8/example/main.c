/*!
 * @file main.c
 * @brief FAN8 Click example
 *
 * # Description
 * This example demonstrates the use of FAN 8 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Changes the speed of fans at both channels by changing the PWM duty cycle, then calculates 
 * the fans RPM from measured tachometer signal. It also reads the temperature of two thermistors.
 * The results are being displayed via USB UART where you can track their changes.
 * 
 * @note
 * The MAX6615 measures the tachometer signal every 67s, therefore 
 * the fan RPM value will be updated once per 67s.
 * An NTC 10K3 thermistor is required for proper temperature measurements.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "fan8.h"

static fan8_t fan8;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;    /**< Logger config object. */
    fan8_cfg_t fan8_cfg;  /**< Click config object. */

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
    fan8_cfg_setup( &fan8_cfg );
    FAN8_MAP_MIKROBUS( fan8_cfg, MIKROBUS_1 );
    err_t init_flag = fan8_init( &fan8, &fan8_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag = fan8_default_cfg ( &fan8 );
    if ( FAN8_ERROR == init_flag ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t duty_cnt = FAN8_MIN_DUTY_CYCLE;
    static int8_t duty_inc = FAN8_DUTY_CYCLE_STEP_10;
    uint16_t fan_rpm = 0;
    float temperature = 0;

    if ( duty_cnt == FAN8_MAX_DUTY_CYCLE )
    {
        duty_inc = -FAN8_DUTY_CYCLE_STEP_10;
    }
    else if ( duty_cnt == ( FAN8_MIN_DUTY_CYCLE + FAN8_DUTY_CYCLE_STEP_10 ) )
    {
        duty_inc = FAN8_DUTY_CYCLE_STEP_10;
    }
    duty_cnt += duty_inc;

    log_printf( &logger, " - Channel 1 values -\r\n" );
    fan8_set_duty_cycle ( &fan8, FAN8_FAN_CHANNEL_1, duty_cnt );
    log_printf( &logger, " PWM Duty Cycle : %d\r\n", ( uint16_t ) duty_cnt );
    fan8_measure_rpm ( &fan8, FAN8_FAN_CHANNEL_1, FAN8_2_PULSES_PER_REVOLUTION, &fan_rpm );
    log_printf( &logger, " Last measured fan RPM : %u\r\n", fan_rpm );
    fan8_read_temperature ( &fan8, FAN8_TEMP_CHANNEL_1, &temperature );
    log_printf( &logger, " Temperature : %.2f C\r\n\r\n", temperature );

    log_printf( &logger, " - Channel 2 values -\r\n" );
    fan8_set_duty_cycle ( &fan8, FAN8_FAN_CHANNEL_2, duty_cnt );
    log_printf( &logger, " PWM Duty Cycle : %d\r\n", ( uint16_t ) duty_cnt );
    fan8_measure_rpm ( &fan8, FAN8_FAN_CHANNEL_2, FAN8_2_PULSES_PER_REVOLUTION, &fan_rpm );
    log_printf( &logger, " Last measured fan RPM : %u\r\n", fan_rpm );
    fan8_read_temperature ( &fan8, FAN8_TEMP_CHANNEL_2, &temperature );
    log_printf( &logger, " Temperature : %.2f C\r\n\r\n", temperature );

    if ( !fan8_check_fault_indicator ( &fan8 ) )
    {
        log_printf( &logger, " Fault detected!\r\n\r\n", temperature );
    }

    Delay_ms ( 500 );
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
