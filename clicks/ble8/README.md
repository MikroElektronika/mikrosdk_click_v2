\mainpage Main Page
 
---
# BLE 8 click

BLE 8 Click is fully embedded stand-alone Bluetooth 5.0 Energy connectivity module, equipped with the ANNA-B112, an ultra-small, high-performing, standalone Bluetooth low energy module for easy integration of Bluetooth low energy connectivity (BLE) into various electronic devices. This module combines a high-performance Arm® Cortex®-M4 CPU microprocessor with FPU, and state-of-the-art power performance. Reliable and easy to use, BLE 8 click is a perfect solution for development of various IoT applications, smart home applications, BLE enabled toys, advanced robotics, and other similar applications.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/ble8_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ble-8-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Ble8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ble8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ble8_cfg_setup ( ble8_cfg_t *cfg ); 
 
- Initialization function.
> BLE8_RETVAL ble8_init ( ble8_t *ctx, ble8_cfg_t *cfg );

- Click Default Configuration function.
> void ble8_default_cfg ( ble8_t *ctx );


#### Example key functions :

- This function sets handler on the function which should be performed, 
- for example function for the results logging.
> void ble8_response_handler_set ( ble8_t *ctx, void ( *handler )( uint8_t* ) );
 
- This function allows user to reset a module.
> void ble8_reset ( ble8_t *ctx );

- This function reads response bytes from the module and sets flag after each received byte.
> void ble8_uart_isr ( ble8_t *ctx, uint8_t read_data );

## Examples Description

> This example reads and processes data from BLE 8 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes UART serial interface, UART interrupt,
> and executes a module reset. Allows user to enter command mode.

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

    ble8_response_handler_set( &ble8, &get_rsp );
    Delay_ms( 200 );

    ble8_reset( &ble8 );
    Delay_ms( 2000 );

    rsp_idx = 0;
    rsp_check = 1;
    start_timer = 0;
    timer_cnt = 0;
    prev_data = 0;
    log_check = BLE8_RSP_NOT_READY;

    #ifdef COMMAND_MODE
        log_printf( &logger, "COMMAND MODE ENTERING...\r\n" );

        ble8_set_dsr_pin( &ble8, 1 );
        Delay_ms( 20 );
        ble8_set_dsr_pin( &ble8, 0 );
        Delay_ms( 20 );

        ble8_set_echo_cmd( &ble8, BLE8_ECHO_OFF );
        ble8_process( );
        log_rsp( );
        Delay_ms( 100 );
    #else
        log_printf( &logger, "DEFAULT MODE ENTERING...\r\n" );
    #endif
}
  
```

### Application Task

> This function has two segments.
> First segment allows user to enter a commands, for using function from driver
> ( those with AT command ). Second ( default ) segment allows user to comunicate with 
> other bluetooth devices - by sending data to the ANNA-B112 module.

```c

void application_task ( void )
{
    ble8_process( );

    if ( start_timer == 1 )
    {
        timer_cnt++;
    }

    log_rsp( );
    Delay_us( 1 );
} 

```

## Note

> <pre>
> For using AT commands swich to COMMAND_MODE
> The all possible commands, module configuration and specification can be found in the 
> related documents:
>     [1] ANNA-B112 System Integration Manual, document number UBX-18009821 
>     [2] u-blox Short Range AT Commands Manual, document number UBX-14044127 
>     [3] ANNA-B112 Getting Started Guide, document number UBX-18020387 
>     [4] ANNA-B112 Declaration of Conformity, document number UBX-18058993
> </pre>

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ble8

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
