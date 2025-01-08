
---
# 1-Wire I2C Click

> [1-Wire I2C Click](https://www.mikroe.com/?pid_product=MIKROE-2750) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2750&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : One Wire type

# Software Support

## Example Description

> This example demonstrates the use of 1-Wire I2C Click board by reading the temperature measurement from connected Thermo 4 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.1WireI2C

### Example Key Functions

- `c1wirei2c_cfg_setup` Config Object Initialization function.
```c
void c1wirei2c_cfg_setup ( c1wirei2c_cfg_t *cfg );
```

- `c1wirei2c_init` Initialization function.
```c
err_t c1wirei2c_init ( c1wirei2c_t *ctx, c1wirei2c_cfg_t *cfg );
```

- `c1wirei2c_default_cfg` Click Default Configuration function.
```c
err_t c1wirei2c_default_cfg ( c1wirei2c_t *ctx );
```

- `c1wirei2c_reset_device` This function resets the device by toggling the RST pin state.
```c
void c1wirei2c_reset_device ( c1wirei2c_t *ctx );
```

- `c1wirei2c_write_data` This function addresses and writes 1-255 bytes to an I2C slave without completing the transaction with a stop.
```c
err_t c1wirei2c_write_data ( c1wirei2c_t *ctx, uint8_t slave_addr, uint8_t *data_in, uint8_t len );
```

- `c1wirei2c_read_data_stop` This function is used to address and read 1-255 bytes from an I2C slave in one transaction.
```c
err_t c1wirei2c_read_data_stop ( c1wirei2c_t *ctx, uint8_t slave_addr, uint8_t *data_out, uint8_t len );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c1wirei2c_cfg_t c1wirei2c_cfg;  /**< Click config object. */

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
    c1wirei2c_cfg_setup( &c1wirei2c_cfg );
    C1WIREI2C_MAP_MIKROBUS( c1wirei2c_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == c1wirei2c_init( &c1wirei2c, &c1wirei2c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C1WIREI2C_ERROR == c1wirei2c_default_cfg ( &c1wirei2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature measurement from connected Thermo 4 Click board and displays the results on the USB UART once per second.

```c
void application_task ( void )
{
    float temperature = 0;
    uint8_t reg_data[ 2 ] = { 0 };
    uint8_t reg_addr = DEVICE_REG_TEMPERATURE;
    if ( ( C1WIREI2C_OK == c1wirei2c_write_data ( &c1wirei2c, DEVICE_SLAVE_ADDRESS, &reg_addr, 1 ) ) && 
         ( C1WIREI2C_OK == c1wirei2c_read_data_stop ( &c1wirei2c, DEVICE_SLAVE_ADDRESS, reg_data, 2 ) ) )
    {
        temperature = ( ( ( int16_t ) ( ( ( uint16_t ) reg_data[ 0 ] << 8 ) | 
                                                       reg_data[ 1 ] ) ) >> 5 ) * DEVICE_TEMPERATURE_RES;
        log_printf( &logger, "\r\n%s - Temperature: %.3f degC\r\n", ( char * ) DEVICE_NAME, temperature );
    }
    else
    {
        log_error( &logger, "%s - no communication!\r\n", ( char * ) DEVICE_NAME );
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
