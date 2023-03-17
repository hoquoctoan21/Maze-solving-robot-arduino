#define m1 7  //Right Motor MA1
#define m2 6  //Right Motor MA2
#define m3 9  //Left Motor MB1
#define m4 8  //Left Motor MB2
#define e1 11  //Right Motor Enable Pin EA
#define e2 10 //Left Motor Enable Pin EB

//**********5 Channel IR Sensor Connection**********//
#define ir1 2
#define ir2 3
#define ir3 12
#define ir4 4
#define ir5 5

//*************************************************//
char path[30] = {};
int pathLength;
int readLength;
s
//************************************************//
void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
}

void readingSensor(){
  //Reading Sensor Values
  int s1 = digitalRead(ir1);  //Left Most Sensor
  int s2 = digitalRead(ir2);  //Left Sensor
  int s3 = digitalRead(ir3);  //Middle Sensor
  int s4 = digitalRead(ir4);  //Right Sensor
  int s5 = digitalRead(ir5);  //Right Most Sensor
}

void loop() {
  // readingSensor();
  int s1 = digitalRead(ir1);  //Left Most Sensor
  int s2 = digitalRead(ir2);  //Left Sensor
  int s3 = digitalRead(ir3);  //Middle Sensor
  int s4 = digitalRead(ir4);  //Right Sensor
  int s5 = digitalRead(ir5);  //Right Most Sensor
  
  //turnleft
  if(s1 == 1){
    //stop if all sensor is HIGH
    if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1)){
      path[pathLength] = "D";
      pathLength++;
      stop();

    }else{
      analogWrite(e1, 120); //you can adjust the speed of the motors from 0-255
      analogWrite(e2, 120);
        turnLeft();
        delay(200);
        path[pathLength] = "L";
        pathLength++;
    }

  }else{
    //forward
    if(s3 == 1 && s1 == 0 ){
      path[pathLength] = "S";
      pathLength++;
      speed();
      forward();
      
    }
    // fix line forward
      if(s2 == 1  && s1 == 0 && s5 == 0){
        speed();
        turnLeft();
        }  
      if(s4 == 1  && s5 == 0 && s1 == 0){
        speed();
        turnRight();
      }
    
    //turnright
    if(s5 == 1 && s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 ){
      path[pathLength] = "R";
      pathLength++;
      speed();
      turnRight();
    }
  }

  //turnaround
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0)){
      path[pathLength] = "B";
      pathLength++;
        analogWrite(e1, 100); //you can adjust the speed of the motors from 0-255
        analogWrite(e2, 100);
        turnAround();
  }
  // stop
  
}
void shortpath(int path[], int pathLength){
  int action;
   for(int i = 0; i <= pathLength-2; i++)
    {
      action = shortpath[i];
      if (action == 'B'){
        if(path[i-1] == 'L' && path[i+1] == 'R'){
          path[i] = 'B';
          path[i-1] = 0;
          path[i+1] = 0;
    
        }
        if(path[i-1] == 'L' && path[i+1] == 'S'){
          path[i] = 'R';
          path[i-1] = 0;
          path[i+1] = 0;
        }
        if(path[i-1] == 'R' && path[i+1] == 'L'){
          path[i] = 'B';
          path[i-1] = 0;
          path[i+1] = 0;
        }
        if(path[i-1] == 'S' && path[i+1] == 'L'){
          path[i] = 'R';
          path[i-1] = 0;
          path[i+1] = 0;
        }
        if(path[i-1] == 'S' && path[i+1] == 'S'){
          path[i] = 'B';
          path[i-1] = 0;
          path[i+1] = 0;
        }
         if(path[i-1] == 'L' && path[i+1] == 'L'){
          path[i] = 'S';
          path[i-1] = 0;
          path[i+1] = 0;
        }
      i=-1;
      }
    }
}
void doneGoing(int path[], int pathLength){
  delay(5000);
  int action;
  while(action != 'D')
  {
  for(int i=0; i<= pathLength - 1;i++){
    action = path[i];
    
    if(action == 'L' && digitalRead(ir1) == 1){
      speed();
      turnLeft();
      delay(200);
    }
    else if(action == 'R' && digitalRead(ir5) == 1){
      speed();
      turnRight();
      delay(200);
    }
    else if(action == 'S' && digitalRead(ir3) == 1){
      speed();
      forward();
      delay(200);
    }else{
      speed();
      forward();
    }
  }
  }
}
void Delete(int arr[], int &n, int index){
    //neu dia chi xoa nho hon 0 thi xoa phan tu dau tien
    if(index < 0){
        index = 0;
    }
    //neu dia chi xoa lon hon hoac bang n thi xoa phan tu cuoi cung
    if(index >= n){
        index = n - 1;
    }
    // Dich chuyen mang ve ben trai tu vi tri xoa
    for(int i = index; i < n - 1; i++){
        arr[i] = arr[i+1];
    }
    //sau khi xoa giam so luong phan tu mang
    n--;
}
void speed(){
    analogWrite(e1, 100); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 100);
}
void turnLeft(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
}
void turnRight(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);  
}
void forward(){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
}
void stop(){
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
}
void turnAround(){
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}
