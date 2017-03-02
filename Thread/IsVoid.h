struct is_void
{
	enum 
	{
		value = false,
	};
};

template< >
struct is_void<void>
{
	enum  
	{
		value = true,
	};
};