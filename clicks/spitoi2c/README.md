
---
# SPI to I2C Click

> [SPI to I2C Click](https://www.mikroe.com/?pid_product=MIKROE-6789) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6789&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of SPI to I2C Click board by reading the manufacturer ID
of a 3D Hall 11 Click board connected to the I2C port and controlling the GPIO pins.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SPItoI2C

### Example Key Functions

- `spitoi2c_cfg_setup` Config Object Initialization function.
```c
void spitoi2c_cfg_setup ( spitoi2c_cfg_t *cfg );
```

- `spitoi2c_init` Initialization function.
```c
err_t spitoi2c_init ( spitoi2c_t *ctx, spitoi2c_cfg_t *cfg );
```

- `spitoi2c_default_cfg` Click Default Configuration function.
```c
err_t spitoi2c_default_cfg ( spitoi2c_t *ctx );
```

- `spitoi2c_i2c_read_after_write` This function performs a write then read with a repeated start to the I2C target device.
```c
err_t spitoi2c_i2c_read_after_write ( spitoi2c_t *ctx, uint8_t slave_addr, 
                                      uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len );
```

- `spitoi2c_gpio_write` This function writes a desired data to the gpio port.
```c
err_t spitoi2c_gpio_write ( spitoi2c_t *ctx, uint8_t gpio_data );
```

- `spitoi2c_gpio_read` This function reads data from the gpio port.
```c
err_t spitoi2c_gpio_read ( spitoi2c_t *ctx, uint8_t *gpio_data );
```

### Application Init

> Initializes the driver and performs the Click default config which enables
the device and sets the GPIO pins 0-2 as push-pull output and others as input.
Then sets the I2C clock to 99KHz, I2C address to 127 and disables I2C timeout.
After that, reads and displays the chip firmware version.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spitoi2c_cfg_t spitoi2c_cfg;  /**< Click config object. */

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
    spitoi2c_cfg_setup( &spitoi2c_cfg );
    SPITOI2C_MAP_MIKROBUS( spitoi2c_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == spitoi2c_init( &spitoi2c, &spitoi2c_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SPITOI2C_ERROR == spitoi2c_default_cfg ( &spitoi2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t version[ 16 ] = { 0 };
    if ( SPITOI2C_OK == spitoi2c_read_version ( &spitoi2c, version ) )
    {
        log_printf( &logger, " Firmware version: %s\r\n", version );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the manufacturer ID of a 3D Hall 11 Click board connected to the I2C port, 
toggles the output pins and displays the GPIO port state. The results will
be displayed on the USB UART approximately once per second.

```c
void application_task ( void )
{
    static uint8_t gpio_state = SPITOI2C_NO_PIN_MASK;
    uint8_t reg_addr = DEVICE_REG_MAN_ID;
    uint8_t man_id[ 2 ] = { 0 };
    err_t error_flag = spitoi2c_i2c_read_after_write ( &spitoi2c, DEVICE_SLAVE_ADDRESS, 
                                                       &reg_addr, 1, man_id, 2 );
    log_printf( &logger, " %s - ID read: %s\r\n", ( char * ) DEVICE_NAME,
                ( char * ) ( ( ( DEVICE_MAN_ID_0 == man_id[ 0 ] ) && 
                               ( DEVICE_MAN_ID_1 == man_id[ 1 ] ) && 
                               ( SPITOI2C_OK == error_flag ) ) ? "Success" : "Fail" ) );
    if ( ( SPITOI2C_OK == spitoi2c_gpio_write ( &spitoi2c, gpio_state ) ) && 
         ( SPITOI2C_OK == spitoi2c_gpio_read ( &spitoi2c, &gpio_state ) ) )
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
