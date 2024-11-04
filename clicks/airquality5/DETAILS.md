
# Air quality 5 Click

Air quality 5 Click is a triple MOS sensor on a single Click board™, which can detect gas pollution for a number of different gases. The onboard sensor is specially designed to detect the pollution from automobile exhausts, as well as the gas pollution from the industrial or agricultural industry.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/airquality5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/air-quality-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Airquality5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Airquality5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void airquality5_cfg_setup ( airquality5_cfg_t *cfg ); 
 
- Initialization function.
> AIRQUALITY5_RETVAL airquality5_init ( airquality5_t *ctx, airquality5_cfg_t *cfg );

- Click Default Configuration function.
> void airquality5_default_cfg ( airquality5_t *ctx );


#### Example key functions :

- Functions for write data in register.
> void airq5_write_data ( airquality5_t *ctx, uint8_t reg, uint16_t data_b );
 
- Functions for read data from register.
> uint16_t airq5_read_data ( airquality5_t *ctx, uint8_t reg );

- Functions for configuration.
> void airq5_set_configuration ( airquality5_t *ctx, uint16_t config );

## Examples Description
 
> This application can detect gas pollution for a number of different gases.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device and configuration chip. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality5_cfg_t cfg;
    airquality5.data_config = 0x8583;

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

    airquality5_cfg_setup( &cfg );
    AIRQUALITY5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality5_init( &airquality5, &cfg );
}
  
```

### Application Task

> Reads the values of CO, NH3 and NO2 sensor and logs data on USBUART every 500ms. 

```c

void application_task ( void )
{
    uint16_t NO2_sensor_data;
    uint16_t NH3_sensor_data;
    uint16_t CO_sensor_data;
 
    CO_sensor_data = airq5_read_sensor_data( &airquality5, AIRQ5_DATA_CHANNEL_CO );
      
    NO2_sensor_data = airq5_read_sensor_data( &airquality5, AIRQ5_DATA_CHANNEL_NO2 );
    log_printf( &logger, " NO2 data: %d\r\n", NO2_sensor_data );
      
    NH3_sensor_data = airq5_read_sensor_data( &airquality5, AIRQ5_DATA_CHANNEL_NH3 );
    log_printf( &logger, " NH3 data: %d\r\n", NH3_sensor_data );
     
    CO_sensor_data = airq5_read_sensor_data( &airquality5, AIRQ5_DATA_CHANNEL_CO );
    log_printf( &logger," CO data: %d\r\n", CO_sensor_data );
     
    log_printf( &logger, " -------- ");
    Delay_ms ( 200 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Airquality5

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
