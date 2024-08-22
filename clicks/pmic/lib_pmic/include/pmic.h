/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file pmic.h
 * @brief This file contains API for PMIC Click Driver.
 */

#ifndef PMIC_H
#define PMIC_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup pmic PMIC Click Driver
 * @brief API for configuring and manipulating PMIC Click driver.
 * @{
 */

/**
 * @defgroup pmic_reg PMIC Registers List
 * @brief List of registers of PMIC Click driver.
 */

/**
 * @addtogroup pmic_reg
 * @{
 */

/**
 * @brief PMIC MAIN instance registers list.
 * @details Specified register for MAIN instance of PMIC Click driver.
 */
#define PMIC_REG_MAIN_TASKSWRESET                   0x0001
#define PMIC_REG_MAIN_EVENTSADCSET                  0x0002
#define PMIC_REG_MAIN_EVENTSADCCLR                  0x0003
#define PMIC_REG_MAIN_INTENEVENTSADCSET             0x0004
#define PMIC_REG_MAIN_INTENEVENTSADCCLR             0x0005
#define PMIC_REG_MAIN_EVENTSBCHARGER0SET            0x0006
#define PMIC_REG_MAIN_EVENTSBCHARGER0CLR            0x0007
#define PMIC_REG_MAIN_INTENEVENTSBCHARGER0SET       0x0008
#define PMIC_REG_MAIN_INTENEVENTSBCHARGER0CLR       0x0009
#define PMIC_REG_MAIN_EVENTSBCHARGER1SET            0x000A
#define PMIC_REG_MAIN_EVENTSBCHARGER1CLR            0x000B
#define PMIC_REG_MAIN_INTENEVENTSBCHARGER1SET       0x000C
#define PMIC_REG_MAIN_INTENEVENTSBCHARGER1CLR       0x000D
#define PMIC_REG_MAIN_EVENTSBCHARGER2SET            0x000E
#define PMIC_REG_MAIN_EVENTSBCHARGER2CLR            0x000F
#define PMIC_REG_MAIN_INTENEVENTSBCHARGER2SET       0x0010
#define PMIC_REG_MAIN_INTENEVENTSBCHARGER2CLR       0x0011
#define PMIC_REG_MAIN_EVENTSSHPHLDSET               0x0012
#define PMIC_REG_MAIN_EVENTSSHPHLDCLR               0x0013
#define PMIC_REG_MAIN_INTENEVENTSSHPHLDSET          0x0014
#define PMIC_REG_MAIN_INTENEVENTSSHPHLDCLR          0x0015
#define PMIC_REG_MAIN_EVENTSVBUSIN0SET              0x0016
#define PMIC_REG_MAIN_EVENTSVBUSIN0CLR              0x0017
#define PMIC_REG_MAIN_INTENEVENTSVBUSIN0SET         0x0018
#define PMIC_REG_MAIN_INTENEVENTSVBUSIN0CLR         0x0019
#define PMIC_REG_MAIN_EVENTSVBUSIN1SET              0x001A
#define PMIC_REG_MAIN_EVENTSVBUSIN1CLR              0x001B
#define PMIC_REG_MAIN_INTENEVENTSVBUSIN1SET         0x001C
#define PMIC_REG_MAIN_INTENEVENTSVBUSIN1CLR         0x001D
#define PMIC_REG_MAIN_EVENTSGPIOSET                 0x0022
#define PMIC_REG_MAIN_EVENTSGPIOCLR                 0x0023
#define PMIC_REG_MAIN_INTENEVENTSGPIOSET            0x0024
#define PMIC_REG_MAIN_INTENEVENTSGPIOCLR            0x0025

/**
 * @brief PMIC VBUSIN instance registers list.
 * @details Specified register for VBUSIN instance of PMIC Click driver.
 */
#define PMIC_REG_VBUSIN_TASKUPDATEILIMSW            0x0200
#define PMIC_REG_VBUSIN_VBUSINILIM0                 0x0201
#define PMIC_REG_VBUSIN_VBUSSUSPEND                 0x0203
#define PMIC_REG_VBUSIN_USBCDETECTSTATUS            0x0205
#define PMIC_REG_VBUSIN_VBUSINSTATUS                0x0207

/**
 * @brief PMIC BCHARGER instance registers list.
 * @details Specified register for BCHARGER instance of PMIC Click driver.
 */
#define PMIC_REG_BCHARGER_TASKRELEASEERR            0x0300
#define PMIC_REG_BCHARGER_TASKCLEARCHGERR           0x0301
#define PMIC_REG_BCHARGER_TASKCLEARSAFETYTIMER      0x0302
#define PMIC_REG_BCHARGER_BCHGENABLESET             0x0304
#define PMIC_REG_BCHARGER_BCHGENABLECLR             0x0305
#define PMIC_REG_BCHARGER_BCHGDISABLESET            0x0306
#define PMIC_REG_BCHARGER_BCHGDISABLECLR            0x0307
#define PMIC_REG_BCHARGER_BCHGISETMSB               0x0308
#define PMIC_REG_BCHARGER_BCHGISETLSB               0x0309
#define PMIC_REG_BCHARGER_BCHGISETDISCHARGEMSB      0x030A
#define PMIC_REG_BCHARGER_BCHGISETDISCHARGELSB      0x030B
#define PMIC_REG_BCHARGER_BCHGVTERM                 0x030C
#define PMIC_REG_BCHARGER_BCHGVTERMR                0x030D
#define PMIC_REG_BCHARGER_BCHGVTRICKLESEL           0x030E
#define PMIC_REG_BCHARGER_BCHGITERMSEL              0x030F
#define PMIC_REG_BCHARGER_NTCCOLD                   0x0310
#define PMIC_REG_BCHARGER_NTCCOLDLSB                0x0311
#define PMIC_REG_BCHARGER_NTCCOOL                   0x0312
#define PMIC_REG_BCHARGER_NTCCOOLLSB                0x0313
#define PMIC_REG_BCHARGER_NTCWARM                   0x0314
#define PMIC_REG_BCHARGER_NTCWARMLSB                0x0315
#define PMIC_REG_BCHARGER_NTCHOT                    0x0316
#define PMIC_REG_BCHARGER_NTCHOTLSB                 0x0317
#define PMIC_REG_BCHARGER_DIETEMPSTOP               0x0318
#define PMIC_REG_BCHARGER_DIETEMPSTOPLSB            0x0319
#define PMIC_REG_BCHARGER_DIETEMPRESUME             0x031A
#define PMIC_REG_BCHARGER_DIETEMPRESUMELSB          0x031B
#define PMIC_REG_BCHARGER_BCHGILIMSTATUS            0x032D
#define PMIC_REG_BCHARGER_NTCSTATUS                 0x0332
#define PMIC_REG_BCHARGER_DIETEMPSTATUS             0x0333
#define PMIC_REG_BCHARGER_BCHGCHARGESTATUS          0x0334
#define PMIC_REG_BCHARGER_BCHGERRREASON             0x0336
#define PMIC_REG_BCHARGER_BCHGERRSENSOR             0x0337
#define PMIC_REG_BCHARGER_BCHGCONFIG                0x033C

/**
 * @brief PMIC BUCK instance registers list.
 * @details Specified register for BUCK instance of PMIC Click driver.
 */
#define PMIC_REG_BUCK_BUCK1ENASET                   0x0400
#define PMIC_REG_BUCK_BUCK1ENACLR                   0x0401
#define PMIC_REG_BUCK_BUCK2ENASET                   0x0402
#define PMIC_REG_BUCK_BUCK2ENACLR                   0x0403
#define PMIC_REG_BUCK_BUCK1PWMSET                   0x0404
#define PMIC_REG_BUCK_BUCK1PWMCLR                   0x0405
#define PMIC_REG_BUCK_BUCK2PWMSET                   0x0406
#define PMIC_REG_BUCK_BUCK2PWMCLR                   0x0407
#define PMIC_REG_BUCK_BUCK1NORMVOUT                 0x0408
#define PMIC_REG_BUCK_BUCK1RETVOUT                  0x0409
#define PMIC_REG_BUCK_BUCK2NORMVOUT                 0x040A
#define PMIC_REG_BUCK_BUCK2RETVOUT                  0x040B
#define PMIC_REG_BUCK_BUCKENCTRL                    0x040C
#define PMIC_REG_BUCK_BUCKVRETCTRL                  0x040D
#define PMIC_REG_BUCK_BUCKPWMCTRL                   0x040E
#define PMIC_REG_BUCK_BUCKSWCTRLSEL                 0x040F
#define PMIC_REG_BUCK_BUCK1VOUTSTATUS               0x0410
#define PMIC_REG_BUCK_BUCK2VOUTSTATUS               0x0411
#define PMIC_REG_BUCK_BUCKCTRL0                     0x0415
#define PMIC_REG_BUCK_BUCKSTATUS                    0x0434

/**
 * @brief PMIC ADC instance registers list.
 * @details Specified register for ADC instance of PMIC Click driver.
 */
#define PMIC_REG_ADC_TASKVBATMEASURE                0x0500
#define PMIC_REG_ADC_TASKNTCMEASURE                 0x0501
#define PMIC_REG_ADC_TASKTEMPMEASURE                0x0502
#define PMIC_REG_ADC_TASKVSYSMEASURE                0x0503
#define PMIC_REG_ADC_TASKIBATMEASURE                0x0506
#define PMIC_REG_ADC_TASKVBUS7MEASURE               0x0507
#define PMIC_REG_ADC_TASKDELAYEDVBATMEASURE         0x0508
#define PMIC_REG_ADC_ADCCONFIG                      0x0509
#define PMIC_REG_ADC_ADCNTCRSEL                     0x050A
#define PMIC_REG_ADC_ADCAUTOTIMCONF                 0x050B
#define PMIC_REG_ADC_TASKAUTOTIMUPDATE              0x050C
#define PMIC_REG_ADC_ADCDELTIMCONF                  0x050D
#define PMIC_REG_ADC_ADCIBATMEASSTATUS              0x0510
#define PMIC_REG_ADC_ADCVBATRESULTMSB               0x0511
#define PMIC_REG_ADC_ADCNTCRESULTMSB                0x0512
#define PMIC_REG_ADC_ADCTEMPRESULTMSB               0x0513
#define PMIC_REG_ADC_ADCVSYSRESULTMSB               0x0514
#define PMIC_REG_ADC_ADCGP0RESULTLSBS               0x0515
#define PMIC_REG_ADC_ADCVBAT0RESULTMSB              0x0516
#define PMIC_REG_ADC_ADCVBAT1RESULTMSB              0x0517
#define PMIC_REG_ADC_ADCVBAT2RESULTMSB              0x0518
#define PMIC_REG_ADC_ADCVBAT3RESULTMSB              0x0519
#define PMIC_REG_ADC_ADCGP1RESULTLSBS               0x051A
#define PMIC_REG_ADC_ADCIBATMEASEN                  0x0524

/**
 * @brief PMIC GPIOS instance registers list.
 * @details Specified register for GPIOS instance of PMIC Click driver.
 */
#define PMIC_REG_GPIOS_GPIOMODE_0                   0x0600
#define PMIC_REG_GPIOS_GPIOMODE_1                   0x0601
#define PMIC_REG_GPIOS_GPIOMODE_2                   0x0602
#define PMIC_REG_GPIOS_GPIOMODE_3                   0x0603
#define PMIC_REG_GPIOS_GPIOMODE_4                   0x0604
#define PMIC_REG_GPIOS_GPIODRIVE_0                  0x0605
#define PMIC_REG_GPIOS_GPIODRIVE_1                  0x0606
#define PMIC_REG_GPIOS_GPIODRIVE_2                  0x0607
#define PMIC_REG_GPIOS_GPIODRIVE_3                  0x0608
#define PMIC_REG_GPIOS_GPIODRIVE_4                  0x0609
#define PMIC_REG_GPIOS_GPIOPUEN_0                   0x060A
#define PMIC_REG_GPIOS_GPIOPUEN_1                   0x060B
#define PMIC_REG_GPIOS_GPIOPUEN_2                   0x060C
#define PMIC_REG_GPIOS_GPIOPUEN_3                   0x060D
#define PMIC_REG_GPIOS_GPIOPUEN_4                   0x060E
#define PMIC_REG_GPIOS_GPIOPDEN_0                   0x060F
#define PMIC_REG_GPIOS_GPIOPDEN_1                   0x0610
#define PMIC_REG_GPIOS_GPIOPDEN_2                   0x0611
#define PMIC_REG_GPIOS_GPIOPDEN_3                   0x0612
#define PMIC_REG_GPIOS_GPIOPDEN_4                   0x0613
#define PMIC_REG_GPIOS_GPIOOPENDRAIN_0              0x0614
#define PMIC_REG_GPIOS_GPIOOPENDRAIN_1              0x0615
#define PMIC_REG_GPIOS_GPIOOPENDRAIN_2              0x0616
#define PMIC_REG_GPIOS_GPIOOPENDRAIN_3              0x0617
#define PMIC_REG_GPIOS_GPIOOPENDRAIN_4              0x0618
#define PMIC_REG_GPIOS_GPIODEBOUNCE_0               0x0619
#define PMIC_REG_GPIOS_GPIODEBOUNCE_1               0x061A
#define PMIC_REG_GPIOS_GPIODEBOUNCE_2               0x061B
#define PMIC_REG_GPIOS_GPIODEBOUNCE_3               0x061C
#define PMIC_REG_GPIOS_GPIODEBOUNCE_4               0x061D
#define PMIC_REG_GPIOS_GPIOSTATUS                   0x061E

/**
 * @brief PMIC TIMER instance registers list.
 * @details Specified register for TIMER instance of PMIC Click driver.
 */
#define PMIC_REG_TIMER_TIMERSET                     0x0700
#define PMIC_REG_TIMER_TIMERCLR                     0x0701
#define PMIC_REG_TIMER_TIMERTARGETSTROBE            0x0703
#define PMIC_REG_TIMER_WATCHDOGKICK                 0x0704
#define PMIC_REG_TIMER_TIMERCONFIG                  0x0705
#define PMIC_REG_TIMER_TIMERSTATUS                  0x0706
#define PMIC_REG_TIMER_TIMERHIBYTE                  0x0708
#define PMIC_REG_TIMER_TIMERMIDBYTE                 0x0709
#define PMIC_REG_TIMER_TIMERLOBYTE                  0x070A

/**
 * @brief PMIC LDSW instance registers list.
 * @details Specified register for LDSW instance of PMIC Click driver.
 */
#define PMIC_REG_LDSW_TASKLDSW1SET                  0x0800
#define PMIC_REG_LDSW_TASKLDSW1CLR                  0x0801
#define PMIC_REG_LDSW_TASKLDSW2SET                  0x0802
#define PMIC_REG_LDSW_TASKLDSW2CLR                  0x0803
#define PMIC_REG_LDSW_LDSWSTATUS                    0x0804
#define PMIC_REG_LDSW_LDSW1GPISEL                   0x0805
#define PMIC_REG_LDSW_LDSW2GPISEL                   0x0806
#define PMIC_REG_LDSW_LDSWCONFIG                    0x0807
#define PMIC_REG_LDSW_LDSW1LDOSEL                   0x0808
#define PMIC_REG_LDSW_LDSW2LDOSEL                   0x0809
#define PMIC_REG_LDSW_LDSW1VOUTSEL                  0x080C
#define PMIC_REG_LDSW_LDSW2VOUTSEL                  0x080D

/**
 * @brief PMIC POF instance registers list.
 * @details Specified register for POF instance of PMIC Click driver.
 */
#define PMIC_REG_POF_POFCONFIG                      0x0900

/**
 * @brief PMIC LEDDRV instance registers list.
 * @details Specified register for LEDDRV instance of PMIC Click driver.
 */
#define PMIC_REG_LEDDRV_LEDDRV0MODESEL              0x0A00
#define PMIC_REG_LEDDRV_LEDDRV1MODESEL              0x0A01
#define PMIC_REG_LEDDRV_LEDDRV2MODESEL              0x0A02
#define PMIC_REG_LEDDRV_LEDDRV0SET                  0x0A03
#define PMIC_REG_LEDDRV_LEDDRV0CLR                  0x0A04
#define PMIC_REG_LEDDRV_LEDDRV1SET                  0x0A05
#define PMIC_REG_LEDDRV_LEDDRV1CLR                  0x0A06
#define PMIC_REG_LEDDRV_LEDDRV2SET                  0x0A07
#define PMIC_REG_LEDDRV_LEDDRV2CLR                  0x0A08

/**
 * @brief PMIC SHIP instance registers list.
 * @details Specified register for SHIP instance of PMIC Click driver.
 */
#define PMIC_REG_SHIP_TASKENTERHIBERNATE            0x0B00
#define PMIC_REG_SHIP_TASKSHPHLDCFGSTROBE           0x0B01
#define PMIC_REG_SHIP_TASKENTERSHIPMODE             0x0B02
#define PMIC_REG_SHIP_TASKRESETCFG                  0x0B03
#define PMIC_REG_SHIP_SHPHLDCONFIG                  0x0B04
#define PMIC_REG_SHIP_SHPHLDSTATUS                  0x0B05
#define PMIC_REG_SHIP_LPRESETCONFIG                 0x0B06

/**
 * @brief PMIC ERRLOG instance registers list.
 * @details Specified register for ERRLOG instance of PMIC Click driver.
 */
#define PMIC_REG_ERRLOG_TASKCLRERRLOG               0x0E00
#define PMIC_REG_ERRLOG_SCRATCH0                    0x0E01
#define PMIC_REG_ERRLOG_SCRATCH1                    0x0E02
#define PMIC_REG_ERRLOG_RSTCAUSE                    0x0E03
#define PMIC_REG_ERRLOG_CHARGERERRREASON            0x0E04
#define PMIC_REG_ERRLOG_CHARGERERRSENSOR            0x0E05

/*! @} */ // pmic_reg

/**
 * @defgroup pmic_set PMIC Registers Settings
 * @brief Settings for registers of PMIC Click driver.
 */

/**
 * @addtogroup pmic_set
 * @{
 */

/**
 * @brief PMIC GPIO mode setting.
 * @details Specified setting for GPIO mode of PMIC Click driver.
 */
#define PMIC_GPIO_MODE_GPIINPUT                     0x00
#define PMIC_GPIO_MODE_GPILOGIC1                    0x01
#define PMIC_GPIO_MODE_GPILOGIC0                    0x02
#define PMIC_GPIO_MODE_GPIEVENTRISE                 0x03
#define PMIC_GPIO_MODE_GPIEVENTFALL                 0x04
#define PMIC_GPIO_MODE_GPOIRQ                       0x05
#define PMIC_GPIO_MODE_GPORESET                     0x06
#define PMIC_GPIO_MODE_GPOPLW                       0x07
#define PMIC_GPIO_MODE_GPOLOGIC1                    0x08
#define PMIC_GPIO_MODE_GPOLOGIC0                    0x09

/**
 * @brief PMIC BCHGDISABLESET register setting.
 * @details Specified setting for BCHGDISABLESET register of PMIC Click driver.
 */
#define PMIC_BCHGDISABLESET_DISABLERCHG             0x01
#define PMIC_BCHGDISABLESET_IGNORENTC               0x02

/**
 * @brief PMIC BCHGDISABLECLR register setting.
 * @details Specified setting for BCHGDISABLECLR register of PMIC Click driver.
 */
#define PMIC_BCHGDISABLECLR_ENABLERCHG              0x01
#define PMIC_BCHGDISABLECLR_USENTC                  0x02

/**
 * @brief PMIC BCHGENABLESET register setting.
 * @details Specified setting for BCHGENABLESET register of PMIC Click driver.
 */
#define PMIC_BCHGENABLESET_ENABLECHG                0x01
#define PMIC_BCHGENABLESET_ENABLECOOL               0x02

/**
 * @brief PMIC BCHGENABLECLR register setting.
 * @details Specified setting for BCHGENABLECLR register of PMIC Click driver.
 */
#define PMIC_BCHGENABLECLR_DISABLECHG               0x01
#define PMIC_BCHGENABLECLR_DISABLECOOL              0x02

/**
 * @brief PMIC ADCCONFIG register setting.
 * @details Specified setting for ADCCONFIG register of PMIC Click driver.
 */
#define PMIC_ADCCONFIG_AUTOENABLE                   0x01
#define PMIC_ADCCONFIG_BURSTMODE                    0x02

/**
 * @brief PMIC Battery Charger Termination Voltage Normal setting.
 * @details Specified setting for Battery Charger Termination Voltage Normal of PMIC Click driver.
 */
#define PMIC_BCHGVTERMNORM_3V50                     0x00
#define PMIC_BCHGVTERMNORM_3V55                     0x01
#define PMIC_BCHGVTERMNORM_3V60                     0x02
#define PMIC_BCHGVTERMNORM_3V65                     0x03
#define PMIC_BCHGVTERMNORM_4V00                     0x04
#define PMIC_BCHGVTERMNORM_4V05                     0x05
#define PMIC_BCHGVTERMNORM_4V10                     0x06
#define PMIC_BCHGVTERMNORM_4V15                     0x07
#define PMIC_BCHGVTERMNORM_4V20                     0x08
#define PMIC_BCHGVTERMNORM_4V25                     0x09
#define PMIC_BCHGVTERMNORM_4V30                     0x0A
#define PMIC_BCHGVTERMNORM_4V35                     0x0B
#define PMIC_BCHGVTERMNORM_4V40                     0x0C
#define PMIC_BCHGVTERMNORM_4V45                     0x0D

/**
 * @brief PMIC Battery Charging current setting.
 * @details Specified setting for Battery Charging current of PMIC Click driver.
 */
#define PMIC_CHARGING_CURRENT_MIN                   32
#define PMIC_CHARGING_CURRENT_DEFAULT               200
#define PMIC_CHARGING_CURRENT_MAX                   800

/**
 * @brief PMIC VBAT/VSYS/VBUS measurement setting.
 * @details Specified setting for VBAT/VSYS/VBUS measurement of PMIC Click driver.
 */
#define PMIC_TRIGGER_MEASUREMENT                    0x01
#define PMIC_VBAT_FULL_SCALE_MILLIVOLTS             5000.0f
#define PMIC_VBAT_DATA_RESOLUTION                   0x03FF
#define PMIC_VSYS_FULL_SCALE_MILLIVOLTS             6375.0f
#define PMIC_VSYS_DATA_RESOLUTION                   0x03FF
#define PMIC_VBUS_FULL_SCALE_MILLIVOLTS             7500.0f
#define PMIC_VBUS_DATA_RESOLUTION                   0x03FF

/**
 * @brief PMIC battery charging status setting.
 * @details Specified setting for battery charging status of PMIC Click driver.
 */
#define PMIC_CHARGE_STATUS_BATTERYDETECTED          0x01
#define PMIC_CHARGE_STATUS_COMPLETED                0x02
#define PMIC_CHARGE_STATUS_TRICKLECHARGE            0x04
#define PMIC_CHARGE_STATUS_CONSTANTCURRENT          0x08
#define PMIC_CHARGE_STATUS_CONSTANTVOLTAGE          0x10
#define PMIC_CHARGE_STATUS_RECHARGE                 0x20
#define PMIC_CHARGE_STATUS_DIETEMPHIGHCHGPAUSED     0x40
#define PMIC_CHARGE_STATUS_SUPPLEMENTACTIVE         0x80

/**
 * @brief PMIC event and interrupt setting.
 * @details Specified setting for event and interrupt of PMIC Click driver.
 */
#define PMIC_EVENTADCVBATRDY                        0x01
#define PMIC_EVENTADCNTCRDY                         0x02
#define PMIC_EVENTADCTEMPRDY                        0x04
#define PMIC_EVENTADCVSYSRDY                        0x08
#define PMIC_EVENTADCVSET1RDY                       0x10
#define PMIC_EVENTADCVSET2RDY                       0x20
#define PMIC_EVENTADCIBATRDY                        0x40
#define PMIC_EVENTADCVBUS7V0RDY                     0x80
#define PMIC_EVENTS_ALL_FLAGS                       0xFF
#define PMIC_WAIT_EVENT_TIMEOUT_MS                  2000

/**
 * @brief PMIC device address setting.
 * @details Specified setting for device slave address selection of
 * PMIC Click driver.
 */
#define PMIC_DEVICE_ADDRESS                         0x6B

/*! @} */ // pmic_set

/**
 * @defgroup pmic_map PMIC MikroBUS Map
 * @brief MikroBUS pin mapping of PMIC Click driver.
 */

/**
 * @addtogroup pmic_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PMIC Click to the selected MikroBUS.
 */
#define PMIC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pmic_map
/*! @} */ // pmic

/**
 * @brief PMIC Click context object.
 * @details Context object definition of PMIC Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< GPIO 4 pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} pmic_t;

/**
 * @brief PMIC Click configuration object.
 * @details Configuration object definition of PMIC Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< GPIO 4 pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} pmic_cfg_t;

/**
 * @brief PMIC Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PMIC_OK = 0,
    PMIC_ERROR = -1

} pmic_return_value_t;

/*!
 * @addtogroup pmic PMIC Click Driver
 * @brief API for configuring and manipulating PMIC Click driver.
 * @{
 */

/**
 * @brief PMIC configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pmic_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pmic_cfg_setup ( pmic_cfg_t *cfg );

/**
 * @brief PMIC initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pmic_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic_init ( pmic_t *ctx, pmic_cfg_t *cfg );

/**
 * @brief PMIC default configuration function.
 * @details This function executes a default configuration of PMIC
 * click board.
 * @param[in] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pmic_default_cfg ( pmic_t *ctx );

/**
 * @brief PMIC reg write function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic_reg_write ( pmic_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief PMIC reg read function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic_reg_read ( pmic_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief PMIC reg write byte function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic_reg_write_byte ( pmic_t *ctx, uint16_t reg, uint8_t data_in );

/**
 * @brief PMIC reg read byte function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic_reg_read_byte ( pmic_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief PMIC get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t pmic_get_int_pin ( pmic_t *ctx );

/**
 * @brief PMIC wait for event function.
 * @details This function waits for a desired bits to be set in the selected event set register.
 * @param[in] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @param[in] evt_set_reg : Event set register address.
 * @param[in] bit_mask : Bit mask to wait for.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic_wait_for_event ( pmic_t *ctx, uint16_t evt_set_reg, uint8_t bit_mask );

/**
 * @brief PMIC get vbat function.
 * @details This function reads the VBAT measurement results in millivolts.
 * @param[in] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @param[in] vbat : VBAT measurement in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic_get_vbat ( pmic_t *ctx, uint16_t *vbat );

/**
 * @brief PMIC get vbus function.
 * @details This function reads the VBUS measurement results in millivolts.
 * @param[in] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @param[in] vbus : VBUS measurement in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic_get_vbus ( pmic_t *ctx, uint16_t *vbus );

/**
 * @brief PMIC get vsys function.
 * @details This function reads the VSYS measurement results in millivolts.
 * @param[in] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @param[in] vsys : VSYS measurement in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic_get_vsys ( pmic_t *ctx, uint16_t *vsys );

/**
 * @brief PMIC set charging current function.
 * @details This function sets the charging current limit.
 * @param[in] ctx : Click context object.
 * See #pmic_t object definition for detailed explanation.
 * @param[in] current : Current limit from 32mA to 800mA in 2mA steps.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Charger must be disabled before changing the current setting.
 */
err_t pmic_set_charging_current ( pmic_t *ctx, uint16_t current );

#ifdef __cplusplus
}
#endif
#endif // PMIC_H

/*! @} */ // pmic

// ------------------------------------------------------------------------ END
