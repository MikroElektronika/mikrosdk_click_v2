\mainpage Main Page
  
---
# SHT click

> SHT click is a temperature and humidity sensing click board that carries Sensiron’s SHT3x-DIS IC. Compared to its predecessor (SHT11), SHT3x click has increased reliability and enhanced signal processing features with a high signal-to-noise ratio.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/sht_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/sht-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Sht Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Sht Click driver.

#### Standard key functions :

- `sht_cfg_setup` Config Object Initialization function.
```c
void sht_cfg_setup ( sht_cfg_t *cfg ); 
```

- `sht_init` Initialization function.
```c
err_t sht_init ( sht_t *ctx, sht_cfg_t *cfg );
```

#### Example key functions :

- `sht_temp_ss` Returns temperature measurement in single shot mode.
```c
float sht_temp_ss ( sht_t *ctx );
```

- `sht_hum_ss` Returns humidity measurement in single shot mode.
```c
float sht_hum_ss ( sht_t *ctx );
```

- `sht_heater_control` Sets the heater state.
```c
void sht_heater_control ( sht_t *ctx, uint8_t state );
```

## Examples Description

> This application enables usage of the temperature and humidity sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initialize the communication interface and configure the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    sht_cfg_t cfg;

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
    sht_cfg_setup( &cfg );
    SHT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    sht_init( &sht, &cfg );
    
    sht_reset( &sht );
    sht_hw_reset( &sht );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Temperature and humidity data is measured and read from the sensor. 
> After the data has been read it is displayed on the serial port.

```c

void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;

    temperature = sht_temp_ss( &sht );
    log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );

    humidity = sht_hum_ss( &sht );
    log_printf( &logger, " Humidity: %.2f %%\r\n\n", humidity );

    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Sht

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
