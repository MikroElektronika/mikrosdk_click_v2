\mainpage Main Page
 
---
# Spectrometer click

Spectrometer Click features an 11-channel spectrometer for spectral identification and color matching applications. This Click board™ features the AS7341 from AMS-AG, whose spectral response is defined in the wavelengths from approximately 350nm to 1000nm.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spectrometer_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/spectrometer-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Spectrometer Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Spectrometer Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void spectrometer_cfg_setup ( spectrometer_cfg_t *cfg ); 
 
- Initialization function.
> SPECTROMETER_RETVAL spectrometer_init ( spectrometer_t *ctx, spectrometer_cfg_t *cfg );

- Default configuration function
> void spectrometer_def_cfg ( spectrometer_t *ctx );


#### Example key functions :

- This function is used to read out channels with SMUX configration 1; F1-F4, Clear.
> void spectrometer_raw_rd_val_mode_1 ( spectrometer_t *ctx, uint8_t *adc_data );
 
- This function is used to read out channels with SMUX configration 2; F5-F8, Clear.
> void spectrometer_raw_rd_val_mode_2 ( spectrometer_t *ctx, uint8_t *adc_data );

- This function is used to detect flicker for 100 and 120 Hz.
> uint8_t spectrometer_flicker_detection ( spectrometer_t *ctx );

## Examples Description

> This Click is an 11-channel spectrometer for spectral identification and color matching. The 
> spectral response is defined in the wavelengths from approximately 350nm to 1000nm. 8 optical 
> channels cover the visible spectrum, one channel can be used to measure near infra-red light
> and one channel is a photo diode without filter (“clear”). The device also integrates a 
> dedicated channel to detect 50Hz or 60Hz ambient light flicker. 

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver, performs safety check and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    spectrometer_cfg_t cfg;

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

    spectrometer_cfg_setup( &cfg );
    SPECTROMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spectrometer_init( &spectrometer, &cfg );
    Delay_ms ( 100 );
    
    spectrometer_generic_read ( &spectrometer, SPECTROMETER_ID, &id_val, 1 );
    if ( id_val == SPECTROMETER_ID_VALUE )
    {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "   Spectrometer  click   \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "     FATAL  ERROR!!!     \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    spectrometer_def_cfg( &spectrometer );
    Delay_ms ( 100 );
}
  
```

### Application Task

> This example shows the capabilities of the Spectrometer click
> by reading out channels with SMUX configrations 1 and 2, detecting 
> flicker for 100 and 120 Hz and displaying data via USART terminal.

```c


void application_task ( void )
{
    spectrometer_raw_rd_val_mode_1( &spectrometer, &adc_buf[ 0 ] );
    
    ch_0 = adc_buf[ 1 ];
    ch_0 <<= 8;
    ch_0 |= adc_buf[ 0 ];
    log_printf( &logger, " ADC0/F1 : %u\r\n", ch_0 );

    ch_1 = adc_buf[ 3 ];
    ch_1 <<= 8;
    ch_1 |= adc_buf[ 2 ];
    log_printf( &logger, " ADC1/F2 : %u\r\n", ch_1 );

    ch_2 = adc_buf[ 5 ];
    ch_2 <<= 8;
    ch_2 |= adc_buf[ 4 ];
    log_printf( &logger, " ADC2/F3 : %u\r\n", ch_2 );

    ch_3 = adc_buf[ 7 ];
    ch_3 <<= 8;
    ch_3 |= adc_buf[ 6 ];
    log_printf( &logger, " ADC3/F4 : %u\r\n", ch_3 );

    ch_4 = adc_buf[ 9 ];
    ch_4 <<= 8;
    ch_4 |= adc_buf[ 8 ];
    log_printf( &logger, " ADC4/Clear : %u\r\n", ch_4 );

    spectrometer_raw_rd_val_mode_2( &spectrometer, &adc_buf[ 0 ] );
    
    ch_0 = adc_buf[ 1 ];
    ch_0 <<= 8;
    ch_0 |= adc_buf[ 0 ];
    log_printf( &logger, " ADC0/F5 : %u\r\n", ch_0 );

    ch_1 = adc_buf[ 3 ];
    ch_1 <<= 8;
    ch_1 |= adc_buf[ 2 ];
    log_printf( &logger, " ADC1/F6 : %u\r\n", ch_1 );

    ch_2 = adc_buf[ 5 ];
    ch_2 <<= 8;
    ch_2 |= adc_buf[ 4 ];
    log_printf( &logger, " ADC2/F7 : %u\r\n", ch_2 );

    ch_3 = adc_buf[ 7 ];
    ch_3 <<= 8;
    ch_3 |= adc_buf[ 6 ];
    log_printf( &logger, " ADC3/F8 : %u\r\n", ch_3 );

    ch_4 = adc_buf[ 9 ];
    ch_4 <<= 8;
    ch_4 |= adc_buf[ 8 ];
    log_printf( &logger, " ADC4/Clear : %u\r\n", ch_4 );

    f_val = spectrometer_flicker_detection( &spectrometer );

    log_printf( &logger, " Flicker : " );
    if ( f_val == SPECTROMETER_UNKNOWN_FREQ )
    {
        log_printf( &logger, "unknown\r\n" );
    }
    else if ( f_val == SPECTROMETER_DETECTED_100_HZ )
    {
        log_printf( &logger, "100 Hz detected\r\n" );
    }
    else if ( f_val == SPECTROMETER_DETECTED_120_HZ )
    {
        log_printf( &logger, "120 Hz detected\r\n" );
    }
    else
    {
        log_printf( &logger, "Error in reading\r\n" );
    }

    log_printf( &logger, "-----------------\r\n" );
    Delay_ms ( 1000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Spectrometer

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
