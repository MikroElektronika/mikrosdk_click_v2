
---
# Relay 7 Click

> [Relay 7 Click](https://www.mikroe.com/?pid_product=MIKROE-6000) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6000&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Relay 7 Click board by toggling the relay state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Relay7

### Example Key Functions

- `relay7_cfg_setup` Config Object Initialization function.
```c
void relay7_cfg_setup ( relay7_cfg_t *cfg );
```

- `relay7_init` Initialization function.
```c
err_t relay7_init ( relay7_t *ctx, relay7_cfg_t *cfg );
```

- `relay7_default_cfg` Click Default Configuration function.
```c
err_t relay7_default_cfg ( relay7_t *ctx );
```

- `relay7_set_relay` This function sets the desired state of the selected relay.
```c
err_t relay7_set_relay ( relay7_t *ctx, uint8_t relay_sel, relay7_relay_state_t state );
```

- `relay7_reset_device` This function performs a hardware reset of the device.
```c
void relay7_reset_device ( relay7_t *ctx );
```

- `relay7_get_interrupt` This function returns the interrupt pin logic state.
```c
uint8_t relay7_get_interrupt ( relay7_t *ctx );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    relay7_cfg_t relay7_cfg;  /**< Click config object. */

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
    relay7_cfg_setup( &relay7_cfg );
    RELAY7_MAP_MIKROBUS( relay7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == relay7_init( &relay7, &relay7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RELAY7_ERROR == relay7_default_cfg ( &relay7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application toggles the state of all relays every 5 seconds. 
> The results are sent to the UART terminal, where you can monitor their changes.

```c
void application_task ( void ) 
{
    for ( uint8_t relay_sel = RELAY7_SEL_REL1; relay_sel <= RELAY7_SEL_REL4; relay_sel++ )
    {
        if ( RELAY7_OK == relay7_set_relay( &relay7, relay_sel, relay_state ) )
        {
            log_printf( &logger, " Relay %d ", ( uint16_t ) relay_sel );
            if ( RELAY7_STATE_OPEN == relay_state )
            {
                log_printf( &logger, " normally open state\r\n" );
            }
            else
            {
                log_printf( &logger, " normally close state\r\n" );
            }
        }
        Delay_ms ( 1000 );
    }
    relay_state = ~relay_state;
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
