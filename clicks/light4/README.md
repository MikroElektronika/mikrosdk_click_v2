
---
# Light 4 Click

> [Light 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6105) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6105&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Light 4 Click board by measuring 
  the ambient light level in Lux.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Light4

### Example Key Functions

- `light4_cfg_setup` Config Object Initialization function.
```c
void light4_cfg_setup ( light4_cfg_t *cfg );
```

- `light4_init` Initialization function.
```c
err_t light4_init ( light4_t *ctx, light4_cfg_t *cfg );
```

- `light4_default_cfg` Click Default Configuration function.
```c
err_t light4_default_cfg ( light4_t *ctx );
```

- `light4_write_reg` This function writes a byte into the selected register by using I2C serial interface.
```c
err_t light4_write_reg ( light4_t *ctx, uint8_t reg, uint8_t data_in );
```

- `light4_sw_reset` This function is used to perform software reset of Light 4 Click board.
```c
err_t light4_sw_reset ( light4_t *ctx );
```

- `light4_read_channel_data` This function is used to read data from selected channel of Light 4 Click board.
```c
err_t light4_read_channel_data ( light4_t *ctx, uint8_t channel_sel, float *channel_data );
```

### Application Init

> Initializes the driver, performs the Click default configuration 
  and checking I2C Communication by reading Device ID.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    light4_cfg_t light4_cfg;  /**< Click config object. */

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
    light4_cfg_setup( &light4_cfg );
    LIGHT4_MAP_MIKROBUS( light4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == light4_init( &light4, &light4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHT4_ERROR == light4_default_cfg ( &light4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    uint8_t dev_id = 0;
    light4_read_reg ( &light4, LIGHT4_REG_ID, &dev_id ); 
    if ( LIGHT4_DEVICE_ID == dev_id )
    {
        log_printf( &logger, " Device ID: 0x%.2X \r\n", ( uint16_t ) dev_id );
    }
    else
    {
        log_error( &logger, " Read error." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reading channel 0 ambient light level in lux once per 
  second and displaying it on the UART terminal.

```c
void application_task ( void ) 
{
    float channel_data = 0;
    err_t error_flag;

    error_flag = light4_read_channel_data( &light4, LIGHT4_CHANNEL0_SEL, &channel_data );
    if( LIGHT4_OK == error_flag )
    {
        log_printf( &logger, " Data: %.2f Lux \r\n", channel_data );
    }
    else if ( LIGHT4_ANALOG_SAT == error_flag )
    {
        log_error( &logger, " Analog saturation \r\n" );
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
