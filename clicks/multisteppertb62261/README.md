
---
# Multi Stepper TB62261 Click

> [Multi Stepper TB62261 Click](https://www.mikroe.com/?pid_product=MIKROE-5040) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5040&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Multi Stepper TB62261 Click board by driving the motor in both directions for a desired number of steps.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MultiStepperTB62261

### Example Key Functions

- `multisteppertb62261_cfg_setup` Config Object Initialization function.
```c
void multisteppertb62261_cfg_setup ( multisteppertb62261_cfg_t *cfg );
```

- `multisteppertb62261_init` Initialization function.
```c
err_t multisteppertb62261_init ( multisteppertb62261_t *ctx, multisteppertb62261_cfg_t *cfg );
```

- `multisteppertb62261_default_cfg` Click Default Configuration function.
```c
err_t multisteppertb62261_default_cfg ( multisteppertb62261_t *ctx );
```

- `multisteppertb62261_set_step_mode` This function sets the step mode resolution settings in ctx->step_mode.
```c
void multisteppertb62261_set_step_mode ( multisteppertb62261_t *ctx, uint8_t mode );
```

- `multisteppertb62261_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
err_t multisteppertb62261_drive_motor ( multisteppertb62261_t *ctx, uint32_t steps, uint8_t speed );
```

- `multisteppertb62261_set_direction` This function sets the motor direction to clockwise or counter-clockwise in ctx->direction.
```c
void multisteppertb62261_set_direction ( multisteppertb62261_t *ctx, uint8_t dir );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    multisteppertb62261_cfg_t multisteppertb62261_cfg;  /**< Click config object. */

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
    multisteppertb62261_cfg_setup( &multisteppertb62261_cfg );
    MULTISTEPPERTB62261_MAP_MIKROBUS( multisteppertb62261_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == multisteppertb62261_init( &multisteppertb62261, &multisteppertb62261_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MULTISTEPPERTB62261_ERROR == multisteppertb62261_default_cfg ( &multisteppertb62261 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor clockwise for 200 steps and then counter-clockiwse for 100 steps with 2 seconds delay before changing the direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    multisteppertb62261_set_direction ( &multisteppertb62261, MULTISTEPPERTB62261_DIR_CW );
    if ( MULTISTEPPERTB62261_OK == multisteppertb62261_drive_motor ( &multisteppertb62261, 200, 
                                                                     MULTISTEPPERTB62261_SPEED_FAST ) )
    {
        log_printf ( &logger, " Move 200 steps clockwise \r\n\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    multisteppertb62261_set_direction ( &multisteppertb62261, MULTISTEPPERTB62261_DIR_CCW );
    if ( MULTISTEPPERTB62261_OK == multisteppertb62261_drive_motor ( &multisteppertb62261, 100,
                                                                     MULTISTEPPERTB62261_SPEED_FAST ) )
    {
        log_printf ( &logger, " Move 100 steps counter-clockwise \r\n\n" );
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
