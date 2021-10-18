
---
# DHT22 click

DHT22 click is a temperature and humidity measurement board carrying the sensor of the same name.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dht22_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dht22-click)

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

- Config Object Initialization function.
> void dht22_cfg_setup ( dht22_cfg_t *cfg ); 
 
- Initialization function.
> DHT22_RETVAL dht22_init ( dht22_t *ctx, dht22_cfg_t *cfg );

#### Example key functions :

- Sends start signal to the sensor function.
> void dht22_start_signal ( dht22_t *ctx );
 
- Release the bus to wait the sensor response signal function.
> uint8_t dht22_check_sensor_response ( dht22_t *ctx );

- Reading data from the sensor function.
> uint32_t dht22_get_sensor_data ( dht22_t *ctx );

## Examples Description

> This is a example which demonstrates the use of DHT22 Click board by measuring temperature and relative humidity.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the SDA data pin depending on the selected GPIO pin (SDA1/SDA2) and log module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;

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
    log_info( &logger, "---- Application Init... ----" );

    dht22_cfg_t dht22_cfg;

    //  Click initialization.

    dht22_cfg_setup( &dht22_cfg );
    DHT22_MAP_MIKROBUS( dht22_cfg, MIKROBUS_1 );

    if ( dht22_init( &dht22, &dht22_cfg ) == DHT22_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

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
    uint8_t resp_stat = DHT22_RESP_NOT_READY;
    uint32_t sens_meas = 0;
    float dht22_temp = 0;
    float dht22_hum = 0;
    
    dht22_init_sda_output( &dht22 );
    
    if ( dht22_start_signal( &dht22 ) == DHT22_OK )
    {
        dht22_init_sda_input( &dht22 );
        
        if ( dht22_check_sensor_response( &dht22, &resp_stat ) == DHT22_OK )
        {
            if ( resp_stat == DHT22_RESP_READY )
            {
                if ( dht22_get_sensor_data( &dht22, &sens_meas ) == DHT22_OK )
                {
                    dht22_temp = dht22_calculate_temperature( &dht22, sens_meas );
                    dht22_hum = dht22_calculate_humidity( &dht22, sens_meas );

                    log_printf( &logger, " Humidity : %.2f %%\r\n", dht22_hum );
                    log_printf( &logger, " Temperature : %.2f degC\r\n", dht22_temp );
                    log_printf( &logger, " ---------------------------\r\n", dht22_temp );
                    Delay_ms( 1000 );
                }
                
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
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
