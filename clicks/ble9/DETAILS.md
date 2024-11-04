
---
# BLE 9 Click

BLE 9 Click is a fully embedded stand-alone Bluetooth 5.2 Energy connectivity module, equipped with the EFR32BG22 Series 2 Modules, an ultra-small, high-performing, standalone Bluetooth low energy module for easy integration of Bluetooth low energy connectivity (BLE) into various electronic devices. This module combines a high-performance Arm® Cortex®-M33 CPU microprocessor with FPU, and state-of-the-art power performance. Reliable and easy to use, BLE 9 Click is a perfect solution for development of various IoT applications, smart home applications, BLE enabled toys, advanced robotics, and other similar applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ble9_click.png">
</p>

[Click Product page](https://www.mikroe.com/ble-9-click)

---

#### Click library

- **Author**        : MikroE Team
- **Date**          : Dec 2020.
- **Type**          : UART type

# Software Support

We provide a library for the BLE9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ble9 Click driver.

#### Standard key functions :

- `ble9_cfg_setup` function initializes Click configuration structure to initial values.
```c
void ble9_cfg_setup ( ble9_cfg_t *cfg );
```

- `ble9_init` function initializes all necessary peripherals.
```c
err_t ble9_init ( ble9_t *ctx, ble9_cfg_t *cfg );
```

#### Example key functions :

- `ble9_adv_create_id` function creates adequate ID.
```c
err_t ble9_adv_create_id ( ble9_t *ctx );
```

- `ble9_adv_start` function starts advertising.
```c
err_t ble9_adv_start ( ble9_t *ctx, ble9_adv_mode_discoverable_t discover, ble9_adv_mode_connectable_t connect );
```

## Examples Description

> This example demonstrates the use of BLE 9 Click board by processing the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

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
    Delay_ms ( 100 );

    // Click initialization.
    ble9_cfg_setup( &cfg );
    BLE9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble9_init( &ble9, &cfg );
    Delay_ms ( 1000 );
    
    // Clear app buffer
    ble9_process ( &ble9 );
    ble9_clear_app_buf( );
    Delay_ms ( 100 );
    
    if ( BLE9_OK == ble9_sys_get_version ( &ble9 ) )
    {
        log_printf( &logger, "--- System Version ---\r\n" );
        log_printf( &logger, " Major: 0x%.4X\r\n", ble9.ble9_version.version_major );
        log_printf( &logger, " Minor: 0x%.4X\r\n", ble9.ble9_version.version_minor );
        log_printf( &logger, " Patch: 0x%.4X\r\n", ble9.ble9_version.version_patch );
        log_printf( &logger, " Build: 0x%.4X\r\n", ble9.ble9_version.version_build );
        log_printf( &logger, " Bootloader: 0x%.8LX\r\n", ble9.ble9_version.version_bootloader );
        log_printf( &logger, " Hash: 0x%.8LX\r\n", ble9.ble9_version.version_hash );
        log_printf( &logger, "------------------------\r\n" );
    }
    
    log_printf( &logger, "Creating advertising point...\r\n" );
    Delay_ms ( 100 );
    ble9_adv_create_id ( &ble9 );

    log_printf( &logger, "Starting module advertising...\r\n" );
    Delay_ms ( 100 );
    ble9_adv_start ( &ble9, BLE9_ADVERTISER_MODE_DISCOVERABLE_GENERAL, 
                     BLE9_ADVERTISER_MODE_CONNECTABLE_SCANNABLE );

    log_printf( &logger, "The module has been configured.\r\n" );
    Delay_ms ( 100 );
}

```

### Application Task

> Reads and processes all incoming data and displays them on the USB UART.

```c

void application_task ( void )
{
    ble9_process ( &ble9 );
    if ( app_buf_len > 0 ) 
    {
        for ( uint16_t cnt = 0; cnt < app_buf_len; cnt++ )
        {
            log_printf( &logger, "%.2X ", ( uint16_t ) app_buf[ cnt ] );
        }
        ble9_clear_app_buf( );
    }
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
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
