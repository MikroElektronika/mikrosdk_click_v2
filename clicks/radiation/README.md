
---
# Radiation Click

> [Radiation Click](https://www.mikroe.com/?pid_product=MIKROE-4036) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4036&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Sep 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Radiation Click board by counting the pulses
that the BG51 sensor generates for each detected radiation event and converting
the average count rate to the radiation dose rate.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Radiation

### Example Key Functions

- `radiation_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void radiation_cfg_setup ( radiation_cfg_t *cfg );
```

- `radiation_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t radiation_init ( radiation_t *ctx, radiation_cfg_t *cfg );
```

- `radiation_int_pin_read` This function reads the logic state of the INT pin.
```c
uint8_t radiation_int_pin_read ( radiation_t *ctx );
```

- `radiation_count_pulses` This function counts the sensor output pulses during the selected measurement window.
```c
err_t radiation_count_pulses ( radiation_t *ctx, uint32_t window_ms, uint32_t *pulse_cnt );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    radiation_cfg_t radiation_cfg;  /**< Click config object. */

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
    radiation_cfg_setup( &radiation_cfg );
    RADIATION_MAP_MIKROBUS( radiation_cfg, MIKROBUS_POSITION_RADIATION );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == radiation_init( &radiation, &radiation_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Counts the sensor pulses in consecutive one-minute windows and displays the number of
pulses in the last window, as well as the average count rate [CPM] and dose rate [uSv/h]
calculated from all windows since the start, on the USB UART.

```c
void application_task ( void ) 
{
    uint32_t pulse_cnt = 0;
    float avg_cpm = 0;

    if ( RADIATION_OK == radiation_count_pulses( &radiation, RADIATION_ONE_MINUTE_MS, &pulse_cnt ) )
    {
        total_pulses += pulse_cnt;
        minute_cnt++;
        avg_cpm = ( float ) total_pulses / minute_cnt;

        log_printf( &logger, " Minute: %lu\r\n", minute_cnt );
        log_printf( &logger, " Last minute: %lu CPM -> %.2f uSv/h\r\n", pulse_cnt, ( float ) pulse_cnt / RADIATION_CPM_PER_USV_H );                    
        log_printf( &logger, " Average: %.2f CPM -> %.2f uSv/h\r\n", avg_cpm, avg_cpm / RADIATION_CPM_PER_USV_H );                    
        log_printf( &logger, "--------------------------------\r\n" );
    }
}
```

### Note

> The dose rate is calculated from the BG51 sensitivity of 5 CPM for 1 uSv/h (+/-15%),
(BG51 datasheet, page 2).

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
