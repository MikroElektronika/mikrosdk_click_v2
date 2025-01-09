
---
# M-BUS RF 3 Click

> [M-BUS RF 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6084) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6084&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of M-BUS RF 3 Click board by processing
  the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MBUSRF3

### Example Key Functions

- `mbusrf3_cfg_setup` Config Object Initialization function.
```c
void mbusrf3_cfg_setup ( mbusrf3_cfg_t *cfg );
```

- `mbusrf3_init` Initialization function.
```c
err_t mbusrf3_init ( mbusrf3_t *ctx, mbusrf3_cfg_t *cfg );
```

- `mbusrf3_default_cfg` Click Default Configuration function.
```c
err_t mbusrf3_default_cfg ( mbusrf3_t *ctx );
```

- `mbusrf3_set_rst_pin` This function is used to set reset pin state.
```c
void mbusrf3_set_rst_pin ( mbusrf3_t *ctx, uint8_t pin_state );
```

- `mbusrf3_send_command` This function is used to send a desired command.
```c
err_t mbusrf3_send_command ( mbusrf3_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );
```

- `mbusrf3_send_data` This function is used to data in transmitter mode.
```c
err_t mbusrf3_send_data ( mbusrf3_t *ctx, uint8_t *data_in, uint8_t len );
```

### Application Init

> Initializes the driver and performs the Click configuration depending on selected DEMO_EXAMPLE macro.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mbusrf3_cfg_t mbusrf3_cfg;  /**< Click config object. */

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
    mbusrf3_cfg_setup( &mbusrf3_cfg );
    MBUSRF3_MAP_MIKROBUS( mbusrf3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == mbusrf3_init( &mbusrf3, &mbusrf3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    mbusrf3_process( );
    mbusrf3_clear_app_buf( );
    Delay_ms ( 500 );
   
    mbusrf3_configure_for_example( );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example contains two examples depending on selected DEMO_EXAMPLE macro:
 > EXAMPLE_TRANSMIT - Device is sending MESSAGE data to be read by receiver.
 > EXAMPLE_RECEIVER - Device is reading transmitted message, and display it on USB UART terminal.

```c
void application_task ( void ) 
{
    mbusrf3_example( );
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
