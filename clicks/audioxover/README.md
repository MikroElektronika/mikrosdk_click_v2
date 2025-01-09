
---
# Audio Xover Click

> [Audio Xover Click](https://www.mikroe.com/?pid_product=MIKROE-4104) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4104&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This function initializes the driver and makes an initial log. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioXover

### Example Key Functions

- `audioxover_cfg_setup` Config Object Initialization function. 
```c
void audioxover_cfg_setup ( audioxover_cfg_t *cfg );
``` 
 
- `audioxover_init` Initialization function. 
```c
err_t audioxover_init ( audioxover_t *ctx, audioxover_cfg_t *cfg );
```

- `audioxover_power_on` Device power on function. 
```c
void audioxover_power_on ( audioxover_t *ctx );
```

- `audioxover_shut_down` Device shut down function. 
```c
void audioxover_shut_down ( audioxover_t *ctx );
```

### Application Init

> This function initializes and configures the Click and logger modules. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    audioxover_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    audioxover_cfg_setup( &cfg );
    AUDIOXOVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioxover_init( &audioxover, &cfg );
}
```

### Application Task

> This function enables and disables the Click board every 10 seconds, and logs an appropriate message on the USB UART.

```c
void application_task ( void )
{
    log_printf( &logger, " * Switch: ON *\r\n" );
    audioxover_power_on ( &audioxover );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " * Switch: OFF *\r\n" );
    audioxover_shut_down ( &audioxover );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
