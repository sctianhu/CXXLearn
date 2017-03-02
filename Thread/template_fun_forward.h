//定义模版类
template<typename T> class function_forward;

//实例化模版类，同时再增加模版参数
template<typename R,typename A, typename T >
class function_forward<R (T::*)(A) >
{
public:
	typedef R(T::*fun)(A );

	function_forward(fun p,T *pobj):mPtr(p),mObj(pobj)
	{ 
	}

	R operator()(A a)
	{
		(mObj->*mPtr)(a);
	}

	fun mPtr;
	T *mObj;
};