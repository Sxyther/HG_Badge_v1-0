
/**********************/
/* Global Definitions */
/**********************/
#define LED1  A2
#define LED2  A3
#define LED3  3
#define LED4  4
#define LED5  7
#define LED6  6
#define LED7  5
#define LIGHT_SENSOR  A0
#define BUTTON  2

#define GENERAL_DELAY   100
#define MAX_DEMOS       4
#define BAUDRATE        9600

#define LIGHT_SCALE     (1024/7)

/********************/
/*Prototype Section */
/********************/
void rotate_right(void); 
void rotate_left(void); 
void ambient_light(void);
void blink_all(void);




/*************************************/
/* general state machine declaration */
/*************************************/
void (*const smStateMachine[])(void) =
{
  rotate_left,
  rotate_right,
  blink_all,
  ambient_light,
};

/********************/
/* Global Variables */
/********************/
unsigned char u8StateMachineCounter=0;


/*****************************************************************************************************/
void pin_ISR() 
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) 
  {
    u8StateMachineCounter++;
    if(u8StateMachineCounter==MAX_DEMOS)
    {
      u8StateMachineCounter=0;  
    }
    Serial.print("Demo: ");
    Serial.println(u8StateMachineCounter);
  }
  last_interrupt_time = interrupt_time;
}


/*****************************************************************************************************/
void setup() 
{
  Serial.begin(BAUDRATE);

  /* Declare LED pins as outputs */
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(LED6,OUTPUT);
  pinMode(LED7,OUTPUT);

  pinMode(BUTTON,INPUT_PULLUP);
  // Attach an interrupt to the ISR vector
  attachInterrupt(0, pin_ISR, FALLING);

}

/*****************************************************************************************************/
void blink_all(void)
{
  digitalWrite(LED1,HIGH);  
  digitalWrite(LED2,HIGH);  
  digitalWrite(LED3,HIGH);  
  digitalWrite(LED4,HIGH);  
  digitalWrite(LED5,HIGH);  
  digitalWrite(LED6,HIGH);  
  digitalWrite(LED7,HIGH);
  delay(GENERAL_DELAY);  
  digitalWrite(LED1,LOW);  
  digitalWrite(LED2,LOW);  
  digitalWrite(LED3,LOW);  
  digitalWrite(LED4,LOW);  
  digitalWrite(LED5,LOW);  
  digitalWrite(LED6,LOW);  
  digitalWrite(LED7,LOW);
  delay(GENERAL_DELAY);  
}

/*****************************************************************************************************/
void ambient_light(void) 
{
  int light=0;

  light= analogRead(LIGHT_SENSOR)/LIGHT_SCALE;
  
  if(light>=1)
    digitalWrite(LED1,HIGH);
  else
    digitalWrite(LED1,LOW);

  if(light>=2)
    digitalWrite(LED2,HIGH);
  else
    digitalWrite(LED2,LOW);

  if(light>=3)
    digitalWrite(LED3,HIGH);
  else
    digitalWrite(LED3,LOW);
  
  if(light>=4)
    digitalWrite(LED4,HIGH);
  else
    digitalWrite(LED4,LOW);
  
  if(light>=5)
    digitalWrite(LED5,HIGH);
  else
    digitalWrite(LED5,LOW);
  
  if(light>=6)
    digitalWrite(LED6,HIGH);
  else
    digitalWrite(LED6,LOW);

   if(light>=7)
    digitalWrite(LED7,HIGH);
  else
    digitalWrite(LED7,LOW);

  //Serial.println(light);

  
}

/*****************************************************************************************************/
void rotate_left(void) 
{
  digitalWrite(LED1,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED2,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED3,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED4,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED5,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED6,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED7,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED1,LOW);
  delay(GENERAL_DELAY);
  digitalWrite(LED2,LOW);
  delay(GENERAL_DELAY);
  digitalWrite(LED3,LOW);
  delay(GENERAL_DELAY);
  digitalWrite(LED4,LOW);
  delay(GENERAL_DELAY);
  digitalWrite(LED5,LOW);
  delay(GENERAL_DELAY);
  digitalWrite(LED6,LOW);
  delay(GENERAL_DELAY);
  digitalWrite(LED7,LOW);
  delay(GENERAL_DELAY);

}

/*****************************************************************************************************/
void rotate_right(void) 
{
  digitalWrite(LED7,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED6,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED5,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED4,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED3,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED2,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED1,HIGH);
  delay(GENERAL_DELAY);
  digitalWrite(LED7,LOW);
  delay(GENERAL_DELAY);
  digitalWrite(LED6,LOW);
  delay(GENERAL_DELAY);
  digitalWrite(LED5,LOW);
  delay(GENERAL_DELAY);
  digitalWrite(LED4,LOW);
  delay(GENERAL_DELAY);
  digitalWrite(LED3,LOW);
  delay(GENERAL_DELAY);
  digitalWrite(LED2,LOW);
  delay(GENERAL_DELAY);
  digitalWrite(LED1,LOW);
  delay(GENERAL_DELAY);

}

/*****************************************************************************************************/
void loop() 
{
  /* Call State machines */
  smStateMachine[u8StateMachineCounter]();
}
