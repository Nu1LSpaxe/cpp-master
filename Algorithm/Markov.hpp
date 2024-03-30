#pragma once
#ifndef MARKOV_H
#define MARKOV_H
#endif

#include <string>
#include <map>
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

class Markov
{
public: 
	const int StateNumber = 3;
	// Each state S_i has V_k probability => B_i(k)
	const int ObervationProbability = 3;
	// N steps means N states
	const int Steps = 15;
};