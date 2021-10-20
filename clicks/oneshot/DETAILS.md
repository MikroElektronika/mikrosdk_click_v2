

---
# One Shot click

One Shot Click is equipped with the monostable multivibrator (also known as a “one-shot” pulse generator) with a programmable pulse width of 1μs to 33.6 seconds. The used LTC6993-2 is part of the TimerBlox® family of versatile silicon timing devices, from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/oneshot_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/one-shot-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

We provide a library for the OneShot Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for OneShot Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void oneshot_cfg_setup ( oneshot_cfg_t *cfg ); 
 
- Initialization function.
> ONESHOT_RETVAL oneshot_init ( oneshot_t *ctx, oneshot_cfg_t *cfg );

- Click Default Configuration function.
> void oneshot_default_cfg ( oneshot_t *ctx );


#### Example key functions :

- This function reads the resistance data from the AD5241 chip.
> float oneshot_get_resistance ( oneshot_t *ctx );
 
- This function reads the digital signal from the RST pin.
> uint8_t oneshot_digital_read_rst ( oneshot_t *ctx );

- This function writes the specified digital signal to the CS pin.
> void oneshot_digital_write_cs ( oneshot_t *ctx, uint8_t signal );

## Examples Description

> This example shows the user how to configure and use the One Shot click. The click has a 
  monostable monovibrator which cam generate a pulse of width between 1μs and 33.6 seconds.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. Resistance data,
  acquired from the AD5241, is displayed at the end of the initialization process. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    oneshot_cfg_t cfg;

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

    oneshot_cfg_setup( &cfg );
    ONESHOT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oneshot_init( &oneshot, &cfg );
    Delay_100ms( );
    oneshot_default_cfg( &oneshot );
    Delay_100ms( );
    log_printf( &logger, " * Resistance: %.1f Ohm\r\n", oneshot_get_resistance( &oneshot ) );
}
  
```

### Application Task

> This function triggers one shot every 8 seconds.

```c

void application_task ( )
{
    oneshot_digital_write_cs( &oneshot, 1 );
    Delay_ms( 1 );
    oneshot_digital_write_cs( &oneshot, 0 );
    log_printf( &logger, " * One shot triggered \r\n" );
    log_printf( &logger, " --------------------------- \r\n" );
    Delay_ms( 8000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.OneShot

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
