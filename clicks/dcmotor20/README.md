
---
# DC Motor 20 Click

> [DC Motor 20 Click](https://www.mikroe.com/?pid_product=MIKROE-4884) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4884&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of DC Motor 20 Click board by driving the motors in both direction in the span of 14 seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor20

### Example Key Functions

- `dcmotor20_cfg_setup` Config Object Initialization function.
```c
void dcmotor20_cfg_setup ( dcmotor20_cfg_t *cfg );
```

- `dcmotor20_init` Initialization function.
```c
err_t dcmotor20_init ( dcmotor20_t *ctx, dcmotor20_cfg_t *cfg );
```

- `dcmotor20_drive_motor` This function drives the motor for a certian time specified by time_ms at the desired speed. 
```c
err_t dcmotor20_drive_motor ( dcmotor20_t *ctx, uint8_t speed, uint32_t time_ms );
```

- `dcmotor20_set_channel_mode` This function sets the active channel and mode which will be used by the dcmotor20_drive_motor function.
```c
err_t dcmotor20_set_channel_mode ( dcmotor20_t *ctx, uint8_t channel, uint8_t mode );
```

- `dcmotor20_set_standby_mode` This function sets the chip to the standby mode which affects both channels.
```c
void dcmotor20_set_standby_mode ( dcmotor20_t *ctx );
```

### Application Init

> Initializes the driver and sets the Click board to standby mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    dcmotor20_cfg_t dcmotor20_cfg;  /**< Click config object. */

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
    dcmotor20_cfg_setup( &dcmotor20_cfg );
    DCMOTOR20_MAP_MIKROBUS( dcmotor20_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == dcmotor20_init( &dcmotor20, &dcmotor20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    dcmotor20_set_standby_mode ( &dcmotor20 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motors in the forward direction for 5 seconds, and then switches the direction, with a brake time of 2 seconds between switching the direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Driving motors forward...\r\n" );
    dcmotor20_set_channel_mode ( &dcmotor20, DCMOTOR20_CHANNEL_1 | DCMOTOR20_CHANNEL_2, DCMOTOR20_MODE_FORWARD );
    dcmotor20_drive_motor ( &dcmotor20, DCMOTOR20_SPEED_DEFAULT, 5000 );
    log_printf ( &logger, " Pull brake!\r\n" );
    dcmotor20_set_standby_mode ( &dcmotor20 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf ( &logger, " Driving motors in reverse...\r\n" );
    dcmotor20_set_channel_mode ( &dcmotor20, DCMOTOR20_CHANNEL_1 | DCMOTOR20_CHANNEL_2, DCMOTOR20_MODE_REVERSE );
    dcmotor20_drive_motor ( &dcmotor20, DCMOTOR20_SPEED_DEFAULT, 5000 );
    log_printf ( &logger, " Pull brake!\r\n\n" );
    dcmotor20_set_standby_mode ( &dcmotor20 );
    Delay_ms ( 1000 );
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
