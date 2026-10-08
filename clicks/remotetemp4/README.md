
---
# Remote Temp 4 Click

> [Remote Temp 4 Click](https://www.mikroe.com/?pid_product=MIKROE-7095) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7095&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jul 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Remote Temp 4 Click board by reading
and displaying the temperature measurements from the local and remote
channels, and monitoring the ALERT and THERM temperature alarm states.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RemoteTemp4

### Example Key Functions

- `remotetemp4_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void remotetemp4_cfg_setup ( remotetemp4_cfg_t *cfg );
```

- `remotetemp4_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t remotetemp4_init ( remotetemp4_t *ctx, remotetemp4_cfg_t *cfg );
```

- `remotetemp4_default_cfg` This function executes a default configuration of Remote Temp 4 Click board.
```c
err_t remotetemp4_default_cfg ( remotetemp4_t *ctx );
```

- `remotetemp4_read_local_temp` This function reads the local sensor temperature in degrees Celsius.
```c
err_t remotetemp4_read_local_temp ( remotetemp4_t *ctx, float *temperature );
```

- `remotetemp4_read_remote_temp` This function reads the remote sensor temperature in degrees Celsius.
```c
err_t remotetemp4_read_remote_temp ( remotetemp4_t *ctx, float *temperature );
```

- `remotetemp4_set_thigh_remote` This function sets the remote temperature high ALERT limit.
```c
err_t remotetemp4_set_thigh_remote ( remotetemp4_t *ctx, float max_temperature );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    remotetemp4_cfg_t remotetemp4_cfg;  /**< Click config object. */

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
    remotetemp4_cfg_setup( &remotetemp4_cfg );
    REMOTETEMP4_MAP_MIKROBUS( remotetemp4_cfg, MIKROBUS_POSITION_REMOTETEMP4 );
    if ( I2C_MASTER_ERROR == remotetemp4_init( &remotetemp4, &remotetemp4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( REMOTETEMP4_ERROR == remotetemp4_default_cfg ( &remotetemp4 ) )
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
alarm states.

```c
void application_task ( void ) 
{
    uint8_t status = 0;
    float local_temp = 0;
    float remote_temp = 0;

    remotetemp4_read_local_temp( &remotetemp4, &local_temp );
    remotetemp4_read_remote_temp( &remotetemp4, &remote_temp );

    log_printf( &logger, " Local  temperature : %.3f degC \r\n", local_temp );
    log_printf( &logger, " Remote temperature : %.3f degC \r\n", remote_temp );
    log_printf( &logger, " ------------------------------ \r\n" );

    if ( !remotetemp4_get_alr_pin( &remotetemp4 ) )
    {
        remotetemp4_get_status( &remotetemp4, &status );
        if ( REMOTETEMP4_STATUS_REMOTE_OPEN & status )
        {
            log_printf( &logger, " Fault - remote diode is open or disconnected \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( REMOTETEMP4_STATUS_LOCAL_HIGH & status )
        {
            log_printf( &logger, " Alert - local temperature is above 30 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( REMOTETEMP4_STATUS_REMOTE_HIGH & status )
        {
            log_printf( &logger, " Alert - remote temperature is above 30 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( REMOTETEMP4_STATUS_REMOTE_LOW & status )
        {
            log_printf( &logger, " Alert - remote temperature is below 0 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
    }

    if ( !remotetemp4_get_thm_pin( &remotetemp4 ) )
    {
        remotetemp4_get_status( &remotetemp4, &status );
        if ( REMOTETEMP4_STATUS_LOCAL_THERM & status )
        {
            log_printf( &logger, " THERM - local temperature exceeded 30 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
        }
        if ( REMOTETEMP4_STATUS_REMOTE_THERM & status )
        {
            log_printf( &logger, " THERM - remote temperature exceeded 30 degC \r\n" );
            log_printf( &logger, " ------------------------------ \r\n" );
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
