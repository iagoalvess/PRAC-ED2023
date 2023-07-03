#ifndef RELACAO_HPP
#define RELACAO_HPP

class Relacao{
private:
	long n;
	long p;
public:
	Relacao(long n);
	~Relacao();	

	bool temRelacao(long x, long y);
};

#endif