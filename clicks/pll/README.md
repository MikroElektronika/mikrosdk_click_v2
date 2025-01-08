
---
# PLL Click

> [PLL Click](https://www.mikroe.com/?pid_product=MIKROE-2993) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2993&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This app sets PLL signals.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pll

### Example Key Functions

- `pll_cfg_setup` Config Object Initialization function.
```c
void pll_cfg_setup ( pll_cfg_t *cfg ); 
```

- `pll_init` Initialization function.
```c
err_t pll_init ( pll_t *ctx, pll_cfg_t *cfg );
```

- `pll_set_clock_output` This function settings clock output.
```c
void pll_set_clock_output ( pll_t *ctx, uint8_t mode );
```

- `pll_set_pll_4x` This function settings PLL x4.
```c
void pll_set_pll_4x ( pll_t *ctx );
```

- `pll_set_pll_6x` This function settings PLL x6.
```c
void pll_set_pll_6x ( pll_t *ctx );
```

### Application Init

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pll_cfg_t cfg;

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
    pll_cfg_setup( &cfg );
    PLL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pll_init( &pll, &cfg );
    pll_set_clock_output( &pll, PLL_CLOCK_ENABLE );
}
```

### Application Task

> Every 2 seconds, the PLL increases the input clock from min (x2) to max (x8) level.

```c
void application_task ( void )
{
    log_printf( &logger, " PLL level: x2\r\n\n" );
    pll_set_pll_2x( &pll );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " PLL level: x3\r\n\n" );
    pll_set_pll_3x( &pll );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " PLL level: x3.125\r\n\n" );
    pll_set_pll_3_125x( &pll );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " PLL level: x4\r\n\n" );
    pll_set_pll_4x( &pll );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " PLL level: x5\r\n\n" );
    pll_set_pll_5x( &pll );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " PLL level: x5.3125\r\n\n" );
    pll_set_pll_5_3125x( &pll );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " PLL level: x6\r\n\n" );
    pll_set_pll_6x( &pll );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " PLL level: x6.25\r\n\n" );
    pll_set_pll_6_25x( &pll );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " PLL level: x8\r\n\n" );
    pll_set_pll_8x( &pll );
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
