
---
# USB UART 6 Click

> [USB UART 6 Click](https://www.mikroe.com/?pid_product=MIKROE-6725) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6725&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the USB UART 6 Click board's ability to act as a USB-to-UART bridge.
It enables bidirectional communication between a USB host and a UART device by forwarding 
received data between the USB and UART interfaces.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBUART6

### Example Key Functions

- `usbuart6_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void usbuart6_cfg_setup ( usbuart6_cfg_t *cfg );
```

- `usbuart6_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t usbuart6_init ( usbuart6_t *ctx, usbuart6_cfg_t *cfg );
```

- `usbuart6_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t usbuart6_generic_write ( usbuart6_t *ctx, uint8_t *data_in, uint16_t len );
```

- `usbuart6_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t usbuart6_generic_read ( usbuart6_t *ctx, uint8_t *data_out, uint16_t len );
```

- `usbuart6_enable_device` This function enables the device by setting the EN pin to high logic state.
```c
void usbuart6_enable_device ( usbuart6_t *ctx );
```

### Application Init

> Initializes the logger and the Click board and enables the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuart6_cfg_t usbuart6_cfg;  /**< Click config object. */

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
    usbuart6_cfg_setup( &usbuart6_cfg );
    USBUART6_MAP_MIKROBUS( usbuart6_cfg, MIKROBUS_1 );
    if ( UART_ERROR == usbuart6_init( &usbuart6, &usbuart6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    usbuart6_enable_device ( &usbuart6 );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );

    // Dummy read to enable RX interrupts
    uart_read( &usbuart6.uart, app_buf, 1 );
    uart_read( &logger.uart, app_buf, 1 );
}
```

### Application Task

> Continuously reads the data from one UART interface and forwards it to the other, enabling seamless USB to UART data transfer and vice versa.

```c
void application_task ( void )
{
    if ( uart_bytes_available ( &logger.uart ) ) 
    {
        app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
        if ( app_buf_len > 0 )
        {
            uart_write ( &usbuart6.uart, app_buf, app_buf_len );
            memset( app_buf, 0, app_buf_len );
            app_buf_len = 0;
        }
    }
    if ( uart_bytes_available ( &usbuart6.uart ) ) 
    {
        app_buf_len = uart_read( &usbuart6.uart, app_buf, PROCESS_BUFFER_SIZE );
        if ( app_buf_len > 0 )
        {
            uart_write ( &logger.uart, app_buf, app_buf_len );
            memset( app_buf, 0, app_buf_len );
            app_buf_len = 0;
        }
    }
}
```

### Note

> Make sure the USB UART 6 Click is properly connected to a USB host and the mikroBUS socket, and that both UART interfaces are configured for the same baud rate.

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
