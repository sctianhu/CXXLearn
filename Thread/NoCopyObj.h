class NoCopyObj{
public:
	NoCopyObj();
	/* error: call to deleted constructor of 'NoCopyObj'
	* 如果用了delete标记，等于以前的private拷贝构造函数
	*/
	NoCopyObj(const NoCopyObj & obj) = delete;	

	NoCopyObj(NoCopyObj && obj) noexcept;
};