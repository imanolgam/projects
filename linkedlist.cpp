#include <iostream>

using namespace std;

template <class T>
class Nodo{
	public:
		T value;
		Nodo<T> *next;
		
		Nodo(T val){
			value=val;
			next=NULL;
		}
};

template <class T>
class LinkedList{
	public:
	Nodo<T> *root;
	
	LinkedList(){
		root=NULL;
	}
	
	void append(Nodo<T> *nuevo){
		if(root==NULL){
			root=nuevo;
		}else{
			Nodo<T> *temp=root;
			while(temp->next!=NULL){
				temp=temp->next;
			}
			temp->next=nuevo;
		}
	}
	
	void append(T value){
		Nodo<T> *nuevo=new Nodo<T>(value);
		append(nuevo);
	}
	
	T getElementAt(int pos){
		Nodo<T> *temp=root;
		int i=0;
		while(temp!=NULL && i<pos){
			temp=temp->next;
			i++;
		}
		if(i==pos && temp!=NULL){
			return temp->value;
		}else{
			return NULL;
		}
	}
	
	void setElementAt(int pos, T value){
		Nodo<T> *temp=root;
		int i=0;
		while(temp!=NULL && i<pos){
			temp=temp->next;
			i++;
		}
		if(i==pos && temp!=NULL){
			 temp->value=value;
		}
	}
	
	
	void insert(Nodo<T> *nuevo, int pos){
		if(root==NULL){
			root=nuevo;
		}else if(pos==0){
			nuevo->next=root;
			root=nuevo;
		}else{
			Nodo<T> *temp=root;
			int i=0;
			while(temp->next!=NULL && i<pos-1){
				temp=temp->next;
				i++;
			}
			nuevo->next=temp->next;
			temp->next=nuevo;
		}
	}
	
	void insert(T value, int pos){
		Nodo<T> *nuevo=new Nodo<T>(value);
		insert(nuevo, pos);
	}
	
	void remove(T value){
		if(root==NULL){
			return;
		}else if(root->value==value){
			Nodo<T> *aBorrar=root;
			root=root->next;
			delete aBorrar;
		}else{
			Nodo<T> *temp=root;
			while(temp->next!=NULL){
				//cout<<temp->value<<endl;
				if(temp->next->value==value){
					Nodo<T> *aBorrar=temp->next;
					//temp->next=temp->next->next
					temp->next=aBorrar->next;
					delete aBorrar;
					return;
				}
				temp=temp->next;
			}
		}
	}
	
	void print(){
		Nodo<T> *temp=root;
		while(temp!=NULL){
			cout<<temp->value<<",";
			temp=temp->next;
		}	
		cout<<endl;
	}
	void duplicar(){
		Nodo<T> *temp=root;
		while(temp!=NULL){
			Nodo<T> *nuevo=new Nodo<T>(temp->value);
			Nodo<T> *tempa=temp->next;
			nuevo->next=temp->next;
			temp->next=nuevo;
			temp=tempa;
		}
		
	}

    int Count(T searchFor){
        Nodo<T> *temp=root;
        int count = 0;
        while(temp!=NULL){
            if(temp->value == searchFor){
                count ++;
            }
            temp = temp->next;
        }
        cout << count << endl;

        return count;
    }

    void DeleteList(){
        Nodo<T> *temp=root;
        while(temp!=NULL){
            Nodo<T> *aBorrar=root;
            root=root->next;
			delete aBorrar;
            temp = root;
        }
        if(root == NULL){
            cout << "¡La lista fue borrada exitosamente!" << endl;
        }

    }

    void SortedInsert (T newValue){
        Nodo<T> *temp=root;
        Nodo<T> *nuevo=new Nodo<T>(newValue);
		if(temp == NULL || temp->value>=nuevo->value){
			nuevo->next = temp;
			temp = nuevo;
		}
		else{
			while (temp!=NULL && temp->next->value < nuevo->value){
				temp = temp->next;
			}
		nuevo->next=temp->next;
		temp->next=nuevo;
		}
    }

    void RemoveDuplicates (){
        Nodo<T> *temp=root;
		Nodo<T> *next_next;


        while(temp->next!=NULL){
            if(temp->value == temp->next->value){
                next_next=temp->next->next;
				free(temp->next);
				temp->next = next_next;
            }
			else{
				temp = temp->next;
			}
        }

    }

	void Reverse(){
		Nodo<T> *temp=root;
		Nodo<T> *prevNode=NULL;
		Nodo<T> *nextNode=NULL;

		while(temp!=NULL){
			nextNode=temp->next;
			temp->next=prevNode;
			prevNode=temp;
			temp=nextNode;
		}
		root = prevNode;
	}

};


int main(){
	LinkedList<int> list;
    int searchFor = 7;
	//Nodo<int> *nuevo=new Nodo<int>(3);
	//list.append(nuevo);
	list.append(3);
	list.append(5);
	list.append(7);
    list.append(7);
    list.append(7);
	list.append(20);
	cout <<"La lista con los valores agregados es: ";
    list.print();
    list.SortedInsert(4);
    list.SortedInsert(8);
    list.SortedInsert(6);
	cout <<"La lista con los valores insertados es: ";
	list.print();
    cout <<"Cantidad de veces que aparece " << searchFor << ": ";
    list.Count(searchFor);
	list.RemoveDuplicates();
	cout <<"La lista sin los valores duplicados es: ";
	list.print();
	list.Reverse();
	cout <<"La lista con valores revertidos es: ";
	list.print();
	list.duplicar();
	list.print();
    list.DeleteList();
    list.print();
}