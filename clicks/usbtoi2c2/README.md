
---
# USB to I2C 2 Click

> [USB to I2C 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5065) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5065&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of USB to I2C 2 Click by echoing back all the received messages.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBtoI2C2

### Example Key Functions

- `usbtoi2c2_cfg_setup` Config Object Initialization function.
```c
void usbtoi2c2_cfg_setup ( usbtoi2c2_cfg_t *cfg );
```

- `usbtoi2c2_init` Initialization function.
```c
err_t usbtoi2c2_init ( usbtoi2c2_t *ctx, usbtoi2c2_cfg_t *cfg );
```

- `usbtoi2c2_default_cfg` Click Default Configuration function.
```c
err_t usbtoi2c2_default_cfg ( usbtoi2c2_t *ctx );
```

- `usbtoi2c2_write_data` This function writes a desired number of data bytes by using I2C serial interface.
```c
err_t usbtoi2c2_write_data ( usbtoi2c2_t *ctx, uint8_t *tx_buf, uint8_t tx_len );
```

- `usbtoi2c2_read_data` This function reads a desired number of data bytes by using I2C serial interface.
```c
err_t usbtoi2c2_read_data ( usbtoi2c2_t *ctx, uint8_t *rx_buf, uint8_t rx_len );
```

- `usbtoi2c2_reset_device` This function resets the device by toggling the RST pin state.
```c
void usbtoi2c2_reset_device ( usbtoi2c2_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbtoi2c2_cfg_t usbtoi2c2_cfg;  /**< Click config object. */

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
    usbtoi2c2_cfg_setup( &usbtoi2c2_cfg );
    USBTOI2C2_MAP_MIKROBUS( usbtoi2c2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == usbtoi2c2_init( &usbtoi2c2, &usbtoi2c2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBTOI2C2_ERROR == usbtoi2c2_default_cfg ( &usbtoi2c2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Any data which the host PC sends to the Virtual COM Port (for example, typed into the terminal 
window in UART Terminal) will be sent over USB to the Click board and then it will be read and 
echoed back by the MCU to the PC where the terminal program will display it.

```c
void application_task ( void )
{
    uint8_t rx_data = 0;
    if ( USBTOI2C2_OK == usbtoi2c2_read_data ( &usbtoi2c2, &rx_data, 1 ) )
    {
        if ( USBTOI2C2_OK == usbtoi2c2_write_data ( &usbtoi2c2, &rx_data, 1 ) )
        {
            log_printf( &logger, "%c", rx_data );
        }
    }
}
```

### Note

> Make sure to download and install appropriate VCP drivers on the host PC.

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
