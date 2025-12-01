
---
# PMIC 2 Click

> [PMIC 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6599) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6599&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the PMIC 2 Click board. The board is designed to efficiently 
harvest energy from high-impedance sources such as solar panels. The demo reads and logs 
status flags and battery health indicators, including over-voltage, under-voltage, 
output current protection, and chip status. It also measures and logs the battery charging 
current in microamperes.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PMIC2

### Example Key Functions

- `pmic2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void pmic2_cfg_setup ( pmic2_cfg_t *cfg );
```

- `pmic2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t pmic2_init ( pmic2_t *ctx, pmic2_cfg_t *cfg );
```

- `pmic2_default_cfg` This function executes a default configuration of PMIC 2 Click board.
```c
err_t pmic2_default_cfg ( pmic2_t *ctx );
```

- `pmic2_get_charge_current` This function reads the charge current measurement and calculates the current value in milliamps.
```c
err_t pmic2_get_charge_current ( pmic2_t *ctx, float *current );
```

- `pmic2_get_bok_pin` This function reads the logic state of the BOK pin.
```c
uint8_t pmic2_get_bok_pin ( pmic2_t *ctx );
```

### Application Init

> Initializes the logger and the PMIC 2 Click driver and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pmic2_cfg_t pmic2_cfg;  /**< Click config object. */

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
    pmic2_cfg_setup( &pmic2_cfg );
    PMIC2_MAP_MIKROBUS( pmic2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pmic2_init( &pmic2, &pmic2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PMIC2_ERROR == pmic2_default_cfg ( &pmic2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically checks and logs status flags, battery OK signal, and charging current.

```c
void application_task ( void )
{
    uint8_t flags = 0;
    float current = 0;

    if ( PMIC2_OK == pmic2_read_reg ( &pmic2, PMIC2_REG_FLAGS, &flags ) )
    {
        if ( flags & PMIC2_FLAGS_OVP_OUT_MASK )
        {
            log_printf ( &logger, " OVP_OUT flag: VBAT is above OVP threshold\r\n" );
        }
        if ( flags & PMIC2_FLAGS_LVD_OUT_MASK )
        {
            log_printf ( &logger, " LVD_OUT flag: VBAT is below LVD threshold\r\n" );
        }
        if ( flags & PMIC2_FLAGS_SDF_MASK )
        {
            log_printf ( &logger, " SDF flag: Low battery harvesting current measured\r\n" );
        }
        if ( flags & PMIC2_FLAGS_OCF_MASK )
        {
            log_printf ( &logger, " OCF flag: IBAT is above OCP level\r\n" );
        }
        if ( !( flags & PMIC2_FLAGS_CHIP_OK_MASK ) )
        {
            log_printf ( &logger, " Chip_NOK flag: cold start not done\r\n" );
        }
    }

    if ( !pmic2_get_bok_pin ( &pmic2 ) )
    {
        log_printf ( &logger, " Battery status: NOK\r\n" );
    }

    if ( PMIC2_OK == pmic2_get_charge_current ( &pmic2, &current ) )
    {
        log_printf ( &logger, " Charge current: %.1f uA\r\n\n", current );
    }

    Delay_ms ( 1000 );
}
```

### Note

> Ensure a valid energy harvesting source and energy storage element (e.g. supercap or battery) 
are connected to the board for proper operation.

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
