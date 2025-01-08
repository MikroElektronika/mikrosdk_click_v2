
---
# Force Click

> [Force Click](https://www.mikroe.com/?pid_product=MIKROE-2065) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2065&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type

# Software Support

## Example Description

> This example showcases how to initialize and configure the logger and Click modules and 
  read and display ADC voltage data read from the analog pin.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Force

### Example Key Functions

- `force_cfg_setup` Config Object Initialization function. 
```c
void force_cfg_setup ( force_cfg_t *cfg );
``` 
 
- `force_init` Initialization function. 
```c
err_t force_init ( force_t *ctx, force_cfg_t *cfg );
```

- `force_default_cfg` Click Default Configuration function. 
```c
void force_default_cfg ( force_t *ctx );
```

- `force_generic_read` This function reads ADC data. 
```c
force_data_t force_generic_read ( force_t *ctx );
```
 
- `force_get_resistance` This function calculates resistance data based on the ADC input. 
```c
float force_get_resistance ( uint32_t adc_value );
```

- `` This function calculates the correction factor based on temperature and humidity data. 
```c
force_get_correction_factor  ( float temperature, float humidity );
```

### Application Init

> This function initializes and configures the logger and Click modules. 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    force_cfg_t cfg;

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

    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "    Force  Click    \r\n" );
    log_printf( &logger, "--------------------\r\n\r\n" );

    //  Click initialization.

    force_cfg_setup( &cfg );
    FORCE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force_init( &force, &cfg );
}
```

### Application Task

> This function reads and displays ADC voltage data from the analog pin every second. 

```c
void application_task ( )
{
    force_data_t tmp;
    
    //  Task implementation.
    
    tmp = force_generic_read ( &force );
    log_printf( &logger, " * ADC value : %d \r\n", tmp );
    log_printf( &logger, "--------------------- \r\n" );
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
