\mainpage Main Page
 
---
# DIGI POT 6 click

DIGI POT 6 Click features the MCP41HVX1 family of devices which have dual power rails (analog and digital). The analog power rail allows high voltage on the resistor network terminal pins.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](https://www.mikroe.com/digi-pot-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the DIGIPOT6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DIGIPOT6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void digipot6_cfg_setup ( digipot6_cfg_t *cfg ); 
 
- Initialization function.
> DIGIPOT6_RETVAL digipot6_init ( digipot6_t *ctx, digipot6_cfg_t *cfg );

- Click Default Configuration function.
> void digipot6_default_cfg ( digipot6_t *ctx );


#### Example key functions :

- This function reads data from the specified register address.
> uint8_t digipot6_read_data ( digipot6_t *ctx, uint8_t reg ) ;
 
- This function writes a wiper configuration command to the click module.
> void digipot6_write_wiper_cmd ( digipot6_t *ctx, uint8_t cmd );

- This function reads data from the specified register address.
> void digipot6_set_resistor ( digipot6_t *ctx, uint8_t state, uint8_t mask, uint8_t tcon );

## Examples Description

> This example showcases how to initialize, configure and use the DIGI POT 6 click module. The
  click is a digital potentiometer. The potentiometer has a programmable wiper which controlls 
  the output voltage on port P0W. An external power supply is required for this example. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. Additional configuring
  is done in the default_cfg(...) function. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot6_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    digipot6_cfg_setup( &cfg );
    DIGIPOT6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot6_init( &digipot6, &cfg );
    Delay_100ms( );
    digipot6_default_cfg( &digipot6 );
    Delay_100ms( );
}
  
```

### Application Task

> This function programs the wiper position and shows the current wiper position in the UART
  console every second. After the final iteration there is a 1 second delay, after which the
  counter resets and the loop starts anew.

```c

void application_task ( void )
{
    uint8_t wiper;
    uint8_t cnt;
    
    for ( cnt = 0; cnt <= 255; cnt += 15 )
    {
        digipot6_write_data( &digipot6, DIGIPOT6_VOLATILE_WIPER_0, cnt );
        Delay_ms( 10 );

        wiper = digipot6_read_data( &digipot6, DIGIPOT6_VOLATILE_WIPER_0 );

        log_printf( &logger, " * Wiper position: %d *\r\n", wiper );
        Delay_ms( 1000 );
    }

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT6

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
