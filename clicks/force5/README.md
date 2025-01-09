
---
# Force 5 Click

> [Force 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4305) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4305&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Force 5 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Force5

### Example Key Functions

- `force5_cfg_setup` Config Object Initialization function.
```c
void force5_cfg_setup ( force5_cfg_t *cfg );
```

- `force5_init` Initialization function.
```c
err_t force5_init ( force5_t *ctx, force5_cfg_t *cfg );
```

- `force5_calibration` Calibration the sensor function.
```c
uint8_t force5_calibration ( force5_t *ctx, force5_calibration_t *calib_data );
```

- `force5_get_force` Get force function.
```c
float force5_get_force ( force5_t *ctx, force5_calibration_t calib_data );
```

- `force5_get_temperature` Get temperature function.
```c
float force5_get_temperature ( force5_t *ctx );
```

### Application Init

> Initialization driver enables - I2C, calibration the device, display diagnostic states and temperature.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    force5_cfg_t force5_cfg;  /**< Click config object. */

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
    force5_cfg_setup( &force5_cfg );
    FORCE5_MAP_MIKROBUS( force5_cfg, MIKROBUS_1 );
    err_t init_flag = force5_init( &force5, &force5_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "      Calibration... \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    
    status = force5_calibration( &force5, &calib_data );
    Delay_ms ( 100 );
    
    log_printf( &logger, "      Completed \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    
    log_printf( &logger, "      Diagnostic States: \r\n" );
    if ( status == FORCE5_STATES_NORMAL_OPERATION ) {
        log_printf( &logger, "    Normal Operation \r\n" );
    }
    if ( status == FORCE5_STATES_COMMAND_MODE ) {
        log_printf( &logger, "      Command Mode \r\n" );
    }
    if ( status == FORCE5_STATES_STALE_DATA ) {
        log_printf( &logger, "       Stale Data \r\n" );
    }
    if ( status == FORCE5_STATES_DIAGNOSTIC_CONDITION ) {
        log_printf( &logger, "   Diagnostic Condition \r\n" );
    }
    log_printf( &logger, "-------------------------\r\n" );
    
    temperature = force5_get_temperature( &force5 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    log_printf( &logger, "-------------------------\r\n" );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Force 5 Click board is measuring force ( N ). All data logs write on USB uart changes every 500 milliseconds.

```c
void application_task ( void ) 
{
    force_n = force5_get_force( &force5, calib_data );
    log_printf( &logger, " Force : %.4f N \r\n", force_n );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms ( 500 );
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
