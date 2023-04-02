#include <iostream>
#include <string>
#include <vector>

using namespace std;



// Subject interface
class Subject {
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

// Concrete subject class (milkshop)
class MilkShop : public Subject {
private:
    vector<Observer*> observers;
    string currentMilkBatch;

public:
    void registerObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        for (int i = 0; i < observers.size(); i++) {
            if (observers[i] == observer) {
                observers.erase(observers.begin() + i);
                break;
            }
        }
    }

    void notifyObservers() {
        for (int i = 0; i < observers.size(); i++) {
            observers[i]->update(currentMilkBatch);
        }
    }

    void setMilkBatch(string milkBatch) {
        currentMilkBatch = milkBatch;
        notifyObservers();
    }
};

// Observer interface
class Observer {
public:
    virtual void update(string milkBatch) = 0;
};
// Concrete observer class (client)
class Client : public Observer {
private:
    string name;

public:
    Client(string name) {
        this->name = name;
    }

    void update(string milkBatch) {
        cout << name << "Notification: " << milkBatch << endl;
    }
};

int main() {
    MilkShop milkShop;

    Client* client1 = new Client("John");
    Client* client2 = new Client("Mary");
    Client* client3 = new Client("Tom");

    milkShop.registerObserver(client1);
    milkShop.registerObserver(client2);
    milkShop.registerObserver(client3);

    milkShop.setMilkBatch("Fresh milk");

    milkShop.removeObserver(client2);

    milkShop.setMilkBatch("Organic milk");

    return 0;
}
