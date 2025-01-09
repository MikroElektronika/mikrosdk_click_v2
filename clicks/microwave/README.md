
---
# Microwave Click

> [Microwave Click](https://www.mikroe.com/?pid_product=MIKROE-2781) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2781&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : ADC type

# Software Support

## Example Description

> This is an example which demonstrates the use of Microwave Click board.
> Microwave Click reads ADC results, takes exact amount of samples,
> calculation of difference between taken samples and reference ADC value, and
> reports movement if difference is greater/lower than selected threshold value.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Microwave

### Example Key Functions

- `microwave_cfg_setup` Configuration Object Setup function. 
```c
void microwave_cfg_setup ( microwave_cfg_t *cfg );
```
 
- `microwave_init` Click Initialization function. 
```c
microwave_err_t microwave_init ( microwave_t *ctx, microwave_cfg_t *cfg );
```

- `microwave_generic_read` Generic ADC Read function. 
```c
analog_in_data_t microwave_generic_read ( microwave_t *ctx );
```

### Application Init

> Initializes the ADC and uart console where the results will be displayed.
> Also calculates the reference ADC value for Microwave Click board.

```c
void application_init( void )
{
    microwave_cfg_t cfg;
    log_cfg_t log_cfg;

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
    microwave_cfg_setup( &cfg );
    MICROWAVE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    microwave_init( &microwave, &cfg );
    Delay_ms ( 100 );

    log_printf( &logger, " Calibrating the sensor...\r\n" );
    log_printf( &logger, " There must be no movement near the sensor!\r\n" );
    log_printf( &logger, "*********************************************\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    sum = 0;

    for ( uint8_t cnt = 0; cnt < MICROWAVE_SAMPLES_COUNT_100; cnt++ )
    {
        sum += microwave_generic_read( &microwave );
    }

    reference = sum / MICROWAVE_SAMPLES_COUNT_100;

    log_printf( &logger, " The sensor has been calibrated!\r\n" );
    log_printf( &logger, "** Reference value: %d\r\n", reference );
    log_printf( &logger, "*********************************************\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads the AD converted results and compares this results with the previously
> calculated reference value, taking into account the choosen threshold value
> which controls the sensor sensitivity. All data is being displayed on the
> USB UART where you can track their changes.

```c
void application_task( void )
{
    microwave_data_t adc_sample;
    uint16_t detector;
    uint8_t sampler;
    uint8_t cnt = 0;

    sum = 0;

    for ( sampler = 0; sampler < MICROWAVE_SAMPLES_COUNT_100; sampler++ )
    {
        adc_sample = microwave_generic_read( &microwave );
        sum += adc_sample;
        cnt++;
    }

    if ( cnt )
    {
        detector = sum / cnt;

        if ( ( ( detector + MICROWAVE_THRESHOLD_10 ) < reference || 
               ( detector - MICROWAVE_THRESHOLD_10 ) > reference ) && 
                 old_detector != detector )
        {
            log_printf( &logger, "** MOVE DETECTED!\r\n" );
            log_printf( &logger, "** Detector value : %d\r\n", detector );
            log_printf( &logger, "**************************\r\n" );
            old_detector = detector;
            Delay_ms ( 100 );
        }
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
