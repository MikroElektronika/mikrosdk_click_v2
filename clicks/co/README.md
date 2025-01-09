
---
# CO Click

> [CO Click](https://www.mikroe.com/?pid_product=MIKROE-1626) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1626&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> The demo application shows the reading of the adc 
values given by the sensors.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CO

### Example Key Functions

- `co_cfg_setup` Config Object Initialization function.
```c
void co_cfg_setup ( co_cfg_t *cfg );
```

- `co_init` Initialization function.
```c
err_t co_init ( co_t *ctx, co_cfg_t *cfg );
```

- `co_read_an_pin_value` This function reads results of AD conversion of the AN pin.
```c
err_t co_read_an_pin_value ( co_t *ctx, uint16_t *data_out );
```

- `co_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t co_read_an_pin_voltage ( co_t *ctx, float *data_out );
```

### Application Init

> Configuring Clicks and log objects.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    co_cfg_t co_cfg;  /**< Click config object. */

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

    co_cfg_setup( &co_cfg );
    CO_MAP_MIKROBUS( co_cfg, MIKROBUS_1 );
    if ( co_init( &co, &co_cfg ) == ADC_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the adc value and prints in two forms (DEC and HEX).

```c
void application_task ( void ) 
{
    uint16_t co_an_value = 0;

    if ( co_read_an_pin_value ( &co, &co_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " ADC Value : %u\r\n", co_an_value );
    }

    float co_an_voltage = 0;

    if ( co_read_an_pin_voltage ( &co, &co_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", co_an_voltage );
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
