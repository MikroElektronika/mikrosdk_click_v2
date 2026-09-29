
---
# DALI 2 Click

> [DALI 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2672) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2672&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of DALI 2 Click for controlling the light level
of DALI control gear and reading its status when an individual short address is selected.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DALI2

### Example Key Functions

- `dali2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void dali2_cfg_setup ( dali2_cfg_t *cfg );
```

- `dali2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t dali2_init ( dali2_t *ctx, dali2_cfg_t *cfg );
```

- `dali2_default_cfg` This function releases TX and checks that the powered DALI bus is idle.
```c
err_t dali2_default_cfg ( dali2_t *ctx );
```

- `dali2_set_level` This function sends a direct arc power control frame to one device, a group, or all control gear.
```c
err_t dali2_set_level ( dali2_t *ctx, uint8_t address, uint8_t address_type, uint8_t level );
```

- `dali2_send_command` This function encodes the selected destination and sends one command frame.
```c
err_t dali2_send_command ( dali2_t *ctx, uint8_t address, uint8_t address_type, uint8_t command );
```

- `dali2_query` This function sends a query to a short address and immediately reads its backward frame.
```c
err_t dali2_query ( dali2_t *ctx, uint8_t address, uint8_t command, uint8_t *response );
```

### Application Init

> Initializes the logger and driver, checks that the DALI bus is idle, and displays the selected addressing mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dali2_cfg_t dali2_cfg;  /**< Click config object. */

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
    dali2_cfg_setup( &dali2_cfg );
    DALI2_MAP_MIKROBUS( dali2_cfg, MIKROBUS_POSITION_DALI2 );
    if ( DALI2_OK != dali2_init( &dali2, &dali2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DALI2_OK != dali2_default_cfg( &dali2 ) )
    {
        log_error( &logger, " Bus is not idle. Check the DALI bus power supply and wiring." );
        for ( ; ; );
    }

#if ( APP_ADDRESS_TYPE == DALI2_ADDRESS_SHORT )
    log_printf( &logger, " Short address: %u | Status readback enabled\r\n", ( uint16_t ) APP_ADDRESS );
#elif ( APP_ADDRESS_TYPE == DALI2_ADDRESS_GROUP )
    log_printf( &logger, " Group address: %u | No status readback\r\n", ( uint16_t ) APP_ADDRESS );
#else
    log_printf( &logger, " Broadcast control | No status readback\r\n" );
#endif
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Cycles through all arc power levels from 0 to 254, increasing by five levels every 250 ms.
In short-address mode, queries and displays the actual level and control-gear status after each interval.

```c
void application_task ( void )
{
    static uint8_t level = DALI2_LEVEL_OFF;
    err_t error_flag;
#if ( APP_ADDRESS_TYPE == DALI2_ADDRESS_SHORT )
    uint8_t actual_level;
    uint8_t status;
#endif

    // DALI control gear applies its own fade time and configured minimum/maximum levels.
    error_flag = dali2_set_level( &dali2, APP_ADDRESS, APP_ADDRESS_TYPE, level );
    if ( DALI2_OK == error_flag )
    {
        log_printf( &logger, " Arc power level sent: %u\r\n", ( uint16_t ) level );
        if ( level == DALI2_LEVEL_MAX )
        {
            level = DALI2_LEVEL_OFF;
        }
        else if ( level > ( DALI2_LEVEL_MAX - APP_LEVEL_STEP ) )
        {
            level = DALI2_LEVEL_MAX;
        }
        else
        {
            level += APP_LEVEL_STEP;
        }
    }
    else
    {
        log_error( &logger, " Set arc power level: %d", ( int16_t ) error_flag );
    }
    Delay_ms( APP_STEP_INTERVAL_MS );

#if ( APP_ADDRESS_TYPE == DALI2_ADDRESS_SHORT )
    // Query only one commissioned device so multiple backward frames cannot collide.
    if ( DALI2_OK == error_flag )
    {
        error_flag = dali2_query( &dali2, APP_ADDRESS, DALI2_CMD_QUERY_ACTUAL_LEVEL, &actual_level );
        if ( DALI2_OK == error_flag )
        {
            log_printf( &logger, " Actual arc power level: %u\r\n", ( uint16_t ) actual_level );
            error_flag = dali2_query( &dali2, APP_ADDRESS, DALI2_CMD_QUERY_STATUS, &status );
            if ( DALI2_OK == error_flag )
            {
                log_printf( &logger, " Status: 0x%.2X | Lamp: %s | Fade: %s\r\n", ( uint16_t ) status,
                            ( status & DALI2_STATUS_LAMP_ON ) ? "ON" : "OFF",
                            ( status & DALI2_STATUS_FADE_RUNNING ) ? "Running" : "Idle" );
            }
        }

        if ( DALI2_ERROR_TIMEOUT == error_flag )
        {
            log_error( &logger, " No response. Check the commissioned short address and control-gear power." );
        }
        else if ( DALI2_OK != error_flag )
        {
            log_error( &logger, " Query response: %d", ( int16_t ) error_flag );
        }
    }
#endif
    log_printf( &logger, "\r\n" );
}
```

### Note

> Connect a dedicated, current-limited DALI bus power supply and separately powered DALI control gear.
Broadcast mode controls all connected gear without commissioning. Short addresses and group membership
must be configured beforehand using a DALI commissioning tool; this example does not assign addresses.
Arc power levels are not percentages. Successful transmission does not acknowledge receipt by the control gear.
The blocking GPIO driver is intended for a single master and requires accurate MCU clock/delay settings.
Long interrupt handlers can disturb the Manchester timing. Check the signal timing on the target hardware.

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
