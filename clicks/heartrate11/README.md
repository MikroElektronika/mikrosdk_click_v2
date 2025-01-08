
---
# Heart Rate 11 Click

> [Heart Rate 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5170) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5170&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Heart Rate 11 Click board by reading and displaying the PPG1 (HR) values which can be visualized on the SerialPlot application.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate11

### Example Key Functions

- `heartrate11_cfg_setup` Config Object Initialization function.
```c
void heartrate11_cfg_setup ( heartrate11_cfg_t *cfg );
```

- `heartrate11_init` Initialization function.
```c
err_t heartrate11_init ( heartrate11_t *ctx, heartrate11_cfg_t *cfg );
```

- `heartrate11_default_cfg` Click Default Configuration function.
```c
err_t heartrate11_default_cfg ( heartrate11_t *ctx );
```

- `heartrate11_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t heartrate11_get_int_pin ( heartrate11_t *ctx );
```

- `heartrate11_set_led_current` This function sets the maximal current of the selected LED.
```c
err_t heartrate11_set_led_current ( heartrate11_t *ctx, uint8_t led, float current );
```

- `heartrate11_read_fifo` This function reads a 24-bit data from the FIFO.
```c
err_t heartrate11_read_fifo ( heartrate11_t *ctx, uint32_t *fifo_data );
```

### Application Init

> Initializes the driver and performs the Click default configuration for heart rate measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate11_cfg_t heartrate11_cfg;  /**< Click config object. */

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
    heartrate11_cfg_setup( &heartrate11_cfg );
    HEARTRATE11_MAP_MIKROBUS( heartrate11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate11_init( &heartrate11, &heartrate11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE11_ERROR == heartrate11_default_cfg ( &heartrate11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then reads the values of PPG from FIFO and displays it on the USB UART (SerialPlot) every 32ms approximately.

```c
void application_task ( void )
{
    // Wait for the data ready interrupt indication
    while ( heartrate11_get_int_pin ( &heartrate11 ) );
    
    uint32_t ppg;
    if ( HEARTRATE11_OK == heartrate11_read_fifo ( &heartrate11, &ppg ) )
    {
        log_printf ( &logger, "%lu\r\n", ppg );
    }
}
```

### Note

> We recommend using the SerialPlot tool for data visualizing.

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
