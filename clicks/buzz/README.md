\mainpage Main Page
 
---
# Buzz click

BUZZ Click is an accessory board in mikroBus™ form factor. Board features a piezo speaker capable of emitting audio signals.Buzzer’s resonant frequency is 3.8kHz (where you can expect it’s best performance).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/buzz-click-group.png" height=300px>
</p>

[click Product page - BUZZ](https://www.mikroe.com/buzz-click)
[click Product page - BUZZ2](https://www.mikroe.com/buzz-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Aug 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Buzz Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly from compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buzz Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buzz_cfg_setup ( buzz_cfg_t *cfg ); 
 
- Initialization function.
> BUZZ_RETVAL buzz_init ( buzz_t *ctx, buzz_cfg_t *cfg );


#### Example key functions :

- This function plays sound on buzzer.
> void buzz_play_sound ( buzz_t *ctx, uint16_t freq, uint8_t level, uint8_t duration );

## Examples Description

> This example demonstrates the use of Buck click boards.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buzz_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buzz_cfg_setup( &cfg );
    BUZZ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buzz_init( &buzz, &cfg );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Plays the Imperial March melody. Also logs an appropriate message on the USB UART.

```c

void application_task ( void )
{
    log_printf( &logger, "Playing the Imperial March melody ...\r\n" );
    imperial_march( ); 
    Delay_ms( 10000 );
}  

```

## Note
> The minimal PWM Clock frequency required for this example is the frequency of tone C6 - 1047 Hz. 
> So, in order to run this example and play all tones correctly, the user will need to decrease 
> the MCU's main clock frequency in MCU Settings for the certain architectures
> in order to get the required PWM clock frequency.

The full application code, and ready to use projects can be installed directly from compilers IDE(recommended) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buzz

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
