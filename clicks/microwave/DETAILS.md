 

---
# Microwave click

Microwave click detects movement, thanks to the PD-V11 a 24GHz microwave motion sensor.
The typical use for Microwave click is a proximity or motion detector in various applications and devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/microwave_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/microwave-click>)

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

>
> This is an example which demonstrates the use of Microwave Click board.
> Microwave click reads ADC results, takes exact amount of samples,
> calculation of difference between taken samples and reference ADC value, and
> reports movement if difference is greater than selected threshold value.
>

**The demo application is composed of two sections :**

### Application Init

>
> Initializes the ADC and uart console where the results will be showed.
> Also calculates the reference ADC value for Microwave Click board.
>

```c

void application_init( void )
{
    microwave_cfg_t microwave_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    microwave_cfg_setup( &microwave_cfg );
    MICROWAVE_MAP_MIKROBUS( microwave_cfg, MIKROBUS_1 );
    microwave_init( &microwave, &microwave_cfg );

    //  UART console module initialization.
    LOG_MAP_USB_UART( console_cfg );
    console_cfg.baud = 57600;
    log_init( &console, &console_cfg );
    log_write( &console, "***************************************",
               LOG_FORMAT_LINE );
    log_write( &console, "***  Microwave initialization done  ***",
               LOG_FORMAT_LINE );
    log_write( &console, "***************************************",
               LOG_FORMAT_LINE );

    sum = 0;

    for (cnt = 0; cnt < MICROWAVE_SAMPLES_COUNT_100; cnt++)
    {
        sum += microwave_generic_read( &microwave );
    }

    reference = sum / MICROWAVE_SAMPLES_COUNT_100;

    log_printf( &console, "** Reference value is %d\r\n", reference );
    log_write( &console, "***************************************",
               LOG_FORMAT_LINE );
}

```

### Application Task

>
> Reads the AD converted results and compares this results with the previously
> calculated reference value, taking into account the choosen threshold value.
>

```c

void application_task( void )
{
    analog_in_data_t adc_sample;
    uint16_t detector;
    uint8_t sampler;

    sum = 0;
    cnt = 0;

    for (sampler = 0; sampler < MICROWAVE_SAMPLES_COUNT_100; sampler++)
    {
        adc_sample = microwave_generic_read( &microwave );

        if (adc_sample < reference)
        {
            sum += adc_sample;
            cnt++;
        }
    }

    if (cnt)
    {
        detector = sum / cnt;

        if (( detector + MICROWAVE_THRESHOLD_50 ) < reference)
        {
            log_printf( &console, "** Detected move is %d\r\n", detector );
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
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
