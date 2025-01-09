
---
# RTK Base Click

> [RTK Base Click](https://www.mikroe.com/?pid_product=MIKROE-5442) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5442&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2022.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of RTK Base Click by reading and displaying the RTCM3 messages.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTKBase

### Example Key Functions

- `rtkbase_cfg_setup` Config Object Initialization function.
```c
void rtkbase_cfg_setup ( rtkbase_cfg_t *cfg );
```

- `rtkbase_init` Initialization function.
```c
err_t rtkbase_init ( rtkbase_t *ctx, rtkbase_cfg_t *cfg );
```

- `rtkbase_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t rtkbase_generic_read ( rtkbase_t *ctx, char *data_out, uint16_t len );
```

- `rtkbase_rx_bytes_available` This function returns the number of bytes available in the RX ring buffer.
```c
err_t rtkbase_rx_bytes_available ( rtkbase_t *ctx );
```

- `rtkbase_calculate_crc24` This function calculates and returns the CRC 24-bit of RTCM3 packet input. The CRC across the whole packet should sum to zero (remainder).
```c
uint32_t rtkbase_calculate_crc24( uint8_t *data_buf, uint16_t data_len );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtkbase_cfg_t rtkbase_cfg;  /**< Click config object. */

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
    rtkbase_cfg_setup( &rtkbase_cfg );
    RTKBASE_MAP_MIKROBUS( rtkbase_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rtkbase_init( &rtkbase, &rtkbase_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and parses the RTCM3 messages received from the module, and displays them on the USB UART.

```c
void application_task ( void )
{
    rtkbase_process_rtcm3 ( &rtkbase );
    rtkbase_clear_app_buf( );
}
```

### Note

> The Click board comes with the default baud rate of 460800, but the baud rate is set to 115200
in the example due to code portability and speed limitations of some MCUs. So in order to run
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
