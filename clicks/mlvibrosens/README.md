
---
# ML Vibro Sens Click

> [ML Vibro Sens Click](https://www.mikroe.com/?pid_product=MIKROE-6470) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6470&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the ML Vibro Sens Click board by capturing and logging
acceleration data on the X, Y, and Z axes, along with temperature readings. The data is output 
over USB UART and can be visualized in real-time using tools like SerialPlot. Additionally, 
the vibro motor state changes periodically, cycling through different vibration states for 
added feedback.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MLVibroSens

### Example Key Functions

- `mlvibrosens_cfg_setup` Config Object Initialization function.
```c
void mlvibrosens_cfg_setup ( mlvibrosens_cfg_t *cfg );
```

- `mlvibrosens_init` Initialization function.
```c
err_t mlvibrosens_init ( mlvibrosens_t *ctx, mlvibrosens_cfg_t *cfg );
```

- `mlvibrosens_default_cfg` Click Default Configuration function.
```c
err_t mlvibrosens_default_cfg ( mlvibrosens_t *ctx );
```

- `mlvibrosens_get_int_pin` This function returns the interrupt pin logic state.
```c
uint8_t mlvibrosens_get_int_pin ( mlvibrosens_t *ctx );
```

- `mlvibrosens_get_data` This function reads accel X, Y, and Z axis data in g and temperature in degrees Celsius.
```c
err_t mlvibrosens_get_data ( mlvibrosens_t *ctx, mlvibrosens_data_t *data_out );
```

- `mlvibrosens_set_vibro_state` This function sets the vibro motors state.
```c
void mlvibrosens_set_vibro_state ( mlvibrosens_t *ctx, uint8_t state );
```

### Application Init

> Initializes the communication interface and configures the ML Vibro Sens Click board 
with default settings. This setup enables an interrupt on the INT pin when data is ready,
sets the acceleration sensitivity to a +/-4G range, and sets the output data rate to 100 Hz.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mlvibrosens_cfg_t mlvibrosens_cfg;  /**< Click config object. */

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
    mlvibrosens_cfg_setup( &mlvibrosens_cfg );
    MLVIBROSENS_MAP_MIKROBUS( mlvibrosens_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == mlvibrosens_init( &mlvibrosens, &mlvibrosens_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MLVIBROSENS_ERROR == mlvibrosens_default_cfg ( &mlvibrosens ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Monitors the data-ready interrupt, retrieves acceleration and temperature data when available,
and logs it over USB UART in the format X;Y;Z;TEMP. After every 1000 data readings, the 
vibro motor state cycles through predefined states to demonstrate the motor's functionality.

```c
void application_task ( void )
{
    static uint8_t vibro_state = MLVIBROSENS_VIBRO_STATE_IDLE;
    static uint16_t result_num = 0;
    static mlvibrosens_data_t accel_data;
    
    // Wait for a data ready interrupt
    while ( mlvibrosens_get_int_pin ( &mlvibrosens ) );

    if ( MLVIBROSENS_OK == mlvibrosens_get_data ( &mlvibrosens, &accel_data ) )
    {
        log_printf ( &logger, "%f;%f;%f;%d;\r\n", accel_data.x, accel_data.y, 
                                                  accel_data.z, accel_data.temperature ); 
    }
    if ( ++result_num > 1000 )
    {
        result_num = 0;
        if ( ++vibro_state > MLVIBROSENS_VIBRO_STATE_BOTH )
        {
            vibro_state = MLVIBROSENS_VIBRO_STATE_IDLE;
        }
        mlvibrosens_set_vibro_state ( &mlvibrosens, vibro_state );
    }
}
```

### Note

> We recommend using the SerialPlot tool for data visualization. The temperature measurements
should be visualized independently. The data format for plotter is as follows: X;Y;Z;TEMP;

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
