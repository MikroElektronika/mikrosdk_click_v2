
---
# THERMO click

THERMO click features the MAX31855K thermocouple-to-digital converter as well 
as PCC-SMP connector for K-type thermocouple probes. The click is designed to
run on a 3.3V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/thermo-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Thermo Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo_cfg_setup ( thermo_cfg_t *cfg ); 
 
- Initialization function.
> THERMO_RETVAL thermo_init ( thermo_t *ctx, thermo_cfg_t *cfg );

#### Example key functions :

- Function gets thermocouple temperature data.
> float thermo_get_temperature ( thermo_t* ctx );
 
- Function checks fault states of MAX31855 sensor on Thermo click board.
> uint8_t thermo_check_fault ( thermo_t* ctx );

- Function reads the 32-bit of data from the sensor.
> uint32_t thermo_read_data ( thermo_t* ctx );

## Examples Description

> This example measures temperature and then logs the results.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo_cfg_t cfg;


    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    thermo_cfg_setup( &cfg );
    THERMO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo_init( &thermo, &cfg );

    if ( thermo_check_fault( &thermo ) )
    {
        display_error_msg();
    }
    else
    {
        log_printf( &logger, "Status OK\r\n" );
    }

}
  
```

### Application Task

> Temperature measured by the thermocouple is converter and the results are logged. 

```c

void application_task ( void )
{
    temperature = thermo_get_temperature( &thermo );

    log_printf( &logger, "Temperature : %f\r\n", temperature );

} 

```

## Note

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo

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
