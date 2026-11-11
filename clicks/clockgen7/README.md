
---
# Clock Gen 7 Click

> [Clock Gen 7 Click](https://www.mikroe.com/?pid_product=MIKROE-7088) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7088&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jul 2026.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Clock Gen 7 Click board by 
generating a low-jitter output clock (CLK_OUT) locked to a frequency
reference (CLK_IN).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ClockGen7

### Example Key Functions

- `clockgen7_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void clockgen7_cfg_setup ( clockgen7_cfg_t *cfg );
```

- `clockgen7_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t clockgen7_init ( clockgen7_t *ctx, clockgen7_cfg_t *cfg );
```

- `clockgen7_default_cfg` This function executes a default configuration of Clock Gen 7 Click board.
```c
err_t clockgen7_default_cfg ( clockgen7_t *ctx );
```

- `clockgen7_set_clk_in_freq` This function sets the CLK_IN frequency generated on the CIN pin.
```c
err_t clockgen7_set_clk_in_freq ( clockgen7_t *ctx, uint32_t freq );
```

- `clockgen7_set_ratio` This function sets the PLL ratio that defines the CLK_OUT to CLK_IN multiplication factor.
```c
err_t clockgen7_set_ratio ( clockgen7_t *ctx, float ratio );
```

- `clockgen7_pll_enable` This function enables the PLL by setting both PLL enable bits.
```c
err_t clockgen7_pll_enable ( clockgen7_t *ctx );
```

### Application Init

> Initializes the driver, performs the Click default configuration
and sets the CLK_IN reference to 48 kHz.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    clockgen7_cfg_t clockgen7_cfg;  /**< Click config object. */

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
    clockgen7_cfg_setup( &clockgen7_cfg );
    CLOCKGEN7_MAP_MIKROBUS( clockgen7_cfg, MIKROBUS_POSITION_CLOCKGEN7 );
    err_t init_flag = clockgen7_init( &clockgen7, &clockgen7_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CLOCKGEN7_ERROR == clockgen7_default_cfg ( &clockgen7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    clockgen7_set_clk_in_freq( &clockgen7, CLOCKGEN7_CLK_IN_FREQ );
    log_printf( &logger, " CLK_IN reference: %lu Hz\r\n", ( uint32_t ) CLOCKGEN7_CLK_IN_FREQ );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Cycles through several PLL ratios every 3 seconds while keeping CLK_IN fixed,
and logs the resulting CLK_OUT frequency.

```c
void application_task ( void )
{
    clockgen7_apply_ratio( CLOCKGEN7_RATIO_STEP_1 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    clockgen7_apply_ratio( CLOCKGEN7_RATIO_STEP_2 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    clockgen7_apply_ratio( CLOCKGEN7_RATIO_STEP_3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> The CS2501 SPI control port is write-only, so communication check and lock
status read-back are available over the I2C interface only.

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
