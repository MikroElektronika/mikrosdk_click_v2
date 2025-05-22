
---
# GNSS RTK 4 Click

> [GNSS RTK 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6580) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6580&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of GNSS RTK 4 Click by reading and displaying the GNSS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSSRTK4

### Example Key Functions

- `gnssrtk4_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void gnssrtk4_cfg_setup ( gnssrtk4_cfg_t *cfg );
```

- `gnssrtk4_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t gnssrtk4_init ( gnssrtk4_t *ctx, gnssrtk4_cfg_t *cfg );
```

- `gnssrtk4_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t gnssrtk4_generic_read ( gnssrtk4_t *ctx, uint8_t *data_out, uint16_t len );
```

- `gnssrtk4_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t gnssrtk4_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

- `gnssrtk4_reset_device` This function resets the device by toggling the RST pin.
```c
void gnssrtk4_reset_device ( gnssrtk4_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssrtk4_cfg_t gnssrtk4_cfg;  /**< Click config object. */

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
    gnssrtk4_cfg_setup( &gnssrtk4_cfg );
    GNSSRTK4_MAP_MIKROBUS( gnssrtk4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnssrtk4_init( &gnssrtk4, &gnssrtk4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the NMEA GGA info from it, and once it receives 
the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    if ( GNSSRTK4_OK == gnssrtk4_process( &gnssrtk4 ) ) 
    {
        gnssrtk4_parser_application( app_buf );
    }
}
```

### Note

> The Click board comes with the default baud rate of 460800, but the baud rate is set to 115200
in the library due to code portability and speed limitations of some MCUs. So in order to run
the example you will need to adjust the baud rate using Quectel QGNSS evaluation software.

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
