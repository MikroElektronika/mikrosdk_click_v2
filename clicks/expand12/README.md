
---
# Expand 12 Click

> [Expand 12 Click](https://www.mikroe.com/?pid_product=MIKROE-4889) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4889&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Expand 12 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand12

### Example Key Functions

- `expand12_cfg_setup` Config Object Initialization function.
```c
void expand12_cfg_setup ( expand12_cfg_t *cfg );
```

- `expand12_init` Initialization function.
```c
err_t expand12_init ( expand12_t *ctx, expand12_cfg_t *cfg );
```

- `expand12_default_cfg` Click Default Configuration function.
```c
err_t expand12_default_cfg ( expand12_t *ctx );
```

- `expand12_set_pin_direction` This function sets the direction of the selected pin.
```c
err_t expand12_set_pin_direction ( expand12_t *ctx, uint8_t pin, uint8_t direction );
```

- `expand12_set_pin_value` This function sets the logic level of the selected pin.
```c
err_t expand12_set_pin_value ( expand12_t *ctx, uint8_t pin, uint8_t pin_value );
```

- `expand12_read_all_pins_value` This function reads all pins logic levels.
```c
err_t expand12_read_all_pins_value ( expand12_t *ctx, uint32_t *pins_value );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets 
> the first three ports (pins 4-23) as output and the fourth port (pins 24-31) as input with pull-ups.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand12_cfg_t expand12_cfg;  /**< Click config object. */

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
    expand12_cfg_setup( &expand12_cfg );
    EXPAND12_MAP_MIKROBUS( expand12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand12_init( &expand12, &expand12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND12_ERROR == expand12_default_cfg ( &expand12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sets the pins of the first three ports and then reads the status of all pins and 
> displays the result on the USB UART approximately every 100 miliseconds.

```c
void application_task ( void )
{
    static uint8_t port_value = 0;
    static uint32_t pins_status = 0;
    
    expand12_set_port_value( &expand12, EXPAND12_PORT_4_7, EXPAND12_ALL_PINS, port_value );
    expand12_set_port_value( &expand12, EXPAND12_PORT_8_15, EXPAND12_ALL_PINS, port_value );
    expand12_set_port_value( &expand12, EXPAND12_PORT_16_23, EXPAND12_ALL_PINS, port_value++ );
        
    expand12_read_all_pins_value( &expand12, &pins_status );
    log_printf( &logger, " Pins status (32-bit) : 0x%.8LX\r\n\n", pins_status );
    Delay_ms ( 100 );
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
