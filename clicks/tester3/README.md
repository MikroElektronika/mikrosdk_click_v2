
---
# Tester 3 Click

> [Tester 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6967) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6967&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Tester 3 Click board by controlling all LEDs on the Click board together and in sequential pin toggling with different delays.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Tester3

### Example Key Functions

- `tester3_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void tester3_cfg_setup ( tester3_cfg_t *cfg );
```

- `tester3_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t tester3_init ( tester3_t *ctx, tester3_cfg_t *cfg );
```

- `tester3_toggle_all` This function toggles all mikroBUS pins together a desired number of times with the selected delay between each toggle.
```c
void tester3_toggle_all ( tester3_t *ctx, uint16_t num_toggles, uint16_t toggle_delay_ms );
```

- `tester3_toggle_seq` This function toggles all mikroBUS pins one by one with the selected delay between each toggle.
```c
void tester3_toggle_seq ( tester3_t *ctx, uint16_t toggle_delay_ms );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tester3_cfg_t tester3_cfg;  /**< Click config object. */

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
    tester3_cfg_setup( &tester3_cfg );
    TESTER3_MAP_MIKROBUS( tester3_cfg, MIKROBUS_POSITION_TESTER3 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == tester3_init( &tester3, &tester3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Toggles all pins together 5 times with a 500ms delay between each toggle, then toggles each pin sequentially with a 300ms delay between toggling each pin.

```c
void application_task ( void )
{
    log_printf( &logger, " Toggling all pins together 5 times with 500ms delay\r\n\n" );
    tester3_toggle_all ( &tester3, 5, 500 );

    log_printf( &logger, " Toggling all pins sequentially with 300ms delay\r\n\n" );
    tester3_toggle_seq ( &tester3, 300 );
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
