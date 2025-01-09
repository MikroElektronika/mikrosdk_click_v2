
---
# Signal Realy Click

> [Signal Relay Click](https://www.mikroe.com/?pid_product=MIKROE-2154) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2154&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> Demo application is used to shows basic controls Signal Relay Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SignalRealy

### Example Key Functions

- `signalrelay_cfg_setup` Config Object Initialization function. 
```c
void signalrelay_cfg_setup ( signalrelay_cfg_t *cfg );
``` 
 
- `signalrelay_init` Initialization function. 
```c
err_t signalrelay_init ( signalrelay_t *ctx, signalrelay_cfg_t *cfg );
```

- `signalrelay_default_cfg` Click Default Configuration function. 
```c
void signalrelay_default_cfg ( signalrelay_t *ctx );
```

- `signalrelay_relay_state` Relays state. 
```c
void signalrelay_relay_state ( signalrelay_t *ctx, uint8_t relay, uint8_t state );
```

### Application Init

> Configuring Clicks and log objects.
> Settings the Click in the default configuration. 
 
```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    signalrelay_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----");

    //  Click initialization.

    signalrelay_cfg_setup( &cfg );
    SIGNALRELAY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    signalrelay_init( &signalrelay, &cfg );

    signalrelay_default_cfg ( &signalrelay );
}
```

### Application Task

> Alternately sets relays to ON-OFF state...

```c
void application_task ( void )
{
    uint8_t cnt;

    //  Task implementation.

    for ( cnt = 1; cnt <= 4; cnt++ )
    {
        log_info( &logger, " *** Relay [ %d ] ON ", cnt );
        signalrelay_relay_state( &signalrelay, cnt, SIGNALRELAY_STATE_ON );
        Delay_ms ( 200 );
        log_info( &logger, " *** Relay [ %d ] OFF ", cnt );
        signalrelay_relay_state( &signalrelay, cnt, SIGNALRELAY_STATE_OFF );
        Delay_ms ( 200 );
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
