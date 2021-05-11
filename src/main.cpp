#include <cpr/cpr.h>
#include <arduino.h>

using namespace cpr; 

const char *ssid = "KVANTORIUM34IT349"; // SSID
const char *password = "it349Impossible"; // пароль

void setup() {
Serial.begin(9600);

}

void loop(){
    Post('text/plain');
    Get();
}


void Post(char _file) {
    char link[] = "file"; // ваш файл
    Response r = Post(Url{ "http://www.httpbin.org/post" },
        Body{ link },
        Header{ {"Content-Type", _file} });
}

void Get(){
    Response r = Get(Url{"http://www.httpbin.org/post"},
                      Authentication{"user", "pass"},
                      Parameters{{"anon", "true"}, {"key", "value"}});
    return r.text;
}
