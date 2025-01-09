
---
# Step Down 5 Click

> [Step Down 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5572) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5572&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Step Down 5 Click driver.
 This driver provides the functions to set the output voltage treshold.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown5

### Example Key Functions

- `stepdown5_cfg_setup` Config Object Initialization function.
```c
void stepdown5_cfg_setup ( stepdown5_cfg_t *cfg );
```

- `stepdown5_init` Initialization function.
```c
err_t stepdown5_init ( stepdown5_t *ctx, stepdown5_cfg_t *cfg );
```

- `stepdown5_default_cfg` Click Default Configuration function.
```c
err_t stepdown5_default_cfg ( stepdown5_t *ctx );
```

- `stepdown5_set_wiper_0_pos` Step Down 5 set wiper 0 position.
```c
err_t stepdown5_set_wiper_0_pos ( stepdown5_t *ctx, uint16_t wiper_0_pos );
```

- `stepdown5_set_r1_resistance` Step Down 5 set potentiometer 0 resistance.
```c
err_t stepdown5_set_r1_resistance ( stepdown5_t *ctx, uint32_t resistance );
```

- `stepdown5_set_output` Step Down 5 set output voltage.
```c
err_t stepdown5_set_output ( stepdown5_t *ctx, uint8_t voltage );
```

### Application Init

> Initialization of I2C module and log UART.
 After driver initialization, default settings sets output voltage to 0.6 V.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown5_cfg_t stepdown5_cfg;  /**< Click config object. */

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
    stepdown5_cfg_setup( &stepdown5_cfg );
    STEPDOWN5_MAP_MIKROBUS( stepdown5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown5_init( &stepdown5, &stepdown5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN5_ERROR == stepdown5_default_cfg ( &stepdown5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Step Down 5 Click board&trade; by changing 
 output voltage every 5 seconds starting from 0.6 V up to 3.3 V.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = STEPDOWN5_OUTPUT_0V6; n_cnt <= STEPDOWN5_OUTPUT_3V3; n_cnt++ )
    {
        stepdown5_set_output( &stepdown5, n_cnt );
        log_printf( &logger, " Selected output is:" );
        print_selected_output_level ( n_cnt );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
