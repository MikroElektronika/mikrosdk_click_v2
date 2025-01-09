
---
# DAC Click

> [DAC Click](https://www.mikroe.com/?pid_product=MIKROE-950) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-950&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> 
> This demo example sends digital signal to the outputs 
> and converts it to analog.
>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Dac

### Example Key Functions

- `dac_cfg_setup` Config Object Initialization function. 
```c
void dac_cfg_setup ( dac_cfg_t *cfg );
``` 
 
- `dac_init` Initialization function. 
```c
err_t dac_init ( dac_t *ctx, dac_cfg_t *cfg );
```

- `dac_set_voltage_pct`  This function is used to set output voltage in percents. 
```c
void dac_set_voltage_pct ( dac_t *ctx, uint8_t v_out_pct );
```
 
- `dac_set_voltage` This function is used to set output voltage. 
```c
void dac_set_voltage ( dac_t *ctx, uint16_t v_out );
```

### Application Init

>
> Initializes driver, SPI communication and LOG.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dac_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    dac_cfg_setup( &cfg );
    DAC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac_init( &dac, &cfg );
}
```

### Application Task

>
> Sends different values( form 0 to 4095 with step 1000 ) to output and 
> prints expected measurement.
> 

```c
void application_task ( void )
{
    for ( dac_val = 0; dac_val <= DAC_RESOLUTION; dac_val += DAC_STEP_VALUE )
    {
        dac_set_voltage( &dac, dac_val );
        dac_val *= DAC_CALIB_VAL_1;
        dac_val /= DAC_CALIB_VAL_2;
        log_printf( &logger, " Current DAC Value: %d mV \r\n", dac_val );

        log_printf( &logger, "----------------------------------\r\n" );

        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
