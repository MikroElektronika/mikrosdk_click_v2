
---
# Manometer Click

> [Manometer Click](https://www.mikroe.com/?pid_product=MIKROE-2237) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2237&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application carries a piezoresistive silicon pressure       sensor. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Manometer

### Example Key Functions

- `manometer_cfg_setup` Config Object Initialization function. 
```c
void manometer_cfg_setup ( manometer_cfg_t *cfg );
``` 
 
- `manometer_init` Initialization function. 
```c
err_t manometer_init ( manometer_t *ctx, manometer_cfg_t *cfg );
```

- `manometer_generic_write` Generic write function. 
```c
void manometer_generic_write ( manometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```
 
- `manometer_generic_read` Generic read function. 
```c
void manometer_generic_read ( manometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

- `manometer_get_pressure` Function read 16-bit data and convert to pressure in mbar. 
```c
float manometer_get_pressure ( manometer_t *ctx );
```

### Application Init

> Initialization driver enable's - I2C and start write log to      Usart Terminal. 

```c
void application_init ( void )
{
 log_cfg_t log_cfg;
    manometer_cfg_t cfg;

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

    manometer_cfg_setup( &cfg );
    MANOMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    manometer_init( &manometer, &cfg );
}
```

### Application Task

> This is a example which demonstrates the use of Manometer Click board.

```c
void application_task ( void )
{
 float read_data;

    read_data = manometer_get_pressure( &manometer );
    Delay_10ms( );

    log_printf( &logger, " Pressure: %d mbar\r\n", read_data );

    read_data = manometer_get_temperature( &manometer );
    Delay_10ms( );

    log_printf( &logger, " Temperature:  %d C\r\n", read_data );
    log_printf( &logger, "--------------------------\r\n" );

    Delay_1sec( );
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
