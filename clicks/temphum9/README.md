\mainpage Main Page
 
---
# Temp-Hum 9 click

> Temp-Hum 9 click is a smart temperature and humidity sensing click board™, packed with features that allow simple integration into any design.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temphum-9-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum9 Click driver.

#### Standard key functions :

- `temphum9_cfg_setup` Config Object Initialization function.
```c
void temphum9_cfg_setup ( temphum9_cfg_t *cfg ); 
```

- `temphum9_init` Initialization function.
```c
err_t temphum9_init ( temphum9_t *ctx, temphum9_cfg_t *cfg );
```

#### Example key functions :

- `temphum9_get_temperature` Calculating temperature
```c
float temphum9_get_temperature ( temphum9_t *ctx, uint8_t data_mode );
```
 
- `temphum9_get_humidity` Calculating relative humidity
```c
float temphum9_get_humidity ( temphum9_t *ctx, uint8_t data_mode );
```

- `temhum9_get_data` Calculating temperature and relative humidity
```c
void temhum9_get_data ( temphum9_t *ctx, uint8_t data_mode, float *temp, float *hum );
```

## Example Description

> This example demonstrates the use of TempHum 9 click board by reading and displaying the temperature and humidity measurement results.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver and sends SLEEP and WAKEUP commands.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum9_cfg_t cfg;

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
    temphum9_cfg_setup( &cfg );
    TEMPHUM9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum9_init( &temphum9, &cfg );
    Delay_ms( 100 );

    temphum9_send_command( &temphum9, TEMPHUM9_SLEEP );
    Delay_ms( 500 );
    temphum9_send_command( &temphum9, TEMPHUM9_WAKEUP );
    Delay_ms( 500 );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Performs simultaneous temperature and relative humidity measurements and logs both values on the USB UART once per second.

```c

void application_task( )
{
    float temperature = 0;
    float humidity = 0;
    
    temhum9_get_data ( &temphum9, TEMPHUM9_NORMAL_MODE, &temperature, &humidity );
    
    log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );

    log_printf( &logger, " Relative humidity: %.2f %%\r\n", humidity );
    
    log_printf( &logger, "-----------------------------\r\n" );
    
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum9

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
