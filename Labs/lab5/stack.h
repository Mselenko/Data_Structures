class Stack {
	char *data_;
	int top_;
public:
	Stack()
	{
		data_ = new char[20];
		top_ = 0;
	}
	void push(char data);
	void pop();
	char top() const;
	bool isEmpty() const;
	bool isFull() const;
};
void Stack::push(char data)
{
	if (top_ != 43)
	{
		data_[top_] = data;
		top_++;
	}
}
void Stack::pop()
{
	if (top_ > 0)
	{
		top_--;
	}
}
char Stack::top() const
{
	if (top_ != 0)
	{
		return data_[top_ - 1];
	}
}
bool Stack::isEmpty() const
{
	return top_ == 0;
}
bool Stack::isFull() const
{
	return top_ == 43;
}
