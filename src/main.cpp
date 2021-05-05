#include <iostream>
#include <cpr/cpr.h>
#include <arduino.h>

using namespace cpr;
using namespace std;

int main() {
    
    char link[] = "start C:\\Users\\Intel Core\\iot_intot\\квант\квант\\jsom.json";
    Response r = Post(Url{ "http://www.httpbin.org/post" },
        Body{ link },
        Header{ {"Content-Type", "application/json"} });
    cout << r.text << endl;

}

void Display() {

}
void Button() {

}
void Beacon() {

}
void Led_1() {

}

