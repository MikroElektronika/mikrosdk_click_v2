
 

---
# Air quality 4 click

Air quality 4 click is an advanced air quality sensing device that combines multiple metal-oxide sensing elements on a chip to provide detailed information of the air quality parameters.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/airquality4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/air-quality-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the AirQuality4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AirQuality4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void airquality4_cfg_setup ( airquality4_cfg_t *cfg ); 
 
- Initialization function.
> AIRQUALITY4_RETVAL airquality4_init ( airquality4_t *ctx, airquality4_cfg_t *cfg );

- Click Default Configuration function.
> void airquality4_default_cfg ( airquality4_t *ctx );


#### Example key functions :

- Function calls general reset witch resets all states on the chip.
> void air_quality4_soft_reset( airquality4_t *ctx );
 
- Function writes 2 bytes CO2 data and 2 bytes TVOC data without CRC data.
> void air_quality4_get_co2_and_tvoc( airquality4_t *ctx, uint16_t *value);

- Function writes 2 bytes H2 data and 2 bytes EthOH data without CRC data.
> void air_quality4_get_h2_and_ehtoh( airquality4_t *ctx, uint16_t *value );

## Examples Description

> This example measures the quality od air.

**The demo application is composed of two sections :**

### Application Init 

>Initializes click driver and gets ID data.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality4_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    airquality4_cfg_setup( &cfg );
    AIRQUALITY4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality4_init( &airquality4, &cfg );
    airquality4_default_cfg( &airquality4 );
}
  
```

### Application Task

> Performs measurements of air concentracion for H2, EthOH, CO2 and TVOC data.

```c

void application_task ( void )
{
    air_quality4_get_h2_and_ethon( &airquality4, data_buffer);

    log_printf( &logger, "H2 value is: %u\n", data_buffer[ 0 ] );
    log_printf( &logger, "EthOH value is:  %u\n", data_buffer[ 1 ] );

    air_quality4_set_baseline( &airquality4 );
    air_quality4_get_co2_and_tvoc( &airquality4, &data_buffer[ 0 ] );
    
    log_printf( &logger, "CO2 value is: %u\n", data_buffer[ 0 ] );
    log_printf( &logger, "TVOC value is: %u\n\n", data_buffer[ 1 ] );

    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality4

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
