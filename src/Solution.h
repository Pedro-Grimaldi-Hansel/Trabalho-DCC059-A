#ifndef SOLTION_H_INCLUDED
#define SOLTION_H_INCLUDED
#include <vector>

using namespace std;

class Solution
{
private:
    float custoTotal;
    vector<int> solucao;
    double tempoExecucao;
    float alpha;
public:
    Solution(){
        this->custoTotal = 0;
        this->tempoExecucao = 0;
        this->alpha = 0;
    };
    Solution(float custoTotal, vector<int> solucao, double tempoExecucao, float alpha){
        this->custoTotal = custoTotal;
        this->solucao = solucao;
        this->tempoExecucao = tempoExecucao;
        this->alpha = alpha;
    };
    ~Solution(){};

    float getCustoTotal(){return this->custoTotal;};
    vector<int> getSolucao(){return this->solucao;};
    float getAlpha(){return this->alpha;};
    double getTempoExecucao(){ return this->tempoExecucao; };

    void setCustoTotal(float custoTotal){this->custoTotal = custoTotal;}
    void setSolucao(vector<int> solucao){this->solucao = solucao;}
    void setTempoExecucao(double tempoExecucao){this->tempoExecucao = tempoExecucao;}
    void setAlpha(float alpha){this->alpha = alpha;}
};

#endif // SOLTION_H_INCLUDED