
---
# SHT1x Click

> [SHT1x Click](https://www.mikroe.com/?pid_product=MIKROE-949) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-949&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This Click measures temperature and humidity.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Sht1x

### Example Key Functions

- `sht1x_cfg_setup` Config Object Initialization function. 
```c
void sht1x_cfg_setup ( sht1x_cfg_t *cfg );
``` 
 
- `sht1x_init` Initialization function. 
```c
err_t sht1x_init ( sht1x_t *ctx, sht1x_cfg_t *cfg );
```

- `sht1x_default_cfg` Click Default Configuration function. 
```c
void sht1x_default_cfg ( sht1x_t *ctx );
```

- `sht1x_output_sda` Set pin on output. 
```c
void sht1x_output_sda ( sht1x_t *ctx, sht1x_cfg_t *cfg );
```
 
- `sht1x_input_sda` Set pin on input. 
```c
void sht1x_input_sda ( sht1x_t *ctx, sht1x_cfg_t *cfg );
```

- `sht1x_sda_high` Set SDA high function. 
```c
void sht1x_sda_high ( sht1x_t *ctx );
```

### Application Init

> Initialization driver enables GPIO.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;

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
    log_info(&logger, "---- Application Init ----");

    sht1x_cfg_setup( &cfg );
    SHT1X_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    sht1x_init( &sht1x, &cfg );
}
```

### Application Task

> This example demonstrates the use of SHT1x Click board by measuring 
  temperature and humidity, and displays the results on USART terminal.

```c
void application_task ( void )
{
    sht1x_read_results( &temperature, &humidity );
    log_printf( &logger, " Temperature: %.2f ", temperature );
    log_printf( &logger, " C \r\n" );
  
    log_printf( &logger, " Humidity: %.2f ", humidity );
    log_printf( &logger, " %% \r\n", humidity );
    
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
