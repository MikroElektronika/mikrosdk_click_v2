
---
# I2C Isolator 5 Click

> [I2C Isolator 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5725) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5725&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Apr 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the I2C Isolator 5 Click driver.
  This demo application shows an example of an I2C Isolator 5 Click 
  wired to the VAV Press Click for reading 
  differential pressure and temperature measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CIsolator5

### Example Key Functions

- `i2cisolator5_cfg_setup` Config Object Initialization function.
```c
void i2cisolator5_cfg_setup ( i2cisolator5_cfg_t *cfg );
```

- `i2cisolator5_init` Initialization function.
```c
err_t i2cisolator5_init ( i2cisolator5_t *ctx, i2cisolator5_cfg_t *cfg );
```

- `i2cisolator5_set_slave_address` I2C Isolator 5 set I2C Slave address function.
```c
err_t i2cisolator5_set_slave_address ( i2cisolator5_t *ctx, uint8_t address );
```

- `i2cisolator5_set_outa_state` I2C Isolator 5 set output A state function.
```c
void i2cisolator5_set_outa_state ( i2cisolator5_t *ctx, uint8_t outa_state );
```

- `i2cisolator5_get_ina_state` I2C Isolator 5 get input A state function.
```c
uint8_t i2cisolator5_get_ina_state ( i2cisolator5_t *ctx );
```

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization and default settings, 
  the app set VAV Press Click I2C slave address ( 0x5C ) 
  and enable device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cisolator5_cfg_t i2cisolator5_cfg;  /**< Click config object. */

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
    i2cisolator5_cfg_setup( &i2cisolator5_cfg );
    I2CISOLATOR5_MAP_MIKROBUS( i2cisolator5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cisolator5_init( &i2cisolator5, &i2cisolator5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Set VAV Press Click I2C Slave Address \r\n" );
    i2cisolator5_set_slave_address ( &i2cisolator5, I2CISOLATOR5_VAV_PRESS_DEV_ADDR );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This is an example that shows the use of an I2C Isolator 5 Click board&trade;.
  Logs pressure difference [ Pa ] and temperature [ degree Celsius ] values 
  of the VAV Press Click written to the I2C Isolator 5 Click board&trade;.  
  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    if ( I2CISOLATOR5_OK == i2cisolator5_get_press_and_temp( ) )
    {
        log_printf( &logger, " Diff. Pressure : %.4f Pa \r\n", diff_press );
        log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
        log_printf( &logger, "--------------------------------\r\n" );
    }
    
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
