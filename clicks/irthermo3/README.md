\mainpage Main Page
 
 

---
# IrThermo 3 click

IrThermo 3 click is a device which allows contactless measurement of the object temperature.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irthermo3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ir-thermo-3-click)

---


#### Click library 

- **Author**        : Jovan Stajokovic
- **Date**          : nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the IrThermo3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IrThermo3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void irthermo3_cfg_setup ( irthermo3_cfg_t *cfg ); 
 
- Initialization function.
> IRTHERMO3_RETVAL irthermo3_init ( irthermo3_t *ctx, irthermo3_cfg_t *cfg );

- Click Default Configuration function.
> void irthermo3_default_cfg ( irthermo3_t *ctx );


#### Example key functions :

- Read Object Temperature function
> float irthermo3_get_object_temperature ( irthermo3_t *ctx );

- Read Ambient Temperature function
> float irthermo3_get_ambient_temperature ( irthermo3_t *ctx );

- Set device mode function
> void irthermo3_set_mode( irthermo3_t *ctx, uint8_t mode );

## Examples Description

> The demo application displays ambient and object temperature measurementss
> using IrThermo 3 click.

**The demo application is composed of two sections :**

### Application Init 

> Initializes Driver ,resets the devic and performs calibration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    irthermo3_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    irthermo3_cfg_setup( &cfg );
    IRTHERMO3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irthermo3_init( &irthermo3, &cfg );

    irthermo3_global_write ( &irthermo3, adr_rst, 4 );
    irthermo3_cal ( &irthermo3 );
    Delay_ms( 500 );
}
```

### Application Task

> The device measures ambient and object temperatures and displays data in
> degree centigrade every second.

```c
void application_task ( void )
{
    amb_temp = irthermo3_get_ambient_temperature( &irthermo3 );
    log_printf( &logger, "Ambient temperature: %.2f °C \r\n", amb_temp );

    obj_temp = irthermo3_get_object_temperature( &irthermo3 );
    log_printf( &logger, "Object temperature: %.2f °C \r\n", obj_temp );

    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IrThermo3

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
