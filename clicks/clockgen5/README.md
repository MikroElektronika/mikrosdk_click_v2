
---
# Clock Gen 5 Click

> [Clock Gen 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4413) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4413&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Clock Gen 5 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ClockGen5

### Example Key Functions

- `clockgen5_cfg_setup` Config Object Initialization function.
```c
void clockgen5_cfg_setup ( clockgen5_cfg_t *cfg );
```

- `clockgen5_init` Initialization function.
```c
err_t clockgen5_init ( clockgen5_t *ctx, clockgen5_cfg_t *cfg );
```

- `clockgen5_out_enable` Enable output function.
```c
void clockgen5_out_enable ( clockgen5_t *ctx, uint8_t en_out );
```

- `clockgen5_set_config` Set configuration function.
```c
void clockgen5_set_config ( clockgen5_t *ctx, uint8_t cfg );
```

- `clockgen5_set_freq` Set frequency function.
```c
void clockgen5_set_freq ( clockgen5_t *ctx, float freq );
```

### Application Init

> Initialization driver enables - SPI, set output configuration CLK 180, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    clockgen5_cfg_t clockgen5_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.

    clockgen5_cfg_setup( &clockgen5_cfg );
    CLOCKGEN5_MAP_MIKROBUS( clockgen5_cfg, MIKROBUS_1 );
    err_t init_flag  = clockgen5_init( &clockgen5, &clockgen5_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... %d", init_flag );

        for ( ; ; );
    }
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    Enabling Output   \r\n" );
    clockgen5_out_enable( &clockgen5, CLOCKGEN5_OUTPUT_ENABLE);
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "   Set configuration   \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    clockgen5_set_config( &clockgen5, CLOCKGEN5_CFG_ON_CLK_180 );
    Delay_ms ( 500 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> In this example, we adjusts different frequencies every 3 sec. Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "        12.0 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 12000.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         8.0 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 8000.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         5.5 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 5500.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         2.7 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 2700.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         0.8 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 800.0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         0.2 MHz       \r\n" );
    clockgen5_set_freq( &clockgen5, 200.0 );
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
