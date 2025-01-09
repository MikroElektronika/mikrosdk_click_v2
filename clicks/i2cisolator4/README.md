
---
# I2C Isolator 4 Click

> [I2C Isolator 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4675) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4675&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the I2C Isolator 4 Click driver.
> This demo application shows an example of an I2C Isolator 4 Click 
> wired to the VAV Press Click for reading 
> differential pressure and temperature measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cIsolator4

### Example Key Functions

- `i2cisolator4_cfg_setup` Config Object Initialization function.
```c
void i2cisolator4_cfg_setup ( i2cisolator4_cfg_t *cfg );
```

- `i2cisolator4_init` Initialization function.
```c
err_t i2cisolator4_init ( i2cisolator4_t *ctx, i2cisolator4_cfg_t *cfg );
```

- `i2cisolator4_default_cfg` Click Default Configuration function.
```c
err_t i2cisolator4_default_cfg ( i2cisolator4_t *ctx );
```

- `i2cisolator4_generic_write` I2C Isolator 4 I2C writing function.
```c
err_t i2cisolator4_generic_write ( i2cisolator4_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len )
```

- `i2cisolator4_generic_read` I2C Isolator 4 I2C reading function.
```c
err_t i2cisolator4_generic_read ( i2cisolator4_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );
```

- `i2cisolator4_set_slave_address` I2C Isolator 4 set I2C Slave address function.
```c
err_t i2cisolator4_set_slave_address ( i2cisolator4_t *ctx, uint8_t address );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization and default settings, 
> the app set VAV Press Click I2C slave address ( 0x5C ) 
> and enable device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    i2cisolator4_cfg_t i2cisolator4_cfg;  /**< Click config object. */

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

    i2cisolator4_cfg_setup( &i2cisolator4_cfg );
    I2CISOLATOR4_MAP_MIKROBUS( i2cisolator4_cfg, MIKROBUS_1 );
    err_t init_flag = i2cisolator4_init( &i2cisolator4, &i2cisolator4_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, "     Set I2C Slave Address      \r\n" );
    i2cisolator4_set_slave_address ( &i2cisolator4, I2CISOLATOR4_VAV_PRESS_DEV_ADDR );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of an I2C Isolator 4 Click board&trade;.
> Logs pressure difference [ Pa ] and temperature [ degree Celsius ] values 
> of the VAV Press Click wired to the I2C Isolator 4 Click board&trade;.  
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    get_dif_press_and_temp( );
    log_printf( &logger, " Diff. Pressure    : %.4f Pa\r\n", diff_press );
    log_printf( &logger, " Temperature       : %.4f C\r\n", temperature );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Additional Function :

- `get_dif_press_and_temp` Get differential pressure [ Pa ] and temperature [ degree Celsius ] function. 
```c
void get_dif_press_and_temp ( void );
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
