
---
# DHT22 2 click

DHT22 2 click is used for measuring the environmental temperature and relative humidity. It uses the AM2322 sensor, with very accurate thermal and humidity measuring capabilities. It can use either 1-Wire or I2C protocol to communicate with the integrated circuit.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dht222_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/dht22-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Dht222 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dht222 Click driver.

#### Standard key functions :

- `dht222_cfg_setup` Config Object Initialization function.
```c
void dht222_cfg_setup ( dht222_cfg_t *cfg ); 
```

- `dht222_init` Initialization function.
```c
err_t dht222_init ( dht222_t *ctx, dht222_cfg_t *cfg );
```

#### Example key functions :

- `dht222_read_reg` This function reads data from the desired register.
```c
err_t dht222_read_reg ( dht222_t *ctx, uint8_t address, uint8_t *data_out, uint8_t len );
```

- `dht222_write_reg` This function writes data to the desired register.
```c
err_t dht222_write_reg ( dht222_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len );
```

- `dht222_get_temp_hum` The function reads the temperature and humidity data from the sensor AM2322 on the DHT22 2 Click.
```c
err_t dht222_get_temp_hum ( dht222_t *ctx, uint16_t *temperature, uint16_t *humidity );
```

## Examples Description

> This example demonstrates the use of DHT22 2 click board by reading the temperature and humidity data.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dht222_cfg_t cfg;

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
    dht222_cfg_setup( &cfg );
    DHT222_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dht222_init( &dht222, &cfg );
    Delay_ms( 500 );
}
  
```

### Application Task

> Reads the temperature (degrees C) and the relative humidity (%RH) data and displays the results on the USB UART approximately once per second.

```c

void application_task ( void )
{
    uint16_t temperature = 0;
    uint16_t humidity = 0;
    if ( DHT222_OK == dht222_get_temp_hum ( &dht222, &temperature, &humidity ) )
    {
        log_printf( &logger, " Humidity   : %.1f %%\r\n", ( float ) humidity / 10 );
        log_printf( &logger, " Temperature: %.1f C \r\n", ( float ) temperature / 10 );
        log_printf( &logger, "---------------------\r\n" );
        Delay_ms ( 1000 );
    }
}

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dht222

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
