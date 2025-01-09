
---
# Thermostat 5 Click

> [Thermostat 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6102) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6102&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2024.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This library contains API for the Thermostat 5 Click driver 
> for temperature measurement and relay control.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermostat5

### Example Key Functions

- `thermostat5_cfg_setup` Config Object Initialization function.
```c
void thermostat5_cfg_setup ( thermostat5_cfg_t *cfg );
```

- `thermostat5_init` Initialization function.
```c
err_t thermostat5_init ( thermostat5_t *ctx, thermostat5_cfg_t *cfg );
```

- `thermostat5_set_relay` This function controls the relay by setting the state of the ON (PWM) pin.
```c
void thermostat5_set_relay ( thermostat5_t *ctx, uint8_t state );
```

- `thermostat5_get_temperature` This function reads and calculates temperature in degrees Celsius [degC] using NTC thermistors.
```c
err_t thermostat5_get_temperature ( thermostat5_t *ctx, float *temperature );
```

- `thermostat5_read_voltage` This function sets the voltage reference for Thermostat 5 Click driver.
```c
err_t thermostat5_read_voltage ( thermostat5_t *ctx, float *voltage );
```

### Application Init

> The initialization of the I2C or ADC module and log UART set the relay to an OFF state.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermostat5_cfg_t thermostat5_cfg;  /**< Click config object. */

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
    thermostat5_cfg_setup( &thermostat5_cfg );
    THERMOSTAT5_MAP_MIKROBUS( thermostat5_cfg, MIKROBUS_1 );
    err_t init_flag = thermostat5_init( &thermostat5, &thermostat5_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    thermostat5_set_relay( &thermostat5, THERMOSTAT5_RELAY_OFF );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application measures temperature in degrees Celsius.
> If the temperature increases above 30 degrees Celsius, 
> the relay will turn ON, otherwise it will turn OFF.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float temperature = 0;
    if ( THERMOSTAT5_OK == thermostat5_get_temperature( &thermostat5, &temperature ) )
    {
        log_printf( &logger, " Temperatur : %.2f [degC]\r\n", temperature );
        if ( THERMOSTAT5_TEMPERATURE_LIMIT < temperature )
        {
            thermostat5_set_relay( &thermostat5, THERMOSTAT5_RELAY_ON );
            log_printf( &logger, " Relay: ON\r\n" );
        }
        else
        {
            thermostat5_set_relay( &thermostat5, THERMOSTAT5_RELAY_OFF );
            log_printf( &logger, " Relay: OFF\r\n" );
        }
        Delay_ms ( 1000 );
    }
}
```

### Note

> For temperature measurement, we used Semitec 103AT-2 NTC Thermistors. 
> - Beta parameter:  3435 K	
> - Resistance:      10 kOhms	
> - Tolerance:	      1 %

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
