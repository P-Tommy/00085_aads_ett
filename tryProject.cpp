//============================================================================
// Name        : tryProject.cpp
// Author      : tommy
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <list>
#include <string>
#include <random>
#include <ctime>
#include <chrono>
#include <locale>

using namespace std;

//Graph coloring
//Δημιουργία χρωματισμού γραφήματος
class GraphC {
	int V;          // No. of vertices
	list<int> *adj; // A dynamic array of adjacency lists
public:
	// Constructor and destructor
	GraphC(int V) {
		this->V = V;
		adj = new list<int> [V];
	}
	~GraphC() {
		delete[] adj;
	}
	int soltable(int tabl[]);

	// function to add an edge to graph
	void addEdge(int v, int w);

	// Prints greedy coloring of the vertices
	int greedyColoring(int f);

	// experimental process for creating a solution table
	GraphC get(list<GraphC> _list, int _i) {
		list<GraphC>::iterator it = _list.begin();
		for (int i = 0; i < _i; i++) {
			++it;
		}
		return *it;
	}

};

void GraphC::addEdge(int v, int w) {
	adj[v].push_back(w);
	adj[w].push_back(v); // Note: the graph is undirected
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
int GraphC::greedyColoring(int f) {
	int x[V];
	int result[V];

	// Assign the first color to first vertex
	result[0] = 0;

	// Initialize remaining V-1 vertices as unassigned
	for (int u = 0; u < V; u++)
		result[u] = -1; // no color is assigned to u

	// A temporary array to store the available colors. True
	// value of available[cr] would mean that the color cr is
	// assigned to one of its adjacent vertices
	bool available[V];
	for (int cr = 0; cr < V; cr++)
		available[cr] = true;

	// Assign colors to remaining V-1 vertices
	for (int u = 0; u < V; u++) {
		// Process all adjacent vertices and flag their colors
		// as unavailable
		list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (result[*i] != -1)
				available[result[*i]] = false;

		// Find the first available color
		int cr;
		for (cr = 0; cr < V; cr++)
			if (available[cr])
				break;

		result[u] = cr; // Assign the found color

		// Reset the values back to true for the next iteration
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (result[*i] != -1)
				available[result[*i]] = true;
	}
	int get_max=0;
	// print the result
	for (int u = 0; u < V; u++) {
		x[u] = result[u]; //second table save color in cell
		if(get_max < result[u])		//επιστρεφει τη μεγαλύτερη τιμη για τον αριθμο χρωμάτων που περιεχει το γραφημα μας
		    get_max = result[u];	//εάν αυτος ο αριθμος ειναι μεγαλυτερος απο τις περιοδους των εξετασεων βαση δεδομένων απο την αρχη του προβληματος
									//τότε δεν υπάρχει εφικτή λύση και χρειάζεται άλλη κατασεκυή λυσης

	//	cout << "Vertex " << u + 1 << " --->  Color " << result[u]<<" Max countcolor "<<get_max << endl;
		//  cout<<"X[ "<<u<<" ]"<<x[u]<<endl;
	}

	cout<< "******************************************* PERIODS *******************************************"<< endl;
	// vertex with same color counted
	std::multiset<int> ms(x, x + V);
	for (auto it = ms.begin(), end = ms.end(); it != end;it = ms.equal_range(*it).second)
	{
		int cnt = 0;
		if ((cnt = ms.count(*it)) > 1)
			std::cout << "There are " << cnt << " of " << *it << std::endl;
		else if ((cnt = ms.count(*it)) <= 1)
			std::cout << "There are " << cnt << " of " << *it << std::endl;
	}

	f=get_max+1;//Χρώματα γράφου που χρειάζονται για τη λύση, εάν ειναι λιγότερα η ίσα με τις περιόδους υπάρχει εφικτή λύση
	return f;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Απλή υλοποίηση κλάσης γραφήματος για τα προβλήματα Toronto --> Graph
// Απευθείας γειτονικές κορυφές για κάθε κορυφή --> set<int> Graph::get_neighbors(int v)
// Έλεγχος εγκυρότητας χρωματισμού --> bool check_coloring(Graph g, int *solution)
// -------------------------------------------------------------------------------
// WARNING: Η συγκεκριμένη υλοποίηση προσπαθεί να είναι απλή, αυτό δεν σημαίνει ότι είναι και αποδοτική (:

class Graph {
private:
	int V;     // πλήθος των κορυφών του γραφήματος
	int *data; // πίνακας γειτνίασης

public:
	Graph(int v) :
			V(v) {
		data = new int[v * v];
		for (int i = 0; i < v * v; i++) {
			data[i] = 0;
		}
	}
	~Graph() {
		delete[] data;
	}

	int get_V() {
		return V;
	}

	void insert_edge(int i, int j, int value) {
		data[i * V + j] = value;
	}

	int get_edge_value(int i, int j) {
		return data[i * V + j];
	}

	// επιστρέφει ένα set από ακεραίους που είναι
	// οι αριθμοί κορυφών με τους οποίους συνδέεται απευθείας η κορυφή v
	set<int> get_neighbors(int v) {
		set<int> neighbors;
		for (int j = 0; j < V; j++) {
			if (get_edge_value(v, j) > 0)
				neighbors.insert(j);
		}
		return neighbors;
	}
};

bool check_coloring(Graph g, int *solution) {
	bool proper_coloring = true;
	for (int v = 1; v <= g.get_V(); v++) {
		int color_v = solution[v];
		set<int> neighbors_of_v = g.get_neighbors(v);
		for (int v2 : neighbors_of_v) {
			int color_v2 = solution[v2];
			if (color_v == color_v2) {
				proper_coloring = false;
				goto jump;
			}
		}
	}
	jump: return proper_coloring;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int count_common_elements(set<int> s1, set<int> s2) {
	int c = 0;
	for (int x : s1) // range based for
	{
		for (int y : s2) {
			if (x == y) {
				c++;
				break;
			}
		}
	}
	return c;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void read_data(string fn, int students, int exams,int periods) {
	// ανάγνωση δεδομένων
	vector<set<int>> exam_students(exams + 1);
	fstream fs(fn);
	if (!fs.is_open()) {
		cerr << "Could not open file " << fn << std::endl;
		exit(-1);
	}
	int student_id = 0;
	string line;
	while (getline(fs, line)) {
		if (line.empty())
			continue;
		student_id++;
		istringstream iss(line);
		int exam_id;
		while (iss >> exam_id) {
			exam_students[exam_id].insert(student_id);
			// cout << "Student " << student_id << " is enrolled in exam " << exam_id << endl;
		}
	}
	fs.close();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int i = 1; i <= exams; i++) {
		// cout << "Exam " << i << " Enrolled students: ";
		for (int student_id : exam_students[i]) // range based for
		{
			// cout << student_id << " ";
		}
		 //cout << endl;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// δημιουργία πίνακα γειτνίασης
	Graph a_graph(exams + 1); // δεδομένα από το αρχείο.stu
	GraphC g1(exams);
	int w[]={16,8,4,2,1};

	int sum=0;
	int c1=0;
			int *adj_matrix = new int[exams * exams];
	for (int i = 0; i < exams; i++) {
		for (int j = 0; j < exams; j++) {
			if (i == j) {
				adj_matrix[i * exams + j] = 0; // adj_matrix[i][j]
				continue;
			}
			int c = count_common_elements(exam_students[i + 1],exam_students[j + 1]);
			if (c > 0) {
				//  cout <<"i+1: "<< i + 1 << " "<<"j+1: " << j + 1 << " "<<"C: " << c << endl; // i= γαμμη πινακα, j =στηλη πινακα, c ποσα κοινα στοιχεια έχουν μεταξύ τους το i με το j

				a_graph.insert_edge(i + 1, j + 1, c);	//Graph neighbours

				g1.addEdge(i, j);				//GraphC coloring
			}

			adj_matrix[i * exams + j] = c;
			c1=c;	// για υπολογισμο κόστους
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Υπολογισμός συντελεστή πυκνότητας
	int c = 0;
	for (int i = 0; i < exams; i++) {
		for (int j = 0; j < exams; j++) {
			if (adj_matrix[i * exams + j] > 0) {
				c++;
			}
		}
	}

	cout << "value of c from Conflict Density " << c << endl;
	double cd = double(c) / double(exams * exams); //υπολογισμός συντελεστή πυκνότητας c / Περιοδοι εξετασεων * περιοδοι εξετάσεων
	cout << "Conflict Density: " << cd << endl;

	int max = 0;
	for (int i = 0; i < exams; i++) {
		int d = 0;
		for (int j = 0; j < exams; j++) {
			if (adj_matrix[i * exams + j] > 0) {
				d++;
			}
		}
		if (d > max) {
			max = d;
		}
	}

	cout << "Degree Max: " << max << endl;

	delete[] adj_matrix;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "*************GREEDY COLORING****************** " << endl;
	int colorperiods=0;
	int ifavailable=0;
	ifavailable=g1.greedyColoring(colorperiods);
	cout << "Number of available periods " << periods << endl;

	srand(time(NULL));
	for (int v = 1; v <= exams; v++) {
		set<int> neighbors = a_graph.get_neighbors(v);
		//cout << "Vertex:" << v << " has neighbors: ";
		for (int v2 : neighbors) {
			//cout << v2 << " ";
			if(v<=v2 && v2<=v+5)
			{
				sum +=w[(v2-v)-1]*c1;// υπολογισμος του weight??
			}
		}
		//cout << endl;

	}
	cout<<"Weight "<<sum<<endl;
	double cost=sum/students;
	cout<<"First cost of solution "<<cost<<endl;
	if (ifavailable<=periods)
	{
		cout<<"Exist an available solution with "<<ifavailable<<" periods."<<endl;
	}
	else
		cout<<"Does not exist any solution.Computed "<<ifavailable<<" number(s) of period(s)."<<endl;

}

////////////////////////////////////////////////////////////////////////////////////

string Uppercase(string answer)//συνάρτηση για κεφαλαία γράμματα
{
	std::string data = answer;
	// convert string to upper case
	std::for_each(data.begin(), data.end(), [](char & c){
c = ::toupper(c);
	});
return data;
}


int main() {
	int input_value = 0;
	string path="C:/Users/Tommy/eclipse-workspace/";
	string answer;
	string Danswer;
	bool question = true;

//***************************** GUI ******************************
	while (question == true) {



		cout << "Select a toronto problem to solve " << "1 : car-f-92" << endl;
		cout << "Select a toronto problem to solve " << "2 : car-s-91" << endl;
		cout << "Select a toronto problem to solve " << "3 : ear-f-83" << endl;
		cout << "Select a toronto problem to solve " << "4 : toy_e5_s6" << endl;
		cout << "Select a toronto problem to solve " << "5 : hec-s-92" << endl;
		cout << "Select a toronto problem to solve " << "6 : kfu-s-93" << endl;
		cout << "Select a toronto problem to solve " << "7 : lse-f-91" << endl;
		cout << "Select a toronto problem to solve " << "8 : pur-s-93" << endl;
		cout << "Select a toronto problem to solve " << "9 : rye-s-93" << endl;
		cout << "Select a toronto problem to solve " << "10 : sta-f-83" << endl;
		cout << "Select a toronto problem to solve " << "11 : tre-s-92" << endl;
		cout << "Select a toronto problem to solve " << "12 : uta-s-92" << endl;
		cout << "Select a toronto problem to solve " << "13 : ute-s-92" << endl;
		cout << "Select a toronto problem to solve " << "14 : yor-f-83" << endl;

		cin >> input_value;
			while ((input_value < 1) || (input_value > 14)) {
				cout << "Wrong answer. please type a number in index 1-14:"
						<< endl;
				cin >> input_value;
				if ((input_value > 0) && (input_value < 15))
					break;

			}

		switch (input_value){
		case 1:
			read_data(path+"car-f-92.stu", 18419,543,32);
			break;
		case 2:
			read_data(path+"car-s-91.stu", 16925,682,35);
			break;
		case 3:
			read_data(path+"ear-f-83.stu", 1125,190,24);
			break;
		case 4:
			read_data(path+"toy_e5_s6.stu", 6, 5,3);
			break;
		case 5:
			read_data(path+"hec-s-92.stu", 2823,81,18);
			break;
		case 6:
			read_data(path+"kfu-s-93.stu", 5349,461,20);
			break;
		case 7:
			read_data(path+"lse-f-91.stu", 2726,381,18);
			break;
		case 8:
			read_data(path+"pur-s-93.stu", 30029,2419,42);
			break;
		case 9:
			read_data(path+"rye-s-93.stu", 11483,486,23);
			break;
		case 10:
			read_data(path+"sta-f-83.stu", 611,139,13);
			break;
		case 11:
			read_data(path+"tre-s-92.stu", 4360,261,23);
			break;
		case 12:
			read_data(path+"uta-s-92.stu", 21266,622,35);
			break;
		case 13:
			read_data(path+"ute-s-92.stu", 2749,184,10);
			break;
		case 14:
			read_data(path+"yor-f-83.stu", 941,181,21);
			break;
		}
		cout << "Do you want to continue in another toronto problem;" << endl;
		cout << "Please type Yes/No" << endl;

		cin >> answer;
		Danswer=Uppercase(answer);

		if (Danswer == "NO") {
			question = false;
			cout <<"Program will be terminated"<< endl<< "BYE BYE!!!" << endl;
		}else if(Danswer!="YES")
		{
			while(Danswer!="YES")
			{
				cout<<"WRONG ANSWER!!!"<<endl<<"Please insert a correct answer."<<endl;
				cout << "Please type Yes/No" << endl;
						cin >> answer;
						Danswer=Uppercase(answer);
								if (Danswer == "NO") {
									question = false;
									cout <<"Program will be terminated"<< endl<< "BYE BYE!!!" << endl;
									break;
								}else if(Danswer=="YES")
									break;
			}
		}
	}

}
