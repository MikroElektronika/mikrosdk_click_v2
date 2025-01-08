
---
# Pollution Click

> [Pollution Click](https://www.mikroe.com/?pid_product=MIKROE-2516) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2516&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : ADC type

# Software Support

## Example Description

> 
> Example code reads ADC value and measures quantity of organic gases in the air.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pollution

### Example Key Functions

- `pollution_cfg_setup` Config Object Initialization function. 
```c
void pollution_cfg_setup ( pollution_cfg_t *cfg );
``` 
 
- `pollution_init` Initialization function. 
```c
err_t pollution_init ( pollution_t *ctx, pollution_cfg_t *cfg );
```

- `pollution_default_cfg` Click Default Configuration function. 
```c
void pollution_default_cfg ( pollution_t *ctx );
```

- `pollution_generic_read` This function read ADC data. 
```c
pollution_data_t pollution_generic_read ( pollution_t *ctx );
```
 
- `pollution_measure_load_voltage` This function gets load voltage from read ADC value. 
```c
float pollution_measure_load_voltage ( pollution_t *ctx, uint16_t adc_value );
```

- `pollution_get_corrected_resistance` This function gets the corrected resistance of the sensor. 
```c
float pollution_get_corrected_resistance ( pollution_t *ctx, uint16_t adc_value );
```

### Application Init

>
> Application Init performs Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pollution_cfg_t cfg;

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
    log_printf( &logger, "---------------------------------------------\r\n" );
    log_printf( &logger, "------------  Application  Init ------------\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    pollution_cfg_setup( &cfg );
    POLLUTION_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pollution_init( &pollution, &cfg );
    
    log_printf( &logger, "---------------------------------------------\r\n" );
    log_printf( &logger, "-------------- Pollution Click --------------\r\n" );
    log_printf( &logger, "---------------------------------------------\r\n" );
    Delay_ms ( 1000 );
    
    pollution_default_cfg( &pollution );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "------------ ADC Initializated ------------\r\n" );
    log_printf( &logger, "---------------------------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> This is an example which demonstrates the usage of Pollution Click board.
> Pollution Click reads ADC value, load voltage from ADC value, and reads  
> corrected resistance of the sensor where results are being sent to 
> the UART terminal where you can track changes.
> 

```c
void application_task ( void )
{
    pollution_data_t tmp;
    
    tmp = pollution_generic_read( &pollution );
    log_printf( &logger, " ADC value : %d ppm\r\n\n", tmp );
    Delay_ms ( 1000 );
    
    value_volt = pollution_measure_load_voltage( &pollution, tmp );
    log_printf( &logger, " Load voltage : %0.2f V\r\n\n", value_volt );
    Delay_ms ( 1000 );
    
    value_res = pollution_get_corrected_resistance( &pollution, tmp );
    log_printf( &logger, " Corrected resistance : %0.2f kOhm\r\n\n", value_res );
    log_printf( &logger, "---------------------------------------------\r\n\n" );
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
