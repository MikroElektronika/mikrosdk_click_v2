
---
# 4-20 mA T Click

> [4-20 mA T Click](https://www.mikroe.com/?pid_product=MIKROE-1296) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1296&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This aplication changes the value of the output current.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.420mat

### Example Key Functions

- `c420mat_cfg_setup` Config Object Initialization function. 
```c
void c420mat_cfg_setup ( c420mat_cfg_t *cfg );
``` 
 
- `c420mat_init` Initialization function. 
```c
err_t c420mat_init ( c420mat_t *ctx, c420mat_cfg_t *cfg );
```

- `c420mat_dac_output` This function sets the output of DAC. 
```c
void c420mat_dac_output ( c420mat_t *ctx, uint16_t value_dac );
```
 
- `c420mat_set_i_out` This function sets the output current to selected value. 
```c
void c420mat_set_i_out ( c420mat_t *ctx, uint8_t i_out );
```

### Application Init

> Initializes Click SPI driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c420mat_cfg_t cfg;

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

    c420mat_cfg_setup( &cfg );
    C420MAT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c420mat_init( &c420mat, &cfg );
}
```

### Application Task

> Periodically changes Iout value.

```c
void application_task ( void )
{
   c420mat_set_i_out( &c420mat, 56 );                   // sets Iout to 5.6mA
   Delay_ms ( 1000 );
   Delay_ms ( 1000 );
   Delay_ms ( 1000 );
   c420mat_set_i_out( &c420mat, 158 );                  // sets Iout to 15.8mA
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
