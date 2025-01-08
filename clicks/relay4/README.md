
---
# Relay 4 Click

> [Relay 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5539) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5539&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Relay 4 Click board by toggling the relays state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Relay4

### Example Key Functions

- `relay4_cfg_setup` Config Object Initialization function.
```c
void relay4_cfg_setup ( relay4_cfg_t *cfg );
```

- `relay4_init` Initialization function.
```c
err_t relay4_init ( relay4_t *ctx, relay4_cfg_t *cfg );
```

- `relay4_set_relay1_open` This function sets the relay 1 to normally open state by setting the RL1 pin to low logic level.
```c
void relay4_set_relay1_open ( relay4_t *ctx );
```

- `relay4_set_relay1_close` This function sets the relay 1 to normally close state by setting the RL1 pin to high logic level.
```c
void relay4_set_relay1_close ( relay4_t *ctx );
```

- `relay4_set_relay2_open` This function sets the relay 2 to normally open state by setting the RL2 pin to low logic level.
```c
void relay4_set_relay2_open ( relay4_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    relay4_cfg_t relay4_cfg;  /**< Click config object. */

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
    relay4_cfg_setup( &relay4_cfg );
    RELAY4_MAP_MIKROBUS( relay4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == relay4_init( &relay4, &relay4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Switches the relays 1 and 2 state every 5 seconds and displays the state on the USB UART.

```c
void application_task ( void )
{
    relay4_set_relay1_open ( &relay4 );
    log_printf( &logger, " Relay 1 set to normally open state\r\n" );
    relay4_set_relay2_close ( &relay4 );
    log_printf( &logger, " Relay 2 set to normally close state\r\n\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    relay4_set_relay1_close ( &relay4 );
    log_printf( &logger, " Relay 1 set to normally close state\r\n" );
    relay4_set_relay2_open ( &relay4 );
    log_printf( &logger, " Relay 2 set to normally open state\r\n\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
