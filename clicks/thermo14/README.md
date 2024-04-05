\mainpage Main Page
 
---
# Thermo 14 click

Thermo 14 Click uses the STTS22H digital temperature sensor and thermal watchdog, which can measure temperature measurements between -40°C and +125°C so that the temperature measurement data can be processed by the host MCU. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo14_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/thermo-14-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo14 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo14 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo14_cfg_setup ( thermo14_cfg_t *cfg ); 
 
- Initialization function.
> THERMO14_RETVAL thermo14_init ( thermo14_t *ctx, thermo14_cfg_t *cfg );

#### Example key functions :

- Reset function.
> void thermo14_reset ( thermo14_t *ctx );
 
- Sensor enable function.
> void thermo14_sensor_enable ( thermo14_t *ctx );

- Get Raw Temperature Data function.
> int16_t thermo14_temp_raw_get ( thermo14_t *ctx );

## Examples Description
 
> Thermo 14 Click provides an accuracy of ±0.5°C in the range from -10°C to 60°C.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver, sets up the device. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo14_cfg_t cfg;
    
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

    thermo14_cfg_setup( &cfg );
    THERMO14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo14_init( &thermo14, &cfg );

    Delay_ms ( 100 );
    thermo14_default_cfg( &thermo14 );
}
  
```

### Application Task

> This example shows capabilities of Thermo 14 click by measuring
   temperature every 3 seconds and displaying temperature in degrres Celsius via USART terminal. 

```c

void application_task ( void )
{
    temp_val = thermo14_get_temperature( &thermo14 );

    log_printf( &logger, " Temperature: %.2f C \r\n ", temp_val );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```
The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo14

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
