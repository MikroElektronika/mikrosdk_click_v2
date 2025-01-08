
---
# Magnetic Rotary Click

> [Magnetic Rotary Click](https://www.mikroe.com/?pid_product=MIKROE-3275) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3275&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example reads a magnetic field angle calculated to degrees for channel A
> The angle can be measured in the range from -90 to 90 degrees.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MagneticRotary

### Example Key Functions

- `magneticrotary_cfg_setup` Config Object Initialization function. 
```c
void magneticrotary_cfg_setup ( magneticrotary_cfg_t *cfg );
``` 
 
- `magneticrotary_init` Initialization function. 
```c
err_t magneticrotary_init ( magneticrotary_t *ctx, magneticrotary_cfg_t *cfg );
```

- `magneticrotary_default_cfg` Click Default Configuration function. 
```c
void magneticrotary_default_cfg ( magneticrotary_t *ctx );
```

- `magnrotary_read_adc` This function returns a 12bit result of AD conversion. 
```c
uint16_t magnrotary_read_adc ( magneticrotary_t *ctx, uint8_t cmnd_byte );
```
 
- `magnrotary_out_volt_adc` This function returns ADC voltage value calculated to millivolts, depending on the voltage selection. 
```c
uint16_t magnrotary_out_volt_adc ( magneticrotary_t *ctx, uint8_t cmd_byte, uint16_t pwr_volt );
```

- `magnrotary_get_field_angle` This function returns a magnetic field angle calculated to degrees,from -90 to 90 degrees. 
```c
double magnrotary_get_field_angle ( magneticrotary_t *ctx, uint8_t cmd_byte );
```

### Application Init

> Initializes peripherals, pins, SPI interface for communication with the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    magneticrotary_cfg_t cfg;

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

    magneticrotary_cfg_setup( &cfg );
    MAGNETICROTARY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneticrotary_init( &magneticrotary, &cfg );
    log_info(&logger, "Magnetic rotary successufully initialized!\r\n");

}
```

### Application Task

> Reads a magnetic field angle calculated to degrees for channel A in Single-Ended Mode and logs results.

```c
void application_task ( void )
{
    //  Task implementation.

    magn_angle = magnrotary_get_field_angle( &magneticrotary, MAGNROTARY_CHA_POS_GND_NEG | 
                                                              MAGNROTARY_MSB_ZEROS_ORDER );

    log_printf( &logger, "Angle:    %.2lf \r\n ", magn_angle );
    
    Delay_ms ( 500 );
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
