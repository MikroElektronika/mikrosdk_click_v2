
---
# ADC 5 Click

> [ADC 5 Click](https://www.mikroe.com/?pid_product=MIKROE-2846) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2846&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases how to initialize and configure the logger and Click modules and 
  how to read and display ADC voltage data from the Click. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC5

### Example Key Functions

- `adc5_cfg_setup` Config Object Initialization function. 
```c
void adc5_cfg_setup ( adc5_cfg_t *cfg );
``` 
 
- `adc5_init` Initialization function. 
```c
err_t adc5_init ( adc5_t *ctx, adc5_cfg_t *cfg );
```

- `adc5_default_cfg` Click Default Configuration function. 
```c
void adc5_default_cfg ( adc5_t *ctx );
```

- `adc5_get_voltage` This function calculates the ADC voltage data. 
```c
uint16_t adc5_get_voltage ( adc5_t *ctx );
```
 
- `adc5_get_data` This function reads the ADC voltage data. 
```c
uint16_t adc5_get_data ( adc5_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules.

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    adc5_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    adc5_cfg_setup( &cfg );
    ADC5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc5_init( &adc5, &cfg );
}
```

### Application Task

> This function reads and displays ADC voltage data every second. 

```c
void application_task ( )
{
    uint16_t adc_value;
    
    adc_value = adc5_get_voltage( &adc5 );
    log_printf( &logger, " * Voltage: %d mV * \r\n", adc_value );
    Delay_1sec( );
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
