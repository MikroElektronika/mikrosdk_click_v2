/*!
 * @file main.c
 * @brief PAC1944 Click example
 *
 * # Description
 * This demo application shows an example of measuring voltage,
 * current and power in a selected part of the circuit. Note that
 * PAC1944 is a high side power monitor, therefore the desired
 * channel should be connected accordingly.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module, log UART and additional pins.
 * In addition, a default configuration is performed as followed:
 * Sample mode is 1024, adaptive accumulation;
 * INT pin is set as an alert;
 * SLW pin is set as slow sampling rate control;
 * All channels are on;
 * Channel 1 is set for bipolar measurements;
 * Channel 2 is set for bipolar measurements reduced by half;
 * Channel 3 and 4 are set for unipolar measurements.
 *
 * ## Application Task
 * The application sends a refresh command which stores the
 * measurement data in registers. Measurements are acquired
 * for voltage, current and power on channel 1 of PAC1944
 * Click board. The last 8 measurements are averaged and
 * calculated in bipolar mode. Process is repeated every
 * two seconds.
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "pac1944.h"

static pac1944_t pac1944;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    pac1944_cfg_t pac1944_cfg;  /**< Click config object. */

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

    pac1944_cfg_setup( &pac1944_cfg );
    PAC1944_MAP_MIKROBUS( pac1944_cfg, MIKROBUS_1 );
    err_t init_flag = pac1944_init( &pac1944, &pac1944_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    pac1944_device_state( &pac1944, PAC1944_DEV_ENABLE );
    Delay_ms ( 100 );
    pac1944_default_cfg ( &pac1944 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) {
    float voltage_sens;
    float current_sens;
    float power_sens;
    
    pac1944_refresh_cmd( &pac1944 );
    
    voltage_sens = pac1944_get_calc_measurement( &pac1944, PAC1944_MEAS_SEL_V_SOURCE,
                                                           PAC1944_CH_SEL_CH_1,
                                                           PAC1944_AVG_SEL_ENABLE,
                                                           PAC1944_MEAS_MODE_BIPOLAR_FSR );
    
    current_sens = pac1944_get_calc_measurement( &pac1944, PAC1944_MEAS_SEL_I_SENSE,
                                                           PAC1944_CH_SEL_CH_1,
                                                           PAC1944_AVG_SEL_ENABLE,
                                                           PAC1944_MEAS_MODE_BIPOLAR_FSR );
    
    power_sens = pac1944_get_calc_measurement( &pac1944,   PAC1944_MEAS_SEL_P_SENSE,
                                                           PAC1944_CH_SEL_CH_1,
                                                           PAC1944_AVG_SEL_ENABLE,
                                                           PAC1944_MEAS_MODE_BIPOLAR_FSR );
    
    
    log_printf( &logger, "  Voltage :  %.6f   V \r\n", voltage_sens );
    log_printf( &logger, "  Current :  %.6f   A \r\n", current_sens );
    log_printf( &logger, "  Power   :  %.6f   W \r\n", power_sens );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 1000 );
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
