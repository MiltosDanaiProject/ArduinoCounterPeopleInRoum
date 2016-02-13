int triger1=2;
int echo1=3;
int triger2=4;
int echo2=5;
int GreenLed=6;
int RedLed=7;
int first=0;
int peopleNum=0;
float DistanceNow1,DistanceNow2;
float doorDis1,doorDis2;

float DiferenceCM=30; // I diafora sta ekatosta gia na theorithi oti pernai anthropos 

///=============DISTANCE=============///
float distance (int SensorNum){
  // if SensorNum==1 tote asxoloume me ton 1 sensora ara 2,3 alios asxoloume me ton deftero ara 4,5
  float distanceCM;
  
  digitalWrite(SensorNum*2,LOW);
  delayMicroseconds(2);
  
  digitalWrite(SensorNum*2,HIGH);
  delayMicroseconds(10);
  digitalWrite(SensorNum*2,LOW);

  distanceCM = pulseIn((SensorNum*2)+1,HIGH);
  distanceCM=distanceCM/58;
  
  return (distanceCM);
}
///=============endDISTANCE=============///




void WaitUntilLeave (int SensorNum,float doorDis)
{
  int Dis=distance(SensorNum);
  
  while (abs(Dis-doorDis)<5)
  {Dis=distance(SensorNum);
  Serial.print("a");}
  delay(1500);
  

}





void setup() {
  pinMode(triger1,OUTPUT);
  pinMode(triger2,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(echo2,INPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(RedLed,OUTPUT);

  doorDis1=distance(1); // I proti apostasi pou exi apo tin porta otan anigi to programa 
  doorDis2=distance(2);

  Serial.begin(9600);
}



void loop() 
{
  DistanceNow1=distance(1);
  DistanceNow2=distance(2);
  if ((abs(DistanceNow1-doorDis1)<DiferenceCM)||(abs(DistanceNow2-doorDis2)<DiferenceCM))
  {
    if (abs(DistanceNow1-doorDis1)>=DiferenceCM){
      if (first==0){
          first=1;
      }  
      else if (first==2){ //tote perase prota apo ton 2 sensora kai oi anthropoi miothikan
        WaitUntilLeave(1,doorDis1);
        peopleNum=peopleNum-1;
        first=0;
        
      }
    }
    
    
    
    if (abs(DistanceNow2-doorDis2)>=DiferenceCM){
      if (first==0){
          first=2;
      }  
      else if (first==1){ //tote perase prota apo ton 2 sensora kai oi anthropoi miothikan
        WaitUntilLeave(2,doorDis2);
        peopleNum=peopleNum+1;
        first=0;
        
      }
    }
  }


  
  Serial.print(first);
  Serial.print(" ");
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
  else
  {
    digitalWrite(RedLed,HIGH);
    digitalWrite(GreenLed,LOW);
  }

  
}



















