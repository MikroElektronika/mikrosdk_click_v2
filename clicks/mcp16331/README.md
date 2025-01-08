
---
# MCP16331 Click

> [MCP16331 Click](https://www.mikroe.com/?pid_product=MIKROE-2762) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2762&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application is buck-boost voltage regulator.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp16331

### Example Key Functions

- `mcp16331_cfg_setup` Config Object Initialization function. 
```c
void mcp16331_cfg_setup ( mcp16331_cfg_t *cfg );
``` 
 
- `mcp16331_init` Initialization function. 
```c
err_t mcp16331_init ( mcp16331_t *ctx, mcp16331_cfg_t *cfg );
```

- `mcp16331_set_vout` mcp16331 set vout. 
```c
void mcp16331_set_vout ( mcp16331_t *ctx, uint16_t millivolts_vout );
```

### Application Init

> Sends hal pointers, and initializes Click

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp16331_cfg_t cfg;

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

    mcp16331_cfg_setup( &cfg );
    MCP16331_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp16331_init( &mcp16331, &cfg );
}
```

### Application Task

> Switches between 5 V and 12 V values

```c
void application_task ( void )
{
    mcp16331_set_vout( &mcp16331, 5000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    mcp16331_set_vout( &mcp16331, 12000 );
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
