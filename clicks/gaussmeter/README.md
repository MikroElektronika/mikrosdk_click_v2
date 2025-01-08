
---
# Gaussmeter Click

> [Gaussmeter Click](https://www.mikroe.com/?pid_product=MIKROE-3099) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3099&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example showcases how to configure and use the Gaussmeter Click. This Click measures
> magnetic fields around the device using a 3 axis measurement system. Alongside the magnetometer,
> the Click contains an integrated temperature sensor which provides data for the thermal compensation.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gaussmeter

### Example Key Functions

- `gaussmeter_cfg_setup` Config Object Initialization function. 
```c
void gaussmeter_cfg_setup ( gaussmeter_cfg_t *cfg );
``` 
 
- `gaussmeter_init` Initialization function. 
```c
err_t gaussmeter_init ( gaussmeter_t *ctx, gaussmeter_cfg_t *cfg );
```

- `gaussmeter_default_cfg` Click Default Configuration function. 
```c
void gaussmeter_default_cfg ( gaussmeter_t *ctx );
```

- `gaussmeter_write_reg` This function writes 16-bit data to the specified register address. 
```c
uint8_t gaussmeter_write_reg ( gaussmeter_t *ctx, uint8_t reg_addr, uint16_t transfer_data );
```
 
- `gaussmeter_get_data` This function reads the temperature and axis data from the chip. 
```c
uint8_t gaussmeter_get_data ( gaussmeter_t *ctx, float *output_data );
```

- `gaussmeter_digital_read_int` This function reads the digital input signal from the INT pin. 
```c
uint8_t gaussmeter_digital_read_int ( gaussmeter_t *ctx );
```

### Application Init

> This function initializes and configures the Click and logger modules. 
> Additional configuring is done in the default_cfg(...) function.

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    gaussmeter_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gaussmeter_cfg_setup( &cfg );
    GAUSSMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gaussmeter_init( &gaussmeter, &cfg );
    Delay_ms ( 100 );
    gaussmeter_default_cfg( &gaussmeter );
    Delay_ms ( 500 );
}
```

### Application Task

> This function reads data from the magnetometer and the temperature sensor and displays that
> data using the UART console every 400 milliseconds.

```c
void application_task ( )
{
    float temp_buf[ 4 ] = { 0 };
    uint8_t error_bit;
    uint8_t axis_check;
    uint8_t cnt;

    error_bit = gaussmeter_get_data( &gaussmeter, temp_buf );

    if ( !error_bit )
    {
        axis_check = 1;
        buf_idx = 0;
    }

    for ( cnt = 0; cnt < 4; cnt++ )
    {
        switch ( gaussmeter.aux.command_byte_low & axis_check )
        {
            case 1:
            {
                log_printf( &logger, " * Temperature: %.2f C\r\n", temp_buf[ buf_idx++ ] );
                break;
            }
            case 2:
            {
                log_printf( &logger, " * X-axis: %.2f microT\r\n", temp_buf[ buf_idx++ ] );
                break;
            }
            case 4:
            {
                log_printf( &logger, " * Y-axis: %.2f microT\r\n", temp_buf[ buf_idx++ ] );
                break;
            }
            case 8:
            {
                log_printf( &logger, " * Z-axis: %.2f microT\r\n", temp_buf[ buf_idx++ ] );
            }
        }
        axis_check <<= 1;
    }
    log_printf( &logger, "----------------------------------\r\n" );
    Delay_ms ( 400 );
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
