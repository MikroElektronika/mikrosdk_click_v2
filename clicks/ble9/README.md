\mainpage Main Page

---
# BLE 9 click

BLE 9 Click is a fully embedded stand-alone Bluetooth 5.2 Energy connectivity module, equipped with the EFR32BG22 Series 2 Modules, an ultra-small, high-performing, standalone Bluetooth low energy module for easy integration of Bluetooth low energy connectivity (BLE) into various electronic devices. This module combines a high-performance Arm® Cortex®-M33 CPU microprocessor with FPU, and state-of-the-art power performance. Reliable and easy to use, BLE 9 click is a perfect solution for development of various IoT applications, smart home applications, BLE enabled toys, advanced robotics, and other similar applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ble9_click.png">
</p>

[click Product page](https://www.mikroe.com/ble-9-click)

---

#### Click library

- **Author**        : Strahinja Jacimovic
- **Date**          : Dec 2020.
- **Type**          : UART GSM/IOT type

# Software Support

We provide a library for the BLE9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ble9 Click driver.

#### Standard key functions :

- `ble9_cfg_setup` function initializes click configuration structure to initial values.
```c
void ble9_cfg_setup ( ble9_cfg_t *cfg );
```

- `ble9_init` function initializes all necessary peripherals.
```c
BLE9_RETVAL ble9_init ( ble9_t *ctx, ble9_cfg_t *cfg );
```

#### Example key functions :

- `ble9_advertiser_create_id` function creates adequate ID.
```c
BLE9_RETVAL init_flag = ble9_advertiser_create_id( &ble9 );
```

- `ble9_advertiser_start` function starts advertizing.
```c
ble9_advertiser_start( &ble9, BLE9_ADVERTISER_MODE_DISCOVERABLE_GENERAL, BLE9_ADVERTISER_MODE_CONNECTABLE_SCANNABLE );
```

## Examples Description

> This example reads and processes data from BLE 9 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and sets up adequate module
> ID, as well as starting module advertizing.
> Once in this state, the module can be connected to and
> communicated with.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble9_cfg_t cfg;

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
    Delay_ms( 100 );

    //  Click initialization.

    ble9_cfg_setup( &cfg );
    BLE9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble9_init( &ble9, &cfg );

    log_printf( &logger, "Creating advertising point...\n" );
    Delay_ms( 100 );
    ble9_advertiser_create_id( &ble9 );

    log_printf( &logger, "Starting module advertizing...\n" );
    Delay_ms( 100 );
    ble9_advertiser_start( &ble9, BLE9_ADVERTISER_MODE_DISCOVERABLE_GENERAL,
                                  BLE9_ADVERTISER_MODE_CONNECTABLE_SCANNABLE );

    log_printf( &logger, "The module has been configured.\n" );
    Delay_ms( 100 );
}

```

### Application Task

> Reads received data.

```c

void application_task ( void )
{
    ble9_process( );
}

```

## Note

> <pre>
> For more information on the chip itself and the firmware on it,
> please visit the following page:
>     [1] https://docs.silabs.com/bluetooth/3.1
>         - Take into condideration that the library itself
>           is designed to work with GSDK version 3.1.0
>           If you wish to use a different version of firmware,
>           take into consideration that some functions might not work.
> </pre>

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ble9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
