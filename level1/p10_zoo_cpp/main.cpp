#include <iostream>
include <std::iostream>
#include <vector>
using namespace std;
class Animal {
public:
    virtual void shout() = 0;
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void shout() override {
        cout << "汪汪！" << endl;
    }
};k

class Cat : public Animal {
public:
    void shout() override {
        cout << "喵喵！" << endl;
    }
};


class Zoo {
private:
    vector<Animal*> animals;
public:
    void addAnimal(Animal* a) {
        animals.push_back(a);
    }
    void allShout() {
        for (auto a : animals) {
            a->shout();
        }
    }
    ~Zoo() {
        for (auto a : animals) {
            delete a;
        }
    }
};

int main() {
    Zoo zoo;
    zoo.addAnimal(new Dog());
    zoo.addAnimal(new Cat());

    cout << "动物园动物开始吼叫：" << endl;
    zoo.allShout();

    return 0;
}