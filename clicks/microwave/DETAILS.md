
---
# Microwave Click

Microwave Click detects movement, thanks to the PD-V11 a 24GHz microwave motion sensor.
The typical use for Microwave Click is a proximity or motion detector in various applications and devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/microwave_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/microwave-click)

---


#### Click library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Microwave Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers).
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account.

## Library Description

> This library contains API for Microwave Click driver.

#### Standard key functions :

- Configuration Object Setup function.
> void microwave_cfg_setup( microwave_cfg_t *cfg );
 
- Click Initialization function.
> microwave_err_t microwave_init( microwave_t *ctx, microwave_cfg_t *cfg );

#### Example key functions :

- Generic ADC Read function.
> analog_in_data_t microwave_generic_read( microwave_t *ctx );

## Examples Description

> This is an example which demonstrates the use of Microwave Click board.
> Microwave Click reads ADC results, takes exact amount of samples,
> calculation of difference between taken samples and reference ADC value, and
> reports movement if difference is greater/lower than selected threshold value.

**The demo application is composed of two sections :**

### Application Init

> Initializes the ADC and uart console where the results will be displayed.
> Also calculates the reference ADC value for Microwave Click board.

```c

void application_init( void )
{
    microwave_cfg_t cfg;
    log_cfg_t log_cfg;

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
    microwave_cfg_setup( &cfg );
    MICROWAVE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    microwave_init( &microwave, &cfg );
    Delay_ms ( 100 );

    log_printf( &logger, " Calibrating the sensor...\r\n" );
    log_printf( &logger, " There must be no movement near the sensor!\r\n" );
    log_printf( &logger, "*********************************************\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    sum = 0;

    for ( uint8_t cnt = 0; cnt < MICROWAVE_SAMPLES_COUNT_100; cnt++ )
    {
        sum += microwave_generic_read( &microwave );
    }

    reference = sum / MICROWAVE_SAMPLES_COUNT_100;

    log_printf( &logger, " The sensor has been calibrated!\r\n" );
    log_printf( &logger, "** Reference value: %d\r\n", reference );
    log_printf( &logger, "*********************************************\r\n" );
    Delay_ms ( 1000 );
}

```

### Application Task

> Reads the AD converted results and compares this results with the previously
> calculated reference value, taking into account the choosen threshold value
> which controls the sensor sensitivity. All data is being displayed on the
> USB UART where you can track their changes.

```c

void application_task( void )
{
    microwave_data_t adc_sample;
    uint16_t detector;
    uint8_t sampler;
    uint8_t cnt = 0;

    sum = 0;

    for ( sampler = 0; sampler < MICROWAVE_SAMPLES_COUNT_100; sampler++ )
    {
        adc_sample = microwave_generic_read( &microwave );
        sum += adc_sample;
        cnt++;
    }

    if ( cnt )
    {
        detector = sum / cnt;

        if ( ( ( detector + MICROWAVE_THRESHOLD_10 ) < reference || 
               ( detector - MICROWAVE_THRESHOLD_10 ) > reference ) && 
                 old_detector != detector )
        {
            log_printf( &logger, "** MOVE DETECTED!\r\n" );
            log_printf( &logger, "** Detector value : %d\r\n", detector );
            log_printf( &logger, "**************************\r\n" );
            old_detector = detector;
            Delay_ms ( 100 );
        }
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Microwave

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
