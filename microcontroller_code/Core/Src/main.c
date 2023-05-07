/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../Components/nt35510/nt35510.h"
#include "stm32469i_discovery_sdram.h"
#include "stm32469i_discovery_qspi.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define N 2000		//input buffer size 1ms worth of adc reads

/* PARAMETERS BEGIN */
//#define TAU 1000.0 // RC time constant of input signal's decay. Set to zero to skip decay tail correction.
#define TAU 0.0		//TEST ONly REEEEEEEEE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define RISETIME 80 // Rise Time of Trapezoid; Must be greater than input signal's rise time. Larger means more noise filtering.
#define FLATTIME 40 // Duration of Trapezoidal flat top. Allows a longer Moving Average Filter.
#define MOVETIME 40 // Points for Moving Average Filter; Must be less than or equal to RISETIME or it will attenuate the peaks.

#define PEAKTHRESH_LOWER 200 // Lower threshold for Peak Detection. Peaks below this value will be ignored by the PeakDetector.
#define PEAKTHRESH_UPPER 5000 // Upper threshold for Peak Detection. Peaks above this value will be ignored by the PeakDetector.
/* PARAMETERS END */

/* Circular Buffer Sizes DO NOT ADJUST DIRECTLY */
#define Na 2
#define Nb (FLATTIME + 2*RISETIME)
#define Nc MOVETIME
#define Np 3

/* DISPLAY */
#define LCD_ORIENTATION_LANDSCAPE 0x01
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

DMA2D_HandleTypeDef hdma2d;

DSI_HandleTypeDef hdsi;

I2C_HandleTypeDef hi2c1;

LTDC_HandleTypeDef hltdc;

QSPI_HandleTypeDef hqspi;

TIM_HandleTypeDef htim12;
TIM_HandleTypeDef htim14;

SDRAM_HandleTypeDef hsdram1;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TouchGFXTask */
osThreadId_t TouchGFXTaskHandle;
const osThreadAttr_t TouchGFXTask_attributes = {
  .name = "TouchGFXTask",
  .stack_size = 4096 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
/* Definitions for dspTask */
osThreadId_t dspTaskHandle;
const osThreadAttr_t dspTask_attributes = {
  .name = "dspTask",
  .stack_size = 2056 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

//__IO uint16_t adcBuffer[N] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,112,225,337,450,562,675,787,900,1012,1125,1237,1350,1462,1575,1687,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1800,1937,2075,2212,2350,2487,2625,2762,2900,3037,3175,3312,3450,3587,3725,3862,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000,4000};     //adcBuffer to hold past adc reads
__IO uint16_t adcBuffer[N] = {0};	//adcBuffer to hold past adc reads
__IO uint16_t n;  						//index to increment adcBuffer write
__IO uint16_t pulseHeight;					//variable that passes pulse height to model
__IO uint16_t adcBufferFull;
volatile uint16_t adcRead;

/* Circular Buffer Indexes */
volatile unsigned na = 0; // Filter #1/#2
volatile unsigned nb = 0; // Filter #3
volatile unsigned nc = 0; // Filter #4
volatile unsigned np = 0; // Peak Detector

/* Circular Buffers */
volatile double V1[Na] = {0}; // Circular Buffer #1 - Raw Input
volatile double V2[Na] = {0}; // Circular Buffer #2 - Tail Correcting
volatile double V3[Nb] = {0}; // Circular Buffer #3 - Corrected Input to Shaper
volatile double V4[Nc] = {0}; // Circular Buffer #4 - Shaped Output to Moving Average
volatile double Vp[Np] = {0}; // Peak Detector Circular Buffer

/* Hack to typecast #define directives to not be ints for division */
static double dbTau = TAU;
static double dbRiseTime = RISETIME;
static double dbMoveTime = MOVETIME;

/* Tracker to prevent double reads of peaks */
volatile int PeakCooldown = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
static void MX_DMA2D_Init(void);
static void MX_DSIHOST_DSI_Init(void);
static void MX_FMC_Init(void);
static void MX_LTDC_Init(void);
static void MX_QUADSPI_Init(void);
static void MX_TIM14_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM12_Init(void);
void StartDefaultTask(void *argument);
extern void TouchGFX_Task(void *argument);

/* USER CODE BEGIN PFP */
void dsp_Task(void *argument);

/* Function Declarations */
double SmoothedTrapezoidalFilter(double Vin);
double PeakDetector(double Vin);
void CleanBuffers(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CRC_Init();
  MX_DMA2D_Init();
  MX_DSIHOST_DSI_Init();
  MX_FMC_Init();
  MX_LTDC_Init();
  MX_QUADSPI_Init();
  MX_TIM14_Init();
  MX_I2C1_Init();
  MX_TIM12_Init();
  MX_TouchGFX_Init();
  /* Call PreOsInit function */
  MX_TouchGFX_PreOSInit();
  /* USER CODE BEGIN 2 */
  /* creation of defaultTask */
  /* creation of TouchGFXTask */
  TouchGFXTaskHandle = osThreadNew(TouchGFX_Task, NULL, &TouchGFXTask_attributes);
  /*creation of dspTask*/
  dspTaskHandle = osThreadNew(dsp_Task, NULL, &dspTask_attributes);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/**
* @}
*/
/**
* @}
*/

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

/**
  * @brief DSIHOST Initialization Function
  * @param None
  * @retval None
  */
static void MX_DSIHOST_DSI_Init(void)
{

  /* USER CODE BEGIN DSIHOST_Init 0 */
  /* Activate XRES active low */
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, GPIO_PIN_RESET);

  HAL_Delay(20); /* wait 20 ms */

  /* Desactivate XRES */
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, GPIO_PIN_SET);

  /* Wait for 10ms after releasing XRES before sending commands */
  HAL_Delay(10);
  /* USER CODE END DSIHOST_Init 0 */

  DSI_PLLInitTypeDef PLLInit = {0};
  DSI_HOST_TimeoutTypeDef HostTimeouts = {0};
  DSI_PHY_TimerTypeDef PhyTimings = {0};
  DSI_LPCmdTypeDef LPCmd = {0};
  DSI_CmdCfgTypeDef CmdCfg = {0};

  /* USER CODE BEGIN DSIHOST_Init 1 */

  /* USER CODE END DSIHOST_Init 1 */
  hdsi.Instance = DSI;
  hdsi.Init.AutomaticClockLaneControl = DSI_AUTO_CLK_LANE_CTRL_DISABLE;
  hdsi.Init.TXEscapeCkdiv = 4;
  hdsi.Init.NumberOfLanes = DSI_TWO_DATA_LANES;
  PLLInit.PLLNDIV = 125;
  PLLInit.PLLIDF = DSI_PLL_IN_DIV2;
  PLLInit.PLLODF = DSI_PLL_OUT_DIV1;
  if (HAL_DSI_Init(&hdsi, &PLLInit) != HAL_OK)
  {
    Error_Handler();
  }
  HostTimeouts.TimeoutCkdiv = 1;
  HostTimeouts.HighSpeedTransmissionTimeout = 0;
  HostTimeouts.LowPowerReceptionTimeout = 0;
  HostTimeouts.HighSpeedReadTimeout = 0;
  HostTimeouts.LowPowerReadTimeout = 0;
  HostTimeouts.HighSpeedWriteTimeout = 0;
  HostTimeouts.HighSpeedWritePrespMode = DSI_HS_PM_DISABLE;
  HostTimeouts.LowPowerWriteTimeout = 0;
  HostTimeouts.BTATimeout = 0;
  if (HAL_DSI_ConfigHostTimeouts(&hdsi, &HostTimeouts) != HAL_OK)
  {
    Error_Handler();
  }
  PhyTimings.ClockLaneHS2LPTime = 28;
  PhyTimings.ClockLaneLP2HSTime = 33;
  PhyTimings.DataLaneHS2LPTime = 15;
  PhyTimings.DataLaneLP2HSTime = 25;
  PhyTimings.DataLaneMaxReadTime = 0;
  PhyTimings.StopWaitTime = 0;
  if (HAL_DSI_ConfigPhyTimer(&hdsi, &PhyTimings) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DSI_ConfigFlowControl(&hdsi, DSI_FLOW_CONTROL_BTA) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DSI_SetLowPowerRXFilter(&hdsi, 10000) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DSI_ConfigErrorMonitor(&hdsi, HAL_DSI_ERROR_NONE) != HAL_OK)
  {
    Error_Handler();
  }
  LPCmd.LPGenShortWriteNoP = DSI_LP_GSW0P_ENABLE;
  LPCmd.LPGenShortWriteOneP = DSI_LP_GSW1P_ENABLE;
  LPCmd.LPGenShortWriteTwoP = DSI_LP_GSW2P_ENABLE;
  LPCmd.LPGenShortReadNoP = DSI_LP_GSR0P_ENABLE;
  LPCmd.LPGenShortReadOneP = DSI_LP_GSR1P_ENABLE;
  LPCmd.LPGenShortReadTwoP = DSI_LP_GSR2P_ENABLE;
  LPCmd.LPGenLongWrite = DSI_LP_GLW_ENABLE;
  LPCmd.LPDcsShortWriteNoP = DSI_LP_DSW0P_ENABLE;
  LPCmd.LPDcsShortWriteOneP = DSI_LP_DSW1P_ENABLE;
  LPCmd.LPDcsShortReadNoP = DSI_LP_DSR0P_ENABLE;
  LPCmd.LPDcsLongWrite = DSI_LP_DLW_ENABLE;
  LPCmd.LPMaxReadPacket = DSI_LP_MRDP_ENABLE;
  LPCmd.AcknowledgeRequest = DSI_ACKNOWLEDGE_ENABLE;
  if (HAL_DSI_ConfigCommand(&hdsi, &LPCmd) != HAL_OK)
  {
    Error_Handler();
  }
  CmdCfg.VirtualChannelID = 0;
  CmdCfg.ColorCoding = DSI_RGB565;
  CmdCfg.CommandSize = 200;
  CmdCfg.TearingEffectSource = DSI_TE_EXTERNAL;
  CmdCfg.TearingEffectPolarity = DSI_TE_RISING_EDGE;
  CmdCfg.HSPolarity = DSI_HSYNC_ACTIVE_HIGH;
  CmdCfg.VSPolarity = DSI_VSYNC_ACTIVE_HIGH;
  CmdCfg.DEPolarity = DSI_DATA_ENABLE_ACTIVE_HIGH;
  CmdCfg.VSyncPol = DSI_VSYNC_RISING;
  CmdCfg.AutomaticRefresh = DSI_AR_DISABLE;
  CmdCfg.TEAcknowledgeRequest = DSI_TE_ACKNOWLEDGE_ENABLE;
  if (HAL_DSI_ConfigAdaptedCommandMode(&hdsi, &CmdCfg) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DSI_SetGenericVCID(&hdsi, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DSIHOST_Init 2 */

  /* USER CODE END DSIHOST_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AH;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AH;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 1;
  hltdc.Init.VerticalSync = 1;
  hltdc.Init.AccumulatedHBP = 2;
  hltdc.Init.AccumulatedVBP = 2;
  hltdc.Init.AccumulatedActiveW = 202;
  hltdc.Init.AccumulatedActiveH = 482;
  hltdc.Init.TotalWidth = 203;
  hltdc.Init.TotalHeigh = 483;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 200;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 480;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0xC0000000;
  pLayerCfg.ImageWidth = 200;
  pLayerCfg.ImageHeight = 480;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */
  __HAL_LTDC_DISABLE(&hltdc);
  DSI_LPCmdTypeDef LPCmd;

  HAL_DSI_Start(&hdsi);
  NT35510_Init(NT35510_FORMAT_RBG565, LCD_ORIENTATION_LANDSCAPE);
  HAL_DSI_ShortWrite(&hdsi, 0, DSI_DCS_SHORT_PKT_WRITE_P1, NT35510_CMD_DISPOFF, 0x00);

  LPCmd.LPGenShortWriteNoP = DSI_LP_GSW0P_DISABLE;
  LPCmd.LPGenShortWriteOneP = DSI_LP_GSW1P_DISABLE;
  LPCmd.LPGenShortWriteTwoP = DSI_LP_GSW2P_DISABLE;
  LPCmd.LPGenShortReadNoP = DSI_LP_GSR0P_DISABLE;
  LPCmd.LPGenShortReadOneP = DSI_LP_GSR1P_DISABLE;
  LPCmd.LPGenShortReadTwoP = DSI_LP_GSR2P_DISABLE;
  LPCmd.LPGenLongWrite = DSI_LP_GLW_DISABLE;
  LPCmd.LPDcsShortWriteNoP = DSI_LP_DSW0P_DISABLE;
  LPCmd.LPDcsShortWriteOneP = DSI_LP_DSW1P_DISABLE;
  LPCmd.LPDcsShortReadNoP = DSI_LP_DSR0P_DISABLE;
  LPCmd.LPDcsLongWrite = DSI_LP_DLW_DISABLE;
  HAL_DSI_ConfigCommand(&hdsi, &LPCmd);

  HAL_LTDC_SetPitch(&hltdc, 800, 0);
  __HAL_LTDC_ENABLE(&hltdc);
  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief QUADSPI Initialization Function
  * @param None
  * @retval None
  */
static void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  /* QUADSPI parameter configuration*/
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 1;
  hqspi.Init.FifoThreshold = 1;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 27;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_5_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */
  BSP_QSPI_DeInit();
  if(BSP_QSPI_Init() != QSPI_OK)
  {
    Error_Handler();
  }
  if(BSP_QSPI_EnableMemoryMappedMode() != QSPI_OK)
  {
    Error_Handler();
  }
  /* USER CODE END QUADSPI_Init 2 */

}

/**
  * @brief TIM12 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM12_Init(void)
{

  /* USER CODE BEGIN TIM12_Init 0 */

  /* USER CODE END TIM12_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM12_Init 1 */

  /* USER CODE END TIM12_Init 1 */
  htim12.Instance = TIM12;
  htim12.Init.Prescaler = 2250-1;
  htim12.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim12.Init.Period = 40-1;
  htim12.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim12.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim12) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 2;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM12_Init 2 */

  /* USER CODE END TIM12_Init 2 */
  HAL_TIM_MspPostInit(&htim12);

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 11-1;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 4-1;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 4/2;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim14, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */
  //HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);	//api to start timer14
  /* USER CODE END TIM14_Init 2 */
  HAL_TIM_MspPostInit(&htim14);

}

/* FMC initialization function */
static void MX_FMC_Init(void)
{

  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_SDRAM_TimingTypeDef SdramTiming = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the SDRAM1 memory initialization sequence
  */
  hsdram1.Instance = FMC_SDRAM_DEVICE;
  /* hsdram1.Init */
  hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_32;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_DISABLE;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_2;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 2;
  SdramTiming.ExitSelfRefreshDelay = 7;
  SdramTiming.SelfRefreshTime = 4;
  SdramTiming.RowCycleDelay = 7;
  SdramTiming.WriteRecoveryTime = 3;
  SdramTiming.RPDelay = 2;
  SdramTiming.RCDDelay = 2;

  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FMC_Init 2 */
  BSP_SDRAM_DeInit();
  if(BSP_SDRAM_Init() != SDRAM_OK)
  {
    Error_Handler();
  }
  /* USER CODE END FMC_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, RD_Pin|MCU_ACTIVE_Pin|CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, FRAME_RATE_Pin|VSYNC_FREQ_Pin|RENDER_TIME_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : D12_9_Pin D12_10_Pin D12_8_Pin */
  GPIO_InitStruct.Pin = D12_9_Pin|D12_10_Pin|D12_8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : D12_2_Pin D12_0_Pin D12_7_Pin */
  GPIO_InitStruct.Pin = D12_2_Pin|D12_0_Pin|D12_7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : D12_3_Pin D12_1_Pin */
  GPIO_InitStruct.Pin = D12_3_Pin|D12_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RD_Pin CS_Pin */
  GPIO_InitStruct.Pin = RD_Pin|CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : MCU_ACTIVE_Pin */
  GPIO_InitStruct.Pin = MCU_ACTIVE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(MCU_ACTIVE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : D12_4_Pin D12_6_Pin D12_5_Pin D12_11_Pin */
  GPIO_InitStruct.Pin = D12_4_Pin|D12_6_Pin|D12_5_Pin|D12_11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PK3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

  /*Configure GPIO pin : BUSY_Pin */
  GPIO_InitStruct.Pin = BUSY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUSY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : FRAME_RATE_Pin VSYNC_FREQ_Pin RENDER_TIME_Pin */
  GPIO_InitStruct.Pin = FRAME_RATE_Pin|VSYNC_FREQ_Pin|RENDER_TIME_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PH7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  //HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
/*This is effectively our main function. Current osThread alternates between touchgfxtask and this one*/
void dsp_Task(void *argument)
{
	unsigned i;
	double Vin;
	double Vout;
	double Vpeak;

	n=0;
	adcRead = 0;
	adcBufferFull = 0;

	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);	//api to start timer14
	//HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);	//api to start timer12  !!!delete this later
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);	//enable busy_pin exint !always comment out the other after MX generate
  for(;;)
  {
	  if(adcBufferFull==1)//when adcBuffer is full execute
	  {
		  /*Begin actual DSP stuff*/
		  /* Process batch of data */
		  	for (i = 0; i < N; i++)
		  	{
		  		Vin = adcBuffer[i];
		  		Vout = SmoothedTrapezoidalFilter(Vin); // Feed input samples into filter
		  		Vpeak = PeakDetector(Vout); // Feed filter output into peak detector
		  		// Single line: Vpeak = PeakDetector(SmoothedTrapezoidalFilter(INPUT[i]));

		  		if (Vpeak > 0)
		  		{
		  			// Add output code here
		  			// Note: there _could_ be multiple peaks in a single batch
		  			pulseHeight = Vpeak;
		  			osDelay(22);	//wait exactly this amount of time after updating pulseHeight to give model a chance
		  		}
		  	}

		  	/* Cleanup Buffers to not contaminate next processing batch */
		  	CleanBuffers();
		  /*End actual DSP stuff*/

		  n=0; //reset adcBuffer write index
		  adcBufferFull = 0;
		  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);	//reenable interrupts from adc
	  }
      //osDelay(1);
  }
}

// EXTI Line10 External Interrupt ISR Handler CallBackFun
//this executes every time BUSY has a rising edge signaling a new ADC value is ready to read
/*non-circular adcBuffer filled by interrupt
DSP filter task will read this non-circular adcBuffer when it has a chance to run
filter will read this adcBuffer as-if it were real-time data being input
(put adcBuffer values into own circular adcBuffer then do dsp algorithms)*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == BUSY_Pin) // If The INT Source Is EXTI Line[15:10] (PB12 Pin)
    {

    	//left shift bits of pins and bitwise or them together into one int
    	adcRead=
    							HAL_GPIO_ReadPin(GPIOB, D12_0_Pin)
								 |(HAL_GPIO_ReadPin(GPIOA, D12_1_Pin)<<1)
								 |(HAL_GPIO_ReadPin(GPIOB, D12_2_Pin)<<2)
								 |(HAL_GPIO_ReadPin(GPIOA, D12_3_Pin)<<3)
								 |(HAL_GPIO_ReadPin(GPIOC, D12_4_Pin)<<4)
								 |(HAL_GPIO_ReadPin(GPIOC, D12_5_Pin)<<5)
								 |(HAL_GPIO_ReadPin(GPIOC, D12_6_Pin)<<6)
								 |(HAL_GPIO_ReadPin(GPIOB, D12_7_Pin)<<7)
								 |(HAL_GPIO_ReadPin(GPIOG, D12_8_Pin)<<8)
								 |(HAL_GPIO_ReadPin(GPIOG, D12_9_Pin)<<9)
								 |(HAL_GPIO_ReadPin(GPIOG, D12_10_Pin)<<10)
								 |(HAL_GPIO_ReadPin(GPIOC, D12_11_Pin)<<11);

    	if(n>=N)
    	{
    		adcBufferFull = 1;
    		HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); //disable interrupt when adcBuffer is full
    	}
    	else
    	{
			adcBuffer[n] = adcRead;	//write temp adc value to buffer
			n++;
    	}

    }
}

/* SmoothedTrapezoidalFilter
 * Takes in voltage samples and shapes them into smoothed-top trapezoids.
 * Input is first pole-zero corrected (if TAU > 0),
 *	then sent to a trapezoidal shaping filter,
 *	then sent to a moving average filter.
 * Input is expected to be either a square step signal (TAU = 0)
 *	or tail pulses with decay time constant TAU.
 * Shaping time is determined by RISETIME and FLATTIME.
 * Smoothing is determined by MOVETIME.
 * Vin: Input voltage sample.
 * Returns the shaped output voltage of the filter.
 */
double SmoothedTrapezoidalFilter(double Vin) {
	unsigned k;
	double Vav_t1;
	double Vav_t2;
	double Vav_t3;

	V1[na] = Vin; // Input into Circular Buffer

	if (dbTau > 0) {
		/* Correct for Decay; turn tail pulse into square steps */
		V2[na] = (V2[(na + 1) % Na] + V1[na] - V1[(na + 1) % Na] * (1 - 1 / dbTau));
		V3[nb] = V2[na];
	} else {
		/* Decay rate not specified; skip */
		V3[nb] = V1[na];
	}

	/* Trapezoid Shaping Filter */
	Vav_t1 = 0.0;
	Vav_t2 = 0.0;
	// Difference of two moving averages, separated by FLATTIME samples
	for (k = 0; k < RISETIME; k++) {
		Vav_t1 = Vav_t1 + V3[(nb + k) % Nb]; // Moving Average #1
		Vav_t2 = Vav_t2 + V3[(RISETIME + FLATTIME + nb + k) % Nb]; // Moving Average #2
	}
	V4[nc] = (Vav_t2 - Vav_t1) / dbRiseTime; // Difference of Moving Averages

	/* Moving Average Filter (low-pass smoothing) */
	Vav_t3 = 0.0;
	for (k = 0; k < MOVETIME; k++) {
		Vav_t3 = Vav_t3 + V4[(nc + k) % Nc];
	}
	Vav_t3 = Vav_t3 / dbMoveTime;

	/* Increment Buffer Indexes */
	if (++na >= Na) {
		na = 0;
	}
	if (++nb >= Nb) {
		nb = 0;
	}
	if (++nc >= Nc) {
		nc = 0;
	}

	return Vav_t3;
}

/* PeakDetector
 * Takes in voltage samples and processes them to find peak values.
 * Rejects all peaks below PEAKTHRESH_LOWER and above PEAKTHRESH_UPPER thresholds.
 * Rejects duplicate peaks found within FLATTIME samples.
 * Vin: Input voltage sample.
 * Returns the peak voltage value if a valid peak is detected.
 * Returns 0 if no valid peak is detected.
 */
double PeakDetector(double Vin) {
	double Vpeak = 0.0;
	double Vprev;
	double Vcurr;
	double Vnext;

	Vp[np] = Vin; // Input into Circular Buffer

	if (PeakCooldown > 0) {
		/* Recently detected a peak; ignore subsequent input for now */
		PeakCooldown--;
	} else {
		/* Check for a valid peak */
		// Circular buffer magic
		Vprev = Vp[(np + 1) % Np]; // Equivalent to Vp[np - 2]
		Vcurr = Vp[(np + 2) % Np]; // Equivalent to Vp[np - 1]
		Vnext = Vp[np];

		if ((Vcurr >= Vprev) && (Vcurr >= Vnext) && // If Vcurr is a "high point"...
			(Vcurr >= PEAKTHRESH_LOWER) && (Vcurr <= PEAKTHRESH_UPPER)) { // and within thresholds...
			Vpeak = Vcurr; // Register as a peak value
			PeakCooldown = FLATTIME; // Prevent double-counting noisy peaks
		}
	}

	/* Increment Buffer Index */
	if (++np >= Np) {
		np = 0;
	}

	return Vpeak;
}

/* CleanBuffers
 * Sets all elements of the circular buffers used by
 *	SmoothedTrapezoidalFilter() and PeakDetector() to 0.0
 */
void CleanBuffers(void) {
	unsigned i;

	for (i = 0; i < Na; i++) {
		V1[i] = 0.0;
		V2[i] = 0.0;
	}
	for (i = 0; i < Nb; i++) {
		V3[i] = 0.0;
	}
	for (i = 0; i < Nc; i++) {
		V4[i] = 0.0;
	}
	for (i = 0; i < Np; i++) {
		Vp[i] = 0.0;
	}

	na = 0;
	nb = 0;
	nc = 0;
	np = 0;
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
