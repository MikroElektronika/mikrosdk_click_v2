
---
# I2C MUX 2 Click

> [I2C MUX 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4094) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4094&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the I2C MUX 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cMux2

### Example Key Functions

- `i2cmux2_cfg_setup` Config Object Initialization function.
```c
void i2cmux2_cfg_setup ( i2cmux2_cfg_t *cfg ); 
```

- `i2cmux2_init` Initialization function.
```c
err_t i2cmux2_init ( i2cmux2_t *ctx, i2cmux2_cfg_t *cfg );
```

- `i2cmux2_hw_reset` This function resets I2C MUX 2 Click board by clearing the RST pin for 100ms.
```c
void i2cmux2_hw_reset ( i2cmux2_t *ctx );
```

- `i2cmux2_set_channel` Function sets channel of the I2C MUX 2 Click board.
```c
void i2cmux2_set_channel ( i2cmux2_t *ctx, uint8_t channel, uint8_t ch_slave_address );
```

- `i2cmux2_generic_read` This function reads data from the desired register.
```c
void i2cmux2_generic_read ( i2cmux2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

### Application Init

> Initializes the driver, performs the device reset, and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux2_cfg_t cfg;

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
    i2cmux2_cfg_setup( &cfg );
    I2CMUX2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux2_init( &i2cmux2, &cfg );

    Delay_ms ( 100 );
    log_printf( &logger, "I2C MUX 2 Click driver init\r\n");
    log_printf( &logger, "---------------------------------------\r\n");
    Delay_ms ( 100 );

    i2cmux2_hw_reset( &i2cmux2 );
    log_printf( &logger, "I2C MUX 2 Click HW reset\r\n");
    log_printf( &logger, "---------------------------------------\r\n");
    Delay_ms ( 100 );
}
```

### Application Task

> In this example, we read the device ID register of the connected Click boards.
> Channel 0 : 6DOF IMU 11 Click [slave address: 0x0E; reg: 0x00; id val.: 0x2D],
> Channel 1 : Altitude Click    [slave address: 0x60; reg: 0x0C; id val.: 0xC4],
> Channel 2 : 6DOF IMU 9 Click  [slave address: 0x69; reg: 0x75; id val.: 0xA9],
> Channel 3 : Compass 3 Click   [slave address: 0x30; reg: 0x2F; id val.: 0x0C].
> All data logs write on USB UART changes every 2 sec.

```c
void application_task ( void )
{
    log_printf( &logger, "  CH  |   ID   |  INT \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    
#ifdef ENABLE_CHANNEL_0
    // SET CHANNEL 0: 6DOF IMU 11 Click
    i2cmux2_set_channel( &i2cmux2, I2CMUX2_CMD_SET_CH_0, 0x0E );
    Delay_ms ( 100 );
    i2cmux2_generic_read( &i2cmux2, 0x00, &rx_data, 1 );
    display_log( I2CMUX2_CMD_SET_CH_0 );
#endif
    
#ifdef ENABLE_CHANNEL_1
    // SET CHANNEL 1: Altitude Click
    i2cmux2_set_channel( &i2cmux2, I2CMUX2_CMD_SET_CH_1, 0x60 );
    Delay_ms ( 100 );
    i2cmux2_generic_read( &i2cmux2, 0x0C, &rx_data, 1 );
    display_log( I2CMUX2_CMD_SET_CH_1 );
#endif
    
#ifdef ENABLE_CHANNEL_2
    // SET CHANNEL 2: 6DOF IMU 9 Click
    i2cmux2_set_channel( &i2cmux2, I2CMUX2_CMD_SET_CH_2, 0x69 );
    Delay_ms ( 100 );
    i2cmux2_generic_read( &i2cmux2, 0x75, &rx_data, 1 );
    display_log( I2CMUX2_CMD_SET_CH_2 );
#endif

#ifdef ENABLE_CHANNEL_3
    // SET CHANNEL 3: Compass 3 Click
    i2cmux2_set_channel( &i2cmux2, I2CMUX2_CMD_SET_CH_3, 0x30 );
    Delay_ms ( 100 );
    i2cmux2_generic_read( &i2cmux2, 0x2F, &rx_data, 1 );
    display_log( I2CMUX2_CMD_SET_CH_3 );
#endif

    log_printf( &logger, "----------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Disable all unconnected channels from the example using ENABLE_CHANNEL_x macros below to prevent the I2C bus from blocking waiting for a device response.

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
