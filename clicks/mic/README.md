
---
# Mic Click

> [Mic Click](https://www.mikroe.com/?pid_product=MIKROE-2563) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2563&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type

# Software Support

## Example Description

> This example showcases the initialization and configuration of the Click and logger modules and later on reads and displays data recorded by the mic.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic

### Example Key Functions

- `mic_cfg_setup` Config Object Initialization function. 
```c
void mic_cfg_setup ( mic_cfg_t *cfg );
``` 
 
- `mic_init` Initialization function. 
```c
err_t mic_init ( mic_t *ctx, mic_cfg_t *cfg );
```

- `mic_default_cfg` Click Default Configuration function. 
```c
void mic_default_cfg ( mic_t *ctx );
```

- `mic_generic_read` This function read ADC data. 
```c
mic_data_t mic_generic_read ( mic_t *ctx );
```

### Application Init

> Initializes LOG communication, ADC and configures AN pin as input on MIKROBUS1.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mic_cfg_t cfg;

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

    mic_cfg_setup( &cfg );
    MIC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic_init( &mic, &cfg );
}
```

### Application Task

> Reads 12 bit ADC data from AN pin and displays it using the logger module. 

```c
void application_task ( void )
{
    mic_data_t tmp;
    
    //  Task implementation.
    
    tmp = mic_generic_read ( &mic );
    
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );

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
