
---
# Relay 3 Click

> [Relay 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3357) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3357&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example starts off with the initialization and configuration of the Click and logger
  modules and later on showcases how to turn specified relays ON/OFF using the output pins.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Relay3

### Example Key Functions

- `relay3_cfg_setup` Config Object Initialization function. 
```c
void relay3_cfg_setup ( relay3_cfg_t *cfg );
``` 
 
- `relay3_init` Initialization function. 
```c
err_t relay3_init ( relay3_t *ctx, relay3_cfg_t *cfg );
```

- `relay3_relay_on` This function turns on either the 1st or the 2nd relay on the Click. 
```c
void relay3_relay_on ( uint8_t relay );
```
 
- `` This function turns off either the 1st or the 2nd relay on the Click. 
```c
relay3_relay_off  ( uint8_t relay );
```

### Application Init

> This function initialises and configures the logger and Click modules.

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    relay3_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    relay3_cfg_setup( &cfg );
    RELAY3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    relay3_init( &relay3, &cfg );
}
```

### Application Task

> This function turns on the 1st and the 2nd relay and then turns them both off.

```c
void application_task ( )
{
    case_1( );
    Delay_ms ( 1000 );

    case_2( );
    Delay_ms ( 1000 );

    case_3( );
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
