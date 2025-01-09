
---
# Expand 10 Click

> [Expand 10 Click](https://www.mikroe.com/?pid_product=MIKROE-4801) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4801&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Expand 10 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand10

### Example Key Functions

- `expand10_cfg_setup` Config Object Initialization function.
```c
void expand10_cfg_setup ( expand10_cfg_t *cfg );
```

- `expand10_init` Initialization function.
```c
err_t expand10_init ( expand10_t *ctx, expand10_cfg_t *cfg );
```

- `expand10_default_cfg` Click Default Configuration function.
```c
err_t expand10_default_cfg ( expand10_t *ctx );
```

- `expand10_set_pin_direction` This function sets the direction of the selected pins.
```c
err_t expand10_set_pin_direction ( expand10_t *ctx, uint8_t direction, uint8_t port, uint8_t pin_mask );
```

- `expand10_set_pin_value` This function sets the value of the selected pins.
```c
err_t expand10_set_pin_value ( expand10_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask );
```

- `expand10_read_port_value` This function reads the value of the selected port input pins.
```c
err_t expand10_read_port_value ( expand10_t *ctx, uint8_t port, uint8_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the first two ports as output and the third port as input with pull-down enabled.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    expand10_cfg_t expand10_cfg;  /**< Click config object. */

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
    expand10_cfg_setup( &expand10_cfg );
    EXPAND10_MAP_MIKROBUS( expand10_cfg, MIKROBUS_1 );
    err_t init_flag = expand10_init( &expand10, &expand10_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    init_flag = expand10_default_cfg ( &expand10 );
    if ( EXPAND10_ERROR == init_flag ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sets the pins of the first two ports and then reads and displays the status of all ports on the USB UART approximately once per second.

```c
void application_task ( void )
{
    uint8_t port_value = 0;
  
    for ( uint16_t pin_num = EXPAND10_PIN_0_MASK; pin_num <= EXPAND10_PIN_7_MASK; pin_num <<= 1 )
    {
        expand10_set_all_pins_value( &expand10, pin_num );
        
        expand10_read_port_value( &expand10, EXPAND10_PORT_0, &port_value );
        log_printf( &logger, " Status P0 (output): 0x%.2X\r\n", ( uint16_t ) port_value );
        
        expand10_read_port_value( &expand10, EXPAND10_PORT_1, &port_value );
        log_printf( &logger, " Status P1 (output): 0x%.2X\r\n", ( uint16_t ) port_value );
        
        expand10_read_port_value( &expand10, EXPAND10_PORT_2, &port_value );
        log_printf( &logger, " Status P2 (input) : 0x%.2X\r\n\r\n", ( uint16_t ) port_value );
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
