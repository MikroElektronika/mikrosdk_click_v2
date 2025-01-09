
---
# ADAC Click

> [ADAC Click](https://www.mikroe.com/?pid_product=MIKROE-2690) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2690&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases how to initialize, configure and use the ADAC Click module. The Click
  has an ADC and a DAC. An external power supply sets the maximum voltage of the input analog
  signal, which is bound to 2.5 V by default. For the input any external analog signal will
  suffice and a multimeter is needed to read the output on one of the channels.
  
### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADAC

### Example Key Functions

- `adac_cfg_setup` Config Object Initialization function. 
```c
void adac_cfg_setup ( adac_cfg_t *cfg );
``` 
 
- `adac_init` Initialization function. 
```c
err_t adac_init ( adac_t *ctx, adac_cfg_t *cfg );
```

- `adac_default_cfg` Click Default Configuration function. 
```c
void adac_default_cfg ( adac_t *ctx );
```

- `adac_write_dac` This function writes DAC using the I2C serial interface. 
```c
void adac_write_dac ( adac_t *ctx, uint8_t chan, uint8_t msb, uint8_t lsb );
```
 
- `adac_read_adc` This function reads ADC data using the I2C serial interface. 
```c
uint16_t adac_read_adc ( adac_t *ctx, uint8_t *chan );
```

- `adac_set_configuration` This function sets the configuration for the Click module. 
```c
void adac_set_configuration ( adac_t *ctx, uint8_t ptr, uint8_t msb, uint8_t lsb );
```

### Application Init

> This function initializes and configures the Click and logger modules. It does a hardware 
  reset first and after that configures the Click module using default settings. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    adac_cfg_t cfg;

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

    adac_cfg_setup( &cfg );
    ADAC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adac_init( &adac, &cfg );
    Delay_100ms( );
    adac_hardware_reset( &adac );
    Delay_100ms( );
    adac_set_configuration( &adac, ADAC_POWER_REF_CTRL, ADAC_VREF_ON, ADAC_NO_OP );
    Delay_100ms( );
    log_printf( &logger, "\r\n Click module initialized \r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

> This function first writes digital values ranging from 0 to 256 to output channel 3 with a 
  10 millisecond delay between iterations and after that reads analog values from channel 4 
  10 times and displays results in the UART console. 

```c
void application_task ( void )
{
    uint16_t adc_val;
    uint16_t cnt;
    uint8_t chan;

    log_printf( &logger, "\r\n *** DAC : write ***\r\n" );
    adac_set_configuration( &adac, ADAC_DAC_CONFIG, ADAC_NO_OP, ADAC_IO3 );
    Delay_100ms( );

    for ( cnt = 0; cnt < 0xFF; cnt +=4 )
    {
        adac_write_dac( &adac, ADAC_PB_PIN3, cnt / 0x100, cnt % 0x100 );
        Delay_ms ( 10 );
        log_printf( &logger, " > write... \r\n" );
    }
    
    log_printf( &logger, "-------------------\r\n" );
    Delay_ms ( 1000 );

    log_printf( &logger, "\r\n *** ADC : read ***\r\n" );
    adac_set_configuration( &adac, ADAC_ADC_CONFIG, ADAC_NO_OP, ADAC_IO4 );
    Delay_100ms( );
    adac_set_configuration( &adac, ADAC_ADC_SEQUENCE, ADAC_SEQUENCE_ON, ADAC_IO4 );

    for( cnt = 0; cnt < 10; cnt++ )
    {
        adc_val = adac_read_adc( &adac, &chan );
        log_printf( &logger, "   channel : %d\r\n", chan );
        log_printf( &logger, "       val : %d\r\n", adc_val ); 
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    log_printf( &logger, "-------------------\r\n" );
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
