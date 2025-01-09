
---
# Pressure 13 Click

> [Pressure 13 Click](https://www.mikroe.com/?pid_product=MIKROE-4294) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4294&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> This is an example which demonstrates the use of Pressure 13 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure13

### Example Key Functions

- `pressure13_cfg_setup` Config Object Initialization function.
```c
void pressure13_cfg_setup ( pressure13_cfg_t *cfg );
```

- `pressure13_init` Initialization function.
```c
err_t pressure13_init ( pressure13_t *ctx, pressure13_cfg_t *cfg );
```

- `pressure13_read_an_pin_value` Pressure 13 read AN pin value function.
```c
err_t pressure13_read_an_pin_value ( pressure13_t *ctx, uint16_t *data_out );
```

- `pressure13_read_an_pin_voltage` Pressure 13 read AN pin voltage level function.
```c
err_t pressure13_read_an_pin_voltage ( pressure13_t *ctx, float *data_out );
```

- `pressure13_get_pressure` Pressure 13 get pressure function.
```c
err_t pressure13_get_pressure ( pressure13_t *ctx, float *data_out );
```

### Application Init

> Initialization driver enables - GPIO, initializes ADC, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure13_cfg_t pressure13_cfg;  /**< Click config object. */

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
    pressure13_cfg_setup( &pressure13_cfg );
    PRESSURE13_MAP_MIKROBUS( pressure13_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == pressure13_init( &pressure13, &pressure13_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n", voltage_val );
}
```

### Application Task

> Measure and display pressure ( mBar ). Results are being sent to the Usart Terminal where you can track their changes. All data logs on usb uart approximately every sec.

```c
void application_task ( void ) 
{
    if ( pressure13_get_pressure( &pressure13, &pressure_val ) != ADC_ERROR ) {
        log_printf( &logger, " Pressure: %.3f [mBar]\r\n", pressure_val );
    }
    log_printf( &logger, "-------------------------\r\n" );
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
