 
---
# Audio Xover click

Audio Xover Click is an analog active crossover solution for two-way loudspeakers. The primary purpose of the crossover circuit in a loudspeaker is to split an incoming audio signal into frequency bands that are passed to the speaker or “driver” best suited.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](https://www.mikroe.com/audio-xover-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the AudioXover Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AudioXover Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void audioxover_cfg_setup ( audioxover_cfg_t *cfg ); 
 
- Initialization function.
> AUDIOXOVER_RETVAL audioxover_init ( audioxover_t *ctx, audioxover_cfg_t *cfg );

- Click Default Configuration function.
> void audioxover_default_cfg ( audioxover_t *ctx );


#### Example key functions :

## Examples Description

> This example showcases how to initialize, configure and use the Audio Xover click module. The
  click splits an incoming audio signal into two channels. It has one output pin which serves as
  a switch. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the click and logger modules. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioxover_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    audioxover_cfg_setup( &cfg );
    AUDIOXOVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioxover_init( &audioxover, &cfg );
}
  
```

### Application Task

> This function enables and disables the switch with a 3 second delay between and after the 
  function calls. Status feedback is printed in the UART console. 

```c

void application_task ( void )
{
    log_printf( &logger, " * Switch: ON *\r\n" );
    digital_out_write( &audioxover.sdn, AUDIOXOVER_ENABLE );
    Delay_ms( 3000 );

    log_printf( &logger, " * Switch: OFF *\r\n" );
    digital_out_write( &audioxover.sdn, AUDIOXOVER_DISABLE );
    Delay_ms( 3000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioXover

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
