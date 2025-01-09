
---
# Altitude 2 Click

> [Altitude 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3030) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3030&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Altitude 2 Click to measure temperature, altitude and pressure.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Altitude2

### Example Key Functions

- `altitude2_cfg_setup` Config Object Initialization function.
```c
void altitude2_cfg_setup ( altitude2_cfg_t *cfg );
```

- `altitude2_init` Initialization function.
```c
err_t altitude2_init ( altitude2_t *ctx, altitude2_cfg_t *cfg );
```

- `altitude2_read_prom` This function reads calibration data from PROM.
```c
uint8_t altitude2_read_prom ( altitude2_t *ctx, uint8_t select_data, uint16_t *data_out );
```
 
- `altitude2_reset` This function resets the device and reads calibration coefficients after reset.
```c
void altitude2_reset( altitude2_t *ctx );
```

- `altitude2_read_data` Data read function.
```c
void altitude2_read_data( altitude2_t *ctx, float *temp_data, float *press_data, float *altitude_data );
```

### Application Init

> Initializes I2C driver and performs the device reset,
> after which the calibration coefficients be read.
> Determines the ratio value for temperature and pressure measurements.
> Calibration coefficients are necessary to read after the device reset.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    altitude2_cfg_t cfg;

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

    altitude2_cfg_setup( &cfg );
    ALTITUDE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    altitude2_init( &altitude2, &cfg );
    Delay_ms ( 500 );
    altitude2_reset( &altitude2 );
    
    altitude2_set_ratio ( &altitude2, ALTITUDE2_RATIO_2048, ALTITUDE2_RATIO_2048 );
    log_printf( &logger, "Altitude 2 is initialized\r\n" );
    Delay_ms ( 200 );
}
```

### Application Task

> Gets temperature data in celsius value and pressure data in mbar value.
> Gets the calculated altitude value in meters which depends on the temperature and pressure measurements.
> Logs results on USBUART and repeats operation each second.

```c
void application_task ( void )
{
    altitude2_read_data( &altitude2, &temperature, &pressure, &altitude );

    log_printf( &logger, "Temperature: %.2f Celsius\r\n", temperature );
    log_printf( &logger, "Pressure: %.2f mbar\r\n", pressure );
    log_printf( &logger, "Altitude: %.2f m\r\n", altitude );
    log_printf( &logger, "---------------------------------------\r\n\r\n" );

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
