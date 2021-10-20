\mainpage Main Page
 
 

---
# Fever click

Fever click features a specially designed sensor, which is capable of accurate measurement of human body temperature. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fever_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/fever-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Fever Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Fever Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void fever_cfg_setup ( fever_cfg_t *cfg ); 
 
- Initialization function.
> FEVER_RETVAL fever_init ( fever_t *ctx, fever_cfg_t *cfg );

#### Example key functions :

- Get temperature
> float fever_get_temperature ( fever_t *ctx );

## Examples Description

> This application measures temperature.

**The demo application is composed of two sections :**

### Application Init 

> Click device initialization

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    fever_cfg_t cfg;

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

    fever_cfg_setup( &cfg );
    FEVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fever_init( &fever, &cfg );
}
  
```

### Application Task

> Reading and displaying current temperature via UART

```c

void application_task ( void )
{
    float temperature;
    temperature = fever_get_temperature( &fever );
    log_printf( &logger, "Current Temperature : %.2f C \r\n", temperature);
    Delay_ms(1000);
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Fever

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
