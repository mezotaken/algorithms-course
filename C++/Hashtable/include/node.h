#pragma once

//Шаблон класса Элемент списка
template<class dtype>
struct node
{
public:
	dtype data;		//Данные в элементе
	node* next;		//Указатель на следующий эл-т
	bool operator< (const node& n) { return (data<n.data); }	//Операторы 
	bool operator> (const node& n) { return (data>n.data); }	//сравнения
	node(dtype in, node<dtype>* nxt = NULL) { data = in; next = nxt; }	//Конструктор с параметром
	node() { next = NULL; }										//Конструктор по умолчанию
};
