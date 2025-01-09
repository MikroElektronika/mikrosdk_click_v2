
---
# Expand 19 Click

> [Expand 19 Click](https://www.mikroe.com/?pid_product=MIKROE-6400) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6400&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Expand 19 Click board by setting and reading the port state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand19

### Example Key Functions

- `expand19_cfg_setup` Config Object Initialization function.
```c
void expand19_cfg_setup ( expand19_cfg_t *cfg );
```

- `expand19_init` Initialization function.
```c
err_t expand19_init ( expand19_t *ctx, expand19_cfg_t *cfg );
```

- `expand19_default_cfg` Click Default Configuration function.
```c
err_t expand19_default_cfg ( expand19_t *ctx );
```

- `expand19_set_pin_direction` This function sets the direction of the selected pins.
```c
err_t expand19_set_pin_direction ( expand19_t *ctx, uint8_t direction, uint8_t pin_mask );
```

- `expand19_set_all_pins_value` This function sets the value of all output pins.
```c
err_t expand19_set_all_pins_value ( expand19_t *ctx, uint8_t set_mask );
```

- `expand19_read_port_value` This function reads the value of all input pins.
```c
err_t expand19_read_port_value ( expand19_t *ctx, uint8_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the pins 0-3 as output and others as input with pull-up enabled.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand19_cfg_t expand19_cfg;  /**< Click config object. */

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
    expand19_cfg_setup( &expand19_cfg );
    EXPAND19_MAP_MIKROBUS( expand19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand19_init( &expand19, &expand19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND19_ERROR == expand19_default_cfg ( &expand19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sets the output pins and then reads the status of all pins and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    uint8_t port_value = 0;
    for ( uint16_t pin_num = EXPAND19_PIN_0_MASK; pin_num <= EXPAND19_PIN_3_MASK; pin_num <<= 1 )
    {
        expand19_set_all_pins_value( &expand19, pin_num );
        
        expand19_read_port_value( &expand19, &port_value );
        log_printf( &logger, " Port status: 0x%.2X\r\n", ( uint16_t ) port_value );
        
        Delay_ms( 1000 );
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
