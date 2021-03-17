\mainpage Main Page
  
---
# Buck 9 / 10 click

Buck 9 Click is a high-efficiency step-down converter which provides a highly regulated output voltage derived from the connected power source, rated from 4V to 36V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/buck910-click-group.png" height=300px>
</p>

[Product page - Buck 10 click](<https://www.mikroe.com/buck-10-click>)
[Product page - Buck 9 click](<https://www.mikroe.com/buck-9-click>)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Buck910 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buck910 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck_9_10_cfg_setup ( buck_9_10_cfg_t *cfg ); 
 
- Initialization function.
> BUCK_9_10_RETVAL buck_9_10_init ( buck_9_10_t *ctx, buck_9_10_cfg_t *cfg );


#### Example key functions :

- Function for enable or disable device
> void buck9_set_device_mode ( buck_9_10_t *ctx, uint8_t mode );

## Examples Description

> Demo application shows basic usage of Buck 9 and Buck 10 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck_9_10_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    buck_9_10_cfg_setup( &cfg );
    BUCK_9_10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck_9_10_init( &buck_9_10, &cfg );
}
```

### Application Task

> Enable and Disable device every 5 seconds.

```c
void application_task ( void )
{
    buck9_set_device_mode ( &buck_9_10, BUCK_9_10_DEVICE_ENABLE );
    log_printf(&logger, "Output:\t ENABLED\r\n");
    Delay_ms( 5000 );
    buck9_set_device_mode ( &buck_9_10, BUCK_9_10_DEVICE_DISABLE );
    log_printf(&logger, "Output:\t DISABLED\r\n");
    Delay_ms( 5000 );
}
```

## Note

> Note for Buck 9 click: 
>   User can connect from 3v3 or 5v to 36V on the input(VIN) and when 
>   enable the device get 3v3 or 5v voltage on the output(VOUT).
>   On the VOUT connect the load to 3A.
> 
> Note for Buck 10 click: 
>   Input voltage recommended range - from 4V to 18V
>   Low-side valley current limit - from 3A to 3.9A
>   Low-side negative current limit - (-2.5A)
>   Output voltage - 3.3V or 5V

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck910

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
