\mainpage Main Page
 
 

---
# Nano Power Click

Nano Power Click is a boost (step-up) DC-DC converter Click with extremely high efficiency and very low input voltage, aimed at the low power IoT market and battery-powered sensors and other devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nanopower_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/nano-power-click)

---


#### Click library 

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the NanoPower Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for NanoPower Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void nanopower_cfg_setup ( nanopower_cfg_t *cfg ); 
 
- Initialization function.
> NANOPOWER_RETVAL nanopower_init ( nanopower_t *ctx, nanopower_cfg_t *cfg );

- Click Default Configuration function.
> void nanopower_default_cfg ( nanopower_t *ctx );


#### Example key functions :

- This function enables and disables the device.
> void nanopw_enable_device( nanopower_t *ctx, const uint8_t state )

## Examples Description

> 
> This example enables the device.
> 

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    nanopower_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    nanopower_cfg_setup( &cfg );
    NANOPOWER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanopower_init( &nanopower, &cfg );
}
  
```

### Application Task

> Turns device on for 5 seconds and than turns device off for 10 seconds,then the output voltage starts to fall.


```c

void application_task ( void )
{
    log_printf(&logger,"Device enabled\r\n");
    nanopw_enable_device( &nanopower, NANOPW_ENABLE_DEVICE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf(&logger,"Device disabled\r\n");
    nanopw_enable_device( &nanopower, NANOPW_DISABLE_DEVICE );
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
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoPower

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
