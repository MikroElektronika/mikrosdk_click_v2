
---
# Dot-Matrix R Click

> [Dot Matrix R Click](https://www.mikroe.com/?pid_product=MIKROE-4169) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4169&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This demo application show data on display.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DotMatrixR

### Example Key Functions

- `dotmatrixr_cfg_setup` Config Object Initialization function. 
```c
void dotmatrixr_cfg_setup ( dotmatrixr_cfg_t *cfg );
``` 
 
- `dotmatrixr_init` Initialization function. 
```c
err_t dotmatrixr_init ( dotmatrixr_t *ctx, dotmatrixr_cfg_t *cfg );
```

- `dotmatrixr_set_bl_pin_state` Sets BL pin to high or low state. 
```c
void dotmatrixr_set_bl_pin_state( dotmatrixr_t *ctx, uint8_t state );
```
 
- `dotmatrixr_restart` Restart device . 
```c
void dotmatrixr_restart( dotmatrixr_t *ctx );
```

- `dotmatrixr_write_ascii` Sets display to written value. 
```c
void dotmatrixr_write_ascii( dotmatrixr_t *ctx, char *ascii_data );
```

### Application Init

> Configuration device

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dotmatrixr_cfg_t cfg;

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

    dotmatrixr_cfg_setup( &cfg );
    DOTMATRIXR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dotmatrixr_init( &dotmatrixr, &cfg );

    Delay_ms ( 100 );
    dotmatrixr_restart( &dotmatrixr );
    Delay_ms ( 500 );
    
    dotmatrixr_set_bl_pin_state( &dotmatrixr, 0 );
    dotmatrixr_set_rs_pin_state( &dotmatrixr, 0 );

    dotmatrixr_ctrl_1( &dotmatrixr, DOTMATRIXR_CTRL_BYTE_1_OSC_PRESCALER_1 |
                       DOTMATRIXR_CTRL_BYTE_1_DOUT_DIN );
    dotmatrixr_ctrl_0( &dotmatrixr, DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_30 |
                       DOTMATRIXR_CTRL_BYTE_0_PIXEL_PEAK_CURRENT_9p3mA |
                       DOTMATRIXR_CTRL_BYTE_0_MODE_NORMAL );
}
```

### Application Task

> Display shows 3 different data in span of 1 second

```c
void application_task ( void )
{
    dotmatrixr_write_ascii( &dotmatrixr, &demo_t1[ 0 ] );
    Delay_ms ( 1000 );
    dotmatrixr_write_ascii( &dotmatrixr, &demo_t2[ 0 ] );
    Delay_ms ( 1000 );
    dotmatrixr_write_ascii( &dotmatrixr, &demo_t3[ 0 ] );
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
