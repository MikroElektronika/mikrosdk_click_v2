
---
# Power Step 2 Click

> [Power Step 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6524) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6524&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Power Step 2 Click board for precise control of stepper motors. 
The application showcases various step modes, directions, and speeds while demonstrating the board's 
ability to control motors using different operation modes.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerStep2

### Example Key Functions

- `powerstep2_cfg_setup` Config Object Initialization function.
```c
void powerstep2_cfg_setup ( powerstep2_cfg_t *cfg );
```

- `powerstep2_init` Initialization function.
```c
err_t powerstep2_init ( powerstep2_t *ctx, powerstep2_cfg_t *cfg );
```

- `powerstep2_default_cfg` Click Default Configuration function.
```c
err_t powerstep2_default_cfg ( powerstep2_t *ctx );
```

- `powerstep2_set_step_mode` This function sets the step mode (microstepping level) of the Power Step 2 device.
```c
err_t powerstep2_set_step_mode ( powerstep2_t *ctx, uint8_t step_mode );
```

- `powerstep2_set_speed` This function sets the minimum and maximum speeds for motor movement.
```c
err_t powerstep2_set_speed ( powerstep2_t *ctx, float min_speed, float max_speed );
```

- `powerstep2_move` This function moves the motor a specified number of steps in a given direction.
```c
err_t powerstep2_move ( powerstep2_t *ctx, uint8_t dir, uint32_t n_step );
```

### Application Init

> Initializes the logger and configures the Power Step 2 Click board. The default settings are applied 
to prepare the device for motor control operations.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    powerstep2_cfg_t powerstep2_cfg;  /**< Click config object. */

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
    powerstep2_cfg_setup( &powerstep2_cfg );
    POWERSTEP2_MAP_MIKROBUS( powerstep2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == powerstep2_init( &powerstep2, &powerstep2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( POWERSTEP2_ERROR == powerstep2_default_cfg ( &powerstep2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Demonstrates motor control with various configurations. The example alternates between multiple step 
modes (1/8, 1/16, 1/32, 1/4), directions (CW, CCW), speeds, and control modes (voltage, current). 
Each configuration is applied sequentially, with the motor driven through specified steps before switching 
to the next configuration.

```c
void application_task ( void )
{
    log_printf ( &logger, " Step mode: 1/8\r\n" );
    log_printf ( &logger, " Direction: CW\r\n" );
    log_printf ( &logger, " Steps: 16000\r\n" );
    log_printf ( &logger, " Speed: [0, 500]\r\n" );
    log_printf ( &logger, " Acc-Dec: [200, 100]\r\n" );
    log_printf ( &logger, " Control mode: Command voltage\r\n\n" );
    powerstep2_clear_status ( &powerstep2 );
    powerstep2_set_control_mode ( &powerstep2, POWERSTEP2_CONTROL_MODE_VOLTAGE );
    powerstep2_set_step_mode ( &powerstep2, POWERSTEP2_STEP_MODE_1_OVER_8 );
    powerstep2_set_speed ( &powerstep2, 0, 500 );
    powerstep2_set_acc_dec ( &powerstep2, 200, 100 );
    powerstep2_move ( &powerstep2, POWERSTEP2_DIR_CW, 16000 );
    powerstep2_soft_hiz ( &powerstep2 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Step mode: 1/16\r\n" );
    log_printf ( &logger, " Direction: CCW\r\n" );
    log_printf ( &logger, " Steps: 32000\r\n" );
    log_printf ( &logger, " Speed: [350, 600]\r\n" );
    log_printf ( &logger, " Acc-Dec: [100, 200]\r\n" );
    log_printf ( &logger, " Control mode: Command current\r\n\n" );
    powerstep2_clear_status ( &powerstep2 );
    powerstep2_set_control_mode ( &powerstep2, POWERSTEP2_CONTROL_MODE_CURRENT );
    powerstep2_set_step_mode ( &powerstep2, POWERSTEP2_STEP_MODE_1_OVER_16 );
    powerstep2_set_speed ( &powerstep2, 350, 600 );
    powerstep2_set_acc_dec ( &powerstep2, 100, 200 );
    powerstep2_move ( &powerstep2, POWERSTEP2_DIR_CCW, 32000 );
    powerstep2_soft_hiz ( &powerstep2 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Step mode: 1/32\r\n" );
    log_printf ( &logger, " Direction: CW\r\n" );
    log_printf ( &logger, " Steps: 16000\r\n" );
    log_printf ( &logger, " Speed: Very fast\r\n" );
    log_printf ( &logger, " Control mode: Step-clock voltage\r\n\n" );
    powerstep2_clear_status ( &powerstep2 );
    powerstep2_set_control_mode ( &powerstep2, POWERSTEP2_CONTROL_MODE_VOLTAGE );
    powerstep2_set_step_mode ( &powerstep2, POWERSTEP2_STEP_MODE_1_OVER_32 );
    powerstep2_step_clock ( &powerstep2, POWERSTEP2_DIR_CW );
    powerstep2_drive_motor ( &powerstep2, 16000, POWERSTEP2_SPEED_VERY_FAST );
    powerstep2_soft_hiz ( &powerstep2 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Step mode: 1/4\r\n" );
    log_printf ( &logger, " Direction: CCW\r\n" );
    log_printf ( &logger, " Steps: 2000\r\n" );
    log_printf ( &logger, " Speed: Medium\r\n" );
    log_printf ( &logger, " Control mode: Step-clock current\r\n\n" );
    powerstep2_clear_status ( &powerstep2 );
    powerstep2_set_control_mode ( &powerstep2, POWERSTEP2_CONTROL_MODE_CURRENT );
    powerstep2_set_step_mode ( &powerstep2, POWERSTEP2_STEP_MODE_QUARTER_STEP );
    powerstep2_step_clock ( &powerstep2, POWERSTEP2_DIR_CCW );
    powerstep2_drive_motor ( &powerstep2, 2000, POWERSTEP2_SPEED_MEDIUM );
    powerstep2_soft_hiz ( &powerstep2 );
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
