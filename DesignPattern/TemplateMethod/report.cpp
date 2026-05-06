#include <iostream>
#include "report.h"
void Report::write_header(const std::string& header){
    std::cout << header << "라는 내용의 헤더 작성 중.." << std::endl;
}
void Report::send(const std::string& name){
    std::cout << name << "에게 전송 중.." << std::endl;
}
void Report::generate_report(const std::string& header, const std::string& name) {
    write_header(header);
    measure_record();
    write_record();
    write_result();
    send(name);
}