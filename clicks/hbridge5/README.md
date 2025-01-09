
---
# H Bridge 5 Click

> [H-Bridge 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3854) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3854&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application controls DC motors and inductive loads.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge5

### Example Key Functions

- `hbridge5_cfg_setup` Config Object Initialization function. 
```c
void hbridge5_cfg_setup ( hbridge5_cfg_t *cfg );
``` 
 
- `hbridge5_init` Initialization function. 
```c
err_t hbridge5_init ( hbridge5_t *ctx, hbridge5_cfg_t *cfg );
```

- `hbridge5_default_cfg` Click Default Configuration function. 
```c
void hbridge5_default_cfg ( hbridge5_t *ctx );
```

- `hbridge5_set_port` Function sets port. 
```c
void hbridge5_set_port ( hbridge5_t *ctx, uint8_t port, uint8_t value );
```
 
- `hbridge5_reverse` Puts motor into reverse motion. 
```c
void hbridge5_reverse ( hbridge5_t *ctx );
```

- `hbridge5_foreward` Puts motor into foreward motion. 
```c
void hbridge5_foreward ( hbridge5_t *ctx );
```

### Application Init

> Initalizes I2C driver, configures all ports as output and writes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge5_cfg_t cfg;

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

    hbridge5_cfg_setup( &cfg );
    HBRIDGE5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge5_init( &hbridge5, &cfg );
    hbridge5_default_cfg( &hbridge5 );
}
```

### Application Task

> This example demonstrates the use of H-Bridge 5 Click board, by running dc motor forward, then stoping and then running it in reverse and stoping again.

```c
void application_task ( void )
{
    log_printf( &logger, "Mode - FORWARD\r\n" );
    hbridge5_forward( &hbridge5 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Mode - SLEEP\r\n" );
    hbridge5_sleep( &hbridge5, HBRIDGE5_DISABLE_ALL_OUTPUT_PORT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Mode - REVERSE\r\n" );
    hbridge5_reverse( &hbridge5 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Mode - SLEEP\r\n" );
    hbridge5_sleep( &hbridge5, HBRIDGE5_DISABLE_ALL_OUTPUT_PORT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

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
