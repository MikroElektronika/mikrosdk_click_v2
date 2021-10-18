/*!
 * @file main.c
 * @brief PAC1954 Click example
 *
 * # Description
 * This example demonstrates the use of PAC1954 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads the voltage, current, and power from Channel 1 and displays all 
 * values on the USB UART once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pac1954.h"

static pac1954_t pac1954;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    pac1954_cfg_t pac1954_cfg;  /**< Click config object. */

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
    pac1954_cfg_setup( &pac1954_cfg );
    PAC1954_MAP_MIKROBUS( pac1954_cfg, MIKROBUS_1 );
    err_t init_flag = pac1954_init( &pac1954, &pac1954_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    pac1954_default_cfg ( &pac1954 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float vsource;
    float isense;
    float power;

    pac1954_refresh_cmd( &pac1954 );
    
    pac1954_get_calc_measurement( &pac1954, PAC1954_MEAS_SEL_V_SOURCE, 
                                            PAC1954_CH_SEL_CH_1, 
                                            PAC1954_AVG_SEL_ENABLE, 
                                            PAC1954_MEAS_MODE_BIPOLAR_FSR,
                                            &vsource );
    pac1954_get_calc_measurement( &pac1954, PAC1954_MEAS_SEL_I_SENSE, 
                                            PAC1954_CH_SEL_CH_1, 
                                            PAC1954_AVG_SEL_ENABLE, 
                                            PAC1954_MEAS_MODE_BIPOLAR_FSR, 
                                            &isense );
    pac1954_get_calc_measurement( &pac1954, PAC1954_MEAS_SEL_P_SENSE, 
                                            PAC1954_CH_SEL_CH_1, 
                                            0, 
                                            PAC1954_MEAS_MODE_BIPOLAR_FSR, 
                                            &power );
    
    log_printf( &logger, " Voltage: %.3f V\r\n", vsource );
    log_printf( &logger, " Current: %.3f A\r\n", isense );
    log_printf( &logger, " Power: %.3f W\r\n", power );
    log_printf( &logger, "---------------------------\r\n" );
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
