
---
# PROTO Click

> [PROTO Click](https://www.mikroe.com/?pid_product=MIKROE-1507) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1507&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstates the use of PROTO Click board by toggling all its pins.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PROTO

### Example Key Functions

- `proto_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void proto_cfg_setup ( proto_cfg_t *cfg );
```

- `proto_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t proto_init ( proto_t *ctx, proto_cfg_t *cfg );
```

- `proto_toggle_pin` This function toggles the specified pin logic level.
```c
void proto_toggle_pin ( digital_out_t *pin );
```

- `proto_set_pin_high` This function sets the specified pin to high logic level.
```c
void proto_set_pin_high ( digital_out_t *pin );
```

- `proto_set_pin_low` This function sets the specified pin to low logic level.
```c
void proto_set_pin_low ( digital_out_t *pin );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proto_cfg_t proto_cfg;  /**< Click config object. */

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
    proto_cfg_setup( &proto_cfg );
    PROTO_MAP_MIKROBUS( proto_cfg, MIKROBUS_POSITION_PROTO );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == proto_init( &proto, &proto_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
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
        &proto.mosi,    // 0 MOSI
        &proto.miso,    // 1 MISO
        &proto.sck,     // 2 SCK
        &proto.cs,      // 3 CS
        &proto.rst,     // 4 RST
        &proto.an,      // 5 AN
        &proto.pwm,     // 6 PWM
        &proto.int_pin, // 7 INT
        &proto.rx_pin,  // 8 RX
        &proto.tx_pin,  // 9 TX
        &proto.scl,     // 10 SCL
        &proto.sda      // 11 SDA
    };
    static uint8_t pin_num = 0;
    log_printf( &logger, " Toggling pin: %u\r\n", ( uint16_t ) pin_num );
    proto_toggle_pin ( pin_addr[ pin_num ] );
    Delay_ms ( 1000 );
    proto_toggle_pin ( pin_addr[ pin_num ] );
    
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
