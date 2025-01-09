
---
# Stepper 16 Click

> [Stepper 16 Click](https://www.mikroe.com/?pid_product=MIKROE-4751) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4751&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : May 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases the device's ability to control the motor.
It initializes the device for control and moves the motor in two 
directions in a variety of speeds and step resolutions for 360 degrees.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper16

### Example Key Functions

- `stepper16_cfg_setup` Config Object Initialization function.
```c
void stepper16_cfg_setup ( stepper16_cfg_t *cfg );
```

- `stepper16_init` Initialization function.
```c
err_t stepper16_init ( stepper16_t *ctx, stepper16_cfg_t *cfg );
```

- `stepper16_default_cfg` Click Default Configuration function.
```c
err_t stepper16_default_cfg ( stepper16_t *ctx );
```

- `stepper16_hard_reset` Resets device.
```c
void stepper16_hard_reset ( stepper16_t *ctx );
```

- `stepper16_set_step_resolution` Set step resolution.
```c
void stepper16_set_step_resolution ( stepper16_t *ctx, uint8_t step_res );
```

- `stepper16_move_motor_angle` Move motor in angle value.
```c
void stepper16_move_motor_angle ( stepper16_t *ctx, float degree, uint8_t speed );
```

### Application Init

> Initializes UART and SPI communication modules, and additional  
pins for motor control, resets device, set's default configuration,
and reads its ID and sets

```c
void application_init ( void ) 
{
    uint16_t read_data = 0;
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper16_cfg_t stepper16_cfg;  /**< Click config object. */

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
    stepper16_cfg_setup( &stepper16_cfg );
    STEPPER16_MAP_MIKROBUS( stepper16_cfg, MIKROBUS_1 );
    err_t init_flag  = stepper16_init( &stepper16, &stepper16_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    stepper16_default_cfg ( &stepper16 );
    check_error( &stepper16 );
    stepper16_generic_read( &stepper16, STEPPER16_REG_SR4, &read_data );
    check_error( &stepper16 );
    log_info( &logger, "DEV ID: %d ", ( read_data >> 3 ) );
    log_info( &logger, "REV ID: %d ", ( read_data & 3 ) );

    log_info( &logger, " Application Task " );
    stepper16_set_dir( &stepper16, 1 );
}
```

### Application Task

> First it move motor clockwise for 360 degrees in medium speed and 
full step resolution. Then changes direction and moves motor for 
180 degrees in slow speed and quarter step, and additional 180 degrees
in fast speed and 1/16 step resolution.

```c
void application_task ( void ) 
{
    static uint8_t direction = 1;
    log_printf( &logger, "> Move 360deg in CW direction.\r\n" );
    stepper16_set_step_resolution( &stepper16, STEPPER16_STEP_RES_FULL );
    check_error( &stepper16 );
    stepper16_move_motor_angle( &stepper16, 360, STEPPER16_SPEED_MEDIUM );
    direction = !direction;
    stepper16_set_dir( &stepper16, direction );
    Delay_ms ( 500 );
    log_printf( &logger, "> Move 180deg in CCW direction.\r\n" );
    stepper16_set_step_resolution( &stepper16, STEPPER16_STEP_RES_QUARTER );
    check_error( &stepper16 );
    stepper16_move_motor_angle( &stepper16, 180, STEPPER16_SPEED_SLOW );
    Delay_ms ( 1000 );
    log_printf( &logger, "> Move 180deg in CCW direcion.\r\n" );
    stepper16_set_step_resolution( &stepper16, STEPPER16_STEP_RES_1div16 );
    check_error( &stepper16 );
    stepper16_move_motor_angle( &stepper16, 180, STEPPER16_SPEED_FAST );
    direction = !direction;
    stepper16_set_dir( &stepper16, direction );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Device is powered by externam VM so for communication to work Click 
board should be connected on power supply from 6V to 29V. At the start of
application user should reset device and read it's Status register 1 to clear it.
After that it can communicate with device and control it noramaly.

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
