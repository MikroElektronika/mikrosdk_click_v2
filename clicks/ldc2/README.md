
---
# LDC 2 Click

> [LDC 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4783) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4783&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of LDC 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LDC2

### Example Key Functions

- `ldc2_cfg_setup` Config Object Initialization function.
```c
void ldc2_cfg_setup ( ldc2_cfg_t *cfg );
```

- `ldc2_init` Initialization function.
```c
err_t ldc2_init ( ldc2_t *ctx, ldc2_cfg_t *cfg );
```

- `ldc2_default_cfg` Click Default Configuration function.
```c
err_t ldc2_default_cfg ( ldc2_t *ctx );
```

- `ldc2_measure_resonance_impedance` This function measures the resonance impedance and proximity data.
```c
err_t ldc2_measure_resonance_impedance ( ldc2_t *ctx, uint8_t *prox_data, float *rp_data );
```

- `ldc2_measure_inductance` This function measures the inductance and sensor frequency.
```c
err_t ldc2_measure_inductance ( ldc2_t *ctx, float *freq, float *inductance );
```

- `ldc2_get_sensor_frequency` This function reads and calculates the sensor frequency.
```c
err_t ldc2_get_sensor_frequency ( ldc2_t *ctx, float *freq );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    ldc2_cfg_t ldc2_cfg;    /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ldc2_cfg_setup( &ldc2_cfg );
    LDC2_MAP_MIKROBUS( ldc2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ldc2_init( &ldc2, &ldc2_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( LDC2_ERROR == ldc2_default_cfg ( &ldc2 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Measures the resonance impedance and proximity as well as the inductance and sensor frequency 
> approximately every 200ms and displays all values on the USB UART.

```c
void application_task ( void )
{
    uint8_t prox_data = 0;
    float rp_data = 0;
    float freq = 0;
    float inductance = 0;
    
    if ( LDC2_OK == ldc2_measure_resonance_impedance( &ldc2, &prox_data, &rp_data ) )
    {
        log_printf( &logger, " Proximity: %u\r\n Resonance Impedance: %.3f kOhm\r\n\n", ( uint16_t ) prox_data, rp_data );
    }
    
    if ( LDC2_OK == ldc2_measure_inductance( &ldc2, &freq, &inductance ) )
    {
        log_printf( &logger, " Sensor Frequency: %.3f MHz\r\n Inductance: %.6f uH\r\n\n", freq, inductance );
    }
    
    Delay_ms ( 200 );
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
