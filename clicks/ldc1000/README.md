\mainpage Main Page

---
# LDC 1000 click

LDC1000 click carries the world's first inductance-to-digital converter IC, along with a detachable sensor (an LC tank comprising a 36-turn PCB coil and a 100pF 1% NPO capacitor). The LDC1000 IC has a sub-micron resolution in short range applications; the board is ideal for highly precise short range measurements of the position, motion or composition of conductive targets.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ldc1000_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/ldc1000-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

We provide a library for the Ldc1000 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ldc1000 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ldc1000_cfg_setup ( ldc1000_cfg_t *cfg ); 
 
- Initialization function.
> LDC1000_RETVAL ldc1000_init ( ldc1000_t *ctx, ldc1000_cfg_t *cfg );

- Click Default Configuration function.
> void ldc1000_default_cfg ( ldc1000_t *ctx );

#### Example key functions :

- This function reads the proximity data.
> uint16_t ldc1000_get_proximity_data ( ldc1000_t *ctx );
 
- This function reads the inductance data.
> float ldc1000_get_inductance_data ( ldc1000_t *ctx );

- This function reads the input voltage from the INT pin.
> uint8_t ldc1000_get_int_input ( ldc1000_t *ctx );

## Examples Description

> This example showcases how to initialize and configure the logger and click modules and
  read and display proximity and impendance data.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. Configuration data 
  is written to the: rp maximum/minimum, sensor frequency, LDC/Clock/Power registers. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    ldc1000_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ldc1000_cfg_setup( &cfg );
    LDC1000_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ldc1000_init( &ldc1000, &cfg );
    Delay_100ms( );
    ldc1000_default_cfg( &ldc1000 );
    Delay_100ms( );
}
  
```

### Application Task

> This function reads and displays proximity and impendance data every 10th of a second. 

```c

void application_task ( )
{
    uint16_t proximity;
    uint16_t inductance;

    proximity = ldc1000_get_proximity_data( &ldc1000 );
    inductance = ldc1000_get_inductance_data( &ldc1000 );

    if ( ( ( proximity - old_proximity ) > LDC1000_SENSITIVITY ) &&
         ( ( old_proximity - proximity ) > LDC1000_SENSITIVITY ) )
    {
        log_printf( &logger, " * Proximity: %d \r\n", proximity );

        log_printf( &logger, " * Impendance: %f uH\r\n", inductance );

        old_proximity = proximity;

        log_printf( &logger, "--------------------\r\n" );
        Delay_100ms();
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ldc1000

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
