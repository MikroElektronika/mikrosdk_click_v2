
---
# Digi Pot 4 Click

> [Digi Pot 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2873) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2873&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application is a digitally controlled dual potentiometer.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DigiPot4

### Example Key Functions

- `digipot4_cfg_setup` Config Object Initialization function. 
```c
void digipot4_cfg_setup ( digipot4_cfg_t *cfg );
``` 
 
- `digipot4_init` Initialization function. 
```c
err_t digipot4_init ( digipot4_t *ctx, digipot4_cfg_t *cfg );
```

- `digipot4_default_cfg` Click Default Configuration function. 
```c
void digipot4_default_cfg ( digipot4_t *ctx );
```

- `digipot4_write_reg` This function writes data in wiper register and NV register. 
```c
void digipot4_write_reg ( digipot4_t *ctx, uint8_t reg,          uint16_t value );
```
 
- `digipot4_copy_reg` This function is used to copy the data from the wipers to the    NV memory and from the NV memory it wipers. 
```c
void digipot4_copy_reg ( digipot4_t *ctx, uint8_t reg );
```

### Application Init

> Driver intialization

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot4_cfg_t cfg;

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

    digipot4_cfg_setup( &cfg );
    DIGIPOT4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot4_init( &digipot4, &cfg );
}
```

### Application Task

> Set the wiper position. 

```c
void application_task ( void )
{

    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_1, 0 );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_2, 0 );
    Delay_1sec( );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_1, 512 );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_2, 512 );
    Delay_1sec( );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_1, 1023 );
    digipot4_write_reg( &digipot4, DIGIPOT4_WIPER_REG_2, 1023 );
    Delay_1sec( );
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
