
---
# Solenoid Driver Click

> [Solenoid Driver Click](https://www.mikroe.com/?pid_product=MIKROE-6574) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6574&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Solenoid Driver Click board by 
enabling output channels one by one in a round-robin fashion and parsing 
the diagnostic status after each update. The diagnosis includes 
undervoltage detection, output fault status, and operation mode.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SolenoidDriver

### Example Key Functions

- `solenoiddriver_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void solenoiddriver_cfg_setup ( solenoiddriver_cfg_t *cfg );
```

- `solenoiddriver_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t solenoiddriver_init ( solenoiddriver_t *ctx, solenoiddriver_cfg_t *cfg );
```

- `solenoiddriver_default_cfg` This function executes a default configuration of Solenoid Driver Click board.
```c
err_t solenoiddriver_default_cfg ( solenoiddriver_t *ctx );
```

- `solenoiddriver_set_output` This function sets the desired output control configuration to the output control register.
```c
err_t solenoiddriver_set_output ( solenoiddriver_t *ctx, uint8_t out_ctrl );
```

- `solenoiddriver_clear_latch` This function clears all latch output states via register write.
```c
err_t solenoiddriver_clear_latch ( solenoiddriver_t *ctx );
```

### Application Init

> Initializes the logger and the Click board driver, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solenoiddriver_cfg_t solenoiddriver_cfg;  /**< Click config object. */

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
    solenoiddriver_cfg_setup( &solenoiddriver_cfg );
    SOLENOIDDRIVER_MAP_MIKROBUS( solenoiddriver_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == solenoiddriver_init( &solenoiddriver, &solenoiddriver_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLENOIDDRIVER_ERROR == solenoiddriver_default_cfg ( &solenoiddriver ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sequentially enables each output channel with a 1-second delay, 
checks the diagnostic register, logs operation status, and clears the latch register.

```c
void application_task ( void )
{
    static uint8_t out_en = SOLENOIDDRIVER_OUT_CTRL_EN0;
    if ( SOLENOIDDRIVER_OK == solenoiddriver_set_output ( &solenoiddriver, out_en ) )
    {
        solenoiddriver_parse_diag ( &solenoiddriver );
        log_printf ( &logger, " OUT0: %u\r\n", ( uint16_t ) 
                    ( SOLENOIDDRIVER_OUT_CTRL_EN0 == ( out_en & SOLENOIDDRIVER_OUT_CTRL_EN0 ) ) );
        log_printf ( &logger, " OUT1: %u\r\n", ( uint16_t ) 
                    ( SOLENOIDDRIVER_OUT_CTRL_EN1 == ( out_en & SOLENOIDDRIVER_OUT_CTRL_EN1 ) ) );
        log_printf ( &logger, " OUT2: %u\r\n", ( uint16_t ) 
                    ( SOLENOIDDRIVER_OUT_CTRL_EN2 == ( out_en & SOLENOIDDRIVER_OUT_CTRL_EN2 ) ) );
        log_printf ( &logger, " OUT3: %u\r\n\n", ( uint16_t ) 
                    ( SOLENOIDDRIVER_OUT_CTRL_EN3 == ( out_en & SOLENOIDDRIVER_OUT_CTRL_EN3 ) ) );
        out_en <<= 1;
        if ( out_en > SOLENOIDDRIVER_OUT_CTRL_EN3 )
        {
            out_en = SOLENOIDDRIVER_OUT_CTRL_EN0;
        }
        solenoiddriver_clear_latch ( &solenoiddriver );
    }
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
