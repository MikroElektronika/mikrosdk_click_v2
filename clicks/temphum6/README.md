\mainpage Main Page
 
 

---
# Temp Hum 6 click

Temp&Hum 6 click is a smart temperature and humidity sensing click board™, packed with features that allow easy and simple integration into any design. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum6_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/temphum-6-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum6_cfg_setup ( temphum6_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHUM6_RETVAL temphum6_init ( temphum6_t *ctx, temphum6_cfg_t *cfg );

- Click Default Configuration function.
> void temphum6_default_cfg ( temphum6_t *ctx );


#### Example key functions :

- This function returns read Temperature data.
> float temphum6_read_temperature ( temphum6_t *ctx, uint8_t temp_in );
 
- This function returns read relative Humidity data.
> float temphum6_read_relative_huminidy( temphum6_t *ctx );

- This function returns the device part id.
> uint16_t temphum6_get_part_id ( temphum6_t *ctx );

## Examples Description

> This application emasures temperature and humidity.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and reset device and read Part ID

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum6_cfg_t cfg;
    uint16_t part_id;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum6_cfg_setup( &cfg );
    TEMPHUM6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum6_init( &temphum6, &cfg );

    temphum6_reset( &temphum6 );
    
    part_id = temphum6_get_part_id( &temphum6 );
    if ( part_id == TEMPHUM6_PART_ID )
    {
        log_printf( &logger, "Device OK - read ID is OK" );
    }
    else
    {
        log_printf( &logger, "Device ERROR - read ID is NOT OK" );
    }
}
  
```

### Application Task

> Reads Temperature and Huminidy data and logs this data to USBUART every 1sec.

```c

void application_task ( void )
{
    //  Task implementation.

    float temp;
    float hum;

    temp = temphum6_read_temperature( &temphum6, TEMPHUM6_TEMP_IN_CELSIUS );
    log_printf( &logger, "Temperature is %f C\r\n");
    
    hum = temphum6_read_relative_huminidy( &temphum6 );
    log_printf( &logger, "Huminidy is %f %%RH\r\n");
    
    log_printf( &logger, "------------------\r\n");
    Delay_ms( 1000 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum6

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
