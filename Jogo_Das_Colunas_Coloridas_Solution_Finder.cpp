#include <bits/stdc++.h>


//O que tem pra fazer:
//1- Calcular tempo
//2- Coletar dados
//3- Fazer os slides




const int n = 4;
const int depth = 24;
const int depth_return = 24;
const int first_bfs_limit = 10000;
using namespace std;
using matriz_str = array<array<char, n>, n>;
using pii = pair<unsigned char, unsigned char>;



set<matriz_str> matrizes1;
set<matriz_str> matrizes2;
set<matriz_str> matrizes3;
set<matriz_str> vazio {};
//queue<matriz_str> andar_atual;
//vector<matriz_str> andar_anterior;
map<matriz_str,int> mapadistfinal;

int dist = 0;
int dirI[4] = {1, 0, -1, 0};
int dirJ[4] = {0, 1, 0,  -1};

bool valid(int i, int j){

	if(i < 0 || j < 0) return false;
	if(i >= n || j >= n) return false;
	return true;
}

pii zeropos(matriz_str mm)
{
    pii pos0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if (mm[i][j] == '0')
            {
                pos0 = make_pair(i,j);
                return pos0;
            } 
        }
    }
    return pos0;
}

void bfs()
{
    queue<pair<matriz_str,unsigned char>> filinha;
    //ideia, criar uma função que acha a posição do 0 ao invés de guardar
    pii pos0 = {n-1,n-1};
    //definindo o primeiro no;
    matriz_str matriz;
    
    for(int j=0; j<n; j++)
    	for(int i=0;i<n; i++)
    		matriz[i][j] = (char)('0'+j+1);
    
    matriz[n-1][n-1] = '0';
    matrizes1.insert(matriz);
    mapadistfinal[matriz] = dist;
    filinha.push(make_pair(matriz,dist));
    float batata = 1;

    while(!filinha.empty())
    {   

        //ideia: guardar em cada matriz um caractere ou int que indica a posição
        //pela qual o pai gerou ele
        //deu ruim

        
        int dist_atual = filinha.front().second;

        //Aqui está Hard coded o limite (no if), caso o limite
        //seja impossível de ser alcançado, o bfs
        //rodará até o final, caso não,
        //o bfs rodará até o limite e parará por aí.
        if(dist_atual > first_bfs_limit)
        {
            for(int i =0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    cout << matriz[i][j] << " ";
                }
                cout << "\n";
            }
            cout << "\n";
            return;
        }

        if(dist != dist_atual)
        {
            //cout << matrizes1.size() << " " << matrizes2.size() << " " << matrizes3.size() << " ";
            cout <<"D: " << dist_atual <<"  Mem Mat: " << (matrizes2.size()+matrizes1.size() + matrizes3.size()+filinha.size()) << " Cres: " << (((matrizes3.size() + matrizes2.size()+matrizes1.size()+filinha.size())/batata)-1)*100 << "% Save: " << mapadistfinal.size();
            batata = matrizes2.size()+matrizes1.size() + matrizes3.size() + filinha.size();
            dist = dist_atual;
            if(dist%3 == 0)
            {
                cout << " Mat atual: " << matrizes1.size()  << "\n";
                matrizes2.clear();
            } 
            else if (dist%3 == 1)
            {
                matrizes3.clear();
                cout << " Mat atual: " << matrizes2.size()  << "\n";
            } 
            else
            {
                matrizes1.clear();
                cout << " Mat atual: " << matrizes3.size()  << "\n";
            }
        }


        matriz = filinha.front().first;
        //pos0 = filinha.front().second;
        pos0 = zeropos(matriz);
        filinha.pop();
        
        for(int d = 0; d < 4; d++){
			pair<int, int> novapos;
			novapos.first = pos0.first + dirI[d];
			novapos.second = pos0.second + dirJ[d];
			if(valid(novapos.first, novapos.second)){
				auto novamat = matriz;
				swap(novamat[pos0.first][pos0.second] , novamat[novapos.first][novapos.second]);
				if(!(matrizes1.count(novamat)) && !(matrizes2.count(novamat)) && !(matrizes3.count(novamat))){
                    if(dist_atual%3 == 0) matrizes2.insert(novamat);
                    else if(dist_atual%3 == 1) matrizes3.insert(novamat);
                    else matrizes1.insert(novamat);
                    if(((dist_atual+1)%depth) == 0)
                    {
                        mapadistfinal[novamat] = dist_atual+1;
                    } 
                    //cout<<"ind "<<ind<<"\n";
                    filinha.push(make_pair(novamat,(dist_atual +1)));			
				}
			}
		}
    }
    for(int i =0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout << matriz[i][j] << " ";
            }
            cout << "\n";
        }
    cout << "\n";
    return;


}  

vector<matriz_str> pai;
vector<matriz_str> pai_final;
map<matriz_str,int> mapaind;
bool primeira_vez = true;
bool firsttrigger = false;
int firstcounter = 0;
int firstdepth = 1000000;
matriz_str primeiramat;
pii posmat;

int bfsreturn(matriz_str matriz,int posl,int posc,int dist_at = -10000)
{   
    int counter = 0;
    int a = 0;
    vector<matriz_str> pai_temp;
    queue<pair<matriz_str,unsigned char>> filinha;
    pii pos0 = {posl,posc};
    int ind = 0;	
    //matriz_str matriz_original = matriz;
    mapaind[matriz] = ind;
    pai.push_back(matriz);
    filinha.push(make_pair(matriz,counter));
    bool vazia = false;

    while(1)
    {   
        if(!filinha.empty())
        {  
        matriz = filinha.front().first;
        //pos0 = filinha.front().second;
        pos0 = zeropos(matriz);
        counter = filinha.front().second;
        filinha.pop();
        }

        if(counter != a)
        {
            a = counter;
            cout << counter << '\n';
        }
        if(counter == depth_return+1) return -1;
        


        if((firsttrigger && (counter >= depth)) || vazia)
        {
            firsttrigger = false;
            primeira_vez = false;
            ind = mapaind[primeiramat];
            matriz_str temp = primeiramat;
            while(ind != 0)
                {
                    //cout << ind << " ";
                    pai_temp.push_back(primeiramat);
                    primeiramat = pai[ind];
                    ind = mapaind[primeiramat];
                }
                pai_temp.push_back(primeiramat);
                pai.clear();
                mapaind.clear();                    
                if(mapadistfinal[temp] == 0)
                {
                    if(pai_final.size()>0) pai_final.pop_back();
                    for(int i = 0;i<pai_temp.size();i++)
                    {
                        pai_final.push_back(pai_temp[i]);
                    }
                    return 0;
                }
                bfsreturn(temp,posmat.first,posmat.second,mapadistfinal[temp]);
                if(pai_final.size()>0) pai_final.pop_back();
                for(int i = 0;i<pai_temp.size();i++)
                {
                    pai_final.push_back(pai_temp[i]);
                }
                            
                return 0;

        }
        if(filinha.empty() && counter >= 2) vazia = true;
        
        for(int d = 0; d < 4; d++){
			pii novapos;
			novapos.first = pos0.first + dirI[d];
			novapos.second = pos0.second + dirJ[d];
			if(valid(novapos.first, novapos.second)){
				auto novamat = matriz;
				swap(novamat[pos0.first][pos0.second] , novamat[novapos.first][novapos.second]);
				if(!mapaind.count(novamat)){
					mapaind[novamat] = ++ind;
                    pai.push_back(matriz);
					if(mapadistfinal.count(novamat)){
                        if(primeira_vez)
                        {
                            firsttrigger = true;
                            if(firstdepth > mapadistfinal[novamat])
                            {
                                firstdepth = mapadistfinal[novamat];
                                primeiramat = novamat;
                                posmat.first = novapos.first;
                                posmat.second = novapos.second;
                            } 
                        }
                        if(!primeira_vez && (mapadistfinal[novamat] == (dist_at - depth)))
                        {
                            matriz_str temp = novamat;
                            while(ind != 0)
                            {
                                //cout << ind << " ";
                                pai_temp.push_back(novamat);
                                novamat = pai[ind];
                                ind = mapaind[novamat];
                            }
                            pai_temp.push_back(novamat);
                            pai.clear();
                            mapaind.clear();                    
                            if(mapadistfinal[temp] == 0)
                            {
                                if(pai_final.size()>0) pai_final.pop_back();
                                for(int i = 0;i<pai_temp.size();i++)
                                {
                                    pai_final.push_back(pai_temp[i]);
                                }
                                return 0;
                            }
                            bfsreturn(temp,novapos.first,novapos.second,mapadistfinal[temp]);
                            if(pai_final.size()>0) pai_final.pop_back();
                            for(int i = 0;i<pai_temp.size();i++)
                            {
                                pai_final.push_back(pai_temp[i]);
                            }
                            
                            return 0;
                        }
                    }
                    //cout<<"ind "<<ind<<"\n";
					filinha.push(make_pair(novamat,counter+1));				
				}
    //else if(pai[mapaind[novamat]] == pai[mapaind[matriz]])
    //printf("arroz\n");
			}
		}
    }


}

int main(void)
{
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    matriz_str matriz;
    bfs();
    cout << "foi\n";
   // matrizes1.clear();
    while(1)
    {
        firstdepth = 10000;
        firsttrigger = false;
        pai_final.clear();
        primeira_vez = true;
        int x,y;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cin >> matriz[i][j];
                if(matriz[i][j] == '0')
                {
                    x = i;
                    y = j;
                }
            }
        }
        int result =  bfsreturn(matriz,x,y);
        cout << "foi \n";
        
        int indice = pai_final.size()-2;
        int distancia2 = 0;
        if(result != -1)
        {
            while(indice != -1)
            {
                matriz = pai_final[indice];
                distancia2++;
                indice--;
                cout << "\t\t" << distancia2 << ":\n\t\t";
                for(int i=0;i<n;i++)
                {
                    for(int j=0;j<n;j++)
                    {
                        cout << matriz[i][j] << " ";
                    }
                    cout << "\n\t\t";
                }
                cout << "\n\n";
            }

            cout << "Prontinho, a menor quantidade de passos possivel é :" << distancia2 << '\n';
        }
        else cout << "Essa solução leva mais de 40 passos";

        

    }
    
    return 0;

}