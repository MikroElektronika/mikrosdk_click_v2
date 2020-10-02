\mainpage Main Page
 
 

---
# HAPTIC click

< Haptic click carries DRV2605, a Haptic Driver for ERM and LRA vibration motors (acronyms stand for Eccentric Rotating Mass and Linear Resonant Actuator, respectively) >

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/haptic_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/haptic-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Haptic Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Haptic Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void haptic_cfg_setup ( haptic_cfg_t *cfg ); 
 
- Initialization function.
> HAPTIC_RETVAL haptic_init ( haptic_t *ctx, haptic_cfg_t *cfg );


#### Example key functions :

- Enable the device function.
> void haptic_enable (  haptic_t *ctx );
 
-  Disable the device function.
> void haptic_disable ( haptic_t *ctx );

- Sets the Haptic click to desired mode function.
> void haptic_set_mode ( haptic_t *ctx, uint8_t sel_mode );

## Examples Description

> This application generate vibrations from the lower frequency range of the audio input. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C, first, we enable the device, set soft reset, set calibrating and start the engine. After that, we set Audio-to-Vibe mode, Minimum Input level ( ~ 1.35V ), enable AC coupling, select input mode for Analog input and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    haptic_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    haptic_cfg_setup( &cfg );
    HAPTIC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    haptic_init( &haptic, &cfg );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "     Haptic  Click     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );

    haptic_enable( &haptic );

    start_status = 1;

    log_printf( &logger, "        Enabled        \r\n" );
    Delay_ms( 200 );

    haptic_soft_reset( &haptic );
    log_printf( &logger, "         Reset         \r\n" );
    Delay_ms( 200 );

    haptic_set_mode( &haptic, HAPTIC_MODE_AUTOCAL );

    log_printf( &logger, "     Calibrating...    \r\n" );
    Delay_ms( 1000 );

    haptic_start_motor( &haptic );
    log_printf( &logger, "   Start the engine    \r\n" );
    Delay_ms( 1000 );
    log_printf( &logger, "-----------------------\r\n" );

    haptic_set_mode( &haptic, HAPTIC_MODE_AUDIOVIBE );

    log_printf( &logger, " Set Audio-to-Vibe mode\r\n" );

    haptic_set_audio_minimum_input( &haptic, HAPTIC_DEFAULT_MIN_INPUT );

    log_printf( &logger, "  Minimum Input level  \r\n" );
    log_printf( &logger, "      About 1.35V      \r\n" );

    haptic_enable_ac_coulping( &haptic );
    log_printf( &logger, "  Enable  AC coupling  \r\n" );

    haptic_set_input_to_analog( &haptic );
    log_printf( &logger, " Sets input -  analog  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}
  
```

### Application Task

> This is a example which demonstrates the use of Haptic Click board. Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    if ( start_status )
        log_printf( &logger, "         START         \r\n" );

    start_status = 0;
}
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Haptic

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
