
---
# USB-C Power 2 Click

> [USB-C Power 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6939) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6939&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the USB-C Power 2 Click board for
detecting USB cable attachment and monitoring CC (Configuration Channel)
status. The application reads interrupt and CC status registers and logs
the interpreted results to the serial terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCPower2

### Example Key Functions

- `usbcpower2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void usbcpower2_cfg_setup ( usbcpower2_cfg_t *cfg );
```

- `usbcpower2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t usbcpower2_init ( usbcpower2_t *ctx, usbcpower2_cfg_t *cfg );
```

- `usbcpower2_default_cfg` This function executes a default configuration of USB-C Power 2 Click board.
```c
err_t usbcpower2_default_cfg ( usbcpower2_t *ctx );
```

- `usbcpower2_check_com` This function checks communication with the device by reading the vendor ID register and validating the returned value.
```c
err_t usbcpower2_check_com ( usbcpower2_t *ctx );
```

- `usbcpower2_get_int_pin` This function reads and returns the logic state of the INT pin.
```c
uint8_t usbcpower2_get_int_pin ( usbcpower2_t *ctx );
```

- `usbcpower2_read_reg` This function reads a single byte of data from the selected readable register address.
```c
err_t usbcpower2_read_reg ( usbcpower2_t *ctx, uint8_t reg, uint8_t *data_out );
```

### Application Init

> Initializes the logger and USB-C Power 2 Click driver, and applies the default device configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcpower2_cfg_t usbcpower2_cfg;  /**< Click config object. */

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
    usbcpower2_cfg_setup( &usbcpower2_cfg );
    USBCPOWER2_MAP_MIKROBUS( usbcpower2_cfg, MIKROBUS_POSITION_USBCPOWER2 );
    if ( I2C_MASTER_ERROR == usbcpower2_init( &usbcpower2, &usbcpower2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBCPOWER2_ERROR == usbcpower2_default_cfg ( &usbcpower2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for an USB detached/attached interrupt event, then reads and displays
cable connection status and CC line status information including VBUS detection,
Rp value, port attachment state, and cable polarity.

```c
void application_task ( void )
{
    uint8_t status = 0;
    if ( !usbcpower2_get_int_pin ( &usbcpower2 ) )
    {
        if ( USBCPOWER2_OK == usbcpower2_read_reg ( &usbcpower2, USBCPOWER2_REG_INTERRUPT_STATUS, &status ) )
        {
            log_printf ( &logger, "USB Status: " );
            if ( status & USBCPOWER2_INTERRUPT_STATUS_CABLE_ATTACHED )
            {
                log_printf ( &logger, "Attached\r\n" );
            }
            else if ( status & USBCPOWER2_INTERRUPT_STATUS_CABLE_DETACHED )
            {
                log_printf ( &logger, "Detached\r\n" );
            }
            else
            {
                log_printf ( &logger, "Unknown\r\n" );
            }
        }
        if ( USBCPOWER2_OK == usbcpower2_read_reg ( &usbcpower2, USBCPOWER2_REG_CC_STATUS, &status ) )
        {
            usbcpower2_display_cc_status ( status );
        }
        Delay_ms ( 10 );
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
