
---
# I2C Repeater Click

> [I2C Repeater Click](https://www.mikroe.com/?pid_product=MIKROE-6785) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6785&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the communication through the I2C Repeater Click board.
It initializes the device, sets the slave I2C address of an external I2C sensor (e.g. 6DOF IMU 11 Click),
and reads its device ID register, verifying if the expected ID is returned.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CRepeater

### Example Key Functions

- `i2crepeater_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void i2crepeater_cfg_setup ( i2crepeater_cfg_t *cfg );
```

- `i2crepeater_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t i2crepeater_init ( i2crepeater_t *ctx, i2crepeater_cfg_t *cfg );
```

- `i2crepeater_enable_device` This function enables the device by setting the EN pin to high logic state.
```c
void i2crepeater_enable_device ( i2crepeater_t *ctx );
```

- `i2crepeater_set_i2c_address` This function sets the slave address for I2C communication.
```c
err_t i2crepeater_set_i2c_address ( i2crepeater_t *ctx, uint8_t slave_addr );
```

- `i2crepeater_i2c_read_reg` This function reads data from a specific register of the I2C slave.
```c
err_t i2crepeater_i2c_read_reg ( i2crepeater_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

### Application Init

> Initializes the logger and the I2C Repeater Click, then enables the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2crepeater_cfg_t i2crepeater_cfg;  /**< Click config object. */

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
    i2crepeater_cfg_setup( &i2crepeater_cfg );
    I2CREPEATER_MAP_MIKROBUS( i2crepeater_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2crepeater_init( &i2crepeater, &i2crepeater_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    i2crepeater_enable_device ( &i2crepeater );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sets the I2C address of a connected I2C sensor and reads its device ID, then logs whether the returned ID matches the expected value.

```c
void application_task ( void )
{
    uint8_t device_id = 0;
    if ( I2CREPEATER_OK == i2crepeater_set_i2c_address ( &i2crepeater, DEVICE_SLAVE_ADDRESS ) )
    {
        if ( I2CREPEATER_OK == i2crepeater_i2c_read_reg ( &i2crepeater, DEVICE_REG_ID, &device_id, 1 ) )
        {
            log_printf( &logger, " %s - Device ID: 0x%.2X - %s\r\n\n", 
                        ( char * ) DEVICE_NAME, ( uint16_t ) device_id, 
                        ( char * ) ( ( DEVICE_ID == device_id ) ? "OK" : "NOK" ) );
        }
        Delay_ms ( 1000 );
    }
}
```

### Note

> Make sure to provide the power supply to VCCB side for the connected I2C sensor. 

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
