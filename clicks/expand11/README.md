
---
# Expand 11 Click

> [Expand 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5532) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5532&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Expand 11 Click board by setting and reading the port state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand11

### Example Key Functions

- `expand11_cfg_setup` Config Object Initialization function.
```c
void expand11_cfg_setup ( expand11_cfg_t *cfg );
```

- `expand11_init` Initialization function.
```c
err_t expand11_init ( expand11_t *ctx, expand11_cfg_t *cfg );
```

- `expand11_default_cfg` Click Default Configuration function.
```c
err_t expand11_default_cfg ( expand11_t *ctx );
```

- `expand11_set_pin_direction` This function sets the direction of the selected pins.
```c
err_t expand11_set_pin_direction ( expand11_t *ctx, uint8_t direction, uint8_t pin_mask );
```

- `expand11_set_all_pins_value` This function sets the value of all output pins.
```c
err_t expand11_set_all_pins_value ( expand11_t *ctx, uint8_t set_mask );
```

- `expand11_read_port_value` This function reads the value of the port input pins.
```c
err_t expand11_read_port_value ( expand11_t *ctx, uint8_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the pins P0-P1 as output and P2-P3 as input.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand11_cfg_t expand11_cfg;  /**< Click config object. */

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
    expand11_cfg_setup( &expand11_cfg );
    EXPAND11_MAP_MIKROBUS( expand11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand11_init( &expand11, &expand11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND11_ERROR == expand11_default_cfg ( &expand11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Toggles all output pins and then reads the status of the whole port and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    static uint16_t pin_num = EXPAND11_PIN_0_MASK;
    uint8_t port_value = 0;
    if ( EXPAND11_OK == expand11_set_all_pins_value( &expand11, pin_num ) )
    {
        if ( EXPAND11_OK == expand11_read_port_value( &expand11, &port_value ) )
        {
            log_printf( &logger, " PORT STATUS \r\n" );
            log_printf( &logger, "  P0: %u\r\n", ( uint16_t ) ( port_value & EXPAND11_PIN_0_MASK ) );
            log_printf( &logger, "  P1: %u\r\n", ( uint16_t ) ( ( port_value & EXPAND11_PIN_1_MASK ) >> 1 ) );
            log_printf( &logger, "  P2: %u\r\n", ( uint16_t ) ( ( port_value & EXPAND11_PIN_2_MASK ) >> 2 ) );
            log_printf( &logger, "  P3: %u\r\n\n", ( uint16_t ) ( ( port_value & EXPAND11_PIN_3_MASK ) >> 3 ) );
            pin_num = ( ~pin_num ) & EXPAND11_ALL_PINS_MASK;
        }
    }
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
