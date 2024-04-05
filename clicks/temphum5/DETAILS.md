
---
# Temp&Hum 5 click

Temp&Hum 5 click is a temperature and humidity sensing click board™, packed with features that allow simple integration into any design. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temphum-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum5_cfg_setup ( temphum5_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHUM5_RETVAL temphum5_init ( temphum5_t *ctx, temphum5_cfg_t *cfg );


#### Example key functions :

- Functions for start measurement
> uint8_t temphum5_start_measurement ( temphum5_t *ctx );
 
- Functions for read Temperature data
> float temphum5_get_temperature ( temphum5_t *ctx, uint8_t temp_in );

- Functions for read Relative Huminidy data
> float temphum5_get_humidity ( temphum5_t *ctx );

## Examples Description

> This application measures temperature and humidity.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device init

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum5_cfg_t cfg;

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

    temphum5_cfg_setup( &cfg );
    TEMPHUM5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum5_init( &temphum5, &cfg );
}
  
```

### Application Task

> Reads Temperature and Humidity data and this data logs to USBUART every 1 sec.

```c

void application_task ( )
{
    float temperature;
    float humidity;
    
    temphum5_start_measurement( &temphum5 );
    
    temperature = temphum5_get_temperature( &temphum5, TEMPHUM5_TEMP_DATA_IN_CELSIUS );
                                        
    log_printf( &logger, "Temperature: %.2f C \r\n ", temperature );
    
    humidity = temphum5_get_humidity ( &temphum5 );
    log_printf( &logger, "Humidity: %f RH \r\n ", humidity );
    
    log_printf( &logger, "------------------------ \r\n " );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum5

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
