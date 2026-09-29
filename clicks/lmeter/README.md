
---
# L meter Click

> [L meter Click](https://www.mikroe.com/?pid_product=MIKROE-3505) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3505&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Sep 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the L meter Click board by measuring the
inductance of an external coil. The inductance is calculated from the ratio of
the edge count measured with the input shorted and the edge count measured

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Lmeter

### Example Key Functions

- `lmeter_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void lmeter_cfg_setup ( lmeter_cfg_t *cfg );
```

- `lmeter_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t lmeter_init ( lmeter_t *ctx, lmeter_cfg_t *cfg );
```

- `lmeter_set_cal_cap` This function connects or disconnects the on-board calibration capacitor C2.
```c
void lmeter_set_cal_cap ( lmeter_t *ctx, uint8_t state );
```

- `lmeter_measure_counts` This function counts the rising edges of the oscillator output signal.
```c
err_t lmeter_measure_counts ( lmeter_t *ctx, uint32_t *count );
```

- `lmeter_calibrate` This function measures and stores the zero reference count.
```c
err_t lmeter_calibrate ( lmeter_t *ctx );
```

- `lmeter_get_inductance` This function calculates the inductance of the connected coil in microhenries.
```c
err_t lmeter_get_inductance ( lmeter_t *ctx, float *inductance );
```

### Application Init

> Initializes the driver and takes the zero reference with the 
measurement input shorted and checks that the oscillator
responds to the on-board calibration capacitor C2.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lmeter_cfg_t lmeter_cfg;  /**< Click config object. */

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
    lmeter_cfg_setup( &lmeter_cfg );
    LMETER_MAP_MIKROBUS( lmeter_cfg, MIKROBUS_POSITION_LMETER );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == lmeter_init( &lmeter, &lmeter_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint32_t cap_on_count = 0;
    uint16_t cnt = 0;

    /* L1 on-board coil measurement as a reference */
    log_printf( &logger, " Short the measurement input for zero calibration.\r\n" );
    log_printf( &logger, " Calibration starts in %u seconds.\r\n\n", ( uint16_t ) CALIBRATION_WAIT_S );
    for ( cnt = 0; CALIBRATION_WAIT_S > cnt; cnt++ )
    {
        Delay_ms( 1000 );
    }
    if ( LMETER_ERROR == lmeter_calibrate( &lmeter ) )
    {
        log_error( &logger, " Calibration." );
        for ( ; ; );
    }
    log_printf( &logger, " Zero reference : %lu counts\r\n", lmeter.zero_count );

    /* Add the on-board C2 to the LC tank to see if it changes the counts as intended */
    lmeter_set_cal_cap( &lmeter, LMETER_CAL_CAP_ENABLE );
    if ( LMETER_OK == lmeter_measure_counts( &lmeter, &cap_on_count ) )
    {
        log_printf( &logger, " C2 connected : %lu counts\r\n\n", cap_on_count );
    }
    lmeter_set_cal_cap( &lmeter, LMETER_CAL_CAP_DISABLE );

    /* Measurement start with an external coil connected */
    log_printf( &logger, " Remove the short and connect the coil.\r\n" );
    log_printf( &logger, " Measurement starts in %u seconds.\r\n\n", ( uint16_t ) MEASUREMENT_WAIT_S );
    for ( cnt = 0; MEASUREMENT_WAIT_S > cnt; cnt++ )
    {
        Delay_ms( 1000 );
    }
        
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Measures the inductance of the connected coil and displays the result on the
USB UART once per second.

```c
void application_task ( void ) 
{
    float inductance = 0;

    if ( LMETER_OK == lmeter_get_inductance( &lmeter, &inductance ) )
    {
        log_printf( &logger, " Inductance : %.1f uH\r\n\n", inductance );
    }
    else
    {
        log_error( &logger, " Failed to get inductance" );
    }
    Delay_ms( 1000 );
}
```

### Note

> Short the measurement input ( TB1 terminal, TS2 header or the probe tips )
before the zero calibration and remove the short afterwards.

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
