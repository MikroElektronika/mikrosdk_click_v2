
---
# 2X5W AMP click

 2x5W AMP click functions as an amplifier and features the TDA7491LP 2x5-watt dual BTL class-D audio amplifier. The click is designed to run on either 3.3V or 5V power supply. It communicates with the target MCU over the following pins on the mikroBUS™ line: AN, RST, CS, PWM, INT.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/2x5wamp_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/2x5w-amp-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the 2x5WAmp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 2x5WAmp Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c2x5wamp_cfg_setup ( c2x5wamp_cfg_t *cfg ); 
 
- Initialization function.
> C2X5WAMP_RETVAL c2x5wamp_init ( c2x5wamp_t *ctx, c2x5wamp_cfg_t *cfg );

- Click Default Configuration function.
> void c2x5wamp_default_cfg ( c2x5wamp_t *ctx );


#### Example key functions :

- Set mode selection of the amplifier function. 
> uint8_t c2x5wamp_set_mode( c2x5wamp_t *ctx, uint8_t select_mode );

- Set Gain resistors of the amplifier function.
> uint8_t c2x5wamp_set_gain( c2x5wamp_t *ctx, uint8_t select_gain );

- Check input impedance function.
> uint8_t c2x5wamp_check_input( c2x5wamp_t *ctx );


**The demo application is composed of two sections :**

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

## Note

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.2x5WAmp

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
