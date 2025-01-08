
---
# Nano Power 3 Click

> [Nano Power 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5783) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5783&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Nano Power 3 Click driver.
  This driver provides the functions to set the output voltage treshold.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoPower3

### Example Key Functions

- `nanopower3_cfg_setup` Config Object Initialization function.
```c
void nanopower3_cfg_setup ( nanopower3_cfg_t *cfg );
```

- `nanopower3_init` Initialization function.
```c
err_t nanopower3_init ( nanopower3_t *ctx, nanopower3_cfg_t *cfg );
```

- `nanopower3_default_cfg` Click Default Configuration function.
```c
err_t nanopower3_default_cfg ( nanopower3_t *ctx );
```

- `nanopower3_set_ctr_pin` Nano Power 3 set CTRL pin state function.
```c
void nanopower3_set_ctr_pin ( nanopower3_t *ctx, uint8_t pin_state );
```

- `nanopower3_set_wiper_pos` Nano Power 3 set wiper position function.
```c
err_t nanopower3_set_wiper_pos ( nanopower3_t *ctx, uint8_t wiper_pos );
```

- `nanopower3_set_voltage` Nano Power 3 set output voltage function.
```c
err_t nanopower3_set_voltage ( nanopower3_t *ctx, uint8_t out_vol );
```

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization, default settings sets output voltage to 1 V.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nanopower3_cfg_t nanopower3_cfg;  /**< Click config object. */

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
    nanopower3_cfg_setup( &nanopower3_cfg );
    NANOPOWER3_MAP_MIKROBUS( nanopower3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == nanopower3_init( &nanopower3, &nanopower3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NANOPOWER3_ERROR == nanopower3_default_cfg ( &nanopower3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the Nano Power 3 Click board&trade; by changing 
  output voltage every 5 seconds starting from 1 V up to 4.5 V.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = NANOPOWER3_1V_OUT_VOLTAGE; n_cnt <= NANOPOWER3_4V5_OUT_VOLTAGE; n_cnt++ )
    {
        nanopower3_set_voltage( &nanopower3, n_cnt );
        log_printf( &logger, " Selected output is:" );
        print_selected_output_level ( n_cnt );
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
