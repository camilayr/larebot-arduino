#define MOTORS_NUM 3 //Numero de motores  

// q0 q1 q2
int pinsDir[] = {48,24,32}; // Pines de dirección de los motores  
int pinsStep[] = {46,22,30}; //Pines de step de los motores
int pinsEn[] = {52,26,34}; // Pines de enable 
int pinsGround[] = {28,36}; //Pin de ground q1 q2 
int pinsOpto[] = {50}; //Pin opto q0 
//Vectores para setup
boolean confEn[] = {1,0,0};

uint8_t estadoSerial;
int buff[8];
int p = 0;
void setup() {
  // put your setup code here, to run once:
      Serial.begin(38400);
      estadoSerial = 0;
      for (int i = 0; i < MOTORS_NUM; i++){
        pinMode(pinsDir[i], OUTPUT);
        pinMode(pinsStep[i], OUTPUT);
        pinMode(pinsEn[i], OUTPUT);
        
        digitalWrite(pinsStep[i],1);
        digitalWrite(pinsEn[i],confEn[i]);         
      }
      for (int i = 0; i<2; i++){
        pinMode(pinsGround[i], OUTPUT);

        digitalWrite(pinsGround[i], 0);
      }
      pinMode(pinsOpto[0],OUTPUT);
      digitalWrite(pinsOpto[0],1);

      moveMotors(1,1,1,0,5940,0);
      Serial.println("Ready to use");
      delay(100);      
}

void loop() {
  leerSerial();
  if (buff[0]==1){
    moveMotors(buff[1],buff[2],buff[3],buff[4],buff[5],buff[6]);
    //estadoSerial=0;
    buff[0]=0;
    Serial.println("END");
  }else if(buff[0]==2){
    Serial.println("Modo Universidad");
  }else if(buff[0]==3){
    Serial.println("Modo prueba");
  }
  }
void leerSerial(){
  if (Serial.available() > 0){
  buff[8]=0;
  int q = 0;
  //Se lee la cadena de caracteres que se envía 
  String c = Serial.readString();
  //Se obtiene la longitud de la cadena 
  int c_len = c.length() + 1;
  //Variable usada para almacenar la cadena como array
  char char_array[c_len];
  const char s[2] = ",";
  //Variable donde se almacena cada uno de los datos 
  char *dato;
  //Se convierte la cadena en array y se almacena en la variable
  c.toCharArray(char_array,c_len);
  //Se obtiene el primer dato antes de la primera coma 
  dato = strtok(char_array, s);
  
  while ( dato != NULL ) {
    int convertido = String(dato).toInt();
    buff[q]=convertido;
    //printf("%s\n", dato);
    dato=strtok(NULL,s);
    q++;
  }

  for (int m =0 ; m < q ; m++){
      Serial.println("buffer");
      Serial.println(buff[m]);
  }

  //Serial.println(command);
 }
}
void moveMotors(int dir0, int dir1, int dir2, int q0, int q1, int q2){
  int pasos[] = {q0,q1,q2};
  int mayorIndex = 0;
  int dir[] = {dir0, dir1, dir2};
  cambioDir(dir);
  delay(10);
  int mayor = 0; 
  for (int i = 0; i < MOTORS_NUM; i++){
    if (mayor < pasos[i]){
      mayor = pasos[i];
      mayorIndex = i;
    }else {
      mayor = mayor;
      mayorIndex = mayorIndex; 
    }
  }
  Serial.println("El mayor es y el indice es");
  Serial.println(mayor);
  Serial.println(mayorIndex);
  int j = 0; //Para q1
  int l = 0; //Para q2
  int w = 0; // Para q1 
  int e = 0; //Para q2
  int aux[] = {0,0};// k,m
  int indexes[] = {0,0};// k,m
  int b = 0; 
  for (int i = 0; i<3; i++){
    if ( i != mayorIndex){
      aux[b] = mayor/pasos[i];
      indexes[b] = i;
      b++;
    }
  }
  Serial.println("Los indices de los demas motores son:");
  Serial.println(indexes[0]);
  Serial.println(indexes[1]);
  Serial.println("Auxiliares:");
  Serial.println(aux[0]);
  Serial.println(aux[1]);
  for(int i=0; i<mayor; i++){
    w = i/aux[1]; //Truncar
    e = i/aux[0];
    if (w != j){
      //Serial.println (w);
      digitalWrite(pinsStep[indexes[1]],LOW);
    }
     if (i<mayor){
      digitalWrite(pinsStep[mayorIndex],LOW);
    }
     if (e != l){
      digitalWrite(pinsStep[indexes[0]],LOW);
    }
      delayMicroseconds(300);
//      Serial.println("Va");
    if (w != j){
      j = w;
      digitalWrite(pinsStep[indexes[1]],HIGH);
    }
     if (i<mayor){
      digitalWrite(pinsStep[mayorIndex],HIGH);
    }
     if (e != l){
      l = e;
      digitalWrite(pinsStep[indexes[0]],HIGH);
    }
      delayMicroseconds(300);
  }
    Serial.println("Final");
    delay(1000);
}
void pruebaMotor()
{
  Serial.println("Inicio");
  int changeDir[] = {1,1,1};
  cambioDir(changeDir);
  
  delay(10);
  int j = 0; 
  int l = 0;
  int w = 0;
  int e = 0;
  float k = 20000/4000;
  float m = 20000/1000;
  for(int i=0; i<20000; i++){
    w = i/k; //Truncar
    e = i/m;
    if (w != j){
      //Serial.println (w);
      digitalWrite(pinsStep[1],LOW);
    }
     if (i<20000){
      digitalWrite(pinsStep[2],LOW);
    }
     if (e != l){
      digitalWrite(pinsStep[0],LOW);
    }
      delayMicroseconds(100);
//      Serial.println("Va");
    if (w != j){
      j = w;
      digitalWrite(pinsStep[1],HIGH);
    }
     if (i<20000){
      digitalWrite(pinsStep[2],HIGH);
    }
     if (e != l){
      l = e;
      digitalWrite(pinsStep[0],HIGH);
    }
      delayMicroseconds(100);
  }
  
  delay(1000);
  //changeDir[] = {0,0,0};
  int changeDir2[]={0,0,0};
  cambioDir(changeDir2);
  delay(10);
  for(int i=0; i<20000; i++){
    w = i/k; 
    e = i/m;
    if (w != j){
      digitalWrite(pinsStep[1],LOW);
    }
     if (i<20000){
      digitalWrite(pinsStep[2],LOW);
    }
     if (e != l){
      digitalWrite(pinsStep[0],LOW);
    }
      delayMicroseconds(1000);
      //Serial.println("Va");
    if (w != j){
      j = w;
      digitalWrite(pinsStep[1],HIGH);
    }
     if (i<20000){
      digitalWrite(pinsStep[2],HIGH);
    }
     if (e != l){
      l = e;
      digitalWrite(pinsStep[0],HIGH);
    }
      delayMicroseconds(1000);
  }
  Serial.println("Final");
  delay(1000);
}

void cambioDir(int dir[]){
  // dir 1 giro positivo
  // dir 0 giro negativo 
  for(int i = 0; i<MOTORS_NUM; i++){
    digitalWrite(pinsDir[i],dir[i]);
  }
}

