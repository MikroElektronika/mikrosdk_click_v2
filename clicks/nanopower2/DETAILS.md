

---
# Nano Power 2 click

Nano Power 2 click is a very low power voltage comparator, aimed at portable 
and battery-powered applications. It allows detecting a difference of two 
voltage potentials, applied on two input pins. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nanopower2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nano-power-2-click)

---


#### Click library 

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the NanoPower2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for NanoPower2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void nanopower2_cfg_setup ( nanopower2_cfg_t *cfg ); 
 
- Initialization function.
> NANOPOWER2_RETVAL nanopower2_init ( nanopower2_t *ctx, nanopower2_cfg_t *cfg );

- Click Default Configuration function.
> void nanopower2_default_cfg ( nanopower2_t *ctx );


#### Example key functions :

- Function gets output voltage from comparator.
> NANOPOWER2_RETVAL nanopower2_check_output ( nanopower2_t *ctx );
 

## Examples Description

> This example logs the comparators output value.


**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO driver.

```c

void application_init ( void )
{
	log_cfg_t log_cfg;
    nanopower2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    nanopower2_cfg_setup( &cfg );
    NANOPOWER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanopower2_init( &nanopower2, &cfg );

	log_printf( &logger, "NANO POWER 2 is initialized\r\n" );
	out_check_prev = 2;
}
  
```

### Application Task

> Checks the comparator's output and logs output value on USBUART.

```c

void application_task ( void )
{
	out_check = nanopower2_check_output( &nanopower2 );
	if ( out_check != out_check_prev )
	{
		log_printf( &logger, "OUT is: %d\r\n", out_check );

		out_check_prev = out_check;
	}
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoPower2

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
