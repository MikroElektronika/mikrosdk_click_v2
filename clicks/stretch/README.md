\mainpage Main Page
 
 

---
# Stretch click

Stretch click is a mikroBUS™ add-on board with circuitry for measuring stretch forces with conductive rubber cords.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stretch_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/stretch-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : ADC type


# Software Support

We provide a library for the Stretch Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Stretch Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void stretch_cfg_setup ( stretch_cfg_t *cfg ); 
 
- Initialization function.
> STRETCH_RETVAL stretch_init ( stretch_t *ctx, stretch_cfg_t *cfg );

- Click Default Configuration function.
> void stretch_default_cfg ( stretch_t *ctx );


#### Example key functions :

- Config Object Initialization function.
> void stretch_cfg_setup ( stretch_cfg_t *cfg )
 
- Turn on the LED function
> void stretch_turn_on_led( stretch_t *ctx )

- Turn off the LED function
> void stretch_turn_off_led( stretch_t *ctx )

## Examples Description

> The application is for stretch measuring  

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables GPIO and ADC, turn off the LED and starts write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    stretch_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    stretch_cfg_setup( &cfg );
    STRETCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stretch_init( &stretch, &cfg );

    Delay_100ms();

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "  Stretch  click  "  );
    log_printf( &logger, "-------------------\r\n" );

    stretch_turn_off_led( &stretch );
    Delay_100ms( );

    log_printf( &logger, " ADC Initializated " );
    log_printf( &logger, "-------------------" );
}
  
```

### Application Task

> This is a example which demonstrates the use of Stretch Click board. Stretch Click reads and display ADC value.

```c

void application_task ( void )
{
    stretch_data_t tmp;
    
    //  Task implementation.
    
    tmp = stretch_generic_read ( &stretch );
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    Delay_ms( 1000 );

    Delay_100ms( );
    
    if ( tmp < 500 )
    {
        stretch_turn_on_led( &stretch );
    }
        
    else
    {
        stretch_turn_off_led( &stretch );
    }

    log_printf( &logger, " Resistance : %d \r\n", tmp );
    log_printf( &logger, "-------------------" );
    Delay_1sec( );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Stretch

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
