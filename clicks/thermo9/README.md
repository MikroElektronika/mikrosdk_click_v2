
---
# Thermo 9 Click

> [Thermo 9 Click](https://www.mikroe.com/?pid_product=MIKROE-3983) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3983&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : Jan 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> 
> This demoapp measures temperature every 3 seconds.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo9

### Example Key Functions

- `thermo9_cfg_setup` Config Object Initialization function. 
```c
void thermo9_cfg_setup ( thermo9_cfg_t *cfg );
``` 
 
- `thermo9_init` Initialization function. 
```c
err_t thermo9_init ( thermo9_t *ctx, thermo9_cfg_t *cfg );
```

- `thermo9_send_cmd` Function is used to send the command to the device. 
```c
void thermo9_send_cmd ( thermo9_t *ctx, uint8_t cmd_byte );
```
 
- `thermo9_calibation` Function resets and calibrates the device in order for it to work properly. 
```c
void thermo9_calibation ( thermo9_t *ctx );
```

- `thermo9_read_temp` Function is used to read temperature in degree centigrade. 
```c
float thermo9_read_temp ( thermo9_t *ctx );
```

### Application Init

>
> Logger initialization, Click initialization and calibration.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo9_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    thermo9_cfg_setup( &cfg );
    THERMO9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo9_init( &thermo9, &cfg );
    Delay_ms ( 100 );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    Thermo 9 Click   \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    thermo9_calibation( &thermo9 );
    Delay_ms ( 100 );
    log_printf( &logger, "      Calibrated     \r\n" );
    log_printf( &logger, "---------------------\r\n" );
}
```

### Application Task

>
> This example shows capabilities of Thermo 9 Click by measuring
> temperature every 3 seconds and displaying temperature in degrres Celsius 
> via USART terminal.
> 

```c
void application_task ( void )
{
    //  Task implementation.
    temp_val = thermo9_read_temp( &thermo9 );
    log_printf( &logger, "-- Temperature : %.2f °C\r\n", temp_val );

    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> 
> Calibration function must be used once in order to get calibrations!
> 

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
