
---
# USB to Serial Click

> [USB to Serial Click](https://www.mikroe.com/?pid_product=MIKROE-7011) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7011&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jun 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the USB to Serial Click board's ability to act as a USB-to-UART bridge.
It enables bidirectional communication between a USB host and a UART device by forwarding 
received data between the USB and UART interfaces.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBtoSerial

### Example Key Functions

- `usbtoserial_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void usbtoserial_cfg_setup ( usbtoserial_cfg_t *cfg );
```

- `usbtoserial_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t usbtoserial_init ( usbtoserial_t *ctx, usbtoserial_cfg_t *cfg );
```

- `usbtoserial_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t usbtoserial_generic_write ( usbtoserial_t *ctx, uint8_t *data_in, uint16_t len );
```

- `usbtoserial_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t usbtoserial_generic_read ( usbtoserial_t *ctx, uint8_t *data_out, uint16_t len );
```

- `usbtoserial_reset_device` This function resets the device by toggling the reset pin logic state.
```c
void usbtoserial_reset_device ( usbtoserial_t *ctx );
```

- `usbtoserial_set_wkp_pin` This function sets the WKP pin to the selected logic state.
```c
void usbtoserial_set_wkp_pin ( usbtoserial_t *ctx, uint8_t state );
```

### Application Init

> Initializes the logger and the Click board and enables the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbtoserial_cfg_t usbtoserial_cfg;  /**< Click config object. */

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
    usbtoserial_cfg_setup( &usbtoserial_cfg );
    USBTOSERIAL_MAP_MIKROBUS( usbtoserial_cfg, MIKROBUS_POSITION_USBTOSERIAL );
    if ( UART_ERROR == usbtoserial_init( &usbtoserial, &usbtoserial_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    usbtoserial_reset_device ( &usbtoserial );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );

    uart_set_blocking( &logger.uart, false );

    // Dummy read to enable RX interrupts
    uart_read( &usbtoserial.uart, app_buf, 1 );
    uart_read( &logger.uart, app_buf, 1 );
}
```

### Application Task

> Continuously reads the data from one UART interface and forwards it to the other,
enabling seamless USB to UART data transfer and vice versa.

```c
void application_task ( void ) 
{
    if ( uart_bytes_available ( &logger.uart ) ) 
    {
        app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
        if ( app_buf_len > 0 )
        {
            uart_write ( &usbtoserial.uart, app_buf, app_buf_len );
            memset( app_buf, 0, app_buf_len );
            app_buf_len = 0;
        }
    }
    if ( uart_bytes_available ( &usbtoserial.uart ) ) 
    {
        app_buf_len = uart_read( &usbtoserial.uart, app_buf, PROCESS_BUFFER_SIZE );
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

> Make sure the USB to Serial Click is properly connected to a USB host and the 
mikroBUS socket, and that both UART interfaces are configured for the same baud rate.

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
