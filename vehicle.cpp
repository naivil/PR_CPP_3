#include <iostream>
using namespace std;

class Vehicle
{
protected:
    int vId, vYear;
    string vMaker, vModel;
    static int vCount;

public:
    Vehicle(int id, string model, string maker, int year)
    {
        vId = id;
        vModel = model;
        vMaker = maker;
        vYear = year;
        vCount++;
    }

    void setVehicle(int id, string model, string maker, int year)
    {
        vId = id;
        vModel = model;
        vMaker = maker;
        vYear = year;
    }

    void getVehicle()
    {
        cout << "Vehicle Id: " << vId << endl
             << "Model: " << vModel << endl
             << "Manufacturer: " << vMaker << endl
             << "Year: " << vYear << endl;
    }

    int getID()
    {
        return vId;
    }

    ~Vehicle()
    {
        vCount--;
    }
};

int Vehicle::vCount = 0;

class Car : public Vehicle
{
protected:
    string cFuel;

public:
    Car(int id, string model, string maker, int year, string fuel)
        : Vehicle(id, model, maker, year)
    {
        cFuel = fuel;
    }

    void getCar()
    {
        getVehicle();
        cout << "Fuel Type: " << cFuel << endl;
    }
};

class ElectricCar : public Car
{
    float eBattery;

public:
    ElectricCar(int id, string model, string maker, int year, string fuel, float batt)
        : Car(id, model, maker, year, fuel)
    {
        eBattery = batt;
    }

    void getElectricCar()
    {
        getCar();
        cout << "Battery Capacity: " << eBattery << " KW" << endl;
    }
};

class Aircraft
{
protected:
    float aRange;

public:
    Aircraft(float range) { aRange = range; }

    void getAircraft()
    {
        cout << "Flight Range: " << aRange << endl;
    }
};

class FlyingCar : public Car, public Aircraft
{
public:
    FlyingCar(int id, string model, string maker, int year, string fuel, float range)
        : Car(id, model, maker, year, fuel), Aircraft(range) {}

    void getFlyingCar()
    {
        getCar();
        getAircraft();
    }
};

class Sedan : public Car
{
public:
    Sedan(int id, string model, string maker, int year, string fuel)
        : Car(id, model, maker, year, fuel) {}

    void getSedan()
    {
        getCar();
    }
};

class SUV : public Car
{
public:
    SUV(int id, string model, string maker, int year, string fuel)
        : Car(id, model, maker, year, fuel) {}

    void getSUV()
    {
        getCar();
    }
};

class VehicleRegistry
{
    Vehicle *list[100];
    int total = 0;

public:
    void add(Vehicle *v)
    {
        list[total++] = v;
    }

    void showAll()
    {
        cout << "\n----- Vehicle Registry -----\n";
        for (int i = 0; i < total; i++)
        {
            cout << "Vehicle #" << (i + 1) << endl;
            list[i]->getVehicle(); // only prints base Vehicle details
            cout << endl;
        }
    }

    void searchByID(int id)
    {
        bool found = false;
        for (int i = 0; i < total; i++)
        {
            if (list[i]->getID() == id)
            {
                cout << "\n--- Vehicle Found ---\n";
                list[i]->getVehicle();
                found = true;
                break;
            }
        }
        if (!found)
            cout << "No vehicle found with ID " << id << endl;
    }
};

void inputCommon(int &id, string &model, string &maker, int &year)
{
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Model: ";
    cin.ignore();
    getline(cin, model);
    cout << "Enter Manufacturer: ";
    getline(cin, maker);
    cout << "Enter Year: ";
    cin >> year;
}

int main()
{
    VehicleRegistry reg;
    int id, year, choice, size;
    string fuel, model, maker;
    float batt, range;

    do
    {
        cout << "\n======= Vehicle Registry System =======" << endl;
        cout << "1. Add Electric Car" << endl;
        cout << "2. Add Flying Car" << endl;
        cout << "3. Add Sedan" << endl;
        cout << "4. Add SUV" << endl;
        cout << "5. Show All Vehicles" << endl;
        cout << "6. Search Vehicle by ID" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "How many Electric Cars to add? ";
            cin >> size;
            for (int i = 0; i < size; i++)
            {
                inputCommon(id, model, maker, year);
                cout << "Enter Fuel Type: ";
                cin.ignore();
                getline(cin, fuel);
                cout << "Enter Battery Capacity: ";
                cin >> batt;
                reg.add(new ElectricCar(id, model, maker, year, fuel, batt));
            }
            break;

        case 2:
            cout << "How many Flying Cars to add? ";
            cin >> size;
            for (int i = 0; i < size; i++)
            {
                inputCommon(id, model, maker, year);
                cout << "Enter Fuel Type: ";
                cin.ignore();
                getline(cin, fuel);
                cout << "Enter Flight Range: ";
                cin >> range;
                reg.add(new FlyingCar(id, model, maker, year, fuel, range));
            }
            break;

        case 3:
            cout << "How many Sedans to add? ";
            cin >> size;
            for (int i = 0; i < size; i++)
            {
                inputCommon(id, model, maker, year);
                cout << "Enter Fuel Type: ";
                cin.ignore();
                getline(cin, fuel);
                reg.add(new Sedan(id, model, maker, year, fuel));
            }
            break;

        case 4:
            cout << "How many SUVs to add? ";
            cin >> size;
            for (int i = 0; i < size; i++)
            {
                inputCommon(id, model, maker, year);
                cout << "Enter Fuel Type: ";
                cin.ignore();
                getline(cin, fuel);
                reg.add(new SUV(id, model, maker, year, fuel));
            }
            break;

        case 5:
            reg.showAll();
            break;

        case 6:
            cout << "Enter ID to search: ";
            cin >> id;
            reg.searchByID(id);
            break;

        case 0:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 0);

    return 0;
}
