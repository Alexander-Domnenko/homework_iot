int led_pin7 = 7;
int led_pin8 = 8;
int led_pin11 = 11;
int led_pin12 = 12;

void setup()
{
  pinMode(led_pin7, OUTPUT);
  pinMode(led_pin8, OUTPUT);
  pinMode(led_pin11, OUTPUT);
  pinMode(led_pin12, OUTPUT);
}
void loop()
{
  //1
  digitalWrite(led_pin7, HIGH);
  digitalWrite(led_pin8, LOW);
  digitalWrite(led_pin11, LOW);
  digitalWrite(led_pin12, HIGH);
  delay(2000);
  //2
  digitalWrite(led_pin7, HIGH);
  digitalWrite(led_pin8, LOW);
  digitalWrite(led_pin11, HIGH);
  digitalWrite(led_pin12, LOW);
  delay(2000);
  //3
  digitalWrite(led_pin7, LOW);
  digitalWrite(led_pin8, HIGH);
  digitalWrite(led_pin11, LOW);
  digitalWrite(led_pin12, HIGH);
  delay(2000);
  //4
  digitalWrite(led_pin7, LOW);
  digitalWrite(led_pin8, HIGH);
  digitalWrite(led_pin11, HIGH);
  digitalWrite(led_pin12, LOW);
  delay(2000);
  //1,2
  digitalWrite(led_pin7, HIGH);
  digitalWrite(led_pin8, LOW);
  digitalWrite(led_pin11,LOW );
  digitalWrite(led_pin12, LOW);
  delay(2000);
  //3,4
  digitalWrite(led_pin7, LOW);
  digitalWrite(led_pin8, HIGH);
  digitalWrite(led_pin11,LOW );
  digitalWrite(led_pin12, LOW);
  delay(2000);
  //1,3
  digitalWrite(led_pin7, HIGH);
  digitalWrite(led_pin8, HIGH);
  digitalWrite(led_pin11, LOW);
  digitalWrite(led_pin12, HIGH);
  delay(2000);
  //2,4
  digitalWrite(led_pin7, HIGH);
  digitalWrite(led_pin8, HIGH);
  digitalWrite(led_pin11, HIGH);
  digitalWrite(led_pin12, LOW);
  delay(2000);
  //1,4
  for (int i = 0; i < 120; i++){
  digitalWrite(led_pin7, HIGH);
  digitalWrite(led_pin8, LOW);
  digitalWrite(led_pin11, LOW);
  digitalWrite(led_pin12, HIGH);
  delay(20);
  digitalWrite(led_pin7, LOW);
  digitalWrite(led_pin8, HIGH);
  digitalWrite(led_pin11, HIGH);
  digitalWrite(led_pin12, LOW);
  delay(20);
  }
  //2,3
  for (int i = 0; i < 120; i++){
  digitalWrite(led_pin7, HIGH);
  digitalWrite(led_pin8, LOW);
  digitalWrite(led_pin11, HIGH);
  digitalWrite(led_pin12, LOW);
  delay(20);
  digitalWrite(led_pin7, LOW);
  digitalWrite(led_pin8, HIGH);
  digitalWrite(led_pin11, LOW);
  digitalWrite(led_pin12, HIGH);
  delay(20);
  }
  //1,2/3 РЅРµ СЃС‚Р°Р» СЂР°СЃСЃРїРёСЃС‹РІР°С‚СЊ РґСЂСѓРіРёРµ 2 СЃРїРѕСЃРѕР±Р°
  for (int i = 0; i < 120; i++){
  digitalWrite(led_pin7, HIGH);
  digitalWrite(led_pin8, LOW);
  digitalWrite(led_pin11,LOW );
  digitalWrite(led_pin12, LOW);
  delay(20);
  digitalWrite(led_pin7, LOW);
  digitalWrite(led_pin8, HIGH);
  digitalWrite(led_pin11, LOW);
  digitalWrite(led_pin12, HIGH);
  delay(20);
  }
  //3,4/2 РЅРµ СЃС‚Р°Р» СЂР°СЃСЃРїРёСЃС‹РІР°С‚СЊ РґСЂСѓРіРёРµ 2 СЃРїРѕСЃРѕР±Р°
  for (int i = 0; i < 120; i++){
  digitalWrite(led_pin7, LOW);
  digitalWrite(led_pin8, HIGH);
  digitalWrite(led_pin11,LOW );
  digitalWrite(led_pin12, LOW);
  delay(20);
  digitalWrite(led_pin7, HIGH);
  digitalWrite(led_pin8, LOW);
  digitalWrite(led_pin11, HIGH);
  digitalWrite(led_pin12, LOW);
  delay(20);
  }
  //3,4/1 РЅРµ СЃС‚Р°Р» СЂР°СЃСЃРїРёСЃС‹РІР°С‚СЊ РґСЂСѓРіРёРµ 2 СЃРїРѕСЃРѕР±Р°
  for (int i = 0; i < 120; i++){
  digitalWrite(led_pin7, LOW);
  digitalWrite(led_pin8, HIGH);
  digitalWrite(led_pin11,LOW );
  digitalWrite(led_pin12, LOW);
  delay(20);
  digitalWrite(led_pin7, HIGH);
  digitalWrite(led_pin8, LOW);
  digitalWrite(led_pin11, LOW);
  digitalWrite(led_pin12, HIGH);
  delay(20);
  }
   //1,2/4 РЅРµ СЃС‚Р°Р» СЂР°СЃСЃРїРёСЃС‹РІР°С‚СЊ РґСЂСѓРіРёРµ 2 СЃРїРѕСЃРѕР±Р°
  for (int i = 0; i < 120; i++){
  digitalWrite(led_pin7, HIGH);
  digitalWrite(led_pin8, LOW);
  digitalWrite(led_pin11,LOW );
  digitalWrite(led_pin12, LOW);
  delay(20);
  digitalWrite(led_pin7, LOW);
  digitalWrite(led_pin8, HIGH);
  digitalWrite(led_pin11, HIGH);
  digitalWrite(led_pin12, LOW);
  delay(20);
  }
   //РІСЃРµ
  digitalWrite(led_pin7, HIGH);
  digitalWrite(led_pin8, HIGH);
  digitalWrite(led_pin11, LOW);
  digitalWrite(led_pin12, LOW);
  delay(2000);
   //РЅРёРѕРґРЅРѕРіРѕ
  digitalWrite(led_pin7, LOW);
  digitalWrite(led_pin8, LOW);
  digitalWrite(led_pin11, LOW);
  digitalWrite(led_pin12, LOW);
  delay(2000);
}