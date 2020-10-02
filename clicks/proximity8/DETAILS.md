
---
# Proximity 8 click

Proximity 8 click is a close-range proximity sensing Click board™, equipped with the VCNL36687S, a very accurate and power-efficient proximity sensor (PS) with VCSEL.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity8_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/proximity-8-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proximity8_cfg_setup ( proximity8_cfg_t *cfg ); 
 
- Initialization function.
> PROXIMITY8_RETVAL proximity8_init ( proximity8_t *ctx, proximity8_cfg_t *cfg );

- Click Default Configuration function.
> void proximity8_default_cfg ( proximity8_t *ctx );


#### Example key functions :

- This function reads data from the desired register.
> void proximity8_generic_read ( proximity8_t *ctx, uint8_t reg, uint8_t *data_buf );
 
- This function writes data to the desired register.
> void proximity8_generic_write ( proximity8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

- This function returns Interrupt state.
> uint8_t proximity8_get_interrupt_state( proximity8_t *ctx );

## Examples Description

> This application enables usage of the proximity sensor

**The demo application is composed of two sections :**

### Application Init 

> Initialization Driver init, test comunication and configuration chip for measurement
 
```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity8_cfg_t cfg;
    uint16_t tmp;
    uint16_t w_temp;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    proximity8_cfg_setup( &cfg );
    PROXIMITY8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity8_init( &proximity8, &cfg );

    //Test Communication
    
    proximity8_generic_read( &proximity8, PROXIMITY8_REG_DEVICE_ID, &tmp );

    if( tmp == PROXIMITY8_DEVICE_ID )
    {
        log_printf( &logger, "---- Comunication OK!!! ----\r\n" );
    }
    else
    {
        log_printf( &logger, "---- Comunication ERROR!!! ----\r\n" );
        while( 1 );
    }

    proximity8_default_cfg( &proximity8 );

    log_printf( &logger, "---- Start measurement ----\r\n" );
}
  
```

### Application Task

> Reads Proximity data and this data logs to the USBUART every 1500ms.

```c

void application_task ( void )
{
    //  Task implementation.

   uint16_t proximity;
   
   proximity8_generic_read( &proximity8, PROXIMITY8_REG_PROX_DATA, &proximity );
   proximity = ( proximity & 0x7FFF );

   log_printf( &logger, " Proximity data: %d\r\n", proximity );
   
   log_printf( &logger, "-------------------------\r\n" );
   Delay_ms( 1500 );
} 

```

## Note

> The reading value and proximity of the data depend on the configuration.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity8

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
