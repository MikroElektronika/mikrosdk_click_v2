

---
# DAC 7 click

DAC 7 click carries the AD5624R 12-bit buffered Digital-to-Analog Converter that converts 
digital value to the corresponding voltage level using external voltage reference.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dac-7-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Dac7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dac7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dac7_cfg_setup ( dac7_cfg_t *cfg ); 
 
- Initialization function.
> DAC7_RETVAL dac7_init ( dac7_t *ctx, dac7_cfg_t *cfg );

- Click Default Configuration function.
> void dac7_default_cfg ( dac7_t *ctx );

#### Example key functions :

- This function set software reset of selected channel of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board.
> DAC7_RETVAL_T dac7_sw_reset ( dac7_t *ctx );
 
- This function set power mode of selected channel of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board.
> DAC7_RETVAL_T dac7_set_power ( dac7_t *ctx, uint8_t pwr_en, uint8_t sel_ch );

- This function set 12-bit value of 3-bit command definition to the target 3-bit address command of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board.
> DAC7_RETVAL_T dac7_set_ch_voltage ( dac7_t *ctx, uint8_t addr_ch, uint16_t vol_val, uint16_t v_ref_mv );

## Examples Description

> DAC 7 click carries the AD5624R 12-bit buffered Digital-to-Analog Converter 
> that converts digital value to the corresponding voltage level 
> using external voltage reference.

**The demo application is composed of two sections :**

### Application Init 

> Application Init performs Logger and Click initialization. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac7_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    dac7_cfg_setup( &cfg );
    DAC7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac7_init( &dac7, &cfg );
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " ------  DAC 7 Click  ------\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
    
    v_ref_sel = DAC7_VREF_5000mV;

    if ( dac7_sw_reset( &dac7 ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "   Software reset   \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }
    
    Delay_ms ( 500 );
    log_printf( &logger, "--------------------------\r\n\n" );

    
    if ( dac7_set_power( &dac7, DAC7_PWR_ON_ENABLE, DAC7_SELECT_CHANNEL_ALL ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "   All channel Power On   \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );

        for ( ; ; );
    }

    Delay_ms ( 500 );
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " -- Initialization  done. --\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

> In this example, we adjust the DAC output voltage from 1000 mV to 4000 mV 
> for the channels, starting from channel A to channel D 
> and then set the DAC output voltage to 5000 mV for all channels.
> Results are being sent to UART Terminal where you can track their changes.
> All data logs write on USB UART changes every 5 sec.

```c

void application_task ( void )
{
    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_A, 1000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "  Channel A : 1000 mV  \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n\n" );
    
    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_B, 2000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "  Channel B : 2000 mV  \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n\n" );
    
    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_C, 3000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "  Channel C : 3000 mV  \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n\n" );
    
    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_D, 4000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "  Channel D : 4000 mV  \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n\n" );

    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_ALL, 5000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, " All Channels: 5000 mV \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n\n" );
} 

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dac7

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
