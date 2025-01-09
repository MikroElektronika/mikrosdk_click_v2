
---
# Brushless 18 Click

> [Brushless 18 Click](https://www.mikroe.com/?pid_product=MIKROE-6395) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6395&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of the Brushless 18 Click board by driving the motor in both directions at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless18

### Example Key Functions

- `brushless18_cfg_setup` Config Object Initialization function.
```c
void brushless18_cfg_setup ( brushless18_cfg_t *cfg );
```

- `brushless18_init` Initialization function.
```c
err_t brushless18_init ( brushless18_t *ctx, brushless18_cfg_t *cfg );
```

- `brushless18_throttle_calib` This function performs the ESC throttle calibration.
```c
err_t brushless18_throttle_calib ( brushless18_t *ctx );
```

- `brushless18_drive_motor` This function drives the motor at the selected speed and direction.
```c
err_t brushless18_drive_motor ( brushless18_t *ctx, uint8_t direction, uint8_t speed );
```

### Application Init

> Initializes the driver and calibrates the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless18_cfg_t brushless18_cfg;  /**< Click config object. */

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
    brushless18_cfg_setup( &brushless18_cfg );
    BRUSHLESS18_MAP_MIKROBUS( brushless18_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless18_init( &brushless18, &brushless18_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS18_ERROR == brushless18_throttle_calib ( &brushless18 ) )
    {
        log_error( &logger, " Throttle calibration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the motor speed every 500 milliseconds with steps of 5%. At the minimal speed, the motor switches direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static uint8_t direction = BRUSHLESS18_DIRECTION_CW;
    static int8_t speed = BRUSHLESS18_SPEED_MIN;
    static int8_t speed_step = 5;
    brushless18_drive_motor ( &brushless18, direction, speed );
    log_printf( &logger, " Direction: %s\r\n", 
                ( char * ) ( BRUSHLESS18_DIRECTION_CW == direction ? "CW" : "CCW" ) );
    log_printf( &logger, " Speed: %u%%\r\n\n", ( uint16_t ) speed );
    Delay_ms ( 500 );
    
    speed += speed_step;
    if ( speed > BRUSHLESS18_SPEED_MAX )
    {
        speed_step = -speed_step;
        speed += speed_step;
        speed += speed_step;
    }
    else if ( speed < BRUSHLESS18_SPEED_MIN )
    {
        speed_step = -speed_step;
        speed += speed_step;
        direction ^= 1;
        Delay_ms ( 1000 );
    }
}
```

### Note

> The theoretical maximal PWM Clock frequency for this Click board is 500 Hz.
The default PWM Clock frequency is set to 400 Hz. To achieve such a low frequency,
the user will probably need to decrease the MCU's main clock frequency in the Setup MCU Settings.

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
