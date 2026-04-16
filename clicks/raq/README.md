
---
# RAQ Click

> [RAQ Click](https://www.mikroe.com/?pid_product=MIKROE-4385) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4385&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Feb 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of RAQ Click board (ZMOD4450) in continuous measurement mode.
The device is initialized, basic sensor information (PID, CONF and production data) is read and
logged, then the sensor is calibrated/initialized to obtain MOX_LR and MOX_ER parameters.
After that, the continuous measurement sequence is configured and started, and the calculated
RMOX value is periodically read and logged to the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RAQ

### Example Key Functions

- `raq_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void raq_cfg_setup ( raq_cfg_t *cfg );
```

- `raq_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t raq_init ( raq_t *ctx, raq_cfg_t *cfg );
```

- `raq_hw_reset` This function toggles the RST pin (active-low) to reset the sensor.
```c
void raq_sw_reset ( raq_t *ctx );
```

- `raq_get_sensor_info` This function reads basic sensor identification and factory data (PID, CONF, PROD_DATA).
```c
err_t raq_get_sensor_info ( raq_t *ctx, raq_info_t *info );
```

- `raq_init_sensor` This function runs the sensor init sequence (CMD=0x80), then reads MOX_LR/MOX_ER sensor specific parameters (0x97..0x9A).
```c
err_t raq_init_sensor ( raq_t *ctx, uint16_t *mox_lr, uint16_t *mox_er );
```

- `raq_cont_run` This function waits for a new sample (last sequence step) and reads RMOX.
```c
err_t raq_cont_run ( raq_t *ctx, float *r_mox );
```

### Application Init

> Initializes the driver and performs a hardware reset. Reads and logs the sensor PID, CONF and
production data. Runs the initialization flow (HSPF calculation + INIT command) to obtain
MOX_LR and MOX_ER calibration parameters, then configures and starts the continuous measurement
sequencer.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    raq_cfg_t raq_cfg;          /**< Click config object. */

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
    raq_cfg_setup( &raq_cfg );
    RAQ_MAP_MIKROBUS( raq_cfg, MIKROBUS_POSITION_RAQ );
    if ( I2C_MASTER_ERROR == raq_init( &raq, &raq_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    /* HW reset */
    raq_hw_reset( &raq );
    
    /* Read basic sensor info */
    raq_info_t info;
    if ( RAQ_OK != raq_get_sensor_info( &raq, &info ) )
    {
        log_error( &logger, " Sensor info read failed." );
        for ( ; ; );
    }

    log_printf( &logger, " PID: 0x%.4X\r\n", info.pid );
  
    /* init sensor -> get MOX_LR / MOX_ER */
    uint16_t mox_lr = 0, mox_er = 0;
    err_t ret = raq_init_sensor( &raq, &mox_lr, &mox_er );

    if ( RAQ_OK != ret )
    {
        log_error( &logger, " Sensor calib/init failed (code=%ld).", ret );
        for ( ; ; );
    }

    log_printf( &logger, " MOX_LR: 0x%.4X  MOX_ER: 0x%.4X\r\n", mox_lr, mox_er );

    /* continuous mode init sequence */
    ret = raq_init_measurement( &raq );
    if ( RAQ_OK != ret )
    {
        log_error( &logger, " Init measurement failed (code=%ld).", ret );
        for ( ; ; );
    }

    ret = raq_cont_init( &raq );
    if ( RAQ_OK != ret )
    {
        log_error( &logger, " Continuous init failed (code=%ld).", ret );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Polls the sensor sequencer, reads the latest ADC sample and computes the RMOX value using the
cached MOX_LR/MOX_ER parameters. The resulting RMOX value is logged to the terminal.

```c
void application_task ( void )
{
    float rmox = 0;
    err_t ret = raq_cont_run( &raq, &rmox );

    if ( RAQ_OK == ret )
    {
        log_printf( &logger, "RMOX: %.3f\r\n", rmox );
    }
    else
    {
        log_printf( &logger, "Error: %ld\r\n", ret );
    }

    Delay_100ms( );
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
