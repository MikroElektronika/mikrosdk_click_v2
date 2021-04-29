\mainpage Main Page
 
---
# BLE 8 click

BLE 8 Click is fully embedded stand-alone Bluetooth 5.0 Energy connectivity module, equipped with the ANNA-B112, an ultra-small, high-performing, standalone Bluetooth low energy module for easy integration of Bluetooth low energy connectivity (BLE) into various electronic devices. This module combines a high-performance Arm® Cortex®-M4 CPU microprocessor with FPU, and state-of-the-art power performance. Reliable and easy to use, BLE 8 click is a perfect solution for development of various IoT applications, smart home applications, BLE enabled toys, advanced robotics, and other similar applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ble8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ble-8-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Ble8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ble8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ble8_cfg_setup ( ble8_cfg_t *cfg ); 
 
- Initialization function.
> BLE8_RETVAL ble8_init ( ble8_t *ctx, ble8_cfg_t *cfg );

#### Example key functions :
 
- This function allows user to reset a module.
> void ble8_reset ( ble8_t *ctx );

## Examples Description

> This example reads and processes data from BLE 8 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble8_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ble8_cfg_setup( &cfg );
    BLE8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble8_init( &ble8, &cfg );

    ble8_reset( &ble8 );
    Delay_1sec( );
    
    log_printf( &logger, "Configuring the module...\n" );
    Delay_1sec( );
    
    ble8_set_dsr_pin( &ble8, 1 );
    Delay_ms( 20 );

    do {
        ble8_set_echo_cmd( &ble8, 1 );
        Delay_100ms( );
    }
    while( ble8_process( ) != 1 );
    
    do {
        ble8_set_local_name_cmd( &ble8, "BLE 8 Click" );
        Delay_100ms( );
    }
    while( ble8_process( ) != 1 );
    
    do {
        ble8_connectability_en_cmd( &ble8, BLE8_GAP_CONNECTABLE_MODE );
        Delay_100ms( );
    }
    while( ble8_process( ) != 1 );
    
    do {
        ble8_discoverability_en_cmd( &ble8, BLE8_GAP_GENERAL_DISCOVERABLE_MODE );
        Delay_100ms( );
    }
    while( ble8_process( ) != 1 );
    
    do {
        ble8_enter_mode_cmd( &ble8, BLE8_DATA_MODE );
        Delay_100ms( );
    }
    while( ble8_process( ) != 1 );
    
    ble8_set_dsr_pin( &ble8, 0 );
    Delay_ms( 20 );
    data_mode = 1;
    log_printf( &logger, "The module has been configured.\n" );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    ble8_process( );
} 

```

## Note

> <pre>
> The all possible commands, module configuration and specification can be found in the 
> related documents:
>     [1] ANNA-B112 System Integration Manual, document number UBX-18009821 
>     [2] u-blox Short Range AT Commands Manual, document number UBX-14044127 
>     [3] ANNA-B112 Getting Started Guide, document number UBX-18020387 
>     [4] ANNA-B112 Declaration of Conformity, document number UBX-18058993
> </pre>

The full application code, and ready to use projects can be installed directly from compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ble8

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
