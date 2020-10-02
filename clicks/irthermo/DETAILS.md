
---
# IrThermo  click

IrThermo click 3.3V is a contactless temperature measurement device that relies
on the accurate thermopile sensor chip, which encompasses both the thermopile
sensor element and the ASSP. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/irthermo-click-group.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/irthermo-33v-click>)

[click Product page](<https://www.mikroe.com/irthermo-5v-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the IrThermo Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IrThermo Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void irthermo_cfg_setup ( irthermo_cfg_t *cfg ); 
 
- Initialization function.
> IRTHERMO_RETVAL irthermo_init ( irthermo_t *ctx, irthermo_cfg_t *cfg );

#### Example key functions :

- Returns ambient temperature value in Celsius
> float irthrm3v3_get_t_ambient ( irthermo_t* ctx );
 
- Returns object temperature value in Celsius
> float irthrm3v3_get_t_object ( irthermo_t* ctx );

- Returns 16bit value of register
> uint16_t irthrm3v3_read_reg ( irthermo_t* ctx, uint8_t address );

## Examples Description

> This example logs the ambient temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initializes IrThermo 3V3 Driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    irthermo_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    irthermo_cfg_setup( &cfg );
    IRTHERMO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irthermo_init( &irthermo, &cfg );
}
  
```

### Application Task

> Reading Ambient Temperature and displaying the value periodically.

```c

void application_task ( void )
{
    measured_temperature = irthrm3v3_get_t_ambient( &irthermo );
    log_printf( &logger, "Ambient Temperature: %f\r\n", measured_temperature );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IrThermo

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