#include <iostream>
#include <utility>
#include <set>

using namespace std;

template<class _A, class _B, class _Compare=less<_A> >
class MMap:public set< pair< _A,_B>,_Compare>
{
public:
	MMap():set<pair< _A,_B> ,_Compare >() {}
	~MMap() {}
};

template<typename InPair>
struct MMapComp
{
	bool operator()(InPair a, InPair b){
		if(a.first == b.first){
			return a.second > b.second;
		}
		else{
			return a.first < b.first;
		}
	}
};

