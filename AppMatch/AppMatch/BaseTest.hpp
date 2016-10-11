#pragma once
#include "Parser.hpp"
#include <iostream>

#define ISLOG false


std::vector<HTerm> decompose(string phase);;

string decompose_bracket(string phase, string dlm);

CList *mk_CList_Literal(std::vector<HTerm> strList);
HBlockNoum noum(std::string n) ;


void testeParser_listA();
void testeParser_listB();

void testeParser_actionA();
void testeParser_actionB();
void testeParser_actionC();


void testeParser_1();
void testeParser_2();
void testeParser_2a();
void testeParser_3();
void testeParser_4();
void testeParser_5();
void testeParser_5b();
void testeParser_5c();
void testeParser_5d();
void testeParser_5e();
void testeParser_5f();

void testeParser_6();
void testeParser_7a();
void testeParser_7b();
void testeParser_7c();
void testeParser_7d();
void testeParser_21();

void testeRelation1();
void testeRelation2();
void testeRelation3();
void testeRelation4();

void testeSerialize1();