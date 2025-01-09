
---
# Oximeter Click

> [Oximeter Click](https://www.mikroe.com/?pid_product=MIKROE-3102) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3102&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application collects data from the sensor, calculates it and then logs the result.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Oximeter

### Example Key Functions

- `oximeter_cfg_setup` Config Object Initialization function.
```c
void oximeter_cfg_setup ( oximeter_cfg_t *cfg ); 
```

- `oximeter_init` Initialization function.
```c
err_t oximeter_init ( oximeter_t *ctx, oximeter_cfg_t *cfg );
```

- `oximeter_default_cfg` Click Default Configuration function.
```c
void oximeter_default_cfg ( oximeter_t *ctx );
```

- `oximeter_write_reg` Function writes 16-bit data to the register.
```c
err_t oximeter_write_reg ( oximeter_t* ctx, uint8_t reg, uint16_t data_in );
```

- `oximeter_set_time_slot_a` Function performs the configuration for Time Slot A and enables the interrupt for this Slot.
```c
err_t oximeter_set_time_slot_a ( oximeter_t* ctx, oximeter_enable_t* dev_enable, uint8_t set_mode );
```

- `oximeter_enable_channels` Function determines which channel/channels be enabled.
```c
err_t oximeter_enable_channels ( oximeter_t* ctx, uint8_t select_channel );
```

### Application Init

> Initializes driver and performs the device configuration which puts Time Slot A
> in enabled mode and LEDX2 (IR diode) to active state.  Before the device configuration, the
> SW reset will be performed and in this way we will put the registers in initial state.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    oximeter_cfg_t cfg;

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
    oximeter_cfg_setup( &cfg );
    OXIMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oximeter_init( &oximeter, &cfg );
    oximeter_default_cfg( &oximeter );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Logs PD1-PD4 data on USB UART

```c
void application_task ( void )
{
    oxim_logs_results();
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
