
---
# 2x30W Amp Click

> [2x30W Amp Click](https://www.mikroe.com/?pid_product=MIKROE-3010) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3010&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application is audio amplifier.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.2x30wAmp

### Example Key Functions

- `c2x30wamp_cfg_setup` Config Object Initialization function. 
```c
void c2x30wamp_cfg_setup ( c2x30wamp_cfg_t *cfg );
``` 
 
- `c2x30wamp_init` Initialization function. 
```c
err_t c2x30wamp_init ( c2x30wamp_t *ctx, c2x30wamp_cfg_t *cfg );
```

- `c2x30wamp_enable` Device Enable function. 
```c
void c2x30wamp_enable( c2x30wamp_t *ctx, uint8_t state );
```
 
- `c2x30wamp_mute` Device Mute function. 
```c
void c2x30wamp_mute( c2x30wamp_t *ctx, uint8_t state );
```

- `c2x30wamp_check_diagnostic` Diagnostic Check function. 
```c
uint8_t c2x30wamp_check_diagnostic( c2x30wamp_t *ctx );
```

### Application Init

> Initializes GPIO driver and enables the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c2x30wamp_cfg_t cfg;

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

    c2x30wamp_cfg_setup( &cfg );
    C2X30WAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c2x30wamp_init( &c2x30wamp, &cfg );

    c2x30wamp_enable( &c2x30wamp, C2X30WAMP_ENABLE );
    log_printf( &logger, "2x30W AMP is initialized \r\n" );
    Delay_ms ( 200 );
}
```

### Application Task

> Mute output for a period of 3 seconds, then keep it unmuted for a period of 10 seconds. 
> After that, checks if over current fault, over temperature fault or too high DC offset fault occurred.

```c
void application_task ( void )
{
    c2x30wamp_mute( &c2x30wamp, C2X30WAMP_MUTE );
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "MUTE \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    c2x30wamp_mute( &c2x30wamp, C2X30WAMP_UNMUTE );
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "UNMUTE \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    uint8_t fault_check = c2x30wamp_check_diagnostic( &c2x30wamp );

    if ( fault_check == 0 )
    {
        log_printf( &logger, "Fault condition! \r\n" );
    }
}
```

### Note

> When under or over voltage condition occurres the output goes to high impedance state,
> but the FAULT pin will not be asserted.

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
