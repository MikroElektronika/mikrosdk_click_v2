 
---
# MQ Sensors click

This click group supports all MQ sensors in click form.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/mq-sensor-click-group.png" height=150px>
</p>

> - [Product page - LPG click](https://www.mikroe.com/lpg-click)

> - [Product page - Alcohol click](https://www.mikroe.com/alcohol-click)

> - [Product page - Hydrogen click](https://www.mikroe.com/hydrogen-click)

> - [Product page - Air Quality click](https://www.mikroe.com/air-quality-click)

> - [Product page - Methane click](https://www.mikroe.com/methane-click)

> - [Product page - CO click](https://www.mikroe.com/co-click)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the MqSensors Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MqSensors Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mqsensors_cfg_setup ( mqsensors_cfg_t *cfg ); 
 
- Initialization function.
> MQSENSORS_RETVAL mqsensors_init ( mqsensors_t *ctx, mqsensors_cfg_t *cfg );

#### Example key functions :

- Generic read function
> mqsensors_data_t mqsensors_generic_read ( mqsensors_t *ctx );

## Examples Description

> The demo application shows the reading of the adc 
> values given by the sensors.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mqsensors_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mqsensors_cfg_setup( &cfg );
    MQSENSORS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mqsensors_init( &mqsensors, &cfg );
}
```

### Application Task

> Reads the adc value and prints in two forms (DEC and HEX)

```c
void application_task ( void )
{
    mqsensors_data_t tmp;
    
    //  Task implementation.
    
    tmp = mqsensors_generic_read ( &mqsensors );
    log_printf
    ( 
        &logger, 
        "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", 
        tmp, 
        tmp
    );
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.MqSensors

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
