
---
# BLE 9 Click

> [BLE 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4487) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4487&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of BLE 9 Click board by processing the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ble9

### Example Key Functions

- `ble9_cfg_setup` function initializes Click configuration structure to initial values.
```c
void ble9_cfg_setup ( ble9_cfg_t *cfg );
```

- `ble9_init` function initializes all necessary peripherals.
```c
err_t ble9_init ( ble9_t *ctx, ble9_cfg_t *cfg );
```

- `ble9_adv_create_id` function creates adequate ID.
```c
err_t ble9_adv_create_id ( ble9_t *ctx );
```

- `ble9_adv_start` function starts advertising.
```c
err_t ble9_adv_start ( ble9_t *ctx, ble9_adv_mode_discoverable_t discover, ble9_adv_mode_connectable_t connect );
```

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

### Note

> <pre>
> For more information on the chip itself and the firmware on it,
> please visit the following page:
>     [1] https://docs.silabs.com/bluetooth/3.1
>         - Take into condideration that the library itself
>           is designed to work with GSDK version 3.1.0
>           If you wish to use a different version of firmware,
>           take into consideration that some functions might not work.
> </pre>

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
