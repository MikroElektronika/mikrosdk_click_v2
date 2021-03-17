
---
# Altitude 4 click

Altitude 4 Click introduces an absolute pressure sensor with digital output for low-cost applications labeled as NPA-201. Altitude 4 click employs a MEMS pressure sensor with a signal-conditioning IC to provide accurate pressure measurements from 260 to 1260 mBar.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/altitude4_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/altitude-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Altitude4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Altitude4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void altitude4_cfg_setup ( altitude4_cfg_t *cfg ); 
 
- Initialization function.
> ALTITUDE4_RETVAL altitude4_init ( altitude4_t *ctx, altitude4_cfg_t *cfg );

- Click Default Configuration function.
> void altitude4_default_cfg ( altitude4_t *ctx );


#### Example key functions :

- This function stores the len amount of data into the r_buf. The data is read from
  the address reg.
> void altitude4_generic_read ( altitude4_t *ctx, uint8_t reg, uint8_t *r_buf, uint8_t len );
 
- This function writes the len amount of data from the w_buf to the address reg.
> void altitude4_generic_write ( altitude4_t *ctx, uint8_t reg, uint8_t *w_buf, uint8_t len );

- This function acquires sensor data from the click module and stores it in the
  sensor data object.
> uint8_t altitude4_read_sensor ( altitude4_t *ctx, altitude4_sensor_t *sens_data );

## Examples Description

> This example showcases how to initialize, configure and use the Altitude 4 click module. The
  click has a sensor that measures: altitude, pressure and temperature. No additional equipment
  or special configuration is required in order for this demo to work. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    altitude4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    altitude4_cfg_setup( &cfg );
    ALTITUDE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    altitude4_init( &altitude4, &cfg );
    Delay_ms( 500 );
}
  
```

### Application Task

> This function initializes the sensor data object through the read_sensor(...) function and
  then prints altitude, pressure and temperature values in the UART console. It does so every
  second.

```c

void application_task ( void )
{
    altitude4_sensor_t sensor_data;
    
    altitude4_read_sensor( &altitude4, &sensor_data );
    
    log_printf( &logger, " * Altitude: %.2f m\r\n", sensor_data.altitude );
    log_printf( &logger, " * Pressure: %.2f mBar\r\n", sensor_data.pressure );
    log_printf( &logger, " * Temperature: %.2f C\r\n", sensor_data.temperature );
    log_printf( &logger, " -------------------------\r\n" );

    Delay_1sec( );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Altitude4

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
