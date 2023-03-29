\mainpage Main Page
 
 

---
# c2x20W Amp click

2x20W Amp click carries the MAX9744 stereo class D audio power amplifier from Maxim Integrated. This click brings the Class AB sound performance with Class D efficiency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/2x20wamp_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/2x20w-amp-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the c2x20WAmp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for c2x20WAmp Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c2x20wamp_cfg_setup ( c2x20wamp_cfg_t *cfg ); 
 
- Initialization function.
> C2X20WAMP_RETVAL c2x20wamp_init ( c2x20wamp_t *ctx, c2x20wamp_cfg_t *cfg );

#### Example key functions :

- Set Play mode of the amplifier function
> void c2x20wamp_mode_play( c2x20wamp_t *ctx );
 
- Set volume of the amplifier function
> void c2x20wamp_set_volume( c2x20wamp_t *ctx, uint8_t volume );

- Set Mute mode of the amplifier function
> void c2x20wamp_mode_mute( c2x20wamp_t *ctx );

## Examples Description

> This application changes the volume level.

**The demo application is composed of two sections :**

### Application Init 

>Initialization driver enable's - I2C,
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
    
    Delay_ms( 100 );

    log_info( &logger, "-----------------------\r\n    2x20W Amp Click    \r\n-----------------------" );
    c2x20wamp_enable( &c2x20wamp );
    log_info( &logger,"   Enable  Amplifier   \r\n-----------------------");

    Delay_ms( 200 );
}  
```

### Application Task

>This is a example which demonstrates the use of 2x20W Amp Click board.
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

    Delay_ms( 5000 );

    for ( cnt = 0; cnt < 10; cnt++ )
    {
        log_info( &logger, "       Volume Up       " );

        c2x20wamp_volume_up( &c2x20wamp );

        Delay_ms( 100 );
    }

    log_info( &logger, "- - - - - - - - - - - -" );

    Delay_ms( 5000 );

    for ( cnt = 0; cnt < 10; cnt++ )
    {
        log_info( &logger, "       Volume Down       " );

        c2x20wamp_volume_down( &c2x20wamp );

        Delay_ms( 100 );
    }

    log_info( &logger, "-----------------------" );

    Delay_ms( 5000 );

    log_info( &logger, "       MUTE MODE       " );

    c2x20wamp_mode_mute( &c2x20wamp );

    log_info( &logger, "-----------------------" );

    Delay_ms( 5000 );
}
``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.2x20WAmp

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
