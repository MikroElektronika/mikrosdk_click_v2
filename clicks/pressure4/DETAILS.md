
---
# Pressure 4 click

> Pressure 4 click is an absolute barometric pressure measurement Click board™, which features a low power consumption, high precision barometric pressure sensor. Capable of using both SPI and I2C communication protocols, Pressure 4 click allows being interfaced with a broad range of various microcontroller units (MCUs). The sensor used on this Click board™ features onboard processing capabilities, such as the IIR filtering, used to filter out abrupt changes of pressure. Low power consumption allows Pressure 4 click to be used in many portable, battery-powered applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-4-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pressure4 Click driver.

#### Standard key functions :

- `pressure4_cfg_setup` Config Object Initialization function.
```c
void pressure4_cfg_setup ( pressure4_cfg_t *cfg ); 
```

- `pressure4_init` Initialization function.
```c
err_t pressure4_init ( pressure4_t *ctx, pressure4_cfg_t *cfg );
```

- `pressure4_default_cfg` Click Default Configuration function.
```c
void pressure4_default_cfg ( pressure4_t *ctx );
```

#### Example key functions :

- `pressure4_read_id` This function returns the contents of the chipid register.
```c
uint8_t pressure4_read_id ( pressure4_t *ctx );
```

- `pressure4_get_temperature` This function returning the calculated temperature value.
```c
float pressure4_get_temperature ( pressure4_t *ctx );
```

- `pressure4_get_pressure` This function returning the calculated value of the pressure.
```c
float pressure4_get_pressure ( pressure4_t *ctx );
```

## Examples Description

> This app measure barometric pressure.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure4_cfg_t cfg;

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
    pressure4_cfg_setup( &cfg );
    PRESSURE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure4_init( &pressure4, &cfg );

    pressure4_default_cfg( &pressure4 );
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> The pressure and temperature data is read from the sensor 
> and it is printed to the UART.

```c

void application_task ( void )
{
    float pressure = 0;
    float temperature = 0;

    temperature = pressure4_get_temperature( &pressure4 );
    log_printf( &logger, "Temperature : %.2f degC\r\n", temperature );
    Delay_ms( 100 );
    
    pressure = pressure4_get_pressure( &pressure4 );
    log_printf( &logger, "Pressure : %.2f mBar\r\n", pressure );
    log_printf( &logger, "========================\r\n" );

    Delay_ms( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure4

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