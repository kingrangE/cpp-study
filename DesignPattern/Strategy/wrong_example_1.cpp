#include <iostream>
// Movable 인터페이스
class Movable{
public:
    virtual void move()=0; // 인터페이스는 순수 가상 함수로 만들어야 한다.
    virtual ~Movable(){}
};
// Bus 클래스
class Bus: public Movable{
public:
	void move() override{ //인터페이스 가상 함수 구현
    	std::cout << "도로를 따라 이동 중" << std::endl;
    }
};
// Train 클래스
class Train: public Movable{
public:
	void move() override{ 
    	std::cout << "선로를 따라 이동 중" << std::endl;
    }
};
// Client 클래스
class Client{
private:
    Movable* m; // Movable이 추상클래스이므로 포인터로 받기
public:
	Client(Movable* m):m(m){}; // 이용하고 있는 수단을 받아 초기화
    ~Client(){delete m;}
    void go(){m->move();} // 지금 이용하고 있는 수단으로 이동
};
// main
int main(){
	Client a(new Bus());
    Client b(new Train());
    
    a.go();
    b.go();
	return 0;
}