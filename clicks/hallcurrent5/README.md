
---
# Hall Current 5 Click

> [Hall Current 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3393) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3393&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type

# Software Support

## Example Description

> The demo application reads ADC value and current value.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent5

### Example Key Functions

- `hallcurrent5_cfg_setup` Config Object Initialization function. 
```c
void hallcurrent5_cfg_setup ( hallcurrent5_cfg_t *cfg );
``` 
 
- `hallcurrent5_init` Initialization function. 
```c
err_t hallcurrent5_init ( hallcurrent5_t *ctx, hallcurrent5_cfg_t *cfg );
```

- `hallcurrent5_default_cfg` Click Default Configuration function. 
```c
void hallcurrent5_default_cfg ( hallcurrent5_t *ctx );
```

- `hallcurrent5_set_adc_resolution` This function sets ADC resolution. 
```c
void hallcurrent5_set_adc_resolution ( hallcurrent5_t *ctx, float adc_res );
```
 
- `hallcurrent5_get_adc_voltage` This function gets ADC voltage. 
```c
float hallcurrent5_get_adc_voltage ( hallcurrent5_t *ctx, uint16_t adc_value );
```

- `hallcurrent5_get_current` This function gets ADC current value. 
```c
float hallcurrent5_get_current ( hallcurrent5_t *ctx, uint16_t adc_value );
```

### Application Init

> Initialization device and ADC Init.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent5_cfg_t cfg;

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

    hallcurrent5_cfg_setup( &cfg );
    HALLCURRENT5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent5_init( &hallcurrent5, &cfg );

    // CLICK INIT
    hallcurrent5_set_adc_resolution( &hallcurrent5, HALLCURRENT5_ADC_RESOLUTION_12bit );
    hallcurrent5_set_init_voltage( &hallcurrent5, 316 );
    Delay_100ms();
}
```

### Application Task

> Reads current value in mA and this data logs to USBUART every 500ms. 

```c
void application_task ( void )
{
    hallcurrent5_data_t tmp;
    int16_t adc_value;
    uint32_t sum_adc = 0;
    uint8_t cnt;
    float current;
  
    //  Task implementation.
    
    tmp = hallcurrent5_generic_read( &hallcurrent5 );
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    Delay_ms ( 1000 );

    sum_adc = 0;
    for(cnt = 0; cnt < 20; cnt++)
    {
        sum_adc += hallcurrent5_generic_read( &hallcurrent5 );
    }
    adc_value = ( sum_adc / 20 );

    current = hallcurrent5_get_current( &hallcurrent5, adc_value/1.8 );

    if ( current < 0 ) 
    {
        current = 0;
    }

    log_printf( &logger, " ADC value: %d \r\n", adc_value);
    log_printf( &logger, " Current : \r\n", adc_value);

    Delay_ms ( 500 );
}
```

### Note

> Before the start of the program you have to set the starting voltage on AN pin.
> First, measure the voltage in mV on AN pin, when electronic load isn't >  connected to the Click board, 
>  and pass that value as an input parameter of the voltage initialization function. 
 
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
