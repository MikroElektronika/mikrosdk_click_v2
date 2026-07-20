
---
# Temp Alarm 2 Click

> [Temp Alarm 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6947) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6947&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : May 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Temp Alarm 2 Click board by reading
and displaying the temperature measurements from the local sensor and 
the remote channel sensor, and monitoring the ALERT and THERM
temperature alarm states.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempAlarm2

### Example Key Functions

- `tempalarm2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void tempalarm2_cfg_setup ( tempalarm2_cfg_t *cfg );
```

- `tempalarm2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t tempalarm2_init ( tempalarm2_t *ctx, tempalarm2_cfg_t *cfg );
```

- `tempalarm2_default_cfg` This function executes a default configuration of Temp Alarm 2 Click board.
```c
err_t tempalarm2_default_cfg ( tempalarm2_t *ctx );
```

- `tempalarm2_read_local_temp` This function reads the local sensor temperature in degrees Celsius.
```c
err_t tempalarm2_read_local_temp ( tempalarm2_t *ctx, float *temperature );
```

- `tempalarm2_read_remote_temp` This function reads the remote sensor temperature in degrees Celsius.
```c
err_t tempalarm2_read_remote_temp ( tempalarm2_t *ctx, float *temperature );
```

- `tempalarm2_clear_alert` This function performs the SMBus Alert Response Address (ARA) command to reset the ALERT pin.
```c
err_t tempalarm2_clear_alert ( tempalarm2_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tempalarm2_cfg_t tempalarm2_cfg;  /**< Click config object. */

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
    tempalarm2_cfg_setup( &tempalarm2_cfg );
    TEMPALARM2_MAP_MIKROBUS( tempalarm2_cfg, MIKROBUS_POSITION_TEMPALARM2 );
    if ( I2C_MASTER_ERROR == tempalarm2_init( &tempalarm2, &tempalarm2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPALARM2_ERROR == tempalarm2_default_cfg ( &tempalarm2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature measurements in degrees Celsius from both the local
sensor and the remote channel, and displays the results on the USB UART
approximately once per second. Also monitors and reports the ALERT and THERM
alarm states via the ALT pin and the status register.

```c
void application_task ( void ) 
{
    uint8_t status = 0;
    float local_temp = 0;
    float remote_temp = 0;

    tempalarm2_read_local_temp( &tempalarm2, &local_temp );
    tempalarm2_read_remote_temp( &tempalarm2, &remote_temp );

    log_printf( &logger, " Local  temperature : %.4f degC \r\n", local_temp );
    log_printf( &logger, " Remote temperature : %.4f degC \r\n", remote_temp );
    log_printf( &logger, " ------------------------------ \r\n" );
    
    /* Status flags are latched => read the status register in order to update them */
    tempalarm2_get_status( &tempalarm2, &status );

    if ( !tempalarm2_get_alt_pin( &tempalarm2 ) )
    {
        if ( TEMPALARM2_STATUS_LHIGH & status )
        {
            log_printf( &logger, " Alert - local temperature is above 28 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( TEMPALARM2_STATUS_RHIGH & status )
        {
            log_printf( &logger, " Alert - remote temperature is above 28 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( TEMPALARM2_STATUS_LLOW & status )
        {
            log_printf( &logger, " Alert - local temperature is below 0 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( TEMPALARM2_STATUS_RLOW & status )
        {
            log_printf( &logger, " Alert - remote temperature is below 0 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( TEMPALARM2_STATUS_OPEN & status )
        {
            log_printf( &logger, " Alert - remote sensor open circuit detected \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }

        /* Alert pin is also latched.
         * Send Alert Response Address command to reset it only if status flags confirm
         * that the temperature is back under high limit or above low limit =>
         * "Condition for Alert is over but the pin is still latched" */
        if ( !( status & ( TEMPALARM2_STATUS_LHIGH | TEMPALARM2_STATUS_RHIGH | 
                           TEMPALARM2_STATUS_LLOW  | TEMPALARM2_STATUS_RLOW  | 
                           TEMPALARM2_STATUS_OPEN ) ) )
        {
            tempalarm2_clear_alert( &tempalarm2 );
        }
    }

    if ( TEMPALARM2_STATUS_RTHRM & status )
    {
        log_printf( &logger, " THERM - remote temperature exceeded 30 degC \r\n" );
        log_printf( &logger, " ------------------------------ \r\n" );
    }
    if ( TEMPALARM2_STATUS_LTHRM & status )
    {
        log_printf( &logger, " THERM - local temperature exceeded 30 degC \r\n" );
        log_printf( &logger, " ------------------------------ \r\n" );
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
