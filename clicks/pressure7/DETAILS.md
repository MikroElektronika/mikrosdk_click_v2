
---
# Pressure 7 Click

Pressure 7 Click features an integrated digital barometric pressure and temperature sensor labeled as MS5837. This sensor relies on the advanced MEMS technology by MEAS Switzerland, a well-known high-volume MEMS manufacturer.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/pressure-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Pressure7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pressure7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pressure7_cfg_setup ( pressure7_cfg_t *cfg ); 
 
- Initialization function.
> PRESSURE7_RETVAL pressure7_init ( pressure7_t *ctx, pressure7_cfg_t *cfg );

- Click Default Configuration function.
> void pressure7_default_cfg ( pressure7_t *ctx );


#### Example key functions :

- This function reads calibration data from PROM
> uint8_t pressure7_read_PROM( pressure7_t *ctx );
 
- This function starts measurement and calculation data.
> void pressure7_start_measurement(pressure7_t *ctx);

- This function reads pressure and temperature data.
> void pressure7_get_sensor_data( pressure7_t *ctx, float *Temperature, float *Pressure );

## Examples Description


> This example reads temperature and pressure and logs it every 3 seconds. 


**The demo application is composed of two sections :**

### Application Init 

> Initialize Logger and Click object and call pressure7_read_PROM() function.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure7_cfg_t cfg;

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

    pressure7_cfg_setup( &cfg );
    PRESSURE7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure7_init( &pressure7, &cfg );
    pressure7_default_cfg ( &pressure7 );

    //  Read calibrated data from the PROM

    prom_exit_value = pressure7_read_PROM( &pressure7 );
    if ( prom_exit_value == PRESSURE7_PROM_READ_OK )
    {
        log_info( &logger, "Read PROM - OK !\r\n" );
    }
    else
    {
        log_info( &logger, "Read PROM - ERROR!\r\n" );
    }
    Delay_ms ( 100 );
}
  
```

### Application Task

> Get sensor data on every 3 seconds and send measured temperature and pressure to logger.

```c

void application_task ( void )
{
    pressure7_start_measurement( &pressure7 );
    pressure7_get_sensor_data( &pressure7, &Temperature, &Pressure );

    log_printf( &logger, "Temperature: %fC\r\n", Temperature );
    log_printf( &logger, "Pressure: %f\r\n", Pressure );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure7

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
