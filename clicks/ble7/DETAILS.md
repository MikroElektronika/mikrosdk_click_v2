
---
# BLE 7 click

The BLE 7 click is a Click board™ witch provide BT/BLE connectivity for any embedded application. BLE 7 click based on the BGX13S22GA-V31, a SiP module from Silicon Labs with a buit-in antenna. Click board™ an ultra-small, high-performing, Bluetooth low energy module for easy integration of Bluetooth low energy connectivity (BLE) into various electronic devices. Given its features, this click can be used for health, sports, and wellness devices as well as Industrial, home, and building automation; and smart phone, tablet, and PC accessories.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/ble7_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ble-7-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Ble7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ble7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ble7_cfg_setup ( ble7_cfg_t *cfg ); 
 
- Initialization function.
> BLE7_RETVAL ble7_init ( ble7_t *ctx, ble7_cfg_t *cfg );


#### Example key functions :

- This function allows user to reset BGX module.
> void ble7_reset ( ble7_t *ctx );
 
- This function sets handler on the function which should be performed, for example function for the results logging.
> void ble7_response_handler_set ( ble7_t *ctx, void ( *handler )( uint8_t* ) );

- This function reads response bytes from the BGX module and sets flag after each received byte.
> void ble7_uart_isr ( ble7_t *ctx, uint8_t rx_dat );

## Examples Description

> This example reads and processes data from BLE 7 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes peripherals, pins, UART serial interface, uart interrupt,
> and executes the module reset. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble7_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ble7_cfg_setup( &cfg );
    BLE7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble7_init( &ble7, &cfg );

    ble7_response_handler_set(  &ble7, &get_rsp );
    Delay_ms( 200 );

    ble7_reset( &ble7 );

    rsp_idx = 0;
    rsp_check = 0;
    log_check = BLE7_RSP_NOT_READY;
}
  
```

### Application Task

> Allows user to recive data from another device ( using mobile bluetooth terminal )

```c

void application_task ( void )
{
    ble7_process(  );
    log_rsp( );
}  

```

## Note

> https://docs.silabs.com/gecko-os/1/bgx/latest/commands

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ble7

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
