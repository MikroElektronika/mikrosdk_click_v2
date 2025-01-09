
---
# I2C MUX 3 Click

> [I2C MUX 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4262) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4262&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of I2C MUX 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cMux3

### Example Key Functions

- `i2cmux3_cfg_setup` Config Object Initialization function. 
```c
void i2cmux3_cfg_setup ( i2cmux3_cfg_t *cfg );
``` 
 
- `i2cmux3_init` Initialization function. 
```c
err_t i2cmux3_init ( i2cmux3_t *ctx, i2cmux3_cfg_t *cfg );
```

- `i2cmux3_rd_slv` Slave Device Read function. 
```c
void i2cmux3_rd_slv ( i2cmux3_t *ctx, uint8_t slv_sel_adr, uint8_t reg, uint8_t *p_rd_data, uint8_t n_bytes );
```
 
- `i2cmux3_dev_enable` Device enable function. 
```c
void i2cmux3_dev_enable ( i2cmux3_t *ctx, uint8_t stat );
```

- `i2cmux3_hw_rst` Hardware reset function. 
```c
void i2cmux3_hw_rst ( i2cmux3_t *ctx );
```

### Application Init

> Initalizes the driver, preforms hardware reset, then enables channel 0 and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux3_cfg_t cfg;

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

    i2cmux3_cfg_setup( &cfg );
    I2CMUX3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux3_init( &i2cmux3, &cfg );
    Delay_ms ( 100 );
    
    i2cmux3_hw_rst( &i2cmux3 );
    Delay_ms ( 100 );
    i2cmux3_ch_sel( &i2cmux3, 0 );
    log_printf( &logger, " Please connect a 6DOF IMU 12 Click to channel 0\r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads the device ID of a 6DOF IMU 12 Click (dev ID: 0x24) and displays it on the USB UART each second.

```c
void application_task ( void )
{
    i2cmux3_rd_slv ( &i2cmux3, 0x68, 0x00, &id_val, 1 );
    log_printf( &logger, " The Click device ID is:  0x%.2X \r\n", ( uint16_t ) id_val );
    log_printf( &logger, "-------------------------------\r\n" );
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
