\mainpage Main Page
 
---
# MIC 3 click

The MIC 3 Click is a Click board™ that features the SSM2167-1RMZ-R7, a Microphone Preamplifier, from Analog Device. This Click board™ is a low voltage Microphone preamplifier with Variable compression and noise gating.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](https://www.mikroe.com/mic-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Mic3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mic3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mic3_cfg_setup ( mic3_cfg_t *cfg ); 
 
- Initialization function.
> MIC3_RETVAL mic3_init ( mic3_t *ctx, mic3_cfg_t *cfg );


#### Example key functions :

- This function set SHD pin to desired state.
> void mic3_set_shd_pin ( mic3_t *ctx, uint8_t state );

## Examples Description

> The MIC 3 Click is a very easy solution to work with it. It can be used for desktop, 
> portable or palmtop computers, telephone conferencing, communication headsets, two-way 
> communication, surveillance system where the microphone is needed, stethoscope, karaoke 
> and DJ mixers.

**The demo application is composed of two sections :**

### Application Init 

> Maps GPIO for Mikrobus1.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    mic3_cfg_setup( &cfg );
    MIC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic3_init( &mic3, &cfg );
}
  
```

### Application Task

> This example show use of MIC 3 click. It sets SHD pin to HIGH state, 
> so the Microphone is ready to use.

```c

void application_task ( void )
{
    mic3_set_shd_pin( &mic3, MIC3_PIN_STATE_HIGH );
    log_printf( &logger, " ***** APP TASK ***** \r\n" );
    log_printf( &logger, " - Microphone is turned on - \r\n" );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic3

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
