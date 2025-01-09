
---
# 3D Hall 6 Click

> [3D Hall 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3764) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3764&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application measure the intensity of the magnetic field across three perpendicular axes.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3dHall6

### Example Key Functions

- `c3dhall6_cfg_setup` Config Object Initialization function.
```c
void c3dhall6_cfg_setup ( c3dhall6_cfg_t *cfg ); 
```

- `c3dhall6_init` Initialization function.
```c
err_t c3dhall6_init ( c3dhall6_t *ctx, c3dhall6_cfg_t *cfg );
```

- `c3dhall6_set_reference_values` This function sets reference values for voltage and angle calculations.
```c
void c3dhall6_set_reference_values ( c3dhall6_t *ctx, c3dhall6_aux_ref_t ref_val );
```

- `c3dhall6_get_adc_value` This function reads ADC value on selected channel.
```c
void c3dhall6_get_adc_value ( c3dhall6_t *ctx, uint8_t channel_no, uint16_t *adc_value );
```

- `c3dhall6_get_volt` This function reads ADC value on selected channel and converts that value to Volts or miliVolts - depending on reference voltage setting.
```c
void c3dhall6_get_volt( c3dhall6_t *ctx, uint8_t channel_no, float *channel_voltage );
```

### Application Init

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall6_cfg_t cfg;

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
    c3dhall6_cfg_setup( &cfg );
    C3DHALL6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall6_init( &c3dhall6, &cfg );

    c3dhall6_aux_ref_t ref_val = 
    {
        .aux_ref_adc_ch0 = 2048.0,
        .aux_ref_adc_ch1 = 2048.0,
        .aux_ref_adc_ch2 = 2048.0,
        .aux_ref_adc_ch3 = 2048.0,
        .aux_ref_volt = 3.3
    };
    c3dhall6_set_reference_values( &c3dhall6, ref_val );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Executes one or more 'c3dhall6_log_xxx_task' functions
> Additional Functions :
>
> - c3dhall6_log_adc_task() - performs and logs adc measurements on all channels
> - c3dhall6_log_volt_task() - performs and logs voltage measurements on all channels
> - c3dhall6_log_angleRad_task() - performs and logs angle measurements in radians on each die
> - c3dhall6_log_angleDeg_task() - performs and logs angle measurements in degrees on each die 

```c
void application_task ( void )
{
    c3dhall6_log_angle_deg_task( );
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
