
---
# AD SWIO 2 Click

> [AD SWIO 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3861) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3861&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This Click is a quad-channel software configurable input/output solution for building 
> and process control application. The AD-SWIO 2 Click contains four 13-bit DACs, one 
> per chanal, and 16-bit Σ-∆ ADC. These options give a lot of flexibility in choosing 
> functionality for analog output, analog input, digital input, resistance temperature 
> detector (RTD), and thermocouple measurements integrated into a single chip solution 
> with a serial peripheral interface (SPI). 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AdSwio2

### Example Key Functions

- `adswio2_cfg_setup` Config Object Initialization function.
```c
void adswio2_cfg_setup ( adswio2_cfg_t *cfg ); 
```

- `adswio2_init` Initialization function.
```c
err_t adswio2_init ( adswio2_t *ctx, adswio2_cfg_t *cfg );
```

- `adswio2_default_cfg` Click Default Configuration function.
```c
void adswio2_default_cfg ( adswio2_t *ctx );
```

- `adswio2_get_conv_results` This function allows user to get the converted results of the selected channel.
```c
adswio2_err_t adswio2_get_conv_results ( adswio2_t *ctx, uint8_t channel, uint16_t *data_out );
```

- `adswio2_status_pin_ready` This function checks the status of the ready pin.
```c
uint8_t adswio2_status_pin_ready ( adswio2_t *ctx );
```

### Application Init

> Performs a hardware reset of the Click board and
> executes a default configuration that enables channel A and sets it to measure voltage
> input in the range from 0V to 10V, with 4800 SPS.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    adswio2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adswio2_cfg_setup( &cfg );
    ADSWIO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adswio2_init( &adswio2, &cfg );
    Delay_ms ( 100 );
    
    adswio2_default_cfg( &adswio2 );
    Delay_ms ( 1000 );

    adswio2_rdy  = DUMMY;
    adswio2_ch_a = DUMMY;
    adswio2_res  = DUMMY;
    adswio2_err  = ADSWIO2_ERR_STATUS_OK;
    log_printf( &logger, " AD-SWIO 2 Click initialization done \r\n");
    log_printf( &logger, "************************************\r\n");
}
```

### Application Task

> Waits for the data ready and then reads the results of ADC conversion from channel A
> and if response is ok, then prints the results on the uart console.

```c
void application_task ( void )
{
    timeout = 0;
    do
    {
        Delay_1ms( );
        timeout++;
        adswio2_rdy = adswio2_status_pin_ready( &adswio2 );
        if ( timeout > 3000 ) 
        {
            timeout = 0;
            log_printf( &logger, " Reinitializing...");
            adswio2_default_cfg( &adswio2 );
            log_printf( &logger, "Done\r\n");
        }
    }
    while ( adswio2_rdy != 0 );
    
    adswio2_err = adswio2_get_conv_results( &adswio2, ADSWIO2_SETUP_CONV_EN_CHA, &adswio2_ch_a );
    
    if ( adswio2_err == ADSWIO2_ERR_STATUS_OK )
    {
        adswio2_res = adswio2_ch_a;
        adswio2_res /= ADSWIO2_RANGE_RESOLUTION;
        adswio2_res *= ADSWIO2_RANGE_VOLT_MV;
        adswio2_ch_a = adswio2_res;

        log_printf( &logger, " Voltage from channel A: %d mV\r\n", adswio2_ch_a );
        
        log_printf( &logger, "-----------------------------------\r\n\r\n" );
        Delay_ms ( 200 );
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
