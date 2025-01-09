
---
# IR Sense 2 Click

> [IR Sense 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2966) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2966&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application enables usage of IR sensor for presence detection.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrSense2

### Example Key Functions

- `irsense2_cfg_setup` Config Object Initialization function. 
```c
void irsense2_cfg_setup ( irsense2_cfg_t *cfg );
``` 
 
- `irsense2_init` Initialization function. 
```c
err_t irsense2_init ( irsense2_t *ctx, irsense2_cfg_t *cfg );
```

- `irsense2_default_cfg` Click Default Configuration function. 
```c
void irsense2_default_cfg ( irsense2_t *ctx );
```

- `irsense2_get_ir_data` This function reads and returns 16bit value from the IR senor. 
```c
int16_t irsense2_get_ir_data ( irsense2_t *ctx );
```
 
- This function calculates differences in read IR sensor data and
- `irsense_human_detected` determines if there was a presence that tireggered a change. 
```c
uint8_t irsense_human_detected ( irsense2_t *ctx, float ir_data );
```

- `irsense2_get_int` This function reads from interrupt factor information register. 
```c
void irsense2_get_int ( irsense2_t *ctx );
```

### Application Init

> Driver initialization.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    irsense2_cfg_t cfg;

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

    irsense2_cfg_setup( &cfg );
    IRSENSE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irsense2_init( &irsense2, &cfg );

    Delay_us( 100 );
    
    irsense2_default_cfg ( &irsense2 );
}
```

### Application Task

> Fetches IR and temperature sensor data and prints them on terminal.

```c
void application_task ( void )
{
    //  Task implementation.

    float temperature;
    float ir_data;
    uint8_t flag;

    Delay_ms ( 400 );

    irsense2_data_read( &irsense2, &ir_data, &temperature );

    flag = irsense_human_detected( &irsense2, ir_data );
    
    if( flag == 1 )
    {   log_printf( &logger, " \r\n----------------------------- \r\n");
        log_printf( &logger, "\r\n Person detected!!! \r\n" );
        log_printf( &logger, " \r\n----------------------------- \r\n");
        Delay_ms ( 300 );
    }

    log_printf( &logger, "\r\n\r\nIR Value:       %.2f  pA ", ir_data );
    log_printf( &logger, " \r\n----------------------------- \r\n");
    log_printf( &logger, "Temperature: %.8f  C \r\n", temperature );

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
