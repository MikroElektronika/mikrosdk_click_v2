
---
# LightRanger 2 Click

> [LightRanger 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2509) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2509&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example measures the distance of the object from the sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger2

### Example Key Functions

- `lightranger2_cfg_setup` Config Object Initialization function. 
```c
void lightranger2_cfg_setup ( lightranger2_cfg_t *cfg );
``` 
 
- `lightranger2_init` Initialization function. 
```c
err_t lightranger2_init ( lightranger2_t *ctx, lightranger2_cfg_t *cfg );
```

- `lightranger2_default_cfg` Click Default Configuration function. 
```c
void lightranger2_default_cfg ( lightranger2_t *ctx );
```

- `lightranger2_write_byte` This function writes a byte of data to the targeted 8-bit register board. 
```c
void lightranger2_write_byte ( lightranger2_t* ctx, uint8_t reg_address, uint8_t write_data );
```
 
- `lightranger2_read_bytes` Function read a sequential data starting from the targeted 8-bit register. 
```c
void lightranger2_read_bytes ( lightranger2_t* ctx, uint8_t reg_address, uint8_t* read_data, uint8_t n_bytes );
```

- `lightranger2_get_range_continuous` Function gets a range measurement in millimeters when continuous mode is active. 
```c
uint16_t lightranger2_get_range_continuous ( lightranger2_t* ctx );
```

### Application Init

> Initialization driver,enable Vl6180X sensor and sets default configuration for Vl6180X.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lightranger2_cfg_t cfg;

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

    lightranger2_cfg_setup( &cfg );
    LIGHTRANGER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightranger2_init( &lightranger2, &cfg );
    lightranger2_default_cfg( &lightranger2 );
    
    lightranger2_start_continuous( &lightranger2, 0 );
    Delay_ms ( 100 );
}
```

### Application Task

> Measures the distance of the object from the sensor and logs on terminal.

```c
void application_task ( void )
{
    uint16_t distance;
    
    distance = lightranger2_get_range_continuous( &lightranger2 );
    Delay_ms ( 10 );
    
    if ( distance )
    {
        log_printf( &logger, "Distance: %u mm \r\n", distance );
        Delay_ms ( 100 );
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
