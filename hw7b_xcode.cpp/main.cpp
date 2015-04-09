#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;


class Car
{
    public:
        Car();
        Car(string, string, int, double, int);
        ~Car();
    
        void setValue(double V)
        {
            Value = V;
        }
    
        double getValue()
        {
            return Value;
        }
    
        string make;
        string model;
        int year;
        double price;
        int miles;
   
    private:
        double Value;
};

int readCars(ifstream& in, Car c[], int max)
{
    int count = 0;
    string make = "", model = "";
    double price=0;
    int year=0, miles=0;
    
    while((count < max) && (in >> make >> model >> year >> price >> miles))
    {
        
        /***
         c[count].make = make;
         c[count].model = model;
         c[count].year = year;
         c[count].price = price;
         c[count].miles = miles;
         ***/
        Car CAR(make, model, year, price, miles);
        c[count] = CAR;
        count++;
    }
    
    return count;
}

void write(ofstream& out, Car c[], int size)
{
    for(int i=0; i < size; i++)
    {
        Car CAR = c[i];
        
        out.setf(ios::fixed);
        out.setf(ios::showpoint);
        out.precision(2);
        
        out << CAR.make << " " << CAR.model << " " << CAR.year << " "
        << CAR.price << " " << CAR.miles  << " " << CAR.getValue() << endl;
    }
    
    return;
}

void computeValue(Car CAR[], int size, int current_year)
{
    for(int i=0; i < size; i++)
    {
        Car c = CAR[i];
        double Value = 0;
        
        int year_diff = current_year - c.year;
        
        int avg_miles = year_diff*15000;
        
        
         if (year_diff <= 5)
         {
            Value = c.price - year_diff * (0.1 * c.price);
         }
         else if (year_diff <= 10)
         {
            int first_five = c.price - 5 * (0.1 * c.price);
            Value = first_five - (year_diff - 5) * (0.05 * c.price);
         }
         else
         {
            int first_five = c.price - 5 * (0.1 * c.price);
            int first_ten = first_five - 5 * (0.05 * c.price);
            
            if (c.miles == avg_miles)
            {
                Value = first_ten;
            }
            if (c.miles < avg_miles)
            {
                Value = first_ten + first_ten*0.02;
            }
            if (c.miles > avg_miles)
            {
                Value = first_ten - first_ten*0.02;
            }
         }
        
        CAR[i].setValue(Value);
    }
    
    return;
}

void bsort(Car CAR[], int size)
{
    Car temp;
    
    while(size > 1)
    {
        for(int i=0; i < size-1; i++){
            
            if(CAR[i].getValue() < CAR[i+1].getValue())
            {
                temp = CAR[i];
                CAR[i] = CAR[i+1];
                CAR[i+1] = temp;
            }
        }
        size--;
    }
    return; 
}

int main()
{
    ifstream in;
    ofstream out;
    string inFile, outFile;
    int current_year;
    Car Cars[50];
    
    cout << "Specify an input file:" << endl;
    cin >> inFile;
    in.open(inFile.c_str());
    
    if(in.fail())
    {
        cout << "Failed to open input file: " << inFile << endl;
        return 1;
    }
    
    cout << "Enter the current year: " <<endl;
    cin >> current_year;
    cout << "Specify an output file: " << endl;
    cin >> outFile;
    
    out.open(outFile.c_str());
    if(out.fail())
    {
        cout << "Failed to open output file: " << outFile << endl;
        return 1;
    }

    int count = readCars(in, Cars, 150);
    
    computeValue(Cars, count, current_year);
    
    bsort(Cars, count);
    
    write(out, Cars, count);
    
    return 0;
}



//default constructor
Car::Car() :
    make(""),
    model(""),
    year(0),
    price(0),
    miles(0)
{}

// parameterized constructor
Car::Car(string mk, string mdl, int yr, double pr, int mi) :
    make(mk),
    model(mdl),
    year(yr),
    price(pr),
    miles(mi)
{}

// Class destructor
Car::~Car(){}







