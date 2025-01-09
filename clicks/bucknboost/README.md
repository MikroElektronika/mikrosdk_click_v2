
---
# Buck n Boost Click

> [Buck n Boost Click](https://www.mikroe.com/?pid_product=MIKROE-4354) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4354&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This application demonstrates the use of Buck n Boost Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BucknBoost

### Example Key Functions

- `bucknboost_cfg_setup` Config Object Initialization function.
```c
void bucknboost_cfg_setup ( bucknboost_cfg_t *cfg );
```

- `bucknboost_init` Initialization function.
```c
err_t bucknboost_init ( bucknboost_t *ctx, bucknboost_cfg_t *cfg );
```

- `bucknboost_default_cfg` Click Default Configuration function.
```c
void bucknboost_default_cfg ( bucknboost_t *ctx );
```

- `bucknboost_set_buck_out_voltage` This function sets the output voltage of a desired buck channel.
```c
err_t bucknboost_set_buck_out_voltage ( bucknboost_t *ctx, uint8_t ch_num, uint8_t data_in );
```

- `bucknboost_set_boost_out_voltage` This function sets the output voltage of the boost channel (CH6).
```c
err_t bucknboost_set_boost_out_voltage ( bucknboost_t *ctx, uint8_t data_in );
```

- `bucknboost_get_status` This function reads Power Good, EEPROM, and Overcurrent status registers.
```c
err_t bucknboost_get_status ( bucknboost_t *ctx, bucknboost_status_t *st_data );
```

### Application Init

> Initializes the driver and sets the Click default configuration.
> The default config enables the Click board and limits the current of all outputs to 1100mA.
> It also sets the default voltages of all channels which are the following:
> OUT1 - 1.8V, OUT2 - 1.1V, OUT3 - 1.8V, OUT4 - 1.05V, OUT5 - 1.25V, OUT6 - 12V 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bucknboost_cfg_t bucknboost_cfg;  /**< Click config object. */

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

    bucknboost_cfg_setup( &bucknboost_cfg );
    BUCKNBOOST_MAP_MIKROBUS( bucknboost_cfg, MIKROBUS_1 );
    
    err_t init_flag = bucknboost_init( &bucknboost, &bucknboost_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag = bucknboost_default_cfg ( &bucknboost );
    if ( init_flag == BUCKNBOOST_ERROR ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Iterates through the entire range of Buck voltages for Buck 1 output starting from the maximal output.
> It also checks the Power Good and Overcurrent status.
> All data is being displayed on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    bucknboost_status_t status_data;
    
    for ( uint8_t cnt = BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_3300mV; 
          cnt <= BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_800mV; cnt++ )
    {
        err_t error_check = bucknboost_set_buck_out_voltage( &bucknboost, 
                                                             BUCKNBOOST_OUTPUT_CH_1, 
                                                             cnt );
        if ( error_check == BUCKNBOOST_ERROR )
        {
            log_error( &logger, " Setting Buck 1 Output Voltage." );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
        else
        {
            log_printf( &logger, " Buck 1 Output Voltage set to %u mV.\r\n", 3300 - cnt * 50 );
            
            bucknboost_get_status( &bucknboost, &status_data );
            log_printf( &logger, " Power Good status -" );
            if ( status_data.power_good == BUCKNBOOST_PGOOD_ALL_MASK )
            {
                log_printf( &logger, " Valid!\r\n" );
            }
            else
            {
                log_printf( &logger, " Not Valid! - Mask: 0x%.2X\r\n", ( uint16_t ) status_data.power_good );
            }
            
            log_printf( &logger, " Overcurrent status -" );
            if ( status_data.power_good == BUCKNBOOST_PGOOD_ALL_MASK )
            {
                log_printf( &logger, " No Fault!\r\n" );
            }
            else
            {
                log_printf( &logger, " Fault! - Mask: 0x%.2X\r\n", ( uint16_t ) status_data.overcurrent_fault );
            }
            log_printf( &logger, "-----------------------------------\r\n" );
        }
        Delay_ms ( 1000 );
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
