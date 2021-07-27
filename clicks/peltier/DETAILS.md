
# Peltier click

The Peltier Click is a Click board™ which utilizes the SPV1050, an ultralow power energy harvester and battery charger from STMicroelectronics. The Peltier click can charge lithium battery using thermoelectric energy harvesting device (TEG).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/peltier_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/peltier-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Peltier Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Peltier Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void peltier_cfg_setup ( peltier_cfg_t *cfg ); 
 
- Initialization function.
> PELTIER_RETVAL peltier_init ( peltier_t *ctx, peltier_cfg_t *cfg );


#### Example key functions :

- Enables LDO2 function.
> void peltier_enable_ldo2 ( peltier_t *ctx );
 
- Disables LDO2 function.
> void peltier_disable_ldo2 ( peltier_t *ctx );

- Check ongoing battery charge flag pin function.
> uint8_t peltier_battery_charge ( peltier_t *ctx );

## Examples Description
 
> This application is ultralow power energy harvester and battery charger.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO driver, disables both 1.8V and 3.3V outputs and starts write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    peltier_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    peltier_cfg_setup( &cfg );
    PELTIER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    peltier_init( &peltier, &cfg ); 
}
  
```

### Application Task

> This example demonstrates the use of Peltier Click board by first enableing 1.8V output, second 
  by enableing 3.3V output, then enabling both outputs and finally disabling both outputs in 5 seconds intervals. 

```c

void application_task ( void )
{
    log_printf( &logger, "   1.8V output    \r\n" );
    log_printf( &logger, "------------------\r\n" );
    peltier_enable_ldo1( &peltier );
    peltier_disable_ldo2( &peltier );
    Delay_ms( 5000 );
    
    log_printf( &logger, "   3.3V output    \r\n" );
    log_printf( &logger, "------------------\r\n" );
    peltier_disable_ldo1( &peltier );
    peltier_enable_ldo2( &peltier );
    Delay_ms( 5000 );
    
    log_printf( &logger, "   Both outputs   \r\n" );
    log_printf( &logger, "------------------\r\n" );
    peltier_enable_ldo1( &peltier );
    peltier_enable_ldo2( &peltier );
    Delay_ms( 5000 );
    
    log_printf( &logger, " Disable  outputs \r\n" );
    log_printf( &logger, "------------------\r\n" );
    peltier_disable_ldo1( &peltier );
    peltier_disable_ldo2( &peltier );
    Delay_ms( 5000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Peltier

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
