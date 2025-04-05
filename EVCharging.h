/*
 * EVCharging.h
 *
 *  Created on: 29 Apr 2023
 *      Author: 2002345
 */

#ifndef EVCHARGING_H_
#define EVCHARGING_H_

class EVCharging {// you may also declare this class as an extension of WeightedGraph
private:
	map<int, Location> locations;//It can also be unordered_map
	int numberOfLocations;
	WeightedGraphType* weightedGraph;
public:
	EVCharging();
	~EVCharging();
	void inputLocations();
	void printLocations();
	void printAdjacencyMatrix();
	void breadthFirstTraversal();
	void listLocation();
	void printAdjacentLocations(int locationindex);
	void minimumCost(int indexLocation);
};

EVCharging::EVCharging() {
	inputLocations();
	weightedGraph = new WeightedGraphType(numberOfLocations);
}

EVCharging::~EVCharging() {
	delete weightedGraph;
}
void EVCharging::inputLocations() {
	ifstream infile;
	char fileName[50] = "Locations.txt";

	cout << "Enter charging location file name: ";
	cin >> fileName;
	cout << endl;

	infile.open(fileName);

	if (!infile) {
		cout << "Cannot open input file." << endl;
		return;
	}

	int locationIndex = 0;

	while (!infile.eof()) {
		Location s;
		string charger;
		string price;
		while (!infile.eof()) {
			getline(infile, s.locationName, ',');
			getline(infile, charger, ',');
			getline(infile, price);
			s.chargerInstalled = (stoi(charger) == 1) ? true : false;
			s.chargingPrice = stod(price);
			s.index = locationIndex;
			locations[locationIndex] = s;
			locationIndex++;
		}
	}

	numberOfLocations = locationIndex;
}

void EVCharging::printLocations() {
	cout << "List of locations and charging information " << endl;
	cout << setw (8) << "Index" << setw (20) << "Location name" << setw (20) <<"Charging station" << setw(20) << "Charging price" << endl;

	map<int, Location>::iterator it = locations.begin();

	for (; it != locations.end(); it++) {
		it->second.printLocation();
	}

    cout << endl;
}

void EVCharging::printAdjacencyMatrix() {
	cout << "Adjacency matrix (0 means no direct connection, non-zero value represents the distance of adjacent locations)\n" << endl;
	cout << setw(13) << " ";
	for (int i = 0; i < numberOfLocations; i++) {
		cout << setw(13) << locations[i].locationName;
	}
	cout << endl;
	for (int i = 0; i < numberOfLocations; i++) {
		cout << setw(13) << locations[i].locationName;
		for (int j = 0; j < numberOfLocations; j++) {
			cout << setw(13) << (weightedGraph->getWeight(i,j) == DBL_MAX ? 0.0 : weightedGraph->getWeight(i,j));
		}
		cout << endl;
	}
}

void EVCharging::breadthFirstTraversal() {
	weightedGraph->breadthFirstTraversal();
}

void EVCharging::listLocation() {
	priority_queue<Location, vector<Location>, greater<Location> > p;
	for(int i =0; i < numberOfLocations; i++) {
	if(locations[i].chargerInstalled) {
		p.push(locations[i]);
	}
	}
	while(!p.empty()) {
		Location pop = p.top(); 
		pop.printLocation();
		p.pop();
	}
} 

void EVCharging::printAdjacentLocations(int locationindex) {
	cout << "Adjacent locations with charging stations for location " << locationindex << ":" << endl;

	list<int> adjacencyList = weightedGraph->getAdjancencyList(locationindex);
	bool hasChargingStation = false;

	for(int adjacentLocationindex : adjacencyList) {
		Location adjacentLocation = locations[adjacentLocationindex];

		if(adjacentLocation.chargerInstalled) {
			cout << "The Location given: " << adjacentLocationindex << adjacentLocation.locationName << endl;
			hasChargingStation = true;
		}
	}
	if(!hasChargingStation) {
		cout << "No Charging Station" << endl;
	}
}
void EVCharging:: minimumCost(int indexLocation) {
	Location currentLocation = locations[indexLocation];
	list<int> adjacencyList = weightedGraph->getAdjancencyList(indexLocation);

	double lowestCost = DBL_MAX;
	int lowestCostLocationIndex = 1;

	for (int adjacentLocationIndex : adjacencyList) {
		Location adjacentLocation = locations[adjacentLocationIndex];

		if (adjacentLocation.chargerInstalled) {
			double travelCost = 2 * currentLocation.chargingPrice;		 // Assuming travel cost is $0.10/km
			double chargingCost = (adjacentLocation.chargingPrice * 40); // Assuming charging amount is 40 kWh

			double totalCost = travelCost + chargingCost;

			if (totalCost < lowestCost) {
				lowestCost = totalCost;
				lowestCostLocationIndex = adjacentLocationIndex;
			}
		}
	}

	if (lowestCostLocationIndex != 1) {
		Location lowestCostLocation = locations[lowestCostLocationIndex];

		cout << "Adjacent location with the lowest charging cost from location " << indexLocation << ":" << endl;
		cout << "Location " << lowestCostLocationIndex << ": " << lowestCostLocation.locationName << endl;
		cout << "Total cost: $" << lowestCost << endl;
	}
	else {
		cout << "No adjacent location with charging stations found from location " << indexLocation << endl;
	}
}


#endif /* EVCHARGING_H_ */
