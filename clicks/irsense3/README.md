
---
# IR Sense 3 Click

> [IR Sense 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3607) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3607&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Demo application shows detection of human and reading of 
> other parameters such as IR current ..

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrSense3

### Example Key Functions

- `irsense3_cfg_setup` Config Object Initialization function. 
```c
void irsense3_cfg_setup ( irsense3_cfg_t *cfg );
``` 
 
- `irsense3_init` Initialization function. 
```c
err_t irsense3_init ( irsense3_t *ctx, irsense3_cfg_t *cfg );
```

- `irsense3_default_cfg` Click Default Configuration function. 
```c
void irsense3_default_cfg ( irsense3_t *ctx );
```

- `irsense3_human_approach_detect` Human approach detection. 
```c
uint8_t irsense3_human_approach_detect ( irsense3_t *ctx );
```
 
- `irsense3_get_ir_sensor_data` Output current of IR sensor. 
```c
float irsense3_get_ir_sensor_data ( irsense3_t *ctx );
```

- `irsense3_get_interrupt_state` Get Interrupt state. 
```c
uint8_t irsense3_get_interrupt_state ( irsense3_t *ctx );
```

### Application Init

> Configuring Clicks and log objects.
> Software reset and settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    irsense3_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    irsense3_cfg_setup( &cfg );
    IRSENSE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irsense3_init( &irsense3, &cfg );

    // Software reset

    log_info( &logger, "---- Software reset ----" );
    irsense3_software_reset( &irsense3 );
    Delay_1sec( );

    // Configuration

    log_info( &logger, "---- Default config ----" );
    irsense3_default_cfg( &irsense3 );
}
```

### Application Task

> Reads temperature data, outputs current of IR Sensor and checks for human approach. 

```c
void application_task ( void )
{
    float temperature;
    float ir_current_data;
    uint8_t f_detect;

    // Detection Object

    f_detect = irsense3_human_approach_detect( &irsense3 );
    if ( f_detect != 0 )
    {
       log_printf( &logger, ">> Human Approach detected !!!\r\n" );
       Delay_1sec( );
    }

    // Output current of IR sensor

    ir_current_data = irsense3_get_ir_sensor_data( &irsense3 );
    log_printf( &logger, ">> IR current data: %.2f pA.\r\n", ir_current_data );

    // Temperature

    temperature = irsense3_get_temperature_data( &irsense3 );
    log_printf( &logger, ">> Temperature: %.2f C.\r\n", temperature );

    log_printf( &logger, "----------------------------\r\n" );
    Delay_1sec( );
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
