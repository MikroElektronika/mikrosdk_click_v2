
---
# Balancer 4 Click

> [Balancer 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5271) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5271&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Balancer 4 Click board by configuring the Click board for charging and then reading the status and fault registers.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Balancer4

### Example Key Functions

- `balancer4_cfg_setup` Config Object Initialization function.
```c
void balancer4_cfg_setup ( balancer4_cfg_t *cfg );
```

- `balancer4_init` Initialization function.
```c
err_t balancer4_init ( balancer4_t *ctx, balancer4_cfg_t *cfg );
```

- `balancer4_default_cfg` Click Default Configuration function.
```c
err_t balancer4_default_cfg ( balancer4_t *ctx );
```

- `balancer4_write_register` This function writes a desired data byte to the selected register by using I2C serial interface.
```c
err_t balancer4_write_register ( balancer4_t *ctx, uint8_t reg, uint8_t data_in );
```

- `balancer4_write_and_verify_register` This function writes a desired data byte to the selected register and verifies if is is written correctly by reading it.
```c
err_t balancer4_write_and_verify_register ( balancer4_t *ctx, uint8_t reg, uint8_t data_in );
```

- `balancer4_read_register` This function reads a data byte from the selected register by using I2C serial interface.
```c
err_t balancer4_read_register ( balancer4_t *ctx, uint8_t reg, uint8_t *data_out );
```

### Application Init

> Initializes the driver and configures the Click board for charging.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    balancer4_cfg_t balancer4_cfg;  /**< Click config object. */

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
    balancer4_cfg_setup( &balancer4_cfg );
    BALANCER4_MAP_MIKROBUS( balancer4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == balancer4_init( &balancer4, &balancer4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BALANCER4_ERROR == balancer4_default_cfg ( &balancer4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the status and fault registers on the USB UART every 500ms approximately.

```c
void application_task ( void )
{
    uint8_t status, fault;
    if ( BALANCER4_OK == balancer4_read_register ( &balancer4, BALANCER4_REG_STATUS, &status ) )
    {
        log_printf ( &logger, "\r\n - STATUS - \r\n", status );
        log_printf ( &logger, " Battery status: " );
        if ( status & BALANCER4_STATUS_BATTERY_MISSING )
        {
            log_printf ( &logger, "missing\r\n" );
        }
        else
        {
            log_printf ( &logger, "present\r\n" );
            log_printf ( &logger, " Charging status: " );
            switch ( status & BALANCER4_STATUS_CHG_STAT_MASK )
            {
                case BALANCER4_STATUS_NOT_CHARGING:
                {
                    log_printf ( &logger, "not charging\r\n" );
                    break;
                }
                case BALANCER4_STATUS_PRE_CHARGE:
                {
                    log_printf ( &logger, "pre-charge\r\n" );
                    break;
                }
                case BALANCER4_STATUS_CONSTANT_CHARGE:
                {
                    log_printf ( &logger, "constant current or constant voltage charge\r\n" );
                    break;
                }
                case BALANCER4_STATUS_CHARGING_COMPLETE:
                {
                    log_printf ( &logger, "charging complete\r\n" );
                    break;
                }
            }
        }
    }
    if ( BALANCER4_OK == balancer4_read_register ( &balancer4, BALANCER4_REG_FAULT, &fault ) )
    {
        if ( fault )
        {
            log_printf ( &logger, "\r\n - FAULT - \r\n" );
            if ( fault & BALANCER4_FAULT_WD )
            {
                log_printf ( &logger, " The watchdog timer has expired\r\n" );
            }
            if ( fault & BALANCER4_FAULT_INPUT )
            {
                log_printf ( &logger, " Input OVP has occured\r\n" );
            }
            if ( fault & BALANCER4_FAULT_THERMAL_SD )
            {
                log_printf ( &logger, " Thermal shutdown\r\n" );
            }
            if ( fault & BALANCER4_FAULT_TIMER )
            {
                log_printf ( &logger, " The safety timer has expired\r\n" );
            }
            if ( fault & BALANCER4_FAULT_BAT )
            {
                log_printf ( &logger, " Battery OVP has occured\r\n" );
            }
            switch ( fault & BALANCER4_FAULT_NTC_MASK )
            {
                case BALANCER4_FAULT_NTC_COLD:
                {
                    log_printf ( &logger, " An NTC cold fault has occured\r\n" );
                    break;
                }
                case BALANCER4_FAULT_NTC_COOL:
                {
                    log_printf ( &logger, " An NTC cool fault has occured\r\n" );
                    break;
                }
                case BALANCER4_FAULT_NTC_WARM:
                {
                    log_printf ( &logger, " An NTC warm fault has occured\r\n" );
                    break;
                }
                case BALANCER4_FAULT_NTC_HOT:
                {
                    log_printf ( &logger, " An NTC hot fault has occured\r\n" );
                    break;
                }
            }
        }
    }
    Delay_ms ( 500 );
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
