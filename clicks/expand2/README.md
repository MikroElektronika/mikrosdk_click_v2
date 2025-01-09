
---
# Expand 2 Click

> [Expand 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1838) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1838&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application demonstrates the use of the Expand 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand2

### Example Key Functions

- `expand2_cfg_setup` Config Object Initialization function. 
```c
void expand2_cfg_setup ( expand2_cfg_t *cfg );
``` 
 
- `expand2_init` Initialization function. 
```c
err_t expand2_init ( expand2_t *ctx, expand2_cfg_t *cfg );
```

- `expand2_default_cfg` Click Default Configuration function. 
```c
void expand2_default_cfg ( expand2_t *ctx );
```

- `expand2_set_bit_port_a` Function set bit to 8-bit register address from PORTA of MCP23017 chip. 
```c
void expand2_set_bit_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );
```
 
- `expand2_toggle_bit_port_a` Function toggle bit from 8-bit register address from PORTA of MCP23017 chip. 
```c
void expand2_toggle_bit_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask );
```

- `expand2_clear_bit_port_a` Function clear bit from 8-bit register address from PORTA of MCP23017 chip. 
```c
void expand2_clear_bit_port_a ( expand2_t *ctx, uint8_t moduleAddress, uint8_t bitMask );
```

### Application Init

> Initializes the driver and logger, and then sets the Click default configuration: PORTA as output, PORTB as input with pull-ups on all pins.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    expand2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    expand2_cfg_setup( &cfg );
    EXPAND2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand2_init( &expand2, &cfg );

    expand2_default_cfg ( &expand2 );

    log_printf( &logger, "----------------\r\n" );
    log_printf( &logger, " Expand 2 Click \r\n" );
    log_printf( &logger, "----------------\r\n" );

    Delay_ms ( 100 );
}
```

### Application Task

> Sets other pin of PORTA every 3 seconds, then reads and displays the status of both ports on USB UART.

```c
void application_task ( void )
{
    //  Task implementation.

    uint8_t port_status;
    uint8_t pin_position;

    for ( pin_position = 0; pin_position < 8; pin_position++ )
    {
        expand2_set_port_a( &expand2, EXPAND2_I2C_MODULE_ADDRESS_0, pin_position );
        
        port_status = expand2_read_port_a( &expand2, EXPAND2_I2C_MODULE_ADDRESS_0 );

        log_printf( &logger, " Status PA (output): %d\r\n", (uint16_t) port_status );
        
        port_status = expand2_read_port_b( &expand2, EXPAND2_I2C_MODULE_ADDRESS_0 );

        log_printf( &logger, " Status PB (input) : %d  \r\n", (uint16_t) port_status );
        log_printf( &logger, "----------------\r\n" );
        
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
