
---
# GeoMagnetic Click

> [GeoMagnetic Click](https://www.mikroe.com/?pid_product=MIKROE-2935) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2935&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example showcases how to initialize and configure the logger and Click modules and
  measure and display the data later on. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Geomagnetic

### Example Key Functions

- `geomagnetic_cfg_setup` Config Object Initialization function. 
```c
void geomagnetic_cfg_setup ( geomagnetic_cfg_t *cfg );
``` 
 
- `geomagnetic_init` Initialization function. 
```c
err_t geomagnetic_init ( geomagnetic_t *ctx, geomagnetic_cfg_t *cfg );
```

- `geomagnetic_default_cfg` Click Default Configuration function. 
```c
void geomagnetic_default_cfg ( geomagnetic_t *ctx );
```

- `geomagnetic_read_axis_data ` This function sets the x/y/z axis and hall resolution value. 
```c
void geomagnetic_read_axis_data  ( geomagnetic_t *ctx, int16_t *data_x, int16_t *data_y, int16_t *data_z, uint16_t *resolution_hall  );
```
 
- `geomagnetic_check_ready` This function gives feedback on whether the device is ready to measure or not. 
```c
uint8_t geomagnetic_check_ready ( geomagnetic_t *ctx );
```

- `` This function configures some Click module registers after the device has been reset. 
```c
geomagnetic_power_on_reset  ( geomagnetic_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules. 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    geomagnetic_cfg_t cfg;

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

    geomagnetic_cfg_setup( &cfg );
    GEOMAGNETIC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    geomagnetic_init( &geomagnetic, &cfg );
    geomagnetic_default_cfg( &geomagnetic );
}
```

### Application Task

> This function first checks whether the device is ready to start measuring and after that
  collects and displays data from all three axes every half a second. 

```c
void application_task ( )
{
err_t ready_check;
    int16_t axis_x;
    int16_t axis_y;
    int16_t axis_z;
    int16_t resolution_hall;

    ready_check = geomagnetic_check_ready( &geomagnetic );

    while ( ready_check != GEOMAG_DATA_READY )
    {
        ready_check = geomagnetic_check_ready( &geomagnetic );
    }

    geomagnetic_read_axis_data( &geomagnetic, &axis_x, &axis_y, &axis_z, &resolution_hall );

    log_printf( &logger, "X axis: %d\r\n", axis_x );
    log_printf( &logger, "Y axis: %d\r\n", axis_y );
    log_printf( &logger, "Z axis: %d\r\n", axis_z );
    log_printf( &logger, "---------------------------------\r\n" );

    Delay_ms ( 500 );
}
```

### Note

> The Geomagnetic Click needs to initialize the SPI communication module first, because the
  communication interface selection ( on the Click ) is locked on to SPI and we need to write
  some data to the registers in order to configure the Click module.

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
