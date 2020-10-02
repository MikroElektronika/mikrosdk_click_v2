\mainpage Main Page
 
 

---
# Hall Current 4 click

The Hall Current 4 click is designed to measure relatively high current by using the integrated ACS70331 sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent4_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/hall-current-4-click>)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the HallCurrent4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HallCurrent4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hallcurrent4_cfg_setup ( hallcurrent4_cfg_t *cfg ); 
 
- Initialization function.
> HALLCURRENT4_RETVAL hallcurrent4_init ( hallcurrent4_t *ctx, hallcurrent4_cfg_t *cfg );

#### Example key functions :

- Reads current in mA
> float hallcurrent4_get_current_data ( hallcurrent4_t *ctx );
 
- Reads raw (ADC) current data
> uint16_t hallcurrent4_get_raw_data ( hallcurrent4_t *ctx );

## Examples Description

> Demo application shows is reading current data in mA using Hall current 4 click. 

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hallcurrent4_cfg_setup( &cfg );
    HALLCURRENT4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent4_init( &hallcurrent4, &cfg );
}
```

### Application Task

> Reads Current value in mA and logs this data to USBUART every 1 sec.

```c
void application_task ( void )
{
    float current;

    current = hallcurrent4_get_current_data( &hallcurrent4 );

    log_printf( &logger, " >> Current value: %.2f mA\r\n", current );
    log_printf( &logger, " ------------------------- \r\n" );
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent4

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
