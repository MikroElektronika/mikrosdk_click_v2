
---
# MIC 2 Click

> [MIC 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3445) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3445&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : ADC type

# Software Support

## Example Description

> This range is suited for audio and/or speech applications.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic2

### Example Key Functions

- `mic2_cfg_setup` Config Object Initialization function.
```c
void mic2_cfg_setup ( mic2_cfg_t *cfg ); 
```

- `mic2_init` Initialization function.
```c
err_t mic2_init ( mic2_t *ctx, mic2_cfg_t *cfg );
```

- `mic2_set_potentiometer` This function set the value of digital potentiometer.
```c
void mic2_set_potentiometer ( mic2_t *ctx, uint8_t ptt_value );
```

- `mic2_read_an_pin_value` This function reads results of AD conversion of the AN pin.
```c
err_t mic2_read_an_pin_value ( mic2_t *ctx, uint16_t *data_out );
```

- `mic2_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t mic2_read_an_pin_voltage ( mic2_t *ctx, float *data_out );
```

### Application Init

> Initializes the driver and logger and sets the digital potentiometer.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mic2_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    mic2_cfg_setup( &cfg );
    MIC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic2_init( &mic2, &cfg );

    mic2_set_potentiometer( &mic2, 35 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the AN pin voltage and displays the results on the USB UART every 100ms.

```c
void application_task ( void )
{
    float voltage = 0;
    if ( MIC2_OK == mic2_read_an_pin_voltage ( &mic2, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", voltage );
        Delay_ms ( 100 );
    }
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
