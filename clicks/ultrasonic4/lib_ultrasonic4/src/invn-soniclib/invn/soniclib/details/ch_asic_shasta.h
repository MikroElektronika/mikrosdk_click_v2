/*! \file ch_asic_shasta.h
 *
 * \brief Definitions for Chirp Shasta sensor ASIC
 *
 */

/*
 Copyright 2016-2023, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */

#ifndef CH_ASIC_SHASTA_H_
#define CH_ASIC_SHASTA_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SHASTA_CPU_ID_VALUE (0x2041)

#define SHASTA_DATA_MEM_SIZE      0x1000
#define SHASTA_DATA_MEM_ADDR      0x1000
#define SHASTA_PROG_MEM_SIZE      0x1800
#define SHASTA_PROG_MEM_ADDR      0xE800
#define SHASTA_PROG_MEM_BASE_ADDR 0xE000  // start of addr space, for DMA

#define SHASTA_CONFIG_PTR_ADDR    SHASTA_DATA_MEM_ADDR          // location of config addr
#define SHASTA_ALGO_INFO_PTR_ADDR (SHASTA_CONFIG_PTR_ADDR + 2)  // location of algo info addr

#define SHASTA_CPU_TRIM_MAX (63)

#define SHASTA_SMCLK_CYCLES_PER_PMUT (16)

#define SHASTA_FCOUNT_CYCLES     (128)
#define SHASTA_CPU_TRIM_DEFAULT  (0x1E)
#define SHASTA_PMUT_TRIM_DEFAULT (0x4028)

/* Shasta System Control Register */
#define SHASTA_REG_SYS_CTRL (0xA000)  // register address

#define SYS_CTRL_RESET_N        (0x0001)  // sensor reset - active low
#define SYS_CTRL_DEBUG          (0x0002)  // enable debug mode
#define SYS_CTRL_DUMMY_BYTES_BM (0x001C)  // number of extra dummy SPI bytes (3 bits)
#define SYS_CTRL_POR_N          (0x0020)  // power-on - read (1 for 100ms, then 0 when ready)
#define SYS_CTRL_SCAN_MODE_BM   (0x0060)  // scan mode bits - write (should be zero)

/* Shasta ASIC Debug Register Offsets */
#define SHASTA_DBG_REG_CPU_ID_LO (0x00)  // CPU ID - low 16 bits
#define SHASTA_DBG_REG_CPU_ID_HI (0x01)  // CPU ID - high 16 bits
#define SHASTA_DBG_REG_MEM_ADDR  (0x02)  // memory address (16 bits)
#define SHASTA_DBG_REG_MEM_DATA  (0x03)  // memory data (16 bits)
#define SHASTA_DBG_REG_CPU_CTL   (0x04)  // CPU control (8 bits)
#define SHASTA_DBG_REG_CPU_STAT  (0x05)  // CPU status (8 bits)
#define SHASTA_DBG_REG_MEM_CTL   (0x06)  // memory control (8 bits)

#define SHASTA_LAST_16BIT_DBG_REG SHASTA_DBG_REG_MEM_DATA  // last 16-bit debug reg

/* Shasta ASIC Debug Register bit masks */
#define CPU_ID_LO_CHIP_VERSION_BM (0x00FF)  // CPU version (8 bits)
#define CPU_ID_LO_CHIP_ID_BM      (0xFF00)  // chip ID value (8 bits)

#define CPU_ID_HI_MPY          (0x0001)  // hardware multiplier present
#define CPU_ID_HI_DMEM_SIZE_BM (0x03FE)  // data mem size (9 bits)
#define CPU_ID_HI_PMEM_SIZE_BM (0xFC00)  // program mem size (6 bits)

#define CPU_CTL_HALT       (0x01)
#define CPU_CTL_RUN        (0x02)
#define CPU_CTL_ISTEP      (0x04)
#define CPU_CTL_SW_BRK_EN  (0x08)
#define CPU_CTL_FRZ_BRK_EN (0x10)
#define CPU_CTL_RST_BRK_EN (0x20)
#define CPU_CTL_CPU_RST    (0x40)

#define CPU_STAT_HALT_RUN  (0x01)
#define CPU_STAT_PUC_PND   (0x04)
#define CPU_STAT_SWBRK_PND (0x08)

#define MEM_CTL_START   (0x01)
#define MEM_CTL_RDWR    (0x02)
#define MEM_CTL_MEM_REG (0x04)
#define MEM_CTL_SW_BW   (0x08)

#define SHASTA_CPU_ID_HI_VALUE                                                                                         \
	(0x2041)  // expected CPU_HI value at startup
	          //  PMEM=6kB, DMEM=4kB, h/w mult

/* Shasta Peripheral Registers */

#define SHASTA_REG_LPWKUP_PERIOD     (0x0190)  // low power wake-up period
#define SHASTA_REG_LPWKUP_CTRL       (0x0192)  // low power wake-up control
#define SHASTA_REG_LPWKUP_STATUS     (0x0194)  // low power wake-up status
#define SHASTA_REG_LPWKUP_COUNT      (0x0196)  // low power wake-up counter value
#define SHASTA_REG_PMUT_CONFIG       (0x01A0)  // PMUT config
#define SHASTA_REG_PMUT_CHPUMP       (0x01A2)  // PMUT charge pump control
#define SHASTA_REG_PMUT_STATUS       (0x01A4)  // PMUT status
#define SHASTA_REG_PMUT_IP           (0x01A6)  // PMUT instruction pointer
#define SHASTA_REG_PMUT_CTRL         (0x01A8)  // PMUT control
#define SHASTA_REG_PMUT_NEXT_WRT_PTR (0x01AA)  // PMUT next DMA write pointer
#define SHASTA_REG_PMUT_CAP_VAL      (0x01AC)  // PMUT matching capacitor value
#define SHASTA_REG_PMUT_DMA_WRT_PTR  (0x01AE)  // PMUT DMA write pointer
#define SHASTA_REG_PMUT_DMA_END_PTR  (0x01B0)  // PMUT DMA end pointer
#define SHASTA_REG_ATP_TPEN          (0x01C0)  // analog test peripheral enable
#define SHASTA_REG_ATP_TPSEL         (0x01C1)  // analog test peripheral select
#define SHASTA_REG_FCOUNT_CTRL       (0x01D0)  // freq counter control
#define SHASTA_REG_FCOUNT_RESULT     (0x01D2)  // freq counter result
#define SHASTA_REG_FCOUNT_STATUS     (0x01D4)  // freq counter status
#define SHASTA_REG_PT_CTRL           (0x01D8)  // pulse timer control
#define SHASTA_REG_PT_SELECT         (0x01D9)  // pulse timer pin select
#define SHASTA_REG_PT_RESULT         (0x01DA)  // pulse timer count result
#define SHASTA_REG_GPIO_0_PCFG       (0x01E0)  // GPIO 0 pin config
#define SHASTA_REG_GPIO_0_PDIN       (0x01E1)  // GPIO 0 pin input pin value
#define SHASTA_REG_GPIO_0_PDOUT      (0x01E2)  // GPIO 0 pin output pin value
#define SHASTA_REG_GPIO_0_PDIR       (0x01E3)  // GPIO 0 pin direction (0=in 1=out)
#define SHASTA_REG_GPIO_1_PCFG       (0x01E4)  // GPIO 1 pin config
#define SHASTA_REG_GPIO_1_PDIN       (0x01E5)  // GPIO 1 pin input pin value
#define SHASTA_REG_GPIO_1_PDOUT      (0x01E6)  // GPIO 1 pin output pin value
#define SHASTA_REG_GPIO_1_PDIR       (0x01E7)  // GPIO 1 pin direction (0=in 1=out)
#define SHASTA_REG_OTP_ADDR          (0x01E8)  // OTP address input
#define SHASTA_REG_OTP_CTRL          (0x01E9)  // OTP control
#define SHASTA_REG_OTP_DATA          (0x01EA)  // OTP data
#define SHASTA_REG_SCM_PMUT_CLK      (0x01F0)  // PMUT clock control
#define SHASTA_REG_SCM_RTC_CLK       (0x01F2)  // RTC clock control
#define SHASTA_REG_SCM_CPU_CLK       (0x01F3)  // CPU clock control
#define SHASTA_REG_SCM_PASSWORD      (0x01F4)  // clock module password (for ATP mode)
#define SHASTA_REG_SPI_WR_ADDR       (0x0200)  // SPI write address
#define SHASTA_REG_SPI_WR_MASK       (0x0202)  // SPI write mask
#define SHASTA_REG_SPI_CTRL          (0x0204)  // SPI control
#define SHASTA_REG_SPI_DMA_PTR       (0x0206)  // SPI DMA pointer current value
#define SHASTA_REG_SPI_START_ADDR    (0x0208)  // SPI start address of last DMA

/* Shasta Peripheral Register Bit Masks & Values */

/* SHASTA_REG_LPWKUP_CTRL (0x0192) */
#define LPWKUP_CTRL_IEN     (0x0001)  // LP wake-up interrupt enable
#define LPWKUP_CTRL_CLK_EN  (0x0002)  // LP wake-up clock enable
#define LPWKUP_CTRL_RESET_N (0x0004)  // LP wake-up counter reset (active low)

/* SHASTA_REG_LPWKUP_STATUS (0x0194) */
#define LPWKUP_STATUS_PERIOD_RDY (0x0001)  // LP wake-up period reg is ready for new data
#define LPWKUP_STATUS_CTRL_RDY   (0x0002)  // LP wake-up control reg is ready for new data
#define LPWKUP_STATUS_COUNT_SYNC (0x0004)  // start loading count reg (clears automatically)

/* SHASTA_REG_PMUT_CONFIG (0x01A0) */
#define PMUT_CONFIG_VREF_CTRL           (0x0001)  // PMUT voltage ref control
#define PMUT_CONFIG_SINGLE_ENDED_TX     (0x0002)  // put transmitter in single-ended mode
#define PMUT_CONFIG_CP_ACTIVE_DISCHARGE (0x0004)  // actively discharge charge pump (also resets)
#define PMUT_CONFIG_TX0_ENABLE          (0x0008)  // drive tx pad 0
#define PMUT_CONFIG_TX1_ENABLE          (0x0010)  // drive tx pad 1
#define PMUT_CONFIG_TX2_ENABLE          (0x0020)  // drive tx pad 2
#define PMUT_CONFIG_TX3_ENABLE          (0x0040)  // drive tx pad 3
#define PMUT_CONFIG_CIC_ODR_BM          (0x0700)  // output data rate (3 bits)
#define PMUT_CONFIG_CIC_ODR_32          (0x0200)  //   output data rate = op freq / 32
#define PMUT_CONFIG_CIC_ODR_16          (0x0300)  //   output data rate = op freq / 16
#define PMUT_CONFIG_CIC_ODR_8           (0x0400)  //   output data rate = op freq / 8
#define PMUT_CONFIG_CIC_ODR_4           (0x0500)  //   output data rate = op freq / 4
#define PMUT_CONFIG_CIC_ODR_2           (0x0600)  //   output data rate = op freq / 2
#define PMUT_CONFIG_RX_PWR_OVERRIDE     (0x1000)  // rx power override
#define PMUT_CONFIG_AFE_BIAS_EN         (0x2000)  // enable AFE bias current
#define PMUT_CONFIG_ADC_LF_EN           (0x4000)  // enable ADC bias current

/* SHASTA_REG_PMUT_CHPUMP (0x01A2) */
#define PMUT_CHPUMP_HVVDD_CYCLES_BM (0x0007)  // number of cycles charge pump enabled (3 bits)
#define PMUT_CHPUMP_SMCLK_DIV_BM    (0x0030)  // charge pump divider ratio (2 bits)
#define PMUT_CHPUMP_SMCLK_DIV_1     (0x0000)  //   charge pump divisor = 1
#define PMUT_CHPUMP_SMCLK_DIV_2     (0x0010)  //   charge pump divisor = 2
#define PMUT_CHPUMP_SMCLK_DIV_4     (0x0020)  //   charge pump divisor = 4
#define PMUT_CHPUMP_SMCLK_DIV_8     (0x0030)  //   charge pump divisor = 8
#define PMUT_CHPUMP_HVVDD_FON       (0x0200)  // run charge pump continuously
#define PMUT_CHPUMP_CP_CLK_SEL      (0x1000)  // use SMCLK for charge pump clock
#define PMUT_CHPUMP_RUN_CP_IN_RX    (0x2000)  // run charge pump during receive

/* SHASTA_REG_PMUT_STATUS (0x01A4) */
#define PMUT_STATUS_EOF_IFG          (0x0004)  // EOF interrupt has occurred
#define PMUT_STATUS_ERROR_IFG        (0x0008)  // error interrupt has occurred
#define PMUT_STATUS_ACTIVE           (0x0010)  // PMUT is active
#define PMUT_STATUS_RDY_NEXT_WR_PTR  (0x0020)  // PMUT is ready for next write pointer
#define PMUT_STATUS_RDY_CONFIG_WRITE (0x0040)  // PMUT is ready for next write pointer

/* SHASTA_REG_PMUT_CTRL (0x01A8) */
#define PMUT_CTRL_ENABLE    (0x0001)  // enable PMUT
#define PMUT_CTRL_RESET     (0x0002)  // reset PMUT
#define PMUT_CTRL_EOF_IEN   (0x0004)  // enable EOF interrupt
#define PMUT_CTRL_ERROR_IEN (0x0008)  // enable error interrupt

/* SHASTA_REG_PMUT_CAP_VAL (0x01AC) */
#define PMUT_CAP_VAL_VALUE_BM (0x003F)  // capacitor value (1 LSB = 1 pF) (6 bits)
#define PMUT_CAP_VAL_CONNECT  (0x0040)  // connect capacitor

/* SHASTA_REG_ATP_TPEN (0x01C0) */
#define ATP_TPEN_NONE   (0x00)  // no analog tests enabled
#define ATP_TPEN_ADC0   (0x01)  // ADC 0 test enabled
#define ATP_TPEN_ADC1   (0x02)  // ADC 0 test enabled
#define ATP_TPEN_AFE    (0x03)  // AFE test enabled
#define ATP_TPEN_BIAS   (0x04)  // bias test enabled
#define ATP_TPEN_TIMING (0x05)  // timing test enabled
#define ATP_TPEN_TX     (0x06)  // transmit test enabled
#define ATP_TPEN_CP     (0x07)  // charge pump test enabled

/* SHASTA_REG_FCOUNT_STATUS (0x01D4) */
#define FCOUNT_STATUS_RESULT_RDY (0x0001)  // frequency counter result is ready

/* SHASTA_REG_PT_CTRL (0x01D8) */
#define PT_CTRL_IEN (0x01)  // pulse timer interrupt enable
#define PT_CTRL_RST (0x02)  // reset pulse timer

/* SHASTA_REG_PT_SELECT (0x01D9) */
#define PT_SELECT_SOURCE_BM    (0x01)  // pulse timer GPIO pin
#define PT_SELECT_SOURCE_PIN_0 (0x00)  //   pulse timer uses GPIO pin 0
#define PT_SELECT_SOURCE_PIN_1 (0x01)  //   pulse timer uses GPIO pin 1

/* SHASTA_REG_GPIO_0_PCFG (0x01E0)	 and  SHASTA_REG_GPIO_1_PCFG (0x01E4) */
#define GPIO_PCFG_IEN      (0x0001)  // enable GPIO interrupt
#define GPIO_PCFG_PU       (0x0002)  // enable GPIO pull-up
#define GPIO_PCFG_IRQ_FLAG (0x0004)  // interrupt flag status (set on falling edge)

/* SHASTA_REG_GPIO_0_PDIR (0x01E3)	 and  SHASTA_REG_GPIO_1_PDIR (0x01E7) */
#define GPIO_PDIR_INPUT  (0x00)  // set GPIO as input
#define GPIO_PDIR_OUTPUT (0x01)  // set GPIO as output

/* SHASTA_REG_OTP_CTRL (0x01E9) */
#define OTP_CTRL_OTP_EN      (0x01)  // enable power to OTP memory
#define OTP_CTRL_PRD         (0x02)  // read cycle enable
#define OTP_CTRL_PWE         (0x04)  // write cycle enable
#define OTP_CTRL_PPROG       (0x08)  // program mode enable
#define OTP_CTRL_PTM_BM      (0x30)  // test mode select (2 bits)
#define OTP_CTRL_PPROG_IO_EN (0x40)  // program mode I/O enable
#define OTP_CTRL_VPP_RDY     (0x80)  // VPP voltage is above VDDIO

/* SHASTA_REG_SCM_PMUT_CLK (0x01F0) */
#define SCM_PMUT_CLK_FREQ_TRIM_BM     (0x01FF)  // PMUT frequency trim code (9 bits)
#define SCM_PMUT_CLK_PAD_MODE_BM      (0x0600)  // analog test pad mode (2 bits)
#define SCM_PMUT_CLK_PAD_MODE_NONE    (0x0000)  //   MUTCLK pad disabled
#define SCM_PMUT_CLK_PAD_MODE_PMUT    (0x0200)  //   MUTCLK pad PMUTCLK output
#define SCM_PMUT_CLK_PAD_MODE_AT      (0x0400)  //   MUTCLK pad in analog test mode
#define SCM_PMUT_CLK_PAD_MODE_INPUT   (0x0600)  //   MUTCLK pad is input
#define SCM_PMUT_CLK_EXT_EN           (0x0800)  // enable external clock input
#define SCM_PMUT_CLK_DIV_BM           (0x3000)  // PMUT clock divider ratio (2 bits)
#define SCM_PMUT_CLK_DIV_1            (0x0000)  //   PMUT clock divisor = 1
#define SCM_PMUT_CLK_DIV_2            (0x1000)  //   PMUT clock divisor = 2
#define SCM_PMUT_CLK_DIV_4            (0x2000)  //   PMUT clock divisor = 4
#define SCM_PMUT_CLK_DIV_8            (0x3000)  //   PMUT clock divisor = 8
#define SCM_PMUT_CLK_BIAS_TRIM_BM     (0xC000)  // PMUT oscillator bias trim (2 bits)
#define SCM_PMUT_CLK_BIAS_TRIM_BS     (14)      // PMUT oscillator bias trim bit shift
#define PMUT_CLK_BIAS_0_MAX_FREQ      (65938)   // max frequency that should be used with BIAS_TRIM=0
#define PMUT_CLK_BIAS_1_MAX_FREQ      (102500)  // max frequency that should be used with BIAS_TRIM=1
#define PMUT_CLK_BIAS_2_MAX_FREQ      (153125)  // max frequency that should be used with BIAS_TRIM=2
#define PMUT_CLK_BIAS_3_MAX_FREQ      (212500)  // max frequency that is reliably in BIAS_TRIM=3
#define PMUT_CLK_FREQ_TRIM_MAX_BIAS_0 (300)     // max code to avoid super low frequency at BIAS_TRIM=0
#define PMUT_CLK_FREQ_TRIM_MAX_BIAS_1 (400)     // max code to avoid super low frequency at BIAS_TRIM=1

/* SHASTA_REG_SCM_RTC_CLK (0x01F2) */
#define SCM_RTC_CLK_PAD_MODE_BM    (0x03)  // analog test pad mode (2 bits)
#define SCM_RTC_CLK_PAD_MODE_NONE  (0x00)  //   LFCLK pad disabled
#define SCM_RTC_CLK_PAD_MODE_RTC   (0x01)  //   LFCLK pad = RTC_CLK out
#define SCM_RTC_CLK_PAD_MODE_AT    (0x02)  //   LFCLK pad = analog test mode
#define SCM_RTC_CLK_PAD_MODE_INPUT (0x03)  //   LFCLK pad = input
#define SCM_RTC_CLK_EXT_EN         (0x04)  // enable external clock input

/* SHASTA_REG_SCM_CPU_CLK (0x01F3) */
#define SCM_CPU_CLK_FREQ_TRIM_BM (0x3F)  // CPU frequency trim code (6 bits)
#define SCM_CPU_CLK_STANDBY      (0x40)  // leave oscillator bias on if disabled

/* SHASTA_REG_SCM_PASSWORD (0x01F4) */
#define SCM_PASSWORD_VALUE (0x00A5)  // required password value to set test pad modes

/* SHASTA_REG_SPI_CTRL (0x0204) */
#define SPI_CTRL_IEN_EN_WR (0x0001)  // enable DMA write interrupt
#define SPI_CTRL_IEN_EN_RD (0x0002)  // enable DMA read interrupt
#define SPI_CTRL_WR_FLAG   (0x0004)  // flag set at end of DMA write
#define SPI_CTRL_RD_FLAG   (0x0008)  // flag set at end of DMA read

/* Shasta SPI Command Interface */

#define SPI_CMD_MEM_ACCESS      (0x0000)
#define SPI_CMD_DBG_REG_ACCESS  (0x8000)
#define SPI_CMD_SYS_CTRL_ACCESS (0xA000)
#define SPI_CMD_READ            (0x0000)
#define SPI_CMD_WRITE           (0x4000)
#define SPI_CMD_DATA_MEM        (0x0000)
#define SPI_CMD_PROG_MEM        (0x2000)

#define SPI_CMD_SYS_CTRL_READ                                                                                          \
	(SPI_CMD_SYS_CTRL_ACCESS | SPI_CMD_READ)  // (0xA000)	// command bits for sys ctrl reg read
#define SPI_CMD_SYS_CTRL_WRITE                                                                                         \
	(SPI_CMD_SYS_CTRL_ACCESS | SPI_CMD_WRITE)  // (0xE000)	// command bits for sys ctrl reg write
#define SPI_CMD_DBG_REG_READ  (SPI_CMD_DBG_REG_ACCESS | SPI_CMD_READ)   // (0x8000)	// command bits for debug reg read
#define SPI_CMD_DBG_REG_WRITE (SPI_CMD_DBG_REG_ACCESS | SPI_CMD_WRITE)  // (0xC000)	// command bits for debug reg write
#define SPI_CMD_MEM_READ      (SPI_CMD_MEM_ACCESS | SPI_CMD_READ)       // (0x0000)	// command bits for mem read
#define SPI_CMD_MEM_WRITE     (SPI_CMD_MEM_ACCESS | SPI_CMD_WRITE)      // (0x4000)	// command bits for mem write

#ifdef __cplusplus
}
#endif

#endif /* CH_ASIC_SHASTA_H_ */
