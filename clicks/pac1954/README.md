
---
# PAC1954 Click

> [PAC1954 Click](https://www.mikroe.com/?pid_product=MIKROE-4291) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4291&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of PAC1954 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PAC1954

### Example Key Functions

- `pac1954_cfg_setup` Config Object Initialization function.
```c
void pac1954_cfg_setup ( pac1954_cfg_t *cfg );
```

- `pac1954_init` Initialization function.
```c
err_t pac1954_init ( pac1954_t *ctx, pac1954_cfg_t *cfg );
```

- `pac1954_default_cfg` Click Default Configuration function.
```c
err_t pac1954_default_cfg ( pac1954_t *ctx );
```

- `pac1954_refresh_cmd` This function updates the readable registers for the VBUS, VSENSE, Power, accumulator outputs and accumulator count by issuing the REFRESH command. The values will be static until the next REFRESH command.
```c
err_t pac1954_refresh_cmd ( pac1954_t *ctx );
```

- `pac1954_get_calc_measurement` This function calls the function for getting the selected measurement data and performs all the necessary calculations to get the measurement value in standard unit.
```c
err_t pac1954_get_calc_measurement ( pac1954_t *ctx, uint8_t meas_sel, uint8_t ch_sel, uint8_t avg_sel, uint8_t meas_mode, float *data_out );
```

- `pac1954_generic_write` This function writes a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
err_t pac1954_generic_write ( pac1954_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    pac1954_cfg_t pac1954_cfg;  /**< Click config object. */

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
    pac1954_cfg_setup( &pac1954_cfg );
    PAC1954_MAP_MIKROBUS( pac1954_cfg, MIKROBUS_1 );
    err_t init_flag = pac1954_init( &pac1954, &pac1954_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    pac1954_default_cfg ( &pac1954 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the voltage, current, and power from Channel 1 and displays all 
> values on the USB UART once per second.

```c
void application_task ( void )
{
    float vsource = 0;
    float isense = 0;
    float power = 0;

    pac1954_refresh_cmd ( &pac1954 );
    
    pac1954_get_calc_measurement ( &pac1954, PAC1954_MEAS_SEL_V_SOURCE, 
                                             PAC1954_CH_SEL_CH_1, 
                                             PAC1954_AVG_SEL_ENABLE, 
                                             PAC1954_MEAS_MODE_BIPOLAR_FSR,
                                             &vsource );
    pac1954_get_calc_measurement ( &pac1954, PAC1954_MEAS_SEL_I_SENSE, 
                                             PAC1954_CH_SEL_CH_1, 
                                             PAC1954_AVG_SEL_ENABLE, 
                                             PAC1954_MEAS_MODE_BIPOLAR_FSR, 
                                             &isense );
    pac1954_get_calc_measurement ( &pac1954, PAC1954_MEAS_SEL_P_SENSE, 
                                             PAC1954_CH_SEL_CH_1, 
                                             0, 
                                             PAC1954_MEAS_MODE_BIPOLAR_FSR, 
                                             &power );
    
    log_printf( &logger, " Voltage: %.3f V\r\n", vsource );
    log_printf( &logger, " Current: %.3f A\r\n", isense );
    log_printf( &logger, " Power: %.3f W\r\n", power );
    log_printf( &logger, "---------------------------\r\n" );
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
