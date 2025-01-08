
---
# Current 4 Click

> [Current 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4755) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4755&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> This example showcases the ability of the Current 4 Click board.
It configures Host MCU for communication and reads the voltage 
of AN pin and calculates current on load output.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Current4

### Example Key Functions

- `current4_cfg_setup` Config Object Initialization function.
```c
void current4_cfg_setup ( current4_cfg_t *cfg );
```

- `current4_init` Initialization function.
```c
err_t current4_init ( current4_t *ctx, current4_cfg_t *cfg );
```

- `current4_read_load_current` Read load current.
```c
err_t current4_read_load_current ( current4_t *ctx, float *load_current );
```

- `current4_read_an_pin_voltage` Read AN pin voltage level function.
```c
err_t current4_read_an_pin_voltage ( current4_t *ctx, float *data_out );
```

- `current4_read_an_pin_value` Read AN pin value function.
```c
err_t current4_read_an_pin_value ( current4_t *ctx, uint16_t *data_out );
```

### Application Init

> Initialization of the communication modules(ADC and UART).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current4_cfg_t current4_cfg;  /**< Click config object. */

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
    current4_cfg_setup( &current4_cfg );
    CURRENT4_MAP_MIKROBUS( current4_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == current4_init( &current4, &current4_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> In span on 500ms reads voltage and calculates the current on load.

```c
void application_task ( void ) 
{
    float current4_load_current = 0;

    if ( ADC_ERROR != current4_read_load_current ( &current4, &current4_load_current ) ) 
    {
        log_printf( &logger, " > Load current : %.2f[A]\r\n", current4_load_current );
        log_printf( &logger, "**********************\r\n" );
    }

    Delay_ms ( 500 );
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
