#include <iostream>
#include "accuracy_report.h"

void AccuracyReport::measure_record(){
    std::cout << "정확도 측정 중.." << std::endl;
}
void AccuracyReport::write_record(){
    std::cout << "정확도 측정 결과 작성 중.." << std::endl;
}
void AccuracyReport::write_result(){
    std::cout << "정확도 성능 보고서 결과 작성 중.." << std::endl;
}