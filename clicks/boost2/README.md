
---
# Boost 2 Click

> [Boost 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2894) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2894&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application features very high efficiency, low noise and anti-ringing voltage output.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost2

### Example Key Functions

- `boost2_cfg_setup` Config Object Initialization function. 
```c
void boost2_cfg_setup ( boost2_cfg_t *cfg );
``` 
 
- `boost2_init` Initialization function. 
```c
err_t boost2_init ( boost2_t *ctx, boost2_cfg_t *cfg );
```

- `boost2_set_en_pin` Set enable pin. 
```c
void boost2_set_en_pin ( boost2_t *ctx, uint8_t new_state );
```
 
- `boost2_get_pg_pin` Get PG pin state. 
```c
uint8_t boost2_get_pg_pin ( boost2_t *ctx );
```

### Application Init

> Initializes Click driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    boost2_cfg_t cfg;

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

    //  Click initialization.

    boost2_cfg_setup( &cfg );
    BOOST2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost2_init( &boost2, &cfg );
}
```

### Application Task

> Demonstrates the use of the Click drivers function. It
shows how to enable or disable Click operation, and how to check if supplied
voltage is good.

```c
void application_task ( void )
{
    log_printf( &logger, "Enabling Click operation... \r\n" );
    boost2_set_en_pin( &boost2, 1 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Checking output voltage... \r\n" );
    Delay_ms ( 500 );
    if ( boost2_get_pg_pin( &boost2 ))
    {
        log_printf( &logger, "Output voltage good. \r\n" );
    }
    else
    {
        log_printf( &logger, "Output voltage incorrect. \r\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Disabling Click operation... \r\n" );
    boost2_set_en_pin( &boost2, 0 );
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
