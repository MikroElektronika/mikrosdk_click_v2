
---
# LEM Click

> [LEM Click](https://www.mikroe.com/?pid_product=MIKROE-2553) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2553&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> 
> Demo app measures and displays current by using LEM Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Lem

### Example Key Functions

- `lem_cfg_setup` Config Object Initialization function. 
```c
void lem_cfg_setup ( lem_cfg_t *cfg );
``` 
 
- `lem_init` Initialization function. 
```c
err_t lem_init ( lem_t *ctx, lem_cfg_t *cfg );
```

- `lem_get_current` Function is used to read current in amperes or milliamperes. 
```c
float lem_get_current ( lem_t *ctx, float coef );
```

### Application Init

>
> Initalizes SPI, LOG and Click drivers.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lem_cfg_t cfg;

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

    lem_cfg_setup( &cfg );
    LEM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lem_init( &lem, &cfg );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "      LEM Click      \r\n" );
    log_printf( &logger, "---------------------\r\n" );
}
```

### Application Task

>
> This is an example that shows the capabilities of the LEM Click by measuring 
> current passing through the conductor placed through the hole on the sensor.
> 

```c
void application_task ( void )
{
    current = lem_get_current( &lem, LEM_MILIAMP_COEF );
    
    log_printf( &logger, " Current : %.2f mA \r\n", current );
    log_printf( &logger, "---------------------\r\n" );
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
