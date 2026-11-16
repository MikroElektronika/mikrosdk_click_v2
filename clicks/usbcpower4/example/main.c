/*!
 * @file main.c
 * @brief USB-C Power 4 Click example
 *
 * # Description
 * This example demonstrates the use of USB-C Power 4 Click by monitoring the
 * USB-C connection, active power role, VBUS voltage, PP5V source current, and
 * negotiated USB PD power contract.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Click driver, checks communication with the
 * TPS26750A, loads the embedded Low Region application image when the device
 * is in patch mode, and enables the internal PP5V current monitor.
 *
 * ## Application Task
 * Reads the USB-C connection status, measured VBUS voltage, and the active USB
 * PD Power Data Object once per second. PP5V current is reported in source mode.
 *
 * @note
 * The embedded image configures dual-role power operation with liquid detection
 * disabled. The EPR control output remains disabled in this example.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "usbcpower4.h"
#include "usbcpower4_app.h"

#ifndef MIKROBUS_POSITION_USBCPOWER4
    #define MIKROBUS_POSITION_USBCPOWER4 MIKROBUS_1
#endif

static usbcpower4_t usbcpower4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcpower4_cfg_t usbcpower4_cfg;  /**< Click config object. */

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
    usbcpower4_cfg_setup( &usbcpower4_cfg );
    USBCPOWER4_MAP_MIKROBUS( usbcpower4_cfg, MIKROBUS_POSITION_USBCPOWER4 );
    if ( I2C_MASTER_ERROR == usbcpower4_init( &usbcpower4, &usbcpower4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( USBCPOWER4_ERROR == usbcpower4_default_cfg( &usbcpower4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    // A Low Region image must be loaded before a controller in PTCH mode can run.
    uint8_t mode[ USBCPOWER4_MODE_SIZE + 1 ] = { 0 };
    if ( USBCPOWER4_OK == usbcpower4_read_mode( &usbcpower4, mode ) )
    {
        log_printf( &logger, " Controller mode: %s\r\n", mode );

        if ( ( USBCPOWER4_MODE_APP_0 != mode[ 0 ] ) ||
             ( USBCPOWER4_MODE_APP_1 != mode[ 1 ] ) ||
             ( USBCPOWER4_MODE_APP_2 != mode[ 2 ] ) ||
             ( USBCPOWER4_MODE_APP_3 != mode[ 3 ] ) )
        {
            log_printf( &logger, " Loading application configuration...\r\n" );
            if ( USBCPOWER4_ERROR == usbcpower4_load_app( &usbcpower4, usbcpower4_app_image, usbcpower4_app_image_size ) )
            {
                log_error( &logger, " Application configuration." );
                for ( ; ; );
            }

            if ( USBCPOWER4_OK == usbcpower4_read_mode( &usbcpower4, mode ) )
            {
                log_printf( &logger, " Controller mode: %s\r\n", mode );
            }
        }
    }
    else
    {
        log_error( &logger, " Controller mode." );
        for ( ; ; );
    }

    // Current results are valid only while the controller sources through PP5V.
    if ( USBCPOWER4_ERROR == usbcpower4_set_current_monitor( &usbcpower4,
                                                             USBCPOWER4_CURRENT_MONITOR_ENABLED ) )
    {
        log_error( &logger, " Current monitor configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    usbcpower4_status_t status = { 0 };
    usbcpower4_contract_t contract = { 0 };
    usbcpower4_adc_t adc_result = { 0 };

    if ( USBCPOWER4_OK == usbcpower4_read_status( &usbcpower4, &status ) )
    {
        // Require both physical attachment and a valid Type-C power connection.
        if ( ( 0 != status.plug_present ) && ( 0 != status.power_connection ) )
        {
            log_printf( &logger, " USB-C connection: Detected\r\n" );

            if ( USBCPOWER4_POWER_ROLE_SOURCE == status.power_role )
            {
                log_printf( &logger, " Power role: Source" );
            }
            else
            {
                log_printf( &logger, " Power role: Sink" );
            }

            if ( USBCPOWER4_ORIENTATION_CC2 == status.orientation )
            {
                log_printf( &logger, " | Orientation: CC2\r\n" );
            }
            else
            {
                log_printf( &logger, " | Orientation: CC1\r\n" );
            }

            if ( USBCPOWER4_OK == usbcpower4_read_adc_results( &usbcpower4, &adc_result ) )
            {
                log_printf( &logger, " VBUS: %u.%.3u V", adc_result.vbus_mv / 1000, adc_result.vbus_mv % 1000 );
                if ( USBCPOWER4_POWER_ROLE_SOURCE == status.power_role )
                {
                    log_printf( &logger, " | PP5V source current: %u mA", adc_result.vbus_mean_ma );
                }
                log_printf( &logger, "\r\n" );
            }

            // A zero active PDO indicates that no explicit PD contract is present.
            if ( ( USBCPOWER4_OK == usbcpower4_read_active_pdo( &usbcpower4, &contract ) ) &&
                 ( 0 != contract.valid ) )
            {
                switch ( contract.supply_type )
                {
                    case USBCPOWER4_PDO_TYPE_FIXED:
                    {
                        log_printf( &logger, " Contract: Fixed %u.%.3u V, %u mA\r\n",
                                    contract.voltage_mv / 1000, contract.voltage_mv % 1000, contract.current_ma );
                        break;
                    }
                    case USBCPOWER4_PDO_TYPE_BATTERY:
                    {
                        log_printf( &logger, " Contract: Battery %u.%.3u-%u.%.3u V, %lu mW\r\n",
                                    contract.min_voltage_mv / 1000, contract.min_voltage_mv % 1000,
                                    contract.max_voltage_mv / 1000, contract.max_voltage_mv % 1000,
                                    ( unsigned long ) contract.power_mw );
                        break;
                    }
                    case USBCPOWER4_PDO_TYPE_VARIABLE:
                    {
                        log_printf( &logger, " Contract: Variable %u.%.3u-%u.%.3u V, %u mA\r\n",
                                    contract.min_voltage_mv / 1000, contract.min_voltage_mv % 1000,
                                    contract.max_voltage_mv / 1000, contract.max_voltage_mv % 1000,
                                    contract.current_ma );
                        break;
                    }
                    case USBCPOWER4_PDO_TYPE_AUGMENTED:
                    {
                        if ( USBCPOWER4_APDO_TYPE_PPS == contract.apdo_type )
                        {
                            log_printf( &logger, " Contract: PPS %u.%.3u-%u.%.3u V, %u mA\r\n",
                                        contract.min_voltage_mv / 1000, contract.min_voltage_mv % 1000,
                                        contract.max_voltage_mv / 1000, contract.max_voltage_mv % 1000,
                                        contract.current_ma );
                        }
                        else
                        {
                            log_printf( &logger, " Contract: Augmented PDO 0x%LX\r\n", contract.raw_pdo );
                        }
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            log_printf( &logger, " USB-C connection: Not detected\r\n" );
        }
    }
    else
    {
        log_error( &logger, " Status read." );
    }

    log_printf( &logger, "\r\n" );
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
