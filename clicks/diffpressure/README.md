
---
# Diff pressure Click

> [Diff pressure Click](https://www.mikroe.com/?pid_product=MIKROE-2387) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2387&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application is temperature compensated and calibrated pressure sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Diffpressure

### Example Key Functions

- `diffpressure_cfg_setup` Config Object Initialization function.
```c
void diffpressure_cfg_setup ( diffpressure_cfg_t *cfg ); 
```

- `diffpressure_init` Initialization function.
```c
err_t diffpressure_init ( diffpressure_t *ctx, diffpressure_cfg_t *cfg );
```

- `diffpressure_read_adc_voltage` This function read ADC voltage value from Diff Pressure Click.
```c
float diffpressure_read_adc_voltage ( diffpressure_t *ctx );
```

- `diffpressure_get_pa_difference` This function get pressure difference [Pa].
```c
int32_t diffpressure_get_pa_difference ( diffpressure_t *ctx, float adc_voltage );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    diffpressure_cfg_t cfg;

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
    diffpressure_cfg_setup( &cfg );
    DIFFPRESSURE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( DIFFPRESSURE_OK != diffpressure_init( &diffpressure, &cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This is an example which demonstrates the use of Diff Pressure Click board.
The example reads the values of ADC module (MPC3551) 22-bit register value
converted to voltage and the pressure difference [ Pa ] and displays
those values on the USB UART.

```c
void application_task ( void )
{
    float adc_voltage = 0;
    int32_t difference = 0;

    adc_voltage = diffpressure_read_adc_voltage( &diffpressure );
    difference = diffpressure_get_pa_difference( &diffpressure, adc_voltage );

    log_printf( &logger, " ADC Voltage: %.3f [V]\r\n", adc_voltage );

    log_printf( &logger, " Pressure Diff: %ld [Pa]\r\n\n", difference );

    Delay_ms ( 100 );
}
```## Application Output

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
