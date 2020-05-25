#ifndef Coin__H
#define Coin__H

class Coin
{

private:
double m_DiameterMax;
double m_DiameterMin;
double m_Value;

public:
Coin();
Coin(double m_DiameterMax,double m_DiameterMin, double m_Value);
virtual ~Coin();
double getDiameterMax();
double getDiameterMin();
double getValue();
bool isTheCoin( double diameterImage);
	
};

#endif
