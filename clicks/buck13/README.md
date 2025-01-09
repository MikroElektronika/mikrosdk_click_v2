
---
# Buck 13 Click

> [Buck 13 Click](https://www.mikroe.com/?pid_product=MIKROE-3651) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3651&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example switches the output of the Buck13 and logs the output voltage on the Vout terminal.
 
### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck13

### Example Key Functions

- `buck13_cfg_setup` Config Object Initialization function. 
```c
void buck13_cfg_setup ( buck13_cfg_t *cfg );
``` 
 
- `buck13_init` Initialization function. 
```c
err_t buck13_init ( buck13_t *ctx, buck13_cfg_t *cfg );
```

- `buck13_default_cfg` Click Default Configuration function. 
```c
void buck13_default_cfg ( buck13_t *ctx );
```

- `buck13_enable` Enables the Buck 13 output. 
```c
void buck13_enable ( buck13_t *ctx, uint8_t pwr_state );
```
 
- `buck13_get_adc` Gets the ADC values from the module. 
```c
uint16_t buck13_get_adc ( buck13_t *ctx );
```

- `buck13_get_voltage` Gets the output voltage. 
```c
uint16_t buck13_get_voltage ( buck13_t *ctx );
```

### Application Init

> Initializes driver and turns OFF the Buck 13 output as default state.
 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck13_cfg_t cfg;

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

    buck13_cfg_setup( &cfg );
    BUCK13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck13_default_cfg ( &buck13 );
    buck13_init( &buck13, &cfg );
    log_info( &logger, "Buck 13 is enabled now" );
}
```

### Application Task

> Displays the output voltage every 2 seconds.

```c
void application_task ( void )
{
    //  Task implementation.

    buck13_enable( &buck13, BUCK13_ENABLE ); 
    out_voltage = buck13_get_voltage( &buck13 );
    log_printf( &logger, "Vout =  %d mV\r\n", out_voltage );
    
    Delay_ms ( 1000 );
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
