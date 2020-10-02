\mainpage Main Page
 
 

---
# Temp Log 4 click

Temp-Log 4 Click is a temperature measuring Click board™ featuring the SE97B IC, an accurate temperature sensor IC with integrated EEPROM.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/templog4_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/temp-log-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempLog4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempLog4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void templog4_cfg_setup ( templog4_cfg_t *cfg ); 
 
- Initialization function.
> TEMPLOG4_RETVAL templog4_init ( templog4_t *ctx, templog4_cfg_t *cfg );

- Click Default Configuration function.
> void templog4_default_cfg ( templog4_t *ctx );


#### Example key functions :

- Generic Write function.
> uint8_t templog4_write_reg ( templog4_t *ctx, uint8_t reg, uint16_t input_data );
 
- Generic Read function.
> uint8_t templog4_read_reg ( templog4_t *ctx, uint8_t reg, uint16_t *out_var );

- Set Address Pointer function.
> void templog4_set_addr_ptr ( templog4_t *ctx, uint8_t addr );

## Examples Description

> This application measures the temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C interface and performs a device configuration    for properly working. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    templog4_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    templog4_cfg_setup( &cfg );
    TEMPLOG4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    templog4_init( &templog4, &cfg );
    templog4_default_cfg ( &templog4 );
}
  
```

### Application Task

> First ensures that the minimum conversion time is met, and then reads the ambient temperature calculated to the Celsius degrees.

```c

void application_task ( void )
{
    float temperature;

    wait_conversion_done( );

    ret_status = templog4_get_temp( &templog4, TEMPLOG4_TEMP_AMBIENT_REG, &temperature );

    log_printf( &logger, "** Ambient temperature: %f C **\r\n", temperature );

    check_limit_status( );

    log_printf( &logger, "\r\n", temperature );

    Delay_ms( 300 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog4

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
