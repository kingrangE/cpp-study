#include <iostream>
#include "throughput_report.h"

void ThroughputReport::measure_record() {
	std::cout << "처리량 측정 중.." << std::endl;
}
void ThroughputReport::write_record() {
	std::cout << "처리량 측정 결과 작성 중.." << std::endl;
}
void ThroughputReport::write_result() {
	std::cout << "처리량 성능 보고서 결과 작성 중.." << std::endl;
}