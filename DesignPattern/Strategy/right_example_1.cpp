#include <iostream>
class MoveStrategy{
public:
    virtual void move() = 0;
    virtual ~MoveStrategy(){}
};

class RailMove: public MoveStrategy{
public:
    void move() override{
        std::cout << "선로로 이동" << std::endl;
    }
};

class RoadMove: public MoveStrategy{
public:
    void move() override{
        std::cout << "도로로 이동" << std::endl;
    }
};

class Movable{
private:
    MoveStrategy* strategy;
public:
    Movable(){strategy = nullptr;}
    Movable(MoveStrategy* s): strategy(s){};
    ~Movable(){delete strategy;}
    void move(){
        if(strategy)strategy->move();
    }
    void setStrategy(MoveStrategy* s){
        delete strategy;
        strategy = s;
    }
};
class Bus: public Movable{
public:
    Bus(){setStrategy(new RoadMove());} // 기본적으로는 도로로 이동
};
class Train: public Movable{
public:
    Train(){setStrategy(new RailMove());}// 기본적으로는 선로로 이동
};

int main(){
    Movable* bus = new Bus();
    Movable* train = new Train();

    bus->move(); // 도로
    train->move(); // 선로

    //만약 여기서는 둘 다 도로로 이동해야 한다.
    train->setStrategy(new RoadMove());
    bus->move();
    train->move();

    delete bus;
    delete train;
    return 0;
}