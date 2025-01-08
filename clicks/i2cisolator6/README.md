
---
# I2C Isolator 6 Click

> [I2C Isolator 6 Click](https://www.mikroe.com/?pid_product=MIKROE-5603) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5603&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the I2C Isolator 6 Click driver.
> This demo application shows an example of an I2C Isolator 6 Click 
> wired to the Accel 21 Click for reading device ID.
> The library also includes an I2C writing and reading functions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CIsolator6

### Example Key Functions

- `i2cisolator6_cfg_setup` Config Object Initialization function.
```c
void i2cisolator6_cfg_setup ( i2cisolator6_cfg_t *cfg );
```

- `i2cisolator6_init` Initialization function.
```c
err_t i2cisolator6_init ( i2cisolator6_t *ctx, i2cisolator6_cfg_t *cfg );
```

- `i2cisolator6_write` I2C Isolator 6 I2C writing function.
```c
err_t i2cisolator6_write ( i2cisolator6_t *ctx, uint8_t *data_in, uint8_t len );
```

- `i2cisolator6_read` I2C Isolator 6 I2C reading function.
```c
err_t i2cisolator6_read ( i2cisolator6_t *ctx, uint8_t *data_out, uint8_t len );
```

- `i2cisolator6_write_then_read` I2C Isolator 6 I2C write then read function.
```c
err_t i2cisolator6_write_then_read ( i2cisolator6_t *ctx, uint8_t *data_in, uint8_t len_write_data, uint8_t *data_out, uint8_t len_read_data );
```

### Application Init

> The initialization of the I2C module, log UART.
> After the driver init, the app sets Accel 21 Click I2C Slave address.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cisolator6_cfg_t i2cisolator6_cfg;  /**< Click config object. */

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
    i2cisolator6_cfg_setup( &i2cisolator6_cfg );
    I2CISOLATOR6_MAP_MIKROBUS( i2cisolator6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cisolator6_init( &i2cisolator6, &i2cisolator6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( I2CISOLATOR6_ERROR == i2cisolator6_set_slave_address( &i2cisolator6, ACCEL21_DEVICE_ADDRESS_GND ) )
    {
        log_error( &logger, " Set I2C Slave address ERROR." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------\r\n" );
}
```

### Application Task

> This example demonstrates the use of the I2C Isolator 6 Click board&trade;.
> Logs device ID values of the Accel 21 Click 
> wired to the I2C Isolator 6 Click board&trade;.

```c
void application_task ( void ) 
{
    static uint8_t device_id = 0;
    static uint8_t reg = ACCEL21_REG_WHO_AM_I;
    if ( I2CISOLATOR6_OK == i2cisolator6_write_then_read( &i2cisolator6, &reg, 1, &device_id, 1 ) )
    {
        if ( ACCEL21_DEVICE_ID == device_id )
        {
            log_printf( &logger, " Device ID: 0x%.2X\r\n", ( uint16_t ) device_id );
            log_printf( &logger, "---------------------\r\n" );
        }
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
