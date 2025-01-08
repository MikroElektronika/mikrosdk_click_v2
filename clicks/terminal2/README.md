
---
# Terminal 2 Click

> [Terminal 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4951) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4951&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstates the use of Terminal 2 Click board by toggling all its pins.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Terminal2

### Example Key Functions

- `terminal2_cfg_setup` Config Object Initialization function.
```c
void terminal2_cfg_setup ( terminal2_cfg_t *cfg );
```

- `terminal2_init` Initialization function.
```c
err_t terminal2_init ( terminal2_t *ctx, terminal2_cfg_t *cfg );
```

- `terminal2_set_all_pins_high` This function sets all terminal pins to high logic level.
```c
void terminal2_set_all_pins_high ( terminal2_t *ctx );
```

- `terminal2_set_all_pins_low` This function sets all terminal pins to low logic level.
```c
void terminal2_set_all_pins_low ( terminal2_t *ctx );
```

- `terminal2_toggle_pin` This function toggles the specified pin logic level.
```c
void terminal2_toggle_pin ( digital_out_t *pin );
```

### Application Init

> Initializes the driver and logger and sets all pins to low logic state.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    terminal2_cfg_t terminal2_cfg;  /**< Click config object. */

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
    terminal2_cfg_setup( &terminal2_cfg );
    TERMINAL2_MAP_MIKROBUS( terminal2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == terminal2_init( &terminal2, &terminal2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    terminal2_set_all_pins_low ( &terminal2 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Toggles all pins from mikroBUS one by one in the span of 1 second between each pin toggle.

```c
void application_task ( void )
{
    /**< Array of pins object addresses. */
    static digital_out_t *pin_addr[ 12 ] =
    {
        &terminal2.mosi,    // 0 MOSI
        &terminal2.miso,    // 1 MISO
        &terminal2.sck,     // 2 SCK
        &terminal2.cs,      // 3 CS
        &terminal2.rst,     // 4 RST
        &terminal2.an,      // 5 AN
        &terminal2.pwm,     // 6 PWM
        &terminal2.int_pin, // 7 INT
        &terminal2.tx_pin,  // 8 TX
        &terminal2.rx_pin,  // 9 RX
        &terminal2.scl,     // 10 SCL
        &terminal2.sda      // 11 SDA
    };
    static uint8_t pin_num = 0;
    log_printf( &logger, " Toggling pin: %u\r\n", ( uint16_t ) pin_num );
    terminal2_toggle_pin ( pin_addr[ pin_num ] );
    Delay_ms ( 1000 );
    terminal2_toggle_pin ( pin_addr[ pin_num ] );
    
    pin_num++;
    if ( 12 == pin_num )
    {
        pin_num = 0;
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
