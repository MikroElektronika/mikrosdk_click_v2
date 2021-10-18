\mainpage Main Page
 
---
# Pressure 11 click

Pressure 11 Click is a digital barometer on a Click board™. Pressure 11 is equipped with the LPS33HW, an absolute piezoresistive pressure sensor, manufactured using a proprietary technology. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-11-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure11 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pressure11 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pressure11_cfg_setup ( pressure11_cfg_t *cfg ); 
 
- Initialization function.
> PRESSURE11_RETVAL pressure11_init ( pressure11_t *ctx, pressure11_cfg_t *cfg );

#### Example key functions :

- Functions for cheking commuincation with the chip and checking its ID.
> uint8_t pressure11_check_id ( pressure11_t *ctx );
 
- Functions for temperature reading.
> float pressure11_get_temperature ( pressure11_t *ctx );

- Functions for pressure reading.
> float pressure11_get_pressure ( pressure11_t *ctx );

## Examples Description

> This sensor offers many benefits, including low power consumption,  high resolution of the pressure data, embedded thermal compensation,  FIFO buffer with several operating modes, temperature measurement, etc.

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI driver and checks chip ID

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure11_cfg_t cfg;

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

    pressure11_cfg_setup( &cfg );
    PRESSURE11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure11_init( &pressure11, &cfg );
}
  
```

### Application Task

>
> Reads Pressure and Temperature values and displays it on UART LOG
> 

```c

void application_task ( void )
{
    float temperature;
    float pressure;
        
    temperature = pressure11_get_temperature( &pressure11 );
    log_printf( &logger, "Temperature: %.2f \r\n", temperature );
    log_printf( &logger, " C" );
 
    pressure = pressure11_get_pressure( &pressure11 );
    log_printf( &logger, "Pressure:  %.2f \r\n", pressure );
    log_printf( &logger, "   hPa (mBar)" );
 
    Delay_ms( 500 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure11

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
