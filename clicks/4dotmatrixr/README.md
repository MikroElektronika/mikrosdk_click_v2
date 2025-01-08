
---
# 4Dot-Matrix R Click

> [4Dot-Matrix R Click](https://www.mikroe.com/?pid_product=MIKROE-2706) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2706&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of 4Dot-Matrix R Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.4dotmatrixr

### Example Key Functions

- `c4dotmatrixr_cfg_setup` Config Object Initialization function. 
```c
void c4dotmatrixr_cfg_setup ( c4dotmatrixr_cfg_t *cfg );
``` 
 
- `c4dotmatrixr_init` Initialization function. 
```c
err_t c4dotmatrixr_init ( c4dotmatrixr_t *ctx, c4dotmatrixr_cfg_t *cfg );
```

- `c4dotmatrixr_default_cfg` Click Default Configuration function. 
```c
void c4dotmatrixr_default_cfg ( c4dotmatrixr_t *ctx );
```

- `c4dot_write_char` 4DotMatrix Char Write. 
```c
void c4dot_write_char ( c4dotmatrixr_t *ctx, uint8_t char_num, uint8_t char_value );
```
 
- `c4dot_write_char0` 4DotMatrix Char 0 Write. 
```c
void c4dot_write_char0 ( c4dotmatrixr_t *ctx, uint8_t char_value );
```

- `c4dot_write_text` 4DotMatrix Text Write. 
```c
void c4dot_write_text ( c4dotmatrixr_t *ctx, uint8_t *text_to_write );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c4dotmatrixr_cfg_t cfg;

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

    c4dotmatrixr_cfg_setup( &cfg );
    C4DOTMATRIXR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c4dotmatrixr_init( &c4dotmatrixr, &cfg );
    
    c4dotmatrixr_default_cfg ( &c4dotmatrixr );
    log_info( &logger, "---- Application Task ----" );
}
```

### Application Task

> Displays a desired text message and then numbers from -20 to 20 on the Click board.
> Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    int8_t i;
    log_printf( &logger, "------------------------------------\r\n" );
    log_printf( &logger, "Displaying \"Mikroelektronika\" on the Click board...\r\n" );
    for ( i = 0; i < 20; i++ )
    {
        c4dot_write_text(  &c4dotmatrixr, text + i );
        Delay_ms ( 150 );
    }
        
    // Clear and delay.
    c4dot_clear_display( &c4dotmatrixr );
    Delay_ms ( 500 );
        
    log_printf( &logger, "Displaying all integer numbers from -20 to 20 on the Click board...\r\n" );
    // Write some numbers on the display.
    for ( i = -20; i <= 20; i++ )
    {
        c4dot_write_int_dec( &c4dotmatrixr, i );
        Delay_ms ( 150 );
    }

    // Clear and delay.
    c4dot_clear_display( &c4dotmatrixr );
    Delay_ms ( 500 );
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
