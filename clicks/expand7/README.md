\mainpage Main Page
 
---
# Expand 7 click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Expand7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void expand7_cfg_setup ( expand7_cfg_t *cfg ); 
 
- Initialization function.
> EXPAND7_RETVAL expand7_init ( expand7_t *ctx, expand7_cfg_t *cfg );


#### Example key functions :

- Select a PWM output pin function
> void expand7_sel_pwm_pin ( expand7_t *ctx, uint16_t pin, uint8_t pwm_en );
 
- Enable Register Configuration function
> void expand7_eeprom_enable ( expand7_t *ctx, uint8_t cmd );

- Get Interrupt state function
> uint8_t expand7_check_int ( expand7_t *ctx );

## Examples Description

> This demo app shows the capabilities of the EXPAND 7 click. 

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand7_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    expand7_cfg_setup( &cfg );
    EXPAND7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand7_init( &expand7, &cfg );
    Delay_ms( 100 );

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   EXPAND 7 click   \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}
  
```

### Application Task

> This example shows the capabilities of the
>EXPAND 7 click by toggling each of 40 available pins.

```c

void application_task ( void )
{
    for ( pin_num = 0; pin_num < 40; pin_num++ )
    {
        expand7_write_all ( &expand7, 0xFF );
        
        expand7_write_pin( &expand7, pin_num, EXPAND7_LOW );
        log_printf( &logger, "Pin %d is low! \r\n", pin_num );

        Delay_ms( 200 );
        expand7_write_all ( &expand7, 0xFF );
    }
    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand7

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
