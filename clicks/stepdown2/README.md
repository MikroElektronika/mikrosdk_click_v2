\mainpage Main Page
 
---
# Step Down 2 click

The Step Down 2 click is a Click board™ equipped with the L6986HTR, a synchronous step-down switching regulator with operating input voltages from 4V to 38V and output voltage adjustability ranges from 0.85 V to VIN. Because of the main possibilities its features offer, the Step Down 2 click is ideally used for programmable logic controllers (PLCs), decentralized intelligent nodes, sensors, and low noise applications (LNM).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepdown2_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/step-down-2-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : GPIO type

# Software Support

We provide a library for the StepDown2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for StepDown2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void stepdown2_cfg_setup ( stepdown2_cfg_t *cfg ); 
 
- Initialization function.
> STEPDOWN2_RETVAL stepdown2_init ( stepdown2_t *ctx, stepdown2_cfg_t *cfg );

- Click Default Configuration function.
> void stepdown2_default_cfg ( stepdown2_t *ctx );


#### Example key functions :

- This function reads the digital signal from the RST pin.
> uint8_t stepdown2_digital_read_rst ( stepdown2_t *ctx );
 
- This function writes the specified digital signal to the CS pin.
> void stepdown2_digital_write_cs ( stepdown2_t *ctx, uint8_t signal );

## Examples Description

> This example showcases how to initialize and use the Step Down 2 click. The click is a 
  step-down monolithic switching regulator able to deliver up to 2 A (DC). 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    stepdown2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    stepdown2_cfg_setup( &cfg );
    STEPDOWN2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stepdown2_init( &stepdown2, &cfg );

    stepdown2_digital_write_cs( &stepdown2, 1 );
    Delay_100ms( );
}
  
```

### Application Task

> This function checks error input on the RST pin and reports if the device is working properly
  or not. It does so every second. 

```c

void application_task ( )
{
    if ( stepdown2_digital_read_rst( &stepdown2 ) )
    {
        log_printf( &logger, " * The device works as it should. *\r\n" );
    }
    else 
    {
        log_printf( &logger, " * The device does not work as it should. *\r\n" );
    }

    Delay_1sec( );
} 

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown2

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
