
---
# I2C MUX 4 Click

> [I2C MUX 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4240) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4240&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the I2C MUX 4 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cMux4

### Example Key Functions

- `i2cmux4_cfg_setup` Config Object Initialization function. 
```c
void i2cmux4_cfg_setup ( i2cmux4_cfg_t *cfg );
``` 
 
- `i2cmux4_init` Initialization function. 
```c
err_t i2cmux4_init ( i2cmux4_t *ctx, i2cmux4_cfg_t *cfg );
```

- `i2cmux4_get_ch_interrupt` Get channel interrupt function. 
```c
uint8_t i2cmux4_get_ch_interrupt ( i2cmux4_t *ctx );
```
 
- `i2cmux4_rmt_read_bytes` Generic read data function. 
```c
void i2cmux4_rmt_read_bytes ( i2cmux4_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );
```

- `i2cmux4_check_int` Check interrupt function. 
```c
uint8_t i2cmux4_check_int ( i2cmux4_t *ctx );
```

### Application Init

> Initializes the driver, enables the Click board and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux4_cfg_t cfg;

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

    i2cmux4_cfg_setup( &cfg );
    I2CMUX4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux4_init( &i2cmux4, &cfg );

    i2cmux4_power_on( &i2cmux4, I2CMUX4_ENABLE_POWER_ON );
    Delay_ms ( 100 );
    
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_ALL_DISABLE, 0x00 );
    Delay_ms ( 100 );
}
```

### Application Task

> In this example, we read the device ID register of the connected Click boards.
> Channel 0 : 6DOF IMU 12 Click [slave address: 0x68; reg: 0x00; id val.: 0x24],
> Channel 1 : Compass 3 Click   [slave address: 0x30; reg: 0x2F; id val.: 0x0C].
> All data logs write on USB UART changes every 2 sec.

```c
void application_task ( void )
{
    // CH 0 - 6DOF IMU 12 Click
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_0, 0x68 );
    Delay_ms ( 100 );

    i2cmux4_rmt_read_bytes( &i2cmux4, 0x00, &rx_data, 1 );
    Delay_ms ( 100 );

    log_printf( &logger, "    6DOF IMU 12 Click   \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    log_printf( &logger, "       ID = 0x%.2X  \r\n", ( uint16_t ) rx_data );
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms ( 1000 );
    
    
    // CH 1 - Compass 3 Click
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_1, 0x30 );
    Delay_ms ( 100 );

    i2cmux4_rmt_read_bytes( &i2cmux4, 0x2F, &rx_data, 1 );
    Delay_ms ( 100 );

    log_printf( &logger, "      Compass 3 Click      \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    log_printf( &logger, "       ID = 0x%.2X \r\n ", ( uint16_t ) rx_data );
    log_printf( &logger, "----------------------- \r\n" );
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
