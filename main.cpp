#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


//Good!
void readData(const string &fileName, vector<double> &flightAngles,
             vector<double> &liftCoefficients);
//Good!
double interpolation(double userAngle, const vector<double> &flightAngles, const vector<double> &liftCoefficients);
//Good!
bool isOrdered(const vector<double> &flightAngles);
//Good!
void reorder(vector<double> &flightAngles, vector<double> &liftCoefficients);


int main(int argc, char *argv[]) {
   string fileName;
   vector<double> flightAngles;
   vector<double> liftCoefficients;
   /*
   vector <double> test1Vec {1,5,4,7};
   vector <double> test2Vec {8,4,5,3};

   reorder (test1Vec, test2Vec);

   for ()
*/

   if (argc != 2) {
     cout << "Usage: progname inputFileName" << endl;
     return 1;
   }


   fileName = argv[1];

   readData(fileName, flightAngles, liftCoefficients);

   if (!isOrdered(flightAngles)){
		reorder(flightAngles, liftCoefficients);
	}

   bool replay = true;
   while (replay){
    double userAngle;
    string userAction;

    
    cout << "Select a flight angle: " << endl;
    cin >> userAngle;

    if (userAngle >= flightAngles.at(0) && userAngle <= flightAngles.at(flightAngles.size() - 1)){
        cout << interpolation(userAngle, flightAngles, liftCoefficients) << endl;
        
        cout << "Would you like to input another angle? Please enter Yes or No. " << endl;
        cin >> userAction;
        
        if (userAction == "Yes"){
         replay = true;
        }
        else if (userAction == "No"){
         replay = false;
        }
        else{
          break;
        }
    }
    else {
      cout << "Angle chosen is not within the bounds" << endl;
    }
   }
   return 0;
}


void readData(const string &fileName, vector<double> &flightAngles, vector<double> &liftCoefficients){
   ifstream inputFile;
   inputFile.open(fileName);
   
   if(!inputFile.is_open()){
    cout << "Error opening " << fileName << endl;
    exit(EXIT_FAILURE);
   }

   double flightAngleVal;
   double liftCoefficientVal;

   while (inputFile >> flightAngleVal >> liftCoefficientVal){
       flightAngles.push_back(flightAngleVal);
       liftCoefficients.push_back(liftCoefficientVal);
   }
   inputFile.close();
}

double interpolation(double userAngle, const vector<double> &flightAngles, const vector<double> &liftCoefficients){
   double liftCo;
   
   for (unsigned int i = 0; i < flightAngles.size(); ++i){
    if (userAngle == flightAngles.at(i)){
      liftCo = liftCoefficients.at(i);
      break;
    }
    else if (userAngle < flightAngles.at(i) && userAngle > flightAngles.at(i - 1)){
      liftCo = liftCoefficients.at(i-1) +  (userAngle - flightAngles.at(i-1)) / (flightAngles.at(i) - flightAngles.at(i-1))*(liftCoefficients.at(i)-(liftCoefficients.at(i-1)));
      }
    }

   return liftCo;
}



bool isOrdered(const vector<double> &flightAngles){
   bool ascending = true;
  for (unsigned int i = 1; i < flightAngles.size(); ++i){
     if (flightAngles.at(i-1) > flightAngles.at(i)){
        ascending = false;
        break;
     }
  }
  return ascending;


}
void reorder(vector<double> &flightAngles, vector<double> &liftCoefficients){
    for (unsigned int i = 1; i < flightAngles.size(); ++i) {
       if (flightAngles.at(i - 1) > flightAngles.at(i)) {
         
         int indOne = i;
         int indTwo = i - 1;
         
         bool ascend = true;
         
         while (ascend){
         
         double tAngle = flightAngles.at(indTwo);
         double tLift = liftCoefficients.at(indTwo);

         flightAngles.at(indTwo) = flightAngles.at(indOne);
         liftCoefficients.at(indTwo) = liftCoefficients.at(indOne);

         flightAngles.at(indOne) = tAngle;
         liftCoefficients.at(indOne) = tLift;

         --indOne;
         --indTwo;

         if (indOne == 0) {
          ascend = false;
        }

        else {
            ascend = true;
        }
       }
    }
}
}