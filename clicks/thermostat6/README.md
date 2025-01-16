
---
# Thermostat 6 Click

> [Thermostat 6 Click](https://www.mikroe.com/?pid_product=MIKROE-6313) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of Thermostat 6 Click board by reading
the temperature level set using an on-board potentiometer and the temperature
from the NTC Thermistor 10k Cylindrical Probe (B57500M0103A005) which is connected
to the input, and also displaying the relay state. If the set temperature level
is lower than the temperature read from NTC, then the relay switches ON.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermostat6

### Example Key Functions

- `thermostat6_cfg_setup` Config Object Initialization function.
```c
void thermostat6_cfg_setup ( thermostat6_cfg_t *cfg );
```

- `thermostat6_init` Initialization function.
```c
err_t thermostat6_init ( thermostat6_t *ctx, thermostat6_cfg_t *cfg );
```

- `thermostat6_get_adc_v_avg` This function reads and averages the ADC voltage for a desired number of samples.
```c
err_t thermostat6_get_adc_v_avg ( thermostat6_t *ctx, float *voltage, uint16_t num_samples );
```

- `thermostat6_get_an_pin_v_avg` This function reads and averages the AN pin voltage for a desired number of samples.
```c
err_t thermostat6_get_an_pin_v_avg ( thermostat6_t *ctx, float *voltage, uint16_t num_samples );
```

- `thermostat6_get_temperature` This function calculates temperature in degrees Celsius based on a voltage input using the NTC Thermistor 10k Cylindrical Probe (B57500M0103A005) R/T characteristics map.
```c
float thermostat6_get_temperature ( float voltage );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermostat6_cfg_t thermostat6_cfg;  /**< Click config object. */

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
    thermostat6_cfg_setup( &thermostat6_cfg );
    THERMOSTAT6_MAP_MIKROBUS( thermostat6_cfg, MIKROBUS_1 );
    err_t init_flag = thermostat6_init( &thermostat6, &thermostat6_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature level set using an on-board potentiometer and the temperature
from the NTC Thermistor 10k Cylindrical Probe (B57500M0103A005) connected to the input,
and displays the relay state. If the set temperature level is lower than the temperature
read from NTC, then the relay switches ON.

```c
void application_task ( void )
{
    float voltage = 0;
    if ( THERMOSTAT6_OK == thermostat6_get_an_pin_v_avg ( &thermostat6, &voltage, THERMOSTAT6_ADC_NUM_SAMPLES_50 ) ) 
    {
        log_printf( &logger, " Set temperature : %.2f[degC]\r\n", thermostat6_get_temperature ( voltage ) );
    }
    if ( THERMOSTAT6_OK == thermostat6_get_adc_v_avg ( &thermostat6, &voltage, THERMOSTAT6_ADC_NUM_SAMPLES_50 ) ) 
    {
        log_printf( &logger, " Read temperature : %.2f[degC]\r\n", thermostat6_get_temperature ( voltage ) );
    }
    if ( thermostat6_get_relay_pin ( &thermostat6 ) )
    {
        log_printf( &logger, " Set temperature is lower than read temperature! Relay: ON\r\n\n" );
    }
    else
    {
        log_printf( &logger, " Set temperature is higher than read temperature! Relay: OFF\r\n\n" );
    }
    Delay_ms ( 1000 );
}
```

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
