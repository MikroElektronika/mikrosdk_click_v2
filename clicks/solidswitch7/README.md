
---
# SolidSwitch 7 Click

> [SolidSwitch 7 Click](https://www.mikroe.com/?pid_product=MIKROE-6721) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6721&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of the SolidSwitch 7 Click board by 
periodically enabling and disabling the output channel while monitoring 
and logging the load current.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SolidSwitch7

### Example Key Functions

- `solidswitch7_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void solidswitch7_cfg_setup ( solidswitch7_cfg_t *cfg );
```

- `solidswitch7_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t solidswitch7_init ( solidswitch7_t *ctx, solidswitch7_cfg_t *cfg );
```

- `solidswitch7_output_enable` This function sets the IN0 pin to high logic level to enable the output stage.
```c
void solidswitch7_output_enable ( solidswitch7_t *ctx );
```

- `solidswitch7_output_disable` This function sets the IN0 pin to low logic level to disable the output stage.
```c
void solidswitch7_output_disable ( solidswitch7_t *ctx );
```

- `solidswitch7_read_current` This function reads the analog voltage from the diagnostic output and calculates the load current.
```c
err_t solidswitch7_read_current ( solidswitch7_t *ctx, float *current );
```

### Application Init

> Initializes the logger and the Click board, enables analog diagnostics and automatic restart features.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch7_cfg_t solidswitch7_cfg;  /**< Click config object. */

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
    solidswitch7_cfg_setup( &solidswitch7_cfg );
    SOLIDSWITCH7_MAP_MIKROBUS( solidswitch7_cfg, MIKROBUS_POSITION_SOLIDSWITCH7 );
    err_t init_flag = solidswitch7_init( &solidswitch7, &solidswitch7_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    solidswitch7_an_diag_enable ( &solidswitch7 );
    solidswitch7_auto_rst_enable ( &solidswitch7 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Alternately enables and disables the output every few seconds, and logs the measured current in each state using the USB UART.

```c
void application_task ( void )
{
    float current = 0;
    log_printf( &logger, " Enable VOUT\r\n" );
    solidswitch7_output_enable ( &solidswitch7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( SOLIDSWITCH7_OK == solidswitch7_read_current ( &solidswitch7, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f A\r\n\n", current );
    }
    Delay_ms ( 1000 );
    log_printf( &logger, " Disable VOUT\r\n" );
    solidswitch7_output_disable ( &solidswitch7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( SOLIDSWITCH7_OK == solidswitch7_read_current ( &solidswitch7, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f A\r\n\n", current );
    }
    Delay_ms ( 1000 );
}
```

### Note

> Ensure proper load and supply are connected to observe current change during output toggling.

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
