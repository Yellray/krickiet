
// begin PWM-output
void setup() 
{
  pinMode(2, OUTPUT);
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  
  

  // Phase Correct PWM, non-inverting, TOP = OCR0A
  TCCR0A = _BV(COM0B1) | _BV(WGM00); // WGM00=1 → Phase Correct PWM, OCR0A jako TOP
  TCCR0B = _BV(CS01);                // prescaler = 8

  OCR0A = 88;   // TOP → częstotliwość ~3 kHz
  OCR0B = 0;   // wypełnienie 50%

  
  while(digitalRead(0)!=LOW)
  {
    digitalWrite(2,HIGH);
    delay(100);
    digitalWrite(2,LOW);
    delay(100);
  }
}

void softDelay(unsigned long count) {
  while(count--) {
    asm volatile("nop"); // 1 cykl CPU
  }
}

#define yepKrickiet OCR0A;
#define noKrickiet 0;

void krickiet()
{
  for(int i=0; i<10; i++)
  {
    OCR0B=noKrickiet;
    OCR0B=yepKrickiet;
    softDelay(1);
    OCR0B=20;
    OCR0B=yepKrickiet;
    softDelay(1);
    OCR0B=noKrickiet;
    softDelay(1);
    OCR0B=5;
    OCR0B=yepKrickiet;
  }
}

long waitFor;

void loop() 
{
  int factor = random(0,50);

  if(factor >= 5)
  {
    krickiet();
    delay(16);                     
    OCR0B=noKrickiet;
    delay(23);              
    krickiet();
    delay(16);     
    OCR0B=noKrickiet;
  
    if(factor >= 30)
    {
      for(int i=0; i<100; i++)
      {
        OCR0B=1;
        OCR0B=0;
      }

      krickiet();
      delay(16);                     
      OCR0B=noKrickiet;
      delay(23);              
      krickiet();  
      delay(16);                     
      OCR0B=noKrickiet;      
    }
    else if(factor <= 8)
    {
      for(int x=0; x<1; x++)
      {
        for(int i=0; i<10; i++)
        {
          OCR0B=50;
          delay(5);
          OCR0B=0;
          delay(5);
        }
      }

      delay(500);

      krickiet();
      delay(16);                     
      OCR0B=noKrickiet;
      delay(23);              
      krickiet();  
      delay(16);                     
      OCR0B=noKrickiet;
    }
  }
  else 
  {
    for(int x=0; x<1; x++)
    {
      for(int i=0; i<10; i++)
      {
        OCR0B=50;
        delay(5);
        OCR0B=0;
        delay(5);
      }
    }
  }

  if(digitalRead(0)!=LOW)
    waitFor = random(25000,35000)*60;
  else
    waitFor=2000;
    
  delay(waitFor);              




  
  if(0)
  {
  digitalWrite(PB2, HIGH); 
  
  analogWrite(PB1, 250); 
  delay(10);                     
  digitalWrite(PB1, LOW);
  delay(20);              
  analogWrite(PB1, 250); 
  delay(10);                     
  digitalWrite(PB1, LOW);

  delay(80);

  analogWrite(PB1, 250); 
  delay(10);                     
  digitalWrite(PB1, LOW);
  delay(20);              
  analogWrite(PB1, 250); 
  delay(10);                     
  digitalWrite(PB1, LOW);
          
  digitalWrite(PB2, LOW);    
  delay(2000);                      
  }
}
