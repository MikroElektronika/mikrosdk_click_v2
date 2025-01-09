
---
# Boost-INV 3 Click

> [Boost-INV 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5755) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5755&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Boost-INV 3 Click driver.
  This driver provides the functions to set the output voltage treshold.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BoostINV3

### Example Key Functions

- `boostinv3_cfg_setup` Config Object Initialization function.
```c
void boostinv3_cfg_setup ( boostinv3_cfg_t *cfg );
```

- `boostinv3_init` Initialization function.
```c
err_t boostinv3_init ( boostinv3_t *ctx, boostinv3_cfg_t *cfg );
```

- `boostinv3_default_cfg` Click Default Configuration function.
```c
err_t boostinv3_default_cfg ( boostinv3_t *ctx );
```

- `boostinv3_set_enp` Boost-INV 3 set ENP pin state function.
```c
void boostinv3_set_enp ( boostinv3_t *ctx, uint8_t out_state );
```

- `boostinv3_set_pos_out` Boost-INV 3 set positive output voltage function.
```c
err_t boostinv3_set_pos_out ( boostinv3_t *ctx, uint8_t out_val );
```

- `boostinv3_set_neg_out` Boost-INV 3 set negative output voltage function.
```c
err_t boostinv3_set_neg_out ( boostinv3_t *ctx, uint8_t out_val );
```

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization, default settings enable the positive and 
  negative output and sets the output voltage to 4 V.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boostinv3_cfg_t boostinv3_cfg;  /**< Click config object. */

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
    boostinv3_cfg_setup( &boostinv3_cfg );
    BOOSTINV3_MAP_MIKROBUS( boostinv3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == boostinv3_init( &boostinv3, &boostinv3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( BOOSTINV3_ERROR == boostinv3_default_cfg ( &boostinv3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Boost-INV 3 Click board by changing 
 * output voltage every 5 seconds starting from 4 V up to 6 V.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = BOOSTINV3_OUT_VOLTAGE_4V; n_cnt <= BOOSTINV3_OUT_VOLTAGE_6V; n_cnt++ )
    {
        err_t error_flag = boostinv3_set_pos_out( &boostinv3, n_cnt );
        error_flag |= boostinv3_set_neg_out( &boostinv3, n_cnt );
        if ( BOOSTINV3_OK == error_flag )
        {
            log_printf( &logger, " Set positive and negative voltage to %.1f V \r\n", 
                        ( BOOSTINV3_MIN_VOL_LVL + n_cnt * BOOSTINV3_INCREMENT ) );
        }
        else
        {
            log_printf( &logger, " Error has occurred!!! \r\n" );
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
