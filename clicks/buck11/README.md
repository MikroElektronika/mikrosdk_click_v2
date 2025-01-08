
---
# Buck 11 Click

> [Buck 11 Click](https://www.mikroe.com/?pid_product=MIKROE-3438) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3438&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This aplication control voltage using Buck 11.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck11

### Example Key Functions

- `buck11_cfg_setup` Config Object Initialization function. 
```c
void buck11_cfg_setup ( buck11_cfg_t *cfg );
``` 
 
- `buck11_init` Initialization function. 
```c
err_t buck11_init ( buck11_t *ctx, buck11_cfg_t *cfg );
```

- `buck11_default_cfg` Click Default Configuration function. 
```c
void buck11_default_cfg ( buck11_t *ctx );
```

- `buck11_read_adc` ADC Read function. 
```c
uint16_t buck11_read_adc( buck11_t *ctx );
```
 
- `` Get VOUT function. 
```c
buck11_get_vout  ( buck11_t *ctx, uint8_t vout_resolution );
```

- `buck11_get_averaged_vout` Get Averaged VOUT function. 
```c
float buck11_get_averaged_vout( buck11_t *ctx, uint8_t vout_resolution, uint8_t n_samples );
```

### Application Init

> Initializes I2C serial interface and selects the desired VDD voltage value
> and VOUT value resolution (to get VOUT value in Volts).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck11_cfg_t cfg;

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

    buck11_cfg_setup( &cfg );
    BUCK11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck11_init( &buck11, &cfg );

    Delay_ms ( 500 );
    
    buck11_set_vdd_value( 4.935 );
    vout_resol = BUCK11_VOUT_VOLTS;
    
    log_printf( &logger, "** Buck 11 is initialized ** \r\n" );
    log_printf( &logger, "************************************* \r\n" );
    Delay_ms ( 200 );
}
```

### Application Task

> Reads the averaged VOUT voltage calculated to Volts by performing a 30 conversions
> in one measurement cycle. The measured results will be showed on the uart terminal every 300 milliseconds.

```c
void application_task ( )
{
    float vout_value;
    uint8_t vout_resol;

    vout_value = buck11_get_averaged_vout( &buck11, vout_resol, 30 );

    log_printf( &logger, "VOUT:  \r\n", vout_value );
    
    if (vout_resol == BUCK11_VOUT_VOLTS)
    {
        log_printf( &logger, " V \r\n" );
    }
    else
    {
        log_printf( &logger, " mV \r\n" );
    }
    
    log_printf( &logger, "************************************* \r\n" );
    Delay_ms ( 300 );
}
```

### Note

> The user should measure the VDD voltage value and enter this measured value to the function as VDD value to get
> more accurate measurement. This VDD voltage is used as reference voltage for the AD conversion.
> The input voltage (VIN) range is from 4.2V to 60V.
> The output current (IOUT) value should not be greater than 1.5A.

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
