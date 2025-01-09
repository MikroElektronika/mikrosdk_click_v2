
---
# VCP Monitor 2 Click

> [VCP Monitor 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4126) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4126&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> VCP Monitor 2 Click is a three-channel, high-side current and bus voltage monitor with alert indication 
> function ensuring the intended application works within desired operating conditions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Vcpmonitor2

### Example Key Functions

- `vcpmonitor2_cfg_setup` Config Object Initialization function. 
```c
void vcpmonitor2_cfg_setup ( vcpmonitor2_cfg_t *cfg );
``` 
 
- `vcpmonitor2_init` Initialization function. 
```c
err_t vcpmonitor2_init ( vcpmonitor2_t *ctx, vcpmonitor2_cfg_t *cfg );
```

- `vcpmonitor2_get_manifacture_id` Get Manufacture ID. 
```c
uint16_t vcpmonitor2_get_manifacture_id ( vcpmonitor2_t *ctx );
```
 
- `vcpmonitor2_get_die_id` Get DIE ID. 
```c
uint16_t vcpmonitor2_get_die_id ( vcpmonitor2_t *ctx );
```

- `vcpmonitor2_get_bus_voltage` Get BUS voltage in mV. 
```c
float vcpmonitor2_get_bus_voltage ( vcpmonitor2_t *ctx, uint8_t channel );
```

### Application Init

> Initiaizes the driver, and checks the communication by reading the manufacture device ID. After that, performs the device default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    vcpmonitor2_cfg_t cfg;

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

    vcpmonitor2_cfg_setup( &cfg );
    VCPMONITOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vcpmonitor2_init( &vcpmonitor2, &cfg );

    check_id = vcpmonitor2_get_manifacture_id( &vcpmonitor2 );
    if ( check_id == VCPMONITOR2_DEF_MANUFACTURE_ID )
    {
        log_printf( &logger, ">> Manufacture ID: 0x%.4X\r\n", check_id );
    }
    else
    {
        log_error( &logger, " WRONG ID READ! " );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }

    vcpmonitor2_default_cfg( &vcpmonitor2 );
}
```

### Application Task

> Displays the voltage, current, and power detected from channel 1 on the USB UART every 2 seconds. It also displays the status of alert indicators.

```c
void application_task ( void )
{
    log_printf( &logger, ">> CHANNEL 1 <<\r\n" );
    display_channel_data( VCPMONITOR2_CHANNEL_1 );

    display_alert_status( );
    log_printf( &logger, "--------------------------\r\n" );
    
    Delay_ms ( 1000 );
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
