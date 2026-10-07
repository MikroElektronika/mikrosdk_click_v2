/*!
 * @file main.c
 * @brief PMIC 3 Click example
 *
 * # Description
 * This example demonstrates the use of PMIC 3 Click by detecting the battery
 * and monitoring the input, battery, and system voltages, onboard temperature,
 * and active battery-charger state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger, I2C and ADC interfaces, verifies communication with
 * the PCA9422, starts the PMIC if it is in the OFF state, restores the
 * PCA9422M active regulator voltages and standard 4.2 V charger configuration,
 * enables battery detection and charging, and programs the default charge current.
 *
 * ## Application Task
 * Periodically detects the battery, logs the valid input, battery, and system
 * voltages and onboard temperature, and reports the current battery-charger state.
 *
 * @note
 * Select the required board supply and output jumpers before connecting a
 * battery or load. The example restores the PCA9422M active rail defaults and
 * uses a 4.2 V regulation target with a 200 mA charge current. Temperature is
 * measured by the onboard 10 kOhm NTC thermistor.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pmic3.h"

#ifndef MIKROBUS_POSITION_PMIC3
    #define MIKROBUS_POSITION_PMIC3 MIKROBUS_1
#endif

static pmic3_t pmic3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pmic3_cfg_t pmic3_cfg;  /**< Click config object. */

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
    pmic3_cfg_setup( &pmic3_cfg );
    PMIC3_MAP_MIKROBUS( pmic3_cfg, MIKROBUS_POSITION_PMIC3 );
    if ( I2C_MASTER_ERROR == pmic3_init( &pmic3, &pmic3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PMIC3_ERROR == pmic3_default_cfg ( &pmic3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    pmic3_status_t status = { 0 };
    err_t error_flag = PMIC3_ERROR;
    uint8_t battery_state = PMIC3_BATTERY_UNKNOWN;
    float vin = 0;
    float vbat = 0;
    float vsys = 0;
    float temperature = 0;

    error_flag = pmic3_read_status( &pmic3, &status );
    if ( PMIC3_OK == error_flag )
    {
        error_flag = pmic3_detect_battery( &pmic3, &status, &battery_state );
    }
    if ( PMIC3_OK == error_flag )
    {
        error_flag = pmic3_read_amux( &pmic3, PMIC3_AMUX_CHANNEL_VIN, &vin );
    }
    if ( ( PMIC3_OK == error_flag ) && ( PMIC3_BATTERY_PRESENT == battery_state ) )
    {
        error_flag = pmic3_read_amux( &pmic3, PMIC3_AMUX_CHANNEL_VBAT, &vbat );
    }
    if ( PMIC3_OK == error_flag )
    {
        error_flag = pmic3_read_amux( &pmic3, PMIC3_AMUX_CHANNEL_VSYS, &vsys );
    }
    if ( PMIC3_OK == error_flag )
    {
        error_flag = pmic3_read_temperature( &pmic3, &temperature );
    }

    if ( PMIC3_OK == error_flag )
    {
        log_printf( &logger, " Input voltage: %.3f V\r\n", vin );

        if ( PMIC3_BATTERY_PRESENT == battery_state )
        {
            log_printf( &logger, " Battery voltage: %.3f V\r\n", vbat );
        }
        else if ( PMIC3_BATTERY_ABSENT == battery_state )
        {
            log_printf( &logger, " Battery: Not detected\r\n" );
        }
        else
        {
            log_printf( &logger, " Battery: Detecting\r\n" );
        }
        log_printf( &logger, " System voltage: %.3f V\r\n", vsys );
        log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );

        if ( PMIC3_BATTERY_ABSENT == battery_state )
        {
            log_printf( &logger, " Charger: Inactive\r\n\n" );
        }
        else if ( PMIC3_BATTERY_UNKNOWN == battery_state )
        {
            log_printf( &logger, " Charger: Waiting for battery\r\n\n" );
        }
        // Report completion before the active charging phase flags.
        else if ( status.charger_2_status & PMIC3_CHARGER2_CHARGE_DONE )
        {
            log_printf( &logger, " Charger: Charge complete\r\n\n" );
        }
        else if ( status.charger_0_status & PMIC3_CHARGER0_TOP_OFF )
        {
            log_printf( &logger, " Charger: Top-off\r\n\n" );
        }
        else if ( status.charger_0_status & PMIC3_CHARGER0_CV_MODE )
        {
            log_printf( &logger, " Charger: Constant voltage\r\n\n" );
        }
        else if ( status.charger_0_status & PMIC3_CHARGER0_FAST_CHARGE )
        {
            log_printf( &logger, " Charger: Constant-current charge\r\n\n" );
        }
        else if ( status.charger_0_status & PMIC3_CHARGER0_PRECHARGE )
        {
            log_printf( &logger, " Charger: Pre-charge\r\n\n" );
        }
        else if ( status.charger_0_status & PMIC3_CHARGER0_OFF )
        {
            log_printf( &logger, " Charger: Off\r\n\n" );
        }
        else
        {
            log_printf( &logger, " Charger: Idle\r\n\n" );
        }
    }
    else
    {
        log_error( &logger, " Data read." );
    }

    Delay_ms( 1000 );
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
