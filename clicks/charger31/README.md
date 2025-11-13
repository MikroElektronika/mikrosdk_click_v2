
---
# Charger 31 Click

> [Charger 31 Click](https://www.mikroe.com/?pid_product=MIKROE-6713) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6713&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the operation of the Charger 31 Click board by monitoring
the status registers and displaying information related to power input, charging state, 
battery presence, and possible faults.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger31

### Example Key Functions

- `charger31_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void charger31_cfg_setup ( charger31_cfg_t *cfg );
```

- `charger31_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t charger31_init ( charger31_t *ctx, charger31_cfg_t *cfg );
```

- `charger31_default_cfg` This function executes a default configuration of Charger 31 Click board.
```c
err_t charger31_default_cfg ( charger31_t *ctx );
```

- `charger31_read_status` This function reads multiple status registers and stores the values into the provided status structure.
```c
err_t charger31_read_status ( charger31_t *ctx, charger31_status_t *status );
```

### Application Init

> Initializes the logger and the Click board, then performs the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger31_cfg_t charger31_cfg;  /**< Click config object. */

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
    charger31_cfg_setup( &charger31_cfg );
    CHARGER31_MAP_MIKROBUS( charger31_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger31_init( &charger31, &charger31_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER31_ERROR == charger31_default_cfg ( &charger31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically reads the status registers and logs messages for VIN readiness, battery presence, charging status, and charging faults.

```c
void application_task ( void )
{
    charger31_status_t status;
    if ( CHARGER31_OK == charger31_read_status ( &charger31, &status ) )
    {
        if ( !( ( status.status_1 & CHARGER31_STATUS1_VIN_GD ) && 
                ( status.status_1 & CHARGER31_STATUS1_VIN_RDY ) ) )
        {
            log_printf ( &logger, " No VIN ready to charge\r\n" );
        }

        if ( status.status_3 & CHARGER31_STATUS3_BATT_MISSING )
        {
            log_printf ( &logger, " No battery detected\r\n" );
        }
        else
        {
            if ( !( status.status_1 & CHARGER31_STATUS1_VSYS_STAT ) )
            {
                log_printf ( &logger, " VBATT is lower than VSYS_MIN\r\n" );
            }

            if ( status.status_5 & CHARGER31_STATUS5_BFET_STAT_DISCHARGING )
            {
                log_printf ( &logger, " The battery is discharging\r\n" );
            }
            else
            {
                log_printf ( &logger, " Charging status: " );
                switch ( status.status_2 & CHARGER31_STATUS2_CHG_STAT_MASK )
                {
                    case CHARGER31_STATUS2_CHG_STAT_NOT_CHARGING:
                    {
                        log_printf ( &logger, "Not charging\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_STAT_TRICKLE_CHG:
                    {
                        log_printf ( &logger, "Trickle charge\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_STAT_PRE_CHG:
                    {
                        log_printf ( &logger, "Pre-charge\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_STAT_FAST_CHG:
                    {
                        log_printf ( &logger, "Fast charge\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_STAT_CV_CHG:
                    {
                        log_printf ( &logger, "Constant-voltage charge\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_STAT_CHG_DONE:
                    {
                        log_printf ( &logger, "Charging is done\r\n" );
                        break;
                    }
                    default:
                    {
                        log_printf ( &logger, "Unknown\r\n" );
                        break;
                    }
                }
            }

            if ( status.status_2 & CHARGER31_STATUS2_CHG_FAULT_MASK )
            {
                log_printf ( &logger, " Charging fault: " );
                switch ( status.status_2 & CHARGER31_STATUS2_CHG_FAULT_MASK )
                {
                    case CHARGER31_STATUS2_CHG_FAULT_IN_OVP:
                    {
                        log_printf ( &logger, "Input OVP\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_FAULT_TIMER:
                    {
                        log_printf ( &logger, "The charge timer has expired\r\n" );
                        break;
                    }
                    case CHARGER31_STATUS2_CHG_FAULT_BATT_OVP:
                    {
                        log_printf ( &logger, "Battery OVP\r\n" );
                        break;
                    }
                    default:
                    {
                        log_printf ( &logger, "Unknown\r\n" );
                        break;
                    }
                }
            }
        }
        log_printf ( &logger, "\r\n" );
    }
    Delay_ms ( 1000 );
}
```

### Note

> Either a battery or VIN USB must be connected to the Click board for the communication to work.

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
