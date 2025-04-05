/* DECLARATION
I hereby certify that no other part of this submission has been copied from any other sources,
including the Internet, books, or other student’s work, or generated from generative AI tools,
such as ChatGPT except the ones I have listed below:
// List the part of code you acquired from other resources
I hold a copy of this assignment that I can produce if the original is lost or damaged.
*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <queue>
#include <map>

using namespace std;

#include "Location.h"
#include "WeightedGraph.h"
#include "EVCharging.h"


int main() {
	EVCharging charging;
	WeightedGraphType weights;
	Location location;
	charging.printLocations();
	charging.printAdjacencyMatrix(); 
	cout << "Task 3: List all the locations with charging stations in ascending order of charging price" << endl;
	cout << "Task 4: Take user's input of a location and output the list of adjacent locations with charging stations." << endl;
	cout << "Task 5: Take user's input of a location and find the adjacent location with the lowest charging cost." << endl;
	cout << "Print all locations." << endl;
	int choice;
	cin >> choice;

	switch(choice) {
		case 3:
			charging.listLocation();
			break;
		case 4:
			cout << "Input a location: " << endl;
			cin >> location.locationName;
			charging.printAdjacentLocations(1);
			break;
		case 5:
			cout << "Input a location: " << endl;
			cin >> location.locationName;
			charging.minimumCost(1);
			break;
		case 6: 
			charging.printLocations();
	} 

	
	
	return 0;
}
