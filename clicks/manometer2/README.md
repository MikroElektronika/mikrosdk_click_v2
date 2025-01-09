
---
# Manometer 2 Click

> [Manometer 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2550) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2550&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This application is digital pressure sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Manometer2

### Example Key Functions

- `manometer2_cfg_setup` Config Object Initialization function. 
```c
void manometer2_cfg_setup ( manometer2_cfg_t *cfg );
``` 
 
- `manometer2_init` Initialization function. 
```c
err_t manometer2_init ( manometer2_t *ctx, manometer2_cfg_t *cfg );
```

- Generic read data function
uint32_t manometer2_read_command ( manometer2_t *ctx, uint8_t reg_address );

- `manometer2_read_coef` Function read coeffitient. 
```c
void manometer2_read_coef ( manometer2_t *ctx );
```

- Get pressure data function
float manometer2_get_pressure ( manometer2_t *ctx, uint8_t oversampling_ratio );

### Application Init

> Initialization driver enable's - I2C,
> initialization Manometer 2 sensor MS5525DSO-SB001GS by read coeffitient value
> and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    manometer2_cfg_t cfg;

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

    manometer2_cfg_setup( &cfg );
    MANOMETER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    manometer2_init( &manometer2, &cfg );

    manometer2_read_coef( &manometer2 );
    log_printf( &logger, "        Initialization \r\n" );
    log_printf( &logger, "----------------------------- \r\n" );
    Delay_100ms( );
}
```

### Application Task

> This is a example which demonstrates the use of Manometer 2 Click board.
> Measured pressure and temperature value from sensor, calculate pressure [ PSI ] and temperature [ �C ],
> results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 3 sec when the data value changes.

```c
void application_task (  )
{
    float temperature;
    float pressure;

    temperature = manometer2_get_temperature( &manometer2, MANOMETER2_CONVERT_4096 );
    Delay_10ms( );

    pressure = manometer2_get_pressure( &manometer2, MANOMETER2_CONVERT_4096 );
    Delay_10ms( );

    log_printf( &logger, " Pressure :  %.2f PSI \r\n", pressure );
    log_printf( &logger, " Temperature: %.2f C \r\n", temperature );
    log_printf( &logger, "----------------------------- \r\n" );

    Delay_1sec( );
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
