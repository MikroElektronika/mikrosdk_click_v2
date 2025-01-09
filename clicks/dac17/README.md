
---
# DAC 17 Click

> [DAC 17 Click](https://www.mikroe.com/?pid_product=MIKROE-6059) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6059&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of DAC 17 Click board by changing the voltage level on the output channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC17

### Example Key Functions

- `dac17_cfg_setup` Config Object Initialization function.
```c
void dac17_cfg_setup ( dac17_cfg_t *cfg );
```

- `dac17_init` Initialization function.
```c
err_t dac17_init ( dac17_t *ctx, dac17_cfg_t *cfg );
```

- `dac17_default_cfg` Click Default Configuration function.
```c
err_t dac17_default_cfg ( dac17_t *ctx );
```

- `dac17_send_command` This function is used to send specific command of the DAC 17 Click board.
```c
err_t dac17_send_command ( dac17_t *ctx, uint8_t command, uint8_t ch_sel, uint16_t data_in );
```

- `dac17_set_dac_output` This function is used to set output level of the sellected channel of the DAC 17 Click board.
```c
err_t dac17_set_dac_output ( dac17_t *ctx, uint8_t ch_sel, uint16_t dac_data );
```

- `dac17_set_all_dac_output` This function is used to set output level of the DAC 17 Click board.
```c
err_t dac17_set_all_dac_output ( dac17_t *ctx, uint16_t dac_data );
```

### Application Init

> Initializes the driver and performs Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac17_cfg_t dac17_cfg;  /**< Click config object. */

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
    dac17_cfg_setup( &dac17_cfg );
    DAC17_MAP_MIKROBUS( dac17_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dac17_init( &dac17, &dac17_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC17_ERROR == dac17_default_cfg ( &dac17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output channels voltage level starting from full scale ( REF voltage ),  
 to the mid-scale ( half of the REF voltage ), and then to zero every two seconds.

```c
void application_task ( void )
{
    #define DAC17_OUTPUT_ZERO           0x0000u
    #define DAC17_OUTPUT_MID_SCALE      0x0800u
    #define DAC17_OUTPUT_FULL_SCALE     0x0FFFu

    log_printf( &logger, " Setting all channels to full scale output \r\n" );
    dac17_set_all_dac_output( &dac17, DAC17_OUTPUT_FULL_SCALE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Setting all channels outputs to zero \r\n" );
    dac17_set_all_dac_output( &dac17, DAC17_OUTPUT_ZERO );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Setting all channels outputs to mid scale \r\n" );
    dac17_set_all_dac_output( &dac17, DAC17_OUTPUT_MID_SCALE );
    Delay_ms ( 1000 );
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
