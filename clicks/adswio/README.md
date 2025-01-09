
---
# AD SWIO Click

> [AD SWIO Click](https://www.mikroe.com/?pid_product=MIKROE-4081) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4081&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This Click provides a fully integrated single chip solution for input and output operation. 
> The AD-SWIO Click contains four 13-bit DACs, one per chanal, and 16-bit Σ-∆ ADC. 
> These options give a lot of flexibility in choosing functionality for analog output, 
> analog input, digital input, resistance temperature detector (RTD), and thermocouple 
> measurements integrated into a single chip solution with a serial peripheral interface (SPI)

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AdSwio

### Example Key Functions

- `adswio_cfg_setup` Config Object Initialization function. 
```c
void adswio_cfg_setup ( adswio_cfg_t *cfg );
``` 
 
- `adswio_init` Initialization function. 
```c
err_t adswio_init ( adswio_t *ctx, adswio_cfg_t *cfg );
```

- `adswio_default_cfg` Click Default Configuration function. 
```c
void adswio_default_cfg ( adswio_t *ctx );
```

- `adswio_status_pin_ready` This function checks the status of the ready pin. 
```c
uint8_t adswio_status_pin_ready ( adswio_t *ctx );
```
 
- `adswio_get_conv_results` This function allows user to get the converted results of the selected channel. 
```c
adswio_err_t adswio_get_conv_results ( adswio_t *ctx, uint8_t channel, uint16_t *data_out );
```

### Application Init

> Performs a hardware reset of the Click board and
> executes a default configuration that enables channel A and sets it to measure voltage
> input in the range from 0V to 10V, with 4800 SPS.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    adswio_cfg_t cfg;

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

    adswio_cfg_setup( &cfg );
    ADSWIO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adswio_init( &adswio, &cfg );
    Delay_ms ( 100 );

    adswio_default_cfg( &adswio );
    Delay_ms ( 1000 );

    adswio_rdy  = DUMMY;
    adswio_ch_a = DUMMY;
    adswio_res  = DUMMY;
    adswio_err  = ADSWIO_ERR_STATUS_OK;

    log_printf( &logger, " AD-SWIO Click initialization done \r\n");
    log_printf( &logger, "************************************\r\n");
}
```

### Application Task

> Waits for the data ready and then reads the results of ADC conversion from channel A
> and if response is ok, then prints the results on the uart console.

```c
void application_task ( void )
{
    uint16_t timeout = 0;
    do
    {
        Delay_1ms( );
        timeout++;
        adswio_rdy = adswio_status_pin_ready( &adswio );
        if ( timeout > 3000 ) 
        {
            timeout = 0;
            log_printf( &logger, " Reinitializing...");
            adswio_default_cfg( &adswio );
            log_printf( &logger, "Done\r\n");
        }
    }
    while ( adswio_rdy != 0 );

    adswio_err = adswio_get_conv_results( &adswio, ADSWIO_SETUP_CONV_EN_CHA, &adswio_ch_a );

    if ( adswio_err == ADSWIO_ERR_STATUS_OK )
    {
        adswio_res = adswio_ch_a;
        adswio_res /= ADSWIO_RANGE_RESOLUTION;
        adswio_res *= ADSWIO_RANGE_VOLT_MV;
        adswio_ch_a = adswio_res;

        log_printf( &logger, " Voltage from channel A: %d mV\r\n", adswio_ch_a );
        
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
