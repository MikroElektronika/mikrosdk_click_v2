\mainpage Main Page
 
 

---
# BUCK 6 Click

BUCK 6 Click is an advanced synchronous DC-DC step down (buck) converter, with a very wide input voltage range and reasonably high output current.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/buck-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the BUCK6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BUCK6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck6_cfg_setup ( buck6_cfg_t *cfg ); 
 
- Initialization function.
> BUCK6_RETVAL buck6_init ( buck6_t *ctx, buck6_cfg_t *cfg );


#### Example key functions :

- Gets reset.
> uint8_t buck6_get_rst( buck6_t *ctx )
 
- Set mode.
> void buck6_set_mode( buck6_t *ctx, uint8_t mode);

- Set maximum voltage.
> void buck6_set_max_voltage( buck6_t *ctx, uint8_t voltage );

## Examples Description

> BUCK 6 Click is an advanced synchronous DC-DC step down (buck) converter, with a very wide input voltage range and reasonably high output current. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization Driver init and settings chip on ACTIVE mode and setting the maximum range to 5V.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck6_cfg_t cfg;

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

    buck6_cfg_setup( &cfg );
    BUCK6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck6_init( &buck6, &cfg );
}
  
```

### Application Task

> Sets the different ranges of the maximum voltage. 

```c

void application_task ( void )
{
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_2500mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_5000mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_7500mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_10000mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_7500mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_5000mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
 

```
 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BUCK6

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
