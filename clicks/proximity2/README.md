\mainpage Main Page
 
 

---
# Proximity 2 click

Proximity 2 Click features MAX44000, an IC that integrates an ambient light as well as a proximity sensor. The chip consists of an array of photodiodes that convert light into current, which the internal circuitry then converts into a digital value.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/proximity-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proximity2_cfg_setup ( proximity2_cfg_t *cfg ); 
 
- Initialization function.
> PROXIMITY2_RETVAL proximity2_init ( proximity2_t *ctx, proximity2_cfg_t *cfg );

- Click Default Configuration function.
> void proximity2_default_cfg ( proximity2_t *ctx );


#### Example key functions :

- Read PROX Data Register function.
> uint8_t proximity2_read_prox ( proximity2_t *ctx );
 
- Read ALS Data Registers function.
> uint16_t proximity2_read_als ( proximity2_t *ctx );

## Examples Description

> 
> This is an example that shows the most important
> functions that Proximity 2 click has.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Configuring clicks and log objects.
> Setting the click in the default configuration.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity2_cfg_t cfg;

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
    log_info( &logger, "Application Init" );
    
    //  Click initialization.

    proximity2_cfg_setup( &cfg );
    PROXIMITY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity2_init( &proximity2, &cfg );
    
    proximity2_default_cfg ( &proximity2 );
    
    log_info( &logger, "Application Init" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> Shows the most important proximity and ambient value.
> 

```c

void application_task ( void )
{
    proxi_val =  proximity2_read_prox ( &proximity2 );
    ambient = proximity2_read_als ( &proximity2 );

    log_printf( &logger, " Distance : %d \r\n", (uint16_t)proxi_val );
    
    log_printf( &logger, " Light    : %d \r\n", ambient );

    log_printf( &logger, "------------------\r\n" );
    
    Delay_ms ( 300 );
}

```

## Note


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity2

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
