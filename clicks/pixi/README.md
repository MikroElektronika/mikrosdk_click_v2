
---
# Pixi Click

> [Pixi Click](https://www.mikroe.com/?pid_product=MIKROE-2817) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2817&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases how to initialize, configure and use the Pixi Click moduel. The Click
  features Maxim Integrated's versatile, proprietary PIXI&trade; technology - the industry's first
  configurable 20-channel mixed-signal data converter. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pixi

### Example Key Functions

- `pixi_cfg_setup` Config Object Initialization function. 
```c
void pixi_cfg_setup ( pixi_cfg_t *cfg );
``` 
 
- `pixi_init` Initialization function. 
```c
err_t pixi_init ( pixi_t *ctx, pixi_cfg_t *cfg );
```

- `pixi_default_cfg` Click Default Configuration function. 
```c
void pixi_default_cfg ( pixi_t *ctx );
```

- `pixi_write_reg` This function writes data to the Click module. 
```c
uint8_t pixi_write_reg ( pixi_t *ctx, const uint8_t reg_addr, uint32_t reg_data );
```
 
- `pixi_read_reg` This function reads data from the Click module. 
```c
uint8_t pixi_read_reg ( pixi_t *ctx, const uint8_t reg_addr, uint32_t *reg_data );
```

### Application Init

> This function initializes and configures the Click and logger modules. After the initial setup
  a device id check is performed which will stop the module if the check fails. Additional con-
  figurating is done in the default_cfg(...) function. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pixi_cfg_t cfg;
    uint32_t res;

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
    Delay_100ms( );

    //  Click initialization.

    pixi_cfg_setup( &cfg );
    PIXI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pixi_init( &pixi, &cfg );

    //  Device ID check.

    pixi_read_reg( &pixi, PIXI_REG_DEVICE_ID, &res );
    if ( res != 1060 )
    {
        log_printf( &logger, "ERROR : WRONG DEVICE ID!\r\n" );
        for( ; ; );
    }
    else
    {
        log_printf( &logger, "Driver Init - DONE!\r\n" );
    }

    //  Default configuration.

    pixi_default_cfg( &pixi );
}
```

### Application Task

> This function sets the output signal on port 0 to different values every second. 

```c
void application_task ( void )
{
    pixi_write_reg( &pixi, PIXI_REG_GPO_DATA, 1 );
    Delay_ms ( 1000 );
    pixi_write_reg( &pixi, PIXI_REG_GPO_DATA, 0 );
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
