#include "Coin.h"
Coin::Coin(){
	this->m_DiameterMax  =0;
	this->m_DiameterMin =0;
    this->m_Value=0;
}
Coin::~Coin(){
}

Coin::Coin(double m_DiameterMax ,double m_DiameterMin, double m_Value)
{
	
	this->m_DiameterMax  = m_DiameterMax ;
	this->m_DiameterMin =m_DiameterMin;
    this->m_Value= m_Value;
}


double Coin::getDiameterMax(){
	return this->m_DiameterMax ;
}
double Coin::getDiameterMin(){
	return this->m_DiameterMin;
}
double Coin::getValue(){
	return this->m_Value;
}

bool Coin::isTheCoin( double diameterImage){
	if( diameterImage <this->m_DiameterMax  && diameterImage>=this->m_DiameterMin)
        return true;
    else
        return false;
}



