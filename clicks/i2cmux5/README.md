
---
# I2C MUX 5 Click

> [I2C MUX 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4453) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4453&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This app reads "Who am I" and "Status" register of the connected Click boards to the I2C MUX 5 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cMux5

### Example Key Functions

- `i2cmux5_cfg_setup` Config Object Initialization function.
```c
void i2cmux5_cfg_setup ( i2cmux5_cfg_t *cfg );
```

- `i2cmux5_init` Initialization function.
```c
err_t i2cmux5_init ( i2cmux5_t *ctx, i2cmux5_cfg_t *cfg );
```

- `i2cmux5_default_cfg` Click Default Configuration function.
```c
void i2cmux5_default_cfg ( i2cmux5_t *ctx );
```

- `i2cmux5_generic_write` I2C MUX 5 I2C writing function.
```c
err_t i2cmux5_generic_write ( i2cmux5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );
```

- `i2cmux5_generic_read` I2C MUX 5 I2C reading function.
```c
err_t i2cmux5_generic_read ( i2cmux5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );
```

- `i2cmux5_channel_read_byte` I2C MUX 5 I2C channel reading function.
```c
uint8_t i2cmux5_channel_read_byte ( i2cmux5_t *ctx, uint8_t sel_ch, uint8_t ch_slave_addr, uint8_t reg );
```

### Application Init

> Initializes I2C driver, set the default configuration and start to write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cmux5_cfg_t i2cmux5_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    i2cmux5_cfg_setup( &i2cmux5_cfg );
    I2CMUX5_MAP_MIKROBUS( i2cmux5_cfg, MIKROBUS_1 );
    err_t init_flag = i2cmux5_init( &i2cmux5, &i2cmux5_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    i2cmux5_default_cfg ( &i2cmux5 );
    log_info( &logger, " Application Task \r\n" );
    Delay_ms ( 100 );
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "        I2C MUX 5 Click        \r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    
}
```

### Application Task

> This is an example that demonstrates the use of the I2C MUX 5 Click board.
> In this example, we read "Who am I" ( or "Status" ) register
> of the connected Click boards to the I2C MUX 5 Click.
> Channel 1 : 6DOF IMU 9 Click  [slave address: 0x69; reg: 0x75; ID val.: 0xA9],
> Channel 2 : 6DOF IMU 11 Click [slave address: 0x0E; reg: 0x00; ID val.: 0x2D],
> Channel 3 : RTC 10 Click      [slave address: 0x68; reg: 0x0F; St val.: 0x88],
> Channel 4 : Accel 10 Click    [slave address: 0x18; reg: 0x0F; ID val.: 0x44].
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{   
    
    rx_data = i2cmux5_channel_read_byte( &i2cmux5, I2CMUX5_CH_1, I2CMUX5_SET_6DOF_IMU_9_ADDR, 0x75 );
    Delay_ms ( 1000 );
    log_printf( &logger, " CH-1 6DOF IMU 9 Click  : 0x%X \r\n", ( uint16_t )rx_data );
    
    rx_data = i2cmux5_channel_read_byte( &i2cmux5, I2CMUX5_CH_2, I2CMUX5_SET_6DOF_IMU_11_ADDR, 0x00 );
    Delay_ms ( 1000 );
    log_printf( &logger, " CH-2 6DOF IMU 11 Click : 0x%X \r\n", ( uint16_t )rx_data );
    
    rx_data = i2cmux5_channel_read_byte( &i2cmux5, I2CMUX5_CH_3, I2CMUX5_SET_RTC_10_ADDR, 0x0F ); 
    Delay_ms ( 1000 );
    log_printf( &logger, " CH-3 RTC 10 Click      : 0x%X \r\n", ( uint16_t )rx_data ); 
    
    rx_data = i2cmux5_channel_read_byte( &i2cmux5, I2CMUX5_CH_4, I2CMUX5_SET_ACCEL_10_ADDR, 0x0F );
    Delay_ms ( 1000 );
    log_printf( &logger, " CH-4 Accel 10 Click    : 0x%X \r\n", ( uint16_t )rx_data );
    log_printf( &logger, "-------------------------------\r\n" );
        
    i2cmux5_hw_reset( &i2cmux5 );
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
