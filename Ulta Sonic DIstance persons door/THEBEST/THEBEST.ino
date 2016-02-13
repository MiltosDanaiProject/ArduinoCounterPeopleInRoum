int triger1=2;
int echo1=3;
int triger2=4;
int echo2=5;
int peopleNum=0;
int GreenLed=6;
int RedLed=7;
float DistanceNow1,DistanceNow2;
float doorDis1,doorDis2;

float DiferenceCM=30; // I diafora sta ekatosta gia na theorithi oti pernai anthropos 


///=============DISTANCE=============///
float distance (int SensorNum){
  // if SensorNum==1 tote asxoloume me ton 1 sensora ara 2,3 alios asxoloume me ton deftero ara 4,5
  float distanceCM=200;

  while(distanceCM>150)
  {
    digitalWrite(SensorNum*2,LOW);
    delayMicroseconds(2);
    
    digitalWrite(SensorNum*2,HIGH);
    delayMicroseconds(10);
    digitalWrite(SensorNum*2,LOW);
  
    distanceCM = pulseIn((SensorNum*2)+1,HIGH);
    distanceCM=distanceCM/58;
  }
  return (distanceCM);
}
///=============endDISTANCE=============///


void waiting(float doorDis1,float doorDis2)
{
  float Dis1=distance(1);  float Dis2=distance(2);

  while((abs(Dis1-doorDis1)>1) || (abs(Dis2-doorDis2)>8))
  {
    Dis1=distance(1);
    Dis2=distance(2);

    Serial.print(abs(Dis1-doorDis1));
    Serial.print(" a ");
    Serial.print(abs(Dis2-doorDis2));
    Serial.print(" a ");
    Serial.print(Dis2);
    Serial.print(" a ");
    Serial.print(doorDis2);
    Serial.print(" a ");
    Serial.print(Dis1);
    Serial.print(" a ");
    Serial.println(doorDis1);
  }
   delay(200);
}


void setup() {
  pinMode(triger1,OUTPUT);
  pinMode(triger2,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(echo2,INPUT);

  delay(200);
  doorDis1=distance(1); // I proti apostasi pou exi apo tin porta otan anigi to programa 
  delay(15);
  doorDis2=distance(2);
  delay(15);
  Serial.begin(9600);
}

void loop() 
{
  DistanceNow1=distance(1);
  DistanceNow2=distance(2);
  
  if (abs(DistanceNow1-doorDis1)>=DiferenceCM)
  {
    waiting(doorDis1,doorDis2);
    peopleNum+=1;
    delay(200);
  }
  
  DistanceNow1=distance(1);
  DistanceNow2=distance(2);
  if (abs(DistanceNow2-doorDis2)>=DiferenceCM)
  {
    waiting(doorDis1,doorDis2);
    peopleNum-=1;
    delay(200);
  }

  Serial.print(peopleNum);
  Serial.print(" ");
  Serial.print(DistanceNow1);
  Serial.print(" ");
  Serial.println(DistanceNow2);
  
  if (peopleNum==0)
  {
    digitalWrite(GreenLed,HIGH);
    digitalWrite(RedLed,LOW);
  }
  else if (peopleNum>0)
  {
    digitalWrite(RedLed,HIGH);
    digitalWrite(GreenLed,LOW);
  }
}






