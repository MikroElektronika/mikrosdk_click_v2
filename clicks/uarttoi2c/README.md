
---
# UART to I2C Click

> [UART to I2C Click](https://www.mikroe.com/?pid_product=MIKROE-5508) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5508&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of USB to I2C Click board by reading the device ID of a 3D Hall 11 Click board connected to the I2C port and controlling the GPIO pins.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UARTtoI2C

### Example Key Functions

- `uarttoi2c_cfg_setup` Config Object Initialization function.
```c
void uarttoi2c_cfg_setup ( uarttoi2c_cfg_t *cfg );
```

- `uarttoi2c_init` Initialization function.
```c
err_t uarttoi2c_init ( uarttoi2c_t *ctx, uarttoi2c_cfg_t *cfg );
```

- `uarttoi2c_default_cfg` Click Default Configuration function.
```c
err_t uarttoi2c_default_cfg ( uarttoi2c_t *ctx );
```

- `uarttoi2c_gpio_write` This function writes a desired data to the gpio port.
```c
void uarttoi2c_gpio_write ( uarttoi2c_t *ctx, uint8_t gpio_data );
```

- `uarttoi2c_gpio_read` This function reads data from the gpio port.
```c
err_t uarttoi2c_gpio_read ( uarttoi2c_t *ctx, uint8_t *gpio_data );
```

- `uarttoi2c_i2c_write_then_read` This function performs a write then read with a repeated start to the I2C target device.
```c
err_t uarttoi2c_i2c_write_then_read ( uarttoi2c_t *ctx, uint8_t slave_addr, uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len );
```

### Application Init

> Initializes the driver and performs the Click default config which resets the device and sets the GPIO pins 0-3 as push-pull output and others as input.
After that, reads and displays the chip firmware version.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uarttoi2c_cfg_t uarttoi2c_cfg;  /**< Click config object. */

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
    uarttoi2c_cfg_setup( &uarttoi2c_cfg );
    UARTTOI2C_MAP_MIKROBUS( uarttoi2c_cfg, MIKROBUS_1 );
    if ( UART_ERROR == uarttoi2c_init( &uarttoi2c, &uarttoi2c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UARTTOI2C_ERROR == uarttoi2c_default_cfg ( &uarttoi2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t version[ 16 ] = { 0 };
    if ( UARTTOI2C_OK == uarttoi2c_read_version ( &uarttoi2c, version ) )
    {
        log_printf( &logger, " Firmware version: %s\r\n", version );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the device ID of a 3D Hall 11 Click board connected to the I2C port, toggles the output pins and displays the GPIO port state.
The results will be displayed on the USB UART approximately once per second.

```c
void application_task ( void )
{
    static uint8_t gpio_state = UARTTOI2C_NO_PIN_MASK;
    uint8_t slave_address = DEVICE_SLAVE_ADDRESS;
    uint8_t reg_addr = DEVICE_REG_ID;
    uint8_t device_id;
    if ( UARTTOI2C_OK == uarttoi2c_i2c_write_then_read ( &uarttoi2c, slave_address, 
                                                         &reg_addr, 1, &device_id, 1 ) )
    {
        log_printf( &logger, " %s - Device ID read: %s\r\n", ( char * ) DEVICE_NAME,
                    ( char * ) ( ( DEVICE_ID == device_id ) ? "Success" : "Fail" ) );
    }
    uarttoi2c_gpio_write ( &uarttoi2c, gpio_state );
    if ( UARTTOI2C_OK == uarttoi2c_gpio_read ( &uarttoi2c, &gpio_state ) )
    {
        log_printf( &logger, " GPIO state: 0x%.2X\r\n\n", ( uint16_t ) gpio_state );
        gpio_state = ~gpio_state;
    }
    Delay_ms ( 1000 );
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
