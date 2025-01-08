
---
# MUX Click

> [MUX Click](https://www.mikroe.com/?pid_product=MIKROE-3247) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3247&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> Sets the current active channel. Changes the channel every 5 sec.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mux

### Example Key Functions

- `mux_cfg_setup` Config Object Initialization function. 
```c
void mux_cfg_setup ( mux_cfg_t *cfg );
``` 
 
- `mux_init` Initialization function. 
```c
err_t mux_init ( mux_t *ctx, mux_cfg_t *cfg );
```

- `mux_default_cfg` Click Default Configuration function. 
```c
void mux_default_cfg ( mux_t *ctx );
```

- `mux_active_mux_channel` Seelect active MUX channel. 
```c
void mux_active_mux_channel ( mux_t *ctx, uint8_t sel_ch );
```
 
- `mux_device_disable` Disable MUX device function. 
```c
void mux_device_disable ( mux_t *ctx );
```

- `mux_device_enable` Enable MUX device function. 
```c
void mux_device_enable ( mux_t *ctx );
```

### Application Init

> Initializes GPIO module and sets RST, CS and PWM pins as OUTPUT.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mux_cfg_t cfg;

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

    mux_cfg_setup( &cfg );
    MUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mux_init( &mux, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, "        MUX Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    
    mux_device_enable( &mux );
    log_printf( &logger, "    Enable MUX device\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Changes currently active channel every 5 sec.

```c
void application_task ( void )
{
    uint16_t n_cnt;
    
    for ( n_cnt = MUX_CHANNEL_1A_AND_1B; n_cnt < MUX_CHANNEL_END; n_cnt++ )
    {
        log_printf( &logger, "      CHANNEL  S%u\r\n", n_cnt );
        log_printf( &logger, "------------------------\r\n" );
        
        mux_active_mux_channel( &mux, n_cnt );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
