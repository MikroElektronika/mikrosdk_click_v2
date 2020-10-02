\mainpage Main Page
 
---
# NO 2 click

NO2 click is a very accurate nitrogen-dioxide gas sensor Click board™, equipped with the SPEC amperometric gas sensor which electrochemically reacts with the nitrogen-dioxide (NO2). 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/no2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/no2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the No2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for No2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void no2_cfg_setup ( no2_cfg_t *cfg ); 
 
- Initialization function.
> NO2_RETVAL no2_init ( no2_t *ctx, no2_cfg_t *cfg );

- Click Default Configuration function.
> void no2_default_cfg ( no2_t *ctx );


#### Example key functions :

- Device Enable function
> void no2_enable ( no2_t *ctx, uint8_t state );
 
- Function for read ADC sensor data
> uint16_t no2_read_adc ( no2_t *ctx );

- Get NO2 Data function
> float no2_get_no_2_ppm ( no2_t *ctx );

## Examples Description

> This application measures NO2.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver and device configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    no2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    no2_cfg_setup( &cfg );
    NO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    no2_init( &no2, &cfg );

    no2_default_cfg( &no2 );

    log_printf( &logger, "NO2 is initialized \r\n" );
    Delay_ms( 300 );
}
  
```

### Application Task

> Gets NO2 (Nitrogen dioxide) data as ppm value and logs to USBUART every 500ms.

```c

void application_task ( void )
{
    float no2_value;

    no2_value = no2_get_no_2_ppm( &no2 );
    log_printf( &logger, "NO2 value : %.2f ppm \r\n", no2_value );
    Delay_ms( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.No2

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
