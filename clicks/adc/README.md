
---
# ADC Click

> [ADC Click](https://www.mikroe.com/?pid_product=MIKROE-922) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-922&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : SPI type

# Software Support

## Example Description

>
> This example demonstrates the use of ADC Click board.
> The all channels can be configured as single-ended or pseudo-differential pair.
>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc

### Example Key Functions

- `adc_cfg_setup` Configuration Object Setup function. 
```c
void adc_cfg_setup ( adc_cfg_t *cfg );
```
 
- `adc_init` Click Initialization function. 
```c
adc_err_t adc_init ( adc_t *ctx, adc_cfg_t *cfg );
```

- `adc_get_single_ended_ch` Get Single-Ended Channel function. 
```c
uint16_t adc_get_single_ended_ch ( adc_t *ctx, adc_ch_t channel );
```
 
- `adc_get_differential_ch` Get Pseudo-Differential Pair function. 
```c
uint16_t adc_get_differential_ch ( adc_t *ctx, adc_ch_t channel );
```

### Application Init

>
> Initializes SPI driver, performs the reference voltage selection and
> initializes UART console for results logging.
>

```c
void application_init( void )
{
    log_cfg_t log_cfg;
    adc_cfg_t cfg;

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

    adc_cfg_setup( &cfg );
    ADC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc_init( &adc, &cfg );
}
```

### Application Task

>
> Reads voltage level of channels 0 and 1 in the both configurations,
> single-ended and pseudo-differential pair, every 1 second.
> All channels results will be calculated to millivolts [mV].
>

```c
void application_task( void )
{
    adc_get_single_ended_ch( &adc, ADC_CH0_OR_CH01 );
    adc_get_single_ended_ch( &adc, ADC_CH1_OR_CH10 );
    adc_get_single_ended_ch( &adc, ADC_CH2_OR_CH23 );
    adc_get_single_ended_ch( &adc, ADC_CH3_OR_CH32 );
    adc_get_differential_ch( &adc, ADC_CH0_OR_CH01 );

    log_printf( &logger, "* CH0 = %u mV\r\n", adc.ch0 );
    log_printf( &logger, "* CH1 = %u mV\r\n", adc.ch1 );
    log_printf( &logger, "* CH2 = %u mV\r\n", adc.ch2 );
    log_printf( &logger, "* CH3 = %u mV\r\n", adc.ch3 );
    log_printf( &logger, "* CH0 - CH1 = %d mV\r\n", adc.ch01 );
    log_printf( &logger, "-----------------------------\r\n" );

    Delay_ms ( 1000 );
}
```

### Note

>
> In single-ended mode the all channels must be in the range from Vss (GND)
> to Vref (3V3 by default).
> In pseudo-differential mode the IN- channel must be in the range from
> (Vss - 100mV) to (Vss + 100mV). The IN+ channel must be in the range from
> IN- to (Vref + IN-).
> If any of conditions are not fullfilled, the device will return 0 or Vref
> voltage level, and measurements are not valid.

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
