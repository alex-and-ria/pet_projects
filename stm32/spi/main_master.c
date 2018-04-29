/*
 * This is one of two projects;
 * This project describes master's behavior in SPI communication.
 * Operation sequence:
 * 1) Slaves configuring their SPI interfaces followed by sending confirmation as rising edge on
 * master's PA0 and PA1 GPIO pins;
 * 2) Master accepts this confirmation, selects slave for communication via PWM (slaves using pwm input
 * mode to distinguish which of them is selected), receives confirmation from slaves (falling edge on PA0
 * or PA1 pin), enables SPI and starts communication.
 * 3) DMA is used for communication;
 * 4) Rising edge at PA0 (for first slave) or at PA1 (for second slave) is a signal that the
 * message transmitted and new SPI communication starts.
 * 5) SPI interfaces disabled, reconfigured and new iteration starts. Master waits for answer from
 * slave;
 * 6) New iteration of SPI communication starts;
 * PA2 -- TIM2_CH3;
 * PA5 SPI1_SCK; PA7 SPI1_MOSI; PA6 SPI1_MISO;
 * master should be started first;
 */

#include<stm32f4xx_rcc.h>
#include<stm32f4xx_gpio.h>
#include<stm32f4xx_exti.h>
#include<stm32f4xx_tim.h>
#include<stm32f4xx_dma.h>
#include<stm32f4xx_spi.h>
#include<stm32f4xx_syscfg.h>
#include<stm32f4xx_pwr.h>
#include<misc.h>

#define RX_BUF_SZ 50
#define s1_dc 25
#define s2_dc 75

uint8_t tx_buf[]="Hi, initiation SPI communication, master unit \0";
uint8_t rx_buf[RX_BUF_SZ];
volatile uint8_t is_s1=0,is_s2=0,s1_spi_ready=0,s2_spi_ready=0,is_spi_en=0,s1_strt=1;

void init_gpios(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//PA0 and PA1 -- pins for interrupts;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);//enable system configuration controller to
//manage the external interrupt line connection to the GPIOs;
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode=GPIO_Mode_IN;//to use external interrupt lines, the port must be
//configured in input mode;
	gpio_struct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	gpio_struct.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA,&gpio_struct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource1);

	EXTI_InitTypeDef exti_struct;
	exti_struct.EXTI_Line=EXTI_Line0/*|EXTI_Line1*/;//PA0 -- line0;
	exti_struct.EXTI_LineCmd=ENABLE;//enable interrupt;
	exti_struct.EXTI_Mode=EXTI_Mode_Interrupt;//selected interrupt mode;
	exti_struct.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_Init(&exti_struct);
	exti_struct.EXTI_Line=EXTI_Line1;//PA1 -- line1;
	EXTI_Init(&exti_struct);

	NVIC_InitTypeDef nvic_struct;
	nvic_struct.NVIC_IRQChannel=EXTI0_IRQn/*|EXTI1_IRQn*/;
	nvic_struct.NVIC_IRQChannelCmd=ENABLE;
	nvic_struct.NVIC_IRQChannelPreemptionPriority=10;
	nvic_struct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&nvic_struct);
	nvic_struct.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_Init(&nvic_struct);

/*	RCC_ClocksTypeDef rcc_clocks;
 * 	RCC_GetClocksFreq(&rcc_clocks);
 * SYSCLK_Frequency	16000000
 * HCLK_Frequency	16000000
 * PCLK1_Frequency	16000000
 * PCLK2_Frequency	16000000
 */

//pwm configuration
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2);//PA2 -- TIM2_CH3;
	gpio_struct.GPIO_Mode=GPIO_Mode_AF;
	gpio_struct.GPIO_OType=GPIO_OType_PP;
	gpio_struct.GPIO_Pin=GPIO_Pin_2;
	gpio_struct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	gpio_struct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio_struct);

//spi configuration;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);

	gpio_struct.GPIO_Mode=GPIO_Mode_AF;
	gpio_struct.GPIO_OType=GPIO_OType_PP;
	gpio_struct.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_6;//SPI1_SCK, SPI1_MOSI and SPI1_MISO;
	gpio_struct.GPIO_PuPd=GPIO_PuPd_DOWN;
	gpio_struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_struct);

}

void strt();

void EXTI0_IRQHandler(){
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)){//if current pin state is '1', rising edge detected;
		if(s1_spi_ready==0){
			s1_spi_ready=1;
		}
		else{
			is_s1=0;
			s1_spi_ready=0;
		}
	}
	else{
		if(s1_spi_ready){
			is_s1=1;
			strt();
		}
	}
	EXTI_ClearFlag(EXTI_Line0);
}

void EXTI1_IRQHandler(){
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)){//if current pin state is '1', rising edge detected;
		if(s2_spi_ready==0){
			s2_spi_ready=1;
		}
		else{
			is_s2=0;
			s2_spi_ready=0;
		}
	}
	else{
		if(s2_spi_ready){
			is_s2=1;
			strt();
		}
	}
	EXTI_ClearFlag(EXTI_Line1);
}

void init_pwm(uint32_t pwm_dc){
	TIM_TimeBaseInitTypeDef tim_struct;
	tim_struct.TIM_ClockDivision=TIM_CKD_DIV1;//no clock division;
	tim_struct.TIM_CounterMode=TIM_CounterMode_Up;
	tim_struct.TIM_Period=99;//period consists of 100 ticks;
	tim_struct.TIM_Prescaler=0;//CK_CNT is equal to fCK_PSC;
	tim_struct.TIM_RepetitionCounter=0;//This parameter is valid only for TIM1 and TIM8;
	TIM_TimeBaseInit(TIM2,&tim_struct);
	TIM_Cmd(TIM2,ENABLE);

	TIM_OCInitTypeDef tim_oc_struct;
	tim_oc_struct.TIM_OCMode=TIM_OCMode_PWM1;//PWM mode 1 - In upcounting, channel 1 is active
//as long as TIMx_CNT<TIMx_CCR1 else inactive;
	tim_oc_struct.TIM_OCPolarity=TIM_OCPolarity_High;
	tim_oc_struct.TIM_OutputState=TIM_OutputState_Enable;
	tim_oc_struct.TIM_Pulse=pwm_dc;//TIM_Pulse/(TIM_Period+1)==duty_cycle;
	TIM_OC3Init(TIM2,&tim_oc_struct);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
}

void init_dma(){//SPI1_TX -- channel 3, stream 3; SPI1_RX -- channel 3 stream 0; (dma2);
	DMA_InitTypeDef dma_struct;

//SPI_TX configuration;
	dma_struct.DMA_Channel=DMA_Channel_3;
	dma_struct.DMA_PeripheralBaseAddr=(uint32_t)(&(SPI1->DR));
	dma_struct.DMA_Memory0BaseAddr=(uint32_t)tx_buf;
	dma_struct.DMA_DIR=DMA_DIR_MemoryToPeripheral;
	dma_struct.DMA_BufferSize=sizeof(tx_buf)/2;//transfer performed by half-words;
	dma_struct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//SPI1->DR is the same register for all
//transfers;
	dma_struct.DMA_MemoryInc=DMA_MemoryInc_Enable;//moving through the tx_buf;
	dma_struct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;//SPI allows to transmit data by
//half-words;
	dma_struct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	dma_struct.DMA_Mode=DMA_Mode_Normal;
	dma_struct.DMA_Priority=DMA_Priority_Medium;
	dma_struct.DMA_FIFOMode=DMA_FIFOMode_Disable;//direct mode selected;
	dma_struct.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	dma_struct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream3,&dma_struct);//SPI1_TX;
	DMA_Cmd(DMA2_Stream3,ENABLE);

//SPI_RX configuration;
	dma_struct.DMA_Memory0BaseAddr=(uint32_t)rx_buf;
	dma_struct.DMA_DIR=DMA_DIR_PeripheralToMemory;
	dma_struct.DMA_BufferSize=RX_BUF_SZ/2-1;
	DMA_Init(DMA2_Stream0,&dma_struct);//SPI1_RX;
	DMA_Cmd(DMA2_Stream0,ENABLE);
}

void init_spi(){//PA5 SPI1_SCK; PA7 SPI1_MOSI; PA6 SPI1_MISO;
	SPI_I2S_DeInit(SPI1);
	SPI_InitTypeDef spi_struct;
	spi_struct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	spi_struct.SPI_Mode=SPI_Mode_Master;
	spi_struct.SPI_DataSize=SPI_DataSize_16b;
	spi_struct.SPI_CPOL=SPI_CPOL_Low;
	spi_struct.SPI_CPHA=SPI_CPHA_1Edge;
	spi_struct.SPI_NSS=SPI_NSS_Soft;
	spi_struct.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;
	spi_struct.SPI_FirstBit=SPI_FirstBit_MSB;
	spi_struct.SPI_CRCPolynomial=7;
	SPI_Init(SPI1,&spi_struct);
	//SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);
	//SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Rx,ENABLE);
	//SPI_Cmd(SPI1,ENABLE);
}

void strt(){
	TIM_Cmd(TIM2,DISABLE);//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,DISABLE);//disabling pwm;
	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);//starting dma_tx;
	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Rx,ENABLE);//starting dma_rx;
	SPI_Cmd(SPI1,ENABLE);//starting spi;
	is_spi_en=1;


}

void re_strt(){
	if(is_spi_en&&(!is_s1)&&(!is_s2)){//spi enabled and slave send notification that it finished it's
//data transfer;
		if(DMA_GetFlagStatus(DMA2_Stream3,DMA_FLAG_TCIF3)&&
				DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0)&&
				!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY)){
//SPI1_TX -- channel 3, stream 3; SPI1_RX -- channel 3 stream 0; (dma2);
//master finished it's data transfer;
			DMA_ClearFlag(DMA2_Stream3,DMA_FLAG_TCIF3);
			DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);
			DMA_Cmd(DMA2_Stream3,DISABLE);
			DMA_Cmd(DMA2_Stream0,DISABLE);
			SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,DISABLE);//starting dma_tx;
			SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Rx,DISABLE);//starting dma_rx;
			SPI_Cmd(SPI1,DISABLE);//starting spi;
			is_spi_en=0;
			uint8_t tmp_i=0;
			for(tmp_i=0;tmp_i<sizeof(rx_buf);tmp_i++){
				rx_buf[tmp_i]=0;
			}
			s1_strt=!s1_strt;
			init_pwm((s1_strt)?s1_dc:s2_dc);
			init_dma();
			init_spi();
		}
	}
}

int main(void){
	init_gpios();
	init_pwm((s1_strt)?s1_dc:s2_dc);
	init_dma();
	init_spi();

    while(1){
    	re_strt();


    }
}
