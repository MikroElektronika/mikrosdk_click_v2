
---
# ADC 9 Click

> [ADC 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4105) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4105&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This Click is 8th channel analog to digital converter expansion board, usefull for projects 
> where we have demand for multi channel ADC conversion such as microcontrollers with small 
> number or none analog inputs. It offers integrated features, such as internal oscillator, 
> temperature sensor and burnout sensor detection, in order to reduce system component count 
> and total solution cost. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc9

### Example Key Functions

- `adc9_cfg_setup` Config Object Initialization function. 
```c
void adc9_cfg_setup ( adc9_cfg_t *cfg );
``` 
 
- `adc9_init` Initialization function. 
```c
err_t adc9_init ( adc9_t *ctx, adc9_cfg_t *cfg );
```

- `adc9_default_cfg` Click Default Configuration function. 
```c
void adc9_default_cfg ( adc9_t *ctx, adc9_rw_t *rw );
```

- `adc9_irq_pin_state` Function is used to check if an interrupt has occured. 
```c
uint8_t adc9_irq_pin_state ( adc9_t *ctx );
```
 
- `adc9_read_def_adc` Function is used to read ADC value when the default fata format is applied. 
```c
uint8_t adc9_read_def_adc ( adc9_t *ctx, adc9_rw_t *rw, int32_t *rd_data );
```

- `adc9_volt_calc` Function is used to calculate voltage based on ADC values. 
```c
float adc9_volt_calc ( adc9_t *ctx, int32_t adc_val, uint16_t v_ref, uint8_t gain );
```

### Application Init

> Initalizes SPI driver, resets and starts the device, and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    adc9_cfg_t cfg;

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

    adc9_cfg_setup( &cfg );
    ADC9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uint8_t err_flag = adc9_init( &adc9, &cfg );
    if ( ADC9_INIT_ERROR == err_flag )
    {
        log_info( &logger, "---- Error Init ----" );
        for ( ; ; );
    }

    adc9_default_cfg( &adc9, &adc9_rw );
    
    Delay_ms ( 1000 );
}
```

### Application Task

> This is an example that shows the capabilities of the ADC 9 Click by calculating voltage level 
> based on ADC from channels 0(positive) and 1(negative), and logs the result. 

```c
void application_task ( void )
{
    measurement_init( &adc9, &adc9_rw );
    
    while ( adc9_irq_pin_state( &adc9 ) );
    
    adc9_rw.reg = ADC9_DEVICE_ADR;
    adc9_read_def_adc ( &adc9, &adc9_rw, &adc_value );

    log_printf( &logger, "ADC Value : %ld\r\n" , adc_value );
    
    m_volts = adc9_volt_calc ( &adc9, adc_value, VREF, 1 );
    log_printf( &logger, "Voltage in milivolts : %.2f\r\n", m_volts );

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Note

> Depending on the VOLT SEL jumper position on the Click board the user needs to set VREF macro value (mV) in the code.

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
