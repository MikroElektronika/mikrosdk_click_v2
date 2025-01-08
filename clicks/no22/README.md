
---
# NO2 2 Click

> [NO2 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3700) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3700&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> 
> Measure the level of NO2
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NO22

### Example Key Functions

- `no22_cfg_setup` Config Object Initialization function. 
```c
void no22_cfg_setup ( no22_cfg_t *cfg );
``` 
 
- `no22_init` Initialization function. 
```c
err_t no22_init ( no22_t *ctx, no22_cfg_t *cfg );
```

- `no22_default_cfg` Click Default Configuration function. 
```c
void no22_default_cfg ( no22_t *ctx );
```

- `no22_read_data` Function for reading ADC data. 
```c
uint16_t no22_read_data ( no22_t *ctx );
```
 
- `no22_get_ppb` Function for reading ppb data. 
```c
float no22_get_ppb ( no22_t *ctx );
```

- `no22_set_pht_state` Function for setting pht pin. 
```c
uint8_t no22_set_pht_state ( no22_t *ctx, uint8_t state );
```

### Application Init

>
> Driver init
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    no22_cfg_t cfg;
    uint8_t error_data;

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

    
    no22_cfg_setup( &cfg );
    NO22_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    no22_init( &no22, &cfg );

    error_data = no22_set_pht_state( &no22, NO22_PIN_STATE_LOW );

    if ( error_data == NO22_DEVICE_ERROR )
    {
        log_printf( &logger, "Device error \r\n" );
        for ( ; ; );
    }

    log_printf( &logger, "***** App init ***** \r\n" );
}
```

### Application Task

>
> Measures in span of 1 seconc ppb of NO2
> 

```c
void application_task ( )
{
    uint16_t temp_data_read;
    float data_ppb;
    
    temp_data_read = no22_read_data( &no22 );
    log_printf( &logger, "ADC: %d \n\r", temp_data_read );
    
    data_ppb = no22_get_ppb( &no22 );
    log_printf( &logger, "PPB: %f \r\n", data_ppb );
    
    log_printf( &logger, "___________________________\r\n" );
    
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
