
---
# GNSS RTK 2 Click

> [GNSS RTK 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5430) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5430&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : UART/I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of GNSS RTK 2 Click by reading and displaying the GNSS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSSRTK2

### Example Key Functions

- `gnssrtk2_cfg_setup` Config Object Initialization function.
```c
void gnssrtk2_cfg_setup ( gnssrtk2_cfg_t *cfg );
```

- `gnssrtk2_init` Initialization function.
```c
err_t gnssrtk2_init ( gnssrtk2_t *ctx, gnssrtk2_cfg_t *cfg );
```

- `gnssrtk2_default_cfg` Click Default Configuration function.
```c
err_t gnssrtk2_default_cfg ( gnssrtk2_t *ctx );
```

- `gnssrtk2_reset_device` This function resets the device by toggling the RST pin.
```c
void gnssrtk2_reset_device ( gnssrtk2_t *ctx );
```

- `gnssrtk2_generic_read` This function reads a desired number of data bytes from the module.
```c
err_t gnssrtk2_generic_read ( gnssrtk2_t *ctx, uint8_t *data_out, uint8_t len );
```

- `gnssrtk2_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t gnssrtk2_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```

### Application Init

> Initializes the driver and resets the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssrtk2_cfg_t gnssrtk2_cfg;  /**< Click config object. */

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
    gnssrtk2_cfg_setup( &gnssrtk2_cfg );
    GNSSRTK2_MAP_MIKROBUS( gnssrtk2_cfg, MIKROBUS_1 );
    err_t init_flag = gnssrtk2_init( &gnssrtk2, &gnssrtk2_cfg );
    if ( ( UART_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the GNGGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    gnssrtk2_process( &gnssrtk2 );
    if ( app_buf_len > ( sizeof ( GNSSRTK2_RSP_GNGGA ) + GNSSRTK2_GNGGA_ELEMENT_SIZE ) ) 
    {
        gnssrtk2_parser_application( app_buf );
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
