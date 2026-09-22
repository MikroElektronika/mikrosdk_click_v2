
---
# BATT Boost 3 Click

> [BATT Boost 3 Click](https://www.mikroe.com/?pid_product=MIKROE-7027) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7027&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jun 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of BATT Boost 3 Click board by configuring
and monitoring the TLV61290 battery front-end boost converter with true-bypass.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BATTBoost3

### Example Key Functions

- `battboost3_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void battboost3_cfg_setup ( battboost3_cfg_t *cfg );
```

- `battboost3_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t battboost3_init ( battboost3_t *ctx, battboost3_cfg_t *cfg );
```

- `battboost3_default_cfg` This function executes a default configuration of BATT Boost 3 Click board.
```c
err_t battboost3_default_cfg ( battboost3_t *ctx );
```

- `battboost3_get_status` This function reads the STATUS register.
```c
err_t battboost3_get_status ( battboost3_t *ctx, uint8_t *status );
```

- `battboost3_set_enable_mode` This function sets the device enable mode via CONFIG register.
```c
err_t battboost3_set_enable_mode ( battboost3_t *ctx, uint8_t enable_mode );
```

- `battboost3_set_output_voltage` This function sets the VOUT floor threshold from 2.35V to 5.00V.
```c
err_t battboost3_set_output_voltage ( battboost3_t *ctx, float vout );
```

### Application Init

> Initializes the driver and performs the Click default configuration,
reads the device ID and displays it via USB UART.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battboost3_cfg_t battboost3_cfg;  /**< Click config object. */

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
    battboost3_cfg_setup( &battboost3_cfg );
    BATTBOOST3_MAP_MIKROBUS( battboost3_cfg, MIKROBUS_POSITION_BATTBOOST3 );
    if ( I2C_MASTER_ERROR == battboost3_init( &battboost3, &battboost3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTBOOST3_ERROR == battboost3_default_cfg ( &battboost3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint8_t device_id = 0;

    if ( BATTBOOST3_OK == battboost3_get_device_id( &battboost3, &device_id ) )
    {
        log_printf( &logger, " Device ID: 0x%.2X\r\n", ( uint16_t ) device_id );
    }
        
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the status register approximately once per second and displays the
power-good state, operating mode, and current-limit or thermal warning flags.

```c
void application_task ( void ) 
{
    uint8_t status = 0;

    if ( BATTBOOST3_OK == battboost3_get_status( &battboost3, &status ) )
    {
        if ( status & BATTBOOST3_STATUS_PGOOD )
        {
            log_printf( &logger, " Power good: Yes\r\n" );
        }
        else
        {
            log_printf( &logger, " Power good: No\r\n" );
        }

        if ( status & BATTBOOST3_STATUS_OPMODE )
        {
            log_printf( &logger, " Operating mode: Boost\r\n" );
        }
        else
        {
            log_printf( &logger, " Operating mode: Bypass\r\n" );
        }

        if ( status & BATTBOOST3_STATUS_TSD )
        {
            log_printf( &logger, " Warning: Thermal shutdown detected.\r\n" );
        }

        if ( status & BATTBOOST3_STATUS_ILIMBST )
        {
            log_printf( &logger, " Warning: Boost current limit detected.\r\n" );
        }

        if ( status & BATTBOOST3_STATUS_ILIMPT )
        {
            log_printf( &logger, " Warning: Bypass current limit detected.\r\n" );
        }

        if ( status & BATTBOOST3_STATUS_FL_LD )
        {
            log_printf( &logger, " Warning: Heavy load/current limit flag detected.\r\n" );
        }
    }
    else
    {
        log_error( &logger, " Failed status read." );
    }
    
    Delay_ms( 1000 );
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
