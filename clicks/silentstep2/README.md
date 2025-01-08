
---
# Silent Step 2 Click

> [Silent Step 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5934) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5934&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Silent Step 2 Click board&trade; 
> by driving the motor in both directions for a desired rotation angle.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SilentStep2

### Example Key Functions

- `silentstep2_cfg_setup` Config Object Initialization function.
```c
void silentstep2_cfg_setup ( silentstep2_cfg_t *cfg );
```

- `silentstep2_init` Initialization function.
```c
err_t silentstep2_init ( silentstep2_t *ctx, silentstep2_cfg_t *cfg );
```

- `silentstep2_default_cfg` Click Default Configuration function.
```c
err_t silentstep2_default_cfg ( silentstep2_t *ctx );
```

- `silentstep2_rotate_by_angle` Silent Step 2 rotates the shaft through a desired angle function.
```c
err_t silentstep2_rotate_by_angle ( silentstep2_t *ctx, uint8_t step_speed, float angle, uint16_t res_360 );
```

- `silentstep2_set_direction` Silent Step 2 sets the clockwise or counterclockwise direction movement function.
```c
void silentstep2_set_direction ( silentstep2_t *ctx, uint8_t dir );
```

### Application Init

> The initialization of I2C and SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    silentstep2_cfg_t silentstep2_cfg;  /**< Click config object. */

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
    silentstep2_cfg_setup( &silentstep2_cfg );
    SILENTSTEP2_MAP_MIKROBUS( silentstep2_cfg, MIKROBUS_1 );
    err_t init_flag = silentstep2_init( &silentstep2, &silentstep2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SILENTSTEP2_ERROR == silentstep2_default_cfg ( &silentstep2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The application task represents an example that demonstrates 
> the use of the Silent Step 2 Click board&trade; with which the user can sequentially move the motor. 
> The first part of the sequence executes the clockwise/counterclockwise motor movement 
> for an angle of 90 degrees with a step speed of 50%, 
> all the way to the last sequence of the same movement routine 
> of 360 degree angle with a step speed of 90%. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation :  90 degrees\r\n" );
    log_printf( &logger, " Step speed        :  50 %%\r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_CLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 50, 90, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Counterclockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation :  180 deg\r\n" );
    log_printf( &logger, " Step speed        :  50 %%\r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_COUNTERCLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 50, 180, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 270 deg\r\n" );
    log_printf( &logger, " Step speed        :  50 %% \r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_CLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 50, 270, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Counterclockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 360 deg\r\n" );
    log_printf( &logger, " Step speed        : 90 %%\r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_COUNTERCLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 90, 360, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Clockwise motion\r\n" );
    log_printf( &logger, " Angle of rotation : 360 deg\r\n" );
    log_printf( &logger, " Step speed        : 90 %% \r\n" );
    silentstep2_set_direction( &silentstep2, SILENTSTEP2_DIRECTION_CLOCKWISE );
    if ( SILENTSTEP2_OK == silentstep2_rotate_by_angle( &silentstep2, 90, 360, SILENTSTEP2_STEP_RES_200 ) )
    {
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
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
