 
---
# BLE 3 click

BLE 3 click is a quick and simple solution if you want to add Bluetooth Low Energy to your project. It features the NINA-B1 Bluetooth 4.2 module, from u-blox. This click also comes with an integrated antenna mounted on the PCB.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/ble3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ble-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Ble3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ble3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ble3_cfg_setup ( ble3_cfg_t *cfg ); 
 
- Initialization function.
> BLE3_RETVAL ble3_init ( ble3_t *ctx, ble3_cfg_t *cfg );

- Click Default Configuration function.
> void ble3_default_cfg ( ble3_t *ctx );


#### Example key functions :

- This function read specific number of data using uart_read function.
> uint16_t ble3_generic_read ( ble3_t *ctx, char *data_buf, uint16_t max_len );
 

## Examples Description

> This example reads and processes data from BLE 3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ble3_cfg_setup( &cfg );
    BLE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble3_init( &ble3, &cfg );

    ble3_default_cfg ( &ble3 );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    ble3_process(  );
    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ble3

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
