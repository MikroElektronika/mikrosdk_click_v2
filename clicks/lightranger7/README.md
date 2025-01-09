
---
# LightRanger 7 Click

> [LightRanger 7 Click](https://www.mikroe.com/?pid_product=MIKROE-6238) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6238&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of LightRanger 7 Click board by processing the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger7

### Example Key Functions

- `lightranger7_cfg_setup` Config Object Initialization function.
```c
void lightranger7_cfg_setup ( lightranger7_cfg_t *cfg );
```

- `lightranger7_init` Initialization function.
```c
err_t lightranger7_init ( lightranger7_t *ctx, lightranger7_cfg_t *cfg );
```

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

### Application Init

> Initializes the driver and performs the Click default configuration.

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

### Note

> By default, the Click board is programmed with the AFBR_S50_Example_RA4M2 firmware.
At the beginning this FW returns API version, chip ID, and module version. After that
it starts the measurements and prints the recent measurement results that consists of:
> - Time stamp in seconds since the last MCU reset.
> - Range in mm (converting the Q9.22 value to mm).
> - Amplitude in LSB (converting the UQ12.4 value to LSB).
> - Signal Quality in % (100% = good signal).
> - Status (0: OK; < 0: Error; > 0: Warning.
>
> For more information refer to the [AFBR-S50 GitHub repository](https://github.com/Broadcom/AFBR-S50-API).


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
