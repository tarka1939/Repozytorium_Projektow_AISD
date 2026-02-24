#include "Css.h"
#include "BlockList.h"

using namespace std;
void ScanCSS(BlockList<CSS> &cssy, int &NumOfCss) {


    while (true) {
        CSS* newCSS = new CSS;
        int n = 0;
        scanf(" ????%n", &n);
        if (n != 0)
            break;
        while (true) {
            char* selector = new char[INPUTSIZE];
            selector[0] = '\0';
            char next = 0;
            if (scanf(" %[^,{\n]\n%c", selector, &next) == 0) {
                newCSS->selectors[newCSS->selNum] = selector;
                newCSS->selNum++;
                break;
            }
            else
            {
                newCSS->selectors[newCSS->selNum] = selector;
                newCSS->selNum++;
                //cout << selector << endl;
                if (next == '{') {
                    for (int i = INPUTSIZE - 1; i >= 0; i--) {
                        if (selector[i] == ' ') {
                            selector[i] = '\0';
                            break;
                        }
                    }
                    break;
                }
            }
        }
        while (true) {
            char* attribute = new char[INPUTSIZE];
            char* value = new char[200];
            int next = 0;
            scanf(" %[^:]: %[^;];\n", attribute, value);
            //cout << attribute << endl;
            //cout << value << endl; 
            scanf(" }%n", &next);
            bool wasSwaped=false;

            for (size_t i = 0; i < newCSS->attriNum; i++)
            {
                if (strcmp(newCSS->attributes[i],attribute)==0) {
                    delete[] newCSS->attributes[i];
                    newCSS->attributes[i] = attribute;
                    delete[] newCSS->values[i];
                    newCSS->values[i] = value;
                    wasSwaped = true;
                }
                
            }
            if (wasSwaped)
            {
            }
            else
            {
                newCSS->attributes[newCSS->attriNum] = attribute;
                newCSS->values[newCSS->attriNum] = value;
                newCSS->attriNum++;
            }

            if (next != 0) {
                cssy.AddValue(*newCSS);
                //cout << "css added" << endl;
                NumOfCss++;
                break;
            }
        }
        
    }
    //cout << "done";
}

int main()
{
    int NumOfCss = 0;
    char c = 0;
    BlockList<CSS> cssy;
    ScanCSS(cssy, NumOfCss);
    char line[1024];
    while (fgets(line, sizeof(line), stdin) != NULL){                          //TODO
        //_iobuf* input = stdin;
        //cout <<"c: " << c << endl;
        
        char command1[INPUTSIZE]="";
        char command2='\0';
        char command3[INPUTSIZE]="";
        int num = 0;
        
        if (feof(stdin)) {
            break;

        }
        if (sscanf(line, "****%n\n", &num)==1 || num == 4) {
            ScanCSS(cssy, NumOfCss);
        }
        else if (sscanf(line, " ?%c\n", &num)==1 || num == 1)
        {
            cout << "? == " << NumOfCss << endl;
        }
        else if(sscanf(line, "%[^,],%c,%[^\n]", command1, &command2, command3)==3)
        {
            if (command2 == 'S') {

                if (isdigit(command1[0])) {
                    int i;
                    sscanf(command1, "%d", &i);
                    CSS temp = cssy[i-1];
                    
                    if (i <= NumOfCss) {
                        if (!strcmp(command3, "?")) {
                            //i,S,? – wypisz liczbę selektorów dla sekcji nr i (numery zaczynają się od 1), jeśli nie ma takiego bloku pomiń;
                            cout << command1 << "," << command2 << "," << command3 << " == ";
                            cout << temp.selNum << endl;
                        }
                        else {
                            //i,S,j – wypisz j-ty selector dla i-tego bloku (numery sekcji oraz atrybutów zaczynają się od 1) jeśli nie ma sekcji lub selektora pomiń;
                            int j;
                            sscanf(command3, "%d", &j);
                            if (j <= temp.selNum) {
                                cout << command1 << "," << command2 << "," << command3 << " == ";
                                cout << temp.selectors[j - 1] << endl;

                            }
                        }
                    }
                }
                else {
                    //z,S,? – wypisz łączną (dla wszystkich bloków) liczbę wystąpień selektora z. Możliwe jest 0;
                    int numofSel = 0;
                    for (int i = 0; i < NumOfCss; i++) {
                        CSS temp = cssy[i];
                        for (size_t j = 0; j < temp.selNum; j++)
                        {
                            if (!strcmp(temp.selectors[j], command1))
                            {
                                numofSel++;
                                break;
                            }
                        }
                    }
                    cout << command1 << "," << command2 << "," << command3 << " == ";
                    cout << numofSel << endl;
                }
            }
            else if (command2 == 'A') {
                if (isdigit(command1[0])) {
                    int i;
                    sscanf(command1, "%d", &i);
                    if (i <= NumOfCss)
                    {
                        CSS& current = cssy[i - 1];
                        if (!strcmp(command3, "?")) {
                            // i, A, ? -wypisz liczbę atrybutów dla sekcji nr i, jeśli nie ma takiego bloku lub sekcji pomiń;
                            cout << command1 << "," << command2 << "," << command3 << " == ";
                            cout << current.attriNum << endl;
                        }
                        else {
                            //i,A,n – wypisz dla i-tej sekcji wartość atrybutu o nazwie n, jeśli nie ma takiego pomiń;




                            
                            List<char*> temp = current.attributes;
                            for (int attriNum = 0; attriNum < current.attriNum; attriNum++) {
                                if (!strcmp(temp[attriNum], command3)) {
                                    cout << command1 << "," << command2 << "," << command3 << " == ";
                                    cout << current.values[attriNum] << endl;
                                }
                            }
                        }
                    }
                }
                else {
                    //n,A,? – wypisz łączną (dla wszystkich bloków) liczbę wystąpień atrybutu nazwie n. (W ramach pojedynczego bloku duplikaty powinny zostać usunięte na etapie wczytywania). Możliwe jest 0;
                    int numofAtr = 0;
                    for (int i = 0; i < NumOfCss; i++) {
                        CSS temp = cssy[i];
                        for (size_t j = 0; j < temp.attriNum; j++)
                        {
                            if (strcmp(temp.attributes[j], command1) == 0)
                            {
                                numofAtr++;
                                break;
                            }
                        }
                    }
                    cout << command1 << "," << command2 << "," << command3 << " == ";
                    cout << numofAtr << endl;
                }

            }
            else if (command2 == 'E') {
                //z,E,n – wypisz wartość atrybutu o nazwie n dla selektora z, w przypadku wielu wystąpień selektora z bierzemy ostatnie. W przypadku braku pomiń;
                for (int i = -1; i >= -NumOfCss; i--) {
                    CSS temp = cssy[i];
                    bool hasSelector = false;
                    bool hasAttribute = false;
                    int attriNum = 0;
                    for (int j = 0; j < temp.selNum; j++) {
                        if (hasSelector = (strcmp(temp.selectors[j], command1) == 0)) {
                            break;
                        };
                    }
                    if (hasSelector) {
                        for (attriNum; attriNum < temp.attriNum; attriNum++) {
                            if (hasAttribute = (strcmp(temp.attributes[attriNum], command3) == 0)) {
                                break;
                            };
                        }
                    }
                    if (hasAttribute && hasSelector) {
                        cout << command1 << "," << command2 << "," << command3 << " == ";
                        cout << temp.values[attriNum] << endl;
                        break;
                    }
                }
            }
            else if (command2 == 'D') {
                int i;
                sscanf(command1, "%d", &i);
                if (i <= NumOfCss) {
                    if (!strcmp(command3, "*")) {
                        //i,D,* - usuń całą sekcję nr i (tj. selektory+atrybuty), po poprawnym wykonaniu wypisz deleted;

                        cssy.RemoveOnIndex(i-1);
                        NumOfCss--;
                        cout << command1 << "," << command2 << "," << command3 << " == ";
                        cout << "deleted" << endl;
                    }
                    else {
                        //i,D,n – usuń z i-tej sekcji atrybut o nazwie n, jeśli w wyniku operacji pozostaje pusta sekcja powinna zostać również usunięta (wraz z ew. selektorami), po poprawnym wykonaniu wypisz deleted;
                        int i;
                        sscanf(command1, "%d", &i);
                        CSS& temp = cssy[i - 1];
                        for (int attriNum = 0; attriNum < temp.attriNum; attriNum++) {
                            if (strcmp(temp.attributes[attriNum], command3) == 0) {
                                temp.attributes.Delete(attriNum);
                                temp.values.Delete(attriNum);
                                temp.attriNum--;
                                if (temp.attriNum == 0) {
                                    cssy.RemoveOnIndex(i - 1);
                                    NumOfCss--;
                                }
                                cout << command1 << "," << command2 << "," << command3 << " == ";
                                cout << "deleted" << endl;
                            }        
                        }
                    }
                }
            }
        }
    }
}
