 

---
# MOTION click

MOTION click is a motion detector sensitive only to live bodies. It carries PIR500B, a pyroelectric sensor. The click is designed to run on 3.3V power supply only.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/motion_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/motion-click>)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Motion Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Motion Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void motion_cfg_setup ( motion_cfg_t *cfg ); 
 
- Initialization function.
> MOTION_RETVAL motion_init ( motion_t *ctx, motion_cfg_t *cfg );

- Click Default Configuration function.
> void motion_default_cfg ( motion_t *ctx );


#### Example key functions :

- Motion detected function
> motion_pin_state_t motion_detected ( motion_t *ctx );
 
- Set states of the enable pin
> void motion_set_en_pin (  motion_t *ctx, motion_pin_state_t en_state );

## Examples Description

> This application detects any motion around it and shows message

**The demo application is composed of two sections :**

### Application Init 

> Initializes Driver enable's the motion detection.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    motion_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");
    log_printf( &logger, "------------------------\r\n" );

    //  Click initialization.

    motion_cfg_setup( &cfg );
    MOTION_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    motion_init( &motion, &cfg );
    log_printf( &logger, "      Motion Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );

    motion_default_cfg ( &motion );
    log_printf( &logger, "  Enable Motion sensor\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 100 );

    motion_state = MOTION_NO_DETECT;
    motion_old_state = MOTION_DETECTED;
}
  
```

### Application Task

> Detect the motion and send a notification to the UART.

```c

void application_task ( void )
{
    //  Task implementation.

    motion_state = motion_detected( &motion );

    if ( motion_state == MOTION_DETECTED &&  motion_old_state == MOTION_NO_DETECT )
    {
        motion_old_state = MOTION_DETECTED;
        log_printf( &logger, "  > Motion detected! <\r\n" );
        log_printf( &logger, "------------------------\r\n" );
   }

   if ( motion_old_state == MOTION_DETECTED &  motion_state == MOTION_NO_DETECT )
   {
        log_printf( &logger, "  There is no movement\r\n" );
        log_printf( &logger, "------------------------\r\n" );
        motion_old_state = MOTION_NO_DETECT;
   }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Motion

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
