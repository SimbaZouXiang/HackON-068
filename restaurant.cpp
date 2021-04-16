#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <map>
using namespace std;

struct food{
  // the score of a food is formulated by score = initial*exp(decay)
  string name;
  double cooktime;

  food(){}

  food(string head){
    name = head;
  }
};

struct food_type_Hash{
  food foodlist[500]{}; //學以致用 :D

  bool Full(){
    for (int i = 0; i > 500; i++){
      if (foodlist[i].name == "" || foodlist[i].name == "deleted"){
        return false;
      }
    }
    return true;
  }

  void insert(food x){
    /*
    if (Full()){
      cout << "the list is full" << endl;
      return;
    }
    */
    int i = 0;
    while (i < 500){
      if (foodlist[i].name == "" || foodlist[i].name == "deleted"){
        foodlist[i] = x;
        return;
      }
      i++;
    }
  }

  void cancel(string x){
    int n = 0;
    for (int i = 0; i < 500; i ++){
      if (foodlist[i].name == x){
        foodlist[i].cooktime = 0;
        foodlist[i].name = "deleted";
        cout << "\ncompleted!\n\n";
        n = 1;
        break;
      }
    }
    if (n == 0){
      cout << "\nfood not found!\n\n";
    }
  }


  food search (string x){
    for (int i = 0; i < 500; i ++){
      if (foodlist[i].name == x){
        return foodlist[i];
      }
    }
    food emptyfood;
    return emptyfood;
  }


};

/* not so good using Queue, since we may need to make the food for the second customers in some cases
struct Queue{
  food waitlist[500]; // we can have atmost 500 customers in one queue
  int head = 0;
  int tail = 0;

  bool Empty(){
    return (tail = head);
  }
  bool Full(){
    return ((tail+1)%500 == head);
  }

  void Enqueue(food x){
    waitlist[tail] = x;
    tail ++;
  }
};
*/

struct customers{
  double initial; // will also be modified
  //double decay = -0.5 //must be negative!;
  food fdtype;
  customers * next = NULL;
};


bool operator< (const food& a, const food& b){
  return a.name < b.name;
}

bool operator== (const food& a, const food& b){
  return a.name == b.name;
}


struct Restaurant{

//variables
  food_type_Hash offerfood; // we assume theres only at most 500 types of food provided by the restaurant
  customers * dinein = new customers;//new customers;

  customers * store = new customers;//new customers;

  customers * online = new customers;//new customers;

  int totalseat = 100; // the restaurant can accomodate at most 100 ppl at the same time
  int seated = 0;

//methods
  void newfood(string name, double cooktime){
    food newfood;
    newfood.name = name;
    newfood.cooktime = cooktime;
    offerfood.insert(newfood);
  }
  void order(string type, food x){
    if (type == "dine_in"){
      double admendment = 1;
      if (seated == totalseat){
        admendment = 1.5; // can change
      }
      customers * p = new customers();
      p->fdtype = x;
      p->initial = 4 * admendment; // can change!
      p->next = NULL;
      if (dinein == NULL){
        dinein = p;
      }
      else{
        customers * current = dinein;
        while (current -> next != NULL){
          current = current -> next;
        }
        current->next = p;
        //cout << p->initial << endl << endl;
      }
    }

    if (type == "take_away_at_store"){
      customers * p = new customers();
      p->fdtype = x;
      p->initial = 5; // can change!
      p->next = NULL;
      if (store == NULL){
        store = p;
      }
      else{
        customers * current = store;
        while (current -> next != NULL){
          current = current -> next;
        }
        current->next = p;
      }
    }

    if (type == "online_order"){
      customers * p = new customers();
      p->fdtype = x;
      p->initial = 3; // can change!
      p->next = NULL;
      if (online == NULL){
        online = p;
      }
      else{
        customers * current = online;
        while (current -> next != NULL){
          current = current -> next;
        }
        current->next = p;
      }
    }
  } // end of the order method

  food nextfoodproduced(){

    map<food, double> score;


    for (food i : offerfood.foodlist){
      double mark = 0;
      if (i.name != "" && i.name != "deleted"){ // we found out the score of each food
        customers * current = dinein;
        while (current != NULL){
          if (current -> fdtype == i){
            mark += current->initial * sqrt((current->fdtype.cooktime));
          }
          current = current->next;
        }

        current = store;
        while (current != NULL){
          if (current -> fdtype == i){
            mark += current->initial * sqrt((current->fdtype.cooktime));
          }
          current = current->next;
        }

        current = online;
        while (current != NULL){
          if (current -> fdtype == i){
            mark += current->initial * sqrt((current->fdtype.cooktime));
          }
          current = current->next;
        }
      }

      score[i] = mark;
    }// end of the for loop

    // return and delete the highest ranked food, and modified the initial of all customers
    double max_num = 0;
    food shouldcook;
    for (food i : offerfood.foodlist){
      if (i.name != "" && i.name != "deleted"){
        if (score[i] > max_num){
          max_num = score[i];
          shouldcook = i;
        }
      }
    }
    //above this line, everything is fine.
    //return shouldcook;

    customers * current = dinein;
    double admendment = 1;
    int num = 0;
    if (seated == totalseat){
      admendment = 1.5;
    }
    while (current -> next != NULL){
      while (current -> next != NULL && current -> next -> fdtype.name == shouldcook.name){
        current -> next = current->next->next;
        num ++;
      }
      if (current -> next != NULL){
               // issue arrised!
        current = current -> next;
        double original = current -> initial;
        current->initial = original + sqrt(shouldcook.cooktime) * admendment;
        //cout << "\n\n\n\n\n\n\n" << current -> fdtype.name <<current->initial << "\n\n\n\n\n\n\n\n\n";
      }
    }

    current = store;
    while (current -> next != NULL){
      while (current -> next != NULL && current -> next -> fdtype.name == shouldcook.name){
        current -> next = current->next->next;
        num ++;
      }
      if (current -> next != NULL){
               // issue arrised!
        current = current -> next;
        double original = current -> initial;
        current->initial = original + sqrt(shouldcook.cooktime) * admendment;
        //cout << "\n\n\n\n\n\n\n" << current -> fdtype.name <<current->initial << "\n\n\n\n\n\n\n\n\n";
      }
    }

    current = online;
    while (current -> next != NULL){
      while (current -> next != NULL && current -> next -> fdtype.name == shouldcook.name){
        current -> next = current->next->next;
        num ++;
      }
      if (current -> next != NULL){
               // issue arrised!
        current = current -> next;
        double original = current -> initial;
        current->initial = original + sqrt(shouldcook.cooktime) * admendment;
        //cout << "\n\n\n\n\n\n\n" << current -> fdtype.name <<current->initial << "\n\n\n\n\n\n\n\n\n";
      }
    }

    shouldcook.cooktime = num;
    return shouldcook;
  }// end of the function nextfoodproduced

  void enter_dine_in(int n){
    if (seated + n > totalseat){
      cout << "\nthe seats are full!\n\n";
    }
    else{
      seated += n;
      cout << "\ncompleted!\n\n";
    }
  }

  void leave_dine_in(int n){
    seated -= n;
    cout << "\ncompleted\n\n";
  }

}; // end of the struct restaurant

int main(){
  Restaurant rant;
  int commend;
  cout << "welcome to use restaurant version 1.0.\n";
  while (true){
    cout << "Please choose from the following functions:" << endl;
    cout << "1. Add a new type of possible food.\n";
    cout << "2. Delete a possible food.\n";
    cout << "3. Add a new order.\n";
    cout << "4. which food should you do next? \n";
    cout << "5. New customers choose to dine in!\n";
    cout << "6. Some dine-in customers are leaving!\n";
    cout << "7. Leave the system.\n";
    cout << "your commend is: ";
    cin >> commend;
    if (commend == 1 ){
      food newfood;
      cout << "please type the name of the new food: ";
      cin >> newfood.name;
      cout << "please type the production time the new food (in minutes): ";
      cin >> newfood.cooktime;
      food testing;
      testing = rant.offerfood.search(newfood.name);
      if (testing.name == ""){
        rant.offerfood.insert(newfood);
        cout << "\ninsertion completed! \n\n";
      }
      else {cout << "food already there!" << endl;}
    }

    else if (commend == 2){
      //under construction
      string name;
      cout << "please type the name of the food to be deleted: ";
      cin >> name;
      rant.offerfood.cancel(name);
    }

    else if (commend == 3){
      cout << "1. dine in the restaurant.\n2. takeaway order at the restaurant.\n3. Online order.";
      cout << "what is the type of the new order: \n";
      int types;
      cin >> types;
      string newfood;
      cout << "please type the name of the ordered food: ";
      cin >> newfood;
      food testing;
      testing = rant.offerfood.search(newfood);
      if (testing.name == ""){
        cout << "this food is not available!\n\n\n" ;
      }
      else{
        int n = 0;
        if (types == 1){
          rant.order("dine_in", testing);
          //cout << "\n\n\n\n\n\n\n" << testing.name << " " << testing.cooktime << "\n\n\n\n\n\n\n\n\n";
          n = 1;
        }
        else if (types == 2){
          rant.order("take_away_at_store", testing);
          n = 1;
        }
        else if (types == 3){
          rant.order("online_order", testing);
          n = 1;
        }
        else { cout << "\nInvalid Order!\n\n";}
        if (n == 1){
          cout << "\nnew order added!\n\n" << endl;
        }
      }
    }// end of commend 3

    else if (commend == 4){
      food nextdo;
      nextdo = rant.nextfoodproduced();
      if (nextdo.name != ""){
        cout << "\nplease prepare " << nextdo.name << " for " << nextdo.cooktime << "\n\n";
      }
      else {
        cout << "\nThere's currently no food orders. \n\n";
      }
    }

    else if (commend == 5){
      int n;
      cout << "How many customers are coming: ";
      cin >> n;
      rant.enter_dine_in(n);
    }

    else if (commend == 6){
      int n;
      cout << "How many customers are leaving: ";
      cin >> n;
      rant.leave_dine_in(n);
    }

    else if (commend == 7){
      cout << "\nSee you Soon :D!\n\n";
      break;
    }

    else if (commend == 10){
      for (int i = 0; i < 20; i ++){
        cout << rant.offerfood.foodlist[i].name << " " <<  rant.offerfood.foodlist[i].cooktime << endl;
      }
    }

    else if (commend == 11){
      customers * current = rant.dinein;
      while (current != NULL){
        cout << current->fdtype.name << " " << current->initial << endl;
        current = current->next;
      }
    }
    else {
      cout << "\nInvaild Order!\n\n";
    }
  } // end of the while loop
  return 0;
}
