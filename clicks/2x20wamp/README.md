
---
# c2x20W Amp Click

> [2x20W Amp Click](https://www.mikroe.com/?pid_product=MIKROE-2779) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2779&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application changes the volume level.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.2x20WAmp

### Example Key Functions

- `c2x20wamp_cfg_setup` Config Object Initialization function. 
```c
void c2x20wamp_cfg_setup ( c2x20wamp_cfg_t *cfg );
``` 
 
- `c2x20wamp_init` Initialization function. 
```c
err_t c2x20wamp_init ( c2x20wamp_t *ctx, c2x20wamp_cfg_t *cfg );
```

- `c2x20wamp_mode_play` Set Play mode of the amplifier function. 
```c
void c2x20wamp_mode_play ( c2x20wamp_t *ctx );
```
 
- `c2x20wamp_set_volume` Set volume of the amplifier function. 
```c
void c2x20wamp_set_volume ( c2x20wamp_t *ctx, uint8_t volume );
```

- `c2x20wamp_mode_mute` Set Mute mode of the amplifier function. 
```c
void c2x20wamp_mode_mute ( c2x20wamp_t *ctx );
```

### Application Init

> Initialization driver enable's - I2C,
     start write log and enable amplifire of 2x20W Amp Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c2x20wamp_cfg_t cfg;

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

    c2x20wamp_cfg_setup( &cfg );
    C2X20WAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c2x20wamp_init( &c2x20wamp, &cfg );
    
    Delay_ms ( 100 );

    log_info( &logger, "-----------------------\r\n    2x20W Amp Click    \r\n-----------------------" );
    c2x20wamp_enable( &c2x20wamp );
    log_info( &logger,"   Enable  Amplifier   \r\n-----------------------");

    Delay_ms ( 200 );
}  
```

### Application Task

> This is a example which demonstrates the use of 2x20W Amp Click board.
     This examples first activates operation mode PLAY and set volume lvl 32 ( 50% ),
     after that, we increase the volume level one level ten times for 5 seconds and
     we decrease the volume level one level ten times for 5 seconds.
     And finally, we set MUTE mode for next 5 seconds.
     Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    int cnt;
    
    log_info( &logger, "       PLAY MODE       " );
    c2x20wamp_mode_play( &c2x20wamp );
    
    log_info( &logger, "-----------------------\r\n  Set Volume lvl : 32  " );
    c2x20wamp_set_volume( &c2x20wamp, 32 );

    log_info( &logger, "- - - - - - - - - - - -" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    for ( cnt = 0; cnt < 10; cnt++ )
    {
        log_info( &logger, "       Volume Up       " );

        c2x20wamp_volume_up( &c2x20wamp );

        Delay_ms ( 100 );
    }

    log_info( &logger, "- - - - - - - - - - - -" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    for ( cnt = 0; cnt < 10; cnt++ )
    {
        log_info( &logger, "       Volume Down       " );

        c2x20wamp_volume_down( &c2x20wamp );

        Delay_ms ( 100 );
    }

    log_info( &logger, "-----------------------" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_info( &logger, "       MUTE MODE       " );

    c2x20wamp_mode_mute( &c2x20wamp );

    log_info( &logger, "-----------------------" );

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
