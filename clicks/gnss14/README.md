
---
# GNSS 14 Click

> [GNSS 14 Click](https://www.mikroe.com/?pid_product=MIKROE-5995) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5995&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : UART/I2C type

# Software Support

## Example Description

> This example demonstrates the use of GNSS 14 Click board by reading and displaying
> the GNSS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS14

### Example Key Functions

- `gnss14_cfg_setup` Config Object Initialization function.
```c
void gnss14_cfg_setup ( gnss14_cfg_t *cfg );
```

- `gnss14_init` Initialization function.
```c
err_t gnss14_init ( gnss14_t *ctx, gnss14_cfg_t *cfg );
```

- `gnss14_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t gnss14_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```

- `gnss14_reset_device` This function resets the device by toggling the RST pin.
```c
void gnss14_reset_device ( gnss14_t *ctx );
```

### Application Init

> Initializes the driver and resets the Click board.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss14_cfg_t gnss14_cfg;  /**< Click config object. */

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
    gnss14_cfg_setup( &gnss14_cfg );
    GNSS14_MAP_MIKROBUS( gnss14_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss14_init( &gnss14, &gnss14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    gnss14_reset_device( &gnss14 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the GNGGA info from it, and once it receives the position fix
> it will start displaying the coordinates on the USB UART.

```c
void application_task ( void ) 
{
    if ( GNSS14_OK == gnss14_process( &gnss14 ) ) 
    {
        if ( app_buf_len > ( sizeof ( GNSS14_RSP_GNGGA ) + GNSS14_GNGGA_ELEMENT_SIZE ) ) 
        {
            gnss14_parser_application( app_buf );
        }
    }
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
