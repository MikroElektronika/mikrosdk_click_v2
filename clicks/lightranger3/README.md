\mainpage Main Page
 
 

---
# Light Ranger 3 click

Light Ranger 3 click is an accurate distance measurement Click board™ based on a ToF ( Time of Flight ) measurement principle. The Simblee™ enabled RFD77402 rangefinder module from RF Digital is a complete measurement stack on the chip.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lightranger3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/lightranger-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the LightRanger3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LightRanger3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lightranger3_cfg_setup ( lightranger3_cfg_t *cfg ); 
 
- Initialization function.
> LIGHTRANGER3_RETVAL lightranger3_init ( lightranger3_t *ctx, lightranger3_cfg_t *cfg );

- Click Default Configuration function.
> void lightranger3_default_cfg ( lightranger3_t *ctx );


#### Example key functions :

- This function go to measurement mode.
> uint8_t lightranger3_set_measurement_mode ( lightranger3_t *ctx );
 
- This function reads distance.
> uint16_t lightranger3_get_distance ( lightranger3_t *ctx );

- This function reads confidence value.
> uint16_t lightranger3_get_confidence_value ( lightranger3_t *ctx );

## Examples Description

> This app precisely measure distance without making actual contact.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and configuration chip.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lightranger3_cfg_t cfg;
    uint8_t init_status;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    lightranger3_cfg_setup( &cfg );
    LIGHTRANGER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightranger3_init( &lightranger3, &cfg );

    init_status = lightranger3_device_init( &lightranger3 );

    if ( init_status == 0 )
    {
        log_printf( &logger, " --- Device init successfully --- \r\n " );
    }
    else
    {
        log_printf( &logger, " ---  Device init error --- \r\n " );
    }
}
  
```

### Application Task

> Includes measurements, reads distance, and logs distance to USBUART for every 300 ms.
> Distance measurement at distances ranging from 100 mm to 2000 mm. 

```c

void application_task ( void )
{
    uint16_t distance;

    lightranger3_take_single_measurement( &lightranger3 );
    
    distance = lightranger3_get_distance( &lightranger3 );

    log_printf( &logger, "Distance = %u mm \r\n ", distance );

    Delay_ms( 300 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger3

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
