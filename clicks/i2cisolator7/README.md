
---
# I2C Isolator 7 Click

> [I2C Isolator 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5943) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5943&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo application shows an example of an I2C Isolator 7 Click 
> wired to the PRESS Click board&trade; for reading device ID (Who am I).
> The library also includes an I2C writing and reading functions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CIsolator7

### Example Key Functions

- `i2cisolator7_cfg_setup` Config Object Initialization function.
```c
void i2cisolator7_cfg_setup ( i2cisolator7_cfg_t *cfg );
```

- `i2cisolator7_init` Initialization function.
```c
err_t i2cisolator7_init ( i2cisolator7_t *ctx, i2cisolator7_cfg_t *cfg );
```

- `i2cisolator7_generic_write` This function shall generate a START signal, followed by len number of writes from data_in.
```c
err_t i2cisolator7_generic_write ( i2cisolator7_t *ctx, uint8_t *data_in, uint8_t len );
```

- `i2cisolator7_generic_read` This function shall generate a START signal, followed by len number of reads from the bus placing the data in data_out.
```c
err_t i2cisolator7_generic_read ( i2cisolator7_t *ctx, uint8_t *data_out, uint8_t len );
```

- `i2cisolator7_write_then_read` This function performs a write operation followed by a read operation on the bus by using I2C serial interface.
```c
err_t i2cisolator7_write_then_read ( i2cisolator7_t *ctx, uint8_t *data_in, uint8_t len_write_data, uint8_t *data_out, uint8_t len_read_data );
```

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the PRESS Click board&trade; slave address.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cisolator7_cfg_t i2cisolator7_cfg;  /**< Click config object. */

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
    i2cisolator7_cfg_setup( &i2cisolator7_cfg );
    I2CISOLATOR7_MAP_MIKROBUS( i2cisolator7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cisolator7_init( &i2cisolator7, &i2cisolator7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( I2CISOLATOR7_ERROR == i2cisolator7_set_slave_address( &i2cisolator7, PRESS_DEVICE_ADDRESS ) )
    {
        log_error( &logger, " Set I2C Slave address ERROR." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the I2C Isolator 7 Click board&trade;.
> Logs device ID values of the PRESS Click board&trade; 
> wired to the I2C Isolator 7 Click board&trade;.

```c
void application_task ( void ) 
{
    uint8_t device_id = 0;
    uint8_t reg = PRESS_REG_WHO_AM_I;
    if ( I2CISOLATOR7_OK == i2cisolator7_write_then_read( &i2cisolator7, &reg, 1, &device_id, 1 ) )
    {
        if ( PRESS_WHO_AM_I == device_id )
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
