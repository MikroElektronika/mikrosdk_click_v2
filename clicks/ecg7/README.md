
---
# ECG 7 Click

> [ECG 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5214) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5214&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of ECG 7 Click board by reading and displaying the voltage from VOUT BUFF which can be visualized on the SerialPlot application.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ECG7

### Example Key Functions

- `ecg7_cfg_setup` Config Object Initialization function.
```c
void ecg7_cfg_setup ( ecg7_cfg_t *cfg );
```

- `ecg7_init` Initialization function.
```c
err_t ecg7_init ( ecg7_t *ctx, ecg7_cfg_t *cfg );
```

- `ecg7_read_raw_adc` This function reads raw ADC value.
```c
err_t ecg7_read_raw_adc ( ecg7_t *ctx, uint16_t *raw_adc );
```

- `ecg7_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t ecg7_read_voltage ( ecg7_t *ctx, float *voltage );
```

- `ecg7_set_vref` This function sets the voltage reference for ECG 7 Click driver.
```c
err_t ecg7_set_vref ( ecg7_t *ctx, float vref );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ecg7_cfg_t ecg7_cfg;  /**< Click config object. */

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
    ecg7_cfg_setup( &ecg7_cfg );
    ECG7_MAP_MIKROBUS( ecg7_cfg, MIKROBUS_1 );
    err_t init_flag = ecg7_init( &ecg7, &ecg7_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the output voltage and displays it on the USB UART (SerialPlot) every 4ms approximately.

```c
void application_task ( void )
{
    float ecg7_an_voltage = 0;
    if ( ECG7_OK == ecg7_read_voltage ( &ecg7, &ecg7_an_voltage ) ) 
    {
        log_printf( &logger, "%.3f\r\n", ecg7_an_voltage );
        Delay_ms ( 4 );
    }
}
```

### Note

> We recommend using the SerialPlot tool for data visualizing. Please make sure to set up ECG electrodes properly.

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
