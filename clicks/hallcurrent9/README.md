
---
# Hall Current 9 Click

> [Hall Current 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4466) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4466&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for Hall Current 9 Click driver.
> The library contains drivers for measuring ADC values 
> and for calculation current.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent9

### Example Key Functions

- `hallcurrent9_cfg_setup` Config Object Initialization function.
```c
void hallcurrent9_cfg_setup ( hallcurrent9_cfg_t *cfg );
```

- `hallcurrent9_init` Initialization function.
```c
err_t hallcurrent9_init ( hallcurrent9_t *ctx, hallcurrent9_cfg_t *cfg );
```

- `hallcurrent9_default_cfg` Click Default Configuration function.
```c
void hallcurrent9_default_cfg ( hallcurrent9_t *ctx );
```

- `hallcurrent9_read_adc` Hall Current 9 I2C ADC reading function.
```c
err_t hallcurrent9_read_adc ( hallcurrent9_t *ctx, uint16_t *read_adc );
```

- `hallcurrent9_set_calibration` Hall Current 9 set calibration function.
```c
err_t hallcurrent9_set_calibration ( hallcurrent9_t *ctx, hallcurrent9_calibration_data_t *adc_val );
```

- `hallcurrent9_get_current` Hall Current 9 get current function.
```c
float hallcurrent9_get_current ( hallcurrent9_t *ctx, hallcurrent9_calibration_data_t *adc_val );
```

### Application Init

> Initializes I2C driver and triggers the built-in calibration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    hallcurrent9_cfg_t hallcurrent9_cfg;  /**< Click config object.  */

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
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "   Hall Current 9 Click   \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    hallcurrent9_cfg_setup( &hallcurrent9_cfg );
    HALLCURRENT9_MAP_MIKROBUS( hallcurrent9_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent9_init( &hallcurrent9, &hallcurrent9_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "        Calibration        \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "> Turn OFF the Power unit <\r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "  In the following 5 sec.  \r\n" );
    log_printf( &logger, " turn OFF the Power Supply \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Start calibration    \r\n" );
    
    if ( hallcurrent9_set_calibration( &hallcurrent9, &avg_adc_data ) == HALLCURRENT9_OK ) {
        log_printf( &logger, "---------------------------\r\n" );
        log_printf( &logger, "    Calibration  Done    \r\n" );
        Delay_ms ( 1000 );    
    }
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "    Start measurements :   \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
}
```

### Application Task

> This is an example that demonstrates the use of the Hall Current 9 Click board.
> In this example, we read and display the ADC and current ( mA ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{   
    log_printf( &logger, "--------------------------\r\n", adc_data );
    hallcurrent9_read_adc( &hallcurrent9, &adc_data );
    log_printf( &logger, "   ADC     : %d \r\n", adc_data );

    current = hallcurrent9_get_current( &hallcurrent9, &avg_adc_data );
    log_printf( &logger, "   Current : %.2f mA \r\n", current );
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
