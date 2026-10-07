
---
# PMIC 3 Click

> [PMIC 3 Click](https://www.mikroe.com/?pid_product=MIKROE-7039) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7039&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of PMIC 3 Click by detecting the battery
and monitoring the input, battery, and system voltages, onboard temperature,
and active battery-charger state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PMIC3

### Example Key Functions

- `pmic3_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void pmic3_cfg_setup ( pmic3_cfg_t *cfg );
```

- `pmic3_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t pmic3_init ( pmic3_t *ctx, pmic3_cfg_t *cfg );
```

- `pmic3_default_cfg` This function executes a default configuration of PMIC 3 Click board.
```c
err_t pmic3_default_cfg ( pmic3_t *ctx );
```

- `pmic3_read_status` This function reads the non-destructive system, regulator, input, and charger status registers into one status object.
```c
err_t pmic3_read_status ( pmic3_t *ctx, pmic3_status_t *status );
```

- `pmic3_detect_battery` This function uses the latched no-battery interrupt and live no-battery status to debounce battery insertion and removal.
```c
err_t pmic3_detect_battery ( pmic3_t *ctx, pmic3_status_t *status, uint8_t *battery_state );
```

- `pmic3_read_amux` This function selects an AMUX source, and reads the source voltage with the configured AMUX gain.
```c
err_t pmic3_read_amux ( pmic3_t *ctx, uint8_t channel, float *source_voltage );
```

### Application Init

> Initializes the logger, I2C and ADC interfaces, verifies communication with
the PCA9422, starts the PMIC if it is in the OFF state, restores the
PCA9422M active regulator voltages and standard 4.2 V charger configuration,
enables battery detection and charging, and programs the default charge current.

```c
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
```

### Application Task

> Periodically detects the battery, logs the valid input, battery, and system
voltages and onboard temperature, and reports the current battery-charger state.

```c
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
```

### Note

> Select the required board supply and output jumpers before connecting a
battery or load. The example restores the PCA9422M active rail defaults and
uses a 4.2 V regulation target with a 200 mA charge current. Temperature is
measured by the onboard 10 kOhm NTC thermistor.

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
