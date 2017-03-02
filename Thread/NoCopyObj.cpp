#include <iostream>
#include "NoCopyObj.h"

NoCopyObj::NoCopyObj(){
	std::cout<<"no copy object create!"<<std::endl;
}

NoCopyObj::NoCopyObj(NoCopyObj && obj) noexcept {
	std::cout<<"move construct function"<<std::endl;
}