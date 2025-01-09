
---
# Brushless 30 Click

> [Brushless 30 Click](https://www.mikroe.com/?pid_product=MIKROE-6337) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6337&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This example configures the Brushless 30 Click board and makes it ready for the motor control over 6 PWM input signals.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless30

### Example Key Functions

- `brushless30_cfg_setup` Config Object Initialization function.
```c
void brushless30_cfg_setup ( brushless30_cfg_t *cfg );
```

- `brushless30_init` Initialization function.
```c
err_t brushless30_init ( brushless30_t *ctx, brushless30_cfg_t *cfg );
```

- `brushless30_default_cfg` Click Default Configuration function.
```c
err_t brushless30_default_cfg ( brushless30_t *ctx );
```

- `brushless30_write_reg` This function writes a data word to the selected register by using SPI serial interface.
```c
err_t brushless30_write_reg ( brushless30_t *ctx, uint8_t reg, uint16_t data_in );
```

- `brushless30_read_reg` This function reads a data word from the selected register by using SPI serial interface.
```c
err_t brushless30_read_reg ( brushless30_t *ctx, uint8_t reg, uint16_t *data_out );
```

- `brushless30_get_diag_pin` This function returns the DIAG pin logic state.
```c
uint8_t brushless30_get_diag_pin ( brushless30_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless30_cfg_t brushless30_cfg;  /**< Click config object. */

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
    brushless30_cfg_setup( &brushless30_cfg );
    BRUSHLESS30_MAP_MIKROBUS( brushless30_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == brushless30_init( &brushless30, &brushless30_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS30_ERROR == brushless30_default_cfg ( &brushless30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, " Click is configured successfully.\r\n" );
    log_printf( &logger, " Apply a 6 PWM signals to UVW H/L pins to drive the motor.\r\n" );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Monitors the DIAG pin state, displays the STAT1 and STAT2 registers on the USB UART, and clears the set flags.

```c
void application_task ( void )
{
    uint16_t status = 0;
    if ( !brushless30_get_diag_pin ( &brushless30 ) )
    {
        if ( BRUSHLESS30_OK == brushless30_read_reg ( &brushless30, BRUSHLESS30_REG_STAT1, &status ) )
        {
            if ( status )
            {
                log_printf( &logger, " STAT1: 0x%.4X\r\n", status );
                if ( BRUSHLESS30_OK == brushless30_write_reg ( &brushless30, BRUSHLESS30_REG_STAT1, status ) )
                {
                    log_printf( &logger, " STAT1: cleared\r\n" );
                }
            }
        }
        
        if ( BRUSHLESS30_OK == brushless30_read_reg ( &brushless30, BRUSHLESS30_REG_STAT2, &status ) )
        {
            if ( status )
            {
                log_printf( &logger, " STAT2: 0x%.4X\r\n", status );
                if ( BRUSHLESS30_OK == brushless30_write_reg ( &brushless30, BRUSHLESS30_REG_STAT2, status ) )
                {
                    log_printf( &logger, " STAT2: cleared\r\n" );
                }
            }
        }
        
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
