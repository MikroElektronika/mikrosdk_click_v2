
---
# Ambient 4 Click

> [Ambient 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3199) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3199&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is a light intensity-sensing and measuring.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient4

### Example Key Functions

- `ambient4_cfg_setup` Config Object Initialization function. 
```c
void ambient4_cfg_setup ( ambient4_cfg_t *cfg );
``` 
 
- `ambient4_init` Initialization function. 
```c
err_t ambient4_init ( ambient4_t *ctx, ambient4_cfg_t *cfg );
```

- `ambient4_default_cfg` Click Default Configuration function. 
```c
void ambient4_default_cfg ( ambient4_t *ctx );
```

- `ambient4_send_command` Function for send command. 
```c
void ambient4_send_command ( ambient4_t *ctx, uint8_t cmd );
```
 
- `ambient4_read_data` Function for read 16bit data. 
```c
uint16_t ambient4_read_data ( ambient4_t *ctx );
```

- `ambient4_device_reset` Function for device reset. 
```c
void ambient4_device_reset ( ambient4_t *ctx );
```

### Application Init

> Initialization device and power ON chip and set resolution mode. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient4_cfg_t cfg;

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
    log_info(&logger, "|-----Application init -----|");

    ambient4_cfg_setup( &cfg );
    AMBIENT4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient4_init( &ambient4, &cfg );
    ambient4_default_cfg ( &ambient4 );
}
```

### Application Task

> Read ambient light in [lx] and logs data to USBUART every 1 sec. 

```c
void application_task ( void )
{
    uint16_t read_value;

    //  Task implementation.
    
    read_value = ambient4_read_data( &ambient4 );
    
    log_printf( &logger, " Ambient light: %d \r\n", read_value );

    Delay_ms ( 1000);
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
