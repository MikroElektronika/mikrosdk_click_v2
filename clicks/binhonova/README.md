
---
# Binho Nova Click

> [Binho Nova Click](https://www.mikroe.com/?pid_product=MIKROE-4439) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4439&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Binho Nova Click board by processing the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BinhoNova

### Example Key Functions

- `binhonova_cfg_setup` Config Object Initialization function.
```c
void binhonova_cfg_setup ( binhonova_cfg_t *cfg );
```

- `binhonova_init` Initialization function.
```c
err_t binhonova_init ( binhonova_t *ctx, binhonova_cfg_t *cfg );
```

- `binhonova_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t binhonova_generic_write ( binhonova_t *ctx, uint8_t *data_in, uint16_t len );
```

- `binhonova_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t binhonova_generic_read ( binhonova_t *ctx, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    binhonova_cfg_t binhonova_cfg;  /**< Click config object. */

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
    binhonova_cfg_setup( &binhonova_cfg );
    BINHONOVA_MAP_MIKROBUS( binhonova_cfg, MIKROBUS_1 );
    if ( UART_ERROR == binhonova_init( &binhonova, &binhonova_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    
    uart_set_blocking( &logger.uart, false );
}
```

### Application Task

> All data received from the USB UART will be forwarded to mikroBUS UART, and vice versa.

```c
void application_task ( void )
{
    app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &binhonova.uart, app_buf, app_buf_len );
        memset( app_buf, 0, app_buf_len );
        app_buf_len = 0;
    }
    app_buf_len = uart_read( &binhonova.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &logger.uart, app_buf, app_buf_len );
        memset( app_buf, 0, app_buf_len );
        app_buf_len = 0;
    }
}
```

### Note

> The example code is performed via UART communication and consists of a few simple steps:
> 1. Place "Binho Nova Click" into the mikroBUS socket 1.
> 2. Insert the "Binho USB Host Adapter" connector into the "Binho Nova Click" I2C/UART slot.
> 3. Start the "Mission Control Software" application.
> 4. Connect "Binho USB Host Adapter".
> 5. Activate UART Bridge with a baud rate of 115200bps.
> 6. All data sent via the "Mission Control Software" application will be displayed on the USB UART logger, and vice versa.

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
