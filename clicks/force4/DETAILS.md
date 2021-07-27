
---
# Force 4 click

Force 4 Click is based on HSFPAR003A piezoresistive force sensor from Alpsalpine. This product is a force sensor using the effect of a piezoresistive bridge circuit formed on silicon diaphragm.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/force4_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/force-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Force4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Force4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void force4_cfg_setup ( force4_cfg_t *cfg ); 
 
- Initialization function.
> FORCE4_RETVAL force4_init ( force4_t *ctx, force4_cfg_t *cfg );


#### Example key functions :

- This function reads 12bit ADC data from device.
> uint16_t force4_read_adc ( force4_t *ctx )


## Examples Description

> This example shows the use of Force 4 Click.
> It reads 12bit ADC value, using I2C communication,
> at the interval of one second. 
> The result is represented on the UART terminal.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and logger, and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    force4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    force4_cfg_setup( &cfg );
    FORCE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force4_init( &force4, &cfg );
    Delay_ms( 100 );
}
  
```

### Application Task

> It reads 12bit ADC value, using I2C communication,
> at the interval of one second.
> The result is represented on the UART terminal.

```c

void application_task ( void )
{
    adc_val = force4_read_adc( &force4 );
    log_printf( &logger, "ADC value: %d\r\n", adc_val );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Force4

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
