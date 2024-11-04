 
---
# DHT22 Click

> DHT22 Click is a temperature and humidity measurement board carrying the sensor of the same name.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dht22_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dht22-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Dht22 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dht22 Click driver.

#### Standard key functions :

- `dht22_cfg_setup` Config Object Initialization function.
```c
void dht22_cfg_setup ( dht22_cfg_t *cfg );
```

- `dht22_init` Initialization function.
```c
err_t dht22_init ( dht22_t *ctx, dht22_cfg_t *cfg );
```

#### Example key functions :

- `dht22_get_measurement_data` DHT22 get measurement data from the sensor function.
```c
err_t dht22_get_measurement_data ( dht22_t *ctx, float *humidity, float *temperature );
``` 

- `dht22_start_signal` DHT22 sends start signal to the sensor function.
```c
void dht22_start_signal ( dht22_t *ctx );
```

- `dht22_check_sensor_response` DHT22 release the bus to wait the sensor response signal function.
```c
uint8_t dht22_check_sensor_response ( dht22_t *ctx );
``` 

## Examples Description

> This is a example which demonstrates the use of DHT22 Click board by measuring temperature and relative humidity.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the SDA data pin depending on the selected GPIO pin (SDA1/SDA2) and log module.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dht22_cfg_t dht22_cfg;  /**< Click config object. */

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

    // Click initialization.
    dht22_cfg_setup( &dht22_cfg );
    DHT22_MAP_MIKROBUS( dht22_cfg, MIKROBUS_1 );

   if ( DIGITAL_OUT_UNSUPPORTED_PIN == dht22_init( &dht22, &dht22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, "---- Application Init done. ----" );
}
```

### Application Task

> Reads the temperature and humidity from the sensor and displays the values on the USB UART. 

```c
void application_task ( void )
{
    static float temperature = 0;
    static float humidity = 0;
    
    dht22_init_sda_output( &dht22 );
    if ( DHT22_OK == dht22_start_signal( &dht22 ) )
    {
        dht22_init_sda_input( &dht22 );
        if ( DHT22_OK == dht22_check_sensor_response( &dht22 ) )
        {
            if ( DHT22_OK == dht22_get_measurement_data( &dht22, &humidity, &temperature ) )
            {
                log_printf( &logger, " Humidity : %.2f %%\r\n", humidity );
                log_printf( &logger, " Temperature : %.2f degC\r\n", temperature );
                log_printf( &logger, " ---------------------------\r\n" );
                Delay_ms ( 1000 );
            }
        }
    }
}
``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dht22

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
