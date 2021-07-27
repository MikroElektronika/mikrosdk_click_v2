\mainpage Main Page
 
 

---
# Temp&Hum 10 click

Temp&Hum 10 Click is a smart temperature and humidity sensing Click board™, aimed towards IoT applications, due to its extremely small size and very low power consumption.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temphum-10-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum10 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum10 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum10_cfg_setup ( temphum10_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHUM10_RETVAL temphum10_init ( temphum10_t *ctx, temphum10_cfg_t *cfg );

#### Example key functions :

- Functions for read Temperature data
> float temphum10_get_temperature ( temphum10_t *ctx );
 
- Functions for sets Device mode
> void temphum10_set_device_mode ( temphum10_t *ctx, uint8_t mode );

- Functions for repeat measurement
> void temphum10_repeat_measurement ( temphum10_t *ctx, uint8_t average );

## Examples Description

> This application measures temperature and humidity. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and sets device mode

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum10_cfg_t cfg;
    uint8_t tmp;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum10_cfg_setup( &cfg );
    TEMPHUM10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum10_init( &temphum10, &cfg );

    log_info( &logger, "---- Device config ----" );
    
    temphum10_set_device_mode( &temphum10, TEMPHUM10_MODE_STANDBY );
    Delay_ms( 100 );
    
    tmp = TEMPHUM10_RST_NORMAL_OPERATION;
    temphum10_generic_write( &temphum10, TEMPHUM10_REG_DEVICE_RESET, &tmp, 1 );
    Delay_ms( 100 );
    log_info( &logger, "---- Device calibration ----" );
    tmp = TEMPHUM10_AM_TIMES_AVERAGE_MODE_8 | TEMPHUM10_AM_TEMP_AVERAGE_MODE_TIMES_16;
    temphum10_repeat_measurement( &temphum10, tmp );
    temphum10_get_temperature( &temphum10 );
    temphum10_get_humidity( &temphum10 );
    Delay_ms( 100 );
    temphum10_repeat_measurement( &temphum10, tmp );
    temphum10_get_temperature( &temphum10 );
    temphum10_get_humidity( &temphum10 );
    log_info( &logger, "---- Application Task ----" );
}
  
```

### Application Task

> Reads Temperature and Humidity data and logs this data to USBUART every 1 sec.

```c

void application_task ( )
{
    float temperature = 0;
    float humidity = 0;
    uint8_t tmp;
    
    tmp = TEMPHUM10_AM_TIMES_AVERAGE_MODE_8 | TEMPHUM10_AM_TEMP_AVERAGE_MODE_TIMES_16;
    temphum10_repeat_measurement( &temphum10, tmp );
    temperature = temphum10_get_temperature( &temphum10 );
    humidity = temphum10_get_humidity( &temphum10 );
    
    log_printf( &logger, " Temperature : %.2f \r\n", temperature );
    log_printf( &logger, " Humidity :  %.2f \r\n", humidity );
    log_printf( &logger, "---------------------\r\n" );

    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum10

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
