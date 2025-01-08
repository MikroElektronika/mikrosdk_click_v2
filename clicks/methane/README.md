
---
# Methane Click

> [Methane Click](https://www.mikroe.com/?pid_product=MIKROE-1628) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1628&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> The demo application shows the reading of the adc values given by the sensors.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Methane

### Example Key Functions

- `methane_cfg_setup` Config Object Initialization function.
```c
void methane_cfg_setup ( methane_cfg_t *cfg );
```

- `methane_init` Initialization function.
```c
err_t methane_init ( methane_t *ctx, methane_cfg_t *cfg );
```

- `methane_default_cfg` Click Default Configuration function.
```c
void methane_default_cfg ( methane_t *ctx );
```

- `methane_read_an_pin_value` Methane read AN pin value function.
```c
err_t methane_read_an_pin_value ( methane_t *ctx, uint16_t *data_out );
```

- `methane_read_an_pin_voltage` Methane read AN pin voltage level function.
```c
err_t methane_read_an_pin_voltage ( methane_t *ctx, float *data_out );
```

### Application Init

> Configuring Clicks and log objects.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    methane_cfg_t methane_cfg;  /**< Click config object. */

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

    methane_cfg_setup( &methane_cfg );
    METHANE_MAP_MIKROBUS( methane_cfg, MIKROBUS_1 );
    if ( methane_init( &methane, &methane_cfg ) == ADC_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the adc value and prints in two forms adc value and voltage.

```c
void application_task ( void ) 
{
    uint16_t methane_an_value = 0;

    if ( methane_read_an_pin_value ( &methane, &methane_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " ADC Value : %u\r\n", methane_an_value );
    }

    float methane_an_voltage = 0;

    if ( methane_read_an_pin_voltage ( &methane, &methane_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", methane_an_voltage );
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
