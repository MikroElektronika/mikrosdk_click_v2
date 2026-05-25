
---
# 5V to 3V3 Click

> [5V to 3V3 Click](https://www.mikroe.com/?pid_product=MIKROE-6900) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6900&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the 5V to 3V3 Click board to control and
toggle all mikroBUS pins. The application alternates between two toggle modes:
toggling all pins simultaneously a fixed number of times with a defined delay,
and toggling pins sequentially with a separate delay between each pin change.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.5Vto3V3

### Example Key Functions

- `c5vto3v3_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void c5vto3v3_cfg_setup ( c5vto3v3_cfg_t *cfg );
```

- `c5vto3v3_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t c5vto3v3_init ( c5vto3v3_t *ctx, c5vto3v3_cfg_t *cfg );
```

- `c5vto3v3_toggle_all` This function toggles all mikroBUS pins together a desired number of times with the selected delay between each toggle.
```c
void c5vto3v3_toggle_all ( c5vto3v3_t *ctx, uint16_t num_toggles, uint16_t toggle_delay_ms );
```

- `c5vto3v3_toggle_seq` This function toggles all mikroBUS pins one by one with the selected delay between each toggle.
```c
void c5vto3v3_toggle_seq ( c5vto3v3_t *ctx, uint16_t toggle_delay_ms );
```

### Application Init

> Initializes the logger and the 5V to 3V3 Click driver. After driver setup and
mikroBUS mapping, the digital output pins are initialized and the example is ready to run.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c5vto3v3_cfg_t c5vto3v3_cfg;  /**< Click config object. */

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
    c5vto3v3_cfg_setup( &c5vto3v3_cfg );
    C5VTO3V3_MAP_MIKROBUS( c5vto3v3_cfg, MIKROBUS_POSITION_5VTO3V3 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == c5vto3v3_init( &c5vto3v3, &c5vto3v3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Executes two toggle demonstrations in a loop:
 - Toggles all output pins together 5 times with a 500 ms delay.
 - Toggles all output pins sequentially with a 300 ms delay.

```c
void application_task ( void )
{
    log_printf( &logger, " Toggling all pins together 5 times with 500ms delay\r\n\n" );
    c5vto3v3_toggle_all ( &c5vto3v3, 5, 500 );

    log_printf( &logger, " Toggling all pins sequentially with 300ms delay\r\n\n" );
    c5vto3v3_toggle_seq ( &c5vto3v3, 300 );
}
```

### Note

> Use a Tester 2 Click board for real-time visual monitoring of mikroBUS pin logic levels.

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
