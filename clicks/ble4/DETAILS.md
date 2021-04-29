 
---
# BLE 4  click

BLE 4 Click is fully embedded stand-alone Bluetooth 5.0 low energy connectivity module, equipped with the NINA-B312, an ultra-small, high-performing, standalone Bluetooth low energy module for easy integration of Bluetooth low energy connectivity (BLE) into various electronic devices. This module combines a high-performance Arm® Cortex®-M4 CPU microprocessor with FPU, and state-of-the-art power performance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ble4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ble-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the BLE4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BLE4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ble4_cfg_setup ( ble4_cfg_t *cfg ); 
 
- Initialization function.
> BLE4_RETVAL ble4_init ( ble4_t *ctx, ble4_cfg_t *cfg );

#### Example key functions :

- This function allows user to reset a module.
> void ble4_reset ( ble4_t *ctx );

## Examples Description

> This example reads and processes data from BLE 4 clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ble4_cfg_setup( &cfg );
    BLE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble4_init( &ble4, &cfg );

    ble4_reset( &ble4 );
    Delay_1sec( );
    
    log_printf( &logger, "Configuring the module...\n" );
    Delay_1sec( );
    
    ble4_set_dsr_pin( &ble4, 1 );
    Delay_ms( 20 );

    do {
        ble4_set_echo_cmd( &ble4, 1 );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    do {
        ble4_set_local_name_cmd( &ble4, "BLE 4 Click" );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    do {
        ble4_connectability_en_cmd( &ble4, BLE4_GAP_CONNECTABLE_MODE );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    do {
        ble4_discoverability_en_cmd( &ble4, BLE4_GAP_GENERAL_DISCOVERABLE_MODE );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    do {
        ble4_enter_mode_cmd( &ble4, BLE4_DATA_MODE );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    ble4_set_dsr_pin( &ble4, 0 );
    Delay_ms( 20 );
    data_mode = 1;
    log_printf( &logger, "The module has been configured.\n" );
}
  
```

### Application Task

> Reads the received data and parses it. 

```c

void application_task ( void )
{
    ble4_process( );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BLE4

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
