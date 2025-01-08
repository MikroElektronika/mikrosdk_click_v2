
---
# GainAMP 3 Click

> [GainAMP 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4800) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4800&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of GainAMP 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GainAMP3

### Example Key Functions

- `gainamp3_cfg_setup` Config Object Initialization function.
```c
void gainamp3_cfg_setup ( gainamp3_cfg_t *cfg );
```

- `gainamp3_init` Initialization function.
```c
err_t gainamp3_init ( gainamp3_t *ctx, gainamp3_cfg_t *cfg );
```

- `gainamp3_default_cfg` Click Default Configuration function.
```c
err_t gainamp3_default_cfg ( gainamp3_t *ctx );
```

- `gainamp3_write_register` This function writes a data byte to the selected register by using SPI serial interface.
```c
err_t gainamp3_write_register ( gainamp3_t *ctx, uint8_t reg, uint8_t data_in );
```

- `gainamp3_set_amplifier_gain` This function sets the amplifier gain level.
```c
err_t gainamp3_set_amplifier_gain ( gainamp3_t *ctx, uint8_t gain );
```

- `gainamp3_set_input_channel` This function sets the input channel.
```c
err_t gainamp3_set_input_channel ( gainamp3_t *ctx, uint8_t channel );
```

### Application Init

> Initializes the driver and performs the Click default configuration which verifies the communication and sets active the input channel 1.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    gainamp3_cfg_t gainamp3_cfg;  /**< Click config object. */

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

    gainamp3_cfg_setup( &gainamp3_cfg );
    GAINAMP3_MAP_MIKROBUS( gainamp3_cfg, MIKROBUS_1 );
    err_t init_flag = gainamp3_init( &gainamp3, &gainamp3_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag = gainamp3_default_cfg ( &gainamp3 );
    if ( GAINAMP3_ERROR == init_flag )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the amplifier gain level every 3 seconds and displays the gain value on the USB UART.

```c
void application_task ( void )
{
    for ( uint8_t cnt = GAINAMP3_GAIN_1_OVER_16; cnt <= GAINAMP3_GAIN_128; cnt++ )
    {
        gainamp3_set_amplifier_gain ( &gainamp3, cnt );
        log_printf( &logger, " Amplifier gain set to " );
        float gain = ( 1 << cnt ) / 16.0;
        
        if ( gain < 1.0 )
        {
            log_printf( &logger, "1/%u\r\n", ( uint16_t ) ( 1.0 / gain ) );
        }
        else
        {
            log_printf( &logger, "%u\r\n", ( uint16_t ) gain );
        }
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

### Note

> VDDH should be within the range from +5V to +30V.
VSSH should be within the range from -5V to -30V.
Input channels should be within the range from GND to VCC selected by the VCC_SEL SMD jumpers.
Gain * Input voltage must not exceed VCC voltage.

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
