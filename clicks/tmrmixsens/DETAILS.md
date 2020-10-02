
---
# TMR MIX SENS click

The TMR mix-sens Click is an add-on board equipped with the TMR digital push-pull and analog magnetic sensors, as well as intensity of magnetic field indicator.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](< https://www.mikroe.com/tmr-mix-sens-click > )

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : ADC type


# Software Support

We provide a library for the Tmrmixsens Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Tmrmixsens Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void tmrmixsens_cfg_setup ( tmrmixsens_cfg_t *cfg ); 
 
- Initialization function.
> TMRMIXSENS_RETVAL tmrmixsens_init ( tmrmixsens_t *ctx, tmrmixsens_cfg_t *cfg );

#### Example key functions :

- Generic read function.
> tmrmixsens_data_t tmrmixsens_generic_read ( tmrmixsens_t *ctx );
 
- Get state of the omnipolar ( OMN ) pin function.
> uint8_t tmrmixsens_get_omnipolar ( tmrmixsens_t *ctx );

- Get state of the bipolar ( BI ) pin function.
> uint8_t tmrmixsens_get_bipolar ( tmrmixsens_t *ctx );

## Examples Description

> The TMR mix-sens Click has three types of magnetic field sensors: Two digital and one analog sensor. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - GPIO, initializes ADC and set ADC channel.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    tmrmixsens_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    tmrmixsens_cfg_setup( &cfg );
    TMRMIXSENS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tmrmixsens_init( &tmrmixsens, &cfg );
}
  
```

### Application Task

> This is a example which demonstrates the use of TMR mix-sens Click board.
  This examples respond to changes north or south magnetic pole and display ADC data value.
  Results are being sent to the Usart Terminal where you can track their changes.
  All data logs on usb uart for aproximetly every 1 sec.

```c

void application_task ( void )
{
    tmrmixsens_data_t tmp;
    
    tmp = tmrmixsens_generic_read ( &tmrmixsens );
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    Delay_ms( 1000 );

    if ( tmrmixsens_get_bipolar( &tmrmixsens ) == TMRMIXSENS_NORT_POLE )
    {
        log_printf( &logger, " ~~~ Nort  pole ~~~ \r\n" );
    }
    else if( tmrmixsens_get_bipolar( &tmrmixsens ) == TMRMIXSENS_SOUTH_POLE )
    {
        log_printf( &logger, " ~~~ South pole ~~~ \r\n" );
    }
    
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Tmrmixsens

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
