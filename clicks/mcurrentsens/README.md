
---
# mCurrent Sens Click

> [mCurrent Sens Click](https://www.mikroe.com/?pid_product=MIKROE-6985) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6985&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of mCurrent Sens Click for measuring voltage, current, and temperature on two independent channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.mCurrentSens

### Example Key Functions

- `mcurrentsens_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void mcurrentsens_cfg_setup ( mcurrentsens_cfg_t *cfg );
```

- `mcurrentsens_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t mcurrentsens_init ( mcurrentsens_t *ctx, mcurrentsens_cfg_t *cfg );
```

- `mcurrentsens_default_cfg` This function executes a default configuration of mCurrent Sens Click board.
```c
err_t mcurrentsens_default_cfg ( mcurrentsens_t *ctx );
```

- `mcurrentsens_fetch_calib` This function reads calibration values from external EEPROM.
```c
err_t mcurrentsens_fetch_calib ( mcurrentsens_t *ctx );
```

- `mcurrentsens_read_ch1_current` This function reads channel 1 current measurement in mA.
```c
err_t mcurrentsens_read_ch1_current ( mcurrentsens_t *ctx, float *data_out );
```

- `mcurrentsens_read_ch1_voltage` This function reads channel 1 voltage measurement in mV.
```c
err_t mcurrentsens_read_ch1_voltage ( mcurrentsens_t *ctx, float *data_out );
```

### Application Init

> Initializes communication, configures the device, optionally performs
calibration, and loads calibration data from EEPROM. ADC oversampling
ratio is set for faster runtime measurements.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mcurrentsens_cfg_t mcurrentsens_cfg;  /**< Click config object. */

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
    mcurrentsens_cfg_setup( &mcurrentsens_cfg );
    MCURRENTSENS_MAP_MIKROBUS( mcurrentsens_cfg, MIKROBUS_POSITION_MCURRENTSENS );
    if ( SPI_MASTER_ERROR == mcurrentsens_init( &mcurrentsens, &mcurrentsens_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MCURRENTSENS_ERROR == mcurrentsens_default_cfg ( &mcurrentsens ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

#if ENABLE_CALIBRATION
    if ( MCURRENTSENS_OK == mcurrentsens_calibrate_device ( &mcurrentsens ) )
    {
        log_printf( &logger, " Device calibration success\r\n" );
    }
    else
    {
        log_error( &logger, " Device calibration" );
        for ( ; ; );
    }
#endif

    if ( MCURRENTSENS_OK == mcurrentsens_fetch_calib ( &mcurrentsens ) )
    {
        log_printf( &logger, " Calibration data read from EEPROM\r\n" );
    }
    else
    {
        log_error( &logger, " Calibration fetch - No communication with EEPROM or EEPROM is empty" );
        for ( ; ; );
    }
    
    /* Reduce OSR after calibration for faster runtime measurements. */
    mcurrentsens_set_osr( &mcurrentsens, MCURRENTSENS_CONFIG1_OSR_256 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and logs voltage, current, and temperature values continuously.

```c
void application_task ( void )
{
    float ch1_voltage_mv = 0;
    float ch1_current_ma = 0;
    float ch2_voltage_mv = 0;
    float ch2_current_ma = 0;
    float temperature = 0;

    if ( MCURRENTSENS_OK == mcurrentsens_read_ch1_voltage( &mcurrentsens, &ch1_voltage_mv ) )
    {
        log_printf( &logger, " CH1 voltage : %.1f mV\r\n", ch1_voltage_mv );
    }
    else
    {
        log_printf( &logger, " CH1 voltage read error\r\n" );
    }

    if ( MCURRENTSENS_OK == mcurrentsens_read_ch1_current( &mcurrentsens, &ch1_current_ma ) )
    {
        log_printf( &logger, " CH1 current : %.2f mA\r\n", ch1_current_ma );
    }
    else
    {
        log_printf( &logger, " CH1 current read error\r\n" );
    }

    if ( MCURRENTSENS_OK == mcurrentsens_read_ch2_voltage( &mcurrentsens, &ch2_voltage_mv ) )
    {
        log_printf( &logger, " CH2 voltage : %.1f mV\r\n", ch2_voltage_mv );
    }
    else
    {
        log_printf( &logger, " CH2 voltage read error\r\n" );
    }

    if ( MCURRENTSENS_OK == mcurrentsens_read_ch2_current( &mcurrentsens, &ch2_current_ma ) )
    {
        log_printf( &logger, " CH2 current : %.2f mA\r\n", ch2_current_ma );
    }
    else
    {
        log_printf( &logger, " CH2 current read error\r\n" );
    }

    if ( MCURRENTSENS_OK == mcurrentsens_read_temperature( &mcurrentsens, &temperature ) )
    {
        log_printf( &logger, " Temperature : %.2f degC\r\n", temperature );
    }
    else
    {
        log_printf( &logger, " Temperature read error\r\n" );
    }

    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 1000 );
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
