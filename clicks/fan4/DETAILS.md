
 

---
# FAN 4 click

Fan 4 click is a very compact, two-wire fan driver. It utilizes an integrated 5V, DC, brushless-motor driver chip.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fan4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/fan-4-click)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Fan4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Fan4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void fan4_cfg_setup ( fan4_cfg_t *cfg ); 
 
- Initialization function.
> FAN4_RETVAL fan4_init ( fan4_t *ctx, fan4_cfg_t *cfg );

- Click Default Configuration function.
> void fan4_default_cfg ( fan4_t *ctx );


#### Example key functions :

- Check diagnostic.
> uint8_t fan4_check_diagnostic ( fan4_t *ctx );
 
- Set output voltage
> FAN4_RETVAL fan4_set_output ( fan4_t *ctx, uint16_t output_volt, uint8_t boost_start_timer );

## Examples Description

> Demo application shows basic use of Fan 4 click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    fan4_cfg_t cfg;

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

    fan4_cfg_setup( &cfg );
    FAN4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fan4_init( &fan4, &cfg );

    fan4_default_cfg( &fan4 );
}
```

### Application Task

> Increases the output voltage every 500 ms until it reaches the maximum fan voltage.
> Prints current voltase data on usbuart.

```c
void application_task ( void )
{
    uint16_t voltage;

    //  Task implementation.

    voltage = FAN4_MIN_VOLT_SCALE;

    while ( voltage <= FAN4_MAX_VOLT_SCALE )
    {
        voltage += ( FAN4_DAC_LSB * 4 );
        log_info( &logger, "** Voltage is %d mV", voltage );

        fan4_set_output( &fan4, voltage, FAN4_BOOST_START_TIMER_DIS );
        Delay_ms ( 500 );
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Fan4

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
