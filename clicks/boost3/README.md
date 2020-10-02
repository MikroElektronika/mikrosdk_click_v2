\mainpage Main Page
 
---
# Boost 3 click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Boost3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Boost3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void boost3_cfg_setup ( boost3_cfg_t *cfg ); 
 
- Initialization function.
> BOOST3_RETVAL boost3_init ( boost3_t *ctx, boost3_cfg_t *cfg );

#### Example key functions :

- Function is used to enable or disable the device.
> void boost3_dev_enable ( boost3_t *ctx, uint8_t state );

## Examples Description

> Boost 3 click provides an adjustable output voltage through the onboard
> potentiometer. The chip is a 700-kHz pulse-width modulating (PWM) step-up 
> converter with an 85-V switch FET with an input ranging from 2.5 V to 5.5 V. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO and LOG structures, and set CS pin as output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    boost3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    boost3_cfg_setup( &cfg );
    BOOST3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost3_init( &boost3, &cfg );
}
  
```

### Application Task

> Demonstrates use of Boost 3 click board by by reading 
> user's command input from USART terminal and turning the
> device on or off accordingly. User can use the on-board
> potentiometer to adjust 'Vout' voltage.

```c

void application_task ( void )
{
    char cmd;
    
    if ( log_read ( &logger, &cmd, 1 ) != -1)
    {
        cmd -= 48;
        boost3_dev_enable( &boost3, cmd );
        
        if ( cmd == BOOST3_ENABLE )
        {
             log_printf( &logger, "The device is turned on!\r\n" );
             log_printf( &logger, "Use on-board potentiometer\r\n" );
             log_printf( &logger, " to adjust 'Vout' voltage\r\n" );
        }
        else
        {
             log_printf( &logger, "The device is turned off!\r\n" );
        }
        Delay_ms( 10000 );
    }
    else
    {
        log_printf( &logger, "Send '1' to turn the device on\r\n" );
        log_printf( &logger, "Send '0' to turn the device off\r\n" );
        Delay_ms( 2000 );
    }
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost3

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
