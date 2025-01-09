
---
# Ambient 9 Click

> [Ambient 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4197) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4197&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 9 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient9

### Example Key Functions

- `ambient9_cfg_setup` Config Object Initialization function. 
```c
void ambient9_cfg_setup ( ambient9_cfg_t *cfg );
``` 
 
- `ambient9_init` Initialization function. 
```c
err_t ambient9_init ( ambient9_t *ctx, ambient9_cfg_t *cfg );
```

- `ambient9_als_data` Generic function for reading ALS data from senso. 
```c
uint32_t ambient9_als_data( ambient9_t *ctx );
```
 
- `ambient9_proxy_data` Generic function for reading proximity data from sensor. 
```c
uint16_t ambient9_proxy_data( ambient9_t *ctx );
```

- `ambient9_enable_data` Function for enabeling sensor for ALS or proximity. 
```c
void ambient9_enable_data( ambient9_t *ctx, uint8_t als_ps );
```

### Application Init

> Initializes the driver then reads the device status and part ID. If there's any error occured 
> it displays an appropriate message on the USB UART. After that, it enables the device mode
> defined by the dev_mode variable. ALS mode is selected by default.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient9_cfg_t cfg;

    uint8_t status_data;

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

    ambient9_cfg_setup( &cfg );
    AMBIENT9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient9_init( &ambient9, &cfg );

    ambient9_generic_read( &ambient9, AMBIENT9_REG_PART_ID, &status_data, 1 );
    if ( AMBIENT9_PART_ID_VAL != status_data )
    {
        log_printf( &logger, " *****  ERROR ID!  ***** \r\n" );
        for( ; ; );
    }
    Delay_ms ( 500 );
    ambient9_generic_read( &ambient9, AMBIENT9_REG_MAIN_STATUS, &status_data, 1 );
    if ( AMBIENT9_POWER_ON == ( status_data & AMBIENT9_POWER_ON ) )
    {
        log_printf( &logger, " *****  ERROR POWER ON!  ***** \r\n" );
        for( ; ; );
    }
    
    dev_mode = AMBIENT9_ALS;
    ambient9_enable_data( &ambient9, dev_mode );  

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

> Depending on the selected device mode, it reads an ambient light sensor or proximity data and 
> displays the results on the USB UART every 100ms.

```c
void application_task ( void )
{
    uint16_t proxy_data;
    uint32_t als_data;

    if ( AMBIENT9_ALS == dev_mode )
    {
        als_data = ambient9_als_data( &ambient9 );
        log_printf( &logger, " - ALS data: %lu \r\n", als_data );
    }
    else if ( AMBIENT9_PROXY == dev_mode )
    {
        proxy_data = ambient9_proxy_data( &ambient9 );
        log_printf( &logger, " - Proximity data: %u \r\n", proxy_data );
    }
    Delay_ms ( 100 );
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
