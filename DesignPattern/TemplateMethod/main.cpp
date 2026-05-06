#include <iostream>
#include "throughput_report.h"
#include "accuracy_report.h"

int main() {
    Report* throughput = new ThroughputReport();
    Report* accuracy = new AccuracyReport();
    throughput->generate_report("처리량 보고서", "Kilwon");
    accuracy->generate_report("정확도 보고서","Kiltwo");
    
    
    
    delete throughput;
    delete accuracy;
    
    return 0;
}