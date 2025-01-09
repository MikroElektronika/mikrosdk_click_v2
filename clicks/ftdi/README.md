
---
# FTDI Click

> [FTDI Click](https://www.mikroe.com/?pid_product=MIKROE-1421) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1421&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of FTDI Click by echoing back all the received messages.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.FTDI

### Example Key Functions

- `ftdi_cfg_setup` Config Object Initialization function.
```c
void ftdi_cfg_setup ( ftdi_cfg_t *cfg );
```

- `ftdi_init` Initialization function.
```c
err_t ftdi_init ( ftdi_t *ctx, ftdi_cfg_t *cfg );
```

- `ftdi_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t ftdi_generic_write ( ftdi_t *ctx, uint8_t *data_in, uint16_t len );
```

- `ftdi_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t ftdi_generic_read ( ftdi_t *ctx, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ftdi_cfg_t ftdi_cfg;  /**< Click config object. */

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
    ftdi_cfg_setup( &ftdi_cfg );
    FTDI_MAP_MIKROBUS( ftdi_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ftdi_init( &ftdi, &ftdi_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Any data which the host PC sends to the Virtual COM Port (for example, typed into the terminal 
window in UART Terminal) will be sent over USB to the Click board and then it will be read and 
echoed back by the MCU to the PC where the terminal program will display it. The data will also
be displayed on the USB UART.

```c
void application_task ( void )
{
    uint8_t rx_data = 0;
    if ( ftdi_generic_read ( &ftdi, &rx_data, 1 ) > 0 )
    {
        ftdi_generic_write ( &ftdi, &rx_data, 1 );
        log_printf( &logger, "%c", rx_data );
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
