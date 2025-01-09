
---
# Expand Click

> [Expand Click](https://www.mikroe.com/?pid_product=MIKROE-951) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-951&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This applicatioin use for expansion I/O lines.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand

### Example Key Functions

- `expand_cfg_setup` Config Object Initialization function. 
```c
void expand_cfg_setup ( expand_cfg_t *cfg );
``` 
 
- `expand_init` Initialization function. 
```c
err_t expand_init ( expand_t *ctx, expand_cfg_t *cfg );
```

- `expand_set_direction_port_a` Set expander PORTA direction function. 
```c
void expand_set_direction_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data );
```
 
- `expand_write_port_a` Write one byte of data to register for PORTA function. 
```c
void expand_write_port_a ( expand_t *ctx, uint8_t mod_cmd, uint8_t write_data );
```

- `expand_reset` Reset function. 
```c
void expand_reset ( expand_t *ctx );
```

### Application Init

> Initialization driver enable's - GPIO, reset MCP23S17 chip, set PORTA to be output and PORTB to be input, set default configuration and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    expand_cfg_t cfg;

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

    expand_cfg_setup( &cfg );
    EXPAND_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand_init( &expand, &cfg );
    
    expand_default_configuration( &expand, EXPAND_SPI_MODULE_POSITION_0 );

    expand_set_direction_port_a( &expand, EXPAND_SPI_MODULE_POSITION_0, EXPAND_PORT_DIRECTION_OUTPUT );
    
    expand_set_direction_port_b( &expand, EXPAND_SPI_MODULE_POSITION_0, EXPAND_PORT_DIRECTION_INPUT );
    
    expand_set_pull_ups_port_b( &expand, EXPAND_SPI_MODULE_POSITION_0, 0xFF );
}
```

### Application Task

> This is a example which demonstrates the use of Expand Click board. 
> Expand Click communicates with register via SPI protocol by write and read from register, set configuration and state and read configuration and state. 
> Results are being sent to the Usart Terminal where you can track their changes. All data logs on usb uart for aproximetly every 500 ms.

```c
void application_task ( void )
{
    pin_position = 1;

    for ( position = 0; position < 8; position++ )
    {
        expand_write_port_a( &expand, EXPAND_SPI_MODULE_POSITION_0, pin_position );
        log_printf( &logger, " PA%d set\r\n", (uint16_t) position );

        port_status = expand_read_port_b( &expand, EXPAND_SPI_MODULE_POSITION_0 );

        log_printf( &logger, " Status PB (input) : %d  \r\n", (uint16_t) port_status );
        log_printf( &logger, "----------------\r\n" );
        
        pin_position <<= 1;

        Delay_ms ( 500 );
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
