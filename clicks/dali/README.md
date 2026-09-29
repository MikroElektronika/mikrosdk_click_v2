
---
# DALI Click

> [DALI Click](https://www.mikroe.com/?pid_product=MIKROE-1297) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1297&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of DALI Click for controlling the light level
of DALI control gear and reading its status when an individual short address is selected.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DALI

### Example Key Functions

- `dali_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void dali_cfg_setup ( dali_cfg_t *cfg );
```

- `dali_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t dali_init ( dali_t *ctx, dali_cfg_t *cfg );
```

- `dali_default_cfg` This function executes a default configuration of DALI Click board.
```c
err_t dali_default_cfg ( dali_t *ctx );
```

- `dali_set_level` This function sends a direct arc power control frame to one device, a group, or all control gear.
```c
err_t dali_set_level ( dali_t *ctx, uint8_t address, uint8_t address_type, uint8_t level );
```

- `dali_query` This function sends a query to a short address and immediately reads its backward frame.
```c
err_t dali_query ( dali_t *ctx, uint8_t address, uint8_t command, uint8_t *response );
```

- `dali_get_phy_state` This function reads the logic level of the on-board PHY SEL pushbutton.
```c
uint8_t dali_get_phy_state ( dali_t *ctx );
```

### Application Init

> Initializes the logger and driver, checks that the receive input is idle, and displays the selected addressing mode.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dali_cfg_t dali_cfg;  /**< Click config object. */

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
    dali_cfg_setup( &dali_cfg );
    DALI_MAP_MIKROBUS( dali_cfg, MIKROBUS_POSITION_DALI );
    dali_cfg.rx_sel = APP_RX_SELECTION;
    if ( DALI_OK != dali_init( &dali, &dali_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DALI_OK != dali_default_cfg( &dali ) )
    {
        log_error( &logger, " RX is not idle. Check the INT/ICP jumper and DALI bus wiring." );
        for ( ; ; );
    }

#if ( APP_ADDRESS_TYPE == DALI_ADDRESS_SHORT )
    log_printf( &logger, " Short address: %u | Status readback enabled\r\n", ( uint16_t ) APP_ADDRESS );
#elif ( APP_ADDRESS_TYPE == DALI_ADDRESS_GROUP )
    log_printf( &logger, " Group address: %u | No status readback\r\n", ( uint16_t ) APP_ADDRESS );
#else
    log_printf( &logger, " Broadcast control | No status readback\r\n" );
#endif
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Cycles arc power levels from 0 to 254 in steps of five, with a 250 ms pause after each level.
Displays changes in the PHY SEL pushbutton state.
In short-address mode, queries and displays the actual level and control-gear status after each interval.

```c
void application_task ( void ) 
{
    static uint8_t level = DALI_LEVEL_OFF;
    static uint8_t last_phy_state = DALI_PHY_RELEASED;
    uint8_t phy_state;
    err_t error_flag;
#if ( APP_ADDRESS_TYPE == DALI_ADDRESS_SHORT )
    uint8_t actual_level;
    uint8_t status;
#endif

    // Sample the local button between frames so logging cannot disturb Manchester timing.
    phy_state = dali_get_phy_state( &dali );
    if ( phy_state != last_phy_state )
    {
        log_printf( &logger, " PHY SEL button: %s\r\n", ( DALI_PHY_PRESSED == phy_state ) ? "Pressed" : "Released" );
        last_phy_state = phy_state;
    }

    // DALI control gear applies its own fade time and configured minimum/maximum levels.
    error_flag = dali_set_level( &dali, APP_ADDRESS, APP_ADDRESS_TYPE, level );
    if ( DALI_OK == error_flag )
    {
        log_printf( &logger, " Arc power level sent: %u\r\n", ( uint16_t ) level );
        if ( level == DALI_LEVEL_MAX )
        {
            level = DALI_LEVEL_OFF;
        }
        else if ( level > ( DALI_LEVEL_MAX - APP_LEVEL_STEP ) )
        {
            level = DALI_LEVEL_MAX;
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

#if ( APP_ADDRESS_TYPE == DALI_ADDRESS_SHORT )
    // Query only one commissioned device so multiple backward frames cannot collide.
    if ( DALI_OK == error_flag )
    {
        error_flag = dali_query( &dali, APP_ADDRESS, DALI_CMD_QUERY_ACTUAL_LEVEL, &actual_level );
        if ( DALI_OK == error_flag )
        {
            log_printf( &logger, " Actual arc power level: %u\r\n", ( uint16_t ) actual_level );
            error_flag = dali_query( &dali, APP_ADDRESS, DALI_CMD_QUERY_STATUS, &status );
            if ( DALI_OK == error_flag )
            {
                log_printf( &logger, " Status: 0x%.2X | Lamp: %s | Fade: %s\r\n", ( uint16_t ) status,
                            ( status & DALI_STATUS_LAMP_ON ) ? "ON" : "OFF",
                            ( status & DALI_STATUS_FADE_RUNNING ) ? "Running" : "Idle" );
            }
        }

        if ( DALI_ERROR_TIMEOUT == error_flag )
        {
            log_error( &logger, " No response. Check the commissioned short address and control-gear power." );
        }
        else if ( DALI_OK != error_flag )
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
Set the INT/ICP jumper to match APP_RX_SELECTION and select the MCU logic voltage with the VCC SEL jumper.
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
