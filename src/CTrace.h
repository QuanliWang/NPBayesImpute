#pragma once
#if !defined(_CTRACE_H)
#define _CTRACE_H
class CTrace
{
public:
	CTrace(CLcm* pm);
	~CTrace(void);
	
	void SetTrace(std::vector<std::string> list, int size);
	std::vector<std::string> GetParameterList();
	std::vector<std::string> GetTracedList();
	void PrepareTrace();
	bool Trace(int index,int currentiter);
	void ClearTrace();
	
	double ** trace;
	
	int mnindex;
	int mnsize;
private:
	CLcm*  m;
	std::vector<std::string> TracedParameters;
};
#endif  //_CENV_H
