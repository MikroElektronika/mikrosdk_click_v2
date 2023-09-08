
---
# LightRanger 7 click

> LightRanger 7 Click is a compact add-on board capable of precise distance measurement and motion tracking. This board features the AFBR-S50, a medium-range 3D multipixel Time-of-Flight (ToF) sensor from Broadcom. Besides a VCSEL-based ToF sensor (Laser Class 1 eye safety), optimized to measure various distances working equally well on white, black, colored, and metallic reflective surfaces, this board also includes a 32-bit MCU, RA4M2 group of Renesas MCU with Arm® Cortex®-M33 core, alongside a 4-pin standard CAN connections compatible with Pixhawk®, a popular general-purpose flight controller.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lightranger7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lightranger-7-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : UART type


# Software Support

We provide a library for the LightRanger 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LightRanger 7 Click driver.

#### Standard key functions :

- `lightranger7_cfg_setup` Config Object Initialization function.
```c
void lightranger7_cfg_setup ( lightranger7_cfg_t *cfg );
```

- `lightranger7_init` Initialization function.
```c
err_t lightranger7_init ( lightranger7_t *ctx, lightranger7_cfg_t *cfg );
```

#### Example key functions :

- `lightranger7_reset_device` This function resets the device by toggling the rst pin state.
```c
void lightranger7_reset_device ( lightranger7_t *ctx );
```

- `lightranger7_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t lightranger7_generic_write ( lightranger7_t *ctx, uint8_t *data_in, uint16_t len );
```

- `lightranger7_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t lightranger7_generic_read ( lightranger7_t *ctx, uint8_t *data_out, uint16_t len );
```

## Example Description

> This example demonstrates the use of LightRanger 7 click board by processing the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger7_cfg_t lightranger7_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    lightranger7_cfg_setup( &lightranger7_cfg );
    LIGHTRANGER7_MAP_MIKROBUS( lightranger7_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lightranger7_init( &lightranger7, &lightranger7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, " Reset device\r\n" );
    lightranger7_reset_device ( &lightranger7 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and processes all incoming data and displays them on the USB UART.

```c
void application_task ( void )
{
    lightranger7_process( &lightranger7 );
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s", app_buf );
        lightranger7_clear_app_buf( );
    }
}
```

## Note

> By default, the click board is programmed with the AFBR_S50_Example_RA4M2 firmware.
At the beginning this FW returns API version, chip ID, and module version. After that
it starts the measurements and prints the recent measurement results that consists of:
> - Time stamp in seconds since the last MCU reset.
> - Range in mm (converting the Q9.22 value to mm).
> - Amplitude in LSB (converting the UQ12.4 value to LSB).
> - Signal Quality in % (100% = good signal).
> - Status (0: OK; < 0: Error; > 0: Warning.
>
> For more information refer to the [AFBR-S50 GitHub repository](https://github.com/Broadcom/AFBR-S50-API).


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
