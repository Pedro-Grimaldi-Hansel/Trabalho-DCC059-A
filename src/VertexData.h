#ifndef VERTEXDATA_H_INCLUDED
#define VERTEXDATA_H_INCLUDED

class VertexData{

    private:
        int id; // id de arquivo
        int grau;
        float custo;
        
    public:
        VertexData(int id, int grau, float custo){
            this->id = id;
            this->grau = grau;
            this->custo = custo;
        };
        int getId(){return this->id;};
        int getGrau(){return this->grau;};
        void setGrau(int grau){this->grau = grau;};
        float getCusto(){return this->custo;};
        void setCusto(float custo){this->custo = custo;};
        float getPrioridade(){return this->custo/this->grau;};
};

#endif // VERTEXDATA_H_INCLUDED
