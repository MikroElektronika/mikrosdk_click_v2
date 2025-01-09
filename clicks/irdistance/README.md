
---
# IR distance Click

> [IR distance Click](https://www.mikroe.com/?pid_product=MIKROE-1991) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1991&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> The Click board outputs an analog voltage corresponding to the distance of the object 
> (through the mikroBUS AN pin). An Enable (EN) pin is also utilized.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrDistance

### Example Key Functions

- `irdistance_cfg_setup` Config Object Initialization function. 
```c
void irdistance_cfg_setup ( irdistance_cfg_t *cfg );
``` 
 
- `irdistance_init` Initialization function. 
```c
err_t irdistance_init ( irdistance_t *ctx, irdistance_cfg_t *cfg );
```

- `irdistance_default_cfg` Click Default Configuration function. 
```c
void irdistance_default_cfg ( irdistance_t *ctx );
```

- `irdistance_enable` Function enable distance measuring sensor by set RST pin on Stretch Click board. 
```c
void irdistance_enable ( irdistance_t *ctx );
```
 
- `irdistance_read_adc` This function reads ADC data using analog_in_read function. 
```c
irdistance_data_t irdistance_read_adc ( irdistance_t *ctx );
```

- `irdistance_get_voltage_out` Function calculate the voltage output of distance measuring sensor on IR Distance Click board. 
```c
float irdistance_get_voltage_out ( uint32_t adc_value, uint16_t resolution_value, float vcc_value );
```

### Application Init

> Initialization driver enables GPIO, enable IR sensor, initialization ADC, also write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    irdistance_cfg_t cfg;

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

    irdistance_cfg_setup( &cfg );
    IRDISTANCE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irdistance_init( &irdistance, &cfg );
    irdistance_default_cfg ( &irdistance );
}
```

### Application Task

> This is an example which demonstrates the use of IR Distance Click board.
> IR Distance Click reads and displays ADC value.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on USB uart change for every 1 sec.
 

```c
void application_task ( void )
{
    adc_val = irdistance_read_adc( &irdistance );
    log_printf( &logger, " ADC value : %u\r\n", adc_val );
    log_printf( &logger, "---------------------\r\n" );
   
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
