
---
# Microwave 5 Click

> [Microwave 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5772) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5772&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Microwave 5 Click board&trade; 
> by reading and displaying the results of AD conversion and motion detection.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Microwave5

### Example Key Functions

- `microwave5_cfg_setup` Config Object Initialization function.
```c
void microwave5_cfg_setup ( microwave5_cfg_t *cfg );
```

- `microwave5_init` Initialization function.
```c
err_t microwave5_init ( microwave5_t *ctx, microwave5_cfg_t *cfg );
```

- `microwave5_read_raw_adc` Microwave 5 read raw ADC value function.
```c
err_t microwave5_read_raw_adc ( microwave5_t *ctx, uint16_t *raw_adc );
```

- `microwave5_read_voltage` Microwave 5 read voltage level function.
```c
err_t microwave5_read_voltage ( microwave5_t *ctx, float *voltage );
```

- `microwave5_set_vref` Microwave 5 set vref function.
```c
err_t microwave5_set_vref ( microwave5_t *ctx, float vref );
```

### Application Init

> The initialization of I2C or ADC module and log UART.
> After driver initialization, the app calculates the reference ADC value.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    microwave5_cfg_t microwave5_cfg;  /**< Click config object. */
    
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
    microwave5_cfg_setup( &microwave5_cfg );
    MICROWAVE5_MAP_MIKROBUS( microwave5_cfg, MIKROBUS_1 );
    err_t init_flag = microwave5_init( &microwave5, &microwave5_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Calibrating the sensor...\r\n" );
    log_printf( &logger, " There must be no movement near the sensor!\r\n" );
    log_printf( &logger, "----------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( MICROWAVE5_OK == microwave5_read_voltage( &microwave5, &reference ) )
    {
        log_printf( &logger, " The sensor has been calibrated!\r\n" );
        log_printf( &logger, " Detector AN Voltage : %.3f[V]\r\n", reference );
        log_printf( &logger, "----------------------------------\r\n" );
        Delay_ms ( 100 );
    }
    else
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    log_printf( &logger, "The motion detector unit is ready.\r\n" );
    log_printf( &logger, "----------------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads the ADC results, takes an ADC sample, 
> compares the difference between the taken samples and the ADC reference value, 
> and reports the movement if the difference is higher/lower than the selected threshold value.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( MICROWAVE5_OK == microwave5_read_voltage( &microwave5, &voltage ) )
    {
        if ( ( ( voltage + MICROWAVE5_THRESHOLD ) < reference ) || 
             ( ( voltage - MICROWAVE5_THRESHOLD ) > reference ) )
        {
            if ( MICROWAVE5_FLAG_SET == flag )
            {
                log_printf( &logger, " Motion detected!\r\n" );
                log_printf( &logger, " Detector AN Voltage : %.3f[V]\r\n", voltage );
                log_printf( &logger, "----------------------------------\r\n" );
                flag = MICROWAVE5_FLAG_CLEAR;
                Delay_ms ( 100 );
            }
        }
        else
        {
            flag = MICROWAVE5_FLAG_SET;
        }
    }
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
