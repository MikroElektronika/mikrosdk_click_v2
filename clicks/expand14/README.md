
---
# Expand 14 Click

> [Expand 14 Click](https://www.mikroe.com/?pid_product=MIKROE-5241) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5241&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Expand 14 Click board by setting and reading the ports state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand14

### Example Key Functions

- `expand14_cfg_setup` Config Object Initialization function.
```c
void expand14_cfg_setup ( expand14_cfg_t *cfg );
```

- `expand14_init` Initialization function.
```c
err_t expand14_init ( expand14_t *ctx, expand14_cfg_t *cfg );
```

- `expand14_default_cfg` Click Default Configuration function.
```c
err_t expand14_default_cfg ( expand14_t *ctx );
```

- `expand14_set_pin_direction` This function sets the direction of the selected pins.
```c
err_t expand14_set_pin_direction ( expand14_t *ctx, uint8_t direction, uint8_t port, uint8_t pin_mask );
```

- `expand14_set_all_pins_value` This function sets the value of all output pins.
```c
err_t expand14_set_all_pins_value ( expand14_t *ctx, uint8_t set_mask );
```

- `expand14_read_port_value` This function reads the value of the selected port input pins.
```c
err_t expand14_read_port_value ( expand14_t *ctx, uint8_t port, uint8_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the port 0 as output and the port 1 as input.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand14_cfg_t expand14_cfg;  /**< Click config object. */

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
    expand14_cfg_setup( &expand14_cfg );
    EXPAND14_MAP_MIKROBUS( expand14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand14_init( &expand14, &expand14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND14_ERROR == expand14_default_cfg ( &expand14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sets the pins of the port 0 and then reads the status of both ports and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    uint8_t port_value = 0;
    for ( uint16_t pin_num = EXPAND14_PIN_0_MASK; pin_num <= EXPAND14_PIN_7_MASK; pin_num <<= 1 )
    {
        expand14_set_all_pins_value( &expand14, pin_num );
        
        expand14_read_port_value( &expand14, EXPAND14_PORT_0, &port_value );
        log_printf( &logger, " Status port 0 (output): 0x%.2X\r\n", ( uint16_t ) port_value );
        
        expand14_read_port_value( &expand14, EXPAND14_PORT_1, &port_value );
        log_printf( &logger, " Status port 1 (input) : 0x%.2X\r\n\n", ( uint16_t ) port_value );
        Delay_ms ( 1000 );
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
