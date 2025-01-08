
---
# I2C MUX 7 Click

> [I2C MUX 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5069) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5069&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of I2C MUX 7 Click board by reading the
device ID of a 6DOF IMU 11 and Compass 3 Click boards connected to the channels 0 and 7 respectfully.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CMUX7

### Example Key Functions

- `i2cmux7_cfg_setup` Config Object Initialization function.
```c
void i2cmux7_cfg_setup ( i2cmux7_cfg_t *cfg );
```

- `i2cmux7_init` Initialization function.
```c
err_t i2cmux7_init ( i2cmux7_t *ctx, i2cmux7_cfg_t *cfg );
```

- `i2cmux7_default_cfg` Click Default Configuration function.
```c
err_t i2cmux7_default_cfg ( i2cmux7_t *ctx );
```

- `i2cmux7_set_channel` This function sets the desired channel active and configures its slave address.
```c
err_t i2cmux7_set_channel ( i2cmux7_t *ctx, uint8_t ch_sel, uint8_t ch_slave_addr );
```

- `i2cmux7_read_channel` This function reads the currently selected channel value.
```c
err_t i2cmux7_read_channel ( i2cmux7_t *ctx, uint8_t *ch_sel );
```

- `i2cmux7_generic_read` This function reads a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
err_t i2cmux7_generic_read ( i2cmux7_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );
```

### Application Init

> Initializes the driver and resets the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cmux7_cfg_t i2cmux7_cfg;  /**< Click config object. */

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
    i2cmux7_cfg_setup( &i2cmux7_cfg );
    I2CMUX7_MAP_MIKROBUS( i2cmux7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cmux7_init( &i2cmux7, &i2cmux7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    i2cmux7_reset_device ( &i2cmux7 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the device ID of the connected Click boards.
Channel 0 : 6DOF IMU 11 Click [slave address: 0x0E; reg: 0x00; id: 0x2D],
Channel 7 : Compass 3 Click   [slave address: 0x30; reg: 0x2F; id: 0x0C].
All data is being logged on the USB UART where you can check the device ID.

```c
void application_task ( void )
{
    uint8_t channel, device_id;
    if ( I2CMUX7_OK == i2cmux7_set_channel ( &i2cmux7, DEVICE0_POSITION, DEVICE0_SLAVE_ADDRESS ) )
    {
        if ( I2CMUX7_OK == i2cmux7_read_channel ( &i2cmux7, &channel ) )
        {
            log_printf( &logger, " --- Channel %u --- \r\n", ( uint16_t ) ( channel & I2CMUX7_CHANNEL_NUM_MASK ) );
        }
        if ( I2CMUX7_OK == i2cmux7_generic_read ( &i2cmux7, DEVICE0_REG_ID, &device_id, 1 ) )
        {
            log_printf( &logger, " %s - Device ID: 0x%.2X \r\n\n", ( char * ) DEVICE0_NAME, ( uint16_t ) device_id );
        }
        Delay_ms ( 1000 );
    }
    if ( I2CMUX7_OK == i2cmux7_set_channel ( &i2cmux7, DEVICE1_POSITION, DEVICE1_SLAVE_ADDRESS ) )
    {
        if ( I2CMUX7_OK == i2cmux7_read_channel ( &i2cmux7, &channel ) )
        {
            log_printf( &logger, " --- Channel %u --- \r\n", ( uint16_t ) ( channel & I2CMUX7_CHANNEL_NUM_MASK ) );
        }
        if ( I2CMUX7_OK == i2cmux7_generic_read ( &i2cmux7, DEVICE1_REG_ID, &device_id, 1 ) )
        {
            log_printf( &logger, " %s - Device ID: 0x%.2X \r\n\n", ( char * ) DEVICE1_NAME, ( uint16_t ) device_id );
        }
        Delay_ms ( 1000 );
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
