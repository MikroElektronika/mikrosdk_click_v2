
---
# Barcode 3 Click

> [Barcode 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6130) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6130&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of the Barcode 3 Click board by scanning and displaying the content of a barcode or QR Code.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Barcode3

### Example Key Functions

- `barcode3_cfg_setup` Config Object Initialization function.
```c
void barcode3_cfg_setup ( barcode3_cfg_t *cfg );
```

- `barcode3_init` Initialization function.
```c
err_t barcode3_init ( barcode3_t *ctx, barcode3_cfg_t *cfg );
```

- `barcode3_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t barcode3_generic_read ( barcode3_t *ctx, uint8_t *data_out, uint16_t len );
```

- `barcode3_start_scanning` This function starts the barcode scanning by setting the TRG pin to low logic state.
```c
void barcode3_start_scanning ( barcode3_t *ctx );
```

- `barcode3_stop_scanning` This function stops the barcode scanning by setting the TRG pin to high logic state.
```c
void barcode3_stop_scanning ( barcode3_t *ctx );
```

### Application Init

> Initializes the driver, stops scanning and resets the barcode device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barcode3_cfg_t barcode3_cfg;  /**< Click config object. */

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
    barcode3_cfg_setup( &barcode3_cfg );
    BARCODE3_MAP_MIKROBUS( barcode3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == barcode3_init( &barcode3, &barcode3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    barcode3_stop_scanning ( &barcode3 );
    barcode3_reset_device ( &barcode3 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Triggers scanning and waits up to 3 seconds for the barcode to be detected.
If a barcode or QR Code is detected, it displays its content on the USB UART.

```c
void application_task ( void )
{
    uint16_t timeout = 0;
    log_printf( &logger, "\r\n------- SCAN START ------\r\n" );
    barcode3_start_scanning ( &barcode3 );
    while ( ++timeout < 3000 )
    {
        if ( BARCODE3_OK == barcode3_process( &barcode3 ) )
        {
            barcode3_log_app_buf( );
            barcode3_clear_app_buf( );
            Delay_10ms ( );
            while ( BARCODE3_OK == barcode3_process( &barcode3 ) )
            {
                barcode3_log_app_buf( );
                barcode3_clear_app_buf( );
                Delay_10ms ( );
            }
            break;
        }
        Delay_1ms ( );
    }
    log_printf( &logger, "------- SCAN STOP -------\r\n" );
    barcode3_stop_scanning ( &barcode3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

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
