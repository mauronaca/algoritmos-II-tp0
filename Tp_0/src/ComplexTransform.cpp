#include "ComplexTransform.h"


int ComplexTransform::userOption = 0;

ComplexTransform::ComplexTransform(){
	this->option = userOption;
}

ComplexTransform::ComplexTransform(int i){
	this->option=i;
}

ComplexTransform::~ComplexTransform(){
/*No solicita memoria dinámica*/
}

void ComplexTransform::fun(Complejo & input){
		switch(option){
		case 1:
			this->input=input;
			this->output=input;
			break;
		case 2:
			this->input=input;
			this->output.setReal(exp(input.getReal())*cos(input.getImag()));
			this->output.setImag(exp(input.getReal())*sin(input.getImag()));
			break;
		case 3:
			this->input=input;
			this->output.setReal(-1*input.getReal());
			this->output.setImag(-1*input.getImag());
			break;
		default:
			this->input=input;
			this->output=input;
	}
}


Complejo ComplexTransform::getInput(){
	return this->input;
}

Complejo ComplexTransform::getOutput(){
	return this->output;
}

void ComplexTransform::setOption(int option)
{
	ComplexTransform::userOption = option;
}

int ComplexTransform::getOption(void)
{
	return this->option;
}
