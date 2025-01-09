
---
# UART 1-Wire Click

> [UART 1-Wire Click](https://www.mikroe.com/?pid_product=MIKROE-3340) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3340&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from UART 1-Wire Clicks. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UART1Wire

### Example Key Functions

- `uart1wire_cfg_setup` Config Object Initialization function. 
```c
void uart1wire_cfg_setup ( uart1wire_cfg_t *cfg );
``` 
 
- `uart1wire_init` Initialization function. 
```c
err_t uart1wire_init ( uart1wire_t *ctx, uart1wire_cfg_t *cfg );
```

- `uart1wire_write_command` This function sends an 8-bit command to the Click module. 
```c
void uart1wire_write_command ( uart1wire_t *ctx, uint8_t cmd );
```
 
- `uart1wire_read_temperature` This function reads the temperature from DALLAS one wire temperature sensors. 
```c
int8_t uart1wire_read_temperature ( uart1wire_t *ctx, float *temperature, uint8_t resolution );
```

- `uart1wire_reset` This function sends a reset pulse signal. 
```c
void uart1wire_reset ( uart1wire_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    uart1wire_cfg_t cfg;

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

    uart1wire_cfg_setup( &cfg );
    UART1WIRE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uart1wire_init( &uart1wire, &cfg );
    
    Delay_ms ( 100 );
}
```

### Application Task

> Reads the temperature data from DALLAS temperature sensors and logs the results on the USB UART every second.

```c
void application_task ( void )
{
    float temp_f;
    uint8_t res_flag;
    
    res_flag = uart1wire_read_temperature ( &uart1wire, &temp_f, UART1WIRE_TEMP_SENSOR_RESOLUTION_9BIT );
    if ( res_flag == UART1WIRE_OK )
    {
        log_printf( &logger, " * Temperature:     %.2f C\r\n", temp_f );
        log_printf( &logger, "------------------------------\r\n" );
        Delay_ms ( 1000 );
    }
}
```

### Note

> Connect only DQ and GND pins to the UART 1-Wire Click connector.

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
