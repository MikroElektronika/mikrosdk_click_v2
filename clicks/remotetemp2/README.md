
---
# Remote Temp 2 Click

> [Remote Temp 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6996) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6996&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : May 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Remote Temp 2 Click board by reading
and displaying the temperature measurements from the local sensor and both
remote channel sensors (CH1 and CH2), and monitoring the alert and critical
temperature states.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RemoteTemp2

### Example Key Functions

- `remotetemp2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void remotetemp2_cfg_setup ( remotetemp2_cfg_t *cfg );
```

- `remotetemp2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t remotetemp2_init ( remotetemp2_t *ctx, remotetemp2_cfg_t *cfg );
```

- `remotetemp2_default_cfg` This function executes a default configuration of Remote Temp 2 Click board.
```c
err_t remotetemp2_default_cfg ( remotetemp2_t *ctx );
```

- `remotetemp2_read_local_temp` This function reads the local sensor temperature in degrees Celsius.
```c
err_t remotetemp2_read_local_temp ( remotetemp2_t *ctx, int8_t *temperature );
```

- `remotetemp2_read_temp_ch1` This function reads the remote channel 1 temperature in degrees Celsius.
```c
err_t remotetemp2_read_temp_ch1 ( remotetemp2_t *ctx, float *temperature );
```

- `remotetemp2_read_temp_ch2` This function reads the remote channel 2 temperature in degrees Celsius.
```c
err_t remotetemp2_read_temp_ch2 ( remotetemp2_t *ctx, float *temperature );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    remotetemp2_cfg_t remotetemp2_cfg;  /**< Click config object. */

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
    remotetemp2_cfg_setup( &remotetemp2_cfg );
    REMOTETEMP2_MAP_MIKROBUS( remotetemp2_cfg, MIKROBUS_POSITION_REMOTETEMP2 );
    if ( I2C_MASTER_ERROR == remotetemp2_init( &remotetemp2, &remotetemp2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( REMOTETEMP2_ERROR == remotetemp2_default_cfg ( &remotetemp2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature measurements in degrees Celsius from the local sensor
and both remote channels, and displays the results on the USB UART
approximately once per second. Also monitors and reports the alert and
critical temperature states via the ALR and TCR pins.

```c
void application_task ( void ) 
{
    uint8_t status = 0;
    int8_t local_temp = 0;
    float ch1_temp = 0;
    float ch2_temp = 0;    

    remotetemp2_read_local_temp( &remotetemp2, &local_temp );
    remotetemp2_read_temp_ch1( &remotetemp2, &ch1_temp );
    remotetemp2_read_temp_ch2( &remotetemp2, &ch2_temp );

    log_printf( &logger, " Local temperature      : %d degC \r\n", ( int16_t ) local_temp );
    log_printf( &logger, " Remote CH1 temperature : %.4f degC \r\n", ch1_temp );
    log_printf( &logger, " Remote CH2 temperature : %.4f degC \r\n", ch2_temp );
    log_printf( &logger, " ---------------------------------- \r\n" );

    if ( !remotetemp2_get_alr_pin( &remotetemp2 ) )
    {
        remotetemp2_get_status( &remotetemp2, &status );
        if ( ( REMOTETEMP2_STATUS_THIGH | REMOTETEMP2_STATUS_TLOW ) & status )
        {
            log_printf( &logger, " Alert - remote temperature is above 30 degC \r\n" );
            log_printf( &logger, " ---------------------------------- \r\n" );
        }
    }

    if ( !remotetemp2_get_tcr_pin( &remotetemp2 ) )
    {
        remotetemp2_get_status( &remotetemp2, &status );
        if ( REMOTETEMP2_STATUS_TCRIT & status )
        {
            log_printf( &logger, " Critical alert - temperature is above 30 degC \r\n" );
            log_printf( &logger, " ---------------------------------- \r\n" );
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
