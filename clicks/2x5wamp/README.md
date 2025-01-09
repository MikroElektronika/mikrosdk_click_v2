
---
# 2X5W AMP Click

> [2X5W AMP Click](https://www.mikroe.com/?pid_product=MIKROE-2477) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2477&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

>
> This is a example which demonstrates the use of 2x5W Amp Click board.
> 2x5W AMP Click functions as an amplifier and features the TDA7491LP 
> 2x5-watt dual BTL class-D audio amplifier.
> It communicates with the target MCU over the following pins
> on the mikroBUS&trade; line: AN, RST, CS, PWM, INT.
>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.2x5WAmp

### Example Key Functions

- `c2x5wamp_cfg_setup` Config Object Initialization function. 
```c
void c2x5wamp_cfg_setup ( c2x5wamp_cfg_t *cfg );
``` 
 
- `c2x5wamp_init` Initialization function. 
```c
err_t c2x5wamp_init ( c2x5wamp_t *ctx, c2x5wamp_cfg_t *cfg );
```

- `c2x5wamp_default_cfg` Click Default Configuration function. 
```c
void c2x5wamp_default_cfg ( c2x5wamp_t *ctx );
```

- `c2x5wamp_set_mode` Set mode selection of the amplifier function. . 
```c
uint8_t c2x5wamp_set_mode ( c2x5wamp_t *ctx, uint8_t select_mode );
```

- `c2x5wamp_set_gain` Set Gain resistors of the amplifier function. 
```c
uint8_t c2x5wamp_set_gain ( c2x5wamp_t *ctx, uint8_t select_gain );
```

- `c2x5wamp_check_input` Check input impedance function. 
```c
uint8_t c2x5wamp_check_input ( c2x5wamp_t *ctx );
```

### Application Init

>
> Initializes GPIO and LOG structures,
> set INT pin as input and sets AN, RST, CS and PWM pins as output.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c2x5wamp_cfg_t cfg;

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
    log_printf( &logger, "-- Application Init --\r\n" );
    Delay_ms ( 100 );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    2x5W Amp  Click    \r\n" );
    log_printf( &logger, "-----------------------\r\n" );

    //  Click initialization.

    c2x5wamp_cfg_setup( &cfg );
    C2X5WAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c2x5wamp_init( &c2x5wamp, &cfg );
    Delay_ms ( 100 );
    
    c2x5wamp_default_cfg ( &c2x5wamp );
    Delay_ms ( 100 );
}
```

### Application Task

>
> This is a example which demonstrates the use of 2x5W Amp Click board.
> This examples first activates operation mode MUTE for 5 seconds and after that activates operation mode PLAY.
> When the device is in Play mode then changes the gain selection, the first sets the minimum gain ( 20dB ) for 10 seconds
> and then sets the maximum gain (32dB) for 5 seconds too.
> Results are being sent to the Usart Terminal where you can track their changes.
> 

```c
void application_task ( void )
{
    c2x5wamp_set_mode( &c2x5wamp, C2X5WAMP_MODE_MUTE );

    log_printf( &logger, "       MUTE  MODE      \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "-----------------------\r\n" );

    if ( c2x5wamp_set_mode( &c2x5wamp, C2X5WAMP_MODE_PLAY ) )
    {
        log_printf( &logger, "       PLAY  MODE       \r\n" );
    }
    else
    {
        log_printf( &logger, "    ERROR PLAY MODE    \r\n" );
    }

    log_printf( &logger, "-----------------------\r\n" );

    c2x5wamp_set_gain( &c2x5wamp, C2X5WAMP_GAIN_20DB );

    log_printf( &logger, "   Gain set to  20dB   \r\n" );
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
    log_printf( &logger, "- - - - - - - - - - - -\r\n" );

    c2x5wamp_set_gain( &c2x5wamp, C2X5WAMP_GAIN_32DB );

    log_printf( &logger, "   Gain set to  32dB   \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "-----------------------\r\n" );
}
```

### Note

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
