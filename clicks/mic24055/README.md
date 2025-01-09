
---
# MIC24055  Click

> [MIC24055 Click](https://www.mikroe.com/?pid_product=MIKROE-2835) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2835&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application is the buck regulator.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic24055

### Example Key Functions

- `mic24055_cfg_setup` Config Object Initialization function. 
```c
void mic24055_cfg_setup ( mic24055_cfg_t *cfg );
``` 
 
- `mic24055_init` Initialization function. 
```c
err_t mic24055_init ( mic24055_t *ctx, mic24055_cfg_t *cfg );
```

- `mic24055_generic_transfer` Generic transfer function. 
```c
void mic24055_generic_transfer ( mic24055_t *ctx, spi_master_transfer_data_t *block );
```
 
- `mic24055_dac_output` Generic transfer function. 
```c
void mic24055_dac_output ( mic24055_t *ctx, uint16_t value_dac );
```

- `mic24055_set_vout` Set output voltage. 
```c
void mic24055_set_vout ( mic24055_t *ctx, uint16_t voltage );
```

### Application Init

> Initializes Click driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mic24055_cfg_t cfg;

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

    mic24055_cfg_setup( &cfg );
    MIC24055_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic24055_init( &mic24055, &cfg );
}
```

### Application Task

> Slowly alternates the Click output between two values.

```c
void application_task ( void )
{
    mic24055_set_vout( &mic24055, 1500 );
    log_printf( &logger, "VOUT set to 1500mV \r\n" );
    log_printf( &logger, "-------------------------- \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    mic24055_set_vout( &mic24055, 3300 );
    log_printf( &logger, "VOUT set to 3300mV \r\n" );
    log_printf( &logger, "-------------------------- \r\n" );
    Delay_ms ( 1000 );
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
