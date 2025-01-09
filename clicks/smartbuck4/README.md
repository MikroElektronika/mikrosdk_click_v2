
---
# Smart Buck 4 Click

> [Smart Buck 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5750) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5750&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Smart Buck 4 Click board.
  This driver provides functions for device configurations 
  and for the setting of the output voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartBuck4

### Example Key Functions

- `smartbuck4_cfg_setup` Config Object Initialization function.
```c
void smartbuck4_cfg_setup ( smartbuck4_cfg_t *cfg );
```

- `smartbuck4_init` Initialization function.
```c
err_t smartbuck4_init ( smartbuck4_t *ctx, smartbuck4_cfg_t *cfg );
```

- `smartbuck4_default_cfg` Click Default Configuration function.
```c
err_t smartbuck4_default_cfg ( smartbuck4_t *ctx );
```

- `smartbuck4_en_r40_reg` Smart Buck 4 enable 400A regulator function.
```c
void smartbuck4_en_r40_reg ( smartbuck4_t *ctx );
```

- `smartbuck4_send_command` Smart Buck 4 send command function.
```c
err_t smartbuck4_send_command ( smartbuck4_t *ctx, uint8_t addr, uint8_t data_in );
```

- `smartbuck4_disable_regulators` Smart Buck 4 disable regulators function.
```c
err_t smartbuck4_disable_regulators ( smartbuck4_t *ctx );
```

### Application Init

> Initialization of I2C module and log UART.
  After initializing the driver, the default configuration is executed 
  and the outputs are turned off.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck4_cfg_t smartbuck4_cfg;  /**< Click config object. */

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
    smartbuck4_cfg_setup( &smartbuck4_cfg );
    SMARTBUCK4_MAP_MIKROBUS( smartbuck4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck4_init( &smartbuck4, &smartbuck4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK4_ERROR == smartbuck4_default_cfg ( &smartbuck4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output voltage every 5 seconds, starting from 0.6 V to 3.3V/3.7V 
 depending on the input voltage.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = SMARTBUCK4_REGULATOR_B_600_MV; 
          n_cnt <= SMARTBUCK4_REGULATOR_B_3700_MV; 
          n_cnt += SMARTBUCK4_REGULATOR_B_700_MV )
    {
        err_t error_flag = smartbuck4_send_command( &smartbuck4, SMARTBUCK4_REG_R600B_PROGRAM | 
                                                                 SMARTBUCK4_REG_R400B_PROGRAM | 
                                                                 SMARTBUCK4_REG_LDO_MODE, 
                                                                 SMARTBUCK4_ENABLE_REGULATOR | n_cnt );
        if ( SMARTBUCK4_OK == error_flag )
        {
            log_printf( &logger, " Set output to %d mV. \r\n", 
                        ( SMARTBUCK4_MIN_VOLTAGE + n_cnt * SMARTBUCK4_STEP ) );
        }
        else
        {
            log_error( &logger, " Transmission error occurred." );
            smartbuck4_disable_regulators( &smartbuck4 );
            for ( ; ; );
        }
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
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
