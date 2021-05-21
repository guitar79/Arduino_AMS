//https://forum.arduino.cc/t/how-to-set-an-alarm-with-the-ds1302-real-time-clock/594882
//https://m.blog.naver.com/chandong83/221451714944

#include <ThreeWire.h>  
#include <RtcDS1302.h>

//ThreeWire myWire(4,5,2); // IO, SCLK, CE
ThreeWire myWire(3,2,4); // IO, SCLK, RST

//RTC 라이브러리 생성
RtcDS1302<ThreeWire> Rtc(myWire);


/*
미세 먼지 센서 값 출력
http://www.devicemart.co.kr/
*/

// 미세 먼지 없을 때 초기 V 값 0.35
// 공기청정기 위 등에서 먼지를 가라앉힌 후 voltage값 개별적으로 측정 필요
#define no_dust 0.35

// 아두이노 - 미세 먼지 센서 연결
int dustout=A0;
int v_led=13;

// 센서로 읽은 값 변수 선언
float vo_value=0;

// 센서로 읽은 값을 전압으로 측정 변수
float sensor_voltage=0;

// 실제 미세 먼지 밀도 변수
float dust_density=0;


// for the temperature and hubmidity sensor

 #include <DHT.h>
 #define DHT22_PIN 2
 #define DHTTYPE DHT22
 DHT dht(DHT22_PIN, DHTTYPE);
 int chkSensor;
 String Temperature;
 String Humidity;

  
void setup () 
{
    Serial.begin(9600);
    pinMode(v_led,OUTPUT); // 적외선 led 출력으로 설정
    
    //컴파일 시점의 날짜(__DATE__)와 시간(__TIME__)을 시리얼모니터에 표시
    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.print(" ");
    Serial.println(__TIME__);

    //RTC 모듈 라이브러리 시작
    Rtc.Begin();
    
    //RTC 시간을 설정 컴파일된 날짜로
    setTRTCDateTime();

    //U8G displayer
    u8gStart();
}

void loop () 
{
    //RTC 모듈의 현재 시간 얻기
    RtcDateTime now = Rtc.GetDateTime();

    digitalWrite(v_led, LOW); // 적외선 LED ON
    delayMicroseconds(280); // 280us동안 딜레이
    vo_value=analogRead(dustout); // 데이터를 읽음
    delayMicroseconds(40); // 320us - 280us
    digitalWrite(v_led, HIGH); // 적외선 LED OFF
    delayMicroseconds(9680); //

    Temperature = String(dht.readTemperature(),1);
    Humidity = String(dht.readHumidity(),1);
    humidityTemperatureReport();

    //시리얼 모니터에 출력
    //시간 출력
    printDateTime(now);
    Serial.print(",");
    // PM25 값 추가
    csvPM25();
    Serial.println();
    
    // PM25 값 출력
    printPM25();
    //줄 바꿈.
    Serial.println();
    //OLED display
    u8gDraw();
    //1초 대기...후 다시 loop 시작
    delay(1000); // ten seconds
}
