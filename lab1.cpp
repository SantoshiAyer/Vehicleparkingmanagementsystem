#include <conio.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;
class EarnedMoney
{
private:
    int carType;
    int busType;
    int trcukType;
    int bikeType;
    int cycleType;
    int total;

public:
    EarnedMoney()
    {
        this->carType = 0;
        this->busType = 0;
        this->trcukType = 0;
        this->bikeType = 0;
        this->cycleType = 0;
        this->total = 0;
    }
    void setEarnedMoney(int carType, int busType, int trcukType, int bikeType, int cycleType, int total)
    {
        this->carType = carType;
        this->busType = busType;
        this->trcukType = trcukType;
        this->bikeType = bikeType;
        this->cycleType = cycleType;
        this->total = total;
    }
    void showEarnedMoney()
    {
        cout << "\n--------------------------------------------------------------\n";
        cout << setw(10) << "Car|" << setw(10) << "Bus|" << setw(10) << "Truck|" << setw(10) << "Bike|" << setw(10) << "Cycle|" << setw(10) << "Total|";
        cout << "\n--------------------------------------------------------------\n";
        cout << setw(9) << this->carType << "|" << setw(9) << this->busType << "|" << setw(9) << this->trcukType << "|" << setw(9) << this->bikeType << "|" << setw(9) << this->cycleType << "|" << setw(9) << this->total << "|";
        cout << "\n--------------------------------------------------------------\n";
    }
    void getAllEarnedMoney();
    friend void addTwoMoney(EarnedMoney, EarnedMoney &);
};
void EarnedMoney::getAllEarnedMoney()
{
    ifstream fin;
    fin.open("aaEarnedMonry.txt", ios_base::in | ios_base::binary);
    if (!fin)
    {
        cout << "\nFile Not Found";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
        // this->showEarnedMoney();
    }
}
void addTwoMoney(EarnedMoney oldMoney, EarnedMoney &newMoney)
{
    newMoney.carType += oldMoney.carType;
    newMoney.busType += oldMoney.busType;
    newMoney.trcukType += oldMoney.trcukType;
    newMoney.bikeType += oldMoney.bikeType;
    newMoney.cycleType += oldMoney.cycleType;
    newMoney.total += oldMoney.total;
}
class VehicleType
{
private:
    char vehicleTypeName[50];

public:
    VehicleType()
    {
        strcpy(vehicleTypeName, "Vehicle");
    }
    void setVehivleType(EarnedMoney &earnedMoney)
    {
        while (1)
        {
            cout << "\nSelect Vehicle Type:";
            cout << "\n1. Car  2. Bus  3. Truck  4. Bike  5. Cycle\n";
            int vehicleType;
            cin >> vehicleType;
            if (vehicleType == 1)
            {
                strcpy(this->vehicleTypeName, "Car");
                earnedMoney.setEarnedMoney(100, 0, 0, 0, 0, 100);
                break;
            }
            else if (vehicleType == 2)
            {
                strcpy(vehicleTypeName, "Bus");
                earnedMoney.setEarnedMoney(0, 200, 0, 0, 0, 200);
                break;
            }
            else if (vehicleType == 3)
            {
                strcpy(vehicleTypeName, "Truck");
                earnedMoney.setEarnedMoney(0, 0, 400, 0, 0, 400);
                break;
            }
            else if (vehicleType == 4)
            {
                strcpy(vehicleTypeName, "Bike");
                earnedMoney.setEarnedMoney(0, 0, 0, 50, 0, 50);
                break;
            }
            else if (vehicleType == 5)
            {
                strcpy(vehicleTypeName, "Cycle");
                earnedMoney.setEarnedMoney(0, 0, 0, 0, 20, 20);
                break;
            }
            else
            {
                cout << "\nInvalid Choice:";
            }
        }
    }
    void showVehicleType() { cout << vehicleTypeName << "  "; }
};
class Vehicle : public VehicleType
{
private:
    int vehicleNo;
    char shortDescription[60];
    char description[100];
    char createdBy[50];
    char lastUpdatedBy[50];
    char createdDateTime[50];
    char lastUpdatedDateTime[50];
    EarnedMoney earnedMoney;

public:
    Vehicle()
    {
        this->vehicleNo = 0;
        strcpy(this->shortDescription, "default");
        strcpy(this->description, "default");
        strcpy(this->createdBy, "ssyr");
        strcpy(this->lastUpdatedBy, "ssyr");
        time_t tt;
        time(&tt);
        strcpy(this->createdDateTime, asctime(localtime(&tt)));
        strcpy(this->lastUpdatedDateTime, asctime(localtime(&tt)));
    }
    void setVehicle()
    {
        cout << "\nEnter The Vehicle Number: ";
        cin >> vehicleNo;
        cin.ignore();
        cout << "\nEnter The Vehicle Short Description: ";
        cin.getline(shortDescription, 50);
        cout << "\nEnter The Vehicle Description: ";
        cin.getline(description, 100);
        strcpy(createdBy, "ssyr");
        strcpy(lastUpdatedBy, "ssyr");
        setVehivleType(earnedMoney);
        // date and time
        time_t tt;
        time(&tt);
        strcpy(createdDateTime, asctime(localtime(&tt)));
        strcpy(lastUpdatedDateTime, asctime(localtime(&tt)));
    }
    void showVehicle()
    {
        cout << vehicleNo << "  " << shortDescription << "  ";
        cout << description << "  ";
        showVehicleType();
        cout << createdBy << "  " << lastUpdatedBy << "  ";
        cout << createdDateTime << lastUpdatedDateTime << endl;
        // earnedMoney.showEarnedMoney();
    }
    void addVehicle();
    void getAllVehicleList();
    void searchVehicle(int vno);
    void deleteVehicle(int vno);
    void updateVehicle(int vno);
};
void Vehicle::addVehicle()
{
    ofstream fout;
    fout.open("aaVehivleData.txt", ios_base::app | ios_base::binary);
    getch();
    fout.write((char *)this, sizeof(*this));
    fout.close();

    EarnedMoney em;
    em.getAllEarnedMoney();
    addTwoMoney(em, this->earnedMoney);
    fout.open("aaEarnedMonry.txt", ios_base::out | ios_base::binary);
    fout.write((char *)(&this->earnedMoney), sizeof(this->earnedMoney));
    fout.close();
    cout << "\nRecord Added Successfully\n";
}
void Vehicle::getAllVehicleList()
{
    ifstream fin;
    int nor = 0;
    fin.open("aaVehivleData.txt", ios_base::in | ios_base::binary);
    if (!fin)
    {
        cout << "\nFile Not Found";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            this->showVehicle();
            nor++;
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        if (nor == 0)
        {
            cout << "\nFile Has No Record:";
        }
    }
}
void Vehicle::searchVehicle(int vno)
{
    ifstream fin;
    int nor = 0;
    fin.open("aaVehivleData.txt", ios_base::in | ios_base::binary);
    if (!fin)
    {
        cout << "\nFile Not Found";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (this->vehicleNo == vno)
            {
                this->showVehicle();
                nor = 1;
                break;
            }
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        if (nor == 0)
        {
            cout << "\nRecord Not Found:";
        }
    }
}
void Vehicle::deleteVehicle(int vno)
{
    ifstream fin;
    ofstream fout;
    int flag = 0;
    fin.open("aaVehivleData.txt", ios_base::in | ios_base::binary);
    if (!fin)
    {
        cout << "\nFile Not Found";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
        fout.open("aaTempVehivleData.txt", ios_base::out | ios_base::binary);
        while (!fin.eof())
        {
            if (this->vehicleNo == vno)
            {
                flag = 1;
            }
            else
            {
                fout.write((char *)this, sizeof(*this));
            }
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        fout.close();
        if (flag == 0)
        {
            cout << "\nRecord Not Found: Hence Can Not delete";
            remove("aaTempVehivleData.txt");
        }
        else
        {
            cout << "\nRecord Deleted:";
            remove("aaVehivleData.txt");
            rename("aaTempVehivleData.txt", "aaVehivleData.txt");
        }
    }
}
void Vehicle::updateVehicle(int vno)
{
    fstream foutIn;
    int flag = 0;
    foutIn.open("aaVehivleData.txt", ios_base::in | ios_base::out | ios_base::ate | ios_base::binary);
    foutIn.seekg(0);
    if (!foutIn)
    {
        cout << "\nFile Not Found";
    }
    else
    {
        foutIn.read((char *)this, sizeof(*this));
        while (!foutIn.eof())
        {
            if (this->vehicleNo == vno)
            {
                // this->setVehicle();
                cout << "\nUpdating The Data:";
                cout << "\nEnter The Vehicle Number: ";
                cin >> vehicleNo;
                cin.ignore();
                cout << "\nEnter The Vehicle Short Description: ";
                cin.getline(shortDescription, 50);
                cout << "\nEnter The Vehicle Description: ";
                cin.getline(description, 100);
                strcpy(createdBy, "ssyr");
                strcpy(lastUpdatedBy, "ssyr");
                // date and time
                time_t tt;
                time(&tt);
                strcpy(lastUpdatedDateTime, asctime(localtime(&tt)));

                foutIn.seekp(foutIn.tellp() - sizeof(*this));
                foutIn.write((char *)this, sizeof(*this));
                cout << "\nRecord Updated Successfully\n";
                flag = 1;
                break;
            }
            foutIn.read((char *)this, sizeof(*this));
        }
        foutIn.close();
        if (flag == 0)
        {
            cout << "\nRecord Not Found:";
        }
    }
}
int menu()
{
    system("cls");
    int ch;
    printf("\n1. Add Vehicle");
    printf("\n2. Search Vehicle");
    printf("\n3. Delete Vehicle");
    printf("\n4. Update Vehicle");
    printf("\n5. List All Vehicle");
    printf("\n6. Check Earned Money");
    printf("\n7. Exit");
    printf("\nEnter Your Choice: ");
    scanf("%d", &ch);
    return (ch);
}
int main()
{
    system("cls");
    Vehicle vehicle;
    EarnedMoney earnedMoney;
    int breakInfiniteloop = 0, vno;
    while (1)
    {
        system("cls");
        switch (menu())
        {
        case 1:
            vehicle.setVehicle();
            vehicle.addVehicle();
            getch();
            break;
        case 2:
            cout << "\nEnter The Vehicle Number To Searched: ";
            cin >> vno;
            vehicle.searchVehicle(vno);
            getch();
            break;
        case 3:
            cout << "\nEnter The Vehicle Number To Deleted: ";
            cin >> vno;
            vehicle.deleteVehicle(vno);
            getch();
            break;
        case 4:
            cout << "\nEnter The Vehicle Number To Updated: ";
            cin >> vno;
            vehicle.updateVehicle(vno);
            getch();
            break;
        case 5:
            vehicle.getAllVehicleList();
            getch();
            break;
        case 6:
            earnedMoney.getAllEarnedMoney();
            earnedMoney.showEarnedMoney();
            getch();
            break;
        case 7:
            breakInfiniteloop = 1;
            break;
        default:
            cout << "\nInvalid Choice:";
            getch();
        } // end of switch
        if (breakInfiniteloop == 1)
        {
            break;
        }
    } // enf of infinite loop
    return (0);
}