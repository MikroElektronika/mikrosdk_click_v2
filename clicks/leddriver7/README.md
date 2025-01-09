
---
# LED Driver 7 Click

> [LED Driver 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3917) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3917&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is portable lighting and rechargeable flashlights.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver7

### Example Key Functions

- `leddriver7_cfg_setup` Config Object Initialization function. 
```c
void leddriver7_cfg_setup ( leddriver7_cfg_t *cfg );
``` 
 
- `leddriver7_init` Initialization function. 
```c
err_t leddriver7_init ( leddriver7_t *ctx, leddriver7_cfg_t *cfg );
```

- `leddriver7_generic_write` Generic write function. 
```c
void leddriver7_generic_write ( leddriver7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```
 
- `leddriver7_generic_read` Generic read function. 
```c
void leddriver7_generic_read ( leddriver7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

### Application Init

> Initalizes I2C driver and writes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver7_cfg_t cfg;

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

    leddriver7_cfg_setup( &cfg );
    LEDDRIVER7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver7_init( &leddriver7, &cfg );

    Delay_ms ( 100 );
    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, " LED Driver 7 Click  \r\n" );
    log_printf( &logger, "-------------------- \r\n" );
}
```

### Application Task

> This example demonstrates the use of LED Driver 7 Click board,
> by cycling wiper positions of AD5171 Digital Potentiometer.

```c
void application_task ( void )
{
    uint8_t n_pos = 0;
    uint8_t pos_num = 64;

    for ( n_pos = 12; n_pos < pos_num; n_pos++ )
    {
        leddriver7_generic_write( &leddriver7, LEDDRIVER7_NORM_OP_MODE, &n_pos, 1 );
        log_printf( &logger, "Position : %d \r\n", n_pos );
        Delay_ms ( 500 );
    }
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
