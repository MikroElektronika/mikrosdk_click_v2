
---
# C Meter Click

> [C Meter Click](https://www.mikroe.com/?pid_product=MIKROE-2376) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2376&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Sep 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the C Meter Click board by measuring the
capacitance of an external capacitor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CMeter

### Example Key Functions

- `cmeter_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void cmeter_cfg_setup ( cmeter_cfg_t *cfg );
```

- `cmeter_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t cmeter_init ( cmeter_t *ctx, cmeter_cfg_t *cfg );
```

- `cmeter_measure_period` This function measures the average period of the oscillator output signal.
```c
err_t cmeter_measure_period ( cmeter_t *ctx, float *period );
```

- `cmeter_calibrate` This function measures the oscillator period with nothing connected to the measurement input.
```c
err_t cmeter_calibrate ( cmeter_t *ctx );
```

- `cmeter_get_capacitance` This function measures the oscillator period and calculates the capacitance.
```c
err_t cmeter_get_capacitance ( cmeter_t *ctx, float *capacitance );
```

### Application Init

> Initializes the driver, performs the zero calibration with the measurement
input left open.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cmeter_cfg_t cmeter_cfg;  /**< Click config object. */

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
    cmeter_cfg_setup( &cmeter_cfg );
    CMETER_MAP_MIKROBUS( cmeter_cfg, MIKROBUS_POSITION_CMETER );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == cmeter_init( &cmeter, &cmeter_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    uint8_t cnt = 0;

    /* On-board CX measurement as a reference */
    log_printf( &logger, " Leave the measurement input open for zero calibration.\r\n" );
    log_printf( &logger, " Calibration starts in %u seconds.\r\n\n", ( uint16_t ) CALIBRATION_WAIT_S );
    for ( cnt = 0; CALIBRATION_WAIT_S > cnt; cnt++ )
    {
        Delay_ms( 1000 );
    }
    if ( CMETER_ERROR == cmeter_calibrate( &cmeter ) )
    {
        log_error( &logger, " Calibration." );
        for ( ; ; );
    }
    log_printf( &logger, " Zero reference : %.2f loop passes per period\r\n\n", cmeter.zero_period );

    /* Measurement start with an external capacitor connected */
    log_printf( &logger, " Connect the capacitor.\r\n" );
    log_printf( &logger, " Measurement starts in %u seconds.\r\n\n", ( uint16_t ) MEASUREMENT_WAIT_S );
    for ( cnt = 0; MEASUREMENT_WAIT_S > cnt; cnt++ )
    {
        Delay_ms( 1000 );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Measures the capacitance of the connected capacitor and logs the result in nF
on the USB UART once per second.

```c
void application_task ( void ) 
{
    float capacitance = 0;

    if ( CMETER_OK == cmeter_get_capacitance( &cmeter, &capacitance ) )
    {
        log_printf( &logger, " Capacitance : %.3f nF\r\n", capacitance );
    }
    else
    {
        log_printf( &logger, " Measurement failed, check the connected capacitor.\r\n" );
    }
    Delay_ms( 1000 );
}
```

### Note

> Leave the measurement input ( TB1 terminal, J1 socket and the SMD pads ) open
during the zero calibration, and connect the capacitor afterwards.

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
