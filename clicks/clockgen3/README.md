
---
# Clock Gen 3 Click

> [Clock Gen 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4171) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4171&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Clock Gen 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ClockGen3

### Example Key Functions

- `clockgen3_cfg_setup` Config Object Initialization function.
```c
void clockgen3_cfg_setup ( clockgen3_cfg_t *cfg );
```
 
- `clockgen3_init` Initialization function.
```c
err_t clockgen3_init ( clockgen3_t *ctx, clockgen3_cfg_t *cfg );
```

- `clockgen3_set_cs_pin` Sets CS pin state
```c
void clockgen3_set_cs_pin ( clockgen3_t *ctx, uint8_t state );
```
 
- `clockgen3_generic_write` Generic write function.
```c
void clockgen3_generic_write ( clockgen3_t *ctx, uint8_t *data_buf, uint8_t len );
```

- `clockgen3_set_freq` Sets Frequency
```c
void clockgen3_set_freq ( clockgen3_t *ctx, float freq );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    clockgen3_cfg_t cfg;

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

    // Click initialization.
    clockgen3_cfg_setup( &cfg );
    CLOCKGEN3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    clockgen3_init( &clockgen3, &cfg );

    clockgen3_config( &clockgen3, CLOCKGEN3_CFG_ON_CLK_180 );
    Delay_ms ( 500 );
}
```

### Application Task

> Sets different frequencies every 3 seconds and displays the set frequency on the USB UART.

```c
void application_task ( void )
{
    log_printf( &logger, ">> Set Freq = 12.000 MHz \r\n" );
    clockgen3_set_freq( &clockgen3, 12000.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, ">> Set Freq = 8.000 MHz \r\n" );
    clockgen3_set_freq( &clockgen3, 8000.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, ">> Set Freq = 5.500 MHz \r\n" );
    clockgen3_set_freq( &clockgen3, 5500.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, ">> Set Freq = 2.700 MHz \r\n" );
    clockgen3_set_freq( &clockgen3, 2700.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, ">> Set Freq = 800 KHz \r\n" );
    clockgen3_set_freq( &clockgen3, 800.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, ">> Set Freq = 200 KHz \r\n" );
    clockgen3_set_freq( &clockgen3, 200.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "---------------------------- \r\n" );
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
