
---
# I2C 1-Wire 2  Click

> [I2C 1-Wire 2  Click](https://www.mikroe.com/?pid_product=MIKROE-6058) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6058&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the I2C 1-Wire 2 Click board
  by searching if a device is connected and reading its ROMID.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2C1Wire2

### Example Key Functions

- `i2c1wire2_cfg_setup` Config Object Initialization function.
```c
void i2c1wire2_cfg_setup ( i2c1wire2_cfg_t *cfg );
```

- `i2c1wire2_init` Initialization function.
```c
err_t i2c1wire2_init ( i2c1wire2_t *ctx, i2c1wire2_cfg_t *cfg );
```

- `i2c1wire2_default_cfg` Click Default Configuration function.
```c
err_t i2c1wire2_default_cfg ( i2c1wire2_t *ctx );
```

- `i2c1wire2_master_reset` This function is used to reset device, and return all configuration registers to the default values.
```c
err_t i2c1wire2_master_reset ( i2c1wire2_t *ctx );
```

- `i2c1wire2_write_port_cfg` This function is used to write a 1-Wire configuration register.
```c
err_t i2c1wire2_write_port_cfg ( i2c1wire2_t *ctx, uint8_t reg, uint8_t *data_in );
```

- `i2c1wire2_search` This function is used to perform 1-Wire Search algorithm and return one device ROMID.
```c
err_t i2c1wire2_search ( i2c1wire2_t *ctx, uint8_t *flag, uint8_t *rom_id, uint8_t *last_flag, uint8_t param_data, uint8_t command_code );
```

### Application Init

> Initialization of I2C module, log UART and perform Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2c1wire2_cfg_t i2c1wire2_cfg;  /**< Click config object. */

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
    i2c1wire2_cfg_setup( &i2c1wire2_cfg );
    I2C1WIRE2_MAP_MIKROBUS( i2c1wire2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2c1wire2_init( &i2c1wire2, &i2c1wire2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( I2C1WIRE2_ERROR == i2c1wire2_default_cfg ( &i2c1wire2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Performing 1-Wire Search algorithm to find if any device is connected.
 If a device is connected and detected, its ROMID will be read and displayed.

```c
void application_task ( void ) 
{
    err_t error_flag;
    uint8_t flag;
    uint8_t last_flag;
    uint8_t rom_id[ 8 ] = { 0 };
    #define I2C1WIRE2_DEVICE_SEARCH_CODE            0xF0

    error_flag = i2c1wire2_search ( &i2c1wire2, &flag, rom_id, &last_flag, I2C1WIRE2_SEARCH_RESET | 
                                    I2C1WIRE2_SEARCH_1WIRE_RESET, I2C1WIRE2_DEVICE_SEARCH_CODE );
    if ( I2C1WIRE2_OK == error_flag )
    {   
        if ( I2C1WIRE2_RESULT_BYTE_OK == flag )
        {
            log_printf( &logger, " Device found: \r\n" );
            log_printf( &logger, " Device ROMID: 0x" );
            for ( uint8_t n_cnt = 0; n_cnt < 8; n_cnt++ )
            {
                log_printf( &logger, "%.2X", ( uint16_t ) rom_id[ n_cnt ] );
            }
            log_printf( &logger, " \r\n" );
            log_printf( &logger, " Last device flag %d \r\n", last_flag );
        }
        else if ( I2C1WIRE2_NO_DEVICE_DETECTED == flag )
        {
            log_printf( &logger, " No device detected \r\n" );
        }
        else if ( I2C1WIRE2_NO_PRESENCE_PULS == flag )
        {
            log_printf( &logger, " No presence puls \r\n" );
        }
    }
    else 
    {
        log_printf( &logger, " ERROR \r\n" );
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
