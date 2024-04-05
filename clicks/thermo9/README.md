\mainpage Main Page
 
 

---
# Thermo 9 click

The TSYS01 is a single chip, versatile, new technology temperature sensor. The TSYS01 provides factory calibrated temperature information. It includes a temperature sensing chip and a 24 bit Σ-ADC.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-9-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : Jan 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Thermo9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo9_cfg_setup ( thermo9_cfg_t *cfg ); 
 
- Initialization function.
> THERMO9_RETVAL thermo9_init ( thermo9_t *ctx, thermo9_cfg_t *cfg );

#### Example key functions :

- Function is used to send the command to the device.
> void thermo9_send_cmd ( thermo9_t *ctx, uint8_t cmd_byte );
 
- Function resets and calibrates the device in order for it to work properly.
> void thermo9_calibation ( thermo9_t *ctx );

- Function is used to read temperature in degree centigrade.
> float thermo9_read_temp ( thermo9_t *ctx );

## Examples Description

> 
> This demoapp measures temperature every 3 seconds.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Logger initialization, click initialization and calibration.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo9_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    thermo9_cfg_setup( &cfg );
    THERMO9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo9_init( &thermo9, &cfg );
    Delay_ms ( 100 );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    Thermo 9 click   \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    thermo9_calibation( &thermo9 );
    Delay_ms ( 100 );
    log_printf( &logger, "      Calibrated     \r\n" );
    log_printf( &logger, "---------------------\r\n" );
}
  
```

### Application Task

>
> This example shows capabilities of Thermo 9 click by measuring
> temperature every 3 seconds and displaying temperature in degrres Celsius 
> via USART terminal.
> 

```c

void application_task ( void )
{
    //  Task implementation.
    temp_val = thermo9_read_temp( &thermo9 );
    log_printf( &logger, "-- Temperature : %.2f °C\r\n", temp_val );

    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

## Note

> 
> Calibration function must be used once in order to get calibrations!
> 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo9

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
