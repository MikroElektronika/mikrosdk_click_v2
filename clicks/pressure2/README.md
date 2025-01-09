
---
# Pressure 2 Click

> [Pressure 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1880) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1880&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application measures pressure in range from 0 to 14 bars (with a resolution of up to 0.2 mbars),
but because of the stainless steel cap enclosure, the sensor can withstand up to 30 bars of pressure.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure2

### Example Key Functions

- `pressure2_cfg_setup` Config Object Initialization function.
```c
void pressure2_cfg_setup ( pressure2_cfg_t *cfg ); 
```

- `pressure2_init` Initialization function.
```c
err_t pressure2_init ( pressure2_t *ctx, pressure2_cfg_t *cfg );
```

- `pressure2_default_cfg` Click Default Configuration function.
```c
err_t pressure2_default_cfg ( pressure2_t *ctx );
```

- `pressure2_read_coefficient` This function read calibration coefficients and return coefficient.
```c
uint16_t pressure2_read_coefficient ( pressure2_t *ctx, uint8_t index );
```

- `pressure2_send_cmd_adc` This function preforms ADC conversion and return 24bit result.
```c
uint32_t pressure2_send_cmd_adc ( pressure2_t *ctx, uint8_t cmd );
```

- `pressure2_read_sensor` Functions for readding sensor.
```c
void pressure2_read_sensor ( pressure2_t *ctx, float *press, float *temp );
```

### Application Init

> Initializes driver init and chip init.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure2_cfg_t pressure2_cfg;

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
    pressure2_cfg_setup( &pressure2_cfg );
    PRESSURE2_MAP_MIKROBUS( pressure2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == pressure2_init( &pressure2, &pressure2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE2_ERROR == pressure2_default_cfg ( &pressure2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads sensor and logs to USB UART pressure and temperature every second. 

```c
void application_task ( void )
{
    pressure2_read_sensor( &pressure2, &pressure, &temperature );
    
    log_printf( &logger," Pressure: %.2f mBar\r\n", pressure );
    log_printf( &logger," Temperature: %.2f degC\r\n\n", temperature );

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
