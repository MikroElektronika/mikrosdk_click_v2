
---
# Magneto 9 Click

> [Magneto 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4778) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4778&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of Magneto 9 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto9

### Example Key Functions

- `magneto9_cfg_setup` Config Object Initialization function.
```c
void magneto9_cfg_setup ( magneto9_cfg_t *cfg );
```

- `magneto9_init` Initialization function.
```c
err_t magneto9_init ( magneto9_t *ctx, magneto9_cfg_t *cfg );
```

- `magneto9_read_adc_voltage` This function reads raw 12-bit ADC data and converts it to voltage by using I2C serial interface.
```c
err_t magneto9_read_adc_voltage ( magneto9_t *ctx, float *voltage );
```

- `magneto9_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t magneto9_read_an_pin_voltage ( magneto9_t *ctx, float *data_out );
```

- `magneto9_get_pwm_pin` This function returns the PWM pin logic state.
```c
uint8_t magneto9_get_pwm_pin ( magneto9_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    magneto9_cfg_t magneto9_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    magneto9_cfg_setup( &magneto9_cfg );
    MAGNETO9_MAP_MIKROBUS( magneto9_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == magneto9_init( &magneto9, &magneto9_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the ADC voltage and calculates the magnetic field strength from it.
> Voltage increases with increasing positive (south) applied magnetic field.
> All data are being displayed on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    float voltage = 0;
    
    if ( MAGNETO9_OK == magneto9_read_an_pin_voltage ( &magneto9, &voltage ) )
    {
        float field_strength = MAGNETO9_VOLTAGE_TO_FIELD_STRENGTH ( voltage );
        log_printf( &logger, " ADC Voltage : %.3f V\r\n", voltage );
        log_printf( &logger, " Magnetic field strength : %.3f mT\r\n", field_strength );
        if ( field_strength < 0 )
        {
            log_printf( &logger, " The North Pole magnetic field prevails.\r\n\n" );
        }
        else
        {
            log_printf( &logger, " The South Pole magnetic field prevails.\r\n\n" );
        }
    }
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
