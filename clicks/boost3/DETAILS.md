\mainpage Main Page
 
---
# Boost 3 Click

Boost 3 Click is a compact add-on board that contains a boost converter with an integrated current mirror function. This board features the TPS61391, a 700-kHz pulse-width modulating (PWM) Step-Up converter with a 70V switch FET with an input voltage up to 5.5V from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/boost3_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/boost-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Boost3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Boost3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void boost3_cfg_setup ( boost3_cfg_t *cfg ); 
 
- Initialization function.
> BOOST3_RETVAL boost3_init ( boost3_t *ctx, boost3_cfg_t *cfg );

#### Example key functions :

- Function is used to enable or disable the device.
> void boost3_dev_enable ( boost3_t *ctx, uint8_t state );

## Examples Description

> Boost 3 Click provides an adjustable output voltage through the onboard
> potentiometer. The chip is a 700-kHz pulse-width modulating (PWM) step-up 
> converter with an 85-V switch FET with an input ranging from 2.5 V to 5.5 V. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO and LOG structures, and set CS pin as output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    boost3_cfg_t cfg;

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

    boost3_cfg_setup( &cfg );
    BOOST3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost3_init( &boost3, &cfg );
}
  
```

### Application Task

> Turns ON the device for 10 seconds and then turns it OFF for 3 seconds.
> It also displays appropriate messages on the USB UART.

```c

void application_task ( void )
{
    boost3_dev_enable( &boost3, BOOST3_ENABLE );
        
    log_printf( &logger, "The Click board is enabled!\r\n" );
    log_printf( &logger, "Please use the on-board potentiometer" );
    log_printf( &logger, " to adjust the voltage output.\r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    boost3_dev_enable( &boost3, BOOST3_DISABLE );
    log_printf( &logger, "The Click board is turned OFF!\r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost3

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
