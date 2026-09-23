
---
# Expand 20 Click

> [Expand 20 Click](https://www.mikroe.com/?pid_product=MIKROE-7046) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7046&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jun 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Expand 20 Click board by setting and
reading port 0 and port 1 states.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand20

### Example Key Functions

- `expand20_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void expand20_cfg_setup ( expand20_cfg_t *cfg );
```

- `expand20_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t expand20_init ( expand20_t *ctx, expand20_cfg_t *cfg );
```

- `expand20_default_cfg` This function executes a default configuration of Expand 20 Click board.
```c
err_t expand20_default_cfg ( expand20_t *ctx );
```

- `expand20_set_pin_direction` This function sets the direction of the selected pins on the selected port.
```c
err_t expand20_set_pin_direction ( expand20_t *ctx, uint8_t port, uint8_t direction, uint8_t pin_mask );
```

- `expand20_set_pin_value` This function sets the value of the selected pins on the selected output port.
```c
err_t expand20_set_pin_value ( expand20_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask );
```

- `expand20_set_port_value` This function sets the value of all output pins on the selected port.
```c
err_t expand20_set_port_value ( expand20_t *ctx, uint8_t port, uint8_t set_mask );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets
port 0 pins as output and port 1 pins as input.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand20_cfg_t expand20_cfg;  /**< Click config object. */

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
    expand20_cfg_setup( &expand20_cfg );
    EXPAND20_MAP_MIKROBUS( expand20_cfg, MIKROBUS_POSITION_EXPAND20 );
    if ( I2C_MASTER_ERROR == expand20_init( &expand20, &expand20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND20_ERROR == expand20_default_cfg ( &expand20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Walks a single high level across all Port 0 output pins, then reads back the
state of both Port 0 and Port 1 and displays the results on the USB UART
approximately once per second.

```c
void application_task ( void ) 
{
    uint8_t port_0_value = 0;
    uint8_t port_1_value = 0;

    for ( uint16_t pin_num = EXPAND20_PIN_0_MASK; pin_num <= EXPAND20_PIN_7_MASK; pin_num <<= 1 )
    {
        expand20_set_port_value( &expand20, EXPAND20_PORT_0, ( uint8_t ) pin_num );
        
        expand20_read_port_value( &expand20, EXPAND20_PORT_0, &port_0_value );
        expand20_read_port_value( &expand20, EXPAND20_PORT_1, &port_1_value );

        log_printf( &logger, " Port 0 ( output ): 0x%.2X\r\n", ( uint16_t ) port_0_value );
        log_printf( &logger, " Port 1 ( input ) : 0x%.2X\r\n\n", ( uint16_t ) port_1_value );

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
