
---
# TempHum 3 click

> Temp&Hum 3 click is a smart environmental temperature and humidity sensor Click board™, packed with features which allow easy and simple integration into any design that requires accurate and reliable humidity and temperature measurements.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temp-hum-3-click)

---


#### Click library 

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum3 Click driver.

#### Standard key functions :

- `temphum3_cfg_setup` Config Object Initialization function.
```c
void temphum3_cfg_setup ( temphum3_cfg_t *cfg ); 
```

- `temphum3_init` Initialization function.
```c
err_t temphum3_init ( temphum3_t *ctx, temphum3_cfg_t *cfg );
```

- `temphum3_default_cfg` Click Default Configuration function.
```c
void temphum3_default_cfg ( temphum3_t *ctx );
```

#### Example key functions :

- `temphum3_get_temperature` Get temperature value
```c
float temphum3_get_temperature ( temphum3_t *ctx );
```

- `temphum3_get_huminidy` Get humidity value
```c
float temphum3_get_huminidy ( temphum3_t *ctx );
```

- `temphum3_get_max_hum` Get maximum temperature value
```c
float temphum3_get_max_hum ( temphum3_t *ctx );
```

## Example Description

> This application reads temperature and humidity data.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum3_cfg_t temphum3_cfg;

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
    log_info( &logger, " Application Init " );

    //  Click initialization.
    temphum3_cfg_setup( &temphum3_cfg );
    TEMPHUM3_MAP_MIKROBUS( temphum3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum3_init( &temphum3, &temphum3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    temphum3_default_cfg( &temphum3 );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads the temperature and huminidy and logs results to the USB UART every 500 ms.

```c
void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;

    temperature = temphum3_get_temperature( &temphum3 );
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    
    humidity = temphum3_get_humidity( &temphum3 );
    log_printf( &logger, " Humidity : %.1f %% \r\n", humidity );
    Delay_ms ( 500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum3

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
