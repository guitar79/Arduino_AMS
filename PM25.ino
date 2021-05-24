//https://devicemart.blogspot.com/2019/12/gp2y1010au0f.html

void csvPM25()
  {
   sensor_voltage=get_voltage(vo_value);
   dust_density=get_dust_density(sensor_voltage);
   Serial.print(dust_density);  //" [ug/m^3]")
  }


void printPM25()
  {
   sensor_voltage=get_voltage(vo_value);
   dust_density=get_dust_density(sensor_voltage);
  
    Serial.print("value = ");
    Serial.println(vo_value);
    Serial.print("Voltage = ");
    Serial.print(sensor_voltage);
    Serial.println(" [V]");
    Serial.print("Dust Density = ");
    Serial.print(dust_density);
    Serial.println(" [ug/m^3]");\
  }

float get_voltage(float value)
  {
   // 아날로그 값을 전압 값으로 바꿈
   float V= value * 5.0 / 1024; 
   return V;
  }

float get_dust_density(float voltage)
  {
   // 데이터 시트에 있는 미세 먼지 농도(ug) 공식 기준
   float dust=(voltage-no_dust) / 0.005;
   return dust;
  }
