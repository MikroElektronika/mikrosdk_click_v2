
---
# PIR Click

> [PIR Click](https://www.mikroe.com/?pid_product=MIKROE-3339) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3339&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application which generates a voltage when exposed to infrared radiation.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pir

### Example Key Functions

- `pir_cfg_setup` Config Object Initialization function. 
```c
void pir_cfg_setup ( pir_cfg_t *cfg );
``` 
 
- `pir_init` Initialization function. 
```c
err_t pir_init ( pir_t *ctx, pir_cfg_t *cfg );
```

- `pir_get_adc` Reading 12bit ADC value. 
```c
uint16_t pir_get_adc ( pir_t *ctx );
```
 
- `pir_reg_read` Reading register. 
```c
uint16_t pir_reg_read ( pir_t *ctx );
```

- `pir_get_mili_volt` Reading ADC data in mili Volts. 
```c
float pir_get_mili_volt ( pir_t *ctx, uint16_t ref_voltage );
```

### Application Init

> Initializes device. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pir_cfg_t cfg;

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

    pir_cfg_setup( &cfg );
    PIR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pir_init( &pir, &cfg );
}
```

### Application Task

> Reads ADC data, converts it to miliVolts and logs scaled value in miliVolts. 

```c
void application_task ( void )
{
    uint16_t adc_val;
    float map_out;

    adc_val = pir_get_adc( &pir );
    map_out = pir_scale_results( &pir, adc_val, 0, 3303 );
    
    log_printf( &logger, " Voltage: %.2f\r\n", map_out);
   
    log_printf( &logger, " miliVolts \r\n" );
    Delay_ms ( 100 );
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
