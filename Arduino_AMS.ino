#include <ThreeWire.h>  
#include <RtcDS1302.h>

//4핀이 DAT
//5핀이 CLK
//2핀이 CE
//ThreeWire myWire(4,5,2); // IO, SCLK, CE
ThreeWire myWire(3,2,4); // IO, SCLK, RST

//RTC 라이브러리 생성
RtcDS1302<ThreeWire> Rtc(myWire);

void setup () 
{
    Serial.begin(9600);
    
    //컴파일 시점의 날짜(__DATE__)와 시간(__TIME__)을 시리얼모니터에 표시
    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.print(" ");
    Serial.println(__TIME__);

    //RTC 모듈 라이브러리 시작
    Rtc.Begin();
    
    //RTC 시간을 설정 컴파일된 날짜로
    setTRTCDateTime();
}

void loop () 
{
    //RTC 모듈의 현재 시간 얻기
    RtcDateTime now = Rtc.GetDateTime();

    //시리얼 모니터에 출력
    printDateTime(now);
    //줄 바꿈.
    Serial.println();
    //10초 대기...후 다시 loop 시작
    delay(1000); // ten seconds
}
