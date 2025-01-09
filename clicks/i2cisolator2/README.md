
---
# I2C Isolator 2 Click

> [I2C Isolator 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2609) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2609&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases how to initialize, configure and use the I2C Isolator 2 Click module.
> The Click provides I2C lines and power isolation for slave devices. In order for this 
> example to work, you need the EEPROM 3 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CIsolator2

### Example Key Functions

- `i2cisolator2_cfg_setup` Config Object Initialization function.
```c
void i2cisolator2_cfg_setup ( i2cisolator2_cfg_t *cfg ); 
```

- `i2cisolator2_init` Initialization function.
```c
err_t i2cisolator2_init ( i2cisolator2_t *ctx, i2cisolator2_cfg_t *cfg );
```

- `i2cisolator2_enable_power` This function sets PDIS pin state.
```c
void i2cisolator2_enable_power ( i2cisolator2_t *ctx, uint8_t state );
```

- `i2cisolator2_write` This function writes a desired data to I2C bus.
```c
err_t i2cisolator2_write ( i2cisolator2_t *ctx, uint8_t *data_in, uint16_t len );
```

- `i2cisolator2_read` This function reads a desired number of data bytes from I2C bus.
```c
err_t i2cisolator2_read ( i2cisolator2_t *ctx, uint8_t *data_out, uint16_t len );
```

- `i2cisolator2_set_slave_address` This function sets the slave address.
```c
err_t i2cisolator2_set_slave_address ( i2cisolator2_t *ctx, uint8_t slave_addr );
```

### Application Init

> Initializes the driver and enables the power output.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cisolator2_cfg_t cfg;

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
    i2cisolator2_cfg_setup( &cfg );
    I2CISOLATOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cisolator2_init( &i2cisolator2, &cfg );
    
    i2cisolator2_enable_power( &i2cisolator2, I2CISOLATOR2_POWER_ENABLE );
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes the desired message to EEPROM 3 Click board and reads it back every 2 seconds.
> All data is being displayed on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    uint8_t read_buf[ 100 ] = { 0 };
    if ( I2CISOLATOR2_OK == eeprom3_write_page ( EEPROM3_MEMORY_ADDRESS, EEPROM3_DEMO_TEXT, 
                                                 strlen( EEPROM3_DEMO_TEXT ) ) )
    {
        log_printf( &logger, " Demo text message is written to EEPROM 3 Click!\r\n" );
    }
    Delay_ms ( 1000 );
    
    if ( I2CISOLATOR2_OK == eeprom3_read_page ( EEPROM3_MEMORY_ADDRESS, read_buf, 
                                                strlen( EEPROM3_DEMO_TEXT ) ) )
    {
        read_buf[ strlen( EEPROM3_DEMO_TEXT ) ] = 0;
        log_printf( &logger, " Read data: \"%s\"\r\n\n", read_buf );
    }
    Delay_ms ( 1000 );
}

``` 

### Note

> Make sure to provide the VCC power supply on VCC pin and EEPROM 3 Click.

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
